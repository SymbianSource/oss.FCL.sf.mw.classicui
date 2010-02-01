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
* Description:     
*
*/


#include "HgScrollBufferManager.h"
#include <ganes/HgScrollBufferObserverIface.h>

#include <e32debug.h>

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::NewL()
// -----------------------------------------------------------------------------
//
CHgScrollBufferManager* CHgScrollBufferManager::NewL( 
        MHgScrollBufferObserver& aObserver, 
        TInt aBufferSize,
        TInt aBufferTreshold,
        TInt aInitialPosition,
        TInt aTotalCount )
    {
    CHgScrollBufferManager* self = new (ELeave) CHgScrollBufferManager(
                                                        aObserver, 
                                                        aBufferSize, 
                                                        aBufferTreshold, 
                                                        aInitialPosition, 
                                                        aTotalCount );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::CHgScrollBufferManager()
// -----------------------------------------------------------------------------
//
CHgScrollBufferManager::CHgScrollBufferManager(
        MHgScrollBufferObserver& aObserver, 
        TInt aBufferSize,
        TInt aBufferTreshold,
        TInt aInitialPosition,
        TInt aTotalCount )
: CActive( CActive::EPriorityHigh ), 
    iObserver( aObserver ),
    iBufferSize( aBufferSize ),
    iBufferTreshold( aBufferTreshold ),
    iBufferPosition( aInitialPosition ),
    iTotalCount( aTotalCount )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::ConstructL()
// -----------------------------------------------------------------------------
//
void CHgScrollBufferManager::ConstructL()
    {
    CActiveScheduler::Add(this);
    
    iResetOrdered = ETrue;
    ResetBuffer(iBufferPosition, iTotalCount);
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::~CHgScrollBufferManager()
// -----------------------------------------------------------------------------
//
CHgScrollBufferManager::~CHgScrollBufferManager()
    {
    Cancel();
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::RunL()
// -----------------------------------------------------------------------------
//
void CHgScrollBufferManager::RunL()
    {
    MHgScrollBufferObserver::THgScrollDirection direction = MHgScrollBufferObserver::EHgBufferNoMove;
    
    if(iResetOrdered)
        {
        iResetOrdered = EFalse;
        direction = MHgScrollBufferObserver::EHgBufferReset;
        }
    else
        {
        if(iDiff < 0)
            {
            iReleaseStart = iBufferPosition;
            iRequestStart = iBufferPosition + iBufferSize;
            direction = MHgScrollBufferObserver::EHgBufferScrollDown;
            }
        else if( iDiff > 0)
            {
            iReleaseStart = iBufferPosition + iBufferSize - iDiff;
            iRequestStart = iBufferPosition - iDiff;
            direction = MHgScrollBufferObserver::EHgBufferScrollUp;
            }
        }
    
    // Release 
    TInt end = iReleaseStart + iReleaseCount < iTotalCount ?
        iReleaseStart + iReleaseCount: iTotalCount; 
    end--;
    if(end >= iReleaseStart )
        {
        iObserver.Release(iReleaseStart, end);
        if(iOwner) iOwner->Release( iReleaseStart, end );
        }
    
    iReleaseCount = 0;
    
    // Request
    end = iRequestStart + iRequestCount < iTotalCount ? 
        iRequestStart + iRequestCount : iTotalCount;

    end--;
    if(end >= iRequestStart )
        iObserver.Request(iRequestStart, end, direction);
      
    iRequestCount = 0;

    // Move Buffer
    iBufferPosition -= iDiff;
    // Reset Diff
    iDiff = 0;
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::DoCancel()
// -----------------------------------------------------------------------------
//
void CHgScrollBufferManager::DoCancel()
    {
    // Nothing to do here
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::RunError()
// -----------------------------------------------------------------------------
//
TInt CHgScrollBufferManager::RunError( TInt /*aError*/ )
    {
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::SetPosition()
// -----------------------------------------------------------------------------
//
void CHgScrollBufferManager::SetPosition( TInt aIndex )
    {
    TBool forceUpdate = EFalse;
    aIndex -= iBufferSize / 2; // normalize index to Buffer start
    
    if(aIndex < 0)
        {
        aIndex = 0;
        forceUpdate = ETrue;
        }
    else if( aIndex > iTotalCount - iBufferSize )
        {
        aIndex = iTotalCount - iBufferSize;
        forceUpdate = ETrue;
        }
    
    iDiff = iBufferPosition - aIndex; 
    
    // Too large change reset whole buffer
    if( iDiff >= iBufferSize || -iDiff >= iBufferSize || iResetOrdered ) 
        {
        ResetBuffer(aIndex + (iBufferSize/2), iTotalCount);
        }
    // Move Up
    else if( iDiff >= iBufferTreshold ) 
        {
        iRequestCount = iDiff;
        iReleaseCount = iDiff;
        NotifyObserver();
        }
    // Move Down
    else if( -iDiff >= iBufferTreshold ) 
        {
        iRequestCount = -iDiff;
        iReleaseCount = -iDiff;
        NotifyObserver();
        }
    // Top or bottom has been reached
    else if( forceUpdate && iDiff )
        {
        TInt diff = iDiff < 0 ? -iDiff : iDiff;
        iRequestCount = diff;
        iReleaseCount = diff;
        NotifyObserver();
        }
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::SetTotalCount()
// -----------------------------------------------------------------------------
//
void CHgScrollBufferManager::SetTotalCount( TInt aTotalCount )
    {
    iTotalCount = aTotalCount;
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::SetBufferOwner()
// -----------------------------------------------------------------------------
//
void CHgScrollBufferManager::SetBufferOwner( MHgBufferOwner& aOwner )
    {
    iOwner = &aOwner;
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::ResetBuffer()
// -----------------------------------------------------------------------------
//
void CHgScrollBufferManager::ResetBuffer( TInt aPosition, TInt aTotalCount)
    {
    if( !iResetOrdered )
        {
        // release Old buffer
        iReleaseStart = iBufferPosition;
        iReleaseCount = iBufferSize;
        }
    
    // set position and count
    iBufferPosition = aPosition - (iBufferSize / 2);
    iTotalCount = aTotalCount;
    iDiff = 0;
    
    if( iBufferPosition + iBufferSize > iTotalCount - 1 )
        {
        iBufferPosition = iTotalCount - iBufferSize;
        }
    
    if(iBufferPosition < 0 )
        {
        iBufferPosition = 0;
        }
    
    //request new Buffer
    iRequestStart = iBufferPosition;
    iRequestCount = iBufferSize;
    iResetOrdered = ETrue;
    
    NotifyObserver();
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::NotifyObserver()
// -----------------------------------------------------------------------------
//
void CHgScrollBufferManager::NotifyObserver()
    {
    if( !IsActive() )
        {
        SetActive();
        TRequestStatus* status = &iStatus;
        User::RequestComplete(status, KErrNone);
        }
    }

// -----------------------------------------------------------------------------
// CHgScrollBufferManager::ItemChanged()
// -----------------------------------------------------------------------------
//
void CHgScrollBufferManager::ItemCountChanged( 
        TInt aIndex, 
        TBool aRemoved,
        TInt aNewTotalCount )
    {  
    iTotalCount = aNewTotalCount;
    if ( aIndex >= iBufferPosition && aIndex < iBufferPosition + iBufferSize )
        {
        // Change inside the buffer
        MHgScrollBufferObserver::THgScrollDirection direction = MHgScrollBufferObserver::EHgBufferNoMove;
        if( aRemoved )
            {
            // Release removed item ( Item deleted already from the owner )
            iObserver.Release( aIndex, aIndex );
            if( iTotalCount >= iBufferSize )
                {
                // There are more items to keep the buffer filled
                if( iBufferPosition + iBufferSize <= iTotalCount )
                    {
                    // Requested from the end
                    iObserver.Request( iBufferPosition + iBufferSize - 1, 
                            iBufferPosition + iBufferSize - 1, direction );
                    }
                else if( iBufferPosition > 0 )
                    {
                    // Move buffer and request from the beginning 
                    iBufferPosition--;
                    iObserver.Request( iBufferPosition, iBufferPosition, direction );
                    }
                }
            }            
        else
            {
            if( iTotalCount > iBufferSize )
                {
                // One item needs to be released
                if( iBufferPosition + iBufferSize < iTotalCount )
                    {
                    // Release from the end of the buffer
                    iObserver.Release(iBufferPosition + iBufferSize, iBufferPosition + iBufferSize);
                    if(iOwner)
                        iOwner->Release(iBufferPosition + iBufferSize, iBufferPosition + iBufferSize);
                    }
                }
            // Request added item
            iObserver.Request(aIndex, aIndex, direction);
            }
        }
    }

