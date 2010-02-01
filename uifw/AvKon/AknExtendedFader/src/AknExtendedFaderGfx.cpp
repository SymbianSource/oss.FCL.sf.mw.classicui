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
#include <e32base.h>
#include "AknExtendedFaderGfx.h"


void TAknExtendedFaderGfx::FadeRect_GrayColorize_16MX(TUint32* aPixels, TUint32 aStrideInPixels, TInt x1, TInt y1, TInt x2, TInt y2, const TInt aFadeMapFactor, const TInt aFadeMapOffset, const TUint32 aROverlay, const TUint32 aGOverlay, const TUint32 aBOverlay)
	{	
	// Width and height of the rectangle
	TUint32 width = x2-x1;
	TUint32 height = y2-y1;
	
	// Get pointer to first pixel
	register TUint32* data = aPixels + x1 + aStrideInPixels*y1;
	
	// Padding is the amount of bytes we need to skip after single scanline to reach the beginning of the next one
	TUint32 padding = (aStrideInPixels - width)<<2;

	// Align address to 32-byte boundary
	TUint32 leftwidth, middlewidth, rightwidth;	
	AlignTo32Bytes(data, width, leftwidth, middlewidth, rightwidth);

	// 8 pixels at a time in the midsection
	middlewidth>>=3;
	
	// Shift offset so we can remove one shift operation for each pixel
	const TUint32 shiftedFadeMapOffset = aFadeMapOffset << 18;
	
	// Constants for greyscale conversion
	const TUint32 KRBCoef(0x0144007C); // Coefficients for R & B: 324, 124 (/ 1024)
	const TUint32 KGCoef(0x00000240);  // Coefficient for G: 576
	TUint32 rbOverlay = (aROverlay << 16) | aBOverlay; // Combine R & B overlays to do two calculations at once
	
	FadeAlignedRect_GrayColorize_16MX(data, height, KRBCoef, KGCoef, aFadeMapFactor, shiftedFadeMapOffset, rbOverlay, aGOverlay, leftwidth, middlewidth, rightwidth, padding);
	}


void TAknExtendedFaderGfx::FadeRect_GrayColorize_64K(TUint16* aPixels, TUint32 aStrideInPixels, TInt x1, TInt y1, TInt x2, TInt y2, const TInt aFadeMapFactor, const TInt aFadeMapOffset, const TUint32 aROverlay, const TUint32 aGOverlay, const TUint32 aBOverlay)
	{	
	// Width and height of the rectangle
	TUint32 width = x2-x1;
	TUint32 height = y2-y1;
	
	// Get pointer to first pixel
	register TUint16* data = aPixels + x1 + aStrideInPixels*y1;
	
	// Padding is the amount of pixels we need to skip after single scanline to reach the beginning of the next one
	TUint32 padding = aStrideInPixels - width;
		
	// Helper variables
	register TInt x;
	
	while(height--)
		{
		x = width;

		while(x--)
			{
			// Process pixels
			*data++ = PixelToGrayscaleWithFade_64K((TUint32)*data, aFadeMapFactor, aFadeMapOffset, aROverlay, aGOverlay, aBOverlay);
			}

		data+=padding;
		}
	}

