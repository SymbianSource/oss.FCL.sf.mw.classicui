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
*  Support for Radio button style popup setting pages
*
*
*/


#include "aknradiobuttonsettingpage.h"

// For icon support
#include <barsread.h>
#include <gulicon.h>

// lists
#include <aknlists.h>

// For icon array support
#include <AknIconArray.h>

#include <AknTasHook.h>
// Used for setting  1 in the radio button 
_LIT(KOneSlashT, "1\t");

enum TAknRadioButtonSettingPagePanicCodes
    {
    EAknPanicRadioButtonSettingPageIndexOutOfRange
    };

GLDEF_C void Panic(TAknRadioButtonSettingPagePanicCodes aPanic)
    {
    _LIT(KPanicCat,"AknRadioButtonSettingPage");
    User::Panic(KPanicCat, aPanic);
    }
    
    
// ----------------------------------------------------------------------------
// Extension class definition
// ----------------------------------------------------------------------------
//
NONSHARABLE_CLASS( CAknRadioButtonSettingPageExtension ) : public CBase
    {
public: // Data
	CAknRadioButtonSettingPageExtension( CCoeControl& aOwner );
	~CAknRadioButtonSettingPageExtension();

    // This CBase object is owned. Note that this depends upon the ownership flag given 
	// to the CTextListBoxModel object
	CDesCArrayFlat* iInternalItemArray;
	
	TInt iOldFocusedItemIndex; // Index of item that was focused before pointer down event
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
// end of CAknRadioButtonSettingPageExtension class definition


CAknRadioButtonSettingPageExtension::CAknRadioButtonSettingPageExtension(
    CCoeControl& aOwner ) :
    iOldFocusedItemIndex(-1), iIsDragged( EFalse )
    {
    if ( static_cast<CAknAppUi*>(
            aOwner.ControlEnv()->AppUi() )->IsSingleClickCompatible() )
        {
        iFlags.Set( ESingleClickEnabled );
        }
    }   
    
CAknRadioButtonSettingPageExtension::~CAknRadioButtonSettingPageExtension()
    {
    }



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


EXPORT_C CAknRadioButtonSettingPage::CAknRadioButtonSettingPage( TInt aResourceId, TInt& aCurrentSelectionItem, const MDesCArray* aItemArray):
	CAknListBoxSettingPage(aResourceId), iOldSelectionIndex(aCurrentSelectionItem), iCurrentSelectionIndex(aCurrentSelectionItem), iItemArray(aItemArray)
	{
	AKNTASHOOK_ADD( this, "CAknRadioButtonSettingPage" );
	}


EXPORT_C CAknRadioButtonSettingPage::CAknRadioButtonSettingPage(	
			const TDesC* aSettingText, 
			TInt aSettingNumber, 
			TInt aControlType,
			TInt aEditorResourceId, 
			TInt aSettingPageResourceId, 
			TInt& aCurrentSelectionIndex, 
			const MDesCArray* aItemArray )
			:	CAknListBoxSettingPage( 
				aSettingText, 
				aSettingNumber, 
				aControlType, 
				aEditorResourceId, 
				aSettingPageResourceId ), 
				iOldSelectionIndex(aCurrentSelectionIndex), 
				iCurrentSelectionIndex(aCurrentSelectionIndex), 
				iItemArray(aItemArray)
	{
	AKNTASHOOK_ADD( this, "CAknRadioButtonSettingPage" );
	}


/**
 * Destructor
 *
 */
EXPORT_C CAknRadioButtonSettingPage::~CAknRadioButtonSettingPage()
	{
	AKNTASHOOK_REMOVE();
	if ( iExtension )
		{
		delete iExtension->iInternalItemArray;
		delete iExtension;
		}
	}

EXPORT_C void CAknRadioButtonSettingPage::ConstructL()
	{
	BaseConstructL();

    // Construct an appropriate control context for the contained editor areas.
    // Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrSetOpt, KAknsIIDQsnFrSetOptCenter );

	GenerateInternalArrayAndGiveToListBoxL();

	// This updates the CBA 
	CheckAndSetDataValidity();
	UpdateCbaL();

	// Only a reference to the CBase object; not owned
	CAknSetStyleListBox* listBox = ListBoxControl();
	
	InitialiseRadioButtonBitmapsL();
	
	if (!iExtension)
		{
		iExtension = new (ELeave) CAknRadioButtonSettingPageExtension( *this ); 
		}

    // Range should be within the valid indices, or -1:
	// So valid range is >= -1 and also < Count.
	__ASSERT_ALWAYS( iCurrentSelectionIndex >= -1, Panic(	EAknPanicRadioButtonSettingPageIndexOutOfRange) );
	__ASSERT_ALWAYS( iCurrentSelectionIndex < iExtension->iInternalItemArray->Count(), Panic(	EAknPanicRadioButtonSettingPageIndexOutOfRange) );

	listBox->View()->CalcBottomItemIndex();
	// Set initial highlight to the top element
	if (FocusToFirstItem())
		{// Set initial highlight to the top element
		if ( iExtension->iInternalItemArray->Count() > 0 )
			listBox->SetCurrentItemIndex( 0 );
		}
	if (FocusToSelectedItem())
		{// Set initial highlight to the current element.
		if ( iExtension->iInternalItemArray->Count() > 0 )
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
	{
    	TBool redrawDisabled = listBox->View()->RedrawDisabled();
    	listBox->View()->SetDisableRedraw(ETrue);
		listBox->View()->SelectItemL( iCurrentSelectionIndex );
    	listBox->View()->SetDisableRedraw(redrawDisabled);
	}

	// Set the scroller indication to appear when needed
	listBox->CreateScrollBarFrameL(ETrue, ETrue);
	listBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,CEikScrollBarFrame::EAuto);

    listBox->ItemDrawer()->FormattedCellData()->SetDrawScrollbarBackground( EFalse ); 
	// Need to do this to set up the scroll bar model
	listBox->ScrollBarFrame()->VerticalScrollBar()->SetMopParent(this);
	listBox->UpdateScrollBarsL();
	
	if(!IsBackgroundDrawingEnabled())
        	listBox->ScrollBarFrame()->DrawBackground(EFalse, EFalse);

	// Force a size changed
	SizeChanged();
}


EXPORT_C void CAknRadioButtonSettingPage::HandleListBoxEventL(CEikListBox* /*aListBox*/, 
		MEikListBoxObserver::TListBoxEvent aEventType)
	{
	if (!iExtension)
		{
        iExtension = new (ELeave) CAknRadioButtonSettingPageExtension( *this );
		}
		
    switch ( aEventType )
        {
        case MEikListBoxObserver::EEventItemSingleClicked:
        case MEikListBoxObserver::EEventItemDoubleClicked:
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
                     CAknRadioButtonSettingPageExtension::ESingleClickEnabled ) )
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

EXPORT_C void CAknRadioButtonSettingPage::UpdateSettingL()
	{
	}

EXPORT_C CAknSetStyleListBox* CAknRadioButtonSettingPage::ListBoxControl() const
	{
	return STATIC_CAST( CAknSetStyleListBox*, EditorControl());
	}

EXPORT_C void CAknRadioButtonSettingPage::DynamicInitL()
    {
    }

void CAknRadioButtonSettingPage::SetRadioButtonSelectionL( TInt aPushed )
	{
	if ( aPushed != iOldSelectionIndex )
		{
	    CListBoxView* view = ListBoxControl()->View();
	    view->DeselectItem( iOldSelectionIndex );
		iOldSelectionIndex = aPushed;
		view->SelectItemL( aPushed );
		}
	} 

EXPORT_C void CAknRadioButtonSettingPage::SelectCurrentItemL()
	{
    iCurrentSelectionIndex = ListBoxControl()->CurrentItemIndex();
    SetRadioButtonSelectionL( iCurrentSelectionIndex );
	UpdateSettingL();
	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);
	} 


EXPORT_C void CAknRadioButtonSettingPage::SetItemArrayAndSelectionL( const MDesCArray* aItemArray, TInt aPushed )
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

void CAknRadioButtonSettingPage::GenerateInternalArrayAndGiveToListBoxL()
	{
	if (!iExtension)
		{
        iExtension = new (ELeave) CAknRadioButtonSettingPageExtension( *this );
		}

	delete iExtension->iInternalItemArray;
	iExtension->iInternalItemArray = 0;
	
	// Make a new owned text array from the input one with the "Pushed in" icon index:
  	iExtension->iInternalItemArray = new(ELeave)CDesCArrayFlat(1);
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
		iExtension->iInternalItemArray->AppendL(newTPtr); 
		CleanupStack::PopAndDestroy(); // newText
		}

	// Only a reference to the CBase object; not owned
	CAknSetStyleListBox* listBox = ListBoxControl();

	// Set the text data
	CTextListBoxModel* model=listBox->Model();
	model->SetItemTextArray(iExtension->iInternalItemArray);
	model->SetOwnershipType(ELbmDoesNotOwnItemArray);

	}


void CAknRadioButtonSettingPage::InitialiseRadioButtonBitmapsL()
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
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknRadioButtonSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknRadioButtonSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

//---------------------------------------------------------------------------------------
// CAknRadioButtonSettingPage::HandlePointerEventL()
// Handles pointer events by removing Shift and Control button modifiers from it and
// sends modified pointerevent to CEikListbox. This prevents multiselection
//---------------------------------------------------------------------------------------
//

EXPORT_C void CAknRadioButtonSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    TPointerEvent& event = const_cast<TPointerEvent&>( aPointerEvent );
    event.iModifiers &= ~EModifierShift;
    event.iModifiers &= ~EModifierCtrl;

    CAknListBoxSettingPage::HandlePointerEventL( aPointerEvent );
    }

EXPORT_C void* CAknRadioButtonSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

    
/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknRadioButtonSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknRadioButtonSettingPage::HandleResourceChange(TInt aType)
	{
    if( aType == KAknsMessageSkinChange )
    	{
    	TRAP_IGNORE( InitialiseRadioButtonBitmapsL() );    	
    	}
	
	CAknListBoxSettingPage::HandleResourceChange(aType);
	}

EXPORT_C void CAknRadioButtonSettingPage::CAknSettingPage_Reserved_1()
	{
	}

EXPORT_C void CAknRadioButtonSettingPage::CAknSettingPage_Reserved_2()
	{
	}
/**
* CAknListBoxSettingPage-derived reserved methods
*/
EXPORT_C void CAknRadioButtonSettingPage::CAknListBoxSettingPage_Reserved_1()
	{
	}

// End of File
