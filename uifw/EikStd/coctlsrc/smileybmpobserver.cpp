/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  smiely engine class
*
*/

#include <fbs.h>
#include <AknIconUtils.h>
#include <coeutils.h>
#include <eikedwin.h>
#include "smileybmpobserver.h"
#include "smileydrawer.h"
#include "smileyimagedata.h"
#include "smileyiconrecord.h"

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CSmileyImageData::CSmileyImageData
// ---------------------------------------------------------------------------
//
CSmileyBmpObserver::CSmileyBmpObserver( CSmileyAsyncDraw& aAsyncDraw ) : 
    iAsyncDraw( aAsyncDraw )
    {
    }

// ---------------------------------------------------------------------------
// CSmileyBmpObserver::~CSmileyBmpObserver
// ---------------------------------------------------------------------------
//
CSmileyBmpObserver::~CSmileyBmpObserver()
    {
    }

// ---------------------------------------------------------------------------
// CSmileyBmpObserver::SetImageData
// ---------------------------------------------------------------------------
//
void CSmileyBmpObserver::SetImageData( CSmileyImageData* aImage )
    {
    iImage = aImage;
    }

// ---------------------------------------------------------------------------
// CSmileyBmpObserver::BitmapChanged
// ---------------------------------------------------------------------------
//
void CSmileyBmpObserver::BitmapChanged( CFbsBitmap* /*aBitmap*/ )
    {
    if ( iImage )
        {
        if ( !iIsRegisted )
            {
            iAsyncDraw.SmileyDrawer().RegisterAnimChecker( this );
            iIsRegisted = EFalse;
            }
        iIsAnimProgress = ETrue;
        iAsyncDraw.RequestAsyncDraw();
        }
    }

// ---------------------------------------------------------------------------
// CSmileyBmpObserver::ReplayAnimationL
// ---------------------------------------------------------------------------
//
void CSmileyBmpObserver::ReplayAnimationL()
    { 
    if ( iImage )
        {
        iAsyncDraw.SmileyDrawer().CreateImageL( iImage );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyBmpObserver::StopAnimation
// ---------------------------------------------------------------------------
//
void CSmileyBmpObserver::StopAnimation()
    {
    if ( iImage )
        {
        iImage->DeleteImage();
        iAsyncDraw.SmileyDrawer().RemoveAnimChecker( this );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyBmpObserver::IsOnProgress
// ---------------------------------------------------------------------------
//
TBool CSmileyBmpObserver::IsOnProgress() const
    {
    return iIsAnimProgress;
    }

// ---------------------------------------------------------------------------
// CSmileyBmpObserver::IsOnProgress
// ---------------------------------------------------------------------------
//
void CSmileyBmpObserver::ResetStatus()
    {
    iIsAnimProgress = EFalse;
    }

// ---------------------------------------------------------------------------
// CSmileyBmpObserver::IsOnProgress
// ---------------------------------------------------------------------------
//
void CSmileyBmpObserver::DoOnAnimStoppedL()
    {
    TBool replay( EFalse );   
    for ( TInt i( 0 ); i < iImage->RefArrayCount(); i++ )
        {
        CSmileyIcon* icon( iImage->RefIcon( i ) ); 
        icon->IncreasePlayCount();
        replay = ( replay || !icon->IsPlayFinished() );
        }
    if ( replay )
        {
        iAsyncDraw.AddReplayImage( iImage );
        }
    else
        {
        StopAnimation();
        }
    iAsyncDraw.RequestAsyncDraw( ETrue );
    }

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CSmileyAsyncDraw::CSmileyAsyncDraw
// ---------------------------------------------------------------------------
//
CSmileyAsyncDraw::CSmileyAsyncDraw( CSmileyDrawer& aDrawer ) : 
    CActive( EPriorityStandard ), iDrawer( aDrawer )
    {
    CActiveScheduler::Add( this );
    }

// ---------------------------------------------------------------------------
// CSmileyAsyncDraw::~CSmileyAsyncDraw
// ---------------------------------------------------------------------------
//
CSmileyAsyncDraw::~CSmileyAsyncDraw()
    {
    Cancel();
    iReplayImageArray.Reset();
    iReplayImageArray.Close();
    }

// ---------------------------------------------------------------------------
// CSmileyAsyncDraw::StartActive
// ---------------------------------------------------------------------------
//
void CSmileyAsyncDraw::RequestAsyncDraw( TBool aForce )
    {
    if ( !IsActive() && ( IsRequestIntervalBigEnough() || aForce ) )
        {
        iEverActivated = ETrue;
        iLastRequestTime.HomeTime();
        iStatus = KRequestPending;
        TRequestStatus* status = &iStatus;
        User::RequestComplete( status, KErrNone );
        SetActive();        
        }
    }

// ---------------------------------------------------------------------------
// CSmileyAsyncDraw::DoCancel
// ---------------------------------------------------------------------------
//
void CSmileyAsyncDraw::DoCancel()
    {
    }

// ---------------------------------------------------------------------------
// CSmileyAsyncDraw::RunL
// ---------------------------------------------------------------------------
//
void CSmileyAsyncDraw::RunL()
    {
    CreateReplayImageL();
    iDrawer.DrawTextView();
    }

// ---------------------------------------------------------------------------
// CSmileyAsyncDraw::AddReplayImage
// ---------------------------------------------------------------------------
//
void CSmileyAsyncDraw::AddReplayImage( CSmileyImageData* aImage )
    {
    if ( aImage )
        {
        TBool found( EFalse );
        for ( TInt i( 0 ); i < iReplayImageArray.Count(); i++ )
            {
            if ( iReplayImageArray[i] == aImage )
                {
                found = ETrue;
                break;
                }
            }
        if ( !found )
            {
            aImage->DeleteImage();
            iReplayImageArray.Append( aImage );
            }
        }
    RequestAsyncDraw( ETrue );
    }

// ---------------------------------------------------------------------------
// CSmileyAsyncDraw::CreateReplayImageL
// ---------------------------------------------------------------------------
//
void CSmileyAsyncDraw::CreateReplayImageL()
    {
    for ( TInt i( 0 ); i < iReplayImageArray.Count(); i++ )
        {
        iDrawer.CreateImageL( iReplayImageArray[i] );
        }
    iReplayImageArray.Reset();
    }

// ---------------------------------------------------------------------------
// CSmileyAsyncDraw::IsRequestIntervalBigEnough
// ---------------------------------------------------------------------------
//
TBool CSmileyAsyncDraw::IsRequestIntervalBigEnough() const
    {
    if ( !iEverActivated )
        {
        return ETrue;
        }
    TTime current;
    current.HomeTime();
    return ( current.MicroSecondsFrom( iLastRequestTime ) >= KDrawIntervalMicroSec );
    }
