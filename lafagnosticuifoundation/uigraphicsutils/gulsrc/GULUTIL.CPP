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

#include <s32file.h>
#include <s32std.h>
#include <badesca.h>
#include <barsread.h>
#include <bautils.h>
#include <gdi.h>
#include <w32std.h>
#include <gulutil.h>
#include <gulcolor.h>
#include "GULSTD.H"
#include "GULLU.H"
#include <gulfont.hrh>
#include <gulftflg.hrh>
#include <numberconversion.h>

//
// TMargins8
//

EXPORT_C TMargins8::TMargins8()
/** The constructor initialises all four margins to zero. */
	{
	iLeft=iRight=iTop=iBottom=(TInt8)0;
	}

/**
Constructor setting the left, top, right, and bottom margins.

@param aLeft Left margin (between -128 and +127)
@param aTop Top margin (between -128 and +127)
@param aRight Right margin (between -128 and +127)
@param aBottom Bottom margin (between -128 and +127)
*/
EXPORT_C TMargins8::TMargins8(TInt8 aLeft, TInt8 aTop, TInt8 aRight, TInt8 aBottom) 
 : iLeft(aLeft), iRight(aRight), iTop(aTop), iBottom(aBottom)
	{
	}

EXPORT_C void TMargins8::SetAllValuesTo(TInt aCommonValue)
/** Sets all four margins to a common value (between -128 and +127).

@param aCommonValue The new value for all margins. */
	{
	iLeft=iRight=iTop=iBottom=(TInt8)aCommonValue;
	}

EXPORT_C TRect TMargins8::InnerRect(const TRect& aOuterRect) const
/** Calculates and returns an inner rectangle by applying the margins 
to the specified outer rectangle.

@param aOuterRect The coordinates of the outer rectangle from which 
the inner rectangle is calculated.
@return Inner rectangle. */
	{
    TRect inner=aOuterRect;
    inner.iTl.iX+=iLeft;
    inner.iTl.iY+=iTop;
    inner.iBr.iX-=iRight;
    inner.iBr.iY-=iBottom;
    return inner;
	}

EXPORT_C TRect TMargins8::OuterRect(const TRect& aInnerRect) const
/** Calculates and returns an outer rectangle by applying the margins 
to the specified inner rectangle.

@param aInnerRect The coordinates of the inner rectangle from which 
the outer rectangle is calculated.
@return Outer rectangle. */
	{
    TRect outer=aInnerRect;
    outer.iTl.iX-=iLeft;
    outer.iTl.iY-=iTop;
    outer.iBr.iX+=iRight;
    outer.iBr.iY+=iBottom;
    return outer;
	}

EXPORT_C TSize TMargins8::SizeDelta() const
/** Calculates and returns the difference in size between the outer 
and inner rectangles.

@return Size difference between outer and inner rectangles. */
	{
	return TSize(iLeft+iRight,iTop+iBottom);
	}

//
// class DrawUtils
//

EXPORT_C void DrawUtils::DrawText(CGraphicsContext& aGc,const TDesC& aString,const TRect& aBox,TInt aBaseLineOffset,
									 CGraphicsContext::TTextAlign aHoriz,TInt aMargin,const CFont* aFont)
/** Draws text inside a rectangle. 

@param aGc The graphics context.
@param aString The text string to draw. 
@param aBox The rectangle to draw the text in. 
@param aBaseLineOffset An offset from the top of the box to the text baseline. 
@param aHoriz The horizontal text alignment.
@param aMargin The margin around the text.
@param aFont The font to use. */
	{ // static
	if (aHoriz!=CGraphicsContext::ELeft)
        {
		const TInt extraWidth=aBox.Width()-aFont->TextWidthInPixels(aString)-aMargin;
        if (aHoriz==CGraphicsContext::ECenter)
            aMargin+=extraWidth/2;
		else
			aMargin=extraWidth;
        }
	aGc.DrawText(aString,aBox,aBaseLineOffset,CGraphicsContext::ELeft,aMargin);
	}

EXPORT_C void DrawUtils::ClearBetweenRects(CGraphicsContext& aGc,const TRect& aOuterRect,const TRect& aInnerRect)
/** Clears between two rectangles, using a solid brush style and no pen.

@param aGc The graphics context.
@param aOuterRect The outer rectangle.
@param aInnerRect The inner rectangle. */
    { // static
    aGc.SetPenStyle(CGraphicsContext::ENullPen);
    aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    DrawBetweenRects(aGc,aOuterRect,aInnerRect);
    aGc.SetPenStyle(CGraphicsContext::ESolidPen);
    aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
    }

EXPORT_C void DrawUtils::DrawBetweenRects(CGraphicsContext& aGc,const TRect& aOuterRect,const TRect& aInnerRect)
/** Draws between two rectangles.

The pen and brush settings are used as specified in the graphics context.

@param aGc The graphics context.
@param aOuterRect The outer rectangle to be drawn.
@param aInnerRect The inner rectangle to be drawn. */
    { // static
    TRect rect=aOuterRect;
    rect.iBr.iY=aInnerRect.iTl.iY;
    aGc.DrawRect(rect);
    rect.iBr.iY=aOuterRect.iBr.iY;
    rect.iTl.iY=aInnerRect.iBr.iY;
    aGc.DrawRect(rect);
    rect=aInnerRect;
    rect.iTl.iX=aOuterRect.iTl.iX;
    rect.iBr.iX=aInnerRect.iTl.iX;
    aGc.DrawRect(rect);
    rect.iTl.iX=aInnerRect.iBr.iX;
    rect.iBr.iX=aOuterRect.iBr.iX;
    aGc.DrawRect(rect);
    }

//
// class TextUtils
//	

EXPORT_C void TextUtils::ClipToFit(TDes& aBuffer,const CFont& aFont,TInt aMaxWidthInPixels,TChar aAlternativeEnd)
/** Clips text to fit into a maximum width.

If the text is too wide to fit in the width when displayed in aFont, 
it is truncated and the specified character (by default, 
a horizontal ellipsis) is appended to it.

@param aBuffer A buffer containing the text to clip.
@param aFont The font.
@param aMaxWidthInPixels The maximum width in pixels.
@param aAlternativeEnd The Unicode character to append to the buffer if truncated. 
By default, this is the horizontal ellipsis. */
	{
	TInt textWidth=aFont.TextWidthInPixels(aBuffer);
	if (textWidth<=aMaxWidthInPixels)
		return;
	TBuf<1> ellipse;
	ellipse.Append(aAlternativeEnd);
	TInt extraWidth=aFont.TextWidthInPixels(ellipse);
	TInt cutOff=aFont.TextCount(aBuffer,aMaxWidthInPixels-extraWidth);
	aBuffer.SetLength(cutOff);
	aBuffer.Append(ellipse);
	}

EXPORT_C TInt TextUtils::ColumnText(TPtrC& aColumnText,TInt aColumn,const TDesC* aSourceText,TChar aColumnSeparator)
/** Gets a portion of text from a descriptor, corresponding to a requested column.

@param aColumnText On return, set to the portion of aSourceText that corresponds 
to the column aColumn.
@param aColumn The column to extract. The first column is numbered zero.
@param aSourceText The source text string that contains one or more column 
separators.
@param aColumnSeparator The character used in aSourceText to separate the columns. 
By default, a tab character.
@return KErrNotFound if the column number is invalid, otherwise KErrNone. */
	{
	aColumnText.Set(TPtrC());
	TInt end=0;
	TInt column=0;
	TPtrC text;
	if (aSourceText)
		text.Set(*aSourceText);
	while (text.Length())
		{
		end=text.Locate(aColumnSeparator);
		if (end==KErrNotFound)
			end=text.Length();
		if (column==aColumn)
			{
			aColumnText.Set(text.Left(end));
			return(KErrNone);
			}
		else if (++column>aColumn)
			break;
		if (end<text.Length())
			++end;
		text.Set(text.Mid(end));
		}
	return(KErrNotFound);
	}

EXPORT_C void TextUtils::TruncateToNumChars(TDes& aBuffer, TInt numChars)
/** Truncates text to a number of characters.

If truncation is required (because aBuffer contains more than numChars 
characters), an ellipsis is added to the text as the last character.

@param aBuffer On return, contains the truncated text.
@param numChars The number of characters. */
	{
	if (aBuffer.Length() <= numChars)
		return;
	aBuffer.SetLength(numChars-1);
	aBuffer.Append(KTextUtilClipEndChar);
	}

//
// class FontUtils
//

enum { EMinFontHeight=4 };

EXPORT_C void FontUtils::GetAvailableFontsL(const CGraphicsDevice& aDevice, CDesCArray& aFontNameList,TInt aFonts)
/** Gets the list of typeface names available for the graphics device.

@param aDevice The graphics device.
@param aFontNameList On return, contains the list of typeface names.
@param aFonts Can be used to specify which sorts of typefaces are required. 
For possible values, see the flags defined in gulftflg.hrh 
beginning with EGulAllFonts. */
	{ // static
	aFontNameList.Reset();
	const TInt numTypefaces=aDevice.NumTypefaces();
	TTypefaceSupport typefaceInfo;
	for (TInt ii=0;ii<numTypefaces;ii++)
		{
		aDevice.TypefaceSupport(typefaceInfo,ii);
		if (typefaceInfo.iTypeface.IsProportional())
			{
			if (aFonts==EGulMonospaceFontsOnly)
				continue;
			}
		else if (aFonts==EGulNoMonospaceFonts || aFonts==EGulNoMonospaceOrSymbolFonts)
			continue;
		if (typefaceInfo.iTypeface.IsSymbol())
			{
			if (aFonts==EGulNoSymbolFonts || aFonts==EGulNoMonospaceOrSymbolFonts || aFonts==EGulMonospaceFontsOnly)
				continue;
			}
		else if (aFonts==EGulSymbolFontsOnly)
			continue;
		aFontNameList.AppendL(typefaceInfo.iTypeface.iName);
		}
	}

EXPORT_C TInt FontUtils::TypefaceAttributes(const CGraphicsDevice& aDevice, const TDesC& aTypefaceName)
/** Gets the attributes of a named typeface, if supported by the graphics device.

@param aDevice The graphics device.
@param aTypefaceName The name of the typeface.
@return The typeface attributes. Attributes are zero if the typeface is not 
supported by the graphics device. Attribute values are defined in TTypeface. */
	{
	const TInt numTypefaces=aDevice.NumTypefaces();
	TInt fontIndex;
	for (fontIndex=0;fontIndex<numTypefaces;fontIndex++)
		{
    	TTypefaceSupport typefaceInfo;
		aDevice.TypefaceSupport(typefaceInfo,fontIndex);
		if (typefaceInfo.iTypeface.iName==aTypefaceName)
			return(typefaceInfo.iTypeface.Attributes());
		}	
	return(0);
	}

EXPORT_C TInt FontUtils::GetAvailableHeightsInTwipsL(const CGraphicsDevice& aDevice,const TDesC& aTypefaceName,CArrayFix<TInt>& aHeightList)
/** Gets a list of all heights in twips, available for the named typeface and the 
graphics device specified.

@param aDevice The graphics device.
@param aTypefaceName The name of the typeface.
@param aHeightList On return, contains all available heights for the typeface, 
in twips. 
@return KErrNotSupported if the named typeface is not supported by the graphics 
device, otherwise KErrNone. */
	{ // static
	aHeightList.Reset();
	const TInt numTypefaces=aDevice.NumTypefaces();
	TInt fontIndex;
	for (fontIndex=0;fontIndex<numTypefaces;fontIndex++)
		{
    	TTypefaceSupport typefaceInfo;
		aDevice.TypefaceSupport(typefaceInfo,fontIndex);
		if (typefaceInfo.iTypeface.iName==aTypefaceName)
			break;
		}
	if (fontIndex>=numTypefaces)
		return KErrNotSupported;
	TTypefaceSupport typefaceInfo;
	aDevice.TypefaceSupport(typefaceInfo,fontIndex);
	const TInt numHeights=typefaceInfo.iNumHeights;
	for (TInt ii=0;ii<numHeights;ii++)
		{
		const TInt height=aDevice.FontHeightInTwips(fontIndex,ii);
		if (PointsFromTwips(height)>=EMinFontHeight)
			aHeightList.AppendL(height);
		}
	return KErrNone;
	}

EXPORT_C TInt FontUtils::GetAvailableHeightsInTwipsAndPointsL(const CGraphicsDevice& aDevice,const TDesC& aTypefaceName,CArrayFix<TInt>& aTwipsList,CDesCArray& aPointsList)
/** Gets a list of all heights in twips, available for the named typeface and the 
graphics device specified.

Also gets a list of heights in points, represented as character strings.

@param aDevice The graphics device.
@param aTypefaceName The name of the typeface.
@param aTwipsList On return, contains all available heights for the typeface, 
in twips.
@param aPointsList On return, the heights in points, represented as character 
strings.
@return KErrNotSupported if the named typeface is not supported by the graphics 
device, otherwise KErrNone. */
	{ // static
	aTwipsList.Reset();
	aPointsList.Reset();
	TInt err=GetAvailableHeightsInTwipsL(aDevice,aTypefaceName,aTwipsList);
	if (err==KErrNotSupported)
		return err;
	const TInt count=aTwipsList.Count();
	for (TInt ii=0;ii<count;ii++)
		{
		const TInt points=PointsFromTwips(aTwipsList[ii]);
		if (points<EMinFontHeight)
			continue;
		TBuf<8> num;
		num.Num(points);
		aPointsList.AppendL(num);
		}
	return KErrNone;
	}

EXPORT_C TInt FontUtils::PointsFromTwips(TInt aTwips)
/** Converts a number of twips to points. 

@param aTwips A number of twips.
@return A number of points. */
	{ // static
	//one point=20 twips
	return (aTwips+10)/20;
	}

EXPORT_C TInt FontUtils::TwipsFromPoints(TInt aPoints)
/** Converts a number of points into twips.

@param aPoints A number of points.
@return A number of twips. */
	{ // static
	//one point=20 twips
	return (aPoints*20);
	}

EXPORT_C TInt FontUtils::TwipsFromPoints(const TDesC& aPoints)
/** Converts a number of points held as text to twips.

@param aPoints A number of points as text.
@return A number of twips. */
	{ // static
	TInt digits=aPoints.Length();
	TInt num=aPoints[--digits];
	TInt count=0;
	while (digits)
		num+=aPoints[--digits]*(++count*10);
	return TwipsFromPoints(num);
	}

EXPORT_C TInt FontUtils::IndexOfNearestHeight(CArrayFix<TInt>& aTwipsList,TInt aHeight)
/** Gets the index into the supplied list of font heights of the closest  
match to the font height specified.

@param aTwipsList The twips list.
@param aHeight The requested font height. This may be generated by a call to GetAvailableHeightsInTwipsL() 
or GetAvailableHeightsInTwipsAndPointsL().
@return The index into the list of the closest font height to aHeight. */
	{ // static
	TInt pos=0;
	const TInt count=aTwipsList.Count();
	for (TInt ii=0; ii<count; ii++)
		{
		if (aTwipsList[ii]>aHeight)
			break;
		pos=ii;
		}
	return pos;
	}

//
// class ResourceUtils
//

EXPORT_C CFbsFont* ResourceUtils::CreateNamedScreenFontL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice)
/** Creates and returns a named screen font from a NAMED_FONT resource.

@param aResourceReader Resource reader to use to read the font information. 
@param aScreenDevice The screen device for which the font will be created. 
@return The screen font, whose size is in twips. The caller takes ownership. */
	{
	TFontSpec fontSpec;
	fontSpec.iTypeface.iName=aResourceReader.ReadTPtrC();
	fontSpec.iHeight=aResourceReader.ReadInt16();

	TUint flags=aResourceReader.ReadUint16(); // a combination of EGulFontFlagXxxxs

	fontSpec.iTypeface.SetIsProportional( !(flags&EGulFontFlagMono) );
	
	if (flags&EGulFontFlagBold)
		fontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightBold );

	if (flags&EGulFontFlagItalic)
		fontSpec.iFontStyle.SetPosture(EPostureItalic);

	CFbsFont* font;
	User::LeaveIfError(aScreenDevice.GetNearestFontInTwips((CFont*&)font,fontSpec));
	return(font);
	}

EXPORT_C CFbsFont* ResourceUtils::CreateNamedScreenFontInPixelsL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice)
/** Creates a named screen font in pixels from a NAMED_FONT resource.

@param aResourceReader Resource reader to use to read the font information. 
@param aScreenDevice The screen device for which the font will be created. 
@return The screen font, whose size is in pixels. The caller takes ownership. */
	{
	TFontSpec fontSpec;
	fontSpec.iTypeface.iName=aResourceReader.ReadTPtrC();
	fontSpec.iHeight=aResourceReader.ReadInt16();

	TUint flags=aResourceReader.ReadUint16(); // a combination of EGulFontFlagXxxxs

	fontSpec.iTypeface.SetIsProportional( !(flags&EGulFontFlagMono) );
	
	if (flags&EGulFontFlagBold)
		fontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightBold );

	if (flags&EGulFontFlagItalic)
		fontSpec.iFontStyle.SetPosture(EPostureItalic);

	CFbsFont* font;
	User::LeaveIfError(aScreenDevice.GetNearestFontInPixels((CFont*&)font,fontSpec));
	return(font);
	}

EXPORT_C CFbsFont* ResourceUtils::CreateScreenFontL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice)
/** Creates a screen font from a FONT resource.

@param aResourceReader Resource reader to use to read the font UID and flags. 
@param aScreenDevice The screen device for which the font will be created. 
@return The screen font. The caller takes ownership. */
	{
	TUid fontId;
	fontId.iUid=aResourceReader.ReadInt32();
	TUint flags=aResourceReader.ReadUint16(); // a combination of EGulFontFlagXxxxs
	TAlgStyle algStyle;
	algStyle.SetIsBold(flags&EGulFontFlagBold);
	algStyle.SetIsItalic(flags&EGulFontFlagItalic);
	algStyle.SetIsMono(flags&EGulFontFlagMono);
	algStyle.SetWidthFactor((flags&EGulFontFlagDoubleWidth)? 2: 1); 
	algStyle.SetHeightFactor((flags&EGulFontFlagDoubleHeight)? 2: 1);
	CFbsFont* font;
	User::LeaveIfError(aScreenDevice.GetFontById((CFont*&)font,fontId,algStyle));
	return(font);
	}

EXPORT_C TInt32 ResourceUtils::ReadResourceIntL(TResourceReader& aReader,TResourceTypeInt aSize)
//
//	Read a resource specifying a number
//
	{
	TInt32 value=0;
	switch(aSize)
		{
	case EResourceInt8:
		value=aReader.ReadInt8();
		break;
	case EResourceInt16:
		value=aReader.ReadInt16();
		break;
	case EResourceInt32:
		value=aReader.ReadInt32();
		break;
	default:
		Panic(EEgulPanicResourceInvalidNumberType);
		}
	return(value);
	}

EXPORT_C void ResourceUtils::PopulateColorArrayL(CColorArray& aColors,TResourceReader& aReader)
/** Populates an array of logical colours using a pre-initialised resource 
reader from an array of CTRL_COLOR resources.

@param aColors On return, contains the colour array read from the resource. 
@param aReader Resource reader to use to read the colour array. */
	{ // static
	const TInt count=aReader.ReadInt16();
	for (TInt ii=0;ii<count;ii++)
		{
		TInt logicalColor=aReader.ReadInt16();
		TInt red=aReader.ReadUint8();
		TInt green=aReader.ReadUint8();
		TRgb color(red,green,aReader.ReadUint8());
		aColors.AddL(logicalColor,color);
		}
	}


//
// class ColorUtils
//

EXPORT_C TRgb ColorUtils::ColorAdjust(TRgb aColor,TInt aPercentage)
/** Brightens or darkens a 24-bit colour by a percentage. 

If the percentage given is less than 100%, a darker colour will be returned. 
The algorithm brightens or darkens each of the R, G and B channels equally.

@param aColor Input colour. 
@param aPercentage Percentage by which to adjust the input colour. 
@return The adjusted colour. */
	{
	// Poor algorithm for the moment, but it can improve and all apps that
	// use this will benefit. (I don't think the accuracy for a 16/256 color system
	// is really relevant anyway)
	TInt red=aColor.Red();
	TInt green=aColor.Green();
	TInt blue=aColor.Blue();
	TInt alpha=aColor.Alpha();
	if (aPercentage<=100)
		{
		red=(red * aPercentage)/100;
		green=(green * aPercentage)/100;
		blue=(blue * aPercentage)/100;
		}
	else
		{
		red = 255 - (((255 - red) * 100) / aPercentage);
		green = 255 - (((255 - green) * 100) / aPercentage);
		blue = 255 - (((255 - blue) * 100) / aPercentage);
		}
	return TRgb(red,green,blue,alpha);
	}

const TInt KDarkRgbSubtractor = 85;

EXPORT_C TRgb ColorUtils::RgbDarkerColor(TRgb aRgb, TDisplayMode aMode)
/** Creates a darker color.

@param aRgb The RGB color.
@param aMode The display mode, which indicates the screen output of the colour 
e.g. 256 colour display mode (8 bpp).
@return The darker colour. */
	{
	switch (aMode)
		{
	case EColor256:
		return TRgb::Color256(color256darklutab[aRgb.Color256()]);
	default:
		TInt value = aRgb.Internal();
		TInt b = Max( 0, ((value & 0x000000ff)  ) - KDarkRgbSubtractor );
		TInt g = Max( 0, ((value & 0x0000ff00)  >> 8) - KDarkRgbSubtractor );
		TInt r = Max( 0, ((value & 0x00ff0000)  >> 16) - KDarkRgbSubtractor );
		return TRgb(r,g,b,aRgb.Alpha());
		}
	}

const TInt KLightRgbAdder = 30;

EXPORT_C TRgb ColorUtils::RgbLighterColor(TRgb aRgb, TDisplayMode aMode)
/** Creates a lighter colour.

@param aRgb The Rgb colour.
@param aMode The display mode, which indicates the screen output of the colour 
e.g. 256 colour display mode (8 bpp).
@return The lighter colour. */
	{
	switch (aMode)
		{
	case EColor256:
		return TRgb::Color256(color256lightlutab[aRgb.Color256()]);
	default:
		TInt value = aRgb.Internal();
		TInt b = Min( 255, ((value & 0x000000ff)  ) + KLightRgbAdder );
		TInt g = Min( 255, ((value & 0x0000ff00)  >> 8) + KLightRgbAdder );
		TInt r = Min( 255, ((value & 0x00ff0000)  >> 16) + KLightRgbAdder );
		return TRgb(r,g,b,aRgb.Alpha());
		}
	}

const TInt KMidDarkRgbSubtractor = 42;

EXPORT_C TRgb ColorUtils::RgbMidDarkerColor(TRgb aRgb, TDisplayMode aMode)
/** Creates a medium dark version of the colour.

This function darkens the colour 50% less than RgbDarkerColor().

@param aRgb The Rgb color. 
@param aMode The display mode, which indicates the screen output of the colour 
e.g. 256 colour display mode (8 bpp).
@return The medium dark colour. */
	{
	switch (aMode)
		{
	case EColor256:
		return TRgb::Color256(color256middarklutab[aRgb.Color256()]);
	default:
		TInt value = aRgb.Internal();
		TInt b = Max( 0, ((value & 0x000000ff)  ) - KMidDarkRgbSubtractor );
		TInt g = Max( 0, ((value & 0x0000ff00)  >> 8) - KMidDarkRgbSubtractor );
		TInt r = Max( 0, ((value & 0x00ff0000)  >> 16) - KMidDarkRgbSubtractor );
		return TRgb(r,g,b,aRgb.Alpha());
		}
	}

EXPORT_C void ColorUtils::GetRgbDerivedBorderColors(TGulBorder::TColors& aBorderColors,TRgb aBackgroundColor,TDisplayMode aMode)
/** Gets the colours to use for a control's border.

Lighter and darker tones in the border are derived from the specified TRgb 
background colour using an algorithm operating on the RGB value of this color 
or a lookup table, depending on the display mode aMode. It sets the values 
of the aBorderColors members iBack, iLight, iMidlight, iMid, and iDark.

@param aBorderColors On return, the derived border colours.
@param aBackgroundColor The control's background colour. 
@param aMode The display mode. */
	{
	aBorderColors.iBack = aBackgroundColor;
	aBorderColors.iMid = RgbDarkerColor( aBorderColors.iBack, aMode );
	aBorderColors.iDark = RgbDarkerColor( aBorderColors.iMid, aMode );
	aBorderColors.iMidlight = RgbLighterColor( aBorderColors.iBack, aMode );
	aBorderColors.iLight = RgbLighterColor( aBorderColors.iMidlight, aMode );
	}

//
// The TGradientFill class is a private utility class that is used by the ColorUtils::CreateGradientBitmapL method
//

NONSHARABLE_CLASS(TGradientFill)
	{
public:
	TGradientFill(CFbsBitmap& aBitmap,ColorUtils::TBitmapOrientation aOrientation,TRgb aStartColor,TRgb aEndColor);
	void DrawBitmap();
private:
	void Calculate();
	TRgb ColorAt(TInt aPos) const;
	TRgb Map(const TRgb aRgb) const;
	TInt Index(const TRgb aRgb) const;
private:
	CFbsBitmap& iBitmap;
	ColorUtils::TBitmapOrientation iOrientation;
	TRgb iStartColor;
	TRgb iEndColor;
	TDisplayMode iMode;
	TInt iBitmapLength;
	TUint32 iStartColRed;
	TInt32 iDiffRed;
    TInt iRoundingRed;
	TUint32 iStartColGreen;
	TInt32 iDiffGreen;
    TInt iRoundingGreen;
	TUint32 iStartColBlue;
	TInt32 iDiffBlue;
    TInt iRoundingBlue;
	};

TGradientFill::TGradientFill(CFbsBitmap& aBitmap, ColorUtils::TBitmapOrientation aOrientation,
							TRgb aStartColor,TRgb aEndColor) 
: iBitmap(aBitmap), 
  iOrientation(aOrientation),
  iStartColor(aStartColor), 
  iEndColor(aEndColor), 
  iMode(aBitmap.DisplayMode()) 
	{
	}

void TGradientFill::DrawBitmap()
	{
    TBitmapUtil bitmapUtil(&iBitmap);
    bitmapUtil.Begin(TPoint(0,0)); 
    bitmapUtil.SetPos(TPoint(0,0));

	Calculate();

	TBool toggleDither = ETrue;

	// Initialise the colors
	TRgb thisMapped = Map(ColorAt(0));
	TInt thisIndex = 0;
	TRgb nextMapped = thisMapped;
	TInt nextIndex = 0;

    for (TInt i=0;i<iBitmapLength;i++)
        {
		// Update colors if necessary
		thisMapped = Map(ColorAt(i));
		TInt lookAhead=i;

		FOREVER
			{
			if (lookAhead == (iBitmapLength-1))
				{
				break; // Reached end of gradient
				}
			TRgb testNext = ColorAt(++lookAhead);
			TRgb testMapped = Map(testNext);
			if (testMapped != thisMapped)
				{
				if (testMapped != nextMapped)
					{
					thisIndex = nextIndex;
					nextMapped = testMapped;
					nextIndex = lookAhead;
					}
				break;
				}
			}

		TRgb pixelOne;
		TRgb pixelTwo;
		TInt range = nextIndex - thisIndex;

		if ( (4*i) < ( (4*thisIndex)+range ) )
			{
			pixelOne = pixelTwo = thisMapped;
			}
		else if ( (4*i) < ( (4*thisIndex)+(3*range) ) )
			{
			pixelOne = thisMapped;
			pixelTwo = nextMapped;
			}
		else 
			{
			pixelOne = pixelTwo = nextMapped;
			}

		if (toggleDither)
			{
			TRgb temp = pixelOne;
			pixelOne = pixelTwo;
			pixelTwo = temp;
			}

		toggleDither = !toggleDither;
		
		// Write out the pixels
		bitmapUtil.SetPixel(Index(pixelOne));
        if(iOrientation==ColorUtils::EBitmapOrientationHorizontal)
            {
			bitmapUtil.IncYPos();
			bitmapUtil.SetPixel(Index(pixelTwo));
			bitmapUtil.DecYPos();			
			bitmapUtil.IncXPos();
            }
        else
			{
            bitmapUtil.IncXPos();
			bitmapUtil.SetPixel(Index(pixelTwo));
			bitmapUtil.DecXPos();			
            bitmapUtil.IncYPos();
			}
		}
    bitmapUtil.End();
    }

void TGradientFill::Calculate()
	{
	if (iOrientation==ColorUtils::EBitmapOrientationVertical)
		iBitmapLength = iBitmap.SizeInPixels().iHeight; 
	else
		iBitmapLength = iBitmap.SizeInPixels().iWidth; 

	const TUint32 rounding=(iBitmapLength+1)>>1;

	iStartColRed=iStartColor.Red();
	iDiffRed=iEndColor.Red()-iStartColRed;
    iRoundingRed=0;
    if (iDiffRed>0)
		iRoundingRed+=rounding;
	else
		iRoundingRed-=rounding;

	iStartColGreen=iStartColor.Green();
	iDiffGreen=iEndColor.Green()-iStartColGreen;
    iRoundingGreen=0;
	if (iDiffGreen>0)
		iRoundingGreen+=rounding;
	else
		iRoundingGreen-=rounding;

	iStartColBlue=iStartColor.Blue();
	iDiffBlue=iEndColor.Blue()-iStartColBlue;
    iRoundingBlue=0;
	if (iDiffBlue>0)
		iRoundingBlue+=rounding;
	else
		iRoundingBlue-=rounding;
	}

TRgb TGradientFill::ColorAt(TInt aPos) const
	{
	TUint32 redCurrentVal = iStartColRed+((aPos*iDiffRed+iRoundingRed)/(iBitmapLength-1));
	TUint32 greenCurrentVal = iStartColGreen+((aPos*iDiffGreen+iRoundingGreen)/(iBitmapLength-1));
	TUint32 blueCurrentVal = iStartColBlue+((aPos*iDiffBlue+iRoundingBlue)/(iBitmapLength-1));
	return TRgb(redCurrentVal,greenCurrentVal,blueCurrentVal);
	}

TRgb TGradientFill::Map(const TRgb aRgb) const
	{
	switch (iMode)
		{
	case EGray2:
		return TRgb::Gray2(aRgb.Gray2());
	case EGray4:
		return TRgb::Gray4(aRgb.Gray4());
	case EGray16:
		return TRgb::Gray16(aRgb.Gray16());
	case EGray256:
		return TRgb::Gray256(aRgb.Gray256());
	case EColor16:
		return TRgb::Color16(aRgb.Color16());
	case EColor256:
		return TRgb::Color256(aRgb.Color256());
	case EColor64K:
		return TRgb::Color64K(aRgb.Color64K());
	case EColor16M:
		return TRgb::Color16M(aRgb.Color16M());
	case EColor4K:
		return TRgb::Color4K(aRgb.Color4K());
	case EColor16MU:
		return TRgb::Color16MU(aRgb.Color16MU());
	case EColor16MA:
		return TRgb::Color16MA(aRgb.Color16MA());
	case EColor16MAP:
		return TRgb::Color16MAP(aRgb.Color16MAP());
	default:
		return aRgb;
		}
	}

TInt TGradientFill::Index(const TRgb aRgb) const
	{
	switch (iMode)
		{
	case EGray2:
		return aRgb.Gray2();
	case EGray4:
		return aRgb.Gray4();
	case EGray16:
		return aRgb.Gray16();
	case EGray256:
		return aRgb.Gray256();
	case EColor16:
		return aRgb.Color16();
	case EColor256:
		return aRgb.Color256();
	case EColor64K:
		return aRgb.Color64K();
	case EColor16M:
		return aRgb.Color16M();
	case EColor4K:
		return aRgb.Color4K();
	case EColor16MU:
	    return aRgb.Color16MU();
	case EColor16MA:
	    return aRgb.Color16MA();
	case EColor16MAP:
	    return aRgb.Color16MAP();
	default:
		return aRgb.Color16M();
		}
	}

const TInt KBitmapBreadthPixels=2;

EXPORT_C void ColorUtils::CreateGradientBitmapL(CFbsBitmap& aBitmap,  const RWsSession& aWs, TInt aBreadth,
											   TBitmapOrientation aOrientation,TRgb aStartColor,TRgb aEndColor)
/** Creates a CFbsBitmap containing a colour gradient.

To create a gradient, the end colour aEndColor must be different to the 
start colour aStartingColor.

@param aBitmap Bitmap which on return contains the colour gradient.
@param aWs Handle to a window server session. 
@param aBreadth The width or the height of the bitmap, depending on the orientation.
@param aOrientation The bitmap's orientation (vertical or horizontal).
@param aStartColor The start color.
@param aEndColor The end color. */
    { // static
    TInt grayscaleCapabilities;
	TInt colorCapabilities;
    TDisplayMode displayMode=aWs.GetDefModeMaxNumColors(colorCapabilities,grayscaleCapabilities);
	const TSize bmpSize=(aOrientation==EBitmapOrientationVertical?
		TSize(KBitmapBreadthPixels,aBreadth) : TSize(aBreadth,KBitmapBreadthPixels));
	User::LeaveIfError(aBitmap.Create(bmpSize,displayMode));
	TGradientFill filler(aBitmap,aOrientation,aStartColor,aEndColor);
	filler.DrawBitmap();
    }

//
// TFindWidthOfWidestTextItem
//

EXPORT_C TInt TFindWidthOfWidestTextItem::MaximumWidthInPixels(const CFont& aFont) const
/** Gets the width in pixels of the widest item in the range, using the specified 
font.

@param aFont The font.
@return The maximum width. */
	{
	TInt widthOfWidestTextItem=0;
	TBuf<256> textItem;
	TInt firstIndex;
	TInt lastIndex;
	GetFirstAndLastIndex(firstIndex, lastIndex);
	for (TInt i=firstIndex; i<=lastIndex; ++i)
		{
		GetTextItem(textItem, i);
		TInt widthOfTextItem=aFont.TextWidthInPixels(textItem);
		if (widthOfWidestTextItem<widthOfTextItem)
			widthOfWidestTextItem=widthOfTextItem;
		}
	return widthOfWidestTextItem;
	}

//
// class TFindWidthOfWidestDigit
//

EXPORT_C TFindWidthOfWidestDigit::TFindWidthOfWidestDigit()
/** Default constructor. */
	{
	}

void TFindWidthOfWidestDigit::GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const
	{
	aFirstIndex='0';
	aLastIndex='9';
	}

void TFindWidthOfWidestDigit::GetTextItem(TDes& aText, TInt aIndex) const
	{
	aText.SetLength(0);
	aText.Append(aIndex);
	}

//
// class TFindWidthOfWidestDigitType
//

EXPORT_C TFindWidthOfWidestDigitType::TFindWidthOfWidestDigitType(TDigitType aDigitType):
	iDigitType(aDigitType)
	{
	__ASSERT_DEBUG(aDigitType != EDigitTypeUnknown, Panic(EEgulPanicInvalidDigitType));
	__ASSERT_DEBUG(aDigitType != EDigitTypeAllTypes, Panic(EEgulPanicInvalidDigitType));
	}

void TFindWidthOfWidestDigitType::GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const
	{
	aFirstIndex='0';
	aLastIndex='9';
	}

void TFindWidthOfWidestDigitType::GetTextItem(TDes& aText, TInt aIndex) const
	{
	aText.SetLength(0);
	aText.Append(aIndex);
	NumberConversion::ConvertDigits(aText, iDigitType);
	}

//
// class TFindWidthOfWidestAmPmName
//

EXPORT_C TFindWidthOfWidestAmPmName::TFindWidthOfWidestAmPmName()
/** Default constructor. */
	{
	}

void TFindWidthOfWidestAmPmName::GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const
	{
	aFirstIndex=EAm;
	aLastIndex=EPm;
	}

void TFindWidthOfWidestAmPmName::GetTextItem(TDes& aText, TInt aIndex) const
	{
	aText=TAmPmName((TAmPm)aIndex);
	}

//
// TFindWidthOfWidestAbbreviatedDayName
//

EXPORT_C TFindWidthOfWidestAbbreviatedDayName::TFindWidthOfWidestAbbreviatedDayName()
/** Default constructor. */
	{
	}

void TFindWidthOfWidestAbbreviatedDayName::GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const
	{
	aFirstIndex=0;
	aLastIndex=6;
	}

void TFindWidthOfWidestAbbreviatedDayName::GetTextItem(TDes& aText, TInt aIndex) const
	{
	aText=TDayNameAbb((TDay)aIndex);
	}

//
// TFindWidthOfWidestDayName
//

EXPORT_C TFindWidthOfWidestDayName::TFindWidthOfWidestDayName()
/** Default constructor. */
	{
	}

void TFindWidthOfWidestDayName::GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const
	{
	aFirstIndex=0;
	aLastIndex=6;
	}

void TFindWidthOfWidestDayName::GetTextItem(TDes& aText, TInt aIndex) const
	{
	aText=TDayName((TDay)aIndex);
	}

//
// TFindWidthOfWidestAbbreviatedMonthName

EXPORT_C TFindWidthOfWidestAbbreviatedMonthName::TFindWidthOfWidestAbbreviatedMonthName()
/** Default constructor. */
	{
	}

void TFindWidthOfWidestAbbreviatedMonthName::GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const
	{
	aFirstIndex=0;
	aLastIndex=11;
	}

void TFindWidthOfWidestAbbreviatedMonthName::GetTextItem(TDes& aText, TInt aIndex) const
	{
	aText=TMonthNameAbb((TMonth)aIndex);
	}

//
// TFindWidthOfWidestMonthName
//

EXPORT_C TFindWidthOfWidestMonthName::TFindWidthOfWidestMonthName()
/** Default constructor. */
	{
	}

void TFindWidthOfWidestMonthName::GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const
	{
	aFirstIndex=0;
	aLastIndex=11;
	}

void TFindWidthOfWidestMonthName::GetTextItem(TDes& aText, TInt aIndex) const
	{
	aText=TMonthName((TMonth)aIndex);
	}

//
// TFindWidthOfWidestDateSuffix
//

EXPORT_C TFindWidthOfWidestDateSuffix::TFindWidthOfWidestDateSuffix()
/** Default constructor. */
	{
	}

void TFindWidthOfWidestDateSuffix::GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const
	{
	aFirstIndex=0;
	aLastIndex=30;
	}

void TFindWidthOfWidestDateSuffix::GetTextItem(TDes& aText, TInt aIndex) const
	{
	aText=TDateSuffix(aIndex);
	}


