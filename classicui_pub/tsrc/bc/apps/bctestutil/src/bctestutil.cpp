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
* Description:         Test utility, the interface of test framework.
*
*/








#include <eikenv.h>

#include "bctestutil.h"
#include "bctestsuite.h"
#include "bctestlogger.h"
#include "bctestkeyfeeder.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestUtil::CBCTestUtil()    
    {
    }

// ---------------------------------------------------------------------------
// 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestUtil::ConstructL()
    {
    CEikonEnv* eikonEnv = CEikonEnv::Static();
        
    iLogger = CBCTestLogger::NewL( eikonEnv );    
    iTestSuite = new( ELeave ) CBCTestSuite( iLogger );
    iKeyFeeder = new( ELeave ) CBCTestKeyFeeder();
    iKeyFeeder->SetSuite( iTestSuite );
    
    iAutoTest.scripts = NULL;
    iAutoTest.countArray = NULL;
    iAutoTest.scriptCount = 0;
    }

// ---------------------------------------------------------------------------
// static ConstructL
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestUtil* CBCTestUtil::NewL()
    {
    CBCTestUtil* util = new( ELeave ) CBCTestUtil();    
    CleanupStack::PushL( util );
    util->ConstructL();
    CleanupStack::Pop( util );    
    return util;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestUtil::~CBCTestUtil()
    {        
    delete iKeyFeeder;            
    delete [] iAutoTest.countArray;
    delete [] iAutoTest.scripts;
    iAutoTest.nameArray.Close();
    delete iTestSuite;
    delete iLogger;
    }

// ---------------------------------------------------------------------------
// CBCTestUtil::RunL
// Execute automatic test.
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestUtil::RunL()
    {  
    iTestSuite->BuildScriptsL( &iAutoTest );    
    iKeyFeeder->StartAutoTestL( &iAutoTest );   
    }

// ---------------------------------------------------------------------------
// CBCTestUtil::RunL
// Execute a command specified by the command.
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestUtil::RunL( TInt aCmd )
    {
    iTestSuite->RunL( aCmd );
    }

// ---------------------------------------------------------------------------
// CBCTestUtil::AddTestCaseL
// Add test case to test suite.
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestUtil::AddTestCaseL( CBCTestCase* aTestCase, const TDesC& aName )
    {
    iTestSuite->AddTestCaseL( aTestCase, aName );
    }

