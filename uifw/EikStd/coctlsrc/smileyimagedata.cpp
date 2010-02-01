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
#include <bitdev.h>
#include <bitstd.h>
#include <AknIconUtils.h>
#include <coeutils.h>
#include <AknIconObserver.h>

#include "smileymodel.h"
#include "smileybmpobserver.h"
#include "smileyiconrecord.h"
#include "smileyimagedata.h"

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CSmileyImageData::CSmileyImageData
// ---------------------------------------------------------------------------
//
CSmileyImageData::CSmileyImageData( CSmileyBmpObserver* aObserver ) : 
    iObserver( aObserver )
    { 
    if ( iObserver )
        {
        iObserver->SetImageData( this );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::~CSmileyImageData
// ---------------------------------------------------------------------------
//
CSmileyImageData::~CSmileyImageData()
    {    
    AknIconUtils::SetObserver( iBmp, NULL );    
    delete iBmp;
    delete iMask;
    delete iStaticBmp;
    delete iStaticMask;
    for ( TInt i( 0 ); i < iRefArray.Count(); i++ )
        {
        iRefArray[i]->SetImageData( NULL );
        }
    iRefArray.Reset();
    iRefArray.Close();
    delete iObserver;
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::Bitmap
// ---------------------------------------------------------------------------
//
CFbsBitmap* CSmileyImageData::Bitmap()
    {
    return iBmp;
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::Mask
// ---------------------------------------------------------------------------
//
CFbsBitmap* CSmileyImageData::Mask()
    {
    return iMask;
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::CreateImageL
// ---------------------------------------------------------------------------
//
void CSmileyImageData::CreateImageL( const TDesC& aIconFileName, TImageInfo& aInfo )
    {
    DeleteImage();
    CreateBmpAndMaskL( aIconFileName, aInfo );
    if ( !iStaticBmp )
        {
        CreateStaticBmpAndMaskForAnimationL( aIconFileName, aInfo );
        }
    SetBitmapSize( iBmpSize, ETrue );        
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::DeleteImage
// ---------------------------------------------------------------------------
//
void CSmileyImageData::DeleteImage()
    {
    AknIconUtils::SetObserver( iBmp, NULL );
    delete iBmp;
    iBmp = NULL;
    delete iMask;
    iMask = NULL;
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::RefArrayCount
// ---------------------------------------------------------------------------
//
TInt CSmileyImageData::RefArrayCount()
    {
    return iRefArray.Count();
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::AddToRefArray
// ---------------------------------------------------------------------------
//
void CSmileyImageData::AddToRefArray( CSmileyIcon* aNode )
    {
    for ( TInt i( 0 ); i < iRefArray.Count(); i++ )
        {
        if ( iRefArray[i] == aNode )
            {
            return;
            }
        }
    iRefArray.Append( aNode );
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::RemoveFromaRefArray
// ---------------------------------------------------------------------------
//
void CSmileyImageData::RemoveFromRefArray( CSmileyIcon* aNode )
    {
    for ( TInt i( 0 ); i < iRefArray.Count(); i++ )
        {
        if ( iRefArray[i] == aNode )
            {
            iRefArray.Remove( i );
            break;
            }
        }
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::RefIcon
// ---------------------------------------------------------------------------
//
CSmileyIcon* CSmileyImageData::RefIcon( TInt aIndex )
    {
    CSmileyIcon* icon( NULL );
    if ( aIndex >= 0 && aIndex < iRefArray.Count() )
        {
        icon = iRefArray[aIndex];
        }
    return icon;
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::Code
// ---------------------------------------------------------------------------
//
TText CSmileyImageData::Code()
    {
    return iCode;
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::SetCode
// ---------------------------------------------------------------------------
//
void CSmileyImageData::SetCode( TText aCode )
    {
    iCode = aCode;
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::BitmapSize
// ---------------------------------------------------------------------------
//
TSize CSmileyImageData::BitmapSize()
    {
    return iBmpSize;
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::BitmapSize
// ---------------------------------------------------------------------------
//
void CSmileyImageData::SetBitmapSize( TSize aBmpSize, TBool aForceSet )
    {
    TBool sizeChanged = ( iBmpSize != aBmpSize );
    iBmpSize = aBmpSize;
    if ( sizeChanged || aForceSet )
        {
        if ( iBmp )
            {
            AknIconUtils::SetSize( iBmp, iBmpSize );        
            }
        if ( iStaticBmp )
            {
            AknIconUtils::SetSize( iStaticBmp, iBmpSize );
            }        
        }
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::IsAnimationFinished
// ---------------------------------------------------------------------------
//
TBool CSmileyImageData::IsAnimationFinished()
    {
    return ( iIsAnimation && iBmp == NULL );
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::IsAnimation
// ---------------------------------------------------------------------------
//
TBool CSmileyImageData::IsAnimation()
    {
    return iIsAnimation;
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::StoredBmp
// ---------------------------------------------------------------------------
//
CFbsBitmap* CSmileyImageData::StaticBmp()
    {
    return iStaticBmp;
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::StoredMask
// ---------------------------------------------------------------------------
//
CFbsBitmap* CSmileyImageData::StaticMask()
    {
    return iStaticMask;
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::CreateBmpAndMaskL
// ---------------------------------------------------------------------------
//
void CSmileyImageData::CreateBmpAndMaskL( const TDesC& aIconFileName, 
    TImageInfo& aInfo )
    {
    iIsAnimation = aInfo.iIsAnimation;
    if ( aInfo.iMaskId != 0 )
        {
        AknIconUtils::CreateIconL( iBmp, iMask, aIconFileName, aInfo.iBmpId, 
            aInfo.iMaskId );        
        }
    else
        {
        AknIconUtils::CreateIconL( iBmp, iMask, aIconFileName, aInfo.iBmpId, 
            aInfo.iBmpId );       
        }
    if ( iIsAnimation )
        {
        AknIconUtils::SetObserver( iBmp, iObserver );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyImageData::CreateStaticBmpAndMaskForAnimationL
// ---------------------------------------------------------------------------
//
void CSmileyImageData::CreateStaticBmpAndMaskForAnimationL( 
    const TDesC& aIconFileName, TImageInfo& aInfo )
    {
    if ( aInfo.iIsAnimation )
        {
        if ( aInfo.iStaticMaskId != 0 )
            {
            AknIconUtils::CreateIconL( iStaticBmp, iStaticMask, aIconFileName, 
                aInfo.iStaticBmpId, aInfo.iStaticMaskId );        
            }
        else
            {
            AknIconUtils::CreateIconL( iStaticBmp, iStaticMask, aIconFileName, 
                aInfo.iStaticBmpId, aInfo.iStaticBmpId );       
            }
        }
    }


