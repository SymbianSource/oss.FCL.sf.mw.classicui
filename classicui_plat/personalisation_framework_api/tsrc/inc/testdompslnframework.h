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
* Description:  ?Description
*
*/



#ifndef C_TESTDOMPSLNFRAMEWORK_H
#define C_TESTDOMPSLNFRAMEWORK_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <eikenv.h>

// CONSTANTS

// MACROS
//#define ?macro ?macro_def
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdompslnframeworkLogPath, "\\logs\\testframework\\testdompslnframework\\" ); 
// Log file
_LIT( KtestdompslnframeworkLogFile, "testdompslnframework.txt" ); 
_LIT( KtestdompslnframeworkLogFileWithTitle, "testdompslnframework_[%S].txt" );
//resource
_LIT( KFilePath, "C:\\resource\\testdompslnframework.rsc" );
_LIT( KFileDir, "C:\\resource\\" );

// CLASS DECLARATION
class CTestDOMPSLNFramework;
class CPslnFWAppThemeHandler;
class CPslnFWBaseContainer;
class CTestPslnFWBaseView;
class CPslnFWIconHelper;
class CPslnFWPluginHandler;

/**
*  Ctestdompslnframework test class for STIF Test Framework TestScripter.
*/
NONSHARABLE_CLASS(CTestDOMPSLNFramework) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTestDOMPSLNFramework* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTestDOMPSLNFramework();

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
        CTestDOMPSLNFramework( CTestModuleIf& aTestModuleIf );

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
        * Test methods are listed below. 
        */

private:// PslnFWBaseContainer.h
        /**
         * TestPlsnFWBCConstructL test function for 
         * testing the ConstructL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBCConstructL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBCBaseConstructL test function for 
         * testing the BaseConstructL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBCBaseConstructL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBCCPslnFWBaseContainer test function for 
         * testing the CPslnFWBaseContainer function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBCCPslnFWBaseContainerL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBCCPslnFWBaseContainer test function for 
         * testing the CPslnFWBaseContainer function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBCDelete( CStifItemParser& aItem );

        /**
         * TestPlsnFWBCSetMiddleSoftkeyObserver test function for 
         * testing the SetMiddleSoftkeyObserver function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBCSetMiddleSoftkeyObserverL( CStifItemParser& aItem );
        
private://PslnFWBaseView.h
        /**
         * TestPlsnFWBVCPslnFWBaseView test function for 
         * testing the PslnFWBaseView function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVCPslnFWBaseViewL( CStifItemParser& aItem );
         
        /**
         * TestPlsnFWBVConstructL test function for 
         * testing the ConstructL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVConstructL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVDelete test function for 
         * testing the Deconstruct function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVDelete( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVSetCurrentItem test function for 
         * testing the CurrentItem function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVSetCurrentItem( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVContainer test function for 
         * testing the Container function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVContainer( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVOpenLocalizedResourceFileL test function for 
         * testing the OpenLocalizedResourceFileL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVOpenLocalizedResourceFileL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVOpenLocalizedResourceFileLWithPathL test function for 
         * testing the OpenLocalizedResourceFileL function with path param
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVOpenLocalizedResourceFileLWithPathL( CStifItemParser& aItem );
        
        /**
         * TestPlsnFWBVSetNaviPaneDecorator test function for 
         * testing the SetNaviPaneDecorator function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVSetNaviPaneDecoratorL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVDoActivateL test function for 
         * testing the DoActivateL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVDoActivateL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVDoDeactivate test function for 
         * testing the DoDeactivate function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVDoDeactivateL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVSetTabIndex test function for 
         * testing the SetTabIndex function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVSetTabIndex( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVGetTabIndex test function for 
         * testing the GetTabIndex function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVGetTabIndex( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVSetNaviPaneL test function for testing the SetNaviPaneL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVSetNaviPaneL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVCreateNaviPaneContextL test function for 
         * testing the CreateNaviPaneContextL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVCreateNaviPaneContextL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVCreateContainerL test function for testing the CreateContainerL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVCreateContainerL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVNewContainerL test function for testing the NewContainerL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVNewContainerL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVSetNaviPaneLWithTIntL test function for testing the SetNaviPaneL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVSetNaviPaneLWithTIntL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVSetMiddleSoftKeyLabelL test function for
         * testing the SetMiddleSoftKeyLabelL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVSetMiddleSoftKeyLabelL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVHandleCommandL test function for testing the HandleCommandL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVHandleCommandL( CStifItemParser& aItem );

        /**
         * TestPlsnFWBVSetTitlePaneL test function for testing the SetTitlePaneL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWBVSetTitlePaneL( CStifItemParser& aItem );

private:
        //PslnFWIconHelper.h
        /**
         * TestPlsnFWIHNewL test function for 
         * testing the NewL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWIHNewL( CStifItemParser& aItem );

        /**
         * TestPlsnFWIHNewL test function for 
         * testing the NewL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWIHDelete( CStifItemParser& aItem );

        /**
         * TestPlsnFWIHAddIconsToSettingItemsL test function for 
         * testing the AddIconsToSettingItemsL function 
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWIHAddIconsToSettingItemsL( CStifItemParser& aItem );

        /**
         * TestPlsnFWIHGetLocalizedStringLC test function for 
         * testing the GetLocalizedStringLC function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWIHGetLocalizedStringLC( CStifItemParser& aItem );

private:
        //PslnFWPluginHandler.h
        /**
         * TestPlsnFWPHNewL test function for 
         * testing the NewL function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWPHNewL( CStifItemParser& aItem );

        /**
         * TestPlsnFWPHNewL test function for 
         * testing the NewL function with CArrayPtrFlat param
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWPHNewLWithArrayL( CStifItemParser& aItem );
        
        /**
         * TestPlsnFWPHDelete test function for 
         * testing the Deconstruct function
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWPHDelete( CStifItemParser& aItem );

        /**
         * TestPlsnFWPHLoadPluginsLWithArray test function for 
         * testing the LoadPluginsL function with CArrayPtrFlat param
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWPHLoadPluginsLWithArrayL( CStifItemParser& aItem );
        
        /**
         * TestPlsnFWPHLoadPluginsLWithId test function for 
         * testing the LoadPluginsL function with TUid param
         * @since S60 5.0
         * @param aItem never used
         * @return Symbian OS error code.
         */
        virtual TInt TestPlsnFWPHLoadPluginsLWithId( CStifItemParser& aItem );
        
        //ADD NEW METHOD DEC HERE
        //[TestMethods] - Do not remove
private:
        /**
         * Method used to log version of test class
         */
        void SendTestClassVersion();

private://data
    /**
     * for test CPslnFWAppThemeHandler
     */
    CPslnFWAppThemeHandler* iHandle;
    
    /**
     * for test CPslnFWBaseContainer
     */
    CPslnFWBaseContainer* iFWBContainer;
    
    /**
     * for test CPslnFWBaseView
     */
    CTestPslnFWBaseView* iFWBView;
    
    /**
     * for test CPslnFWIconHelper
     */
    CPslnFWIconHelper* iHelper;
    
    /**
     * for test CPslnFWPluginHandler
     */
    CPslnFWPluginHandler* iFWPHandler;
    
    /**
     * Own, for CEikonEnv::Static()
     */
    CEikonEnv* iEikonEnvPointer;

    // ScreenSaver Property
    TInt iOldScreenSaverProperty;
    
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTDOMPSLNFRAMEWORK_H

// End of File
