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
* Description:  Test api of stylus activated popup
*
*/


#ifndef C_TESTDOMSTYLUSACTIVEPOPUP_H
#define C_TESTDOMSTYLUSACTIVEPOPUP_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <eikenv.h>
#include <e32std.h>
#include <aknlayout2scalabledef.h>
#include <aknstylusactivatedpopupcontent.h>

#include "testdomstylusactivepopupcontainer.h"

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomstylusactivepopupLogPath, "\\logs\\testframework\\testdomstylusactivepopup\\" ); 
// Log file
_LIT( KtestdomstylusactivepopupLogFile, "testdomstylusactivepopup.txt" ); 
_LIT( KtestdomstylusactivepopupLogFileWithTitle, "testdomstylusactivepopup_[%S].txt" );

/**
*  CTestDomStylusActivePopup test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomStylusActivePopup ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomStylusActivePopup* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomStylusActivePopup();

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
    CTestDomStylusActivePopup( CTestModuleIf& aTestModuleIf );

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
    * TestCAknStylActivePopUpContentNewL test four overload function
    * NewL of CAknStylusActivatedPopUpContent
    * @since S60 5.0
    * @param aItem is a number, 1 test NewL only with text parameters,
    * 2 test function with array parameters, 3 test function with resource
    * and 4 test function with reader.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknStylActivePopUpContentNewL( CStifItemParser& aItem );
    
    /**
    * TestCAknStylActivePopUpContentConstructFromResourceL test two overload function
    * ConstructFromResourceL of CAknStylusActivatedPopUpContent in 
    * aknstylusactivatedpopupcontent.h
    * @since S60 5.0
    * @param aItem is a number, 1 test function with resource id,
    * 2 test function with resource reader
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknStylActivePopUpContentConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestCAknStylActivePopUpContentConstructFromResourceL test SetCommandObserver
    * of CAknStylusActivatedPopUpContent in aknstylusactivatedpopupcontent.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknStylActivePopUpContentSetCommandObserverL( CStifItemParser& aItem );
    
    /**
    * TestCAknStylActivePopUpContentSetContainerWindowLL test SetContainerWindowL
    * of CAknStylusActivatedPopUpContent in aknstylusactivatedpopupcontent.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknStylActivePopUpContentSetContainerWindowLL( CStifItemParser& aItem );
    
    /**
    * TestCAknStylActivePopUpContentHandleEventL test HandleResourceChange and
    * HandleControlEventL of CAknStylusActivatedPopUpContent 
    * in aknstylusactivatedpopupcontent.h
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknStylActivePopUpContentHandleEventL( CStifItemParser& aItem );
    
    
    
    
    

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * Container with window
     * Own
     */
    CTestStyleActivePopUpContainer* iContainer;
    
     /*
      * Switch case Id
      * */
     enum SwitchId
         {
         ECaseOne = 1,
         ECaseTwo,
         ECaseThree,
         ECaseFour
         };
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTDOMSTYLUSACTIVEPOPUP_H

// End of File
