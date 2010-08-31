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
#include <avkon.hrh>
#include <coecntrl.h>
#include <aknsoundsystem.h>
#include <s32strm.h> 
#include <bctestaknsound.rsg>
#include "bctestaknsoundsystemcase.h"
#include "bctestaknsoundcontainer.h"
#include "bctestaknsound.hrh"

// Constant
const TInt KUid = 100;
const TInt KResourceId = 10;
const TInt KSid = 20;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestAknSoundSystemCase* CBCTestAknSoundSystemCase::NewL( 
    CBCTestAknSoundContainer* aContainer )
    {
    CBCTestAknSoundSystemCase* self = new( ELeave ) CBCTestAknSoundSystemCase( 
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
CBCTestAknSoundSystemCase::CBCTestAknSoundSystemCase( 
    CBCTestAknSoundContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestAknSoundSystemCase::~CBCTestAknSoundSystemCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestAknSoundSystemCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAknSoundSystemCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestAknSoundSystemCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, Down, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAknSoundSystemCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestAknSoundSystemCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline2 || aCmd > EBCTestCmdOutline2 )
        {
        return;
        }

    switch ( aCmd )  
        {
        case EBCTestCmdOutline2:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestAknSoundSystemCase::TestFunctionL
// ---------------------------------------------------------------------------
//    
void CBCTestAknSoundSystemCase::TestFunctionL()
    {
    // Test some API here
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KUid );
    CleanupStack::PushL( aknsoundsystem );
	_LIT ( KBCTestAknSoundSystem, "BCTestAknSound System NewL" );
    AssertNotNullL( aknsoundsystem, KBCTestAknSoundSystem );
    
    aknsoundsystem->PushContextL( KResourceId );
	_LIT ( KInfoPushContext, "BCTestAknSound System PushContextL" );
    AssertNotNullL( aknsoundsystem, KInfoPushContext);
    
    aknsoundsystem->PopContext();
	_LIT ( KInfoPopContext, "BCTestAknSound System PopContext" );
    AssertNotNullL( aknsoundsystem, KInfoPopContext );

    aknsoundsystem->PlaySound( 0x6000 );
	_LIT ( KInfoKeyPlaySound, "BCTestAknSound System PlaySound" );
    AssertNotNullL( aknsoundsystem, KInfoKeyPlaySound );
    
    aknsoundsystem->PlaySound( KSid );
	_LIT ( KInfoPlaySound, "BCTestAknSound System PlaySound2" );
    AssertNotNullL( aknsoundsystem, KInfoPlaySound );
    
    aknsoundsystem->AddAppSoundInfoListL( R_BCTESTAKNSINFO_LIST );
    _LIT ( KAddSoundInfoList, "BCTestAknSound System AddAppSoundInfoListL" );
    AssertNotNullL( aknsoundsystem, KAddSoundInfoList );
   
    aknsoundsystem->BringToForeground();
	_LIT ( KBringToForeground, "BCTestAknSound System BringToForeground" );
    AssertNotNullL( aknsoundsystem, KBringToForeground );
    
    aknsoundsystem->StopSound( KSid );
	_LIT ( KStopSound, "BCTestAknSound System StopSound" );
    AssertNotNullL( aknsoundsystem, KStopSound );
    
    aknsoundsystem->LockContext();
	_LIT ( KLockContext, "BCTestAknSound System LockContext" );
    AssertNotNullL( aknsoundsystem, KLockContext );
    
    aknsoundsystem->ReleaseContext();
	_LIT ( KReleaseContext, "BCTestAknSound System ReleaseContext" );
    AssertNotNullL( aknsoundsystem, KReleaseContext );
    
    CAknSoundInfo *aknsoundinfo = CAknSoundInfo::NewL();
    CleanupStack::PushL( aknsoundinfo );
 	_LIT ( KInfoCreate, "CAknSoundInfo is not NULL" );
    AssertNotNullL( aknsoundinfo, KInfoCreate );  
	_LIT ( KSystemRequest, "AknSoundSystem RequestSoundInfoL" );
	
	// The first parameter should not be less than 1000.
	TInt sInfo = aknsoundsystem->RequestSoundInfoL( EAvkonSIDDefaultSound,
	    *aknsoundinfo );
    AssertIntL( KErrNone, sInfo, KSystemRequest );
    CleanupStack::PopAndDestroy( aknsoundinfo );
    
    CleanupStack::PopAndDestroy(aknsoundsystem);
    }
    
