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



#ifndef C_TESTDOMEDITOR_H
#define C_TESTDOMEDITOR_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KTestDOMEditorLogPath, "\\logs\\testframework\\testdomeditor\\" ); 
// Log file
_LIT( KTestDOMEditorLogFile, "testdomeditor.txt" ); 
_LIT( KTestDOMEditorLogFileWithTitle, "testdomeditor_[%S].txt" );

/**
*  CTestDOMEditor test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMEditor ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMEditor* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMEditor();

public: // Functions from base classes

    /**
    * From CScriptBase Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
    * @return Symbian OS error code
    */
    virtual TInt RunMethodL( CStifItemParser& aItem );

private:

    /**
    * C++ default constructor.
    */
    CTestDOMEditor( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // test methods in aknedformaccessor.h

    /**
    * test default constructor method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAcceDefConsL( CStifItemParser& aItem );

    /**
    * test SetEdwin method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAcceSetEdwinL( CStifItemParser& aItem );

private: // test methods in aknedwindrawingmodifier.h

    /**
    * test SetInhibitNotifyNewFormatDrawing method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestModifSetInhibitL( CStifItemParser& aItem );

private: // test methods in aknphonenumbereditor.h

    /**
    * test default construct method of class CAknPhoneNumberEditor::TFormat with
    * no param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTForamtDefConsWithNoParam( CStifItemParser& aItem );

    /**
    * test default construct method of class CAknPhoneNumberEditor::TFormat with
    * resouce.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTForamtDefConsWithResL( CStifItemParser& aItem );

    /**
    * test default construct method of class CAknPhoneNumberEditor::TFormat with
    * font.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTForamtDefConsWithFont( CStifItemParser& aItem );

    /**
    * test SetInhibitNotifyNewFormatDrawing method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorDefConsL( CStifItemParser& aItem );

    /**
    * test ConstructL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorConstructL( CStifItemParser& aItem );

    /**
    * test ConstructFromResourceL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorConstructFromResourceL( CStifItemParser& aItem );

    /**
    * test AddFormat method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorAddFormatL( CStifItemParser& aItem );

    /**
    * test CountFormats method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCountFormatsL( CStifItemParser& aItem );

    /**
    * test Format method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorFormatL( CStifItemParser& aItem );

    /**
    * test CurrentFormatIndex method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCurrentFormatIndexL( CStifItemParser& aItem );

    /**
    * test WouldTextFitInFormat method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorWouldTextFitInFormatL( CStifItemParser& aItem );

    /**
    * test SetFormat method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorSetFormatL( CStifItemParser& aItem );

    /**
    * test Text method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorTextL( CStifItemParser& aItem );

    /**
    * test SetText method with non-pointer param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorSetTextL( CStifItemParser& aItem );

    /**
    * test SizeChanged method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorSizeChangedL( CStifItemParser& aItem );

    /**
    * test OfferKeyEventL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorOfferKeyEventL( CStifItemParser& aItem );

    /**
    * test MinimumSize method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorMinimumSizeL( CStifItemParser& aItem );

    /**
    * test FocusChanged method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorFocusChangedL( CStifItemParser& aItem );

    /**
    * test Draw method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorDrawL( CStifItemParser& aItem );

    /**
    * test InputCapabilities method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorInputCapabilitiesL( CStifItemParser& aItem );

    /**
    * test TextLength method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorTextLengthL( CStifItemParser& aItem );

    /**
    * test CursorPos method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCursorPosL( CStifItemParser& aItem );

    /**
    * test SelectionLength method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorSelectionLengthL( CStifItemParser& aItem );

    /**
    * test Selection method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorSelectionL( CStifItemParser& aItem );

    /**
    * test ClearSelectionL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorClearSelectionL( CStifItemParser& aItem );

    /**
    * test SetSelectionL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorSetSelectionL( CStifItemParser& aItem );

    /**
    * test SetCursorPosL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorSetCursorPosL( CStifItemParser& aItem );

    /**
    * test SelectAllL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorSelectAllL( CStifItemParser& aItem );

    /**
    * test GetText method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorGetTextL( CStifItemParser& aItem );

    /**
    * test GetTextInHBufL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorGetTextInHBufL( CStifItemParser& aItem );

    /**
    * test SetText method with pointer param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorSetTextWithPoiL( CStifItemParser& aItem );

    /**
    * test CancelFepTransaction methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCancelFepTransactionL( CStifItemParser& aItem );

    /**
    * test UpdateScrollBarsL methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorUpdateScrollBarsL( CStifItemParser& aItem );

    /**
    * test CreateScrollBarFrameL methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCreateScrollBarFrameL( CStifItemParser& aItem );

    /**
    * test ScrollBarFrame methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorScrollBarFrameL( CStifItemParser& aItem );

    /**
    * test LineCursorWidth methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorLineCursorWidthL( CStifItemParser& aItem );

    /**
    * test Margins methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorMarginsL( CStifItemParser& aItem );

    /**
    * test ChangeEditorMode methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorChangeEditorModeL( CStifItemParser& aItem );

    /**
    * test GetEditorMode methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorGetEditorModeL( CStifItemParser& aItem );

    /**
    * test ResetEditorToDefaultValues methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorResetEditorToDefaultValuesL( CStifItemParser& aItem );

    /**
    * test HandlePointerEventL methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorHandlePointerEventL( CStifItemParser& aItem );

    /**
    * test CcpuIsFocused methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCcpuIsFocusedL( CStifItemParser& aItem );

    /**
    * test CcpuCanCut methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCcpuCanCutL( CStifItemParser& aItem );

    /**
    * test CcpuCutL methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCcpuCutL( CStifItemParser& aItem );

    /**
    * test CcpuCanCopy methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCcpuCanCopyL( CStifItemParser& aItem );

    /**
    * test CcpuCopyL methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCcpuCopyL( CStifItemParser& aItem );

    /**
    * test CcpuCanPaste methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCcpuCanPasteL( CStifItemParser& aItem );

    /**
    * test CcpuPasteL methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCcpuPasteL( CStifItemParser& aItem );

    /**
    * test CcpuCanUndo methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCcpuCanUndoL( CStifItemParser& aItem );

    /**
    * test CcpuUndoL methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorCcpuUndoL( CStifItemParser& aItem );

    /**
    * test OpenVKB methodm.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestEditorOpenVKBL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTDOMEDITOR_H

// End of File
