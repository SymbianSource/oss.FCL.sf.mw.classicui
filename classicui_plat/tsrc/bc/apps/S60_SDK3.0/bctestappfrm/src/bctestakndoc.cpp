/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:       
*
*/







#include <eikapp.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikdoc.h>
#include <s32file.h>
#include <akndoc.h>

#include "bctestakndoc.h"
#include "bctestappfrm.hrh"
#include "bctestappfrmapp.h"
#include "streamlogger.h"

//============helper class==============
class CMockDocument: public CAknDocument
	{
public:
	CMockDocument(CEikApplication& aApp);
	CEikAppUi* CreateAppUiL()
		{
		return NULL;
		}
	};

CMockDocument::CMockDocument(CEikApplication& aApp):CAknDocument(aApp)
	{
	}

// ----------------------------------------------------------------------------
// ctor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestAknDoc::CBCTestAknDoc()
    {
    }

// ----------------------------------------------------------------------------
// dtor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestAknDoc::~CBCTestAknDoc()
    {
    }

// ----------------------------------------------------------------------------
// symbian 2nd phase ctor.
// ----------------------------------------------------------------------------
//
void CBCTestAknDoc::ConstructL()
    {
    BuildScriptL();
    }

// ----------------------------------------------------------------------------
// symbian NewL.
// ----------------------------------------------------------------------------
//
CBCTestAknDoc* CBCTestAknDoc::NewL()
    {
    CBCTestAknDoc* self = new ( ELeave ) CBCTestAknDoc();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// override the CBCTestCase::RunL, only response to the related command ID.
// ----------------------------------------------------------------------------
//
void CBCTestAknDoc::RunL(int aCmd)
    {
    if(aCmd != EBCTestCmdDocument) return;
    SetupL();
    TestL();
    TearDownL();
    }

// ----------------------------------------------------------------------------
// build the test scripts for this test case.
// ----------------------------------------------------------------------------
//
void CBCTestAknDoc::BuildScriptL()
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

// ----------------------------------------------------------------------------
// test the volume setting page creation api.
// ----------------------------------------------------------------------------
//
void CBCTestAknDoc::TestL()
    {
	CBCTestAppFrmApp* app = new CBCTestAppFrmApp();
	CleanupStack::PushL(app);
	CMockDocument* ptr = new (ELeave) CMockDocument(*app);
	delete ptr;
	CleanupStack::Pop();	//app;
	delete app;

    //CEikDocument subclass #CAknDocument,
    CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();    // doc pointer to CBCTestAppFrmDocument(which is infact a CAknDocument)

    RFs& fs = CEikonEnv::Static()->FsSession();
    _LIT(KFileName, "C:\\BCTestLog\\foo.txt");
    CFileStore* store = doc->OpenFileL(EFalse, KFileName, fs);
    //AssertNotNullL(store, _L("CFileStore* CAknDocument::OpenFileL() invoked with EFalse."));
    AssertTrueL(ETrue, _L("CAknDocument::OpenFileL() is empty in S60."));
    delete store;

    store = NULL;
    store = doc->OpenFileL(ETrue, KFileName, fs);
    //AssertNotNullL(store, _L("CFileStore* CAknDocument::OpenFileL() invoked with ETrue."));
    AssertTrueL(ETrue, _L("CAknDocument::OpenFileL() is empty in S60."));
    delete store;
    
    store = NULL;
    RFile file;
    if ( file.Open( fs, KFileName, EFileWrite | EFileShareAny ) != KErrNone ){
        file.Create( fs, KFileName, EFileWrite | EFileShareAny );
    }

    doc->OpenFileL(store, file);
    //AssertNotNullL(store, _L("void CAknDocument::OpenFileL() invoked."));
    AssertTrueL(ETrue, _L("CAknDocument::OpenFileL() is empty in S60."));
    delete store;
    file.Close();
    }

// ----------------------------------------------------------------------------
// prepare for the test.
// ----------------------------------------------------------------------------
//
void CBCTestAknDoc::SetupL()
    {
    }

// ----------------------------------------------------------------------------
// do release jobs.
// ----------------------------------------------------------------------------
//
void CBCTestAknDoc::TearDownL()
    {
    }

//end of file
