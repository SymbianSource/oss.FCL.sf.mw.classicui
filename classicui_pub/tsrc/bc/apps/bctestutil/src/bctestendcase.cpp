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
* Description:         Test utility, the interface of test framework.
*
*/









#include <sysutil.h>
#include <s32file.h>
#include <apgtask.h>
#include "bctestendcase.h"

_LIT( KSdkVerFile, "c:\\BCTestLog\\sdkversion.log" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestEndCase::CBCTestEndCase()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEndCase::~CBCTestEndCase()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd constructor
// ---------------------------------------------------------------------------
//
CBCTestEndCase* CBCTestEndCase::NewL()
    {
    CBCTestEndCase* self = new( ELeave ) CBCTestEndCase();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd constructor
// ---------------------------------------------------------------------------
//
void CBCTestEndCase::ConstructL()
    {
    BuildScriptL();
    }
static TInt ManualSDKVersion()
	{
	RFs fs;
    User::LeaveIfError( fs.Connect() );
    RFileReadStream readStream;
    if ( readStream.Open( fs, KSdkVerFile, EFileRead ) < 0 )
	    {
	    fs.Close();
	    readStream.Release ();
	    return 0;    		
	    }
    readStream.PushL();
    TInt ver = static_cast<TInt>(readStream.ReadInt32L());   
    readStream.Pop ();
    readStream.Release ();
    fs.Close();
	return ver;
	}
	

// ---------------------------------------------------------------------------
// CBCTestEndCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEndCase::BuildScriptL()
    {
    TInt sdkver = ManualSDKVersion();
    if ( sdkver == 32 || sdkver == 50 )
        {
        AddTestL( LeftCBA, Up, Up, LeftCBA, TEND );
        }
    else
        {
        AddTestL( LeftCBA, Up, LeftCBA, TEND );
        }
    }
