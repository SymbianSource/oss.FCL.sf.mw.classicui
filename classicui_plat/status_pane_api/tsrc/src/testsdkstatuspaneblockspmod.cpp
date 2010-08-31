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
* Description:  test eikspmod.h
*
*/

#include <eikspmod.h>
#include <aknutils.h>
#include <aknlayout.lag>
#include <eikspane.h>

#include "testsdkstatuspane.h"
#include "testsdkstatuspanepmod.h"
#include "testsdkstatuspaneext.h"
#include "testsdkstatuspanevisitor.h"

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPIIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPIIdL( CStifItemParser& /*aItem*/ )
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
// CTestSDKStatusPane::TestSPIAppOwnedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPIAppOwnedL( CStifItemParser& /*aItem*/ )
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
// CTestSDKStatusPane::TestSPIControlTypeIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPIControlTypeIdL( CStifItemParser& /*aItem*/ )
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
// CTestSDKStatusPane::TestSPIControlResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPIControlResourceIdL( CStifItemParser& /*aItem*/ )
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
// CTestSDKStatusPane::TestSPISetHiddenL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPISetHiddenL( CStifItemParser& /*aItem*/ )
    {
    //Constructor is not IMPORT_C or inline, no condition call function invoke it
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPIClearHiddenL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPIClearHiddenL( CStifItemParser& /*aItem*/ )
    {
    //Constructor is IMPORT_C or inline, no condition call function invoke it
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPIIsHiddenL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPIIsHiddenL( CStifItemParser& /*aItem*/ )
    {
    CEikStatusPaneBase* statuspane = CEikStatusPaneBase::Current();
    CleanupStack::PushL( statuspane );
    STIF_ASSERT_NOT_NULL( statuspane );
    
    statuspane->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::Pop( statuspane );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPLTIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPLTIdL( CStifItemParser& aItem )
    {
    return TestSPLAcceptL( aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPLTRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPLTRectL( CStifItemParser& aItem )
    {
    return TestPaneBasePaneRectL( aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPLFindL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPLFindL( CStifItemParser& aItem )
    {
    return TestPaneBasePaneRectL( aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPLAcceptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPLAcceptL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKStatusPaneEXT* statusPane = static_cast<CTestSDKStatusPaneEXT*>( CEikStatusPaneBase::Current() );
    CEikStatusPaneModelBase* model = statusPane->CreateModelL( R_AVKON_STATUS_PANE );
    CTestSDKStatusPanePmod* pmod = static_cast<CTestSDKStatusPanePmod*>( model );
    
    CEikStatusPaneLayout* layout = pmod->LoadLayoutL( R_AVKON_STATUS_PANE_LAYOUT_IDLE );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPLRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPLRectL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKStatusPaneEXT* statusPane = static_cast<CTestSDKStatusPaneEXT*>( CEikStatusPaneBase::Current() );
    CEikStatusPaneModelBase* model = statusPane->CreateModelL( R_AVKON_STATUS_PANE );
    CTestSDKStatusPanePmod* pmod = static_cast<CTestSDKStatusPanePmod*>( model );
    
    pmod->SetLayoutL( R_AVKON_STATUS_PANE_LAYOUT_USUAL );
    CEikStatusPaneLayout* layout = pmod->CurrentLayout();
    TRect rect = layout->Rect();
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPMBDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPMBDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKStatusPanePmod* pmod = new (ELeave) CTestSDKStatusPanePmod( *iEnv );
    CleanupStack::PushL( pmod );
    STIF_ASSERT_NOT_NULL( pmod );
    
    CleanupStack::Pop( pmod );
    delete pmod;
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPMBPaneInitsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPMBPaneInitsL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKStatusPanePmod* pmod = new (ELeave) CTestSDKStatusPanePmod( *iEnv );
    CleanupStack::PushL( pmod );
    STIF_ASSERT_NOT_NULL( pmod );
    
    pmod->BaseConstructL( R_AVKON_STATUS_PANE );
    CEikStatusPaneSetInit* init = pmod->PaneInits();
    
    CleanupStack::PopAndDestroy( pmod );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPMBSetLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPMBSetLayoutL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKStatusPaneEXT* statusPane = static_cast<CTestSDKStatusPaneEXT*>( CEikStatusPaneBase::Current() );
    CEikStatusPaneModelBase* model = statusPane->CreateModelL( R_AVKON_STATUS_PANE );
    CTestSDKStatusPanePmod* pmod = static_cast<CTestSDKStatusPanePmod*>( model );
    
    pmod->SetLayoutL( R_AVKON_STATUS_PANE_LAYOUT_USUAL );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPMBCurrentLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPMBCurrentLayoutL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKStatusPanePmod* pmod = new (ELeave) CTestSDKStatusPanePmod( *iEnv );
    CleanupStack::PushL( pmod );
    STIF_ASSERT_NOT_NULL( pmod );
    
    pmod->BaseConstructL( R_AVKON_STATUS_PANE );
    CEikStatusPaneLayout* layout = pmod->CurrentLayout();
    STIF_ASSERT_NULL( layout );
    
    CleanupStack::PopAndDestroy( pmod );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPMBCurrentLayoutResIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPMBCurrentLayoutResIdL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKStatusPanePmod* pmod = new (ELeave) CTestSDKStatusPanePmod( *iEnv );
    CleanupStack::PushL( pmod );
    STIF_ASSERT_NOT_NULL( pmod );
    
    pmod->BaseConstructL( R_AVKON_STATUS_PANE );
    TInt id = pmod->CurrentLayoutResId();
    
    CleanupStack::PopAndDestroy( pmod );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPMBCEikStatusPaneModelBaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPMBCEikStatusPaneModelBaseL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKStatusPanePmod* pmod = new (ELeave) CTestSDKStatusPanePmod( *iEnv );
    CleanupStack::PushL( pmod );
    STIF_ASSERT_NOT_NULL( pmod );
    
    CleanupStack::PopAndDestroy( pmod );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPMBBaseConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPMBBaseConstructL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKStatusPanePmod* pmod = new (ELeave) CTestSDKStatusPanePmod( *iEnv );
    CleanupStack::PushL( pmod );
    STIF_ASSERT_NOT_NULL( pmod );
    
    pmod->BaseConstructL( R_AVKON_STATUS_PANE );
    
    CleanupStack::PopAndDestroy( pmod );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPMBLoadLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPMBLoadLayoutL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKStatusPaneEXT* statusPane = static_cast<CTestSDKStatusPaneEXT*>( CEikStatusPaneBase::Current() );
    CEikStatusPaneModelBase* model = statusPane->CreateModelL( R_AVKON_STATUS_PANE );
    CTestSDKStatusPanePmod* pmod = static_cast<CTestSDKStatusPanePmod*>( model );
    
    CEikStatusPaneLayout* layout = pmod->LoadLayoutL( R_AVKON_STATUS_PANE_LAYOUT_IDLE );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::TestSPMBLegalIdsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::TestSPMBLegalIdsL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKStatusPanePmod* pmod = new (ELeave) CTestSDKStatusPanePmod( *iEnv );
    CleanupStack::PushL( pmod );
    STIF_ASSERT_NOT_NULL( pmod );
    
    pmod->BaseConstructL( R_AVKON_STATUS_PANE );
    CArrayFixFlat<TInt>* legalID = pmod->LegalIds();
    
    CleanupStack::PopAndDestroy( pmod );
    
    return KErrNone;

    }

// End of file

