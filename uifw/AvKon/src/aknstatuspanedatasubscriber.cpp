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
* Description:  Implementation for the status pane data subscriber, which
*                updates the data of system controlled sub-panes when
*                their state changes.
*
*/


// SYSTEM INCLUDE FILES
#include <e32property.h>
#include <AknCapServerClient.h>
#include <eikapp.h>
#include <eikappui.h>
#include <coemain.h>

// USER INCLUDE FILES
#include "aknstatuspanedatasubscriber.h"
#include "avkoninternalpskeys.h"
#include "aknstatuspanedata.h"
#include "aknstatuspanedataobserver.h"
#include "AknSgcc.h"
#include "AknDef.h"
#include "AknIncallStatusBubble.h"

class CAknStatusPaneSubscriberData : public CBase
    {
public:
    CAknStatusPaneSubscriberData() {};
    ~CAknStatusPaneSubscriberData() {};
public:
    TAknStatusPaneStateData iData;
    };

/**
 * Class to monitor window server events.
 */
NONSHARABLE_CLASS( CAknStatusPaneDataSubscriber::TWsEventObserver )
    : public MCoeMessageMonitorObserver
    {
    public:

        /**
         * Constructor.
         * @param  aSubs  Reference to subscriber.
         */
        TWsEventObserver( CAknStatusPaneDataSubscriber& aSubs );

    public:

        /**
         * From @c MCoeMessageMonitorObserver, this method is called
         * when a window server event is received.
         * @param  aEvent  received event.
         */
        virtual void MonitorWsMessage( const TWsEvent& aEvent );

    private:

        /** Now owned. Reference to subscriber.*/
        CAknStatusPaneDataSubscriber& iSubs;
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::NewL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C CAknStatusPaneDataSubscriber* CAknStatusPaneDataSubscriber::NewL()
    {
    CAknStatusPaneDataSubscriber* self =
        new (ELeave) CAknStatusPaneDataSubscriber();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::ConstructL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataSubscriber::ConstructL()
    {
    // We create an unique id for this container, use app uid for that.
    CEikonEnv* eikEnv = CEikonEnv::Static();
    CEikAppUi* app = eikEnv->EikAppUi();
    if ( app )
        {
        CEikApplication* application = app->Application();
        if ( application )
            {
            iSubscriberId = application->AppDllUid().iUid;
            }
        }

    User::LeaveIfError( iProperty.Attach( KPSUidAvkonInternal,
                                          KAknStatusPaneSystemData) );
    DoSubscribe();
    iStatusPaneStateData = new (ELeave) CAknStatusPaneSubscriberData();

    iObserver = new (ELeave) TWsEventObserver( *this );
    eikEnv->AddMessageMonitorObserverL( *iObserver );
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::CAknStatusPaneDataSubscriber
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknStatusPaneDataSubscriber::CAknStatusPaneDataSubscriber()
    :CActive( EPriorityStandard )
    {
    CActiveScheduler::Add( this );
    iRefreshLevel = ERefreshLevelMedium;
    }


// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknStatusPaneDataSubscriber::~CAknStatusPaneDataSubscriber()
    {
    CEikonEnv* eikEnv = CEikonEnv::Static();
    if ( eikEnv && iObserver )
        {
        eikEnv->RemoveMessageMonitorObserver( *iObserver );
        }
    delete iObserver;

    Cancel();
    iProperty.Close();
    iObservers.Close();
    delete iStatusPaneStateData;
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::RefreshDataL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataSubscriber::RefreshDataL()
    {
    // If call bubble is visible refresh is needed.
    if ( iRefreshLevel == ERefreshLevelNone &&
         !( iStatusPaneStateData->iData.iIndicatorState.iIncallBubbleFlags
                & CIncallStatusBubble::ESBVisible ) )
        {
        return;
        }

    TAknStatusPaneStateData::TAknStatusPaneStateDataPckg
        statusPaneStateDataPckg( iStatusPaneStateData->iData );

    TInt err = iProperty.Get( KPSUidAvkonInternal,
                              KAknStatusPaneSystemData,
                              statusPaneStateDataPckg );

    if ( err == KErrNone )
        {
        TInt count = iObservers.Count();
        for( TInt i = 0; i < count; i++ )
            {
            TRAP_IGNORE( iObservers[i]->HandleUpdateL(
                                            iStatusPaneStateData->iData ) );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::SetAlwaysBackground
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataSubscriber::SetAlwaysBackground(
    TBool aAlwaysBackground )
    {
    iAlwaysBackground = aAlwaysBackground;
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::HandleGainingForeground
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataSubscriber::HandleGainingForeground()
    {
    iIsForeground = ETrue;
    
    // We let server side to know that now we are in the foreground.
    RAknUiServer* client = CAknSgcClient::AknSrv();
    if ( client && client->Handle() && !iAlwaysBackground )
        {
        client->SetFgSpDataSubscriberId( iSubscriberId );
        }
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::HandleLosingForeground
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataSubscriber::HandleLosingForeground()
    {
    iIsForeground = EFalse;
    
    // Data must be refreshed to hide the incall status bubble.
    TRAP_IGNORE( RefreshDataL() );
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::DoSubscribe
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataSubscriber::DoSubscribe()
    {
    if ( !IsActive() )
        {
        iProperty.Subscribe( iStatus );
        SetActive();
        }
    }


// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::RunL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataSubscriber::RunL()
    {
    TBool noError = (iStatus == KErrNone);
    
    // Re-subscribe immediately to prevent missing changes.
    DoSubscribe();
    
    if (noError)
        {
        TAknStatusPaneStateData::TAknStatusPaneStateDataPckg
            statusPaneStateDataPckg( iStatusPaneStateData->iData );

        TInt err = iProperty.Get( KPSUidAvkonInternal,
                                  KAknStatusPaneSystemData,
                                  statusPaneStateDataPckg );

        if ( err == KErrNone )
            {
            SetForegroundSubscriberId(
                iStatusPaneStateData->iData.iForegroundSubscriberId );

            TInt count = iObservers.Count();
            for(TInt i = 0; i < count; i++)
                {
                TRAP_IGNORE( iObservers[i]->HandleUpdateL(
                                                iStatusPaneStateData->iData ) );
                }
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::DoCancel
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataSubscriber::DoCancel()
    {
    iProperty.Cancel();
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::RunError
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CAknStatusPaneDataSubscriber::RunError( TInt /*aError*/ )
    {
    DoSubscribe();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::ForegroundSubscriberId
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CAknStatusPaneDataSubscriber::ForegroundSubscriberId() const
    {
    return iStatusPaneStateData->iData.iForegroundSubscriberId;
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::SetForegroundSubscriberId
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataSubscriber::SetForegroundSubscriberId( TInt aId )
    {
    iStatusPaneStateData->iData.iForegroundSubscriberId = aId;
    if ( aId == iSubscriberId )
        {
        SetRefreshLevel( ERefreshLevelHigh, EFalse );
        }
    else
        {
        SetRefreshLevel( ERefreshLevelMedium, EFalse );
        }
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::SubscriberId
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CAknStatusPaneDataSubscriber::SubscriberId() const
    {
    return iSubscriberId;
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::IsBackground
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TBool CAknStatusPaneDataSubscriber::IsBackground() const
    {
    if ( !iIsForeground || iAlwaysBackground )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::AddObserver
// (other items were commented in a header).
// -----------------------------------------------------------------------------
void CAknStatusPaneDataSubscriber::AddObserver(
    MAknStatusPaneDataObserver* aObserver )
    {
    TRAP_IGNORE( iObservers.AppendL( aObserver ) );
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::RemoveObserver
// (other items were commented in a header).
// -----------------------------------------------------------------------------
void CAknStatusPaneDataSubscriber::RemoveObserver(
    MAknStatusPaneDataObserver* aObserver )
    {
    TInt count = iObservers.Count();
    for( TInt i = 0; i < count; i++ )
        {
        if ( iObservers[i] == aObserver )
            {
            iObservers.Remove( i );
            iObservers.Compress();
            break;
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::SetRefreshLevel
// (other items were commented in a header).
// -----------------------------------------------------------------------------
EXPORT_C void CAknStatusPaneDataSubscriber::SetRefreshLevel(
    TInt aLevel,
    TBool aForced )
    {
    TInt oldLevel = iRefreshLevel;
    if ( iForcedRefreshLevel )
        {
        if ( aForced )
            {
            iRefreshLevel = aLevel;
            }
        }
    else
        {
        iRefreshLevel = aLevel;
        iForcedRefreshLevel = aForced;
        }

    if ( aLevel == ERefreshLevelNone )
        {
        // Refresh the data for the observers first, required in case the
        // incall status bubble is shown and status pane is made non-visible.
        TRAP_IGNORE( RefreshDataL() );
        Cancel();
        }
    else if ( oldLevel == ERefreshLevelNone &&
              iRefreshLevel != ERefreshLevelNone )
        {
        DoSubscribe();
        TRAP_IGNORE( RefreshDataL() );
        }
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::RefreshLevel
// (other items were commented in a header).
// -----------------------------------------------------------------------------
EXPORT_C TInt CAknStatusPaneDataSubscriber::RefreshLevel()
    {
    return iRefreshLevel;
    }

// Implementation of TWsEventObserver:

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::TWsEventObserver::TWsEventObserver
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
CAknStatusPaneDataSubscriber::TWsEventObserver::TWsEventObserver(
    CAknStatusPaneDataSubscriber& aSubs )
    : iSubs( aSubs )
    {
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataSubscriber::TWsEventObserver::MonitorWsMessage
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataSubscriber::TWsEventObserver::MonitorWsMessage(
    const TWsEvent& aEvent )
    {
    switch ( aEvent.Type() )
        {
        case KAknFullOrPartialForegroundGained:
            iSubs.HandleGainingForeground();
            break;

        case KAknFullOrPartialForegroundLost:
            iSubs.HandleLosingForeground();
            break;

        default:
            break;
        }
    }

//  End of File
