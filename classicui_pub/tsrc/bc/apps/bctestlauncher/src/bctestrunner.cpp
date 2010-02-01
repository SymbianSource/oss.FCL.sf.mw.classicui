/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Base class for autotest application starters.
*
*/









#include <vwsdef.h>

#include "bctestrunner.h"
#include "bctestlauncher.hrh"
#include "bctestapplication.h"
#include "bctestconf.h"
#include "bcteststrmlogger.h"

using namespace BCTest;

// CONSTANTS
_LIT( KTimeFormat, "%:0%J%:1%T%:2%S%:3%+B" );

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CBCTestRunner::NewL
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestRunner* CBCTestRunner::NewL()
    {
    CBCTestRunner* self = new( ELeave ) CBCTestRunner();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestRunner::CBCTestRunner()
// C++ default constructor can NOT contain any code, that
// might leave.
// ---------------------------------------------------------------------------
//
CBCTestRunner::CBCTestRunner()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestRunner::~CBCTestRunner()
// ---------------------------------------------------------------------------
//
CBCTestRunner::~CBCTestRunner()
    {
    for ( TInt i = 0; i < iTestApps.Count(); i++ )
        {
        delete iTestApps[ i ];
        }
    iTestApps.Close();
    }

// ---------------------------------------------------------------------------
// CBCTestRunner::ConstructL
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CBCTestRunner::ConstructL( /*CAknAtLogWriter* aLogWriter*/ )
    {
    CBCTestConf* conf = CBCTestConf::NewLC();
    while( conf->NextL() )
        {
        AddTestAppL( CBCTestApplication::NewL(
            conf->Name(), conf->AppUID(), conf->ViewUID(),
            conf->Timeout(), conf->Version() ) );
        }
    CleanupStack::PopAndDestroy();  //conf
    }

// ---------------------------------------------------------------------------
// CBCTestRunner::AddTestAppL(CBCTestApplication* aApp)
// ---------------------------------------------------------------------------
//
void CBCTestRunner::AddTestAppL( CBCTestApplication* aApp )
    {
    iTestApps.AppendL( aApp );
    }

// ---------------------------------------------------------------------------
// CBCTestRunner::RunTestL( TInt aCommand )
// Starts test application and returns after test has been run
// ---------------------------------------------------------------------------
//
TBool CBCTestRunner::RunL( TInt aCommand )
    {
    _LIT( KTEST, "test runner run." );
    LOG << KTEST << EndLine << End;
    for ( TInt i = 0; i < iTestApps.Count(); ++i )
        {
        TRAPD( errno, iTestApps[ i ]->RunL( aCommand ) );
        switch( errno )
        {
        case KErrNotFound:
            {
            _LIT( KNOTFOUND, ": not found!" );
            LOG << iTestApps[ i ]->Name() << KNOTFOUND << EndLine << End;
            break;
            }
        case KErrTimedOut:
            {
            _LIT( KTIMEOUT, ": timeout." );
            LOG << iTestApps[ i ]->Name() << KTIMEOUT << EndLine << End;
            break;
            }
        default:
            break;
        }
    }
    return ETrue;
    }

// ---------------------------------------------------------------------------
// CBCTestRunner::CreateTimeStamp
// Creates time stamp.
// ---------------------------------------------------------------------------
//
void CBCTestRunner::CreateTimeStamp()
    {
    _LIT( KTIMEFAILED, "Getting time failed" );
    TTime homeTime;
    homeTime.HomeTime();
    TRAPD( err, homeTime.FormatL( iTempBuf, KTimeFormat ) );
    if ( err != KErrNone ) // FormatL failed
        iTempBuf = KTIMEFAILED();
    iBuf.Append( iTempBuf );
    }

// ---------------------------------------------------------------------------
// CBCTestRunner::Apps()
// ---------------------------------------------------------------------------
//
RArray<CBCTestApplication*>* CBCTestRunner::Apps()
    {
    return &iTestApps;
    }
