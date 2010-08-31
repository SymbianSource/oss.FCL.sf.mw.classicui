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
* Description:  Test sounds_api 
 *
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdksounds.h"

// CONSTANTS

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdksounds::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKSounds::Delete()
    {

    }

// -----------------------------------------------------------------------------
// Ctestsdksounds::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSounds::RunMethodL(CStifItemParser& aItem)
    {
    static TStifFunctionInfo const KFunctions[] =
        {
        // First string is the function name used in TestScripter script file.
        ENTRY( "TestSINewL", CTestSDKSounds::TestSINewL ),
        ENTRY( "TestSIInternalizeL", CTestSDKSounds::TestSIInternalizeL ),
        ENTRY( "TestSIExternalizeL", CTestSDKSounds::TestSIExternalizeL ),
        ENTRY( "TestSSNewL", CTestSDKSounds::TestSSNewL ),
        ENTRY( "TestSSPushContextL", CTestSDKSounds::TestSSPushContextL ),
        ENTRY( "TestSSPopContextL", CTestSDKSounds::TestSSPopContextL ),
        ENTRY( "TestSSPlaySoundWithTKeyEventL", CTestSDKSounds::TestSSPlaySoundWithTKeyEventL ),
        ENTRY( "TestSSPlaySoundWithTIntL", CTestSDKSounds::TestSSPlaySoundWithTIntL ),
        ENTRY( "TestSSAddAppSoundInfoListL", CTestSDKSounds::TestSSAddAppSoundInfoListL ),
        ENTRY( "TestSSBringToForegroundL", CTestSDKSounds::TestSSBringToForegroundL ),
        ENTRY( "TestSSStopSoundL", CTestSDKSounds::TestSSStopSoundL ),
        ENTRY( "TestSSLockContextL", CTestSDKSounds::TestSSLockContextL ),
        ENTRY( "TestSSReleaseContextL", CTestSDKSounds::TestSSReleaseContextL ),
        ENTRY( "TestSSRequestSoundInfoL", CTestSDKSounds::TestSSRequestSoundInfoL ),
        ENTRY( "TestSSTopContextL", CTestSDKSounds::TestSSTopContextL ),
        // [test cases entries]
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//  [End of File]
