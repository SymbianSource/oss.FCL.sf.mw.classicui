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
* Description:  test EIKCOLIB.H EIKCTLIB.H
*
*/



#ifndef C_TESTSDKINITIALIZATION_H
#define C_TESTSDKINITIALIZATION_H

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
_LIT( KtestsdkinitializationLogPath, "\\logs\\testframework\\testsdkinitialization\\" ); 
// Log file
_LIT( KtestsdkinitializationLogFile, "testsdkinitialization.txt" ); 
_LIT( KtestsdkinitializationLogFileWithTitle, "testsdkinitialization_[%S].txt" );

/**
*  CTestSDKInitialization test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKInitialization ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKInitialization* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKInitialization();

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
    CTestSDKInitialization( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test EIKCOLIB.H
/*                                class CEikCoCtlLibrary                     */
    /**
     * TestCCLResourceFileL test function for testing the 
     *     ResourceFile function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCLResourceFile( CStifItemParser& aItem );
    
    /**
     * TestCCLControlFactory test function for testing the 
     *     ControlFactory function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCLControlFactory( CStifItemParser& aItem );
    
    /**
     * TestCCLButtonGroupFactory test function for testing the 
     *     ButtonGroupFactory function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCLButtonGroupFactory( CStifItemParser& aItem );
    
    /**
     * TestAUFCEikAppUiFactoryL test function for testing the 
     *     CEikAppUiFactory function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAUFCEikAppUiFactoryL( CStifItemParser& aItem );
    
    /**
     * TestAUFTouchPaneL test function for testing the 
     *     TouchPane function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAUFTouchPaneL( CStifItemParser& aItem );
    
    /**
     * TestAUFPopupToolbarL test function for testing the 
     *     PopupToolbar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAUFPopupToolbarL( CStifItemParser& aItem );
    
    /**
     * TestAUFCurrentPopupToolbarL test function for testing the 
     *     CurrentPopupToolbar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAUFCurrentPopupToolbarL( CStifItemParser& aItem );
    
    /**
     * TestAUFSetViewPopupToolbarL test function for testing the 
     *     SetViewPopupToolbar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAUFSetViewPopupToolbarL( CStifItemParser& aItem );
    
    /**
     * TestAUFCurrentFixedToolbarL test function for testing the 
     *     CurrentFixedToolbar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAUFCurrentFixedToolbarL( CStifItemParser& aItem );
    
    /**
     * TestAUFSetViewFixedToolbarL test function for testing the 
     *     SetViewFixedToolbar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAUFSetViewFixedToolbarL( CStifItemParser& aItem );
    
    /**
     * TestCLResourceFile test function for testing the 
     *     ResourceFile function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLResourceFile( CStifItemParser& aItem );
    
    /**
     * TestCLControlFactory test function for testing the 
     *     ControlFactory function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLControlFactory( CStifItemParser& aItem );
    
    /**
     * TestCLInitializeL test function for testing the 
     *     InitializeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLInitializeL( CStifItemParser& aItem );
    
    /**
     * TestCLButtonGroupFactory test function for testing the 
     *     ButtonGroupFactory function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLButtonGroupFactory( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTSDKINITIALIZATION_H

// End of File
