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
#include <ptilanguagedatabase.h>
#include <ptiuids.hrh>

#include "BCTestLanDB.h"
#include "BCTestPtiEngcontainer.h"
#include "BCTestPtiEng.hrh"
#include "bctestqwertymap.h"
#include "bctestkeymap.h"
#include "streamlogger.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestLanDB* CBCTestLanDB::NewL()
    {
    CBCTestLanDB* self = new( ELeave ) CBCTestLanDB();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestLanDB::CBCTestLanDB():iDB(NULL)
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestLanDB::~CBCTestLanDB()
    {
    Teardown();
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestLanDB::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestLanDB::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestLanDB::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, 
        REP(Down, 4),
        KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestLanDB::RunL
// ---------------------------------------------------------------------------
//
void CBCTestLanDB::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdLanDB)
        {
        return;
        }
    
    TestFunctionL();
    }

// ---------------------------------------------------------------------------
// CBCTestLanDB::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestLanDB::TestFunctionL()
    {
    SetupL();
    TestDBInfoL();
    TestImplL();
	TestOthersL();
    }
    

void CBCTestLanDB::SetupL()
{
    // language impl uid(s) are defined in ptiuids.hrh
    iDB = CPtiLanguageDatabase::CreateDatabaseL(TUid::Uid(EPtiLangImplUidEnglish));
    AssertNotNullL(iDB, _L("english Pti language base create"));
}

void CBCTestLanDB::Teardown()
    {
    delete iDB;
	iDB = NULL;
    }


void CBCTestLanDB::TestImplL()
{

    // #languages
    AssertTrueL(iDB->NumLanguages() != 0, _L("NumLanguages got"));
    CERR<<_L("Num of Languages: ")<<iDB->NumLanguages()<<endl<<end;

    // lan code[]
    AssertTrueL(iDB->LanguageCode(0)==1, _L("1st lan code got"));

    // sub lan code[]
    AssertTrueL(iDB->SubLanguageCode(0)==0, _L("sub lan code at 0 got"));
    CERR<<_L("sub lan code at 0: ")<<iDB->SubLanguageCode(0)<<endl<<end;

    // lan data[]
    AssertTrueL(iDB->LangData(0)==NULL, _L("lan data at 0 got"));
    AssertTrueL(iDB->LangData(0, NULL)==NULL, _L("lan data at 0 with param NULL got"));
    
    //
    AssertTrueL(iDB->PinyinPhraseData() == NULL, _L("pinyin phrase data got"));
    AssertTrueL(iDB->ZhuyinPhraseData() == NULL, _L("zhuyin phrase data got"));
    AssertTrueL(iDB->NativeId(0) == 9, _L("native id at 0 got"));
    CERR<<_L("nativeID[0]: ")<<iDB->NativeId(0)<<endl<<end;
}

void CBCTestLanDB::TestDBInfoL()
    {

    //language code for uid
    AssertIntL( CPtiLanguageDatabase::LanguageCodeForUid(EPtiLangImplUidEnglish),
        ELangEnglish, _L("language code for english is OK"));

    }

// a helper class
class CMockLanDB: public CPtiLanguageDatabase
	{
public:
	//
	};

void CBCTestLanDB::TestOthersL()
	{
	CMockLanDB* ptr = new (ELeave) CMockLanDB;
	CleanupStack::PushL(ptr);

	AssertIntL(0, ptr->CoreUID(), _L("Empty CoreUID returned"));

	AssertTrueL(ptr->LangData(0)==NULL, _L("Empty LangData1 returned"));

	AssertTrueL(ptr->LangData(0, NULL)==NULL, _L("Empty LangData2 returned"));

	AssertIntL(0, ptr->LanguageCode(0), _L("Empty Language code returned"));

	AssertIntL(0, ptr->NativeId(0), _L("Empty NativeId returned"));

	AssertIntL(0, ptr->NumLanguages(), _L("Empty NumLanguages returned"));

	CleanupStack::PopAndDestroy();	//ptr;
	}
//end of file
