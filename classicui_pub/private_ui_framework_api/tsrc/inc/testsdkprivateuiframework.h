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
* Description:  test private_ui_framework_api
*
*/



#ifndef C_TESTSDKPRIVATEUIFRAMEWORK_H
#define C_TESTSDKPRIVATEUIFRAMEWORK_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <eikalert.h>
#include <eikbtpan.h>
#include <eikhfdlg.h>
#include <eikappui.h>
#include <eikhkeyc.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkprivateuiframeworkLogPath, "\\logs\\testframework\\testsdkprivateuiframework\\" ); 
// Log file
_LIT( KtestsdkprivateuiframeworkLogFile, "testsdkprivateuiframework.txt" ); 
_LIT( KtestsdkprivateuiframeworkLogFileWithTitle, "testsdkprivateuiframework_[%S].txt" );

/**
*  CTestSdkPrivateUiFramework test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSdkPrivateUiFramework ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSdkPrivateUiFramework* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSdkPrivateUiFramework();

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
    CTestSdkPrivateUiFramework( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();


    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test eikalert.h
    /**
    * TestEAHandlePointerEventL test function of class CEikAlert in eikalert.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestEAHandlePointerEventL( CStifItemParser& aItem );
    
private: // Test eikbtpan.h
    /**
    * TestBPCEikButtonPanelL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPCEikButtonPanelL( CStifItemParser& aItem );
    
    /**
    * TestBPConstructL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPConstructL( CStifItemParser& aItem );
    
    /**
    * TestBPAddButtonL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPAddButtonL( CStifItemParser& aItem );
    
    /**
    * TestBPAddButtonIntL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPAddButtonIntL( CStifItemParser& aItem );
    
    /**
    * TestBPSetHorizontalL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPSetHorizontalL( CStifItemParser& aItem );
    
    /**
    * TestBPButtonIdL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPButtonIdL( CStifItemParser& aItem );
    
    /**
    * TestBPButtonByIdL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPButtonByIdL( CStifItemParser& aItem );
    
    /**
    * TestBPLabeledButtonByIdL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPLabeledButtonByIdL( CStifItemParser& aItem );
    
    /**
    * TestBPMakeButtonVisibleL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPMakeButtonVisibleL( CStifItemParser& aItem );
    
    /**
    * TestBPButtonForKeyL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPButtonForKeyL( CStifItemParser& aItem );
    
    /**
    * TestBPResetMinimumSizeL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPResetMinimumSizeL( CStifItemParser& aItem );
    
    /**
    * TestBPSetMinButtonWidthL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPSetMinButtonWidthL( CStifItemParser& aItem );
    
    /**
    * TestBPSetCommandObserverL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPSetCommandObserverL( CStifItemParser& aItem );
    
    /**
    * TestBPConstructFromResourceL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestBPMinimumSizeL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPMinimumSizeL( CStifItemParser& aItem );
    
    /**
    * TestBPGetColorUseListL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPGetColorUseListL( CStifItemParser& aItem );
    
    /**
    * TestBPHandleResourceChangeL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
    * TestBPOfferKeyEventL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPOfferKeyEventL( CStifItemParser& aItem );
    
    /**
    * TestBPHandlePointerEventL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPHandlePointerEventL( CStifItemParser& aItem );
    
    /**
    * TestBPDoWriteInternalStateL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPDoWriteInternalStateL( CStifItemParser& aItem );
    
    /**
    * TestBPHandleControlEventL test function of class CEikButtonPanel in eikbtpan.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestBPHandleControlEventL( CStifItemParser& aItem );
    
    
private: // Test eikdpage.h
    /**
    * TestDPSetFormLayoutL test function of class CEikDialogPage in eikdpage.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestDPSetFormLayoutL( CStifItemParser& aItem );
    
    /**
    * TestDPFormLayoutL test function of class CEikDialogPage in eikdpage.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestDPFormLayoutL( CStifItemParser& aItem );
    
private: // Test eikhgdlg.h
    /**
    * TestDKHandlePointerEventL test function of class CEikDebugKeys in eikhgdlg.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestDKHandlePointerEventL( CStifItemParser& aItem );
    
    /**
    * TestDWHandlePointerEventL test function of class CEikDebugWin in eikhgdlg.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestDWHandlePointerEventL( CStifItemParser& aItem );
   
private: //eikhkeyc.h 
    /**
    * TestKEYWriteInternalStateLL test function of class CEikDebugWin in eikhgdlg.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestKEYWriteInternalStateLL( CStifItemParser& aItem );	
	
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKPRIVATEUIFRAMEWORK_H

// End of File


