/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implements test bc for popup field text testcase.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <bctestpopups.rsg> 
#include <aknpopupfieldtext.h>
#include <barsread.h>           // TResourceRead
#include <aknform.h>
#include <aknlists.h>
#include <akndef.h>             //KEikDynamicLayoutVariantSwitch
#include <aknscontrolcontext.h> //MAknsControlContext
#include <aknqueryvaluenumber.h>
#include <BADESCA.H>

#include "bctestpopupfieldtextcase.h"
#include "bctestsubpopupfieldtext.h"
#include "bctestpopupscontainer.h"
#include "bctestpopups.hrh"
#include "autotestcommands.h"

// constant
const TInt KBCTestMaxNumberOfLine = 2;
const TInt KAPFNumber = 1;

_LIT( KBaseDialog, "BaseDialog created" );
_LIT( KAknPopupFieldText, "Popupfieldtext created" );
_LIT( KCurrentValueTextLC, 
    "Invoke CAknPopupFieldText's CurrentValueTextLC()" );
_LIT( KCurrentValueIndex, 
    "Invoke CAknPopupFieldText's CurrentValueIndex()" );
_LIT( KSetCurrentValueIndex, 
    "Invoke CAknPopupFieldText's SetCurrentValueIndex()" );
_LIT( KSetAutoAppend, "Invoke CAknPopupFieldText's SetAutoAppend()" );
_LIT( KAPFTSetAllowsUserDefinedEntry, 
    "Invoke CAknPopupFieldText's SetAllowsUserDefinedEntry()" );
_LIT( KMdcArray, "Invoke CAknPopupFieldText's MdcArray()" );
_LIT( KHandlePointerEventL, 
    "Invoke CAknPopupFieldText's HandlePointerEventL()" );
_LIT( KConstructFromResourceL, 
    "Invoke CAknPopupFieldText's ConstructFromResourceL" );
_LIT( KConstructL, "Invoke CAknPopupField's ConstructL()" );
_LIT( KAknPopupField, "Popupfield created" );
_LIT( KMinimumSize, "Invoke CAknPopupField's MinimumSize()" );
_LIT( KSetAllowsUserDefinedEntry, 
    "Invoke CAknPopupField's SetAllowsUserDefinedEntry()" );
_LIT( KActivateSelectionListL, 
    "Invoke CAknPopupField's ActivateSelectionListL()" );
_LIT( KSetFont, "Invoke CAknPopupField's SetFont()" );
_LIT( KSetShowIndicatorsL, 
    "Invoke CAknPopupField's SetShowIndicatorsL()" );
_LIT( KNumLines, "Invoke CAknPopupField's NumLines()" );
_LIT( KSetPopupFieldObserver, 
    "Invoke CAknPopupField's SetPopupFieldObserver()" );
_LIT( KEmptyText, "empty text" );
_LIT( KSetEmptyTextL, "Invoke CAknPopupField's SetEmptyTextL()" );
_LIT( KOtherText, "Other text" );
_LIT( KSetOtherTextL, "Invoke CAknPopupField's SetOtherTextL()" );
_LIT( KInvalidText, "Invalid text" );
_LIT( KSetInvalidTextL, "Invoke CAknPopupField's SetInvalidTextL()" );
_LIT( KOfferKeyEventL, "Invoke CAknPopupField's OfferKeyEventL()" );
_LIT( KSetMaxNumberOfLinesPermitted, 
    "Invoke CAknPopupField's SetMaxNumberOfLinesPermitted()" );
_LIT( KSetFormFieldRect, "Invoke CAknPopupField's SetFormFieldRect()" );
_LIT( KSetEmptyListNoteL, "Invoke CAknPopupField's SetEmptyListNoteL()" );
_LIT( KHandleResourceChange, 
    "Invoke CAknPopupField's HandleResourceChange()" );
_LIT( KBCTestSubPopupFieldText, "BCTestSubPopupFieldText created" );
_LIT( KSizeChanged, "Invoke CAknPopupField's SizeChanged()" );
_LIT( KSubHandleControlEventL, 
    "Invoke CAknPopupField's HandleControlEventL()" );
_LIT( KCountComponentControls, 
    "Invoke CAknPopupField's CountComponentControls()" );
_LIT( KComponentControl, "Invoke CAknPopupField's ComponentControl()" );
_LIT( KFocusChanged, "Invoke CAknPopupField's FocusChanged()" );
_LIT( KMopSupplyObject, "Invoke CAknPopupField's MopSupplyObject()" );
_LIT( KProcessCommandL, "Invoke CAknPopupField's ProcessCommandL()" );
_LIT( KHandleListBoxEventL, "Invoke CAknPopupField's HandleListBoxEventL()" );
_LIT( KDraw, "Invoke CAknPopupField's Draw()" );

const TInt KZero = 1;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KTen = 10;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPopupFieldTextCase* CBCTestPopupFieldTextCase::NewL(
    CBCTestPopupsContainer* aContainer )
    {
    CBCTestPopupFieldTextCase* self = new( ELeave ) CBCTestPopupFieldTextCase(
        aContainer );
    CleanupStack::PushL( self ); 
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestPopupFieldTextCase::CBCTestPopupFieldTextCase(
    CBCTestPopupsContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPopupFieldTextCase::~CBCTestPopupFieldTextCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPopupFieldTextCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestPopupFieldTextCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestPopupFieldTextCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline1
        DELAY( KOne ),  // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        KeyOK,
        KeyOK,

        //outline2
        LeftCBA,
        KeyOK,
        REP( Down, KOne ),
        KeyOK,
        
        //outline3
        LeftCBA,
        KeyOK,
        REP( Down, KTwo ),
        KeyOK 
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestPopupFieldTextCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestPopupFieldTextCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestPopupsCmdOutline01 ) 
        || ( aCmd > EBCTestPopupsCmdOutline03 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestPopupsCmdOutline01:
            TestPopupFieldTextL();
            break;
        case EBCTestPopupsCmdOutline02:
            TestPopupFieldL();
            break;
        case EBCTestPopupsCmdOutline03:
            TestProtectedFunctionsL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestPopupFieldTextCase::TestPopupFieldTextL
// ---------------------------------------------------------------------------
//
void CBCTestPopupFieldTextCase::TestPopupFieldTextL()
    {
    iBaseDialog = new( ELeave ) CAknForm();
    AssertNotNullL( iBaseDialog, KBaseDialog );       
    iBaseDialog->PrepareLC( R_BCTESTPOPUPS_FIELD_TEXT_DIALOG );
    CleanupStack::Pop();
    
    // Invoke CAknPopupFieldText()
    CAknPopupFieldText* popupFieldText = new( ELeave ) CAknPopupFieldText();
    delete popupFieldText;
    popupFieldText = NULL;
    
    popupFieldText = static_cast<CAknPopupFieldText*>
        ( iBaseDialog->ControlOrNull( EBCTestPopFieldDlgCtrlIdFldText01 ) );
    AssertNotNullL( popupFieldText, KAknPopupFieldText );    
    
    // Invoke CAknPopupFieldText's CurrentValueTextLC()
    HBufC* text = popupFieldText->CurrentValueTextLC();
    AssertTrueL( ETrue, KCurrentValueTextLC );
    CleanupStack::PopAndDestroy( text ); 

    // Invoke CAknPopupFieldText's CurrentValueIndex()
    TInt value = popupFieldText->CurrentValueIndex();
    AssertTrueL( ETrue, KCurrentValueIndex );

    // Invoke CAknPopupFieldText's SetCurrentValueIndex()
    popupFieldText->SetCurrentValueIndex( KOne );
    AssertTrueL( ETrue, KSetCurrentValueIndex );
    
    // Invoke CAknPopupFieldText's SetAutoAppend()
    popupFieldText->SetAutoAppend( ETrue );
    AssertTrueL( ETrue, KSetAutoAppend );
    
    // Invoke CAknPopupFieldText's SetAllowsUserDefinedEntry()
    popupFieldText->SetAllowsUserDefinedEntry( ETrue );
    AssertTrueL( ETrue, KAPFTSetAllowsUserDefinedEntry );
        
    // Invoke CAknPopupFieldText's MdcArray()
    const MDesCArray* array = popupFieldText->MdcArray();
    AssertTrueL( ETrue, KMdcArray );
    TInt mdcaCount = array->MdcaCount(); 
    
    // Invoke CAknPopupFieldText's HandlePointerEventL()
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    popupFieldText->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KHandlePointerEventL ); 
       
    delete iBaseDialog;
    iBaseDialog = NULL; 
       
    // Invoke CAknPopupFieldText's ConstructFromResourceL()
    popupFieldText = new( ELeave ) CAknPopupFieldText();
    CleanupStack::PushL( popupFieldText );
    TResourceReader reader;
    iContainer->GetCoeEnv()->CreateResourceReaderLC( 
        reader, R_BCTESTPOPUPS_POPUP_FIELD_TEXT );
    popupFieldText->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KConstructFromResourceL );  
    CleanupStack::PopAndDestroy(); //reader 
     
    CleanupStack::PopAndDestroy( popupFieldText );
    }
    
// ---------------------------------------------------------------------------
// CBCTestPopupFieldTextCase::TestPopupFieldL
// ---------------------------------------------------------------------------
//
void CBCTestPopupFieldTextCase::TestPopupFieldL()
    {
    iBaseDialog = new( ELeave ) CAknForm();
    AssertNotNullL( iBaseDialog, KBaseDialog );       
    iBaseDialog->PrepareLC( R_BCTESTPOPUPS_TWO_TEXT_FIELD_DIALOG );
    CleanupStack::Pop();
    
    // Invoke CAknPopupField()
    CAknPopupField* popupField = new( ELeave ) CAknPopupField();
    
    // Invoke CAknPopupField's ConstructL()
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, 
        R_BCTESTPOPUPS_POPUP_FIELD_TEXT );
    popupField->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KConstructL );
    
    CleanupStack::PopAndDestroy(); 
     
    delete popupField;
    popupField = NULL;
    
    popupField = static_cast<CAknPopupField*>
        ( iBaseDialog->ControlOrNull( EBCTestPopFieldDlgCtrlIdPop01 ) );
    AssertNotNullL( popupField, KAknPopupField );    
        
    // Invoke CAknPopupField's MinimumSize()
    TSize s = popupField->MinimumSize(); 
    AssertTrueL( ETrue, KMinimumSize );  
    
    // Invoke CAknPopupField's SetAllowsUserDefinedEntry()
    popupField->SetAllowsUserDefinedEntry( ETrue );
    AssertTrueL( ETrue, KSetAllowsUserDefinedEntry );

    // Invoke CAknPopupField's ActivateSelectionListL()
    popupField->ActivateSelectionListL();
    AssertTrueL( ETrue, KActivateSelectionListL );
    
    // Invoke CAknPopupField's SetFont()
    popupField->SetFont( NULL );
    AssertTrueL( ETrue, KSetFont );    
    
    // Invoke CAknPopupField's SetShowIndicatorsL()
    popupField->SetShowIndicatorsL( EFalse );
    AssertTrueL( ETrue, KSetShowIndicatorsL );   
    
    // Invoke CAknPopupField's NumLines()
    popupField->NumLines();
    AssertTrueL( ETrue, KNumLines );     
    
    // Invoke CAknPopupField's SetPopupFieldObserver()
    popupField->SetPopupFieldObserver( NULL );
    AssertTrueL( ETrue, KSetPopupFieldObserver ); 
    
    // Invoke CAknPopupField's SetEmptyTextL()
    popupField->SetEmptyTextL( KEmptyText );
    AssertTrueL( ETrue, KSetEmptyTextL );
    
    // Invoke CAknPopupField's SetOtherTextL()
    popupField->SetOtherTextL( KOtherText );
    AssertTrueL( ETrue, KSetOtherTextL );    

    // Invoke CAknPopupField's SetInvalidTextL()
    popupField->SetInvalidTextL( KInvalidText );
    AssertTrueL( ETrue, KSetInvalidTextL );
    
    // Invoke CAknPopupField's OfferKeyEventL()
    TKeyEvent keyEvent;  
    keyEvent.iCode = EKeyTab;
    popupField->OfferKeyEventL( keyEvent, EEventKey ); 
    keyEvent.iCode = EKeyEnter;
    popupField->OfferKeyEventL( keyEvent, EEventKey ); 
    keyEvent.iCode = EKeyOK;
    popupField->OfferKeyEventL( keyEvent, EEventKey ); 
    keyEvent.iCode = EKeyLeftArrow;
    popupField->OfferKeyEventL( keyEvent, EEventKey ); 
    keyEvent.iCode = EKeyRightArrow;
    popupField->OfferKeyEventL( keyEvent, EEventKey ); 
    keyEvent.iCode = EKeyDownArrow;
    popupField->OfferKeyEventL( keyEvent, EEventKey );                     
    AssertTrueL( ETrue, KOfferKeyEventL );  
        
    // Invoke CAknPopupField's SetMaxNumberOfLinesPermitted()
    popupField->SetMaxNumberOfLinesPermitted( KBCTestMaxNumberOfLine );
    AssertTrueL( ETrue, KSetMaxNumberOfLinesPermitted );
    
    // Invoke CAknPopupField's SetFormFieldRect()
    TRect rect( KTen, KTen, KTen, KTen );
    popupField->SetFormFieldRect( rect );
    AssertTrueL( ETrue, KSetFormFieldRect );

    // Invoke CAknPopupField's SetEmptyListNoteL()
    popupField->SetEmptyListNoteL( R_BCTESTPOPUPS_EMPTY_LIST_NOTE );
    AssertTrueL( ETrue, KSetEmptyListNoteL );

    // Invoke CAknPopupField's HandleResourceChange()
    popupField->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    AssertTrueL( ETrue, KHandleResourceChange );
    popupField->HandleResourceChange( 
        KEikMessageCaptionedControlEditableStateChange );
    popupField->HandleResourceChange( 
        KEikMessageCaptionedControlEditableStateChangeWideWithGraphic );
    popupField->HandleResourceChange( 
        KEikMessageCaptionedControlNotEditableStateChange );
    popupField->HandleResourceChange( 
        KEikMessageCaptionedControlEditableStateChangeWideWithoutGraphic );
    popupField->HandleResourceChange( 
        KEikMessageCaptionedControlNotEditableStateChangeWideWithGraphic );    
    popupField->HandleResourceChange( 
        KEikMessageCaptionedControlNotEditableStateChangeWideWithoutGraphic );  
   
    
    _LIT( KArrayContent, "test" );
    CAknQueryValueText* queryValue = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValue );
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( array );
    CDesC16ArrayFlat* temp = new (ELeave) CDesC16ArrayFlat(1);
    CleanupStack::PushL( temp );
    temp->AppendL( KArrayContent );
    array->SetArray( *temp );
    queryValue->SetArrayL( array );
    popupField->SetQueryValueL( queryValue );
    
    CBCTestSubPopupFieldText* subPopupField = 
        static_cast<CBCTestSubPopupFieldText*>( popupField );
    subPopupField->ActivateSelectionListL();
    subPopupField->HandleListBoxEventL( NULL, 
       MEikListBoxObserver::EEventEnterKeyPressed );
    AssertTrueL( ETrue, KHandleListBoxEventL );
    
    temp->Delete( 0 );
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( queryValue );
     
    delete iBaseDialog;
    iBaseDialog = NULL;
    }
    
// ---------------------------------------------------------------------------
// CBCTestPopupFieldTextCase::TestProtectedFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestPopupFieldTextCase::TestProtectedFunctionsL()
    {
    iBaseDialog = new( ELeave ) CAknForm();
    AssertNotNullL( iBaseDialog, KBaseDialog );       
    iBaseDialog->PrepareLC( R_BCTESTPOPUPS_TWO_TEXT_FIELD_DIALOG );
    CleanupStack::Pop();    
    
    CBCTestSubPopupFieldText* subPopupField = 
        static_cast<CBCTestSubPopupFieldText*>
        ( iBaseDialog->ControlOrNull( EBCTestPopFieldDlgCtrlIdPop01 ) );
    AssertNotNullL( subPopupField, KBCTestSubPopupFieldText );    
    
    // Invoke CAknPopupField's SetFormFieldRect()
    TRect rect( KZero, KZero, KTen, KTen );
    subPopupField->SetFormFieldRect( rect );
    AssertTrueL( ETrue, KSetFormFieldRect );
        
    // Invoke CAknPopupField's SizeChanged()
    subPopupField->SizeChanged();
    AssertTrueL( ETrue, KSizeChanged );

    // Invoke CAknPopupField's HandleControlEventL()
    CEikFormattedCellListBox* formatListBox = 
        new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( formatListBox );
    subPopupField->HandleControlEventL( formatListBox, 
        MCoeControlObserver::EEventRequestExit ); 
    subPopupField->HandleControlEventL( formatListBox, 
        MCoeControlObserver::EEventRequestFocus );         
    subPopupField->HandleControlEventL( formatListBox, 
        MCoeControlObserver::EEventPrepareFocusTransition ); 
    _LIT( KArrayContent, "test" );
    CAknQueryValueText* queryValue = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValue );
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( array );
    CDesC16ArrayFlat* temp = new (ELeave) CDesC16ArrayFlat(1);
    CleanupStack::PushL( temp );
    temp->AppendL( KArrayContent );
    array->SetArray( *temp );
    queryValue->SetArrayL( array );
    subPopupField->SetQueryValueL( queryValue );    
    subPopupField->ActivateSelectionListL();// this called change the variable iSelectionMode to MCoeControlObserver::EEventRequestCancel
    // so that when called function handleControlEventl(), it doesn't panic
    // the above paragraph is copy from function CBCTestPopupFieldTextCase::TestPopupFieldL()
    subPopupField->HandleControlEventL( formatListBox, 
        MCoeControlObserver::EEventRequestCancel ); 
    subPopupField->HandleControlEventL( formatListBox, 
        MCoeControlObserver::EEventStateChanged ); 
    AssertTrueL( ETrue, KSubHandleControlEventL );
    
    // Invoke CAknPopupField's CountComponentControls()
    subPopupField->CountComponentControls();
    AssertTrueL( ETrue, KCountComponentControls );

    // Invoke CAknPopupField's ComponentControl()
    subPopupField->ComponentControl( KAPFNumber );
    AssertTrueL( ETrue, KComponentControl );
    
    // Invoke CAknPopupField's FocusChanged()
    subPopupField->FocusChanged( EDrawNow );
    AssertTrueL( ETrue, KFocusChanged );
    
    // Invoke CAknPopupField's MopSupplyObject()
    TTypeUid typeUid( MAknsControlContext::ETypeId );
    subPopupField->MopSupplyObject( typeUid ); 
    AssertTrueL( ETrue, KMopSupplyObject );  
    
    // Invoke CAknPopupField's ProcessCommandL()
    subPopupField->ProcessCommandL( EAknSoftkeyBack ); 
    AssertTrueL( ETrue, KProcessCommandL ); 
    
    // Invoke CAknPopupField's Draw() 
    CWindowGc& gc = iContainer->SystemGc();
    iContainer->ActivateGc();
    subPopupField->Draw( rect );
    iContainer->DeactivateGc();    
    AssertTrueL( ETrue, KDraw );    
       
    delete iBaseDialog;
    iBaseDialog = NULL; 
    temp->Delete( 0 );
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( queryValue );
    CleanupStack::PopAndDestroy( formatListBox );    
    }

    





    
   

    
