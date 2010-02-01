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

#include <gdi.h>
#include <gulicon.h>
#include <fbs.h>
#include "GULSTD.H"

CGulIcon::CGulIcon()
	: iBitmapsOwnedExternally(EFalse)
	{
	}

EXPORT_C CGulIcon::~CGulIcon()
/** Destructor. */
	{
	if(!iBitmapsOwnedExternally)
		{
		if(iMask!=iBitmap)
			delete iMask;

		delete iBitmap;
		}
	}

EXPORT_C CGulIcon* CGulIcon::NewLC()
/** Creates a new icon and leaves it on the cleanup stack.

@return The new icon. */
	{
	CGulIcon* self=new(ELeave) CGulIcon;
	CleanupStack::PushL(self);
	return self;
	}


EXPORT_C CGulIcon* CGulIcon::NewL(CFbsBitmap* aBitmap,CFbsBitmap* aMask)
/** Creates a new icon using the bitmap and mask.

It takes ownership of the bitmap and mask and returns a pointer to the new object.

@param aBitmap The icon bitmap.
@param aMask The icon mask.
@return The new icon. */
	{
	__ASSERT_DEBUG(aBitmap,Panic(EEgulPanicNullPointer));

	CGulIcon* self=NewLC();
	self->SetBitmap(aBitmap);
	self->SetMask(aMask);
	CleanupStack::Pop();	// self
	return self;
	}

EXPORT_C CGulIcon* CGulIcon::NewL()
/** Creates a new icon.

@return The new icon. */
	{
	CGulIcon* self=NewLC();
	CleanupStack::Pop();	// self
	return self;
	}

EXPORT_C void CGulIcon::SetBitmap(CFbsBitmap* aBitmap)
/** Sets the icon image's bitmap.

Transfers ownership to this object unless bitmaps are set to be owned externally.

@param aBitmap Pointer to the icon image's bitmap. */
	{
	__ASSERT_DEBUG(aBitmap,Panic(EEgulPanicNullPointer));

	if(!iBitmapsOwnedExternally && iBitmap!=iMask)
		delete iBitmap;

	iBitmap=aBitmap;
	}

EXPORT_C CFbsBitmap* CGulIcon::Bitmap() const
/** Gets the icon image's bitmap.

Does not normally imply transfer of ownership. Ownership can be transferred if bitmaps 
are set to be owned externally.

@return Pointer to the icon image's bitmap. */
	{
	return iBitmap;
	}

EXPORT_C void CGulIcon::SetMask(CFbsBitmap* aMask)
/** Sets the icon image's mask.

Ownership is transferred to this object unless the bitmaps are owned externally.

The mask can be set to be identical to the bitmap if the bitmap is self-masking.

@param aMask Pointer to the icon image's mask. */
	{
	if(!iBitmapsOwnedExternally && iBitmap!=iMask)
		delete iMask;

	iMask=aMask;
	}

EXPORT_C CFbsBitmap* CGulIcon::Mask() const
/** Gets the icon image's mask.

Transfers ownership to the caller if bitmaps are owned externally.

@return Pointer to the icon image's mask. */
	{
	return iMask;
	}

EXPORT_C void CGulIcon::SetBitmapsOwnedExternally(TBool aOwnedExternally)
/** Sets the bitmap and mask to be owned externally.

@param aOwnedExternally ETrue if bitmaps are set as externally owned. EFalse 
if bitmaps are set as not being externally owned. */
	{
	iBitmapsOwnedExternally=aOwnedExternally;
	}

EXPORT_C TBool CGulIcon::BitmapsOwnedExternally() const
/** Gets the icon bitmap ownership. 

@return ETrue if bitmaps are externally owned. EFalse if bitmaps are 
owned by this object. */
	{
	return iBitmapsOwnedExternally;
	}

