/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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









#include <apgtask.h>
#include <eikappui.h>
#include <sysutil.h>
#include <s32file.h>

#include "bctestapplication.h"
#include "bctestlauncher.hrh"
#include "bcteststrmlogger.h"

#include <e32property.h>
using namespace BCTest; 

const TInt KDelay = 500*1000;   //500 ms
const TUid KPSUidAvkonDomainForBC = { 0x10207218 }; // Same as KPSUidAvkonDomain
const TUint32 KAknMenuOptionNoTaskSwapper = 0x10000002;

enum TAknMenuOptionNoTaskSwapper
    {
    ETaskSwapper,
    ENoTaskSwapper
    };

// ================================== local functions ========================
inline static void Wait(TInt aSec)
    {
    User::After(aSec*KDelay*2);
    }

inline static void Wait()
    {
    User::After( KDelay );
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
static TInt SDKVersion()
	{
	TInt swver = 30;
    TInt taskSwapper( ENoTaskSwapper ) ;// taskSwapper
    TInt result = RProperty::Get( KPSUidAvkonDomainForBC, 
            KAknMenuOptionNoTaskSwapper, taskSwapper );
    TInt ret = RProperty::Define( KPSUidAvkonDomainForBC,
            KAknMenuOptionNoTaskSwapper, RProperty::EInt );
    if (ret == KErrAlreadyExists)
        {
        if ( result == KErrNotFound )
            {
            swver = 30;
            }
        else
            {
            if ( taskSwapper == 0 )
                {
                swver = 50;
                }
            else
                {
                swver = 30;
                }
            }
        }
    else
        {
        RProperty::Set( KPSUidAvkonDomainForBC,
                KAknMenuOptionNoTaskSwapper, ENoTaskSwapper );
        }
    
    return swver;
	}

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestApplication::CBCTestApplication(
    const TDesC& aName, TInt aAppUID, TInt aViewUID, 
	TInt aTimeout, TInt aVersion):
      iName(aName), iAppUID(aAppUID), iViewUID(aViewUID), iTimeout(aTimeout),
	  iVersion(aVersion),
	  iSelected(EFalse)
    {
    }

// ---------------------------------------------------------------------------
// CBCTestApplication::~CBCTestApplication()
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestApplication::~CBCTestApplication()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestApplication::NewL()
// 
// ---------------------------------------------------------------------------
//
CBCTestApplication* CBCTestApplication::NewL( const TDesC& aName, 
            TInt aAppUID, TInt aViewUID, TInt aTimeout, TInt aVersion )
    {
    CBCTestApplication* self= new ( ELeave ) CBCTestApplication( 
        aName, aAppUID, aViewUID, aTimeout, aVersion );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestApplication::RunL. 
// ---------------------------------------------------------------------------
//
void CBCTestApplication::RunL( TInt aCommand )
    {
	if( iVersion > SDKVersion() )
		{
		if ( iVersion > ManualSDKVersion() )
			{
		return;
			}
		}
		
    if( iSelected || aCommand == EAutoTestAll )
        {
        SetupL();
        StartAutoTest();    
        WatchDogL();
        TearDown();
        }
    }

// ---------------------------------------------------------------------------
// CBCTestApplication::SetupL. 
// ---------------------------------------------------------------------------
//
void CBCTestApplication::SetupL()
    {
    TInt mem = GetFreeMem();
    
    CEikonEnv::Static()->EikAppUi()->ActivateViewL(
        TVwsViewId(TUid::Uid(iAppUID), TUid::Uid(iViewUID)));
    
    LOG<<iName<<_L("[SDK ")<<SDKVersion()<<_L("]: start, with memory: ")
        << mem << EndLine << End;
    }

// ---------------------------------------------------------------------------
// CBCTestApplication::StartAutoTest. 
// by simulate menu operations  
// ---------------------------------------------------------------------------
//
void CBCTestApplication::StartAutoTest()
    {
    Wait(2);
    KeyPress( EKeyDevice0, EStdKeyDevice0 ); // open menu
    
    TInt sdkVer = SDKVersion();
    TInt loop = 2;
    if ( ( sdkVer == 32 ) || ( sdkVer == 33 ) || ( sdkVer == 50 )  )
        {
        loop = 3;
        }
    for ( TInt i = 0; i < loop; i++ )
        {
        Wait();
        KeyPress( EKeyUpArrow, EStdKeyUpArrow );        
        }

    Wait();
    KeyPress( EKeyDevice0, EStdKeyDevice0 ); // start autotest
    }

// ---------------------------------------------------------------------------
// CBCTestApplication::WatchDogL. 
// ---------------------------------------------------------------------------
//
void CBCTestApplication::WatchDogL()
    {
    TInt durationCount = iTimeout*6*5;
    TApaTaskList taskList(CEikonEnv::Static()->WsSession());
    while (taskList.FindApp(TUid::Uid(iAppUID)).Exists() && durationCount--)
        {
        Wait(2);	//monitor every 2 seconds
        }

    if ( taskList.FindApp( TUid::Uid( iAppUID ) ).Exists() ) 
        {
        // still alive, kill it!
        taskList.FindApp( TUid::Uid( iAppUID ) ).KillTask();
        // wait for application actually killed
        while ( taskList.FindApp( TUid::Uid( iAppUID ) ).Exists() )
            {
            Wait();
            }
        User::Leave( KErrTimedOut );
        }
    }

void CBCTestApplication::TearDown()
    {
    LOG<<iName<<_L(": End with memory: ")
            <<GetFreeMem()<<EndLine<<End;
    }

// ---------------------------------------------------------------------------
// CBCTestRunner::KeyPress(TInt aCode, TInt aScanCode)
// Simulates keypress event
// ---------------------------------------------------------------------------
//
void CBCTestApplication::KeyPress( TInt aCode, TInt aScanCode )
    {
    User::ResetInactivityTime();// Reset user inactivity timers
    TKeyEvent event = { aCode, aScanCode, 0, 0 };
    CEikonEnv::Static()->WsSession().SimulateKeyEvent(event);
    CEikonEnv::Static()->WsSession().Flush();
    }

// ---------------------------------------------------------------------------
// CBCTestRunner::GetFreeMem()
// ---------------------------------------------------------------------------
//
TInt CBCTestApplication::GetFreeMem()
	{
	User::CompressAllHeaps();
	TMemoryInfoV1Buf meminfo;
	UserHal::MemoryInfo( meminfo );
	return meminfo().iFreeRamInBytes;
	}

