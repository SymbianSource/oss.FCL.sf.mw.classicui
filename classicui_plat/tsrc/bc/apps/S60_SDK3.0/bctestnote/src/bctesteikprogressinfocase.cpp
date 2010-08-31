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
* Description:         Implements test bc for eik progress info testcase.
*
*/









#include <w32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <eikprogi.h>
#include <AknProgressDialog.h>
#include <coecntrl.h>
#include <barsread.h> 
#include <coemain.h>
#include <bctestnote.rsg>
#include <s32mem.h> 

#include "bctesteikprogressinfocase.h"
#include "bctestsubeikprogressinfo.h"
#include "bctestnotecontainer.h"
#include "bctestnote.hrh"
#include "autotestcommands.h"

// constant
const TInt KBCTestNoteProgressbarFinalValue = 200;
const TInt KBCTestNoteProgressbarMaxLength = 256;
const TInt KOne = 1;
const TInt KFour = 4;
const TInt KTen = 10;
const TInt KTwenty = 20;
const TInt KTwoHundred = 200;

_LIT( KEikProgressInfoComment, "Eikprogressinfo created" );
_LIT( KRunDlgLDComment, "Eikprogressinfo's SetFinalValue() invoked" );
_LIT( KMinimumSizeComment, "Eikprogressinfo's MinimumSize() invoked" );
_LIT( KSizeChangedComment, "Eikprogressinfo's SizeChanged() invoked" );
_LIT( KActivateLComment, "Eikprogressinfo's ActivateL() invoked" );
_LIT( KSetLayoutComment, "Eikprogressinfo's SetLayout() invoked" );
_LIT( KSetBorderComment, "Eikprogressinfo's SetBorder() invoked" );
_LIT( KEikProgressInfoCreateOverComment, 
    "Eikprogressinfo created(overload)" );
_LIT( KIncrementAndDrawComment, 
    "Eikprogressinfo's IncrementAndDraw() invoked" );
_LIT( KGetColorUseListLComment, 
    "Eikprogressinfo's GetColorUseListL() invoked" );
_LIT( KHandlePointerEventLComment, 
    "EikProgressInfo's HandlePointerEventL() invoked" );
_LIT( KHandleResourceChangeComment, 
    "EikProgressInfo's HandleResourceChange() invoked" );
_LIT( KConstructFromResourceLComment, 
    "EikProgressInfo's ConstructFromResourceL() invoked" );
_LIT( KWriteInternalStateL, 
    "EikProgressInfo's WriteInternalStateL() invoked" );
_LIT( KBuf, "Evaluate" );
_LIT( KEvaluateText, 
    "EikProgressInfo's EvaluateText() invoked" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEikProgressInfoCase* CBCTestEikProgressInfoCase::NewL(
    CBCTestNoteContainer* aContainer )
    {
    CBCTestEikProgressInfoCase* self = new( ELeave ) 
		CBCTestEikProgressInfoCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestEikProgressInfoCase::CBCTestEikProgressInfoCase(
    CBCTestNoteContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEikProgressInfoCase::~CBCTestEikProgressInfoCase()
    {
        if ( iEikProgressInfo )
        {
        delete iEikProgressInfo;
        iEikProgressInfo = NULL;
        }
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEikProgressInfoCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestEikProgressInfoCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEikProgressInfoCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline13
        DELAY( KOne ),// delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP( Down, KFour ),
        KeyOK,
        KeyOK,

        //outline14
        LeftCBA,
        REP( Down, KFour ),
        KeyOK,
        REP( Down, KOne ),        
        KeyOK
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestEikProgressInfoCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEikProgressInfoCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestNoteCmdOutline13 ) 
        || ( aCmd > EBCTestNoteCmdOutline14 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestNoteCmdOutline13:
            TestPublicFunctionsL();
            break;
        case EBCTestNoteCmdOutline14:
            TestProtectedFunctionsL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestEikProgressInfoCase::TestPublicFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestEikProgressInfoCase::TestPublicFunctionsL()
    {
    iEikProgressInfo = new( ELeave ) CEikProgressInfo();
    AssertNotNullL( iEikProgressInfo, KEikProgressInfoComment );
    
    iEikProgressInfo->SetFinalValue( KBCTestNoteProgressbarFinalValue );
    AssertTrueL( ETrue, KRunDlgLDComment ); 

    iEikProgressInfo->MinimumSize();
    AssertTrueL( ETrue, KMinimumSizeComment ); 
    
    iEikProgressInfo->SizeChanged();
    AssertTrueL( ETrue, KSizeChangedComment ); 
    
    iEikProgressInfo->ActivateL();
    AssertTrueL( ETrue, KActivateLComment );   
    
    CEikProgressInfo::SLayout sLayout;
    iEikProgressInfo->SetLayout( sLayout );
    AssertTrueL( ETrue, KSetLayoutComment );   

    const TGulBorder gulBorder;
    iEikProgressInfo->SetBorder( gulBorder );
    AssertTrueL( ETrue, KSetBorderComment ); 
    
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* tEikProgressInfo = 
        new( ELeave ) CEikProgressInfo( sInfo );
    CleanupStack::PushL( tEikProgressInfo );
    AssertNotNullL( tEikProgressInfo, KEikProgressInfoCreateOverComment );
    
    tEikProgressInfo->IncrementAndDraw( 1 );
    AssertTrueL( ETrue, KIncrementAndDrawComment ); 
    
    CArrayFix <TCoeColorUse>* colorUseList = 
        new( ELeave ) CArrayFix <TCoeColorUse>( 
        ( TBufRep )CBufFlat::NewL, KTwenty );
    CleanupStack::PushL( colorUseList );
    tEikProgressInfo->GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KGetColorUseListLComment );
    CleanupStack::PopAndDestroy( colorUseList );
    CleanupStack::PopAndDestroy( tEikProgressInfo );
    
    TPointerEvent tPointerEvent;
    tPointerEvent.iType = TPointerEvent::EButton2Up;
    iEikProgressInfo->HandlePointerEventL( tPointerEvent );
    AssertTrueL( ETrue, KHandlePointerEventLComment ); 

    iEikProgressInfo->HandleResourceChange( KBCTestNoteProgressbarMaxLength ); 
    AssertTrueL( ETrue, KHandleResourceChangeComment );
    
    TResourceReader reader;
    iContainer->GetCoeEnv()->CreateResourceReaderLC( 
        reader, R_BCTEST_FOR_PROGRESSINFO );    
    iEikProgressInfo->ConstructFromResourceL( reader ); 
    AssertTrueL( ETrue, KConstructFromResourceLComment );
    CleanupStack::PopAndDestroy();
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikProgressInfoCase::TestProtectedFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestEikProgressInfoCase::TestProtectedFunctionsL()    
    {
    CBCTestSubEikProgressInfo* subEikProgressInfo = 
        CBCTestSubEikProgressInfo::NewL();
    CleanupStack::PushL( subEikProgressInfo );
    
    CBufFlat* buf = CBufFlat::NewL( KTwoHundred );
    CleanupStack::PushL( buf );
    RBufWriteStream stream;
    stream.Open( *buf );
    subEikProgressInfo->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KWriteInternalStateL ); 
    stream.Close();
    CleanupStack::PopAndDestroy( buf );
    
    TBuf<KTen> stackBuf( KBuf );
    subEikProgressInfo->EvaluateText( stackBuf );     
    AssertTrueL( ETrue, KEvaluateText );     
    
    CleanupStack::PopAndDestroy( subEikProgressInfo );
    }






