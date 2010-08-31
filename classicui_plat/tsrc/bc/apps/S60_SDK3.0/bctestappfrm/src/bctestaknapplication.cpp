/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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







#include <aknserverapp.h>
#include <aknapp.h>
#include <eikenv.h>
#include <eikappui.h>
#include "bctestaknapplication.h"
#include "bctestappfrm.hrh"
#include "streamlogger.h"

// ----------------------------------------------------------------------------
// ctor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestAknApplication::CBCTestAknApplication()
    {
    }

// ----------------------------------------------------------------------------
// dtor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestAknApplication::~CBCTestAknApplication()
    {
    }

// ----------------------------------------------------------------------------
// symbian 2nd phase ctor.
// ----------------------------------------------------------------------------
//
void CBCTestAknApplication::ConstructL()
    {
    BuildScriptL();
    }

// ----------------------------------------------------------------------------
// symbian NewL.
// ----------------------------------------------------------------------------
//
CBCTestAknApplication* CBCTestAknApplication::NewL()
    {
    CBCTestAknApplication* self = new ( ELeave ) CBCTestAknApplication();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// override the CBCTestCase::RunL, only response to the related command ID.
// ----------------------------------------------------------------------------
//
void CBCTestAknApplication::RunL(int aCmd)
    {
    if(aCmd != EBCTestCmdApplication) return;
    SetupL();
    TestL();
    TearDownL();
    }

// ----------------------------------------------------------------------------
// build the test scripts for this test case.
// ----------------------------------------------------------------------------
//
void CBCTestAknApplication::BuildScriptL()
    {
    const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, 
        //REP(Down, n),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }

void CBCTestAknApplication::TestIniFileL(CAknApplication* aApp, RFs& aFs)
{
	// In fact OpenIniFileLC do nothing with clean up stack, but leave with
	// not supported error.
	aApp->OpenIniFileLC(aFs);
}

// ----------------------------------------------------------------------------
// test the volume setting page creation api.
// ----------------------------------------------------------------------------
//
void CBCTestAknApplication::TestL()
    {
    CAknApplication* app = static_cast<CAknApplication*>(CEikonEnv::Static()->EikAppUi()->Application());

    //app->PreDocConstructL();    //TO DO: need a release, but dono
    //AssertTrueL(ETrue, _L("CAknApplication::PreDocConstructL() invoked."));

    RFs& fs = CEikonEnv::Static()->FsSession();
    TRAPD( err, TestIniFileL(app, fs));
    if(err == KErrNotSupported){
        AssertTrueL(ETrue, _L("CAknApplication::OpenIniFileLC () isn't supported in S60"));
    }

    CApaAppServer* server = NULL;
    app->NewAppServerL(server);
    CleanupStack::PushL(server);
    AssertNotNullL(server, _L("CAknApplication::NewAppServerL() invoked."));
    CleanupStack::PopAndDestroy(server);    //server
    }

// ----------------------------------------------------------------------------
// prepare for the test.
// ----------------------------------------------------------------------------
//
void CBCTestAknApplication::SetupL()
    {
    }

// ----------------------------------------------------------------------------
// do release jobs.
// ----------------------------------------------------------------------------
//
void CBCTestAknApplication::TearDownL()
    {
    }

//end of file
