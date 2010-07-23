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
* Description:         Implements test bc for note wrapper testcase.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknnotewrappers.h> 
#include <bctestnote.rsg>
#include <eikdpobs.h>
#include <barsread.h>

#include "bctestnotewrappercase.h"
#include "bctestnotecontainer.h"
#include "bctestnote.hrh"
#include "autotestcommands.h"

// constant
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KFour = 4;
const TInt KFive = 5;
const TInt KTen = 15;

// constant for CAknWarningNote
_LIT( KWarningNoteCreateComment, "WarningNote created" );
_LIT( KWHandlePointerEventLComment, 
    "Warning Note's HandlePointerEventL() invoked" );
_LIT( KWarningNoteCreateOverComment, "WarningNote created(OverLoad)" );
_LIT( KWarningNote, "This is Warning note!" );
_LIT( KWExecuteLDComment, 
    "CAknResourceNoteDialog's ExecuteLD() invoked" );
_LIT( KWarningNoteCreateLoadComment, "pWarningNote created(overload)" );

// constant for CAknErrorNote
_LIT( KErrorNoteCreateComment, "ErrorNote created" );
_LIT( KEHandlePointerEventLComment, 
    "Error Note's HandlePointerEventL() invoked" );
_LIT( KErrorNoteCreateOverComment, "ErrorNote created(OverLoad)" );
_LIT( KErrorNote, "This is Error note!" );
_LIT( KEExecuteLDComment, 
    "CAknResourceNoteDialog's ExecuteLD() invoked" );
_LIT( KErrorNoteCreateLoadComment, "ErrorNote created(OverLoad again)" );

// constant for CAknInformationNote
_LIT( KInformationNoteCreateComment, "informationNote created" );
_LIT( KIHandlePointerEventLComment, 
    "information Note's HandlePointerEventL() invoked" );
_LIT( KInformationNoteCreateOverComment, 
    "informationNote created(OverLoad)" );
_LIT( KInforNote, "This is information note!" );
_LIT( KIExecuteLDComment, 
    "CAknResourceNoteDialog's ExecuteLD() invoked" );
_LIT( KInformationNoteCreateLoadComment, 
    "informationNote created(OverLoad again)" );

// constant for CAknConfirmationNote
_LIT( KConfirmationNoteCreateComment, "confirmationNote created" );
_LIT( KCHandlePointerEventLComment, 
    "confirmation Note's HandlePointerEventL() invoked" );
_LIT( KConfirmationNoteCreateOverComment, 
    "confirmationNote created(OverLoad)" );
_LIT( KCExecuteLDComment, 
    "CAknResourceNoteDialog's ExecuteLD() invoked" );
_LIT( KConfirmationNoteCreateLoadComment, 
    "confirmationNote created(OverLoad again)" );

// constant for CAknNoteWrapper
_LIT( KNoteWrapperCreateComment, "iNoteWrapper Created" );
_LIT( KNHandlePointerEventLComment, 
    "Note Wrapper's HandlePointerEventL() invoked" );
_LIT( KNHandleDialogPageEventLComment, 
    "Note Wrapper's HandleDialogPageEventL() invoked" );
_LIT( KNExecuteLDComment, "Note Wrapper's ExecuteLD() invoked" );
_LIT( KNoteWrapperCreateAgainComment, "iNoteWrapper Created" );
_LIT( KNoteWrapperCreateOverComment, "tmpNoteWrapper Created" );
_LIT( KPrompt, "Akn Note Wrapper OverLoad" );
_LIT( KNExecuteLDOverComment, "Note Wrapper's ExecuteLD() overload" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestNoteWrapperCase* CBCTestNoteWrapperCase::NewL(
    CBCTestNoteContainer* aContainer )
    {
    CBCTestNoteWrapperCase* self = new( ELeave ) CBCTestNoteWrapperCase(
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
CBCTestNoteWrapperCase::CBCTestNoteWrapperCase(
    CBCTestNoteContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestNoteWrapperCase::~CBCTestNoteWrapperCase()
    {
    if ( iNoteWrapper )
        {
        delete iNoteWrapper;
        iNoteWrapper = NULL;
        }
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestNoteWrapperCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestNoteWrapperCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestNoteWrapperCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline1
        DELAY( KOne ),// delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        LeftCBA,
        LeftCBA,
        WAIT( KTwo ),
        LeftCBA,

        //outline2
        LeftCBA,
        LeftCBA,
        REP( Down, KOne ),
        LeftCBA,
        WAIT( KTwo ),
        LeftCBA,
        
        //outline3
        LeftCBA,
        LeftCBA,
        REP( Down, KTwo ),
        LeftCBA,
        WAIT( KTwo ),
        LeftCBA, 

        //outline4
        LeftCBA,
        LeftCBA,
        REP( Down, KThree ),
        LeftCBA,
        WAIT( KTwo ),
        LeftCBA,               
        
        //outline5
        LeftCBA,
        LeftCBA,
        REP( Down, KFour ),
        LeftCBA,
        WAIT( KTen ),
        //LeftCBA,
        
        //outline6
        LeftCBA,
        LeftCBA,
        REP( Down, KFive ),
        LeftCBA,
        WAIT( KTen ), 
        //LeftCBA                
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestNoteWrapperCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestNoteWrapperCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestNoteCmdOutline01 ) 
        || ( aCmd > EBCTestNoteCmdOutline06 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestNoteCmdOutline01:
            TestWarningNoteL();             
            break;
        case EBCTestNoteCmdOutline02:
            TestErrorNoteL();
            break;
        case EBCTestNoteCmdOutline03:
            TestInformationNoteL();
            break;
        case EBCTestNoteCmdOutline04:
            TestConfirmationNoteL();
            break;
        case EBCTestNoteCmdOutline05:
            TestNoteWrapperL(); 
            break;
        case EBCTestNoteCmdOutline06:
            TestNoteWrapperOverLoadL(); 
            break;                                                            
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestNoteWrapperCase::TestWarningNoteL
// ---------------------------------------------------------------------------
//
void CBCTestNoteWrapperCase::TestWarningNoteL()
    {
    iWarningNote = new( ELeave ) CAknWarningNote();
    AssertNotNullL( iWarningNote, KWarningNoteCreateComment );
    
    TPointerEvent tPointerEvent;
    tPointerEvent.iType = TPointerEvent::EButton2Up;
    iWarningNote->HandlePointerEventL( tPointerEvent );
    AssertTrueL( ETrue, KWHandlePointerEventLComment );
    
    CAknWarningNote* tWarningNote = new( ELeave ) CAknWarningNote( EFalse );
    CleanupStack::PushL( tWarningNote );
    AssertNotNullL( tWarningNote, KWarningNoteCreateOverComment );
    
    CleanupStack::Pop( tWarningNote ); 
    tWarningNote->ExecuteLD( KWarningNote );
    AssertTrueL( ETrue, KWExecuteLDComment );     
    
    CAknWarningNote* pWarningNote = new( ELeave ) 
        CAknWarningNote( &iWarningNote ); 
    CleanupStack::PushL( pWarningNote );    
    AssertNotNullL( pWarningNote, KWarningNoteCreateLoadComment );
    CleanupStack::Pop( pWarningNote ); 
       
    delete iWarningNote;
    iWarningNote = NULL;
    delete pWarningNote;
    }

// ---------------------------------------------------------------------------
// CBCTestNoteWrapperCase::TestErrorNoteL
// ---------------------------------------------------------------------------
//
void CBCTestNoteWrapperCase::TestErrorNoteL()
    {
    iErrorNote = new( ELeave ) CAknErrorNote();
    AssertNotNullL( iErrorNote, KErrorNoteCreateComment );
    
    TPointerEvent tPointerEvent;
    tPointerEvent.iType = TPointerEvent::EButton2Up;
    iErrorNote->HandlePointerEventL( tPointerEvent );
    AssertTrueL( ETrue, KEHandlePointerEventLComment );  

    CAknErrorNote* tErrorNote = new( ELeave ) CAknErrorNote( EFalse );
    CleanupStack::PushL( tErrorNote );
    AssertNotNullL( tErrorNote, KErrorNoteCreateOverComment );
    CleanupStack::Pop( tErrorNote );
    
    tErrorNote->ExecuteLD( KErrorNote );    
    AssertTrueL( ETrue, KEExecuteLDComment );  
    
    CAknErrorNote* pErrorNote = new( ELeave ) CAknErrorNote( &iErrorNote );
    CleanupStack::PushL( pErrorNote );
    AssertNotNullL( pErrorNote, KErrorNoteCreateLoadComment );
    CleanupStack::Pop( pErrorNote );
    
    delete iErrorNote;
    iErrorNote = NULL;
    delete pErrorNote;
    }

// ---------------------------------------------------------------------------
// CBCTestNoteWrapperCase::TestInformationNoteL
// ---------------------------------------------------------------------------
//
void CBCTestNoteWrapperCase::TestInformationNoteL()
    {
    iInforNote = new( ELeave ) CAknInformationNote();
    AssertNotNullL( iInforNote, KInformationNoteCreateComment );
    
    TPointerEvent tPointerEvent;
    tPointerEvent.iType = TPointerEvent::EButton2Up;
    iInforNote->HandlePointerEventL( tPointerEvent );
    AssertTrueL( ETrue, KIHandlePointerEventLComment );  

    CAknInformationNote* tInforNote = new( ELeave ) 
        CAknInformationNote( EFalse );
    CleanupStack::PushL( tInforNote );
    AssertNotNullL( tInforNote, KInformationNoteCreateOverComment );
    CleanupStack::Pop( tInforNote );
    
    tInforNote->ExecuteLD( KInforNote );    
    AssertTrueL( ETrue, KIExecuteLDComment );  
    
    CAknInformationNote* pInforNote = new( ELeave ) 
        CAknInformationNote( &iInforNote );
    CleanupStack::PushL( pInforNote );
    AssertNotNullL( pInforNote, KInformationNoteCreateLoadComment );
    CleanupStack::Pop( pInforNote );
    
    delete iInforNote;
    iInforNote = NULL;
    delete pInforNote;
    }
    
// ---------------------------------------------------------------------------
// CBCTestNoteWrapperCase::TestConfirmationNoteL
// ---------------------------------------------------------------------------
//
void CBCTestNoteWrapperCase::TestConfirmationNoteL()
    {
    iConfirmNote = new( ELeave ) CAknConfirmationNote();
    AssertNotNullL( iConfirmNote, KConfirmationNoteCreateComment );
    
    TPointerEvent tPointerEvent;
    tPointerEvent.iType = TPointerEvent::EButton2Up;
    iConfirmNote->HandlePointerEventL( tPointerEvent );
    AssertTrueL( ETrue, KCHandlePointerEventLComment );  

    CAknConfirmationNote* tConfirmNote = new( ELeave ) 
        CAknConfirmationNote( ETrue );
    CleanupStack::PushL( tConfirmNote );
    AssertNotNullL( tConfirmNote, KConfirmationNoteCreateOverComment );
    CleanupStack::Pop( tConfirmNote );
    
    tConfirmNote->ExecuteLD();    
    AssertTrueL( ETrue, KCExecuteLDComment );  
    
    CAknConfirmationNote* pConfirmNote = new( ELeave ) 
        CAknConfirmationNote( &iConfirmNote );
    CleanupStack::PushL( pConfirmNote );
    AssertNotNullL( pConfirmNote, KConfirmationNoteCreateLoadComment );
    CleanupStack::Pop( pConfirmNote );
    
    delete iConfirmNote;
    iConfirmNote = NULL;
    delete pConfirmNote;
    }    

// ---------------------------------------------------------------------------
// CBCTestNoteWrapperCase::TestNoteWrapperL
// ---------------------------------------------------------------------------
//
void CBCTestNoteWrapperCase::TestNoteWrapperL()
    {
    COwnAknNoteWrapper* tmpNoteWrapper = new( ELeave ) COwnAknNoteWrapper();
    CleanupStack::PushL( tmpNoteWrapper );
    AssertNotNullL( tmpNoteWrapper, KNoteWrapperCreateComment );
    
    TInt err;
    TRAP( err, tmpNoteWrapper->ReadAndPrepareLC( R_BCTESTNOTE_WRAPPER ) );
    
    TPointerEvent tPointerEvent;
    tPointerEvent.iType = TPointerEvent::EButton3Up;
    tmpNoteWrapper->HandlePointerEventL( tPointerEvent );
    AssertTrueL( ETrue, KNHandlePointerEventLComment ); 
        
    tmpNoteWrapper->HandleDialogPageEventL( 
        MEikDialogPageObserver::EDialogPageTapped );
    AssertTrueL( ETrue, KNHandleDialogPageEventLComment );     
    
    //static delete tmpNoteWrapper in HandleDialogPageEventL().
    CleanupStack::Pop( tmpNoteWrapper );
    CAknNoteWrapper* otherTmpNoteWrapper = new( ELeave ) CAknNoteWrapper();
    otherTmpNoteWrapper->ExecuteLD( R_BCTESTNOTE_WRAPPER );
    AssertTrueL( ETrue, KNExecuteLDComment );
    }
    
// ---------------------------------------------------------------------------
// CBCTestNoteWrapperCase::TestNoteWrapperOverLoadL
// ---------------------------------------------------------------------------
//
void CBCTestNoteWrapperCase::TestNoteWrapperOverLoadL()
    {
    iNoteWrapper = new( ELeave ) CAknNoteWrapper();
    AssertNotNullL( iNoteWrapper, KNoteWrapperCreateAgainComment );

    CAknNoteWrapper* tmpNoteWrapper = new( ELeave ) 
         CAknNoteWrapper( &iNoteWrapper );
    CleanupStack::PushL( tmpNoteWrapper );
    AssertNotNullL( tmpNoteWrapper, KNoteWrapperCreateOverComment );
    
    delete iNoteWrapper;
    iNoteWrapper = NULL;
    CleanupStack::PopAndDestroy( tmpNoteWrapper ); 
    tmpNoteWrapper = NULL;   
    
    tmpNoteWrapper = new( ELeave ) CAknNoteWrapper();
    tmpNoteWrapper->ExecuteLD( R_BCTESTNOTE_WRAPPER, KPrompt );
    AssertTrueL( ETrue, KNExecuteLDOverComment );
    } 
    
// ---------------------------------------------------------------------------
// COwnAknNoteWrapper::ReadAndPrepareLC
// ---------------------------------------------------------------------------
//    
void COwnAknNoteWrapper::ReadAndPrepareLC(TInt aResId)
    {
    TResourceReader resReader;
    iCoeEnv->CreateResourceReaderLC(resReader, aResId);
    TAknNoteResData resData;
    resData.iResId = resReader.ReadInt32();
    resData.iTimeout = STATIC_CAST(CAknNoteDialog::TTimeout, resReader.ReadInt32());
    resData.iTone = STATIC_CAST(CAknNoteDialog::TTone, resReader.ReadInt16());
    resData.iText = resReader.ReadTPtrC();

    CleanupStack::PopAndDestroy(); // Resource reader
    PrepareLC(resData.iResId);
    CleanupStack::Pop();
    }
    
// ---------------------------------------------------------------------------
// COwnAknNoteWrapper::COwnAknNoteWrapper
// ---------------------------------------------------------------------------
//    
COwnAknNoteWrapper::COwnAknNoteWrapper()
    {    
    } 
    
// ---------------------------------------------------------------------------
// COwnAknNoteWrapper::~COwnAknNoteWrapper
// ---------------------------------------------------------------------------
//    
COwnAknNoteWrapper::~COwnAknNoteWrapper()
    {
    }           
    
    
       
