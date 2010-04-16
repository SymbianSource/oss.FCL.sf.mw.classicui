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
* Description:  test akntabgrp.h
*
*/



#ifndef C_TESTSDKTABGRP_H
#define C_TESTSDKTABGRP_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include <akntabgrp.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KTestSDKTabGroupLogPath, "\\logs\\testframework\\testsdktabgrp\\" ); 
// Log file
_LIT( KTestSDKTabGroupLogFile, "testsdktabgrp.txt" ); 
_LIT( KTestSDKTabGroupLogFileWithTitle, "testsdktabgrp_[%S].txt" );

/**
*  CTestSDKTabGroup test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKTabGroup) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKTabGroup* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKTabGroup();

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
    CTestSDKTabGroup( CTestModuleIf& aTestModuleIf );

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
    * test NewL function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupNewL( CStifItemParser& aItem );

    /**
    * test NewLC function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupNewLCL( CStifItemParser& aItem );

    /**
    * test AddTabL function
    * @since S60 5.0
    * @param aItem refers different param for AddTabL function:
    *  - 1 TResourceReader param
    *  - 2 TInt and TDesC params
    *  - 3 TInt,TDesC and CFbsBitmap params
    *  - 4 TInt and CFbsBitmap params.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupAddTabL( CStifItemParser& aItem );

    /**
    * test ReplaceTabL function
    * @since S60 5.0
    * @param aItem refers different param for AddTabL function:
    * - 1 TResourceReader param
    * - 2 TInt and TDesC params
    * - 3 TInt,TDesC and CFbsBitmap params
    * - 4 TInt and CFbsBitmap params.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupReplaceTabL( CStifItemParser& aItem );

    /**
    * test DeleteTabTextL function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupReplaceTabTextL( CStifItemParser& aItem );

    /**
    * test DeleteTabL function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupDeleteTabL( CStifItemParser& aItem );

    /**
    * test SetActiveTabById function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupSetActiveTabByIdL( CStifItemParser& aItem );

    /**
    * test SetActiveTabByIndex function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupSetActiveTabByIndexL( CStifItemParser& aItem );

    /**
    * test ActiveTabId function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupActiveTabIdL( CStifItemParser& aItem );

    /**
    * test ActiveTabIndex function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupActiveTabIndexL( CStifItemParser& aItem );

    /**
    * test SetTabFixedWidthL function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupSetTabFixedWidthL( CStifItemParser& aItem );

    /**
    * test DimTab function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupDimTabL( CStifItemParser& aItem );

    /**
    * test IsTabDimmed function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupIsTabDimmedL( CStifItemParser& aItem );

    /**
    * test TabIndexFromId function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupTabIndexFromIdL( CStifItemParser& aItem );

    /**
    * test TabIdFromIndex function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupTabIdFromIndexL( CStifItemParser& aItem );

    /**
    * test TabCount function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupTabCountL( CStifItemParser& aItem );

    /**
    * test SetObserver function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupSetObserverL( CStifItemParser& aItem );

    /**
    * test MinimumSize function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupMinimumSizeL( CStifItemParser& aItem );

    /**
    * test OfferKeyEventL function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupOfferKeyEventL( CStifItemParser& aItem );

    /**
    * test GetColorUseListL function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupGetColorUseListL( CStifItemParser& aItem );

    /**
    * test HandleResourceChange function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupHandleResourceChangeL( CStifItemParser& aItem );

    /**
    * test HandlePointerEventL function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupHandlePointerEventL( CStifItemParser& aItem );

    /**
    * test HandleControlEventL function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupHandleControlEventL( CStifItemParser& aItem );

    /**
    * test PrepareContext function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupPrepareContextL( CStifItemParser& aItem );

    /**
    * test HandleNaviDecoratorEventL function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupHandleNaviDecoratorEventL( CStifItemParser& aItem );

    /**
    * test SizeChanged function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupSizeChangedL( CStifItemParser& aItem );

    /**
    * test CountComponentControls function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupCountComponentControlsL( CStifItemParser& aItem );

    /**
    * test ComponentControl function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupComponentControlL( CStifItemParser& aItem );

    /**
    * test FocusChanged function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupFocusChangedL( CStifItemParser& aItem );

    /**
    * test SetTabMultiColorMode function
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTabGroupSetTabMultiColorModeL( CStifItemParser& aItem );

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

    //[TestMethods]

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // CEikonEnv::Static()
    CEikonEnv* iEikonEnvPointer;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKTABGRP_H

// End of File
