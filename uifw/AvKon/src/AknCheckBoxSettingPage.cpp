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
*     Support for CheckBoxes in Popped up setting pages
*
*/


#include "akncheckboxsettingpage.h"

// For icon support
#include <gulicon.h>
#include <barsread.h>

// For icon array support
#include <AknIconArray.h>

// lists
#include <aknlists.h>

#include <AknTasHook.h>
// Used for setting 0 and 1 in the radio button
    _LIT(KOneSlashT, "1\t");

// Selectable Item Array

EXPORT_C CSelectableItem::CSelectableItem( TDesC& aItem, TBool aSelected ) :
    iDesC(aItem), iSelected( aSelected )
    {
    }


EXPORT_C void CSelectableItem::ConstructL()
    {
    iItem = iDesC.AllocL();
    }

CSelectableItem::~CSelectableItem()
    {
    delete ( iItem );
    }

EXPORT_C void CSelectableItem::SetSelectionStatus( TBool aSelected )
    {
    iSelected = aSelected;
    }

EXPORT_C TBool CSelectableItem::SelectionStatus()
    {
    return iSelected;
    }

EXPORT_C TPtrC CSelectableItem::ItemText()
    {
    return (TPtrC)(*iItem);
    }


EXPORT_C CSelectionItemList::CSelectionItemList(TInt aGranularity) : CArrayPtrFlat<CSelectableItem>( aGranularity )
    {
    }


EXPORT_C TInt CSelectionItemList::MdcaCount() const
    {
    return Count();
    }

EXPORT_C TPtrC CSelectionItemList::MdcaPoint(TInt anIndex) const
    {
    return ( (TPtrC)(   (At(anIndex))->ItemText()   ));
    }

// Extension for CAknCheckBoxSettingPage
NONSHARABLE_CLASS(CAknCheckBoxSettingPageExtension): public CBase
    {
public:
    CAknCheckBoxSettingPageExtension();
public:
    TBool iIsDragged;
    };

CAknCheckBoxSettingPageExtension::CAknCheckBoxSettingPageExtension()
    : iIsDragged(EFalse)
    {
    }

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/**
 * Destructor
 *
 */
EXPORT_C CAknCheckBoxSettingPage::~CAknCheckBoxSettingPage()
    {
    AKNTASHOOK_REMOVE();
    delete (iInternalItemArray);
    delete iExtension;
    }


EXPORT_C CAknCheckBoxSettingPage::CAknCheckBoxSettingPage( TInt aResourceId, CSelectionItemList* aItemArray):
     CAknListBoxSettingPage(aResourceId), iItemArray(aItemArray)
    {
    AKNTASHOOK_ADD( this, "CAknCheckBoxSettingPage" );
    }


EXPORT_C CAknCheckBoxSettingPage::CAknCheckBoxSettingPage(
            const TDesC* aSettingText,
            TInt aSettingNumber,
            TInt aControlType,
            TInt aEditorResourceId,
            TInt aSettingPageResourceId,
            CSelectionItemList* aItemArray )
            :   CAknListBoxSettingPage(
                aSettingText,
                aSettingNumber,
                aControlType,
                aEditorResourceId,
                aSettingPageResourceId ),
                iItemArray(aItemArray)
    {
    AKNTASHOOK_ADD( this, "CAknCheckBoxSettingPage" );
    }


EXPORT_C void CAknCheckBoxSettingPage::ConstructL()
    {
    BaseConstructL();
    iExtension = new(ELeave) CAknCheckBoxSettingPageExtension;

    CreateCheckBoxBitmapsL();

    GenerateInternalArrayAndGiveToListBoxL();

    // This updates the CBA
    CheckAndSetDataValidity();
    UpdateCbaL();

    // Only a reference to the CBase object; not owned
    CAknSetStyleListBox* listBox = ListBoxControl();

    listBox->SetListBoxObserver(this);

    // Set the scroller indication to appear when needed
    listBox->CreateScrollBarFrameL(ETrue, ETrue);
    listBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,CEikScrollBarFrame::EAuto);
    listBox->ItemDrawer()->FormattedCellData()->SetDrawScrollbarBackground( EFalse );

    listBox->ScrollBarFrame()->VerticalScrollBar()->SetMopParent(this);
    listBox->UpdateScrollBarsL();

    if(!IsBackgroundDrawingEnabled())
        	listBox->ScrollBarFrame()->DrawBackground(EFalse, EFalse);
    
    // To force the layout
    SizeChanged();

    // check and change MSK according to item selection status
    CEikButtonGroupContainer *bgc;
    CCoeControl* MSK(NULL);
    CEikCba* cba(NULL);
    MopGetObject(bgc);
    TInt newResourceId(NULL);    
    if (bgc)
        {
		cba = ( static_cast<CEikCba*>( bgc->ButtonGroup() ) ); // downcast from MEikButtonGroup
		if (cba)
		    {
		    MSK = cba->Control(3); // MSK's position is 3
		    }
        }
    TInt currentSelectionIndex = listBox->CurrentItemIndex();

    if( iItemArray && iItemArray->Count() > 0 )
        {
        if (MSK && ( (cba->ControlId(MSK) == EAknSoftkeyMark) ||
                     (cba->ControlId(MSK) == EAknSoftkeyUnmark) ))
            {
            if( (*iItemArray)[currentSelectionIndex]->SelectionStatus() )
                {
                newResourceId = R_AVKON_SOFTKEY_UNMARK;
                }
            else
                {
                newResourceId = R_AVKON_SOFTKEY_MARK;
                }
            }
        if (newResourceId)
            {
            bgc->SetCommandL(3,newResourceId);
            cba->DrawNow();
            }
        }

    // Construct an appropriate control context for the contained editor areas.
    // Context produced is owned by CAknSettingPage.
    SetEditedItemFrameIID( KAknsIIDQsnFrSetOpt, KAknsIIDQsnFrSetOptCenter );
    }


EXPORT_C void CAknCheckBoxSettingPage::HandleListBoxEventL(CEikListBox* /*aListBox*/,
        MEikListBoxObserver::TListBoxEvent aEventType)
    {
    if (!iExtension)
        {
        iExtension = new (ELeave) CAknCheckBoxSettingPageExtension;
        }
    
    switch ( aEventType )
        {
        // Fall through these things that should all cause the selection to change
        case MEikListBoxObserver::EEventEnterKeyPressed:
        case MEikListBoxObserver::EEventItemActioned:
        case MEikListBoxObserver::EEventItemClicked:
        case MEikListBoxObserver::EEventItemSingleClicked:
            // select when no dragging
            if ( !iExtension->iIsDragged )
                {
                ToggleSelectionL();
                UpdateSettingL();
                }
            break;
        case MEikListBoxObserver::EEventItemDraggingActioned:
        case EEventPanningStarted:
        case EEventFlickStarted:
            iExtension->iIsDragged = ETrue;
            break;
        case MEikListBoxObserver::EEventPenDownOnItem:         
            iExtension->iIsDragged = EFalse;
            if( iSettingPageObserver )
                iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);
            break;
        default:
            break;
        }
    }

void CAknCheckBoxSettingPage::ToggleSelectionL()
    {
    CAknSetStyleListBox* listBox = ListBoxControl();
    CListBoxView* view = listBox->View();
    TInt currentSelectionIndex = listBox->CurrentItemIndex();

    TInt newResourceId(NULL);
    // Toggle based upon current master status
    if( iItemArray && iItemArray->Count() > 0 )
        {
        if( (*iItemArray)[currentSelectionIndex]->SelectionStatus() )
            {
            view->DeselectItem( currentSelectionIndex );
            ( (*iItemArray)[ currentSelectionIndex ] )->SetSelectionStatus( EFalse );
            newResourceId = R_AVKON_SOFTKEY_MARK;
            }
        else
            {
            view->SelectItemL( currentSelectionIndex );
            ( (*iItemArray)[ currentSelectionIndex ] )->SetSelectionStatus( ETrue );
            newResourceId = R_AVKON_SOFTKEY_UNMARK;
            }
        }


    // if the selection came from Mark/Unmark event from MSK, toggle also MSK
    CEikButtonGroupContainer *bgc;
    CCoeControl* MSK(NULL);
    CEikCba* cba(NULL);
    MopGetObject(bgc);
    if (bgc)
        {
		cba = ( static_cast<CEikCba*>( bgc->ButtonGroup() ) ); // downcast from MEikButtonGroup
		if (cba)
		    {
		    MSK = cba->Control(3); // MSK's position is 3
		    }
        }
    if (MSK && ( (cba->ControlId(MSK) == EAknSoftkeyMark) ||
                 (cba->ControlId(MSK) == EAknSoftkeyUnmark) ))
        {
        if (newResourceId)
            {
            bgc->SetCommandL(3,newResourceId);
            cba->DrawNow();
            }
        }

    if( iSettingPageObserver )
        iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);

    }

EXPORT_C void CAknCheckBoxSettingPage::UpdateSettingL()
    {
    }

EXPORT_C CAknSetStyleListBox* CAknCheckBoxSettingPage::ListBoxControl() const
    {
    return STATIC_CAST( CAknSetStyleListBox*, EditorControl());
    }


EXPORT_C void CAknCheckBoxSettingPage::DynamicInitL()
    {
    }


void CAknCheckBoxSettingPage::UpdateAllSelections()
    {
    TInt nItems = iItemArray->Count();
    CAknSetStyleListBox* listBox = ListBoxControl();
    CListBoxView* view = listBox->View();

    for (TInt ii=0; ii<nItems; ii++)
        {
        (*iItemArray)[ ii ]->SetSelectionStatus( view->ItemIsSelected( ii ) );
        }

    }

void CAknCheckBoxSettingPage::SetAllSelectionsL()
    {
    TInt nItems = iItemArray->Count();
    CAknSetStyleListBox* listBox = ListBoxControl();
    CListBoxView* view = listBox->View();

    for (TInt ii=0; ii<nItems; ii++)
        {
        if ( (*iItemArray)[ ii ]->SelectionStatus() )
            view->SelectItemL( ii );
        else
            view->DeselectItem( ii );
        }

    }

/**
 * Processes events from the softkeys. (Or tranlated from key events)
 *
 *
 * @param   aCommandId  Event Id from the soft-key
 */
EXPORT_C void CAknCheckBoxSettingPage::ProcessCommandL(TInt aCommandId)
    {
    HideMenu();

    // Respond to softkey events
    switch (aCommandId)
        {
        case EAknSoftkeySelect:
        case EAknSoftkeyMark:
        case EAknSoftkeyUnmark:
            if ( AknLayoutUtils::PenEnabled() )
                {
                if (ListBoxControl()->View()->ItemIsVisible(ListBoxControl()->View()->CurrentItemIndex()))
                    {
                    SelectCurrentItemL();
                    }
                else
                    {
                    // No exit in this case
                    ListBoxControl()->View()->ScrollToMakeItemVisible(ListBoxControl()->View()->CurrentItemIndex());
                    ListBoxControl()->UpdateScrollBarsL();
                    }
                }
            else
                {
                SelectCurrentItemL(); // No exit in this case
                }
            break;
        case EAknSoftkeyOk:
        case EAknSoftkeyDone:
            if ( AknLayoutUtils::PenEnabled() )
                {
                // Pen support changes selection only in the view, do update for items here.
                UpdateAllSelections();
                }
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

EXPORT_C void CAknCheckBoxSettingPage::SelectCurrentItemL()
    {
    ToggleSelectionL();
    UpdateSettingL();
    }

void CAknCheckBoxSettingPage::GenerateInternalArrayAndGiveToListBoxL()
    {

    delete iInternalItemArray;
    iInternalItemArray = 0;

// Make a new owned text array from the input one:
    iInternalItemArray = new(ELeave)CDesCArrayFlat(1);
    TInt nItems = iItemArray->Count();

    for (TInt ii=0; ii<nItems; ii++)
        {
        // Fill up the control-owned space for the modified buffers:
        TInt newLen = ((*iItemArray)[ii]->ItemText()).Length() + KOneSlashT().Length();
        HBufC* newText = HBufC::NewMaxLC( newLen );

        TPtr newTPtr = newText->Des();
        newTPtr.Copy( KOneSlashT );
        newTPtr.Append( ((*iItemArray)[ii])->ItemText() );
        // A copy of the new buffer goes to the internal itemarray:
        iInternalItemArray->AppendL(newTPtr);
        CleanupStack::PopAndDestroy(); // newText
        }

    CAknSetStyleListBox* listBox = ListBoxControl();

    CTextListBoxModel* model=listBox->Model();
    model->SetItemTextArray(iInternalItemArray);
    model->SetOwnershipType(ELbmDoesNotOwnItemArray);

    //
    // let the list box not throw away pointer event 
    //
    if( nItems > 0)
        {	
        CArrayFix<TInt>* tmp = new(ELeave)CArrayFixFlat<TInt>(nItems);  
        CleanupStack::PushL( tmp );    
        for(TInt i=0; i<nItems; i++)
            {
            tmp->AppendL( i );
            }
        listBox->SetPointerEventFilterDisabledL( *tmp );         
        CleanupStack::PopAndDestroy( tmp );
        }

// Transfer the selected status from the input array into the listbox view:
    SetAllSelectionsL();

    }

EXPORT_C void CAknCheckBoxSettingPage::SetSelectionItemArrayL( CSelectionItemList* aItemArray )
    {
    iItemArray = aItemArray;
    GenerateInternalArrayAndGiveToListBoxL();

    // This updates the CBA
    CheckAndSetDataValidity();
    UpdateCbaL();

    SizeChanged();
    DrawDeferred();
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknCheckBoxSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {}
#else
EXPORT_C void CAknCheckBoxSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CAknSettingPage::WriteInternalStateL(aWriteStream);
    }
#endif

//---------------------------------------------------------------------------------------
// CAknCheckBoxSettingPage::HandlePointerEventL()
// Handles pointer events by removing Shift and Control button modifiers from it and
// sends modified pointerevent to CEikListbox. This prevents multiselection
//---------------------------------------------------------------------------------------
//
EXPORT_C void CAknCheckBoxSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if ( !iExtension )
        {
        iExtension = new(ELeave) CAknCheckBoxSettingPageExtension;
        }

    TPointerEvent newPointerEvent = aPointerEvent;

    // Remove Shift and Ctrl modifiers from PointerEvent
    newPointerEvent.iModifiers &= ~EModifierShift;
    newPointerEvent.iModifiers &= ~EModifierCtrl;

    // If click on an item, pressed down state draw. After dragging to other item
    // or outside, item can not be selected.        
    CAknSetStyleListBox* listbox = ListBoxControl();
    TInt index;
    if ( newPointerEvent.iType == TPointerEvent::EButton1Down 
        && listbox->View()->XYPosToItemIndex( newPointerEvent.iPosition, index ))
        {
        listbox->View()->ItemDrawer()->SetFlags( CListItemDrawer::EPressedDownState );
        }
    else if ( aPointerEvent.iType == TPointerEvent::EDrag 
              && !listbox->Rect().Contains( aPointerEvent.iPosition ))
        {
        iExtension->iIsDragged = ETrue;
        }

    CAknListBoxSettingPage::HandlePointerEventL( aPointerEvent );
    }

void CAknCheckBoxSettingPage::CreateCheckBoxBitmapsL()
    {
    // Only a reference to the CBase object; not owned
    CAknSetStyleListBox* listBox = ListBoxControl();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
    // In case CAknPopupSettingList has already created the icons
    if ( listBox->ItemDrawer()->FormattedCellData()->IconArray() )
        {
        listBox->ItemDrawer()->FormattedCellData()->IconArray()->ResetAndDestroy();
        delete (listBox->ItemDrawer()->FormattedCellData()->IconArray());
        }
    
    TResourceReader reader;
    // Original code used R_AVKON_SETTING_PAGE_CHECKBOX_ICONS but
    // R_AVKON_RADIOBUTT_BMP defines the same icons.
    iCoeEnv->CreateResourceReaderLC(reader, R_AVKON_SETTING_PAGE_CHECKBOX_ICONS);
    
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
                              KAknsIIDQgnIndiCheckboxOn,
                              EAknsCIQsnIconColorsCG14,
                              *bmpFile,
                              bmpSelected,
                              bmpSelectedM );

    CreateIconAndAddToArrayL( icons,
                              KAknsIIDQgnIndiCheckboxOff,
                              EAknsCIQsnIconColorsCG14,
                              *bmpFile,
                              bmp,
                              bmpM );

    // create highlight colored icons
    CreateIconAndAddToArrayL( icons,
                              KAknsIIDQgnIndiCheckboxOn,
                              EAknsCIQsnIconColorsCG18,
                              *bmpFile,
                              bmpSelected,
                              bmpSelectedM );

    CreateIconAndAddToArrayL( icons,
                              KAknsIIDQgnIndiCheckboxOff,
                              EAknsCIQsnIconColorsCG18,
                              *bmpFile,
                              bmp,
                              bmpM );


    listBox->ItemDrawer()->FormattedCellData()->SetIconArrayL(icons); // ownership transferred, cell data deletes all members of list
    listBox->ItemDrawer()->FormattedCellData()->UseHighlightIconSwapping( ETrue );
        
    CleanupStack::Pop(); // icons - ownership now transferred; do not destroy
    CleanupStack::PopAndDestroy(); // bmpfile
    }

EXPORT_C void CAknCheckBoxSettingPage::HandleResourceChange(TInt aType)
    {
    if( aType == KAknsMessageSkinChange )
        {
        TRAP_IGNORE( CreateCheckBoxBitmapsL() );
        }

    CAknSettingPage::HandleResourceChange(aType);
    }


/**
* Setting Page reserved methods
*/

EXPORT_C void* CAknCheckBoxSettingPage::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

/**
 *  Reserved method derived from CCoeControl
 */
EXPORT_C void CAknCheckBoxSettingPage::Reserved_2()
    {
    }

/**
* Setting Page reserved methods
*/
EXPORT_C void CAknCheckBoxSettingPage::CAknSettingPage_Reserved_1()
    {
    }
EXPORT_C void CAknCheckBoxSettingPage::CAknSettingPage_Reserved_2()
    {
    }

/**
* CAknListBoxSettingPage-derived reserved methods
*/
EXPORT_C void CAknCheckBoxSettingPage::CAknListBoxSettingPage_Reserved_1()
    {
    }

// End of File
