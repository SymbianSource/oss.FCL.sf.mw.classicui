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
* Description:  Test EIKINFO.H EIKPROGI.H AknNoteDialog.h aknnotewrappers.h 
*                     AknProgressDialog.h aknprogresstimer.h AknStaticNoteDialog.h 
*                     aknwaitdialog.h AknWaitNoteWrapper.h aknnotecontrol.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdknotes.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKNotes::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKNotes::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotes::RunMethodL( 
    CStifItemParser& aItem ) 
    {
    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestNCEikInfoDialogL", CTestSDKNotes::TestNCEikInfoDialogL ),
        ENTRY( "TestNRunDlgLD", CTestSDKNotes::TestNRunDlgLD ),
        ENTRY( "TestNHandlePointerEventL", CTestSDKNotes::TestNHandlePointerEventL ),
        
        ENTRY( "TestNPIDeconstructorL", CTestSDKNotes::TestNPIDeconstructorL ),
        ENTRY( "TestNPICEikProgressInfoL", CTestSDKNotes::TestNPICEikProgressInfoL ),
        ENTRY( "TestNPICEikProgressInfoSinfoL", CTestSDKNotes::TestNPICEikProgressInfoSinfoL ),
        ENTRY( "TestNPIIncrementAndDrawL", CTestSDKNotes::TestNPIIncrementAndDrawL ),
        ENTRY( "TestNPISetAndDrawL", CTestSDKNotes::TestNPISetAndDrawL ),
        ENTRY( "TestNPIConstructFromResourceL", CTestSDKNotes::TestNPIConstructFromResourceL ),
        ENTRY( "TestNPISetLayoutL", CTestSDKNotes::TestNPISetLayoutL ),
        ENTRY( "TestNPISetBorderL", CTestSDKNotes::TestNPISetBorderL ),
        ENTRY( "TestNPISetFinalValueL", CTestSDKNotes::TestNPISetFinalValueL ),
        ENTRY( "TestNPIConstructL", CTestSDKNotes::TestNPIConstructL ),
        ENTRY( "TestNPIInfoL", CTestSDKNotes::TestNPIInfoL ),
        ENTRY( "TestNPILayoutL", CTestSDKNotes::TestNPILayoutL ),
        ENTRY( "TestNPICurrentValueL", CTestSDKNotes::TestNPICurrentValueL ),
        ENTRY( "TestNPIEvaluateTextL", CTestSDKNotes::TestNPIEvaluateTextL ),
        ENTRY( "TestNPIActivateL", CTestSDKNotes::TestNPIActivateL ),
        ENTRY( "TestNPIMinimumSizeL", CTestSDKNotes::TestNPIMinimumSizeL ),
        ENTRY( "TestNPISizeChangedL", CTestSDKNotes::TestNPISizeChangedL ),
        ENTRY( "TestNPIGetColorUseListL", CTestSDKNotes::TestNPIGetColorUseListL ),
        ENTRY( "TestNPIHandleResourceChangeL", CTestSDKNotes::TestNPIHandleResourceChangeL ),
        ENTRY( "TestNPIHandlePointerEventL", CTestSDKNotes::TestNPIHandlePointerEventL ),
        ENTRY( "TestNPIWriteInternalStateL", CTestSDKNotes::TestNPIWriteInternalStateL ),
        
        ENTRY( "TestNDCAknNoteDialogL", CTestSDKNotes::TestNDCAknNoteDialogL ),
        ENTRY( "TestNDCAknNoteDialogToneL", CTestSDKNotes::TestNDCAknNoteDialogToneL ),
        ENTRY( "TestNDCAknNoteDialogPointerL", CTestSDKNotes::TestNDCAknNoteDialogPointerL ),
        ENTRY( "TestNDDeconstructorL", CTestSDKNotes::TestNDDeconstructorL ),
        ENTRY( "TestNDSetTimeoutL", CTestSDKNotes::TestNDSetTimeoutL ),
        ENTRY( "TestNDSetToneL", CTestSDKNotes::TestNDSetToneL ),
        ENTRY( "TestNDSetTextWrappingL", CTestSDKNotes::TestNDSetTextWrappingL ),
        ENTRY( "TestNDSetTextProcessingL", CTestSDKNotes::TestNDSetTextProcessingL ),
        ENTRY( "TestNDSetImageL", CTestSDKNotes::TestNDSetImageL ),
        ENTRY( "TestNDSetIconL", CTestSDKNotes::TestNDSetIconL ),
        ENTRY( "TestNDSetTextNumberL", CTestSDKNotes::TestNDSetTextNumberL ),
        ENTRY( "TestNDSetTextPluralityL", CTestSDKNotes::TestNDSetTextPluralityL ),
        ENTRY( "TestNDSetTextL", CTestSDKNotes::TestNDSetTextL ),
        ENTRY( "TestNDOfferKeyEventL", CTestSDKNotes::TestNDOfferKeyEventL ),
        ENTRY( "TestNDHandleResourceChangeL", CTestSDKNotes::TestNDHandleResourceChangeL ),
        ENTRY( "TestNDLayoutAndDrawL", CTestSDKNotes::TestNDLayoutAndDrawL ),
        ENTRY( "TestNDRunLD", CTestSDKNotes::TestNDRunLD ),
        ENTRY( "TestNDExitSleepingDialogL", CTestSDKNotes::TestNDExitSleepingDialogL ),
        ENTRY( "TestNDSetSizeAndPositionL", CTestSDKNotes::TestNDSetSizeAndPositionL ),
        ENTRY( "TestNDPreLayoutDynInitL", CTestSDKNotes::TestNDPreLayoutDynInitL ),
        ENTRY( "TestNDPostLayoutDynInitL", CTestSDKNotes::TestNDPostLayoutDynInitL ),
        ENTRY( "TestNDPlayToneL", CTestSDKNotes::TestNDPlayToneL ),
        ENTRY( "TestNDReportUserActivityL", CTestSDKNotes::TestNDReportUserActivityL ),
        ENTRY( "TestNDStaticDeleteL", CTestSDKNotes::TestNDStaticDeleteL ),
        ENTRY( "TestNDControlAttributesL", CTestSDKNotes::TestNDControlAttributesL ),
        ENTRY( "TestNDTransferControlAttributesL", CTestSDKNotes::TestNDTransferControlAttributesL ),
        ENTRY( "TestNDSoundSystemL", CTestSDKNotes::TestNDSoundSystemL ),
        ENTRY( "TestNDNoteControlL", CTestSDKNotes::TestNDNoteControlL ),
        ENTRY( "TestNDExecuteDlgTimeOutLD", CTestSDKNotes::TestNDExecuteDlgTimeOutLD ),
        ENTRY( "TestNDExecuteDlgToneLD", CTestSDKNotes::TestNDExecuteDlgToneLD ),
        ENTRY( "TestNDExecuteDlgLD", CTestSDKNotes::TestNDExecuteDlgLD ),
        ENTRY( "TestNDRunDlgTimeOuntLD", CTestSDKNotes::TestNDRunDlgTimeOuntLD ),
        ENTRY( "TestNDRunDlgToneLD", CTestSDKNotes::TestNDRunDlgToneLD ),
        ENTRY( "TestNDRunDlgLD", CTestSDKNotes::TestNDRunDlgLD ),
        ENTRY( "TestNDRunDlgIdLD", CTestSDKNotes::TestNDRunDlgIdLD ),
        ENTRY( "TestNDSetCurrentLabelL", CTestSDKNotes::TestNDSetCurrentLabelL ),
        ENTRY( "TestNDSetNoMemoryAllocationL", CTestSDKNotes::TestNDSetNoMemoryAllocationL ),
        ENTRY( "TestNDHandlePointerEventL", CTestSDKNotes::TestNDHandlePointerEventL ),
        
        ENTRY( "TestNWCAknNoteWrapperL", CTestSDKNotes::TestNWCAknNoteWrapperL ),
        ENTRY( "TestNWCAknNoteWrapperPointerL", CTestSDKNotes::TestNWCAknNoteWrapperPointerL ),
        ENTRY( "TestNWExecuteLD", CTestSDKNotes::TestNWExecuteLD ),
        ENTRY( "TestNWExecutePromptLD", CTestSDKNotes::TestNWExecutePromptLD ),
        ENTRY( "TestNWHandlePointerEventL", CTestSDKNotes::TestNWHandlePointerEventL ),
        ENTRY( "TestNWHandleDialogPageEventL", CTestSDKNotes::TestNWHandleDialogPageEventL ),
        
        ENTRY( "TestNRNDExecuteLD", CTestSDKNotes::TestNRNDExecuteLD ),
        ENTRY( "TestNRNDExecutePromptLD", CTestSDKNotes::TestNRNDExecutePromptLD ),
        ENTRY( "TestNRNDHandlePointerEventL", CTestSDKNotes::TestNRNDHandlePointerEventL ),
        ENTRY( "TestNRNDCAknResourceNoteDialogL", CTestSDKNotes::TestNRNDCAknResourceNoteDialogL ),
        ENTRY( "TestNRNDCAknResourceNoteDialogPointerL", CTestSDKNotes::TestNRNDCAknResourceNoteDialogPointerL ),
        
        ENTRY( "TestNCNCAknConfirmationNoteL", CTestSDKNotes::TestNCNCAknConfirmationNoteL ),
        ENTRY( "TestNCNCAknConfirmationNoteParameterL", CTestSDKNotes::TestNCNCAknConfirmationNoteParameterL ),
        ENTRY( "TestNCNCAknConfirmationNotePointerL", CTestSDKNotes::TestNCNCAknConfirmationNotePointerL ),
        ENTRY( "TestNCNHandlePointerEventL", CTestSDKNotes::TestNCNHandlePointerEventL ),
        
        ENTRY( "TestNINCAknInformationNoteL", CTestSDKNotes::TestNINCAknInformationNoteL ),
        ENTRY( "TestNINCAknInformationNoteParameterL", CTestSDKNotes::TestNINCAknInformationNoteParameterL ),
        ENTRY( "TestNINCAknInformationNotePointerL", CTestSDKNotes::TestNINCAknInformationNotePointerL ),
        ENTRY( "TestNINHandlePointerEventL", CTestSDKNotes::TestNINHandlePointerEventL ),
        
        ENTRY( "TestNENCAknErrorNoteL", CTestSDKNotes::TestNENCAknErrorNoteL ),
        ENTRY( "TestNENCAknErrorNoteParameterL", CTestSDKNotes::TestNENCAknErrorNoteParameterL ),
        ENTRY( "TestNENCAknErrorNotePointerL", CTestSDKNotes::TestNENCAknErrorNotePointerL ),
        ENTRY( "TestNENHandlePointerEventL", CTestSDKNotes::TestNENHandlePointerEventL ),
        
        ENTRY( "TestNWNCAknWarningNoteL", CTestSDKNotes::TestNWNCAknWarningNoteL ),
        ENTRY( "TestNWNCAknWarningNoteParameterL", CTestSDKNotes::TestNWNCAknWarningNoteParameterL ),
        ENTRY( "TestNWNCAknWarningNotePointerL", CTestSDKNotes::TestNWNCAknWarningNotePointerL ),
        ENTRY( "TestNWNHandlePointerEventL", CTestSDKNotes::TestNWNHandlePointerEventL ),
        
        
        ENTRY( "TestNPDCAknProgressDialogValueL", CTestSDKNotes::TestNPDCAknProgressDialogValueL ),
        ENTRY( "TestNPDCAknProgressDialogPointerL", CTestSDKNotes::TestNPDCAknProgressDialogPointerL ),
        ENTRY( "TestNPDCAknProgressDialogL", CTestSDKNotes::TestNPDCAknProgressDialogL ),
        ENTRY( "TestNPDDeconstructorL", CTestSDKNotes::TestNPDDeconstructorL ),
        ENTRY( "TestNPDRunLD", CTestSDKNotes::TestNPDRunLD ),
        ENTRY( "TestNPDGetProgressInfoL", CTestSDKNotes::TestNPDGetProgressInfoL ),
        ENTRY( "TestNPDOfferKeyEventL", CTestSDKNotes::TestNPDOfferKeyEventL ),
        ENTRY( "TestNPDProcessFinishedL", CTestSDKNotes::TestNPDProcessFinishedL ),
        ENTRY( "TestNPDSetCallbackL", CTestSDKNotes::TestNPDSetCallbackL ),
        ENTRY( "TestNPDHandlePointerEventL", CTestSDKNotes::TestNPDHandlePointerEventL ),
        ENTRY( "TestNPDPreLayoutDynInitL", CTestSDKNotes::TestNPDPreLayoutDynInitL ),
        ENTRY( "TestNPDOkToExitL", CTestSDKNotes::TestNPDOkToExitL ),
        
        ENTRY( "TestNSNSIHandleResourceChangeL", CTestSDKNotes::TestNSNSIHandleResourceChangeL ),
        ENTRY( "TestNSNSIHandlePointerEventL", CTestSDKNotes::TestNSNSIHandlePointerEventL ),
        ENTRY( "TestNSNDCAknStaticNoteDialogL", CTestSDKNotes::TestNSNDCAknStaticNoteDialogL ),
        ENTRY( "TestNSNDCAknStaticNoteDialogPointerL", CTestSDKNotes::TestNSNDCAknStaticNoteDialogPointerL ),
        ENTRY( "TestNSNDDeconstructorL", CTestSDKNotes::TestNSNDDeconstructorL ),
        ENTRY( "TestNSNDSetNumberOfBordersL", CTestSDKNotes::TestNSNDSetNumberOfBordersL ),
        ENTRY( "TestNSNDHandlePointerEventL", CTestSDKNotes::TestNSNDHandlePointerEventL ),
        ENTRY( "TestNSNDPostLayoutDynInitL", CTestSDKNotes::TestNSNDPostLayoutDynInitL ),
        ENTRY( "TestNSNDOfferKeyEventL", CTestSDKNotes::TestNSNDOfferKeyEventL ),
        
        ENTRY( "TestNWDCAknWaitDialogL", CTestSDKNotes::TestNWDCAknWaitDialogL ),
        ENTRY( "TestNWDCAknWaitDialogBoolL", CTestSDKNotes::TestNWDCAknWaitDialogBoolL ),
        ENTRY( "TestNWDHandlePointerEventL", CTestSDKNotes::TestNWDHandlePointerEventL ),
        ENTRY( "TestNWDGetProgressInfoL", CTestSDKNotes::TestNWDGetProgressInfoL ),
        
        ENTRY( "TestNWNWCAknWaitNoteWrapperL", CTestSDKNotes::TestNWNWCAknWaitNoteWrapperL ),
        ENTRY( "TestNWNWDeconstructorL", CTestSDKNotes::TestNWNWDeconstructorL ),
        ENTRY( "TestNWNWExecuteL", CTestSDKNotes::TestNWNWExecuteL ),
        ENTRY( "TestNWNWExecutePromptL", CTestSDKNotes::TestNWNWExecutePromptL ),
        ENTRY( "TestNWNWWaitDialogL", CTestSDKNotes::TestNWNWWaitDialogL ),
        
        ENTRY( "TestNNCCAknNoteControlL", CTestSDKNotes::TestNNCCAknNoteControlL ),
        ENTRY( "TestNNCDeconstructorL", CTestSDKNotes::TestNNCDeconstructorL ),
        ENTRY( "TestNNCSetImageL", CTestSDKNotes::TestNNCSetImageL ),
        ENTRY( "TestNNCSetAnimationL", CTestSDKNotes::TestNNCSetAnimationL ),
        ENTRY( "TestNNCSetIconL", CTestSDKNotes::TestNNCSetIconL ),
        ENTRY( "TestNNCSetFinalProgressValueL", CTestSDKNotes::TestNNCSetFinalProgressValueL ),
        ENTRY( "TestNNCIncrementBarsAndDrawL", CTestSDKNotes::TestNNCIncrementBarsAndDrawL ),
        ENTRY( "TestNNCCreateProgressBarL", CTestSDKNotes::TestNNCCreateProgressBarL ),
        ENTRY( "TestNNCGetProgressInfoL", CTestSDKNotes::TestNNCGetProgressInfoL ),
        ENTRY( "TestNNCStartAnimationL", CTestSDKNotes::TestNNCStartAnimationL ),
        ENTRY( "TestNNCCancelAnimationL", CTestSDKNotes::TestNNCCancelAnimationL ),
        ENTRY( "TestNNCResetTextL", CTestSDKNotes::TestNNCResetTextL ),
        ENTRY( "TestNNCSetTextL", CTestSDKNotes::TestNNCSetTextL ),
        ENTRY( "TestNNCSetTextLineNumL", CTestSDKNotes::TestNNCSetTextLineNumL ),
        ENTRY( "TestNNCSetTextNumberL", CTestSDKNotes::TestNNCSetTextNumberL ),
        ENTRY( "TestNNCSetTextPluralityL", CTestSDKNotes::TestNNCSetTextPluralityL ),
        ENTRY( "TestNNCNumberOfLinesL", CTestSDKNotes::TestNNCNumberOfLinesL ),
        ENTRY( "TestNNCLayoutL", CTestSDKNotes::TestNNCLayoutL ),
        ENTRY( "TestNNCNoteHeightL", CTestSDKNotes::TestNNCNoteHeightL ),
        ENTRY( "TestNNCNoteWidthL", CTestSDKNotes::TestNNCNoteWidthL ),
        ENTRY( "TestNNCHandlePointerEventL", CTestSDKNotes::TestNNCHandlePointerEventL ),
        ENTRY( "TestNNCSetDynamicTextL", CTestSDKNotes::TestNNCSetDynamicTextL ),
        ENTRY( "TestNNCUpdateAndFormatLabelsL", CTestSDKNotes::TestNNCUpdateAndFormatLabelsL ),
        ENTRY( "TestNNCUpdateLabelsLeaveL", CTestSDKNotes::TestNNCUpdateLabelsLeaveL ),
        ENTRY( "TestNNCUpdateLabelsL", CTestSDKNotes::TestNNCUpdateLabelsL ),
        ENTRY( "TestNNCSetLabelReserveLengthL", CTestSDKNotes::TestNNCSetLabelReserveLengthL ),
        ENTRY( "TestNNCMopSupplyObjectL", CTestSDKNotes::TestNNCMopSupplyObjectL ),
        ENTRY( "TestNNCSetBgRectL", CTestSDKNotes::TestNNCSetBgRectL ),


        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );
    }

//  [End of File]
