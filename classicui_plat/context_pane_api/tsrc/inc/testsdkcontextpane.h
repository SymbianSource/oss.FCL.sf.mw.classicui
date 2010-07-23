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



#ifndef C_TESTSDKCONTEXTPANE_H
#define C_TESTSDKCONTEXTPANE_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

class CAknContextPane;
class CTestSDKCPContainer;
class CTestSDKCPView;

// Logging path
_LIT( KtestsdkcontextpaneLogPath, "\\logs\\testframework\\testsdkcontextpane\\" ); 
// Log file
_LIT( KtestsdkcontextpaneLogFile, "testsdkcontextpane.txt" ); 
_LIT( KtestsdkcontextpaneLogFileWithTitle, "testsdkcontextpane_[%S].txt" );

/**
*  Ctestsdkcontextpane test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKContextPane) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKContextPane* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKContextPane();

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
    CTestSDKContextPane( CTestModuleIf& aTestModuleIf );

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
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private:// akncontext.h
    /**
     * TestCTXTPConstructor test function for testing the constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPConstructorL( CStifItemParser& aItem );

    /**
     * TestCTXTPDestructor test function for testing the destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPDestructor( CStifItemParser& aItem );

    /**
     * TestCTXTPConstructL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPConstructL( CStifItemParser& aItem );

    /**
     * TestCTXTPConstructFromResourceL test function for testing the ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPConstructFromResourceL( CStifItemParser& aItem );

    /**
     * TestCTXTPSetPictureUseBitmap test function for testing the SetPicture function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPSetPictureUseBitmapL( CStifItemParser& aItem );

    /**
     * TestCTXTPSetPictureUseImage test function for testing the SetPicture function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPSetPictureUseImageL( CStifItemParser& aItem );

    /**
     * TestCTXTPSetPictureFromFileL test function for testing the SetPictureFromFileL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPSetPictureFromFileL( CStifItemParser& aItem );

    /**
     * TestCTXTPSetFromResourceL test function for testing the SetFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPSetFromResourceL( CStifItemParser& aItem );

    /**
     * TestCTXTPSetPictureToDefaultL test function for testing the SetPictureToDefaultL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPSetPictureToDefaultL( CStifItemParser& aItem );

    /**
     * TestCTXTPPicture test function for testing the Picture function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPPicture( CStifItemParser& aItem );

    /**
     * TestCTXTPSwapPicture test function for testing the SwapPicture function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPSwapPictureL( CStifItemParser& aItem );

    /**
     * TestCTXTPHandlePointerEventL test function for testing the HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestCTXTPSizeChanged test function for testing the SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPSizeChangedL( CStifItemParser& aItem );

    /**
     * TestCTXTPHandleResourceChange test function for testing the HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPHandleResourceChangeL( CStifItemParser& aItem );

    /**
     * TestCTXTPCountComponentControls test function for testing the CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPCountComponentControlsL( CStifItemParser& aItem );

    /**
     * TestCTXTPComponentControl test function for testing the ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCTXTPComponentControlL( CStifItemParser& aItem );
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    /**
     * CAknContextPane
     */
    CAknContextPane* iContextPane;

    /**
     * use CEikonEnv::Static()
     */
    CCoeEnv* iEikonEnvPointer;

    /**
     * construct using container 
     */
    CTestSDKCPContainer* iContainer;

    /**
     * construct using view
     */
    CTestSDKCPView* iView;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKCONTEXTPANE_H

// End of File
