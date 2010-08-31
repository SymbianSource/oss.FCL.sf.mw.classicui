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
*	Implementation of popup setting item in its editing state
*
*/
 


#include "aknpopupsettingpage.h"

//For TResourceReader
#include <barsread.h>

// For icon array support
#include <AknIconArray.h>

// For icon support
#include <gulicon.h>

#include <AknTasHook.h>
// For Avkon list styles
#include "aknlists.h"


#include <aknlayoutscalable_avkon.cdl.h>

// Used for setting  1 in the radio button 
_LIT(KPopupSettingListLeadingLayoutText, "1\t");

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistloadertfx.h>
#include <aknlistboxtfxinternal.h>
#endif //RD_UI_TRANSITION_EFFECTS_LIST



// ----------------------------------------------------------------------------
// Extension class definition
// ----------------------------------------------------------------------------
//
NONSHARABLE_CLASS( CAknPopupSettingListExtension ) : public CBase
    {
public:
    /**
     * C++ constructor.
     */
    CAknPopupSettingListExtension( CCoeControl& aOwner );

public: // Data
    TInt iOldFocusedItemIndex;
    TBool iIsDragged;

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

// ----------------------------------------------------------------------------
// Extension class constructor.
// ----------------------------------------------------------------------------
//
CAknPopupSettingListExtension::CAknPopupSettingListExtension(
        CCoeControl& aOwner )
    {
    if ( static_cast<CAknAppUi*>(
            aOwner.ControlEnv()->AppUi() )->IsSingleClickCompatible() )
        {
        iFlags.Set( ESingleClickEnabled );
        }
    }

// end of CAknPopupSettingListExtension class definition



//*******************************************************************************************/
// CAknPopupSettingList


/** 
 * Standard constructor.
 */
EXPORT_C CAknPopupSettingList::CAknPopupSettingList()
	{
	}

/** 
 * Destructor.
 *
 */
EXPORT_C CAknPopupSettingList::~CAknPopupSettingList()
	{
	DestroyMenuList(); // currnetly just removes this from control stack
	delete iLayoutDecorator;
	delete iOtherText;
	delete iExtension;
	}



/** 
 * 2nd phase construction
 *
 */
EXPORT_C void CAknPopupSettingList::ConstructL()
	{
	iOtherText = HBufC::NewL(0);
	CommonConstructL();
	}

/** 
 * Construct from resources.
 *
 */
EXPORT_C void CAknPopupSettingList::ConstructFromResourceL(TResourceReader& aReader)
	{
	// First construct the standard lisbox using a standard Avkon resource
	TResourceReader defaultReader;
	iCoeEnv->CreateResourceReaderLC(defaultReader, R_AVKON_POPUP_SETTING_LIST_EMPTY_LISTBOX );
	CEikFormattedCellListBox::ConstructFromResourceL(defaultReader);
	CleanupStack::PopAndDestroy(); // defaultReader
	SetListBoxObserver(this);

	iFlags=aReader.ReadInt16();
 	aReader.ReadInt16();   // Read in and discard Width.
	iOtherText  = aReader.ReadHBufCL();
	iNewItemSettingPageResourceId = aReader.ReadInt32();
	iNewItemEditorType = aReader.ReadInt16();
	iNewItemEditorControlResourceId = aReader.ReadInt32();

	CommonConstructL();

	}

void CAknPopupSettingList::CommonConstructL()
	{
	// Finish construction
	SetUpSelectionListL();

	// It may be possible that value is set already
	if (iValue)
		{
		ConfigureMenuListL();
		ActivateMenuListL();
		}
	}

/**
 *
 * This routine sets up the text arrays for the menu list
 *
 */
EXPORT_C void CAknPopupSettingList::ConfigureMenuListL()
	{
	ConfigureDecorator();	
	ConstructLayoutDecoratorL();
	}

/**
 * Causes the list of pre-defined values to appear. 
 * Use this method to activate the pop-up field from a menu option command. 
 * Note that the desired control must have the focus before it can be activated.
 *
 */
EXPORT_C void CAknPopupSettingList::ActivateMenuListL()
	{
	if (iValue)
		{
		CreateMenuListL();
		SetFocus(ETrue, ENoDrawNow);		
		}
	}


/** 
 * Create the menu list. 
 * 
 */
void CAknPopupSettingList::SetUpSelectionListL()
	{
	TResourceReader reader;
	iCoeEnv->CreateResourceReaderLC( reader, R_AVKON_SET_PANE_EMPTY) ;
	HBufC *buf = reader.ReadHBufC16L(); // read text stored as a LBUF, which is actually a LTEXT
	CleanupStack::PopAndDestroy(); // reader no longer needed.
	CleanupStack::PushL(buf);
	View()->SetListEmptyTextL(*buf);
	CleanupStack::PopAndDestroy(); // buf no longer needed.
	InitialiseRadioButtonBitmapsL();
	}

/** 
 * Set up the bitmap array for the "not pushed" and "pushed in" states
 *
 */
void CAknPopupSettingList::InitialiseRadioButtonBitmapsL()
    {
    // This method is more or less a verbatim copy of
    // CAknPopupField::InitialiseRadioButtonBitmapsL
        
    // In case CAknPopupSettingList has already created the icons
    if ( ItemDrawer()->FormattedCellData()->IconArray() )
        {
        ItemDrawer()->FormattedCellData()->IconArray()->ResetAndDestroy();
        delete (ItemDrawer()->FormattedCellData()->IconArray());
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
    CAknListBoxSettingPage::CreateIconAndAddToArrayL(
        icons,
        KAknsIIDQgnIndiRadiobuttOn,
        EAknsCIQsnIconColorsCG14,
        *bmpFile,
        bmpSelected,
        bmpSelectedM );

    CAknListBoxSettingPage::CreateIconAndAddToArrayL(
        icons,
        KAknsIIDQgnIndiRadiobuttOff,
        EAknsCIQsnIconColorsCG14,
        *bmpFile,
        bmp,
        bmpM );

    // create highlight colored icons
    CAknListBoxSettingPage::CreateIconAndAddToArrayL(
        icons,
        KAknsIIDQgnIndiRadiobuttOn,
        EAknsCIQsnIconColorsCG18,
        *bmpFile,
        bmpSelected,
        bmpSelectedM );
    
    CAknListBoxSettingPage::CreateIconAndAddToArrayL(
        icons,
        KAknsIIDQgnIndiRadiobuttOff,
        EAknsCIQsnIconColorsCG18,
        *bmpFile,
        bmp,
        bmpM );


    ItemDrawer()->FormattedCellData()->SetIconArrayL(icons); // ownership transferred, cell data deletes all members of list
    ItemDrawer()->FormattedCellData()->UseHighlightIconSwapping( ETrue );        

    CleanupStack::Pop(icons); // icons - ownership now transferred; do not destroy
    
    CleanupStack::PopAndDestroy(bmpFile); // bmpfile
    }


/**
 * Processes key events from the listbox. Responds to EEventEnterKeyPressed to accept
 * the pop-up.
 *
 * @param	aListBox	Listbox being observed
 * @param	aEventType	Event observed
 *
 *
 * This implementation is vestige of former implementation when the listbox was wrapped up,
 * not derived from. Currently observing itself..
 *
 */
EXPORT_C void CAknPopupSettingList::HandleListBoxEventL(CEikListBox* /*aListBox*/, TListBoxEvent aEventType)
	{
	switch ( aEventType )
	    {
        case MEikListBoxObserver::EEventPanningStopped:
        case MEikListBoxObserver::EEventFlickStopped:
            // Change list's current item index to the selected item. This
            // ensures that correct item gets selected if setting page is
            // accepted by clicking the left softkey.
            if ( iExtension && iExtension->iFlags.IsSet( 
                    CAknPopupSettingListExtension::ESingleClickEnabled ) )
                {
                View()->SetCurrentItemIndex( iCurrentSelection );
                }
            break;
            
        case MEikListBoxObserver::EEventItemSingleClicked:
        case MEikListBoxObserver::EEventEnterKeyPressed: 
        case MEikListBoxObserver::EEventItemActioned:
        case MEikListBoxObserver::EEventItemDoubleClicked:
            {
            CListBoxView* view = View();

            if ( aEventType == MEikListBoxObserver::EEventItemSingleClicked ||
                 !( ItemDrawer()->Flags() &
                        CListItemDrawer::ESingleClickDisabledHighlight ) )
                {
                // Update the current selection only if the selection came from
                // HW-keys, i.e. the list highlight is visible OR in case
                // of single tap event.
                if ( iCurrentSelection != view->CurrentItemIndex() )
                    {
                    view->DeselectItem( iCurrentSelection );
                    iCurrentSelection = view->CurrentItemIndex();
                    view->SelectItemL( iCurrentSelection );
                    }
                }

            if ( iValue )
                {
                if ( aEventType == MEikListBoxObserver::EEventItemSingleClicked )
                    {
                    iValue->SetCurrentValueIndex( iCurrentSelection );
                    }
                else
                    {
                    iValue->SetCurrentValueIndex( view->CurrentItemIndex() );
                    }
                }

            if ( iPopupSettingListObserver )
                {
                // To do selection, point event needs
                // EAknPopupSettingSelectionAndClose, but it will also cause
                // AttemptExit() run twice. So we give different oberver
                // event for them.
                iPopupSettingListObserver->HandlePopupSettingListEventL(
                    this,
                    aEventType == MEikListBoxObserver::EEventEnterKeyPressed ? 
                        MAknPopupSettingListObserver::EAknPopupSettingSelectionAndRequestAccept : 
                        MAknPopupSettingListObserver::EAknPopupSettingSelectionAndClose,
                    iCurrentSelection );
                }
            }
            break; 

        default:
            break;
	    }
	}

// ----------------------------------------------------------------------------
// CAknPopupSettingList::HandlePointerEventL()
// Processes listbox's pointer event's so that listboxt will act like radiobuttons. 
// This implementation overwrites CEikListBox's HandlePointerEventL function
// It will not act for control-button presses. So multiple selection is impossible. 
// ----------------------------------------------------------------------------
EXPORT_C void CAknPopupSettingList::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    // remove pointer event modifiers to prevent marking etc
    TPointerEvent& pointerEvent = const_cast<TPointerEvent&>( aPointerEvent );
    pointerEvent.iModifiers &= ~EModifierShift;
    pointerEvent.iModifiers &= ~EModifierCtrl;

    CAknSetStyleListBox::HandlePointerEventL( pointerEvent );
    }


EXPORT_C void* CAknPopupSettingList::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 * All this does now is remove this from the stack
 *
 */
EXPORT_C void CAknPopupSettingList::DestroyMenuList()
    {
    iEikonEnv->RemoveFromStack(this);
    }

/**
 * Create the popup list. Current implementation  
 *
 */
EXPORT_C void CAknPopupSettingList::CreateMenuListL()
	{
	if (!iExtension)
		{
        iExtension = new ( ELeave ) CAknPopupSettingListExtension( *this );
		}
	
	// set the array into the listbox
	Model()->SetItemTextArray(iLayoutDecorator);
	Model()->SetOwnershipType(ELbmDoesNotOwnItemArray);
	View()->ClearSelection();

	// must update the scrollbars before setting the current index
	UpdateScrollBarsL();
	
	TInt selection = -1;
	
	if(iValue)
	    selection = iValue->CurrentValueIndex();

	if ( selection > -1 )
		{
		View()->SelectItemL(selection);
		iCurrentSelection = selection;
		}
	
	MakeVisible(ETrue);
	ActivateL();

	}


EXPORT_C void CAknPopupSettingList::Reserved_1()
	{}
EXPORT_C void CAknPopupSettingList::Reserved_2()
	{}


	
/**
 * Sets flag that enables user defined entry. Note that flag can also be set from resources, 
 * but this method allows behaviour to be changed at runtime.
 *
 * @param aAllows	if ETrue, set flag; if EFalse, clear flag.
 */
EXPORT_C void CAknPopupSettingList::SetAllowsUserDefinedEntry(TBool aAllows)
	{
	if(aAllows)
		iFlags |= EAknPopupSettingListFlagAllowsUserDefinedEntry;
	else
		iFlags &= ~EAknPopupSettingListFlagAllowsUserDefinedEntry;
	
	ConfigureDecorator();
	}



/**
 * Used by the client to set the query value used to represent the user defined 
 * value belonging to this popup field control.
 *
 * @param aValue	pointer to value, ownership is not passed
 *
 */
EXPORT_C void CAknPopupSettingList::SetQueryValueL(MAknQueryValue* aValue)
	{
	__ASSERT_DEBUG(aValue, Panic(EAknPanicPopupSettingListInvalidValue));
	iValue = aValue; // The query value is externally owned.  Just copy the pointer
	ConfigureMenuListL();
	ActivateMenuListL();
	}


/**
 * Set the flag which determines whether the indicators are shown
 * In practice the indicators have the appearance of radio buttons
 *
 * @param aShowIndicators	
 *		If ETrue, indicators are displayed; 
 *		if EFalse, indicators are not displayed
 *
 */
EXPORT_C void CAknPopupSettingList::SetShowIndicators(TBool aShowIndicators)
	{
	__ASSERT_DEBUG(iLayoutDecorator, Panic(EAknPanicPopupSettingListUninitialisedMember));
	iLayoutDecorator->SetActive(aShowIndicators);
	}

/**
 * number of lines used
 *
 * @returns number of lines being currently displayed by control, which is determined 
 *		by the number of entries on the selection list, and whether the selection list is active.
 *		NOTE that the number is limited by KAknMaxLinesOnOnePage
 *
 */
EXPORT_C TInt CAknPopupSettingList::NumLines() const
	{
	TInt lines = iDecorator.MdcaCount();
	
	// The maximum lines for the listbox
    TAknLayoutScalableParameterLimits listBoxLimits = 
	AknLayoutScalable_Avkon::list_set_graphic_pane_ParamLimits();
	TInt maxNumberOfRows = listBoxLimits.LastRow() + 1;
	
	// we must restrict ourselves to the max number of lines, as form will allow controls to be larger (e.g. edwin)
	if(lines > maxNumberOfRows)
		lines = maxNumberOfRows;

	return lines;
	}

/**
 * set an observer of this class to receive events from popup setting list
 * 
 * @param aObserver pointer to the class that implements the observer interface,
 *
 */
EXPORT_C void CAknPopupSettingList::SetPopupSettingListObserver(MAknPopupSettingListObserver* aObserver)
	{
	iPopupSettingListObserver = aObserver;
	}

/**
 * Selects current item.
 */
void CAknPopupSettingList::SelectCurrentItemL()
    {
    CListBoxView* view = View();

    if ( iCurrentSelection != view->CurrentItemIndex() )
        {
        view->DeselectItem( iCurrentSelection );
        iCurrentSelection = view->CurrentItemIndex();
        view->SelectItemL( iCurrentSelection );
        }

    if ( iValue )
        {
        iValue->SetCurrentValueIndex( iCurrentSelection );
        }

    if ( iPopupSettingListObserver )
        {
        // To do selection, point event needs
        // EAknPopupSettingSelectionAndClose, but it will also cause
        // AttemptExit() run twice. So we give different oberver
        // event for them.
        iPopupSettingListObserver->HandlePopupSettingListEventL(
            this,
            MAknPopupSettingListObserver::EAknPopupSettingSelectionAndRequestAccept,
            iCurrentSelection );
        }
    }


// -----------------------------------------------------------------------------
// CAknPopupSettingList::CurrentSelection
// -----------------------------------------------------------------------------
//
TInt CAknPopupSettingList::CurrentSelection() const
    {
    return iCurrentSelection;
    }


/**
 * Configures the decoration according to the currently set flags.
 * Should be called whenever the flags are changed. 
 *
 */
void CAknPopupSettingList::ConfigureDecorator()
	{
	__ASSERT_DEBUG(iOtherText, Panic(EAknPanicPopupSettingListUninitialisedMember));

	iDecorator.SetDecorationText(*iOtherText);
	iDecorator.SetActive(iFlags & EAknPopupSettingListFlagAllowsUserDefinedEntry);

	// decorate the array from the query value
	if(iValue)
	    {
    	const MDesCArray* array = iValue->MdcArray();
    	iDecorator.SetArray(array);
	    }
	}

/**
 * Configures the layout decoration according to the "has buttons" flag
 * Should be called whenever the flags are changed. 
 *
 */
void CAknPopupSettingList::ConstructLayoutDecoratorL()
	{
	delete iLayoutDecorator;
	iLayoutDecorator = NULL;
	iLayoutDecorator = CAknListBoxLayoutDecorator::NewL();
	TPtrC textPtr(KPopupSettingListLeadingLayoutText);
	iLayoutDecorator->SetLeadingDecorationTextL(textPtr);
	iLayoutDecorator->SetArray(&iDecorator);
	iLayoutDecorator->SetActive(ETrue); // for now, always has buttons
	}

EXPORT_C void CAknPopupSettingList::HandleResourceChange(TInt aType)
	{	
	if( aType == KAknsMessageSkinChange )
	    {
		TRAP_IGNORE(InitialiseRadioButtonBitmapsL());
	    }
	CAknSetStyleListBox::HandleResourceChange(aType);
	}
//
// CAknPopupSettingPage Implementation
//
//


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


EXPORT_C CAknPopupSettingPage::CAknPopupSettingPage( TInt aResourceId, MAknQueryValue& aQueryValue ):
	CAknListBoxSettingPage(aResourceId), iQueryValue(aQueryValue)
	{
	AKNTASHOOK_ADD( this, "CAknPopupSettingPage" );
	}

EXPORT_C CAknPopupSettingPage::CAknPopupSettingPage(	
					const TDesC* aSettingText, 
					TInt aSettingNumber, 
					TInt aControlType,
					TInt aEditorResourceId, 
					TInt aSettingPageResourceId, 
					MAknQueryValue& aQueryValue)
					:	CAknListBoxSettingPage( 
						aSettingText, 
						aSettingNumber, 
						aControlType, 
						aEditorResourceId, 
						aSettingPageResourceId ), 
						iQueryValue(aQueryValue) 
	{
	AKNTASHOOK_ADD( this, "CAknPopupSettingPage" );
	}

/**
 * Destructor
 *
 */
EXPORT_C CAknPopupSettingPage::~CAknPopupSettingPage()
	{
	AKNTASHOOK_REMOVE();
	}

EXPORT_C void CAknPopupSettingPage::ConstructL()
	{
	BaseConstructL();

    // Construct an appropriate control context for the contained editor areas.
    // Context produced is owned by CAknSettingPage.
    SetEditedItemFrameIID( KAknsIIDQsnFrSetOpt, KAknsIIDQsnFrSetOptCenter );

	iQueryValue.SetQueryMode( MAknQueryValue::ESettingPageMode );
	PopupSettingListBox()->SetQueryValueL( &iQueryValue );
	CheckAndSetDataValidity();
	UpdateCbaL();

	PopupSettingListBox()->SetPopupSettingListObserver( this );
	// Set the scroller indication to appear when needed
	ListBoxControl()->CreateScrollBarFrameL(ETrue, ETrue);
	ListBoxControl()->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,CEikScrollBarFrame::EAuto);
	ListBoxControl()->ScrollBarFrame()->VerticalScrollBar()->SetMopParent(this);
	
	if(!IsBackgroundDrawingEnabled())
        	ListBoxControl()->ScrollBarFrame()->DrawBackground(EFalse, EFalse);

    ListBoxControl()->ItemDrawer()->FormattedCellData()->SetDrawScrollbarBackground( EFalse ); 

	//  This must be called to propogate the changed size of the listbox upward
	SizeChanged();

    // Exercise initial selection policy
    if ( FocusToSelectedItem() )
        ListBoxControl()->SetCurrentItemIndex( iQueryValue.CurrentValueIndex() );
    if ( FocusToFirstItem() )
        ListBoxControl()->SetCurrentItemIndex( 0 );
	}

EXPORT_C void CAknPopupSettingPage::HandlePopupSettingListEventL(CAknPopupSettingList* /*aPopupSettingList*/, TAknPopupSettingListEvent aEventType, TInt /*aHint*/)
	{
	if ( aEventType == MAknPopupSettingListObserver::EAknPopupSettingSelectionAndRequestAccept )
		{
		CheckAndSetDataValidity();
		UpdateCbaL();
		SizeChanged();
		ListBoxControl()->SetCurrentItemIndex( iQueryValue.CurrentValueIndex() );
		DrawDeferred();
		}
    else if ( aEventType == MAknPopupSettingListObserver::EAknPopupSettingSelectionAndClose )
        {
        AttemptExitL(ETrue);
        }
	}


EXPORT_C CAknPopupSettingList* CAknPopupSettingPage::PopupSettingListBox() const
	{
	return STATIC_CAST( CAknPopupSettingList*, EditorControl());
	}

/**
 * This is required to give access to the QUery from re-implementations of the 
 * popup setting page
 *
 */
EXPORT_C MAknQueryValue* CAknPopupSettingPage::QueryValue() const
	{
	return &iQueryValue;
	}

EXPORT_C void CAknPopupSettingPage::SelectCurrentItemL()
	{
#ifdef RD_TOUCH2
    CAknPopupSettingList* list = PopupSettingListBox();
    
    if ( ( list->ItemDrawer()->Flags() & 
            CListItemDrawer::ESingleClickDisabledHighlight ) 
            && list->CurrentItemIndex() != list->CurrentSelection() )
        {
        list->View()->SetCurrentItemIndex( list->CurrentSelection() );
        }
#endif // RD_TOUCH2
    
    PopupSettingListBox()->SelectCurrentItemL();
	} 

EXPORT_C void CAknPopupSettingPage::UpdateQueryValueL( MAknQueryValue* aQueryValue )
	{
	PopupSettingListBox()->SetQueryValueL( aQueryValue );
    iQueryValue = *aQueryValue ;
	CheckAndSetDataValidity();
	UpdateCbaL();
	SizeChanged();
    // Note that there is no update of the highlight selection here. 
	DrawDeferred();
	}

EXPORT_C CAknSetStyleListBox* CAknPopupSettingPage::ListBoxControl() const
	{
	return ( PopupSettingListBox() );
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknPopupSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknPopupSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknPopupSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknListBoxSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknPopupSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknPopupSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknPopupSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknPopupSettingPage::CAknSettingPage_Reserved_2()
	{
	}
/**
* CAknListBoxSettingPage-derived reserved methods
*/
EXPORT_C void CAknPopupSettingPage::CAknListBoxSettingPage_Reserved_1()
	{
	}

// End of File
