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
* Description: Test aknphysics.h
*
*/


#ifndef C_TESTPLATPHYSICS_H
#define C_TESTPLATPHYSICS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <eikenv.h>
#include <eikappui.h>
#include <coemain.h>
#include <aknphysics.h>
#include <aknphysicsobserveriface.h>
#include "testplatphysicscontrol.h"
// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KTestPlatPhysicsLogPath, "\\logs\\testframework\\testplatphysics\\" ); 
// Log file
_LIT( KTestPlatPhysicsLogFile, "testplatphysics.txt" ); 
_LIT( KTestPlatPhysicsLogFileWithTitle, "testplatphysics_[%S].txt" );

/**
*  CTestPlatPhysics test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestPlatPhysics ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestPlatPhysics* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestPlatPhysics();

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
    CTestPlatPhysics( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Example test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */

    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // [TestMethods]
    /**
     * TestCAknPhysicsNewL test NewL of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsNewL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsInitPhysicsL test InitPhysicsL of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsInitPhysicsL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsStartPhysicsL test StartPhysics of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsStartPhysicsL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsStopPhysicsL test StopPhysics of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsStopPhysicsL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsOngoingPhysicsActionL test OngoingPhysicsAction of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsOngoingPhysicsActionL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsRegisterPanningPositionL test RegisterPanningPosition of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsRegisterPanningPositionL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsSetFrictionL test SetFriction of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsSetFrictionL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsResetFrictionL test ResetFriction of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsResetFrictionL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsHighlightTimeoutL test HighlightTimeout of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsHighlightTimeoutL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsDragThresholdL test DragThreshold of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsDragThresholdL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsFeatureEnabledL test FeatureEnabled of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsFeatureEnabledL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsEventHandlingAllowedL test EventHandlingAllowed of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsEventHandlingAllowedL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsUpdateViewWindowControlL test UpdateViewWindowControl of CAknPhysics
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsUpdateViewWindowControlL( CStifItemParser& aItem );

    /**
     * TestCAknPhysicsSuspendPhysicsL test SuspendPhysics of CAknPhysics
     * @since S60 5.2
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsSuspendPhysicsL( CStifItemParser& aItem );
    
    /**
     * TestCAknPhysicsResumePhysicsL test ResumePhysics of CAknPhysics
     * @since S60 5.2
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCAknPhysicsResumePhysicsL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * ?description_of_pointer_member
     * Not own.
     */
    CPhysicsControl* iControl;

    };

#endif      // C_TESTPLATPHYSICS_H

// End of File

