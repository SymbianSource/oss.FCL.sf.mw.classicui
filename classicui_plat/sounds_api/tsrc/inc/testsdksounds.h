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
* Description:  Test sounds_api 
 *
*/


#ifndef C_TESTSDKSOUNDS_H
#define C_TESTSDKSOUNDS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include <aknsoundinfo.h>
#include <coemain.h>
#include <coeaui.h>

#include <aknsoundsystem.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdksoundsLogPath, "\\logs\\testframework\\testsdksounds\\" );
// Log file
_LIT( KtestsdksoundsLogFile, "testsdksounds.txt" );
_LIT( KtestsdksoundsLogFileWithTitle, "testsdksounds_[%S].txt" );

/**
 *  Ctestsdksounds test class for STIF Test Framework TestScripter.
 *  @since S60 5.0
 */
NONSHARABLE_CLASS(CTestSDKSounds) : public CScriptBase
    {
public: // Constructors and destructor

    /**
     * Two-phased constructor.
     */
    static CTestSDKSounds* NewL( CTestModuleIf& aTestModuleIf );

    /**
     * Destructor.
     */
    virtual ~CTestSDKSounds();

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
    CTestSDKSounds( CTestModuleIf& aTestModuleIf );

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
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test AknSoundInfo.h
    /**
     * TestSINewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSINewL( CStifItemParser& aItem );
    /*
     * TestSIInternalizeL test function for testing the NewL function with Resource
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSIInternalizeL( CStifItemParser& aItem );
    /**
     * TestSIExternalizeL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSIExternalizeL( CStifItemParser& aItem );

private: // Test AknSoundSystem.h
    /**
     * TestSSNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSNewL( CStifItemParser& aItem );
    /*
     * TestSSPushContextL test function for testing the NewL function with Resource
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSPushContextL( CStifItemParser& aItem );
    /**
     * TestSSPopContextL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSPopContextL( CStifItemParser& aItem );
    /**
     * TestSSPlaySoundWithTKeyEventL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSPlaySoundWithTKeyEventL(CStifItemParser& aItem);
    /**
     * TestSSPlaySoundWithTIntL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSPlaySoundWithTIntL(CStifItemParser& aItem);
    /**
     * TestSSAddAppSoundInfoListL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSAddAppSoundInfoListL(CStifItemParser& aItem);
    /**
     * TestSSBringToForegroundL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSBringToForegroundL(CStifItemParser& aItem);
    /**
     * TestSSStopSoundL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSStopSoundL(CStifItemParser& aItem);
    /**
     * TestSSLockContextL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSLockContextL( CStifItemParser& aItem );
    /**
     * TestSSReleaseContextL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSReleaseContextL(CStifItemParser& aItem);
    /**
     * TestSSRequestSoundInfoL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSRequestSoundInfoL(CStifItemParser& aItem);
    /**
     * TestSSTopContextL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSTopContextL(CStifItemParser& aItem);

private: // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKSOUNDS_H
// End of File
