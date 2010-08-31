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
* Description:  Test AknInputBlock.h
*
*/



#ifndef C_TESTDOMINPUTBLK_H
#define C_TESTDOMINPUTBLK_H

/*
 * INCLUDES
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
_LIT( KtestdominputblkLogPath, "\\logs\\testframework\\testdominputblk\\" ); 
/*
 *  Log file
 */
_LIT( KtestdominputblkLogFile, "testdominputblk.txt" ); 
_LIT( KtestdominputblkLogFileWithTitle, "testdominputblk_[%S].txt" );

/*
 *  FORWARD DECLARATIONS
 */
class CTestDOMINPUTBLK;
class CAknInputBlock;

/**
*  CTestDOMINPUTBLK test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestDOMINPUTBLK) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMINPUTBLK* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMINPUTBLK();

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
    CTestDOMINPUTBLK( CTestModuleIf& aTestModuleIf );

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
     * TestIPBLKNewLCL test function for testing the NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPBLKNewLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestIPBLKNewCancelHandlerLCL test function for testing the NewCancelHandlerLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPBLKNewCancelHandlerLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestIPBLKNewCancelActiveLCL test function for testing the NewCancelActiveLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPBLKNewCancelActiveLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestIPBLKNewCancelDeleteLCL test function for testing the NewCancelDeleteLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPBLKNewCancelDeleteLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestIPBLKDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPBLKDestructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestIPBLKSetCancelHandlerL test function for testing the SetCancelHandler function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPBLKSetCancelHandlerL( CStifItemParser& /*aItem*/ );
    /**
     * TestIPBLKSetCancelActiveL test function for testing the SetCancelActive function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPBLKSetCancelActiveL( CStifItemParser& /*aItem*/ );
    /**
     * TestIPBLKSetCancelDeleteL test function for testing the SetCancelDelete function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPBLKSetCancelDeleteL( CStifItemParser& /*aItem*/ );
    /**
     * TestIPBLKCancelL test function for testing the Cancel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIPBLKCancelL( CStifItemParser& aItem );
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private:  
    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    


    };

#endif      

/*
 *  End of File
 */
