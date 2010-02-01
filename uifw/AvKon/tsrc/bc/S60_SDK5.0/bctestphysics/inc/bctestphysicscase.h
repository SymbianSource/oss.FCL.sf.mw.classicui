/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  container
*
*/

#ifndef C_BCTESTPHYSICSCASE_H
#define C_BCTESTPHYSICSCASE_H

#include <aknphysicsobserveriface.h>

#include "bctestcase.h"

class CBCTestPhysicsContainer;
class CCoeControl;
class CAknPhysics;

/**
* test case for various classes
*/
class CBCTestPhysicsCase: public CBCTestCase,
                          public MAknPhysicsObserver
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestPhysicsCase* NewL( CBCTestPhysicsContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestPhysicsCase();
    
public: // from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

protected: // new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
    
    /**
     * Create control or allocate resource for test
     * @param aCmd UI command, maybe you need to do some work 
     * for different outline
     */
    void PrepareCaseL( TInt aCmd );
    
    /**
     * Release resource used in test
     */
    void ReleaseCaseL();
    
    /**
     * Physics emulation has moved the view
     * 
     * @since S60 v5.0
     * @param aNewPosition The new position of the view.
     */
    void ViewPositionChanged( const TPoint& aNewPosition,
            TBool aDrawNow,
            TUint aFlags );
    
    /**
     * Physics emulation has stopped moving the view
     *
     * @since S60 v5.0
     */
    void PhysicEmulationEnded();

    /**
     * Returns the observer view position.
     *
     * @since S60 v5.0
     * @return Physics observer view position.
     */
    TPoint ViewPosition() const;
    
    /**
     * Test Physics apis
     */
    void TestPhysicsL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestPhysicsCase( CBCTestPhysicsContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    /**
     * Pointer to a control, maybe you need one in your test
     * own
     */
    CCoeControl* iControl;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestPhysicsContainer* iContainer;
    
    /*
     * Pointer to Physics instance
     * owned
     */
    CAknPhysics* iPhysics;
    };

#endif // C_BCTESTPHYSICSCASE_H