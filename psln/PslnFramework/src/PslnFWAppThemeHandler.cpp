/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Handles interface towards XUIKON, sets and gets theme information.
*
*/



// INCLUDE FILES

// Psln Framework
#include    <PslnFWAppThemeHandler.h>
#include    <MPslnFWAppThemeObserver.h>
#include    "PslnXNClientLoader.h"

// Constants
#include    "PslnConst.h"
#include    "PslnDebug.h"

// Xuikon
#include    <XnODT.h>

#include    <AknEnv.h>

// CONTANTS
// Path to wrapper dll for XnClient.
_LIT( KPslnXuikonClientLoaderName, 
     "\\system\\libs\\PslnXNClientLoader.dll");

// TYPE DEFINITIONS
// Xuikon client loader.
typedef TAny* (*NewXuikonClientL)();

// -----------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnFWAppThemeHandler::CPslnFWAppThemeHandler( 
    MPslnFWAppThemeObserver& aObserver,
    CArrayPtrFlat<CXnODT>& aApplicationSkinList ) : 
    iObserver( aObserver ), iAppThemeList( &aApplicationSkinList )
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnFWAppThemeHandler::ConstructL()
    {
    PSLN_TRACE_DEBUG("CPslnFWAppThemeHandler::ConstructL BEGIN");
    PSLN_TRACE_DEBUG("CPslnFWAppThemeHandler::ConstructL END");
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnFWAppThemeHandler* CPslnFWAppThemeHandler::NewL
    ( MPslnFWAppThemeObserver& aObserver,
      CArrayPtrFlat<CXnODT>& aApplicationSkinList )
    {
    CPslnFWAppThemeHandler* self = 
        new( ELeave ) CPslnFWAppThemeHandler( aObserver, aApplicationSkinList );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;
    }


// Destructor
CPslnFWAppThemeHandler::~CPslnFWAppThemeHandler()
    {
    PSLN_TRACE_DEBUG("CPslnFWAppThemeHandler destructor BEGIN");
    // deleting iXnClientLoader automatically cancels all existing fetches.
    delete iXnClientLoader;
    if( iXnClientDllLoaded )
        {
        iXnClientDll.Close();
        }
    PSLN_TRACE_DEBUG("CPslnFWAppThemeHandler destructor END");
    // do not destroy iAppThemeList - it is owned by application.
    }

// -----------------------------------------------------------------------------
// Collect application specific themes from server.
// -----------------------------------------------------------------------------
//
EXPORT_C TXnServiceCompletedMessage CPslnFWAppThemeHandler::GetApplicationSkinsL( 
    TUid aUid )
    {
    PSLN_TRACE_DEBUG("CPslnFWAppThemeHandler::GetApplicationSkinsL BEGIN");
    if ( !iXnClientLoader )
        {
        CreateXnClientL();
        }    
    // Remember to cancel first. CPslnFWAppThemeHandler only supports one 
    // active request per application.
    if ( iFetchOngoing )
        {
        return EXnServiceRequestError;
        }

    // Clear previous fetch first.
    iFetchOngoing = ETrue;
    if ( iAppThemeList )
        {
        iAppThemeList->ResetAndDestroy();
        }

    // Start looking for application skins.
    CXnODT* odt = CreateODTFromAppUidLC( aUid );
    TXnServiceCompletedMessage ret =
        iXnClientLoader->GetListHeaders( *odt, *iAppThemeList ); 

    if ( ret == EXnGetListHeadersSuccess )
        {
        // There are existing application specific skins. 
        // Let's start looking for these.
        iXnClientLoader->GetNextHeader();
        }
    else if ( ret == EXnGetListHeadersEmpty )
        {
        // There are no application specific skins now, but
        // let's start to wait if some would appear later.
        iXnClientLoader->GetNextHeader();
        }
    else if ( ret == EXnGetListHeadersFailed || ret == EXnServiceRequestError )
        {
        // Error.
        PSLN_TRACE_DEBUG("CPslnFWAppThemeHandler::GetApplicationSkinsL Error");
        }
    else
        {
        PSLN_TRACE_DEBUG("CPslnFWAppThemeHandler::GetApplicationSkinsL Empty else");
        }

    CleanupStack::PopAndDestroy( odt );
    return ret;
    }

// -----------------------------------------------------------------------------
// Sets application specific theme.
// -----------------------------------------------------------------------------
//
EXPORT_C TXnServiceCompletedMessage CPslnFWAppThemeHandler::SetApplicationSkinL( 
    CXnODT& aThemeODT )
    {
    PSLN_TRACE_DEBUG("CPslnFWAppThemeHandler::SetApplicationSkinL BEGIN");
    if ( !iXnClientLoader )
        {
        CreateXnClientL();
        }

    CXnODT* odt = CXnODT::NewL();
    CleanupStack::PushL( odt );

    TXnServiceCompletedMessage ret = 
        iXnClientLoader->SetActiveTheme( aThemeODT, *odt );

    CleanupStack::PopAndDestroy( odt );
    return ret;
    }

// -----------------------------------------------------------------------------
// CPslnFWAppThemeHandler::CancelGetApplicationSkins
// 
// -----------------------------------------------------------------------------
//
EXPORT_C void CPslnFWAppThemeHandler::CancelGetApplicationSkins()
    {
    PSLN_TRACE_DEBUG("CPslnFWAppThemeHandler::CancelGetApplicationSkins BEGIN");
    iFetchOngoing = EFalse;
    if ( iXnClientLoader )
        {
        iXnClientLoader->CancelGetListHeaders(); 
        }   
    }

EXPORT_C TXnServiceCompletedMessage CPslnFWAppThemeHandler::SetApplicationSkinAndExitL( 
    CXnODT& aThemeODT )
    {
    TXnServiceCompletedMessage ret = SetApplicationSkinL( aThemeODT );
    if ( ret ==  EXnSetActiveThemeSuccess )
        {
        CAknEnv::RunAppShutter();
        }    
    return ret;
    }

// -----------------------------------------------------------------------------
// Xuikon theme manager callback.
// -----------------------------------------------------------------------------
//
void CPslnFWAppThemeHandler::HandleXnClientMessage( 
    TXnServiceCompletedMessage aMessage )
    {
    PSLN_TRACE_DEBUG("CPslnFWAppThemeHandler::HandleXnClientMessage BEGIN");   
    switch ( aMessage )
        {
        case EXnGetListHeadersEmpty:
            // notify client that there are no themes available. 
            // Destroy possible previously available skins
            iObserver.HandleMessage( aMessage );
            if ( iAppThemeList )
                {
                iAppThemeList->ResetAndDestroy();
                }
            break;
        case EXnGetListHeadersFailed:
            // notify client that observation has been stopped
            iObserver.HandleMessage( aMessage );
            CancelGetApplicationSkins();
            break;
        case EXnServiceRequestCanceled:
        case EXnServiceRequestError:
            // notify client about possible error cause.
            iObserver.HandleMessage( aMessage );
            break;
        case EXnGetListHeadersUpdate:
            // give the client the new list.
            // Fall through
        case EXnGetListHeadersRestart:
            // notify client that old list is now not valid, and the new list needs to
            // be used.
            // Fall through
        default:
            iObserver.HandleMessage( aMessage, *iAppThemeList );
            break;
        }
    }

// -----------------------------------------------------------------------------
// Creates ODT based on application UID. 
// 
// -----------------------------------------------------------------------------
//
CXnODT* CPslnFWAppThemeHandler::CreateODTFromAppUidLC( TUid aUid )
    {
    PSLN_TRACE_DEBUG("CPslnFWAppThemeHandler::CreateODTFromAppUidLC BEGIN");
    CXnODT* odt = CXnODT::NewL();
    CleanupStack::PushL( odt );
    odt->SetAppUid( aUid.iUid ); // the UID of the application
    odt->SetProviderUid( Nokia_VID ); // all provided by Nokia
    return odt;
    }

// -----------------------------------------------------------------------------
// Creates XUIKON Client interface.
// 
// -----------------------------------------------------------------------------
//
void CPslnFWAppThemeHandler::CreateXnClientL()
    {    
    // Xuikon Client dll loading.
    if( !iXnClientDllLoaded )
        {
        if( iXnClientDll.Load( KPslnXuikonClientLoaderName ) == KErrNone )
            {
            iXnClientDllLoaded = ETrue;
            // Request the entry function
            NewXuikonClientL xuikonClient = 
                (NewXuikonClientL) iXnClientDll.Lookup( KPslnDllEntryPoint );
            if( xuikonClient )
                {
                // Create the class
                iXnClientLoader = 
                    (CPslnXNClientLoader*) (*xuikonClient)();
                }
            }
        }
    // The wrapper failed to load.
    if ( !iXnClientLoader )
        {
        User::Leave( KErrNotFound );
        }
    iXnClientLoader->CreateClientL( *this );
    }
//  End of File
