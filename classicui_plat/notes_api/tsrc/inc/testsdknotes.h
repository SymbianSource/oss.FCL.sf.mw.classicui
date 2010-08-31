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



#ifndef C_TESTSDKNOTES_H
#define C_TESTSDKNOTES_H

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
_LIT( KtestsdknotesLogPath, "\\logs\\testframework\\testsdknotes\\" ); 
// Log file
_LIT( KtestsdknotesLogFile, "testsdknotes.txt" ); 
_LIT( KtestsdknotesLogFileWithTitle, "testsdknotes_[%S].txt" );

// FORWARD DECLARATIONS
class CEikSpacer;

/**
*  CTestSDKNotes test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKNotes) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKNotes* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKNotes();

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
    CTestSDKNotes( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Frees all resources allocated from test methods.
    * @since S60 5.0
    */
    void Delete();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();
    
private: // Test EIKINFO.H
/*                               class CEikInfoDialog                         */
    /**
     * TestNCEikInfoDialogL test function for testing the 
     *     CEikInfoDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNCEikInfoDialogL( CStifItemParser& aItem );

    /**
     * TestNRunDlgLD test function for testing the 
     *     RunDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNRunDlgLD( CStifItemParser& aItem );
    
    /**
     * TestNHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNHandlePointerEventL( CStifItemParser& aItem );

private: // Test EIKPROGI.H
/*                               class CEikProgressInfo                       */
    /**
     * TestNPIDeconstructorL test function for testing the 
     *     ~CEikProgressInfo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestNPICEikProgressInfoL test function for testing the 
     *     CEikProgressInfo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPICEikProgressInfoL( CStifItemParser& aItem );
    
    /**
     * TestNPICEikProgressInfoSinfoL test function for testing the 
     *     CEikProgressInfo function using the information held in 
     *     the specified @c SInfo struct.
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPICEikProgressInfoSinfoL( CStifItemParser& aItem );
    
    /**
     * TestNPIIncrementAndDrawL test function for testing the 
     *     IncrementAndDraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIIncrementAndDrawL( CStifItemParser& aItem );
    
    /**
     * TestNPISetAndDrawL test function for testing the 
     *     SetAndDraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPISetAndDrawL( CStifItemParser& aItem );
    
    /**
     * TestNPIConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestNPISetLayoutL test function for testing the 
     *     SetLayout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPISetLayoutL( CStifItemParser& aItem );
    
    /**
     * TestNPISetBorderL test function for testing the 
     *     SetBorder function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPISetBorderL( CStifItemParser& aItem );
    
    /**
     * TestNPISetFinalValueL test function for testing the 
     *     SetFinalValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPISetFinalValueL( CStifItemParser& aItem );
    
    /**
     * TestNPIConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIConstructL( CStifItemParser& aItem );
    
    /**
     * TestNPIInfoL test function for testing the 
     *     Info function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIInfoL( CStifItemParser& aItem );
    
    /**
     * TestNPILayoutL test function for testing the 
     *     Layout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPILayoutL( CStifItemParser& aItem );
    
    /**
     * TestNPICurrentValueL test function for testing the 
     *     CurrentValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPICurrentValueL( CStifItemParser& aItem );
    
    /**
     * TestNPIEvaluateTextL test function for testing the 
     *     EvaluateText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIEvaluateTextL( CStifItemParser& aItem );
    
    /**
     * TestNPIActivateL test function for testing the 
     *     ActivateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIActivateL( CStifItemParser& aItem );
    
    /**
     * TestNPIMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIMinimumSizeL( CStifItemParser& aItem );
    
    /**
     * TestNPISizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPISizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestNPIGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIGetColorUseListL( CStifItemParser& aItem );
    
    /**
     * TestNPIHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestNPIHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestNPIWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPIWriteInternalStateL( CStifItemParser& aItem );
    
private: // Test AknNoteDialog.h
/*                               class CAknNoteDialog                         */
    /**
     * TestNDCAknNoteDialogL test function for testing the 
     *     CAknNoteDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDCAknNoteDialogL( CStifItemParser& aItem );
    
    /**
     * TestNDCAknNoteDialogToneL test function for testing the 
     *     CAknNoteDialog function with the tone
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDCAknNoteDialogToneL( CStifItemParser& aItem );
    
    /**
     * TestNDCAknNoteDialogPointerL test function for testing the 
     *     CAknNoteDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDCAknNoteDialogPointerL( CStifItemParser& aItem );
    
    /**
     * TestNDDeconstructorL test function for testing the 
     *     ~CAknNoteDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestNDSetTimeoutL test function for testing the 
     *     SetTimeout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetTimeoutL( CStifItemParser& aItem );
    
    /**
     * TestNDSetToneL test function for testing the 
     *     SetTone function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetToneL( CStifItemParser& aItem );
    
    /**
     * TestNDSetTextWrappingL test function for testing the 
     *     SetTextWrapping function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetTextWrappingL( CStifItemParser& aItem );
    
    /**
     * TestNDSetTextProcessingL test function for testing the 
     *     SetTextProcessing function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetTextProcessingL( CStifItemParser& aItem );
    
    /**
     * TestNDSetImageL test function for testing the 
     *     SetImageL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetImageL( CStifItemParser& aItem );
    
    /**
     * TestNDSetIconL test function for testing the 
     *     SetIconL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetIconL( CStifItemParser& aItem );
    
    /**
     * TestNDSetTextNumberL test function for testing the 
     *     SetTextNumberL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetTextNumberL( CStifItemParser& aItem );
    
    /**
     * TestNDSetTextPluralityL test function for testing the 
     *     SetTextPluralityL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetTextPluralityL( CStifItemParser& aItem );
    
    /**
     * TestNDSetTextL test function for testing the 
     *     SetTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetTextL( CStifItemParser& aItem );
    
    /**
     * TestNDOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestNDHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestNDLayoutAndDrawL test function for testing the 
     *     LayoutAndDraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDLayoutAndDrawL( CStifItemParser& aItem );
    
    /**
     * TestNDRunLD test function for testing the 
     *     RunLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDRunLD( CStifItemParser& aItem );
    
    /**
     * TestNDExitSleepingDialogL test function for testing the 
     *     ExitSleepingDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDExitSleepingDialogL( CStifItemParser& aItem );
    
    /**
     * TestNDSetSizeAndPositionL test function for testing the 
     *     SetSizeAndPosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetSizeAndPositionL( CStifItemParser& aItem );
    
    /**
     * TestNDPreLayoutDynInitL test function for testing the 
     *     PreLayoutDynInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDPreLayoutDynInitL( CStifItemParser& aItem );
    
    /**
     * TestNDPostLayoutDynInitL test function for testing the 
     *     PostLayoutDynInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDPostLayoutDynInitL( CStifItemParser& aItem );
    
    /**
     * TestNDPlayToneL test function for testing the 
     *     PlayTone function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDPlayToneL( CStifItemParser& aItem );
    
    /**
     * TestNDReportUserActivityL test function for testing the 
     *     ReportUserActivity function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDReportUserActivityL( CStifItemParser& aItem );
    
    /**
     * TestNDStaticDeleteL test function for testing the 
     *     StaticDeleteL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDStaticDeleteL( CStifItemParser& aItem );
    
    /**
     * TestNDControlAttributesL test function for testing the 
     *     ControlAttributes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDControlAttributesL( CStifItemParser& aItem );
    
    /**
     * TestNDTransferControlAttributesL test function for testing the 
     *     TransferControlAttributes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDTransferControlAttributesL( CStifItemParser& aItem );
    
    /**
     * TestNDSoundSystemL test function for testing the 
     *     SoundSystem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSoundSystemL( CStifItemParser& aItem );
    
    /**
     * TestNDNoteControlL test function for testing the 
     *     NoteControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDNoteControlL( CStifItemParser& aItem );
    
    /**
     * TestNDExecuteDlgLD test function for testing the 
     *     ExecuteDlgLD function with Timeout
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDExecuteDlgTimeOutLD( CStifItemParser& aItem );
    
    /**
     * TestNDExecuteDlgToneLD test function for testing the 
     *     ExecuteDlgLD function with Tone
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDExecuteDlgToneLD( CStifItemParser& aItem );
    
    /**
     * TestNDExecuteDlgLD test function for testing the 
     *     ExecuteDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDExecuteDlgLD( CStifItemParser& aItem );
    
    /**
     * TestNDRunDlgLD test function for testing the 
     *     RunDlgLD function with Timeout
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDRunDlgTimeOuntLD( CStifItemParser& aItem );
    
    /**
     * TestNDRunDlgLD test function for testing the 
     *     RunDlgLD function with Tone
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDRunDlgToneLD( CStifItemParser& aItem );
    
    /**
     * TestNDRunDlgLD test function for testing the 
     *     RunDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDRunDlgLD( CStifItemParser& aItem );
    
    /**
     * TestNDRunDlgIdLD test function for testing the 
     *     RunDlgLD function with Id
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDRunDlgIdLD( CStifItemParser& aItem );
    
    /**
     * TestNDSetCurrentLabelL test function for testing the 
     *     SetCurrentLabelL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetCurrentLabelL( CStifItemParser& aItem );
    
    /**
     * TestNDSetNoMemoryAllocationL test function for testing the 
     *     SetNoMemoryAllocation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDSetNoMemoryAllocationL( CStifItemParser& aItem );
    
    /**
     * TestNDHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNDHandlePointerEventL( CStifItemParser& aItem );
    
private: // Test AknNoteWrappers.h
/*                               class CAknNoteWrapper                        */
    /**
     * TestNWCAknNoteWrapperL test function for testing the 
     *     CAknNoteWrapper function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWCAknNoteWrapperL( CStifItemParser& aItem );
    
    /**
     * TestNWCAknNoteWrapperPointerL test function for testing the 
     *     CAknNoteWrapper function with pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWCAknNoteWrapperPointerL( CStifItemParser& aItem );
    
    /**
     * TestNWExecuteLD test function for testing the 
     *     ExecuteLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWExecuteLD( CStifItemParser& aItem );
    
    /**
     * TestNWExecutePromptLD test function for testing the 
     *     ExecuteLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWExecutePromptLD( CStifItemParser& aItem );
    
    /**
     * TestNWHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestNWHandleDialogPageEventL test function for testing the 
     *     HandleDialogPageEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWHandleDialogPageEventL( CStifItemParser& aItem );
    
/*                               class CAknResourceNoteDialog                 */
    /**
     * TestNRNDExecuteLD test function for testing the 
     *     ExecuteLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNRNDExecuteLD( CStifItemParser& aItem );
    
    /**
     * TestNRNDExecutePromptLD test function for testing the 
     *     ExecuteLD function with prompt
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNRNDExecutePromptLD( CStifItemParser& aItem );
    
    /**
     * TestNRNDHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function with prompt
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNRNDHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestNRNDCAknResourceNoteDialogL test function for testing the 
     *     CAknResourceNoteDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNRNDCAknResourceNoteDialogL( CStifItemParser& aItem );
    
    /**
     * TestNRNDCAknResourceNoteDialogPointerL test function for testing the 
     *     CAknResourceNoteDialog function with pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNRNDCAknResourceNoteDialogPointerL( CStifItemParser& aItem );
    
/*                               class CAknConfirmationNote                   */
    /**
     * TestNCNCAknConfirmationNoteL test function for testing the 
     *     CAknConfirmationNote function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNCNCAknConfirmationNoteL( CStifItemParser& aItem );
    
    /**
     * TestNCNCAknConfirmationNoteParameterL test function for testing the 
     *     CAknConfirmationNote function with parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNCNCAknConfirmationNoteParameterL( CStifItemParser& aItem );
    
    /**
     * TestNCNCAknConfirmationNotePointerL test function for testing the 
     *     CAknConfirmationNote function with Pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNCNCAknConfirmationNotePointerL( CStifItemParser& aItem );
    
    /**
     * TestNCNHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function with Pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNCNHandlePointerEventL( CStifItemParser& aItem );
    
/*                               class CAknInformationNote                     */
    /**
     * TestNINCAknInformationNoteL test function for testing the 
     *     CAknInformationNote function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNINCAknInformationNoteL( CStifItemParser& aItem );
    
    /**
     * TestNINCAknInformationNoteParameterL test function for testing the 
     *     CAknInformationNote function with Parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNINCAknInformationNoteParameterL( CStifItemParser& aItem );
    
    /**
     * TestNINCAknInformationNotePointerL test function for testing the 
     *     CAknInformationNote function with Pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNINCAknInformationNotePointerL( CStifItemParser& aItem );
    
    /**
     * TestNINHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function with Pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNINHandlePointerEventL( CStifItemParser& aItem );
    
/*                               class CAknErrorNote                         */
    /**
     * TestNENCAknErrorNoteL test function for testing the 
     *     CAknErrorNote function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNENCAknErrorNoteL( CStifItemParser& aItem );
    
    /**
     * TestNENCAknErrorNoteParameterL test function for testing the 
     *     CAknErrorNote function with Parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNENCAknErrorNoteParameterL( CStifItemParser& aItem );
    
    /**
     * TestNENCAknErrorNotePointerL test function for testing the 
     *     CAknErrorNote function with Pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNENCAknErrorNotePointerL( CStifItemParser& aItem );
    
    /**
     * TestNENHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function with Pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNENHandlePointerEventL( CStifItemParser& aItem );
    
/*                               class CAknWarningNote                        */
    /**
     * TestNWNCAknWarningNoteL test function for testing the 
     *     CAknWarningNote function with Pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWNCAknWarningNoteL( CStifItemParser& aItem );
    
    /**
     * TestNWNCAknWarningNoteParameterL test function for testing the 
     *     CAknWarningNote function with Parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWNCAknWarningNoteParameterL( CStifItemParser& aItem );
    
    /**
     * TestNWNCAknWarningNotePointerL test function for testing the 
     *     CAknWarningNote function with Pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWNCAknWarningNotePointerL( CStifItemParser& aItem );
    
    /**
     * TestNWNHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function with Pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWNHandlePointerEventL( CStifItemParser& aItem );
    
/*                               class CAknProgressDialog                   */
    /**
     * TestNPDCAknProgressDialogValueL test function for testing the 
     *     CAknProgressDialog function with Value
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDCAknProgressDialogValueL( CStifItemParser& aItem );
    
    /**
     * TestNPDCAknProgressDialogPointerL test function for testing the 
     *     CAknProgressDialog function with Pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDCAknProgressDialogPointerL( CStifItemParser& aItem );
    
    /**
     * TestNPDCAknProgressDialogL test function for testing the 
     *     CAknProgressDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDCAknProgressDialogL( CStifItemParser& aItem );
    
    /**
     * TestNPDDeconstructorL test function for testing the 
     *     ~CAknProgressDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestNPDRunLD test function for testing the 
     *     RunLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDRunLD( CStifItemParser& aItem );
    
    /**
     * TestNPDGetProgressInfoL test function for testing the 
     *     GetProgressInfoL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDGetProgressInfoL( CStifItemParser& aItem );
    
    /**
     * TestNPDOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestNPDProcessFinishedL test function for testing the 
     *     ProcessFinishedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDProcessFinishedL( CStifItemParser& aItem );
    
    /**
     * TestNPDSetCallbackL test function for testing the 
     *     SetCallback function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDSetCallbackL( CStifItemParser& aItem );
    
    /**
     * TestNPDHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestNPDPreLayoutDynInitL test function for testing the 
     *     PreLayoutDynInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDPreLayoutDynInitL( CStifItemParser& aItem );
    
    /**
     * TestNPDOkToExitL test function for testing the 
     *     OkToExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNPDOkToExitL( CStifItemParser& aItem );
    
/*                       class CAknStaticNoteStackIndicator               */
    /**
     * TestNSNSIHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSNSIHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestNSNSIHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSNSIHandlePointerEventL( CStifItemParser& aItem );
    
/*                           class CAknStaticNoteDialog                    */
    /**
     * TestNSNDCAknStaticNoteDialogL test function for testing the 
     *     CAknStaticNoteDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSNDCAknStaticNoteDialogL( CStifItemParser& aItem );
    
    /**
     * TestNSNDCAknStaticNoteDialogPointerL test function for testing the 
     *     CAknStaticNoteDialog function with pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSNDCAknStaticNoteDialogPointerL( CStifItemParser& aItem );
    
    /**
     * TestNSNDDeconstructorL test function for testing the 
     *     ~CAknStaticNoteDialog function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSNDDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestNSNDSetNumberOfBordersL test function for testing the 
     *     SetNumberOfBorders function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSNDSetNumberOfBordersL( CStifItemParser& aItem );
    
    /**
     * TestNSNDHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSNDHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestNSNDPostLayoutDynInitL test function for testing the 
     *     PostLayoutDynInitL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSNDPostLayoutDynInitL( CStifItemParser& aItem );
    
    /**
     * TestNSNDOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSNDOfferKeyEventL( CStifItemParser& aItem );
    
/*                             class CAknWaitDialog                     */
    /**
     * TestNWDCAknWaitDialogL test function for testing the 
     *     CAknWaitDialog function with pointer
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWDCAknWaitDialogL( CStifItemParser& aItem );
    
    /**
     * TestNWDCAknWaitDialogBoolL test function for testing the 
     *     CAknWaitDialog function with two parameters
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWDCAknWaitDialogBoolL( CStifItemParser& aItem );
    
    /**
     * TestNWDHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function with two parameters
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWDHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestNWDGetProgressInfoL test function for testing the 
     *     GetProgressInfo function with two parameters
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWDGetProgressInfoL( CStifItemParser& aItem );
    
/*                             class CAknWaitNoteWrapper               */
    /**
     * TestNWNWCAknWaitNoteWrapperL test function for testing the 
     *     CAknWaitNoteWrapper function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWNWCAknWaitNoteWrapperL( CStifItemParser& aItem );
    
    /**
     * TestNWNWDeconstructorL test function for testing the 
     *     ~CAknWaitNoteWrapper function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWNWDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestNWNWExecuteL test function for testing the 
     *     ExecuteL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWNWExecuteL( CStifItemParser& aItem );
    
    /**
     * TestNWNWExecutePromptL test function for testing the 
     *     ExecuteL function with prompt
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWNWExecutePromptL( CStifItemParser& aItem );
    
    /**
     * TestNWNWWaitDialogL test function for testing the 
     *     WaitDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNWNWWaitDialogL( CStifItemParser& aItem );
    
/*                             class CAknNoteControl                   */
    /**
     * TestNNCCAknNoteControlL test function for testing the 
     *     CAknNoteControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCCAknNoteControlL( CStifItemParser& aItem );
    
    /**
     * TestNNCDeconstructorL test function for testing the 
     *     ~CAknNoteControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestNNCSetImageL test function for testing the 
     *     SetImageL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCSetImageL( CStifItemParser& aItem );
    
    /**
     * TestNNCSetAnimationL test function for testing the 
     *     SetAnimationL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCSetAnimationL( CStifItemParser& aItem );
    
    /**
     * TestNNCSetIconL test function for testing the 
     *     SetIconL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCSetIconL( CStifItemParser& aItem );
    
    /**
     * TestNNCSetFinalProgressValueL test function for testing the 
     *     SetFinalProgressValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCSetFinalProgressValueL( CStifItemParser& aItem );
    
    /**
     * TestNNCIncrementBarsAndDrawL test function for testing the 
     *     IncrementBarsAndDraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCIncrementBarsAndDrawL( CStifItemParser& aItem );
    
    /**
     * TestNNCCreateProgressBarL test function for testing the 
     *     CreateProgressBarL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCCreateProgressBarL( CStifItemParser& aItem );
    
    /**
     * TestNNCGetProgressInfoL test function for testing the 
     *     GetProgressInfo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCGetProgressInfoL( CStifItemParser& aItem );
    
    /**
     * TestNNCStartAnimationL test function for testing the 
     *     StartAnimationL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCStartAnimationL( CStifItemParser& aItem );
    
    /**
     * TestNNCCancelAnimationL test function for testing the 
     *     CancelAnimation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCCancelAnimationL( CStifItemParser& aItem );
    
    /**
     * TestNNCResetTextL test function for testing the 
     *     ResetText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCResetTextL( CStifItemParser& aItem );
    
    /**
     * TestNNCSetTextL test function for testing the 
     *     SetTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCSetTextL( CStifItemParser& aItem );
    
    /**
     * TestNNCSetTextLineNumL test function for testing the 
     *     SetTextL function with linenum
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCSetTextLineNumL( CStifItemParser& aItem );
    
    /**
     * TestNNCSetTextNumberL test function for testing the 
     *     SetTextNumberL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCSetTextNumberL( CStifItemParser& aItem );
    
    /**
     * TestNNCSetTextPluralityL test function for testing the 
     *     SetTextPluralityL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCSetTextPluralityL( CStifItemParser& aItem );
    
    /**
     * TestNNCNumberOfLinesL test function for testing the 
     *     NumberOfLines function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCNumberOfLinesL( CStifItemParser& aItem );
    
    /**
     * TestNNCLayoutL test function for testing the 
     *     Layout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCLayoutL( CStifItemParser& aItem );
    
    /**
     * TestNNCNoteHeightL test function for testing the 
     *     NoteHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCNoteHeightL( CStifItemParser& aItem );
    
    /**
     * TestNNCNoteWidthL test function for testing the 
     *     NoteWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCNoteWidthL( CStifItemParser& aItem );
    
    /**
     * TestNNCHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestNNCSetDynamicTextL test function for testing the 
     *     SetDynamicTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCSetDynamicTextL( CStifItemParser& aItem );
    
    /**
     * TestNNCUpdateAndFormatLabelsL test function for testing the 
     *     UpdateAndFormatLabelsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCUpdateAndFormatLabelsL( CStifItemParser& aItem );
    
    /**
     * TestNNCUpdateLabelsLeaveL test function for testing the 
     *     UpdateLabelsL function with Leave
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCUpdateLabelsLeaveL( CStifItemParser& aItem );
    
    /**
     * TestNNCUpdateLabelsL test function for testing the 
     *     UpdateLabelsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCUpdateLabelsL( CStifItemParser& aItem );
    
    /**
     * TestNNCSetLabelReserveLengthL test function for testing the 
     *     SetLabelReserveLengthL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCSetLabelReserveLengthL( CStifItemParser& aItem );
    
    /**
     * TestNNCMopSupplyObjectL test function for testing the 
     *     MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCMopSupplyObjectL( CStifItemParser& aItem );
    
    /**
     * TestNNCSetBgRectL test function for testing the 
     *     SetBgRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNNCSetBgRectL( CStifItemParser& aItem );


private:    // Data
    
    /**
     * for Cancel ScreenSaver
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKNOTES_H

// End of File
