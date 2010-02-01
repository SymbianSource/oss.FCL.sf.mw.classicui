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

#ifndef __LAFMAIN_H__
#define __LAFMAIN_H__

#include <e32std.h>
#include <e32base.h>
#include <gulbordr.h>
#include <gulcolor.h>
#include <frmtlay.h>

class CCoeControl;
class CFont;
class TLogicalFont;
class MLafEnv;


class CLafEdwinCustomDrawBase : public CBase, public MFormCustomDraw
/** LAF support for custom drawing of Edwins.

This class is used by CEikEdwin to draw lines in plain text editors. It does 
not work in rich text editors, as it assumes the line spacing is constant.

The custom drawing interface is defined by the MFormCustomDraw class. 

@publishedPartner
@released */
	{
public:
	/** Allocates and constructs the custom drawer.
	
	@param aEnv LAF environment functions
	@param aControl The Edwin control
	@return New custom drawer */
	IMPORT_C static CLafEdwinCustomDrawBase* NewL(const MLafEnv& aEnv,const CCoeControl& aControl);
public: // from MFormCustomDraw
	/** Implements MFormCustomDraw::DrawBackground() to draw the Edwin background. 
	
	See that function for a full description.
	
	@param aParam Drawing parameters
	@param aBackground Default background colour
	@param aDrawn On return, the rectangle to which the function has drawn */
	IMPORT_C void DrawBackground(const TParam& aParam,const TRgb& aBackground,TRect& aDrawn) const;
	/** Gets the physical colour that maps to a specified logical colour.
	
	@param aColorIndex Logical colour
	@param aDefaultColor The default physical colour. This is the colour to be 
	used if no translation is performed. This allows translation to change certain 
	indices but not others ( by passing the default colour back unchanged).
	@return Physical colour */
	IMPORT_C TRgb SystemColor(TUint aColorIndex,TRgb aDefaultColor) const;
public:
	/** Notifies the drawer that a MEikEdwinObserver::EEventFormatChanged event has 
	occurred for the Edwin. */
	IMPORT_C virtual void LineSpacingChanged();
protected:
	/** Constructor that initialises data members.
	
	@param aEnv LAF environment functions
	@param aControl The Edwin control */
	IMPORT_C CLafEdwinCustomDrawBase(const MLafEnv& aEnv,const CCoeControl& aControl);
protected:
	/** LAF environment functions
	
	This is initialised by the constructor. */
	const MLafEnv& iEnv;
	/** The Edwin control. 
	
	This is initialised by the constructor. */
	const CCoeControl& iControl;
private:
	/** Unused. */
	TInt iSpare;
	};


class CLafEdwinCustomWrapBase : public CBase, public MFormCustomWrap
/** LAF support for custom line breaking in Edwins.

This class is used by CEikEdwin to determine how to place line breaks.

The custom line breaking interface is defined by the MFormCustomWrap class. 

@publishedPartner
@released */
	{
public:
	/** Allocates and constructs the custom line breaker.
	
	@param aControl The Edwin control
	@return The new line breaker */
	IMPORT_C static CLafEdwinCustomWrapBase* NewL(const CCoeControl& aControl);
	/** Destructor. */
	IMPORT_C ~CLafEdwinCustomWrapBase();
public: // from MFormCustomWrap
	/** Gets the line break class for a Unicode character.
	
	This implements MFormCustomWrap::LineBreakClass().
	
	@param aCode The Unicode character code
	@param aRangeStart On return, contains the Unicode character code at the start 
	of the range including aCode that shares the same line break class as aCode.
	@param aRangeEnd On return, contains the Unicode character code at the end 
	of the range including aCode that shares the same line break class as aCode
	@return The line break class assigned to the character. Line break classes 
	are enumerated with MTmCustom::EOpLineBreakClass etc. */
	IMPORT_C TUint LineBreakClass(TUint aCode,TUint& aRangeStart,TUint& aRangeEnd) const;
	/** Tests whether a line break is possible between two characters.
	
	This implements MFormCustomWrap::LineBreakPossible().
	
	@param aPrevClass The line break class of the previous non-space character. 
	@param aNextClass The line break class of the next non-space character. 
	@param aHaveSpaces True if there are one or more space characters (with a line 
	break class of MTmCustom::ESpLineBreakClass) between aPrevClass and aNextClass; 
	false if not.
	@return ool True if a line break is possible between characters with the two 
	line break classes, false if not */
	IMPORT_C TBool LineBreakPossible(TUint aPrevClass,TUint aNextClass,TBool aHaveSpaces) const;
	/** Gets the position of the first or last possible line break position in a text 
	string.
	
	This implements MFormCustomWrap::GetLineBreakInContext().
	
	@param aText A string containing characters of class MTmCustom::ESaLineBreakClass. 
	
	@param aMinBreakPos A position within aText at which to begin searching for 
	a possible line break position. 
	@param aMaxBreakPos A position within aText at which to stop searching for 
	a possible line break position. 
	@param aForwards If ETrue, the function gets the first possible line break 
	position (searches forwards from aMinBreakPos); if EFalse, gets the last one 
	(searches backwards from aMaxBreakPos). 
	@param aBreakPos On return, the position of the first or last possible line 
	break within aText. This must be greater than zero and less than aText.Length() 
	- 1, and must also be in the range aMinBreakPos to aMaxBreakPos. 
	@return True if a possible line break position is found, false if not */
	IMPORT_C TBool GetLineBreakInContext(const TDesC& aText,TInt aMinBreakPos,TInt aMaxBreakPos,TBool aForwards,TInt& aBreakPos) const;
	/** Tests whether a character can overhang the right margin.
	
	@param aChar The Unicode character code of interest
	@return True if the character specified can overhang the right margin, false 
	if not */
	IMPORT_C TBool IsHangingCharacter(TUint aChar) const;
private:
	/** Unused. */
	IMPORT_C void MFormCustomWrap_Reserved_1();
	/** Unused. */
	IMPORT_C void MFormCustomWrap_Reserved_2();	

protected:
	/** Constructor.
	
	@param aControl The Edwin control */
	IMPORT_C CLafEdwinCustomWrapBase(const CCoeControl& aControl);
protected:	
	/** The Edwin control, initialised by the constructor. */
	const CCoeControl& iControl;
private:
	/** Unused. */
	TInt iSpare;
	};

class MLafEnv
/** LAF interface to access the current system environment settings.

It is implemented by the Uikon Core, and effectively allows the LAF 
limited access to the current thread's CEikonEnv.

@publishedPartner 
@released 
*/
	{
public:
	/** Gets the environment's nearest match to the specified logical font.

	The return value is never NULL.

	@param aLogicalFont Logical font to match.
	@return The font that most closely matches aLogicalFont. */
	virtual const CFont* Font(const TLogicalFont& aLogicalFont) const=0;

	/** Gets an environment bitmap specified by UID. 

	@param aBmpUid The UID of the bitmap to retrieve.
	@return The bitmap. */
	virtual const CFbsBitmap* Bitmap(TUid aBmpUid) const=0;

	/** Gets the physical (TRgb) colour that corresponds to the specified 
	logical colour, for a specified control.

	@param aLogicalColor Logical colour.
	@param aControl Control for which to get the mapping. Note controls can override 
	the system mappings.
	@return Physical colour. */
	virtual TRgb ControlColor(TLogicalColor aLogicalColor, const CCoeControl& aControl) const=0;

	/** Gets the environment's physical (TRgb) colour that corresponds to 
	the specified logical colour.

	@param aLogicalColor Logical colour.
	@param aColorListUid UID of the colour list from which to get the mapping. The default 
	value is the environment's list.
	@return Physical colour. */
	virtual TRgb Color(TLogicalColor aLogicalColor, TUid aColorListUid=KNullUid) const=0;

	/** Gets the environment setting for the default display mode.

	@return Display mode. */
	virtual TDisplayMode DefaultDisplayMode() const=0; 
	};

class MLafClientRectResolver
/** Interface that works out how screen furniture reduces the available screen area 
for applications.

The interface is implemented by the UI and can be called by the LAF to get information 
on the areas of screen furniture.

@see LafAppUi::ClientRect() 
@publishedPartner
@released */
	{
public:
	/** Flags for types of screen furniture. */
	enum TScreenFurniture
		{ 
		/** Menu bar. */
		EMenuBar, 
		/** Button group. */
		EButtonGroup, 
		/** Tool band. */
		EToolBand, 
		/** Title band. */
		ETitleBand, 
		/** Status pane. */
		EStatusPane,
		/** Command Button Array */
		ECba
		};
public:
	/** Calculates how a specified type of screen furniture reduces the application 
	area of a specified screen rectangle. 

	@param aScreenFurniture Type of screen furniture.
	@param aRect Screen rectangle from which to remove area of specified furniture. 
	On return, the modified rectangle. */
	virtual void ReduceRect(TScreenFurniture aScreenFurniture,TRect& aRect) const=0;
	};

#endif //__LAFMAIN_H__
