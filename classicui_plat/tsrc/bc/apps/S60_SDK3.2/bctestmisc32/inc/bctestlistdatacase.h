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









#ifndef C_BCTESTLISTDATACASE_H
#define C_BCTESTLISTDATACASE_H


#include "bctestcase.h"

class CBCTestmisc32Container;
class CCoeControl;
class CEikFormattedCellListBox;
class CEikColumnListBox;

class CFormattedCellListBoxData;
class CColumnListBoxData;

const TInt KBCTestList32DefaultFlag = 0;
/**
* test case for various list classes
*/
class CBCTestListDataCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestListDataCase* NewL( CBCTestmisc32Container* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestListDataCase();
    
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
     * Test CFormattedCellListBoxData
     */
    void TestFmtLongTextWasClippedL();

    /**
     * Test CFormattedCellListBoxData
     */
    void TestFmtShortTextWasClippedL();

    /**
     * Test CColumnListBoxData
     */
    void TestColLongTextWasClippedL();

    /**
     * Test CColumnListBoxData
     */
    void TestColShortTextWasClippedL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestListDataCase( CBCTestmisc32Container* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
    // new functions
    /**
    * Sets listbox from resource using ConstructFromResourceL() of
    * CEikColumnListBox class.
    * @param aListBox Pointer of listbox.
    * @param aResourceId Resource ID of listbox.
    */
    void SetListBoxFromResourceL( CEikColumnListBox* aListBox,
                                  const TInt aResourceId );
    
    /**
    * Sets listbox from resource using ConstructFromResourceL() of
    * CEikFormattedCellListBox class.
    * @param aListBox Pointer of listbox.
    * @param aResourceId Resource ID of listbox.
    */
    void SetListBoxFromResourceL( CEikFormattedCellListBox* aListBox,
                                  const TInt aResourceId );
                                  

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
    CBCTestmisc32Container* iContainer;
    
    /**
     * own
     */
    CEikFormattedCellListBox* iFormattedListBox;

    /**
     * own
     */
    CEikColumnListBox* iColumnListBox; 

    /**
     * not own
     */    
    CEikonEnv* iEikEnv;
    };

#endif // C_BCTESTLISTDATACASE_H