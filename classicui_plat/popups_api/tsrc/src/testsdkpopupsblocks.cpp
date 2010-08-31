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
* Description:  test aknPopup.h aknpopupfader.h AknPopupField.h AknPopupFieldList.h 
*                     AknPopupFieldText.h aknPopupHeadingPane.h aknpopuplayout.h 
*                     AknPopupSettingPage.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkpopups.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKPopups::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKPopups::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestPLNewL", CTestSDKPopups::TestPLNewL ),
        ENTRY( "TestPLExecuteLD", CTestSDKPopups::TestPLExecuteLD ),
        ENTRY( "TestPLSetTitleL", CTestSDKPopups::TestPLSetTitleL ),
        ENTRY( "TestPLCancelPopupL", CTestSDKPopups::TestPLCancelPopupL ),
        ENTRY( "TestPLButtonGroupContainerL", CTestSDKPopups::TestPLButtonGroupContainerL ),
        ENTRY( "TestPLHeadingL", CTestSDKPopups::TestPLHeadingL ),
        ENTRY( "TestPLHeadingConstL", CTestSDKPopups::TestPLHeadingConstL ),
        ENTRY( "TestPLListBoxL", CTestSDKPopups::TestPLListBoxL ),
        ENTRY( "TestPLSetMaximumHeightL", CTestSDKPopups::TestPLSetMaximumHeightL ),
        ENTRY( "TestPLEnableFindL", CTestSDKPopups::TestPLEnableFindL ),
        ENTRY( "TestPLEnableAdaptiveFindL", CTestSDKPopups::TestPLEnableAdaptiveFindL ),
        ENTRY( "TestPLFindBoxL", CTestSDKPopups::TestPLFindBoxL ),
        ENTRY( "TestPLHandlePointerEventL", CTestSDKPopups::TestPLHandlePointerEventL ),
        ENTRY( "TestPLProcessCommandL", CTestSDKPopups::TestPLProcessCommandL ),
        ENTRY( "TestPLHandleListBoxEventL", CTestSDKPopups::TestPLHandleListBoxEventL ),
        ENTRY( "TestPLHandleControlEventL", CTestSDKPopups::TestPLHandleControlEventL ),
        ENTRY( "TestPLCAknPopupListL", CTestSDKPopups::TestPLCAknPopupListL ),
        ENTRY( "TestPLDeconstrutorL", CTestSDKPopups::TestPLDeconstrutorL ),
        ENTRY( "TestPLConstructL", CTestSDKPopups::TestPLConstructL ),
        ENTRY( "TestPLAttemptExitL", CTestSDKPopups::TestPLAttemptExitL ),
        ENTRY( "TestPLSetupWindowLayoutL", CTestSDKPopups::TestPLSetupWindowLayoutL ),
        ENTRY( "TestPLListBoxConstL", CTestSDKPopups::TestPLListBoxConstL ),
        ENTRY( "TestPLLayoutConstL", CTestSDKPopups::TestPLLayoutConstL ),
        ENTRY( "TestPLLayoutL", CTestSDKPopups::TestPLLayoutL ),
        ENTRY( "TestPLMopSupplyObjectL", CTestSDKPopups::TestPLMopSupplyObjectL ),
        ENTRY( "TestPLHandleResourceChangeL", CTestSDKPopups::TestPLHandleResourceChangeL ),
        ENTRY( "TestPLFadeBehindPopupL", CTestSDKPopups::TestPLFadeBehindPopupL ),
        
        ENTRY( "TestMFCCountFadedComponentsL", CTestSDKPopups::TestMFCCountFadedComponentsL ),
        ENTRY( "TestMFCFadedComponentL", CTestSDKPopups::TestMFCFadedComponentL ),
        ENTRY( "TestTPFFadeBehindPopupL", CTestSDKPopups::TestTPFFadeBehindPopupL ),
        
        ENTRY( "TestCPFCAknPopupFieldL", CTestSDKPopups::TestCPFCAknPopupFieldL ),
        ENTRY( "TestCPFDeconstructorL", CTestSDKPopups::TestCPFDeconstructorL ),
        ENTRY( "TestCPFConstructL", CTestSDKPopups::TestCPFConstructL ),
        ENTRY( "TestCPFSetAllowsUserDefinedEntryL", CTestSDKPopups::TestCPFSetAllowsUserDefinedEntryL ),
        ENTRY( "TestCPFActivateSelectionListL", CTestSDKPopups::TestCPFActivateSelectionListL ),
        ENTRY( "TestCPFSetQueryValueL", CTestSDKPopups::TestCPFSetQueryValueL ),
        ENTRY( "TestCPFSetFontL", CTestSDKPopups::TestCPFSetFontL ),
        ENTRY( "TestCPFSetShowIndicatorsL", CTestSDKPopups::TestCPFSetShowIndicatorsL ),
        ENTRY( "TestCPFNumLinesL", CTestSDKPopups::TestCPFNumLinesL ),
        ENTRY( "TestCPFSetPopupFieldObserverL", CTestSDKPopups::TestCPFSetPopupFieldObserverL ),
        ENTRY( "TestCPFSetEmptyListNoteL", CTestSDKPopups::TestCPFSetEmptyListNoteL ),
        ENTRY( "TestCPFSetEmptyTextL", CTestSDKPopups::TestCPFSetEmptyTextL ),
        ENTRY( "TestCPFSetOtherTextL", CTestSDKPopups::TestCPFSetOtherTextL ),
        ENTRY( "TestCPFSetInvalidTextL", CTestSDKPopups::TestCPFSetInvalidTextL ),
        ENTRY( "TestCPFOfferKeyEventL", CTestSDKPopups::TestCPFOfferKeyEventL ),
        ENTRY( "TestCPFConstructFromResourceL", CTestSDKPopups::TestCPFConstructFromResourceL ),
        ENTRY( "TestCPFMinimumSizeL", CTestSDKPopups::TestCPFMinimumSizeL ),
        ENTRY( "TestCPFHandleResourceChangeL", CTestSDKPopups::TestCPFHandleResourceChangeL ),
        ENTRY( "TestCPFHandlePointerEventL", CTestSDKPopups::TestCPFHandlePointerEventL ),
        ENTRY( "TestCPFSetMaxNumberOfLinesPermittedL", CTestSDKPopups::TestCPFSetMaxNumberOfLinesPermittedL ),
        ENTRY( "TestCPFSetFormFieldRectL", CTestSDKPopups::TestCPFSetFormFieldRectL ),
        ENTRY( "TestCPFHandleControlEventL", CTestSDKPopups::TestCPFHandleControlEventL ),
        ENTRY( "TestCPFProcessCommandL", CTestSDKPopups::TestCPFProcessCommandL ),
        ENTRY( "TestCPFHandleListBoxEventL", CTestSDKPopups::TestCPFHandleListBoxEventL ),
        ENTRY( "TestCPFCountComponentControlsL", CTestSDKPopups::TestCPFCountComponentControlsL ),
        ENTRY( "TestCPFComponentControlL", CTestSDKPopups::TestCPFComponentControlL ),
        ENTRY( "TestCPFSizeChangedL", CTestSDKPopups::TestCPFSizeChangedL ),
        ENTRY( "TestCPFFocusChangedL", CTestSDKPopups::TestCPFFocusChangedL ),
        ENTRY( "TestCPFDrawL", CTestSDKPopups::TestCPFDrawL ),
        ENTRY( "TestCPFMopSupplyObjectL", CTestSDKPopups::TestCPFMopSupplyObjectL ),
        
        ENTRY( "TestCPFTCAknPopupFieldTextL", CTestSDKPopups::TestCPFTCAknPopupFieldTextL ),
        ENTRY( "TestCPFTDeconstructorL", CTestSDKPopups::TestCPFTDeconstructorL ),
        ENTRY( "TestCPFTCurrentValueTextLC", CTestSDKPopups::TestCPFTCurrentValueTextLC ),
        ENTRY( "TestCPFTCurrentValueIndexL", CTestSDKPopups::TestCPFTCurrentValueIndexL ),
        ENTRY( "TestCPFTSetCurrentValueIndexL", CTestSDKPopups::TestCPFTSetCurrentValueIndexL ),
        ENTRY( "TestCPFTMdcArrayL", CTestSDKPopups::TestCPFTMdcArrayL ),
        ENTRY( "TestCPFTSetAutoAppendL", CTestSDKPopups::TestCPFTSetAutoAppendL ),
        ENTRY( "TestCPFTConstructFromResourceL", CTestSDKPopups::TestCPFTConstructFromResourceL ),
        ENTRY( "TestCPFTHandlePointerEventL", CTestSDKPopups::TestCPFTHandlePointerEventL ),
        
        ENTRY( "TestCPHPCAknPopupHeadingPaneL", CTestSDKPopups::TestCPHPCAknPopupHeadingPaneL ),
        ENTRY( "TestCPHPDeconstructorL", CTestSDKPopups::TestCPHPDeconstructorL ),
        ENTRY( "TestCPHPSizeChangedL", CTestSDKPopups::TestCPHPSizeChangedL ),
        ENTRY( "TestCPHPMinimumSizeL", CTestSDKPopups::TestCPHPMinimumSizeL ),
        ENTRY( "TestCPHPConstructL", CTestSDKPopups::TestCPHPConstructL ),
        ENTRY( "TestCPHPConstructFromResourceL", CTestSDKPopups::TestCPHPConstructFromResourceL ),
        ENTRY( "TestCPHPPromptL", CTestSDKPopups::TestCPHPPromptL ),
        ENTRY( "TestCPHPPromptTextL", CTestSDKPopups::TestCPHPPromptTextL ),
        ENTRY( "TestCPHPSetTextL", CTestSDKPopups::TestCPHPSetTextL ),
        ENTRY( "TestCPHPSetHeaderImageOwnedL", CTestSDKPopups::TestCPHPSetHeaderImageOwnedL ),
        ENTRY( "TestCPHPSetHeaderImageL", CTestSDKPopups::TestCPHPSetHeaderImageL ),
        ENTRY( "TestCPHPSetHeaderAnimationL", CTestSDKPopups::TestCPHPSetHeaderAnimationL ),
        ENTRY( "TestCPHPSetLayoutL", CTestSDKPopups::TestCPHPSetLayoutL ),
        ENTRY( "TestCPHPStartAnimationL", CTestSDKPopups::TestCPHPStartAnimationL ),
        ENTRY( "TestCPHPCancelAnimationL", CTestSDKPopups::TestCPHPCancelAnimationL ),
        ENTRY( "TestCPHPHandlePointerEventL", CTestSDKPopups::TestCPHPHandlePointerEventL ),
        ENTRY( "TestCPHPHandleResourceChangeL", CTestSDKPopups::TestCPHPHandleResourceChangeL ),
        ENTRY( "TestCPHPSetSkinFrameIdL", CTestSDKPopups::TestCPHPSetSkinFrameIdL ),
        ENTRY( "TestCPHPSetSkinFrameCenterIdL", CTestSDKPopups::TestCPHPSetSkinFrameCenterIdL ),
        
        ENTRY( "TestCPLHandleSizeChangedL", CTestSDKPopups::TestCPLHandleSizeChangedL ),
        ENTRY( "TestCPLHandleSizeChangedListBoxL", CTestSDKPopups::TestCPLHandleSizeChangedListBoxL ),
        ENTRY( "TestCPLHandleDrawL", CTestSDKPopups::TestCPLHandleDrawL ),
        ENTRY( "TestCPLModifyWindowGraphicForHeadingL", CTestSDKPopups::TestCPLModifyWindowGraphicForHeadingL ),
        ENTRY( "TestCPLModifyWindowGraphicForMessageBoxL", CTestSDKPopups::TestCPLModifyWindowGraphicForMessageBoxL ),
        ENTRY( "TestCPLCalcPopupMenuWindowL", CTestSDKPopups::TestCPLCalcPopupMenuWindowL ),
        ENTRY( "TestCPLCalcPopupMenuGraphicWindowL", CTestSDKPopups::TestCPLCalcPopupMenuGraphicWindowL ),
        ENTRY( "TestCPLCalcPopupMenuGraphicHeadingWindowL", CTestSDKPopups::TestCPLCalcPopupMenuGraphicHeadingWindowL ),
        ENTRY( "TestCPLCalcPopupMenuDoubleWindowL", CTestSDKPopups::TestCPLCalcPopupMenuDoubleWindowL ),
        ENTRY( "TestCPLCalcPopupMenuDoubleLargeGraphicWindowL", CTestSDKPopups::TestCPLCalcPopupMenuDoubleLargeGraphicWindowL ),
        ENTRY( "TestCPLCalcPopupSNoteGroupWindowL", CTestSDKPopups::TestCPLCalcPopupSNoteGroupWindowL ),
        ENTRY( "TestCPLSetupMenuPopupWindowL", CTestSDKPopups::TestCPLSetupMenuPopupWindowL ),
        ENTRY( "TestCPLSetupPopupMenuGraphicWindowL", CTestSDKPopups::TestCPLSetupPopupMenuGraphicWindowL ),
        ENTRY( "TestCPLSetupPopupMenuGraphicHeadingWindowL", CTestSDKPopups::TestCPLSetupPopupMenuGraphicHeadingWindowL ),
        ENTRY( "TestCPLSetupPopupMenuDoubleWindowL", CTestSDKPopups::TestCPLSetupPopupMenuDoubleWindowL ),
        ENTRY( "TestCPLSetupImageSelectionMenuPopupWindowL", CTestSDKPopups::TestCPLSetupImageSelectionMenuPopupWindowL ),
        ENTRY( "TestCPLSetupPopupSNoteGroupWindowL", CTestSDKPopups::TestCPLSetupPopupSNoteGroupWindowL ),
        ENTRY( "TestCPLHandleSizeAndPositionOfComponentsL", CTestSDKPopups::TestCPLHandleSizeAndPositionOfComponentsL ),
        ENTRY( "TestCPLSetupDefaultsL", CTestSDKPopups::TestCPLSetupDefaultsL ),
        ENTRY( "TestCPLWindowRectL", CTestSDKPopups::TestCPLWindowRectL ),
        ENTRY( "TestCPLMenuRectL", CTestSDKPopups::TestCPLMenuRectL ),
        ENTRY( "TestCPLCheckRangeL", CTestSDKPopups::TestCPLCheckRangeL ),
        ENTRY( "TestCPLMenuPopupWindowGraphicsL", CTestSDKPopups::TestCPLMenuPopupWindowGraphicsL ),

        ENTRY( "TestCPSLCAknPopupSettingListL", CTestSDKPopups::TestCPSLCAknPopupSettingListL ),
        ENTRY( "TestCPSLDeconstructorL", CTestSDKPopups::TestCPSLDeconstructorL ),
        ENTRY( "TestCPSLConstructL", CTestSDKPopups::TestCPSLConstructL ),
        ENTRY( "TestCPSLSetAllowsUserDefinedEntryL", CTestSDKPopups::TestCPSLSetAllowsUserDefinedEntryL ),
        ENTRY( "TestCPSLSetQueryValueL", CTestSDKPopups::TestCPSLSetQueryValueL ),
        ENTRY( "TestCPSLSetShowIndicatorsL", CTestSDKPopups::TestCPSLSetShowIndicatorsL ),
        ENTRY( "TestCPSLNumLinesL", CTestSDKPopups::TestCPSLNumLinesL ),
        ENTRY( "TestCPSLSetPopupSettingListObserverL", CTestSDKPopups::TestCPSLSetPopupSettingListObserverL ),
        ENTRY( "TestCPSLConstructFromResourceL", CTestSDKPopups::TestCPSLConstructFromResourceL ),
        ENTRY( "TestCPSLCreateMenuListL", CTestSDKPopups::TestCPSLCreateMenuListL ),
        ENTRY( "TestCPSLActivateMenuListL", CTestSDKPopups::TestCPSLActivateMenuListL ),
        ENTRY( "TestCPSLConfigureMenuListL", CTestSDKPopups::TestCPSLConfigureMenuListL ),
        ENTRY( "TestCPSLDestroyMenuListL", CTestSDKPopups::TestCPSLDestroyMenuListL ),
        ENTRY( "TestCPSLHandlePointerEventL", CTestSDKPopups::TestCPSLHandlePointerEventL ),
        ENTRY( "TestCPSLHandleResourceChangeL", CTestSDKPopups::TestCPSLHandleResourceChangeL ),
        ENTRY( "TestCPSLHandleListBoxEventL", CTestSDKPopups::TestCPSLHandleListBoxEventL ),
        ENTRY( "TestCPSPCAknPopupSettingPageL", CTestSDKPopups::TestCPSPCAknPopupSettingPageL ),
        ENTRY( "TestCPSPCAknPopupSettingPageTextL", CTestSDKPopups::TestCPSPCAknPopupSettingPageTextL ),
        ENTRY( "TestCPSPConstructLL", CTestSDKPopups::TestCPSPConstructLL ),
        ENTRY( "TestCPSPListBoxControlL", CTestSDKPopups::TestCPSPListBoxControlL ),
        ENTRY( "TestCPSPPopupSettingListBoxL", CTestSDKPopups::TestCPSPPopupSettingListBoxL ),
        ENTRY( "TestCPSPHandlePopupSettingListEventL", CTestSDKPopups::TestCPSPHandlePopupSettingListEventL ),
        ENTRY( "TestCPSPUpdateQueryValueL", CTestSDKPopups::TestCPSPUpdateQueryValueL ),
        ENTRY( "TestCPSPHandlePointerEventL", CTestSDKPopups::TestCPSPHandlePointerEventL ),
        ENTRY( "TestCPSPDeconstructorL", CTestSDKPopups::TestCPSPDeconstructorL ),
        ENTRY( "TestCPSPQueryValueL", CTestSDKPopups::TestCPSPQueryValueL ),
        ENTRY( "TestCPSPSelectCurrentItemL", CTestSDKPopups::TestCPSPSelectCurrentItemL ),
        ENTRY( "TestCPSPWriteInternalStateL", CTestSDKPopups::TestCPSPWriteInternalStateL ),
        ENTRY( "TestCPSPReservedL", CTestSDKPopups::TestCPSPReservedL ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
