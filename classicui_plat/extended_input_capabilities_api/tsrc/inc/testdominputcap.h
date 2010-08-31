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
* Description:  test aknextendedinputcapabilities.h
*
*/



#ifndef C_TESTDOMINPUTCAP_H
#define C_TESTDOMINPUTCAP_H

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
_LIT( KTestDOMInputCapLogPath, "\\logs\\testframework\\testdominputcap\\" ); 
// Log file
_LIT( KTestDOMInputCapLogFile, "testdominputcap.txt" ); 
_LIT( KTestDOMInputCapLogFileWithTitle, "testdominputcap_[%S].txt" );

/**
*  CTestDOMInputCap test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMInputCap ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMInputCap* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMInputCap();

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
    CTestDOMInputCap( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // test functions of CAknExtendedInputCapabilities::CAknExtendedInputCapabilitiesProvider

    /**
    * test default construct method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestProviderDefConL( CStifItemParser& aItem );

    /**
    * test SetExtendedInputCapabilities method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestProviderSetCapL( CStifItemParser& aItem );

    /**
    * test ExtendedInputCapabilities method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestProviderInputCapL( CStifItemParser& aItem );

    /**
    * test SetMopParent method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestProviderSetMopParentL( CStifItemParser& aItem );

private: // test functions of CAknExtendedInputCapabilities

    /**
    * test NewL method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapNewL( CStifItemParser& aItem );

    /**
    * test NewLC method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapNewLCL( CStifItemParser& aItem );

    /**
    * test SetCapabilities method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapSetCapabilitiesL( CStifItemParser& aItem );

    /**
    * test Capabilities method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapCapabilitiesL( CStifItemParser& aItem );

    /**
    * test SupportsCapabilities method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapSupportsCapabilitiesL( CStifItemParser& aItem );

    /**
    * test SetMIDPConstraints method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapSetMIDPConstraintsL( CStifItemParser& aItem );

    /**
    * test MIDPConstrainst method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapMIDPConstrainstL( CStifItemParser& aItem );

    /**
    * test SetEditorType method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapSetEditorTypeL( CStifItemParser& aItem );

    /**
    * test EditorType method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapEditorTypeL( CStifItemParser& aItem );

    /**
    * test RegisterObserver method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapRegisterObserverL( CStifItemParser& aItem );

    /**
    * test UnregisterObserver method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapUnregisterObserverL( CStifItemParser& aItem );

    /**
    * test ReportEventL method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestInputCapReportEventL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTDOMINPUTCAP_H

// End of File
