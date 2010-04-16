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
* Description:  test akntransparentcamerasettingpage.h
*
*/



#ifndef C_TESTDOMSETPAGE_H
#define C_TESTDOMSETPAGE_H

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
_LIT( KTestDOMSetPageLogPath, "c:\\logs\\testframework\\testdomsetpage\\" ); 
// Log file
_LIT( KTestDOMSetPageLogFile, "testdomsetpage.txt" ); 
_LIT( KTestDOMSetPageLogFileWithTitle, "testdomsetpage_[%S].txt" );

/**
*  CTestDOMSetPage test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDOMSetPage ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMSetPage* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMSetPage();

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
    CTestDOMSetPage( CTestModuleIf& aTestModuleIf );

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
    * test default construct method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestDefaultConstructL( CStifItemParser& aItem );

    /**
    * test default construct method with TDesC param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestConstructWithTDesCL( CStifItemParser& aItem );

    /**
    * test ConstructL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestConstructL( CStifItemParser& aItem );

    /**
    * test ListBoxControl method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestListBoxControlL( CStifItemParser& aItem );

    /**
    * test ExecuteLD method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestExecuteLDL( CStifItemParser& aItem );

    /**
    * test HandleListBoxEventL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestHandleListBoxEventL( CStifItemParser& aItem );

    /**
    * test SetItemArrayAndSelectionL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetItemArrayAndSelectionL( CStifItemParser& aItem );

    /**
    * test ChangeBackground method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestChangeBackgroundL( CStifItemParser& aItem );

    /**
    * test SetBitmapPositionAndClipRect method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetBitmapPositionAndClipRectL( CStifItemParser& aItem );

    /**
    * test HandleResourceChange method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestHandleResourceChangeL( CStifItemParser& aItem );

    /**
    * test SetBitmapPositionAndClipRect method With TBool param.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSetBitmapPositionAndClipRectWithBoolL( CStifItemParser& aItem );

    /**
    * test UpdateSettingL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestUpdateSettingL( CStifItemParser& aItem );

    /**
    * test DynamicInitL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestDynamicInitL( CStifItemParser& aItem );

    /**
    * test SelectCurrentItemL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSelectCurrentItemL( CStifItemParser& aItem );

    /**
    * test HandleControlEventL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestHandleControlEventL( CStifItemParser& aItem );

    /**
    * test ProcessCommandL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestProcessCommandL( CStifItemParser& aItem );

    /**
    * test OfferKeyEventL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestOfferKeyEventL( CStifItemParser& aItem );

    /**
    * test WriteInternalStateL method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestWriteInternalStateL( CStifItemParser& aItem );

    /**
    * test SizeChanged method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestSizeChangedL( CStifItemParser& aItem );

    /**
    * test Draw method.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestDrawL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTDOMSETPAGE_H

// End of File
