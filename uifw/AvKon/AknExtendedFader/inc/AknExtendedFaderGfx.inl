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
#ifndef AKNEXTENDEDFADERGFX_INL_
#define AKNEXTENDEDFADERGFX_INL_

inline void TAknExtendedFaderGfx::AlignTo32Bytes(TUint32* data, TUint32 width, TUint32& leftwidth, TUint32& middlewidth, TUint32& rightwidth)
	{
	leftwidth = width; middlewidth = 0; rightwidth = 0;
	
	if(width>7)
		{
		// Calculate amount of residual pixels on the left side of 8-word aligned memory
		leftwidth = (0x20 - (TUint32(data)&0x1F)) >> 2;
		
		if(leftwidth==8)
			{
			// No alignment needed
			leftwidth = 0;
			middlewidth = width;
			rightwidth = middlewidth & 0x7;
			middlewidth -= rightwidth;
			}
		else if(leftwidth<width)
			{
			// Scanline more than 8 pixels long
			middlewidth = width - leftwidth;
			rightwidth = middlewidth & 0x7;
			middlewidth -= rightwidth;
			}
		else
			{
			// Less than 8 pixels wide
			leftwidth = width;
			middlewidth = rightwidth = 0;
			}
		}		
	}	

inline void TAknExtendedFaderGfx::ReadBurst(TUint32* aSource, TUint32& a1, TUint32& a2, TUint32& a3, TUint32& a4)
    {
    a1 = *aSource;
    a2 = *( aSource + 1 );
    a3 = *( aSource + 2 );
    a4 = *( aSource + 3 );
    }
      
inline void TAknExtendedFaderGfx::ReadBurst(TUint32* aSource, TUint32& a1, TUint32& a2, TUint32& a3, TUint32& a4, TUint32& a5, TUint32& a6, TUint32& a7, TUint32& a8)
    {
    a1 = *aSource;
    a2 = *( aSource + 1 );
    a3 = *( aSource + 2 );
    a4 = *( aSource + 3 );
    a5 = *( aSource + 4 );
    a6 = *( aSource + 5 );
    a7 = *( aSource + 6 );
    a8 = *( aSource + 7 );
    }
	
inline void TAknExtendedFaderGfx::WriteBurst(TUint32* aDest, TUint32 a1, TUint32 a2, TUint32 a3, TUint32 a4, TUint32 a5, TUint32 a6, TUint32 a7, TUint32 a8)
	{
	*aDest = a1;
	*( aDest + 1 ) = a2;
	*( aDest + 2 ) = a3;
	*( aDest + 3 ) = a4;
	*( aDest + 4 ) = a5;
	*( aDest + 5 ) = a6;
	*( aDest + 6 ) = a7;
	*( aDest + 7 ) = a8;
	}
	
inline void TAknExtendedFaderGfx::WriteBurst(TUint32* aDest, TUint32 a1, TUint32 a2, TUint32 a3, TUint32 a4)
	{
	*aDest = a1;
	*( aDest + 1 ) = a2;
	*( aDest + 2 ) = a3;
	*( aDest + 3 ) = a4;
	}


// Include CPU specific stuff
#ifdef __ARM11_SUPPORT
#include "AknExtendedFaderGfx_ARM11.inl"
#else
#include "AknExtendedFaderGfx_Basic.inl"
#endif

#endif
