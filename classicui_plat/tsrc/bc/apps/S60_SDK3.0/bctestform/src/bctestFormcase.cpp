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
* Description:         bc test case For bctestform application
*
*/









#include <aknnavide.h>
#include <avkon.rsg>
#include <bctestform.rsg>
#include <eikenv.h>
#include <eikappui.h>
#include <eikspane.h>
#include <eikMenuP.h>
#include <avkon.hrh>

#include "bctestFormcase.h"
#include "BCTestForm.hrh"
#include "BCTestFormView.h"
#include "BCTestFormContainer.h"
#include "bctestlogger.h"
#include "autotestcommands.h"


// ---------------------------------------------------------------------------
// dtor, do nothing.
// ---------------------------------------------------------------------------
//
CBCTestFormCase::CBCTestFormCase( CBCTestFormView* aView ):
    iView(aView)
    {
    }

// ---------------------------------------------------------------------------
// dtor, do nothing.
// ---------------------------------------------------------------------------
//
CBCTestFormCase::~CBCTestFormCase()
    {
    }


// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestFormCase::ConstructL()
    {
    ScriptCreateL();
    }
// ---------------------------------------------------------------------------
// symbian NewL
// ---------------------------------------------------------------------------
//
CBCTestFormCase* CBCTestFormCase::NewL( CBCTestFormView* aView )
    {
    CBCTestFormCase* self = CBCTestFormCase::NewLC( aView );
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// symbian NewLC
// ---------------------------------------------------------------------------
//
CBCTestFormCase* CBCTestFormCase::NewLC( CBCTestFormView* aView )
    {
    CBCTestFormCase* self = new ( ELeave ) CBCTestFormCase( aView );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// override from CBCTestCase, response for relative command ID.
// ---------------------------------------------------------------------------
//
void CBCTestFormCase::RunL(int aCmd)
    {
    if( aCmd<EBCTestFormCmdEmptyOutline || aCmd>EBCTestFormCmdOutline06 )
        return;

    SetupL();
    switch(aCmd)
        {
    case EBCTestFormCmdOutline01:
        TryCreateL();
        break;
    case EBCTestFormCmdOutline02:
        TestCreateL();
        break;
    default:
        break;
        }
    TearDownL();

    }

// ---------------------------------------------------------------------------
// build the test scripts
// ---------------------------------------------------------------------------
//
void CBCTestFormCase::ScriptCreateL()
    {
    //
    // method 2: add test script dynamically
    //
    
        AddTestL( LeftCBA, TEND );
        AddTestL( LeftCBA, TEND );
        for(int i = 0;i<4;i++)
        {
            AddTestL( RightCBA, TEND );	
        }
        for(int j=0;j<3;j++)\
        {
            AddTestL( RightCBA, TEND );	
        }
        AddTestL( LeftCBA, TEND );
        AddTestL( LeftCBA, TEND );
        for(int k = 0;k<5;k++)
        {
            AddTestL( LeftCBA, TEND );	
        }
    }

// ---------------------------------------------------------------------------
// test Function for OutLine1
// ---------------------------------------------------------------------------
//
void CBCTestFormCase::TryCreateL()
    {
    _LIT( KConstructL, "Functon ConstructL called" );
    _LIT( KDynInitMenuPaneL, "Functon DynInitMenuPaneL called" );
    _LIT( KProcessCommandL, "Functon ProcessCommandL called" );
    _LIT( KAddItemL, "Function AddItemL is called" );
    _LIT( KDeleteCurrentItemL, "Function DeleteCurrentItemL is called");
    _LIT( KUnsavedEdit, "Function UnsavedEdit is called" );
    _LIT( KDoNotSaveFormDataL, "Function DoNotSaveFormDataL is called" );
    _LIT( KTestQuerySaveChangeL, "Function TestQuerySaveChangeL is called" );
    _LIT( KPostLayoutDynInitL, "Function PostLayoutDynInitL is called" );
    _LIT( KTestSetChangesPending, "Function TestSetChangesPending is called" );
    _LIT( KSetFormFlag, "Function SetFormFlag is called" );
    _LIT( KSaveFormDataL, "Function SaveFormDataL is called" );
    _LIT( KOkToExitL, "Function OkToExitL is called" );
	_LIT( KSetInitialCurrentLine, "Function SetInitialCurrentLine is called" );
	_LIT( KDeleting, "Function Deleting is called" );
	_LIT( KPrepareForFocusTransitionL,
	"Function PrepareForFocusTransitionL is called" );
    _LIT( KTestEditCurrentLabelL, "Function TestEditCurrentLabelL is called" );
    _LIT( KHandlePointerEventL, "Function HandlePointerEventL is called" );
    _LIT( KHandleResourceChange, "Function HandleResourceChange is called" );
    _LIT( KHandleControlStateChangeL, "Function HandleControlStateChangeL is called" );
    
    iForm = new (ELeave) CAknForm;  
    iForm->ConstructL();
    
    AssertTrueL( ETrue, KConstructL );
    iForm->PrepareLC( R_BCTESTFORM_MOVING_THROUGH_LINE_DIALOG );
    CleanupStack::Pop();
    iPane = new ( ELeave ) CEikMenuPane( iForm );
    iPane->ConstructL( iPane, 0 );
    iForm->DynInitMenuPaneL( R_BCTESTFORM_MOVING_THROUGH_LINE_DIALOG, iPane );
    AssertTrueL( ETrue, KDynInitMenuPaneL );
    
    iForm->ProcessCommandL( EAknFormCmdEdit );
    iForm->ProcessCommandL( EAknFormCmdAdd );
    iForm->ProcessCommandL( EAknFormCmdSave );
    iForm->ProcessCommandL( EAknFormCmdLabel );
    iForm->ProcessCommandL( EAknFormCmdDelete );
    AssertTrueL( ETrue, KProcessCommandL );
    
    
    TPointerEvent pointerEvent;
    iForm->HandlePointerEventL( pointerEvent ); 
    AssertTrueL( ETrue, KHandlePointerEventL );
    
    iForm->HandleResourceChange( 1 );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    iAknFormTest = new ( ELeave ) CBCTestFormAdd;
    iAknFormTest->ConstructL();
    iAknFormTest->PrepareLC( R_BCTESTFORM_MOVING_THROUGH_LINE_DIALOG );
    CleanupStack::Pop();
    
    iAknFormTest->TestAddItemL();
	AssertTrueL( ETrue, KAddItemL );
	 
    iAknFormTest->TestDeleteCurrentItemL();
	AssertTrueL( ETrue, KDeleteCurrentItemL );

    iAknFormTest->TestUnsavedEdit();
	AssertTrueL( ETrue, KUnsavedEdit );
    
    iAknFormTest->TestDoNotSaveFormDataL();
	AssertTrueL( ETrue, KDoNotSaveFormDataL );
	
    iAknFormTest->TestQuerySaveChangeL();
    AssertTrueL( ETrue, KTestQuerySaveChangeL );
    
    iAknFormTest->TestPostLayoutDynInitL();
	AssertTrueL( ETrue, KPostLayoutDynInitL );
	
	iAknFormTest->TestSetChangesPending();
	AssertTrueL( ETrue, KTestSetChangesPending );
	
	iAknFormTest->TestSetFormFlag();
	AssertTrueL( ETrue, KSetFormFlag );	
			
    iAknFormTest->TestSaveFormDataL();
	AssertTrueL( ETrue, KSaveFormDataL );	
	
	iAknFormTest->TestOkToExitL();
	AssertTrueL( ETrue, KOkToExitL );
		
    iAknFormTest->TestSetInitialCurrentLine();
	AssertTrueL( ETrue, KSetInitialCurrentLine );
	
    iAknFormTest->TestDeleting();
	AssertTrueL( ETrue, KDeleting );	
	
    iAknFormTest->TestPrepareForFocusTransitionL();
	AssertTrueL( ETrue, KPrepareForFocusTransitionL );
	
	iAknFormTest->TestEditCurrentLabelL();
    AssertTrueL( ETrue, KTestEditCurrentLabelL );  
    AssertTrueL( ETrue, KHandleControlStateChangeL );  
    
    
    delete iAknFormTest;
    iAknFormTest = NULL;
    delete iPane;
    iPane = NULL;
    delete iForm; 
    iForm=NULL;
    }


// ---------------------------------------------------------------------------
// test Function for OutLine2
// ---------------------------------------------------------------------------
//
void CBCTestFormCase::TestCreateL()
    {
    }
    
// ---------------------------------------------------------------------------
// getter of the container
// ---------------------------------------------------------------------------
//
CBCTestFormContainer*  CBCTestFormCase::Container()  const
    { 
    return iView->Container(); 
    }

// ---------------------------------------------------------------------------
// do necessary setup jobs.
// ---------------------------------------------------------------------------
//
void CBCTestFormCase::SetupL()
    {
    }

// ---------------------------------------------------------------------------
// do release jobs.
// ---------------------------------------------------------------------------
//
void CBCTestFormCase::TearDownL()
    {
    }


// ---------------------------------------------------------------------------
// dtor, do nothing.
// ---------------------------------------------------------------------------
//
CBCTestFormAdd::CBCTestFormAdd()
    {
    }

// Destructor
// ---------------------------------------------------------------------------
// dtor, do nothing.
// ---------------------------------------------------------------------------
//
CBCTestFormAdd::~CBCTestFormAdd()
    {
    }

// ---------------------------------------------------------------------------
// test Function AddItemL
// ---------------------------------------------------------------------------
//
void CBCTestFormAdd::TestAddItemL()
    {	
    AddItemL();
    }

// ---------------------------------------------------------------------------
// test Function SaveFormDataL
// ---------------------------------------------------------------------------
//    
void CBCTestFormAdd::TestSaveFormDataL()
    {
    SaveFormDataL();
    }

// ---------------------------------------------------------------------------
// test Function DoNotSaveFormDataL
// ---------------------------------------------------------------------------
//     
void CBCTestFormAdd::TestDoNotSaveFormDataL()
    {
    DoNotSaveFormDataL();
    }

// ---------------------------------------------------------------------------
// test Function Deleting
// ---------------------------------------------------------------------------
//    
TBool CBCTestFormAdd::TestDeleting()
    {
    TBool iDeleting;
	iDeleting = Deleting();
	return iDeleting;
    }
// ---------------------------------------------------------------------------
// test Function UnsavedEdit
// ---------------------------------------------------------------------------
//     
void CBCTestFormAdd::TestUnsavedEdit()
    {
	UnsavedEdit();
    }
// ---------------------------------------------------------------------------
// test Function EditCurrentLabelL
// ---------------------------------------------------------------------------
//    
void CBCTestFormAdd::TestEditCurrentLabelL()
    {
    EditCurrentLabelL();
    }
// ---------------------------------------------------------------------------
// test Function QuerySaveChangeL
// ---------------------------------------------------------------------------
//      
TBool CBCTestFormAdd::TestQuerySaveChangeL()
    {
    TBool iQuerySaveChangeL;
    iQuerySaveChangeL = QuerySaveChangesL();
    return iQuerySaveChangeL;
    }
// ---------------------------------------------------------------------------
// test Function PrepareForFocusTransitionL
// ---------------------------------------------------------------------------
//      
void CBCTestFormAdd::TestPrepareForFocusTransitionL()
    {
    PrepareForFocusTransitionL();
    } 
// ---------------------------------------------------------------------------
// test Function PostLayoutDynInitL
// ---------------------------------------------------------------------------
//    
void CBCTestFormAdd::TestPostLayoutDynInitL()
    {
    PostLayoutDynInitL();
    }    
// ---------------------------------------------------------------------------
// test Function DeleteCurrentItemL
// ---------------------------------------------------------------------------
//    
void CBCTestFormAdd::TestDeleteCurrentItemL()
    {
    DeleteCurrentItemL();
    }
// ---------------------------------------------------------------------------
// test Function SetInitialCurrentLine
// ---------------------------------------------------------------------------
//        
void CBCTestFormAdd::TestSetInitialCurrentLine()
    {
    SetInitialCurrentLine();
    }
// ---------------------------------------------------------------------------
// test Function SetChangesPending
// ---------------------------------------------------------------------------
//       
void CBCTestFormAdd::TestSetChangesPending()
    {
    SetChangesPending( EFalse );
    }  
// ---------------------------------------------------------------------------
// test Function SetFormFlag
// ---------------------------------------------------------------------------
//                
void CBCTestFormAdd::TestSetFormFlag()
    {
    SetFormFlag( EDeleting, ETrue );
    SetFormFlag( EDeleting, EFalse );
    }
// ---------------------------------------------------------------------------
// test Function OkToExitL
// ---------------------------------------------------------------------------
//                   
void CBCTestFormAdd::TestOkToExitL()
    {
    OkToExitL( EAknSoftkeyOptions );
    SetEditableL( ETrue );
    OkToExitL( EAknSoftkeyBack );
    
    HandleControlStateChangeL( 1 );
    }
