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
* Description:    Test aiwserviceifbase.h
*
*/





#ifndef C_TESTDOMSERVICEIB_H
#define C_TESTDOMSERVICEIB_H

/*
 *   INCLUDES
 */
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>


#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

/*
 *  Logging path
 */
_LIT( KtestdomserviceibLogPath, "\\logs\\testframework\\testdomserviceib\\" ); 
/*
 *  Log file
 */
_LIT( KtestdomserviceibLogFile, "testdomserviceib.txt" ); 
_LIT( KtestdomserviceibLogFileWithTitle, "testdomserviceib_[%S].txt" );

/*
 *  FORWARD DECLARATIONS
 */
class CTestDOMSERVICEIB;
class CAiwServiceIfBase;

/**
*  CTestDOMSERVICEIB test class for STIF Test Framework TestScripter.
*/
NONSHARABLE_CLASS(CTestDOMSERVICEIB) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTestDOMSERVICEIB* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTestDOMSERVICEIB();

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
        CTestDOMSERVICEIB( CTestModuleIf& aTestModuleIf );

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
         * TestSERVICEIBDestructorL test function for testing the ~CAiwServiceIfBase() function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSERVICEIBDestructorL( CStifItemParser& /*aItem*/ );
        /**
         * TestSERVICEIBExtensionInterface test function for testing the ExtensionInterface function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestSERVICEIBExtensionInterfaceL( CStifItemParser& /*aItem*/ );
        
        /**
         * Method used to log version of test class
         */
        void SendTestClassVersion();
    };

#endif      // TESTDOMSERVICEIB_H

/*
 *  End of File
 */
