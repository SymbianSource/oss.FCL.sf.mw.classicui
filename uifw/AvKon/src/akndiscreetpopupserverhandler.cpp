/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon discreet popup ui server handler.
*
*/


#include <eikcmobs.h>
#include <avkon.hrh>
#include "akndiscreetpopupserverhandler.h"
#include "akndiscreetpopupdata.h"
#include "akntrace.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknDiscreetPopupServerHandler::NewL
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupServerHandler* CAknDiscreetPopupServerHandler::NewL()
    {
    CAknDiscreetPopupServerHandler* self = 
        CAknDiscreetPopupServerHandler::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupServerHandler::NewLC
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupServerHandler* CAknDiscreetPopupServerHandler::NewLC()
    {
    CAknDiscreetPopupServerHandler* self = 
        new ( ELeave ) CAknDiscreetPopupServerHandler();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupServerHandler::~CAknDiscreetPopupServerHandler
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupServerHandler::~CAknDiscreetPopupServerHandler()
    {
    _AKNTRACE_FUNC_ENTER;
    iLaunchers.ResetAndDestroy();
    iUiServer.Close();
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupServerHandler::LaunchGlobalPopup
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupServerHandler::LaunchGlobalPopupL(
        const TDesC& aTitle,
        const TDesC& aText,
        const TAknsItemID& aSkinId,
        const TDesC& aBitmapFile,
        const TInt& aBitmapId,
        const TInt& aMaskId,
        const TInt& aFlags,
        const TInt& aCommandId,
        const TInt& aPopupId,
        MEikCommandObserver* aCommandObserver,
        const TUid& aAppUid,
        const TUid& aViewUid )
    {
    CAknDiscreetPopupGlobalParamLauncher* launcher = 
        CAknDiscreetPopupGlobalParamLauncher::NewL( this, 
                                                    aCommandObserver, 
                                                    aCommandId,
                                                    aPopupId,
                                                    aAppUid,
                                                    aViewUid );
    CleanupStack::PushL( launcher );
    launcher->SetData(
        aTitle,
        aText,
        aSkinId,
        aBitmapFile,
        aBitmapId,
        aMaskId,
        aFlags );
    iLaunchers.AppendL( launcher );
    CleanupStack::Pop( launcher );
    launcher->LaunchDiscreetPopup();
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupServerHandler::LaunchGlobalPopup
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupServerHandler::LaunchGlobalPopupL(
        const TInt aResourceId,
        const TDesC& aResourceFile,
        const TInt& aCommandId,
        const TInt& aPopupId,
        MEikCommandObserver* aCommandObserver,
        const TUid& aAppUid,
        const TUid& aViewUid )
    {
    CAknDiscreetPopupGlobalResourceLauncher* launcher = 
        CAknDiscreetPopupGlobalResourceLauncher::NewL( this, 
                                                       aCommandObserver, 
                                                       aCommandId,
                                                       aPopupId,
                                                       aAppUid,
                                                       aViewUid );
    CleanupStack::PushL( launcher );
    launcher->SetData( 
            aResourceId,
            aResourceFile );
    iLaunchers.AppendL( launcher );
    CleanupStack::Pop( launcher );
    launcher->LaunchDiscreetPopup();
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupServerHandler::PopupClosed
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupServerHandler::PopupClosed(
        CAknDiscreetPopupGlobalLauncher* aLauncher )
    {
    for ( TInt i = 0; i < iLaunchers.Count(); i++ )
        {
        if ( iLaunchers[ i ] == aLauncher )
            {
            iLaunchers.Remove( i );
            delete aLauncher;
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupServerHandler::UiServer
// ---------------------------------------------------------------------------
//
RAknUiServer* CAknDiscreetPopupServerHandler::UiServer()
    {
    return &iUiServer;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupServerHandler::CheckPopupId
// ---------------------------------------------------------------------------
//
TInt CAknDiscreetPopupServerHandler::CheckPopupId( const TInt& aPopupId )
    {
    TInt popupId( aPopupId );
    while ( PopupIdInUse( popupId ) )
        {
        popupId++;
        }
    return popupId;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupServerHandler::CAknDiscreetPopupServerHandler
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupServerHandler::CAknDiscreetPopupServerHandler()
    {
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupServerHandler::ConstructL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupServerHandler::ConstructL()
    {
    _AKNTRACE_FUNC_ENTER;
    User::LeaveIfError( iUiServer.Connect() );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupServerHandler::PopupIdInUse
// ---------------------------------------------------------------------------
//
TBool CAknDiscreetPopupServerHandler::PopupIdInUse( const TInt& aPopupId )
    {
    TInt popupId( 0 );
    for ( TInt i = 0; i < iLaunchers.Count(); i++ )
        {
        popupId = static_cast<TAknDiscreetPopupLaunchData*>( 
                iLaunchers[ i ]->PopupData() )->PopupId();
        if ( popupId == aPopupId )
            {
            return ETrue;
            }
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalLauncher::~CAknDiscreetPopupGlobalLauncher
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupGlobalLauncher::~CAknDiscreetPopupGlobalLauncher()
    {
    _AKNTRACE( "[%s][%s] Enter ", "CAknDiscreetPopupGlobalLauncher", __FUNCTION__ );
    if ( IsActive() && iHandler )
        {
        // Cancel request using status handle
        TAknDiscreetPopupCancelRequestData cancelData;
        cancelData.SetStatusHandle( ( TUint ) &iStatus );
        iHandler->UiServer()->DoDiscreetPopupAction( &cancelData );
        }
    Cancel();
    _AKNTRACE( "[%s][%s] Exit ", "CAknDiscreetPopupGlobalLauncher", __FUNCTION__ );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalLauncher::LaunchDiscreetPopup
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupGlobalLauncher::LaunchDiscreetPopup()
    {
    _AKNTRACE( "[%s][%s] Enter ", "CAknDiscreetPopupGlobalLauncher", __FUNCTION__ );
    if ( IsActive() )
        {
        _AKNTRACE( "[%s][%s] Exit ", "CAknDiscreetPopupGlobalLauncher", __FUNCTION__ );
        return;
        }
    RenewRequest();
    _AKNTRACE( "[%s][%s] Exit ", "CAknDiscreetPopupGlobalLauncher", __FUNCTION__ );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalLauncher::RunL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupGlobalLauncher::RunL()
    {
    _AKNTRACE( "[%s][%s] Enter,  iStatus : %d", 
    		"CAknDiscreetPopupGlobalLauncher", __FUNCTION__, iStatus.Int() );
    if ( iStatus.Int() != KRequestPending )
        {
        if( iCommandObserver )
        	{
        	if( iStatus.Int() == KErrCompletion && iCommandId )
        		{
        		iCommandObserver->ProcessCommandL( iCommandId );
        		}
        	iCommandObserver->ProcessCommandL( EAknDiscreetPopupCmdClose );
        	}    
        if ( iHandler )
            {
            iHandler->PopupClosed( this );
            }
        }
    else
        {
        RenewRequest();
        }
    _AKNTRACE( "[%s][%s] Exit ", "CAknDiscreetPopupGlobalLauncher", __FUNCTION__ );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalLauncher::DoCancel
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupGlobalLauncher::DoCancel()
    {
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalLauncher::CAknDiscreetPopupGlobalLauncher
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupGlobalLauncher::CAknDiscreetPopupGlobalLauncher(
        CAknDiscreetPopupServerHandler* aHandler, 
        MEikCommandObserver* aObserver,
        const TInt& aCommandId )
    :
    CActive( EPriorityStandard ),
    iCommandObserver( aObserver ),
    iCommandId( aCommandId ),
    iHandler( aHandler )
    {
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalLauncher::ConstructL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupGlobalLauncher::ConstructL()
    {
    CActiveScheduler::Add( this );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalLauncher::RenewRequest
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupGlobalLauncher::RenewRequest()
    {
    if ( iHandler )
        {
        _AKNTRACE( "CAknDiscreetPopupGlobalLauncher::RenewRequest, issue request." );
        iHandler->UiServer()->DoDiscreetPopupAction( PopupData(), &iStatus );
        }
    SetActive();
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalParamLauncher::~CAknDiscreetPopupGlobalParamLauncher
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupGlobalParamLauncher::~CAknDiscreetPopupGlobalParamLauncher()
    {
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalParamLauncher::NewL
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupGlobalParamLauncher* CAknDiscreetPopupGlobalParamLauncher::NewL(
        CAknDiscreetPopupServerHandler* aHandler, 
        MEikCommandObserver* aObserver,
        const TInt& aCommandId,
        const TInt& aPopupId,
        const TUid& aAppUid,
        const TUid& aViewUid )
    {
    _AKNTRACE( "[%s][%s] Enter ", "CAknDiscreetPopupGlobalParamLauncher", __FUNCTION__ );
    CAknDiscreetPopupGlobalParamLauncher* self = 
        new ( ELeave ) CAknDiscreetPopupGlobalParamLauncher(
                aHandler, aObserver, aCommandId, aPopupId, aAppUid, aViewUid );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    _AKNTRACE( "[%s][%s] Exit ", "CAknDiscreetPopupGlobalParamLauncher", __FUNCTION__ );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalParamLauncher::SetData
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupGlobalParamLauncher::SetData(
        const TDesC& aTitle,
        const TDesC& aText,
        const TAknsItemID& aSkinId,
        const TDesC& aBitmapFile,
        const TInt& aBitmapId,
        const TInt& aMaskId,
        const TInt& aFlags )
    {
    iPopupData.SetTitleText( aTitle );
    iPopupData.SetBodyText( aText );
    iPopupData.SetSkinId( aSkinId );
    iPopupData.SetBitmapFile( aBitmapFile );
    iPopupData.SetBitmapId( aBitmapId );
    iPopupData.SetMaskId( aMaskId );
    iPopupData.SetFlags( aFlags );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalParamLauncher::CAknDiscreetPopupGlobalParamLauncher
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupGlobalParamLauncher::CAknDiscreetPopupGlobalParamLauncher(
        CAknDiscreetPopupServerHandler* aHandler,
        MEikCommandObserver* aObserver,
        const TInt& aCommandId,
        const TInt& aPopupId,
        const TUid& aAppUid,
        const TUid& aViewUid )
    : CAknDiscreetPopupGlobalLauncher( aHandler, 
                                       aObserver, 
                                       aCommandId )
    {
    iPopupData.SetPopupId( aPopupId );
    iPopupData.SetAppUid( aAppUid );
    iPopupData.SetViewUid( aViewUid );
    if ( aAppUid == TUid::Null() && !aCommandId )
        {
        iPopupData.SetAction( EFalse );
        }
    else
        {
        iPopupData.SetAction( ETrue );
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalParamLauncher::PopupData
// ---------------------------------------------------------------------------
//
TAknDiscreetPopupData* CAknDiscreetPopupGlobalParamLauncher::PopupData()
    {
    return &iPopupData;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalResourceLauncher::~CAknDiscreetPopupGlobalResourceLauncher
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupGlobalResourceLauncher::~CAknDiscreetPopupGlobalResourceLauncher()
    {
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalResourceLauncher::NewL
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupGlobalResourceLauncher* CAknDiscreetPopupGlobalResourceLauncher::NewL(
        CAknDiscreetPopupServerHandler* aHandler,
        MEikCommandObserver* aObserver,
        const TInt& aCommandId,
        const TInt& aPopupId,
        const TUid& aAppUid,
        const TUid& aViewUid )
    {
    _AKNTRACE( "[%s][%s] Enter ", "CAknDiscreetPopupGlobalResourceLauncher", __FUNCTION__ );
    CAknDiscreetPopupGlobalResourceLauncher* self = 
        new ( ELeave ) CAknDiscreetPopupGlobalResourceLauncher(
                aHandler, aObserver, aCommandId, aPopupId, aAppUid, aViewUid );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    _AKNTRACE( "[%s][%s] Exit ", "CAknDiscreetPopupGlobalResourceLauncher", __FUNCTION__ );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalResourceLauncher::SetData
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupGlobalResourceLauncher::SetData(
        const TInt aResourceId,
        const TDesC& aResourceFile )
    {
    iPopupData.SetResourceFile( aResourceFile );
    iPopupData.SetResourceId( aResourceId );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalResourceLauncher::CAknDiscreetPopupGlobalResourceLauncher
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupGlobalResourceLauncher::CAknDiscreetPopupGlobalResourceLauncher(
        CAknDiscreetPopupServerHandler* aHandler,
        MEikCommandObserver* aObserver,
        const TInt& aCommandId,
        const TInt& aPopupId,
        const TUid& aAppUid,
        const TUid& aViewUid )
    : CAknDiscreetPopupGlobalLauncher( aHandler, 
                                       aObserver, 
                                       aCommandId )
    {
    iPopupData.SetPopupId( aPopupId );
    iPopupData.SetAppUid( aAppUid );
    iPopupData.SetViewUid( aViewUid );
    if ( aAppUid == TUid::Null() && !aCommandId )
        {
        iPopupData.SetAction( EFalse );
        }
    else
        {
        iPopupData.SetAction( ETrue );
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalResourceLauncher::PopupData
// ---------------------------------------------------------------------------
//
TAknDiscreetPopupData* CAknDiscreetPopupGlobalResourceLauncher::PopupData()
    {
    return &iPopupData;
    }

