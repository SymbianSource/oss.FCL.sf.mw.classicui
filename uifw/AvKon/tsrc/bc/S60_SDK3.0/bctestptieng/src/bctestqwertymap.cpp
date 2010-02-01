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
    TRAPD(err, iMap = static_cast<CPtiQwertyKeyMappings*>(CreateKeyMapL()));
    if(err == KErrCorrupt)
        {
        AssertTrueL(ETrue, _L("data format err"));
        }
    else if ( KErrNotFound == err )
    	{
    	iMap = NULL;
    	AssertTrueL(ETrue, _L("data format err KErrNotFound"));
    	}
    else
        {
        AssertNotNullL(iMap, _L("created by NewL from descriptor"));
        }
    }

// ---------------------------------------------------------------------------
// CBCTestQwertyMap::Teardown()
// ---------------------------------------------------------------------------
//  
void CBCTestQwertyMap::Teardown()
    {
    delete iMap;
    iMap = NULL;
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
    
    TPtrC keydata(_L('a'));
    TInt size = keydata.Length();

    iMap->StartMapping( (TPtiKey)keydata[size/2+1], EPtiCaseLower );
    _LIT( KStartMapping, "StartMapping is invoked" );
    AssertTrueL( ETrue, KStartMapping );
        
    iMap->StartMapping( (TPtiKey)keydata[0], EPtiCaseLower );
    _LIT( KStartMapping1, "StartMapping1 is invoked" );
    AssertTrueL( ETrue, KStartMapping1 );

    }


// ---------------------------------------------------------------------------
// CBCTestQwertyMap::TestNextKey()
// ---------------------------------------------------------------------------
//  
void CBCTestQwertyMap::TestNextKey()
    {
    
    TPtrC keydata(_L('a'));
    TInt size = keydata.Length();
    
    TBool isAppend = ETrue;
    iMap->StartMapping( (TPtiKey)keydata[size/2+1], EPtiCaseLower);
    
    iMap->NextKey( (TPtiKey)keydata[size/2+1], isAppend, EPtiCaseLower );
    _LIT( KNextKey, "NextKey is invoked" );
    AssertTrueL( ETrue, KNextKey );     
    
    iMap->NextKey( (TPtiKey)keydata[0], isAppend, EPtiCaseLower );
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
    
    TPtrC keydata(_L('a'));
    TInt size = keydata.Length();

    iMap->ReplaceKeyMapL( (TPtiKey)keydata[0], lowerMap, EPtiCaseLower );
    _LIT( KReplaceKeyMapL, "ReplaceKeyMapL is invoked" );
    AssertTrueL( ETrue, KReplaceKeyMapL );    
    
    iMap->ReplaceKeyMapL( (TPtiKey)keydata[0], upperMap, EPtiCaseUpper );
     _LIT( KReplaceKeyMapL1, "ReplaceKeyMapL1 is invoked" );
    AssertTrueL( ETrue, KReplaceKeyMapL1 ); 
    
    iMap->StartMapping( (TPtiKey)keydata[0], EPtiCaseLower );
     _LIT( KStartMapping, "StartMapping is invoked" );
    AssertTrueL( ETrue, KStartMapping ); 
    
    iMap->NextKey( (TPtiKey)keydata[0], isAppend, EPtiCaseLower);
     _LIT( KNextKey, "NextKey is invoked" );
    AssertTrueL( ETrue, KNextKey ); 
        
    iMap->NextKey( (TPtiKey)keydata[0], isAppend, EPtiCaseUpper);
     _LIT( KNextKey1, "NextKey1 is invoked" );
    AssertTrueL( ETrue, KNextKey1 ); 

    }


// ---------------------------------------------------------------------------
// CBCTestQwertyMap::TestReverseMapping()
// ---------------------------------------------------------------------------
//  
void CBCTestQwertyMap::TestReverseMapping()
    {
    
    
    TPtrC keydata(_L('a'));
    TInt size = keydata.Length();
    
    iMap->KeyForCharacter( keydata[1] );
    _LIT( KKeyForCharacter, "KeyForCharacter is invoked" );
    AssertTrueL( ETrue, KKeyForCharacter );
    
    iMap->KeyForCharacter( keydata[2] );
    _LIT( KKeyForCharacter1, "KeyForCharacter1 is invoked" );
    AssertTrueL( ETrue, KKeyForCharacter1 );
    }


// ---------------------------------------------------------------------------
// CBCTestQwertyMap::TestKeyData()
// ---------------------------------------------------------------------------
//  
void CBCTestQwertyMap::TestKeyData()
    {
    
    TPtrC keydata(_L('a'));
    TInt size = keydata.Length();
    
    TBuf<8> mapStr;

    iMap->GetDataForKey( (TPtiKey)keydata[0], mapStr, EPtiCaseLower );
    AssertTrueL( ETrue, _L("Lower case data for key 1 is `") );

    iMap->GetDataForKey( (TPtiKey)keydata[0], mapStr, EPtiCaseUpper );
    AssertTrueL( ETrue, _L("Upper case data for key 1 is ~") );
    }


// ---------------------------------------------------------------------------
// CBCTestQwertyMap::CreateKeyMapL()
// ---------------------------------------------------------------------------
//  
MPtiKeyMappings* CBCTestQwertyMap::CreateKeyMapL()
    {
    
    MPtiKeyMappings* keyMappings = NULL;
    RFs fsSession;
    User::LeaveIfError( fsSession.Connect() ); // Start session
    CleanupClosePushL( fsSession ); 
    
    fsSession.SetSessionPath( KQwertyDir );                 
            
    TResourceReader reader;
    RResourceFile resFile;
    
    TFindFile fileFinder( fsSession );
    CDir* fileList = NULL;
    TInt err;   
    err = fileFinder.FindWildByPath( KMultiTapWildName, &KQwertyDir, fileList );   
    
    TInt code = User::Language();
    TInt lcode;
    
    if ( err == KErrNoMemory )
        {
        delete fileList;
    User::Leave( KErrNoMemory );                
    }
        
    else if ( err == KErrNone )
        {
        CleanupStack::PushL( fileList );
        TParse fileName;            
        HBufC8* rBuffer = NULL; 
        
        TInt i;
        for ( i = 0; i < fileList->Count(); i++ )
            {
            fileName.Set( (*fileList)[i].iName, &fileFinder.File(), NULL );
            resFile.OpenL( fsSession, fileName.FullName() );                
            CleanupClosePushL( resFile );               
                
            rBuffer = resFile.AllocReadLC( 1 ); 
            reader.SetBuffer( rBuffer );    
                
            lcode = *( (TInt16*)rBuffer->Ptr() );       
            if ( lcode == code )
                {
                break;
                }           
            CleanupStack::PopAndDestroy(2); // rBuffer, resFile                                                             
            }
        if ( i >= fileList->Count() )   
            {
            User::Leave( KErrNotFound );
            }
                
        TPtrC mtdata( (TUint16*)( rBuffer->Ptr() + ( 2 * sizeof( TUint16 ) ) ),
                 ( rBuffer->Length() - (2 * sizeof(TUint16) ) ) / 2 ); 
        keyMappings = CPtiQwertyKeyMappings::NewL( mtdata );     
        
        CleanupStack::PopAndDestroy(3); // fileList, rBuffer, resFile                           
    }
        
    CleanupStack::PopAndDestroy(); // fsSession 
    
    return keyMappings;
    
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
