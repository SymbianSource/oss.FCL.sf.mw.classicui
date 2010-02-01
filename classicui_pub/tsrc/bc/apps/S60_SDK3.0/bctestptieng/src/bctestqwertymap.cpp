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

#include "BCTestQwertymap.h"
#include "BCTestPtiEngcontainer.h"
#include "BCTestPtiEng.hrh"
#include "streamlogger.h"

const TInt KPtiQwertyNumKeys = 44;

//
// the oder of Qwerty can be found in ptidefs.h.
//
const char LowerKeys[]=
    "1234567890"
    "+-,;.#/'"
    "abcdefghijklmnopqrstuvwxyz";

const char UpperKeys[]=
    "!@[$%^&*()"
    "=_<:>]?\""
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//
// helper class
//
struct TKeyMap
    {
    static const int KSize = 
        KPtiQwertyNumKeys*2                 // char, '\t'
        +2                                  // '\n', PAD
        +KPtiQwertyNumKeys*2                // CHAR, '\t'
        +1;                                 // '\0' as terminator

    static TKeyMap& Instance()
        {
        static TKeyMap inst;
        return inst;
        }

    const TUint16* AsUint16()
        {
        return iBuffer;
        }

    const TDesC& AsDescriptor()
        {
        return iDes;
        }

private:
    TKeyMap()
        {
        TUint16* ptr = iBuffer;
        for(int i=0; i<KPtiQwertyNumKeys; ++i)
            {
            *ptr++=LowerKeys[i];
            *ptr++='\t';
            }

        ptr--;
        *ptr++='\n';
        *ptr++='\r';    //just padding

        for(int i=0; i<KPtiQwertyNumKeys; ++i)
            {
            *ptr++=UpperKeys[i];
            *ptr++='\t';
            }
        
        ptr--;
        *ptr='\0';      //terminator;
        iDes=iBuffer;
        }

    TUint16 iBuffer[KSize];
    TBuf<KSize> iDes;
    };

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestQwertyMap* CBCTestQwertyMap::NewL()
    {
    CBCTestQwertyMap* self = new( ELeave ) CBCTestQwertyMap();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestQwertyMap::CBCTestQwertyMap():iMap(NULL)
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestQwertyMap::~CBCTestQwertyMap()
    {
    Teardown();
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestQwertyMap::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestQwertyMap::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestQwertyMap::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, 
        REP(Down, 3),
        KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestQwertyMap::RunL
// ---------------------------------------------------------------------------
//
void CBCTestQwertyMap::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdQwertyMap)
        {
        return;
        }
    
    TestFunctionL();
    }

// ---------------------------------------------------------------------------
// CBCTestQwertyMap::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestQwertyMap::TestFunctionL()
    {
    SetupL();
    //TestCreateL();
    TestMapping();
    TestReplaceMappingL();
    TestReverseMapping();
    TestKeyData();
    }

/*    
static void MyConstructL(TDesC& aData)
    {
    //monk members
    HBufC* iData;
    HBufC* iDeadKeyData;
    RArray<TPtiKeyMapping> iMaps;
    RArray<TPtiKeyMapping> iDeadKeyMaps;

    TBool deadkey = EFalse;

    iData = HBufC::NewL(aData.Length());
    iDeadKeyData = HBufC::NewL(aData.Length());

    TInt curKey = 0, i, index = 0;
    TInt deadIndex = 0;
    const TUint16* ptr = aData.Ptr();
    TPtr dest(iData->Des());
    TPtr deadDest(iDeadKeyData->Des());

    TPtiKeyMapping map;
    map.iNumChars = 0;  
    for (i = 0; i < KPtiQwertyNumKeys * 2; i++)
        {
        iMaps.AppendL(map);
        iDeadKeyMaps.AppendL(map);
        }
    CERR<<_L("map init with size: ")<<iMaps.Count()<<endl<<end;

    iMaps[0].iIndex = 0;
    iDeadKeyMaps[0].iIndex = 0;
    for (i = 0; i < aData.Length(); i++)
        {
        if (ptr[i] == '\t')
            {
            curKey++; 
            deadkey = EFalse;
            if (curKey > iMaps.Count())
                {
                User::Leave(KErrCorrupt);
                }
            iMaps[curKey].iIndex = index;
            iDeadKeyMaps[curKey].iIndex = deadIndex;
            continue;
            }
        else if (ptr[i] == '\v')
            {
            deadkey = ETrue;
            }
        else if (ptr[i] == '\n')
            {
            // This is last character for lower keys.
            // Jump to beginning of upper keys.
            curKey++;
            deadkey = EFalse;
            if (curKey > iMaps.Count())
                {
                User::Leave(KErrCorrupt);               
                }
            iMaps[curKey].iIndex = index;
            iDeadKeyMaps[curKey].iIndex = deadIndex;
            i++;
            continue;
            }

        if (!deadkey)
            {
            dest.Append(ptr[i]);
            index++;
            iMaps[curKey].iNumChars++;
            }
        else
            {
            deadDest.Append(ptr[i]);
            deadIndex++;            
            iDeadKeyMaps[curKey].iNumChars++;
            }           
        }
    // monk destruct
    iMaps.Close();
    delete iData;
    iDeadKeyMaps.Close();
    delete iDeadKeyData;
    }
*/

void CBCTestQwertyMap::SetupL()
    {
    TRAPD(err, iMap = static_cast<CPtiQwertyKeyMappings*>(CreateKeyMapL()));
    if(err == KErrCorrupt)
        {
        AssertTrueL(ETrue, _L("data format err"));
        }
    else
        {
        AssertNotNullL(iMap, _L("created by NewL from descriptor"));
        }
    }

void CBCTestQwertyMap::Teardown()
    {
    delete iMap;
	iMap = NULL;
    }

void CBCTestQwertyMap::TestCreateL()
    {
    TInt16 charBuffer[1             //map count
        +(KPtiQwertyNumKeys*2)*2    //map {index, numChars} * count
        +1                          //data count
        +(KPtiQwertyNumKeys*2)*2    //data buffer: lower case (char, \t) + upper case (CHAR \t)
        +1                          //dead data count
        +1                          //dead data buffer
        ];

    RArray<TPtiKeyMapping> maps;
    for (TInt i = 0; i < KPtiQwertyNumKeys * 2; i++)
        {
        TPtiKeyMapping map = {0, 0};
        maps.AppendL( map );
        }

    TInt16* ptr = charBuffer+1+maps.Count()*2+1;
    TInt curKey=0;
    TInt index=0;
    const TUint16* keys = TKeyMap::Instance().AsUint16();
    for (TInt i = 0; i < TKeyMap::KSize-1; ++i)
        {
        if (keys[i] == '\t' || keys[i] == '\n')
            {
            maps[++curKey].iIndex = index;
            if(keys[i] == '\n'){
                ++i;
            }
            continue;
            }

        *(ptr+index)= keys[i];
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

    ptr = charBuffer+1+maps.Count()*2+TKeyMap::KSize;
    *ptr=0;

    Teardown();
    TRAPD(err, iMap = CPtiQwertyKeyMappings::NewL(charBuffer));
    if(err == KErrCorrupt)
        {
        AssertTrueL(ETrue, _L("data format err"));
        }
    else
        {
        AssertNotNullL(iMap, _L("created by NewL from raw data"));
        }   
    }

void CBCTestQwertyMap::TestMapping()
    {
    TestStartMapping();
    TestNextKey();
    }

void CBCTestQwertyMap::TestStartMapping()
    {
    AssertIntL(
        TUint('a'), iMap->StartMapping(EPtiKeyQwertyA, EPtiCaseLower),
        _L("press a got 'a'"));
    AssertIntL(
        TUint('A'), iMap->StartMapping(EPtiKeyQwertyA, EPtiCaseUpper),
        _L("press Shift a got 'A'"));
    AssertIntL(
        TUint('^'), iMap->StartMapping(EPtiKeyQwerty6, EPtiCaseUpper),
        _L("press Shift 6 got '^'"));
    }

void CBCTestQwertyMap::TestNextKey()
    {
    TBool isAppend = ETrue;
    iMap->StartMapping(EPtiKeyQwertyA, EPtiCaseLower);
    AssertIntL( TUint16('a'), iMap->NextKey(EPtiKeyQwertyA, isAppend, EPtiCaseLower),
        _L("press a, press a still got 'a'"));

    AssertTrueL( !isAppend, _L("and 'a' is not append"));

    AssertIntL( TUint16('A'), iMap->NextKey(EPtiKeyQwertyA, isAppend, EPtiCaseUpper),
        _L("then, press Shift a got 'A'"));

    AssertIntL( TUint16('b'), iMap->NextKey(EPtiKeyQwertyB, isAppend, EPtiCaseLower),
        _L("then press b as next key, got 'b'"));
    }

void CBCTestQwertyMap::TestReplaceMappingL()
    {
    TBool isAppend = ETrue;
    _LIT(KNewMapLower, "`");
    _LIT(KNewMapUpper, "~");
    TBuf<5> lowerMap(KNewMapLower);
    TBuf<5> upperMap(KNewMapUpper);

    AssertIntL( KErrNone, iMap->ReplaceKeyMapL(EPtiKeyQwerty1, lowerMap, EPtiCaseLower),
        _L("Lower case mapping for Key 1 change to `"));
    AssertIntL( KErrNone, iMap->ReplaceKeyMapL(EPtiKeyQwerty1, upperMap, EPtiCaseUpper),
        _L("Upper case mapping for Key 1 change to ~"));

    AssertIntL( TUint('`'), iMap->StartMapping(EPtiKeyQwerty1, EPtiCaseLower),
        _L("press 1 got '`'"));
    AssertIntL( TUint16('`'), iMap->NextKey(EPtiKeyQwerty1, isAppend, EPtiCaseLower),
        _L("press 1, again still got '`'"));
    AssertIntL( TUint16('~'), iMap->NextKey(EPtiKeyQwerty1, isAppend, EPtiCaseUpper),
        _L("then, press Shift 1 got '~'"));
    AssertIntL( TUint16('2'), iMap->NextKey(EPtiKeyQwerty2, isAppend, EPtiCaseLower),
        _L("then press 2 as next key, got '2'"));
    }

void CBCTestQwertyMap::TestReverseMapping()
    {
    AssertIntL( EPtiKeyQwerty2, iMap->KeyForCharacter('@'), 
        _L("'@' is mapped by key 2"));
    AssertIntL( EPtiKeyQwertyW, iMap->KeyForCharacter('W'),
        _L("'W' is mapped by key w"));
    }

void CBCTestQwertyMap::TestKeyData()
    {
    _LIT(KNewMapLower, "`");
    _LIT(KNewMapUpper, "~");
    TBuf<8> mapStr;

    iMap->GetDataForKey(EPtiKeyQwerty1, mapStr, EPtiCaseLower);
    AssertTrueL( mapStr == KNewMapLower,
        _L("Lower case data for key 1 is `"));

    iMap->GetDataForKey(EPtiKeyQwerty1, mapStr, EPtiCaseUpper);
    AssertTrueL( mapStr == KNewMapUpper,
        _L("Upper case data for key 1 is ~"));
    }

//static
MPtiKeyMappings* CBCTestQwertyMap::CreateKeyMapL()
    {
    TBuf<TKeyMap::KSize> keyStr(TKeyMap::Instance().AsDescriptor());
    return CPtiQwertyKeyMappings::NewL(keyStr);
    }
