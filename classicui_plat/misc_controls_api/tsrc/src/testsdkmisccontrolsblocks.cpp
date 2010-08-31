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
* Description:  misc_controls_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkmisccontrols.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkmisccontrols::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //for test misc_controls_api EIKCAPC.H
        ENTRY( "TestMCConstructorL", CTestSDKMiscControls::TestMCConstructorL ),
        ENTRY( "TestMCDestructor", CTestSDKMiscControls::TestMCDestructor ),
        ENTRY( "TestMCSetUsesEars", CTestSDKMiscControls::TestMCSetUsesEars ),
        ENTRY( "TestMCSetSpaceSharingFlags", CTestSDKMiscControls::TestMCSetSpaceSharingFlags ),
        ENTRY( "TestMCSetExtraAscent", CTestSDKMiscControls::TestMCSetExtraAscent ),
        ENTRY( "TestMCSetCaptionL", CTestSDKMiscControls::TestMCSetCaptionL ),
        ENTRY( "TestMCSetTrailerL", CTestSDKMiscControls::TestMCSetTrailerL ),
        ENTRY( "TestMCSetCurrentL", CTestSDKMiscControls::TestMCSetCurrentL ),
        ENTRY( "TestMCCheckDimmedDisplayStateL", CTestSDKMiscControls::TestMCCheckDimmedDisplayStateL ),
        ENTRY( "TestMCResetMinimumSizes", CTestSDKMiscControls::TestMCResetMinimumSizes ),
        ENTRY( "TestMCIsLatent", CTestSDKMiscControls::TestMCIsLatent ),
        ENTRY( "TestMCSetLatentL", CTestSDKMiscControls::TestMCSetLatentL ),
        ENTRY( "TestMCLatentGroupLineFollows", CTestSDKMiscControls::TestMCLatentGroupLineFollows ),
        ENTRY( "TestMCSetLatentGroupLineFollows", CTestSDKMiscControls::TestMCSetLatentGroupLineFollows ),
        ENTRY( "TestMCDividerAfter", CTestSDKMiscControls::TestMCDividerAfter ),
        ENTRY( "TestMCSetDividerAfter", CTestSDKMiscControls::TestMCSetDividerAfter ),
        ENTRY( "TestMCTakesEnterKey", CTestSDKMiscControls::TestMCTakesEnterKey ),
        ENTRY( "TestMCSetTakesEnterKey", CTestSDKMiscControls::TestMCSetTakesEnterKey ),
        ENTRY( "TestMCOfferHotKeys", CTestSDKMiscControls::TestMCOfferHotKeys ),
        ENTRY( "TestMCSetOfferHotKeys", CTestSDKMiscControls::TestMCSetOfferHotKeys ),
        ENTRY( "TestMCHandleControlEventL", CTestSDKMiscControls::TestMCHandleControlEventL ),
        ENTRY( "TestMCMinimumSizeL", CTestSDKMiscControls::TestMCMinimumSizeL ),
        ENTRY( "TestMCConstructFromResourceL", CTestSDKMiscControls::TestMCConstructFromResourceL ),
        ENTRY( "TestMCOfferKeyEventL", CTestSDKMiscControls::TestMCOfferKeyEventL ),
        ENTRY( "TestMCGetColorUseListL", CTestSDKMiscControls::TestMCGetColorUseListL ),
        ENTRY( "TestMCHandleResourceChangeL", CTestSDKMiscControls::TestMCHandleResourceChangeL ),
        ENTRY( "TestMCInputCapabilities", CTestSDKMiscControls::TestMCInputCapabilities ),
        ENTRY( "TestMCSetDimmed", CTestSDKMiscControls::TestMCSetDimmed ),
        ENTRY( "TestMCHandlePointerEventL", CTestSDKMiscControls::TestMCHandlePointerEventL ),
        ENTRY( "TestMCDrawL", CTestSDKMiscControls::TestMCDrawL ),
        ENTRY( "TestMCWriteInternalStateL", CTestSDKMiscControls::TestMCWriteInternalStateL ),
        ENTRY( "TestMCMopSupplyObjectL", CTestSDKMiscControls::TestMCMopSupplyObjectL ),
        ENTRY( "TestMCSetToolTipTextL", CTestSDKMiscControls::TestMCSetToolTipTextL ),
        ENTRY( "TestMCToolTipTextL", CTestSDKMiscControls::TestMCToolTipTextL ),
        ENTRY( "TestMCSetBitmapFromFileL", CTestSDKMiscControls::TestMCSetBitmapFromFileL ),
        ENTRY( "TestMCSetEditableL", CTestSDKMiscControls::TestMCSetEditableL ),
        ENTRY( "TestMCSetFormFlagsL", CTestSDKMiscControls::TestMCSetFormFlagsL ),
        ENTRY( "TestMCGetFullCaptionTextL", CTestSDKMiscControls::TestMCGetFullCaptionTextL ),
        ENTRY( "TestMCSetDrawNoWhiteBackgroundL", CTestSDKMiscControls::TestMCSetDrawNoWhiteBackgroundL ),
        ENTRY( "TestMCSetIconL", CTestSDKMiscControls::TestMCSetIconL ),
        ENTRY( "TestMCSetIndicatorIconL", CTestSDKMiscControls::TestMCSetIndicatorIconL ),
        ENTRY( "TestMCSetPointerEventObserverL", CTestSDKMiscControls::TestMCSetPointerEventObserverL ),
        //for test misc_controls_api eikcapca.h
        ENTRY( "TestCCAConstructorL", CTestSDKMiscControls::TestCCAConstructorL ),
        ENTRY( "TestCCADestructor", CTestSDKMiscControls::TestCCADestructor ),
        ENTRY( "TestCCAMinimumSize", CTestSDKMiscControls::TestCCAMinimumSize ),
        ENTRY( "TestCCASetRect", CTestSDKMiscControls::TestCCASetRect ),
        ENTRY( "TestCCAResetMinimumSizes", CTestSDKMiscControls::TestCCAResetMinimumSizes ),
        ENTRY( "TestCCALineIndexFromId", CTestSDKMiscControls::TestCCALineIndexFromId ),
        ENTRY( "TestCCAFindLineIndexL", CTestSDKMiscControls::TestCCAFindLineIndexL ),
        ENTRY( "TestCCADeleteLineL", CTestSDKMiscControls::TestCCADeleteLineL ),
        ENTRY( "TestCCAAdjustAllIds", CTestSDKMiscControls::TestCCAAdjustAllIds ),
        ENTRY( "TestCCASetDensePacking", CTestSDKMiscControls::TestCCASetDensePacking ),
        //for test misc_controls_api eikconso.h
        ENTRY( "TestCSDefaultConstructorL", CTestSDKMiscControls::TestCSDefaultConstructorL ),
        ENTRY( "TestCSDestructor", CTestSDKMiscControls::TestCSDestructor ),
        ENTRY( "TestCSConstructL", CTestSDKMiscControls::TestCSConstructL ),
        ENTRY( "TestCSConstructWithSizeL", CTestSDKMiscControls::TestCSConstructWithSizeL ),
        ENTRY( "TestCSConstructWithSizeAndPointL",
                CTestSDKMiscControls::TestCSConstructWithSizeAndPointL ),
        ENTRY( "TestCSCreate", CTestSDKMiscControls::TestCSCreate ),
        ENTRY( "TestCSRead", CTestSDKMiscControls::TestCSRead ),
        ENTRY( "TestCSReadCancel", CTestSDKMiscControls::TestCSReadCancel ),
        ENTRY( "TestCSKeyCode", CTestSDKMiscControls::TestCSKeyCode ),
        ENTRY( "TestCSKeyModifiers", CTestSDKMiscControls::TestCSKeyModifiers ),
        ENTRY( "TestCSSetConsWinL", CTestSDKMiscControls::TestCSSetConsWinL ),
        ENTRY( "TestCSConsoleControl", CTestSDKMiscControls::TestCSConsoleControlL ),
        ENTRY( "TestCSSetTitle", CTestSDKMiscControls::TestCSSetTitle ),
        ENTRY( "TestCSSetTitleL", CTestSDKMiscControls::TestCSSetTitleL ),
        ENTRY( "TestCSTitle", CTestSDKMiscControls::TestCSTitleL ),
        ENTRY( "TestCSScreenSize", CTestSDKMiscControls::TestCSScreenSize ),
        ENTRY( "TestCSFlushChars", CTestSDKMiscControls::TestCSFlushChars ),
        ENTRY( "TestCSCursorPos", CTestSDKMiscControls::TestCSCursorPos ),
        ENTRY( "TestCSSetCursorPosAbs", CTestSDKMiscControls::TestCSSetCursorPosAbs ),
        ENTRY( "TestCSSetCursorPosRel", CTestSDKMiscControls::TestCSSetCursorPosRel ),
        ENTRY( "TestCSSetCursorHeight", CTestSDKMiscControls::TestCSSetCursorHeight ),
        ENTRY( "TestCSWrite", CTestSDKMiscControls::TestCSWrite ),
        ENTRY( "TestCSClearScreen", CTestSDKMiscControls::TestCSClearScreen ),
        ENTRY( "TestCSClearToEndOfLine", CTestSDKMiscControls::TestCSClearToEndOfLine ),
        ENTRY( "TestCSClearChars", CTestSDKMiscControls::TestCSClearChars ),
        ENTRY( "TestCSHideCursor", CTestSDKMiscControls::TestCSHideCursor ),
        ENTRY( "TestCSDrawCursor", CTestSDKMiscControls::TestCSDrawCursor ),
        ENTRY( "TestCSDrawInSight", CTestSDKMiscControls::TestCSDrawInSight ),
        ENTRY( "TestCSDrawCursorInSight", CTestSDKMiscControls::TestCSDrawCursorInSight ),
        ENTRY( "TestCSUp", CTestSDKMiscControls::TestCSUp ),
        ENTRY( "TestCSDown", CTestSDKMiscControls::TestCSDown ),
        ENTRY( "TestCSRight", CTestSDKMiscControls::TestCSRight ),
        ENTRY( "TestCSLeft", CTestSDKMiscControls::TestCSLeft ),
        ENTRY( "TestCSCr", CTestSDKMiscControls::TestCSCr ),
        ENTRY( "TestCSLf", CTestSDKMiscControls::TestCSLf ),
        ENTRY( "TestCSScrollChars", CTestSDKMiscControls::TestCSScrollChars ),
        ENTRY( "TestCSRedraw", CTestSDKMiscControls::TestCSRedraw ),
        ENTRY( "TestCSMoveTopLeft", CTestSDKMiscControls::TestCSMoveTopLeft ),
        ENTRY( "TestCSHistorySize", CTestSDKMiscControls::TestCSHistorySize ),
        ENTRY( "TestCSSetHistorySizeL", CTestSDKMiscControls::TestCSSetHistorySizeL ),
        ENTRY( "TestCSAtt", CTestSDKMiscControls::TestCSAtt ),
        ENTRY( "TestCSSetAtt", CTestSDKMiscControls::TestCSSetAtt ),
        ENTRY( "TestCSSetAttWithGround", CTestSDKMiscControls::TestCSSetAttWithGround ),
        ENTRY( "TestCSSetFontL", CTestSDKMiscControls::TestCSSetFontL ),
        ENTRY( "TestCSFont", CTestSDKMiscControls::TestCSFont ),
        ENTRY( "TestCSSetSelection", CTestSDKMiscControls::TestCSSetSelection ),
        ENTRY( "TestCSSelectCursor", CTestSDKMiscControls::TestCSSelectCursor ),
        ENTRY( "TestCSSelection", CTestSDKMiscControls::TestCSSelection ),
        ENTRY( "TestCSRetrieveL", CTestSDKMiscControls::TestCSRetrieveL ),
        ENTRY( "TestCSSetPureCRLF", CTestSDKMiscControls::TestCSSetPureCRLF ),
        ENTRY( "TestCSSetAllPrintable", CTestSDKMiscControls::TestCSSetAllPrintable ),
        ENTRY( "TestCSSetScrollLock", CTestSDKMiscControls::TestCSSetScrollLock ),
        ENTRY( "TestCSSetKeepCursorInSight", CTestSDKMiscControls::TestCSSetKeepCursorInSight ),
        ENTRY( "TestCSSetScrollBarVisibilityL", CTestSDKMiscControls::TestCSSetScrollBarVisibilityL ),
        ENTRY( "TestCSUpdateScrollBars", CTestSDKMiscControls::TestCSUpdateScrollBars ),
        ENTRY( "TestCCDefaultConstructorL", CTestSDKMiscControls::TestCCDefaultConstructorL ),
        ENTRY( "TestCCDestructor", CTestSDKMiscControls::TestCCDestructor ),
        ENTRY( "TestCCConstructL", CTestSDKMiscControls::TestCCConstructL ),
        ENTRY( "TestCCConstructWithPointL", CTestSDKMiscControls::TestCCConstructWithPointL ),
        ENTRY( "TestCCSetRedrawer", CTestSDKMiscControls::TestCCSetRedrawer ),
        ENTRY( "TestCCSetFontL", CTestSDKMiscControls::TestCCSetFontL ),
        ENTRY( "TestCCFont", CTestSDKMiscControls::TestCCFont ),
        ENTRY( "TestCCCharSize", CTestSDKMiscControls::TestCCCharSize ),
        ENTRY( "TestCCVisibleSize", CTestSDKMiscControls::TestCCVisibleSize ),
        ENTRY( "TestCCSetCursorHeight", CTestSDKMiscControls::TestCCSetCursorHeight ),
        ENTRY( "TestCCDrawCursor", CTestSDKMiscControls::TestCCDrawCursor ),
        ENTRY( "TestCCHideCursor", CTestSDKMiscControls::TestCCHideCursor ),
        ENTRY( "TestCCDrawChars", CTestSDKMiscControls::TestCCDrawChars ),
        ENTRY( "TestCCClearChars", CTestSDKMiscControls::TestCCClearChars ),
        ENTRY( "TestCCInvertChars", CTestSDKMiscControls::TestCCInvertChars ),
        ENTRY( "TestCCScrollChars", CTestSDKMiscControls::TestCCScrollChars ),
        ENTRY( "TestCCSetScrollBarVisibilityL", CTestSDKMiscControls::TestCCSetScrollBarVisibilityL ),
        ENTRY( "TestCCUpdateScrollbarsL", CTestSDKMiscControls::TestCCUpdateScrollbarsL ),
        ENTRY( "TestCCHandleScrollEventL", CTestSDKMiscControls::TestCCHandleScrollEventL ),
        ENTRY( "TestCCUpdateArea", CTestSDKMiscControls::TestCCUpdateArea ),
        ENTRY( "TestCCGetColorUseListL", CTestSDKMiscControls::TestCCGetColorUseListL ),
        ENTRY( "TestCCHandleResourceChange", CTestSDKMiscControls::TestCCHandleResourceChange ),
        ENTRY( "TestCCHandlePointerEventL", CTestSDKMiscControls::TestCCHandlePointerEventL ),
        ENTRY( "TestCCDrawL", CTestSDKMiscControls::TestCCDrawL ),
        ENTRY( "TestCCSizeChangedL", CTestSDKMiscControls::TestCCSizeChangedL ),
        ENTRY( "TestCCFocusChangedL", CTestSDKMiscControls::TestCCFocusChangedL ),
        ENTRY( "TestCCCountComponentControlsL", CTestSDKMiscControls::TestCCCountComponentControlsL ),
        ENTRY( "TestCCComponentControlL", CTestSDKMiscControls::TestCCComponentControlL ),
        ENTRY( "TestCCWriteInternalStateL", CTestSDKMiscControls::TestCCWriteInternalStateL ),
        //for test misc_controls_api eikctgrp.h
        ENTRY( "TestGCConstructorL", CTestSDKMiscControls::TestGCConstructorL ),
        ENTRY( "TestGCConstructorWithControlL", CTestSDKMiscControls::TestGCConstructorWithControlL ),
        ENTRY( "TestGCIsLengthSet", CTestSDKMiscControls::TestGCIsLengthSet ),
        ENTRY( "TestGCLength", CTestSDKMiscControls::TestGCLength ),
        ENTRY( "TestGCIsStretchable", CTestSDKMiscControls::TestGCIsStretchable ),
        ENTRY( "TestGCSetLength", CTestSDKMiscControls::TestGCSetLength ),
        ENTRY( "TestGCSetStretchable", CTestSDKMiscControls::TestGCSetStretchable ),
        ENTRY( "TestCGConstructorL", CTestSDKMiscControls::TestCGConstructorL ),
        ENTRY( "TestCGDestructor", CTestSDKMiscControls::TestCGDestructor ),
        ENTRY( "TestCGConstructL", CTestSDKMiscControls::TestCGConstructL ),
        ENTRY( "TestCGAddControlL", CTestSDKMiscControls::TestCGAddControlL ),
        ENTRY( "TestCGAddControlWithGroupControlL", CTestSDKMiscControls::TestCGAddControlWithGroupControlL ),
        ENTRY( "TestCGInsertControlL", CTestSDKMiscControls::TestCGInsertControlL ),
        ENTRY( "TestCGDeleteControl", CTestSDKMiscControls::TestCGDeleteControl ),
        ENTRY( "TestCGSetLengthInPixels", CTestSDKMiscControls::TestCGSetLengthInPixels ),
        ENTRY( "TestCGSetBreadthInPixels", CTestSDKMiscControls::TestCGSetBreadthInPixels ),
        ENTRY( "TestCGSetControlSpacing", CTestSDKMiscControls::TestCGSetControlSpacing ),
        ENTRY( "TestCGSetControlLayout", CTestSDKMiscControls::TestCGSetControlLayout ),
        ENTRY( "TestCGSetNumberOfLines", CTestSDKMiscControls::TestCGSetNumberOfLines ),
        ENTRY( "TestCGSetControlsAllSameSize", CTestSDKMiscControls::TestCGSetControlsAllSameSize ),
        ENTRY( "TestCGLayoutControls", CTestSDKMiscControls::TestCGLayoutControls ),
        ENTRY( "TestCGControlByIdL", CTestSDKMiscControls::TestCGControlByIdL ),
        ENTRY( "TestCGIndexById", CTestSDKMiscControls::TestCGIndexById ),
        ENTRY( "TestCGReset", CTestSDKMiscControls::TestCGReset ),
        ENTRY( "TestCGControlId", CTestSDKMiscControls::TestCGControlId ),
        ENTRY( "TestCGControlL", CTestSDKMiscControls::TestCGControlL ),
        ENTRY( "TestCGControlArrayL", CTestSDKMiscControls::TestCGControlArrayL ),
        ENTRY( "TestCGOrientation", CTestSDKMiscControls::TestCGOrientation ),
        ENTRY( "TestCGControlSpacing", CTestSDKMiscControls::TestCGControlSpacing ),
        ENTRY( "TestCGMinimumSize", CTestSDKMiscControls::TestCGMinimumSize ),
        ENTRY( "TestCGCountComponentControls", CTestSDKMiscControls::TestCGCountComponentControls ),
        ENTRY( "TestCGGetColorUseListL", CTestSDKMiscControls::TestCGGetColorUseListL ),
        ENTRY( "TestCGHandleResourceChange", CTestSDKMiscControls::TestCGHandleResourceChange ),
        ENTRY( "TestCGHandlePointerEventL", CTestSDKMiscControls::TestCGHandlePointerEventL ),
        ENTRY( "TestCGComponentControlL", CTestSDKMiscControls::TestCGComponentControlL ),
        ENTRY( "TestCGWriteInternalStateL", CTestSDKMiscControls::TestCGWriteInternalStateL ),
        //for test misc_controls_api eikmover.h
        ENTRY( "TestEMConstructorL", CTestSDKMiscControls::TestEMConstructorL ),
        ENTRY( "TestEMDestructor", CTestSDKMiscControls::TestEMDestructor ),
        ENTRY( "TestEMSetTextNoL", CTestSDKMiscControls::TestEMSetTextNoL ),
        ENTRY( "TestEMSetTextL", CTestSDKMiscControls::TestEMSetTextL ),
        ENTRY( "TestEMSetActive", CTestSDKMiscControls::TestEMSetActive ),
        ENTRY( "TestEMActive", CTestSDKMiscControls::TestEMActive ),
        ENTRY( "TestEMSetFontL", CTestSDKMiscControls::TestEMSetFontL ),
        ENTRY( "TestEMSetTitleLeftMargin", CTestSDKMiscControls::TestEMSetTitleLeftMargin ),
        ENTRY( "TestEMConstructFromResourceL", CTestSDKMiscControls::TestEMConstructFromResourceL ),
        ENTRY( "TestEMMinimumSize", CTestSDKMiscControls::TestEMMinimumSize ),
        ENTRY( "TestEMSetContainerWindowL", CTestSDKMiscControls::TestEMSetContainerWindowL ),
        ENTRY( "TestEMGetColorUseListL", CTestSDKMiscControls::TestEMGetColorUseListL ),
        ENTRY( "TestEMHandleResourceChange", CTestSDKMiscControls::TestEMHandleResourceChange ),
        ENTRY( "TestEMHandlePointerEventL", CTestSDKMiscControls::TestEMHandlePointerEventL ),
        ENTRY( "TestEMWriteInternalStateL", CTestSDKMiscControls::TestEMWriteInternalStateL ),
        //for test misc_controls_api eiktbar.h
        ENTRY( "TestTBConstructorL", CTestSDKMiscControls::TestTBConstructorL ),
        ENTRY( "TestTBDestructor", CTestSDKMiscControls::TestTBDestructor ),
        ENTRY( "TestTBConstructL", CTestSDKMiscControls::TestTBConstructL ),
        ENTRY( "TestTBStaticConstructL", CTestSDKMiscControls::TestTBStaticConstructL ),
        ENTRY( "TestTBSetCommandObserverL", CTestSDKMiscControls::TestTBSetCommandObserverL ),
        ENTRY( "TestTBCoordinateButtonsL", CTestSDKMiscControls::TestTBCoordinateButtonsL ),
        ENTRY( "TestTBSetButtonStateOnL", CTestSDKMiscControls::TestTBSetButtonStateOnL ),
        ENTRY( "TestTBDelayActivation", CTestSDKMiscControls::TestTBDelayActivation ),
        ENTRY( "TestTBConstructFromResourceL", CTestSDKMiscControls::TestTBConstructFromResourceL ),
        ENTRY( "TestTBSetDimmed", CTestSDKMiscControls::TestTBSetDimmed ),
        ENTRY( "TestTBGetColorUseListL", CTestSDKMiscControls::TestTBGetColorUseListL ),
        ENTRY( "TestTBHandleResourceChange", CTestSDKMiscControls::TestTBHandleResourceChange ),
        ENTRY( "TestTBHandlePointerEventL", CTestSDKMiscControls::TestTBHandlePointerEventL ),
        ENTRY( "TestTBAddControlL", CTestSDKMiscControls::TestTBAddControlL ),
        ENTRY( "TestTBAddControlWithGroupL", CTestSDKMiscControls::TestTBAddControlWithGroupL ),
        ENTRY( "TestTBSetBoundingRect", CTestSDKMiscControls::TestTBSetBoundingRect ),
        ENTRY( "TestTBReduceRect", CTestSDKMiscControls::TestTBReduceRect ),
        ENTRY( "TestTBWriteInternalStateL", CTestSDKMiscControls::TestTBWriteInternalStateL ),



        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
