/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon cap server discreet popup handler.
*
*/

#include <apgtask.h>
#include <coeaui.h>
#include <e32property.h>
#include <avkondomainpskeys.h>

#include "akncapserverdiscreetpopuphandler.h"
#include "akndiscreetpopupcontrol.h"
#include "akndiscreetpopupdata.h"
#include "akntrace.h"

const TUid KAknCapServerDiscreetPopupHandler = { 0x2001FDF8 };

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::~CAknCapServerDiscreetPopupHandler
// ---------------------------------------------------------------------------
//
CAknCapServerDiscreetPopupHandler::~CAknCapServerDiscreetPopupHandler()
    {
    _AKNTRACE_FUNC_ENTER;
    for ( TInt i = 0; i < iPopupDataArray.Count(); i++ )
        {
        if ( iPopupDataArray[ i ].iPopupControl )
            {
            delete iPopupDataArray[ i ].iPopupControl;
            iPopupDataArray[ i ].iPopupControl = NULL;
            }
        }
    iPopupDataArray.Close();    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::HandleDiscreetPopupMessageL
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::HandleDiscreetPopupMessageL( 
        const RMessage2& aMessage )
    {
    _AKNTRACE_FUNC_ENTER;
    CAknCapServerDiscreetPopupHandler* instance 
        = CAknCapServerDiscreetPopupHandler::InstanceL();
    if ( instance )
        {
        instance->DoHandleDiscreetPopupMessageL( aMessage );
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::CreateDiscreetPopupHandlerL
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::CreateDiscreetPopupHandlerL()
    {
    _AKNTRACE_FUNC_ENTER;
    CAknCapServerDiscreetPopupHandler* instance 
        = CAknCapServerDiscreetPopupHandler::InstanceL();
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::CAknCapServerDiscreetPopupHandler
// ---------------------------------------------------------------------------
//
CAknCapServerDiscreetPopupHandler::CAknCapServerDiscreetPopupHandler() 
    : 
    CCoeStatic( KAknCapServerDiscreetPopupHandler, CCoeStatic::EThread ),
    iAppUi( CCoeEnv::Static()->AppUi() )
    {
    }


// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::ConstructL
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::ConstructL()
    {
    }


// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::InstanceL
// ---------------------------------------------------------------------------
//
CAknCapServerDiscreetPopupHandler* CAknCapServerDiscreetPopupHandler::InstanceL()
    {
    CAknCapServerDiscreetPopupHandler* instance = 
        static_cast<CAknCapServerDiscreetPopupHandler*>( 
            CCoeEnv::Static( KAknCapServerDiscreetPopupHandler ) );
    if ( !instance )
        {
        instance = new ( ELeave ) CAknCapServerDiscreetPopupHandler;
        CleanupStack::PushL( instance );
        instance->ConstructL();
        CleanupStack::Pop( instance );
        }
    return instance;
    }


// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::DoLaunchDiscreetPopupL
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::DoHandleDiscreetPopupMessageL(
    const RMessage2& aMessage )
    {
    _AKNTRACE_FUNC_ENTER;
    TAknDiscreetPopupData dataType;
    TPckg<TAknDiscreetPopupData> pkgType( dataType );
    aMessage.ReadL( 0, pkgType );
    switch ( dataType.Type() )
        {
        case ( TAknDiscreetPopupData::EAknPopupTypeResource ):
            {
            LaunchFromResourceL( aMessage );
            break;
            }
        case ( TAknDiscreetPopupData::EAknPopupTypeParam ):
            {
            LaunchWithParamsL( aMessage );
            break;
            }
        case ( TAknDiscreetPopupData::EAknPopupTypeCancelRequest ):
            {
            HandleRequestCancellationL( aMessage );
            break;
            }
        case ( TAknDiscreetPopupData::EAknPopupTypeQueryInUseRect ):
            {
            HandleQueryInUseRectL( aMessage );
            break;
            }        
        default:
            {
            break;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::LaunchFromResourceL
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::LaunchFromResourceL(  
        const RMessage2& aMessage )
    {
    _AKNTRACE_FUNC_ENTER;
    TAknDiscreetPopupResourceData data;
    TPckg<TAknDiscreetPopupResourceData> pkg( data );
    aMessage.ReadL( 0, pkg );

    MEikCommandObserver* observer( NULL );
    TInt commandId( 0 );
    if ( data.Action() )
        {
        commandId = NextAvailableCommandId();
        observer = this;
        }

    CAknDiscreetPopupControl* popup = 
        CAknDiscreetPopupControl::NewL( 
                ETrue,
                data.ResourceId(),
                data.ResourceFile(),
                commandId,
                data.PopupId(),
                observer );
    CleanupStack::PushL( popup );
    ShowPopupL( commandId,
        popup,
        data.AppUid(),
        data.ViewUid(),
        aMessage );
    CleanupStack::Pop( popup );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::LaunchWithParamsL
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::LaunchWithParamsL(  
        const RMessage2& aMessage )
    {
    _AKNTRACE_FUNC_ENTER;
    TAknDiscreetPopupParamData data;
    TPckg<TAknDiscreetPopupParamData> pkg( data );
    aMessage.ReadL( 0, pkg );

    MEikCommandObserver* observer( NULL );
    TInt commandId( 0 );
    if ( data.Action() )
        {
        commandId = NextAvailableCommandId();
        observer = this;
        }

    CAknDiscreetPopupControl* popup = 
        CAknDiscreetPopupControl::NewL( 
                ETrue,
                data.TitleText(),
                data.BodyText(),
                NULL,
                data.SkinId(),
                data.BitmapFile(),
                data.BitmapId(),
                data.MaskId(),
                data.Flags(),
                commandId,
                data.PopupId(),
                observer );
    CleanupStack::PushL( popup );
    ShowPopupL( commandId,
        popup,
        data.AppUid(),
        data.ViewUid(),
        aMessage );
    CleanupStack::Pop( popup );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::HandleRequestCancellationL
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::HandleRequestCancellationL(  
        const RMessage2& aMessage )
    {
    _AKNTRACE_FUNC_ENTER;
    TAknDiscreetPopupCancelRequestData data;
    TPckg<TAknDiscreetPopupCancelRequestData> pkg( data );
    aMessage.ReadL( 0, pkg );
    
    for ( TInt i = 0; i < iPopupDataArray.Count(); i++ )
        {
        if ( !iPopupDataArray[ i ].iMessage.IsNull()
                && ( TUint ) iPopupDataArray[ i ].iMessage.ClientStatus() 
                == data.StatusHandle() )
            {
            iPopupDataArray[ i ].iMessage.Complete( KErrNone );
            if ( !iPopupDataArray[ i ].iPopupControl->IsVisible() )
                {
                delete iPopupDataArray[ i ].iPopupControl;
                iPopupDataArray[ i ].iPopupControl = NULL;
                iPopupDataArray.Remove( i );
                NotifyRunningGlobalDiscreetPopupChanged();
                break;
                }
            }
        }
    aMessage.Complete( KErrNone );
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::HandleQueryInUseRectL
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::HandleQueryInUseRectL( 
        const RMessage2& aMessage )
    {
    _AKNTRACE_FUNC_ENTER;
    TRect rect(TRect::EUninitialized);
    if( iPopupDataArray.Count() != 0 ) 
        {
        rect = iPopupDataArray[0].iPopupControl->Rect();
        }
    
    TAknDiscreetPopupRectData data(rect);
    TPckg<TAknDiscreetPopupRectData> pkg( data );
    aMessage.WriteL( 0, pkg );
    aMessage.Complete( KErrNone );
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::ShowPopupL
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::ShowPopupL(
        const TInt& aCommandId,
        CAknDiscreetPopupControl* aPopup,
        const TUid& aAppUid,
        const TUid& aViewUid,
        const RMessage2& aMessage )
    {
    _AKNTRACE_FUNC_ENTER;
    aPopup->SetObserver( this );

    // Inform other popups that new popup is launched
    for ( TInt i = 0; i < iPopupDataArray.Count(); i++ )
        {
        iPopupDataArray[ i ].iPopupControl->HandleDiscreetPopupActionL( 
            CAknDiscreetPopupControl::EAknDiscreetPopupAnotherLaunched );
        }

    aPopup->HandleDiscreetPopupActionL( 
        CAknDiscreetPopupControl::EAknDiscreetPopupShow );

    // Show popup and add it to popup list
    TAknCapServerDiscreetPopupData popupData;
    popupData.iCommandId = aCommandId;
    popupData.iPopupControl = aPopup;
    popupData.iAppUid = aAppUid;
    popupData.iViewUid = aViewUid;
    popupData.iMessage = aMessage;
    iPopupDataArray.AppendL( popupData );
    NotifyRunningGlobalDiscreetPopupChanged();
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::NextAvailableCommandId
// ---------------------------------------------------------------------------
//
TInt CAknCapServerDiscreetPopupHandler::NextAvailableCommandId()
    {
    TBool idFoundInArray( ETrue );
    TInt commandId( 0 );
    
    while ( idFoundInArray )
        {
        commandId++;
        idFoundInArray = EFalse;
        for ( TInt i = 0; i < iPopupDataArray.Count(); i++ )
            {
            if ( iPopupDataArray[ i ].iCommandId == commandId )
                {
                idFoundInArray = ETrue;
                break;
                }
            }
        }
    return commandId;
    }

// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::NotifyRunningGlobalDiscreetPopupChanged
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::NotifyRunningGlobalDiscreetPopupChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    _LIT_SECURITY_POLICY_S0( writePolicy, RProcess().SecureId() );
	_LIT_SECURITY_POLICY_PASS( readPolicy );
    
    TInt err = RProperty::Define( KPSUidAvkonDomain, 
                                  KAknGlobalDiscreetPopupNumChanged, 
                                  RProperty::EInt, 
                                  readPolicy, 
                                  writePolicy );

    if( err == KErrAlreadyExists || err == KErrNone )
        {
        RProperty::Set( KPSUidAvkonDomain, KAknGlobalDiscreetPopupNumChanged, 0 );
        }            
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::ProcessCommandL
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::ProcessCommandL( TInt aCommandId )
    {
    _AKNTRACE_FUNC_ENTER;
    TAknCapServerDiscreetPopupData* popupData( NULL );
    for ( TInt i = 0; i < iPopupDataArray.Count(); i++ )
        {
        if ( iPopupDataArray[ i ].iCommandId == aCommandId )
            {
            popupData = &iPopupDataArray[ i ];
            break;
            }
        }

    // If client has defined application uid, it should be launched when the
    // command is handled
    if ( popupData && popupData->iAppUid != TUid::Null() && iAppUi )
        {
        TApaTaskList taskList( CCoeEnv::Static()->WsSession() );
        TApaTask task = taskList.FindApp( popupData->iAppUid );
        
        if ( task.Exists() && popupData->iViewUid == TUid::Null() )
            {
            task.BringToForeground();
            }
        else
            {
            iAppUi->CreateActivateViewEventL(
            TVwsViewId( popupData->iAppUid, popupData->iViewUid ),
            TUid::Null(),
            KNullDesC8() );   
            }        

        }
    if ( popupData && !popupData->iMessage.IsNull() )
        {
        popupData->iMessage.Complete( KErrCompletion );
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknCapServerDiscreetPopupHandler::HandleControlEventL
// ---------------------------------------------------------------------------
//
void CAknCapServerDiscreetPopupHandler::HandleControlEventL( 
    CCoeControl* aControl, TCoeEvent aEventType )
    {
    _AKNTRACE( "CAknCapServerDiscreetPopupHandler::HandleControlEventL, aEventType : %d", aEventType );
    // Popup has been closed or cancelled - remove from array
    if ( aEventType == EEventRequestExit || aEventType == EEventRequestCancel )
        {
        for ( TInt i = 0; i < iPopupDataArray.Count(); i++ )
            {
            if ( iPopupDataArray[ i ].iPopupControl == aControl )
                {
                if ( !iPopupDataArray[ i ].iMessage.IsNull() )
                    {
                    iPopupDataArray[ i ].iMessage.Complete( KErrNone );
                    }
                delete iPopupDataArray[ i ].iPopupControl;
                iPopupDataArray[ i ].iPopupControl = NULL;
                iPopupDataArray.Remove( i );
                NotifyRunningGlobalDiscreetPopupChanged();
                break;
                }
            }
        }
    }
