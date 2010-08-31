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
* Description:  test api in AknControl.h, eikalign.h, eikbctrl.h.
*
*/



#ifndef C_TESTSDKBASECONTROLS_H
#define C_TESTSDKBASECONTROLS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <akncontrol.h>
#include <eikbctrl.h>
#include <eikalign.h>
#include <gulbordr.h>


// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkbasecontrolsLogPath, "\\logs\\testframework\\testsdkbasecontrols\\" ); 
// Log file
_LIT( KtestsdkbasecontrolsLogFile, "testsdkbasecontrols.txt" ); 
_LIT( KtestsdkbasecontrolsLogFileWithTitle, "testsdkbasecontrols_[%S].txt" );

// FORWARD DECLARATIONS


/**
*  CTestSDKBaseControls test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKBaseControls) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKBaseControls* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKBaseControls();

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
    CTestSDKBaseControls( CTestModuleIf& aTestModuleIf );

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

private: // Test functions
    /**
    * TestCAknControlContructorL test constructor of CAknControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknControlContructorL( CStifItemParser& aItem );
    
    /**
    * TestCAknControlDecontructorL test deconstructor of CAknControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknControlDecontructorL( CStifItemParser& aItem );
    
    /**
    * TestCEikAlignedControlContructorL test constructor of CEikAlignedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikAlignedControlContructorL( CStifItemParser& aItem );
    
    /**
    * TestCEikAlignedControlDecontructorL test deconstructor of CEikAlignedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikAlignedControlDecontructorL( CStifItemParser& aItem );
    
    /**
    * TestCEikAlignedControlSetAllMarginsToL test SetAllMarginsTo function of CEikAlignedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikAlignedControlSetAllMarginsToL( CStifItemParser& aItem );
    
    /**
    * TestCEikAlignedControlSetAlignmentL test SetAlignment function of CEikAlignedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikAlignedControlSetAlignmentL( CStifItemParser& aItem );
    
    /**
    * TestCEikAlignedControlHandlePointerEventL test HandlePointerEventL function of CEikAlignedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikAlignedControlHandlePointerEventL( CStifItemParser& aItem );
    
    /**
    * TestCEikAlignedControlWriteInternalStateL test WriteInternalStateL function of CEikAlignedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikAlignedControlWriteInternalStateL( CStifItemParser& aItem );
    
    /**
    * TestCEikBorderedControlContructorL test constructor of CEikBorderedControl.
    * @since S60 5.0
    * @param aItem is a number
    * 1, constructor wihtout parameter.
    * 2, constructor with TGulBorder parameter.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBorderedControlContructorL( CStifItemParser& aItem );

    /**
    * TestCEikBorderedControlHasBorderL test HasBorder function of CEikBorderedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBorderedControlHasBorderL( CStifItemParser& aItem );
    
    /**
    * TestCEikBorderedControlSetAdjacentL test SetAdjacent function of CEikBorderedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBorderedControlSetAdjacentL( CStifItemParser& aItem );
    
    /**
    * TestCEikBorderedControlGetColorUseListL test GetColorUseListL function of CEikBorderedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBorderedControlGetColorUseListL( CStifItemParser& aItem );
    
    /**
    * TestCEikBorderedControlHandleResourceChangeL test HandleResourceChange function of CEikBorderedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBorderedControlHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
    * TestCEikBorderedControlHandleResourceChangeL test HandleResourceChange function of CEikBorderedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBorderedControlHandlePointerEventL( CStifItemParser& aItem );
    
    /**
    * TestCEikBorderedControlSetBorderL test SetBorder function of CEikBorderedControl.
    * @since S60 5.0
    * @param aItem is a number,
    * 1 test SetBorder(TGulBorder::TBorderType aBorderType)
    * 2 test SetBorder(TInt aBorderType)
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBorderedControlSetBorderL( CStifItemParser& aItem );
    
    /**
    * TestCEikBorderedControlBorderL test Border function of CEikBorderedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBorderedControlBorderL( CStifItemParser& aItem );
    
    /**
    * TestCEikBorderedControlBorderL test Border function of CEikBorderedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBorderedControlDrawL( CStifItemParser& aItem );
    
    /**
    * TestCEikBorderedControlBorderL test Border function of CEikBorderedControl.
    * @since S60 5.0
    * @param aItem never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCEikBorderedControlWriteInternalStateL( CStifItemParser& aItem );


    //[TestMethods]

private:    // Data

    enum TSwitchId
        {
        ECaseOne = 1,
        ECaseTwo,
        ECaseThree
        };
    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    };

#endif      // C_TESTSDKBASECONTROLS_H

// End of File
