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
* Description:  Test avkon_fonts_api
*
*/



#ifndef C_TESTDOMAKFONTS_H
#define C_TESTDOMAKFONTS_H

/*
 *   INCLUDES
 */
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

/*
 *  MACROS
 */
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

/*
 *  Logging path
 */
_LIT( KtestdomakfontsLogPath, "\\logs\\testframework\\testdomakfonts\\" ); 
/*
 *  Log file
 */
_LIT( KtestdomakfontsLogFile, "testdomakfonts.txt" ); 
_LIT( KtestdomakfontsLogFileWithTitle, "testdomakfonts_[%S].txt" );

/*
 *  FORWARD DECLARATIONS
 */
class Ctestdomakfonts;
class CLafSystemFont;
class CAknFontIdLayoutFont;

/**
*  Ctestdomakfonts test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestDOMAKFONTS) : public CScriptBase
    {
public:

    /**
    * Two-phased constructor.
    */
    static CTestDOMAKFONTS* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMAKFONTS();

public:

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
    CTestDOMAKFONTS( CTestModuleIf& aTestModuleIf );

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
     * TestSTFONTNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSTFONTNewL( CStifItemParser& /*aItem*/ );
    /**
     * TestSTFONTFontL test function for testing the Font function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSTFONTFontL( CStifItemParser& /*aItem*/ );
    /**
     * TestSTFONTUidL test function for testing the Uid function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSTFONTUidL( CStifItemParser& /*aItem*/ );
    /**
     * TestLOFONTNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLOFONTNewL( CStifItemParser& /*aItem*/ );
    /**
     * TestLOFONTFontIdL test function for testing the FontId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLOFONTFontIdL( CStifItemParser& /*aItem*/ );
    /**
     * TestLOFONTUpdateId test function for testing the UpdateId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLOFONTUpdateIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();



private:


    };

#endif

/*
 * End of File
 */
