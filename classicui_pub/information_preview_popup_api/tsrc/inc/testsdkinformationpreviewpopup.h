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
* Description:  information_preview_popup_api
*
*/



#ifndef C_TESTSDKINFORMATIONPREVIEWPOPUP_H
#define C_TESTSDKINFORMATIONPREVIEWPOPUP_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <aknpreviewpopupcontentprovider.h>



// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkinformationpreviewpopupLogPath, "\\logs\\testframework\\testsdkinformationpreviewpopup\\" ); 
// Log file
_LIT( KtestsdkinformationpreviewpopupLogFile, "testsdkinformationpreviewpopup.txt" ); 
_LIT( KtestsdkinformationpreviewpopupLogFileWithTitle, "testsdkinformationpreviewpopup_[%S].txt" );
//for test
class CAknPreviewPopUpController;



/**
*  CTestSDKInformationPreviewPopup test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/

NONSHARABLE_CLASS( CTestSDKInformationPreviewPopup ) : public CScriptBase
                                                      
                                                       
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKInformationPreviewPopup* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKInformationPreviewPopup();

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
    CTestSDKInformationPreviewPopup( CTestModuleIf& aTestModuleIf );

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
    * NewProviderL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPNewProviderL( CStifItemParser& aItem );
    /**
    * NewL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPNewL( CStifItemParser& aItem );
    /**
    * NewProviderAndStyleL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPNewProviderAndStyleL( CStifItemParser& aItem );
    /**
    * NewStyleL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPNewStyleL( CStifItemParser& aItem );
    /**
    * ContentSizeInLayout test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPContentSizeInLayout( CStifItemParser& aItem );
    /**
    * SetPopUpShowDelay test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPSetPopUpShowDelay( CStifItemParser& aItem );
    /**
    * SetPopUpHideDelay test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPSetPopUpHideDelay( CStifItemParser& aItem );
    /**
    * ShowPopUp test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPShowPopUp( CStifItemParser& aItem );
    /**
    * HidePopUp test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPHidePopUp( CStifItemParser& aItem );
    /**
    * ContentReady test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPContentReadyL( CStifItemParser& aItem );
    /**
    * SetPosition test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPSetPosition( CStifItemParser& aItem );
    /**
    * SetPositionByHighlight test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPSetPositionByHighlight( CStifItemParser& aItem );
    /**
    * AddObserverL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPAddObserverL( CStifItemParser& aItem );
    /**
    * RemoveObserverL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPRemoveObserverL( CStifItemParser& aItem );
    /**
    * UpdateContentSize test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPUpdateContentSize( CStifItemParser& aItem );
    /**
    * Size test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPSize( CStifItemParser& aItem );
    /**
    * SetHeadingTextL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPSetHeadingTextL( CStifItemParser& aItem );
    /**
    * ResetTimer test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPPResetTimer( CStifItemParser& aItem );



private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    //for test
    CAknPreviewPopUpController* iPopup ;
    


    };

#endif      // C_TESTSDKINFORMATIONPREVIEWPOPUP_H

// End of File
