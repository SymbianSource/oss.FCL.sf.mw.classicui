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
* Description:  Test EIKDIALG.H
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eikdialg.h>
#include <testsdkdialogs.rsg>
#include <coeaui.h>
#include <avkon.rsg>
#include <eikcapc.h> 
#include <eikedwin.h> 
#include <eikbtgpc.h> 
#include <coecntrl.h>
#include <akncontrol.h> 
#include <coedef.h>
#include <akndef.h>
#include <eikon.hrh>
#include <uikon.hrh>
#include <s32std.h>
#include <eikmfne.h> 
#include <eikfpne.h>
#include <eikseced.h> 
#include <eikgted.h> 
#include <txtglobl.h> 
#include <barsread.h>
#include <eikrted.h> 
#include <flddef.h>
#include <s32mem.h>
#include <eikmover.h>
#include <eikdpage.h> 
#include <coecobs.h>
#include <aknborders.h> 
#include <eiktxlbm.h> 
#include <txtrich.h>

#include "testsdkdialogs.hrh"
#include "testsdkdialogs.h"
#include "testsdkdialogscontrol.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKDialogs::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKDialogs::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestsdkdialogs::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKDialogs::RunMethodL( CStifItemParser& aItem ) 
    {
    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestDCEikDialogL", CTestSDKDialogs::TestDCEikDialogL ),
        ENTRY( "TestDDeconstructorL", CTestSDKDialogs::TestDDeconstructorL ),
        ENTRY( "TestDExecuteLD", CTestSDKDialogs::TestDExecuteLD ),
        ENTRY( "TestDPrepareLC", CTestSDKDialogs::TestDPrepareLC ),
        ENTRY( "TestDReadResourceLC", CTestSDKDialogs::TestDReadResourceLC ),
        ENTRY( "TestDRunLD", CTestSDKDialogs::TestDRunLD ),
        ENTRY( "TestDSetTitleTDesCL", CTestSDKDialogs::TestDSetTitleTDesCL ),
        ENTRY( "TestDSetTitleResourceL", CTestSDKDialogs::TestDSetTitleResourceL ),
        ENTRY( "TestDSetPageDimmedNowL", CTestSDKDialogs::TestDSetPageDimmedNowL ),
        ENTRY( "TestDSetLineNonFocusingL", CTestSDKDialogs::TestDSetLineNonFocusingL ),
        ENTRY( "TestDSetLineDimmedNowL", CTestSDKDialogs::TestDSetLineDimmedNowL ),
        ENTRY( "TestDMakeLineVisibleL", CTestSDKDialogs::TestDMakeLineVisibleL ),
        ENTRY( "TestDMakeWholeLineVisibleL", CTestSDKDialogs::TestDMakeWholeLineVisibleL ),
        ENTRY( "TestDDeleteLineL", CTestSDKDialogs::TestDDeleteLineL ),
        ENTRY( "TestDInsertLineL", CTestSDKDialogs::TestDInsertLineL ),
        ENTRY( "TestDMakePanelButtonVisibleL", CTestSDKDialogs::TestDMakePanelButtonVisibleL ),
        ENTRY( "TestDTryChangeFocusToL", CTestSDKDialogs::TestDTryChangeFocusToL ),
        ENTRY( "TestDSwitchLineLatencyL", CTestSDKDialogs::TestDSwitchLineLatencyL ),
        ENTRY( "TestDSetPageDensePackingL", CTestSDKDialogs::TestDSetPageDensePackingL ),
        ENTRY( "TestDConstructAutoDialogLC", CTestSDKDialogs::TestDConstructAutoDialogLC ),
        ENTRY( "TestDDeclareItemAutoL", CTestSDKDialogs::TestDDeclareItemAutoL ),
        ENTRY( "TestDLayoutL", CTestSDKDialogs::TestDLayoutL ),
        ENTRY( "TestDPreferredSizeL", CTestSDKDialogs::TestDPreferredSizeL ),
        ENTRY( "TestDCreateLineByTypeL", CTestSDKDialogs::TestDCreateLineByTypeL ),
        ENTRY( "TestDCreateLineByTypePageIdL", CTestSDKDialogs::TestDCreateLineByTypePageIdL ),
        ENTRY( "TestDSetControlCaptionTextL", CTestSDKDialogs::TestDSetControlCaptionTextL ),
        ENTRY( "TestDSetControlCaptionResourceIdL", CTestSDKDialogs::TestDSetControlCaptionResourceIdL ),
        ENTRY( "TestDControlCaptionL", CTestSDKDialogs::TestDControlCaptionL ),
        ENTRY( "TestDControlL", CTestSDKDialogs::TestDControlL ),
        ENTRY( "TestDControlOrNullL", CTestSDKDialogs::TestDControlOrNullL ),
        ENTRY( "TestDButtonGroupContainerL", CTestSDKDialogs::TestDButtonGroupContainerL ),
        ENTRY( "TestDTitleL", CTestSDKDialogs::TestDTitleL ),
        ENTRY( "TestDActivePageIdL", CTestSDKDialogs::TestDActivePageIdL ),
        ENTRY( "TestDActivateFirstPageL", CTestSDKDialogs::TestDActivateFirstPageL ),
        ENTRY( "TestDSetEditableL", CTestSDKDialogs::TestDSetEditableL ),
        ENTRY( "TestDIsEditableL", CTestSDKDialogs::TestDIsEditableL ),
        ENTRY( "TestDOfferKeyEventL", CTestSDKDialogs::TestDOfferKeyEventL ),
        ENTRY( "TestDFocusChangedL", CTestSDKDialogs::TestDFocusChangedL ),
        ENTRY( "TestDGetColorUseListL", CTestSDKDialogs::TestDGetColorUseListL ),
        ENTRY( "TestDHandleResourceChangeL", CTestSDKDialogs::TestDHandleResourceChangeL ),
        ENTRY( "TestDInputCapabilitiesL", CTestSDKDialogs::TestDInputCapabilitiesL ),
        ENTRY( "TestDMakeVisibleL", CTestSDKDialogs::TestDMakeVisibleL ),
        ENTRY( "TestDHandlePointerEventL", CTestSDKDialogs::TestDHandlePointerEventL ),
        ENTRY( "TestDPrepareForFocusTransitionL", CTestSDKDialogs::TestDPrepareForFocusTransitionL ),
        ENTRY( "TestDPageChangedL", CTestSDKDialogs::TestDPageChangedL ),
        ENTRY( "TestDLineChangedL", CTestSDKDialogs::TestDLineChangedL ),
        ENTRY( "TestDCreateCustomControlL", CTestSDKDialogs::TestDCreateCustomControlL ),
        ENTRY( "TestDConvertCustomControlTypeToBaseControlTypeL", CTestSDKDialogs::TestDConvertCustomControlTypeToBaseControlTypeL ),
        ENTRY( "TestDGetCustomAutoValueL", CTestSDKDialogs::TestDGetCustomAutoValueL ),
        ENTRY( "TestDPrepareContextL", CTestSDKDialogs::TestDPrepareContextL ),
        ENTRY( "TestDWriteInternalStateL", CTestSDKDialogs::TestDWriteInternalStateL ),
        ENTRY( "TestDCountComponentControlsL", CTestSDKDialogs::TestDCountComponentControlsL ),
        ENTRY( "TestDComponentControlL", CTestSDKDialogs::TestDComponentControlL ),
        ENTRY( "TestDGetNumberOfLinesOnPageL", CTestSDKDialogs::TestDGetNumberOfLinesOnPageL ),
        ENTRY( "TestDGetNumberOfPagesL", CTestSDKDialogs::TestDGetNumberOfPagesL ),
        ENTRY( "TestDGetLineByLineAndPageIndexL", CTestSDKDialogs::TestDGetLineByLineAndPageIndexL ),
        ENTRY( "TestDHandleControlEventL", CTestSDKDialogs::TestDHandleControlEventL ),
        ENTRY( "TestDTryExitL", CTestSDKDialogs::TestDTryExitL ),
        ENTRY( "TestDAdjustAllIdsOnPageL", CTestSDKDialogs::TestDAdjustAllIdsOnPageL ),
        ENTRY( "TestDConstructSleepingDialogL", CTestSDKDialogs::TestDConstructSleepingDialogL ),
        ENTRY( "TestDConstructSleepingAlertDialogL", CTestSDKDialogs::TestDConstructSleepingAlertDialogL ),
        ENTRY( "TestDRouseSleepingDialogL", CTestSDKDialogs::TestDRouseSleepingDialogL ),
        ENTRY( "TestDExitSleepingDialogL", CTestSDKDialogs::TestDExitSleepingDialogL ),
        ENTRY( "TestDIdOfFocusControlL", CTestSDKDialogs::TestDIdOfFocusControlL ),
        ENTRY( "TestDFindLineIndexL", CTestSDKDialogs::TestDFindLineIndexL ),
        ENTRY( "TestDLineL", CTestSDKDialogs::TestDLineL ),
        ENTRY( "TestDCurrentLineL", CTestSDKDialogs::TestDCurrentLineL ),
        ENTRY( "TestDRotateFocusByL", CTestSDKDialogs::TestDRotateFocusByL ),
        ENTRY( "TestDActivePageIndexL", CTestSDKDialogs::TestDActivePageIndexL ),
        ENTRY( "TestDResetLineMinimumSizesL", CTestSDKDialogs::TestDResetLineMinimumSizesL ),
        ENTRY( "TestDSwapButtonGroupContainerL", CTestSDKDialogs::TestDSwapButtonGroupContainerL ),
        ENTRY( "TestDButtonCommandObserverL", CTestSDKDialogs::TestDButtonCommandObserverL ),
        ENTRY( "TestDOkToExitL", CTestSDKDialogs::TestDOkToExitL ),
        ENTRY( "TestDPreLayoutDynInitL", CTestSDKDialogs::TestDPreLayoutDynInitL ),
        ENTRY( "TestDPostLayoutDynInitL", CTestSDKDialogs::TestDPostLayoutDynInitL ),
        ENTRY( "TestDSetInitialCurrentLineL", CTestSDKDialogs::TestDSetInitialCurrentLineL ),
        ENTRY( "TestDHandleControlStateChangeL", CTestSDKDialogs::TestDHandleControlStateChangeL ),
        ENTRY( "TestDHandleInteractionRefusedL", CTestSDKDialogs::TestDHandleInteractionRefusedL ),
        ENTRY( "TestDSetSizeAndPositionL", CTestSDKDialogs::TestDSetSizeAndPositionL ),
        ENTRY( "TestDBorderStyleL", CTestSDKDialogs::TestDBorderStyleL ),
        ENTRY( "TestDMappedCommandIdL", CTestSDKDialogs::TestDMappedCommandIdL ),
        ENTRY( "TestDFormFlagsFromActivePageL", CTestSDKDialogs::TestDFormFlagsFromActivePageL ),
        ENTRY( "TestDGetFirstLineOnFirstPageOrNullL", CTestSDKDialogs::TestDGetFirstLineOnFirstPageOrNullL ),
        ENTRY( "TestDControlsOnPageL", CTestSDKDialogs::TestDControlsOnPageL ),
        ENTRY( "TestDMopSupplyObjectL", CTestSDKDialogs::TestDMopSupplyObjectL ),
        ENTRY( "TestDExtensionL", CTestSDKDialogs::TestDExtensionL ),
        ENTRY( "TestDDialogFlagsL", CTestSDKDialogs::TestDDialogFlagsL ),
        ENTRY( "TestDDeclareAutoTextEditorL", CTestSDKDialogs::TestDDeclareAutoTextEditorL ),
        ENTRY( "TestDDeclareAutoNumberEditorL", CTestSDKDialogs::TestDDeclareAutoNumberEditorL ),
        ENTRY( "TestDDeclareAutoRangeEditorL", CTestSDKDialogs::TestDDeclareAutoRangeEditorL ),
        ENTRY( "TestDDeclareAutoTimeEditorL", CTestSDKDialogs::TestDDeclareAutoTimeEditorL ),
        ENTRY( "TestDDeclareAutoDateEditorL", CTestSDKDialogs::TestDDeclareAutoDateEditorL ),
        ENTRY( "TestDDeclareAutoTimeAndDateEditorL", CTestSDKDialogs::TestDDeclareAutoTimeAndDateEditorL ),
        ENTRY( "TestDDeclareAutoDurationEditorL", CTestSDKDialogs::TestDDeclareAutoDurationEditorL ),
        ENTRY( "TestDDeclareAutoTimeOffsetEditorL", CTestSDKDialogs::TestDDeclareAutoTimeOffsetEditorL ),
        ENTRY( "TestDDeclareAutoFixedPointEditorL", CTestSDKDialogs::TestDDeclareAutoFixedPointEditorL ),
        ENTRY( "TestDDeclareAutoSecretEditorL", CTestSDKDialogs::TestDDeclareAutoSecretEditorL ),
        ENTRY( "TestDAddAutoTextEditorL", CTestSDKDialogs::TestDAddAutoTextEditorL ),
        ENTRY( "TestDAddAutoGlobalTextEditorL", CTestSDKDialogs::TestDAddAutoGlobalTextEditorL ),
        ENTRY( "TestDAddAutoRichTextEditorL", CTestSDKDialogs::TestDAddAutoRichTextEditorL ),
        ENTRY( "TestDAddAutoNumberEditorL", CTestSDKDialogs::TestDAddAutoNumberEditorL ),
        ENTRY( "TestDAddAutoRangeEditorL", CTestSDKDialogs::TestDAddAutoRangeEditorL ),
        ENTRY( "TestDAddAutoTimeEditorL", CTestSDKDialogs::TestDAddAutoTimeEditorL ),
        ENTRY( "TestDAddAutoDateEditorL", CTestSDKDialogs::TestDAddAutoDateEditorL ),
        ENTRY( "TestDAddAutoTimeAndDateEditorL", CTestSDKDialogs::TestDAddAutoTimeAndDateEditorL ),
        ENTRY( "TestDAddAutoDurationEditorL", CTestSDKDialogs::TestDAddAutoDurationEditorL ),
        ENTRY( "TestDAddAutoTimeOffsetEditorL", CTestSDKDialogs::TestDAddAutoTimeOffsetEditorL ),
        ENTRY( "TestDAddAutoFloatEditorL", CTestSDKDialogs::TestDAddAutoFloatEditorL ),
        ENTRY( "TestDAddAutoFixedPointEditorL", CTestSDKDialogs::TestDAddAutoFixedPointEditorL ),
        ENTRY( "TestDAddAutoSecretEditorL", CTestSDKDialogs::TestDAddAutoSecretEditorL ),
        ENTRY( "TestDSetLabelByDesL", CTestSDKDialogs::TestDSetLabelByDesL ),
        ENTRY( "TestDSetLabelByResourceIdL", CTestSDKDialogs::TestDSetLabelByResourceIdL ),
        ENTRY( "TestDSetLabelReserveLengthL", CTestSDKDialogs::TestDSetLabelReserveLengthL ),
        ENTRY( "TestDSetEdwinTextL", CTestSDKDialogs::TestDSetEdwinTextL ),
        ENTRY( "TestDSetTextEditorTextL", CTestSDKDialogs::TestDSetTextEditorTextL ),
        ENTRY( "TestDResetSecretEditorL", CTestSDKDialogs::TestDResetSecretEditorL ),
        ENTRY( "TestDSetFloatingPointEditorValueL", CTestSDKDialogs::TestDSetFloatingPointEditorValueL ),
        ENTRY( "TestDSetFixedPointEditorValueL", CTestSDKDialogs::TestDSetFixedPointEditorValueL ),
        ENTRY( "TestDSetFixedPointEditorDecimalL", CTestSDKDialogs::TestDSetFixedPointEditorDecimalL ),
        ENTRY( "TestDSetNumberEditorMinAndMaxL", CTestSDKDialogs::TestDSetNumberEditorMinAndMaxL ),
        ENTRY( "TestDSetNumberEditorValueL", CTestSDKDialogs::TestDSetNumberEditorValueL ),
        ENTRY( "TestDSetFloatEditorMinAndMaxL", CTestSDKDialogs::TestDSetFloatEditorMinAndMaxL ),
        ENTRY( "TestDSetFloatEditorValueL", CTestSDKDialogs::TestDSetFloatEditorValueL ),
        ENTRY( "TestDSetRangeEditorMinAndMaxL", CTestSDKDialogs::TestDSetRangeEditorMinAndMaxL ),
        ENTRY( "TestDSetRangeEditorValueL", CTestSDKDialogs::TestDSetRangeEditorValueL ),
        ENTRY( "TestDSetTTimeEditorMinAndMaxL", CTestSDKDialogs::TestDSetTTimeEditorMinAndMaxL ),
        ENTRY( "TestDSetTTimeEditorValueL", CTestSDKDialogs::TestDSetTTimeEditorValueL ),
        ENTRY( "TestDSetDurationEditorMinAndMaxL", CTestSDKDialogs::TestDSetDurationEditorMinAndMaxL ),
        ENTRY( "TestDSetDurationEditorValueL", CTestSDKDialogs::TestDSetDurationEditorValueL ),
        ENTRY( "TestDSetTimeOffsetEditorMinAndMaxL", CTestSDKDialogs::TestDSetTimeOffsetEditorMinAndMaxL ),
        ENTRY( "TestDSetTimeOffsetEditorValueL", CTestSDKDialogs::TestDSetTimeOffsetEditorValueL ),
        ENTRY( "TestDSetListBoxCurrentItemL", CTestSDKDialogs::TestDSetListBoxCurrentItemL ),
        ENTRY( "TestDSetFileNameL", CTestSDKDialogs::TestDSetFileNameL ),
        ENTRY( "TestDGetLabelTextL", CTestSDKDialogs::TestDGetLabelTextL ),
        ENTRY( "TestDGetEdwinTextL", CTestSDKDialogs::TestDGetEdwinTextL ),
        ENTRY( "TestDGetTextEditorTextL", CTestSDKDialogs::TestDGetTextEditorTextL ),
        ENTRY( "TestDGetSecretEditorTextL", CTestSDKDialogs::TestDGetSecretEditorTextL ),
        ENTRY( "TestDFloatingPointEditorValueL", CTestSDKDialogs::TestDFloatingPointEditorValueL ),
        ENTRY( "TestDFixedPointEditorValueL", CTestSDKDialogs::TestDFixedPointEditorValueL ),
        ENTRY( "TestDFixedPointEditorDecimalL", CTestSDKDialogs::TestDFixedPointEditorDecimalL ),
        ENTRY( "TestDFloatEditorValueL", CTestSDKDialogs::TestDFloatEditorValueL ),
        ENTRY( "TestDNumberEditorValueL", CTestSDKDialogs::TestDNumberEditorValueL ),
        ENTRY( "TestDRangeEditorValueL", CTestSDKDialogs::TestDRangeEditorValueL ),
        ENTRY( "TestDTTimeEditorValueL", CTestSDKDialogs::TestDTTimeEditorValueL ),
        ENTRY( "TestDDurationEditorValueL", CTestSDKDialogs::TestDDurationEditorValueL ),
        ENTRY( "TestDTimeOffsetEditorValueL", CTestSDKDialogs::TestDTimeOffsetEditorValueL ),
        ENTRY( "TestDGetAutoValuesFromPageL", CTestSDKDialogs::TestDGetAutoValuesFromPageL ),
        ENTRY( "TestDListBoxCurrentItemL", CTestSDKDialogs::TestDListBoxCurrentItemL ),
        ENTRY( "TestDGetFileNameL", CTestSDKDialogs::TestDGetFileNameL ),
        ENTRY( "TestDUpdatePageL", CTestSDKDialogs::TestDUpdatePageL ),
        ENTRY( "TestDHandleDialogPageEventL", CTestSDKDialogs::TestDHandleDialogPageEventL ),
        ENTRY( "TestDPublishDialogL", CTestSDKDialogs::TestDPublishDialogL ),
        ENTRY( "TestDSetMediatorObserverL", CTestSDKDialogs::TestDSetMediatorObserverL ),
        ENTRY( "TestDSlideDialogL", CTestSDKDialogs::TestDSlideDialogL ),
        ENTRY( "TestDSetMultilineQueryL", CTestSDKDialogs::TestDSetMultilineQueryL ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// =========================== CLASS CEIKDIALOG ================================
// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDCEikDialogL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDCEikDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    
    STIF_ASSERT_NOT_NULL( dialog );
    
    CleanupStack::PopAndDestroy( dialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeconstructorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    
    STIF_ASSERT_NOT_NULL( dialog );
    
    CleanupStack::Pop( dialog );
    delete dialog;
    
    return KErrNone;
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDExecuteLD 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDExecuteLD( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    
    TInt flag = dialog->ExecuteLD( R_TESTSDK_DIALOG );
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDPrepareLC 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDPrepareLC( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDReadResourceLC 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDReadResourceLC( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    
    dialog->ReadResourceLC( R_TESTSDK_DIALOG );
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDRunLD 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDRunLD( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetTitleTDesCL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetTitleTDesCL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    _LIT( KTitle, "TestSDKDialogs" );
    const TInt lengthC = 20;
    TBuf<lengthC> title( KTitle );
    STIF_ASSERT_NOT_LEAVES( dialog->SetTitleL( title ) );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetTitleResourceL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetTitleResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    STIF_ASSERT_NOT_LEAVES( dialog->SetTitleL( R_TESTSDK_TITLE ) );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetPageDimmedNowL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetPageDimmedNowL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->SetPageDimmedNow( 0, EFalse );
    dialog->SetPageDimmedNow( 0, ETrue );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetLineNonFocusingL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetLineNonFocusingL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->SetLineNonFocusing( EDialogLine );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetLineDimmedNowL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetLineDimmedNowL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->SetLineDimmedNow( EDialogLine, EFalse );
    dialog->SetLineDimmedNow( EDialogLine, ETrue );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDMakeLineVisibleL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDMakeLineVisibleL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->MakeLineVisible( EDialogLine, EFalse );
    dialog->MakeLineVisible( EDialogLine, ETrue );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDMakeWholeLineVisibleL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDMakeWholeLineVisibleL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->MakeWholeLineVisible( EDialogLine, EFalse );
    dialog->MakeWholeLineVisible( EDialogLine, ETrue );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeleteLineL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeleteLineL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->DeleteLine( EDialogLine, ETrue );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    dialog = NULL;
    
    dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->DeleteLine( EDialogLine, EFalse );
    
    flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDInsertLineL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDInsertLineL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->InsertLineL( 0, R_TESTSDK_LINE, 0 );
    CEikEdwin* edwin = static_cast<CEikEdwin*> ( dialog->ControlOrNull( EEdwinLine ) );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDMakePanelButtonVisibleL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDMakePanelButtonVisibleL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->MakePanelButtonVisible( R_AVKON_SOFTKEYS_OK_CANCEL, EFalse );
    dialog->MakePanelButtonVisible( R_AVKON_SOFTKEYS_OK_CANCEL, ETrue );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDTryChangeFocusToL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDTryChangeFocusToL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->InsertLineL( 1, R_TESTSDK_LINE );
    dialog->InsertLineL( 1, R_TESTSDK_LINE2 );
    
    dialog->CTestSDKDialogsSetInitialCurrentLine();
    CEikCaptionedControl* curLine = dialog->CTestSDKDialogsCurrentLine();
    if (curLine)
        {
        dialog->TryChangeFocusToL(curLine->iId);
        }
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSwitchLineLatencyL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSwitchLineLatencyL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->InsertLineL( 1, R_TESTSDK_LINE );
    dialog->InsertLineL( 2, R_TESTSDK_LINE2 );
    dialog->SwitchLineLatency( EEdwinLine, EEdwinLine2 );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetPageDensePackingL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetPageDensePackingL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->InsertLineL( 1, R_TESTSDK_LINE );
    dialog->SetPageDensePacking( 0, ETrue );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDConstructAutoDialogLC 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDConstructAutoDialogLC( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    
    dialog->ConstructAutoDialogLC( EEikDialogFlagFillScreen, R_AVKON_SOFTKEYS_OK_CANCEL );
    dialog->InsertLineL( 0, R_TESTSDK_LINE );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeclareItemAutoL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeclareItemAutoL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    TInt value = 0;
    dialog->DeclareItemAuto( EDialogLine, EEikCtEdwin, &value );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDLayoutL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDLayoutL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->Layout();
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDPreferredSizeL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDPreferredSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->Layout();
    const TInt lengthC = 10;
    TSize size( lengthC, lengthC );
    TSize preferredSize = dialog->PreferredSize( size );
    TPoint point( preferredSize.AsPoint() );
    
    STIF_ASSERT_EQUALS( lengthC, point.iX );
    STIF_ASSERT_EQUALS( lengthC, point.iY );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDCreateLineByTypeL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDCreateLineByTypeL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    const TInt lengthC = 20;
    _LIT( KCaption, "LineByType" );
    TBufC<lengthC> caption( KCaption );
    CEikEdwin* edwin = static_cast<CEikEdwin*> ( dialog->CreateLineByTypeL( 
        caption, ELineByType, EEikCtEdwin, NULL ) );
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    const TInt textLimitC = 100;
    const TInt widthC = 10;
    edwin->ConstructL( 0, lengthC, textLimitC, widthC );
    edwin->CreateTextViewL();
    edwin->SetTextL( &caption );
    CleanupStack::Pop( edwin );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDCreateLineByTypePageIdL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDCreateLineByTypePageIdL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    _LIT( KCaption, "LineByType" );
    const TInt lengthC = 20;
    TBufC<lengthC> caption( KCaption );
    CEikEdwin* edwin = static_cast<CEikEdwin*> ( dialog->CreateLineByTypeL( 
        caption, 0, ELineByType, EEikCtEdwin, NULL ) );
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    const TInt textLimitC = 100;
    const TInt widthC = 10;
    edwin->ConstructL( 0, lengthC, textLimitC, widthC );
    edwin->CreateTextViewL();
    edwin->SetTextL( &caption );
    CleanupStack::Pop( edwin );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetControlCaptionTextL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetControlCaptionTextL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    _LIT( KCaption, "CaptionText" );
    const TInt lengthC = 20;
    TBufC<lengthC> captionValue( KCaption );
    dialog->SetControlCaptionL( EDialogLine, captionValue );
    
    CEikLabel* caption = dialog->ControlCaption( EDialogLine );
    HBufC* captionbuf = caption->Text()->AllocLC();
    STIF_ASSERT_EQUALS( 0, captionbuf->Compare( KCaption ) );
    CleanupStack::PopAndDestroy( captionbuf );

    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetControlCaptionResourceIdL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetControlCaptionResourceIdL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->SetControlCaptionL( EDialogLine, R_TESTSDK_CAPTION );
    CEikLabel* caption = dialog->ControlCaption( EDialogLine );
    HBufC* captionbuf = caption->Text()->AllocLC();
    _LIT( KCaption, "CaptionResource" );
    STIF_ASSERT_EQUALS( 0, captionbuf->Compare( KCaption ) );
    CleanupStack::PopAndDestroy( captionbuf );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDControlCaptionL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDControlCaptionL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    _LIT( KCaption, "ControlCaption" );
    const TInt lengthC = 20;
    TBufC<lengthC> captionValue( KCaption );
    dialog->SetControlCaptionL( EDialogLine, captionValue );
    
    CEikLabel* caption = dialog->ControlCaption( EDialogLine );
    HBufC* captionbuf = caption->Text()->AllocLC();
    STIF_ASSERT_EQUALS( 0, captionbuf->Compare( KCaption ) );
    CleanupStack::PopAndDestroy( captionbuf );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDControlL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDControlL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    CEikEdwin* edwin = static_cast<CEikEdwin*> ( dialog->Control( EDialogLine ) );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDControlOrNullL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDControlOrNullL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    CEikEdwin* edwin = static_cast<CEikEdwin*> ( dialog->ControlOrNull( EDialogLine ) );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDButtonGroupContainerL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDButtonGroupContainerL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    CEikButtonGroupContainer* container = &( dialog->ButtonGroupContainer() );
    STIF_ASSERT_NOT_NULL( container );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDTitleL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDTitleL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    CEikMover* title = &( dialog->Title() );
    STIF_ASSERT_NOT_NULL( title );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDActivePageIdL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDActivePageIdL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    TInt pageid = dialog->ActivePageId();
    STIF_ASSERT_EQUALS( 0, pageid);
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDActivateFirstPageL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDActivateFirstPageL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->ActivateFirstPageL();
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetEditableL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetEditableL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->SetEditableL( EFalse );
    dialog->SetEditableL( ETrue );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDIsEditableL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDIsEditableL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->SetEditableL( ETrue );
    TBool edit = dialog->IsEditable();
    STIF_ASSERT_TRUE( edit );
    
    dialog->SetEditableL( EFalse );
    edit = dialog->IsEditable();
    STIF_ASSERT_FALSE( edit );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDOfferKeyEventL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    TKeyEvent event;
    event.iCode = '0';
    TKeyResponse response = dialog->OfferKeyEventL( event, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDFocusChangedL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->InsertLineL( 1, R_TESTSDK_LINE );
    dialog->InsertLineL( 1, R_TESTSDK_LINE2 );
    
    dialog->CTestSDKDialogsSetInitialCurrentLine();
    CEikCaptionedControl* curLine = dialog->CTestSDKDialogsCurrentLine();
    if (curLine)
        {
        dialog->TryChangeFocusToL(curLine->iId);
        }
    
    dialog->FocusChanged( ENoDrawNow );
    dialog->FocusChanged( EDrawNow );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetColorUseListL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    CArrayFix<TCoeColorUse>* colorList = new (ELeave) CArrayFixFlat<TCoeColorUse>(1);
    CleanupStack::PushL(colorList);
    dialog->GetColorUseListL( *colorList ); 
    STIF_ASSERT_NOT_NULL( colorList );
    CleanupStack::PopAndDestroy( colorList );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDHandleResourceChangeL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    dialog->HandleResourceChange( KEikColorResourceChange );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDInputCapabilitiesL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    TCoeInputCapabilities capability = dialog->InputCapabilities();
    TUint uvalue = capability.Capabilities();
    STIF_ASSERT_TRUE( uvalue == TCoeInputCapabilities::ENavigation );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDMakeVisibleL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDMakeVisibleL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->MakeVisible( EFalse );
    dialog->MakeVisible( ETrue );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDHandlePointerEventL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    STIF_ASSERT_NOT_LEAVES( dialog->HandlePointerEventL( event ) );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDPrepareForFocusTransitionL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDPrepareForFocusTransitionL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->PrepareForFocusTransitionL();
    TInt lineId = dialog->IdOfFocusControl();
    
    STIF_ASSERT_TRUE( lineId = EDialogLine );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDPageChangedL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDPageChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->PageChangedL( 1 );
    dialog->ActivateFirstPageL();
    TInt pageId = dialog->ActivePageId();
    STIF_ASSERT_TRUE( pageId == 0 );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );

    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDLineChangedL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDLineChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->InsertLineL( 0, R_TESTSDK_LINE, 0 );
    dialog->LineChangedL( EEdwinLine );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDCreateCustomControlL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDCreateCustomControlL( CStifItemParser& /*aItem*/ )
    {
    // This function will call panic directly, so no need to test it temporary
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDConvertCustomControlTypeToBaseControlTypeL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDConvertCustomControlTypeToBaseControlTypeL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    TInt controlType = EEikCtEdwin;
    MEikDialogPageObserver::TFormControlTypes type = 
        dialog->ConvertCustomControlTypeToBaseControlType( controlType );
    STIF_ASSERT_EQUALS( type, MEikDialogPageObserver::EUnknownType );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetCustomAutoValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetCustomAutoValueL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    // GetCustomAutoValue will call assert efalse directly, no need to test it temporary
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDPrepareContextL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDPrepareContextL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    CWindowGc& gc = CCoeEnv::Static()->SystemGc();
    
    dialog->ActivateGc();
    dialog->PrepareContext();
    dialog->DeactivateGc();
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDWriteInternalStateL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    const TInt LengthC = 200;
    CBufFlat* buf = CBufFlat::NewL( LengthC );
    CleanupStack::PushL( buf );
    RBufWriteStream writeStream;
    CleanupClosePushL( writeStream );
    writeStream.Open( *buf );
        
    STIF_ASSERT_NOT_LEAVES( dialog->WriteInternalStateL( writeStream ) );
    STIF_ASSERT_NOT_NULL( buf );
    STIF_ASSERT_NOT_NULL( &writeStream );
    
    CleanupStack::PopAndDestroy( &writeStream );
    CleanupStack::PopAndDestroy( buf );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDCountComponentControlsL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    TInt count = dialog->CountComponentControls();
    STIF_ASSERT_EQUALS( 2, count );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDComponentControlL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDComponentControlL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    CEikMover* mover = static_cast<CEikMover*> ( dialog->ComponentControl( 1 ) );
    STIF_ASSERT_NOT_NULL( mover );

    CCoeControl* selector = static_cast<CCoeControl*> ( dialog->ComponentControl( 2 ) );
    STIF_ASSERT_NOT_NULL( selector );
    
    const TInt numberC =3;
    CCoeControl* otherselector = static_cast<CCoeControl*> ( dialog->ComponentControl( numberC ) );
    STIF_ASSERT_NOT_NULL( otherselector );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetNumberOfLinesOnPageL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetNumberOfLinesOnPageL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->InsertLineL( 1, R_TESTSDK_LINE );
    dialog->InsertLineL( 1, R_TESTSDK_LINE2 );
    
    TInt number = dialog->GetNumberOfLinesOnPage( 0 );
    const TInt numberC =3;
    STIF_ASSERT_EQUALS( numberC, number );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetNumberOfPagesL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetNumberOfPagesL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    TInt number = dialog->GetNumberOfPages();
    STIF_ASSERT_EQUALS( 2, number );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetLineByLineAndPageIndexL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetLineByLineAndPageIndexL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    CEikCaptionedControl* control = dialog->GetLineByLineAndPageIndex( ETESTSDKPageLine2Editor , 1 );
    STIF_ASSERT_NOT_NULL( dialog );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDHandleControlEventL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDHandleControlEventL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    CEikEdwin* edwin = static_cast<CEikEdwin*> ( dialog->ControlOrNull( ETESTSDKPageLine1Editor ) );
    CEikTimeAndDateEditor* dateTimeEditor = NULL;
    dialog->HandleControlEventL( edwin, MCoeControlObserver::EEventStateChanged );
    dialog->HandleControlEventL( edwin, MCoeControlObserver::EEventInteractionRefused );
    dialog->HandleControlEventL( edwin, MCoeControlObserver::EEventPrepareFocusTransition );
    dialog->HandleControlEventL( dateTimeEditor, MCoeControlObserver::EEventStateChanged );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDTryExitL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDTryExitL( CStifItemParser& /*aItem*/ )
    {
  
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    
    dialog->ConstructAutoDialogLC( EEikDialogFlagNoUserExit, R_AVKON_SOFTKEYS_OK_CANCEL );
    dialog->TryExitL( EEikBidCancel );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    
    dialog->ConstructAutoDialogLC( EEikDialogFlagNotifyEsc, R_AVKON_SOFTKEYS_OK_CANCEL );
    CleanupStack::Pop( dialog );
    dialog->TryExitL( EEikBidCancel );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAdjustAllIdsOnPageL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAdjustAllIdsOnPageL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->AdjustAllIdsOnPage( 1, 2 );
    TInt id = ETESTSDKPageLine2Editor + 2;
    CEikCaptionedControl* control = dialog->GetLineByLineAndPageIndex( id , 1 );
    STIF_ASSERT_NOT_NULL( dialog );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDConstructSleepingDialogL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDConstructSleepingDialogL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    dialog->ConstructSleepingDialogL( R_TESTSDK_PAGE );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDConstructSleepingAlertDialogL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDConstructSleepingAlertDialogL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    dialog->ConstructSleepingAlertDialogL( R_TESTSDK_PAGE );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDRouseSleepingDialogL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDRouseSleepingDialogL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->RouseSleepingDialog();
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );

    dialog->ConstructSleepingDialogL( R_TESTSDK_PAGE );
    dialog->RouseSleepingDialog();
    dialog->RunLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDExitSleepingDialogL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDExitSleepingDialogL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->ExitSleepingDialog();
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );

    dialog->ConstructSleepingDialogL( R_TESTSDK_PAGE );
    dialog->ExitSleepingDialog();
    dialog->RunLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDIdOfFocusControlL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDIdOfFocusControlL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->InsertLineL( 1, R_TESTSDK_LINE );
    dialog->InsertLineL( 1, R_TESTSDK_LINE2 );
    
    dialog->CTestSDKDialogsSetInitialCurrentLine();
    CEikCaptionedControl* curLine = dialog->CTestSDKDialogsCurrentLine();
    if (curLine)
        {
        dialog->TryChangeFocusToL(curLine->iId);
        }
    
    TInt idFocus = dialog->IdOfFocusControl();
    STIF_ASSERT_TRUE( EDialogLine == idFocus );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDFindLineIndexL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDFindLineIndexL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->ActivateFirstPageL();
    CEikEdwin* edwin = static_cast<CEikEdwin*> ( dialog->ControlOrNull( ETESTSDKPageLine1Editor ) );
    TInt index = dialog->FindLineIndex( *edwin );
    STIF_ASSERT_TRUE( index == 0 );
    
    edwin = static_cast<CEikEdwin*> ( dialog->ControlOrNull( ETESTSDKPageLine2Editor ) );
    index = dialog->FindLineIndex( *edwin );
    STIF_ASSERT_TRUE( index == KErrNotFound );
    
    CEikTimeAndDateEditor* dateTimeEditor = NULL;
    index = dialog->FindLineIndex( *dateTimeEditor );
    STIF_ASSERT_TRUE( index == KErrNotFound );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDLineL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDLineL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    CEikCaptionedControl* control = dialog->Line( EDialogLine );
    STIF_ASSERT_NOT_NULL( control );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDCurrentLineL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDCurrentLineL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->ActivateFirstPageL();
    dialog->InsertLineL( 1, R_TESTSDK_LINE );
    dialog->InsertLineL( 1, R_TESTSDK_LINE2 );
    
    dialog->CTestSDKDialogsSetInitialCurrentLine();
    CEikCaptionedControl* control = dialog->CurrentLine();
    STIF_ASSERT_NOT_NULL( control );
    
    dialog->TryChangeFocusToL(control->iId);
    TInt idFocus = dialog->IdOfFocusControl();
    STIF_ASSERT_TRUE( EDialogLine == idFocus );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDRotateFocusByL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDRotateFocusByL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->ActivateFirstPageL();
    const TInt countC = 5;
    TBool rotate = dialog->RotateFocusByL( countC );
    STIF_ASSERT_TRUE( rotate );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    
    dialog->ConstructAutoDialogLC( 0, R_AVKON_SOFTKEYS_OK_CANCEL );
    rotate = dialog->RotateFocusByL( countC );
    STIF_ASSERT_FALSE( rotate );
    
    flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDActivePageIndexL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDActivePageIndexL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->ActivateFirstPageL();
    TInt index = dialog->ActivePageIndex();
    STIF_ASSERT_EQUALS( 0, index );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDResetLineMinimumSizesL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDResetLineMinimumSizesL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->ResetLineMinimumSizes();
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSwapButtonGroupContainerL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSwapButtonGroupContainerL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    CEikButtonGroupContainer* currentBtGrp = CEikButtonGroupContainer::Current();
    STIF_ASSERT_NOT_NULL( currentBtGrp );
    CEikButtonGroupContainer* btGrp = dialog->SwapButtonGroupContainer( currentBtGrp );
    dialog->SwapButtonGroupContainer( btGrp );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDButtonCommandObserverL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDButtonCommandObserverL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    MEikCommandObserver* server = dialog->ButtonCommandObserver();
    STIF_ASSERT_NOT_NULL( server );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDOkToExitL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDOkToExitL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    TBool exit = dialog->OkToExitL( R_AVKON_SOFTKEYS_OK_CANCEL );
    STIF_ASSERT_TRUE( exit );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDPreLayoutDynInitL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->PreLayoutDynInitL();
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDPostLayoutDynInitL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->PostLayoutDynInitL();
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetInitialCurrentLineL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetInitialCurrentLineL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->SetInitialCurrentLine();
    TInt id = dialog->IdOfFocusControl();
    STIF_ASSERT_TRUE( ETESTSDKPageLine1Editor == id );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDHandleControlStateChangeL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDHandleControlStateChangeL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->HandleControlStateChangeL( ETESTSDKPageLine1Editor );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDHandleInteractionRefusedL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDHandleInteractionRefusedL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->SetLineDimmedNow( ETESTSDKPageLine1Editor, ETrue );
    dialog->HandleInteractionRefused( ETESTSDKPageLine1Editor );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetSizeAndPositionL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetSizeAndPositionL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    const TInt lengthC = 10;
    TSize size( lengthC, lengthC );
    dialog->SetSizeAndPosition( size );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDBorderStyleL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDBorderStyleL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    TInt style = dialog->BorderStyle();
    STIF_ASSERT_TRUE( TGulBorder::ENone == style );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDMappedCommandIdL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDMappedCommandIdL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    TInt id = dialog->MappedCommandId( EAknSoftkeyCancel );
    STIF_ASSERT_TRUE( id == EEikBidCancel );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDFormFlagsFromActivePageL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDFormFlagsFromActivePageL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    dialog->ActivateFirstPageL();
    TInt id = dialog->FormFlagsFromActivePage();
    STIF_ASSERT_EQUALS( 0, id );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetFirstLineOnFirstPageOrNullL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetFirstLineOnFirstPageOrNullL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    CEikCaptionedControl* control = dialog->GetFirstLineOnFirstPageOrNull();
    STIF_ASSERT_NOT_NULL( control );
    STIF_ASSERT_TRUE( control->iId == ETESTSDKPageLine1Editor );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDControlsOnPageL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDControlsOnPageL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_PAGE );
    
    RArray<CEikCaptionedControl*> control(1) ;
    CleanupClosePushL( control );
    dialog->ControlsOnPage( control, 0 );
    STIF_ASSERT_TRUE( control.Count() == 1 );
    STIF_ASSERT_TRUE( control[0]->iId == ETESTSDKPageLine1Editor );
    CleanupStack::Pop( &control );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDMopSupplyObjectL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    TTypeUid::Ptr ptr = TTypeUid::Null();
    ptr = dialog->MopSupplyObject( CEikDialog::ETypeId );
    CTestSDKDialogsControl* point = static_cast<CTestSDKDialogsControl*> ( ptr.Pointer() );
    STIF_ASSERT_NOT_NULL( point );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDExtensionL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDExtensionL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    CEikDialogExtension* extension = dialog->Extension();
    STIF_ASSERT_NOT_NULL( extension );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDialogFlagsL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDialogFlagsL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    TInt flags = dialog->DialogFlags();
    STIF_ASSERT_EQUALS( 0, flags );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeclareAutoTextEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeclareAutoTextEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGEDITOR );
    
    _LIT( KText, "TextEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> text( KText );
    dialog->DeclareAutoTextEditorL( ETESTSDKTextEditor, &text );
    
    CEikEdwin* edwin = static_cast<CEikEdwin*> ( dialog->ControlOrNull( ETESTSDKTextEditor ) );
    HBufC* textbuf = edwin->GetTextInHBufL();
    STIF_ASSERT_EQUALS( 0, textbuf->Compare( KText ) );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeclareAutoNumberEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeclareAutoNumberEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGEDITOR );
    
    const TInt numberC = 10;
    TInt number = numberC;
    dialog->DeclareAutoNumberEditor( ETESTSDKNumberEditor, &number );
    
    CEikNumberEditor* numberEditor = static_cast<CEikNumberEditor*> ( dialog->ControlOrNull( ETESTSDKNumberEditor ) );
    TInt numberGet = numberEditor->Number();
    STIF_ASSERT_EQUALS( number, numberGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeclareAutoRangeEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeclareAutoRangeEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGEDITOR );
    
    SEikRange range;
    range.iLowerLimit = 0;
    const TInt upperLimitC = 100;
    range.iUpperLimit = upperLimitC;
    dialog->DeclareAutoRangeEditor( ETESTSDKRangeEditor, &range );
    
    CEikRangeEditor * rangeEditor = static_cast<CEikRangeEditor *> ( dialog->ControlOrNull( ETESTSDKRangeEditor ) );
    SEikRange rangeGet = rangeEditor->Range();
    TInt lower = rangeGet.iLowerLimit;
    STIF_ASSERT_EQUALS( 0, lower );
    TInt upper = rangeGet.iUpperLimit;
    STIF_ASSERT_EQUALS( upperLimitC, upper );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeclareAutoTimeEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeclareAutoTimeEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGEDITOR );
    
    TDateTime datetime( 0, TMonth( 0 ), 0, 20, 20, 20, 0 );
    TTime time( datetime );
    dialog->DeclareAutoTimeEditor( ETESTSDKTimeEditor, &time );
    
    CEikTimeEditor* timeEditor = static_cast<CEikTimeEditor*> ( dialog->ControlOrNull( ETESTSDKTimeEditor ) );
    TTime timeGet = timeEditor->Time();
    STIF_ASSERT_TRUE( time == timeGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeclareAutoDateEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeclareAutoDateEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGEDITOR );
    
    TDateTime datetime( 2008, TMonth( 7 ), 8, 0, 0, 0, 0 );
    TTime date( datetime );
    dialog->DeclareAutoDateEditor( ETESTSDKDateEditor, &date );
    
    CEikDateEditor* dateEditor = static_cast<CEikDateEditor*> ( dialog->ControlOrNull( ETESTSDKDateEditor ) );
    TTime dateGet = dateEditor->Date();
    STIF_ASSERT_TRUE( date == dateGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeclareAutoTimeAndDateEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeclareAutoTimeAndDateEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGEDITOR );
    
    TDateTime datetime( 2008, TMonth( 7 ), 8, 20, 0, 0, 0 );
    TTime dateTime( datetime );
    dialog->DeclareAutoTimeAndDateEditor( ETESTSDKTimeAndDateEditor, &dateTime );
    
    CEikTimeAndDateEditor* dateTimeEditor = static_cast<CEikTimeAndDateEditor*> ( dialog->ControlOrNull( ETESTSDKTimeAndDateEditor ) );
    TTime dateTimeGet = dateTimeEditor->TimeAndDate();
    STIF_ASSERT_TRUE( dateTime == dateTimeGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeclareAutoDurationEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeclareAutoDurationEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGEDITOR );
    
    const TInt durationC(1000);
    TTimeIntervalSeconds duration( durationC );
    dialog->DeclareAutoDurationEditor( ETESTSDKDurationEditor, &duration );
    
    CEikDurationEditor* ddurationEditor = static_cast<CEikDurationEditor*> ( dialog->ControlOrNull( ETESTSDKDurationEditor ) );
    TTimeIntervalSeconds durationGet = ddurationEditor->Duration();
    STIF_ASSERT_TRUE( duration == durationGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeclareAutoTimeOffsetEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeclareAutoTimeOffsetEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGEDITOR );
    
    const TInt timeOffsetC(1000);
    TTimeIntervalSeconds timeOffset( timeOffsetC );
    dialog->DeclareAutoTimeOffsetEditor( ETESTSDKTimeOffsetEditor, &timeOffset );
    
    CEikTimeOffsetEditor* timeOffsetEditor = static_cast<CEikTimeOffsetEditor*> ( dialog->ControlOrNull( ETESTSDKTimeOffsetEditor ) );
    TTimeIntervalSeconds timeOffsetGet = timeOffsetEditor->TimeOffset();
    STIF_ASSERT_TRUE( timeOffset == timeOffsetGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeclareAutoFixedPointEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeclareAutoFixedPointEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGEDITOR );
    
    const TInt valueC(100);
    TInt value = valueC;
    dialog->DeclareAutoFixedPointEditor( ETESTSDKFixPointedEditor, &value );
    
    CEikFixedPointEditor* fixedPointEditor = static_cast<CEikFixedPointEditor*> ( dialog->ControlOrNull( ETESTSDKFixPointedEditor ) );
    TInt valueGet = fixedPointEditor->Value();
    STIF_ASSERT_TRUE( value == valueGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDeclareAutoSecretEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDeclareAutoSecretEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGEDITOR );
    
    _LIT( KSecret, "Secret" );
    const TInt lengthC = 10;
    TBuf<lengthC> text( KSecret );
    dialog->DeclareAutoSecretEditor( ETESTSDKSecretEditor, &text );
    
    CEikSecretEditor* secretEditor = static_cast<CEikSecretEditor*> ( dialog->ControlOrNull( ETESTSDKSecretEditor ) );
    TBuf<lengthC> textGet;
    secretEditor->GetText( textGet );
    STIF_ASSERT_EQUALS( 0, text.Compare( KSecret ) );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoTextEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoTextEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    _LIT( KText, "TextEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> text( KText );
    _LIT( KPrompt, "AddTextEditor" );
    TBuf<lengthC> prompt( KPrompt );
    dialog->AddAutoTextEditorL( prompt, ETESTSDKAddTextEditor, 0, 10, 1, &text );
    
    CEikEdwin* edwin = static_cast<CEikEdwin*> ( dialog->ControlOrNull( ETESTSDKAddTextEditor ) );
    STIF_ASSERT_NOT_NULL( edwin );
    
    HBufC* textbuf = edwin->GetTextInHBufL();
    TBuf<lengthC> textGet;
    edwin->GetText( textGet );
    STIF_ASSERT_EQUALS( 0, textGet.Compare( KText ) );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoGlobalTextEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoGlobalTextEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL( paraFormatLayer );
    CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
    CleanupStack::PushL( charFormatLayer );
    CGlobalText* globalText = CGlobalText::NewL( paraFormatLayer, charFormatLayer );
    CleanupStack::PushL( globalText );
    _LIT( KPrompt, "AddGlobalTextEditor" );
    const TInt lengthC = 20;
    const TInt textLimitC = 10;
    TBufC<lengthC> prompt( KPrompt );
    dialog->AddAutoGlobalTextEditorL( prompt, ETESTSDKAddGlobalTextEditor, 0, textLimitC, 1, lengthC, globalText );
    
    CEikGlobalTextEditor* globalTextEditor = static_cast<CEikGlobalTextEditor*> ( dialog->ControlOrNull( ETESTSDKAddGlobalTextEditor ) );
    STIF_ASSERT_NOT_NULL( globalTextEditor );

    CleanupStack::Pop( globalText );
    CleanupStack::Pop( charFormatLayer );
    CleanupStack::Pop( paraFormatLayer );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoRichTextEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoRichTextEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL( paraFormatLayer );
    CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
    CleanupStack::PushL( charFormatLayer );
    CRichText * richText = CRichText::NewL( paraFormatLayer, charFormatLayer );
    CleanupStack::PushL( richText );

    _LIT( KPrompt, "AddRichTextEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> prompt( KPrompt );
    dialog->AddAutoRichTextEditorL( prompt, ETESTSDKAddRichTextEditor, 0, 10, 1, 0, richText );
    
    CEikRichTextEditor* richTextEditor = static_cast<CEikRichTextEditor*> ( dialog->ControlOrNull( ETESTSDKAddRichTextEditor ) );
    STIF_ASSERT_NOT_NULL( richTextEditor );
    
    CleanupStack::Pop( richText );
    CleanupStack::Pop( charFormatLayer );
    CleanupStack::Pop( paraFormatLayer );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoNumberEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoNumberEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    _LIT( KText, "NumberEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> text( KText );
    _LIT( KPrompt, "AddNumberEditor" );
    TBuf<lengthC> prompt( KPrompt );
    const TInt returnnumberC = 50;
    TInt returnnumber = returnnumberC;
    const TInt maxC = 100;
    TInt max = maxC;
    dialog->AddAutoNumberEditorL( prompt, ETESTSDKADDNumberEditor, 0, max, &returnnumber );
    
    CEikNumberEditor* numberEditor = static_cast<CEikNumberEditor*> ( dialog->ControlOrNull( ETESTSDKADDNumberEditor ) );
    STIF_ASSERT_NOT_NULL( numberEditor );
    
    TInt numberGet = numberEditor->Number();
    STIF_ASSERT_EQUALS( returnnumber, numberGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoRangeEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoRangeEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    _LIT( KText, "RangerEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> text( KText );
    HBufC* textbuf = text.AllocLC();
    _LIT( KPrompt, "AddRangerEditor" );
    TBuf<lengthC> prompt( KPrompt );
    
    SEikRange range;
    range.iLowerLimit = 0;
    const TInt upperLimit = 100;
    range.iUpperLimit = upperLimit;
    dialog->AddAutoRangeEditorL( prompt, ETESTSDKADDRangeEditor, 0, upperLimit, textbuf, &range );
    
    CEikRangeEditor * rangeEditor = static_cast<CEikRangeEditor *> ( dialog->ControlOrNull( ETESTSDKADDRangeEditor ) );
    STIF_ASSERT_NOT_NULL( rangeEditor );
    
    SEikRange rangeGet = rangeEditor->Range();
    TInt lower = rangeGet.iLowerLimit;
    STIF_ASSERT_EQUALS( 0, lower );
    TInt upper = rangeGet.iUpperLimit;
    STIF_ASSERT_EQUALS( upperLimit, upper );
    
    CleanupStack::Pop( textbuf );
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoTimeEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoTimeEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    TDateTime datetime( 0, TMonth( 0 ), 0, 20, 20, 20, 0 );
    TTime time( datetime );
    TDateTime mindatetime( 0, TMonth( 0 ), 0, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 0, TMonth( 0 ), 0, 23, 59, 59, 0 );
    TTime maxtime( mindatetime );
    _LIT( KPrompt, "AddTimeEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> prompt( KPrompt );
    dialog->AddAutoTimeEditorL( prompt, ETESTSDKADDTimeEditor, mintime, maxtime, EFalse, &time );
    
    CEikTimeEditor* timeEditor = static_cast<CEikTimeEditor*> ( dialog->ControlOrNull( ETESTSDKADDTimeEditor ) );
    STIF_ASSERT_NOT_NULL( timeEditor );
    
    timeEditor->SetTime( time );
    TTime timeGet = timeEditor->Time();
    STIF_ASSERT_TRUE( time == timeGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoDateEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoDateEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 0, 0, 0, 0 );
    TTime maxtime( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 0, 0, 0, 0 );
    TTime date( datetime );
    _LIT( KPrompt, "AddDateEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> prompt( KPrompt );
    dialog->AddAutoDateEditorL( prompt, ETESTSDKADDDateEditor, mintime, maxtime, ETrue, &date );
    
    CEikDateEditor* dateEditor = static_cast<CEikDateEditor*> ( dialog->ControlOrNull( ETESTSDKADDDateEditor ) );
    STIF_ASSERT_NOT_NULL( dateEditor );
    
    TTime dateGet = dateEditor->Date();
    STIF_ASSERT_TRUE( date == dateGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoTimeAndDateEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoTimeAndDateEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintimeanddate( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 23, 59, 59, 0 );
    TTime maxtimeanddate( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 20, 20, 20, 0 );
    TTime timeanddate( datetime );
    _LIT( KPrompt, "AddTimeAndDateEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> prompt( KPrompt );
    dialog->AddAutoTimeAndDateEditorL( prompt, ETESTSDKAddTimeAndDateEditor, mintimeanddate, maxtimeanddate, EFalse, ETrue, NULL, &timeanddate );
    
    CEikTimeAndDateEditor* dateTimeEditor = static_cast<CEikTimeAndDateEditor*> ( dialog->ControlOrNull( ETESTSDKAddTimeAndDateEditor ) );
    STIF_ASSERT_NOT_NULL( dateTimeEditor );
    
    TTime dateTimeGet = dateTimeEditor->TimeAndDate();
    STIF_ASSERT_TRUE( timeanddate == dateTimeGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoDurationEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoDurationEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    _LIT( KPrompt, "AddDurationEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> prompt( KPrompt );
    const TInt minC = 0;
    TTimeIntervalSeconds minduration( minC );
    const TInt maxC = 1000000;
    TTimeIntervalSeconds maxduration( maxC );
    const TInt durationC = 1000;
    TTimeIntervalSeconds duration( durationC );
    dialog->AddAutoDurationEditorL( prompt, ETESTSDKAddDurationEditor, minduration, maxduration, EFalse, &duration );
    
    CEikDurationEditor* ddurationEditor = static_cast<CEikDurationEditor*> ( dialog->ControlOrNull( ETESTSDKAddDurationEditor ) );
    STIF_ASSERT_NOT_NULL( ddurationEditor );
    
    TTimeIntervalSeconds durationGet = ddurationEditor->Duration();
    STIF_ASSERT_TRUE( duration == durationGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoTimeOffsetEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoTimeOffsetEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    _LIT( KPrompt, "AddTimeOffsetEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> prompt( KPrompt );
    const TInt minC = 0;
    TTimeIntervalSeconds minTimeOffset( minC );
    const TInt maxC = 1000000;
    TTimeIntervalSeconds maxTimeOffset( maxC );
    const TInt timeOffsetC = 1000;
    TTimeIntervalSeconds timeOffset( timeOffsetC );
    dialog->AddAutoTimeOffsetEditorL( prompt, ETESTSDKAddTimeOffsetEditor, minTimeOffset, maxTimeOffset, EFalse, &timeOffset );
    
    CEikTimeOffsetEditor* timeOffsetEditor = static_cast<CEikTimeOffsetEditor*> ( dialog->ControlOrNull( ETESTSDKAddTimeOffsetEditor ) );
    STIF_ASSERT_NOT_NULL( timeOffsetEditor );
    
    TTimeIntervalSeconds timeOffsetGet = timeOffsetEditor->TimeOffset();
    STIF_ASSERT_TRUE( timeOffset == timeOffsetGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoFloatEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoFloatEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    _LIT( KPrompt, "AddFloatEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> prompt( KPrompt );
    const TReal minC(0);
    TReal min = minC;
    const TReal maxC(1000);
    TReal max = maxC;
    const TReal valueC(100);
    TReal value = valueC;
    dialog->AddAutoFloatEditorL( prompt, ETESTSDKAddFloatEditorEditor, min, max, &value );
    
    CEikFloatingPointEditor* floatEditor = static_cast<CEikFloatingPointEditor*> ( dialog->ControlOrNull( ETESTSDKAddFloatEditorEditor ) );
    STIF_ASSERT_NOT_NULL( floatEditor );
    
    TReal floatEditorGet = floatEditor->Value();
    STIF_ASSERT_TRUE( value == floatEditorGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoFixedPointEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoFixedPointEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
    
    _LIT( KPrompt, "AddFixedPointEditor" );
    const TInt lengthC = 20;
    TBuf<lengthC> prompt( KPrompt );
    const TInt minC(100);
    TInt min = minC;
    const TInt maxC(9999);
    TInt max = maxC;
    const TInt valueC(100);
    TInt value = valueC;
    dialog->AddAutoFixedPointEditorL( prompt, ETESTSDKAddFixPointedEditor, min, max, &value, 2 );
    
    CEikFixedPointEditor* fixedPointEditor = static_cast<CEikFixedPointEditor*> ( dialog->ControlOrNull( ETESTSDKAddFixPointedEditor ) );
    STIF_ASSERT_NOT_NULL( fixedPointEditor );
    
    TInt valueGet = fixedPointEditor->Value();
    STIF_ASSERT_TRUE( value == valueGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDAddAutoSecretEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDAddAutoSecretEditorL( CStifItemParser& /*aItem*/ )
    {
    // Because AddAutoSecretEditorL is deprecated (Not supported) according to
    // API comment, so comment below code.
//    CEikDialog* dialog = new (ELeave) CEikDialog;
//    CleanupStack::PushL( dialog );
//    STIF_ASSERT_NOT_NULL( dialog );
//    CleanupStack::Pop( dialog );
//    dialog->PrepareLC( R_TESTSDK_DIALOGADDEDITOR );
//    
//    const TInt lengthC = 10;
//    _LIT( KSecret, "Secret" );
//    TBuf<lengthC> text( KSecret );
//    _LIT( KPrompt, "Prompt" );
//    TBufC<lengthC> prompt( KPrompt );
//    dialog->AddAutoSecretEditorL( prompt, ETESTSDKAddSecretEditor, &text);
//    CEikSecretEditor* secretEditor = static_cast<CEikSecretEditor*> ( dialog->ControlOrNull( ETESTSDKAddSecretEditor ) );
//    STIF_ASSERT_NOT_NULL( secretEditor );
//    
//    TResourceReader reader;
//    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_SECRET );
//    secretEditor->ConstructFromResourceL( reader );
//    CleanupStack::PopAndDestroy();
//    
//    secretEditor->SetText( KSecret );
//    TBuf<lengthC> textGet;
//    secretEditor->GetText( textGet );
//    STIF_ASSERT_EQUALS( 0, text.Compare( KSecret ) );
//    
//    TInt flag = dialog->RunLD();
//    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetLabelByDesL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetLabelByDesL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    _LIT( KLabel, "SetLabel" );
    const TInt lengthC = 10;
    TBuf<lengthC> label( KLabel );
    dialog->SetLabelL( ETESTSDKSGLabel, label );
    
    TBuf<lengthC> labelGet;
    dialog->GetLabelText( labelGet, ETESTSDKSGLabel );
    
    STIF_ASSERT_EQUALS( 0, label.Compare( labelGet ) );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetLabelByResourceIdL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetLabelByResourceIdL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    _LIT( KLabel, "LabelResource" );
    const TInt lengthC = 20;
    TBuf<lengthC> label( KLabel );
    dialog->SetLabelL( ETESTSDKSGLabel, R_TESTSDK_LABEL );
    
    TBuf<lengthC> labelGet;
    dialog->GetLabelText( labelGet, ETESTSDKSGLabel );
    
    STIF_ASSERT_EQUALS( 0, label.Compare( labelGet ) );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetLabelReserveLengthL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetLabelReserveLengthL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TInt lengthC = 20;
    dialog->SetLabelReserveLengthL( ETESTSDKSGLabel, lengthC );
    CEikLabel* label = static_cast<CEikLabel*> ( dialog->ControlOrNull( ETESTSDKSGLabel ) );
    TInt length = label->BufferReserveLength();
    STIF_ASSERT_EQUALS( lengthC, length );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetEdwinTextL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetEdwinTextL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    _LIT( KText, "Edwin" );
    const TInt lengthC = 10;
    TBuf<lengthC> text( KText );
    dialog->SetEdwinTextL( ETESTSDKSGEdwin, &text );
    
    TBuf<lengthC> textGet;
    dialog->GetEdwinText( textGet, ETESTSDKSGEdwin );
    STIF_ASSERT_EQUALS( 0, text.Compare( textGet ) );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetTextEditorTextL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetTextEditorTextL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL( paraFormatLayer );
    CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
    CleanupStack::PushL( charFormatLayer );
    CGlobalText* globalText = CGlobalText::NewL( paraFormatLayer, charFormatLayer );
    CleanupStack::PushL( globalText );
    
    dialog->SetTextEditorTextL( ETESTSDKSGTextEditor, globalText );
    
    CGlobalText* globalTextGet = NULL;
    dialog->GetTextEditorText( globalTextGet, ETESTSDKSGTextEditor );
    const CParaFormatLayer* paraFormatLayerGet = globalTextGet->GlobalParaFormatLayer();
    TBool idntical = paraFormatLayerGet->IsIdentical( paraFormatLayer );
    STIF_ASSERT_TRUE( idntical );
    
    CleanupStack::Pop( globalText );
    CleanupStack::Pop( charFormatLayer );
    CleanupStack::Pop( paraFormatLayer );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDResetSecretEditorL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDResetSecretEditorL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    dialog->ResetSecretEditor( ETESTSDKSGSecretEditor );
    const TInt lengthC = 10;
    TBuf<lengthC> textGet;
    dialog->GetSecretEditorText( textGet , ETESTSDKSGSecretEditor );
    STIF_ASSERT_EQUALS( 0, textGet.Length() );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetFloatingPointEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetFloatingPointEditorValueL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TReal value = 3.14;
    dialog->SetFloatingPointEditorValueL( ETESTSDKSGFloatPointEditor, &value );
    STIF_ASSERT_TRUE( dialog->FloatingPointEditorValue( ETESTSDKSGFloatPointEditor ) == value );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetFixedPointEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetFixedPointEditorValueL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TInt value = 100;
    dialog->SetFixedPointEditorValueL( ETESTSDKSGFixPointedEditor, value );
    STIF_ASSERT_TRUE( dialog->FixedPointEditorValue( ETESTSDKSGFixPointedEditor ) == value );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetFixedPointEditorDecimalL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetFixedPointEditorDecimalL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TInt decimal = 25;
    dialog->SetFixedPointEditorDecimal( ETESTSDKSGFixPointedEditor, decimal );
    STIF_ASSERT_TRUE( dialog->FixedPointEditorDecimal( ETESTSDKSGFixPointedEditor ) == decimal );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetNumberEditorMinAndMaxL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetNumberEditorMinAndMaxL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TInt min = 10;
    const TInt max = 20;
    dialog->SetNumberEditorMinAndMax( ETESTSDKSGNumberEditor, min, max );
    
    CEikNumberEditor* numberEditor = static_cast<CEikNumberEditor*> ( dialog->ControlOrNull( ETESTSDKSGNumberEditor ) );
    STIF_ASSERT_NOT_NULL( numberEditor );
    TInt minGet;
    TInt maxGet;
    numberEditor->GetMinimumAndMaximum( minGet, maxGet );
    STIF_ASSERT_EQUALS( min, minGet );
    STIF_ASSERT_EQUALS( max, maxGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetNumberEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetNumberEditorValueL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TInt value = 50;
    dialog->SetNumberEditorValue( ETESTSDKSGNumberEditor, value );
    STIF_ASSERT_EQUALS( dialog->NumberEditorValue( ETESTSDKSGNumberEditor ), value );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetFloatEditorMinAndMaxL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetFloatEditorMinAndMaxL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TReal min = 125;
    const TReal max = 548;
    dialog->SetFloatEditorMinAndMax( ETESTSDKSGFloatPointEditor, min, max );
    
    CEikFloatingPointEditor* floatEditor = static_cast<CEikFloatingPointEditor*> ( dialog->ControlOrNull( ETESTSDKSGFloatPointEditor ) );
    STIF_ASSERT_NOT_NULL( floatEditor );
    
    TReal minGet;
    TReal maxGet;
    floatEditor->GetMinMax( minGet, maxGet );
    STIF_ASSERT_TRUE( minGet == min );
    STIF_ASSERT_TRUE( maxGet == max );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetFloatEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetFloatEditorValueL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TReal value = 3.14;
    dialog->SetFloatEditorValueL( ETESTSDKSGFloatPointEditor, value );
    STIF_ASSERT_TRUE( dialog->FloatEditorValue( ETESTSDKSGFloatPointEditor ) == value );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetRangeEditorMinAndMaxL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetRangeEditorMinAndMaxL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    TInt min = 0;
    const TInt max = 50;
    dialog->SetRangeEditorMinAndMax( ETESTSDKSGRangeEditor, min, max );
    
    CEikRangeEditor * rangeEditor = static_cast<CEikRangeEditor *> ( dialog->ControlOrNull( ETESTSDKSGRangeEditor ) );
    STIF_ASSERT_NOT_NULL( rangeEditor );
    
    TInt minGet;
    TInt maxGet;
    rangeEditor->GetMinimumAndMaximum( minGet, maxGet );
    STIF_ASSERT_TRUE( min == minGet );
    STIF_ASSERT_TRUE( max == maxGet );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetRangeEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetRangeEditorValueL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TInt lowerLimit = 10;
    const TInt upperLimit = 50;
    SEikRange range;
    range.iLowerLimit = lowerLimit;
    range.iUpperLimit = upperLimit;
    dialog->SetRangeEditorValue( ETESTSDKSGRangeEditor, range );
    
    SEikRange rangeGet = dialog->RangeEditorValue( ETESTSDKSGRangeEditor );
    TInt lower = rangeGet.iLowerLimit;
    STIF_ASSERT_EQUALS( lowerLimit, lower );
    TInt upper = rangeGet.iUpperLimit;
    STIF_ASSERT_EQUALS( upperLimit, upper );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetTTimeEditorMinAndMaxL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetTTimeEditorMinAndMaxL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    TDateTime mindatetime( 0, TMonth( 0 ), 0, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 0, TMonth( 0 ), 0, 23, 59, 59, 0 );
    TTime maxtime( mindatetime );
    dialog->SetTTimeEditorMinAndMax( ETESTSDKSGTimeEditor, mintime, maxtime );
    
    CEikTimeEditor* timeEditor = static_cast<CEikTimeEditor*> ( dialog->ControlOrNull( ETESTSDKSGTimeEditor ) );
    STIF_ASSERT_NOT_NULL( timeEditor );
    TTime mintimeGet;
    TTime maxtimeGet;
    timeEditor->GetMinimumAndMaximum( mintimeGet, maxtimeGet );
    STIF_ASSERT_TRUE( mintimeGet == mintime );
    STIF_ASSERT_TRUE( maxtimeGet == maxtime );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetTTimeEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetTTimeEditorValueL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    TDateTime datetime( 0, TMonth( 0 ), 0, 2, 24, 10, 0 );
    TTime time( datetime );
    dialog->SetTTimeEditorValue( ETESTSDKSGTimeEditor, time );
    STIF_ASSERT_TRUE( dialog->TTimeEditorValue( ETESTSDKSGTimeEditor ) == time );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetDurationEditorMinAndMaxL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetDurationEditorMinAndMaxL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TInt mindurationC = 0;
    const TInt maxdurationC = 2000000;
    TTimeIntervalSeconds minduration( mindurationC );
    TTimeIntervalSeconds maxduration( maxdurationC );
    dialog->SetDurationEditorMinAndMax( ETESTSDKSGDurationEditor, minduration, maxduration );
    CEikDurationEditor* ddurationEditor = static_cast<CEikDurationEditor*> ( dialog->ControlOrNull( ETESTSDKSGDurationEditor ) );
    STIF_ASSERT_NOT_NULL( ddurationEditor );
    
    TTimeIntervalSeconds mindurationGet;
    TTimeIntervalSeconds maxdurationGet;
    ddurationEditor->GetMinimumAndMaximum( mindurationGet, maxdurationGet );
    STIF_ASSERT_TRUE( mindurationGet == minduration );
    STIF_ASSERT_TRUE( maxdurationGet == maxduration ); 
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetDurationEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetDurationEditorValueL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TInt durationC = 1000;
    TTimeIntervalSeconds duration( durationC );
    dialog->SetDurationEditorValue( ETESTSDKSGDurationEditor, duration );
    STIF_ASSERT_TRUE( dialog->DurationEditorValue( ETESTSDKSGDurationEditor ) == duration );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetTimeOffsetEditorMinAndMaxL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetTimeOffsetEditorMinAndMaxL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    TTimeIntervalSeconds minTimeOffset(0);
    const TInt timeOffsetC = 1000000;
    TTimeIntervalSeconds maxTimeOffset( timeOffsetC );
    dialog->SetTimeOffsetEditorMinAndMax( ETESTSDKSGTimeOffsetEditor, minTimeOffset, maxTimeOffset );

    CEikTimeOffsetEditor* timeOffsetEditor = static_cast<CEikTimeOffsetEditor*> ( dialog->ControlOrNull( ETESTSDKSGTimeOffsetEditor ) );
    STIF_ASSERT_NOT_NULL( timeOffsetEditor );
    
    TTimeIntervalSeconds minTimeOffsetGet;
    TTimeIntervalSeconds maxTimeOffsetGet;
    timeOffsetEditor->GetMinimumAndMaximum( minTimeOffsetGet, maxTimeOffsetGet );
    STIF_ASSERT_TRUE( minTimeOffsetGet == minTimeOffset );
    STIF_ASSERT_TRUE( maxTimeOffsetGet == maxTimeOffset ); 
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetTimeOffsetEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetTimeOffsetEditorValueL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOGSGFUNCTION );
    
    const TInt timeOffsetC = 1000;
    TTimeIntervalSeconds timeOffset( timeOffsetC );
    dialog->SetTimeOffsetEditorValue( ETESTSDKSGTimeOffsetEditor, timeOffset );
    STIF_ASSERT_TRUE( dialog->TimeOffsetEditorValue( ETESTSDKSGTimeOffsetEditor ) == timeOffset );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetListBoxCurrentItemL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetListBoxCurrentItemL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_LISTBOX );
    
    TInt item = 0;
    dialog->SetListBoxCurrentItem( EDialogListBox, item );

    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetFileNameL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetFileNameL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    _LIT( KFileName, "filename" );
    TFileName filename( KFileName );
    dialog->SetFileNameL( EDialogLine, &filename );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetLabelTextL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetLabelTextL( CStifItemParser& aItem )
    {
    return TestDSetLabelByDesL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetEdwinTextL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetEdwinTextL( CStifItemParser& aItem )
    {
    return TestDSetEdwinTextL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetTextEditorTextL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetTextEditorTextL( CStifItemParser& aItem )
    {
    return TestDSetTextEditorTextL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetSecretEditorTextL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetSecretEditorTextL( CStifItemParser& aItem )
    {
    return TestDResetSecretEditorL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDFloatingPointEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDFloatingPointEditorValueL( CStifItemParser& aItem )
    {
    return TestDSetFloatingPointEditorValueL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDFixedPointEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDFixedPointEditorValueL( CStifItemParser& aItem )
    {
    return TestDSetFixedPointEditorValueL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDFixedPointEditorDecimalL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDFixedPointEditorDecimalL( CStifItemParser& aItem )
    {
    return TestDSetFixedPointEditorDecimalL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDFloatEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDFloatEditorValueL( CStifItemParser& aItem )
    {
    return TestDSetFloatEditorValueL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDNumberEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDNumberEditorValueL( CStifItemParser& aItem )
    {
    return TestDSetNumberEditorValueL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDRangeEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDRangeEditorValueL( CStifItemParser& aItem )
    {
    return TestDSetRangeEditorValueL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDTTimeEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDTTimeEditorValueL( CStifItemParser& aItem )
    {
    return TestDSetTTimeEditorValueL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDDurationEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDDurationEditorValueL( CStifItemParser& aItem )
    {
    return TestDSetDurationEditorValueL( aItem ); 
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDTimeOffsetEditorValueL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDTimeOffsetEditorValueL( CStifItemParser& aItem )
    {
    return TestDSetTimeOffsetEditorValueL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetAutoValuesFromPageL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetAutoValuesFromPageL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    CEikCapCArray* lines = NULL;
    dialog->GetAutoValuesFromPage( lines );
    STIF_ASSERT_NULL( lines );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDListBoxCurrentItemL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDListBoxCurrentItemL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_LISTBOX );
    
    TInt currentitem = dialog->ListBoxCurrentItem( EDialogListBox );
    STIF_ASSERT_EQUALS( -1, currentitem );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDGetFileNameL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDGetFileNameL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    _LIT( KFileName, "filenameGet" );
    TFileName filenameGet( KFileName );
    dialog->GetFileName( &filenameGet, EDialogLine );
    STIF_ASSERT_EQUALS( 0, filenameGet.Compare( KFileName ) );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDUpdatePageL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDUpdatePageL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->DeleteLine( EDialogLine, EFalse );
    dialog->UpdatePageL( ETrue );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDHandleDialogPageEventL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDHandleDialogPageEventL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->HandleDialogPageEventL( MEikDialogPageObserver::EDialogPageTapped );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    dialog = NULL;
    
    dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    
    dialog->ConstructAutoDialogLC( EEikDialogFlagCloseDialogWhenTapped, R_AVKON_SOFTKEYS_OK_CANCEL );
    CleanupStack::Pop( dialog );
    dialog->HandleDialogPageEventL( MEikDialogPageObserver::EDialogPageTapped );
    
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDPublishDialogL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDPublishDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->PublishDialogL( 1 );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetMediatorObserverL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetMediatorObserverL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKDialogsControl* dialog = new (ELeave) CTestSDKDialogsControl;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->CTestSDKSetMediatorObserver();
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSlideDialogL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSlideDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->SlideDialog();
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogs::TestDSetMultilineQueryL 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogs::TestDSetMultilineQueryL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    CleanupStack::Pop( dialog );
    dialog->PrepareLC( R_TESTSDK_DIALOG );
    
    dialog->SetMultilineQuery( EFalse );
    dialog->SetMultilineQuery( ETrue );
    
    TInt flag = dialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }
//  [End of File]
