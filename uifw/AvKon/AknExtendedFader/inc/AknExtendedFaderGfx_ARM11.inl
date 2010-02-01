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
#ifndef AKNEXTENDEDFADERGFX_ARM11_INL_
#define AKNEXTENDEDFADERGFX_ARM11_INL_

#ifdef __ARM11_SUPPORT

// Externalization of our assembler version of the fader
extern "C" void FadeAlignedRect_GrayColorize_16MX(TUint32* address, TUint32 height, TUint32 rbCoef, TUint32 gCoef, TUint32 fadeMapFactor, TUint32 fadeMapOffset, TUint32 rbOverlay, TUint32 gOverlay, TUint32 leftwidth, TUint32 middlewidth, TUint32 rightwidth, TUint32 padding);

__forceinline void TAknExtendedFaderGfx::PreLoad(TUint32 aStartAddress)
	{
	asm( "pld [aStartAddress]" );
    }

inline TUint32 TAknExtendedFaderGfx::PixelToGrayscaleWithFade_64K(register TUint32 aPixel, register TInt aFadeMapFactor, register TInt aFadeMapOffset, const TUint32 aROverlay, const TUint32 aGOverlay, const TUint32 aBOverlay)
	{
	const TUint32 KRCoef(0x00000144); // R coefficient: 324
	const TUint32 KGCoef(0x00000009); // G coefficient: 9 (* 64 = 576 as G will already be shifted left 6 bits)
	const TUint32 KBCoef(0x0000007C); // B coefficient: 124
	
	// Unpack R,G,B
	register TUint32 r = (aPixel & 0xf800)>>11; // asm("and r, pixel, #0xf800");
	register TUint32 g = (aPixel & 0x07e0); // asm("and g, pixel, #0x07e0");
	register TUint32 b = aPixel & 0x001f; // asm("and b, pixel, #0x001f");
	
	// Calculate unadjusted greyscale value
	aPixel = r*KRCoef + g*KGCoef + b*KBCoef;
		
	// Do fading and adjustment to get a greyscale value between 0-255
	aPixel = (((aPixel * aFadeMapFactor) >> 15 ) + aFadeMapOffset) & 0xFF;
	
	// Colorize and pack
	aPixel = ((aPixel*aROverlay)&0xf800) | (((aPixel*aGOverlay)>>5)&0x07e0) | ((aPixel*aBOverlay)>>11);
	
	return aPixel;
	}

#endif

#endif
