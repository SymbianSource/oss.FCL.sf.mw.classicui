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
* Description:         test case for aknlistquery
*
*/








#ifndef C_CBCTESTLISTQUERY_H
#define C_CBCTESTLISTQUERY_H

#include <aknlistquerydialog.h>
#include <aknmessagequerydialog.h>

#include "bctestcase.h"

class CEikonEnv;
class CBCTestQueryContainer;

/**
* test case for various list classes
*/
class CBCTestListQuery: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestListQuery* NewL( CBCTestQueryContainer* aContainer, 
        CEikonEnv* aEnv );
    
    /**
    * Destructor
    */
    virtual ~CBCTestListQuery();
    
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
    * Creates the icon and adds it to the array if it was successful
    */
    void CreateIconAndAddToArrayL( CArrayPtr<CGulIcon>*& aIconsArray, 
        const TDesC& aIconFile,
        TInt aBitmap, TInt aMask = -1);
    /**
     * Appends graphics data.
     * @param Pointer of icon using graphics for listbox.
     */
    void GraphicIconL( CArrayPtr<CGulIcon>* aIcons );
    
    /**
    * Test functions
    */    
    void TestListQueryDialogL();    
        
    void TestMessageQueryDialogL();
    
    void TestListQuerySetSizeAndPositionL( TInt aResourceId );
        
private: // constructor
    
    /**
    * C++ default constructor
    */
    CBCTestListQuery(  CBCTestQueryContainer* aContainer,
        CEikonEnv* aEnv );
    
    /**
    * Symbian 2nd constructor
    */
    void ConstructL();
    
private: // data
    
    /**
     * Not Own
     */
   CBCTestQueryContainer* iContainer;
    
    /**
     * Not Own
     */
    CEikonEnv* iEnv;
        
    };
    
/**
 * Test protected API of CAknListQueryDialog
 */
class CBCTestListQueryDialog: public CAknListQueryDialog
    {
    friend class CBCTestListQuery;

public:

// constructor
    
    CBCTestListQueryDialog( TInt* aIndex );
    
    CBCTestListQueryDialog( CListBoxView::CSelectionIndexArray* aSelectionIndexArray );   
    
    }; 
    
/**
 * Test protected API of CAknMessageQueryDialog 
 */
class CBCTestMessageQueryDialog: public CAknMessageQueryDialog
    {
    friend class CBCTestListQuery;
    
public:
    
    CBCTestMessageQueryDialog( const TTone aTone );
    
    };

#endif // C_CBCTESTLISTQUERY_H