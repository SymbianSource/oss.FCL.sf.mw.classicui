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
* Description:         test case
*
*/








#include <avkon.rsg>
#include <bctestsearchfield.rsg>
#include <eikenv.h>
#include <eikappui.h>
#include <eikspane.h>
#include <aknsfld.h>    // CAknSearchField

#include "bctestsearchfieldcase.h"
#include "bctestsearchfieldcontainer.h"
#include "bctestsearchfield.hrh"

const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KFifteen = 15;
const TInt KTwenty = 20;
const TInt KSearchFieldMaxLength = 256;

_LIT( KCreateComment, "iSearchField created" );
_LIT( KSetSkinEnabledLComment, "SetSkinEnabledL() invoked" );
_LIT( KText, "TestSearchField" );
_LIT( KSetSearchTextLComment, "SetSearchTextL() invoked" );
_LIT( KTextLengthComment, "SearchFieldLength = 15" );
_LIT( KSelectSearchTextLComment, "SelectSearchTextL() invoked" );
_LIT( KGetSearchTextLComment, "GetSearchTextL() invoked" );
_LIT( KResetLComment, "ResetL() invoked" );
_LIT( KTextLengthOverComment, "SearchFieldLength = 0" );
_LIT( KInfoText, "This is my searchfield.");
_LIT( KSetInfoTextLComment, "SetInfoTextL() invoked" );
_LIT( KMinimumSizeComment, "MinimumSize() invoked" );
_LIT( KSetLinePosComment, "SetLinePos() invoked" );
_LIT( KEditorComment, "Editor() invoked" );
_LIT( KClipboardLComment, "ClipboardL() invoked" );
_LIT( KOfferKeyEventLComment, "OfferKeyEventL() invoked" );
_LIT( KHandleControlEventL, "HandleControlEventL() invoked" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestSearchFieldCase* CBCTestSearchFieldCase::NewL( 
    CBCTestSearchFieldContainer* aContainer )
    {
    CBCTestSearchFieldCase* self = new( ELeave ) CBCTestSearchFieldCase( 
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
CBCTestSearchFieldCase::CBCTestSearchFieldCase( 
    CBCTestSearchFieldContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSearchFieldCase::~CBCTestSearchFieldCase()
    {  
    delete iSearchField;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestSearchFieldCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldCase::BuildScriptL()
    { 
    const TInt scripts[] =
        {
        //outline1
        DELAY( KTwo ),// delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, 
        LeftCBA,

        //outline2
        LeftCBA,
        REP( Down, KOne ),
        LeftCBA,
        
        //outline3
        LeftCBA,
        REP( Down, KTwo ),
        LeftCBA        
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestSearchFieldCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline01 || 
        aCmd > EBCTestCmdOutline03 )
        {
        return;
        }    
    switch ( aCmd )
        {
        case EBCTestCmdOutline01:
            TestCreateL();
            break;
        case EBCTestCmdOutline02: 
            TestTextL();       
            break;
        case EBCTestCmdOutline03:
            TestOthersL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// try to test creation of the searchfield control.
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldCase::TestCreateL()
    {
    if ( !iSearchField )
        {
        iSearchField = CAknSearchField::NewL( *iContainer, 
            CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
        AssertNotNullL( iSearchField, KCreateComment );
        
        iSearchField->SetSkinEnabledL( ETrue );
        iSearchField->SetSkinEnabledL( EFalse );
        
        AssertTrueL( ETrue, KSetSkinEnabledLComment );
        }
    }

// ---------------------------------------------------------------------------
// test searchfield control about text APIs.
// ---------------------------------------------------------------------------
//    
void CBCTestSearchFieldCase::TestTextL()
    {
    if ( !iSearchField )
        {
        TestCreateL();
        }
        
    iSearchField->SetSearchTextL( KText );
    AssertTrueL( ETrue, KSetSearchTextLComment );
    iContainer->DrawNow();
    
    AssertIntL( KFifteen, iSearchField->TextLength(), KTextLengthComment ); 
    
    iSearchField->SelectSearchTextL();
    AssertTrueL( ETrue, KSelectSearchTextLComment );
    
    TBuf<KTwenty> rSearchTxt;
    iSearchField->GetSearchText( rSearchTxt );
    AssertTrueL( ETrue, KGetSearchTextLComment );
    
    iSearchField->ResetL(); 
    AssertTrueL( ETrue, KResetLComment );
    AssertIntL( 0, iSearchField->TextLength(), KTextLengthOverComment );
    
    iSearchField->SetInfoTextL( KInfoText );
    AssertTrueL( ETrue, KSetInfoTextLComment );
       
    }

// ---------------------------------------------------------------------------
// test searchfield control about other APIs.
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldCase::TestOthersL()
    {
    if ( !iSearchField )
        {
        TestCreateL();
        }
        
    TSize minisize;
    minisize = iSearchField->MinimumSize(); 
    AssertTrueL( ETrue, KMinimumSizeComment );
    
    iSearchField->SetLinePos( KOne );
    iSearchField->SetLinePos( KThree );
    AssertTrueL( ETrue, KSetLinePosComment );

    iSearchField->Editor();
    AssertTrueL( ETrue, KEditorComment );
    
    iSearchField->ClipboardL( CEikEdwin::ECopy );
    AssertTrueL( ETrue, KClipboardLComment );
        
    CCoeControl* control = new( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    iSearchField->HandleControlEventL( control, 
        MCoeControlObserver::EEventRequestFocus );
    AssertTrueL( ETrue, KHandleControlEventL );  
    CleanupStack::PopAndDestroy( control );  
    
    TKeyEvent keyevent;
    keyevent.iCode = EKeyOK;
    iSearchField->OfferKeyEventL( keyevent, EEventKey ); 
    
    keyevent.iCode = EKeyRightArrow;
    iSearchField->OfferKeyEventL( keyevent, EEventKey ); 

    keyevent.iCode = EKeyLeftArrow;
    iSearchField->OfferKeyEventL( keyevent, EEventKey );
    
    keyevent.iCode = EKeyUpArrow;
    iSearchField->OfferKeyEventL( keyevent, EEventKey );    

    keyevent.iCode = EKeyDownArrow;
    iSearchField->OfferKeyEventL( keyevent, EEventKey );
           
    AssertTrueL( ETrue, KOfferKeyEventLComment );    
    }

    
