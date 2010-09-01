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
* Description:         test case for CFormattedCellListBox
*
*/








#ifndef C_BCTESTLISTFROMATBASECASE_H
#define C_BCTESTLISTFROMATBASECASE_H

#include <eikfrlbd.h>

#include "bctestlistbasecase.h"

class CEikonEnv;
class CEikFormattedCellListBox;
class CBCTestListContainer;

/**
 * Fake implementation of MListBoxAnimBackgroundDrawer
 */
class TBCTestListFormatAnimBgDrawer: public MListBoxAnimBackgroundDrawer
    {
public:
    TBool DrawHighlightAnimBackground( CFbsBitGc& aGc ) const;
    
    };

/**
* test case for various list classes
*/
class CBCTestListFormatBaseCase: public CBCTestListBaseCase
    {
public: 

// constructor and destructor
    
    /**
     * Symbian 2nd static constructor
     */
    static CBCTestListFormatBaseCase* NewL( 
        CBCTestListContainer* aContainer, CEikonEnv* aEikEnv );
    
    /**
     * Destructor
     */
    virtual ~CBCTestListFormatBaseCase();

// from CBCTestCase
    
    /**
     * Execute corresponding test functions for UI command
     * @param aCmd, UI command
     */
    void RunL( TInt aCmd );
    
    /**
     * From CBCTestListBaseCase
     */
    void DrawCaseL( CWindowGc& aGc );

protected: 

// new functions
    
    /**
     * Build autotest script
     */
    void BuildScriptL();
    
    /**
     * prepare environment for test
     */
    void PrepareCaseL();
    
    /**
     * Release resource used in test
     */
    void ReleaseCase();
    
    /**
     * Test CEikFormattedCellListBox
     */
    void TestFormatListL();
    
    /**
     * Test CFormattedCellListBoxItemDrawer
     */
    void TestFormatItemDrawerL();
    
    /**
     * Test CFormattedCellListBoxData
     */
    void TestFormatListDataL();
        
private: 

// constructor
    
    /**
    * C++ default constructor
    */
    CBCTestListFormatBaseCase( CBCTestListContainer* aContainer, 
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
    
private: // data
    
    /**
     * Own
     */
    CEikFormattedCellListBox* iListBox;
    
    TBCTestListFormatAnimBgDrawer iDrawer;
        
    };
    
/**
 * Subclass for testing protected API of CFormattedCellListBoxData
 */
class CBCTestListFormatData: public CFormattedCellListBoxData
    {
public: // constructor and destructor
    
    /**
     * C++ default constructor
     */
    CBCTestListFormatData();
    
    /**
     * C++ default constructor
     */
    ~CBCTestListFormatData();
    
public: // new fuctions
    
    void TestConstructLD( const TAknsItemID& aAnimationIID );
    
    };

#endif // C_BCTESTLISTFROMATBASECASE_H