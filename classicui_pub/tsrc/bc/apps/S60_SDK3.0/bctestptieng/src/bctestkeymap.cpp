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
#include <ptikeymappings.h>

#include "BCTestKeymap.h"
#include "BCTestPtiEngcontainer.h"
#include "BCTestPtiEng.hrh"

const TInt KPtiNumKeys = 12;

const TUint16 Keys[]=
    {
        //lower case
        /*1*/ '1', '\t',
        /*2*/ 'a','b','c','\t',
        /*3*/ 'd','e','f','\t',
        /*4*/ 'g','h','i','\t',
        /*5*/ 'j','k','l','\t',
        /*6*/ 'm','n','o','\t',
        /*7*/ 'p','q','r','s','\t',
        /*8*/ 't','u','v','\t',
        /*9*/ 'w','x','y','z','\t',
        /***/ '+','\t',
        /*0*/ '0','\t',
        /*#*/ '#','\t',

        //upper case
        /*1*/ '.', '\t',
        /*2*/ 'A','B','C','\t',
        /*3*/ 'D','E','F','\t',
        /*4*/ 'G','H','I','\t',
        /*5*/ 'J','K','L','\t',
        /*6*/ 'M','N','O','\t',
        /*7*/ 'P','Q','R','S','\t',
        /*8*/ 'T','U','V','\t',
        /*9*/ 'W','X','Y','Z','\t',
        /***/ '-','\t',
        /*0*/ ' ','\t',
        /*#*/ '^',

        '\0'    //string terminator
    };

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestKeymap* CBCTestKeymap::NewL()
    {
    CBCTestKeymap* self = new( ELeave ) CBCTestKeymap();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestKeymap::CBCTestKeymap():iMap(NULL)
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestKeymap::~CBCTestKeymap()
    {
    Teardown();
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestKeymap::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestKeymap::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestKeymap::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, 
        REP(Down, 2),
        KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestKeymap::RunL
// ---------------------------------------------------------------------------
//
void CBCTestKeymap::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdPtiKeymap)
        {
        return;
        }
    
    TestFunctionL();
    }

// ---------------------------------------------------------------------------
// CBCTestKeymap::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestKeymap::TestFunctionL()
    {
    SetupL();
    TestCreateL();
    TestMapping();
    TestReplaceMappingL();
    TestReverseMapping();
    TestKeyData();
    }
    

void CBCTestKeymap::SetupL()
    {
    TRAPD(err, iMap = static_cast<CPtiKeyMappings*>(CreateKeyMapL()));
    if(err == KErrCorrupt)
        {
        AssertTrueL(ETrue, _L("data format err"));
        }
    else
        {
        AssertNotNullL(iMap, _L("created by NewL from descriptor"));
        }
    }

void CBCTestKeymap::Teardown()
    {
    delete iMap;
	iMap = NULL;
    }

void CBCTestKeymap::TestCreateL()
    {
    //raw data format:
    //
    // #map //=2*KPtiNumKeys*sizeof(TPtiKeyMapping) = 2*12*(2*sizeof(int))
    // {index, chars}, {index, chars}, ... , {index, chars} //lower case
    // {INDEX, CHARS}, {INDEX, CHARS}, ... , {INDEX, CHARS} //upper case
    //
    // #chars
    // char1, char2, ... , charN
    //

    TInt16 charBuffer[1+(KPtiNumKeys*2)*2+1+sizeof(Keys)/sizeof(TUint16)];

    RArray<TPtiKeyMapping> maps;
    for (TInt i = 0; i < KPtiNumKeys * 2; i++)
        {
        TPtiKeyMapping map = {0, 0};
        maps.AppendL( map );
        }

    TInt16* ptr = charBuffer+1+maps.Count()*2+1;
    TInt curKey=0;
    TInt index=0;
    for (TInt i = 0; i < sizeof(Keys)/sizeof(TUint16)-1; ++i)
        {
        if (Keys[i] == '\t')
            {
            maps[++curKey].iIndex = index;
            continue;
            }

        *(ptr+index)= Keys[i];
        index++;
        maps[curKey].iNumChars++;
        }

    charBuffer[0]=maps.Count();
    ptr=charBuffer+1;
    for(TInt i=0; i<maps.Count(); ++i)
        {
        *ptr=maps[i].iIndex;
        ptr++;
        *ptr=maps[i].iNumChars;
        ptr++;
        }
    *ptr=index;
    maps.Close();

    Teardown();
    TRAPD(err, iMap = CPtiKeyMappings::NewL(charBuffer));
    if(err == KErrCorrupt)
        {
        AssertTrueL(ETrue, _L("data format err"));
        }
    else
        {
        AssertNotNullL(iMap, _L("created by NewL from raw data"));
        }   
    }

void CBCTestKeymap::TestMapping()
    {
    TestStartMapping();
    TestNextKey();
    }

void CBCTestKeymap::TestStartMapping()
    {
    AssertIntL(
        TUint('a'), iMap->StartMapping(/*TPtiKey::*/EPtiKey2, /*TPtiTextCase::*/EPtiCaseLower),
        _L("press 2 got 'a'"));
    AssertIntL(
        TUint('A'), iMap->StartMapping(/*TPtiKey::*/EPtiKey2, /*TPtiTextCase::*/EPtiCaseUpper),
        _L("press Shift 2 got 'A'"));
    }

void CBCTestKeymap::TestNextKey()
    {
    TBool isAppend = ETrue;
    iMap->StartMapping(EPtiKey3, EPtiCaseLower);
    AssertIntL( TUint16('e'), iMap->NextKey(EPtiKey3, isAppend, EPtiCaseLower),
        _L("press 3, press 3 got 'e'"));

    AssertTrueL( !isAppend, _L("and 'e' is not append"));

    AssertIntL( TUint16('F'), iMap->NextKey(EPtiKey3, isAppend, EPtiCaseUpper),
        _L("then, press Shift 3 got 'F'"));

    AssertIntL( TUint16('g'), iMap->NextKey(EPtiKey4, isAppend, EPtiCaseLower),
        _L("then press 4 as next key, got 'g'"));
    }

void CBCTestKeymap::TestReplaceMappingL()
    {
    TBool isAppend = ETrue;
    _LIT(KNewMapLower, "!@#$");
    _LIT(KNewMapUpper, "%:=&");
    TBuf<5> lowerMap(KNewMapLower);
    TBuf<5> upperMap(KNewMapUpper);

    AssertIntL( KErrNone, iMap->ReplaceKeyMapL(EPtiKey1, lowerMap, EPtiCaseLower),
        _L("Lower case mapping for Key 1 change to !@#$"));
    AssertIntL( KErrNone, iMap->ReplaceKeyMapL(EPtiKey1, upperMap, EPtiCaseUpper),
        _L("Upper case mapping for Key 1 change to %:=&"));

    AssertIntL( TUint('!'), iMap->StartMapping(EPtiKey1, EPtiCaseLower),
        _L("press 1 got '!'"));
    AssertIntL( TUint16('@'), iMap->NextKey(EPtiKey1, isAppend, EPtiCaseLower),
        _L("press 1, again got '@'"));
    AssertIntL( TUint16('='), iMap->NextKey(EPtiKey1, isAppend, EPtiCaseUpper),
        _L("then, press Shift 1 got '@'"));
    AssertIntL( TUint16('a'), iMap->NextKey(EPtiKey2, isAppend, EPtiCaseLower),
        _L("then press 2 as next key, got 'a'"));
    }

void CBCTestKeymap::TestReverseMapping()
    {
    AssertIntL( EPtiKey2, iMap->KeyForCharacter('c'), 
        _L("'c' is mapped by key 2"));
    AssertIntL( EPtiKey9, iMap->KeyForCharacter('X'),
        _L("'X' is mapped by key 9"));
    }

void CBCTestKeymap::TestKeyData()
    {
    _LIT(KNewMapLower, "!@#$");
    _LIT(KNewMapUpper, "%:=&");
    TBuf<8> mapStr;

    iMap->GetDataForKey(EPtiKey1, mapStr, EPtiCaseLower);
    AssertTrueL( ETrue, _L("Lower case data for key 1 is !@#$"));

    iMap->GetDataForKey(EPtiKey1, mapStr, EPtiCaseUpper);
    AssertTrueL( ETrue, _L("Upper case data for key 1 is %:=&"));
    }

//static
MPtiKeyMappings* CBCTestKeymap::CreateKeyMapL()
    {
    TBuf<sizeof(Keys)/sizeof(TUint16)> keyStr(Keys);
    return CPtiKeyMappings::NewL(keyStr);
    }
