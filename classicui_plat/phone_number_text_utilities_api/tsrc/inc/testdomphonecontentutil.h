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
* Description:  Test api of phone number text utilities
*
*/



#ifndef C_TESTDOMPHONECONTENTUTIL_H
#define C_TESTDOMPHONECONTENTUTIL_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <aknphonenumbertextutils.h>
#include <eikenv.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomphonecontentutilLogPath, "\\logs\\testframework\\testdomphonecontentutil\\" ); 
// Log file
_LIT( KtestdomphonecontentutilLogFile, "testdomphonecontentutil.txt" ); 
_LIT( KtestdomphonecontentutilLogFileWithTitle, "testdomphonecontentutil_[%S].txt" );

/**
*  CTestDomPhoneContentUtil test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomPhoneContentUtil ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomPhoneContentUtil* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomPhoneContentUtil();

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
    CTestDomPhoneContentUtil( CTestModuleIf& aTestModuleIf );

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
    * TestAknPhoneNumberTextUtilsWrapToArrayL test WrapPhoneNumberToArrayL 
    * of AknPhoneNumberTextUtils in aknphonenumbertextutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknPhoneNumberTextUtilsWrapToArrayL( CStifItemParser& aItem );
    
    /**
    * TestAknPhoneNumberTextUtilsClipLineOnLeft test ClipLineOnLeft 
    * of AknPhoneNumberTextUtils in aknphonenumbertextutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknPhoneNumberTextUtilsClipLineOnLeft( CStifItemParser& aItem );
    
    /**
    * TestAknPhoneNumberTextUtilsCharsThatFitOnRight test CharsThatFitOnRight 
    * of AknPhoneNumberTextUtils in aknphonenumbertextutils.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestAknPhoneNumberTextUtilsCharsThatFitOnRight( CStifItemParser& aItem );
    
    
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    };

#endif      // C_TESTDOMPHONECONTENTUTIL_H

// End of File
