/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#ifndef C_CBCTESTFORAKNGRID_H
#define C_CBCTESTFORAKNGRID_H

#include <akngrid.h>

#include "bctestcase.h"

class CBCTestGridsContainer;
class CCoeControl;
class CEikonEnv;
class CAknGrid;

/**
 * test case for various list classes
 */
class CBCTestForAknGrid: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
     * Symbian 2nd static constructor
     */
    static CBCTestForAknGrid* NewL( CBCTestGridsContainer* aContainer );
    
    /**
     * Destructor
     */
    virtual ~CBCTestForAknGrid();
    
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
     * Test TestCAknGridL
     */
    void TestCAknGridL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestForAknGrid( CBCTestGridsContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
    /**
     * Set up for TestCAknGridL
     */
    CAknGrid* SetUpCAknGridL();
    
    /**
     * Tear Down for TestCAknGridL
     */
    void TearDownCAknGridL( CAknGrid* aGrid );
    
private: // data
    
    /**
     * Pointer to a control, maybe you need one in your test
     * own
     */
    CEikonEnv* iEnv;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestGridsContainer* iContainer;
    
    };

/**
 * for testing protected fuctions of CBCTestForAknGrid
 */    
class CBCTestForGrid: public CAknGrid
    {
    friend class CBCTestForAknGrid;
    };

#endif // BCTESTFORAKNGRID_H