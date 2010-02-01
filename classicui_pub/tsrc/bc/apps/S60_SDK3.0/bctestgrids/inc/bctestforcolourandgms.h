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









#ifndef C_CBCTESTFORCOLOURANDGMS_H
#define C_CBCTESTFORCOLOURANDGMS_H

#include "bctestcase.h"

class CBCTestGridsContainer;
class CCoeControl;

/**
 * test case for various list classes
 */
class CBCTestForColourAndGms: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
     * Symbian 2nd static constructor
     */
    static CBCTestForColourAndGms* NewL( CBCTestGridsContainer* aContainer );
    
    /**
     * Destructor
     */
    virtual ~CBCTestForColourAndGms();
    
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
     * Test TestTestColourSelectionGridL
     */
    void TestColourSelectionGridL();
    /**
     * Test TestakngmsstylegridL
     */
    void TestAknGmsStyleGridL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestForColourAndGms( CBCTestGridsContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    /**
     * TestCAknGMSStyleGridViewL
     */
    void TestCAknGMSStyleGridViewL();
    /**
     * TestCAknGMSStyleGridL
     */
    void TestCAknGMSStyleGridL();
    /**
     * TestCAknGMSPopupGridL
     */
    void TestCAknGMSPopupGridL();
    
private: // data
    /**
     * Pointer to container.
     * not own
     */
    CBCTestGridsContainer* iContainer;
    
    };

#endif // BCTESTFORCOLOURANDGMS_H