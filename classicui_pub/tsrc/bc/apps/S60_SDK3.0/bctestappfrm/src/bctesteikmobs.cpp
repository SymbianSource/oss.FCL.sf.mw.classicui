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







#include "bctestappfrm.hrh"
#include "streamlogger.h"
#include "bctesteikmobs.h"
#include "eikcmobs.h"

class CMonkObserver: public MEikCommandObserver, public CBase{
public:
    CMonkObserver(): MEikCommandObserver(){}
    void ProcessCommandL(TInt /*aCommandId*/){}
    CCoeControl* CreateCustomCommandControlL(TInt aControlType){
        return MEikCommandObserver::CreateCustomCommandControlL(aControlType);
    }
};

// ----------------------------------------------------------------------------
// ctor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestEikMObserver::CBCTestEikMObserver()
    {
    }

// ----------------------------------------------------------------------------
// dtor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestEikMObserver::~CBCTestEikMObserver()
    {
    }

// ----------------------------------------------------------------------------
// symbian 2nd phase ctor.
// ----------------------------------------------------------------------------
//
void CBCTestEikMObserver::ConstructL()
    {
    BuildScriptL();
    }

// ----------------------------------------------------------------------------
// symbian NewL.
// ----------------------------------------------------------------------------
//
CBCTestEikMObserver* CBCTestEikMObserver::NewL()
    {
    CBCTestEikMObserver* self = new ( ELeave ) CBCTestEikMObserver();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// override the CBCTestCase::RunL, only response to the related command ID.
// ----------------------------------------------------------------------------
//
void CBCTestEikMObserver::RunL(int aCmd)
    {
    if(aCmd != EBCTestCmdEikMObserver) return;
    SetupL();
    TestL();
    TearDownL();
    }

// ----------------------------------------------------------------------------
// build the test scripts for this test case.
// ----------------------------------------------------------------------------
//
void CBCTestEikMObserver::BuildScriptL()
    {
    const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, 
        REP(Down, 3),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }

// ----------------------------------------------------------------------------
// test the volume setting page creation api.
// ----------------------------------------------------------------------------
//
void CBCTestEikMObserver::TestL()
    {
    CMonkObserver* obs = new (ELeave) CMonkObserver;
    AssertNotNullL(obs, _L("MEikObserver ctor invoked"));

    AssertTrueL( NULL == obs->CreateCustomCommandControlL(0), 
        _L("MEikCommandObserver::CreateCustomCommandControlL() invoked") );

    delete obs;
    }

// ----------------------------------------------------------------------------
// prepare for the test.
// ----------------------------------------------------------------------------
//
void CBCTestEikMObserver::SetupL()
    {
    }

// ----------------------------------------------------------------------------
// do release jobs.
// ----------------------------------------------------------------------------
//
void CBCTestEikMObserver::TearDownL()
    {
    }

//end of file
