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
* Description:  test skinnable_clock_api
 *
*/



#ifndef C_TESTDOMSKINNABLECLOCK_H
#define C_TESTDOMSKINNABLECLOCK_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <eikenv.h>
#include <aknskinnableclock.h>
#include <coemain.h>
#include <coeaui.h>



#include "testdomclockcontainer.h"


// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomskinnableclockLogPath, "\\logs\\testframework\\testdomskinnableclock\\" ); 
// Log file
_LIT( KtestdomskinnableclockLogFile, "testdomskinnableclock.txt" ); 
_LIT( KtestdomskinnableclockLogFileWithTitle, "testdomskinnableclock_[%S].txt" );

/**
*  CTestDomSkinnableClock test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomSkinnableClock ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomSkinnableClock* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomSkinnableClock();

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
    CTestDomSkinnableClock( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test AknSkinnableClock.h
    /**
    * TestSCNewL test function of class CAknSkinnableClock in AknSkinnableClock.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSCNewL( CStifItemParser& aItem );
    
    /**
    * TestSCUpdateDisplayL test function of class CAknSkinnableClock in AknSkinnableClock.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSCUpdateDisplayL( CStifItemParser& aItem );
    
    /**
    * TestSCSetFormatL test function of class CAknSkinnableClock in AknSkinnableClock.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSCSetFormatL( CStifItemParser& aItem );
    
    /**
    * TestSCPositionChangedL test function of class CAknSkinnableClock in AknSkinnableClock.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSCPositionChangedL( CStifItemParser& aItem );
    
    /**
    * TestSCHandlePointerEventL test function of class CAknSkinnableClock in AknSkinnableClock.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestSCHandlePointerEventL( CStifItemParser& aItem );
    

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * Pointer to Test CAknSkinnableClock.
     * own
     */
    CTestDomClockContainer* iContainer;
    /**
     * Pointer to Component Control.
     * own
     */
    CCoeControl* iControl;

    };

#endif      // C_TESTDOMSKINNABLECLOCK_H

// End of File
