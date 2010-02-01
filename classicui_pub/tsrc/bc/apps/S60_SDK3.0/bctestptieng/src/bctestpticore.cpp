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
#include <ptiuids.hrh>
#include <ptiuserdicentry.h>

#include "BCTestPtiCore.h"
#include "BCTestPtiEngcontainer.h"
#include "BCTestPtiEng.hrh"
#include "streamlogger.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPtiCore* CBCTestPtiCore::NewL()
    {
    CBCTestPtiCore* self = new( ELeave ) CBCTestPtiCore();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestPtiCore::CBCTestPtiCore():iCore(NULL)
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPtiCore::~CBCTestPtiCore()
    {
    Teardown();
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPtiCore::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestPtiCore::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestPtiCore::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( LeftCBA,
        REP(Down, 4),
        KeyOK, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestPtiCore::RunL
// ---------------------------------------------------------------------------
//
void CBCTestPtiCore::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdPtiCore)
        {
        return;
        }

    TestFunctionL();
    }

// ---------------------------------------------------------------------------
// CBCTestPtiCore::TestLayoutDecorator
// ---------------------------------------------------------------------------
//
void CBCTestPtiCore::TestFunctionL()
    {
    SetupL();
    TestGeneralL();
    TestPredictiveLatinL();
    TestUserDictL();
    TestChineseL();
    TestJapaneseL();
    }


void CBCTestPtiCore::SetupL()
    {
    iCore = CPtiCore::CreateCoreL(TUid::Uid(TestListCoreL()));
    AssertNotNullL(iCore, _L("Pti core create from core list"));
    }

void CBCTestPtiCore::Teardown()
    {
    delete iCore;
    iCore = NULL;
    }

//static
TInt CBCTestPtiCore::TestListCoreL()
    {
    CArrayFix<TInt>* list = CPtiCore::ListCoresLC();
    TInt firstUID = (*list)[0] ;
    CleanupStack::PopAndDestroy();  //list
    return firstUID;
    }

void CBCTestPtiCore::TestGeneralL()
    {
    Teardown();
    iCore = new (ELeave) MonkCore;

    AssertIntL(  KErrNotSupported, iCore->Convert(EPtiSimplifiedToComplex, NULL, 0, NULL),
        _L("Convert hasn't been supported yet"));

    TPtrC8 dummy(KNullDesC8);
    AssertTrueL( iCore->SetCurrentInputSequence(dummy) == KErrNotSupported,
        _L("SetCurrentImputSequence() is not support"));

    TBuf<5> output;
    AssertIntL( KErrNotSupported, iCore->GetSpelling('a', output, EPtiStrokes),
        _L("GetSpelling returns General Err"));

    _LIT(KNewMapLower, "!@#$");
    TBuf<5> lowerMap(KNewMapLower);
    AssertIntL( KErrNotSupported,
        iCore->SetExternalKeyMapL(EPtiEngineMultitapping, EPtiKey1, lowerMap, EPtiCaseLower),
        _L("SetExternalKeyMapL hasn't been supported"));

    AssertIntL( KErrNotSupported, iCore->CommitCurrentWord(),
        _L("CommitCurrentWord"));

    AssertTrueL( TPtrC() == iCore->GetCurrentWord(),
        _L("GetCurrentWord"));
    }

void CBCTestPtiCore::TestPredictiveLatinL()
    {
    AssertIntL( 0, iCore->NumberOfCandidates(),
        _L("NumberOfCandidates not implemented"));

    CDesCArray* cands = new (ELeave) CDesCArrayFlat(2);
    CleanupStack::PushL(cands);
    AssertIntL(KErrNotSupported, iCore->GetCandidateListL(*cands), _L("Get CandidateList not supported"));
    AssertIntL(KErrNotSupported, iCore->GetNextWordCandidateListL(*cands), _L("Get Next word CandidateList not supported"));
    CleanupStack::PopAndDestroy();  //cands

    TBuf<5> res;
    AssertIntL(KErrNotSupported, iCore->GetFirstCandidate(res), _L("Get first cnadiate not supported"));
    AssertIntL(KErrNotSupported, iCore->GetNextCandidate(res), _L("Get next cnadiate not supported"));
    AssertIntL(KErrNotSupported, iCore->GetPreviousCandidate(res), _L("Get prev cnadiate not supported"));
    }

void CBCTestPtiCore::TestUserDictL()
    {
    TPtiUserDictionaryEntry entry(_L("foobar"));
    AssertIntL(KErrNotSupported, iCore->AddUserDictionaryEntry(entry, NULL), _L("Add user dict entry not supported"));
    AssertIntL(KErrNotSupported, iCore->RemoveUserDictionaryEntry(entry, NULL), _L("Remove user dict entry not supported"));
    AssertIntL(0, iCore->NumberOfEntriesInUserDictionary(NULL), _L("NumberOfEntries in user dict got"));
    AssertIntL(KErrNotSupported, iCore->GetUserDictionaryEntry(0, entry, NULL), _L("get user dict entry not supported"));
    CPtiUserDictionary* dict=iCore->CreateEmptyUserDictionaryL(32);
    CleanupStack::PushL(dict);
    AssertNotNullL(dict, _L("Create empty user dict"));
    AssertIntL(KErrNotSupported, iCore->AttachUserDictionary(dict), _L("attach user dict not supported"));
    AssertTrueL(!iCore->DetachUserDictionary(dict), _L("detach user dict"));
    CleanupStack::PopAndDestroy();  //dict
    }

void CBCTestPtiCore::TestChineseL()
    {
    AssertTrueL(TPtrC() == iCore->GetCandidatePage(), _L("Get candidate page"));
    AssertTrueL(!iCore->NextCandidatePage(), _L("no next candidate page"));
    AssertTrueL(!iCore->PreviousCandidatePage(), _L("no prev candidate page"));
    AssertTrueL(!iCore->MoreCandidatePages(), _L("no more candidate page"));
    iCore->SetCandidatePageLength(0);
    AssertTrueL(ETrue, _L("set cnadidate page length do nothing"));
    AssertTrueL(TPtrC() == iCore->GetPhoneticSpelling(0), _L("Get phonetic spelling"));
    AssertIntL(0, iCore->PhoneticSpellingCount(), _L("phonetic spelling count returns 0"));
    AssertTrueL(!iCore->SelectPhoneticSpelling(0), _L("select phonetic spelling returns false"));
    AssertIntL(KErrNotSupported, iCore->SelectedPhoneticSpelling(), _L("selected phonetic spelling not supported"));
    TText mark='a';
    AssertTrueL(!iCore->ToneMark(mark), _L("tone mark returns false"));
    AssertTrueL(!iCore->IsToneMarkValidForSpelling(), _L("tone mark is invalid for spelling"));
    AssertTrueL(!iCore->SetPredictiveChineseChar(_L("")), _L("set predictive chinese char returns false"));
    AssertTrueL(!iCore->SetToneMark(0), _L("set tone mark returns false"));
    }

void CBCTestPtiCore::TestJapaneseL()
    {
    AssertTrueL(TPtrC() == iCore->ReadingTextL(), _L("reading text"));
    AssertTrueL(NULL == iCore->CompositionData(), _L("composition data got"));
    }
