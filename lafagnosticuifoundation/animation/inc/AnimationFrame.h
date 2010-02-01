// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __ANIMATIONFRAME_H__
#define __ANIMATIONFRAME_H__

#include <icl/imagedata.h>

class CFbsBitmap;

/**
Data format for individual bitmap format animation frames.

Animators and data providers which use the "bitmap" data type use objects
of this type to transfer data.

You do not need to instantiate an object of this type unless you are writing
a new data provider.

@see CBitmapAnimator
@see CICLAnimationDataProvider
@publishedAll
@released
*/
class CAnimationFrame : public CBase
	{
public:
	/** Structure used for passing a CAnimationFrame safely over a
	client/server connection.*/
	struct THandles
		{
		/** A handle to the bitmap into which the decoded frame(s) are put */
		TInt iBitmapHandle;
		/**	The bitmap mask for the changed area for this frame */
		TInt iMaskHandle;
		/** General frame info provided by all plugins */
		TFrameInfo iFrameInfo;
		};
public:
	virtual ~CAnimationFrame();
	IMPORT_C static CAnimationFrame* NewL();
	IMPORT_C static CAnimationFrame* NewL(const THandles& aHandles);
	IMPORT_C void GetHandles(THandles & aHandles) const;
	IMPORT_C void SetHandlesL(const THandles & aHandles);
	IMPORT_C void CreateL(const TFrameInfo& aFrameInfo);
	/** Returns the bitmap image for the changed area for this frame
	@return A pointer to a CFbsBitmap */
	CFbsBitmap* Bitmap()				{ return iBitmap; }
	/** Returns the bitmap image for the changed area for this frame
	@return A pointer to a const CFbsBitmap */
	const CFbsBitmap* Bitmap() const	{ return iBitmap; }
	/** Returns the bitmap mask for the changed area for this frame
	@return A pointer to a CFbsBitmap */
	CFbsBitmap* Mask()					{ return iMask; }
	/** Returns the bitmap mask for the changed area for this frame
	@return A pointer to a const CFbsBitmap */
	const CFbsBitmap* Mask() const		{ return iMask; }
	/** Returns information about the frame.
  	@return A TFrameInfo */
  	TFrameInfo& FrameInfo() 			{ return iFrameInfo; }
  	/** Returns information about the frame.	
	@return A const TFrameInfo */
	const TFrameInfo& FrameInfo() const	{ return iFrameInfo; }
protected:
	IMPORT_C virtual void CAnimationFrame_Reserved1();
	IMPORT_C virtual void CAnimationFrame_Reserved2();
private:
	TInt iCAnimationFrame_Reserved;
private:
	CAnimationFrame() {};
	CAnimationFrame(const CAnimationFrame&); // no implementation
	CAnimationFrame& operator=(const CAnimationFrame&); // no implementation
	void ConstructL();
private:
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMask;
	TFrameInfo iFrameInfo;
	};

#endif //__ANIMATIONFRAME_H__
