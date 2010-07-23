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








#include <eikapp.h>
#include <eikenv.h>
#include <eikappui.h>
#include <w32std.h>
#include <coecntrl.h>
#include <s32file.h>

#include "bctesteikfrmcase.h"
#include "bctesteikfrmcontainer.h"
#include "bctesteikfrm.hrh"
#include "bctesteikfrmapp.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEikFrmCase* CBCTestEikFrmCase::NewL( 
    CBCTestEikFrmContainer* aContainer )
    {
    CBCTestEikFrmCase* self = new( ELeave ) CBCTestEikFrmCase( 
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
CBCTestEikFrmCase::CBCTestEikFrmCase( 
    CBCTestEikFrmContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEikFrmCase::~CBCTestEikFrmCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEikFrmCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikFrmCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEikFrmCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikFrmCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEikFrmCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdEikApp )
        {
        return;
        }
    
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    TestFunction();
    }

// ---------------------------------------------------------------------------
// CBCTestEikFrmCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestEikFrmCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdEikApp:
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
// CBCTestEikFrmCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestEikFrmCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestEikFrmCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestEikFrmCase::TestFunction()
    {
	CEikApplication* app = static_cast<CEikApplication*>(CEikonEnv::Static()->EikAppUi()->Application());
    TFileName filename = app->BitmapStoreName();
    filename = filename.Right(filename.Length()-3 );
    filename.LowerCase();
    _LIT(KBmpFile, "resource\\apps\\bctesteikfrm.mbm");
	AssertTrueL( filename == KBmpFile, _L("CEikApplication::BitmapStoreName() invoked"));
	
	TBuf8<256> cap;
	app->Capability(cap);
	AssertTrueL( ETrue, _L("CEikApplication::Capability() got"));
	app->GetDefaultDocumentFileName(filename);
    filename.LowerCase();
    _LIT(KDocFile, "bctesteikfrm");
	AssertTrueL( filename == KDocFile, _L("CEikApplication::GetDefaultDocumentFileName() invoked"));

	filename = app->ResourceFileName();
	filename = filename.Right(filename.Length()-3 );
    filename.LowerCase();
	_LIT(KResFile, "resource\\apps\\bctesteikfrm.r01");
	AssertTrueL( filename == KResFile, _L("CEikApplication::ResourceFileName() invoked") );

	TParse parse;
	app->SetToIniFileNameL(parse);
	AssertTrueL( ETrue, _L("CEikApplication::SetToIniFileNameL() parse got"));

	RFs& fs = CEikonEnv::Static()->FsSession();
	CDictionaryStore* store = app->OpenIniFileLC(fs);
	AssertTrueL( ETrue, _L("CEikApplication::OpenIniFileLC() ini file opened"));
	CleanupStack::PopAndDestroy();

	//CApaAppServer* server = NULL;
	//static_cast<CBCTestEikFrmApp*>(app)->NewAppServerL(server);
	//CleanupStack::PushL(server);
	//AssertNotNullL(server, _L("CEikApplication::NewAppServerL() invoked."));
	//CleanupStack::PopAndDestroy(server);	//server
    }
    
