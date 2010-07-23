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

#include <aknsoundinfo.h>
#include <s32mem.h>

#include "testsdksounds.h"

// CONSTANTS
const TInt KHBufSize = 1000;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSINewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSounds::TestSINewL( CStifItemParser& /*aItem*/ )
    {
    CAknSoundInfo *aknsoundinfo = CAknSoundInfo::NewL();
    CleanupStack::PushL( aknsoundinfo );
    STIF_ASSERT_NOT_NULL( aknsoundinfo );
    CleanupStack::PopAndDestroy( aknsoundinfo );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSIInternalizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSounds::TestSIInternalizeL( CStifItemParser& /*aItem*/ )
    {
    CAknSoundInfo *aknsoundinfo = CAknSoundInfo::NewL();
    CleanupStack::PushL( aknsoundinfo );

    HBufC8* buf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( buf );
    TPtr8 ptr = buf->Des();

    RDesReadStream readstream;
    readstream.Open( ptr );
    CleanupClosePushL( readstream );
    aknsoundinfo->InternalizeL( readstream );
    readstream.Close();

    CleanupStack::PopAndDestroy( 3);
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKSounds::TestSIExternalizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSounds::TestSIExternalizeL( CStifItemParser& /*aItem*/ )
    {
    CAknSoundInfo *aknsoundinfo = CAknSoundInfo::NewL();
    CleanupStack::PushL( aknsoundinfo );
    HBufC8* buf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( buf );
    TPtr8 ptr = buf->Des();
    RDesWriteStream writestream;
    CleanupClosePushL(writestream);
    writestream.Open( ptr );
    aknsoundinfo->ExternalizeL( writestream );
    writestream.CommitL();
    writestream.Close();
    CleanupStack::PopAndDestroy( 3 );
    return KErrNone;
    }

// End of file


