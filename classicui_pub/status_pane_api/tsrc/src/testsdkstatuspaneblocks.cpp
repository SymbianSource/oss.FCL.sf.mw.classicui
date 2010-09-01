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
* Description:  test eikspmod.h eikspane.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkstatuspane.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKStatusPane::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKStatusPane::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        ENTRY( "TestPaneBaseDeconstructorL", CTestSDKStatusPane::TestPaneBaseDeconstructorL ),
        ENTRY( "TestPaneBaseCurrentL", CTestSDKStatusPane::TestPaneBaseCurrentL ),
        ENTRY( "TestPaneBaseSetObserverL", CTestSDKStatusPane::TestPaneBaseSetObserverL ),
        ENTRY( "TestPaneBaseReduceRectL", CTestSDKStatusPane::TestPaneBaseReduceRectL ),
        ENTRY( "TestPaneBaseGetShapeL", CTestSDKStatusPane::TestPaneBaseGetShapeL ),
        ENTRY( "TestPaneBaseSwitchLayoutL", CTestSDKStatusPane::TestPaneBaseSwitchLayoutL ),
        ENTRY( "TestPaneBaseMakeVisibleL", CTestSDKStatusPane::TestPaneBaseMakeVisibleL ),
        ENTRY( "TestPaneBaseCurrentL", CTestSDKStatusPane::TestPaneBaseCurrentL ),
        ENTRY( "TestPaneBaseSetDimmedL", CTestSDKStatusPane::TestPaneBaseSetDimmedL ),
        ENTRY( "TestPaneBaseSetFadedL", CTestSDKStatusPane::TestPaneBaseSetFadedL ),
        ENTRY( "TestPaneBaseHandleResourceChangeL", 
                CTestSDKStatusPane::TestPaneBaseHandleResourceChangeL ),
        ENTRY( "TestPaneBaseOkToChangeStatusPaneNowL", 
                CTestSDKStatusPane::TestPaneBaseOkToChangeStatusPaneNowL ),
        ENTRY( "TestPaneBaseSetFlagsL", CTestSDKStatusPane::TestPaneBaseSetFlagsL ),
        ENTRY( "TestPaneBaseFlagsL", CTestSDKStatusPane::TestPaneBaseFlagsL ),
        ENTRY( "TestPaneBaseIsVisibleL", CTestSDKStatusPane::TestPaneBaseIsVisibleL ),
        ENTRY( "TestPaneBaseIsDimmedL", CTestSDKStatusPane::TestPaneBaseIsDimmedL ),        
        ENTRY( "TestPaneBaseBaseConstructL", 
                CTestSDKStatusPane::TestPaneBaseBaseConstructL ),
        ENTRY( "TestPaneBaseIsFadedL", CTestSDKStatusPane::TestPaneBaseIsFadedL ),
        ENTRY( "TestPaneBasePaneCapabilitiesL", 
                CTestSDKStatusPane::TestPaneBasePaneCapabilitiesL ),
        ENTRY( "TestPaneBasePaneRectL", CTestSDKStatusPane::TestPaneBasePaneRectL ),
        ENTRY( "TestPaneBaseControlL", CTestSDKStatusPane::TestPaneBaseControlL ),
        ENTRY( "TestPaneBaseSwapControlL", CTestSDKStatusPane::TestPaneBaseSwapControlL ),
        ENTRY( "TestPaneBaseContainerControlL", 
                CTestSDKStatusPane::TestPaneBaseContainerControlL ),
        ENTRY( "TestPaneBaseWindowGroupL", CTestSDKStatusPane::TestPaneBaseWindowGroupL ),
        ENTRY( "TestPaneBaseDrawNowL", CTestSDKStatusPane::TestPaneBaseDrawNowL ),
        ENTRY( "TestPaneBaseCurrentLayoutResIdL", 
                CTestSDKStatusPane::TestPaneBaseCurrentLayoutResIdL ),
        ENTRY( "TestPaneBaseCEikStatusPaneBaseL", 
                CTestSDKStatusPane::TestPaneBaseCEikStatusPaneBaseL ),
                
        ENTRY( "TestPaneBaseBaseConstructL", CTestSDKStatusPane::TestPaneBaseBaseConstructL ),
        ENTRY( "TestPaneBaseRectL", CTestSDKStatusPane::TestPaneBaseRectL ),
        ENTRY( "TestPaneBaseDisableClearerL", 
                CTestSDKStatusPane::TestPaneBaseDisableClearerL ),
        ENTRY( "TestPaneBaseCommonPrepareForAppExitL", 
                CTestSDKStatusPane::TestPaneBaseCommonPrepareForAppExitL ),
        ENTRY( "TestPaneBaseTPaneCapIsPresentL", 
                CTestSDKStatusPane::TestPaneBaseTPaneCapIsPresentL ),
        ENTRY( "TestPaneBaseTPaneCapIsAppOwnedL", 
                CTestSDKStatusPane::TestPaneBaseTPaneCapIsAppOwnedL ),
        ENTRY( "TestPaneBaseTPaneCapIsInCurrentLayoutL", 
                CTestSDKStatusPane::TestPaneBaseTPaneCapIsInCurrentLayoutL ),
                
        ENTRY( "TestPaneNewL", CTestSDKStatusPane::TestPaneNewL ),
        ENTRY( "TestPaneDeconstructorL", CTestSDKStatusPane::TestPaneDeconstructorL ),
        ENTRY( "TestPaneApplyCurrentSettingsL", 
                CTestSDKStatusPane::TestPaneApplyCurrentSettingsL ),
        ENTRY( "TestPanePrepareForAppExitL", 
                CTestSDKStatusPane::TestPanePrepareForAppExitL ),
        ENTRY( "TestPaneMakeVisibleL", CTestSDKStatusPane::TestPaneMakeVisibleL ),
        ENTRY( "TestPaneSetDimmedL", CTestSDKStatusPane::TestPaneSetDimmedL ),
        ENTRY( "TestPaneSetFadedL", CTestSDKStatusPane::TestPaneSetFadedL ),
        ENTRY( "TestPaneHandleResourceChangeL", 
                CTestSDKStatusPane::TestPaneHandleResourceChangeL ),
        ENTRY( "TestPaneOkToChangeStatusPaneNowL", 
                CTestSDKStatusPane::TestPaneOkToChangeStatusPaneNowL ),

        ENTRY( "TestSPIIdL", CTestSDKStatusPane::TestSPIIdL ),
        ENTRY( "TestSPIAppOwnedL", CTestSDKStatusPane::TestSPIAppOwnedL ),
        ENTRY( "TestSPIControlTypeIdL", CTestSDKStatusPane::TestSPIControlTypeIdL ),
        ENTRY( "TestSPIControlResourceIdL", CTestSDKStatusPane::TestSPIControlResourceIdL ),
        ENTRY( "TestSPISetHiddenL", CTestSDKStatusPane::TestSPISetHiddenL ),
        ENTRY( "TestSPIClearHiddenL", CTestSDKStatusPane::TestSPIClearHiddenL ),
        ENTRY( "TestSPIIsHiddenL", CTestSDKStatusPane::TestSPIIsHiddenL ),
        ENTRY( "TestSPLTIdL", CTestSDKStatusPane::TestSPLTIdL ),
        ENTRY( "TestSPLTRectL", CTestSDKStatusPane::TestSPLTRectL ),
        ENTRY( "TestSPLFindL", CTestSDKStatusPane::TestSPLFindL ),
        ENTRY( "TestSPLAcceptL", CTestSDKStatusPane::TestSPLAcceptL ),
        ENTRY( "TestSPLRectL", CTestSDKStatusPane::TestSPLRectL ),
        ENTRY( "TestSPMBDeconstructorL", CTestSDKStatusPane::TestSPMBDeconstructorL ),
        ENTRY( "TestSPMBPaneInitsL", CTestSDKStatusPane::TestSPMBPaneInitsL ),
        ENTRY( "TestSPMBSetLayoutL", CTestSDKStatusPane::TestSPMBSetLayoutL ),
        ENTRY( "TestSPMBCurrentLayoutL", CTestSDKStatusPane::TestSPMBCurrentLayoutL ),
        ENTRY( "TestSPMBCurrentLayoutResIdL", CTestSDKStatusPane::TestSPMBCurrentLayoutResIdL ),
        ENTRY( "TestSPMBCEikStatusPaneModelBaseL", CTestSDKStatusPane::TestSPMBCEikStatusPaneModelBaseL ),
        ENTRY( "TestSPMBBaseConstructL", CTestSDKStatusPane::TestSPMBBaseConstructL ),
        ENTRY( "TestSPMBLoadLayoutL", CTestSDKStatusPane::TestSPMBLoadLayoutL ),
        ENTRY( "TestSPMBLegalIdsL", CTestSDKStatusPane::TestSPMBLegalIdsL ),

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }



//  [End of File]

