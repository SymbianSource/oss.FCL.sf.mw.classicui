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

#include <gulalign.h>
#include <gulpanic.h>
#include "GULSTD.H"

#if No_Compiler_Bug
#if (EHLeft!=ELeft || EHCenter!=ECenter || EHRight!=ERight)
#error "GDI enum values have changed"
#endif
#endif


/** Gets the (absolute) alignment value as @c TGulAlignmentValue.

Note that this has the absolute horizontal alignment. I.e. left and right 
horizontal alignment will not be swapped depending on language directionality.
*/
EXPORT_C TGulAlignment::operator TGulAlignmentValue() const
	{return static_cast<TGulAlignmentValue>(iValue&(EHMask|EVMask));}


/**
Return whether horizontal alignment will be treated as an absolute value, 
or relative the specified language directionality. In the latter case, 
left and right will be swapped (by @c TGulAlignment methods for which a 
@c TBidiText::TDirectionality is provided) for languages with RightToLeft 
directionality.
*/
EXPORT_C TBool TGulAlignment::HasAbsoluteHAlignment() const
	{
	return (iValue&EHAbsoluteFlag);
	}

/**
Set the current horizontal alignment to be used as an absolute value. 
If set to true, this means that the alignment will NOT be swapped depending 
on language directionality when calling e.g. @c HAlignment(TBidiText::TDirectionality).

Note that the default is false (i.e. relative alignment), and calling any 
of the setters on the @c TGulAlignment object will reset it to relative alignment 
(i.e. always call this method after the horizontal alignment has been set).

Also note that support for absolute horizontal alignment was added to TGulAlignment
late in Symbian OS release 9.1. Hence if this method is called on an object that is 
passed to a client compiled against an earlier release (or if the client does not yet
support absolute alignment) then the resulting alignment may be incorrect. 
*/		
EXPORT_C void TGulAlignment::SetAbsoluteHAlignment(TBool aAbsoluteHAlignment)
	{
	if(aAbsoluteHAlignment)
		iValue |= EHAbsoluteFlag;
	else
		iValue &= ~EHAbsoluteFlag;
	}
	
/**
Return the horizontal alignment, relative to the language directionality specified. 
Calling this method will return a horizontal alignment where left and right has 
been swapped for any language with RightToLeft directionality, UNLESS the 
alignment has been set as being absolute, by calling @c SetAbsoluteHAlignment().

@param aLanguageDirectionality The language directionality to consider when swapping left and right.
@return The horizontal alignment, taking language directionality into account.
*/
EXPORT_C TGulHAlignment TGulAlignment::HAlignment(TBidiText::TDirectionality aApplicationLanguageDirectionality) const
	{
	if((aApplicationLanguageDirectionality == TBidiText::ERightToLeft) && !(iValue&EHAbsoluteFlag) && ((iValue&EHMask) != EHCenter))
		return ((iValue&EHMask) == EHLeft ? EHRight : EHLeft);
	else
		return static_cast<TGulHAlignment>(iValue&EHMask);		
	}

/**
Return the horizontal alignment, relative to the language directionality specified. 
Calling this method will return a horizontal alignment where left and right has 
been swapped for any language with RightToLeft directionality, UNLESS the 
alignment has been set as being absolute, by calling @c SetAbsoluteHAlignment().

@param aLanguageDirectionality The language directionality to consider when swapping left and right.
@return The horizontal alignment, taking language directionlity into account.
*/
EXPORT_C CGraphicsContext::TTextAlign TGulAlignment::TextAlign(TBidiText::TDirectionality aLanguageDirectionality) const
	{
	return static_cast<CGraphicsContext::TTextAlign>(HAlignment(aLanguageDirectionality));
	}

/**
Return the horizontal alignment as a @c CParaFormat::TAlignment object. Note that the 
@c CParaFormat::TAlignment class supports the concept of horizontal absolute alignment, 
so left and right alignment will not be swapped.

@return The horizontal alignment, including whether it's absolute or not.
*/
EXPORT_C CParaFormat::TAlignment TGulAlignment::ParaAlign() const
	{
	if(HAlignment() == EHLeft)
		return (HasAbsoluteHAlignment() ? CParaFormat::EAbsoluteLeftAlign : CParaFormat::ELeftAlign);
	else if(HAlignment() == EHRight)
		return (HasAbsoluteHAlignment() ? CParaFormat::EAbsoluteRightAlign : CParaFormat::ERightAlign);
	else 
		return CParaFormat::ECenterAlign;
	}

/** Sets the vertical alignment.

@param aVAlign The vertical alignment. */
EXPORT_C void TGulAlignment::SetVAlignment(TGulVAlignment aVAlign)
	{
	const TInt allButVAlign = iValue&(~EVMask);
	iValue = (allButVAlign|aVAlign);
	}

/** Sets the horizontal alignment. Alignment will be reset to relative. I.e. when calling
@c HAlignment() with a @c TBidiText::ERightToLeft argument, left and right will be swapped.
Calling @c HAlignment() without argument will always return the alignment in absolute terms.

@param aHAlign The horizontal alignment. */
EXPORT_C void TGulAlignment::SetHAlignment(TGulHAlignment aHAlign)
	{
	const TInt allButHAlign = iValue&(~EHMask);
	iValue = (allButHAlign|aHAlign);
	SetAbsoluteHAlignment(EFalse);	// Reset the horizintal alignment to relative app language
	}

/** Sets the horizontal alignment. Alignment will be reset to relative. I.e. when calling
@c HAlignment() with a @c TBidiText::ERightToLeft argument, left and right will be swapped.
Calling @c HAlignment() without argument will always return the alignment in absolute terms.

@param aHAlign The horizontal alignment. */
EXPORT_C void TGulAlignment::SetHAlignment(CGraphicsContext::TTextAlign aHAlign)
	{
	SetHAlignment(static_cast<TGulHAlignment>(aHAlign));	// CGraphicsContext::TTextAlign has the same values as TGulHAlignment
	// Abosolute alignment flag set to false by the call above.
	}

/** Sets the horizontal alignment. Alignment will be set to absolute for @c EAbsoluteLeftAlign 
and @c EAbsoluteRightAlign, otherwise relative the language directionality (if specified).

@param aHAlign The horizontal alignment. */
EXPORT_C void TGulAlignment::SetHAlignment(CParaFormat::TAlignment aHAlign)
	{
	const TInt allButHAlign = iValue&(~EHMask);
	
	switch(aHAlign)
		{
	case CParaFormat::ELeftAlign:
		iValue = (allButHAlign|EHLeft);
		SetAbsoluteHAlignment(EFalse);
		break;
	case CParaFormat::ERightAlign:
		iValue = (allButHAlign|EHRight);
		SetAbsoluteHAlignment(EFalse);
		break;
	case CParaFormat::EAbsoluteLeftAlign:
		iValue = (allButHAlign|EHLeft);
		SetAbsoluteHAlignment(ETrue);
		break;
	case CParaFormat::EAbsoluteRightAlign:
		iValue = (allButHAlign|EHRight);
		SetAbsoluteHAlignment(ETrue);
		break;
	default:
		__ASSERT_DEBUG(0, Panic(EEgulPanicCParaFormatAlignementValueNotSupported));
		}
	}


/** Gets the co-ordinates of the top left corner of an object of size @c aInnerSize, 
which is placed in the area of the rectangle @c aOuter according to the current 
alignment. 

Note that horizontal alignment is always treated as being in absolute terms.

@param aOuter The outer rectangle.
@param aInnerSize The size of the inner rectangle.
@return The inner top left point. */
EXPORT_C TPoint TGulAlignment::InnerTopLeft(const TRect& aOuter,const TSize& aInnerSize) const
	{
	return InnerTopLeft(aOuter, aInnerSize, TBidiText::ELeftToRight);
	}

/** Gets the co-ordinates of the top left corner of an object of size @c aInnerSize, 
which is placed in the area of the rectangle @c aOuter according to the current 
alignment. 

Note that if RightToLeft language directionality is specified, left and right horizontal 
alignment for the inner object will be swapped.

@param aOuter The outer rectangle.
@param aInnerSize The size of the inner rectangle.
@param aLanguageDirectionality The language directionality to consider when swapping left and right.
@return The inner top left point. */
EXPORT_C TPoint TGulAlignment::InnerTopLeft(const TRect& aOuter, const TSize& aInnerSize, TBidiText::TDirectionality aLanguageDirectionality) const
	{
	TSize delta = aOuter.Size()-aInnerSize;
	switch (HAlignment(aLanguageDirectionality))
		{
	case EHLeft:
		delta.iWidth=0;
		break;
	case EHCenter:
		delta.iWidth>>=1; 	// div 2
		break;
	default:
		break;
		}
		
	switch (VAlignment())
		{
	case EVTop:
		delta.iHeight=0;
		break;
	case EVCenter:
		delta.iHeight>>=1;	// div 2
		break;
	default:
		break;
		}
	
	return(aOuter.iTl+delta);
	}

/** Gets the rectangle occupied by an object of size @c aInnerSize, which is placed 
in the area of the rectangle @c aOuter according to the current alignment.

Note that horizontal alignment is always treated as being in absolute terms.

@param aOuter The outer rectangle.
@param aInnerSize The size of the inner rectangle.
@return The rectangle. */
EXPORT_C TRect TGulAlignment::InnerRect(const TRect& aOuter, const TSize& aInnerSize) const
	{
	return InnerRect(aOuter, aInnerSize, TBidiText::ELeftToRight);
	}

/** Gets the rectangle occupied by an object of size @c aInnerSize, which is placed 
in the area of the rectangle @c aOuter according to the current alignment.

Note that if RightToLeft language directionality is specified, left and right horizontal 
alignment for the inner object will be swapped.

@param aOuter The outer rectangle.
@param aInnerSize The size of the inner rectangle.
@param aLanguageDirectionality The language directionality to consider when swapping left and right.
@return The rectangle. */
EXPORT_C TRect TGulAlignment::InnerRect(const TRect& aOuter, const TSize& aInnerSize, TBidiText::TDirectionality aLanguageDirectionality) const
	{
	const TSize outerSize = aOuter.Size();
	TSize clippedInner = aInnerSize;
	if (clippedInner.iWidth > outerSize.iWidth)
		clippedInner.iWidth = outerSize.iWidth;
	
	if (clippedInner.iHeight > outerSize.iHeight)
		clippedInner.iHeight = outerSize.iHeight;
	
	return(TRect(InnerTopLeft(aOuter,clippedInner,aLanguageDirectionality), clippedInner));
	}


