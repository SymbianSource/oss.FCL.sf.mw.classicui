/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Class for the test cases.
*
*/

#ifndef C_BCTESTMIXMCLGENERALCASE_H
#define C_BCTESTMIXMCLGENERALCASE_H

#include <aknlongtapdetector.h>
#include <aknphysicsobserveriface.h>
#include <itemfinderobserver.h>

#include "bctestcase.h"

class CBCTestMixMCLContainer;
class CBCTestMixMCLView;
class CCoeControl;

/**
* test case for general apis
*/
class CBCTestMixMCLGeneralCase: public CBCTestCase,
							    public MAknLongTapDetectorCallBack,
                                public MAknPhysicsObserver,
                                public MAknItemFinderObserver
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestMixMCLGeneralCase* NewL( 
            CBCTestMixMCLContainer* aContainer,
            CBCTestMixMCLView* aView );
    
    /**
    * Destructor
    */
    virtual ~CBCTestMixMCLGeneralCase();
    
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
    * Callback method. Get's called when a long tap occurs.
    * @param aPenEventLocation Long tap event location relative to parent control.
    * @param aPenEventScreenLocation Long tap event location relative to screen.
    */
    void HandleLongTapEventL( const TPoint& aPenEventLocation, 
                                      const TPoint& aPenEventScreenLocation );
    /*
     * Test list box apis
     */
    void TestListBoxL();
    
    /*
     * Test options menu's apis
     */    
    void TestOptionsMenuL();    
    
    /*
     * Test tas object apis
     */ 
    void TestTasObjectInfoAndTasHookL();
    
    /*
     * Test miscellaneous apis, function one
     */
    void TestMiscApisFuncOneL();
    
    /*
     * Test one function in class AknPopupUtils
     */
    void TestAknPopupUtilsL();    
    /*
     * Test one function in class AknListUtils
     */
    void TestAknListUtilsL(); 
	    
    /*
     * Test new APIs in CAknToolbar
     */
    void TestAknToolbarL();
 
    /*
     * Test ProcessCommandL in AknRadioButtonSettingPage
     */
    void TestRadioButtonSettingPageL();
 
    /*
     * Test ProcessCommandL in AknPopupSettingPage
     */
    void TestPopupSettingPageL();

    /*
     * Tests editor's kinetic scrolling related functions.
     */
    void TestEditorKineticScrollingL();
    
    /*
     * Tests editor's kinetic scrolling related functions.
     */
    void TestEnableKineticScrollingPhysicsL();

    /**
     * Tests the SuspendPhysics() method in CAknPhysics.
     */
    void TestAknPhysicsSuspendPhysicsL();
    
    /**
     * Tests the ResumePhysics() method in CAknPhysics.
     */
    void TestAknPhysicsResumePhysicsL();
    
    /*
     * Tests CBA APIs.
     */
     void TestCbaL();

     /*
      * Tests common dialogs APIs.
      */
     void TestCommonDialogsL();

     /*
      * Tests ItemFinder.
      */
     void TestItemFinder();

     /**
      * Tests FindItemDialog.
      */
     void TestFindItemDialog();


protected: // From base class MAknPhysicsObserver
    
    /**
     * Physics emulation has moved the view
     * 
     * @param  aNewPosition  The new position of the view.
     * @param  aDrawNow      @c ETrue if client should redraw the screen,
     *                       otherwise @c EFalse.
     * @param  aFlags        Additional flags, not used currently.
     */
    void ViewPositionChanged( const TPoint& aNewPosition,
                              TBool aDrawNow,
                              TUint aFlags );
    
    /**
     * Physics emulation has stopped moving the view
     */
    void PhysicEmulationEnded();

    /**
     * Returns the observer view position.
     *
     * @return Physics observer view position.
     */
    TPoint ViewPosition() const;
    
    // From MAknItemFinderObserver

    /**
     * Handles the activation event.
     *
     * @param  aItem        Activated item.
     * @param  aEvent       Activation method.
     * @param  aFlags       Additional information about the event.
     */
    void HandleFindItemEventL( const CItemFinder::CFindItemExt& aItem,
            MAknItemFinderObserver::TEventFlag aEvent, TUint aFlags);

private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestMixMCLGeneralCase( CBCTestMixMCLContainer* aContainer, 
            CBCTestMixMCLView* aView );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    /**
     * Pointer to view
     * not own
     */
	CBCTestMixMCLView* iView;
	
    /**
     * Pointer to view
     * own
     */
    CCoeControl* iControl;
    
    /**
     * Pointer to container.
     * not own
     */
    CBCTestMixMCLContainer* iContainer;
    };

#endif /*C_BCTESTMIXMCLGENERALCASE_H*/

