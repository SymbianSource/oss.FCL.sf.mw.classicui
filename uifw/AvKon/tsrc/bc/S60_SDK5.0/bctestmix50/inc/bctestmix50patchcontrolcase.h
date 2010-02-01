/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  declaration of test case
*
*/


#ifndef C_BCTESTMIX50PATCHCONTROLCASE_H
#define C_BCTESTMIX50PATCHCONTROLCASE_H

#include <akntoolbarobserver.h>
#include <eikcmobs.h>
#include "bctestcase.h"

class CBCTestMix50Container;
class CCoeControl;
class MAknToolbarObserver;
class CAknStaticNoteDialog;
class CBCTestAknNoteDialog;

/**
* test case for various classes
*/
class CBCTestMix50PatchControlCase: public CBCTestCase,
							  public MAknToolbarObserver,
							  public MEikCommandObserver
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestMix50PatchControlCase* NewL( 
            CBCTestMix50Container* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestMix50PatchControlCase();
    
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
     * Test the bitmap animation apis
     */
    void TestAnimationL();
   
    /**
     * Test the buttons api
     */
    void TestButtonsL();
    
    /*
    * Test the choice list api
    */
    void TestChoiceListL();
    
    /*
    * Test the common file api
    */
    void TestCommonFileL();
    
    /*
    * Test the common file api
    */
    void TestSelectCommonFileL();
    
    /*
    * Test the common file api
    */
    void TestSaveCommonFileL();
    
    /*
    * Test the document handler api
    */
    void TestDocumentHandlerL();
    
    /*
    * Test the fonts api
    */
    void TestFontsL();
    
    /*
    * Test the generic buttons api and grids api
    */
    void TestGridsL();
    
    /*
    * Test the hlist and hotkey api
    */
    void TestHListsAndHotkeysL();
    
    /*
    * Test miscellaneous apis
    */
    void TestMiscellOneL();    
    
    /*
    * Test the initialization apis
    */
    void TestInitializationL();
    
    /*
    * Test the input language apis
    */
    void TestInputLanL();
    
    /*
    * Test menus apis
    */
    void TestMenusL();
    
    /*
    * Test the notes apis
    */
    void TestNotesL();
    
    /*
    * Test another miscellaneous apis
    */
    void TestMiscellTwoL();
    
    /*
    * Test the notifier apis
    */
    void TestNotifierL();
    
    /*
    * Test the buttons apis
    */
    void TestPopupsL();
    
    /*
    * Test the ui framework apis
    */
    void TestUIFrmL();
    
    /*
    * Test the queries apis
    */
    void TestQueriesL();
    
    /*
    * Test the scroller apis
    */
    void TestScrollerL();
    
    /*
    * Test the search field api
    */
    void TestSearchfieldL();
    
    /*
    * Test the setting page apis
    */
    void TestSettingPagesL();
    
    /*
    * Test the title pane apis
    */
    void TestTitlePaneL();
    
    /*
    * Test the toolbar apis
    */
    void TestAknToolbarL();
    
    /*
    * Test touch pane api
    */
    void TestAknTouchPaneL();

    /*
    * Test CAknEnv apis
    */
    void TestAknEnvL();

    /*
    * Test volume control api
    */
    void TestAknVolumeControlL();
    
    /*
    * Test haptics api
    */
    void TestHapticsL();
    
    /*
     * Test image item data
     */
    void TestImageTableItemDataL();
    
    /*
     * Test image item data
     */
    void TestMBmpItemDataL();
    
    /*
     * Test color table item data
     */
    void TestColTableItemDataL();
    
    /*
     * Test a bunch of background control context apis
     */
    void TestBackgroundCCL();
    
    /*
     * Test AknLayoutUtils apis
     */
    void TestAknLayoutUtilsL();
    
    /*
     * Test AknsUtils apis
     */
    void TestAknsUtilsL();
    
    /*
     * Test AknsDrawUtils apis
     */
    void TestAknsDrawUtilsL();
    
    /*
     * Test various dialog classes api
     */
    void TestDialogsL();
    
    /*
     * Test popup control apis
     */
    void TestPopupL();
    
    /*
     * Test state related objects
     */
    void TestStatesL();
    
    /*
     * Test ip field editor apis
     */
    void TestIpFieldEditorL();
    
    /*
     * Test icon array apis
     */
    void TestIconArrayL();
private: // constructor
    
    /**
     * C++ default constructor
     */
	CBCTestMix50PatchControlCase( CBCTestMix50Container* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
    /**
     * Handles toolbar events for a certain toolbar item.
     * @param aCommand The command ID of some toolbar item.
     */
    inline void OfferToolbarEventL( TInt /* aCommand */ ){}
    
    /**
     * ProcessComamndL
     */
    inline void ProcessCommandL( TInt ){}
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
    CBCTestMix50Container* iContainer;
    
    /*
     * pointer to the CCoeEnv
     * not own 
     */
    CCoeEnv* iCoeEnv;

    /*
     * pointer to the static note dialog
     * own 
     */
    CAknStaticNoteDialog * iStaticNoteDialog;
    
    /*
     * pointer to the note dialog
     * own 
     */
    CBCTestAknNoteDialog* iNoteDialog;
    };
#endif /*C_BCTESTMIX50PATCHCONTROLCASE_H*/
