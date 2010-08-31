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
* Description:  Test AknKeyLock.h
*
*/



#ifndef C_TESTSDKKEYLOCK_H
#define C_TESTSDKKEYLOCK_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>


#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkkeylockLogPath, "\\logs\\testframework\\testsdkkeylock\\" ); 
// Log file
_LIT( KtestsdkkeylockLogFile, "testsdkkeylock.txt" ); 
_LIT( KtestsdkkeylockLogFileWithTitle, "testsdkkeylock_[%S].txt" );

class CTestSDKKeyLock;

/**
*  CTestSDKKeyLock test class for STIF Test Framework TestScripter.
*/
NONSHARABLE_CLASS(CTestSDKKeyLock) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
         * Two-phased constructor.
         */
        static CTestSDKKeyLock* NewL( CTestModuleIf& aTestModuleIf );

        /**
         * Destructor.
         */
        virtual ~CTestSDKKeyLock();

    public: // Functions from base classes

        /**
         * From CScriptBase Runs a script line.
         * @since ?Series60_version
         * @param aItem Script line containing method name and parameters
         * @return Symbian OS error code
         */
        virtual TInt RunMethodL( CStifItemParser& aItem );

    private:

        /**
         * C++ default constructor.
         */
        CTestSDKKeyLock( CTestModuleIf& aTestModuleIf );

        /**
         * By default Symbian 2nd phase constructor is private.
         */
        void ConstructL();

        /**
         * Frees all resources allocated from test methods.
         * @since ?Series60_version
         */
        void Delete();
        /**
         * Method used to log version of test class
         */
        void SendTestClassVersion();
        
    private: // Test AknKeyLock.h
/*                               class RAknKeylock2                         */
        /**
         * TestKLConnectL test function for testing the 
         *     Connect function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestKLConnectL( CStifItemParser& aItem );

/*                               class RAknKeyLock                          */
        /**
         * TestKLEnableKeyLockL test function for testing the EnableKeyLock function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestKLEnableKeyLockL( CStifItemParser& aItem );
        
        /**
         * TestKLDisableKeyLockL test function for testing the DisableKeyLock function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestKLDisableKeyLockL( CStifItemParser& aItem );
        
        /**
         * TestKLIsKeyLockEnabledL test function for testing the 
         *     IsKeyLockEnabled function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestKLIsKeyLockEnabledL( CStifItemParser& aItem );
        
        /**
         * TestKLEnableSoftNotificationsL test function for testing the 
         *     EnableSoftNotifications function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestKLEnableSoftNotificationsL( CStifItemParser& aItem );
        
        /**
         * TestKLOfferKeyLockL test function for testing the OfferKeyLock function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestKLOfferKeyLockL( CStifItemParser& aItem );
        
        /**
         * TestKLCancelAllNotificationsL test function for testing the 
         *     CancelAllNotifications function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestKLCancelAllNotificationsL( CStifItemParser& aItem );
         
        /**
         * TestKLDisableWithoutNoteL test function for testing the  
         *     DisableWithoutNote function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestKLDisableWithoutNoteL( CStifItemParser& aItem );
        
        /**
         * TestKLEnableWithoutNoteL test function for testing the 
         *     EnableWithoutNote function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestKLEnableWithoutNoteL( CStifItemParser& aItem );
        
        /**
         * TestKLEnableAutoLockEmulationL test function for testing the 
         *     EnableAutoLockEmulation function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestKLEnableAutoLockEmulationL( CStifItemParser& aItem );
        
    private:    // Data

        TInt iOldScreenSaverProperty;
    };

#endif      // C_TESTSDKKEYLOCK_H

// End of File
