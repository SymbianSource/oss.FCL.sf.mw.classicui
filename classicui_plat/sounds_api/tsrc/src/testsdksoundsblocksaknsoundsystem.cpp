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

#include <aknsoundsystem.h> 
#include <aknsoundinfo.h>
#include <avkon.hrh>
#include <testsdksounds.rsg>

#include "testsdksounds.h"


const TInt KKeySoundUid = 100;
const TInt KResourceId = 10;
const TInt KSid = 20;

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSounds::TestSSNewL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    STIF_ASSERT_NOT_NULL( aknsoundsystem );
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSPushContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSounds::TestSSPushContextL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    aknsoundsystem->PushContextL( R_SKEY_LIST );
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSPopContext
// -----------------------------------------------------------------------------
//

TInt CTestSDKSounds::TestSSPopContextL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    aknsoundsystem->PushContextL(KResourceId);
    aknsoundsystem->PopContext();
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSPlaySoundWithTKeyEvent
// -----------------------------------------------------------------------------
//

TInt CTestSDKSounds::TestSSPlaySoundWithTKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem* aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    TKeyEvent keyevent;
    aknsoundsystem->PlaySound( keyevent );
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSPlaySoundWithTInt
// -----------------------------------------------------------------------------
//

TInt CTestSDKSounds::TestSSPlaySoundWithTIntL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    aknsoundsystem->PlaySound( KSid );
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSAddAppSoundInfoListL
// -----------------------------------------------------------------------------
//

TInt CTestSDKSounds::TestSSAddAppSoundInfoListL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    aknsoundsystem->AddAppSoundInfoListL( R_TESTSOUNDSINFO_LIST );
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSBringToForeground
// -----------------------------------------------------------------------------
//

TInt CTestSDKSounds::TestSSBringToForegroundL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    aknsoundsystem->BringToForeground();
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSStopSound
// -----------------------------------------------------------------------------
//

TInt CTestSDKSounds::TestSSStopSoundL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    aknsoundsystem->StopSound( KSid );
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSLockContext
// -----------------------------------------------------------------------------
//

TInt CTestSDKSounds::TestSSLockContextL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    aknsoundsystem->LockContext();
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSReleaseContext
// -----------------------------------------------------------------------------
//

TInt CTestSDKSounds::TestSSReleaseContextL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    aknsoundsystem->LockContext();
    aknsoundsystem->ReleaseContext();
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSRequestSoundInfoL
// -----------------------------------------------------------------------------
//

TInt CTestSDKSounds::TestSSRequestSoundInfoL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    CAknSoundInfo *aknsoundinfo = CAknSoundInfo::NewL();
    CleanupStack::PushL( aknsoundinfo );
    TInt sInfo = aknsoundsystem->RequestSoundInfoL( EAvkonSIDDefaultSound,
            *aknsoundinfo );
    CleanupStack::PopAndDestroy( aknsoundinfo );
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSSTopContext
// -----------------------------------------------------------------------------
//

TInt CTestSDKSounds::TestSSTopContextL( CStifItemParser& /*aItem*/ )
    {
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KKeySoundUid );
    CleanupStack::PushL( aknsoundsystem );
    aknsoundsystem->TopContext();
    CleanupStack::PopAndDestroy( aknsoundsystem );
    return KErrNone;
    }

// End of file


