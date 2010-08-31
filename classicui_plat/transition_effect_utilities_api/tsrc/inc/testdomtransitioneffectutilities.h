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
* Description:  test transition_effect_utilities_api
*
*/



#ifndef C_TESTDOMTRANSITIONEFFECTUTILITIES_H
#define C_TESTDOMTRANSITIONEFFECTUTILITIES_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <akntransitionutils.h>
#include <aknstatuspaneutils.h>
#include <akntransitionutils.h>

#include "testdomutilitiesobserver.h"
#include "testdomutilitiescontainer.h"


// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomtransitioneffectutilitiesLogPath, "\\logs\\testframework\\testdomtransitioneffectutilities\\" ); 
// Log file
_LIT( KtestdomtransitioneffectutilitiesLogFile, "testdomtransitioneffectutilities.txt" ); 
_LIT( KtestdomtransitioneffectutilitiesLogFileWithTitle, "testdomtransitioneffectutilities_[%S].txt" );

/**
*  CTestDomTransitionEffectUtilities test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomTransitionEffectUtilities ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomTransitionEffectUtilities* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomTransitionEffectUtilities();

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
    CTestDomTransitionEffectUtilities( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test akntransitionutils.h
    /**
    * TestTUAddObserverL test function of class CAknTransitionUtils in akntransitionutils.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTUAddObserverL( CStifItemParser& aItem );
    
    /**
    * TestTURemoveObserverL test function of class CAknTransitionUtils in akntransitionutils.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTURemoveObserverL( CStifItemParser& aItem );
    
    /**
    * TestTUGetState test function of class CAknTransitionUtils in akntransitionutils.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTUGetState( CStifItemParser& aItem );
    
    
    /**
    * TestTUSetData test function of class CAknTransitionUtils in akntransitionutils.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTUSetData( CStifItemParser& aItem );
    
    /**
    * TestTUGetData test function of class CAknTransitionUtils in akntransitionutils.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTUGetData( CStifItemParser& aItem );
    
    /**
    * TestTURemoveData test function of class CAknTransitionUtils in akntransitionutils.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTURemoveData( CStifItemParser& aItem );
    
    /**
    * TestTUSetAllParents test function of class CAknTransitionUtils in akntransitionutils.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTUSetAllParents( CStifItemParser& aItem );
    
    /**
    * TestTUTransitionsEnabled test function of class CAknTransitionUtils in akntransitionutils.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTUTransitionsEnabled( CStifItemParser& aItem );
    
    /**
    * TestTUMakeVisibleSubComponents test function of class CAknTransitionUtils in akntransitionutils.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTUMakeVisibleSubComponents( CStifItemParser& aItem );
    
    /**
    * TestTUGetDemarcation test function of class CAknTransitionUtils in akntransitionutils.h
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTUGetDemarcation( CStifItemParser& aItem );
    

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
   /**
     * Pointers to test CAknTransitionUtils
     * own*/
    CTestDomUtilitiesContainer *iContainer;
    /**
     * Pointer to component control.
     * own
     */
    CCoeControl* iControl;

    };

#endif      // C_TESTDOMTRANSITIONEFFECTUTILITIES_H

// End of File
