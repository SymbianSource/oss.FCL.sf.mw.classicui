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
#include <aknsoundinfo.h>
#include <s32strm.h> 
#include "bctestaknsoundinfocase.h"
#include "bctestaknsoundcontainer.h"
#include "bctestaknsound.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestAknSoundInfoCase* CBCTestAknSoundInfoCase::NewL( 
    CBCTestAknSoundContainer* aContainer )
    {
    CBCTestAknSoundInfoCase* self = new( ELeave ) CBCTestAknSoundInfoCase( 
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
CBCTestAknSoundInfoCase::CBCTestAknSoundInfoCase( 
    CBCTestAknSoundContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestAknSoundInfoCase::~CBCTestAknSoundInfoCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestAknSoundInfoCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAknSoundCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestAknSoundInfoCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAknSoundCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestAknSoundInfoCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }

    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestAknSoundCase::TestFunctionL
// ---------------------------------------------------------------------------
//    
void CBCTestAknSoundInfoCase::TestFunctionL()
    {
    // Test some API here
    CAknSoundInfo *aknsoundinfo = CAknSoundInfo::NewL();
	_LIT (KNewL, "BCTestAknSoundInfo::NewL");
    AssertNotNullL( aknsoundinfo, KNewL);
    
    RReadStream readstream;
    aknsoundinfo->InternalizeL( readstream );
	_LIT (KInternalizeL, "BCTestAknSoundInfo::InternalizeL");
    AssertNotNullL( aknsoundinfo, KInternalizeL);
    
    RWriteStream writestream;
    aknsoundinfo->ExternalizeL( writestream );
	_LIT (KExternalizeL, "BCTestAknSoundInfo::ExternalizeL");
    AssertNotNullL( aknsoundinfo, KExternalizeL);
    delete aknsoundinfo;    
    }
    
