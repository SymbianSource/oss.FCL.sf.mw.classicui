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
* Description:  test case for column list classes
*
*/


#ifndef C_BCTESTMIX50PATCHCOLUMNCASE_H
#define C_BCTESTMIX50PATCHCOLUMNCASE_H

#include <e32std.h>
#include <eiktxlbx.h>
#include <eiktxlbm.h>
#include <eiklbx.h>
#include <eiklbi.h>
#include <eiklbd.h>
#include <aknselectionlist.h>
#include <eikconso.h>
#include "bctestmix50patchcolumnbasecase.h"

class CEikColumnListBox;
class CBCTestMix50Container;
class CEikTextListBox;
class CSubSnakingListBoxView;

/**
* test case for various list classes
*/
class CBCTestMix50ListColumnCase: public CBCTestMix50ListBaseCase
    {
public: 

// constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestMix50ListColumnCase* NewL( 
            CBCTestMix50Container* aContainer, CEikonEnv* aEikEnv );
    
    /**
    * Destructor
    */
    virtual ~CBCTestMix50ListColumnCase();
    
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
    * Release resource used by test case
    */
    void ReleaseCase();

	/**
	* test CEikSnakingTextListBox
	*/
	void TestSnakingTextListBoxL();
	
	/**
	* test CEikTextListBox
	*/
    void TestEikTextListBoxL();
    
	/**
	* test CTextListBoxModel
	*/
	void TestTextListBoxModelL();
	
	/**
	* test CEikSnakingListBoxL
	*/
	void TestEikSnakingListBoxL();
	
	/**
	* test CEikListBox
	*/
	void TestEikListBoxL();
	
	/**
	* test CSnakingListBoxView
	*/
	void TestSnakingListBoxViewL();
	
	/**
	* test CListBoxView
	*/
	void TestListBoxViewL();
	
	/**
	* test TextListItemDrawer
	*/
	void TestTextListItemDrawerL();
	
	/**
	* test CEikListBoxTextEditor
	*/
	void TestListBoxTextEditorL();
	
	/**
	* test CListBoxData and CFontsWithStyle
	*/
	void TestListBoxDataL();
	
	/**
	* test CFormattedCellListBoxData
	*/
	void TestFormattedCellListBoxDataL();
	
	/**
	* test CEikFormattedCellListBox
	*/
	void TestFormattedCellListBoxL();
	
	/**
	* test CColumnListBoxData
	*/
	void TestColumnListBoxDataL();
	
	/**
	* test CEikColumnListBox
	*/
	void TestColumnListBoxL();
	
	/**
	* test CAknSelectionListDialog CAknMarkableListDialog
	*/
	void TestSelectionListDialogL();
	
	/**
	* test AknListBoxLayouts
	*/
	void TestListBoxLayoutsL();
	
	/**
	* test CEikConsoleScreen
	*/
	void TestConsoleScreenL();
	
	/**
	* test CEikCapCArray
	*/
	void TestCapCArrayL();
private: 

// constructor
    
    /**
    * C++ default constructor
    */
    CBCTestMix50ListColumnCase( CBCTestMix50Container* aContainer, 
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
    CEikColumnListBox* iListBox;
    };
/**
 * Test class for protected API of CEikTextListBox
 */    
class CSubEikTextListBox: public CEikTextListBox
    {
public:
	 /**
     * Test WriteInternalStateL
     */
	void TestWriteInternalStateL(RWriteStream& aWriteStream) const;
	 /**
     * Test CreateItemDrawerL
     */
	void TestCreateItemDrawerL();
	
    };
/**
 * Test class for protected API of CTextListBoxModel
 */ 
class CSubTextListBoxModel: public CTextListBoxModel
	{
public:
	/**
     * Test ItemArrayOwnershipType
     */
	TListBoxModelItemArrayOwnership TestItemArrayOwnershipType() const;
	};
/**
 * Test class for protected API of CEikSnakingListBox
 */ 
class CSubEikSnakingListBox: public CEikSnakingListBox
	{
	friend class CBCTestMix50ListColumnCase;
	};
/**
 * Test class for protected API of CEikListBox
 */ 
class CSubEikListBox: public CEikListBox
	{
	friend class CBCTestMix50ListColumnCase;
	};
/**
 * Test class for protected API of CSnakingListBoxView
 */ 
class CSubSnakingListBoxView: public CSnakingListBoxView
	{
	friend class CBCTestMix50ListColumnCase;
	};
/**
 * Test class for protected API of CListBoxView
 */ 
class CSubListBoxView : public CListBoxView
	{
	friend class CBCTestMix50ListColumnCase;
	};
/**
 * Test class for protected API of CTextListItemDrawer
 */ 
class CSubTextListItemDrawer: public CTextListItemDrawer
	{	
	friend class CBCTestMix50ListColumnCase;
public: 
	/**
     * C++ constructor
     */
	CSubTextListItemDrawer(MTextListBoxModel* aTextListBoxModel, 
        const CFont* aFont);
	};
/**
 * Test class for protected API of CListItemDrawer
 */ 
class CSubListItemDrawer: public CListItemDrawer
	{
	friend class CBCTestMix50ListColumnCase;
	};
/**
 * Test class for protected API of CEikListBoxTextEditor
 */ 
class CSubEikListBoxTextEditor: public CEikListBoxTextEditor
    {
	friend class CBCTestMix50ListColumnCase;
public:
		CSubEikListBoxTextEditor(MListBoxModel* aModel);
    };
/**
 * Test class for protected API of CListBoxData
 */ 
class CSubListBoxData: public CListBoxData
	{
	friend class CBCTestMix50ListColumnCase;
public:
	/**
     * add fonts to CListBoxData
     */
	TInt AddActualFontL(const CFont* aBaseFont);
	/**
     * Test CFontWithStyle
     */
	TBool TestCFontWithStyle();
	};
/**
 * Test class for protected API of CAknMarkableListDialog
 */ 
class CSubAknMarkableListDialog: public CAknMarkableListDialog
    {
    friend class CBCTestMix50ListColumnCase;
public:
	/**
     * 2nd constructor
     */
    static CSubAknMarkableListDialog* NewL( TInt &aValue, 
        CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray );
    /**
     * C++ constructor
     */
    CSubAknMarkableListDialog( TInt &aValue, CArrayFix<TInt> *aSelectedItems,
        MDesCArray *aArray, TInt aMenuBarResourceId, 
        TInt aOkMenuBarResourceId, MEikCommandObserver *aObserver );
	};
/**
 * Test class for protected API of CEikConsoleScreen
 */ 
class CSubEikConsoleScreen: public CEikConsoleScreen
	{
	friend class CBCTestMix50ListColumnCase;
	};


#endif /*C_BCTESTMIX50PATCHCOLUMNCASE_H*/
