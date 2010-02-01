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

#ifndef TESTSDKDOMMENU_H
#define TESTSDKDOMMENU_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <TestclassAssert.h>


// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KTestSDKDomMenuLogPath, "\\logs\\testframework\\TestSDKDomMenu\\" ); 
// Log file
_LIT( KTestSDKDomMenuLogFile, "TestSDKDomMenu.txt" ); 
_LIT( KTestSDKDomMenuLogFileWithTitle, "TestSDKDomMenu_[%S].txt" );


// FORWARD DECLARATIONS
class CTestDomOptionsMenu;
class TTestCollection;
class CEikMenuBar;
class CEikMenuBarTitle;

// CLASS DECLARATION

/**
*  CTestSDKDomMenu test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CTestDomOptionsMenu) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTestDomOptionsMenu* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTestDomOptionsMenu();

    public: // New functions

    public: // Functions from base classes

        /**
        * From CScriptBase Runs a script line.
        * @since ?Series60_version
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual TInt RunMethodL( CStifItemParser& aItem );

    protected:  // New functions

    protected:  // Functions from base classes

    private:

        /**
        * C++ default constructor.
        */
        CTestDomOptionsMenu( CTestModuleIf& aTestModuleIf );

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
         * Method used to log version of test class
         */
        void SendTestClassVersion();

        //ADD NEW METHOD DEC HERE
        //[TestMethods] - Do not remove
    	
    private:  // Test aknitemactionmenu.h
    	/**
    	 * TestIMRegisterCollectionL test function of class CAknItemActionMenu for in aknitemactionmenu.h
    	 * @since S60 5.0
    	 * @param aItem never used
    	 * @return Symbian OS error code.
    	*/
        virtual TInt TestIMRegisterCollectionL( CStifItemParser& aItem );
        
        /**
         * TestIMRemoveCollection test function of class CAknItemActionMenu for in aknitemactionmenu.h
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
        */
        virtual TInt TestIMRemoveCollection( CStifItemParser& aItem );
                
        /**
         * TestIMShowMenuL test function of class CAknItemActionMenu for in aknitemactionmenu.h
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
        */
        virtual TInt TestIMShowMenuL( CStifItemParser& aItem );
        
        /**
         * TestIMInitMenuL test function of class CAknItemActionMenu for in aknitemactionmenu.h
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
        */
        virtual TInt TestIMInitMenuL( CStifItemParser& aItem );


        /**
         * TestIMCollectionChangedL test function CollectionChanged of class
		 * CAknItemActionMenu in aknitemactionmenu.h.
		 *
         * @since S60 5.2
         * @param aItem never used
         * @return Symbian OS error code.
        */
        virtual TInt TestIMCollectionChangedL( CStifItemParser& aItem );
	
    public:     // Data

    protected:  // Data      

    private:    // Data
        // Own
    	TTestCollection* iCollection;
        /**
         * Pointer for test CEikMenuBar
         * own
         */
        CEikMenuBar* iEikMenuBar;
        /**
         * Pointer for test CEikMenuBarTitle
         * own
         */
        CEikMenuBarTitle* iEikMenuBarTitle;
        
        TInt iOffset;
    public:     // Friend classes
       
    protected:  // Friend classes
       
    private:    // Friend classes
   
    };

#endif      // TESTSDKDOMMENU_H

// End of File
