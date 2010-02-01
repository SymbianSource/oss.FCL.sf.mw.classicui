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
* Description:         test bc of the form control API(s)
*
*/









#include <aknview.h>
#include <eikdialg.h>
#include <aknform.h>

#include "bctestcase.h"

/**
* test class for aknform control in test case.
*/
class CBCTestFormAdd : public CAknForm
    {
    public: // Constructor and Detructor
        /**
        * Default constructor.
        */
        CBCTestFormAdd();

        /**
        * Destructor.
        */
        virtual ~CBCTestFormAdd();
        /**
        * test function AddItemL
        */
	    void TestAddItemL();
        /**
        * test function SaveFormDataL
        */
	    void TestSaveFormDataL();
        /**
        * test function DoNotSaveFormDataL
        */
	    void TestDoNotSaveFormDataL();
        /**
        * test function Deleting
        */
	    TBool TestDeleting();
        /**
        * test function UnsavedEdit
        */
	    void TestUnsavedEdit();
        /**
        * test function EditCurrentLabelL
        */
	    void TestEditCurrentLabelL();
        /**
        * test function QuerySaveChangeL
        */
        TBool TestQuerySaveChangeL();
        /**
        * test function PrepareForFocusTransitionL
        */
        void TestPrepareForFocusTransitionL();
        /**
        * test function PostLayoutDynInitL
        */
        void TestPostLayoutDynInitL();
        /**
        * test function SetInitialCurrentLine
        */
        void TestSetInitialCurrentLine();
        /**
        * test function SetChangesPending
        */
        void TestSetChangesPending();
        /**
        * test function SetFormFlag
        */
        void TestSetFormFlag();
        /**
        * test function OkToExitL
        */
        void TestOkToExitL();
        /**
        * test function DeleteCurrentItemL
        */
        void TestDeleteCurrentItemL();
    protected:

    private:
        // In order to prevent adding controls which ID is the same.
       // TInt iNewItemId;
    };
/**
* test case for aknform
*/
class CBCTestFormView;
class CBCTestFormContainer;
class CAknForm;
class CEikMenuPane;

class CBCTestFormCase: public CBCTestCase
	{
	public:        
	    static CBCTestFormCase* NewL( CBCTestFormView* aView );
	    static CBCTestFormCase* NewLC( CBCTestFormView* aView );
	    virtual ~CBCTestFormCase();
        
	    virtual void RunL(int aCmd);    //from CBCTestCase
	    
	    
	protected: // new
	    virtual void TearDownL();
        /**
        * do necessary setup things.
        */
        virtual void SetupL();

	    
	    CBCTestFormCase( CBCTestFormView* aView );
	    void ConstructL();

	private:
	    void ScriptCreateL();
        /**
        * test Function for OutLine2
        */
	    void TestCreateL();

        /**
        * test Function for OutLine1
        */
	    void TryCreateL();
	    
	    CBCTestFormContainer*  Container()  const;
	    
	private: // Data
	    CBCTestFormView * iView;       // not own, just reference
	    CAknForm * iForm;     // own
	    CEikMenuPane * iPane;
	    CBCTestFormAdd *iAknFormTest;
	};

