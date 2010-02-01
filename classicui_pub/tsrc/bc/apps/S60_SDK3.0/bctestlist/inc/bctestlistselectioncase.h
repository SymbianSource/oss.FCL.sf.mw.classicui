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
* Description:         test case for selection list dialog classes
*
*/








#ifndef C_BCTESTSELECTIONLISTCASE_H
#define C_BCTESTSELECTIONLISTCASE_H

#include <aknselectionlist.h>

#include "bctestlistbasecase.h"

class CEikonEnv;
class CEikTextListBox;
class CBCTestListContainer;
class CColumnListBoxItemDrawer;

/**
* test case for various list classes
*/
class CBCTestListSelectionCase: public CBCTestListBaseCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestListSelectionCase* NewL( 
        CBCTestListContainer* aContainer, CEikonEnv* aEikEnv );
    
    /**
    * Destructor
    */
    virtual ~CBCTestListSelectionCase();
    
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
    * prepare environment for test
    */
    void PrepareCaseL( TInt aCmd );
    
    /**
    * Release resource used in test
    */
    void ReleaseCase();
    
    /**
    * Test functions
    */  
    void TestMarkableListDialogL();
    
    void TestSelectionListDialogL();
        
private: 

// constructor
    
    /**
    * C++ default constructor
    */
    CBCTestListSelectionCase( CBCTestListContainer* aContainer, 
        CEikonEnv* aEikEnv );
    
    /**
    * Symbian 2nd constructor
    */
    void ConstructL();
    
// from CBCTestListBaseCase
    
    /**
    * Appends graphics data.
    * @param Pointer of icon using graphics for listbox.
    */
    virtual void GraphicIconL( CArrayPtr<CGulIcon>* aIcons );
    
    };
    
/**
 * Test class for protected API of CAknMarkableListDialog
 */
class CBCMarkableListDialog: public CAknMarkableListDialog
    {
    friend class CBCTestListSelectionCase;

public:

    static CBCMarkableListDialog* NewL( TInt &aValue, 
        CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray );
    
    CBCMarkableListDialog( TInt &aValue, CArrayFix<TInt> *aSelectedItems, 
        MDesCArray *aArray, TInt aMenuBarResourceId, 
        TInt aOkMenuBarResourceId, MEikCommandObserver *aObserver );
    
    };
    
/**
 * Test class for protected API of CAknSelectionListDialog
 */
class CBCSelectionListDialog: public CAknSelectionListDialog
    {
    friend class CBCTestListSelectionCase;

public:

    static CBCSelectionListDialog* NewL( TInt &aValue, MDesCArray *aArray );
    
    CBCSelectionListDialog( TInt &aValue, MDesCArray *aArray,          
        MEikCommandObserver *aObserver );
    
    };

#endif // C_BCTESTSELECTIONLISTCASE_H