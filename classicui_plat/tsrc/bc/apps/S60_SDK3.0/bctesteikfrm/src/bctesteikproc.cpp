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








#include <eikenv.h>
#include <eikproc.h>
#include <eikappui.h>
#include <s32file.h>
#include <eikdoc.h>

#include "bctesteikproc.h"
#include "bctesteikfrm.hrh"
#include "bctesteikfrmapp.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEikProc* CBCTestEikProc::NewL()
    {
    CBCTestEikProc* self = new( ELeave ) CBCTestEikProc();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestEikProc::CBCTestEikProc()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEikProc::~CBCTestEikProc()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEikProc::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikProc::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEikProc::BuildScriptL()
    { 
    const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, 
		REP(Down, 2),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikProc::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEikProc::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdEikProc )
        {
        return;
        }
    
    TestFunctionL();
    }

// ---------------------------------------------------------------------------
// CBCTestEikProc::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestEikProc::TestFunctionL()
    {
	TestFileL();
	TestOpsL();
    }

void CBCTestEikProc::TestFileL()
{
	CEikProcess* proc = CEikonEnv::Static()->Process();

	// main store
    CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();
	CFileStore* store = proc->MainStore();
	AssertNotNullL( store , _L("main store got"));
    proc->SetMainStore(store);
	AssertTrueL( ETrue , _L("main store set"));
	
	// save
	_LIT(KFileName, "C:\\BCTestLog\\foo.txt");
	TFileName newname(KFileName);

	{
		TRAPD( err, proc->SaveToDirectFileStoreL(doc));
		HandleErrL(err);
	}
	
	{
		TRAPD(err, proc->SaveToDirectFileStoreL(doc, &newname));
		HandleErrL(err);
	}
	
	{
		TRAPD( err, proc->SaveToDirectFileStoreL(doc, &newname, ETrue));
		HandleErrL(err);
	}
	
	{
		TRAPD(err, proc->SaveToDirectFileStoreL(doc, &newname, EFalse));
		HandleErrL(err);
	}
	
	_LIT(KTempFile, "C:\\BCTestLog\\temp.txt");
	TFileName tempname(KTempFile);
	{
		TRAPD(err, proc->SaveToDirectFileStoreL(doc, &newname, ETrue, &tempname));
		HandleErrL(err);
	}
	
	{
		TRAPD(err, proc->SaveToDirectFileStoreL(doc, &newname, EFalse, &tempname));
		HandleErrL(err);
	}
}

void CBCTestEikProc::HandleErrL(TInt err){
	if( err == KErrAlreadyExists ){
		AssertTrueL( ETrue, _L("save to direct file store already exist"));
	}
	else{
		AssertTrueL( ETrue, _L("save to direct file store invoked"));
	}
}

void CBCTestEikProc::TestOpsL()
{
	CEikProcess* proc = CEikonEnv::Static()->Process();

	// lib name
	TFileName docname, libname;
	CEikonEnv::Static()->EikAppUi()->Application()->GetDefaultDocumentFileName(docname);
	TRAPD( err, proc->AppFromDocL(libname, docname));
	if( err == KErrCorrupt ){
		AssertTrueL( ETrue, _L("AppFromDocL() fail: UID2 is not KUidAppDllDoc"));
	}
	else{
		AssertTrueL( ETrue, _L("AppFromDocL() return lib name"));
	}

	// command tail end
	TPtrC ptr = proc->CommandTailEnd();
	AssertTrueL( ETrue, _L("CommandTailEnd() invoked") );

	// last used file
	_LIT(KFileName, "C:\\BCTestLog\\foo.txt");
	proc->SetLastUsedFileL(CEikProcess::ELastCreatedFile, KFileName);
	docname = proc->LastUsedFileL(CEikProcess::ELastCreatedFile);
	AssertTrueL( docname == KFileName, _L("last used file got"));

	// main doc folder
	TFileName folder = proc->MainDocFolder();
	AssertTrueL( ETrue, _L("main doc folder got") );
}
