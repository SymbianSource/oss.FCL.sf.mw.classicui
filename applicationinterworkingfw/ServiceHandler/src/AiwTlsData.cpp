/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     TLS data object.
*
*/




// INCLUDE FILES
#include "AiwTlsData.h"

// CONSTANTS

const TInt KMenuLaunchObserversGranularity = 2;

// ================= MEMBER FUNCTIONS ==========================================

CAiwTlsData::CAiwTlsData() :
    iMenuLaunchObservers( KMenuLaunchObserversGranularity )
    {
    }

CAiwTlsData::~CAiwTlsData()
    {
    iMenuLaunchObservers.Reset();
    Dll::FreeTls();
    }
    
CAiwTlsData* CAiwTlsData::NewL()
    {
    CAiwTlsData* data = new( ELeave ) CAiwTlsData;
    CleanupStack::PushL( data );
    data->ConstructL();
    CleanupStack::Pop(); // data
    return data;
    }
    
void CAiwTlsData::ConstructL()
    {
    User::LeaveIfError( Dll::SetTls( this ) );
    }

// -----------------------------------------------------------------------------
// CAiwTlsData::OpenL
// -----------------------------------------------------------------------------
//
CAiwTlsData* CAiwTlsData::OpenL()
    {
    CAiwTlsData* data = Instance();
    if ( !data )
        {
        data = NewL();
        }
    
    data->iRefCount++;
    return data;
    }

// -----------------------------------------------------------------------------
// CAiwTlsData::Close
// -----------------------------------------------------------------------------
//
void CAiwTlsData::Close()
    {
    CAiwTlsData* data = Instance();
    __ASSERT_DEBUG( data, User::Invariant() );
    if ( data )
        {
        if ( --data->iRefCount == 0 )
            {
            delete data; // also frees TLS
            }
        }
    }

// -----------------------------------------------------------------------------
// CAiwTlsData::AddMenuLaunchObserverL
// -----------------------------------------------------------------------------
//
void CAiwTlsData::AddMenuLaunchObserverL( MAiwMenuLaunchObserver* aObserver )
    {
    User::LeaveIfError( iMenuLaunchObservers.Append( aObserver ) );
    }

// -----------------------------------------------------------------------------
// CAiwTlsData::RemoveMenuLaunchObserver
// -----------------------------------------------------------------------------
//   
void CAiwTlsData::RemoveMenuLaunchObserver( MAiwMenuLaunchObserver* aObserver )
    {
    TInt index = iMenuLaunchObservers.Find( aObserver );
    if ( index >= 0 )
        {
        iMenuLaunchObservers.Remove( index );
        }
    }
    
// -----------------------------------------------------------------------------
// CAiwTlsData::ReportMenuLaunch
// -----------------------------------------------------------------------------
//
void CAiwTlsData::ReportMenuLaunch()
    {
    TInt count = iMenuLaunchObservers.Count();
    for ( TInt i = 0 ; i < count ; i++ )
        {
        iMenuLaunchObservers[i]->MenuLaunched();
        }
    }

// End of file
