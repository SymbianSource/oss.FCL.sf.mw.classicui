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
* Description:    Test aiwserviceifmenu
*
*/





#ifndef C_TESTDOMSERVICEIM_H
#define C_TESTDOMSERVICEIM_H

/*
 *   INCLUDES
 */
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

// MACROS
//#define ?macro ?macro_def
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

/*
 *  Logging path
 */
_LIT( KtestdomserviceimLogPath, "\\logs\\testframework\\testdomserviceim\\" ); 
/*
 *  Log file
 */
_LIT( KtestdomserviceimLogFile, "testdomserviceim.txt" ); 
_LIT( KtestdomserviceimLogFileWithTitle, "testdomserviceim_[%S].txt" );

// CLASS DECLARATION
class CAiwServiceIfMenu;

/**
*  CTestDOMSERVICEIM test class for STIF Test Framework TestScripter.
*/
NONSHARABLE_CLASS(CTestDOMSERVICEIM) : public CScriptBase
    {
    public: 

        /**
        * Two-phased constructor.
        */
        static CTestDOMSERVICEIM* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTestDOMSERVICEIM();

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
        CTestDOMSERVICEIM( CTestModuleIf& aTestModuleIf );

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
         * TestSERVICEIMDestructorL test function for testing the ~CAiwServiceIfMenu() function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSERVICEIMDestructorL( CStifItemParser& /*Item*/ );
        /**
         * TestSERVICEIMMenuPaneL test function for testing the MenuPane() function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSERVICEIMMenuPaneL( CStifItemParser& /*Item*/ );
        /**
         * TestSERVICEIBExtensionInterface test function for testing the ExtensionInterface function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSERVICEIMExtensionInterfaceL( CStifItemParser& /*aItem*/ );
        /**
         * Method used to log version of test class
         */
        void SendTestClassVersion();

    };

#endif

/*
 *  End of File
 */
