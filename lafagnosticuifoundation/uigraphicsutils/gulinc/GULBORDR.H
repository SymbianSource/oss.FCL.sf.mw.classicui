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

#if !defined(__GULBORDR_H__)
#define __GULBORDR_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif

#if !defined(__GULDEF_H__)
#include <guldef.h>
#endif

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

class TGulBorder
/** Draws a border around a control.

The rectangular areas enclosed by borders are typically working areas of the 
graphics context so the class supplies a number of methods which describe 
how it occupies the area.

A distinction between descriptive and logical borders is made. For descriptive 
borders the appearance of the border is known and fixed. The type of border 
drawn is determined by flags which describe how it is to be constructed. These 
flags can be combined to achieve many different effects, and standard combinations 
have been supplied (see the TBorderType enumeration). For logical borders 
the use of the border is known and fixed but the appearance is not specified. 
The appearance and sizing functions must be supplied in custom written code. 
@publishedAll
@released*/
    {
public:
	class TColors
	/** Represents the colours used within the border and for the optional single pixel 
	border outlines.

	These colours are stored using TRgb values.

	An object of this type can be populated using ColorUtils::GetRgbDerivedBorderColors().

	The colours used inside the border are derived from iBack, the border's background 
	colour, so that border colours can be lighter or darker shades of the colour 
	used in the main body of the control they enclose. Different combinations 
	of light and dark shades are used to draw opposite border sides, to achieve 
	a raised or sunken effect. */
		{
	public:
		IMPORT_C TColors();
	public:	
		/** The line colour.
	
		This is the colour used to draw the outlines on either side of the border. 
		Not all border types have an outline. By default, KRgbBlack. */
		TRgb iLine;
		/** The background colour for the border. 
	
		The other colours used in the border are derived from this.
	
		By default, KRgbWhite. */
		TRgb iBack;
		/** The lightest colour. 
	
		By default, KRgbWhite. */
		TRgb iLight;
		/** The mid light colour. 
	
		This colour is midway between iBack and iLight. By default, KRgbWhite. */
		TRgb iMidlight;
		/** The mid dark colour. 
	
		This colour is midway between iBack and iDark. By default, KRgbDarkGray. */
		TRgb iMid;
		/** The darkest colour.
	
		By default, KRgbDarkGray. */
		TRgb iDark;
		/** Not used. */
		TRgb iInternalBack;
		};

public:
	/** Defines the border outline style. 

	Note that not all border types have an outline. */
	enum TOutlineStyle
		{
		/** The border has a single pixel outline, either solid (by default) or dotted. */
		EWithOutline=0x01,
		/** The border outline is drawn using a dotted pen. */
		EDottedOutline=0x02
		};

	/** Defines whether or not the border has a single pixel interior border. 

	By default it does not. */
	enum TInlineStyle
		{
		/** The border has an interior border. */
		EWithInline=0x04
		};

	/** Defines the 3D border style. */
	enum T3DStyle
		{
		/** A flat border. */
		EFlat=0x10,
		/** A 3D effect sunken border. */
		ESunken=0x20,
		/** A 3D effect raised border. */
		ERaised=0x40
		};

	/** Defines the border's construction style. */
	enum TConstructionStyle
		{
		/** One step border construction. 
	
		This type of border is drawn using the mid light and mid dark colours on opposite 
		sides of the border. */
		EOneStep=0x100,
		/** Two step border construction.
	
		This type of border uses light and dark colours for the main border frame 
		(or mid light for the flat border), and an additional half frame using mid 
		light or mid dark colours. */
		ETwoStep=0x200,
		/** Three step border construction. 
	
		This type of border is drawn with an outer frame, a repeating one pixel band 
		in mid tones, and an inner frame. */
		EThreeStep=0x400,
		/** Inverted two step border construction. 
	
		This is the same as ETwoStep except that for raised and sunken borders, the 
		additional half frame is drawn on the opposite side to that used in ETwoStep. */
		EInvertedTwoStep=0x800
		};

	/** Defines the number of pixels to add to the border thickness.

	The border thickness is the central part of the border, coloured in the mid-tone 
	highlights and lowlights.

	For two step-constructed borders, the additional pixels are only added to 
	either the top left or bottom right hand sides. */
	enum TThickness
		{
		/** The border has one extra pixel. */
		EAddOnePixel=0x1000,
		/** The border has two extra pixels. */
		EAddTwoPixels=0x2000,
		/** The border has four extra pixels. */
		EAddFourPixels=0x4000
		};

	/** Defines the number of pixels that are removed to produce rounded corners. */
	enum TRounding
		{
		/** Border rounded by removing one extra pixel. */
		EAddOneRoundingPixel=0x10000,
		/** Border rounded by removing two extra pixels. */
		EAddTwoRoundingPixels=0x20000,
		/** Border rounded by by removing four extra pixels. */
		EAddFourRoundingPixels=0x40000
		};
private:
	enum TNull
		{
		ENoBorder=0x00
		};

	enum TLegacyStyle
		{
		EShallow=EAddOnePixel,
		EDeep=EAddTwoPixels,
		EThick=EAddFourPixels,
		EHorizontal=0x100000,
		EWithOverlap=0x200000,
		EGray=0x400000,
		EBlack=0x80000
		};

	enum TLogicalStyle
		{
		ELogical=0x800000
		};
public:
	/** For logical borders, defines whether the border encloses a window, a container 
	control or a control. */
	enum TLogicalFamily
		{
		/** Logical border around a window. */
		EWindowFamily=ELogical|0x1,
		/** Logical border around a container. */
		EContainerFamily=ELogical|0x2,
		/** Logical border around a control. */
		EControlFamily=ELogical|0x3
		};
public:
	/** Defines the descriptive border types. */
	enum TBorderType
		{
		/** No border. */
		ENone=ENoBorder,
		/** Border is a 1 pixel wide grey outline. */
		ESingleGray=EWithOutline|EGray,
		/** Border is a 1 pixel wide black outline. */
		ESingleBlack=EWithOutline|EBlack,
		/** Border is a 1 pixel wide dotted outline. */
		ESingleDotted=EWithOutline|EDottedOutline,
		/** A 3D raised border, with 1 pixel thickness. */
		EShallowRaised=ERaised|EOneStep|EAddOnePixel,
		/** A 3D sunken border, with 1 pixel thickness. */
		EShallowSunken=ESunken|EOneStep|EAddOnePixel,
		/** A 3D raised border, with outline, and 2 pixel thickness. */
		EDeepRaised=EWithOutline|ERaised|EOneStep|EAddTwoPixels,
		/** The same as EDeepRaised. */
		EDeepRaisedWithOutline=EWithOutline|ERaised|EOneStep|EAddTwoPixels,
		/** A 3D sunken border, with outline, and 2 pixel thickness. */
		EDeepSunken=EWithOutline|ESunken|EOneStep|EAddTwoPixels,
		/** The same as EDeepSunken. */
		EDeepSunkenWithOutline=EWithOutline|ESunken|EOneStep|EAddTwoPixels,
		/** A 3D raised border, with outline, and 3 pixel thickness. */
		EThickDeepRaisedWithOutline=EWithOutline|ERaised|EOneStep|EAddOnePixel|EAddTwoPixels, 
		/** A 3D raised border, with 2 pixels thickness and no outline on the left and 
		right hand sides. */
		EVerticalBar=ERaised|EOneStep|EAddTwoPixels|EWithOverlap,
		/** A 3D raised border, with 2 pixels thickness and no outline on the top and bottom. */
		EHorizontalBar=ERaised|EOneStep|EAddTwoPixels|EHorizontal|EWithOverlap
		};

	/** Defines the logical border types. */
	enum TLogicalType
		{
		// Window family
		/** Raised border around a window. */
		EWindow=EWindowFamily|ERaised,
		// Container family
		/** Flat border around a container. */
		EFlatContainer=EContainerFamily|EFlat,
		/** Raised border around a container. */
		ERaisedContainer=EContainerFamily|ERaised,
		/** Sunken border around a container. */
		ESunkenContainer=EContainerFamily|ESunken,
		// Control Family
		/** Flat border around a control. */
		EFlatControl=EControlFamily|EFlat,
		/** Raised border around a control. */
		ERaisedControl=EControlFamily|ERaised,
		/** Sunken border around a control. */
		ESunkenControl=EControlFamily|ESunken,
		/** Raised border around a control with focus. */
		EFocusedRaisedControl=EControlFamily|ERaised|0x100,
		/** Sunken border around a control with focus. */
		EFocusedSunkenControl=EControlFamily|ESunken|0x100
		};

public:
    IMPORT_C TGulBorder();
    IMPORT_C TGulBorder(TBorderType aType);
    IMPORT_C TGulBorder(TBorderType aType,TGulAdjacent aAdjacent);
	IMPORT_C TGulBorder(TInt aType);
    IMPORT_C TGulBorder(TInt aType,TGulAdjacent aAdjacent);
	IMPORT_C void Draw(CGraphicsContext& aGc,const TRect& aRect,const TColors& aBorderColors) const;
   	IMPORT_C void Draw(CGraphicsContext& aGc,const TRect& aRect) const;
	IMPORT_C TRect InnerRect(const TRect& aOuterRect) const;
   	IMPORT_C TRect OuterRect(const TRect& aInnerRect) const;
	IMPORT_C void SetType(TInt aType);
	IMPORT_C void SetAdjacent(TInt aAdjacent);
	IMPORT_C TSize SizeDelta() const;
   	IMPORT_C TMargins Margins() const;
	IMPORT_C TBool HasBorder() const;
	IMPORT_C TInt Adjacent() const;	
	IMPORT_C TInt Type() const;
public:	// Internal to Symbian
	IMPORT_C TInt Thickness() const;
	IMPORT_C TInt Rounding() const;
private:
	TBool IsSunken() const;
	TInt Depth() const;
	void DrawOutline(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor) const;
	void DrawRectOutline(CGraphicsContext& aGc,const TRect& aRect) const;
	void DrawInline(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor) const;
	TMargins OutlineMargins() const;
	TMargins BorderMargins() const;
	TMargins InlineMargins() const;
	TRect OutlineInnerRect(const TRect& aOuterRect) const;
	TRect BorderInnerRect(const TRect& aOuterRect) const;
	TInt BorderRounding() const;
	TInt InlineRounding() const;
	void DrawOneStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aMidlight,TRgb aMid) const;
	void DrawTwoStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aLight,TRgb aMidlight,TRgb aMid,TRgb aDark) const;
	void DrawInvertedTwoStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aLight,TRgb aMidlight,TRgb aMid,TRgb aDark) const;
	void DrawThreeStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aBack,TRgb aLight,TRgb aMidlight,TRgb aMid,TRgb aDark) const;
	void DrawTopLeft(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor,const TInt aRounding) const;
	void DrawRoundedTopLeft(CGraphicsContext& aGc,const TRect& aRect,const TInt aRounding) const;
	void DrawBottomRight(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor,const TInt aRounding) const;
	void DrawRoundedBottomRight(CGraphicsContext& aGc,const TRect& aRect,const TInt aRounding) const;
	void DrawRoundedCorner(CGraphicsContext& aGc,const TPoint& aStart,const TInt aRoundedLength, const TBool aUp, const TBool aRight) const;
	TInt RoundingMargin(const TInt aRoundedLength) const;
	inline TInt InternalType() const;
	void TranslateLegacyTypes();
private:
    TInt iType;
    };

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <graphics/uigraphicsutils/gullogicalborder.h>
#endif

#endif
