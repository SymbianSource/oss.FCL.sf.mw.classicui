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


#include <lafmain.h>
#include <coecntrl.h>
#include <AknsUtils.h>

EXPORT_C CLafEdwinCustomDrawBase* CLafEdwinCustomDrawBase::NewL(const MLafEnv& aEnv,const CCoeControl& aControl)
	{ // static
	return new(ELeave) CLafEdwinCustomDrawBase(aEnv,aControl);
	}

EXPORT_C void CLafEdwinCustomDrawBase::DrawBackground(const TParam& aParam,const TRgb& /*aBackground*/,TRect& aDrawn) const
	{
	aParam.iGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	aParam.iGc.SetPenStyle(CGraphicsContext::ESolidPen);
	TRgb color=(iControl.IsDimmed()? iEnv.ControlColor(EColorControlDimmedBackground,iControl) :
									iEnv.ControlColor(EColorControlBackground,iControl));
	aParam.iGc.SetBrushColor(color);
	aParam.iGc.SetPenColor(color);
	aParam.iGc.DrawRect(aParam.iDrawRect);
	aDrawn=aParam.iDrawRect;

	}

EXPORT_C TRgb CLafEdwinCustomDrawBase::SystemColor(TUint /* aColorIndex */,TRgb aDefaultColor) const
	{
    return aDefaultColor;
	}

EXPORT_C void CLafEdwinCustomDrawBase::LineSpacingChanged()
	{
	}

EXPORT_C CLafEdwinCustomDrawBase::CLafEdwinCustomDrawBase(const MLafEnv& aEnv,const CCoeControl& aControl)
	: iEnv(aEnv), iControl(aControl)
	{}

EXPORT_C CLafEdwinCustomWrapBase* CLafEdwinCustomWrapBase::NewL(const CCoeControl& aControl)
/**
@publishedPartner
@test
*/
	{
	// static 
	return new (ELeave) CLafEdwinCustomWrapBase(aControl);
	}

EXPORT_C CLafEdwinCustomWrapBase::~CLafEdwinCustomWrapBase()
/**
@publishedPartner
@test
*/
	{
	}

/**
Returns the line break class for a character. 
Return the range of characters including aCode that are known to share this range.

The custom wrapping interface returns the default implementation. The overriding implementation 
could return different value to perform custom line break. 

*/
EXPORT_C TUint CLafEdwinCustomWrapBase::LineBreakClass(TUint aCode,TUint& aRangeStart,TUint& aRangeEnd) const
/**
@publishedPartner
@test
*/
	{
	TUint temp; 
	temp = MFormCustomWrap::LineBreakClass(aCode,aRangeStart,aRangeEnd);
	return temp;
	}
/**
Return TRUE if a line break is possible between characters of the two specified classes.
If aHaveSpaces is TRUE, one or more characters in ESpLineBreakClass was found between the characters
in the two specified classes.

For the custom implementation here, returns true everytime, ie a line break is possible
anywhere. This allows the edwin to break a line anywhere, thus eliminating the jagged
white space at the right hand side of the edwin window. 
*/
EXPORT_C TBool CLafEdwinCustomWrapBase::LineBreakPossible(TUint /*aPrevClass*/,TUint /*aNextClass*/,TBool /*aHaveSpaces*/) const
/**
@publishedPartner
@test
*/
	{
	return ETrue;
	}

/**
Return the first (if aForwards is TRUE) or last (if aForwards is FALSE) linebreak in aText,
This must be in the range aMinBreakPos...aMaxBreakPos, which is a run of characters in the
class ESaLineBreakClass, usually employed for Thai, Lao and Khmer
letters, because these scripts don't use word spaces and need dictionary-based line breaking.
The break position is returned in aBreakPos, which must be > 0 and < aText.Length() - 1.
Return TRUE if a break is found, FALSE otherwise.
*/
EXPORT_C TBool CLafEdwinCustomWrapBase::GetLineBreakInContext(const TDesC& aText,TInt aMinBreakPos,TInt aMaxBreakPos,TBool aForwards,TInt& aBreakPos) const
/**
@publishedPartner
@test
*/
	{
	TBool temp;
	temp = MFormCustomWrap::GetLineBreakInContext(aText,aMinBreakPos,aMaxBreakPos,aForwards,aBreakPos);
	return temp;
	}

// Return TRUE if this character can overhang the measured right end of the line.
EXPORT_C TBool CLafEdwinCustomWrapBase::IsHangingCharacter(TUint aChar) const
/**
@publishedPartner
@test
*/
	{
	TBool temp;
	temp = MFormCustomWrap::IsHangingCharacter(aChar);
	return temp;
	}

EXPORT_C void CLafEdwinCustomWrapBase::MFormCustomWrap_Reserved_1()
/**
@publishedPartner
@test
*/
	{
	// reserved functions, private until used
	}

EXPORT_C void CLafEdwinCustomWrapBase::MFormCustomWrap_Reserved_2()
/**
@publishedPartner
@test
*/
	{
	// reserved functions, private until used
	}


EXPORT_C CLafEdwinCustomWrapBase::CLafEdwinCustomWrapBase(const CCoeControl& aControl):iControl(aControl)
/**
@publishedPartner
@test
*/
	{
	}


