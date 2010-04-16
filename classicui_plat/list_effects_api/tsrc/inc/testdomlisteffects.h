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
* Description:  test aknlistloadertfx.h
*
*/



#ifndef C_TESTDOMLISTEFFECTS_H
#define C_TESTDOMLISTEFFECTS_H

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
_LIT( KtestdomlisteffectsLogPath, "\\logs\\testframework\\testdomlisteffects\\" ); 
// Log file
_LIT( KtestdomlisteffectsLogFile, "testdomlisteffects.txt" ); 
_LIT( KtestdomlisteffectsLogFileWithTitle, "testdomlisteffects_[%S].txt" );

/**
*  CTestDOMListEffects test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMListEffects ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMListEffects* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMListEffects();

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
    CTestDOMListEffects( CTestModuleIf& aTestModuleIf );

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
    * test TfxApi method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTfxApiL( CStifItemParser& aItem );

    /**
    * test TfxApiInternal method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTfxApiInternalL( CStifItemParser& aItem );

    /**
    * test CreateTfxGc method.
    * @since S60 5.0
    * @param aItem referred to different params.
    * @return Symbian OS error code.
    */
    virtual TInt TestCreateTfxGcL( CStifItemParser& aItem );

    /**
    * test RemoveTfxGc method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestRemoveTfxGcL( CStifItemParser& aItem );

    /**
    * test InvalidateAll method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestInvalidateAll( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTDOMLISTEFFECTS_H

// End of File
