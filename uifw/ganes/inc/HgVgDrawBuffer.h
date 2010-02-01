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

#ifndef HGVGDRAWBUFFER_H_
#define HGVGDRAWBUFFER_H_

// INCLUDES
#include <e32base.h>
#include <VG/openvg.h>
#include <gulcolor.h>

/**
 * Helper class for rendering graphics to offscreen buffer
 * using avkon and then copying that buffer to OpenVG images.
 */
NONSHARABLE_CLASS(CHgVgDrawBuffer) : public CBase
    {
public:

    /**
     * Creates new CHgVgDrawBuffer
     * 
     * @param aDrawBufferSize
     * @param aDisplayMode
     * @return HgVgDrawBuffer-object
     */
    static CHgVgDrawBuffer* NewL (const TSize& aDrawBufferSize, const TDisplayMode& aMode); 
        
    // Destructor.
    virtual ~CHgVgDrawBuffer();

public: // METHODS

    /**
     * Getter for buffer size in pixels.
     * 
     * @return buffer size in pixels.
     */
    const TSize& BufferSize() const;
    
    /**
     * Getter for draw context.
     * 
     * @return reference to CFbsBitGc-object.
     */
    CFbsBitGc& Gc();
    
    /**
     * 
     */
    CFbsBitmap& DrawBuffer();
        
    /**
     * Clears draw buffer
     * 
     * @param aColor color to clear.
     */
    void Clear(const TRect& aRect, const TRgb& aColor);
        
    /**
     * Draws text to draw buffer.
     * 
     * @param aText text.
     * @param aFont font to use for text rendering.
     * @param aColor color to use for text rendering.
     * @param aPosition position to render.
     */
    void DrawText(const TDesC& aText, const CFont* aFont, 
            const TRgb& aColor, const TPoint& aPosition);
    
    /**
     * Gets drawbuffer to VGImage.
     * 
     * @param aSrcRect rectangle in draw buffer to copy to the image.
     * @param aDestRect rectangle in image.
     * @param aDestImage destination image.
     */
    void GetDrawBufferToVgImage(const TRect& aSrcRect, 
            const TPoint& aDest, VGImage destImage, VGImageFormat destFormat);
        
protected: // Constructors
    CHgVgDrawBuffer( );

    void ConstructL (const TSize& aBufferSize, const TDisplayMode& aMode );
    
private: // Data
        
    CFbsBitmapDevice* iDevice; // owns
    CFbsBitmap* iDrawBuffer; // owns
    CFbsBitGc* iGc; // owns
    TSize iBufferSize;

    };

#endif /* HGVGDRAWBUFFER_H_ */
