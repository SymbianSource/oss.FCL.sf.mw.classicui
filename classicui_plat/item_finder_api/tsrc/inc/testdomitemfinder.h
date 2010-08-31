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
* Description:  item_finder_api
*
*/



#ifndef C_TESTDOMITEMFINDER_H
#define C_TESTDOMITEMFINDER_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <itemfinder.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomitemfinderLogPath, "\\logs\\testframework\\testdomitemfinder\\" ); 
// Log file
_LIT( KtestdomitemfinderLogFile, "testdomitemfinder.txt" ); 
_LIT( KtestdomitemfinderLogFileWithTitle, "testdomitemfinder_[%S].txt" );
/**
*  CItemFinderObserverExt test class for MItemFinderObserver.
*  @since S60 5.0
*/
class CItemFinderObserverExt : public CBase,public MItemFinderObserver
    {
    void HandleParsingComplete()
        {
        
        }
    };
/**
*  CTestDOMItemFinder test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CItemFinder;

NONSHARABLE_CLASS( CTestDOMItemFinder ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMItemFinder* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMItemFinder();

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
    CTestDOMItemFinder( CTestModuleIf& aTestModuleIf );

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
    * TestIFNewL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFNewL( CStifItemParser& aItem );
    /**
    * TestIFNextItemOrScrollL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFNextItemOrScrollL( CStifItemParser& aItem );
    /**
    * TestIFSetFindModeL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFSetFindModeL( CStifItemParser& aItem );
    /**
    * TestIFSetEditor test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFSetEditorL( CStifItemParser& aItem );
    /**
    * TestIFParseThisText test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFParseThisTextL( CStifItemParser& aItem );
    /**
    * TestIFCreateDoItTextL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFCreateDoItTextL( CStifItemParser& aItem );
    /**
    * TestIFActivateThisTextL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFActivateThisTextL( CStifItemParser& aItem );
    /**
    * TestIFReformatOnRecognise test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFReformatOnRecognise( CStifItemParser& aItem );
    /**
    * TestIFReformatOnRollover test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFReformatOnRollover( CStifItemParser& aItem );
    /**
    * TestIFGetRecogniseFormat test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFGetRecogniseFormat( CStifItemParser& aItem );
    /**
    * TestIFGetRolloverFormat test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFGetRolloverFormat( CStifItemParser& aItem );
    /**
    * TestIFConfirmCursorOverTagL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFConfirmCursorOverTagL( CStifItemParser& aItem );
    /**
    * TestIFRelease test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFRelease( CStifItemParser& aItem );
    /**
    * TestIFMParser_Reserved_2 test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFMParser_Reserved_2( CStifItemParser& aItem );
    /**
    * TestIFPositionOfNextItem test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFPositionOfNextItem( CStifItemParser& aItem );
    /**
    * TestIFResetCurrentItem test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFResetCurrentItem( CStifItemParser& aItem );
    /**
    * TestIFResolveAndSetItemTypeL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFResolveAndSetItemTypeL( CStifItemParser& aItem );
    /**
    * TestIFAddObserver test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFAddObserverL( CStifItemParser& aItem );
    /**
    * TestIFItemWasTappedL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFItemWasTappedL( CStifItemParser& aItem );
    /**
    * TestIFSetExternalLinks test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFSetExternalLinksL( CStifItemParser& aItem );
    /**
    * TestIFCurrentItemExt test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFCurrentItemExt( CStifItemParser& aItem );
    /**
    * TestIFCurrentSelection test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIFCurrentSelection( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * for test
     * Not own.
     */
    CItemFinder* iItemFinder;

    };

#endif      // C_TESTDOMITEMFINDER_H

// End of File
