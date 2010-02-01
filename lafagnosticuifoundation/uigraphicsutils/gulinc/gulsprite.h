// Copyright (c) 2001-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#if !defined(__GULSPRITE_H__)
#define __GULSPRITE_H__

#include <w32std.h>
#include <gulicon.h>

class CWindowToBitmapMappingGc;

class CSpriteSet : public CBase
/**
The CSpriteSet class allows a window server sprite to be drawn to a window.  The class
supports storage of any number of bitmap/mask pairs, though allowing only one of these
bitmap/mask members to be displayed at any one time.  The client of this class should
provide the source bitmap/mask pairs which can be resized to fit a specified rectangle.
Also provided for at runtime is the ability to draw onto the sprite as though it were a
regular CWindowGc and using the same coordinate offsets as the window it exists in.

@publishedPartner 
@released 
*/
	{
public:
	enum TSpriteResizeMode
		{
		ENoResizing,
		EResizeHorizToFit,
		EResizeVertToFit,
		EResizeHorizAndVertToFit
		};
public:
	// methods for creation of the sprite set
	IMPORT_C static CSpriteSet* NewL(RWindowTreeNode& aWindow, RWsSession& aWs, CWsScreenDevice& aDevice, CGulIcon* aSpriteSetMember, TBool aInvertMask);
	IMPORT_C static CSpriteSet* NewLC(RWindowTreeNode& aWindow, RWsSession& aWs, CWsScreenDevice& aDevice, CGulIcon* aSpriteSetMember, TBool aInvertMask);
	IMPORT_C void AddMemberL(CGulIcon* aSpriteSetMember);
	IMPORT_C void RemoveMember(TInt aSpriteSetMemberIndex);
	// methods for preparing and using a sprite in the set
	IMPORT_C void PrepareSpriteForDisplayL(TInt aSpriteType, const TPoint& aSpritePos, const TSize& aSpriteSize, TSpriteResizeMode aSpriteResizeMode);
	IMPORT_C void StartDisplayingSpriteL();
	IMPORT_C void StopDisplayingSprite();
	IMPORT_C CWindowGc* SpriteGc() const;
	IMPORT_C void TranslateSpritePosition(const TPoint& aSpritePos);
	IMPORT_C void SetClippingRect(const TRect& aRect);
public:
	~CSpriteSet();
private:
	enum TInternalSpriteResizeMode
		{
		EHSameVSame,
		EHSameVShrink,
		EHSameVStretch,
		EHShrinkVSame,
		EHShrinkVShrink,
		EHShrinkVStretch,
		EHStretchVSame,
		EHStretchVShrink,
		EHStretchVStretch
		};
private:
	CSpriteSet(TBool aInvertMask);
	void ConstructL(RWindowTreeNode& aWindow, RWsSession& aWs, CWsScreenDevice& aDevice);
	void CreateSpriteMember();
	void AdjustSpriteSizeAccordingToResizeMode(TSize& aTargetSize, const TSize& aSourceSize, TSpriteResizeMode aSpriteResizeMode) const;
	void ComputeInternalResizeMode(TInternalSpriteResizeMode& aInternalSpriteResizeMode, TSpriteResizeMode aSpriteResizeMode, const TSize& aSourceSize, const TSize& aSpriteSize) const;
	void RenderSprite(TInt aSpriteType, TInternalSpriteResizeMode aInternalSpriteResizeMode, const TSize& aSourceSize, const TSize& aSpriteSize);
private:
	enum TFlags
		{
		EMaskIsInverted				=0x01,
		ESpriteIsCurrentlyDisplayed	=0x02
		};
private:
	RPointerArray<CGulIcon> iSourceMembers;
	CWsBitmap* iTargetBitmap;
	CWsBitmap* iTargetMaskBitmap;
	RWsSprite iSprite;
	TSpriteMember iSpriteMember;
	CWindowToBitmapMappingGc* iWindowToBitmapMappingGc;
	CFbsBitGc* iMainFbsBitGc;
	CFbsBitGc* iMaskFbsBitGc;
	CFbsBitmapDevice* iMainBmpDevice;
	CFbsBitmapDevice* iMaskBmpDevice;
	TPoint iSpritePosition;
	TRect iClippingRect;
	TInt iFlags;
	};

#endif
