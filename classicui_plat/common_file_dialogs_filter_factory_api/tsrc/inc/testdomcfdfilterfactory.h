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
* Description:  for testing the cfd filer factory module
*
*/



#ifndef C_TESTDOMCFDFILTERFACTORY_H
#define C_TESTDOMCFDFILTERFACTORY_H

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
_LIT( KtestdomcfdfilterfactoryLogPath, "\\logs\\testframework\\testdomcfdfilterfactory\\" ); 
// Log file
_LIT( KtestdomcfdfilterfactoryLogFile, "testdomcfdfilterfactory.txt" ); 
_LIT( KtestdomcfdfilterfactoryLogFileWithTitle, "testdomcfdfilterfactory_[%S].txt" );

/**
*  Ctestdomcfdfilterfactory test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMCFDFilterFactory ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMCFDFilterFactory* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMCFDFilterFactory();

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
    CTestDOMCFDFilterFactory( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();
    
        /**
     * Turn off ScreenSaver
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    void TurnOffScreenSaver();

    /**
     * Restore ScreenSaver
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    void RestoreScreenSaver();


private: //test the AknFileFilterFactory.h
    /**
    * TestFFFCreateAttributeFilterLC test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFFFCreateAttributeFilterLC( CStifItemParser& aItem );
    
    /**
    * TestFFFCreateFilenameFilterLC test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFFFCreateFilenameFilterLC( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    // Resource file offset
    TInt iOffset;

    };

#endif      // C_TESTDOMCFDFILTERFACTORY_H

// End of File