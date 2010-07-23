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
* Description:         test case for list classes in eikstd
*
*/









#ifndef C_BCTESTLISTEIKLISTCASE_H
#define C_BCTESTLISTEIKLISTCASE_H

#include <eiklbd.h>
#include <eiklbed.h>
#include <eiklbi.h>

#include "bctestlistbasecase.h"

class CEikonEnv;
class CBCTestListContainer;
class CBCTestListBoxData;
class CBCTestTextListItemDrawer;
class CBCTestTextListModel;
class CBCTestTextListBox;
class CBCTestTextSnakingListBox;

/**
* test case for various list classes
*/
class CBCTestListEiklistCase: public CBCTestListBaseCase
    {
public: 

// constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestListEiklistCase* NewL( 
        CBCTestListContainer* aContainer, CEikonEnv* aEikEnv );
    
    /**
    * Destructor
    */
    virtual ~CBCTestListEiklistCase();
    
// from CBCTestCase
    
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
    void TestListBoxDataL();
     
    void TestCEikListBoxEditorL();
     
    void TestCTextListItemDrawerL();
     
    void TestListBoxViewL();
     
    void TestEikListBoxL();
     
    void TestSnakingListBoxL();
    
    void TestSnakingListBoxViewL();
        
private: // constructor
    
    /**
    * C++ default constructor
    */
    CBCTestListEiklistCase( CBCTestListContainer* aContainer, 
        CEikonEnv* aEikEnv );
    
    /**
    * Symbian 2nd constructor
    */
    void ConstructL();
    
private: // data
    
    CBCTestListBoxData* iData; // own
    
    TInt iCurrentCmd;
    
    CBCTestTextListItemDrawer* iTextDrawer; // own
    
    CBCTestTextListModel* iModel; // own
    
    CBCTestTextListBox* iListBox; // own
    
    CBCTestTextSnakingListBox* iSnakingList; // own
    
    };
    
/**
 * Test class for protected API of CListBoxData
 */
class CBCTestListBoxData: public CListBoxData
    {
public: 
   
    TInt TestRegenerateFonts();
    void TestConstructFontL( const CFont* aBaseFont );
    void TestUpdateFontBoundValues( const CFont* aBaseFont );
    TBool TestCFontWithStyle();

    };

/**
 * Fake class of MListBoxEditorObserver
 */
class TBCTestListBoxEditorObserver: public MListBoxEditorObserver
    {
public:
    
    TKeyResponse HandleListBoxEditorEventL(
        MEikListBoxEditor* aListBoxEditor, const TKeyEvent& aKeyEvent);
    
    };

/**
 * Test class for protected API of CEikListBoxTextEditor
 */   
class CBCTestListBoxEditor: public CEikListBoxTextEditor
    {
public:
    
    CBCTestListBoxEditor( MListBoxModel* aModel, CEikonEnv* aEikonEnv );
    
    void TestWriteInternalStateL();
       
private: // data
    
    /**
     * Not own.
     */
    CEikonEnv* iEikEnv;
     
    };

/**
 * Test class for protected API of CTextListItemDrawer
 */    
class CBCTestTextListItemDrawer: public CTextListItemDrawer
    {
public:
    
    CBCTestTextListItemDrawer( MTextListBoxModel* aTextListBoxModel, 
        const CFont* aFont );
    
    /**
     * Test DrawItemText and it will call DoDrawItemText,
     * CListItemDrawer::DrawFrame and both two ResetGc().
     */
    void TestDrawItemText( CWindowGc& aGc );
    
    };
    
/**
 * Test class for protected API of CTextListBoxModel
 */    
class CBCTestTextListModel: public CTextListBoxModel
    {
public:
    
    /**
     * Test ItemArrayOwnershipType
     */
    TListBoxModelItemArrayOwnership TestItemArrayOwnershipType();
    
    };
    
/**
 * Test class for protected API of CEikTextListBox
 */    
class CBCTestTextListBox: public CEikTextListBox
    {
    
    friend class CBCTestListEiklistCase;
    
    };
    
/**
 * Test class for protected API of CEikSnakingTextListBox
 */    
class CBCTestTextSnakingListBox: public CEikSnakingTextListBox
    {
    
    friend class CBCTestListEiklistCase;
    
    };
    
/**
 * Fake list box observer
 */ 
class TBCTestListBoxObserver: public MEikListBoxObserver
    {
public:
    void HandleListBoxEventL(CEikListBox* aListBox, 
        TListBoxEvent aEventType);
    };

#endif // C_BCTESTLISTEIKLISTCASE_H