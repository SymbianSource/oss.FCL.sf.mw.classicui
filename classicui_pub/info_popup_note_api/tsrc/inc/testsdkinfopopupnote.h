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
* Description:  info_popup_note_api
*
*/



#ifndef C_TESTSDKINFOPOPUPNOTE_H
#define C_TESTSDKINFOPOPUPNOTE_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <akninfopopupnotecontroller.h> 

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkinfopopupnoteLogPath, "\\logs\\testframework\\testsdkinfopopupnote\\" ); 
// Log file
_LIT( KtestsdkinfopopupnoteLogFile, "testsdkinfopopupnote.txt" ); 
_LIT( KtestsdkinfopopupnoteLogFileWithTitle, "testsdkinfopopupnote_[%S].txt" );

/**
*  CTestSDKInfoPopupNote test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CAknInfoPopupNoteController;
class TestSubAknInfoPopupNoteObserver : public MAknInfoPopupNoteObserver
    {
public:
    void HandleInfoPopupNoteEvent(CAknInfoPopupNoteController* /*aController*/,
              MAknInfoPopupNoteObserver::TAknInfoPopupNoteEvent /*aEvent*/ )
        {}
    
    };
NONSHARABLE_CLASS(CTestSDKInfoPopupNote) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKInfoPopupNote* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKInfoPopupNote();

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
    CTestSDKInfoPopupNote( CTestModuleIf& aTestModuleIf );

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

    //[TestMethods]
private:
    /**
    * NewL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCNewL( CStifItemParser& aItem );    
    /**
    * SetTimeDelayBeforeShow test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCSetTimeDelayBeforeShow( CStifItemParser& aItem );    
    /**
    * SetTimePopupInView test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCSetTimePopupInView( CStifItemParser& aItem );    
    /**
    * SetTextL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCSetTextL( CStifItemParser& aItem );    
    /**
    * ShowInfoPopupNote test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCShowInfoPopupNote( CStifItemParser& aItem );
    /**
    * HideInfoPopupNote test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCHideInfoPopupNote( CStifItemParser& aItem );
    /**
    * AddObserverL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCAddObserverL( CStifItemParser& aItem );
    /**
    * RemoveObserver test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCRemoveObserverL( CStifItemParser& aItem );
    /**
    * SetPositionAndAlignment test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCSetPositionAndAlignment( CStifItemParser& aItem );
    /**
    * SetPositionByHighlight test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCSetPositionByHighlight( CStifItemParser& aItem );
    /**
    * RestoreDefaultPosition test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCRestoreDefaultPosition( CStifItemParser& aItem );
    /**
    * SetTooltipModeL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCSetTooltipModeL( CStifItemParser& aItem );
    /**
    * SetTone test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCSetTone( CStifItemParser& aItem );
    /**
    * HideWhenAppFaded test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIPNCHideWhenAppFaded( CStifItemParser& aItem );



private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    

    //for test AknInfoPopupNoteController.h;
    CAknInfoPopupNoteController* infoPopupNoteController;

    };

#endif      // C_TESTSDKINFOPOPUPNOTE_H

// End of File
