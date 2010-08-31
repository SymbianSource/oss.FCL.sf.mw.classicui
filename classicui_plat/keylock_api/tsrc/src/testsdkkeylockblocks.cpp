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
* Description:  Test AknKeyLock.h
*
*/

    
    
// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknkeylock.h>

#include "testsdkkeylock.h"
// ============================ MEMBER FUNCTIONS ===============================
    
// -----------------------------------------------------------------------------
// CTestSDKKeyLock::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKKeyLock::Delete() 
    {
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKKeyLock::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKKeyLock::RunMethodL( CStifItemParser& aItem ) 
    {
    static TStifFunctionInfo const KFunctions[] =
        {
        ENTRY( "TestKLConnectL", CTestSDKKeyLock::TestKLConnectL ),
        ENTRY( "TestKLEnableKeyLockL", CTestSDKKeyLock::TestKLEnableKeyLockL ),
        ENTRY( "TestKLDisableKeyLockL", CTestSDKKeyLock::TestKLDisableKeyLockL ),
        ENTRY( "TestKLIsKeyLockEnabledL", CTestSDKKeyLock::TestKLIsKeyLockEnabledL ),
        ENTRY( "TestKLEnableSoftNotificationsL", CTestSDKKeyLock::TestKLEnableSoftNotificationsL ),
        ENTRY( "TestKLOfferKeyLockL", CTestSDKKeyLock::TestKLOfferKeyLockL ),
        ENTRY( "TestKLCancelAllNotificationsL", CTestSDKKeyLock::TestKLCancelAllNotificationsL ),
        ENTRY( "TestKLDisableWithoutNoteL", CTestSDKKeyLock::TestKLDisableWithoutNoteL ),
        ENTRY( "TestKLEnableWithoutNoteL", CTestSDKKeyLock::TestKLEnableWithoutNoteL ),
        ENTRY( "TestKLEnableAutoLockEmulationL", CTestSDKKeyLock::TestKLEnableAutoLockEmulationL ),
        };
    
    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );
    
    return RunInternalL( KFunctions, count, aItem );
    
    }

// ============================ MEMBER FUNCTIONS ===============================

// =========================== CLASS RAKNKEYLOCK2 ==============================
// -----------------------------------------------------------------------------
// CTestSDKKeyLock::TestKLConnectL
// -----------------------------------------------------------------------------
TInt CTestSDKKeyLock::TestKLConnectL( CStifItemParser& /*aItem*/ )
    {
    RAknKeyLock connect;
    CleanupClosePushL( connect );
    STIF_ASSERT_EQUALS( KErrNone, connect.Connect() );
    
    STIF_ASSERT_NOT_NULL( &connect );
    
    connect.EnableKeyLock();
    STIF_ASSERT_TRUE( connect.IsKeyLockEnabled() );
    connect.DisableKeyLock();
    STIF_ASSERT_FALSE( connect.IsKeyLockEnabled() );
    
    CleanupStack::PopAndDestroy( &connect );
    
    return KErrNone;
    }

// =========================== CLASS RAKNKEYLOCK ===============================
// -----------------------------------------------------------------------------
// CTestSDKKeyLock::TestKLEnableKeyLockL 
// -----------------------------------------------------------------------------
TInt CTestSDKKeyLock::TestKLEnableKeyLockL( CStifItemParser& /*aItem*/ )
    {
    RAknKeyLock enablekeylock;
    CleanupClosePushL( enablekeylock );
    STIF_ASSERT_NOT_LEAVES( enablekeylock.Connect() );
    
    STIF_ASSERT_NOT_NULL( &enablekeylock );
    
    STIF_ASSERT_FALSE( enablekeylock.IsKeyLockEnabled() );
    enablekeylock.EnableKeyLock();
    STIF_ASSERT_TRUE( enablekeylock.IsKeyLockEnabled() );
    enablekeylock.DisableKeyLock();
    STIF_ASSERT_FALSE( enablekeylock.IsKeyLockEnabled() );
    
    CleanupStack::PopAndDestroy( &enablekeylock );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKKeyLock::TestKLDisableKeyLockL
// -----------------------------------------------------------------------------
TInt CTestSDKKeyLock::TestKLDisableKeyLockL( CStifItemParser& /*aItem*/ )
    {
    RAknKeyLock disablekeylock;
    CleanupClosePushL( disablekeylock );
    STIF_ASSERT_NOT_LEAVES( disablekeylock.Connect() );
    
    STIF_ASSERT_NOT_NULL( &disablekeylock );
    
    STIF_ASSERT_FALSE( disablekeylock.IsKeyLockEnabled() );
    disablekeylock.EnableKeyLock();
    STIF_ASSERT_TRUE( disablekeylock.IsKeyLockEnabled() );
    disablekeylock.DisableKeyLock();
    STIF_ASSERT_FALSE( disablekeylock.IsKeyLockEnabled() );
    
    CleanupStack::PopAndDestroy( &disablekeylock );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKKeyLock::TestKLIsKeyLockEnabledL
// -----------------------------------------------------------------------------
TInt CTestSDKKeyLock::TestKLIsKeyLockEnabledL( CStifItemParser& /*aItem*/ )
    {
    RAknKeyLock iskeylockenabled;
    CleanupClosePushL( iskeylockenabled );
    STIF_ASSERT_NOT_LEAVES( iskeylockenabled.Connect() );
    
    STIF_ASSERT_NOT_NULL( &iskeylockenabled );
    
    STIF_ASSERT_FALSE( iskeylockenabled.IsKeyLockEnabled() );
    iskeylockenabled.EnableKeyLock();
    STIF_ASSERT_TRUE( iskeylockenabled.IsKeyLockEnabled() );
    iskeylockenabled.DisableKeyLock();
    STIF_ASSERT_FALSE( iskeylockenabled.IsKeyLockEnabled() );
    
    CleanupStack::PopAndDestroy( &iskeylockenabled );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKKeyLock::TestKLEnableSoftNotificationsL
// -----------------------------------------------------------------------------
TInt CTestSDKKeyLock::TestKLEnableSoftNotificationsL( CStifItemParser& /*aItem*/ )
    {
    RAknKeyLock enablesoftnotifications;
    CleanupClosePushL( enablesoftnotifications );
    STIF_ASSERT_NOT_LEAVES( enablesoftnotifications.Connect() );
    
    STIF_ASSERT_NOT_NULL( &enablesoftnotifications );
    
    enablesoftnotifications.EnableKeyLock();
    STIF_ASSERT_TRUE( enablesoftnotifications.IsKeyLockEnabled() );
    
    TBool enable = EFalse;
    enablesoftnotifications.EnableSoftNotifications( enable );
    
    enablesoftnotifications.DisableKeyLock();
    STIF_ASSERT_FALSE( enablesoftnotifications.IsKeyLockEnabled() );
    
    CleanupStack::PopAndDestroy( &enablesoftnotifications );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKKeyLock::TestKLOfferKeyLockL
// -----------------------------------------------------------------------------
TInt CTestSDKKeyLock::TestKLOfferKeyLockL( CStifItemParser& /*aItem*/ )
    {
    RAknKeyLock offerkeylock;
    CleanupClosePushL( offerkeylock );
    STIF_ASSERT_NOT_LEAVES( offerkeylock.Connect() );
    
    STIF_ASSERT_NOT_NULL( &offerkeylock );
    
    offerkeylock.EnableKeyLock();
    STIF_ASSERT_TRUE( offerkeylock.IsKeyLockEnabled() );
    
    offerkeylock.OfferKeyLock();
    
    offerkeylock.DisableKeyLock();
    STIF_ASSERT_FALSE( offerkeylock.IsKeyLockEnabled() );
   
    CleanupStack::PopAndDestroy( &offerkeylock );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKKeyLock::TestKLCancelAllNotificationsL
// -----------------------------------------------------------------------------
TInt CTestSDKKeyLock::TestKLCancelAllNotificationsL( CStifItemParser& /*aItem*/ )
    {
    RAknKeyLock cancelallnotifications;
    CleanupClosePushL( cancelallnotifications );
    STIF_ASSERT_NOT_LEAVES( cancelallnotifications.Connect() );
    
    STIF_ASSERT_NOT_NULL( &cancelallnotifications );
    
    cancelallnotifications.EnableKeyLock();
    STIF_ASSERT_TRUE( cancelallnotifications.IsKeyLockEnabled() );
    
    TBool enable = ETrue;
    cancelallnotifications.EnableSoftNotifications( enable );
    
    cancelallnotifications.CancelAllNotifications();
    
    cancelallnotifications.DisableKeyLock();
    STIF_ASSERT_FALSE( cancelallnotifications.IsKeyLockEnabled() );
    
    CleanupStack::PopAndDestroy( &cancelallnotifications );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKKeyLock::TestKLEnableWithoutNoteL
// -----------------------------------------------------------------------------
TInt CTestSDKKeyLock::TestKLEnableWithoutNoteL( CStifItemParser& /*aItem*/ )
    {
    RAknKeyLock enablewithoutnote;
    CleanupClosePushL( enablewithoutnote );
    STIF_ASSERT_NOT_LEAVES( enablewithoutnote.Connect() );
    
    STIF_ASSERT_NOT_NULL( &enablewithoutnote );
    
    enablewithoutnote.EnableWithoutNote();
    STIF_ASSERT_TRUE( enablewithoutnote.IsKeyLockEnabled() );
    
    enablewithoutnote.DisableWithoutNote();
    STIF_ASSERT_FALSE( enablewithoutnote.IsKeyLockEnabled() );
    
    CleanupStack::PopAndDestroy( &enablewithoutnote );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKKeyLock::TestKLDisableWithoutNoteL
// -----------------------------------------------------------------------------
TInt CTestSDKKeyLock::TestKLDisableWithoutNoteL( CStifItemParser& /*aItem*/ )
    {
    RAknKeyLock disablewithoutnote;
    CleanupClosePushL( disablewithoutnote );
    STIF_ASSERT_NOT_LEAVES( disablewithoutnote.Connect() );
    
    STIF_ASSERT_NOT_NULL( &disablewithoutnote );
    
    disablewithoutnote.EnableWithoutNote();
    STIF_ASSERT_TRUE( disablewithoutnote.IsKeyLockEnabled() );
    
    disablewithoutnote.DisableWithoutNote();
    STIF_ASSERT_FALSE( disablewithoutnote.IsKeyLockEnabled() );
    
    CleanupStack::PopAndDestroy( &disablewithoutnote );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKKeyLock::TestKLEnableAutoLockEmulationL
// -----------------------------------------------------------------------------
TInt CTestSDKKeyLock::TestKLEnableAutoLockEmulationL( CStifItemParser& /*aItem*/ )
    {
    RAknKeyLock enableautolockemulation;
    CleanupClosePushL( enableautolockemulation );
    STIF_ASSERT_NOT_LEAVES( enableautolockemulation.Connect() );
    
    STIF_ASSERT_NOT_NULL( &enableautolockemulation );
    
    enableautolockemulation.EnableAutoLockEmulation();
    enableautolockemulation.EnableSoftNotifications( EFalse );

    CleanupStack::PopAndDestroy( &enableautolockemulation );
    
    return KErrNone;
    }

