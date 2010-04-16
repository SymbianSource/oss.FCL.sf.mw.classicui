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
* Description:  test media_shared_document_api
*
*/



#ifndef C_TESTDOMMEDIASHAREDDOC_H
#define C_TESTDOMMEDIASHAREDDOC_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <mediashareddocument.h>
#include <eikenv.h>
#include <eikappui.h>
#include <s32mem.h>
#include <s32std.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdommediashareddocLogPath, "\\logs\\testframework\\testdommediashareddoc\\" ); 
// Log file
_LIT( KtestdommediashareddocLogFile, "testdommediashareddoc.txt" ); 
_LIT( KtestdommediashareddocLogFileWithTitle, "testdommediashareddoc_[%S].txt" );

/**
*  CTestDomMediaSharedDoc test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomMediaSharedDoc ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomMediaSharedDoc* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomMediaSharedDoc();

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
    CTestDomMediaSharedDoc( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test MediaSharedDocument.h
    /**
    * TestMSDSetAppModeArgL test function of class CMediaSharedDocument in MediaSharedDocument.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestMSDSetAppModeArgL( CStifItemParser& aItem );
    
    /**
    * TestMSDGetAppModeArgL test function of class CMediaSharedDocument in MediaSharedDocument.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestMSDGetAppModeArgL( CStifItemParser& aItem );
    
    /**
    * TestMSDSetFileNameL test function of class CMediaSharedDocument in MediaSharedDocument.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestMSDSetFileNameL( CStifItemParser& aItem );
    
    /**
    * TestMSDGetFileNameL test function of class CMediaSharedDocument in MediaSharedDocument.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestMSDGetFileNameL( CStifItemParser& aItem );
    
    /**
    * TestMSDSetAppDataL test function of class CMediaSharedDocument in MediaSharedDocument.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestMSDSetAppDataL( CStifItemParser& aItem );
    
    /**
    * TestMSDGetAppDataL test function of class CMediaSharedDocument in MediaSharedDocument.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestMSDGetAppDataL( CStifItemParser& aItem );
    

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    };

#endif      // C_TESTDOMMEDIASHAREDDOC_H

// End of File
