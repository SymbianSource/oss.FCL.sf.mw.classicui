// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//


#if !defined(__BMPANCLI_H__)
#define __BMPANCLI_H__

#include <e32base.h>
#include <w32std.h>
#include <fbs.h>

//
// CFrameData
//


/** 
Encapsulates the information required for one frame of an animation. 

Each animation frame includes a bitmap that is displayed in a specified position 
for a specified length of time. You can optionally include a mask that either 
hides part of the bitmap, or makes part of the bitmap transparent so that the 
background can be seen.

You will probably need to define several frames for a complete animation. 
When you have defined the frames you require, use CBitmapAnimClientData to 
construct the animation itself. 

@publishedAll
@released 
*/
class CBitmapFrameData : public CBase
	{
public:
	IMPORT_C ~CBitmapFrameData();
	IMPORT_C static CBitmapFrameData* NewL();
	IMPORT_C static CBitmapFrameData* NewL(CFbsBitmap* aBitmap, CFbsBitmap* aMask=NULL);
	IMPORT_C static CBitmapFrameData* NewL(CFbsBitmap* aBitmap, CFbsBitmap* aMask, TInt aIntervalInMilliSeconds, TPoint aPosition);
//
	IMPORT_C void SetBitmap(CFbsBitmap* aBitmap);
	IMPORT_C void SetMask(CFbsBitmap* aMask);
	IMPORT_C void SetPosition(TPoint aPosition);
	IMPORT_C void SetInterval(TInt aIntervalInMilliSeconds);
	IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);
//
	IMPORT_C CFbsBitmap* Bitmap() const;
	IMPORT_C CFbsBitmap* Mask() const;
	IMPORT_C TInt IntervalInMilliSeconds() const;
	IMPORT_C TPoint Position() const;
	IMPORT_C TBool BitmapsOwnedExternally() const;
private:
	CBitmapFrameData();
private:
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMaskBitmap;
	TBool iBitmapsOwnedExternally;
	TInt iIntervalInMilliSeconds;
	TPoint iPosition;
	};


//
// CBitmapAnimClientData
//


/** 
Encapsulates one or more animation frames into an entire animation.

In addition to specifying the frames you wish to include in your animation, 
you can also specify:

- whether the animation will flash

- whether the animation is played once, or continuously

- the background frame that is drawn to clear each frame in the animation

You can also specify a default frame interval that is used for all frames 
in an animation. If the interval is already set for any of the individual 
frames, that takes precedence.

When you have defined your animation, use RBitmapAnim to play the animation. 

@publishedAll 
@released 
*/
class CBitmapAnimClientData : public CBase
	{
public:
	/** Animation play mode flags. 

	The animation can be played in any of the ways described below. */
	enum TPlayMode
		{
		/** Plays the animation once, from the first frame to the last one. */
		EPlay		= 0x00,
		/** Plays the animation from the first frame to the last one continuously. */
		ECycle		= 0x01,
		/** Plays the animation from the first frame to the last one then from the last 
		frame to the first continuously. */
		EBounce		= 0x02
		};
public:
	IMPORT_C static CBitmapAnimClientData* NewL();
	IMPORT_C ~CBitmapAnimClientData();
//
	IMPORT_C void AppendFrameL(CBitmapFrameData* aFrame);
	IMPORT_C void ResetFrameArray();
	IMPORT_C void SetBackgroundFrame(CBitmapFrameData* aBackgroundFrame);
	IMPORT_C void SetFlash(TBool aFlash);
	IMPORT_C void SetFrameInterval(TInt aFrameIntervalInMilliSeconds);
	IMPORT_C void SetPlayMode(TPlayMode aPlayMode);
//
	IMPORT_C CBitmapFrameData* BackgroundFrame() const;
	IMPORT_C TBool Flash() const;
	IMPORT_C const CArrayPtrFlat<CBitmapFrameData>& FrameArray() const;
	IMPORT_C TInt FrameIntervalInMilliSeconds() const;
	IMPORT_C TPlayMode PlayMode() const;
//
	IMPORT_C TInt DurationInMilliSeconds() const;
	IMPORT_C TSize Size() const;
private:
	CBitmapAnimClientData();
private:
	TBool iFlash;
	TPlayMode iPlayMode;
	TInt iFrameIntervalInMilliSeconds;
	CArrayPtrFlat<CBitmapFrameData> iFrameArray;
	CBitmapFrameData* iBackgroundFrame;
	};



/** 
Enables a client to package animation data, and send it to the window server 
for display.

Before using RBitmapAnim, a client must instantiate an RAnimDll. This provides 
a reference to the window server DLL that runs the animation specified through 
the RBitmapAnim() object. To complete construction, call ConstructL(). 

@publishedAll 
@released 
*/
class RBitmapAnim : public RAnim
	{
public:
	IMPORT_C RBitmapAnim(RAnimDll& aAnimDll);
	IMPORT_C void ConstructL(const RWindowBase& aWindow);
	IMPORT_C void DisplayFrameL(TInt aIndex);
	IMPORT_C void SetBitmapAnimDataL(const CBitmapAnimClientData& aBitmapAnimData);
	IMPORT_C void SetFlashL(TBool aFlash);
	IMPORT_C void SetFrameIntervalL(TInt aFrameIntervalInMilliSeconds);
	IMPORT_C void SetPlayModeL(CBitmapAnimClientData::TPlayMode aPlayMode);
	IMPORT_C void StartL();
	IMPORT_C void StopL();
	IMPORT_C void SetNumberOfCyclesL(TInt aNumberOfCycles);
	IMPORT_C void SetPositionL(TPoint aPosition);
private:
	void SetAttributesL(const CBitmapAnimClientData& aBitmapAnimData);
	void SetBackgroundFrameL(const CBitmapFrameData& aFrame);
	void SetFrameArrayL(const CArrayPtrFlat<CBitmapFrameData>& aFrameArray);
	void SetFrameL(const CBitmapFrameData& aFrame, TInt aOpCode);
	};

#endif

