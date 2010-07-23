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








#include <eikdoc.h>
#include <eikenv.h>
#include <eikappui.h>
#include <w32std.h>
#include <coecntrl.h>
#include <s32file.h>

#include "bctesteikdoc.h"
#include "bctesteikfrm.hrh"
#include "bctesteikfrmapp.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEikDoc* CBCTestEikDoc::NewL()
    {
    CBCTestEikDoc* self = new( ELeave ) CBCTestEikDoc();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestEikDoc::CBCTestEikDoc()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEikDoc::~CBCTestEikDoc()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEikDoc::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikDoc::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEikDoc::BuildScriptL()
    { 
    const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, 
		REP(Down, 1),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }
    
// ---------------------------------------------------------------------------
// CBCTestEikDoc::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEikDoc::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdEikDoc )
        {
        return;
        }
    
    TestFunctionL();
    }

// ---------------------------------------------------------------------------
// CBCTestEikDoc::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestEikDoc::TestFunctionL()
    {
	TestFileL();
	TestPropertyL();
	TestOpsL();
    }

void CBCTestEikDoc::TestFileL()
	{
    CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();

	RFs& fs = CEikonEnv::Static()->FsSession();
	_LIT(KFileName, "C:\\BCTestLog\\foo.txt");
	CFileStore* store = doc->OpenFileL(EFalse, KFileName, fs);
    AssertNotNullL(store, _L("CFileStore* CAknDocument::OpenFileL() invoked with EFalse."));
	delete store;

	store = NULL;
	store = doc->OpenFileL(ETrue, KFileName, fs);
	AssertNotNullL(store, _L("CFileStore* CAknDocument::OpenFileL() invoked with ETrue."));
	delete store;
	
    store = NULL;
	RFile file;
	if ( file.Open( fs, KFileName, EFileWrite | EFileShareAny ) != KErrNone ){
		file.Create( fs, KFileName, EFileWrite | EFileShareAny );
	}

	doc->OpenFileL(store, file);
	AssertNotNullL(store, _L("void CAknDocument::OpenFileL() invoked."));
	delete store;
	file.Close();

	CStreamStore* strm = doc->EditStore();
	AssertNotNullL(strm, _L("StreamStore got"));
	doc->SetEditStoreL(strm);
	AssertTrueL( ETrue, _L("StreamStore set"));

	store = doc->CreateFileStoreLC(fs, KFileName);
	AssertNotNullL( store, _L("file store created"));
	CleanupStack::PopAndDestroy();
	}

void CBCTestEikDoc::TestOpsL()
{
    CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();
	doc->NewDocumentL();
	AssertTrueL( ETrue, _L("NewDocument() OK"));

	doc->ValidatePasswordL();
	AssertTrueL( ETrue, _L("password validated"));

	class CMonkObserver: public CBase, public MApaEmbeddedDocObserver
	{
	public:
		void NotifyExit(TExitMode /*aMode*/){}
	};
	/*
	*not supported for non-embbed app
	MApaEmbeddedDocObserver* observer = new (ELeave) CMonkObserver;
	CleanupStack::PushL(observer);
	TRAPD( err, doc->EditL(observer));
	if( err == KErrNotSupported ){
		AssertTrueL( ETrue, _L("EditL not supported for non-embedded app"));
	}
	CleanupStack::PopAndDestroy();	//observer
	*/
	AssertTrueL( ETrue, _L("EditL & PrepareEditL are not supported for non-embedded app"));

	CStreamStore* strm = doc->EditStore();
	doc->PrintL(*strm);
	AssertTrueL( ETrue, _L("PrintL is empty"));

	doc->SaveL();
	AssertTrueL( ETrue, _L("SaveL() invoked"));

	CStreamDictionary* dict = CStreamDictionary::NewLC();

	doc->StoreL(*strm, *dict);
	AssertTrueL( ETrue, _L("store"));

	doc->RestoreL(*strm, *dict);
	AssertTrueL( ETrue, _L("Restore"));

	CleanupStack::PopAndDestroy();	//dict
}

void CBCTestEikDoc::TestPropertyL(){
	CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();

	//caption
	TApaAppCaption caption = doc->AppCaption();
    _LIT(KCaption, "CEikDocument::AppCaption");	
	AssertTrueL(ETrue, KCaption );	

	//empty
	AssertTrueL( doc->IsEmpty(), _L("Alway Empity for EikDoc::IsEmpity()"));

	//changed
	doc->SetChanged(ETrue);
	AssertTrueL( doc->HasChanged(), _L("Doc has changed"));

	doc->SetChanged(EFalse);
	AssertTrueL( !doc->HasChanged(), _L("Doc hasn't changed"));

	//file mode
	doc->SetAppFileMode(EFileRead);
	AssertTrueL( EFileRead == doc->AppFileMode(), _L("FileMode confirmed"));
}
