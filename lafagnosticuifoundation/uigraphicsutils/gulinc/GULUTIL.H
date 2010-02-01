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

#if !defined(__GULUTIL_H__)
#define __GULUTIL_H__

#include <e32std.h>
#include <badesca.h>
#include <gdi.h>
#include <gulbordr.h>
#include <gulftflg.hrh>

/** 
@publishedAll 
@released 
*/
const TUint KTextUtilClipEndChar=0x2026;

/**
@publishedAll 
@released 
*/
const TUint KColumnListSeparator='\t';

class CFont;
class CFbsFont;
class CWsScreenDevice;
class TResourceReader;
class CColorArray;
class CGraphicsDevice;
class RWsSession;
class CColorList;
template <class T> class CArrayFix;


class TMargins8
/** A set of margins stored as 8 bit integer values which can represent 
either pixels or twips between -128 and +127.

@publishedAll 
@released */
	{
public :
	/** Left margin in twips or pixels. */
	TInt8 iLeft;
	/** Right margin in twips or pixels. */
	TInt8 iRight;
	/** Top margin in twips or pixels. */
	TInt8 iTop;
	/** Bottom margin in twips or pixels. */
	TInt8 iBottom;
public :
	IMPORT_C TMargins8();
	IMPORT_C TMargins8(TInt8 aLeft, TInt8 aTop, TInt8 aRight, TInt8 aBottom);
	IMPORT_C void SetAllValuesTo(TInt aCommonValue);
    IMPORT_C TRect InnerRect(const TRect& aOuterRect) const;
    IMPORT_C TRect OuterRect(const TRect& aInnerRect) const;
	IMPORT_C TSize SizeDelta() const;
	};


class DrawUtils
/** Provides static functions for drawing text in a rectangle. 

@publishedAll 
@released */
	{
public:
	IMPORT_C static void DrawText(CGraphicsContext& aGc,const TDesC& aString,const TRect& aBox,TInt aBaseLineOffset,
									CGraphicsContext::TTextAlign aHoriz,TInt aMargin,const CFont* aFont);
    IMPORT_C static void DrawBetweenRects(CGraphicsContext& aGc,const TRect& aOuterRect,const TRect& aInnerRect);
    IMPORT_C static void ClearBetweenRects(CGraphicsContext& aGc,const TRect& aOuterRect,const TRect& aInnerRect);
	};


class TextUtils
/** Provides static functions for truncating and aligning text strings. 

@publishedAll 
@released */
	{
public:
	IMPORT_C static void ClipToFit(TDes& aBuffer,const CFont& aFont,TInt aMaxWidthInPixels,TChar aAlternativeEnd=KTextUtilClipEndChar);
	IMPORT_C static TInt ColumnText(TPtrC& aColumnText,TInt aColumn,const TDesC* aSourceText,TChar aColumnSeparator=KColumnListSeparator);
	IMPORT_C static void TruncateToNumChars(TDes& aBuffer, TInt numChars);
	};

class FontUtils
/** Provides static functions for getting information about the fonts supported by a graphics 
device. 

@publishedAll 
@released */
	{
public:
	IMPORT_C static void GetAvailableFontsL(const CGraphicsDevice& aDevice,CDesCArray& aFontNameList,
											TInt aFonts=EGulNoSymbolFonts);
	IMPORT_C static TInt TypefaceAttributes(const CGraphicsDevice& aDevice,const TDesC& aTypefaceName);
	IMPORT_C static TInt GetAvailableHeightsInTwipsL(const CGraphicsDevice& aDevice,const TDesC& aTypefaceName,
													CArrayFix<TInt>& aHeightList);
	IMPORT_C static TInt GetAvailableHeightsInTwipsAndPointsL(const CGraphicsDevice& aDevice,const TDesC& aTypefaceName,
															CArrayFix<TInt>& aTwipsList,CDesCArray& aPointsList);
	IMPORT_C static TInt PointsFromTwips(TInt aTwips);
	IMPORT_C static TInt TwipsFromPoints(TInt aPoints);
	IMPORT_C static TInt TwipsFromPoints(const TDesC& aPoints);
	IMPORT_C static TInt IndexOfNearestHeight(CArrayFix<TInt>& aTwipsList,TInt aHeight);
	};


class ResourceUtils
/** Provides static functions for resource reading.

All functions use pre-initialised resource reader objects to read information 
from resource files.

@publishedAll 
@released 
@see CCoeEnv::CreateResourceReaderLC() */
	{
public:
	IMPORT_C static CFbsFont* CreateNamedScreenFontL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CFbsFont* CreateNamedScreenFontInPixelsL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CFbsFont* CreateScreenFontL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice);
	inline static TInt8 ReadTInt8L(TResourceReader& aReader);
	inline static TInt16 ReadTInt16L(TResourceReader& aReader);
	inline static TInt32 ReadTInt32L(TResourceReader& aReader);
	IMPORT_C static void PopulateColorArrayL(CColorArray& aColors,TResourceReader& aReader);
private:
	enum TResourceTypeInt { EResourceInt8,EResourceInt16,EResourceInt32 };
private:
	IMPORT_C static TInt32 ReadResourceIntL(TResourceReader& aReader,TResourceTypeInt aSize);
	};

class ColorUtils
/** Provides static functions for manipulating colours.

@publishedAll 
@released 
@see TDisplayMode */
	{
public:
	/** The orientation of a bitmap. */
    enum TBitmapOrientation
	    {
		/** The bitmap is vertical. */
	    EBitmapOrientationVertical,
		/** The bitmap is horizontal. */
	    EBitmapOrientationHorizontal
	    };
public:
	IMPORT_C static TRgb ColorAdjust(TRgb aColor,TInt aPercentage);
    IMPORT_C static void CreateGradientBitmapL(CFbsBitmap& aBitmap, const RWsSession& aWs, TInt aBreadth,
                                       TBitmapOrientation aOrientation, TRgb aStartColor, TRgb aEndColor);
	IMPORT_C static CColorList* CreateSystemColorListL(RFs& aFs);
	IMPORT_C static CColorList* CreateSystemColorListL(RFs& aFs,const CColorList& aColorList);
	IMPORT_C static void UpdateSystemColorListL(RFs& aFs,CColorList& aColorList);
	IMPORT_C static void GetRgbDerivedBorderColors(TGulBorder::TColors& aBorderColors,TRgb aBackgroundColor,TDisplayMode aMode);
	IMPORT_C static TRgb RgbDarkerColor(TRgb aRgb,TDisplayMode aMode);
	IMPORT_C static TRgb RgbMidDarkerColor(TRgb aRgb,TDisplayMode aMode);
	IMPORT_C static TRgb RgbLighterColor(TRgb aRgb,TDisplayMode aMode);
	};


class TFindWidthOfWidestTextItem
/** Finds the width in pixels of the widest item in a range of indexed text items.

This is the base class for several classes used to get the maximum width for 
date and time components.

Derived classes should override the pure virtual methods to supply an appropriate 
range of items. 

@publishedAll 
@released */
	{
protected:
	/** Default constructor. */
	inline TFindWidthOfWidestTextItem() {}
public:
	IMPORT_C TInt MaximumWidthInPixels(const CFont& aFont) const;
private:
	/** Gets the first and last index in the range of items.
	
	@param aFirstIndex On return, the first index.
	@param aLastIndex On return, the last index. 
	@publishedAll
	@released */
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const=0;
	/** Gets the text item at the specfied index.
	
	@param aText On return, the indexed text item.
	@param aIndex The index. 
	@publishedAll 
	@released */
	virtual void GetTextItem(TDes& aText, TInt aIndex) const=0;
	};


class TFindWidthOfWidestDigit : public TFindWidthOfWidestTextItem
/** Finds the width in pixels of the widest digit, when displayed in a specified 
font.

After construction, call MaximumWidthInPixels(), defined in the base class, 
specifying the font. 

@publishedAll
@released */
	{
public:
	IMPORT_C TFindWidthOfWidestDigit();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

class TFindWidthOfWidestDigitType : public TFindWidthOfWidestTextItem
/**
@publishedAll
@released
*/
	{
public:
	IMPORT_C TFindWidthOfWidestDigitType(TDigitType aDigitType);
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;

private:
	TDigitType iDigitType;
	};

class TFindWidthOfWidestAmPmName : public TFindWidthOfWidestTextItem
/** Finds the width in pixels of the widest Am or Pm text, when displayed in a specified 
font.

After construction, call MaximumWidthInPixels(), defined in the base class, 
specifying the font.

@publishedAll
@released 
@see TAmPmName */
	{
public:
	IMPORT_C TFindWidthOfWidestAmPmName();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

class TFindWidthOfWidestAbbreviatedDayName : public TFindWidthOfWidestTextItem
/** Finds the width in pixels of the widest abbreviated day name (for instance Mon, Tue) 
when displayed in a specified font.

After construction, call MaximumWidthInPixels(), defined in the base class, 
specifying the font.

@publishedAll
@released 
@see TDayNameAbb */
	{
public:
	IMPORT_C TFindWidthOfWidestAbbreviatedDayName();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};


class TFindWidthOfWidestDayName : public TFindWidthOfWidestTextItem
/** Finds the width in pixels of the widest day name, when displayed in a specified 
font.

After construction, call MaximumWidthInPixels(), defined in the base class, 
specifying the font. 

@publishedAll 
@released */
	{
public:
	IMPORT_C TFindWidthOfWidestDayName();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};


class TFindWidthOfWidestAbbreviatedMonthName : public TFindWidthOfWidestTextItem
/** Finds the width in pixels of the widest abbreviated month name (for instance Jan, Feb), 
when displayed in a specified font.

After construction, call MaximumWidthInPixels(), defined in the base class, 
specifying the font. 

@publishedAll 
@released */
	{
public:
	IMPORT_C TFindWidthOfWidestAbbreviatedMonthName();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

class TFindWidthOfWidestMonthName : public TFindWidthOfWidestTextItem
/** Finds the width in pixels of the widest month name, when displayed in a specified 
font.

After construction, call MaximumWidthInPixels(), defined in the base class, 
specifying the font. 

@publishedAll 
@released */
	{
public:
	IMPORT_C TFindWidthOfWidestMonthName();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

class TFindWidthOfWidestDateSuffix : public TFindWidthOfWidestTextItem
/** Finds the width in pixels of the widest date suffix (for instance st, nd), 
when displayed in a specified font.

After construction, call MaximumWidthInPixels(), defined in the base class, 
specifying the font. 

@publishedAll 
@released */
	{
public:
	IMPORT_C TFindWidthOfWidestDateSuffix();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

//	class ResourceUtils
inline TInt8 ResourceUtils::ReadTInt8L(TResourceReader& aReader)
/** Reads an 8 bit signed integer from a resource.

@param aReader Resource reader to use to read the integer.
@return The 8 bit signed integer. */
	{ return((TInt8)ReadResourceIntL(aReader,EResourceInt8)); }
inline TInt16 ResourceUtils::ReadTInt16L(TResourceReader& aReader)
/** Reads a 16 bit signed integer from a resource.

@param aReader Resource reader to use to read the integer.
@return The 16 bit signed integer. */
	{ return((TInt16)ReadResourceIntL(aReader,EResourceInt16)); }
inline TInt32 ResourceUtils::ReadTInt32L(TResourceReader& aReader)
/** Reads a 32 bit signed integer from a resource.

@param aReader Resource reader to use to read the integer.
@return The 32 bit signed integer. */
	{ return((TInt32)ReadResourceIntL(aReader,EResourceInt32)); }

#endif

