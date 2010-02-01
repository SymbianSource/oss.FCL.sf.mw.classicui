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
* Description:  test aknedformaccessor.h, aknedwindrawingmodifier.h
*                and aknphonenumbereditor.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomeditor.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMEditor::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        // test functions in aknedformaccessor.h
        ENTRY( "TestAcceDefCons", CTestDOMEditor::TestAcceDefConsL ),
        ENTRY( "TestAcceSetEdwin", CTestDOMEditor::TestAcceSetEdwinL ),

        // test functions in aknedwindrawingmodifier.h
        ENTRY( "TestModifSetInhibit", CTestDOMEditor::TestModifSetInhibitL ),

        // test functions in aknphonenumbereditor.h
        ENTRY( "TestTForamtDefConsWithNoParam",
                CTestDOMEditor::TestTForamtDefConsWithNoParam ),
        ENTRY( "TestTForamtDefConsWithRes",
                CTestDOMEditor::TestTForamtDefConsWithResL ),
        ENTRY( "TestTForamtDefConsWithFont",
                CTestDOMEditor::TestTForamtDefConsWithFont ),
        ENTRY( "TestEditorDefCons", CTestDOMEditor::TestEditorDefConsL ),
        ENTRY( "TestEditorConstructL", CTestDOMEditor::TestEditorConstructL ),
        ENTRY( "TestEditorConstructFromResourceL",
                CTestDOMEditor::TestEditorConstructFromResourceL ),
        ENTRY( "TestEditorAddFormat", CTestDOMEditor::TestEditorAddFormatL ),
        ENTRY( "TestEditorCountFormats",
                CTestDOMEditor::TestEditorCountFormatsL ),
        ENTRY( "TestEditorFormat", CTestDOMEditor::TestEditorFormatL ),
        ENTRY( "TestEditorCurrentFormatIndex",
                CTestDOMEditor::TestEditorCurrentFormatIndexL ),
        ENTRY( "TestEditorWouldTextFitInFormat",
                CTestDOMEditor::TestEditorWouldTextFitInFormatL ),
        ENTRY( "TestEditorSetFormat", CTestDOMEditor::TestEditorSetFormatL ),
        ENTRY( "TestEditorText", CTestDOMEditor::TestEditorTextL ),
        ENTRY( "TestEditorSetText", CTestDOMEditor::TestEditorSetTextL ),
        ENTRY( "TestEditorSizeChanged", CTestDOMEditor::TestEditorSizeChangedL ),
        ENTRY( "TestEditorOfferKeyEventL",
                CTestDOMEditor::TestEditorOfferKeyEventL ),
        ENTRY( "TestEditorMinimumSize", CTestDOMEditor::TestEditorMinimumSizeL ),
        ENTRY( "TestEditorFocusChanged",
                CTestDOMEditor::TestEditorFocusChangedL ),
        ENTRY( "TestEditorDraw", CTestDOMEditor::TestEditorDrawL ),
        ENTRY( "TestEditorInputCapabilities",
                CTestDOMEditor::TestEditorInputCapabilitiesL ),
        ENTRY( "TestEditorTextLength", CTestDOMEditor::TestEditorTextLengthL ),
        ENTRY( "TestEditorCursorPos", CTestDOMEditor::TestEditorCursorPosL ),
        ENTRY( "TestEditorSelectionLength",
                CTestDOMEditor::TestEditorSelectionLengthL ),
        ENTRY( "TestEditorSelection", CTestDOMEditor::TestEditorSelectionL ),
        ENTRY( "TestEditorClearSelectionL",
                CTestDOMEditor::TestEditorClearSelectionL ),
        ENTRY( "TestEditorSetSelectionL",
                CTestDOMEditor::TestEditorSetSelectionL ),
        ENTRY( "TestEditorSetCursorPosL",
                CTestDOMEditor::TestEditorSetCursorPosL ),
        ENTRY( "TestEditorSelectAllL", CTestDOMEditor::TestEditorSelectAllL ),
        ENTRY( "TestEditorGetText", CTestDOMEditor::TestEditorGetTextL ),
        ENTRY( "TestEditorGetTextInHBufL",
                CTestDOMEditor::TestEditorGetTextInHBufL ),
        ENTRY( "TestEditorSetTextL", CTestDOMEditor::TestEditorSetTextWithPoiL ),
        ENTRY( "TestEditorCancelFepTransaction",
                CTestDOMEditor::TestEditorCancelFepTransactionL ),
        ENTRY( "TestEditorUpdateScrollBarsL",
                CTestDOMEditor::TestEditorUpdateScrollBarsL ),
        ENTRY( "TestEditorCreateScrollBarFrameL",
                CTestDOMEditor::TestEditorCreateScrollBarFrameL ),
        ENTRY( "TestEditorScrollBarFrame",
                CTestDOMEditor::TestEditorScrollBarFrameL ),
        ENTRY( "TestEditorLineCursorWidth",
                CTestDOMEditor::TestEditorLineCursorWidthL ),
        ENTRY( "TestEditorMargins", CTestDOMEditor::TestEditorMarginsL ),
        ENTRY( "TestEditorChangeEditorMode",
                CTestDOMEditor::TestEditorChangeEditorModeL ),
        ENTRY( "TestEditorGetEditorMode",
                CTestDOMEditor::TestEditorGetEditorModeL ),
        ENTRY( "TestEditorResetEditorToDefaultValues",
                CTestDOMEditor::TestEditorResetEditorToDefaultValuesL ),
        ENTRY( "TestEditorHandlePointerEventL",
                CTestDOMEditor::TestEditorHandlePointerEventL ),
        ENTRY( "TestEditorCcpuIsFocused",
                CTestDOMEditor::TestEditorCcpuIsFocusedL ),
        ENTRY( "TestEditorCcpuCanCut", CTestDOMEditor::TestEditorCcpuCanCutL ),
        ENTRY( "TestEditorCcpuCutL", CTestDOMEditor::TestEditorCcpuCutL ),
        ENTRY( "TestEditorCcpuCanCopy", CTestDOMEditor::TestEditorCcpuCanCopyL ),
        ENTRY( "TestEditorCcpuCopyL", CTestDOMEditor::TestEditorCcpuCopyL ),
        ENTRY( "TestEditorCcpuCanPaste",
                CTestDOMEditor::TestEditorCcpuCanPasteL ),
        ENTRY( "TestEditorCcpuPasteL", CTestDOMEditor::TestEditorCcpuPasteL ),
        ENTRY( "TestEditorCcpuCanUndo", CTestDOMEditor::TestEditorCcpuCanUndoL ),
        ENTRY( "TestEditorCcpuUndoL", CTestDOMEditor::TestEditorCcpuUndoL ),
        ENTRY( "TestEditorOpenVKB", CTestDOMEditor::TestEditorOpenVKBL ),

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
