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
*  Support for transparent camera setting pages
*
*
*/


#include "AknTransparentCameraSettingPage.h"

// For icon support
#include <barsread.h>
#include <gulicon.h>
#include <AknIconArray.h>

// lists
#include <aknlists.h>

#include <AknTasHook.h>
// Used for setting  1 in the radio button 
_LIT(KOneSlashT, "1\t");

enum TAknTransparentCameraSettingPagePanicCodes
    {
    EAknPanicTransparentCameraSettingPageIndexOutOfRange
    };

GLDEF_C void Panic(TAknTransparentCameraSettingPagePanicCodes aPanic)
    {
    _LIT(KPanicCat,"AknTransparentCameraSettingPage");
    User::Panic(KPanicCat, aPanic);
    }

NONSHARABLE_CLASS(CAknTransparentCameraSettingPageExtension) : public CBase
    {
    friend class CAknTransparentCameraSettingPage;

public:
    static CAknTransparentCameraSettingPageExtension* NewL(
        CCoeControl& aOwner );
    ~CAknTransparentCameraSettingPageExtension();

private:
    CAknTransparentCameraSettingPageExtension( CCoeControl& aOwner );
    void ConstructL();
public: //data
    
    CFbsBitmap* iBackground;
    // Background bitmap's top left corner.
    TPoint iBitmapPosition;
    // Background bitmap will be drawn inside this rect (ie. it will be cropped 
    // if the rect is smaller than the actual bitmap)
    TRect iBitmapClipRect;
    TBool iDrawFullBackground;
    TBool iDrawBackgroundBitmap;
    TBool iFullScreenMode;

    TBool iReplaceNaviPane; //replace navi pane with empty contents?
    TBool iReturn; //user select okay or cancel?
    TInt iUpdateMode;
    CActiveSchedulerWait iWait; //owned

    /**
     * Extension flags definition.
     */
    enum TFlags
        {
        ESingleClickEnabled
        };

    /**
     * Extension flags.
     */
    TBitFlags iFlags;
    };

CAknTransparentCameraSettingPageExtension* CAknTransparentCameraSettingPageExtension::NewL(
    CCoeControl& aOwner )
    {
    CAknTransparentCameraSettingPageExtension* self =
        new (ELeave) CAknTransparentCameraSettingPageExtension( aOwner );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CAknTransparentCameraSettingPageExtension::~CAknTransparentCameraSettingPageExtension()
    {
    if(iWait.IsStarted())
        {
        CAknEnv::StopSchedulerWaitWithBusyMessage(iWait);
        }
    }

CAknTransparentCameraSettingPageExtension::CAknTransparentCameraSettingPageExtension(
    CCoeControl& aOwner )
    : iDrawFullBackground(ETrue), iDrawBackgroundBitmap(ETrue),
      iReplaceNaviPane(ETrue),
      iUpdateMode(CAknSettingPage::EUpdateWhenAccepted)
    {
    if ( static_cast<CAknAppUi*>(
            aOwner.ControlEnv()->AppUi() )->IsSingleClickCompatible() )
        {
        iFlags.Set( ESingleClickEnabled );
        }
    }

void CAknTransparentCameraSettingPageExtension::ConstructL()
    {
    }

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


EXPORT_C CAknTransparentCameraSettingPage::CAknTransparentCameraSettingPage( TInt aResourceId, TInt& aCurrentSelectionItem, const MDesCArray* aItemArray):
    CAknListBoxSettingPage(aResourceId), iOldSelectionIndex(aCurrentSelectionItem), iCurrentSelectionIndex(aCurrentSelectionItem), iItemArray(aItemArray)
    {
    AKNTASHOOK_ADD( this, "CAknTransparentCameraSettingPage" );
    }


EXPORT_C CAknTransparentCameraSettingPage::CAknTransparentCameraSettingPage(    
            const TDesC* aSettingText, 
            TInt aSettingNumber, 
            TInt aControlType,
            TInt aEditorResourceId, 
            TInt aSettingPageResourceId, 
            TInt& aCurrentSelectionIndex, 
            const MDesCArray* aItemArray )
            :   CAknListBoxSettingPage( 
                aSettingText, 
                aSettingNumber, 
                aControlType, 
                aEditorResourceId, 
                aSettingPageResourceId ), 
                iOldSelectionIndex(aCurrentSelectionIndex), 
                iCurrentSelectionIndex(aCurrentSelectionIndex), 
                iItemArray(aItemArray)
    {
    AKNTASHOOK_ADD( this, "CAknTransparentCameraSettingPage" );
    }


/**
 * Destructor
 *
 */
EXPORT_C CAknTransparentCameraSettingPage::~CAknTransparentCameraSettingPage()
    {   
    AKNTASHOOK_REMOVE();
    delete(iInternalItemArray);
    if (iExtension)
        delete iExtension;
    }

EXPORT_C void CAknTransparentCameraSettingPage::ConstructL()
    {
    BaseConstructL( KAknSettingPageNoEmbeddedSoftKeys );
    
    SetDrawBackground(EFalse);  // Enable transparent drawing
    
    GenerateInternalArrayAndGiveToListBoxL();
    
    iExtension = CAknTransparentCameraSettingPageExtension::NewL( *this );

    // This updates the CBA 
    CheckAndSetDataValidity();
    UpdateCbaL();

    // Only a reference to the CBase object; not owned
    CAknSetStyleListBox* listBox = ListBoxControl();

    CreateBitmapArrayAndGiveToListBoxL();
        
    listBox->ItemDrawer()->FormattedCellData()->SetDrawBackground( EFalse );
    listBox->ItemDrawer()->FormattedCellData()->ToggleDropShadows( ETrue );
    
    // Range should be within the valid indices, or -1:
    // So valid range is >= -1 and also < Count.
    __ASSERT_ALWAYS( iCurrentSelectionIndex >= -1, Panic(   EAknPanicTransparentCameraSettingPageIndexOutOfRange) );
    __ASSERT_ALWAYS( iCurrentSelectionIndex < iInternalItemArray->Count(), Panic(   EAknPanicTransparentCameraSettingPageIndexOutOfRange) );

    listBox->View()->CalcBottomItemIndex();
    // Set initial highlight to the top element
    if (FocusToFirstItem())
        {// Set initial highlight to the top element
        if ( iInternalItemArray->Count() > 0 )
            listBox->SetCurrentItemIndex( 0 );
        }
    if (FocusToSelectedItem())
        {// Set initial highlight to the current element.
        if ( iInternalItemArray->Count() > 0 )
            {
            if (iCurrentSelectionIndex != -1)
                listBox->SetCurrentItemIndex( iCurrentSelectionIndex );
            else
                listBox->SetCurrentItemIndex( 0 ); // Set at the top if selected is -1
            }
        }

    listBox->SetListBoxObserver(this);

    // Set the current "pushed in" indication
    if ( iCurrentSelectionIndex != -1 )
        listBox->View()->SelectItemL( iCurrentSelectionIndex );

    // Set the scroller indication off
    listBox->CreateScrollBarFrameL(ETrue);
    listBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,CEikScrollBarFrame::EOff);

    // Need to do this to set up the scroll bar model
    listBox->UpdateScrollBarsL();
    
    if(!IsBackgroundDrawingEnabled())
            listBox->ScrollBarFrame()->DrawBackground(EFalse, EFalse);
    

    // Force a size changed
    SizeChanged();

    // Construct an appropriate control context for the contained editor areas.
    // Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrSetOpt, KAknsIIDQsnFrSetOptCenter );
}

//---------------------------------------------------------------------------------------------
// Note: please call CAknSettingPage::ConstructL() before call this function!
//---------------------------------------------------------------------------------------------
//
EXPORT_C TBool CAknTransparentCameraSettingPage::ExecuteLD( 
        enum CAknSettingPage::TAknSettingPageUpdateMode aMode, 
        TBool aReplaceNaviPane )
    {
    iExtension->iReplaceNaviPane = aReplaceNaviPane;
    if(aReplaceNaviPane)
        {
        return CAknSettingPage::ExecuteLD( aMode );
        }

    CleanupStack::PushL( this ); // Matching Pop is in AttemptExitL
    iExtension->iUpdateMode = aMode;

    DynamicInitL();
    ActivateL();
    DrawNow();

    EditorControl()->SetObserver( this );
    iEikonEnv->EikAppUi()->AddToStackL(this,ECoeStackPriorityDialog);

    if ( PostDisplayCheckL() )
        {
        if (!iExtension->iWait.IsStarted())
            {
            iExtension->iWait.Start();
            }
        }
    else
        AttemptExitL(EFalse);
    
    iEikonEnv->EikAppUi()->RemoveFromStack(this);
    CleanupStack::Pop(); // this

    TBool res=iExtension->iReturn;
    delete (this);

    return res;
    }

//---------------------------------------------------------------------------------------------
// Set the flags in extension to indicate user accept settings or cancel it.
//---------------------------------------------------------------------------------------------
//
void CAknTransparentCameraSettingPage::AttemptExitL(TBool aAccept)
    {
    if ( OkToExitL( aAccept ) )
        {
        DismissL( aAccept );
        iExtension->iReturn = aAccept;

        if ( iExtension->iWait.IsStarted() )
            {
            CAknEnv::StopSchedulerWaitWithBusyMessage( iExtension->iWait );
            }
        else
            {
            StopActiveScheduler();
            }
        }
    }

//---------------------------------------------------------------------------------------------
// Update settings according to update mode
//---------------------------------------------------------------------------------------------
//
EXPORT_C void CAknTransparentCameraSettingPage::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent aEventType)
    {
    if ( aEventType == EEventStateChanged && iExtension &&
         iExtension->iUpdateMode == EUpdateWhenChanged )
        {
        UpdateSettingL();
        }
    }

//---------------------------------------------------------------------------------------------
// Process user command by modifying flags in extension
//---------------------------------------------------------------------------------------------
//
EXPORT_C void CAknTransparentCameraSettingPage::ProcessCommandL(TInt aCommandId)
    {
    if(iExtension->iReplaceNaviPane)
        {
        CAknSettingPage::ProcessCommandL(aCommandId);
        return;
        }

    if(!IsEditable() && !(aCommandId == EAknSoftkeyBack || aCommandId == EAknSoftkeyCancel))
        {
        return;
        }
    
    HideMenu();

    // Respond to softkey events
    switch (aCommandId)
        {
        case EAknSoftkeyOk:
        case EAknSoftkeySelect:  
        case EAknSoftkeyDone:
            SelectCurrentItemL(); // has non-trivial implemenations in listbox type 
                                        // controls to put the selection on the current item
            AttemptExitL(ETrue);
            break;
        case EAknSoftkeyBack:
        case EAknSoftkeyCancel:
            AttemptExitL(EFalse);
            break;
        case EAknSoftkeyOptions:
            DisplayMenuL();
            break;
        default:
            break;
        }
    }

EXPORT_C void CAknTransparentCameraSettingPage::HandleListBoxEventL(CEikListBox* /*aListBox*/, 
        MEikListBoxObserver::TListBoxEvent aEventType)
    {
    switch ( aEventType )
        {
        case MEikListBoxObserver::EEventItemSingleClicked:
        case MEikListBoxObserver::EEventEnterKeyPressed:
        case MEikListBoxObserver::EEventItemDoubleClicked:
        case MEikListBoxObserver::EEventItemActioned:
            {
            SelectCurrentItemL();
            AttemptExitL( ETrue );
            break;
            }
            
        case MEikListBoxObserver::EEventFlickStopped:   // fallthrough
        case MEikListBoxObserver::EEventPanningStopped:
            {
            // The current item index (highlighted item) of the listbox control
            // has been changed when starting the dragging / flicking, so
            // it must be reverted back to represent the same item as
            // the current selection in the setting page.
            // Only in single click enabled applications.
            if ( iExtension &&
                 iExtension->iFlags.IsSet(
                         CAknTransparentCameraSettingPageExtension::ESingleClickEnabled ) )
                {
                ListBoxControl()->View()->SetCurrentItemIndex(
                    iCurrentSelectionIndex );
                }
            break;
            }

        default:
            break;
        }
    }


EXPORT_C void CAknTransparentCameraSettingPage::UpdateSettingL()
    {
    }

EXPORT_C CAknSetStyleListBox* CAknTransparentCameraSettingPage::ListBoxControl() const
    {
    return STATIC_CAST( CAknSetStyleListBox*, EditorControl());
    }

EXPORT_C void CAknTransparentCameraSettingPage::DynamicInitL()
    {
    }

void CAknTransparentCameraSettingPage::SetRadioButtonSelectionL( TInt aPushed )
    {
    // reference listbox's view; not owned here
    CListBoxView* view = ListBoxControl()->View();
    view->SelectItemL( aPushed );
    if ( aPushed != iOldSelectionIndex )
        {
        view->DeselectItem( iOldSelectionIndex );
        iOldSelectionIndex = aPushed;
        }
    } 

EXPORT_C void CAknTransparentCameraSettingPage::SelectCurrentItemL()
    {
    iCurrentSelectionIndex = ListBoxControl()->CurrentItemIndex();
    SetRadioButtonSelectionL( iCurrentSelectionIndex );
    UpdateSettingL();
    if( iSettingPageObserver )
        iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);
    } 


EXPORT_C void CAknTransparentCameraSettingPage::SetItemArrayAndSelectionL( const MDesCArray* aItemArray, TInt aPushed )
    {
    SetRadioButtonSelectionL(0);  // Put the selection into a known state
    iItemArray = aItemArray;
    GenerateInternalArrayAndGiveToListBoxL();

    // This updates the CBA 
    CheckAndSetDataValidity();
    UpdateCbaL();
    SizeChanged();
    SetRadioButtonSelectionL(aPushed);

    DrawDeferred();
    }

void CAknTransparentCameraSettingPage::GenerateInternalArrayAndGiveToListBoxL()
    {

    delete iInternalItemArray;
    iInternalItemArray = 0;
    
    // Make a new owned text array from the input one with the "Pushed in" icon index:
    iInternalItemArray = new(ELeave)CDesCArrayFlat(1);
    TInt nItems = iItemArray->MdcaCount();

    for (TInt ii=0; ii<nItems; ii++)
        {
        // Fill up the control-owned space for the modified buffers:
        TInt newLen = (iItemArray->MdcaPoint(ii)).Length() + KOneSlashT().Length();
        HBufC* newText = HBufC::NewMaxLC( newLen ); 
        TPtr newTPtr = newText->Des();
        newTPtr.Copy( KOneSlashT );
        newTPtr.Append( iItemArray->MdcaPoint(ii) );
        // A copy of the new buffer goes to the internal itemarray:
        iInternalItemArray->AppendL(newTPtr); 
        CleanupStack::PopAndDestroy(); // newText
        }

    // Only a reference to the CBase object; not owned
    CAknSetStyleListBox* listBox = ListBoxControl();

    // Set the text data
    CTextListBoxModel* model=listBox->Model();
    model->SetItemTextArray(iInternalItemArray);
    model->SetOwnershipType(ELbmDoesNotOwnItemArray);

    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknTransparentCameraSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {}
#else
EXPORT_C void CAknTransparentCameraSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CAknSettingPage::WriteInternalStateL(aWriteStream);
    }
#endif

/**
* Handles the size change events.
*/
EXPORT_C void CAknTransparentCameraSettingPage::SizeChanged()
    {
    CAknListBoxSettingPage::SizeChanged();    
    }      

/**
* Draws the setting page on top of the camera feed.
*/
EXPORT_C void CAknTransparentCameraSettingPage::Draw(const TRect &/*aRect*/) const
    {
    
    // The draw is called only when setting page is drawn the first time
    // After first time, the drawing is only made on relevant parts in 
    // ChangeBackground-method
    
    TRect parentRect = Rect();  // this will be used a lot in this routine

	CWindowGc& gc = SystemGc();
        
    MAknsControlContext* ccBg = AknsDrawUtils::ControlContext(this);
	MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    // Draw black background if full screen in use
	if (iExtension->iFullScreenMode)
	    {
        gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
        gc.SetPenStyle(CGraphicsContext::ENullPen);
        gc.SetBrushColor(KRgbBlack);
        gc.DrawRect(parentRect); // in fullscreen control size is EScreen
        }
	else // draw skinbackground
        {
	    TRect mainPaneRect;
	   	AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, mainPaneRect);
        TRect bgRect(TPoint(0, 0), mainPaneRect.Size());
        
        if (iExtension->iDrawBackgroundBitmap && ccBg != NULL && skin != NULL)
            {
            AknsDrawUtils::DrawBackground (skin, 
                                           ccBg, 
                                           NULL, 
                                           gc,
                                           parentRect.iTl,
                                           parentRect,                                       
                                           KAknsDrawParamDefault);
            }
        else
            {
            gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
            gc.SetPenStyle(CGraphicsContext::ENullPen);
            gc.SetBrushColor(KRgbWhite);
            gc.DrawRect (bgRect);
            }
        }
        
    // draw viewfinder if available
	if(iExtension->iBackground)
        {         
        gc.SetClippingRect(iExtension->iBitmapClipRect);
        
        gc.BitBlt(iExtension->iBitmapPosition, iExtension->iBackground);
        gc.CancelClippingRect();
        }  
    }

void CAknTransparentCameraSettingPage::CreateBitmapArrayAndGiveToListBoxL()
    {
    // This method is more or less a verbatim copy of
    // CAknPopupField::InitialiseRadioButtonBitmapsL

    CAknSetStyleListBox* listBox = ListBoxControl();
    
    // In case CAknPopupSettingList has already created the icons
    if ( listBox->ItemDrawer()->FormattedCellData()->IconArray() )
        {
        listBox->ItemDrawer()->FormattedCellData()->IconArray()->ResetAndDestroy();
        delete (listBox->ItemDrawer()->FormattedCellData()->IconArray());
        }

    TResourceReader reader;
    
    iCoeEnv->CreateResourceReaderLC(reader, R_AVKON_SETTING_PAGE_RADIOBUTTON_ICONS);

    reader.ReadInt16(); //not needed, simple or complex

    HBufC* bmpFile = reader.ReadHBufCL();
    TInt count = reader.ReadInt16(); // count
    
    if(count<2)
        User::Leave(KErrCorrupt);
    
    TInt32 bmpSelected = reader.ReadInt32();
    TInt32 bmpSelectedM = reader.ReadInt32();
    TInt32 bmp = reader.ReadInt32();
    TInt32 bmpM = reader.ReadInt32();
    CleanupStack::PopAndDestroy(); // reader

    if (bmpFile == NULL)
        User::Leave(KErrCorrupt);
    
    CleanupStack::PushL(bmpFile);

    CArrayPtr<CGulIcon>* icons = new(ELeave) CAknIconArray(4);
    // put on the cleanup stack until ownership is transferred
    CleanupStack::PushL( icons );

    // create normally colored icons
    CreateIconAndAddToArrayL( icons,
                              KAknsIIDQgnIndiRadiobuttOn,
                              EAknsCIQsnIconColorsCG14,
                              *bmpFile,
                              bmpSelected,
                              bmpSelectedM );

    CreateIconAndAddToArrayL( icons,
                              KAknsIIDQgnIndiRadiobuttOff,
                              EAknsCIQsnIconColorsCG14,
                              *bmpFile,
                              bmp,
                              bmpM );

    // create highlight colored icons
    CreateIconAndAddToArrayL( icons,
                              KAknsIIDQgnIndiRadiobuttOn,
                              EAknsCIQsnIconColorsCG18,
                              *bmpFile,
                              bmpSelected,
                              bmpSelectedM );

    CreateIconAndAddToArrayL( icons,
                              KAknsIIDQgnIndiRadiobuttOff,
                              EAknsCIQsnIconColorsCG18,
                              *bmpFile,
                              bmp,
                              bmpM );


    __ASSERT_DEBUG(listBox != NULL, Panic(EAknPanicRadioButtonSettingPageListDoesntExist));
    listBox->ItemDrawer()->FormattedCellData()->SetIconArrayL( icons ); // ownership transferred
    listBox->ItemDrawer()->FormattedCellData()->UseHighlightIconSwapping( ETrue );
    CleanupStack::Pop(); // icons - ownership now transferred; do not destroy
    CleanupStack::PopAndDestroy(); // bmpfile
    }
/**
 *  Reserved method derived from CCoeControl
 */
EXPORT_C void CAknTransparentCameraSettingPage::Reserved_2()
    {
    }

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknTransparentCameraSettingPage::CAknSettingPage_Reserved_1()
    {
    }
EXPORT_C void CAknTransparentCameraSettingPage::CAknSettingPage_Reserved_2()
    {
    }
/**
* CAknListBoxSettingPage-derived reserved methods
*/
EXPORT_C void CAknTransparentCameraSettingPage::CAknListBoxSettingPage_Reserved_1()
    {
    }
    
EXPORT_C void CAknTransparentCameraSettingPage::ChangeBackground(CFbsBitmap* aBitmap)
    {
    iExtension->iBackground = aBitmap;    
    
    if (iExtension->iBackground)
        {
        DrawNow();
        }       
    }

EXPORT_C void CAknTransparentCameraSettingPage::SetBitmapPositionAndClipRect(
    const TPoint aPoint, const TRect aRect)
    {
    SetBitmapPositionAndClipRect(aPoint, aRect, EFalse);
    }

EXPORT_C void CAknTransparentCameraSettingPage::SetBitmapPositionAndClipRect(
    const TPoint aPoint, const TRect aRect, const TBool aFullScreenUsed)
    {
    iExtension->iBitmapPosition = aPoint;
    iExtension->iBitmapClipRect = aRect;
    iExtension->iFullScreenMode = aFullScreenUsed;


    // cannot redraw here because the skin context is not updated
    if(aFullScreenUsed)
        {
        TRect newRect;
        iExtension->iDrawBackgroundBitmap = EFalse;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EScreen, newRect);
        SetRect(newRect);
        }
    else
        {
        iExtension->iDrawBackgroundBitmap = ETrue;
        }
    }

EXPORT_C void CAknTransparentCameraSettingPage::HandleResourceChange(TInt aType)
    {
    if( aType == KAknsMessageSkinChange )
    	{
    	TRAP_IGNORE( CreateBitmapArrayAndGiveToListBoxL() );    	
    	}
    
    CAknListBoxSettingPage::HandleResourceChange(aType);
    }

EXPORT_C TKeyResponse CAknTransparentCameraSettingPage::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType) 
    {

	// Only handle other key events if we're focused
	TKeyResponse response = CAknSettingPage::OfferKeyEventL(aKeyEvent, aType);

	if (IsFocused())
		{
		if (EditorControl())
			{
			// Abstraction of key events: Escape is handled like Cancel 
			// OK is handled like select.
			if ( aType == EEventKey && response == EKeyWasConsumed)
			    if ( aKeyEvent.iScanCode == EStdKeyUpArrow ||
                     aKeyEvent.iScanCode == EStdKeyDownArrow )
			        ChangeBackground(iExtension->iBackground);
			}
		}
    
	return response;	// Keys can fall through to menus

    }

// End of File
