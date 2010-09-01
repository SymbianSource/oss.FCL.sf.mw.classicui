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
* Description:  Test AknAppUi.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <documenthandler.h>

#include "testsdkappfw.h"
#include "testsdkappfwappui.h"

// CONSTANTS
const TInt KTextBuf = 16;

// -----------------------------------------------------------------------------
// simple test class
// -----------------------------------------------------------------------------
//
class CResolver : public CBase, public MAknAliasKeyCodeResolver
    {
    TInt GetAliasKeyCode( TUint& /*aCode*/, const TKeyEvent& /*aKeyEvent*/, 
        TEventCode /*aType*/ )
        {
        return KErrNone;
        }
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseCAknAppUiBaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseCAknAppUiBaseL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseCAknAppUiBaseL, "TestAppUiBaseCAknAppUiBaseL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseCAknAppUiBaseL );
    // Print to log file
    iLog->Log( KTestAppUiBaseCAknAppUiBaseL );

    CAknAppUiBase* appUiBase = new ( ELeave ) CAknAppUiBase;
    CleanupStack::PushL( appUiBase );
    appUiBase->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    STIF_ASSERT_NOT_NULL( appUiBase );
    CleanupStack::PopAndDestroy( appUiBase );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBBaseConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBBaseConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBBaseConstructL, "TestAppUiBBaseConstructL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBBaseConstructL );
    // Print to log file
    iLog->Log( KTestAppUiBBaseConstructL );

    CAknAppUiBase* appUiBase = new ( ELeave ) CAknAppUiBase;
    CleanupStack::PushL( appUiBase );
    appUiBase->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    CleanupStack::PopAndDestroy( appUiBase );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseHandleForegroundEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseHandleForegroundEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseHandleForegroundEventL, "TestAppUiBaseHandleForegroundEventL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseHandleForegroundEventL );
    // Print to log file
    iLog->Log( KTestAppUiBaseHandleForegroundEventL );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->CAknAppUiBase::HandleForegroundEventL( ETrue );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBConstructL, "TestAppUiBConstructL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBConstructL );
    // Print to log file
    iLog->Log( KTestAppUiBConstructL );

    CAknAppUiBase* appUiBase = new ( ELeave ) CAknAppUiBase;
    CleanupStack::PushL( appUiBase );
    CEikDocument* document = iEikonEnvPointer->EikAppUi()->Document();
    CleanupStack::PushL( document );
    appUiBase->SetDocument( document );
    appUiBase->ConstructL();
    CleanupStack::Pop( document );
    CleanupStack::PopAndDestroy( appUiBase );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseExitL( CStifItemParser& /*aItem*/ )
    {
    // !!! crash
    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseExitL, "TestAppUiBaseExitL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseExitL );
    // Print to log file
    iLog->Log( KTestAppUiBaseExitL );

    CAknAppUiBase* appUiBase = new ( ELeave ) CAknAppUiBase;
    CleanupStack::PushL( appUiBase );
    STIF_ASSERT_LEAVES( appUiBase->Exit() );
    CleanupStack::Pop( appUiBase );
    

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseSetFadedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseSetFadedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseSetFadedL, "TestAppUiBaseSetFadedL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseSetFadedL );
    // Print to log file
    iLog->Log( KTestAppUiBaseSetFadedL );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->SetFadedL( EFalse );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseHandleResourceChangeL, "TestAppUiBaseHandleResourceChangeL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseHandleResourceChangeL );
    // Print to log file
    iLog->Log( KTestAppUiBaseHandleResourceChangeL );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    TInt type = 2;
    aknAppUiBase->HandleResourceChangeL( type );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseApplicationRect
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseApplicationRect( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseApplicationRect, "TestAppUiBaseApplicationRect" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseApplicationRect );
    // Print to log file
    iLog->Log( KTestAppUiBaseApplicationRect );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->ApplicationRect();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBasePrepareToExit
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBasePrepareToExit( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBasePrepareToExit, "TestAppUiBasePrepareToExit" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBasePrepareToExit );
    // Print to log file
    iLog->Log( KTestAppUiBasePrepareToExit );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->PrepareToExit();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseIsFadedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseIsFadedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseIsFadedL, "TestAppUiBaseIsFadedL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseIsFadedL );
    // Print to log file
    iLog->Log( KTestAppUiBaseIsFadedL );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->SetFadedL( EFalse );
    aknAppUiBase->IsFaded();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseEventMonitor
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseEventMonitor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseIsFaded, "TestAppUiBaseIsFaded" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseIsFaded );
    // Print to log file
    iLog->Log( KTestAppUiBaseIsFaded );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    STIF_ASSERT_NOT_NULL( aknAppUiBase->EventMonitor() );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseKeySounds
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseKeySounds( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseKeySounds, "TestAppUiBaseKeySounds" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseKeySounds );
    // Print to log file
    iLog->Log( KTestAppUiBaseKeySounds );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    STIF_ASSERT_NOT_NULL( aknAppUiBase->KeySounds() );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseIsFullScreenAppL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseIsFullScreenAppL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseIsFullScreenAppL, "TestAppUiBaseIsFullScreenAppL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseIsFullScreenAppL );
    // Print to log file
    iLog->Log( KTestAppUiBaseIsFullScreenAppL );

    CAknAppUiBase* appUiBase = new ( ELeave ) CAknAppUiBase;
    CleanupStack::PushL( appUiBase );
    appUiBase->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    TBool flag = appUiBase->IsFullScreenApp();
    CleanupStack::PopAndDestroy( appUiBase );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseIsLayoutAwareApp
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseIsLayoutAwareApp( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseIsLayoutAwareApp, "TestAppUiBaseIsLayoutAwareApp" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseIsLayoutAwareApp );
    // Print to log file
    iLog->Log( KTestAppUiBaseIsLayoutAwareApp );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->SetLayoutAwareApp( ETrue );
    TBool flag = aknAppUiBase->IsLayoutAwareApp();
    STIF_ASSERT_TRUE( flag );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseSetLayoutAwareApp
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseSetLayoutAwareApp( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseSetLayoutAwareApp, "TestAppUiBaseSetLayoutAwareApp" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseSetLayoutAwareApp );
    // Print to log file
    iLog->Log( KTestAppUiBaseSetLayoutAwareApp );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->SetLayoutAwareApp( ETrue );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseIsForeground
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseIsForeground( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseIsForeground, "TestAppUiBaseIsForeground" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseIsForeground );
    // Print to log file
    iLog->Log( KTestAppUiBaseIsForeground );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->IsForeground();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseIsPartialForeground
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseIsPartialForeground( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseIsPartialForeground, "TestAppUiBaseIsPartialForeground" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseIsPartialForeground );
    // Print to log file
    iLog->Log( KTestAppUiBaseIsPartialForeground );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    TBool flag = aknAppUiBase->IsPartialForeground();
    STIF_ASSERT_FALSE( flag );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseOrientationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseOrientationL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseOrientationL, "TestAppUiBaseOrientationL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseOrientationL );
    // Print to log file
    iLog->Log( KTestAppUiBaseOrientationL );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );

    TInt flag = aknAppUiBase->Orientation();
    TInt defaultFlag = CAknAppUiBase::EAppUiOrientationUnspecified;
    STIF_ASSERT_EQUALS( flag, defaultFlag );

    aknAppUiBase->SetOrientationL( CAknAppUiBase::EAppUiOrientationPortrait );
    flag = aknAppUiBase->Orientation();
    TInt setFlag = CAknAppUiBase::EAppUiOrientationPortrait;
    STIF_ASSERT_EQUALS( flag, setFlag );

    aknAppUiBase->SetOrientationL( CAknAppUiBase::EAppUiOrientationLandscape );
    flag = aknAppUiBase->Orientation();
    setFlag = CAknAppUiBase::EAppUiOrientationLandscape;
    STIF_ASSERT_EQUALS( flag, setFlag );

    aknAppUiBase->SetOrientationL( CAknAppUiBase::EAppUiOrientationAutomatic );
    flag = aknAppUiBase->Orientation();
    STIF_ASSERT_EQUALS( flag, defaultFlag );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseOrientationCanBeChanged
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseOrientationCanBeChanged( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseOrientationCanBeChanged, "TestAppUiBaseOrientationCanBeChanged" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseOrientationCanBeChanged );
    // Print to log file
    iLog->Log( KTestAppUiBaseOrientationCanBeChanged );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->OrientationCanBeChanged();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseSetOrientationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseSetOrientationL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseSetOrientationL, "TestAppUiBaseSetOrientationL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseSetOrientationL );
    // Print to log file
    iLog->Log( KTestAppUiBaseSetOrientationL );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->SetOrientationL( CAknAppUiBase::EAppUiOrientationPortrait );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseLocalUiZoom
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseLocalUiZoom( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseLocalUiZoom, "TestAppUiBaseLocalUiZoom" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseLocalUiZoom );
    // Print to log file
    iLog->Log( KTestAppUiBaseLocalUiZoom );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->SetLocalUiZoom( EAknUiZoomAutomatic );
    TInt flag = aknAppUiBase->LocalUiZoom();
    TInt setFlag = EAknUiZoomAutomatic;
    STIF_ASSERT_EQUALS( flag, setFlag );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseSetLocalUiZoom
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseSetLocalUiZoom( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseSetLocalUiZoom, "TestAppUiBaseSetLocalUiZoom" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseSetLocalUiZoom );
    // Print to log file
    iLog->Log( KTestAppUiBaseSetLocalUiZoom );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->SetLocalUiZoom( EAknUiZoomNormal );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseApplyLayoutChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseApplyLayoutChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseApplyLayoutChangeL, "TestAppUiBaseApplyLayoutChangeL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseApplyLayoutChangeL );
    // Print to log file
    iLog->Log( KTestAppUiBaseApplyLayoutChangeL );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->ApplyLayoutChangeL( ETrue );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseSetKeyEventFlags
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseSetKeyEventFlags( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseSetKeyEventFlags, "TestAppUiBaseSetKeyEventFlags" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseSetKeyEventFlags );
    // Print to log file
    iLog->Log( KTestAppUiBaseSetKeyEventFlags );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->SetKeyEventFlags( CAknAppUiBase::EDisableSendKeyShort );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBasePointerEventModifier
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBasePointerEventModifier( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBasePointerEventModifier, "TestAppUiBasePointerEventModifier" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBasePointerEventModifier );
    // Print to log file
    iLog->Log( KTestAppUiBasePointerEventModifier );

    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    STIF_ASSERT_NOT_NULL( aknAppUiBase->PointerEventModifier() );
    aknAppUiBase->IsTouchCompatible();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseHandleScreenDeviceChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseHandleScreenDeviceChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseHandleScreenDeviceChangedL, "TestAppUiBaseHandleScreenDeviceChangedL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseHandleScreenDeviceChangedL );
    // Print to log file
    iLog->Log( KTestAppUiBaseHandleScreenDeviceChangedL );

    CTestSDKAppFWAppUiBase* aknAppUiBase = static_cast<CTestSDKAppFWAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->ProtectedHandleScreenDeviceChangedL();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseHandleApplicationSpecificEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseHandleApplicationSpecificEventL
    ( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseHandleApplicationSpecificEventL,
        "TestAppUiBaseHandleApplicationSpecificEventL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW,
        KTestAppUiBaseHandleApplicationSpecificEventL );
    // Print to log file
    iLog->Log( KTestAppUiBaseHandleApplicationSpecificEventL );

    CTestSDKAppFWAppUiBase* aknAppUiBase = static_cast<CTestSDKAppFWAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    TWsEvent event;

    aknAppUiBase->ProtectedHandleApplicationSpecificEventL
        ( KEikPartialForeground, event );

    aknAppUiBase->ProtectedHandleApplicationSpecificEventL
        ( KEikClearPartialForegroundState, event );

    aknAppUiBase->ProtectedHandleApplicationSpecificEventL
        ( KEikDynamicLayoutVariantSwitch, event );

    aknAppUiBase->ProtectedHandleApplicationSpecificEventL
        ( KEikHasBecomeCurrentAppUiWhileEmbeddedAppUiDeletes, event );

    aknAppUiBase->ProtectedHandleApplicationSpecificEventL
        ( KEikNotifyPostCreateEmbeddedL, event );

    aknAppUiBase->ProtectedHandleApplicationSpecificEventL
        ( KEikPostCoeAppUiConstructL, event );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseSetFullScreenAppL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseSetFullScreenAppL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseSetFullScreenAppL, "TestAppUiBaseSetFullScreenAppL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseSetFullScreenAppL );
    // Print to log file
    iLog->Log( KTestAppUiBaseSetFullScreenAppL );

    CTestSDKAppFWAppUiBase* testAppUi = new ( ELeave ) CTestSDKAppFWAppUiBase;
    CleanupStack::PushL( testAppUi );
    testAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    testAppUi->ProtectedSetFullScreenApp( EFalse );
    CleanupStack::PopAndDestroy( testAppUi );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseReplaceKeySoundsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseReplaceKeySoundsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseReplaceKeySoundsL, "TestAppUiBaseReplaceKeySoundsL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseReplaceKeySoundsL );
    // Print to log file
    iLog->Log( KTestAppUiBaseReplaceKeySoundsL );

    TInt uid = KErrNotFound;
    CTestSDKAppFWAppUiBase* aknAppUiBase = static_cast<CTestSDKAppFWAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->ProtectedReplaceKeySoundsL( uid );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseMopSupplyObject
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseMopSupplyObject( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseMopSupplyObject, "TestAppUiBaseMopSupplyObject" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseMopSupplyObject );
    // Print to log file
    iLog->Log( KTestAppUiBaseMopSupplyObject );

    CTestSDKAppFWAppUiBase* aknAppUiBase = static_cast<CTestSDKAppFWAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->ProtectedMopSupplyObject( MCoeControlStateObserver::ETypeId );
    aknAppUiBase->ProtectedMopSupplyObject( 0 );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiCAknAppUiBaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiBaseConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseBaseConstructL, "TestAppUiBaseBaseConstructL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiBaseBaseConstructL );
    // Print to log file
    iLog->Log( KTestAppUiBaseBaseConstructL );

    CAknAppUi* appUi = new ( ELeave ) CAknAppUi;
    CleanupStack::PushL( appUi );
    appUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    CleanupStack::PopAndDestroy( appUi );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiConstructL, "TestAppUiConstructL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiConstructL );
    // Print to log file
    iLog->Log( KTestAppUiConstructL );

    CAknAppUi* appUi = new ( ELeave ) CAknAppUi;
    CleanupStack::PushL( appUi );
    CEikDocument* document = iEikonEnvPointer->EikAppUi()->Document();
    CleanupStack::PushL( document );
    appUi->SetDocument( document );
    appUi->ConstructL();
    CleanupStack::Pop( document );
    CleanupStack::PopAndDestroy( appUi );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiStatusPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiStatusPaneL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiStatusPaneL, "TestAppUiStatusPaneL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiStatusPaneL );
    // Print to log file
    iLog->Log( KTestAppUiStatusPaneL );

    CAknAppUi* appUi = new ( ELeave ) CAknAppUi;
    CleanupStack::PushL( appUi );
    appUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    appUi->StatusPane();
    CleanupStack::PopAndDestroy( appUi );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiCba
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiCba( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiCba, "TestAppUiCba" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiCba );
    // Print to log file
    iLog->Log( KTestAppUiCba );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    CEikButtonGroupContainer* flag = appUi->Cba();
    STIF_ASSERT_NULL( appUi->Cba() );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiTouchPane
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiTouchPane( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiTouchPane, "TestAppUiTouchPane" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiTouchPane );
    // Print to log file
    iLog->Log( KTestAppUiTouchPane );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    STIF_ASSERT_NULL( appUi->TouchPane() );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiPopupToolbar
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiPopupToolbar( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiPopupToolbar, "TestAppUiPopupToolbar" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiPopupToolbar );
    // Print to log file
    iLog->Log( KTestAppUiPopupToolbar );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    TInt err = KErrNone;
    TRAP( err, appUi->PopupToolbar() );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiCurrentPopupToolbar
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiCurrentPopupToolbar( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiCurrentPopupToolbar, "TestAppUiCurrentPopupToolbar" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiCurrentPopupToolbar );
    // Print to log file
    iLog->Log( KTestAppUiCurrentPopupToolbar );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    STIF_ASSERT_NULL( appUi->CurrentPopupToolbar() );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiCurrentFixedToolbar
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiCurrentFixedToolbar( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiCurrentFixedToolbar, "TestAppUiCurrentFixedToolbar" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiCurrentFixedToolbar );
    // Print to log file
    iLog->Log( KTestAppUiCurrentFixedToolbar );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    TInt err = KErrNone;
    TRAP( err, appUi->CurrentFixedToolbar() );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiProcessCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiProcessCommandL, "TestAppUiProcessCommandL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiProcessCommandL );
    // Print to log file
    iLog->Log( KTestAppUiProcessCommandL );

    CAknAppUi* appUi = new ( ELeave ) CAknAppUi;
    CleanupStack::PushL( appUi );
    appUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    appUi->ProcessCommandL( 0 );
    CleanupStack::PopAndDestroy( appUi );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiHandleError
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiHandleError( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiHandleError, "TestAppUiHandleError" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiHandleError );
    // Print to log file
    iLog->Log( KTestAppUiHandleError );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    SExtendedError extendedError;
    TBuf<KTextBuf> errorText;
    TBuf<KTextBuf> contextText;
    TRAPD( err, appUi->HandleError( KErrNone, extendedError, errorText, contextText ) );
    STIF_ASSERT_EQUALS( err, KErrNone );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiRunAppShutterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiRunAppShutterL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiRunAppShutterL, "TestAppUiRunAppShutterL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiRunAppShutterL );
    // Print to log file
    iLog->Log( KTestAppUiRunAppShutterL );

    CAknAppUi* appUi = new ( ELeave ) CAknAppUi;
    CleanupStack::PushL( appUi );
    appUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    CDocumentHandler* dochandler = CDocumentHandler::NewL((CEikProcess*)CEikonEnv::Static()->Process());
    CleanupStack::PushL( dochandler );
    TDataType empty;
    dochandler->OpenFileEmbeddedL(_L("\\testframework\\tctestsdkappfw.cfg"), empty);
    appUi->RunAppShutter();
    CleanupStack::PopAndDestroy( dochandler );
    CleanupStack::PopAndDestroy( appUi );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiIsAppShutterRunning
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiIsAppShutterRunning( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiIsAppShutterRunning, "TestAppUiIsAppShutterRunning" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiIsAppShutterRunning );
    // Print to log file
    iLog->Log( KTestAppUiIsAppShutterRunning );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    TInt flag = appUi->IsAppShutterRunning();
    STIF_ASSERT_FALSE( flag );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiHandleViewDeactivation
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiHandleViewDeactivation( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiHandleViewDeactivation, "TestAppUiHandleViewDeactivation" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiHandleViewDeactivation );
    // Print to log file
    iLog->Log( KTestAppUiHandleViewDeactivation );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    TVwsViewId viewIdToBeDeactivated;
    TVwsViewId newlyActivatedViewId;
    appUi->HandleViewDeactivation( viewIdToBeDeactivated, newlyActivatedViewId );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiPrepareToExit
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiPrepareToExit( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiPrepareToExit, "TestAppUiPrepareToExit" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiPrepareToExit );
    // Print to log file
    iLog->Log( KTestAppUiPrepareToExit );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    appUi->PrepareToExit();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiHandleTouchPaneSizeChange
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiHandleTouchPaneSizeChange( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiHandleTouchPaneSizeChange, "TestAppUiHandleTouchPaneSizeChange" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiHandleTouchPaneSizeChange );
    // Print to log file
    iLog->Log( KTestAppUiHandleTouchPaneSizeChange );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    appUi->HandleTouchPaneSizeChange();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiHandleStatusPaneSizeChange
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiHandleStatusPaneSizeChange( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiHandleStatusPaneSizeChange, "TestAppUiHandleStatusPaneSizeChange" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiHandleStatusPaneSizeChange );
    // Print to log file
    iLog->Log( KTestAppUiHandleStatusPaneSizeChange );

    CTestSDKAppFWAppUi* appUi = static_cast<CTestSDKAppFWAppUi*>
        ( iEikonEnvPointer->EikAppUi() );
    appUi->ProtectedHandleStatusPaneSizeChange();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiHandleSystemEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiHandleSystemEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiHandleSystemEventL, "TestAppUiHandleSystemEventL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiHandleSystemEventL );
    // Print to log file
    iLog->Log( KTestAppUiHandleSystemEventL );

    CTestSDKAppFWAppUi* appUi = static_cast<CTestSDKAppFWAppUi*>
        ( iEikonEnvPointer->EikAppUi() );
    TWsEvent event;
    appUi->ProtectedHandleSystemEventL( event );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiReserved_MtsmPosition
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiReserved_MtsmPosition( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiReserved_MtsmPosition, "TestAppUiReserved_MtsmPosition" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiReserved_MtsmPosition );
    // Print to log file
    iLog->Log( KTestAppUiReserved_MtsmPosition );

    CTestSDKAppFWAppUi* appUi = static_cast<CTestSDKAppFWAppUi*>
        ( iEikonEnvPointer->EikAppUi() );
    appUi->ProtectedReserved_MtsmPosition();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiReserved_MtsmObject
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiReserved_MtsmObject( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiReserved_MtsmObject, "TestAppUiReserved_MtsmObject" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiReserved_MtsmObject );
    // Print to log file
    iLog->Log( KTestAppUiReserved_MtsmObject );

    CTestSDKAppFWAppUi* appUi = static_cast<CTestSDKAppFWAppUi*>
        ( iEikonEnvPointer->EikAppUi() );
    appUi->ProtectedReserved_MtsmObject();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiHandleForegroundEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiHandleForegroundEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiHandleForegroundEventL, "TestAppUiHandleForegroundEventL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiHandleForegroundEventL );
    // Print to log file
    iLog->Log( KTestAppUiHandleForegroundEventL );

    CTestSDKAppFWAppUi* appUi = static_cast<CTestSDKAppFWAppUi*>
        ( iEikonEnvPointer->EikAppUi() );
    appUi->ProtectedHandleForegroundEventL( ETrue );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiHandleWsEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiHandleWsEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiHandleWsEventL, "TestAppUiHandleWsEventL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiHandleWsEventL );
    // Print to log file
    iLog->Log( KTestAppUiHandleWsEventL );

    CTestSDKAppFWAppUi* appUi = static_cast<CTestSDKAppFWAppUi*>
        ( iEikonEnvPointer->EikAppUi() );
    TWsEvent event;
    CCoeControl* destination = NULL;
    appUi->ProtectedHandleWsEventL( event, destination );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiSetKeyBlockMode
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiSetKeyBlockMode( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiSetKeyBlockMode, "TestAppUiSetKeyBlockMode" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiSetKeyBlockMode );
    // Print to log file
    iLog->Log( KTestAppUiSetKeyBlockMode );

    CTestSDKAppFWAppUi* appUi = static_cast<CTestSDKAppFWAppUi*>
        ( iEikonEnvPointer->EikAppUi() );
    appUi->ProtectedSetKeyBlockMode( EDefaultBlockMode );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiHandleErrorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiHandleErrorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiHandleErrorL, "TestAppUiHandleErrorL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiHandleErrorL );
    // Print to log file
    iLog->Log( KTestAppUiHandleErrorL );

    CTestSDKAppFWAppUi* appUi = static_cast<CTestSDKAppFWAppUi*>
        ( iEikonEnvPointer->EikAppUi() );
    HBufC** errorDesc = NULL;
    STIF_ASSERT_LEAVES( appUi->ProtectedHandleErrorL( KErrNone, errorDesc ) );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiHideApplicationFromFSW
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiHideApplicationFromFSW( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiHideApplicationFromFSW, "TestAppUiHideApplicationFromFSW" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiHideApplicationFromFSW );
    // Print to log file
    iLog->Log( KTestAppUiHideApplicationFromFSW );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    appUi->HideApplicationFromFSW( ETrue );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiGetAliasKeyCodeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiGetAliasKeyCodeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiGetAliasKeyCodeL, "TestAppUiGetAliasKeyCodeL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiGetAliasKeyCodeL );
    // Print to log file
    iLog->Log( KTestAppUiGetAliasKeyCodeL );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    TWsEvent event;
    TKeyEvent key = *( event.Key() );
    appUi->GetAliasKeyCodeL( key.iCode, key, EEventKey );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiSetAliasKeyCodeResolverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiSetAliasKeyCodeResolverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiSetAliasKeyCodeResolverL, "TestAppUiSetAliasKeyCodeResolverL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiSetAliasKeyCodeResolverL );
    // Print to log file
    iLog->Log( KTestAppUiSetAliasKeyCodeResolverL );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    CResolver* resolver = new( ELeave ) CResolver;
    CleanupStack::PushL( resolver );
    appUi->SetAliasKeyCodeResolverL( resolver );
    CleanupStack::PopAndDestroy( resolver );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiCaptureKey
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiCaptureKey( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiCaptureKey, "TestAppUiCaptureKey" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiCaptureKey );
    // Print to log file
    iLog->Log( KTestAppUiCaptureKey );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    TInt flag = appUi->CaptureKey( EStdKeyYes, 0, 0 );
    STIF_ASSERT_TRUE( flag );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiCaptureKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiCaptureKeyL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiCaptureKeyL, "TestAppUiCaptureKeyL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiCaptureKeyL );
    // Print to log file
    iLog->Log( KTestAppUiCaptureKeyL );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    TInt32 handle = 0;
    appUi->CaptureKeyL( EStdKeyNo, 0, 0, handle );
    appUi->DisableNextKeySound( 0 );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiExitHidesInBackground
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiExitHidesInBackground( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiExitHidesInBackground, "TestAppUiExitHidesInBackground" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiExitHidesInBackground );
    // Print to log file
    iLog->Log( KTestAppUiExitHidesInBackground );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    TBool flag = appUi->ExitHidesInBackground();
    STIF_ASSERT_FALSE( flag );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiHideInBackground
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestAppUiHideInBackground( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiHideInBackground, "TestAppUiHideInBackground" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestAppUiHideInBackground );
    // Print to log file
    iLog->Log( KTestAppUiHideInBackground );

    CAknAppUi* appUi = static_cast<CAknAppUi*> ( iEikonEnvPointer->EikAppUi() );
    appUi->HideInBackground();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestAppUiBaseIsSingleClickCompatible
// -----------------------------------------------------------------------------
//
TInt 
CTestSDKAppFW::TestAppUiBaseIsSingleClickCompatible( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestAppUiBaseIsSingleClickCompatible,
          "TestAppUiBaseIsSingleClickCompatible" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, 
                           KTestAppUiBaseIsSingleClickCompatible );
    // Print to log file
    iLog->Log( KTestAppUiBaseIsSingleClickCompatible );
    
    CAknAppUiBase* aknAppUiBase = static_cast<CAknAppUiBase*>
        ( iEikonEnvPointer->EikAppUi() );
    aknAppUiBase->IsSingleClickCompatible();
    
    return KErrNone;
    }

//  [End of File]
