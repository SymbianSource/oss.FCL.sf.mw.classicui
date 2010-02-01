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

#if !defined(__GULFONT_H__)
#define __GULFONT_H__

#include <gdi.h>
#include <w32std.h>

class TResourceReader;

class TLogicalFont
/** Packages the attributes of a logical font.

These attributes include a UID (iFontId) and a category (iCategory), either 
of which can be used to identify a required system font. The possible values 
for the UID are defined in the UI variant's look and feel layer, so are not 
the same as the UID values that may be used to create a physical font.

An object of this class can be passed by any application to CEikonEnv::Font(), 
to return the closest matching system font (a CFont-derived object). 

@publishedAll 
@released */
	{
public:
	/** Logical font categories.
	
	The font category specifies the type of font that is required. It can be specified 
	as an alternative to the logical font UID. The physical fonts associated with 
	these categories are specified in the LAF layer, so are UI variant-specific. */
	enum TFontCategory
		{
		/** The normal system font. */
		EView,
		/** The font used in buttons. */
		EButton,
		/** The font used for annotations. This is smaller than the normal font. 
		For instance, it is used to draw the page number in some applications. */
		EAnnotation,
		/** The font used for titles. */
		ETitle
		};
	/** Font styles. */
	enum TFontStyle
		{
		/** Normal style. */
		ENormal,
		/** Bold. */
		EBold,
		/** Italics. */
		EItalic,
		/** Bold and italics. */
		EBoldItalic,
		/** Superscript. */
		ESuperscript,
		/** Subscript. */
		ESubscript,
		/** Light. This is the opposite of bold, i.e. a smaller than normal pen size is 
		used to draw it. */
		ELight,
		/** Custom font. */
		ECustom
		};
public:
	IMPORT_C TLogicalFont();
	IMPORT_C TLogicalFont(TUid aId);
	IMPORT_C TLogicalFont(TFontCategory aCategory,TFontStyle aStyle,const TZoomFactor& aZoomFactor);
	IMPORT_C TLogicalFont(TUid aId,TFontCategory aCategory,TFontStyle aStyle,const TZoomFactor& aZoomFactor);
public:
	/** The logical font ID. */
	TUid iFontId;
	/** The logical font category. */
	TFontCategory iCategory;
	/** The font style. */
	TFontStyle iStyle;
	/** The zoom factor. */
	TZoomFactor iZoomFactor;
	};


class CCleanupStackableFont : public CBase
/** Wraps a font (CFbsFont) object that can be pushed onto the cleanup stack.

By default, the cleanup stack only handles CBase-derived classes, and untyped 
(TAny*) objects that can be cleaned up by a simple memory free call. Fonts 
must also be released, which this class handles automatically in its destructor.

The font is initialised from a resource file, and can be identified by name 
or UID.

@publishedAll 
@released 
@see CFbsFont */
	{
public:
	IMPORT_C static CCleanupStackableFont* NewL(TResourceReader& aReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CCleanupStackableFont* NewLC(TResourceReader& aReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CCleanupStackableFont* NewByNameL(TResourceReader& aReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CCleanupStackableFont* NewByNameLC(TResourceReader& aReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C virtual ~CCleanupStackableFont();
public:
	IMPORT_C CFbsFont& Font() const;
	IMPORT_C CFbsFont* TakeOwnershipOfFont();
private:
	CCleanupStackableFont(CWsScreenDevice& aScreenDevice);
	static CCleanupStackableFont* NewLC(TBool aByUid,TResourceReader& aReader, CWsScreenDevice& aScreenDevice);
private:
	CWsScreenDevice& iScreenDevice;
	CFbsFont* iFont;
	};

#endif
