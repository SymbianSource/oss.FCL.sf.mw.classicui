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
* Description:  Loads browser launcher dynamically.
*
*/


#include <e32base.h>
#include <w32std.h>
#include <apgcli.h>
#include <apgtask.h>
#include <FavouritesDb.h>

#include "pslnbrowserlaunchloader.h"
#include "PslnConst.h"

//Browser UID
const TUid KUidBrowser = { 0x10008D39 };
const TInt KPslnBrowserParamLen = 20;
_LIT( KPslnBrowserPrefix, "6 " );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnBrowserLaunchLoader::CPslnBrowserLaunchLoader()
    {
    }

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CPslnBrowserLaunchLoader* CPslnBrowserLaunchLoader::NewL()
    {
    CPslnBrowserLaunchLoader* self = 
        new( ELeave ) CPslnBrowserLaunchLoader();

    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CPslnBrowserLaunchLoader::~CPslnBrowserLaunchLoader()
    {
    }

// ---------------------------------------------------------------------------
// Launch browser as standalone application.
// ---------------------------------------------------------------------------
//
void CPslnBrowserLaunchLoader::LaunchBrowserStandaloneL( )
    {
   
    HBufC* param = HBufC::NewLC( KPslnBrowserParamLen );
    param->Des().Copy( KPslnBrowserPrefix );
    TInt folderid = GetFolderIdByContextIdL( KFavouritesSkinContextId );
    param->Des().AppendNum( folderid );
    
    RWsSession wsSession;
    User::LeaveIfError( wsSession.Connect() );
    CleanupClosePushL<RWsSession>( wsSession );
    TApaTaskList taskList( wsSession );
    TApaTask task = taskList.FindApp( KUidBrowser );
    
    if ( task.Exists() )
        {
        HBufC8* param8 = HBufC8::NewLC( param->Length() );
        param8->Des().Append( param->Des() );
        task.SendMessage( TUid::Uid( 0 ), *param8 ); // Uid is not used
        CleanupStack::PopAndDestroy( param8 );
        }
    else 
        {
        RApaLsSession appArcSession;
        User::LeaveIfError( appArcSession.Connect() );
        CleanupClosePushL<RApaLsSession>( appArcSession );
        TThreadId id;
        appArcSession.StartDocument( *param, KUidBrowser , id ); 
        CleanupStack::PopAndDestroy(); // appArcSession
        }
     
    CleanupStack::PopAndDestroy( 2 );  // param,wsSession
    }

// ---------------------------------------------------------------------------
// Cancel download.
// ---------------------------------------------------------------------------
//
void CPslnBrowserLaunchLoader::CancelDownload()
    {
    }

// ---------------------------------------------------------------------------
// Gets browser bookmark folder id.
// ---------------------------------------------------------------------------
//
TInt CPslnBrowserLaunchLoader::GetFolderIdByContextIdL( TUint32 aContextId )
    {
    TInt folder = KFavouritesNullUid;
    if ( aContextId != (TUint32)KFavouritesNullContextId )
        {
        CArrayFix<TInt>* uids = new (ELeave) CArrayFixFlat<TInt>( 1 );
        CleanupStack::PushL( uids );

        RFavouritesDb db;
        RFavouritesSession iFavouritesSess;
        User::LeaveIfError( iFavouritesSess.Connect() ); 
        CleanupClosePushL<RFavouritesSession>( iFavouritesSess );
        User::LeaveIfError( db.Open( iFavouritesSess, KBrowserBookmarks ) );
        CleanupClosePushL<RFavouritesDb>( db );
        User::LeaveIfError( db.GetUids( *uids, KFavouritesNullUid,
                CFavouritesItem::EFolder, NULL, aContextId ) );

        if( uids->Count() > 0 )
           {
           folder = uids->At( 0 );
           }
        CleanupStack::PopAndDestroy( 3 );   // db,iFavouritesSess,uids
        }
    return folder;
    }

//----------------------------------------------------------------------------   
// Launcher gate function
//----------------------------------------------------------------------------
EXPORT_C TAny* GateFunction()
    {
    CPslnBrowserLaunchLoader* launcher = NULL;
    TRAPD( err, launcher = CPslnBrowserLaunchLoader::NewL() );
    if( err != KErrNone )
        {
        return NULL;
        }

    return launcher;
    }

//  End of File  
