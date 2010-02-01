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

#include <gulsprite.h>
#include <gulgcmap.h>
#include "GULSTD.H"

const TInt KOffScreenValue = -1000;

/**
 * Creates and returns a pointer to a CSpriteSet object clipped to the parent aWindow. The
 * sprite set is initialized with aSpriteSetMember and the sprite set takes ownership of
 * this parameter.  aWs is the window session used.  aInvertMask specifies whether the
 * bitmap/mask pairs which will be added will use an inverted mask.
 */
EXPORT_C CSpriteSet* CSpriteSet::NewL(RWindowTreeNode& aWindow, RWsSession& aWs, CWsScreenDevice& aDevice, CGulIcon* aSpriteSetMember, TBool aInvertMask)
	{//static
	CSpriteSet* self = CSpriteSet::NewLC(aWindow,aWs,aDevice,aSpriteSetMember,aInvertMask);
	CleanupStack::Pop();
	return self;
	}

/**
 * Creates and returns a pointer to a CSpriteSet object clipped to the parent aWindow. The
 * sprite set is initialized with aSpriteSetMember and the sprite set takes ownership of
 * this parameter.  aWs is the window session used.  aInvertMask specifies whether the
 * bitmap/mask pairs which will be added will use an inverted mask.  Leaves the returned
 * pointer on the cleanup stack.
 */
EXPORT_C CSpriteSet* CSpriteSet::NewLC(RWindowTreeNode& aWindow, RWsSession& aWs, CWsScreenDevice& aDevice, CGulIcon* aSpriteSetMember, TBool aInvertMask)
	{//static
	CSpriteSet* self = new(ELeave) CSpriteSet(aInvertMask);
	CleanupStack::PushL(self);
	self->ConstructL(aWindow,aWs,aDevice);
	self->AddMemberL(aSpriteSetMember);
	return self;
	}

/**
 * Adds aSpriteSetMember to the sprite set.  Panics if a null member is passed in, or
 * if the argument does not include a bitmap and mask.
 */
EXPORT_C void CSpriteSet::AddMemberL(CGulIcon* aSpriteSetMember)
	{
	__ASSERT_ALWAYS(aSpriteSetMember != NULL, Panic(EEgulPanicAttemptToAppendNullMember));
	__ASSERT_ALWAYS(aSpriteSetMember->Bitmap() && aSpriteSetMember->Mask(), Panic(EEgulPanicAttemptToAppendIncompleteMember));
	User::LeaveIfError(iSourceMembers.Append(aSpriteSetMember));
	}

/**
 * Removes a member (indexed by aSpriteSetMemberIndex) from the array.
 * Panics if the member index is not within the existing array's range.
 */
EXPORT_C void CSpriteSet::RemoveMember(TInt aSpriteSetMemberIndex)
	{
	__ASSERT_ALWAYS((aSpriteSetMemberIndex >= 0) && (aSpriteSetMemberIndex < iSourceMembers.Count()),Panic(EEgulPanicInvalidSpriteIndex));
	delete iSourceMembers[aSpriteSetMemberIndex];
	iSourceMembers.Remove(aSpriteSetMemberIndex);
	}

/**
 * Prepares the sprite in the set of type aSpriteType to be displayed at
 * aSpritePos with size aSpriteSize.  The sprite will be resized as necessary under the
 * restriction of aSpriteResizeMode.
 */
EXPORT_C void CSpriteSet::PrepareSpriteForDisplayL(TInt aSpriteType, const TPoint& aSpritePos, const TSize& aSpriteSize, TSpriteResizeMode aSpriteResizeMode)
	{
	__ASSERT_DEBUG((aSpriteType >= 0) && (aSpriteType < iSourceMembers.Count()),Panic(EEgulPanicInvalidSpriteIndex));
	__ASSERT_DEBUG((aSpriteSize.iWidth >= 0) && (aSpriteSize.iHeight >= 0),Panic(EEgulPanicNegativeSpriteSize));
	iSpritePosition = aSpritePos;
	iMainFbsBitGc->SetOrigin(TPoint(0,0));
	TSize spriteSize(aSpriteSize);
	const TSize sourceSize(iSourceMembers[aSpriteType]->Bitmap()->SizeInPixels());
	AdjustSpriteSizeAccordingToResizeMode(spriteSize, sourceSize, aSpriteResizeMode);
	User::LeaveIfError(iMainBmpDevice->Resize(spriteSize));
	User::LeaveIfError(iMaskBmpDevice->Resize(spriteSize));
	iMainFbsBitGc->Resized();
	iMaskFbsBitGc->Resized();
	iMaskFbsBitGc->SetBrushColor(KRgbBlack);
	iMaskFbsBitGc->Clear();
	const TRect translatedClipRect(iClippingRect.iTl - aSpritePos, iClippingRect.Size());
	if(!translatedClipRect.IsEmpty())
		iMaskFbsBitGc->SetClippingRect(translatedClipRect);
	TInternalSpriteResizeMode resizeMode = EHSameVSame;
	ComputeInternalResizeMode(resizeMode,aSpriteResizeMode,sourceSize,spriteSize);
	RenderSprite(aSpriteType,resizeMode,sourceSize,spriteSize);
	iMaskFbsBitGc->CancelClippingRect();
	iMainFbsBitGc->SetOrigin(-aSpritePos);
	}

/**
 * Brings the sprite onto the visible area of the screen.  Must also call this
 * if the sprite set member which is being used has changed.
 */
EXPORT_C void CSpriteSet::StartDisplayingSpriteL()
	{
	iSprite.SetPosition(iSpritePosition);
	User::LeaveIfError(iSprite.UpdateMember(0,iSpriteMember));
	iFlags |= ESpriteIsCurrentlyDisplayed;
	}

/**
 * Stops the display of the sprite on the visible area of the screen.
 */
EXPORT_C void CSpriteSet::StopDisplayingSprite()
	{
	if(iFlags&ESpriteIsCurrentlyDisplayed)
		{
		iFlags |= (~ESpriteIsCurrentlyDisplayed);
		iSprite.SetPosition(TPoint(KOffScreenValue,KOffScreenValue));
		}
	}

/**
 * Allows use of the Gc which the sprite uses for it's drawing.  This enables the client
 * to effectively draw onto the sprite.
 */
EXPORT_C CWindowGc* CSpriteSet::SpriteGc() const
	{
	__ASSERT_DEBUG(iWindowToBitmapMappingGc,Panic(EEgulPanicNullPointer));
	return iWindowToBitmapMappingGc;
	}

/**
 * Method for moving the postion of the sprite by aSpritePos from the current position.
 */
EXPORT_C void CSpriteSet::TranslateSpritePosition(const TPoint& aSpritePos)
	{
	if(iFlags&ESpriteIsCurrentlyDisplayed)
		{
		iSpritePosition += aSpritePos;
		iSprite.SetPosition(iSpritePosition);
		}
	}

/**
 * Bounds the drawing of the sprite within aRect, stopping it drawing over surrounding
 * components.
 */
EXPORT_C void CSpriteSet::SetClippingRect(const TRect& aRect)
	{
	iClippingRect = aRect;
	}

CSpriteSet::~CSpriteSet()
	{
	iSprite.Close();
	delete iMainFbsBitGc;
	delete iMaskFbsBitGc;
	delete iMainBmpDevice;
	delete iMaskBmpDevice;
	iSourceMembers.ResetAndDestroy();
	iSourceMembers.Close();
	delete iTargetBitmap;
	delete iTargetMaskBitmap;
	delete iWindowToBitmapMappingGc;
	}

CSpriteSet::CSpriteSet(TBool aInvertMask)
	: iFlags((aInvertMask&EMaskIsInverted) & (~ESpriteIsCurrentlyDisplayed))
	{
	}

void CSpriteSet::ConstructL(RWindowTreeNode& aWindow, RWsSession& aWs, CWsScreenDevice& aDevice)
	{
    TInt grayscaleCapabilities;
	TInt colorCapabilities;
	const TDisplayMode mode=aWs.GetDefModeMaxNumColors(colorCapabilities,grayscaleCapabilities);
	iTargetBitmap = new (ELeave) CWsBitmap(aWs);
	const TSize zeroSize(0,0);
	User::LeaveIfError(iTargetBitmap->Create(zeroSize,mode));
	iTargetMaskBitmap = new (ELeave) CWsBitmap(aWs);
	User::LeaveIfError(iTargetMaskBitmap->Create(zeroSize,mode));

	iSprite=RWsSprite(aWs);
	User::LeaveIfError(iSprite.Construct(aWindow, TPoint(KOffScreenValue,KOffScreenValue), ESpriteNoChildClip));
	CreateSpriteMember();
	iSprite.AppendMember(iSpriteMember);
	iSprite.Activate();
	iMainFbsBitGc=CFbsBitGc::NewL();	// for the main bitmap

	iWindowToBitmapMappingGc = CWindowToBitmapMappingGc::NewL(aDevice,*iMainFbsBitGc);	// takes place of iMainFbsBitGc (not passing ownership of context here !)
	iMaskFbsBitGc=CFbsBitGc::NewL();	// for the mask bitmap

	iMainBmpDevice=CFbsBitmapDevice::NewL(iTargetBitmap);
	iMaskBmpDevice=CFbsBitmapDevice::NewL(iTargetMaskBitmap);

	iMainFbsBitGc->Activate(iMainBmpDevice);
	iMaskFbsBitGc->Activate(iMaskBmpDevice);
	}

void CSpriteSet::CreateSpriteMember()
	{
	iSpriteMember.iBitmap=iTargetBitmap;
	iSpriteMember.iMaskBitmap=iTargetMaskBitmap;
	iSpriteMember.iInvertMask=iFlags&EMaskIsInverted;
	iSpriteMember.iInterval=0;
	iSpriteMember.iOffset=TPoint(0,0);
	}

void CSpriteSet::AdjustSpriteSizeAccordingToResizeMode(TSize& aTargetSize, const TSize& aSourceSize, TSpriteResizeMode aSpriteResizeMode) const
	{
	// following switch statement limits the 'other' dimension from the stretch line
	switch(aSpriteResizeMode)
		{
	case ENoResizing:
		{
		aTargetSize = aSourceSize;
		break;
		}
	case EResizeHorizToFit:
		{
		aTargetSize.iHeight = aSourceSize.iHeight;
		break;
		}
	case EResizeVertToFit:
		{
		aTargetSize.iWidth = aSourceSize.iWidth;
		break;
		}
	case EResizeHorizAndVertToFit:
		{
		break;
		}
	default:
		Panic(EEgulPanicInvalidSpriteResizeMode);
		break;
		}
	}

void CSpriteSet::ComputeInternalResizeMode(TInternalSpriteResizeMode& aInternalSpriteResizeMode, TSpriteResizeMode aSpriteResizeMode, const TSize& aSourceSize, const TSize& aSpriteSize) const
	{
	switch(aSpriteResizeMode)
		{
	case ENoResizing:
		{
		aInternalSpriteResizeMode = EHSameVSame;
		break;
		}
	case EResizeHorizToFit:
		{
		if(aSpriteSize.iWidth > aSourceSize.iWidth)
			aInternalSpriteResizeMode = EHStretchVSame;
		else if(aSpriteSize.iWidth < aSourceSize.iWidth)
			aInternalSpriteResizeMode = EHShrinkVSame;
		else
			aInternalSpriteResizeMode = EHSameVSame;
		break;
		}
	case EResizeVertToFit:
		{
		if(aSpriteSize.iHeight > aSourceSize.iHeight)
			aInternalSpriteResizeMode = EHSameVStretch;
		else if(aSpriteSize.iHeight < aSourceSize.iHeight)
			aInternalSpriteResizeMode = EHSameVShrink;
		else
			aInternalSpriteResizeMode = EHSameVSame;
		break;
		}
	case EResizeHorizAndVertToFit:
		{
		if(aSpriteSize.iWidth > aSourceSize.iWidth)
			{
			if(aSpriteSize.iHeight > aSourceSize.iHeight)
				aInternalSpriteResizeMode = EHStretchVStretch;
			else if(aSpriteSize.iHeight < aSourceSize.iHeight)
				aInternalSpriteResizeMode = EHStretchVShrink;
			else
				aInternalSpriteResizeMode = EHStretchVSame;
			}
		else if(aSpriteSize.iWidth < aSourceSize.iWidth)
			{
			if(aSpriteSize.iHeight > aSourceSize.iHeight)
				aInternalSpriteResizeMode = EHShrinkVStretch;
			else if(aSpriteSize.iHeight < aSourceSize.iHeight)
				aInternalSpriteResizeMode = EHShrinkVShrink;
			else
				aInternalSpriteResizeMode = EHShrinkVSame;
			}
		else
			{
			if(aSpriteSize.iHeight > aSourceSize.iHeight)
				aInternalSpriteResizeMode = EHSameVStretch;
			else if(aSpriteSize.iHeight < aSourceSize.iHeight)
				aInternalSpriteResizeMode = EHSameVShrink;
			else
				aInternalSpriteResizeMode = EHSameVSame;
			}

		break;
		}
	default:
		Panic(EEgulPanicInvalidSpriteResizeMode);
		break;
		}
	}

void CSpriteSet::RenderSprite(TInt aSpriteType, TInternalSpriteResizeMode aInternalSpriteResizeMode, const TSize& aSourceSize, const TSize& aSpriteSize)
	{
	const TInt sourceWidth = aSourceSize.iWidth;
	const TInt sourceHeight = aSourceSize.iHeight;
	const TInt spriteWidth = aSpriteSize.iWidth;
	const TInt spriteHeight = aSpriteSize.iHeight;
	const TInt numOfHorizAddedLines = spriteHeight-sourceHeight;
	const TInt numOfVertAddedLines = spriteWidth-sourceWidth;
	const TPoint posZeroZero(0,0);	// cached for repeated use
	CGulIcon* spriteSetMember = iSourceMembers[aSpriteType];
	CFbsBitmap* bitmapToUse = spriteSetMember->Bitmap();
	CFbsBitmap* maskToUse = spriteSetMember->Mask();
	TRect fromRect;
	TPoint toPoint;

	switch(aInternalSpriteResizeMode)
		{
	case EHSameVSame:
		{
		fromRect.SetRect(0,0,sourceWidth,sourceHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		break;
		}
	case EHSameVShrink:
		{
		const TInt halfSpriteHeight = spriteHeight/2;
		fromRect.SetRect(0,0,spriteWidth,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(0,sourceHeight - (halfSpriteHeight) - (spriteHeight%2),sourceWidth,sourceHeight);
		toPoint.SetXY(0,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		break;
		}
	case EHSameVStretch:
		{
		const TInt halfSourceHeight = sourceHeight/2;
		fromRect.SetRect(0,0,sourceWidth,halfSourceHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(0,halfSourceHeight,sourceWidth,sourceHeight);
		toPoint.SetXY(0,spriteHeight-(halfSourceHeight)-(sourceHeight%2));
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		for(TInt i = 0; i < numOfHorizAddedLines;i++)
			{
			fromRect.SetRect(0,halfSourceHeight,sourceWidth,(halfSourceHeight)+1);
			toPoint.SetXY(0,(halfSourceHeight)+i);
			iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
			iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
			}
		break;
		}
	case EHShrinkVSame:
		{
		const TInt halfSpriteWidth = spriteWidth/2;
		fromRect.SetRect(0,0,halfSpriteWidth,spriteHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSpriteWidth) - (spriteWidth%2),0,sourceWidth,sourceHeight);
		toPoint.SetXY(halfSpriteWidth,0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		break;
		}
	case EHShrinkVShrink:
		{
		const TInt halfSpriteWidth = spriteWidth/2;
		const TInt halfSpriteHeight = spriteHeight/2;
		const TInt spriteHeightModTwo = spriteHeight%2;
		const TInt spriteWidthModTwo = spriteWidth%2;
		fromRect.SetRect(0,0,halfSpriteWidth,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSpriteWidth) - (spriteWidthModTwo),0,sourceWidth,halfSpriteHeight);
		toPoint.SetXY(halfSpriteWidth,0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(0,sourceHeight - (halfSpriteHeight) - (spriteHeightModTwo),halfSpriteWidth,sourceHeight);
		toPoint.SetXY(0,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSpriteWidth) - (spriteWidthModTwo),sourceHeight - (halfSpriteHeight) - (spriteHeightModTwo),sourceWidth,sourceHeight);
		toPoint.SetXY(halfSpriteWidth,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		break;
		}
	case EHShrinkVStretch:
		{
		const TInt halfSourceHeight = sourceHeight/2;
		const TInt halfSpriteWidth = spriteWidth/2;
		const TInt sourceHeightModTwo = sourceHeight%2;
		const TInt spriteWidthModTwo = spriteWidth%2;
		fromRect.SetRect(0,0,halfSpriteWidth,halfSourceHeight);	
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSpriteWidth) - (spriteWidthModTwo),0,sourceWidth,halfSourceHeight);
		toPoint.SetXY(halfSpriteWidth,0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(0,sourceHeight - (halfSourceHeight) - (sourceHeightModTwo),halfSpriteWidth,sourceHeight);
		toPoint.SetXY(0,spriteHeight - (halfSourceHeight) - (sourceHeightModTwo));
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSpriteWidth) - (spriteWidthModTwo),sourceHeight - (halfSourceHeight) - (sourceHeightModTwo),sourceWidth,sourceHeight);
		toPoint.SetXY(halfSpriteWidth,spriteHeight - (halfSourceHeight) - (sourceHeightModTwo));
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		for(TInt j = 0; j < numOfHorizAddedLines;j++)
			{
			fromRect.SetRect(0,spriteHeight - (halfSourceHeight) - (sourceHeightModTwo),spriteWidth,spriteHeight - (halfSourceHeight) - (sourceHeightModTwo)+1);
			toPoint.SetXY(0,(halfSourceHeight)+j);
			iMainFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			iMaskFbsBitGc->BitBlt(toPoint,iTargetMaskBitmap,fromRect);
			}
		break;
		}
	case EHStretchVSame:
		{
		const TInt halfSourceWidth = sourceWidth/2;
		fromRect.SetRect(0,0,halfSourceWidth,sourceHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(halfSourceWidth,0,sourceWidth,sourceHeight);
		toPoint.SetXY(spriteWidth-(halfSourceWidth)-(sourceWidth%2),0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		for(TInt i = 0; i < numOfVertAddedLines;i++)
			{
			fromRect.SetRect(halfSourceWidth,0,(halfSourceWidth)+1,sourceHeight);
			toPoint.SetXY((halfSourceWidth)+i,0);
			iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
			iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
			}
		break;
		}
	case EHStretchVShrink:
		{
		const TInt halfSourceWidth = sourceWidth/2;
		const TInt halfSpriteHeight = spriteHeight/2;
		const TInt sourceWidthModTwo = sourceWidth%2;
		const TInt spriteHeightModTwo = spriteHeight%2;
		fromRect.SetRect(0,0,halfSourceWidth,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSourceWidth) - (sourceWidthModTwo),0,sourceWidth,halfSpriteHeight);
		toPoint.SetXY(spriteWidth - (halfSourceWidth) - (sourceWidthModTwo),0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(0,sourceHeight - (halfSpriteHeight) - (spriteHeightModTwo),halfSourceWidth,sourceHeight);
		toPoint.SetXY(0,halfSpriteHeight);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(sourceWidth - (halfSourceWidth) - (sourceWidthModTwo),sourceHeight - (halfSpriteHeight) - (spriteHeightModTwo),sourceWidth,sourceHeight);
		toPoint.SetXY(spriteWidth - (halfSourceWidth) - (sourceWidthModTwo),halfSpriteHeight);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		for(TInt j = 0; j < numOfVertAddedLines;j++)
			{
			fromRect.SetRect(spriteWidth - (halfSourceWidth) - (sourceWidthModTwo),0,spriteWidth - (halfSourceWidth) - (sourceWidthModTwo)+1,spriteHeight);
			toPoint.SetXY((halfSourceWidth)+j,0);
			iMainFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			iMaskFbsBitGc->BitBlt(toPoint,iTargetMaskBitmap,fromRect);
			}
		break;
		}
	case EHStretchVStretch:
		{
		const TInt halfSourceWidth = sourceWidth/2;
		const TInt halfSourceHeight = sourceHeight/2;
		const TInt sourceWidthModTwo = sourceWidth%2;
		const TInt sourceHeightModTwo = sourceHeight%2;
		fromRect.SetRect(0,0,halfSourceWidth,halfSourceHeight);
		iMaskFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		iMainFbsBitGc->BitBlt(posZeroZero,maskToUse,fromRect);
		fromRect.SetRect(0,halfSourceHeight,halfSourceWidth,sourceHeight);
		toPoint.SetXY(0,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo));
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		iMainFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(halfSourceWidth,0,sourceWidth,halfSourceHeight);
		toPoint.SetXY(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),0);
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		iMainFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		fromRect.SetRect(halfSourceWidth,halfSourceHeight,sourceWidth,sourceHeight);
		toPoint.SetXY(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),spriteHeight-(halfSourceHeight)-(sourceHeightModTwo));
		iMaskFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		iMainFbsBitGc->BitBlt(toPoint,maskToUse,fromRect);
		for(TInt h = 0; h < numOfVertAddedLines;h++)
			{
			fromRect.SetRect(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),0,spriteWidth-(halfSourceWidth)-(sourceWidthModTwo)+1,spriteHeight);
			toPoint.SetXY((halfSourceWidth)+h,0);
			iMainFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			iMaskFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			}
		for(TInt m = 0; m < numOfHorizAddedLines;m++)
			{
			fromRect.SetRect(0,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo),spriteWidth,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo)+1);
			toPoint.SetXY(0,(halfSourceHeight)+m);
			iMaskFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			}
		fromRect.SetRect(0,0,halfSourceWidth,halfSourceHeight);
		iMainFbsBitGc->BitBlt(posZeroZero,bitmapToUse,fromRect);
		fromRect.SetRect(0,halfSourceHeight,halfSourceWidth,sourceHeight);
		toPoint.SetXY(0,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo));
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		fromRect.SetRect(halfSourceWidth,0,sourceWidth,halfSourceHeight);
		toPoint.SetXY(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),0);
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		fromRect.SetRect(halfSourceWidth,halfSourceHeight,sourceWidth,sourceHeight);
		toPoint.SetXY(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),spriteHeight-(halfSourceHeight)-(sourceHeightModTwo));
		iMainFbsBitGc->BitBlt(toPoint,bitmapToUse,fromRect);
		for(TInt j = 0; j < numOfVertAddedLines;j++)
			{
			fromRect.SetRect(spriteWidth-(halfSourceWidth)-(sourceWidthModTwo),0,spriteWidth-(halfSourceWidth)-(sourceWidthModTwo)+1,spriteHeight);
			toPoint.SetXY((halfSourceWidth)+j,0);
			iMainFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			}
		for(TInt i = 0; i < numOfHorizAddedLines;i++)
			{
			fromRect.SetRect(0,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo),spriteWidth,spriteHeight-(halfSourceHeight)-(sourceHeightModTwo)+1);
			toPoint.SetXY(0,(halfSourceHeight)+i);
			iMainFbsBitGc->BitBlt(toPoint,iTargetBitmap,fromRect);
			}
		break;
		}
	default:
		Panic(EEgulPanicInvalidInternalSpriteResizeMode);
		break;
		}
	}
