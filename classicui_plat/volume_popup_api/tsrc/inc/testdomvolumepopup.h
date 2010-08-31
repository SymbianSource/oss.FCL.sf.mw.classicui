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
* Description:  volume_popup_api
*
*/



#ifndef C_TESTDOMVOLUMEPOPUP_H
#define C_TESTDOMVOLUMEPOPUP_H

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
_LIT( KtestdomvolumepopupLogPath, "\\logs\\testframework\\testdomvolumepopup\\" ); 
// Log file
_LIT( KtestdomvolumepopupLogFile, "testdomvolumepopup.txt" ); 
_LIT( KtestdomvolumepopupLogFileWithTitle, "testdomvolumepopup_[%S].txt" );

/**
*  CTestDOMVolumePopup test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CAknVolumePopup;
NONSHARABLE_CLASS( CTestDOMVolumePopup ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDOMVolumePopup* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDOMVolumePopup();

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
    CTestDOMVolumePopup( CTestModuleIf& aTestModuleIf );

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
    * TestVPNewL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPNewL( CStifItemParser& aItem );
    /**
    * TestVPDefaultNewL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPDefaultNewL( CStifItemParser& aItem );
    /**
    * TestVPConstructFromResourceL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPConstructFromResourceL( CStifItemParser& aItem );
    /**
    * TestVPNewControlL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPNewControlL( CStifItemParser& aItem );
    /**
    * TestVPHandleVolumeKeyEventL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPHandleVolumeKeyEventL( CStifItemParser& aItem );
    /**
    * TestVPSetValue test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPSetValue( CStifItemParser& aItem );
    /**
    * TestVPSetRange test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPSetRange( CStifItemParser& aItem );
    /**
    * TestVPGetRange test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPGetRange( CStifItemParser& aItem );
    /**
    * TestVPValue test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPValue( CStifItemParser& aItem );
    /**
    * TestVPSetTitleTextL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPSetTitleTextL( CStifItemParser& aItem );
    /**
    * TestVPShowProfileName test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPShowProfileName( CStifItemParser& aItem );
    /**
    * TestVPShowVolumePopupL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPShowVolumePopupL( CStifItemParser& aItem );
    /**
    * TestVPCloseVolumePopup test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPCloseVolumePopup( CStifItemParser& aItem );
    /**
    * TestVPSetValueType test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPSetValueType( CStifItemParser& aItem );
    /**
    * TestVPSetStepSize test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPSetStepSize( CStifItemParser& aItem );
    /**
    * TestVPSetAdjustmentIndicatorDisplay test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPSetAdjustmentIndicatorDisplay( CStifItemParser& aItem );
    /**
    * TestVPSetTimeOutAsSecond test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPSetTimeOutAsSecond( CStifItemParser& aItem );
    /**
    * TestVPSetDecimalPlaces test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPSetDecimalPlaces( CStifItemParser& aItem );
    /**
    * TestVPSetGraphicsL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPSetGraphicsL( CStifItemParser& aItem );
    /**
    * TestVPUseMutedIcon test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPUseMutedIcon( CStifItemParser& aItem );
    /**
    * TestVPClosePopupWhenTappedOutside test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPClosePopupWhenTappedOutside( CStifItemParser& aItem );
    /**
    * TestVPSetDefaultValue test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPSetDefaultValue( CStifItemParser& aItem );
    /**
    * TestVPEnableResetViaValueField test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestVPEnableResetViaValueField( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * for test
     */
    CAknVolumePopup* iVolumePopup;
    };

#endif      // C_TESTDOMVOLUMEPOPUP_H

// End of File
