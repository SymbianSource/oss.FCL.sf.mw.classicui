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
#include <eikenv.h>
#include <ptiuserdictionary.h>

#include "BCTestUserDict.h"
#include "BCTestPtiEngcontainer.h"
#include "BCTestPtiEng.hrh"

const TInt KMaxSize = 32;
_LIT(KFileName, "C:\\BCTestLog\\TestUserDict.txt");

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestUserDict* CBCTestUserDict::NewL( 
    CBCTestPtiEngContainer* aContainer )
    {
    CBCTestUserDict* self = new( ELeave ) CBCTestUserDict( 
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
CBCTestUserDict::CBCTestUserDict( 
    CBCTestPtiEngContainer* aContainer )
    : iContainer( aContainer ), iDict(NULL)
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestUserDict::~CBCTestUserDict()
    {  
	Reset();
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestUserDict::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestUserDict::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestUserDict::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestUserDict::RunL
// ---------------------------------------------------------------------------
//
void CBCTestUserDict::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdPtiUserDict)
        {
        return;
        }
    
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    TestFunctionL();
    }

// ---------------------------------------------------------------------------
// CBCTestUserDict::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestUserDict::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdPtiUserDict:
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
// CBCTestUserDict::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestUserDict::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestUserDict::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestUserDict::TestFunctionL()
    {
    TestCreateL();
	TestSetDataL();
	TestSaveDataL();
	TestReloadL();
    }
    
void CBCTestUserDict::TestCreateL()
	{
	iDict = CPtiUserDictionary::NewL(KMaxSize);
	AssertNotNullL(iDict, _L("CPtiUserDictionary::NewL(iMax) create"));
	}

void CBCTestUserDict::TestSetDataL()
	{
	TUint8 data[] = {'h', 'e', 'l', 'l', 'o'};
	TInt size = sizeof(data)/sizeof(TUint8);
	iDict->SetDataL(
		static_cast<TAny*>(data), 
		size);
	AssertTrueL(ETrue, _L("CPtiUserDictionary::SetDataL() invoked"));

	AssertTrueL( iDict->SpaceLeft() == -1, _L("SpaceLeft() always returns -1"));
	}

void CBCTestUserDict::TestSaveDataL()
	{
	TBuf<KMaxFileName> filename(KFileName);
	iDict->SetFileName(filename);

	RFs& fs = CEikonEnv::Static()->FsSession();
	RFile file;
	if ( file.Open( fs, filename, EFileWrite | EFileShareAny ) != KErrNone )
		{
		file.Create( fs, filename, EFileWrite | EFileShareAny );
		}
		
	file.Close();

	AssertTrueL(KErrNone == iDict->WriteL(), _L("WriteL called WriteL(filename)"));
	}

void CBCTestUserDict::TestReloadL()
	{
	Reset();
	TBuf<KMaxFileName> filename(KFileName);
	iDict = CPtiUserDictionary::NewL(filename, KMaxSize);

	AssertNotNullL(iDict, _L("reload by NewL(filename, iMax)"));
	}

void CBCTestUserDict::Reset()
	{
	delete iDict;
	iDict = NULL;
	}

// End of file
