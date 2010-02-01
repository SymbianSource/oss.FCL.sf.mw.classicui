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

#ifndef __GULALIGN_H__
#define __GULALIGN_H__

#include <e32std.h>
#include <e32base.h>
#include <gdi.h>
#include <biditext.h>	// enum TBidiText::TDirectionality
#include <txtfrmat.h>	// enum CParaFormat::TAlignment

/** Horizontal layout settings for graphic objects. 

@publishedAll
@released */
enum TGulHAlignment
	{
	/** Object is left-aligned. */
	EHLeft=CGraphicsContext::ELeft,
	/** Object is centred horizontally. */
	EHCenter=CGraphicsContext::ECenter,
	/** Object is right-aligned. */
	EHRight=CGraphicsContext::ERight
	};

/** Vertical layout settings for graphic objects. 

@publishedAll
@released */
enum TGulVAlignment
	{
	/** Object is aligned with the top. */
	EVTop=0x00,
	/** Object is centred vertically. */
	EVCenter=0x10,
	/** Object is aligned with the bottom. */
	EVBottom=0x20
	};

/** Alignment settings for the layout of graphic objects. 

@publishedAll
@released */
enum TGulAlignmentValue
	{
	/** Object is left and top aligned. */
	EHLeftVTop=EHLeft|EVTop,
	/** Object is left aligned and centred vertically. */
	EHLeftVCenter=EHLeft|EVCenter,
	/** Object is left aligned and at the bottom. */
	EHLeftVBottom=EHLeft|EVBottom,
	/** Object is centre aligned horizontally and at the top. */
	EHCenterVTop=EHCenter|EVTop,
	/** Object is centred horizontally and vertically. */
	EHCenterVCenter=EHCenter|EVCenter,
	/** Object is centred horizontally and at the bottom. */
	EHCenterVBottom=EHCenter|EVBottom,
	/** Object is right and top aligned. */
	EHRightVTop=EHRight|EVTop,
	/** Object is right aligned and centred vertically. */
	EHRightVCenter=EHRight|EVCenter,
	/** Object is right aligned and at the bottom. */
	EHRightVBottom=EHRight|EVBottom
	};


/** Provides a convenient way to describe horizontal and vertical layouts of rectangular 
objects and to enquire how they occupy an area given their alignment. 

@publishedAll 
@released */
class TGulAlignment
	{
private:
	enum {EHMask=0x03, EHAbsoluteFlag=0x04, EVMask=0x30};
public:
	inline TGulAlignment();
	inline TGulAlignment(TGulAlignmentValue aValue);
	inline TGulAlignment(CGraphicsContext::TTextAlign aHAlign, TGulVAlignment aVAlign = EVTop);
	IMPORT_C operator TGulAlignmentValue() const;
	inline TGulVAlignment VAlignment() const;
	inline TGulHAlignment HAlignment() const;
	IMPORT_C TGulHAlignment HAlignment(TBidiText::TDirectionality aLanguageDirectionality) const;	
	IMPORT_C TBool HasAbsoluteHAlignment() const;
	IMPORT_C void SetAbsoluteHAlignment(TBool aAbsoluteHAlignment);
	
	// Returns the horizontal text alignment. 
	inline CGraphicsContext::TTextAlign TextAlign() const;
	IMPORT_C CGraphicsContext::TTextAlign TextAlign(TBidiText::TDirectionality aLanguageDirectionality) const;
	IMPORT_C CParaFormat::TAlignment ParaAlign() const;

	IMPORT_C void SetVAlignment(TGulVAlignment aVAlign);
	IMPORT_C void SetHAlignment(TGulHAlignment aHAlign);
	IMPORT_C void SetHAlignment(CGraphicsContext::TTextAlign aHAlign);
	IMPORT_C void SetHAlignment(CParaFormat::TAlignment aHAlign);
	IMPORT_C TPoint InnerTopLeft(const TRect& aOuter, const TSize& aInnerSize) const;
	IMPORT_C TPoint InnerTopLeft(const TRect& aOuter, const TSize& aInnerSize, TBidiText::TDirectionality aLanguageDirectionality) const;
	IMPORT_C TRect InnerRect(const TRect& aOuter, const TSize& aInnerSize) const;
	IMPORT_C TRect InnerRect(const TRect& aOuter, const TSize& aInnerSize, TBidiText::TDirectionality aLanguageDirectionality) const;
private:
	TInt iValue;
	};

/** Default constructor. */
inline TGulAlignment::TGulAlignment()
	{};

/** Constructor initialising the object with an alignment value.
@param aValue The alignment value. */
inline TGulAlignment::TGulAlignment(TGulAlignmentValue aValue)
	{iValue=aValue;}
	
/** Constructor initialising the object with an alignment value.
@param aHAlign The horizontal alignment value. 
@param aVAlign The vertical alignment value. */
inline TGulAlignment::TGulAlignment(CGraphicsContext::TTextAlign aHAlign, TGulVAlignment aVAlign)
	{ iValue = static_cast<TGulAlignmentValue>(((TGulHAlignment)aHAlign) |aVAlign); }
		
/** Gets the vertical alignment. 
@return Vertical alignment. */
inline TGulVAlignment TGulAlignment::VAlignment() const
	{return((TGulVAlignment)(iValue&EVMask));}

/** Gets the absolute horizontal alignment. 

Note that this is the alignment in absolute terms. I.e. left and right 
alignment will not be swapped depending on language directionality.
@return Horizontal alignment. */
inline TGulHAlignment TGulAlignment::HAlignment() const
	{return((TGulHAlignment)(iValue&EHMask));}

/** Gets the absolute horizontal text alignment.

Note that this is the alignment in absolute terms. I.e. left and right 
alignment will not be swapped depending on language directionality.
@return The horizontal text alignment. */
inline CGraphicsContext::TTextAlign TGulAlignment::TextAlign() const
	{return((CGraphicsContext::TTextAlign)(HAlignment()));}

#endif	// __GULALIGN_H__
