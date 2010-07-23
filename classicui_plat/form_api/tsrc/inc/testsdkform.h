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
* Description:  test AknForm.h
*
*/



#ifndef C_TESTSDKFORM_H
#define C_TESTSDKFORM_H

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
_LIT( KtestsdkformLogPath, "\\logs\\testframework\\testsdkform\\" ); 
// Log file
_LIT( KtestsdkformLogFile, "testsdkform.txt" ); 
_LIT( KtestsdkformLogFileWithTitle, "testsdkform_[%S].txt" );

/**
*  CTestSDKForm test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKForm) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKForm* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKForm();

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
    CTestSDKForm( CTestModuleIf& aTestModuleIf );

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

private: // Test AknForm.h
/*                               class CAknForm                             */
    /**
     * TestFCAknFormL test function for testing the 
     *     CAknForm function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCAknFormL( CStifItemParser& aItem );
    
    /**
     * TestFConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFConstructL( CStifItemParser& aItem );
    
    /**
     * TestFDecontructorL test function for testing the 
     *     ~CAknForm function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFDecontructorL( CStifItemParser& aItem );
    
    /**
     * TestFDynInitMenuPaneL test function for testing the 
     *     DynInitMenuPaneL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFDynInitMenuPaneL( CStifItemParser& aItem );
    
    /**
     * TestFProcessCommandL test function for testing the 
     *     ProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFProcessCommandL( CStifItemParser& aItem );
    
    /**
     * TestFOkToExitL test function for testing the 
     *     OkToExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFOkToExitL( CStifItemParser& aItem );
    
    /**
     * TestFPrepareForFocusTransitionL test function for testing the 
     *     PrepareForFocusTransitionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPrepareForFocusTransitionL( CStifItemParser& aItem );
    
    /**
     * TestFHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestFHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestFSaveFormDataL test function for testing the 
     *     SaveFormDataL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSaveFormDataL( CStifItemParser& aItem );
    
    /**
     * TestFDoNotSaveFormDataL test function for testing the 
     *     DoNotSaveFormDataL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFDoNotSaveFormDataL( CStifItemParser& aItem );
    
    /**
     * TestFQuerySaveChangesL test function for testing the 
     *     QuerySaveChangesL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFQuerySaveChangesL( CStifItemParser& aItem );
    
    /**
     * TestFEditCurrentLabelL test function for testing the 
     *     EditCurrentLabelL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFEditCurrentLabelL( CStifItemParser& aItem );
    
    /**
     * TestFDeleteCurrentItemL test function for testing the 
     *     DeleteCurrentItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFDeleteCurrentItemL( CStifItemParser& aItem );
    
    /**
     * TestFAddItemL test function for testing the 
     *     AddItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFAddItemL( CStifItemParser& aItem );
    
    /**
     * TestFSetChangesPendingL test function for testing the 
     *     SetChangesPending function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSetChangesPendingL( CStifItemParser& aItem );
    
    /**
     * TestFPostLayoutDynInitL test function for testing the 
     *     PostLayoutDynInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFPostLayoutDynInitL( CStifItemParser& aItem );
    
    /**
     * TestFHandleControlStateChangeL test function for testing the 
     *     HandleControlStateChangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFHandleControlStateChangeL( CStifItemParser& aItem );
    
    /**
     * TestFSetInitialCurrentLineL test function for testing the 
     *     SetInitialCurrentLine function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSetInitialCurrentLineL( CStifItemParser& aItem );
    
    /**
     * TestFUnsavedEditL test function for testing the 
     *     UnsavedEdit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFUnsavedEditL( CStifItemParser& aItem );
    
    /**
     * TestFDeletingL test function for testing the 
     *     Deleting function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFDeletingL( CStifItemParser& aItem );
    
    /**
     * TestFSetFormFlagL test function for testing the 
     *     SetFormFlag function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSetFormFlagL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKFORM_H

// End of File
