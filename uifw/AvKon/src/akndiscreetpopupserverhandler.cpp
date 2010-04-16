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
    iLaunchers.ResetAndDestroy();
    iUiServer.Close();
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
    launcher->SetData(
        aTitle,
        aText,
        aSkinId,
        aBitmapFile,
        aBitmapId,
        aMaskId,
        aFlags );
    iLaunchers.AppendL( launcher );
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
    launcher->SetData( 
            aResourceId,
            aResourceFile );
    iLaunchers.AppendL( launcher );
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
    User::LeaveIfError( iUiServer.Connect() );
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
    if ( IsActive() && iHandler )
        {
        // Cancel request using status handle
        TAknDiscreetPopupCancelRequestData cancelData;
        cancelData.SetStatusHandle( ( TUint ) &iStatus );
        iHandler->UiServer()->DoDiscreetPopupAction( &cancelData );
        }
    Cancel();
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalLauncher::LaunchDiscreetPopup
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupGlobalLauncher::LaunchDiscreetPopup()
    {
    if ( IsActive() )
        {
        return;
        }
    RenewRequest();
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupGlobalLauncher::RunL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupGlobalLauncher::RunL()
    {
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
    CAknDiscreetPopupGlobalParamLauncher* self = 
        new ( ELeave ) CAknDiscreetPopupGlobalParamLauncher(
                aHandler, aObserver, aCommandId, aPopupId, aAppUid, aViewUid );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
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
    CAknDiscreetPopupGlobalResourceLauncher* self = 
        new ( ELeave ) CAknDiscreetPopupGlobalResourceLauncher(
                aHandler, aObserver, aCommandId, aPopupId, aAppUid, aViewUid );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
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

