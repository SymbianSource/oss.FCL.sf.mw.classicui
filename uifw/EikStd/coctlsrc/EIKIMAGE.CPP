/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#include <fbs.h>
#include <coeutils.h>
#include <eikimage.h>
#include <eikenv.h>
#include <barsread.h>
#include "lafimage.h"
#include <AknIconUtils.h>

const TInt KFullEmphasis			= 0x01;
const TInt KPictureOwnedExternally	= 0x10;
const TInt KSameBitmapAndMask		= 0x20;
const TInt KBrushStyleSet			= 0x40;

EXPORT_C CEikImage::~CEikImage()
	{
    if (!(iImFlags&KPictureOwnedExternally))
		{
    	delete CONST_CAST(CFbsBitmap*,iBitmap);		
		if (~iImFlags&KSameBitmapAndMask)
			delete CONST_CAST(CFbsBitmap*,iMaskBitmap);
		}
	}

EXPORT_C CEikImage::CEikImage()
	{
	__DECLARE_NAME(_S("CEikImage"));
	}

EXPORT_C void CEikImage::CreatePictureFromFileL(
    const TDesC& aFilename,TInt aMainId,TInt aMaskId)
    {
    iImFlags&=~KSameBitmapAndMask;
    if (aMaskId>=0)
        {
        AknIconUtils::CreateIconL(
            const_cast<CFbsBitmap*&>(iBitmap),
            const_cast<CFbsBitmap*&>(iMaskBitmap),
            aFilename, aMainId, aMaskId);
        }
    else
        {
        iBitmap = AknIconUtils::CreateIconL(aFilename, aMainId);
        }
    }

//
EXPORT_C const CFbsBitmap* CEikImage::Bitmap() const
	{
	return iBitmap;
	}
//
EXPORT_C const CFbsBitmap* CEikImage::Mask() const
	{
	return iMaskBitmap;
	}
//
EXPORT_C void CEikImage::SetBitmap(const CFbsBitmap* aBitmap)
	{
	iBitmap = aBitmap;
	}
//
EXPORT_C void CEikImage::SetMask(const CFbsBitmap* aMaskBitmap)
	{
	iMaskBitmap = aMaskBitmap;
	}

/**
 * @internal
 * @deprecated
 */
EXPORT_C void CEikImage::SetNewBitmaps(const CFbsBitmap* aNewBitmap,const CFbsBitmap* aNewMask)
	{
	SetPicture(aNewBitmap,aNewMask);
	}

EXPORT_C void CEikImage::SetPicture(const CFbsBitmap* aBitmap,const CFbsBitmap* aMaskBitmap)
	{
	if (!(iImFlags&KPictureOwnedExternally))
		{
    	delete CONST_CAST(CFbsBitmap*,iBitmap);
		if (iMaskBitmap && !(iImFlags&KSameBitmapAndMask))
			delete CONST_CAST(CFbsBitmap*,iMaskBitmap);
		}
	iMaskBitmap=NULL;
	iImFlags&=~KSameBitmapAndMask;
	if (aMaskBitmap)
		{
		iMaskBitmap=aMaskBitmap;
		if (aBitmap==aMaskBitmap)
			iImFlags|=KSameBitmapAndMask;
		}
	iBitmap=aBitmap;
	}

EXPORT_C void CEikImage::Draw(const TRect& aRect) const
	{
	CWindowGc& gc=SystemGc();
	if (iImFlags & KBrushStyleSet)
		gc.SetBrushStyle(iBrushStyle);
#ifdef __SERIES60_30__
    gc.SetOpaque( ETrue ); // transparency off
#endif // __SERIES60_30__
    if (iBitmap)
        {
        LafImage::Draw(iEikonEnv->LafEnv(),*this,gc,aRect,iMargin,iAlignment,*iBitmap,iMaskBitmap,iImFlags&KFullEmphasis);
        }
#ifdef __SERIES60_30__
    gc.SetOpaque( EFalse ); // transparency back on
#endif // __SERIES60_30__
    }

EXPORT_C TSize CEikImage::MinimumSize()
	{
	TSize size(0,0);
    if (iBitmap)
        {
        size = iBitmap->SizeInPixels();
        }
	size += iMargin.SizeDelta();
	return size;
	}

EXPORT_C void CEikImage::SetEmphasis(TBool aEmphasis)
	{
	iImFlags&=~KFullEmphasis;
	if (aEmphasis)
		iImFlags|=KFullEmphasis;
	}

EXPORT_C void CEikImage::SetPictureOwnedExternally(TBool aOwnership)
	{
	if (aOwnership)
		iImFlags|=KPictureOwnedExternally;
	else
		iImFlags&=~KPictureOwnedExternally;
	}
//
EXPORT_C TBool CEikImage::IsPictureOwnedExternally()
	{
    if (iImFlags&KPictureOwnedExternally)
		return ETrue;
	else
		return EFalse;
	}

EXPORT_C void CEikImage::ConstructFromResourceL(TResourceReader& aReader)
	{
	iAlignment.SetHAlignment((TGulHAlignment)aReader.ReadInt16());
	iAlignment.SetVAlignment((TGulVAlignment)aReader.ReadInt16());
	const TPtrC bmpFile=aReader.ReadTPtrC();
	const TInt bmpId=aReader.ReadInt16();
	const TInt bmpMask=aReader.ReadInt16();
	CreatePictureFromFileL(bmpFile,bmpId,bmpMask);
	aReader.ReadInt32(); // extension link
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikImage::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikImage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KLitEikImgCtlStart, "<CEikImage>");
	_LIT(KLitEikImgCtlEnd, "<\\CEikImage>");
	_LIT(KLitEikImgBmp,"<iBitmap>");
	_LIT(KLitEikImgBmpEnd,"<\\iBitmap>");
	_LIT(KLitEikImgMskBmp,"<iMaskBitmap>");
	_LIT(KLitEikImgMskBmpEnd,"<\\iMaskBitmap>");
	_LIT(KLitEikImgFlgs,"<iImFlags>");
	_LIT(KLitEikImgFlgsEnd,"<\\iImFlags>");

	aWriteStream << KLitEikImgCtlStart;
	aWriteStream << KLitEikImgBmp;
	if(iBitmap)
		aWriteStream << *iBitmap;
	aWriteStream << KLitEikImgBmpEnd;
	aWriteStream << KLitEikImgMskBmp;
	if(iMaskBitmap)
		aWriteStream << *iMaskBitmap;
	aWriteStream << KLitEikImgMskBmpEnd;
	aWriteStream << KLitEikImgFlgs;
	aWriteStream.WriteInt32L(iImFlags);
	aWriteStream << KLitEikImgFlgsEnd;
	CEikAlignedControl::WriteInternalStateL(aWriteStream);
	aWriteStream << KLitEikImgCtlEnd;
	}
#endif

EXPORT_C void CEikImage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikAlignedControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikImage::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikImage::Reserved_2()
	{}

EXPORT_C void CEikImage::SetBrushStyle(CGraphicsContext::TBrushStyle aBrushStyle)
	{
	iImFlags |= KBrushStyleSet;
	iBrushStyle=aBrushStyle;
	};
