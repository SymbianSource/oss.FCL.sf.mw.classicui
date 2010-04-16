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
* Description:  test functions in extended_initialization_api
*
*/



#ifndef C_TESTDOMEXTINIT_H
#define C_TESTDOMEXTINIT_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include <aknlib.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomextinitLogPath, "\\logs\\testframework\\testdomextinit\\" ); 
// Log file
_LIT( KtestdomextinitLogFile, "testdomextinit.txt" ); 
_LIT( KtestdomextinitLogFileWithTitle, "testdomextinit_[%S].txt" );

/**
*  Ctestdomextinit test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomExtInit ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomExtInit* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomExtInit();

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
    CTestDomExtInit( CTestModuleIf& aTestModuleIf );

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
    * TestCAknLibraryResourceFile tests ResourceFile
    * of CAknLibrary in AknLib.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLibraryResourceFile( CStifItemParser& aItem );

    /**
    * TestCAknLibraryPrivateResourceFile tests PrivateResourceFile
    * of CAknLibrary in AknLib.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLibraryPrivateResourceFile( CStifItemParser& aItem );

    /**
    * TestCAknLibraryControlFactory tests ControlFactory
    * of CAknLibrary in AknLib.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknLibraryControlFactory( CStifItemParser& aItem );


private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    };

#endif      // C_TESTDOMEXTINIT_H

// End of File
