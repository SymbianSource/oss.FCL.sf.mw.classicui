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









#ifndef C_BCTESTSEARCHFIELDCASE_H
#define C_BCTESTSEARCHFIELDCASE_H

#include "bctestcase.h"

class CAknSearchField;
class CBCTestSearchFieldContainer;
class CCoeControl;

/**
* test case for various list classes
*/
class CBCTestSearchFieldCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestSearchFieldCase* NewL( CBCTestSearchFieldContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestSearchFieldCase();
    
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
    
    /** test searchfield control creation API(s).*/
    void TestCreateL();

    /** try to create the searchfield control. */
    void TryCreateL();
    
    /** test searchfield control about text APIs.*/
    void TestTextL();
    
    /** test searchfield control about other APIs.*/
    void TestOthersL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestSearchFieldCase( CBCTestSearchFieldContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    /**
     * Pointer to SearchField.
     * own
     */    
    CAknSearchField* iSearchField;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestSearchFieldContainer* iContainer;
    
    };

#endif // C_BCTESTSEARCHFIELDCASE_H
