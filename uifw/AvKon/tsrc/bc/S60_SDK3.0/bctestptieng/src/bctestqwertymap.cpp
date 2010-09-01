/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#include <w32std.h>
#include <coecntrl.h>
#include <eikenv.h>
#include <ptikeymappings.h>
#include <ptikeymapdata.h>
#include <BARSREAD.H>

#include "BCTestQwertymap.h"
#include "BCTestPtiEngcontainer.h"
#include "BCTestPtiEng.hrh"
#include "streamlogger.h"
#include "PtiLanguage.h"

_LIT( KQwertyDir, "z:\\resource\\qwerty\\" );
_LIT( KMultiTapWildName, "*.rsc" );

_LIT( KNewMapLower, "`" );
_LIT( KNewMapUpper, "~" );





// ============================ MEMBER FUNCTIONS ============================

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
    if( !ValidQwertyMode() )
        {
        AssertTrueL( ETrue, _L("QwertyKeyBoard not surported!") );
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
    if ( iMap )
    	{
        TestMapping();
        TestReplaceMappingL();
        TestReverseMapping();
        TestKeyData();
    	}
    }

// ---------------------------------------------------------------------------
// CBCTestQwertyMap::SetupL()
// ---------------------------------------------------------------------------
//   
void CBCTestQwertyMap::SetupL()
    {
    RArray<TInt> dataImpl;    
    CPtiKeyMapDataFactory::ListImplementationsL(dataImpl);

    TUid uid = TUid::Uid(dataImpl[0]);
    CPtiKeyMapDataFactory* keymapDatafactory =
    CPtiKeyMapDataFactory::CreateImplementationL(uid);
    CleanupStack::PushL(keymapDatafactory);
    dataImpl.Close();

    iKeymapData =static_cast<CPtiKeyMapData*>(
    keymapDatafactory->KeyMapDataForLanguageL(01));
    iMap = CPtiQwertyKeyMappings::NewL(iKeymapData);

    CleanupStack::PopAndDestroy(keymapDatafactory);
    AssertTrueL(ETrue, _L("CPtiQwertyKeyMappings::NewL"));
    }

// ---------------------------------------------------------------------------
// CBCTestQwertyMap::Teardown()
// ---------------------------------------------------------------------------
//  
void CBCTestQwertyMap::Teardown()
    {
    delete iMap;
    iMap = NULL;
    delete iKeymapData;
    iKeymapData = NULL;    
    }


// ---------------------------------------------------------------------------
// CBCTestQwertyMap::TestMapping()
// ---------------------------------------------------------------------------
//  
void CBCTestQwertyMap::TestMapping()
    {
    TestStartMapping();
    TestNextKey();
    }


// ---------------------------------------------------------------------------
// CBCTestQwertyMap::TestStartMapping()
// ---------------------------------------------------------------------------
//  
void CBCTestQwertyMap::TestStartMapping()
    {

    iMap->StartMapping( EPtiKeyQwerty1, EPtiCaseLower );
    _LIT( KStartMapping, "StartMapping is invoked" );
    AssertTrueL( ETrue, KStartMapping );
        
    iMap->StartMapping( EPtiKeyQwerty2, EPtiCaseLower );
    _LIT( KStartMapping1, "StartMapping1 is invoked" );
    AssertTrueL( ETrue, KStartMapping1 );

    }


// ---------------------------------------------------------------------------
// CBCTestQwertyMap::TestNextKey()
// ---------------------------------------------------------------------------
//  
void CBCTestQwertyMap::TestNextKey()
    {

    TBool isAppend = ETrue;
    iMap->StartMapping( EPtiKeyQwerty1, EPtiCaseLower);
    
    iMap->NextKey( EPtiKeyQwerty2, isAppend, EPtiCaseLower );
    _LIT( KNextKey, "NextKey is invoked" );
    AssertTrueL( ETrue, KNextKey );     
    
    iMap->NextKey( EPtiKeyQwerty3, isAppend, EPtiCaseLower );
    _LIT( KNextKey1, "NextKey1 is invoked" );
    AssertTrueL( ETrue, KNextKey1 );

    }


// ---------------------------------------------------------------------------
// CBCTestQwertyMap::TestReplaceMappingL()
// ---------------------------------------------------------------------------
//  
void CBCTestQwertyMap::TestReplaceMappingL()
    {
    TBool isAppend = ETrue;
    TBuf<5> lowerMap( KNewMapLower );
    TBuf<5> upperMap( KNewMapUpper );
    
    iMap->ReplaceKeyMapL( EPtiKeyQwerty1, lowerMap, EPtiCaseLower );
    _LIT( KReplaceKeyMapL, "ReplaceKeyMapL is invoked" );
    AssertTrueL( ETrue, KReplaceKeyMapL );    
    
    iMap->ReplaceKeyMapL( EPtiKeyQwerty2, upperMap, EPtiCaseUpper );
     _LIT( KReplaceKeyMapL1, "ReplaceKeyMapL1 is invoked" );
    AssertTrueL( ETrue, KReplaceKeyMapL1 ); 
    
    iMap->StartMapping( EPtiKeyQwerty3, EPtiCaseLower );
     _LIT( KStartMapping, "StartMapping is invoked" );
    AssertTrueL( ETrue, KStartMapping ); 
    
    iMap->NextKey( EPtiKeyQwerty4, isAppend, EPtiCaseLower);
     _LIT( KNextKey, "NextKey is invoked" );
    AssertTrueL( ETrue, KNextKey ); 
        
    iMap->NextKey( EPtiKeyQwerty5, isAppend, EPtiCaseUpper);
     _LIT( KNextKey1, "NextKey1 is invoked" );
    AssertTrueL( ETrue, KNextKey1 ); 

    }


// ---------------------------------------------------------------------------
// CBCTestQwertyMap::TestReverseMapping()
// ---------------------------------------------------------------------------
//  
void CBCTestQwertyMap::TestReverseMapping()
    {
    TUint16 c = 1;
    iMap->KeyForCharacter( c );
    _LIT( KKeyForCharacter, "KeyForCharacter is invoked" );
    AssertTrueL( ETrue, KKeyForCharacter );
    
    iMap->KeyForCharacter( c );
    _LIT( KKeyForCharacter1, "KeyForCharacter1 is invoked" );
    AssertTrueL( ETrue, KKeyForCharacter1 );
    
    }


// ---------------------------------------------------------------------------
// CBCTestQwertyMap::TestKeyData()
// ---------------------------------------------------------------------------
//  
void CBCTestQwertyMap::TestKeyData()
    {
    
    TBuf<8> mapStr;

    iMap->GetDataForKey( EPtiKeyQwerty1, mapStr, EPtiCaseLower );
    AssertTrueL( ETrue, _L("Lower case data for key 1 is `") );

    iMap->GetDataForKey( EPtiKeyQwerty2, mapStr, EPtiCaseUpper );
    AssertTrueL( ETrue, _L("Upper case data for key 1 is ~") );
    }


// ---------------------------------------------------------------------------
// CBCTestQwertyMap::CreateKeyMapL()
// ---------------------------------------------------------------------------
//  
MPtiKeyMappings* CBCTestQwertyMap::CreateKeyMapL()
    {
    return NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestQwertyMap::ValidQwertyMode()
// ---------------------------------------------------------------------------
//  
bool CBCTestQwertyMap::ValidQwertyMode()
    {
    
    RFs fsSession;
    User::LeaveIfError( fsSession.Connect() ); // Start session
    CleanupClosePushL( fsSession ); 
    
    fsSession.SetSessionPath( KQwertyDir );                 
            
    TFindFile fileFinder( fsSession );
    CDir* fileList = NULL;
    TInt err = fileFinder.FindWildByPath( KMultiTapWildName, &KQwertyDir, fileList ); 
    delete fileList;
    CleanupStack::PopAndDestroy(); // fsSession 
    if( err == KErrNone )
        {
        return true;
        }
    else
        {
        return false;
        }
    
    }
