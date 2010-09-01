/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Listens to ECOM for screensaver plugin changes.
*
*/


#include "mpslnscreensaverecomobserver.h"

#include "PslnEcomListener.h"
#include "PslnModel.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnEcomListener::CPslnEcomListener( CPslnModel& aModel, 
    MPslnScreenSaverECOMObserver& aObserver ) : 
    CActive( CActive::EPriorityStandard ), iModel( &aModel ), 
    iObserver( &aObserver )
    {
    CActiveScheduler::Add( this );
    }

// ---------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CPslnEcomListener::ConstructL()
    {
    iSession = REComSession::OpenL();
    // Start ECOM monitoring
    StartECOMMonitoringL();
    }

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CPslnEcomListener* CPslnEcomListener::NewL( 
    CPslnModel& aModel, MPslnScreenSaverECOMObserver& aObserver )
    {
    CPslnEcomListener* self = 
        new ( ELeave ) CPslnEcomListener( aModel, aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CPslnEcomListener::~CPslnEcomListener()
    {
    Cancel();
    iSession.Close();
    }

// -----------------------------------------------------------------------------
// Called when active object is ready.
// -----------------------------------------------------------------------------
//
void CPslnEcomListener::RunL()
    {
    iModel->LoadScreensaverArrayL();
    iObserver->HandlePluginListChangeL();
    StartECOMMonitoringL();
    }

// -----------------------------------------------------------------------------
// Called when active object is cancelled.
// -----------------------------------------------------------------------------
//
void CPslnEcomListener::DoCancel()
    {
    iSession.CancelNotifyOnChange( iStatus );
    }

// -----------------------------------------------------------------------------
// Called when active object is cancelled.
// -----------------------------------------------------------------------------
//
void CPslnEcomListener::StartECOMMonitoringL()
    {
    if ( !IsActive() )
        {
        iSession.NotifyOnChange( iStatus );
        SetActive();
        }
    else
        {
        User::Leave( KErrAlreadyExists );
        }
    }

// End of file
