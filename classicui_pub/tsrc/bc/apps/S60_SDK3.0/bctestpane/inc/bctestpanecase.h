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









#ifndef C_BCTESTPANECASE_H
#define C_BCTESTPANECASE_H

#include <akntitle.h>
#include <akntabobserver.h>
#include <aknnavidecoratorobserver.h>
#include <aknpictographdrawerinterface.h>
#include <akncontext.h>

#include "bctestcase.h"

class CEikonEnv;
class CBCTestPaneContainer;
class CBCTestPaneTitle;
class CBCTestContextPane;
class CAknTabGroup;
class CAknNavigationControlContainer;
class CAknNavigationDecorator;
class TBCTestNaviDeObserver;

// a helper observer
// Note that: the header file "akntitlepaneobserver.h" only available in R&D SDK,
// So we just redefined the M-interface directly here.
class MAknTitlePaneObserver
    {
public:
    enum TAknTitlePaneEvents
        {
        EAknTitlePaneTapped
        }; 
        
public:
    /**
    * HandleTitlePaneEventL is used in observers to handle title pane events.
    *
    * @param aEventID TAknTitlePaneEvents type title pane event
    */
    virtual void HandleTitlePaneEventL( TInt aEventID ) = 0; 
    };

/**
 * Observer class for CAknNaviDecorator
 */
class TBCTestNaviDeObserver: public MAknNaviDecoratorObserver
    {
public:
    
    virtual void HandleNaviDecoratorEventL( TInt aEventId );
    
    };

/**
* test case for Title Pane API, Status Pane, Context Pane API, Tab API, 
* Navigation Pane API
*/
class CBCTestPaneCase: public CBCTestCase
    {
public: 

// constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestPaneCase* NewL( CBCTestPaneContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestPaneCase();
    
// from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

// new function

    /**
     * Called by conatainer to test some API related with CWindowGc
     * @param a reference to CWindowGc
     */
    void DrawCaseL( CWindowGc& aGc );
    
protected: // new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
    
    /**
     * Release resource used in test
     */
    void ReleaseCase();
    
    /**
     * Test functions
     */
    void TestTitlePaneL();
    
    void TestStatusPaneL();
    
    void TestContextPaneL();
    
    void TestTabGroupL();
    
    void TestNaviPaneL();
    
    void TestDlgShutAndPictoL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestPaneCase( CBCTestPaneContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
   
    /**
     * Pointer to container.
     * not own
     */
    CBCTestPaneContainer* iContainer;
    
    /**
     * Pointer to CEikonEnv.
     * not own
     */
    CEikonEnv* iEnv;
    
    /**
     * Pointer to title pane class.
     * own
     */
    CBCTestPaneTitle* iTitle;
    
    /**
     * Record current command     
     */
    TInt iCommand;
    
    /**
     * Pointer to context pane
     * own
     */
    CBCTestContextPane* iContext;
    
    /**
     * Pointer to tab group
     * own
     */
    CAknTabGroup* iTab;
    
    /**
     * Pointer to navigation pane
     * own
     */
    CAknNavigationControlContainer* iNavi;
    
    /**
     * Pointer to navigation decorator
     * own
     */
    CAknNavigationDecorator* iNaviDe;
    
    /**
     * Implementation of MAknNaviDecoratorObserver    
     */
    TBCTestNaviDeObserver iNaviObserver;
    
    };
    
/**
 * Class for testing protected API of CAknTitlePane
 */
class CBCTestPaneTitle: public CAknTitlePane
    {
    friend class CBCTestPaneCase;
    };
   
/**
 * Observer class for CAknTabGroup
 */
class TBCTestTabObserver: public MAknTabObserver
    {
public:
    
    virtual void TabChangedL( TInt aIndex );
    
    };
    
/**
 * Implementation of MAknPictographAnimatorCallBack
 */
class TBCTestPictoAnimCallBack: public MAknPictographAnimatorCallBack
    {
public:

    void DrawPictographArea();
    
    };
    
/**
 * Observer class for CAknTitlePane
 */
class TBCTestTitleObserver: public MAknTitlePaneObserver
    {
public:
    
    void HandleTitlePaneEventL( TInt aEventID );
    
    };
    
/**
 * Derived class for CAknContextPane
 */
class CBCTestContextPane: public CAknContextPane
    {
    friend class CBCTestPaneCase;

protected:
    
    TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
    
    };

#endif // C_BCTESTPANECASE_H