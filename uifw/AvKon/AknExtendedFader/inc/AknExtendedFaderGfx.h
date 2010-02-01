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
#ifndef AKNEXTENDEDFADERGFX_H_
#define AKNEXTENDEDFADERGFX_H_
    
class TAknExtendedFaderGfx
{
public:
	// Rectangle grayscale fading with color overlay
	static void FadeRect_GrayColorize_16MX(TUint32* aPixels, TUint32 aStrideInPixels, TInt x1, TInt y1, TInt x2, TInt y2, const TInt aFadeMapFactor, const TInt aFadeMapOffset, const TUint32 aROverlay, const TUint32 aGOverlay, const TUint32 aBOverlay);
	static void FadeRect_GrayColorize_64K(TUint16* aPixels, TUint32 aStrideInPixels, TInt x1, TInt y1, TInt x2, TInt y2, const TInt aFadeMapFactor, const TInt aFadeMapOffset, const TUint32 aROverlay, const TUint32 aGOverlay, const TUint32 aBOverlay);

	// Memory alignment and burst access
	static inline void AlignTo32Bytes(TUint32* data, TUint32 width, TUint32& leftwidth, TUint32& middlewidth, TUint32& rightwidth);
	
	static inline void ReadBurst(TUint32* aSource, TUint32& a1, TUint32& a2, TUint32& a3, TUint32& a4);
	static inline void ReadBurst(TUint32* aSource, TUint32& a1, TUint32& a2, TUint32& a3, TUint32& a4, TUint32& a5, TUint32& a6, TUint32& a7, TUint32& a8);
	
	static inline void WriteBurst(TUint32* aDest, TUint32 a1, TUint32 a2, TUint32 a3, TUint32 a4);
	static inline void WriteBurst(TUint32* aDest, TUint32 a1, TUint32 a2, TUint32 a3, TUint32 a4, TUint32 a5, TUint32 a6, TUint32 a7, TUint32 a8);
	
	// CPU cache preload
	static inline void PreLoad(TUint32 aStartAddress);
	
	// Per pixel processing
	static inline TUint32 PixelToGrayscaleWithFade_64K(register TUint32 aPixel, register TInt aFadeMapFactor, register TInt aFadeMapOffset, const TUint32 aROverlay, const TUint32 aGOverlay, const TUint32 aBOverlay);
};

#include "AknExtendedFaderGfx.inl"

#endif
