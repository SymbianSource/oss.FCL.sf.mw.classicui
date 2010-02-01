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
#include "bctestvcurs.h"
#include "eikcmobs.h"

// ----------------------------------------------------------------------------
// ctor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestVCursor::CBCTestVCursor()
    {
    }

// ----------------------------------------------------------------------------
// dtor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestVCursor::~CBCTestVCursor()
    {
    }

// ----------------------------------------------------------------------------
// symbian 2nd phase ctor.
// ----------------------------------------------------------------------------
//
void CBCTestVCursor::ConstructL()
    {
    BuildScriptL();
    }

// ----------------------------------------------------------------------------
// symbian NewL.
// ----------------------------------------------------------------------------
//
CBCTestVCursor* CBCTestVCursor::NewL()
    {
    CBCTestVCursor* self = new ( ELeave ) CBCTestVCursor();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// override the CBCTestCase::RunL, only response to the related command ID.
// ----------------------------------------------------------------------------
//
void CBCTestVCursor::RunL(int aCmd)
    {
    if(aCmd != EBCTestCmdVCursor) return;
    SetupL();
    TestL();
    TearDownL();
    }

// ----------------------------------------------------------------------------
// build the test scripts for this test case.
// ----------------------------------------------------------------------------
//
void CBCTestVCursor::BuildScriptL()
    {
    const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, 
        REP(Down, 4),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }

// ----------------------------------------------------------------------------
// test the volume setting page creation api.
// ----------------------------------------------------------------------------
//
void CBCTestVCursor::TestL()
    {
    CCoeEnv* env = CCoeEnv::Static();
    TEikVirtualCursor& ref = CEikonEnv::Static()->VirtualCursor();
    ref.SetCursorStateL( TEikVirtualCursor::EOn, *env);
    AssertTrueL( TEikVirtualCursor::EOn == ref.CursorState(*env),
        _L("Get State is equal to EOn"));
    }

// ----------------------------------------------------------------------------
// prepare for the test.
// ----------------------------------------------------------------------------
//
void CBCTestVCursor::SetupL()
    {
    }

// ----------------------------------------------------------------------------
// do release jobs.
// ----------------------------------------------------------------------------
//
void CBCTestVCursor::TearDownL()
    {
    }

//end of file
