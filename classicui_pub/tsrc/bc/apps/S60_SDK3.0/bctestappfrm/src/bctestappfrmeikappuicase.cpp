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









#include <w32std.h>
#include <coecntrl.h>
#include <s32strm.h> 
#include <eikappui.h>
#include <eikenv.h>

#include "bctestappfrmeikappuicase.h"
#include "bctestappfrmcontainer.h"
#include "bctestappfrm.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmEikAppUICase* CBCTestAppFrmEikAppUICase::NewL( 
    CBCTestAppFrmContainer* aContainer )
    {
    CBCTestAppFrmEikAppUICase* self = new( ELeave ) CBCTestAppFrmEikAppUICase( 
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmEikAppUICase::CBCTestAppFrmEikAppUICase( 
    CBCTestAppFrmContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmEikAppUICase::~CBCTestAppFrmEikAppUICase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmEikAppUICase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAppFrmEikAppUICase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmEikAppUICase::BuildScriptL()
    { 
    // Add script as your need.   
       const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, 
        REP(Down, 8),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt)); 
    }
    
// ---------------------------------------------------------------------------
// CBCTestAppFrmEikAppUICase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmEikAppUICase::RunL( TInt aCmd )
    {
    if ( aCmd !=EBCTestEikAppUi)
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    TestFunction();
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmEikAppUICase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmEikAppUICase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestEikAppUi:
            // Here is a simple demo. You should create your control 
            // instead of this.
            iControl = new( ELeave ) CCoeControl();            
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmEikAppUICase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestAppFrmEikAppUICase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmEikAppUICase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestAppFrmEikAppUICase::TestFunction()
    {
    // Test some API here
        TestPublicFunction();
        TestProtectedFunction();  
    }
void CBCTestAppFrmEikAppUICase::TestProtectedFunction()
    {
    CEikAppUi* iEikAppUI = static_cast<CEikAppUi*>
                           ( CEikonEnv::Static()->EikAppUi() );  
    
    iEikAppUI->Application();
    _LIT( KActivateViewL, "CEikAppUi::ActivateViewL() invoked" );
    AssertTrueL( ETrue, KActivateViewL);
    
    iEikAppUI->ApplicationLanguageL();
    _LIT( KApplicationLanguageL, 
    "CEikAppUi::ApplicationLanguageL() invoked" );
    AssertTrueL( ETrue, KApplicationLanguageL );
    
    iEikAppUI->ApplicationRect();
    _LIT( KApplicationRect, "CEikAppUi::ApplicationRect() invoked" );
    AssertTrueL( ETrue, KApplicationRect );

    iEikAppUI->Document();
    _LIT( KDocument, "CEikAppUi::Document()  invoked" );
    AssertTrueL( ETrue, KDocument );   
    
    _LIT( KFileName, "C:\\BCTestLog\\eikappui.txt" );
    iEikAppUI->CreateFileL( KFileName );
    _LIT( KCreateFileL, "CEikAppUi::CreateFileL(const TDesC&) invoked" );
    AssertTrueL( ETrue, KCreateFileL );
     
    iEikAppUI->OpenFileL( KFileName );
    _LIT( KOpenFileL , "CEikAppUi::OpenFileL(const TDesC&) invoked" );
    AssertTrueL( ETrue, KOpenFileL);
      
    TInt iNum = 10;
    iEikAppUI->HandleCommandL( iNum );
    _LIT( KHandleCommandL , "CEikAppUi::HandleCommandL(TInt) invoked" );
    AssertTrueL( ETrue, KHandleCommandL );

    SExtendedError iExtendedError;
    TBuf<16> iErrorText;
    TBuf<16> iContextText;    
    iEikAppUI->HandleError( KErrNone, iExtendedError, iErrorText, iErrorText );
    _LIT( KHandleError ,
    "CEikAppUi::HandleError(TInt,SExtendedError&,TDes&,TDes&) invoked" );
    AssertTrueL( ETrue, KHandleError );

    iEikAppUI->PrepareToExit();
    _LIT( KPrepareToExit , "CEikAppUi::PrepareToExit() invoked" );
    AssertTrueL( ETrue, KPrepareToExit );   
     
    iEikAppUI->HandleModelChangeL();
    _LIT( KHandleModelChangeL , "CEikAppUi::HandleModelChangeL() invoked" );
    AssertTrueL( ETrue, KHandleModelChangeL );   
     
    TInt iType = 2;
    iEikAppUI->HandleResourceChangeL( iType );
    _LIT( KHandleResourceChangeL, 
    "CEikAppUi::HandleResourceChangeL(TInt) invoked" );
    AssertTrueL( ETrue, KHandleResourceChangeL );
    
    TFileName iFileName;
    iEikAppUI->ProcessCommandParametersL( EApaCommandRun, iFileName, KNullDesC8 );
    _LIT( KProcessCommandParametersL,
    "CEikAppUi::ProcessCommandParametersL(TApaCommand,TFileName&,TDesC8&) invoked" );
    AssertTrueL( ETrue, KProcessCommandParametersL );
 
    iEikAppUI->SetDocument( CEikonEnv::Static()->EikAppUi()->Document() );
    _LIT( KSetDocument , "CEikAppUi::SetDocument(CEikDocument* ) invoked" );
    AssertTrueL( ETrue, KSetDocument );   
       
    }
    
void CBCTestAppFrmEikAppUICase::TestPublicFunction()
    {

    }
