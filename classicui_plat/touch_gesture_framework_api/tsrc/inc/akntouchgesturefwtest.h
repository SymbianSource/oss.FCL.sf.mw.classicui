/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: STIF testclass declaration
*
*/

#ifndef AKNTOUCHGESTUREFWTEST_H
#define AKNTOUCHGESTUREFWTEST_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include "akntouchgesturefwtestobserver.h"
#include "akntouchgesturefwtestsubscribercontrol.h"

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KAknTouchGestureFwTestLogPath, "\\logs\\testframework\\AknTouchGestureFwTest\\" );
// Log file
_LIT( KAknTouchGestureFwTestLogFile, "AknTouchGestureFwTest.txt" );
_LIT( KAknTouchGestureFwTestLogFileWithTitle, "AknTouchGestureFwTest_[%S].txt" );

// FORWARD DECLARATIONS
class CAknTouchGestureFwTest;

// CLASS DECLARATION

/**
*  CAknTouchGestureFwTest test class for STIF Test Framework TestScripter.
*
*  @lib AknTouchGestureFwTest
*  @since S60 5.2
*/
NONSHARABLE_CLASS(CAknTouchGestureFwTest) : public CScriptBase
    {

    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CAknTouchGestureFwTest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CAknTouchGestureFwTest();

        /**
        * Performs gesture simulation test.
        *
        * @param aEvent Gesture event from test control.
        */
        void DoGestureTest( MAknTouchGestureFwEvent& aEvent );

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
        CAknTouchGestureFwTest( CTestModuleIf& aTestModuleIf );

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
        * Test methods are listed below.
        */

        /**
        * Gesture fw creation test.
        */
        virtual TInt MAknTouchGestureFwTest_CreateFwL(
                CStifItemParser& aItem );

        /**
        * Gesture fw interest setting test.
        */
        virtual TInt MAknTouchGestureFwTest_SetGestureInterestL(
                CStifItemParser& aItem );

        /**
        * Gesture fw interest setting test.
        */
        virtual TInt MAknTouchGestureFwTest_SetFeedbackForGroupsL(
                CStifItemParser& aItem );
        
        /**
        * Gesture fw interest setting test.
        */
        virtual TInt MAknTouchGestureFwTest_SetFeedbackForTypesL(
                CStifItemParser& aItem );        
        
        /**
        * Gesture fw gesture simulation test.
        */
        virtual TInt MAknTouchGestureFwTest_SimulateGesturesL(
                CStifItemParser& aItem );

        /**
         * Method used to log version of test class
         */
        void SendTestClassVersion();

        /**
         * Method used to fill gesture array.
         */
        void AddGestureL( TInt aGroup, TInt aType, TInt aAmount );

        /**
         * Reads a single pointer event data from a record.
         */
        TBool ReadPointerEvent(
                TLex8& aLex,
                TPointerEvent& aEvent,
                TInt& aPointerNumber,
                TInt& aPointerTime );

        /**
         * Reads an integer value from the given string.
         */
        TBool ReadValue( TLex8& lex, TInt& aValue );

        //ADD NEW METHOD DEC HERE
        //[TestMethods] - Do not remove

    private: // data

        /**
         * Error code for test result.
         */
        TInt iTestResult;

        /**
         * Index for gesture event test.
         */
        TInt iTestIndex;

        /**
         * Array which holds expected result codes.
         */
        RArray<TInt> iGestures;

    };

#endif      // AKNTOUCHGESTUREFWTEST_H

// End of File
