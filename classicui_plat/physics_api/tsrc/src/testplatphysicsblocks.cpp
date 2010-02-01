/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: Test aknphysics.h
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testplatphysics.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestPlatPhysics::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestPlatPhysics::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        // [test cases entries]
        //aknphysics.h
        ENTRY( "TestCAknPhysicsNewL", CTestPlatPhysics::TestCAknPhysicsNewL ), 
        ENTRY( "TestCAknPhysicsInitPhysicsL", CTestPlatPhysics::TestCAknPhysicsInitPhysicsL ), 
        ENTRY( "TestCAknPhysicsStartPhysicsL", CTestPlatPhysics::TestCAknPhysicsStartPhysicsL ), 
        ENTRY( "TestCAknPhysicsStopPhysicsL", CTestPlatPhysics::TestCAknPhysicsStopPhysicsL ), 
        ENTRY( "TestCAknPhysicsOngoingPhysicsActionL", CTestPlatPhysics::TestCAknPhysicsOngoingPhysicsActionL ), 
        ENTRY( "TestCAknPhysicsRegisterPanningPositionL", CTestPlatPhysics::TestCAknPhysicsRegisterPanningPositionL ), 
        ENTRY( "TestCAknPhysicsSetFrictionL", CTestPlatPhysics::TestCAknPhysicsSetFrictionL ), 
        ENTRY( "TestCAknPhysicsResetFrictionL", CTestPlatPhysics::TestCAknPhysicsResetFrictionL ), 
        ENTRY( "TestCAknPhysicsHighlightTimeoutL", CTestPlatPhysics::TestCAknPhysicsHighlightTimeoutL ), 
        ENTRY( "TestCAknPhysicsDragThresholdL", CTestPlatPhysics::TestCAknPhysicsDragThresholdL ), 
        ENTRY( "TestCAknPhysicsFeatureEnabledL", CTestPlatPhysics::TestCAknPhysicsFeatureEnabledL ), 
        ENTRY( "TestCAknPhysicsEventHandlingAllowedL", CTestPlatPhysics::TestCAknPhysicsEventHandlingAllowedL ), 
        ENTRY( "TestCAknPhysicsUpdateViewWindowControlL", CTestPlatPhysics::TestCAknPhysicsUpdateViewWindowControlL ), 
        ENTRY( "TestCAknPhysicsSuspendPhysicsL", CTestPlatPhysics::TestCAknPhysicsSuspendPhysicsL ), 
        ENTRY( "TestCAknPhysicsResumePhysicsL", CTestPlatPhysics::TestCAknPhysicsResumePhysicsL ), 

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

