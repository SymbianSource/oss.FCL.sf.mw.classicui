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
* Description:  No test functions implement
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkbuttons.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKButtons::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKButtons::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestMenuBtConstructorL", CTestSDKButtons::TestMenuBtConstructorL ),
        ENTRY( "TestMenuBtConstructFromResourceL", CTestSDKButtons::TestMenuBtConstructFromResourceL ),
        ENTRY( "TestMenuBtLaunchPopupMenuL", CTestSDKButtons::TestMenuBtLaunchPopupMenuL ),
        ENTRY( "TestMenuBtSetMenuPaneIdL", CTestSDKButtons::TestMenuBtSetMenuPaneIdL ),
        ENTRY( "TestMenuBtAnimateL", CTestSDKButtons::TestMenuBtAnimateL ),
        ENTRY( "TestMenuBtWriteInternalStateL", CTestSDKButtons::TestMenuBtWriteInternalStateL ),
        ENTRY( "TestLabelBtConstructorL", CTestSDKButtons::TestLabelBtConstructorL ),
        ENTRY( "TestLabelBtConstructL", CTestSDKButtons::TestLabelBtConstructL ),
        ENTRY( "TestLabelBtConstructFromResourceL", CTestSDKButtons::TestLabelBtConstructFromResourceL ),
        ENTRY( "TestLabelBtButtonoL", CTestSDKButtons::TestLabelBtButtonoL ),
        ENTRY( "TestLabelBtLabelL", CTestSDKButtons::TestLabelBtLabelL ),
        ENTRY( "TestLabelBtHotKeyFunctionsL", CTestSDKButtons::TestLabelBtHotKeyFunctionsL ),
        ENTRY( "TestLabelBtAnimateL", CTestSDKButtons::TestLabelBtAnimateL ),
        ENTRY( "TestLabelBtOfferKeyEvnetL", CTestSDKButtons::TestLabelBtOfferKeyEvnetL ),
        ENTRY( "TestLabelBtSetContainerWindowL", CTestSDKButtons::TestLabelBtSetContainerWindowL ),
        ENTRY( "TestLabelBtMiniSizeL", CTestSDKButtons::TestLabelBtMiniSizeL ),
        ENTRY( "TestLabelBtSetdimL", CTestSDKButtons::TestLabelBtSetdimL ),
        ENTRY( "TestLabelBtHandleResourceChangeL", CTestSDKButtons::TestLabelBtHandleResourceChangeL ),
        ENTRY( "TestLabelBtInputCapabilitiesL", CTestSDKButtons::TestLabelBtInputCapabilitiesL ),
        ENTRY( "TestLabelBtGetColorUseListL", CTestSDKButtons::TestLabelBtGetColorUseListL ),
        ENTRY( "TestLabelBtWriteInternalStateL", CTestSDKButtons::TestLabelBtWriteInternalStateL ),
        ENTRY( "TestCEikCmdBtBaseConstrutorL", CTestSDKButtons::TestCEikCmdBtBaseConstrutorL ),
        ENTRY( "TestCEikCmdBtBaseSetButtonLayoutL", CTestSDKButtons::TestCEikCmdBtBaseSetButtonLayoutL ),
        ENTRY( "TestCEikCmdBtBaseSetExcessSpaceL", CTestSDKButtons::TestCEikCmdBtBaseSetExcessSpaceL ),
        ENTRY( "TestCEikCmdBtBaseSetDisplayContentL", CTestSDKButtons::TestCEikCmdBtBaseSetDisplayContentL ),
        ENTRY( "TestCEikCmdBtBaseLayoutComponentsL", CTestSDKButtons::TestCEikCmdBtBaseLayoutComponentsL ),
        ENTRY( "TestCEikCmdBtBaseStartConstructFromResourceL", CTestSDKButtons::TestCEikCmdBtBaseStartConstructFromResourceL ),
        ENTRY( "TestCEikCmdBtBaseConstructLabelAndImageFromResourceL", CTestSDKButtons::TestCEikCmdBtBaseConstructLabelAndImageFromResourceL ),
        ENTRY( "TestCEikCmdBtBaseUpdateComponentAlignmentL", CTestSDKButtons::TestCEikCmdBtBaseUpdateComponentAlignmentL ),
        ENTRY( "TestCEikCmdBtBaseSetDefaultL", CTestSDKButtons::TestCEikCmdBtBaseSetDefaultL ),
        ENTRY( "TestCEikCmdBtBaseSetDimmedL", CTestSDKButtons::TestCEikCmdBtBaseSetDimmedL ),
        ENTRY( "TestCEikCmdBtBaseMinimumSizeL", CTestSDKButtons::TestCEikCmdBtBaseMinimumSizeL ),
        ENTRY( "TestCEikCmdBtBaseCountComponentControlsL", CTestSDKButtons::TestCEikCmdBtBaseCountComponentControlsL ),
        ENTRY( "TestCEikCmdBtBaseComponentControlL", CTestSDKButtons::TestCEikCmdBtBaseComponentControlL ),
        ENTRY( "TestCEikCmdBtBaseSetContainerWindowLAndActivateL", CTestSDKButtons::TestCEikCmdBtBaseSetContainerWindowLAndActivateL ),
        ENTRY( "TestCEikCmdBtBaseFocusChangedL", CTestSDKButtons::TestCEikCmdBtBaseFocusChangedL ),
        ENTRY( "TestCEikCmdBtBaseOfferKeyEventL", CTestSDKButtons::TestCEikCmdBtBaseOfferKeyEventL ),
        ENTRY( "TestCEikCmdBtBaseGetColorUseListL", CTestSDKButtons::TestCEikCmdBtBaseGetColorUseListL ),
        ENTRY( "TestCEikCmdBtBaseHandleResourceChangeL", CTestSDKButtons::TestCEikCmdBtBaseHandleResourceChangeL ),
        ENTRY( "TestCEikCmdBtBaseStateChangedL", CTestSDKButtons::TestCEikCmdBtBaseStateChangedL ),
        ENTRY( "TestCEikCmdBtBaseSetTextL", CTestSDKButtons::TestCEikCmdBtBaseSetTextL ),
        ENTRY( "TestCEikCmdBtBaseSetPictureL", CTestSDKButtons::TestCEikCmdBtBaseSetPictureL ),
        ENTRY( "TestCEikCmdBtBaseSetPictureFromFileL", CTestSDKButtons::TestCEikCmdBtBaseSetPictureFromFileL ),
        ENTRY( "TestCEikCmdBtBaseDrawL", CTestSDKButtons::TestCEikCmdBtBaseDrawL ),
        ENTRY( "TestCEikCmdBtBaseWriteInternalStateL", CTestSDKButtons::TestCEikCmdBtBaseWriteInternalStateL ),
        ENTRY( "TestCEikCmdBtConstructorL", CTestSDKButtons::TestCEikCmdBtConstructorL ),
        ENTRY( "TestCEikCmdBtConstructFromResourceL", CTestSDKButtons::TestCEikCmdBtConstructFromResourceL ),
        ENTRY( "TestCEikCmdBtSetPictureL", CTestSDKButtons::TestCEikCmdBtSetPictureL ),
        ENTRY( "TestCEikCmdBtSetThreeEnumL", CTestSDKButtons::TestCEikCmdBtSetThreeEnumL ),
        ENTRY( "TestCEikCmdBtSetTextL", CTestSDKButtons::TestCEikCmdBtSetTextL ),
        ENTRY( "TestCEikCmdBtLabelL", CTestSDKButtons::TestCEikCmdBtLabelL ),
        ENTRY( "TestCEikCmdBtCmdSetL", CTestSDKButtons::TestCEikCmdBtCmdSetL ),
        ENTRY( "TestCEikCmdBtUpdateComponentAlignmentL", CTestSDKButtons::TestCEikCmdBtUpdateComponentAlignmentL ),
        ENTRY( "TestCEikBtBaseConstructorL", CTestSDKButtons::TestCEikBtBaseConstructorL ),
        ENTRY( "TestCEikBtBaseSetAndGetStateL", CTestSDKButtons::TestCEikBtBaseSetAndGetStateL ),
        ENTRY( "TestCEikBtBaseAnimateL", CTestSDKButtons::TestCEikBtBaseAnimateL ),
        ENTRY( "TestCEikBtBaseSetCoordinatorL", CTestSDKButtons::TestCEikBtBaseSetCoordinatorL ),
        ENTRY( "TestCEikBtBaseSetBehaviorL", CTestSDKButtons::TestCEikBtBaseSetBehaviorL ),
        ENTRY( "TestCEikBtBaseGetColorUseListL", CTestSDKButtons::TestCEikBtBaseGetColorUseListL ),
        ENTRY( "TestCEikBtBaseHandleResourceChangeL", CTestSDKButtons::TestCEikBtBaseHandleResourceChangeL ),
        ENTRY( "TestCEikBtBaseWriteInternalStateL", CTestSDKButtons::TestCEikBtBaseWriteInternalStateL ),
        ENTRY( "TestCEikBtBaseDrawStateL", CTestSDKButtons::TestCEikBtBaseDrawStateL ),
        ENTRY( "TestCEikBtBaseSetAllowTristateL", CTestSDKButtons::TestCEikBtBaseSetAllowTristateL ),
        ENTRY( "TestCEikBtBaseCopyDrawStateToL", CTestSDKButtons::TestCEikBtBaseCopyDrawStateToL ),
        ENTRY( "TestCEikBtBaseOfferKeyEventL", CTestSDKButtons::TestCEikBtBaseOfferKeyEventL ),
        ENTRY( "TestCEikBtBaseInputCapabilitiesL", CTestSDKButtons::TestCEikBtBaseInputCapabilitiesL ),
        ENTRY( "TestCEikTwoPicCmdBtConstructorL", CTestSDKButtons::TestCEikTwoPicCmdBtConstructorL ),
        ENTRY( "TestCEikTwoPicCmdBtConstructFromResourceL", CTestSDKButtons::TestCEikTwoPicCmdBtConstructFromResourceL ),
        ENTRY( "TestCEikTwoPicCmdBtIsSecondPictureOwnedExternallyL", CTestSDKButtons::TestCEikTwoPicCmdBtIsSecondPictureOwnedExternallyL ),
        ENTRY( "TestCEikTwoPicCmdBtPictureL", CTestSDKButtons::TestCEikTwoPicCmdBtPictureL ),
        ENTRY( "TestCEikTwoPicCmdBtSetTextL", CTestSDKButtons::TestCEikTwoPicCmdBtSetTextL ),
        ENTRY( "TestCEikTwoPicCmdBtPictureSetL", CTestSDKButtons::TestCEikTwoPicCmdBtPictureSetL ),
        ENTRY( "TestCEikTwoPicCmdBtConstructImagesFromResourceL", CTestSDKButtons::TestCEikTwoPicCmdBtConstructImagesFromResourceL ),
        ENTRY( "TestCEikTwoPicCmdBtSetSecondPictureOwnedExternallyL", CTestSDKButtons::TestCEikTwoPicCmdBtSetSecondPictureOwnedExternallyL ),
        ENTRY( "TestCEikTwoPicCmdBtActivateL", CTestSDKButtons::TestCEikTwoPicCmdBtActivateL ),
        ENTRY( "TestCEikTwoPicCmdBtWriteInternalStateL", CTestSDKButtons::TestCEikTwoPicCmdBtWriteInternalStateL ),
        ENTRY( "TestCEikInverterCmdBtConstructorL", CTestSDKButtons::TestCEikInverterCmdBtConstructorL ),
        ENTRY( "TestCEikInverterCmdBtWriteInternalStateL", CTestSDKButtons::TestCEikInverterCmdBtWriteInternalStateL ),
        ENTRY( "TestCEikTxtBtConstructorL", CTestSDKButtons::TestCEikTxtBtConstructorL ),
        ENTRY( "TestCEikTxtBtConstructFromResourceL", CTestSDKButtons::TestCEikTxtBtConstructFromResourceL ),
        ENTRY( "TestCEikTxtBtSetTextL", CTestSDKButtons::TestCEikTxtBtSetTextL ),
        ENTRY( "TestCEikTxtBtLabelL", CTestSDKButtons::TestCEikTxtBtLabelL ),
        ENTRY( "TestCEikBmpBtConstructorL", CTestSDKButtons::TestCEikBmpBtConstructorL ),
        ENTRY( "TestCEikBmpBtConstructFromResourceL", CTestSDKButtons::TestCEikBmpBtConstructFromResourceL ),
        ENTRY( "TestCEikBmpBtPictureSetL", CTestSDKButtons::TestCEikBmpBtPictureSetL ),
        ENTRY( "TestCEikCmdBtProcessCmdStackL", CTestSDKButtons::TestCEikCmdBtProcessCmdStackL ),
        ENTRY( "TestCEikBtGroupStackMinimumSize", CTestSDKButtons::TestCEikBtGroupStackMinimumSize ),
        ENTRY( "TestCEikCbaOfferCommandListL", CTestSDKButtons::TestCEikCbaOfferCommandListL ),
        ENTRY( "TestCEikCbaIsCommandInGroupL", CTestSDKButtons::TestCEikCbaIsCommandInGroupL ),
        ENTRY( "TestCEikCbaSetButtonGroupFlagsL", CTestSDKButtons::TestCEikCbaSetButtonGroupFlagsL ),
        ENTRY( "TestCEikCbaReplaceCommandL", CTestSDKButtons::TestCEikCbaReplaceCommandL ),
        ENTRY( "TestCEikCbaSetSkinBackgroundIdL", CTestSDKButtons::TestCEikCbaSetSkinBackgroundIdL ),
        ENTRY( "TestCEikCbaIsEmptyL", CTestSDKButtons::TestCEikCbaIsEmptyL ),
        ENTRY( "TestCEikBtGroupFactoryCbaTCreationDataL", CTestSDKButtons::TestCEikBtGroupFactoryCbaTCreationDataL ),
        ENTRY( "TestCEikBtGroupFactoryArrayAddAndRemoveFuncL", CTestSDKButtons::TestCEikBtGroupFactoryArrayAddAndRemoveFuncL ),
        ENTRY( "TestCEikBtGroupContainerNewL", CTestSDKButtons::TestCEikBtGroupContainerNewL ),
        ENTRY( "TestCEikBtGroupContainerCurrent", CTestSDKButtons::TestCEikBtGroupContainerCurrent ),
        ENTRY( "TestCEikBtGroupContainerSetCommandL", CTestSDKButtons::TestCEikBtGroupContainerSetCommandL ),
        ENTRY( "TestCEikBtGroupContainerSetCommandSetL", CTestSDKButtons::TestCEikBtGroupContainerSetCommandSetL ),
        ENTRY( "TestCEikBtGroupContainerAddCommandL", CTestSDKButtons::TestCEikBtGroupContainerAddCommandL ),
        ENTRY( "TestCEikBtGroupContainerAddCommandToStackL", CTestSDKButtons::TestCEikBtGroupContainerAddCommandToStackL ),
        ENTRY( "TestCEikBtGroupContainerAddCommandSetToStackL", CTestSDKButtons::TestCEikBtGroupContainerAddCommandSetToStackL ),
        ENTRY( "TestCEikBtGroupContainerRemoveCommandFromStackL", CTestSDKButtons::TestCEikBtGroupContainerRemoveCommandFromStackL ),
        ENTRY( "TestCEikBtGroupContainerSetDefaultCommandL", CTestSDKButtons::TestCEikBtGroupContainerSetDefaultCommandL ),
        ENTRY( "TestCEikBtGroupContainerCalcMinimumSizeL", CTestSDKButtons::TestCEikBtGroupContainerCalcMinimumSizeL ),
        ENTRY( "TestCEikBtGroupContainerCleanupFunctionL", CTestSDKButtons::TestCEikBtGroupContainerCleanupFunctionL ),
        ENTRY( "TestCEikBtGroupContainerBtNumberL", CTestSDKButtons::TestCEikBtGroupContainerBtNumberL ),
        ENTRY( "TestCEikBtGroupContainerCmdDimL", CTestSDKButtons::TestCEikBtGroupContainerCmdDimL ),
        ENTRY( "TestCEikBtGroupContainerCmdAnimateL", CTestSDKButtons::TestCEikBtGroupContainerCmdAnimateL ),
        ENTRY( "TestCEikBtGroupContainerCmdVisibleL", CTestSDKButtons::TestCEikBtGroupContainerCmdVisibleL ),
        ENTRY( "TestCEikBtGroupContainerLocationL", CTestSDKButtons::TestCEikBtGroupContainerLocationL ),
        ENTRY( "TestCEikBtGroupContainerCommandButtonOrNullL", CTestSDKButtons::TestCEikBtGroupContainerCommandButtonOrNullL ),
        ENTRY( "TestCEikBtGroupContainerControlOrNullL", CTestSDKButtons::TestCEikBtGroupContainerControlOrNullL ),
        ENTRY( "TestCEikBtGroupContainerSetBoundingRectL", CTestSDKButtons::TestCEikBtGroupContainerSetBoundingRectL ),
        ENTRY( "TestCEikBtGroupContainerGetBtAndBtPositionAndBtTypeL", CTestSDKButtons::TestCEikBtGroupContainerGetBtAndBtPositionAndBtTypeL ),
        ENTRY( "TestCEikBtGroupContainerReduceRectL", CTestSDKButtons::TestCEikBtGroupContainerReduceRectL ),
        ENTRY( "TestCEikBtGroupContainerUpdateHotKeyL", CTestSDKButtons::TestCEikBtGroupContainerUpdateHotKeyL ),
        ENTRY( "TestCEikBtGroupContainerUpdateCommandObserverL", CTestSDKButtons::TestCEikBtGroupContainerUpdateCommandObserverL ),
        ENTRY( "TestCEikBtGroupContainerRemoveCommandObserverL", CTestSDKButtons::TestCEikBtGroupContainerRemoveCommandObserverL ),
        ENTRY( "TestCEikBtGroupContainerUpdatedCommandObserverExistsL", CTestSDKButtons::TestCEikBtGroupContainerUpdatedCommandObserverExistsL ),
        ENTRY( "TestCEikBtGroupContainerDelayActivationL", CTestSDKButtons::TestCEikBtGroupContainerDelayActivationL ),
        ENTRY( "TestCEikBtGroupContainerButtonGroupL", CTestSDKButtons::TestCEikBtGroupContainerButtonGroupL ),
        ENTRY( "TestCEikBtGroupContainerReservedFunctionL", CTestSDKButtons::TestCEikBtGroupContainerReservedFunctionL ),
        ENTRY( "TestCEikBtGroupContainerOfferCommandListL", CTestSDKButtons::TestCEikBtGroupContainerOfferCommandListL ),
        ENTRY( "TestCEikBtGroupContainerIsCommandInGroupL", CTestSDKButtons::TestCEikBtGroupContainerIsCommandInGroupL ),
        ENTRY( "TestCEikBtGroupContainerReplaceCommandL", CTestSDKButtons::TestCEikBtGroupContainerReplaceCommandL ),
        ENTRY( "TestCEikBtGroupContainerMinimumSizeL", CTestSDKButtons::TestCEikBtGroupContainerMinimumSizeL ),
        ENTRY( "TestCEikBtGroupContainerOfferKeyEventL", CTestSDKButtons::TestCEikBtGroupContainerOfferKeyEventL ),
        ENTRY( "TestCEikBtGroupContainerMakeVisibleL", CTestSDKButtons::TestCEikBtGroupContainerMakeVisibleL ),
        ENTRY( "TestCEikBtGroupContainerWriteInternalStateL", CTestSDKButtons::TestCEikBtGroupContainerWriteInternalStateL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }



//  [End of File]
