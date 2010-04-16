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
* Description:  test EIKEDWIN.h
*
*/



#ifndef C_TESTSDKEDITORS_H
#define C_TESTSDKEDITORS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <fldbase.h>
#include <flddef.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS

class CEikonEnv;

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkeditorsLogPath, "\\logs\\testframework\\testsdkeditors\\" ); 
// Log file
_LIT( KtestsdkeditorsLogFile, "testsdkeditors.txt" ); 
_LIT( KtestsdkeditorsLogFileWithTitle, "testsdkeditors_[%S].txt" );

/**
*  CTestSDKEditors test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKEditors ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKEditors* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKEditors();

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
    CTestSDKEditors( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test Aknedsts.h
/*                               class TAknEditorCaseState                    */
    /**
     * TestECSTAknEditorCaseStateL test function for testing the 
     *     TAknEditorCaseState function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECSTAknEditorCaseStateL( CStifItemParser& aItem );
    
    /**
     * TestECSSetCurrentCaseL test function for testing the 
     *     SetCurrentCase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECSSetCurrentCaseL( CStifItemParser& aItem );
    
    /**
     * TestECSSetPreviousCaseL test function for testing the 
     *     SetPreviousCase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECSSetPreviousCaseL( CStifItemParser& aItem );
    
    /**
     * TestECSSetPreviousCaseUsedToEnterTextL test function for testing the 
     *     SetPreviousCaseUsedToEnterText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECSSetPreviousCaseUsedToEnterTextL( CStifItemParser& aItem );
    
    /**
     * TestECSCurrentCaseL test function for testing the 
     *     CurrentCase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECSCurrentCaseL( CStifItemParser& aItem );
    
    /**
     * TestECSPreviousCaseL test function for testing the 
     *     PreviousCase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECSPreviousCaseL( CStifItemParser& aItem );
    
    /**
     * TestECSPreviousCaseUsedToEnterTextL test function for testing the 
     *     PreviousCaseUsedToEnterText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECSPreviousCaseUsedToEnterTextL( CStifItemParser& aItem );
    
    /**
     * TestECSSetFlagL test function for testing the 
     *     SetFlag function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECSSetFlagL( CStifItemParser& aItem );
    
    /**
     * TestECSClearFlagL test function for testing the 
     *     ClearFlag function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECSClearFlagL( CStifItemParser& aItem );
    
    /**
     * TestECSIsFlagSetL test function for testing the 
     *     IsFlagSet function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECSIsFlagSetL( CStifItemParser& aItem );
    
/*                               class CAknEdwinState                         */
    /**
     * TestESCAknEdwinStateL test function for testing the 
     *     CAknEdwinState function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESCAknEdwinStateL( CStifItemParser& aItem );
    
    /**
     * TestESSetObserverL test function for testing the 
     *     SetObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetObserverL( CStifItemParser& aItem );
    
    /**
     * TestESReportAknEdStateEventL test function for testing the 
     *     ReportAknEdStateEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESReportAknEdStateEventL( CStifItemParser& aItem );
    
    /**
     * TestESFlagsL test function for testing the 
     *     Flags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESFlagsL( CStifItemParser& aItem );
    
    /**
     * TestESDefaultInputModeL test function for testing the 
     *     DefaultInputMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESDefaultInputModeL( CStifItemParser& aItem );
    
    /**
     * TestESCurrentInputModeL test function for testing the 
     *     CurrentInputMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESCurrentInputModeL( CStifItemParser& aItem );
    
    /**
     * TestESPermittedInputModesL test function for testing the 
     *     PermittedInputModes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESPermittedInputModesL( CStifItemParser& aItem );
    
    /**
     * TestESDefaultCaseL test function for testing the 
     *     DefaultCase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESDefaultCaseL( CStifItemParser& aItem );
    
    /**
     * TestESCurrentCaseL test function for testing the 
     *     CurrentCase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESCurrentCaseL( CStifItemParser& aItem );
    
    /**
     * TestESPermittedCasesL test function for testing the 
     *     PermittedCases function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESPermittedCasesL( CStifItemParser& aItem );
    
    /**
     * TestESDefaultLanguageL test function for testing the 
     *     DefaultLanguage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESDefaultLanguageL( CStifItemParser& aItem );
    
    /**
     * TestESSpecialCharacterTableResourceIdL test function for testing the 
     *     SpecialCharacterTableResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSpecialCharacterTableResourceIdL( CStifItemParser& aItem );
    
    /**
     * TestESNumericKeymapL test function for testing the 
     *     NumericKeymap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESNumericKeymapL( CStifItemParser& aItem );
    
    /**
     * TestESCurrentInlineEditSpanL test function for testing the 
     *     CurrentInlineEditSpan function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESCurrentInlineEditSpanL( CStifItemParser& aItem );
    
    /**
     * TestESCbaStateL test function for testing the 
     *     CbaState function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESCbaStateL( CStifItemParser& aItem );
    
    /**
     * TestESMenuBarL test function for testing the 
     *     MenuBar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESMenuBarL( CStifItemParser& aItem );
    
    /**
     * TestESCcpuStateL test function for testing the 
     *     CcpuState function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESCcpuStateL( CStifItemParser& aItem );
    
    /**
     * TestESObjectProviderL test function for testing the 
     *     ObjectProvider function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESObjectProviderL( CStifItemParser& aItem );
    
    /**
     * TestESLocalLanguageL test function for testing the 
     *     LocalLanguage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESLocalLanguageL( CStifItemParser& aItem );
    
    /**
     * TestESFormAccessorL test function for testing the 
     *     FormAccessor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESFormAccessorL( CStifItemParser& aItem );
    
    /**
     * TestESSetFlagsL test function for testing the 
     *     SetFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetFlagsL( CStifItemParser& aItem );
    
    /**
     * TestESSetDefaultInputModeL test function for testing the 
     *     SetDefaultInputMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetDefaultInputModeL( CStifItemParser& aItem );
    
    /**
     * TestESSetCurrentInputModeL test function for testing the 
     *     SetCurrentInputMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetCurrentInputModeL( CStifItemParser& aItem );
    
    /**
     * TestESSetPermittedInputModesL test function for testing the 
     *     SetPermittedInputModes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetPermittedInputModesL( CStifItemParser& aItem );
    
    /**
     * TestESSetDefaultCaseL test function for testing the 
     *     SetDefaultCase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetDefaultCaseL( CStifItemParser& aItem );
    
    /**
     * TestESSetCurrentCaseL test function for testing the 
     *     SetCurrentCase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetCurrentCaseL( CStifItemParser& aItem );
    
    /**
     * TestESSetPermittedCasesL test function for testing the 
     *     SetPermittedCases function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetPermittedCasesL( CStifItemParser& aItem );
    
    /**
     * TestESSetDefaultLanguageL test function for testing the 
     *     SetDefaultLanguage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetDefaultLanguageL( CStifItemParser& aItem );
    
    /**
     * TestESSetSpecialCharacterTableResourceIdL test function for testing the 
     *     SetSpecialCharacterTableResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetSpecialCharacterTableResourceIdL( CStifItemParser& aItem );
    
    /**
     * TestESSetNumericKeymapL test function for testing the 
     *     SetNumericKeymap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetNumericKeymapL( CStifItemParser& aItem );
    
    /**
     * TestESSetInlineEditSpanL test function for testing the 
     *     SetInlineEditSpan function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetInlineEditSpanL( CStifItemParser& aItem );
    
    /**
     * TestESSetCbaL test function for testing the 
     *     SetCba function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetCbaL( CStifItemParser& aItem );
    
    /**
     * TestESSetMenuL test function for testing the 
     *     SetMenu function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetMenuL( CStifItemParser& aItem );
    
    /**
     * TestESSetObjectProviderL test function for testing the 
     *     SetObjectProvider function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetObjectProviderL( CStifItemParser& aItem );
    
    /**
     * TestESSetLocalLanguageL test function for testing the 
     *     SetLocalLanguage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetLocalLanguageL( CStifItemParser& aItem );
    
    /**
     * TestESSetFormAccessorL test function for testing the 
     *     SetFormAccessor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetFormAccessorL( CStifItemParser& aItem );
    
    /**
     * TestESSetCcpuStateL test function for testing the 
     *     SetCcpuState function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetCcpuStateL( CStifItemParser& aItem );
    
    /**
     * TestESSetMiddleSoftkeyCommandIdL test function for testing the 
     *     SetMiddleSoftkeyCommandId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESSetMiddleSoftkeyCommandIdL( CStifItemParser& aItem );
    
    /**
     * TestESMiddleSoftkeyCommandIdL test function for testing the 
     *     MiddleSoftkeyCommandId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESMiddleSoftkeyCommandIdL( CStifItemParser& aItem );
    //aknipfed.h
/*                               class CAknIpFieldEditor                    */
    /**
     * TestIPFECAknIpFieldEditorL test function for testing the 
     *     CAknIpFieldEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPFECAknIpFieldEditorL( CStifItemParser& aItem );
    
    /**
     * TestIPFEPNewL test function for testing the 
     *     NewL function with parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPFEPNewL( CStifItemParser& aItem );
    
    /**
     * TestIPFENewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPFENewL( CStifItemParser& aItem );
    
    /**
     * TestIPFESetAddressL test function for testing the 
     *     SetAddress function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPFESetAddressL( CStifItemParser& aItem );
    
    /**
     * TestIPFEAddressL test function for testing the 
     *     Address function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPFEAddressL( CStifItemParser& aItem );
    
    /**
     * TestIPFESetMinimumAndMaximumL test function for testing the 
     *     SetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPFESetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestIPFEGetMinimumAndMaximumL test function for testing the 
     *     GetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPFEGetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestIPFEReadIPAddressL test function for testing the 
     *     ReadIPAddress function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPFEReadIPAddressL( CStifItemParser& aItem );
    
    /**
     * TestIPFEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPFEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestIPFEOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPFEOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestIPFEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPFEHandlePointerEventL( CStifItemParser& aItem );
    
    //AknLocationEd.h
/*                               class CAknLocationEditor                  */
    /**
     * TestLECAknLocationEditorL test function for testing the 
     *     CAknLocationEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLECAknLocationEditorL( CStifItemParser& aItem );
    
    /**
     * TestLEDeconstructorL test function for testing the 
     *     ~CAknLocationEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLEDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestLENewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLENewL( CStifItemParser& aItem );
    
    /**
     * TestLEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestLEDisplayableLocationL test function for testing the 
     *     DisplayableLocationL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLEDisplayableLocationL( CStifItemParser& aItem );
    
    /**
     * TestLEPrepareForFocusLossL test function for testing the 
     *     PrepareForFocusLossL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLEPrepareForFocusLossL( CStifItemParser& aItem );
    
    /**
     * TestLESetL test function for testing the 
     *     Set function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLESetL( CStifItemParser& aItem );
    
    /**
     * TestLEGetL test function for testing the 
     *     Get function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLEGetL( CStifItemParser& aItem );
    
    /**
     * TestLEOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLEOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestLECAknLocationEditor_ExtensionInterfaceL test function for testing the 
     *     CAknLocationEditor_ExtensionInterface function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLECAknLocationEditor_ExtensionInterfaceL( CStifItemParser& aItem );
    
    //AknNumed.h
/*                               class CAknNumericEdwin                  */
    /**
     * TestNEDeconstructorL test function for testing the 
     *     ~CAknNumericEdwin function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNEDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestNEMapKeyEventL test function for testing the 
     *     MapKeyEvent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNEMapKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestNEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNEHandlePointerEventL( CStifItemParser& aItem );
    
    //AknNumEdwin.h
/*                               class CAknIntegerEdwin                  */
    /**
     * TestIENewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIENewL( CStifItemParser& aItem );
    
    /**
     * TestIEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestIEConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIEConstructL( CStifItemParser& aItem );
    
    /**
     * TestIESetValueL test function for testing the 
     *     SetValueL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIESetValueL( CStifItemParser& aItem );
    
    /**
     * TestIESetUnsetValueL test function for testing the 
     *     SetUnsetValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIESetUnsetValueL( CStifItemParser& aItem );
    
    /**
     * TestIEGetTextAsIntegerL test function for testing the 
     *     GetTextAsInteger function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIEGetTextAsIntegerL( CStifItemParser& aItem );
    
    /**
     * TestIESetMinimumIntegerValueL test function for testing the 
     *     SetMinimumIntegerValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIESetMinimumIntegerValueL( CStifItemParser& aItem );
    
    /**
     * TestIESetMaximumIntegerValueL test function for testing the 
     *     SetMaximumIntegerValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIESetMaximumIntegerValueL( CStifItemParser& aItem );
    
    /**
     * TestIEPrepareForFocusLossL test function for testing the 
     *     PrepareForFocusLossL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIEPrepareForFocusLossL( CStifItemParser& aItem );
    
    /**
     * TestIEHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIEHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestIEOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIEOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestIEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIEHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestIECheckNumberL test function for testing the 
     *     CheckNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIECheckNumberL( CStifItemParser& aItem );
    
    //Aknnumseced.h
/*                       class CAknNumericSecretEditor                  */
    /**
     * TestNSECAknNumericSecretEditorL test function for testing the 
     *     CAknNumericSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSECAknNumericSecretEditorL( CStifItemParser& aItem ); 
    
    /**
     * TestNSEInputCapabilitiesL test function for testing the 
     *     InputCapabilities function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSEInputCapabilitiesL( CStifItemParser& aItem ); 
    
    /**
     * TestNSEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSEHandlePointerEventL( CStifItemParser& aItem ); 
    
    /**
     * TestNSEAppendCharacterL test function for testing the 
     *     AppendCharacterL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSEAppendCharacterL( CStifItemParser& aItem ); 
    
    /**
     * TestNSECreateFepStateL test function for testing the 
     *     CreateFepStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNSECreateFepStateL( CStifItemParser& aItem ); 

    //aknuniteditor.h
/*                              class CAknUnitEditor                      */
    /**
     * TestUENewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUENewL( CStifItemParser& aItem ); 
    
    /**
     * TestUENewLC test function for testing the 
     *     NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUENewLC( CStifItemParser& aItem ); 
    
    /**
     * TestUEConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUEConstructL( CStifItemParser& aItem ); 
    
    /**
     * TestUEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUEConstructFromResourceL( CStifItemParser& aItem ); 
    
    /**
     * TestUESetValueL test function for testing the 
     *     SetValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUESetValueL( CStifItemParser& aItem ); 
    
    /**
     * TestUEValueL test function for testing the 
     *     Value function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUEValueL( CStifItemParser& aItem ); 
    
    /**
     * TestUESupportsUnitL test function for testing the 
     *     SupportsUnit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUESupportsUnitL( CStifItemParser& aItem ); 
    
    /**
     * TestUESetUnitL test function for testing the 
     *     SetUnitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUESetUnitL( CStifItemParser& aItem ); 
    
    /**
     * TestUESetUnitUL test function for testing the 
     *     SetUnitL function with Unit
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUESetUnitUL( CStifItemParser& aItem ); 
    
    /**
     * TestUEGetUnitL test function for testing the 
     *     GetUnit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUEGetUnitL( CStifItemParser& aItem ); 
    
    /**
     * TestUEUnitL test function for testing the 
     *     Unit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUEUnitL( CStifItemParser& aItem ); 
    
    /**
     * TestUESetMaxFractionalDigitsL test function for testing the 
     *     SetMaxFractionalDigits function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUESetMaxFractionalDigitsL( CStifItemParser& aItem ); 
    
    /**
     * TestUEMaxFractionalDigitsL test function for testing the 
     *     MaxFractionalDigits function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUEMaxFractionalDigitsL( CStifItemParser& aItem ); 
    
    /**
     * TestUESetMinimumAndMaximumL test function for testing the 
     *     SetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUESetMinimumAndMaximumL( CStifItemParser& aItem ); 
    
    /**
     * TestUEGetMinimumAndMaximumL test function for testing the 
     *     GetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUEGetMinimumAndMaximumL( CStifItemParser& aItem ); 
    
    /**
     * TestUESetFlagsL test function for testing the 
     *     SetFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUESetFlagsL( CStifItemParser& aItem ); 
    
    /**
     * TestUEFlagsL test function for testing the 
     *     Flags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUEFlagsL( CStifItemParser& aItem ); 
    
    /**
     * TestUEPrepareForFocusLossL test function for testing the 
     *     PrepareForFocusLossL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestUEPrepareForFocusLossL( CStifItemParser& aItem ); 
    
    //EikCcpu.h
/*                              class CAknCcpuSupport                      */
    /**
     * TestCCAknCcpuSupportL test function for testing the 
     *     CAknCcpuSupport function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCAknCcpuSupportL( CStifItemParser& aItem ); 
    
    /**
     * TestCDeconstructorL test function for testing the 
     *     ~CAknCcpuSupport function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDeconstructorL( CStifItemParser& aItem ); 
    
    /**
     * TestCConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCConstructL( CStifItemParser& aItem ); 
    
    /**
     * TestCHandleSelectionChangeL test function for testing the 
     *     HandleSelectionChangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHandleSelectionChangeL( CStifItemParser& aItem ); 
    
    /**
     * TestCHandleFocusChangeL test function for testing the 
     *     HandleFocusChangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHandleFocusChangeL( CStifItemParser& aItem ); 
    
    /**
     * TestCOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCOfferKeyEventL( CStifItemParser& aItem ); 
    
    /**
     * TestCHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHandlePointerEventL( CStifItemParser& aItem ); 
    
    /**
     * TestCDynInitMenuPaneL test function for testing the 
     *     DynInitMenuPaneL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDynInitMenuPaneL( CStifItemParser& aItem ); 
    
    /**
     * TestCProcessCommandL test function for testing the 
     *     ProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCProcessCommandL( CStifItemParser& aItem ); 
    //EIKFPNE.h
/*                    class CEikFloatingPointEditor                      */
    /**
     * TestFPECEikFloatingPointEditorL test function for testing the 
     *     CEikFloatingPointEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPECEikFloatingPointEditorL( CStifItemParser& aItem );
    
    /**
     * TestFPEConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPEConstructL( CStifItemParser& aItem );
    
    /**
     * TestFPEValueL test function for testing the 
     *     Value function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPEValueL( CStifItemParser& aItem );
    
    /**
     * TestFPEGetValueAsRealL test function for testing the 
     *     GetValueAsReal function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPEGetValueAsRealL( CStifItemParser& aItem );
    
    /**
     * TestFPESetValueL test function for testing the 
     *     SetValueL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPESetValueL( CStifItemParser& aItem );
    
    /**
     * TestFPESetMinMaxL test function for testing the 
     *     SetMinMax function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPESetMinMaxL( CStifItemParser& aItem );
    
    /**
     * TestFPEGetMinMaxL test function for testing the 
     *     GetMinMax function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPEGetMinMaxL( CStifItemParser& aItem );
    
    /**
     * TestFPEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestFPEPrepareForFocusLossL test function for testing the 
     *     PrepareForFocusLossL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPEPrepareForFocusLossL( CStifItemParser& aItem );
    
    /**
     * TestFPEInputCapabilitiesL test function for testing the 
     *     InputCapabilities function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPEInputCapabilitiesL( CStifItemParser& aItem );
    
    /**
     * TestFPEOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPEOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestFPEHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPEHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestFPEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPEHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestXPECEikFixedPointEditorL test function for testing the 
     *     CEikFixedPointEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPECEikFixedPointEditorL( CStifItemParser& aItem );
    
    /**
     * TestXPEConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPEConstructL( CStifItemParser& aItem );
    
    /**
     * TestXPEValueL test function for testing the 
     *     Value function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPEValueL( CStifItemParser& aItem );
    
    /**
     * TestXPEGetValueAsIntegerL test function for testing the 
     *     GetValueAsInteger function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPEGetValueAsIntegerL( CStifItemParser& aItem );
    
    /**
     * TestXPESetValueL test function for testing the 
     *     SetValueL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPESetValueL( CStifItemParser& aItem );
    
    /**
     * TestXPESetMinMaxrL test function for testing the 
     *     SetMinMax function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPESetMinMaxrL( CStifItemParser& aItem );
    
    /**
     * TestXPEGetMinMaxL test function for testing the 
     *     GetMinMax function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPEGetMinMaxL( CStifItemParser& aItem );
    
    /**
     * TestXPESetDecimalPlacesL test function for testing the 
     *     SetDecimalPlaces function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPESetDecimalPlacesL( CStifItemParser& aItem );
    
    /**
     * TestXPEDecimalPlacesL test function for testing the 
     *     DecimalPlaces function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPEDecimalPlacesL( CStifItemParser& aItem );
    
    /**
     * TestXPEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestXPEPrepareForFocusLossL test function for testing the 
     *     PrepareForFocusLossL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPEPrepareForFocusLossL( CStifItemParser& aItem );
    
    /**
     * TestXPEInputCapabilitiesL test function for testing the 
     *     InputCapabilities function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPEInputCapabilitiesL( CStifItemParser& aItem );
    
    /**
     * TestXPEOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPEOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestXPEHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPEHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestXPEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestXPEHandlePointerEventL ( CStifItemParser& aItem );
    
    //EIKEDWIN.h
/*                        class CEikEdwinExtension                     */
    /**
     * TestEFAFormAccessorL test function for testing the 
     *     FormAccessor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEFAFormAccessorL( CStifItemParser& aItem );
    
    /**
     * TestEFASetFormAccessorL test function for testing the 
     *     SetFormAccessor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEFASetFormAccessorL( CStifItemParser& aItem );
    
    /**
     * TestEFASetScrollBarSetterL test function for testing the 
     *     SetScrollBarSetter function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEFASetScrollBarSetterL( CStifItemParser& aItem );
    
    /**
     * TestEFAScrollBarSetterL test function for testing the 
     *     ScrollBarSetter function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEFAScrollBarSetterL( CStifItemParser& aItem );
    
    /**
     * TestEFATextWrapperL test function for testing the 
     *     TextWrapper function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEFATextWrapperL( CStifItemParser& aItem );
    
    /**
     * TestEFAFormCursorModifierL test function for testing the 
     *     FormCursorModifier function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEFAFormCursorModifierL( CStifItemParser& aItem );
    
/*                             class CEikEdwin                          */
    /**
     * TestEDeconstrutorL test function for testing the 
     *     ~CEikEdwin function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEDeconstrutorL( CStifItemParser& aItem );
    
    /**
     * TestECEikEdwinL test function for testing the 
     *     CEikEdwin function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECEikEdwinL( CStifItemParser& aItem );
    
    /**
     * TestECEikEdwinPL test function for testing the 
     *     CEikEdwin function with parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECEikEdwinPL( CStifItemParser& aItem );
    
    /**
     * TestEConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEConstructL( CStifItemParser& aItem );
    
    /**
     * TestESetEdwinObserverL test function for testing the 
     *     SetEdwinObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetEdwinObserverL( CStifItemParser& aItem );
    
    /**
     * TestEAddEdwinObserverL test function for testing the 
     *     AddEdwinObserverL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEAddEdwinObserverL( CStifItemParser& aItem );
    
    /**
     * TestERemoveEdwinObserverL test function for testing the 
     *     RemoveEdwinObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestERemoveEdwinObserverL( CStifItemParser& aItem );
    
    /**
     * TestESetContainerWindowL test function for testing the 
     *     SetContainerWindowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetContainerWindowL( CStifItemParser& aItem );
    
    /**
     * TestESetDocumentContentL test function for testing the 
     *     SetDocumentContentL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetDocumentContentL( CStifItemParser& aItem );
    
    /**
     * TestEOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestEFocusChangedL test function for testing the 
     *     FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEFocusChangedL( CStifItemParser& aItem );
    
    /**
     * TestEActivateL test function for testing the 
     *     ActivateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEActivateL( CStifItemParser& aItem );
    
    /**
     * TestEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestEMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMinimumSizeL( CStifItemParser& aItem );
    
    /**
     * TestEDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEDrawL( CStifItemParser& aItem );
    
    /**
     * TestESetDimmedL test function for testing the 
     *     SetDimmed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetDimmedL( CStifItemParser& aItem );
    
    /**
     * TestESetContainerWindowPL test function for testing the 
     *     SetContainerWindowL function with parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetContainerWindowPL( CStifItemParser& aItem );
    
    /**
     * TestEGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEGetColorUseListL( CStifItemParser& aItem );
    
    /**
     * TestEHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestEInputCapabilitiesL test function for testing the 
     *     InputCapabilities function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEInputCapabilitiesL( CStifItemParser& aItem );
    
    /**
     * TestESetInputCapabilitiesL test function for testing the 
     *     SetInputCapabilitiesL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetInputCapabilitiesL( CStifItemParser& aItem );
    
    /**
     * TestEWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEWriteInternalStateL( CStifItemParser& aItem );
    
    /**
     * TestEHandleScrollEventL test function for testing the 
     *     HandleScrollEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHandleScrollEventL( CStifItemParser& aItem );
    
    /**
     * TestEOnReformatL test function for testing the 
     *     OnReformatL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEOnReformatL( CStifItemParser& aItem );
    
    /**
     * TestETextLengthL test function for testing the 
     *     TextLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestETextLengthL( CStifItemParser& aItem );
    
    /**
     * TestECursorPosL test function for testing the 
     *     CursorPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECursorPosL( CStifItemParser& aItem );
    
    /**
     * TestESelectionLengthL test function for testing the 
     *     SelectionLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESelectionLengthL( CStifItemParser& aItem );
    
    /**
     * TestESelectionL test function for testing the 
     *     Selection function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESelectionL( CStifItemParser& aItem );
    
    /**
     * TestEClearSelectionL test function for testing the 
     *     ClearSelectionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEClearSelectionL( CStifItemParser& aItem );
    
    /**
     * TestESetSelectionL test function for testing the 
     *     SetSelectionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetSelectionL( CStifItemParser& aItem );
    
    /**
     * TestESetCursorPosL test function for testing the 
     *     SetCursorPosL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetCursorPosL( CStifItemParser& aItem );
    
    /**
     * TestESelectAllL test function for testing the 
     *     SelectAllL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESelectAllL( CStifItemParser& aItem );
    
    /**
     * TestECalculateWidthL test function for testing the 
     *     CalculateWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECalculateWidthL( CStifItemParser& aItem );
    
    /**
     * TestEGetTextL test function for testing the 
     *     GetText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEGetTextL( CStifItemParser& aItem );
    
    /**
     * TestEGetTextInHBufL test function for testing the 
     *     GetTextInHBufL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEGetTextInHBufL( CStifItemParser& aItem );
    
    /**
     * TestESetTextL test function for testing the 
     *     SetTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetTextL( CStifItemParser& aItem );
    
    /**
     * TestEClipboardL test function for testing the 
     *     ClipboardL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEClipboardL( CStifItemParser& aItem );
    
    /**
     * TestEInsertFieldL test function for testing the 
     *     InsertFieldL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEInsertFieldL( CStifItemParser& aItem );
    
    /**
     * TestEUpdateAllFieldsL test function for testing the 
     *     UpdateAllFieldsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEUpdateAllFieldsL( CStifItemParser& aItem );
    
    /**
     * TestEUpdateCurrentFieldL test function for testing the 
     *     UpdateCurrentFieldL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEUpdateCurrentFieldL( CStifItemParser& aItem );
    
    /**
     * TestECountWordsL test function for testing the 
     *     CountWords function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECountWordsL( CStifItemParser& aItem );
    
    /**
     * TestEInsertFromTextFileL test function for testing the 
     *     InsertFromTextFileL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEInsertFromTextFileL( CStifItemParser& aItem );
    
    /**
     * TestEIdleL test function for testing the 
     *     IdleL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEIdleL( CStifItemParser& aItem );
    
    /**
     * TestETextL test function for testing the 
     *     Text function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestETextL( CStifItemParser& aItem );
    
    /**
     * TestECancelFepTransactionL test function for testing the 
     *     CancelFepTransaction function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECancelFepTransactionL( CStifItemParser& aItem );
    
    /**
     * TestEHandleTextChangedL test function for testing the 
     *     HandleTextChangedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHandleTextChangedL( CStifItemParser& aItem );
    
    /**
     * TestELayoutWidthL test function for testing the 
     *     LayoutWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestELayoutWidthL( CStifItemParser& aItem );
    
    /**
     * TestENotifyNewDocumentL test function for testing the 
     *     NotifyNewDocumentL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestENotifyNewDocumentL( CStifItemParser& aItem );
    
    /**
     * TestENotifyNewFormatL test function for testing the 
     *     NotifyNewFormatL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestENotifyNewFormatL( CStifItemParser& aItem );
    
    /**
     * TestEFindL test function for testing the 
     *     FindL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEFindL( CStifItemParser& aItem );
    
    /**
     * TestEFindTextL test function for testing the 
     *     FindTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEFindTextL( CStifItemParser& aItem );
    
    /**
     * TestEReplaceL test function for testing the 
     *     ReplaceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEReplaceL( CStifItemParser& aItem );
    
    /**
     * TestEReplaceAllL test function for testing the 
     *     ReplaceAllL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEReplaceAllL( CStifItemParser& aItem );
    
    /**
     * TestEGetFindTextL test function for testing the 
     *     GetFindText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEGetFindTextL( CStifItemParser& aItem );
    
    /**
     * TestEUpdateScrollBarsL test function for testing the 
     *     UpdateScrollBarsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEUpdateScrollBarsL( CStifItemParser& aItem );
    
    /**
     * TestECreateScrollBarFrameL test function for testing the 
     *     CreateScrollBarFrameL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECreateScrollBarFrameL( CStifItemParser& aItem );
    
    /**
     * TestECreatePreAllocatedScrollBarFrameL test function for testing the 
     *     CreatePreAllocatedScrollBarFrameL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECreatePreAllocatedScrollBarFrameL( CStifItemParser& aItem );
    
    /**
     * TestEScrollBarFrameL test function for testing the 
     *     ScrollBarFrame function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEScrollBarFrameL( CStifItemParser& aItem );
    
    /**
     * TestESetWordWrapL test function for testing the 
     *     SetWordWrapL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetWordWrapL( CStifItemParser& aItem );
    
    /**
     * TestELineCursorWidthL test function for testing the 
     *     LineCursorWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestELineCursorWidthL( CStifItemParser& aItem );
    
    /**
     * TestESetZoomFactorL test function for testing the 
     *     SetZoomFactorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetZoomFactorL( CStifItemParser& aItem );
    
    /**
     * TestESetBackgroundColorL test function for testing the 
     *     SetBackgroundColorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetBackgroundColorL( CStifItemParser& aItem );
    
    /**
     * TestESetWysiwygModeOnL test function for testing the 
     *     SetWysiwygModeOn function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetWysiwygModeOnL( CStifItemParser& aItem );
    
    /**
     * TestESetWysiwygModeOffL test function for testing the 
     *     SetWysiwygModeOff function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetWysiwygModeOffL( CStifItemParser& aItem );
    
    /**
     * TestEUpdateLayoutWidthL test function for testing the 
     *     UpdateLayoutWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEUpdateLayoutWidthL( CStifItemParser& aItem );
    
    /**
     * TestESendDataOverIrL test function for testing the 
     *     SendDataOverIrL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESendDataOverIrL( CStifItemParser& aItem );
    
    /**
     * TestEReceiveDataOverIrL test function for testing the 
     *     ReceiveDataOverIrL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEReceiveDataOverIrL( CStifItemParser& aItem );
    
    /**
     * TestESetAmountToFormatL test function for testing the 
     *     SetAmountToFormatL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAmountToFormatL( CStifItemParser& aItem );
    
    /**
     * TestESetAmountToFormatPL test function for testing the 
     *     SetAmountToFormatL function with two parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAmountToFormatPL( CStifItemParser& aItem );
    
    /**
     * TestESetPasteFromIrStoreL test function for testing the 
     *     SetPasteFromIrStore function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetPasteFromIrStoreL( CStifItemParser& aItem );
    
    /**
     * TestEPasteFromStoreL test function for testing the 
     *     PasteFromStoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEPasteFromStoreL( CStifItemParser& aItem );
    
    /**
     * TestECopyToStoreL test function for testing the 
     *     CopyToStoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECopyToStoreL( CStifItemParser& aItem );
    
    /**
     * TestESetBorderViewMarginsL test function for testing the 
     *     SetBorderViewMargins function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetBorderViewMarginsL( CStifItemParser& aItem );
    
    /**
     * TestEForceScrollBarUpdateL test function for testing the 
     *     ForceScrollBarUpdateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEForceScrollBarUpdateL( CStifItemParser& aItem );
    
    /**
     * TestESetDocumentOwnershipL test function for testing the 
     *     SetDocumentOwnership function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetDocumentOwnershipL( CStifItemParser& aItem );
    
    /**
     * TestESetTextLimitL test function for testing the 
     *     SetTextLimit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetTextLimitL( CStifItemParser& aItem );
    
    /**
     * TestERunCharMapDialogL test function for testing the 
     *     RunCharMapDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestERunCharMapDialogL( CStifItemParser& aItem );
    
    /**
     * TestEMarginsL test function for testing the 
     *     Margins function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMarginsL( CStifItemParser& aItem );
    
    /**
     * TestEUpperFullFormattingLengthL test function for testing the 
     *     UpperFullFormattingLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEUpperFullFormattingLengthL( CStifItemParser& aItem );
    
    /**
     * TestELowerPartialFormattingLengthL test function for testing the 
     *     LowerPartialFormattingLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestELowerPartialFormattingLengthL( CStifItemParser& aItem );
    
    /**
     * TestESetReadOnlyL test function for testing the 
     *     SetReadOnly function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetReadOnlyL( CStifItemParser& aItem );
    
    /**
     * TestEIsReadOnlyL test function for testing the 
     *     IsReadOnly function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEIsReadOnlyL( CStifItemParser& aItem );
    
    /**
     * TestECheckNotReadOnlyL test function for testing the 
     *     CheckNotReadOnlyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECheckNotReadOnlyL( CStifItemParser& aItem );
    
    /**
     * TestESetAllowPicturesL test function for testing the 
     *     SetAllowPictures function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAllowPicturesL( CStifItemParser& aItem );
    
    /**
     * TestECheckRemovePicturesL test function for testing the 
     *     CheckRemovePictures function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECheckRemovePicturesL( CStifItemParser& aItem );
    
    /**
     * TestESetRightWrapGutterL test function for testing the 
     *     SetRightWrapGutter function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetRightWrapGutterL( CStifItemParser& aItem );
    
    /**
     * TestEUndoL test function for testing the 
     *     UndoL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEUndoL( CStifItemParser& aItem );
    
    /**
     * TestEClearUndoL test function for testing the 
     *     ClearUndo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEClearUndoL( CStifItemParser& aItem );
    
    /**
     * TestESetAllowUndoL test function for testing the 
     *     SetAllowUndo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAllowUndoL( CStifItemParser& aItem );
    
    /**
     * TestESupportsUndoL test function for testing the 
     *     SupportsUndo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESupportsUndoL( CStifItemParser& aItem );
    
    /**
     * TestECanUndoL test function for testing the 
     *     CanUndo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECanUndoL( CStifItemParser& aItem );
    
    /**
     * TestESetWordDelimitersL test function for testing the 
     *     SetWordDelimiters function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetWordDelimitersL( CStifItemParser& aItem );
    
    /**
     * TestEGetWordInfoL test function for testing the 
     *     GetWordInfo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEGetWordInfoL( CStifItemParser& aItem );
    
    /**
     * TestEMoveCursorL test function for testing the 
     *     MoveCursorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMoveCursorL( CStifItemParser& aItem );
    
    /**
     * TestEMoveDisplayL test function for testing the 
     *     MoveDisplayL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMoveDisplayL( CStifItemParser& aItem );
    
    /**
     * TestECheckValidityOfCharsL test function for testing the 
     *     CheckValidityOfChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECheckValidityOfCharsL( CStifItemParser& aItem );
    
    /**
     * TestESetOnlyASCIICharsL test function for testing the 
     *     SetOnlyASCIIChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetOnlyASCIICharsL( CStifItemParser& aItem );
    
    /**
     * TestEOnlyASCIICharsL test function for testing the 
     *     OnlyASCIIChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEOnlyASCIICharsL( CStifItemParser& aItem );
    
    /**
     * TestEAvgLinesInViewRectL test function for testing the 
     *     AvgLinesInViewRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEAvgLinesInViewRectL( CStifItemParser& aItem );
    
    /**
     * TestEAvgCharsPerLineL test function for testing the 
     *     AvgCharsPerLine function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEAvgCharsPerLineL( CStifItemParser& aItem );
    
    /**
     * TestESetAvgLinesInViewRectL test function for testing the 
     *     SetAvgLinesInViewRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAvgLinesInViewRectL( CStifItemParser& aItem );
    
    /**
     * TestESetAvgCharsPerLineL test function for testing the 
     *     SetAvgCharsPerLine function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAvgCharsPerLineL( CStifItemParser& aItem );
    
    /**
     * TestESetEdwinSizeObserverL test function for testing the 
     *     SetEdwinSizeObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetEdwinSizeObserverL( CStifItemParser& aItem );
    
    /**
     * TestEMinimumHeightL test function for testing the 
     *     MinimumHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMinimumHeightL( CStifItemParser& aItem );
    
    /**
     * TestEMaximumHeightL test function for testing the 
     *     MaximumHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMaximumHeightL( CStifItemParser& aItem );
    
    /**
     * TestESetMinimumHeightL test function for testing the 
     *     SetMinimumHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetMinimumHeightL( CStifItemParser& aItem );
    
    /**
     * TestESetMaximumHeightL test function for testing the 
     *     SetMaximumHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetMaximumHeightL( CStifItemParser& aItem );
    
    /**
     * TestEInsertDeleteCharsL test function for testing the 
     *     InsertDeleteCharsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEInsertDeleteCharsL( CStifItemParser& aItem );
    
    /**
     * TestESetNonPrintingCharsVisibilityL test function for testing the 
     *     SetNonPrintingCharsVisibility function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetNonPrintingCharsVisibilityL( CStifItemParser& aItem );
    
    /**
     * TestENonPrintingCharsVisibilityL test function for testing the 
     *     NonPrintingCharsVisibility function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestENonPrintingCharsVisibilityL( CStifItemParser& aItem );
    
    /**
     * TestESetAvkonWrapL test function for testing the 
     *     SetAvkonWrap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAvkonWrapL( CStifItemParser& aItem );
    
    /**
     * TestESetAknEditorCaseL test function for testing the 
     *     SetAknEditorCase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAknEditorCaseL( CStifItemParser& aItem );
    
    /**
     * TestESetAknEditorPermittedCaseModesL test function for testing the 
     *     SetAknEditorPermittedCaseModes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAknEditorPermittedCaseModesL( CStifItemParser& aItem );
    
    /**
     * TestESetAknEditorNumericKeymapL test function for testing the 
     *     SetAknEditorNumericKeymap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAknEditorNumericKeymapL( CStifItemParser& aItem );
    
    /**
     * TestESetAknEditorInputModeL test function for testing the 
     *     SetAknEditorInputMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAknEditorInputModeL( CStifItemParser& aItem );
    
    /**
     * TestESetAknEditorAllowedInputModesL test function for testing the 
     *     SetAknEditorAllowedInputModes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAknEditorAllowedInputModesL( CStifItemParser& aItem );
    
    /**
     * TestESetAknEditorSpecialCharacterTableL test function for testing the 
     *     SetAknEditorSpecialCharacterTable function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAknEditorSpecialCharacterTableL( CStifItemParser& aItem );
    
    /**
     * TestESetAknEditorFlagsL test function for testing the 
     *     SetAknEditorFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAknEditorFlagsL( CStifItemParser& aItem );
    
    /**
     * TestEEnableCcpuSupportL test function for testing the 
     *     EnableCcpuSupportL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEEnableCcpuSupportL( CStifItemParser& aItem );
    
    /**
     * TestESetAknEditorCurrentInputModeL test function for testing the 
     *     SetAknEditorCurrentInputMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAknEditorCurrentInputModeL( CStifItemParser& aItem );
    
    /**
     * TestEAknEditorCurrentInputModeL test function for testing the 
     *     AknEditorCurrentInputMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEAknEditorCurrentInputModeL( CStifItemParser& aItem );
    
    /**
     * TestESetAknEditorCurrentCaseL test function for testing the 
     *     SetAknEditorCurrentCase function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAknEditorCurrentCaseL( CStifItemParser& aItem );
    
    /**
     * TestESetAknEditorLocalLanguageL test function for testing the 
     *     SetAknEditorLocalLanguage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAknEditorLocalLanguageL( CStifItemParser& aItem );
    
    /**
     * TestENotifyEditorStateObserverOfStateChangeL test function for testing the 
     *     NotifyEditorStateObserverOfStateChangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestENotifyEditorStateObserverOfStateChangeL( CStifItemParser& aItem );
    
    /**
     * TestESetSuppressBackgroundDrawingL test function for testing the 
     *     SetSuppressBackgroundDrawing function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetSuppressBackgroundDrawingL( CStifItemParser& aItem );
    
    /**
     * TestEIsBackgroundDrawingSuppressedL test function for testing the 
     *     IsBackgroundDrawingSuppressed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEIsBackgroundDrawingSuppressedL( CStifItemParser& aItem );
    
    /**
     * TestESetTextLinesRectL test function for testing the 
     *     SetTextLinesRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetTextLinesRectL( CStifItemParser& aItem );
    
    /**
     * TestESetScrollRectL test function for testing the 
     *     SetScrollRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetScrollRectL( CStifItemParser& aItem );
    
    /**
     * TestEGetTextLinesRectL test function for testing the 
     *     GetTextLinesRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEGetTextLinesRectL( CStifItemParser& aItem );
    
    /**
     * TestESetCursorVisibleL test function for testing the 
     *     SetCursorVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetCursorVisibleL( CStifItemParser& aItem );
    
    /**
     * TestESetMaximumHeightInLinesL test function for testing the 
     *     SetMaximumHeightInLines function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetMaximumHeightInLinesL( CStifItemParser& aItem );
    
    /**
     * TestEMaximumHeightInLinesL test function for testing the 
     *     MaximumHeightInLines function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMaximumHeightInLinesL( CStifItemParser& aItem );
    
    /**
     * TestECcpuIsFocusedL test function for testing the 
     *     CcpuIsFocused function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECcpuIsFocusedL( CStifItemParser& aItem );
    
    /**
     * TestECcpuCanCutL test function for testing the 
     *     CcpuCanCut function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECcpuCanCutL( CStifItemParser& aItem );
    
    /**
     * TestECcpuCutL test function for testing the 
     *     CcpuCutL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECcpuCutL( CStifItemParser& aItem );
    
    /**
     * TestECcpuCanCopyL test function for testing the 
     *     CcpuCanCopy function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECcpuCanCopyL( CStifItemParser& aItem );
    
    /**
     * TestECcpuCopyL test function for testing the 
     *     CcpuCopyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECcpuCopyL( CStifItemParser& aItem );
    
    /**
     * TestECcpuCanPasteL test function for testing the 
     *     CcpuCanPaste function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECcpuCanPasteL( CStifItemParser& aItem );
    
    /**
     * TestECcpuPasteL test function for testing the 
     *     CcpuPasteL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECcpuPasteL( CStifItemParser& aItem );
    
    /**
     * TestECcpuCanUndoL test function for testing the 
     *     CcpuCanUndo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECcpuCanUndoL( CStifItemParser& aItem );
    
    /**
     * TestECcpuUndoL test function for testing the 
     *     CcpuUndoL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECcpuUndoL( CStifItemParser& aItem );
    
    /**
     * TestEAknEdwinFlagsL test function for testing the 
     *     AknEdwinFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEAknEdwinFlagsL( CStifItemParser& aItem );
    
    /**
     * TestECreateTextViewL test function for testing the 
     *     CreateTextViewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECreateTextViewL( CStifItemParser& aItem );
    
    /**
     * TestETextViewL test function for testing the 
     *     TextView function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestETextViewL( CStifItemParser& aItem );
    
    /**
     * TestETextLayoutL test function for testing the 
     *     TextLayout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestETextLayoutL( CStifItemParser& aItem );
    
    /**
     * TestESetUndoBufferL test function for testing the 
     *     SetUndoBufferL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetUndoBufferL( CStifItemParser& aItem );
    
    /**
     * TestESetUndoableTextL test function for testing the 
     *     SetUndoableText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetUndoableTextL( CStifItemParser& aItem );
    
    /**
     * TestESetMaxLengthL test function for testing the 
     *     SetMaxLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetMaxLengthL( CStifItemParser& aItem );
    
    /**
     * TestEMaxLengthL test function for testing the 
     *     MaxLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMaxLengthL( CStifItemParser& aItem );
    
    /**
     * TestEAddFlagToUserFlagsL test function for testing the 
     *     AddFlagToUserFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEAddFlagToUserFlagsL( CStifItemParser& aItem );
    
    /**
     * TestERemoveFlagFromUserFlagsL test function for testing the 
     *     RemoveFlagFromUserFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestERemoveFlagFromUserFlagsL( CStifItemParser& aItem );
    
    /**
     * TestEUserFlagsL test function for testing the 
     *     UserFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEUserFlagsL( CStifItemParser& aItem );
    
    /**
     * TestESetCharFormatLayerL test function for testing the 
     *     SetCharFormatLayer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetCharFormatLayerL( CStifItemParser& aItem );
    
    /**
     * TestESetParaFormatLayerL test function for testing the 
     *     SetParaFormatLayer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetParaFormatLayerL( CStifItemParser& aItem );
    
    /**
     * TestESetSkinBackgroundControlContextL test function for testing the 
     *     SetSkinBackgroundControlContextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetSkinBackgroundControlContextL( CStifItemParser& aItem );
    
    /**
     * TestESetAlignmentL test function for testing the 
     *     SetAlignment function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetAlignmentL( CStifItemParser& aItem );
    
    /**
     * TestESetPictographAnimationCallBackL test function for testing the 
     *     SetPictographAnimationCallBack function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetPictographAnimationCallBackL( CStifItemParser& aItem );
    
    /**
     * TestESetUpperFullFormattingLengthL test function for testing the 
     *     SetUpperFullFormattingLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetUpperFullFormattingLengthL( CStifItemParser& aItem );
    
    /**
     * TestESetSuppressNotifyDrawL test function for testing the 
     *     SetSuppressNotifyDraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetSuppressNotifyDrawL( CStifItemParser& aItem );
    
    /**
     * TestESetSuppressFormattingL test function for testing the 
     *     SetSuppressFormatting function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetSuppressFormattingL( CStifItemParser& aItem );
    
    /**
     * TestEEditObserverL test function for testing the 
     *     EditObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEEditObserverL( CStifItemParser& aItem );
    
    /**
     * TestETrappedDrawL test function for testing the 
     *     TrappedDraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestETrappedDrawL( CStifItemParser& aItem );
    
    /**
     * TestEDrawContentsL test function for testing the 
     *     DrawContents function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEDrawContentsL( CStifItemParser& aItem );
    
    /**
     * TestEBaseConstructL test function for testing the 
     *     BaseConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEBaseConstructL( CStifItemParser& aItem );
    
    /**
     * TestEFormatTextL test function for testing the 
     *     FormatTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEFormatTextL( CStifItemParser& aItem );
    
    /**
     * TestEDeleteHighlightL test function for testing the 
     *     DeleteHighlightL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEDeleteHighlightL( CStifItemParser& aItem );
    
    /**
     * TestEOkToDeleteSelectionL test function for testing the 
     *     OkToDeleteSelectionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEOkToDeleteSelectionL( CStifItemParser& aItem );
    
    /**
     * TestEDeleteL test function for testing the 
     *     DeleteL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEDeleteL( CStifItemParser& aItem );
    
    /**
     * TestETrappedSizeChangedL test function for testing the 
     *     TrappedSizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestETrappedSizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestEHandleSizeChangedL test function for testing the 
     *     HandleSizeChangedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHandleSizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestECancelSelectionL test function for testing the 
     *     CancelSelectionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECancelSelectionL( CStifItemParser& aItem );
    
    /**
     * TestEMoveCursorToChunkStartL test function for testing the 
     *     MoveCursorToChunkStartL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMoveCursorToChunkStartL( CStifItemParser& aItem );
    
    /**
     * TestECancelInsertCharFormatL test function for testing the 
     *     CancelInsertCharFormat function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECancelInsertCharFormatL( CStifItemParser& aItem );
    
    /**
     * TestEPlaceDataOnClipboardL test function for testing the 
     *     PlaceDataOnClipboardL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEPlaceDataOnClipboardL( CStifItemParser& aItem );
    
    /**
     * TestEReportEdwinEventL test function for testing the 
     *     ReportEdwinEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEReportEdwinEventL( CStifItemParser& aItem );
    
    /**
     * TestESetLineCursorDetailsL test function for testing the 
     *     SetLineCursorDetailsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetLineCursorDetailsL( CStifItemParser& aItem );
    
    /**
     * TestECopyDocumentContentL test function for testing the 
     *     CopyDocumentContentL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECopyDocumentContentL( CStifItemParser& aItem );
    
    /**
     * TestEDisplayFindTextNotFoundL test function for testing the 
     *     DisplayFindTextNotFound function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEDisplayFindTextNotFoundL( CStifItemParser& aItem );
    
    /**
     * TestEHandleTextPastedL test function for testing the 
     *     HandleTextPastedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHandleTextPastedL( CStifItemParser& aItem );
    
    /**
     * TestECreateCustomDrawL test function for testing the 
     *     CreateCustomDrawL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECreateCustomDrawL( CStifItemParser& aItem );
    
    /**
     * TestEReadAknResourceL test function for testing the 
     *     ReadAknResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEReadAknResourceL( CStifItemParser& aItem );
    
    /**
     * TestECreateLayoutL test function for testing the 
     *     CreateLayoutL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECreateLayoutL( CStifItemParser& aItem );
    
    /**
     * TestECreateTextAndLayoutL test function for testing the 
     *     CreateTextAndLayoutL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECreateTextAndLayoutL( CStifItemParser& aItem );
    
    /**
     * TestECheckEdwinExtensionL test function for testing the 
     *     CheckEdwinExtensionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestECheckEdwinExtensionL( CStifItemParser& aItem );
    
    /**
     * TestEEdwinExtensionL test function for testing the 
     *     EdwinExtension function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEEdwinExtensionL( CStifItemParser& aItem );
    
    /**
     * TestEMopSupplyObjectL test function for testing the 
     *     MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMopSupplyObjectL( CStifItemParser& aItem );
    
    /**
     * TestESetTextSkinColorIdL test function for testing the 
     *     SetTextSkinColorIdL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetTextSkinColorIdL( CStifItemParser& aItem );
    
    /**
     * TestESetHighlightStyleL test function for testing the 
     *     SetHighlightStyleL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestESetHighlightStyleL( CStifItemParser& aItem );
    
    /**
     * TestEEnableKineticScrollingL test function for testing the 
     * kinetic scrolling feature of CEikEdwin.
     *
     * @since S60 5.2
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEEnableKineticScrollingL( CStifItemParser& aItem );

    //EikGTED.h
/*                              class CEikGlobalTextEditor                  */
    /**
     * TestGETCEikGlobalTextEditorL test function for testing the 
     *     CEikGlobalTextEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETCEikGlobalTextEditorL( CStifItemParser& aItem ); 
    
    /**
     * TestGETCEikGlobalTextEditorPL test function for testing the 
     *     CEikGlobalTextEditor function with parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETCEikGlobalTextEditorPL( CStifItemParser& aItem );  
    
    /**
     * TestGETDeconstructorL test function for testing the 
     *     ~CAknCcpuSupport function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETDeconstructorL( CStifItemParser& aItem );  
    
    /**
     * TestGETConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETConstructL( CStifItemParser& aItem );  
    
    /**
     * TestGETSetButtonGroupL test function for testing the 
     *     SetButtonGroup function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETSetButtonGroupL( CStifItemParser& aItem );  
    
    /**
     * TestGETSetLineCursorBitmapL test function for testing the 
     *     SetLineCursorBitmapL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETSetLineCursorBitmapL( CStifItemParser& aItem );  
    
    /**
     * TestGETRunFontDialogL test function for testing the 
     *     RunFontDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETRunFontDialogL( CStifItemParser& aItem );  
    
    /**
     * TestGETRunTabsDialogL test function for testing the 
     *     RunTabsDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETRunTabsDialogL( CStifItemParser& aItem );  
    
    /**
     * TestGETRunIndentsDialogL test function for testing the 
     *     RunIndentsDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETRunIndentsDialogL( CStifItemParser& aItem );  
    
    /**
     * TestGETSetGraphicsDeviceL test function for testing the 
     *     SetGraphicsDevice function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETSetGraphicsDeviceL( CStifItemParser& aItem );  
    
    /**
     * TestGETRunFindDialogL test function for testing the 
     *     RunFindDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETRunFindDialogL( CStifItemParser& aItem );  
    
    /**
     * TestGETRunFindAgainDialogL test function for testing the 
     *     RunFindAgainDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETRunFindAgainDialogL( CStifItemParser& aItem );  
    
    /**
     * TestGETRunReplaceDialogL test function for testing the 
     *     RunReplaceDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETRunReplaceDialogL( CStifItemParser& aItem );  
    
    /**
     * TestGETInitFindL test function for testing the 
     *     InitFindL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETInitFindL( CStifItemParser& aItem );  
    
    /**
     * TestGETDoFindL test function for testing the 
     *     DoFindL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETDoFindL( CStifItemParser& aItem );  
    
    /**
     * TestGETRunParaDialogsL test function for testing the 
     *     RunParaDialogsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETRunParaDialogsL( CStifItemParser& aItem );  
    
    /**
     * TestGETRunPaginateDialogL test function for testing the 
     *     RunPaginateDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETRunPaginateDialogL( CStifItemParser& aItem );  
    
    /**
     * TestGETGlobalTextL test function for testing the 
     *     GlobalText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETGlobalTextL( CStifItemParser& aItem );  
    
    /**
     * TestGETApplyParaFormatL test function for testing the 
     *     ApplyParaFormatL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETApplyParaFormatL( CStifItemParser& aItem );  
    
    /**
     * TestGETApplyCharFormatL test function for testing the 
     *     ApplyCharFormatL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETApplyCharFormatL( CStifItemParser& aItem );  
    
    /**
     * TestGETBoldItalicUnderlineEventL test function for testing the 
     *     BoldItalicUnderlineEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETBoldItalicUnderlineEventL( CStifItemParser& aItem );  
    
    /**
     * TestGETUpdateButtonGroupL test function for testing the 
     *     UpdateButtonGroup function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETUpdateButtonGroupL( CStifItemParser& aItem );  
    
    /**
     * TestGETConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETConstructFromResourceL( CStifItemParser& aItem );  
    
    /**
     * TestGETOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETOfferKeyEventL( CStifItemParser& aItem );  
    
    /**
     * TestGETActivateL test function for testing the 
     *     ActivateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETActivateL( CStifItemParser& aItem );  
    
    /**
     * TestGETHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETHandlePointerEventL( CStifItemParser& aItem );  
    
    /**
     * TestGETLineCursorWidthL test function for testing the 
     *     LineCursorWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETLineCursorWidthL( CStifItemParser& aItem );  
    
    /**
     * TestGETBaseConstructL test function for testing the 
     *     BaseConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETBaseConstructL( CStifItemParser& aItem );  
    
    /**
     * TestGETWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGETWriteInternalStateL( CStifItemParser& aItem ); 
    
    //EikRTED.h
/*                              class CEikGlobalTextEditor                  */
    /**
     * TestRETCEikRichTextEditorL test function for testing the 
     *     CEikRichTextEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETCEikRichTextEditorL( CStifItemParser& aItem ); 
    
    /**
     * TestRETCEikRichTextEditorPL test function for testing the 
     *     CEikRichTextEditor function with parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETCEikRichTextEditorPL( CStifItemParser& aItem ); 
    
    /**
     * TestRETDeconstructorL test function for testing the 
     *     ~CEikRichTextEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETDeconstructorL( CStifItemParser& aItem ); 
    
    /**
     * TestRETConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETConstructL( CStifItemParser& aItem ); 
    
    /**
     * TestRETRichTextL test function for testing the 
     *     RichText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETRichTextL( CStifItemParser& aItem ); 
    
    /**
     * TestRETInsertObjectOPL test function for testing the 
     *     InsertObjectL function with one parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETInsertObjectOPL( CStifItemParser& aItem ); 
    
    /**
     * TestRETInsertObjectL test function for testing the 
     *     InsertObjectL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETInsertObjectL( CStifItemParser& aItem ); 
    
    /**
     * TestRETInsertObjectTPL test function for testing the 
     *     InsertObjectL function with three parameters
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETInsertObjectTPL( CStifItemParser& aItem ); 
    
    /**
     * TestRETInsertObjectWPL test function for testing the 
     *     InsertObjectL function with two parameters
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETInsertObjectWPL( CStifItemParser& aItem ); 
    
    /**
     * TestRETReEditObjectL test function for testing the 
     *     ReEditObjectL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETReEditObjectL( CStifItemParser& aItem ); 
    
    /**
     * TestRETObjectCursorPosL test function for testing the 
     *     ObjectCursorPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETObjectCursorPosL( CStifItemParser& aItem ); 
    
    /**
     * TestRETCheckForObjectL test function for testing the 
     *     CheckForObjectL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETCheckForObjectL( CStifItemParser& aItem ); 
    
    /**
     * TestRETEditPictureFormatL test function for testing the 
     *     EditPictureFormatL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETEditPictureFormatL( CStifItemParser& aItem ); 
    
    /**
     * TestRETPictureFormatChangedL test function for testing the 
     *     PictureFormatChangedL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETPictureFormatChangedL( CStifItemParser& aItem ); 
    
    /**
     * TestRETGetEmbeddedAppL test function for testing the 
     *     GetEmbeddedAppL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETGetEmbeddedAppL( CStifItemParser& aItem ); 
    
    /**
     * TestRETUpdatePictureFormatL test function for testing the 
     *     UpdatePictureFormatL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETUpdatePictureFormatL( CStifItemParser& aItem ); 
    
    /**
     * TestRETUpdatePictureFormatPL test function for testing the 
     *     UpdatePictureFormatL function with parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETUpdatePictureFormatPL( CStifItemParser& aItem ); 
    
    /**
     * TestRETSetDefaultIconicDoorSizeL test function for testing the 
     *     SetDefaultIconicDoorSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETSetDefaultIconicDoorSizeL( CStifItemParser& aItem ); 
    
    /**
     * TestRETDefaultIconicDoorSizeL test function for testing the 
     *     DefaultIconicDoorSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETDefaultIconicDoorSizeL( CStifItemParser& aItem ); 
    
    /**
     * TestRETUpdatePictureSizeL test function for testing the 
     *     UpdatePictureSizeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETUpdatePictureSizeL( CStifItemParser& aItem ); 
    
    /**
     * TestRETUpdatePictureSizePL test function for testing the 
     *     UpdatePictureSizeL function with parameters
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETUpdatePictureSizePL( CStifItemParser& aItem ); 
    
    /**
     * TestRETSetParserObserverL test function for testing the 
     *     SetParserObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETSetParserObserverL( CStifItemParser& aItem ); 
    
    /**
     * TestRETSetPhoneNumberGroupingL test function for testing the 
     *     SetPhoneNumberGrouping function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETSetPhoneNumberGroupingL( CStifItemParser& aItem ); 
    
    /**
     * TestRETOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETOfferKeyEventL( CStifItemParser& aItem ); 
    
    /**
     * TestRETHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETHandlePointerEventL( CStifItemParser& aItem ); 
    
    /**
     * TestRETConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETConstructFromResourceL( CStifItemParser& aItem ); 
    
    /**
     * TestRETActivateL test function for testing the 
     *     ActivateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETActivateL( CStifItemParser& aItem ); 
    
    /**
     * TestRETCopyDocumentContentL test function for testing the 
     *     CopyDocumentContentL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETCopyDocumentContentL( CStifItemParser& aItem ); 
    
    /**
     * TestRETWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETWriteInternalStateL( CStifItemParser& aItem ); 
    
    /**
     * TestRETEditObserverL test function for testing the 
     *     EditObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETEditObserverL( CStifItemParser& aItem ); 
    
    /**
     * TestRETRefreshParsersL test function for testing the 
     *     RefreshParsersL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestRETRefreshParsersL( CStifItemParser& aItem );
    
    //EikSECED.h
/*                              class CEikSecretEditor                       */
    /**
     * TestSECEikSecretEditorL test function for testing the 
     *     CEikSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSECEikSecretEditorL( CStifItemParser& aItem );
    
    /**
     * TestSEDeconstructorL test function for testing the 
     *     ~CEikSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestSEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestSEMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEMinimumSizeL( CStifItemParser& aItem );
    
    /**
     * TestSEOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestSEGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEGetColorUseListL( CStifItemParser& aItem );
    
    /**
     * TestSEHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestSEInputCapabilitiesL test function for testing the 
     *     InputCapabilities function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEInputCapabilitiesL( CStifItemParser& aItem );
    
    /**
     * TestSEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestSEGetTextL test function for testing the 
     *     GetText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEGetTextL( CStifItemParser& aItem );
    
    /**
     * TestSESetTextL test function for testing the 
     *     SetText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSESetTextL( CStifItemParser& aItem );
    
    /**
     * TestSEInitializeDisplayL test function for testing the 
     *     InitializeDisplay function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEInitializeDisplayL( CStifItemParser& aItem );
    
    /**
     * TestSEResetL test function for testing the 
     *     Reset function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEResetL( CStifItemParser& aItem );
    
    /**
     * TestSESetMaxLengthL test function for testing the 
     *     SetMaxLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSESetMaxLengthL( CStifItemParser& aItem );
    
    /**
     * TestSEAknSetFontL test function for testing the 
     *     AknSetFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEAknSetFontL( CStifItemParser& aItem );
    
    /**
     * TestSEAknSetAlignmentL test function for testing the 
     *     AknSetAlignment function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEAknSetAlignmentL( CStifItemParser& aItem );
    
    /**
     * TestSESetDefaultInputModeL test function for testing the 
     *     SetDefaultInputMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSESetDefaultInputModeL( CStifItemParser& aItem );
    
    /**
     * TestSEMaxLengthL test function for testing the 
     *     MaxLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEMaxLengthL( CStifItemParser& aItem );
    
    /**
     * TestSEBufferL test function for testing the 
     *     Buffer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEBufferL( CStifItemParser& aItem );
    
    /**
     * TestSERevealSecretTextL test function for testing the 
     *     RevealSecretText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSERevealSecretTextL( CStifItemParser& aItem );
    
    /**
     * TestSEEnableSCTL test function for testing the 
     *     EnableSCT function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEEnableSCTL( CStifItemParser& aItem );
    
    /**
     * TestSESetSkinBackgroundControlContextL test function for testing the 
     *     SetSkinBackgroundControlContextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSESetSkinBackgroundControlContextL( CStifItemParser& aItem );
    
    /**
     * TestSEAppendCharacterL test function for testing the 
     *     AppendCharacterL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEAppendCharacterL( CStifItemParser& aItem );
    
    /**
     * TestSEUpdateL test function for testing the 
     *     Update function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEUpdateL( CStifItemParser& aItem );
    
    /**
     * TestSESizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSESizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestSESetSkinTextColorL test function for testing the 
     *     SetSkinTextColorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSESetSkinTextColorL( CStifItemParser& aItem );
    
    /**
     * TestSESetFeatureL test function for testing the 
     *     SetFeature function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSESetFeatureL( CStifItemParser& aItem );
    
    /**
     * TestSEGetFeatureL test function for testing the 
     *     GetFeature function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEGetFeatureL( CStifItemParser& aItem );
    
    /**
     * TestSESupportsFeatureL test function for testing the 
     *     SupportsFeature function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSESupportsFeatureL( CStifItemParser& aItem );
    
    /**
     * TestSEFocusChangedL test function for testing the 
     *     FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSEFocusChangedL( CStifItemParser& aItem );

    //EikMFNE.h
/*                              class CEikMfneField                           */
    /**
     * TestSECEikSecretEditorL test function for testing the 
     *     CEikSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNECEikMfneFieldL( CStifItemParser& aItem );
    
    /**
     * TestSECEikSecretEditorL test function for testing the 
     *     CEikSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEIsEditableL( CStifItemParser& aItem );
    
    /**
     * TestSECEikSecretEditorL test function for testing the 
     *     CEikSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEIsValidL( CStifItemParser& aItem );
    
    /**
     * TestSECEikSecretEditorL test function for testing the 
     *     CEikSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEHighlightTypeL( CStifItemParser& aItem );
    
    /**
     * TestSECEikSecretEditorL test function for testing the 
     *     CEikSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEHandleKeyL( CStifItemParser& aItem );
    
    /**
     * TestSECEikSecretEditorL test function for testing the 
     *     CEikSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEHandleDeHighlightL( CStifItemParser& aItem );
    
    /**
     * TestSECEikSecretEditorL test function for testing the 
     *     CEikSecretEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEHandleLeftOrRightArrowL( CStifItemParser& aItem );
    
/*                              class CEikMfneSeparator                         */
    /**
     * TestMFNEDeconstructorL test function for testing the 
     *     ~CEikMfneSeparator function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestMFNERNewL test function for testing the 
     *     NewL function with resourcereader
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNERNewL( CStifItemParser& aItem );
    
    /**
     * TestMFNEHNewL test function for testing the 
     *     NewL function with HBufC
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEHNewL( CStifItemParser& aItem );
    
    /**
     * TestMFNESetTextL test function for testing the 
     *     SetText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESetTextL( CStifItemParser& aItem );
    
/*                              class CEikMfneNumber                             */
    /**
     * TestMFNENDeconstructorL test function for testing the 
     *     ~CEikMfneNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestMFNENRNewL test function for testing the 
     *     NewL function with resourcereader
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENRNewL( CStifItemParser& aItem );
    
    /**
     * TestMFNENVNewL test function for testing the 
     *     NewL function with value
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENVNewL( CStifItemParser& aItem );
    
    /**
     * TestMFNENVSetMinimumAndMaximumL test function for testing the 
     *     SetMinimumAndMaximum function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENSetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNENGetMinimumAndMaximumL test function for testing the 
     *     GetMinimumAndMaximum function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENGetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNENSetValueL test function for testing the 
     *     SetValue function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENSetValueL( CStifItemParser& aItem );
    
    /**
     * TestMFNENValueL test function for testing the 
     *     Value function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENValueL( CStifItemParser& aItem );
    
    /**
     * TestMFNENIsValidL test function for testing the 
     *     IsValid function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENIsValidL( CStifItemParser& aItem );
    
    /**
     * TestMFNENSetUninitialisedL test function for testing the 
     *     SetUninitialised function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENSetUninitialisedL( CStifItemParser& aItem );
    
    /**
     * TestMFNENIsUninitialisedL test function for testing the 
     *     IsUninitialised function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENIsUninitialisedL( CStifItemParser& aItem );
    
    /**
     * TestMFNENSetDigitTypeL test function for testing the 
     *     SetDigitType function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENSetDigitTypeL( CStifItemParser& aItem );
    
    /**
     * TestMFNENDigitTypeL test function for testing the 
     *     DigitType function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENDigitTypeL( CStifItemParser& aItem );
    
    /**
     * TestMFNENRefreshDigitTypeL test function for testing the 
     *     RefreshDigitType function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENRefreshDigitTypeL( CStifItemParser& aItem );
    
/*                              class CEikMfneNumber                             */
    /**
     * TestMFNESCDeconstructorL test function for testing the 
     *     ~CItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESCDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestMFNESCRNewL test function for testing the 
     *     NewL function with resourcereader
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESCRNewL( CStifItemParser& aItem );
    
    /**
     * TestMFNESCNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESCNewL( CStifItemParser& aItem );
    
    /**
     * TestMFNESCSetTextL test function for testing the 
     *     SetText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESCSetTextL( CStifItemParser& aItem );
    
    /**
     * TestMFNESDeconstructorL test function for testing the 
     *     ~CEikMfneSymbol function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestMFNESNewL test function for testing the 
     *     NewL function with resourcereader
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESRNewL( CStifItemParser& aItem );
    
    /**
     * TestMFNESNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESNewL( CStifItemParser& aItem );
    
    /**
     * TestMFNESAddSymbolicItemL test function for testing the 
     *     AddSymbolicItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESAddSymbolicItemL( CStifItemParser& aItem );
    
    /**
     * TestMFNESSetCurrentSymbolicItemToIdL test function for testing the 
     *     SetCurrentSymbolicItemToId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESSetCurrentSymbolicItemToIdL( CStifItemParser& aItem );
    
    /**
     * TestMFNESIdOfCurrentSymbolicItemL test function for testing the 
     *     IdOfCurrentSymbolicItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESIdOfCurrentSymbolicItemL( CStifItemParser& aItem );
    
    /**
     * TestMFNESSetUninitialisedL test function for testing the 
     *     SetUninitialised function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESSetUninitialisedL( CStifItemParser& aItem );
    
    /**
     * TestMFNESIsUninitialisedL test function for testing the 
     *     IsUninitialised function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNESIsUninitialisedL( CStifItemParser& aItem );
    

/*                              class CEikMfne                                 */
    /**
     * TestMFNEMCEikMfneL test function for testing the 
     *     CEikMfne function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMCEikMfneL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMDeconstructorL test function for testing the 
     *     ~CEikMfne function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMCreateFieldArrayL test function for testing the 
     *     CreateFieldArrayL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMCreateFieldArrayL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMAddFieldL test function for testing the 
     *     AddField function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMAddFieldL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMResetFieldArrayL test function for testing the 
     *     ResetFieldArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMResetFieldArrayL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMBorderMarginsL test function for testing the 
     *     BorderMargins function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMBorderMarginsL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMDrawNowAndLeaveWithTimeDateFormatInfoMsgL test function for testing the 
     *     DrawNowAndLeaveWithTimeDateFormatInfoMsgL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMDrawNowAndLeaveWithTimeDateFormatInfoMsgL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMFieldL test function for testing the 
     *     Field function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMFieldL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMReadTimeL test function for testing the 
     *     ReadTime function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMReadTimeL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMReadDateL test function for testing the 
     *     ReadDate function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMReadDateL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMReadTimeAndDateL test function for testing the 
     *     ReadTimeAndDate function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMReadTimeAndDateL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMReadDurationL test function for testing the 
     *     ReadDuration function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMReadDurationL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMReadTimeOffsetL test function for testing the 
     *     ReadTimeOffset function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMReadTimeOffsetL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMTConvertL test function for testing the 
     *     Convert function with TTime
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMTConvertL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMConvertL test function for testing the 
     *     Convert function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMConvertL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMCurrentFieldL test function for testing the 
     *     CurrentField function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMCurrentFieldL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMNumFieldsL test function for testing the 
     *     NumFields function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMNumFieldsL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMSetMfneAlignmentL test function for testing the 
     *     SetMfneAlignment function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMSetMfneAlignmentL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMSetUpAndDownKeysConsumedL test function for testing the 
     *     SetUpAndDownKeysConsumed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMSetUpAndDownKeysConsumedL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMSetSuppressBackgroundDrawingL test function for testing the 
     *     SetSuppressBackgroundDrawing function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMSetSuppressBackgroundDrawingL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMSetFeatureL test function for testing the 
     *     SetFeature function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMSetFeatureL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMGetFeatureL test function for testing the 
     *     GetFeature function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMGetFeatureL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMSupportsFeatureL test function for testing the 
     *     SupportsFeature function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMSupportsFeatureL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMFontL test function for testing the 
     *     Font function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMFontL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMSetFontL test function for testing the 
     *     SetFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMSetFontL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMSetSkinBackgroundControlContextL test function for testing the 
     *     SetSkinBackgroundControlContextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMSetSkinBackgroundControlContextL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMHandleMfneCommandL test function for testing the 
     *     HandleMfneCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMHandleMfneCommandL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMSetUseOverrideColorsL test function for testing the 
     *     SetUseOverrideColors function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMSetUseOverrideColorsL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMPrepareForFocusLossL test function for testing the 
     *     PrepareForFocusLossL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMPrepareForFocusLossL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMMinimumSizeL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMGetColorUseListL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMInputCapabilitiesL test function for testing the 
     *     InputCapabilities function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMInputCapabilitiesL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMMopSupplyObjectL test function for testing the 
     *     MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMMopSupplyObjectL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMSetSkinTextColorL test function for testing the 
     *     SetSkinTextColorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMSetSkinTextColorL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMFocusChangedL test function for testing the 
     *     FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMFocusChangedL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMWriteInternalStateL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMHandleInteractionL test function for testing the 
     *     HandleInteraction function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMHandleInteractionL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMFieldIsAboutToBeDeHighlightedL test function for testing the 
     *     FieldIsAboutToBeDeHighlighted function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMFieldIsAboutToBeDeHighlightedL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMMfneSizeL test function for testing the 
     *     MfneSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMMfneSizeL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMPMfneSizeL test function for testing the 
     *     MfneSize function with parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMPMfneSizeL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMSizeChangedL test function for testing the 
     *     SizeChanged function with parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMSizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestMFNEMMakeVisibleL test function for testing the 
     *     MakeVisible function with parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEMMakeVisibleL( CStifItemParser& aItem );
    
/*                              class CEikNumberEditor                        */
    /**
     * TestMFNENECEikNumberEditorL test function for testing the 
     *     CEikNumberEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENECEikNumberEditorL( CStifItemParser& aItem );
    
    /**
     * TestMFNENEConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENEConstructL( CStifItemParser& aItem );
    
    /**
     * TestMFNENESetMinimumAndMaximumL test function for testing the 
     *     SetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENESetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNENEGetMinimumAndMaximumL test function for testing the 
     *     GetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENEGetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNENESetNumberL test function for testing the 
     *     SetNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENESetNumberL( CStifItemParser& aItem );
    
    /**
     * TestMFNENENumberL test function for testing the 
     *     Number function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENENumberL( CStifItemParser& aItem );
    
    /**
     * TestMFNENEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestMFNENEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNENEHandlePointerEventL( CStifItemParser& aItem );
    
/*                              class CEikRangeEditor                         */
    /**
     * TestMFNERECEikRangeEditorL test function for testing the 
     *     CEikRangeEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNERECEikRangeEditorL( CStifItemParser& aItem );
    
    /**
     * TestMFNEREConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEREConstructL( CStifItemParser& aItem );
    
    /**
     * TestMFNERESetMinimumAndMaximumL test function for testing the 
     *     SetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNERESetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNEREGetMinimumAndMaximumL test function for testing the 
     *     GetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEREGetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNERESetRangeL test function for testing the 
     *     SetRange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNERESetRangeL( CStifItemParser& aItem );
    
    /**
     * TestMFNERERangeL test function for testing the 
     *     Range function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNERERangeL( CStifItemParser& aItem );
    
    /**
     * TestMFNEREConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEREConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestMFNEREHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEREHandlePointerEventL( CStifItemParser& aItem );
    
/*                              class CEikTimeEditor                         */
    /**
     * TestMFNETECEikTimeEditorL test function for testing the 
     *     CEikTimeEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETECEikTimeEditorL( CStifItemParser& aItem );
    
    /**
     * TestMFNETEDeconstructorL test function for testing the 
     *     ~CEikTimeEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETEDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestMFNETEConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETEConstructL( CStifItemParser& aItem );
    
    /**
     * TestMFNETESetTimeL test function for testing the 
     *     SetTime function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETESetTimeL( CStifItemParser& aItem );
    
    /**
     * TestMFNETETimeL test function for testing the 
     *     Time function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETETimeL( CStifItemParser& aItem );
    
    /**
     * TestMFNETESetUninitialisedL test function for testing the 
     *     SetUninitialised function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETESetUninitialisedL( CStifItemParser& aItem );
    
    /**
     * TestMFNETEIsUninitialisedL test function for testing the 
     *     IsUninitialised function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETEIsUninitialisedL( CStifItemParser& aItem );
    
    /**
     * TestMFNETESetMinimumAndMaximumL test function for testing the 
     *     SetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETESetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNETEGetMinimumAndMaximumL test function for testing the 
     *     GetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETEGetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNETEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestMFNETEPrepareForFocusLossL test function for testing the 
     *     PrepareForFocusLossL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETEPrepareForFocusLossL( CStifItemParser& aItem );
    
    /**
     * TestMFNETEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETEHandlePointerEventL( CStifItemParser& aItem );
    
/*                              class CEikDateEditor                         */
    /**
     * TestMFNEDECEikDateEditorL test function for testing the 
     *     CEikDateEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDECEikDateEditorL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDEDeconstructorL test function for testing the 
     *     ~CEikDateEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDEDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDEConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDEConstructL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDESetDateL test function for testing the 
     *     SetDate function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDESetDateL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDEDateL test function for testing the 
     *     Date function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDEDateL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDESetUninitialisedL test function for testing the 
     *     SetUninitialised function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDESetUninitialisedL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDEIsUninitialisedL test function for testing the 
     *     IsUninitialised function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDEIsUninitialisedL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDESetMinimumAndMaximumL test function for testing the 
     *     SetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDESetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDEGetMinimumAndMaximumL test function for testing the 
     *     GetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDEGetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDEOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDEOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDEPrepareForFocusLossL test function for testing the 
     *     PrepareForFocusLossL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDEPrepareForFocusLossL( CStifItemParser& aItem );
    
    /**
     * TestMFNEDEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNEDEHandlePointerEventL( CStifItemParser& aItem );
    
/*                          class CEikTimeAndDateEditor                    */
    /**
     * TestMFNETDECEikTimeAndDateEditorL test function for testing the 
     *     CEikTimeAndDateEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDECEikTimeAndDateEditorL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDEDeconstructorL test function for testing the 
     *     ~CEikTimeAndDateEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDEDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDEConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDEConstructL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDESetTimeAndDateL test function for testing the 
     *     SetTimeAndDate function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDESetTimeAndDateL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDETimeAndDateL test function for testing the 
     *     TimeAndDate function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDETimeAndDateL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDESetUninitialisedL test function for testing the 
     *     SetUninitialised function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDESetUninitialisedL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDEIsUninitialisedL test function for testing the 
     *     IsUninitialised function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDEIsUninitialisedL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDESetMinimumAndMaximumL test function for testing the 
     *     SetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDESetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDEGetMinimumAndMaximumL test function for testing the 
     *     GetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDEGetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDEOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDEOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDEPrepareForFocusLossL test function for testing the 
     *     PrepareForFocusLossL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDEPrepareForFocusLossL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDEHandlePointerEventL( CStifItemParser& aItem );
    
/*                          class CEikDurationEditor                        */
    /**
     * TestMFNETDUECEikDurationEditorL test function for testing the 
     *     CEikDurationEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDUECEikDurationEditorL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDUEDeconstructorL test function for testing the 
     *     ~CEikDurationEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDUEDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDUEConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDUEConstructL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDUESetMinimumAndMaximumL test function for testing the 
     *     SetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDUESetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDUEGetMinimumAndMaximumL test function for testing the 
     *     GetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDUEGetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDUESetDurationL test function for testing the 
     *     SetDuration function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDUESetDurationL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDUEDurationL test function for testing the 
     *     Duration function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDUEDurationL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDUEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDUEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDUEPrepareForFocusLossL test function for testing the 
     *     PrepareForFocusLossL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDUEPrepareForFocusLossL( CStifItemParser& aItem );
    
    /**
     * TestMFNETDUEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETDUEHandlePointerEventL( CStifItemParser& aItem );
    
/*                          class CEikTimeOffsetEditor                      */
    /**
     * TestMFNETOECEikTimeOffsetEditorL test function for testing the 
     *     CEikTimeOffsetEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETOECEikTimeOffsetEditorL( CStifItemParser& aItem );
    
    /**
     * TestMFNETOEDeconstructorL test function for testing the 
     *     ~CEikTimeOffsetEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETOEDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestMFNETOEConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETOEConstructL( CStifItemParser& aItem );
    
    /**
     * TestMFNETOESetMinimumAndMaximumL test function for testing the 
     *     SetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETOESetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNETOEGetMinimumAndMaximumL test function for testing the 
     *     GetMinimumAndMaximum function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETOEGetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
     * TestMFNETOESetTimeOffsetL test function for testing the 
     *     SetTimeOffset function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETOESetTimeOffsetL( CStifItemParser& aItem );
    
    /**
     * TestMFNETOETimeOffsetL test function for testing the 
     *     TimeOffset function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETOETimeOffsetL( CStifItemParser& aItem );
    
    /**
     * TestMFNETOEConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETOEConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestMFNETOEPrepareForFocusLossL test function for testing the 
     *     PrepareForFocusLossL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETOEPrepareForFocusLossL( CStifItemParser& aItem );
    
    /**
     * TestMFNETOEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMFNETOEHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestEikEdwinSmileyInputL test function for testing the 
     *     Simley feature of CEikEdwin
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    TInt TestEikEdwinSmileyInputL(CStifItemParser& aItem);
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /*
     * The enviroment of ui
     */
    CEikonEnv* ivEikonEnv;

    // Resource file offset
    TInt iOffset;
    };

class CMyDateTimeField : public CTextField
    {
public:
    // from CTextField
    void InternalizeL(RReadStream& aStream)
        {
        }
    TInt Value( TPtr& aValueText )
        {
        if (aValueText.Length() == 0 )
            {
            return 0;
            }
        else
            {
            return aValueText.Length();
            }
        }
    TUid Type() const
        {
        return KDateTimeFieldUid;
        }
    };
#endif      // C_TESTSDKEDITORS_H

// End of File
