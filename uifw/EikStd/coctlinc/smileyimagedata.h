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
* Description:  smiley utility class
*
*/

#ifndef C_SMILEYIMAGEDATA_H
#define C_SMILEYIMAGEDATA_H

#include <e32base.h>

class CSmileyBmpObserver;
class CSmileyIcon;
class CFbsBitmap;
class TImageInfo;
class CFbsBitmapDevice;
class CFbsBitGc;

NONSHARABLE_CLASS( CSmileyImageData ): public CBase
	{	
public:
	CSmileyImageData( CSmileyBmpObserver* aObserver );
	~CSmileyImageData();
	
public:
// new functions
    void CreateImageL( const TDesC& aIconFileName, TImageInfo& aInfo );    
    void DeleteImage();
    
    TInt RefArrayCount();
    void AddToRefArray( CSmileyIcon* aNode );
    void RemoveFromRefArray( CSmileyIcon* aNode );
    CSmileyIcon* RefIcon( TInt aIndex );
    
    TText Code();
    void SetCode( TText aCode );
    
    CFbsBitmap* Bitmap();
    CFbsBitmap* Mask();    
    CFbsBitmap* StaticBmp();
    CFbsBitmap* StaticMask();
    TSize BitmapSize();
    void SetBitmapSize( TSize aBmpSize, TBool aForceSet = EFalse );
    TBool IsAnimation();
    TBool IsAnimationFinished();
    
    
private:
    void CreateBmpAndMaskL( const TDesC& aIconFileName, TImageInfo& aInfo );
    void CreateStaticBmpAndMaskForAnimationL( const TDesC& aIconFileName, 
        TImageInfo& aInfo );
	
private: //data
    TText iCode;
	// own
	CFbsBitmap* iBmp;
	// own
	CFbsBitmap* iMask;
	// own
	CFbsBitmap* iStaticBmp;
	// own
	CFbsBitmap* iStaticMask;
	TSize iBmpSize;	
	TBool iIsAnimation;
	// own
	CSmileyBmpObserver* iObserver;
	RArray<CSmileyIcon*> iRefArray;	
	};

#endif C_SMILEYIMAGEDATA_H
