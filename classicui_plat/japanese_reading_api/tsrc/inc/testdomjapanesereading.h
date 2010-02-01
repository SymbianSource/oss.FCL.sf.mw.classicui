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
* Description:  test japanese_reading_api
*
*/



#ifndef C_TESTDOMJAPANESEREADING_H
#define C_TESTDOMJAPANESEREADING_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include <aknjapanesereading.h>
#include <aknreadingconverter.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomjapanesereadingLogPath, "\\logs\\testframework\\testdomjapanesereading\\" ); 
// Log file
_LIT( KtestdomjapanesereadingLogFile, "testdomjapanesereading.txt" ); 
_LIT( KtestdomjapanesereadingLogFileWithTitle, "testdomjapanesereading_[%S].txt" );

/**
*  CTestDomJapaneseReading test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomJapaneseReading ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomJapaneseReading* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomJapaneseReading();

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
    CTestDomJapaneseReading( CTestModuleIf& aTestModuleIf );

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

private: // Test AknJapaneseReading.h
    /**
    * TestJRCreateL test function of class CAknJapaneseReading in AknJapaneseReading.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestJRCreateL( CStifItemParser& aItem );
    
    /**
    * TestJRReadingTextL test function of class CAknJapaneseReading in AknJapaneseReading.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestJRReadingTextL( CStifItemParser& aItem );
    
private: // Test AknReadingConverter.h
    /**
    * TestRCNewL test function of class CReadingConverter in AknReadingConverter.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestRCNewL( CStifItemParser& aItem );
    
    /**
    * TestRCNewCEikEdwinL test function of class CReadingConverter in AknReadingConverter.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestRCNewCEikEdwinL( CStifItemParser& aItem );
    
    /**
    * TestRCHandleCompletionOfTransactionL test function of class CReadingConverter in AknReadingConverter.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestRCHandleCompletionOfTransactionL( CStifItemParser& aItem );
    
    /**
    * TestRCSetMainEditorL test function of class CReadingConverter in AknReadingConverter.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestRCSetMainEditorL( CStifItemParser& aItem );
    
    /**
    * TestRCMainEditorL test function of class CReadingConverter in AknReadingConverter.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestRCMainEditorL( CStifItemParser& aItem );
    
    /**
    * TestRCSetReadingEditorL test function of class CReadingConverter in AknReadingConverter.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestRCSetReadingEditorL( CStifItemParser& aItem );

    /**
    * TestRCReadingEditorL test function of class CReadingConverter in AknReadingConverter.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestRCReadingEditorL( CStifItemParser& aItem );
    

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTDOMJAPANESEREADING_H

// End of File
