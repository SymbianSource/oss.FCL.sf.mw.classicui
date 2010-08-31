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
* Description:  Private image loader to convert binary array into usable image
*
*/


// INCLUDES
#include "AknPrivateImageLoader.h"
#include <imageconversion.h>
#include <eikenv.h>
#include <f32file.h>
#include <e32debug.h>
#include <eikimage.h>
#include <AknIconUtils.h>
#include <SVGEngineInterfaceImpl.h>

/// Max bitmap dimension (heigth or width) which is allowed to be loaded
const TInt KMaxDecodeSize   = 300;

/// Debug print macro
#ifdef _DEBUG
    #define RDEBUG( args... ) RDebug::Printf( args )
#else
    #define RDEBUG( args... )  
#endif

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::CAknPrivateImageLoader
// ---------------------------------------------------------------------------
//
CAknPrivateImageLoader::CAknPrivateImageLoader(
    RFs& aFs,
    MAknPrivateImageLoaderObserver& aObserver ) : 
    CActive( EPriorityStandard ),
    iObserver( aObserver ),
    iFs( aFs )
    {
    CActiveScheduler::Add( this );
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::ConstructL
// ---------------------------------------------------------------------------
//
void CAknPrivateImageLoader::ConstructL()
    {
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::NewL
// ---------------------------------------------------------------------------
//
CAknPrivateImageLoader* CAknPrivateImageLoader::NewL(
    RFs& aFs,
    MAknPrivateImageLoaderObserver& aObserver )
    {
    CAknPrivateImageLoader* self = 
        CAknPrivateImageLoader::NewLC( aFs, aObserver );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::NewLC
// ---------------------------------------------------------------------------
//
CAknPrivateImageLoader* CAknPrivateImageLoader::NewLC(
    RFs& aFs,
    MAknPrivateImageLoaderObserver& aObserver )
    {
    CAknPrivateImageLoader* self = 
        new( ELeave ) CAknPrivateImageLoader( aFs, aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::~CAknPrivateImageLoader
// ---------------------------------------------------------------------------
//
CAknPrivateImageLoader::~CAknPrivateImageLoader()
    {
    Cancel();
    delete iDecoder;
    delete iIcon;
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::LoadIconL
// ---------------------------------------------------------------------------
//
void CAknPrivateImageLoader::LoadIconL( 
    const TDesC8& aImageData, 
    TSize aSize )
    {
    Cancel();

    // try to load bitmap
    TRAPD( err, LoadL( aImageData, aSize ) );
    
    if( err == KErrTooBig )
        {
        User::Leave( err );
        }
    else if( err )
        {
        // Decoder can't open it -> try to load as SVG image
        LoadSVGImageL( aImageData, aSize );
        }
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::RunL
// ---------------------------------------------------------------------------
//
void CAknPrivateImageLoader::RunL()
    {
    // Compress the heap after image conversion as image decoder
    // seems to leave heap uncompressed
    if( iDecoder )
        {
        delete iDecoder;
        iDecoder = NULL;
        User::Heap().Compress();
        }
    
    // check errors
    TInt status = iStatus.Int();
    if( status < KErrNone )
        {
        // Image load failed
        RDEBUG( "CAknPrivateImageLoader::RunL: image load error %d", status );

        delete iIcon;
        iIcon = NULL;

        iObserver.ImageLoadError( status );
        // don't use member variables after callback, since this instance
        // might be deleted
        }
    else
        {
        // Image load success
        ASSERT( iIcon );
        
        // generate dummy mask if image didn't have one.
        CFbsBitmap* mask = iIcon->Mask();
        if( !mask )
            {
            CFbsBitmap* genMask = 
                GenerateMaskLC( iIcon->Bitmap()->SizeInPixels() );
            iIcon->SetMask( genMask );
            CleanupStack::Pop( genMask );
            }
        
        // 1 bit masks needs to be inverted
        else if( mask->DisplayMode() == EGray2 ) 
            {
            InvertImageL( *mask );
            }
        
        // create scalable image
        CAknIcon* icon = iIcon;
        iIcon = NULL;
        iIcon = CreateIconL( icon ); // takes ownership (leave safe)
        
        CEikImage* image = new(ELeave) CEikImage;
        image->SetPicture( iIcon->Bitmap(), iIcon->Mask() );
        
        // remove ownership from iIcon
        iIcon->SetBitmap( NULL );
        iIcon->SetMask( NULL );
        
        delete iIcon;
        iIcon = NULL;
        
        iObserver.ImageLoadSuccess( image ); // ownership given
        // don't use member variables after callback, since this instance
        // might be deleted
        }
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::RunError
// ---------------------------------------------------------------------------
//
TInt CAknPrivateImageLoader::RunError( TInt aError )
    {
    RDEBUG( "CAknPrivateImageLoader::RunError: image load error %d", aError );
    
    delete iIcon;
    iIcon = NULL;

    iObserver.ImageLoadError( aError );
    // don't use member variables after callback, since this instance
    // might be deleted

    return KErrNone;
    }


// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::DoCancel
// ---------------------------------------------------------------------------
//
void CAknPrivateImageLoader::DoCancel()
    {
    if( iDecoder )
        {
        iDecoder->Cancel();
        delete iDecoder;
        iDecoder = NULL;
        }
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::InvertImageL
// ---------------------------------------------------------------------------
//
void CAknPrivateImageLoader::InvertImageL( CFbsBitmap& aBitmap )
    {
    TDisplayMode mode = aBitmap.DisplayMode();
    TInt width = aBitmap.SizeInPixels().iWidth;
    TInt height = aBitmap.SizeInPixels().iHeight;

    HBufC8* buf = HBufC8::NewLC( aBitmap.ScanLineLength( width, mode ) );
    TPtr8 bufPtr( buf->Des() );
    
    for( TInt i = 0; i < height; ++i )
        {
        aBitmap.GetScanLine( bufPtr, TPoint( 0, i ), width, mode );
        TInt len = bufPtr.Length();
        for( TInt j = 0; j < len; ++j )
            {
            bufPtr[j] ^= 0xff;
            }
        aBitmap.SetScanLine( bufPtr, i );
        }
    
    CleanupStack::PopAndDestroy( buf );
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::CreateIconL
// ---------------------------------------------------------------------------
//
CAknIcon* CAknPrivateImageLoader::CreateIconL( CAknIcon* aIcon )
    {
    CAknIcon* result = NULL;
    if( aIcon->Mask() )
        {
        result = AknIconUtils::CreateIconL( aIcon ); // deletes icon in case of leave
        }
    else
        {
        // aMask is NULL
        CFbsBitmap* image = aIcon->Bitmap();
        aIcon->SetBitmap( NULL );
        CleanupStack::PushL( aIcon );
        image = AknIconUtils::CreateIconL( image ); // deletes image in case of leave
        CleanupStack::Pop( aIcon );
        aIcon->SetBitmap( image );
        result = aIcon;
        }
    
    return result; // ownership given to caller
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::LoadL
// ---------------------------------------------------------------------------
//
void CAknPrivateImageLoader::LoadL( const TDesC8& aImageData, TSize aSize )
    {
    delete iDecoder;
    iDecoder = NULL;
    
    // default loader
    iDecoder = CImageDecoder::DataNewL( iFs, aImageData, 
        CImageDecoder::EAllowGeneratedMask );

    TFrameInfo info( iDecoder->FrameInfo() ); 
    TSize& frameSize( info.iFrameSizeInPixels );
    if( frameSize.iHeight > KMaxDecodeSize || 
        frameSize.iWidth > KMaxDecodeSize )
        {
        RDEBUG("CAknPrivateImageLoader::LoadLC err: image larger than %dx%d",
            KMaxDecodeSize, KMaxDecodeSize );
        User::Leave( KErrTooBig );
        }
    
    CAknIcon* icon = CAknIcon::NewL();
    CleanupStack::PushL( icon );
    icon->SetBitmap( new( ELeave ) CFbsBitmap() );
    
    TSize decodeSize( DecodeSize( info, aSize ) );
    
    User::LeaveIfError( icon->Bitmap()->Create( 
        decodeSize, info.iFrameDisplayMode ) );

    if ( info.iFlags & TFrameInfo::ETransparencyPossible )
        {
        // Transparency available -> use mask
        icon->SetMask( new( ELeave ) CFbsBitmap() );
        User::LeaveIfError( icon->Mask()->Create( decodeSize,
            info.iFlags & TFrameInfo::EAlphaChannel ? EGray256 : EGray2 ) );
        }

    // start processing
    if( icon->Mask() )
        {
        iDecoder->Convert( &iStatus, *icon->Bitmap(), *icon->Mask() );
        }
    else
        {
        iDecoder->Convert( &iStatus, *icon->Bitmap() );
        }
    
    CleanupStack::Pop( icon );
    delete iIcon;
    iIcon = icon;

    // wait for completion
    SetActive();
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::LoadSVGImageL
// ---------------------------------------------------------------------------
//
void CAknPrivateImageLoader::LoadSVGImageL(
    const TDesC8& aImageData, 
    TSize aSize )
    {
    CFbsBitmap* dummy = new(ELeave) CFbsBitmap();
    CleanupStack::PushL( dummy );
    TFontSpec spec;
    CSvgEngineInterfaceImpl* svgEngine = 
        CSvgEngineInterfaceImpl::NewL( dummy, NULL, spec );
    CleanupStack::PushL( svgEngine );

    TInt handle = KErrNotFound;
    LeaveIfErrorL( svgEngine->PrepareDom( aImageData, handle ) );
    
    CAknIcon* icon = CAknIcon::NewL();
    CleanupStack::PushL( icon );
    icon->SetBitmap( new(ELeave) CFbsBitmap() );
    
    // create image bitmap
    TDisplayMode mode( EColor64K ); // default value
    CEikonEnv* eikon = CEikonEnv::Static();
    if( eikon )
        {
        mode = eikon->ScreenDevice()->DisplayMode();
        }
    User::LeaveIfError( icon->Bitmap()->Create( aSize, mode ) ); 
    
    // create soft mask
    icon->SetMask( new(ELeave) CFbsBitmap() );
    User::LeaveIfError( icon->Mask()->Create( aSize, EGray256 ) );

    // render svg image
    LeaveIfErrorL( 
        svgEngine->RenderDom( handle, icon->Bitmap(), icon->Mask() ) );

    CleanupStack::Pop( icon );
    CleanupStack::PopAndDestroy( 2, dummy ); // svgEngine
    
    delete iIcon;
    iIcon = icon;

    // handle image in RunL
    TRequestStatus* status = &iStatus;
    User::RequestComplete( status, KErrNone );
    SetActive();
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::LeaveIfErrorL
// ---------------------------------------------------------------------------
//
void CAknPrivateImageLoader::LeaveIfErrorL( MSvgError* aError )
    {
    if( aError )
        {
        if( aError->HasError() && !aError->IsWarning() )
            {
            RDEBUG( "CAknPrivateImageLoader::LeaveIfErrorL: "
                "SVG loading error: %d", aError->ErrorCode() );
            User::Leave( KErrCorrupt );
            }
        }
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::GenerateMaskLC
// ---------------------------------------------------------------------------
//
CFbsBitmap* CAknPrivateImageLoader::GenerateMaskLC( TSize aSize )
    {
    CFbsBitmap* mask = new(ELeave) CFbsBitmap;
    CleanupStack::PushL( mask );
    User::LeaveIfError( mask->Create( aSize, EGray2 ) );

    TInt width = aSize.iWidth;
    TInt height = aSize.iHeight;
    HBufC8* buf = HBufC8::NewLC( mask->ScanLineLength( width, EGray2 ) );
    TPtr8 bufPtr( buf->Des() );
    
    for( TInt i = 0; i < height; ++i )
        {
        mask->GetScanLine( bufPtr, TPoint( 0, i ), width, EGray2 );
        bufPtr.FillZ();
        mask->SetScanLine( bufPtr, i );
        }
    
    CleanupStack::PopAndDestroy( buf );
    User::LeaveIfError( mask->Compress() );
    return mask;
    }

// ---------------------------------------------------------------------------
// CAknPrivateImageLoader::DecodeSize
// ---------------------------------------------------------------------------
//
TSize CAknPrivateImageLoader::DecodeSize( 
    const TFrameInfo& aFrameInfo, 
    const TSize& aTargetSize )
    {
    TSize imageSize( aFrameInfo.iOverallSizeInPixels );
    
    if( aFrameInfo.iFlags & TFrameInfo::EFullyScaleable || 
        aTargetSize == imageSize )
        {
        // decoder can scale to any ratio or the size is already correct
        return aTargetSize;
        }
    
    if( imageSize.iWidth < aTargetSize.iWidth ||
        imageSize.iHeight < aTargetSize.iHeight )
        {
        // image is smaller than targetsize
        return imageSize;
        }
    
    // Scale ratio limits
    const TInt KScaleRatioMin = 2;
    const TInt KScaleRatioMax = 8;
    
    // 1:1 is always valid ratio for decode scaling
    TInt lastValidRatio( 1 );
    for( TInt ratio = KScaleRatioMin; ratio <= KScaleRatioMax; ratio <<= 1 )
        {
        if( imageSize.iWidth % ratio + imageSize.iHeight % ratio == 0 )
            {
            // this ratio is valid
            if( imageSize.iWidth / ratio < aTargetSize.iWidth || 
                imageSize.iHeight / ratio < aTargetSize.iHeight )
                {
                // the decoded size was smaller in some dimension, 
                // the last valid ratio should be used
                break;
                }
                
            // this scale ratio results to greater or equal size
            lastValidRatio = ratio;
            }
        }
    
    // return the size scaled with correct ratio
    return TSize( imageSize.iWidth / lastValidRatio, 
                  imageSize.iHeight / lastValidRatio );
    }

// End of file
