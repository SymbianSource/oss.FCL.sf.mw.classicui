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
#include <eikembal.h>
#include <eikappui.h>
#include <s32file.h>
#include <eikdoc.h>
#include <apaid.h>
#include <eikproc.h>

#include "bctestapplist.h"
#include "bctesteikfrm.hrh"
#include "bctesteikfrmapp.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestAppList* CBCTestAppList::NewL()
    {
    CBCTestAppList* self = new( ELeave ) CBCTestAppList();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestAppList::CBCTestAppList()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestAppList::~CBCTestAppList()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestAppList::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAppList::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestAppList::BuildScriptL()
    { 
    const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, 
		REP(Down, 3),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }
    
// ---------------------------------------------------------------------------
// CBCTestAppList::RunL
// ---------------------------------------------------------------------------
//
void CBCTestAppList::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdEikAppList )
        {
        return;
        }
    
    TestFunctionL();
    }

// ---------------------------------------------------------------------------
// CBCTestAppList::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestAppList::TestFunctionL()
    {
	CEikEmbeddableAppList* list = new (ELeave) CEikEmbeddableAppList;
	CleanupStack::PushL(list);
	AssertNotNullL( list, _L("CEikEmbeddableAppList ctor invoked"));

	list->ConstructL();
	AssertTrueL( ETrue, _L("CEikEmbeddableAppList symbian 2nd ctor invoked"));

	CleanupStack::PopAndDestroy(); //list

	list = new (ELeave) CEikEmbeddableAppList;
	CleanupStack::PushL(list);
	TApaEmbeddabilityFilter filter;
	filter.AddEmbeddability(TApaAppCapability::ENotEmbeddable);
	list->ConstructL(filter);
	AssertTrueL( ETrue, _L("CEikEmbeddableAppList symbian 2nd ctor with filter invoked"));

	CApaProcess* proc = CEikonEnv::Static()->Process();
	CEikDocument* doc = NULL;
	TRAPD(err,  doc = list->CreateEmbeddedDocumentL(0, proc));
	if(err == KErrNotFound){
		AssertTrueL( ETrue, _L("CreateEmbeddedDocumentL leave because not found"));
	}
	else{
		CleanupStack::PushL(doc);
		AssertNotNullL( doc, _L("CreateEmbeddedDocumentL invoked"));
		CleanupStack::PopAndDestroy();	//doc
	}


	CleanupStack::PopAndDestroy(); //list
    }

