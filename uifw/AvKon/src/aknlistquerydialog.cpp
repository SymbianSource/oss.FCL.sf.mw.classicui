/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
*
*/

#include <eikcapc.h>
#include <AknMediatorFacade.h>
#include <MediatorEventProvider.h>
#include <MediatorDomainUIDs.h>
#include <AknNotifyStd.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>

#include "aknPopupHeadingPane.h"
#include "aknlistquerycontrol.h"
#include "aknlistquerysearchcontrol.h"
#include "aknlists.h"

#include "aknenv.h"
#include "aknborders.h"
#include "aknconsts.h"

#include "avkon.hrh"
#include <avkon.rsg>
#include <avkon.mbg>

#include "aknlistquerydialog.h"
#include <AknIconUtils.h>
#include <AknIconArray.h>

#include <aknsfld.h>
#include "aknmessagequerycontrol.h"

#include <skinlayout.cdl.h>

#include <AknLayout2ScalableDef.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <gfxtranseffect/gfxtranseffect.h>
#include <akntransitionutils.h>
#include <avkondomainpskeys.h>
#include <e32property.h>
#include <touchfeedback.h>

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif

#include <AknTasHook.h> // for testability hooks
NONSHARABLE_CLASS(CAknListQueryMediatorObserver): public CBase, public MAknDialogMediatorObserver
    {
public:
    CAknListQueryMediatorObserver(CArrayFixFlat<TInt>* aItemIdArray, CAknListQueryDialog& aOwner)
        :iItemIdArray(aItemIdArray), iOwner(aOwner)
        {}
    
    ~CAknListQueryMediatorObserver()
        {
        NotifyMediatorExit();
        delete iItemIdArray;
        }
        
    void SetExternalObserver(MAknDialogMediatorObserver* aObs)
        {
        iExternalObserver = aObs;
        }
        
    // From MAknDialogMediatorObserver
    TAknDialogMediatorObserverCommand MediatorCommandL( TUid aDomain,
                                       TUid aCategory, 
                                       TInt aCommandId,
                                       const TDesC8& aData );
    
    void UpdateL(TInt aSelectionIndex);
    
    void NotifyMediatorExit()
        {
        if (iExternalObserver)
            iExternalObserver->NotifyMediatorExit();
        }
            
private:
    CArrayFixFlat<TInt>* iItemIdArray;
    CAknListQueryDialog& iOwner;
    MAknDialogMediatorObserver* iExternalObserver;
    };
    
TAknDialogMediatorObserverCommand CAknListQueryMediatorObserver::MediatorCommandL( TUid aDomain,
                                       TUid aCategory, 
                                       TInt aCommandId,
                                       const TDesC8& aData )
    {
    TAknDialogMediatorObserverCommand ret = EHandleAsNormal;
    if (iExternalObserver)
        {
        ret = iExternalObserver->MediatorCommandL(aDomain, aCategory, aCommandId, aData);
        }
    
    if (ret == EHandleAsNormal && aData.Length() >= sizeof(SAknIntegerUpdate))
        {
        SAknIntegerUpdate* params = (SAknIntegerUpdate*) &aData;
        
        if (params->iCmd == EAknListQueryUpdateSelection)
            {
            TInt newSelectionId = params->iId;
            for (TInt i = iItemIdArray->Count()-1; i >= 0; i--)
                {
                if (newSelectionId == iItemIdArray->At(i))
                    {
                    CEikListBox* listBox = iOwner.ListBox();
                    if (listBox)
                        {
                        listBox->SetCurrentItemIndex( i );                        
                        }
    
                    break;
                    }
                }
            return EDoNothingWithThisCommand;
            }
        
        }
    
    return EHandleAsNormal;
    }

void CAknListQueryMediatorObserver::UpdateL(TInt aSelectionIndex)
    {
    CAknMediatorFacade* dialogClient = AknMediatorFacade(&iOwner);
    if (dialogClient)
        {
        if (aSelectionIndex < iItemIdArray->Count())
            {
            SAknIntegerUpdate s = 
                {
                EAknListQueryUpdateSelection,
                iItemIdArray->At(aSelectionIndex)
                };
            
            TPckg<SAknIntegerUpdate> pck(s);
            dialogClient->ResetBuffer();
            dialogClient->BufStream() << pck;
            dialogClient->BufStream().CommitL();
            dialogClient->PostUpdatedDataL();
            }
        }
    
    }

EXPORT_C CAknListQueryDialog::CAknListQueryDialog(TInt* aIndex)
	: CAknQueryDialog(ENoTone)
    {
    iIndex = aIndex;
    iEnterKeyPressed = EFalse;

    GfxTransEffect::Register(this,KGfxContextMenuControlUid);
    AKNTASHOOK_ADD( this, "CAknListQueryDialog" );
    }


EXPORT_C CAknListQueryDialog::CAknListQueryDialog(CListBoxView::CSelectionIndexArray* aSelectionIndexArray)
	: CAknQueryDialog(ENoTone)
	{
    iSelectionIndexArray = aSelectionIndexArray;
    iEnterKeyPressed = EFalse;

    GfxTransEffect::Register(this,KGfxContextMenuControlUid);
    AKNTASHOOK_ADD( this, "CAknListQueryDialog" );
    }

EXPORT_C CAknListQueryDialog::~CAknListQueryDialog()
    {
    AKNTASHOOK_REMOVE();
    if (iMediatorObs)
        CEikDialog::SetMediatorObserver(0); // Cover UI support cannot handle dialog it self as external observer  
    
    delete iMediatorObs;
	delete iIdle;
    }

EXPORT_C CEikListBox *CAknListQueryDialog::ListBox() const 
    {
    return ListControl()->Listbox();
    }


EXPORT_C CAknListQueryControl* CAknListQueryDialog::ListControl() const
	{
	CCoeControl* controlPtr = FindControlOnAnyPageWithControlType(EAknCtListQueryControl);
	if (controlPtr)
		return STATIC_CAST(CAknListQueryControl*,controlPtr);
	return 0;
	}

EXPORT_C CAknMessageQueryControl* CAknListQueryDialog::MessageBox() const
	{
    CAknMessageQueryControl* msgCtrl = NULL;
    CAknListQueryControl* listControl = ListControl();
    if (listControl)
        {
        msgCtrl = listControl->MessageBox();
        if (msgCtrl) return msgCtrl;
        }
		
    //if not found let's try dialog (old resources)
    //this only corrects scrollbar height though
    CCoeControl* controlPtr = FindControlOnAnyPageWithControlType(EAknCtMessageQuery);
    if (controlPtr)
        return STATIC_CAST(CAknMessageQueryControl*,controlPtr);
    return 0;
	}

EXPORT_C CAknPopupHeadingPane* CAknListQueryDialog::QueryHeading() const
	{
	CAknListQueryControl* listControl = ListControl();
	if (listControl)
		return listControl->Heading();
	
	return NULL;
	}


EXPORT_C void CAknListQueryDialog::PreLayoutDynInitL()
    {
	CAknListQuerySearchControl *control1 = (CAknListQuerySearchControl*)ControlOrNull(EFindControl);
    CAknSearchField *control = NULL;
    CAknSearchField::TSearchFieldStyle flags = CAknSearchField::EPopupWindow;

    if (control1)
        {
        control = CAknSearchField::NewL( *control1, flags, 0, 40 );
        control1->iFind = control;
        }
    
    CAknDialog::PreLayoutDynInitL();

    CEikListBox* listbox = ListBox();
	if (listbox)
		{
		listbox->CreateScrollBarFrameL(ETrue, EFalse, EFalse);
		listbox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, 
                                                        CEikScrollBarFrame::EAuto);
        listbox->ScrollBarFrame()->DrawBackground( EFalse, EFalse );
		listbox->SetListBoxObserver(this);
    
		CAknListQueryControl* listControl = ListControl();
		if (listControl)
			listControl->SetLayout(&iLayout);
		}

    if (FindBox())
        {
        STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->CreateFilterL(ListBox(),FindBox());

		// The next line is needed so that drawing order of list query control and find pane becomes
		// correct. Seems that dialog page draws focused line last.
		SetLineNonFocusing(EListQueryControl);
		Line(EFindControl)->SetDrawNoWhiteBackground(ETrue);
        }        
	}

EXPORT_C void CAknListQueryDialog::SetIconArrayL(CArrayPtr<CGulIcon>* aIcons)
    {
	CEikFormattedCellListBox* listbox = STATIC_CAST(CEikFormattedCellListBox*,ListBox());
    CArrayPtr<CGulIcon>* oldicons = listbox->ItemDrawer()->FormattedCellData()->IconArray();
    
	if (oldicons)
        {
        oldicons->ResetAndDestroy();
        delete oldicons;
        }
    listbox->ItemDrawer()->FormattedCellData()->SetIconArrayL(aIcons);
    }

EXPORT_C void CAknListQueryDialog::PostLayoutDynInitL()
    {
	CEikFormattedCellListBox* listbox = STATIC_CAST(CEikFormattedCellListBox*,ListBox());
    
	// Now we'll load default icons if existing icon array does not exists.
    if (!listbox->ItemDrawer()->FormattedCellData()->IconArray())
        {
		CArrayPtr<CGulIcon>* icons = new(ELeave) CAknIconArray(10);
        CleanupStack::PushL(icons);

/* This macro leaves the "icon" on the cleanupstack as "icons" does NOT take 
ownership of them.
*/
#define __ADD_ICON_C__(NAME) {CGulIcon* icon = CGulIcon::NewLC();\
        	                 CFbsBitmap* bitmap = 0;\
                        	 CFbsBitmap* mask = 0;\
                             AknIconUtils::CreateIconL( bitmap, mask, KAvkonBitmapFile,\
							 NAME, NAME ## _mask);\
                             icon->SetBitmap(bitmap);\
                             icon->SetMask(mask);\
							 icons->AppendL(icon);\
							}

		// for every icon added by __ADD_ICON_C, add a CleanupStack::Pop at the bottom.
		__ADD_ICON_C__(EMbmAvkonQgn_prop_checkbox_on)
		__ADD_ICON_C__(EMbmAvkonQgn_prop_checkbox_off)

#undef __ADD_ICON_C__

        listbox->ItemDrawer()->FormattedCellData()->SetIconArrayL(icons);
        CleanupStack::Pop(); // icon for EMbmAvkonQgn_prop_checkbox_off
        CleanupStack::Pop(); // icon for EMbmAvkonQgn_prop_checkbox_on
        CleanupStack::Pop(); // icons array
        }
    }

EXPORT_C void CAknListQueryDialog::SetSizeAndPosition(const TSize & /*aSize*/)
    {
    AknPopupLayouts::TAknPopupLayouts layout = AknPopupLayouts::EMenuWindow;
    CAknListQueryControl *control = ListControl();
    
    switch(control->Listtype())
        {
        case EAknCtSinglePopupMenuListBox:
            layout = AknPopupLayouts::EMenuWindow;
            break;
        case EAknCtSingleGraphicPopupMenuListBox:
            layout = AknPopupLayouts::EMenuGraphicWindow;
            break;
        case EAknCtSingleGraphicHeadingPopupMenuListBox:
            layout = AknPopupLayouts::EMenuGraphicHeadingWindow;
            break;
        case EAknCtMenuDoublePopupMenuListBox:
            layout = AknPopupLayouts::EMenuDoubleWindow;
            break;
        case EAknCtDoubleLargeGraphicPopupMenuListBox:
            layout = AknPopupLayouts::EMenuDoubleLargeGraphicWindow;
            break;
        case EAknCtSingleHeadingPopupMenuListBox:
            layout = AknPopupLayouts::EMenuGraphicHeadingWindow;
            break;
        case EAknCtDouble2PopupMenuListBox:
            layout = AknPopupLayouts::EMenuDoubleLargeGraphicWindow;
            break;
        case EAknCtSingle2GraphicPopupMenuListBox:
            layout = AknPopupLayouts::EMenuWindow;
            break;
        case EAknCtDoubleGraphicPopupMenuListBox:
            layout = AknPopupLayouts::EMenuDoubleWindow;
            break;
        
        default:
            __ASSERT_DEBUG(0,Panic(EAknPanicListBoxNotSupportedByListQuery));
        }

	// A linked list for HandleSizeChanged().
	TAknPopupLayoutsNode list = { 0, EListNode, control->Listbox() };
	TAknPopupLayoutsNode heading = { &list, EHeadingNode, QueryHeading() };
	TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, this };
	TAknPopupLayoutsNode messageBox = { &windowOwning, EMessageBoxNode, MessageBox() };
	TAknPopupLayoutsNode *listBegin = &messageBox;		

	if (FindBox())
        {
		layout = AknPopupLayouts::TAknPopupLayouts(EAknPopupLayoutsFind + layout);
		AknPopupLayouts::HandleSizeChanged( iLayout, layout, listBegin);
        // set layout for fixed find box in popup window - this makes highlights working
        STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->SetParentControl(this);
        TRect parentrect = Rect();
        if ( AknLayoutUtils::PenEnabled() )
            {
            TRect screen;
            TAknLayoutRect cbaRect;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );
            cbaRect.LayoutRect( screen, 
                            AknLayoutScalable_Avkon::popup_sk_window( 0  ).LayoutLine() );
            TSize size( parentrect.Size() );
            // subtract softkey height
            size.iHeight -= cbaRect.Rect().Height();
            parentrect.SetSize(size);
            }
        
        // popup_find_window overlaps listbox, but this doesn't matter because findbox
        // doesn't draw background
        AknLayoutUtils::LayoutControl(FindBox(), parentrect, AknLayoutScalable_Avkon::find_popup_pane_cp2(0).LayoutLine());
	    Line(EFindControl)->SetRect(FindBox()->Rect());
	    } 
	
    AknPopupLayouts::HandleSizeChanged( iLayout, layout, listBegin);	
		
    CFormattedCellListBoxData *boxData =
        ((CEikFormattedCellListBox*)ListBox())->ItemDrawer()->FormattedCellData();

    TRect windowRect = Rect();

    TAknLayoutRect topLeft;
    topLeft.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_2());

    TAknLayoutRect bottomRight;
    bottomRight.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_5());

    TRect outerRect = TRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
    TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);

    boxData->SetSkinPopupFrame(&KAknsIIDQsnFrPopup,&KAknsIIDQsnFrPopupCenter);
    boxData->SetSkinPopupFramePosition(outerRect,innerRect);

    }
    
EXPORT_C void CAknListQueryDialog::HandleListBoxEventL(CEikListBox* aListBox, 
                                                       TListBoxEvent aEventType)
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        switch(aEventType)
            {
            case EEventEnterKeyPressed:
                {
                iEnterKeyPressed = ETrue;
                break;
                }
            case EEventPenDownOnItem:
                {
                iDragActioned = 0;
                }
                break;
            case EEventItemDraggingActioned:
            case EEventPanningStarted:
            case EEventFlickStarted:
                {
                iDragActioned = 1;
                }
                break;
            case EEventItemClicked:
            case EEventItemSingleClicked:
                {
                if( !iIdle && !aListBox->IsMultiselection() && !iDragActioned)
                    {                
                    iIdle = CIdle::NewL(CActive::EPriorityIdle);                
                    if (iIdle)
                        {                    
                        iIdle->Start(TCallBack(ClosePopupAcceptingChanges, this));
                        }
                    }  
                }
                break;
            default:
                {
                break;
                }
            }
        }
    else
        {
        switch(aEventType)
    		{
    		case EEventEnterKeyPressed:
    			{
    			iEnterKeyPressed = ETrue;
    			break;
    			}
    		case EEventItemDoubleClicked:
    		default:
    			{
    			break;
    			}
    		}
        }
    }


// -----------------------------------------------------------------------------
// If a parent to the supplied control has its Gc set, this function will find 
// it and return it.
// -----------------------------------------------------------------------------
//
LOCAL_C CWindowGc* FindRedirGc(const CCoeControl* aControl)
	{
	const CCoeControl* parent = aControl;
	CWindowGc* gc = NULL;
	while(parent)
		{
		if(NULL != (gc = parent->GetGc()))
			{
			return gc;
			}
		parent = parent->Parent();
		}
	return NULL;
	}

// -----------------------------------------------------------------------------
// CleanupItem to enable redraws again on the listbox view.
// -----------------------------------------------------------------------------
//
LOCAL_C void CleanupDisableRedraw( TAny *aView )
    {
    ((CListBoxView*)aView)->SetDisableRedraw(EFalse);
    }

EXPORT_C TKeyResponse CAknListQueryDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                                          TEventCode aType)
    {
    if (aType==EEventKey && aKeyEvent.iCode == EKeyEscape)
        {
        CloseState();
        return EKeyWasConsumed;
        }
    
	TBool needRefresh = EFalse;
    TKeyResponse res = AknFind::HandleFindOfferKeyEventL(aKeyEvent, aType, this, ListBox(), FindBox(), EFalse, needRefresh);
    if (needRefresh && FindBox())
    	{
	    DrawNow();
	    }
    if ( res == EKeyWasConsumed ) 
		return res;

	CEikListBox* listbox = ListBox();
	
    if (listbox)
        {
		TInt redirstate = 0;
		TBool redrawdisabled = EFalse;
		CWindowGc* redirgc = NULL;
	    RProperty::Get(KPSUidAvkonDomain, KAknTfxServerRedirectionStatus,redirstate);
	    if (redirstate & ETfxScreenRedirected)
	        {
	        //If screen is redirected
		    redirgc = FindRedirGc(this);
		    if(redirgc) 
		    	{
		    	//And this dialog has a redirgc, we assume its in transition
		    	if(EFalse == listbox->View()->RedrawDisabled())
		    		{
		    		//Then we turn of redraws, since listbox view, when navigating, handles its gc in 
		    		// a way that is incompatible with the redirection gc.
					listbox->View()->SetDisableRedraw(ETrue);
					CleanupStack::PushL(TCleanupItem(CleanupDisableRedraw, listbox->View()));
					redrawdisabled = ETrue;
		    		}
		    	}
	        }

        TInt currentSelection = listbox->CurrentItemIndex();
        if( currentSelection == KErrNotFound )
            {
            MakeLeftSoftkeyVisible(EFalse);
            }
        else
            {
            MakeLeftSoftkeyVisible(ETrue);
            }
            
        TKeyResponse response = listbox->OfferKeyEventL( aKeyEvent, aType);
        if (currentSelection != listbox->CurrentItemIndex() && iMediatorObs)
            {
            iMediatorObs->UpdateL(listbox->CurrentItemIndex());
            }

        if (iEnterKeyPressed)
            TryExitL(EAknSoftkeyOk);
        
	if(redrawdisabled) 
		{
		CleanupStack::PopAndDestroy(); //enables redraw again
		}
        return response;
           
        }
        
    return CAknQueryDialog::OfferKeyEventL(aKeyEvent,aType);
    }



EXPORT_C void CAknListQueryDialog::SetItemTextArray(MDesCArray* aItemTextArray)
    {
    STATIC_CAST(CTextListBoxModel*,ListBox()->Model())->SetItemTextArray(aItemTextArray);
    }

EXPORT_C void CAknListQueryDialog::SetOwnershipType(TListBoxModelItemArrayOwnership aOwnershipType)
    {
    STATIC_CAST(CTextListBoxModel*,ListBox()->Model())->SetOwnershipType(aOwnershipType);
    }

EXPORT_C TBool CAknListQueryDialog::OkToExitL(TInt aButtonId)
    {   
    CEikListBox* listbox = ListBox();

    if(aButtonId == GetLeftCBAShortKeyPress() || aButtonId == EEikBidOk)
        {
        if(iIndex)
            {
            *iIndex = listbox->CurrentItemIndex();
            if (FindBox())
        	    {
	            if (*iIndex != -1)
	            *iIndex = STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->FilteredItemIndex(*iIndex);
	            }
            }
        else if(iSelectionIndexArray)
            {
            const CArrayFix<TInt> *array = ListBox()->SelectionIndexes();

        	if (FindBox())
	            {
	            STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->UpdateSelectionIndexesL();
	            array = STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->SelectionIndexes();
	            }
	        TInt numberOfItems(array->Count());
	        iSelectionIndexArray->Reset();
	        for(TInt i(0); i<numberOfItems; i++)
	            iSelectionIndexArray->AppendL(array->At(i));
            }
        return ETrue;
        }
    else if(aButtonId == GetRightCBAShortKeyPress())
        return ETrue;
    return EFalse;
    }

EXPORT_C TInt CAknListQueryDialog::BorderStyle()
    {
#ifndef RD_NO_DIALOG_BORDERS
    return QueryHeading() ? AknBorderId::EAknBorderPopupsWithHeading : AknBorderId::EAknBorderPopups;
#else
    return TGulBorder::ENone;
#endif
    }

EXPORT_C void CAknListQueryDialog::CloseState()
    {
    TRAP_IGNORE(TryExitL(EAknSoftkeyCancel));
    }

EXPORT_C void CAknListQueryDialog::ActivateL()
    {
    TBool notShowingPopup = ListBox()->Model()->NumberOfItems() == 0;
    if (notShowingPopup)
        {
        // We do not show if there's no list items.
        MakeVisible(EFalse);

		// Stops transition
		GfxTransEffect::Deregister(this);

    	if (QueryHeading() && QueryHeading()->Prompt())
            {
            TPtr headTitle= QueryHeading()->PromptText();
  	        iAvkonEnv->ExecuteEmptyPopupListL(ListBox()->View()->EmptyListText(), &headTitle); // show empty popup.
            }
        else 
            {
            const TDesC *title = 0; // use default if not found
  	        iAvkonEnv->ExecuteEmptyPopupListL(ListBox()->View()->EmptyListText(), title); // show empty popup.
            }

        delete iIdle;
        iIdle = NULL;
        iIdle = CIdle::NewL(-20);
        if (iIdle)
            iIdle->Start(TCallBack(ClosePopup, this));
        }
    else
        {
        CAknQueryDialog::ActivateL();
        }
    }

TInt CAknListQueryDialog::ClosePopup(TAny *aObj)
    {
    CAknListQueryDialog *popup = (CAknListQueryDialog*)aObj;
    delete popup->iIdle;
    popup->iIdle = 0;
    popup->CloseState();
    return EFalse;
    }
    
EXPORT_C void CAknListQueryDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    {
    // list query is dismissed if tapped outside
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
        {
        if( !Rect().Contains( aPointerEvent.iPosition ) )
            {
            if ( !iIdle )
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                if ( feedback )
                    {
                    feedback->InstantFeedback( ETouchFeedbackPopUp );
                    }
                iIdle = CIdle::NewL(CActive::EPriorityIdle);
                iIdle->Start(TCallBack(ClosePopup, this));
                return;
                }
            }
        
        TInt index;
        if ( ListBox()->View()->XYPosToItemIndex( aPointerEvent.iPosition, index ) )
            {
            ListBox()->View()->ItemDrawer()->SetFlags( 
                        CListItemDrawer::EPressedDownState );
            }
        }
    
    CAknQueryDialog::HandlePointerEventL( aPointerEvent );
    }    

// ---------------------------------------------------------
// CAknListQueryDialog::ClosePopupAcceptingChanges
// Callback function for CIdle to close and accept changes
// ---------------------------------------------------------
//

TInt CAknListQueryDialog::ClosePopupAcceptingChanges(TAny *aObj)
    {    
    if ( AknLayoutUtils::PenEnabled() ) 
        {
        CAknListQueryDialog *popup = (CAknListQueryDialog*)aObj;
        delete popup->iIdle;
        popup->iIdle = NULL;
        TRAP_IGNORE( popup->TryExitL( EAknSoftkeyOk ) );
        return EFalse;
        }
    else
        {
        return EFalse;
        }
    }


EXPORT_C void* CAknListQueryDialog::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknListQueryDialog::CEikDialog_Reserved_1()
	{
	}

EXPORT_C void CAknListQueryDialog::CEikDialog_Reserved_2()
	{
	}

EXPORT_C void CAknListQueryDialog::CAknDialog_Reserved()
	{
	}

EXPORT_C void CAknListQueryDialog::CAknQueryDialog_Reserved()
	{
	}

EXPORT_C CAknSearchField *CAknListQueryDialog::FindBox() const
    {
    CAknListQuerySearchControl *control = (CAknListQuerySearchControl*)ControlOrNull(EFindControl);
    if (control) { return control->iFind; }
    return NULL;
    }

EXPORT_C void CAknListQueryDialog::SetTone(TInt aTone)
	{
	iTone = (TTone)aTone;
	}

EXPORT_C void CAknListQueryDialog::HandleResourceChange(TInt aType)
	{
	if (aType==KEikDynamicLayoutVariantSwitch)
	    {
	    if (MessageBox())
	        {
	        MessageBox()->SizeChanged();	    
	        }		
	    }	    
	CAknQueryDialog::HandleResourceChange(aType);	
	}
    
EXPORT_C void CAknListQueryDialog::PublishDialogL(TInt aDialogIndex, TUid aCatUid, CArrayFixFlat<TInt>* aItemIds)
    {
    CEikDialog::PublishDialogL(aDialogIndex, aCatUid);
    delete iMediatorObs;
    iMediatorObs = 0;

    if (aItemIds)
        {
        CAknMediatorFacade* coverData = AknMediatorFacade(this);
        if (coverData) // cover functionality enabled
            {
            // publish dialog resets the buffer -> Just append data
            TInt count = aItemIds->Count();
            coverData->BufStream().WriteInt32L(EAknListQueryItemsInfo);            
            coverData->BufStream().WriteInt32L(count);
            for(TInt i = 0;i < count; i++)
                {
                coverData->BufStream().WriteInt32L(aItemIds->At(i));
                }
            coverData->BufStream().CommitL(); // make sure that this data was added ok
            iMediatorObs = new (ELeave) CAknListQueryMediatorObserver(aItemIds, *this); // take ownership after other leaving 
            CEikDialog::SetMediatorObserver(iMediatorObs);                              // methods so we don't cause 
            }                                                                           // double deletion in case of leave
        else
            {
            delete aItemIds; // we own these currently, as we don't use info, delete directly   
            }
        }
    }	
	
EXPORT_C void CAknListQueryDialog::SetMediatorObserver(MAknDialogMediatorObserver* aObserver)
    {
    if (iMediatorObs) // built in update channel is in use
        {
        iMediatorObs->SetExternalObserver(aObserver);
        }
    else 
        {
        CEikDialog::SetMediatorObserver(aObserver);
        }
    }

// End of File

