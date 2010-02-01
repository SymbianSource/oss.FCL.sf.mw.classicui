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
* Description:  test eikspane.h
*
*/

#include <eikspane.h>
#include <avkon.rsg>
#include <akndef.h>
#include <aknindicatorcontainer.h>
#include <eikedwin.h>

#include "testsdkstatuspane.h"
#include "testsdkstatuspaneext.h"
#include "testsdkstatuspanepane.h"

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CEikStatusPane* statuspane = 
        CEikStatusPane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    CleanupStack::Pop( statuspane );
    delete statuspane;
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseCurrentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseCurrentL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseSetObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseSetObserverL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    CAknIndicatorContainer* observer = new (ELeave) CAknIndicatorContainer;
    CleanupStack::PushL( observer );
    
    statuspane->SetObserver( observer );
    
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseReduceRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseReduceRectL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    const TInt point = 30;
    TRect rect( TPoint( 0, 0 ), TPoint( point, point ) );
    
    statuspane->ReduceRect( rect );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseGetShapeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseGetShapeL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    RRegion region;
    
    statuspane->GetShapeL( region, ETrue, ETrue );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseSwitchLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseSwitchLayoutL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_IDLE );
    statuspane->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE );
    statuspane->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_EMPTY );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseMakeVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseMakeVisibleL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->MakeVisible( ETrue );
    STIF_ASSERT_TRUE( statuspane->IsVisible() );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseSetDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseSetDimmedL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->SetDimmed( ETrue );
    STIF_ASSERT_TRUE( statuspane->IsDimmed() );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseSetFadedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseSetFadedL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->SetFaded( EFalse );
    statuspane->IsFaded();
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseOkToChangeStatusPaneNowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseOkToChangeStatusPaneNowL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    TBool boolen = statuspane->OkToChangeStatusPaneNow();
    STIF_ASSERT_TRUE( boolen );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseSetFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseSetFlagsL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    TInt flag = 2;
    statuspane->SetFlags( flag );
    STIF_ASSERT_EQUALS( statuspane->Flags(), 2 );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseFlagsL( CStifItemParser& aItem )
    {
    return TestPaneBaseSetFlagsL( aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseIsVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseIsVisibleL( CStifItemParser& aItem )
    {
    return TestPaneBaseMakeVisibleL( aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseIsDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseIsDimmedL( CStifItemParser& aItem )
    {
    return TestPaneBaseSetDimmedL( aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseIsFadedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseIsFadedL( CStifItemParser& aItem )
    {
    return TestPaneBaseSetFadedL( aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBasePaneCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBasePaneCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    const TInt KPaneCtrlUid = 268458427;
    TPaneId paneId = TPaneId::Uid( KPaneCtrlUid );
    
    CEikStatusPaneBase::TPaneCapabilities capabilities = statuspane->PaneCapabilities( paneId );
    STIF_ASSERT_NOT_NULL( &capabilities );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBasePaneRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBasePaneRectL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    const TInt KPaneCtrlUid = 0;
    TPaneId paneId = TPaneId::Uid( KPaneCtrlUid );
    
    statuspane->PaneRectL( paneId );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseControlL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    const TInt KPaneCtrlUid = 268458427;
    TPaneId paneId = TPaneId::Uid( KPaneCtrlUid );
    
    CCoeControl* control = statuspane->ControlL( paneId );
    
    STIF_ASSERT_NOT_NULL( control );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseSwapControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseSwapControlL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    
    const TInt KPaneCtrlUid = 268458427;
    TPaneId paneId = TPaneId::Uid( KPaneCtrlUid );
    
    CCoeControl* control = statuspane->SwapControlL( paneId, edwin );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::Pop( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseContainerControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseContainerControlL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    const TInt KPaneCtrlUid = 268458427;
    TPaneId paneId = TPaneId::Uid( KPaneCtrlUid );
    
    CCoeControl* control = statuspane->ContainerControlL( paneId );
    STIF_ASSERT_NOT_NULL( control );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseWindowGroupL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseWindowGroupL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    RWindowGroup* windowGroup = statuspane->WindowGroup();
    STIF_ASSERT_NOT_NULL( windowGroup );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseDrawNowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseDrawNowL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->DrawNow();
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseCurrentLayoutResIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseCurrentLayoutResIdL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    TInt resId = statuspane->CurrentLayoutResId();
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseCEikStatusPaneBaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseCEikStatusPaneBaseL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CTestSDKStatusPaneEXT* statusPane = new (ELeave) CTestSDKStatusPaneEXT( *iEnv, &group );
    CleanupStack::PushL( statusPane );
    
    STIF_ASSERT_NOT_NULL( statusPane );
    
    CleanupStack::PopAndDestroy( statusPane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseBaseConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseBaseConstructL( CStifItemParser& aItem )
    {
    return TestPaneBaseDeconstructorL( aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseRectL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CTestSDKStatusPanePane* statuspane = 
        CTestSDKStatusPanePane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    TRect rect = statuspane->Rect();
    
    CleanupStack::PopAndDestroy( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseDisableClearerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseDisableClearerL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CTestSDKStatusPanePane* statuspane = 
        CTestSDKStatusPanePane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->DisableClearer( ETrue );
    
    CleanupStack::PopAndDestroy( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseCommonPrepareForAppExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseCommonPrepareForAppExitL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CTestSDKStatusPanePane* statuspane = 
        CTestSDKStatusPanePane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->CommonPrepareForAppExit();
    
    CleanupStack::PopAndDestroy( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseTPaneCapIsPresentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseTPaneCapIsPresentL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    const TInt KPaneCtrlUid = 268458427;
    TPaneId paneId = TPaneId::Uid( KPaneCtrlUid );
    
    CEikStatusPaneBase::TPaneCapabilities capabilities = statuspane->PaneCapabilities( paneId );
    STIF_ASSERT_NOT_NULL( &capabilities );
    
    TBool present = capabilities.IsPresent();
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseTPaneCapIsAppOwnedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseTPaneCapIsAppOwnedL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    const TInt KPaneCtrlUid = 268458427;
    TPaneId paneId = TPaneId::Uid( KPaneCtrlUid );
    
    CEikStatusPaneBase::TPaneCapabilities capabilities = statuspane->PaneCapabilities( paneId );
    STIF_ASSERT_NOT_NULL( &capabilities );
    
    TBool present = capabilities.IsAppOwned();
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneBaseTPaneCapIsInCurrentLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneBaseTPaneCapIsInCurrentLayoutL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    const TInt KPaneCtrlUid = 268458427;
    TPaneId paneId = TPaneId::Uid( KPaneCtrlUid );
    
    CEikStatusPaneBase::TPaneCapabilities capabilities = statuspane->PaneCapabilities( paneId );
    STIF_ASSERT_NOT_NULL( &capabilities );
    
    TBool present = capabilities.IsInCurrentLayout();
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneNewL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CEikStatusPane* statuspane = 
        CEikStatusPane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    CleanupStack::PopAndDestroy( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneDeconstructorL( CStifItemParser& aItem )
    {
    return TestPaneNewL( aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneApplyCurrentSettingsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneApplyCurrentSettingsL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CEikStatusPane* statuspane = 
        CEikStatusPane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->ApplyCurrentSettingsL();
    
    CleanupStack::PopAndDestroy( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPanePrepareForAppExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPanePrepareForAppExitL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CEikStatusPane* statuspane = 
        CEikStatusPane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->PrepareForAppExit();
    
    CleanupStack::PopAndDestroy( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneMakeVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneMakeVisibleL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CEikStatusPane* statuspane = 
        CEikStatusPane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->MakeVisible( ETrue );
    
    CleanupStack::PopAndDestroy( statuspane );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneSetDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneSetDimmedL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CEikStatusPane* statuspane = 
        CEikStatusPane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->SetDimmed( ETrue );
    
    CleanupStack::PopAndDestroy( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneSetFadedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneSetFadedL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CEikStatusPane* statuspane = 
        CEikStatusPane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->SetFaded( ETrue );
    
    CleanupStack::PopAndDestroy( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CEikStatusPane* statuspane = 
        CEikStatusPane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::PopAndDestroy( statuspane );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestPaneOkToChangeStatusPaneNowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestPaneOkToChangeStatusPaneNowL( CStifItemParser& /*aItem*/ )
    {
    RWindowGroup& group = iEnv->RootWin();
    CEikStatusPane* statuspane = 
        CEikStatusPane::NewL( *iEnv, &group, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->OkToChangeStatusPaneNow();
    
    CleanupStack::PopAndDestroy( statuspane );
    
    return KErrNone;
    
    }
// End of file

