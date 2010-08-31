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
* Description:  test akntitle.h
*
*/



#ifndef C_TESTSDKTITLEPANE_H
#define C_TESTSDKTITLEPANE_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include <akntitle.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KTestSDKTitlePaneLogPath, "\\logs\\testframework\\testsdktitlepane\\" ); 
// Log file
_LIT( KTestSDKTitlePaneLogFile, "testsdktitlepane.txt" ); 
_LIT( KTestSDKTitlePaneLogFileWithTitle, "testsdktitlepane_[%S].txt" );

/**
*  CTestSDKTitlePane test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKTitlePane ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKTitlePane* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKTitlePane();

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
    CTestSDKTitlePane( CTestModuleIf& aTestModuleIf );

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
    * test default construct function of akntitlepane class
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneDefaultConstructL( CStifItemParser& aItem );

    /**
    * test ConstructL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneConstructL( CStifItemParser& aItem );

    /**
    * test ConstructFromResourceL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneConstructFromResourceL( CStifItemParser& aItem );

    /**
    * test ConstructFromResourceL function
    * @since S60 5.0
    * @param aItem refers to different overrides of SetText method
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneSetTextL( CStifItemParser& aItem );

    /**
    * test Text function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneTextL( CStifItemParser& aItem );

    /**
    * test SetPicture function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneSetPictureL( CStifItemParser& aItem );

    /**
    * test SetPictureFromFile function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneSetPictureFromFileL( CStifItemParser& aItem );

    /**
    * test SetSmallPicture function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneSetSmallPictureL( CStifItemParser& aItem );

    /**
    * test SetFromResource function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneSetFromResourceL( CStifItemParser& aItem );

    /**
    * test SetTextToDefault function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneSetTextToDefaultL( CStifItemParser& aItem );

    /**
    * test MaxNumberOfVisibleTextRows function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneMaxNumberOfVisibleTextRowsL( CStifItemParser& aItem );

    /**
    * test SetNumberOfVisibleTextRows function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneSetNumberOfVisibleTextRowsL( CStifItemParser& aItem );

    /**
    * test PrepareContext function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePanePrepareContextL( CStifItemParser& aItem );

    /**
    * test SizeChanged function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneSizeChangedL( CStifItemParser& aItem );

    /**
    * test PositionChanged function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePanePositionChangedL( CStifItemParser& aItem );

    /**
    * test HandleResourceChange function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneHandleResourceChangeL( CStifItemParser& aItem );

    /**
    * test CountComponentControls function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneCountComponentControlsL( CStifItemParser& aItem );

    /**
    * test ComponentControl function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneComponentControlL( CStifItemParser& aItem );
    
    /**
    * test SetTitlePaneObserver function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneSetTitlePaneObserverL( CStifItemParser& aItem );

    /**
    * test HandlePointerEventL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTitlePaneHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKTITLEPANE_H

// End of File
