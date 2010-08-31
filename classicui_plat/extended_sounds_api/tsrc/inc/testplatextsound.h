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
* Description: Test eikkeysound.h
*
*/


#ifndef C_TESTPLATEXTSOUND_H
#define C_TESTPLATEXTSOUND_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <avkon.hrh>
#include <mateventcompleteobserver.h>
#include <ataudioeventapi.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KTestPlatExtSoundLogPath, "\\logs\\testframework\\testplatextsound\\" ); 
// Log file
_LIT( KTestPlatExtSoundLogFile, "testplatextsound.txt" ); 
_LIT( KTestPlatExtSoundLogFileWithTitle, "testplatextsound_[%S].txt" );

/**
*  CTestPlatExtSound test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestPlatExtSound ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestPlatExtSound* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestPlatExtSound();

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
    CTestPlatExtSound( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Example test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */

    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // [TestMethods]
    /**
     * TestCATAudioEventAPINewL test NewL of CATAudioEventAPI
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCATAudioEventAPINewL( CStifItemParser& aItem );

    /**
     * TestCATAudioEventAPINewLCL test NewLC of CATAudioEventAPI
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCATAudioEventAPINewLCL( CStifItemParser& aItem );



private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * ?description_of_pointer_member
     * Not own.
     */
    //?type* ?member_name;

    };

#endif      // C_TESTPLATEXTSOUND_H

// End of File

