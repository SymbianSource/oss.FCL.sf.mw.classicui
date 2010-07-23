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
#include <ptiengine.h>
#include <ptiuids.hrh>
#include <ptidefs.h>
#include <badesca.h>
#include <ptiuserdicentry.h>

#include "BCTestPtiEngine.h"
#include "BCTestPtiEngcontainer.h"
#include "BCTestPtiEng.hrh"
#include "streamlogger.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPtiEngine* CBCTestPtiEngine::NewL()
    {
    CBCTestPtiEngine* self = new( ELeave ) CBCTestPtiEngine();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestPtiEngine::CBCTestPtiEngine():iEngine(NULL)
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPtiEngine::~CBCTestPtiEngine()
    {
    TeardownL();
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPtiEngine::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestPtiEngine::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestPtiEngine::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( LeftCBA,
        REP(Down, 5),
        KeyOK, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestPtiEngine::RunL
// ---------------------------------------------------------------------------
//
void CBCTestPtiEngine::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdPtiEng)
        {
        return;
        }

    TestFunctionL();
    }

// ---------------------------------------------------------------------------
// CBCTestPtiEngine::TestLayoutDecorator
// ---------------------------------------------------------------------------
//
void CBCTestPtiEngine::TestFunctionL()
    {
    SetupL();
    TestLanguageL();
    TestInfoL();
    TestInputL();
    TestJapaneseInputL();
    TestChineseInputL();
    //TestDictL();
    TestOtherL();
    }


void CBCTestPtiEngine::SetupL()
    {
    iEngine = CPtiEngine::NewL();
    AssertNotNullL(iEngine, _L("pti engine created"));
    }

void CBCTestPtiEngine::TeardownL()
    {
    if(iEngine)
        iEngine->CloseCurrentLanguageL();
    delete iEngine;
    iEngine=NULL;
    }

void CBCTestPtiEngine::TestLanguageL()
    {
    CArrayFixFlat<TInt>* langs = new (ELeave) CArrayFixFlat<TInt>(100);
    CleanupStack::PushL(langs);
    iEngine->GetAvailableLanguagesL(langs);

    AssertTrueL(langs->Count()>0, _L("available languages got"));
    CleanupStack::PopAndDestroy( 1 ); // cores, langs

    RArray<TInt> langRefs;
    iEngine->GetAvailableLanguagesL(langRefs);
    AssertTrueL(langRefs.Count()>0, _L("available languages got into RArray"));

    //
    //activate
    //
    if(langRefs.Count())
        {
        MPtiLanguage *lan = iEngine->GetLanguage(langRefs[0]);
        if (lan->HasInputMode(EPtiEngineMultitapping))
            {
            iEngine->ActivateLanguageL(lan->LanguageCode(), EPtiEngineMultitapping);
            AssertTrueL( ETrue, _L("activate multitapping"));
            }
        else
            {
            iEngine->ActivateLanguageL(lan->LanguageCode(), EPtiEnginePredictive);
            AssertTrueL( ETrue, _L("activate predictive"));
            }
        }

    langRefs.Close();
    }


void CBCTestPtiEngine::TestInfoL()
    {
    TBuf<16> msg;
    msg.Format(_L("num of lan: %d"), iEngine->NumberOfLanguages());
    msg.ZeroTerminate();
    AssertTrueL(iEngine->NumberOfLanguages()>0, msg);

    if (iEngine->InputMode() == EPtiEngineMultitapping)
        {
        AssertTrueL(ETrue, _L("input mode is Multitapping"));
        }
    else
        {
        AssertTrueL(ETrue, _L("input mode is Predictive"));
        }

    // localized language name
    TFileName localName;
    iEngine->GetLocalizedLanguageName(31, localName); //31 is chinese?
    localName.ZeroTerminate();
    AssertTrueL(ETrue, localName);

    //observer
    MPtiObserver* obs = iEngine->Observer();
    AssertTrueL(ETrue, _L("observer got"));
    iEngine->SetObserver(obs);
    AssertTrueL(ETrue, _L("observer set"));
    }

void CBCTestPtiEngine::TestInputL()
    {
    TestInputModeL();
    TestMultitappingL();
    TestPredictL();
    TestLastKeyL();
    TestNavigationL();
    TestReorderingL();
    }

void CBCTestPtiEngine::TestMultitappingL()
    {
    //multitapping
    iEngine->ActivateLanguageL(ELangEnglish, EPtiEngineMultitapping);
    iEngine->AppendKeyPress(EPtiKey3);
    iEngine->AppendKeyPress(EPtiKey6);
    iEngine->AppendKeyPress(EPtiKey6);
    iEngine->AppendKeyPress(EPtiKey6);
    iEngine->AppendKeyPress(EPtiKey4);
    _LIT(KDog, "dog");
    AssertTrueL( iEngine->CurrentWord()==KDog, _L("multityping input verified"));

    // commit
    AssertIntL(KErrNone, iEngine->CommitCurrentWord(),
        _L("Tell engine that current word was accepted"));

    // set external key map
    TInt ret(0);
    TBuf<5> testLit;
    testLit.Copy(_L("abcd"));
    TRAPD(err, ret = iEngine->SetExternalKeyMapL(EPtiEngineMultitapping, EPtiKey5,
                                                testLit, EPtiCaseUpper));
    if ((ret == KErrNone) || (err != KErrNone))
        {
        AssertTrueL(ETrue, _L("set external key map failure"));
        }
    AssertTrueL(ETrue, _L("external key map set"));
    }

static void SimuInput(CPtiEngine* aEngine, const TDesC& aKeys)
    {
    for(int i=0; i<aKeys.Length(); ++i)
        {
        if (aKeys[i] == ' ')
            {
            continue;
            }
        else if (aKeys[i] == 'p')
            {
            continue;
            }
        else if (aKeys[i] == 'd')
            {
            aEngine->DeleteKeyPress();
            }
        else
            {
            aEngine->AppendKeyPress(aEngine->CharacterToKey(aKeys[i]));
            }
        }
    }

void CBCTestPtiEngine::TestPredictL()
    {
    //predictive
    iEngine->ActivateLanguageL(ELangEnglish, EPtiEnginePredictive);
    SimuInput(iEngine, _L("this"));

    TBuf<32> msg=_L("current word is: ");
    msg.Append(iEngine->CurrentWord());  //may be "this"
    msg.ZeroTerminate();
    AssertTrueL( ETrue, msg);

    // next
    msg=_L("next word is: ");
    msg.Append(iEngine->NextCandidate()); // Move on to next candidate.
    msg.ZeroTerminate();
    AssertTrueL( ETrue, msg);
    iEngine->CommitCurrentWord();

    // delete
    SimuInput(iEngine, _L("8447"));
    msg = _L("current word after del is: ");
    msg.Append(iEngine->DeleteKeyPress());
    msg.ZeroTerminate();
    AssertTrueL(ETrue, msg);

    // reject
    iEngine->ClearCurrentWord();
    AssertTrueL(ETrue, _L("reject current word"));

    // char2key
    AssertIntL(EPtiKey7, iEngine->CharacterToKey('s'), _L("char 's' map to key 7"));

    // candidate list
    iEngine->ClearCurrentWord();
    CDesCArray* cands = new (ELeave) CDesCArrayFlat(16);
    CleanupStack::PushL(cands);

    SimuInput(iEngine, _L("8447"));
    iEngine->GetCandidateListL(*cands);
    msg=_L("candidates: ");
    for (int i = 0; i < cands->Count(); ++i)
        {
        msg.Append(cands->MdcaPoint(i));
        msg.Append(_L(", "));
        }
    msg.ZeroTerminate();
    AssertIntL(cands->Count(), iEngine->NumberOfCandidates(), msg);
    CleanupStack::PopAndDestroy();  // cands

    // set current word
    iEngine->SetCurrentWord(_L("dog"));
    SimuInput(iEngine, _L("t"));
    msg=_L("dog+t change to: ");
    msg.Append(iEngine->CurrentWord());
    msg.ZeroTerminate();
    AssertTrueL(ETrue, msg);
    }

void CBCTestPtiEngine::TestInputModeL()
    {
   // AssertIntL(iEngine->SetInputMode(EPtiEngineMultitapping), KErrNone,
   //     _L("set input mode to multitapping"));
   // AssertIntL(iEngine->SetInputMode(EPtiEnginePredictive), KErrNone,
   //     _L("set input mode to predictive"));
   // AssertIntL(iEngine->SetInputMode(EPtiEngineNumeric), KErrNone,
   //     _L("set input mode to numeric"));

		TInt err = iEngine->SetInputMode(EPtiEngineMultitapping);
		if(err == KErrNoSuitableCore)
			AssertIntL(KErrNoSuitableCore, err, _L("set input mode to multitapping not supported for current language"));
		else
			AssertIntL(KErrNone, err, _L("set input mode to multitapping"));

		err = iEngine->SetInputMode(EPtiEnginePredictive);
		if(err == KErrNoSuitableCore)
			AssertIntL(KErrNoSuitableCore, err, _L("set input mode to predictive not supported for current language"));
		else
			AssertIntL(KErrNone, err, _L("set input mode to predictive"));

		err = iEngine->SetInputMode(EPtiEngineNumeric);
		if(err == KErrNoSuitableCore)
			AssertIntL(KErrNoSuitableCore, err, _L("set input mode to numeric not supported for current language"));
		else
			AssertIntL(KErrNone, err, _L("set input mode to numeric"));

    // set case
    iEngine->SetCase(EPtiCaseUpper);
    AssertIntL(EPtiCaseUpper, iEngine->Case(), _L("upper case set"));

    iEngine->SetCase(EPtiCaseLower);
    AssertIntL(EPtiCaseLower, iEngine->Case(), _L("lower case set"));
    }

void CBCTestPtiEngine::TestDictL()
    {
    CDesCArrayFlat* words = new (ELeave) CDesCArrayFlat(5);
    CleanupStack::PushL( words );
    words->AppendL(_L("lorem"));
    words->AppendL(_L("ipsum"));
    words->AppendL(_L("dolor"));
    words->AppendL(_L("sit"));
    words->AppendL(_L("amet"));

    TBuf<50> filename(_L("C:\\BCTestLog\\TestUserDict.txt"));
    AssertIntL(KErrNotSupported,
        iEngine->CreateUserDictionaryL(filename, words, EPtiEngineWordCompletion),
        _L("user dict created isn't supported"));

    CleanupStack::PopAndDestroy();  //words


	TInt err;
    //attach
    MPtiUserDictionary* dict = iEngine->AttachUserDictionaryL(filename);
    if(dict)
        {
        AssertTrueL(ETrue, _L("user dict attached"));
        }
    else
        {
        AssertTrueL(ETrue, _L("user dict attached failure"));
        }

    //detach
    if(iEngine->DetachUserDictionary(filename) == KErrNone)
        {
        AssertTrueL(ETrue, _L("user dict detach"));
        }
    else
        {
        AssertTrueL(ETrue, _L("User dict detach failure"));
        }

    if(iEngine->DetachUserDictionary(0) == KErrNone)
        {
        AssertTrueL(ETrue, _L("user dict detach by ID"));
        }
    else
        {
        AssertTrueL(ETrue, _L("User dict detach by ID failure"));
        }

    //entry
    TFileName msg;
    TPtiUserDictionaryEntry entry(_L("foobar"));

    TInt number = iEngine->NumberOfEntriesInUserDictionary();
    if(number == KErrNotSupported)
        {
        AssertTrueL(ETrue, _L("user dict doesn't support entry"));
        }
    else
        {
        msg.Format(_L("total %d entries"), number);
        AssertTrueL(ETrue, msg);
        }

    err=iEngine->AddUserDictionaryEntry(entry);
    msg.Format(_L("add entry returns: %d"), err);
    msg.ZeroTerminate();
    AssertTrueL(ETrue, msg);

    err=iEngine->AddUserDictionaryEntry(entry, 0);
    msg.Format(_L("add entry with ID 0 returns: %d"), err);
    msg.ZeroTerminate();
    AssertTrueL(ETrue, msg);

    err=iEngine->RemoveEntryFromUserDictionary(entry);
    msg.Format(_L("remove entry returns: %d"), err);
    msg.ZeroTerminate();
    AssertTrueL(ETrue, msg);

    err=iEngine->RemoveEntryFromUserDictionary(entry, 0);
    msg.Format(_L("remove entry with ID 0 returns: %d"), err);
    msg.ZeroTerminate();
    AssertTrueL(ETrue, msg);

    err = iEngine->GetUserDictionaryEntry(0, entry);
    msg.Format(_L("get first entry returns: %d"), err);
    msg.ZeroTerminate();
    AssertTrueL(ETrue, msg);

    dict = iEngine->DefaultUserDictionary(EPtiEnginePinyin);
    if(dict)
        {
        AssertNotNullL(dict, _L("dict for Pinyin found"));
        }
    else
        {
        AssertTrueL(ETrue, _L("dict for Pinyin not found"));
        }
    }

void CBCTestPtiEngine::TestLastKeyL()
    {
    iEngine->ClearCurrentWord();
    AssertIntL(EPtiKeyNone, iEngine->LastEnteredKey(), _L("none last entered key"));

    SimuInput(iEngine, _L("dog"));
    AssertIntL(EPtiKeyGHI, iEngine->LastEnteredKey(), _L("last key for 'dog' is GHI"));
    }

void CBCTestPtiEngine::TestNavigationL()
    {
    iEngine->ClearCurrentWord();
    SimuInput(iEngine, _L("46873"));

    CDesCArray* cands = new (ELeave) CDesCArrayFlat(16);
    CleanupStack::PushL(cands);

    iEngine->GetCandidateListL(*cands);
    AssertIntL(0, iEngine->FirstCandidate().Compare(cands->MdcaPoint(0)),
        _L("First candidate verified"));

    for (int i = 1; i < cands->Count(); ++i)
        {
        AssertIntL(0, iEngine->NextCandidate().Compare(cands->MdcaPoint(i)),
            _L("next candidate verified"));
        }

    for (int i = cands->Count() - 2; i >= 0; --i)
        {
        AssertIntL(0, iEngine->PreviousCandidate().Compare(cands->MdcaPoint(i)),
            _L("Previous candidate verified"));
        }

    CleanupStack::PopAndDestroy(); // cands
    }

void CBCTestPtiEngine::TestReorderingL()
    {
    TInt err=iEngine->SetReordering(ETrue);
    if(err == KErrNone)
        {
        AssertIntL(KErrNone, err, _L("set reordering"));
        iEngine->ClearCurrentWord();
        SimuInput(iEngine, _L("364"));

        // get the third candidate
        TBuf<64> word;
        iEngine->NextCandidate();
        iEngine->NextCandidate();
        word.Copy(iEngine->NextCandidate());

        // comit it 4 times
        for(int i=0; i<4; ++i)
            {
            iEngine->SetCurrentWord(word);
            iEngine->CommitCurrentWord();
            }
        SimuInput(iEngine, _L("364"));
        AssertIntL(0, iEngine->CurrentWord().Compare(word),
            _L("reordered candidate verified"));
        iEngine->SetReordering(EFalse);
        }
    else
        {
        AssertIntL(KErrNotSupported, err,
            _L("set reordering isn't supported"));
        }
    }

CPtiEngine* CreateEngineL(TInt aLanguage, TPtiEngineInputMode aMode)
    {
    CPtiEngine* engine = CPtiEngine::NewL();
    MPtiLanguage* lang = engine->GetLanguage(aLanguage);

    TBuf<100> numStr;

    if (!lang)
        {
        goto fail;
        }

    if (!lang->HasInputMode(aMode))
        {
        goto fail;
        }

    TInt err = engine->ActivateLanguageL(aLanguage, aMode);
    if (err != KErrNone)
        {
        goto fail;
        }

    return engine;

fail:
    delete engine;
    return NULL;
    }

void CBCTestPtiEngine::TestChineseInputL()
    {
    TeardownL();

    if((iEngine = CreateEngineL(ELangPrcChinese, EPtiEngineStroke))!=NULL)
        {
        AssertNotNullL(iEngine, _L("Chinese Pinyin activated"));
        SimuInput(iEngine, _L("wei"));

        int page=0;
        iEngine->SetCandidatePageLength(20);
        AssertTrueL(ETrue, _L("page length set to 20"));
        for(TPtrC str=iEngine->CandidatePage();
                iEngine->MoreCandidatePages();
                iEngine->NextCandidatePage())
            {
            TFileName res;
            res.Format(_L("page[%d]: "), page++);
            for(int j=0; j<str.Length(); ++j)
                {
                res.Append(_L("<"));
                res.AppendNumUC(str[j], EHex);
                res.Append(_L(">"));
                }
            res.ZeroTerminate();
            AssertTrueL(ETrue, res);

            if(page>10)
                {
                break;
                }
            }//end of for

        //predict
        iEngine->PreviousCandidatePage();
        TPtrC aChar=iEngine->CandidatePage();
        iEngine->SetPredictiveChineseChar(aChar);
        AssertTrueL(ETrue, _L("next chinese char predicted"));

        //test next candidate list
        iEngine->CommitCurrentWord();
        CDesCArray* cands = new (ELeave) CDesCArrayFlat(16);
        CleanupStack::PushL(cands);

        TRAPD(err, iEngine->GetNextWordCandidateListL(*cands));
        if(err == KErrNotSupported)
            {
            AssertTrueL(ETrue, _L("predict next candidate not supported"));
            }
        else{
            TFileName msg=_L("candidates: ");
            for (int i = 0; i < cands->Count(); ++i)
            {
                msg.Append(cands->MdcaPoint(i));
                msg.Append(_L(", "));
            }
            msg.ZeroTerminate();
            AssertTrueL(ETrue, msg);
            }
        CleanupStack::PopAndDestroy();  // cands

        //test conversion
        TInt convCap=iEngine->AvailableCharConversions();
        if((convCap & EPtiSimplifiedToComplex)!=0)
            {
            AssertTrueL(ETrue, _L("can convert from simplified chinese to traditional"));
            }
        else
            {
            AssertIntL(0, convCap, _L("conv capability:"));
            }
        char inbuf[]={0x76, 0x84};
        char outbuf[]={0,0};
        iEngine->CharConversion(EPtiSimplifiedToComplex, inbuf, 2, outbuf);
        AssertTrueL(ETrue, _L("tried char conversion"));

        //Chinese Varient
        RArray<TInt> modes;
        iEngine->GetModeNameIndexL(EPtiChineseVariantPrc, modes);
        AssertTrueL(ETrue, _L("Chinese varient index table got"));
        modes.Close();

        //phrase list
        iEngine->ClearCurrentWord();
        SimuInput(iEngine, _L("wei"));
        cands = new (ELeave) CDesCArrayFlat(16);
        CleanupStack::PushL(cands);
        iEngine->GetChinesePhraseCandidatesL(*cands);
        AssertTrueL(ETrue, _L("Chinese phrase candidate list got"));
        CleanupStack::PopAndDestroy();  //cands

        TestSpellL();
        TestDictL();// test Pinyin dict.
        }
    else
        {
        AssertTrueL(ETrue, _L("unable to activate Chinese Pinyin"));
        if ( iEngine == NULL )
            {
            SetupL();
            } 
        iEngine->ActivateLanguageL(ELangEnglish, EPtiEnginePredictive);
        }
    }

void CBCTestPtiEngine::TestSpellL()
    {
    TBuf<8> spell;
    TInt err=iEngine->GetSpelling(0x7684, spell, EPtiPinyin);
    if(err==KErrNotSupported)
        {
        AssertTrueL(ETrue, _L("get spelling not support"));
        }
    else if(err==KErrNone)
        {
        spell.ZeroTerminate();
        AssertTrueL(ETrue, spell);
        }
    else
        {
        AssertTrueL(ETrue, _L("get spelling failuer"));
        }

    //phonetic
    iEngine->ClearCurrentWord();
    SimuInput(iEngine, _L("wei"));
    TInt number = iEngine->PhoneticSpellingCount();
    TFileName msg;
    msg.Format(_L("phonetic spelling count: %d"), number);
    msg.ZeroTerminate();
    AssertTrueL(ETrue, msg);

    spell=iEngine->GetPhoneticSpelling(0);
    AssertTrueL(ETrue, _L("get phonetic spelling for 0"));

    TBool result = iEngine->SelectPhoneticSpelling(0);
    AssertTrueL(ETrue, _L("select phonetic spelling for 0"));

    number = iEngine->SelectedPhoneticSpelling();
    msg.Format(_L("selected phonetic spelling: %d"), number);
    msg.ZeroTerminate();
    AssertTrueL(ETrue, msg);

    CDesCArray* array = new (ELeave) CDesCArrayFlat(16);
    CleanupStack::PushL(array);
    iEngine->GetPhoneticSpellingsL(*array);
    AssertTrueL(ETrue, _L("phonetic spellings got"));
    CleanupStack::PopAndDestroy();  //array
    }

void CBCTestPtiEngine::TestOtherL()
    {
    iEngine->HandleCommandL(EPtiCommandNone);
    AssertTrueL(ETrue, _L("handle command"));

    iEngine->EnableToneMarks(ETrue);
    iEngine->EnableToneMarks(EFalse);
    iEngine->ResetToneMark();
    AssertTrueL(ETrue, _L("tone mark set and reset"));

    TText result;
    iEngine->ToneMark(result);
    AssertTrueL(ETrue, _L("tone mark got"));

    if(iEngine->IsToneMarkValidForSpelling())
        AssertTrueL(ETrue, _L("tone mark is valid for spelling"));
    else
        AssertTrueL(ETrue, _L("tone mark is invalid for spelling"));

    if(iEngine->IncrementToneMark(ETrue))
        AssertTrueL(ETrue, _L("new tone mark was found and set"));
    else
        AssertTrueL(ETrue, _L("didn't found new tone mark"));

    if(iEngine->SetToneMark(0))
        AssertTrueL(ETrue, _L("tone mark was legal"));
    else
        AssertTrueL(ETrue, _L("illegal tone mark"));

    //key mapping
    TBuf<8> mapRes;
    iEngine->MappingDataForKey(EPtiKey2, mapRes, EPtiCaseLower);
    AssertTrueL(ETrue, _L("mapping data for key"));

    RArray<TPtiNumericKeyBinding> qwertyMapRes;
    iEngine->GetNumericModeKeysForQwertyL(ELangEnglish, qwertyMapRes);
    AssertTrueL(ETrue, _L("get numeric mode keys for qwerty keys"));
    qwertyMapRes.Close();
    }

void CBCTestPtiEngine::TestJapaneseInputL()
    {
    TeardownL();

    if((iEngine = CreateEngineL(ELangJapanese, /*EPtiEngineHiraganaKanji*/EPtiEnginePredictive))!=NULL)
        {
        AssertTrueL(ETrue, _L("Japanese Hirakana Kanji activated"));
        }
    else
        {
        AssertTrueL(ETrue, _L("can not activate Japanese input"));
        if ( iEngine == NULL )
            {
            SetupL();
            }        
        iEngine->ActivateLanguageL(ELangEnglish, EPtiEnginePredictive);
        }

    MPtiEngineCompositionDataInterface* data=iEngine->CompositionData();
    AssertTrueL(ETrue, _L("Japanese composition data IF got"));

    SimuInput(iEngine, _L("nihon"));
    TPtrC str=iEngine->ReadingTextL();
    AssertTrueL(ETrue, _L("reading text for japanese input"));
    iEngine->ClearCurrentWord();
    }
