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
* Description:  emergency_call_support
*
*/



#ifndef C_TESTDOMEMERGENCYCALLSUPPORT_H
#define C_TESTDOMEMERGENCYCALLSUPPORT_H

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
_LIT( KtestdomemergencycallsupportLogPath, "\\logs\\testframework\\testdomemergencycallsupport\\" ); 
// Log file
_LIT( KtestdomemergencycallsupportLogFile, "testdomemergencycallsupport.txt" ); 
_LIT( KtestdomemergencycallsupportLogFileWithTitle, "testdomemergencycallsupport_[%S].txt" );

/**
*  CTestDOMEmergencyCallSupport test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CAknEcsDetector;
NONSHARABLE_CLASS( CTestDOMEmergencyCallSupport ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMEmergencyCallSupport* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMEmergencyCallSupport();

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
    CTestDOMEmergencyCallSupport( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // [TestMethods]
    /**
    * TestEDNewL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDNewL( CStifItemParser& aItem );
    /**
    * TestEDDestructor test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDDestructor( CStifItemParser& aItem );
    /**
    * TestEDHandleWsEventL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDHandleWsEventL( CStifItemParser& aItem );
    /**
    * TestEDAddChar test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDAddChar( CStifItemParser& aItem );
    /**
    * TestEDSetBuffer test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDSetBuffer( CStifItemParser& aItem );
    /**
    * TestEDReset test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDReset( CStifItemParser& aItem );
    /**
    * TestEDState test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDState( CStifItemParser& aItem );
    /**
    * TestEDCurrentMatch test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDCurrentMatch( CStifItemParser& aItem );
    /**
    * TestEDSetObserver test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDSetObserver( CStifItemParser& aItem );
    /**
    * TestEDConnectToEventSource test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDConnectToEventSource( CStifItemParser& aItem );
    /**
    * TestEDCloseEventSource test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDCloseEventSource( CStifItemParser& aItem );
    /**
    * TestEDConstructorL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDConstructorL( CStifItemParser& aItem );
    /**
    * TestEDConstructL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDConstructL( CStifItemParser& aItem );
    /**
    * TestEDReportEventL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDReportEventL( CStifItemParser& aItem );
    /**
    * TestEDSetStateL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDSetStateL( CStifItemParser& aItem );
    /**
    * TestEDOfferEmergencyCallL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestEDOfferEmergencyCallL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * for test aknesc.h
     */
    CAknEcsDetector* iEcsDetector;

    };

#endif      // C_TESTDOMEMERGENCYCALLSUPPORT_H

// End of File
