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
* Description:         test case for grid pane list box classes
*
*/








#ifndef C_CBCTESTLISTCOLUMNBASECASE_H
#define C_CBCTESTLISTCOLUMNBASECASE_H

#include <eikclbd.h>

#include "bctestlistbasecase.h"

class CEikonEnv;
class CEikColumnListBox;
class CBCTestListContainer;
class CBCTestColumnListBoxData;

/**
 * Fake observer class for test
 */
class TBCTestListBoxAnimBgDrawer: public MColumnListBoxAnimBackgroundDrawer
    {
public:

    TBool DrawHighlightAnimBackground( CFbsBitGc& aGc ) const;
    
    };

/**
* test case for various list classes
*/
class CBCTestListColumnBaseCase: public CBCTestListBaseCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestListColumnBaseCase* NewL( 
        CBCTestListContainer* aContainer, CEikonEnv* aEikEnv );
    
    /**
    * Destructor
    */
    virtual ~CBCTestListColumnBaseCase();
    
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
    * Test CEikColumnListBox
    */
    void TestColumnListL();
    
    /**
    * Test CColumnListBoxItemDrawer and CEikColumnListBoxEditor
    */
    void TestColumnItemDrawerAndEditorL();
    
    /**
     * Test CColumnListBoxData
     */
    void TestColumnListDataL();
        
private: // constructor
    
    /**
    * C++ default constructor
    */
    CBCTestListColumnBaseCase( CBCTestListContainer* aContainer, 
        CEikonEnv* aEikEnv );
    
    /**
    * Symbian 2nd constructor
    */
    void ConstructL();
    
private: // data
    
    /**
     * Own
     */
    CEikColumnListBox* iListBox; 
    
    TBCTestListBoxAnimBgDrawer iDrawer;
    
    /**
     * Own
     */
    CBCTestColumnListBoxData* iBCData;   
    
    };
    
/**
 * Class for testing protected API of CColumnListBoxData
 */
class CBCTestColumnListBoxData: public CColumnListBoxData
    {
public: // constructor and destructor
    
    /**
     * C++ default constructor
     */
    CBCTestColumnListBoxData();
    
    /**
     * C++ default constructor
     */
    ~CBCTestColumnListBoxData();
    
public: 

// new fuctions

    /**
     * Test ConsturctLD
     */    
    void TestConstructLD( const TAknsItemID& aAnimationIID );
    
    /**
     * Test DrawText
     */
    void TestDrawText( CWindowGc& aGc, const TRect& aTextRect, 
        const TDesC& aText, const TDesC& aClippedText, 
        const TInt aBaselineOffset, 
        const CGraphicsContext::TTextAlign aAlign, 
        const CFont& aFont, const TBool aHighlight, 
        const TBool aIsTextClipped );
    
    };

/**
 * Class for test protected API of CEikColumnListBoxEditor
 */    
class CBCTestColumnListBoxEditor: public CEikColumnListBoxEditor
    {
    friend class CBCTestListColumnBaseCase;

public:
        
    CBCTestColumnListBoxEditor( MListBoxModel* aModel );
    
    };
    
#endif // C_CBCTESTLISTCOLUMNBASECASE_H