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

#include <barsread.h>
#include <gulfont.hrh>
#include <gulfont.h>
#include <gulutil.h>

//
// class TLogicalFont
//

EXPORT_C TLogicalFont::TLogicalFont()
	: iFontId(KNullUid), iCategory(TLogicalFont::EView), iStyle(TLogicalFont::ENormal)
/** The default constructor. 

This initialises iFontId to KNullUid, iCategory to EView, iStyle to ENormal 
and iZoomFactor to a default zoom factor. */
	{
	iZoomFactor=TZoomFactor();
	}

EXPORT_C TLogicalFont::TLogicalFont(TUid aId)
	: iFontId(aId), iCategory(TLogicalFont::EView), iStyle(TLogicalFont::ENormal)
/** Constructor with a logical font ID.

The other member data is initialised as for the default constructor.

@param aId The logical font ID. */
	{
	iZoomFactor=TZoomFactor();
	}

EXPORT_C TLogicalFont::TLogicalFont(TFontCategory aCategory,TFontStyle aStyle,const TZoomFactor& aZoomFactor)
	: iFontId(KNullUid), iCategory(aCategory), iStyle(aStyle), iZoomFactor(aZoomFactor)
/** Constructor with a logical font category, style and zoom factor.

iFontId is initialised to KNullUid.

@param aCategory The logical font category.
@param aStyle The font style.
@param aZoomFactor The zoom factor. */
	{}

EXPORT_C TLogicalFont::TLogicalFont(TUid aId,TLogicalFont::TFontCategory aCategory,
										TLogicalFont::TFontStyle aStyle,const TZoomFactor& aZoomFactor)
	: iFontId(aId), iCategory(aCategory), iStyle(aStyle), iZoomFactor(aZoomFactor)
/** Constructs a logical font, specifying its logical font ID, logical font category, 
style and zoom factor.

@param aId The logical font ID.
@param aCategory The logical font category.
@param aStyle The font style.
@param aZoomFactor The zoom factor. */
	{}

//
// class CCleanupStackableFont
//

EXPORT_C CCleanupStackableFont* CCleanupStackableFont::NewByNameL(TResourceReader& aReader,CWsScreenDevice& aScreenDevice)
/** Allocates and constructs a new CCleanupStackableFont. 

aReader should be initialised to read a resource of type NAMED_FONT.

@param aReader The resource reader to use.
@param aScreenDevice The screen device.
@return Pointer to the CCleanupStackableFont object. */
	{
	CCleanupStackableFont* font=NewLC(EFalse, aReader, aScreenDevice); // also pushes on to CleanupStack
	CleanupStack::Pop();
	return font;
	}

EXPORT_C CCleanupStackableFont* CCleanupStackableFont::NewByNameLC(TResourceReader& aReader,CWsScreenDevice& aScreenDevice)
/** Allocates and constructs a new CCleanupStackableFont, leaving it on the cleanup 
stack. 

aReader should be initialised to read a resource of type NAMED_FONT.

@param aReader The resource reader to use.
@param aScreenDevice The screen device.
@return Pointer to the CCleanupStackableFont object. */
	{
	return CCleanupStackableFont::NewLC(EFalse, aReader, aScreenDevice);
	}

EXPORT_C CCleanupStackableFont* CCleanupStackableFont::NewL(TResourceReader& aReader,CWsScreenDevice& aScreenDevice)
/** Allocates and constructs a new CCleanupStackableFont. 

aReader should be initialised to read a resource of type FONT.

@param aReader The resource reader to use.
@param aScreenDevice The screen device.
@return The CCleanupStackableFont object. */
	{
	CCleanupStackableFont* font=NewLC(ETrue, aReader, aScreenDevice); // also pushes on to CleanupStack
	CleanupStack::Pop();
	return font;
	}

EXPORT_C CCleanupStackableFont* CCleanupStackableFont::NewLC(TResourceReader& aReader,CWsScreenDevice& aScreenDevice)
/** Allocates and constructs a new CCleanupStackableFont, leaving it on the cleanup 
stack. 

aReader should be initialised to read a resource of type FONT. 

@param aReader The resource reader to use.
@param aScreenDevice The screen device.
@return Pointer to the CCleanupStackableFont object. */
	{
	return CCleanupStackableFont::NewLC(ETrue, aReader, aScreenDevice);
	}

EXPORT_C CCleanupStackableFont::~CCleanupStackableFont()
/** Destructor.

This releases the font. The font is only deleted if its access count is zero 
(so that no client is using it). */
	{
	iScreenDevice.ReleaseFont(iFont); // N.B. do not do "delete iFont"
	}

EXPORT_C CFbsFont& CCleanupStackableFont::Font() const
/** Gets the font stored in this object.

The caller does not take ownership.

@return The font. */
	{
	return *iFont;
	}

EXPORT_C CFbsFont* CCleanupStackableFont::TakeOwnershipOfFont()
/** Gets the font stored in this object.

The caller takes ownership of the returned font.

@return The font. */
	{
	CFbsFont* font=iFont;
	iFont=NULL;
	return font;
	}

CCleanupStackableFont::CCleanupStackableFont(CWsScreenDevice& aScreenDevice)
	:iScreenDevice(aScreenDevice)
	{
	__DECLARE_NAME(_S("CCleanupStackableFont"));
	}

CCleanupStackableFont* CCleanupStackableFont::NewLC(TBool aByUid,TResourceReader& aReader, CWsScreenDevice& aScreenDevice)
	{ //static	
	CCleanupStackableFont* font=new(ELeave) CCleanupStackableFont(aScreenDevice);
	CleanupStack::PushL(font);
	if(aByUid)
		font->iFont=ResourceUtils::CreateScreenFontL(aReader,aScreenDevice);
	else
		font->iFont=ResourceUtils::CreateNamedScreenFontInPixelsL(aReader,aScreenDevice);
	return font;
	}
