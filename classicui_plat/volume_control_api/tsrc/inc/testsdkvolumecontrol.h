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
* Description:  volume_control_api
*
*/



#ifndef C_TESTSDKVOLUMECONTROL_H
#define C_TESTSDKVOLUMECONTROL_H

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
_LIT( KtestsdkvolumecontrolLogPath, "\\logs\\testframework\\testsdkvolumecontrol\\" ); 
// Log file
_LIT( KtestsdkvolumecontrolLogFile, "testsdkvolumecontrol.txt" ); 
_LIT( KtestsdkvolumecontrolLogFileWithTitle, "testsdkvolumecontrol_[%S].txt" );

/**
*  CTestSDKVolumeControl test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CAknVolumeControl;
class CVolumeControlContainer;
class CVolumeControlView;
NONSHARABLE_CLASS( CTestSDKVolumeControl ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKVolumeControl* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKVolumeControl();

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
    CTestSDKVolumeControl( CTestModuleIf& aTestModuleIf );

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
    * ConstructorL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCConstructorL( CStifItemParser& aItem );
    /**
    * Delete test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCDelete( CStifItemParser& aItem );
    /**
    * ConstructFromResourceL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCConstructFromResourceL( CStifItemParser& aItem );
    /**
    * SetValue test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCSetValue( CStifItemParser& aItem );
    /**
    * Value test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCValue( CStifItemParser& aItem );
    /**
    * SetRange test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCSetRange( CStifItemParser& aItem );
    /**
    * GetRange test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCGetRange( CStifItemParser& aItem );
    /**
    * HandleResourceChange test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCHandleResourceChange( CStifItemParser& aItem );
    /**
    * CreateBitmapL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCCreateBitmapL( CStifItemParser& aItem );
    /**
    * CreateSetStyleListBoxIconL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCCreateSetStyleListBoxIconL( CStifItemParser& aItem );
    /**
    * CreateSetDynRangeStyleListBoxIconL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCCreateSetDynRangeStyleListBoxIconL( CStifItemParser& aItem );
    /**
    * HandlePointerEventL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCHandlePointerEventL( CStifItemParser& aItem );
    /**
    * HandleNaviDecoratorEventL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVCHandleNaviDecoratorEventL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    //for test data
    CAknVolumeControl* iVolumeControl;
    CVolumeControlContainer* iVolumeContainer;
    CVolumeControlView *iVolumeView;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKVOLUMECONTROL_H

// End of File
