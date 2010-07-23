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
* Description:  Test eikhkeyt.h
*
*/



#ifndef C_TESTSDKEIKHKEYT_H
#define C_TESTSDKEIKHKEYT_H

/*
 *   INCLUDES
 */
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

/*
 * MACROS
 */
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

/*
 *  Logging path
 */
_LIT( KtestsdkeikhkeytLogPath, "\\logs\\testframework\\testsdkeikhkeyt\\" ); 
/*
 *  Log file
 */
_LIT( KtestsdkeikhkeytLogFile, "testsdkeikhkeyt.txt" ); 
_LIT( KtestsdkeikhkeytLogFileWithTitle, "testsdkeikhkeyt_[%S].txt" );

/*
 * Class declare
 */
class CTestSDKEIKHKEYT;

// CLASS DECLARATION
class CEikHotKeyTable;

/**
*  CTestSDKEIKHKEYT test class for STIF Test Framework TestScripter.
*/
NONSHARABLE_CLASS(CTestSDKEIKHKEYT) : public CScriptBase
    {
public:

    /**
    * Two-phased constructor.
    */
    static CTestSDKEIKHKEYT* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKEIKHKEYT();

public: // New functions


public:

    /**
    * From CScriptBase Runs a script line.
    * @param aItem Script line containing method name and parameters
    * @return Symbian OS error code
    */
    virtual TInt RunMethodL( CStifItemParser& aItem );
private:

    /**
    * C++ default constructor.
    */
    CTestSDKEIKHKEYT( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Frees all resources allocated from test methods.
    */
    void Delete();

    /**
    * Test methods are listed below. 
    */
    /**
     * TestEHKEYCEikHotKeyTable test function for testing the CEikHotKeyTable function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHKEYCEikHotKeyTableL( CStifItemParser& /*aItem*/ );
    /**
     * TestEHKEYAddItemL test function for testing the AddItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHKEYAddItemL( CStifItemParser& /*aItem*/ );
    /**
     * TestEHKEYCommandIdFromHotKey test function for testing the CommandIdFromHotKey function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHKEYCommandIdFromHotKeyL( CStifItemParser& /*aItem*/ );
    /**
     * TestEHKEYHotKeyFromCommandId test function for testing the HotKeyFromCommandId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHKEYHotKeyFromCommandIdL( CStifItemParser& /*aItem*/ );
    /**
     * TestEHKEYRemoveItem test function for testing the RemoveItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHKEYRemoveItemL( CStifItemParser& /*aItem*/ );
    /**
     * TestEHKEYConstructFromResourceL test function for testing the ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHKEYConstructFromResourceL( CStifItemParser& /*aItem*/ );
    /**
     * TestEHKEYReset test function for testing the Reset function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHKEYResetL( CStifItemParser& /*aItem*/ );
    /**
     * TestEHKEYDestructor test function for testing the ~CEikHotKeyTable function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEHKEYDestructorL( CStifItemParser& /*aItem*/ );

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;

    };

#endif

/*
 * End of File
 */
