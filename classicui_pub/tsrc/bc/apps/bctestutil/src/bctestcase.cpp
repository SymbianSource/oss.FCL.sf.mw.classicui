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
* Description:         Test case.
*
*/








#include "bctestcase.h"

const TInt KInitSize = 20;
const TInt KGranularity = 5;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestCase::CBCTestCase()
    : iType( ENormalCase )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestCase::~CBCTestCase()
    {
    delete [] iTestScripts;
    }

// ---------------------------------------------------------------------------
// CBCTestCase::RunL. 
// User needs to override this function.
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestCase::RunL( TInt )
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestCase::AppendL
// Append a command to iTestScripts.
// ---------------------------------------------------------------------------
//
void CBCTestCase::AppendL(TInt aCmd)
    {     
    if ( !iTestScripts )   
        {
        iScriptCount = 0;
        iMaxSize = KInitSize;
        iTestScripts = new( ELeave ) TInt[iMaxSize];
        }
    if ( iScriptCount == iMaxSize )
        {
        iMaxSize += KGranularity;
        TInt* tempArray = new( ELeave ) TInt[iMaxSize];
        for ( TInt i=0; i<iScriptCount; i++ )
            {
            tempArray[i] = iTestScripts[i];
            }
        delete [] iTestScripts;
        iTestScripts = tempArray;        
        }
    iTestScripts[iScriptCount] = aCmd;
    iScriptCount++;
    }

// ---------------------------------------------------------------------------
// CBCTestCase::AddTestL
// Add automatic test commands.
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestCase::AddTestL( TInt aCmd, ... )
    {    
    TInt cmd = aCmd;
    VA_LIST list;
    VA_START(list, aCmd);
    
    while ( cmd != TEND )
        {
        AppendL( cmd );
        cmd=VA_ARG( list, TInt );
        }
    VA_END(list);    
    }

// ---------------------------------------------------------------------------
// CBCTestCase::TestScripts
// ---------------------------------------------------------------------------
//
TInt* CBCTestCase::TestScripts()
    {
    return iTestScripts;
    }

// ---------------------------------------------------------------------------
// CBCTestCase::ScriptCount
// ---------------------------------------------------------------------------
//
TInt CBCTestCase::ScriptCount() 
    {
    return iScriptCount;
    }

// ---------------------------------------------------------------------------
// CBCTestCase::AddTestScript
// User can write all commands in a TInt array, then add it to test case.
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestCase::AddTestScriptL( const TInt* aCmdArray, TInt aCmdCount )
    {    
    if ( !aCmdArray || aCmdCount < 0 )
        {
        User::Leave( KErrArgument );
        }
    
    TInt count = iScriptCount + aCmdCount;
    if ( iMaxSize < count )
        {
        TInt* temp = new( ELeave ) TInt[count];            
        for ( TInt i = 0; i < iScriptCount; i++ )
            {
            temp[i] = iTestScripts[i];
            }
        delete [] iTestScripts;
        iTestScripts = temp;
        iMaxSize = count;
        }        
    for ( TInt i = 0; i < aCmdCount; i++ )
        {
        iTestScripts[i + iScriptCount] = aCmdArray[i];
        }
    iScriptCount = count;    
    }

// ---------------------------------------------------------------------------
// CBCTestCase::Name
// ---------------------------------------------------------------------------
//
TDesC& CBCTestCase::Name()
    {
    return iName;
    }

// ---------------------------------------------------------------------------
// CBCTestCase::Name
// ---------------------------------------------------------------------------
//
void CBCTestCase::SetName( const TDesC& aName )
    {
    iName.Zero();
    iName.Append( aName );
    }

// ---------------------------------------------------------------------------
// CBCTestCase::Type
// ---------------------------------------------------------------------------
//
TInt CBCTestCase::Type()
    {
    return iType;
    }
    
// ---------------------------------------------------------------------------
// CBCTestCase::SetType
// ---------------------------------------------------------------------------
//
void CBCTestCase::SetType( TInt aType )
    {
    iType = aType;
    }
