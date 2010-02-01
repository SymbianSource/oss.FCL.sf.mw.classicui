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


#ifndef CAKNPRIVATEIMAGELOADER_H
#define CAKNPRIVATEIMAGELOADER_H

// INCLUDES
#include <e32base.h>
#include <f32file.h>

// FORWARD DECLARATION
class CEikImage;
class CImageDecoder;
class CFbsBitmap;
class CAknIcon;
class MSvgError;
class TFrameInfo;


/**
 * Observer interface for CAknPrivateImageLoader.
 * 
 * @since S60 3.2
 * @lib AknOldStyleNotif.DLL
 */
class MAknPrivateImageLoaderObserver
    {
public:
    /**
     * Called when image loading has succeeded.
     * @param aImage Newly loaded image. Observer is responsible of
     *        taking the ownership of the image.
     */
    virtual void ImageLoadSuccess( CEikImage* aImage ) = 0;
    
    /**
     * Called when image loading has failed. 
     * @param aError General Symbian error code. 
     */
    virtual void ImageLoadError( TInt aError ) = 0;
    
protected:
    /// virtual destructor
    virtual ~MAknPrivateImageLoaderObserver() {};
    };


/**
 * Private image loader to convert binary array into usable image. Used by 
 * dynamic soft notification. Supports CImageDecoder formats + SVG images.
 * 
 * @since S60 3.2
 * @lib AknOldStyleNotif.DLL
 */
NONSHARABLE_CLASS( CAknPrivateImageLoader ) : public CActive
    {
public: // Construction & destruction

    /**
     * Constructor.
     * 
     * @param aFs Valid file server handle.
     * @param aObserver Image loader observer.
     */
    static CAknPrivateImageLoader* NewL( RFs& aFs,
        MAknPrivateImageLoaderObserver& aObserver );

    /**
     * Constructor.
     * 
     * @param aFs Valid file server handle.
     * @param aObserver Image loader observer.
     */
    static CAknPrivateImageLoader* NewLC( RFs& aFs,
        MAknPrivateImageLoaderObserver& aObserver );

    /**
     * Destructor.
     */
    virtual ~CAknPrivateImageLoader();


public: // new methods
    
    /**
     * Create scalable bitmap from binary data. This operation is asynchronous.
     * When image loading is complete, it will be reported to observer.
     * 
     * @param aImageData Image data.
     *        - If image data is bitmap and it's bigger than 300x300, then 
     *          leave KErrTooBig will occur.
     * @param aSize Preferred size
     *        - will determine the size of svg images
     *        - bitmaps will be scaled down to as close as possible to this size
     */    
    void LoadIconL( const TDesC8& aImageData, TSize aSize );
    
private: // From CActive
    void RunL();
    void DoCancel();
    TInt RunError( TInt aError ); 
    
private: // new methods

    /**
     * Constructor.
     * 
     * @param aFs Valid file server handle.
     * @param aObserver Observer for image loader.
     */
    CAknPrivateImageLoader( RFs& aFs,
        MAknPrivateImageLoaderObserver& aObserver );

    /**
     * Constructor.
     */
    void ConstructL();
    
    /**
     * Inverts pixels of given image (bit operation).
     * @aBitmap Inverted image.
     */
    void InvertImageL( CFbsBitmap& aBitmap );
    
    /**
     * Creates a scalable icon from bitmap image.
     *  
     * @param aIcon Non-scalable bitmap and mask. mask is optional.
     *        Note! takes ownership of aIcon (leave safe)
     * @return New scalable icon instance.
     */
    CAknIcon* CreateIconL( CAknIcon* aIcon ); 
    
    /**
     * Create bitmap from binary data.
     * 
     * @param aImageData Image data.
     *        - If bitmap is bigger than 300x300, then 
     *          leave KErrTooBig will occur.
     * @param aSize Preferred load size. Loader will try to shrink the loaded 
     *        image to aSize or as close to it as possible.
     */    
    void LoadL( const TDesC8& aImageData, TSize aSize );
    
    /**
     * Create SVG image from binary data.
     * 
     * @param aImageData Image data.
     * @param aSize Preferred size of the new icon.
     */        
    void LoadSVGImageL(    
        const TDesC8& aImageData, 
        TSize aSize );

    /**
     * Leaves with KErrCorrupt if given svg engine error is actual error.
     * 
     * @param aError SVG engine error object.
     */
    void LeaveIfErrorL( MSvgError* aError );

    /**
     * Generate a fully transparent mask.
     * 
     * @param aSize Mask's size.
     * @return Created mask.
     */
    CFbsBitmap* GenerateMaskLC( TSize aSize );

    /**
     * Get decoder size for CImageDecoder. Returns the closest possible size to
     * aTargetSize for decoder. Image will not be scaled upwards.
     * 
     * @param aFrameInfo Decoded images frame info.
     * @param aTargetSize TargetSize to decode.
     * @return New size used to decoded image.
     */
    TSize DecodeSize( const TFrameInfo& aFrameInfo, const TSize& aTargetSize );
    
private: // data
    /// Own. Currently loaded image
    CAknIcon* iIcon;
    /// Own. Image loader/decoder.
    CImageDecoder* iDecoder;
    /// Not own. Image loading observer.
    MAknPrivateImageLoaderObserver& iObserver;
    /// Not own. File system handle
    RFs& iFs;
    };

#endif // CAKNPRIVATEIMAGELOADER_H
