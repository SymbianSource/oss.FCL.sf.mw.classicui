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
* Description:         test case for popup list box classes
*
*/








#ifndef C_CBCTESTLISTPOPUPCASE_H
#define C_CBCTESTLISTPOPUPCASE_H

#include "aknlists.h"

#include "bctestlistbasecase.h"

class CEikFormattedCellListBox;
class CBCTestListContainer;
class CEikonEnv;

/**
* test case for various list classes
*/
class CBCTestListPopupCase: public CBCTestListBaseCase
    {
public: 

// constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestListPopupCase* NewL( 
        CBCTestListContainer* aContainer, CEikonEnv* aEikEnv );
    
    /**
    * Destructor
    */
    virtual ~CBCTestListPopupCase();
    
// from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

protected: 

// new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
    
    /**
    * Prepare necessary resource for test case
    * @param aCmd, UI command
    */
    void PrepareCaseL( TInt aCmd );
    
    /**
    * Release resource used by test case
    */
    void ReleaseCase();
    
    /**
    * test functions
    */
    void TestPopupListL( TInt aCmd );
    
private: 

// constructor
    
    /**
    * C++ default constructor
    */
    CBCTestListPopupCase( CBCTestListContainer* aContainer, 
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
        
    };

/**
* test class, for call protected API
*/
class CBCTestSinglePopupMenuStyleListBox: 
    public CAknSinglePopupMenuStyleListBox
    {
public:
    
    void TestHandlePointerEventL( const TPointerEvent& aPointerEvent );
        
    };

/**
* test class, for call protected API
*/
class CBCTestSingleGraphicPopupMenuStyleListBox: 
    public CAknSingleGraphicPopupMenuStyleListBox
    {
public:

    void TestHandlePointerEventL( const TPointerEvent& aPointerEvent );
           
    };

/**
* test class, for call protected API
*/
class CBCTestSingle2GraphicPopupMenuStyleListBox: 
    public CAknSingle2GraphicPopupMenuStyleListBox
    {
public:
    
    void TestHandlePointerEventL( const TPointerEvent& aPointerEvent );
           
    };
    
/**
* test class, for call protected API
*/
class CBCTestDoubleGraphicPopupMenuStyleListBox: 
    public CAknDoubleGraphicPopupMenuStyleListBox
    {
public:
    
    void TestHandlePointerEventL( const TPointerEvent& aPointerEvent );
           
    };

#endif // C_CBCTESTLISTPOPUPCASE_H