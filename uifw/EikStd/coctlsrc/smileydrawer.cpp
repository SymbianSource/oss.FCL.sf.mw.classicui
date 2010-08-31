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
#include <AknsDrawUtils.h>
#include <eikedwin.h>

#include "smileymanager.h"
#include "smileymodel.h"
#include "smileydrawer.h"
#include "smileyimagedata.h"
#include "smileybmpobserver.h"
#include "smileyiconrecord.h"

const TInt KAnimInterval = 1000000;
const TInt KMaxAnimTimeout = 3;

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// TSmileyAnimCheckerWrapper::TSmileyAnimCheckerWrapper
// ---------------------------------------------------------------------------
//
TSmileyAnimCheckerWrapper::TSmileyAnimCheckerWrapper( 
    MSmileyAnimChecker* aAnimChecker, TInt aMaxCheckTimes ) :
    iAnimChecker( aAnimChecker ), iCheckTimes( 0 ), iMaxCheckTimes( aMaxCheckTimes )
    {
    }

// ---------------------------------------------------------------------------
// CSmileyAnimCheckerWrapper::CheckAnimProgressL
// ---------------------------------------------------------------------------
//
void TSmileyAnimCheckerWrapper::CheckAnimProgressL()
    {
    if ( iAnimChecker )
        {
        if ( iAnimChecker->IsOnProgress() && iCheckTimes < iMaxCheckTimes )
            {
            iAnimChecker->ResetStatus();
            iCheckTimes++;
            }
        else
            {
            iAnimChecker->DoOnAnimStoppedL();
            iCheckTimes = 0;
            }
        }
    }

// ---------------------------------------------------------------------------
// TSmileyAnimCheckerWrapper::CheckAnimProgressL
// ---------------------------------------------------------------------------
//
TBool TSmileyAnimCheckerWrapper::IsContainingAnimChecker( 
    const MSmileyAnimChecker* aAnimChecker ) const
    {  
    return ( iAnimChecker == aAnimChecker );
    }

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CSmileyDrawer::CSmileyDrawer
// ---------------------------------------------------------------------------
//
CSmileyDrawer::CSmileyDrawer( CSmileyModel& aModel, CEikEdwin& aEdwin ) : 
    iModel( aModel ), iEdwin( aEdwin ), iPlayTimes( KDisplayTimes )
    {
    }
    
// ---------------------------------------------------------------------------
// CSmileyDrawer::~CSmileyDrawer
// ---------------------------------------------------------------------------
//
CSmileyDrawer::~CSmileyDrawer()
    {    
    iImageArray.ResetAndDestroy();
    iImageArray.Close();
    delete iAsyncDraw;
    if ( iPeriodic )
        {
        iPeriodic->Cancel();
        }
    delete iPeriodic;
    iAnimArray.Reset();
    iAnimArray.Close();
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::SetHighlightColor
// ---------------------------------------------------------------------------
//
void CSmileyDrawer::SetHighlightColor( TRgb aColor )
    {
    const TInt KAlphaFactor = 127;
    iHighlightColor = TRgb( aColor.Internal(), KAlphaFactor );
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::DrawSmileyContainer
// ---------------------------------------------------------------------------
//
void CSmileyDrawer::DrawTextView()
    {
    iEdwin.DrawTextView();   
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::StartAnimTimerL
// ---------------------------------------------------------------------------
//
void CSmileyDrawer::StartAnimTimerL()
    {
    if ( !iPeriodic )
        {
        iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
        }
    if ( !iPeriodic->IsActive() )
        {
        TTimeIntervalMicroSeconds32 interval( KAnimInterval );
        iPeriodic->Start( interval, interval, 
            TCallBack( AnimTimerCallbackL, this ) );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::AnimTimerCallback
// ---------------------------------------------------------------------------
//
TInt CSmileyDrawer::AnimTimerCallbackL( TAny* aPtr )
    {
    CSmileyDrawer* drawer( static_cast<CSmileyDrawer*>( aPtr ) );
    drawer->CheckAnimStatusL();
    return 0;
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::CheckAnimStatus
// ---------------------------------------------------------------------------
//
void CSmileyDrawer::CheckAnimStatusL()
    {
    for ( TInt i( 0 ); i < iAnimArray.Count(); i++ )
        {
        iAnimArray[i].CheckAnimProgressL();
        }
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::RegisterAnimChecker
// ---------------------------------------------------------------------------
//
void CSmileyDrawer::RegisterAnimChecker( MSmileyAnimChecker* aAnimChecker )
    {
    TBool found( EFalse );
    for ( TInt i( 0 ); i < iAnimArray.Count(); i++ )
        {
        if ( iAnimArray[i].IsContainingAnimChecker( aAnimChecker ) )
            {
            found = ETrue;
            break;
            }
        }
    if ( !found )
        {
        TSmileyAnimCheckerWrapper wrapper( aAnimChecker, KMaxAnimTimeout );
        iAnimArray.Append( wrapper );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::RemoveAnimChecker
// ---------------------------------------------------------------------------
//
void CSmileyDrawer::RemoveAnimChecker( MSmileyAnimChecker* aAnimChecker )
    {
    for ( TInt i( 0 ); i < iAnimArray.Count(); i++ )
        {
        if ( iAnimArray[i].IsContainingAnimChecker( aAnimChecker ) )
            {
            iAnimArray.Remove( i );
            break;
            }
        }
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::DrawImageByInfo
// ---------------------------------------------------------------------------
//
void CSmileyDrawer::DrawImageByIconL( CBitmapContext& aGc, 
    CSmileyIcon* aIcon )
    {
    if ( aIcon->DocPos() < iVisibleStart && aIcon->DocPos() >= 
        iVisibleStart + iVisibleLength )
        {
        return;
        }
    CSmileyImageData* image( aIcon->ImageData() );
    CFbsBitmap* bmp( image->Bitmap() );
    CFbsBitmap* mask( image->Mask() );
    if ( aIcon->IsPlayFinished() )
        {
        bmp = image->StaticBmp();
        mask = image->StaticMask();
        }
    TRect rect( image->BitmapSize() );
    TPoint pt( aIcon->Rect().iTl );
    if ( bmp && mask )
        {
        aGc.BitBltMasked( pt, bmp, rect, mask, EFalse );
        }    
    if ( aIcon->IsHighlight() )
        { 
        aGc.SetPenStyle( CGraphicsContext::ENullPen );
        aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        aGc.SetBrushColor( iHighlightColor );
        aGc.SetDrawMode( CGraphicsContext::EDrawModeNOTOR );
        aGc.DrawRect( TRect( pt, rect.Size() ) );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::CreateImageByIconL
// ---------------------------------------------------------------------------
//
void CSmileyDrawer::CreateImageByIconL( CSmileyIcon* aIcon )
    {
    StartAnimTimerL();
    if ( !aIcon->ImageData() )
        {
        aIcon->SetPlayTimes( iPlayTimes );
        TText code( aIcon->Code() );
        CSmileyImageData* imageData( FindImageDataByCode( code ) );
        TBool needNewImage( EFalse );
        if ( !imageData )
            {
            imageData = CreateImageDataL( code );
            needNewImage = ETrue;
            }
        else if ( imageData && imageData->IsAnimation() )
            {
            needNewImage = imageData->IsAnimationFinished();
            }
        aIcon->SetImageData( imageData );
        imageData->AddToRefArray( aIcon );
        imageData->SetBitmapSize( aIcon->Rect().Size() );
        if ( needNewImage )
            {
            iAsyncDraw->AddReplayImage( imageData );
            }
        }
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::CreateImageDataL
// ---------------------------------------------------------------------------
//
void CSmileyDrawer::CreateImageL( CSmileyImageData* aImage )
    {
    if ( aImage )
        {
        HBufC* fileName( NULL );
        TImageInfo imageInfo;
        imageInfo.iCode = aImage->Code();
        iModel.GetImageInfo( imageInfo, &fileName );
        aImage->CreateImageL( *fileName, imageInfo );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::FindImageDataByCode
// ---------------------------------------------------------------------------
//
CSmileyImageData* CSmileyDrawer::FindImageDataByCode( TText aCode )
    {
    for ( TInt i( 0 ); i < iImageArray.Count(); i++ )
        {
        if ( aCode == iImageArray[i]->Code() )
            {
            return iImageArray[i];
            }
        }
    return NULL;
    }

// ---------------------------------------------------------------------------
// CSmileyDrawer::FindImageDataByCode
// ---------------------------------------------------------------------------
//
CSmileyImageData* CSmileyDrawer::CreateImageDataL( TText aCode )
    {
    if ( !iAsyncDraw )
        {
        iAsyncDraw = new( ELeave ) CSmileyAsyncDraw( *this );
        }
    CSmileyBmpObserver* observer( new( ELeave ) CSmileyBmpObserver( *iAsyncDraw ) );
    CleanupStack::PushL( observer );
    CSmileyImageData* imageData( new( ELeave ) CSmileyImageData( observer ) );
    CleanupStack::PushL( imageData );
    iImageArray.AppendL( imageData );
    imageData->SetCode( aCode );        
    CleanupStack::Pop( imageData );
    CleanupStack::Pop( observer );
    return imageData;
    }

