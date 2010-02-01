// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Tests border drawing using border colour & style.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/
#include <e32keys.h>
#include <basched.h>
#include <gdi.h>
#include <gulutil.h>
#include <gulbordr.h>
#include <coecntrl.h>
#include <coeutils.h>

#include <eikenv.h>
#include <eikappui.h>
#include <eikdef.h>
#include <eikdoc.h>
#include <eikapp.h>
#include <ecom/ecom.h>


#include "tbrdrcol.h"


//#define FORCE_AUTO

//
// This test code exercises the EGUL border colors utilities.
//
//


const TInt KMaxNumAttempt = 30;  // change color

//const TInt KMaxBufLength = 40;

const TUint8 color256darklutab[256] = {
	0,	0,	0,	1,	2,	3,	
	0,	0,	0,	1,	2,	3,	
	0,	0,	0,	1,	2,	3,	
	6,	6,	6,	7,	8,	9,	
	12,	12,	12, 13,	14,	15,	
	18,	18,	18, 19,	20,	21,	

	0,	0,	0,	1,	2,	3,	
	0,	0,	0,	1,	2,	3,	
	0,	0,	0,	1,	2,	3,	
	6,	6,	6,	7,	8,	9,	
	12,	12,	12, 13,	14,	15,	
	18,	18,	18, 19,	20,	21,	

	0,	0,	0,	1,	2,	3,	
	0,	0,	0,	1,	2,	3,	
	0,	0,	0,	1,	2,	3,	
	6,	6,	6,	7,	8,	9,	
	12,	12,	12, 13,	14,	15,	
	18,	18,	18, 19,	20,	21,	

/*
	0,	0,	1,	2,	3,	4,
	0,	0,	1,	2,	3,	4,
	0,	0,	1,	2,	3,	4,
	6,	6,	7,	8,	9,	10,
	12,	12,	13,	14,	15,	16,
	18,	18,	19,	20,	21,	22,
*/
	0, 0, 108, 109, 110,
	0, 0, 113, 114, 115,
	0, 0, 118, 119, 120,
	0, 0, 123, 124, 125,

	126, 127, 128, 129, 130,
	121, 122, 133, 134, 135,
	116, 117, 138, 139, 140,
	111, 112, 143, 144, 145,

	36,	36,	36,	37,	38,	39,
	36,	36,	36,	37,	38,	39,
	36,	36,	36,	37,	38,	39,
	42,	42,	42,	43,	44,	45,
	48,	48,	48,	49,	50,	51,
	54,	54,	54,	55,	56,	57,

	72,	72,	72,	73,	74,	75,
	72,	72,	72,	73,	74,	75,
	72,	72,	72,	73,	74,	75,
	78,	78,	78,	79,	80,	81,
	84,	84,	84,	85,	86,	87,
	90,	90,	90,	91,	92,	93,

	148, 148,  148, 149, 150, 151, 
	148, 148,  148, 149, 150, 151, 
	148, 148,  148, 149, 150, 151, 
	154, 154,  154, 155, 156, 157, 
	160, 160,  160, 161, 162, 163, 
	166, 166,  166, 167, 168, 169
};

const TUint8 color256lightlutab[256] = {
	43,	44,	45,	46,	47,	47,
	49,	50,	51,	52,	53,	53,
	55,	56,	57,	58,	59,	59,
	61,	62,	63,	64,	65,	65,
	67,	68,	69,	70,	71,	71,
	67,	68,	69,	70,	71,	71,

	79,   80,  81,  82,  83,  83,
	85,   86,  87,  88,  89,  89,
	91,	  92,  93,  94,	 95,  95,
	97,	  98,  99, 100,	101, 101,
	103, 104, 105, 106, 107, 107,
	103, 104, 105, 106, 107, 107,

	155, 156, 157, 158,	159, 159,
	161, 162, 163, 164,	165, 165,
	167, 168, 169, 170,	171, 171,
	173, 174, 175, 176,	177, 177,
	179, 180, 181, 182,	183, 183,
	179, 180, 181, 182,	183, 183,

	110, 111, 112, 143, 144,
	115, 116, 117, 138, 139,
	120, 121, 122, 133, 134,
	125, 126, 127, 128, 129,

	130, 131, 132, 132, 220,
	135, 136, 137, 137, 030,
	140, 141, 142, 142, 005,
	145, 146, 147, 147, 255,

	191, 192, 193, 194,	195, 195,
	197, 198, 199, 200,	201, 201,
	203, 204, 205, 206,	207, 207,
	209, 210, 211, 212,	213, 213,
	215, 216, 217, 218,	219, 219,
	215, 216, 217, 218,	219, 219,

	227, 228, 229, 230, 231, 231,
	233, 234, 235, 236, 237, 237,
	239, 240, 241, 242, 243, 243,
	245, 246, 247, 248, 249, 249,
	251, 252, 253, 254, 147, 255,
	251, 252, 253, 254, 255, 255,

	227, 228, 229, 230, 231, 231,
	233, 234, 235, 236, 237, 237,
	239, 240, 241, 242, 243, 243,
	245, 246, 247, 248, 249, 249,
	251, 252, 253, 254, 255, 255,
	251, 252, 253, 254, 255, 255
	};




inline THsl::THsl() : iValue(0x00ffffff)
/**
 * Constructor
 */
{
}

inline THsl::THsl(TUint32 aValue) : iValue(aValue)
/**
   Overloaded Constructor
 */
{
}

inline THsl::THsl(TInt aHue,TInt aSaturation,TInt aLumen) : iValue( aHue | aSaturation << 8 | aLumen << 16 )
/**
   Overloaded Constructor
 */
{
}

/**
   Auxilliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method returns hue factor from HSL model colour format.
  
 */
inline TInt THsl::Hue() const
{
	return (iValue & 0xff);
}

/**
   Auxilliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method returns saturation factor from HSL model colour format.
  
 */
inline TInt THsl::Saturation() const
{
	return ((iValue & 0xff00) >> 8);
}

/**
   Auxilliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
 
   This method returns lumen factor from HSL model colour format.
  
 */
inline TInt THsl::Lumen() const
{
	return ((iValue & 0xff0000) >> 16);
}

/**
   Auxilliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method sets hue factor on HSL model colour format.
  
 */
void THsl::SetHue(TInt aRed)
{
	iValue &= 0xffffff00;
	iValue |= (aRed & 0xff);
}

/**
   Auxilliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method sets saturation factor on HSL model colour format.
  
 */
void THsl::SetSaturation(TInt aSaturation)
{
	iValue &= 0xffff00ff;
	iValue |= (aSaturation & 0xff) << 8;
}

/**
   Auxilliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method sets lumen factor on HSL model colour format.
  
 */
void THsl::SetLumen(TInt aLumen)
{
	iValue &= 0xff00ffff;
	iValue |= (aLumen & 0xff) << 16;
}

/**
   Auxilliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method converts a TRgb colour HSL format.
  
 */
THsl ColorConverter::RgbToHsl(TRgb aRgb)
	{
	const TInt r = aRgb.Red();
	const TInt g = aRgb.Green();
	const TInt b = aRgb.Blue();
	
	const TInt cmax = Max(r, Max(g,b));
	const TInt cmin = Min(r, Min(g,b));
	
	TInt h = 0;
	TInt l = (cmax + cmin) >> 1; // Divided with 2
	TInt s = 0;
	
	if (cmax==cmin) 
		{
		s = 0;
		h = 0; // it's really undefined
		} 
	else 
		{
		if ( l < (255/2) )
			{
			s = ((cmax-cmin)*255)/(cmax+cmin);
			}
		else
			{
			s = ((cmax-cmin)*255)/((2*255)-cmax-cmin);
			}
		
		TInt delta = cmax - cmin;
		
		if (r==cmax)
			{
			h = ((g-b)*255) / delta;
			}
		else if (g==cmax)
			{
			h = 2*255 + ((b-r)*255) / delta;
			}
		else
			{
			h = 4*255 + ((r-g)*255) / delta;
			}
		
		h /= 6;
		
		if (h<0)
			{
			h += (1*255);
			}
		}
	
	return THsl(h, s, l);
	}


/**
   Auxilliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method converts a HSL colour to TRgb format.
  
 */
TRgb ColorConverter::HslToRgb(THsl aHsl)
	{
	TInt r, g, b;
	TInt m1, m2;
	
	const TInt hue = aHsl.Hue();
	const TInt sat = aHsl.Saturation();
	const TInt lum = aHsl.Lumen();
	
	if (sat==0) 
		{
		r=g=b=lum;
		} 
	else 
		{
		if (lum<=(255/2))
			{
			m2=lum*(255+sat)/255;
			}
		else
			{
			m2=lum+sat-(lum*sat/255);
			}
		
		m1=2*lum-m2;
		
		r = HueToRgb(m1, m2, hue+255/3 );
		g = HueToRgb(m1, m2, hue );
		b = HueToRgb(m1, m2, hue-255/3 );
		}
	
	return TRgb(r, g, b);
	}
/**
   Auxilliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method returns a colour in TRgb format based on hue factor in HSL format.
  
 */
TInt ColorConverter::HueToRgb(TInt aM1, TInt aM2, TInt aHue)
	{
	if (aHue<0) 
		aHue += 255;
	
	if (aHue>255) 
		aHue -= 255;
	
	if (6*aHue<255)
		return ( aM1 + ( (aM2-aM1)*aHue*6)/255 );
	
	if (2*aHue<255)
		return aM2;
	
	if (3*aHue<2*255)
		return ( aM1 +  ( (aM2-aM1) * (2*255/3-aHue)*6 )/255 );
	
	return aM1;
	}


CSimpleControl::CSimpleControl( CTmsTestStep* aStep )
/**
   Constructor
 */
:
	iStep( aStep )
	{
	}


CSimpleControl::~CSimpleControl()
/**
   Destructor
 */
	{
	}

/**
   Auxiliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   The method draws colour blocks by refering to look up tables for
   darker & lighter tones  to create the 256 mode colour cube columns .
  
 */
TPoint CSimpleControl::DrawColorBlocks(const TPoint& startPoint, TInt startIndex, TInt numRows, TInt numCols) const
	{
	CWindowGc& gc = SystemGc();

	TInt yPos = startPoint.iY;
	TInt xPos = startPoint.iX;
	TInt maxXPos = xPos;
	const TInt yInc = KBlockHeight;
	const TInt xInc = KBlockWidth;

	TInt index = startIndex;
	for(TInt jj=0;jj<numRows;jj++)
		{
		for(TInt ii=0;ii<numCols;ii++)
			{
			TRect rect(TPoint(xPos,yPos),TSize(KBlockWidth,KBlockHeight));
			TRgb dohCol = TRgb::Color256(color256darklutab[index]);

			gc.SetBrushColor(dohCol);
			gc.DrawRect(rect);
				
			xPos+=xInc-1;

			dohCol = TRgb::Color256(index);

			rect = TRect(TPoint(xPos,yPos),TSize(KBlockWidth,KBlockHeight));
			gc.SetBrushColor(dohCol);
			gc.DrawRect(rect);
				
			xPos+=xInc-1;

			dohCol = TRgb::Color256(color256lightlutab[index]);

			rect = TRect(TPoint(xPos,yPos),TSize(KBlockWidth,KBlockHeight));
			gc.SetBrushColor(dohCol);
			gc.DrawRect(rect);
				
			xPos+=xInc;

			index++;
			}
			maxXPos=Max(xPos,maxXPos);
			xPos-=numCols*(3*xInc-2);
			yPos+=yInc;
		}

	return TPoint(maxXPos,yPos);
	}

/**
   Auxiliary function for all Test Cases
  
   This method creates the user interface control on which tests are carried
   out.
   
 */
void CSimpleControl::ConstructL()
    {
	iNeutralColor=iEikonEnv->ControlColor(EColorWindowBackground,*this);
	iColCubeIndex=0;
    CreateWindowL();
    Window().SetShadowDisabled(ETrue);
    SetExtentToWholeScreen();
    ActivateL();
	}

/**
   Auxiliary function for all Test Cases
  
   This method returns a TRgb colour which is a darker tone of colour aColor.
   
 */
TRgb CSimpleControl::DarkRgb(TRgb aColor) const
	{
	TInt value = aColor.Value();

	TInt r = Max(0,((value & 0x000000ff)  ) - 85);
	TInt g = Max(0,((value & 0x0000ff00)  >> 8) - 85);
	TInt b = Max(0,((value & 0x00ff0000)  >> 16) - 85);

	return TRgb(r,g,b);
	}

/**
   Auxiliary function for all Test Cases
  
   This method returns a TRgb colour which is a lighter tone of colour aColor.
   
 */
TRgb CSimpleControl::LightRgb(TRgb aColor) const
	{
	TInt value = aColor.Value();

	TInt r = Min(255,((value & 0x000000ff)  ) + 30);
	TInt g = Min(255,((value & 0x0000ff00)  >> 8) + 30);
	TInt b = Min(255,((value & 0x00ff0000)  >> 16) + 30);

	return TRgb(r,g,b);
	}


/**
   @SYMTestCaseID UIF-tbrdrcol-DrawNormalBackgroundNow
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test border colour & style against white background.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method sets background colour to be white and tests
   border drawing with border colour & style. The test is carried out for
   RGB & HSL Algorithms and by setting border colours picked from the look up
   table. This test invokes the Draw() method which draws the control.
  
   @SYMTestExpectedResults The test should draw border with the colour & styles
   as expected.
   
 */
void CSimpleControl::DrawNormalBackgroundNow()
	{
	iNeutralColor = iEikonEnv->ControlColor(EColorWindowBackground,*this);
	DrawNow();
	}

/**
   @SYMTestCaseID UIF-tbrdrcol-DrawColorCubeBackgroundNow
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test border colour & style.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method sets the different background colours and tests
   border drawing with border colour & style. The test is carried out for
   RGB & HSL Algorithms and by setting border colours picked from the look up
   table. This test invokes the Draw() method which draws the control.
  
   @SYMTestExpectedResults The test should draw border with the colour & styles
   as expected.
   
 */
void CSimpleControl::DrawColorCubeBackgroundNow()
	{
	iNeutralColor = TRgb::Color256(iColCubeIndex);
	DrawNow();
	}

/**
   Auxilliary function for all Test Cases
  
   This method is an override from CCoeControl. It is used to handle key
   events for the control.
  
 */
TKeyResponse CSimpleControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType!=EEventKey)
        return(EKeyWasNotConsumed);
    TInt code=aKeyEvent.iCode;
    if (code==CTRL('e'))
		{
        CBaActiveScheduler::Exit();
		}
	else if (code==CTRL('b'))
		{
		DrawNormalBackgroundNow();
		}
	else if (code==CTRL('u'))
		{
		iColCubeIndex = ( iColCubeIndex + 1 ) % 255;
        DrawColorCubeBackgroundNow();
		}
	else if (code==CTRL('d'))
		{
		iColCubeIndex = ( iColCubeIndex - 1 ) % 255;
        DrawColorCubeBackgroundNow();
		}
    return(EKeyWasConsumed);
    }

const TInt KXStart = 10;
const TInt KYStart = 10;

const TInt KYTextStart = 22;

const TInt KWidth = 30;
const TInt KHeight = 20;

const TInt KXSpacing = 10;
const TInt KYSpacing = 5;

const TInt KXTextWidth = 60;

/**
   Auxiliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   The method draws the border for the rectangle to be drawn on the Window Gc
   of the control using the border colour specified by aColors.
  
 */
void CSimpleControl::DrawBorder(const TGulBorder& aBorder,CGraphicsContext& aGc,const TRect& aOuterRect,const TGulBorder::TColors& aColors) const
	{
	aBorder.Draw(aGc,aOuterRect,aColors);
	}

/**
   Auxiliary function for all Test Cases
  
   The method draws the border for the rectangle to be drawn on the Window Gc
   of the control using the border colour returned by RGBBorderColors() method.
  
 */
void CSimpleControl::DrawSoftBorder(const TGulBorder& aBorder,CGraphicsContext& aGc,const TRect& aOuterRect) const
	{
	aBorder.Draw(aGc,aOuterRect,RGBBorderColors());
	}

/**
   Auxiliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method draws the text aText after clipping it to fit available space.
  
 */
void CSimpleControl::DrawClippedText(CWindowGc& aGc,const TDesC& aText,const TPoint& aPoint) const
	{
	TRAPD(err,		//TRAPD is used to stop leavescan error occurring. 
		HBufC* text=HBufC::NewLC(1024);
		TPtr textPointer=text->Des();
		textPointer.Format(aText);
		TextUtils::ClipToFit(textPointer, *(iEikonEnv->AnnotationFont()), KXTextWidth);
		aGc.DrawText(textPointer,aPoint);
		CleanupStack::PopAndDestroy(); // text
		);
	__ASSERT_ALWAYS(!err,User::Panic(_L("DrawClippedText"),err));
	}

/**
   Auxiliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method is an overridde from CCoeControl to draw the control. It draws
   256 mode colour cube columns which represent the Look up table for darker
   & lighter tones. It is also used to test border colour & style when used
   with RGB and HSL Algorithms or when used by setting border colours
   picked from the look up table.
  
 */
void CSimpleControl::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(iNeutralColor);
	gc.DrawRect(Rect());

	gc.UseFont(iEikonEnv->AnnotationFont());

	TInt yPos = KYStart;
	TInt xPos = KXStart;

	TInt yTextPos = KYTextStart;
	
	const TInt yInc = KHeight+KYSpacing;
	const TInt xInc = KWidth+KXSpacing;

	//
	// 256 Mode Color Cube Columns 
	//

	TPoint newPoint=DrawColorBlocks(TPoint(xPos,yPos),0,6,6);

	yPos = newPoint.iY;

	newPoint=DrawColorBlocks(TPoint(xPos,yPos),36,6,6);

	yPos = newPoint.iY;

	newPoint=DrawColorBlocks(TPoint(xPos,yPos),72,6,6);	

	xPos = newPoint.iX+KXSpacing;
	yPos = KYStart;

	newPoint=DrawColorBlocks(TPoint(xPos,yPos),108,4,5);
	
	yPos = newPoint.iY;

	newPoint=DrawColorBlocks(TPoint(xPos,yPos),128,4,5);	

	xPos = newPoint.iX+KXSpacing;
	yPos = KYStart;

	newPoint=DrawColorBlocks(TPoint(xPos,yPos),148,6,6);

	yPos = newPoint.iY;

	newPoint=DrawColorBlocks(TPoint(xPos,yPos),184,6,6);

	yPos = newPoint.iY;

	newPoint=DrawColorBlocks(TPoint(xPos,yPos),220,6,6);	

	
	//
	// Set up for next columns
	//

	xPos = newPoint.iX+KXSpacing;
	yPos = KYStart;

	TGulBorder::TColors borderColors;
	TInt numGrays=0;
	TInt numColors=0;
	TDisplayMode displayMode=iEikonEnv->WsSession().GetDefModeMaxNumColors(numColors,numGrays);

	//
	// RGB Algorithm Test Column
	//

	yPos = KYStart;
	yTextPos = KYTextStart;

	gc.SetPenColor(KRgbBlack);
	DrawClippedText(gc,_L("RGB Algorithm"),TPoint(xPos,yTextPos));
		
	yTextPos+=yInc;
	yPos+=yInc;
	ColorUtils::GetRgbDerivedBorderColors(borderColors,iNeutralColor,displayMode);
	

	DrawBorderColors(TPoint(xPos,yPos),borderColors);

	yTextPos+=yInc;
	yPos+=yInc;

	DrawSampleBorders(TPoint(xPos,yPos),borderColors);

	//
	// Lookup Table Test Column
	//

	yPos = KYStart;
	yTextPos = KYTextStart;
	xPos+=3*xInc;

	gc.SetPenColor(KRgbBlack);
	DrawClippedText(gc,_L("Lookup"),TPoint(xPos,yTextPos));
		
	yTextPos+=yInc;
	yPos+=yInc;

	borderColors = LookupBorderColors();

	DrawBorderColors(TPoint(xPos,yPos),borderColors);

	yTextPos+=yInc;
	yPos+=yInc;

	DrawSampleBorders(TPoint(xPos,yPos),borderColors);

	//
	// HSL Algorithm Test Column
	//

	yPos = KYStart;
	yTextPos = KYTextStart;
	xPos+=3*xInc;

	gc.SetPenColor(KRgbBlack);
	DrawClippedText(gc,_L("HSL Algorithm"),TPoint(xPos,yTextPos));
		
	yTextPos+=yInc;
	yPos+=yInc;

	GetHslDerivedBorderColors(borderColors,iNeutralColor,KRgbBlack,displayMode);

	DrawBorderColors(TPoint(xPos,yPos),borderColors);

	yTextPos+=yInc;
	yPos+=yInc;

	DrawSampleBorders(TPoint(xPos,yPos),borderColors);
	}

#define KBorderColorBlockWidth 20


/**
   Auxiliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method sets the logical,descriptive & other custom border types for
   the rectangle to be drawn. It draws rectangles with these border types by
   invoking CSimpleControl::DrawBorder() method.
  
 */
void CSimpleControl::DrawSampleBorders(const TPoint& aPoint,const TGulBorder::TColors& aColors) const
	{
	CWindowGc& gc = SystemGc();

	TInt xPos = aPoint.iX;
	TInt yPos = aPoint.iY;

	const TInt yInc = KHeight+KYSpacing;
	const TInt xInc = KWidth+KXSpacing;

		{
		TGulBorder border(TGulBorder::EWindow);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		}
	xPos+=xInc;

		{
		TGulBorder border(TGulBorder::EFlatContainer);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		}
	yPos+=yInc;
	xPos-=xInc;

		{
		TGulBorder border(TGulBorder::ERaisedContainer);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		}
	xPos+=xInc;

		{
		TGulBorder border(TGulBorder::ESunkenContainer);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		}
	yPos+=yInc;
	xPos-=xInc;

		{
		TGulBorder border(TGulBorder::EFlatControl);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		}
	xPos+=xInc;

		{
		TGulBorder border(TGulBorder::ERaisedControl);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		}
	yPos+=yInc;
	xPos-=xInc;

		{
		TGulBorder border(CSimpleControl::EWindows3Raised);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		
		xPos+=xInc;
		border.SetType(CSimpleControl::EWindows3Sunken);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		}
	yPos+=yInc;
	xPos-=xInc;

		{
		TGulBorder border(CSimpleControl::EJavaRaised);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		
		xPos+=xInc;
		border.SetType(CSimpleControl::EJavaSunken);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		}
	yPos+=yInc;
	xPos-=xInc;

		{
		TGulBorder border(CSimpleControl::EBeOSRaised);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		
		xPos+=xInc;
		border.SetType(CSimpleControl::EBeOSSunken);
		DrawBorder(border,gc,TRect(TPoint(xPos,yPos),TSize(KWidth,KHeight)),aColors);
		}
	yPos+=yInc;
	xPos-=xInc;
	}

/**
   Auxiliary Function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method draws & fills rectangles with colours specified by the
   TGulBorder::TColors member variable iDark, iLight, iMid, iMidlight.
   aColor is derived based on the background colour of the control.
  
 */
void CSimpleControl::DrawBorderColors(const TPoint& aPoint,const TGulBorder::TColors& aColors) const
	{
	CWindowGc& gc = SystemGc();
	TInt xPos = aPoint.iX;
	const TInt xInc=KBorderColorBlockWidth;
	const TSize blockSize(KBorderColorBlockWidth,KHeight);

	gc.SetBrushColor(aColors.iLight);
	gc.DrawRect(TRect(TPoint(xPos,aPoint.iY),blockSize));		
	xPos+=xInc;

	gc.SetBrushColor(aColors.iMidlight);
	gc.DrawRect(TRect(TPoint(xPos,aPoint.iY),blockSize));		
	xPos+=xInc;

	gc.SetBrushColor(aColors.iBack);
	gc.DrawRect(TRect(TPoint(xPos,aPoint.iY),blockSize));		
	xPos+=xInc;

	gc.SetBrushColor(aColors.iMid);
	gc.DrawRect(TRect(TPoint(xPos,aPoint.iY),blockSize));		

	xPos-=xInc/2;
	gc.SetBrushColor(LightRgb(aColors.iMid));
	TSize size=blockSize;
	size.iHeight=5;
	gc.DrawRect(TRect(TPoint(xPos,aPoint.iY-5),size));		
	xPos+=xInc/2;
	xPos+=xInc;

	gc.SetBrushColor(aColors.iDark);
	gc.DrawRect(TRect(TPoint(xPos,aPoint.iY),blockSize));		
	xPos+=xInc;	
	}

/**
   Auxiliary function for all Test Cases
  
   The method returns the current border colours. 
  
 */
TGulBorder::TColors	CSimpleControl::RGBBorderColors() const
	{
	TGulBorder::TColors borderColors;
	
	borderColors.iBack=iNeutralColor;
	borderColors.iMid=DarkRgb(borderColors.iBack);
	borderColors.iDark=DarkRgb(borderColors.iMid);
	borderColors.iMidlight=LightRgb(borderColors.iBack);
	borderColors.iLight=LightRgb(borderColors.iMidlight);

	return borderColors;
	}

/**
   Auxilliary Function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method prepares & returns a TGulBorder::TColors object by setting
   member variables iBack, iDark, iLight, iMid, iMidlight by a colour picked
   from look up tables.
  
 */
TGulBorder::TColors	CSimpleControl::LookupBorderColors() const
	{
	TGulBorder::TColors borderColors;
	
	borderColors.iBack=iNeutralColor;

	borderColors.iMid=TRgb::Color256(color256darklutab[borderColors.iBack.Color256()]);
	borderColors.iDark=TRgb::Color256(color256darklutab[borderColors.iMid.Color256()]);

	borderColors.iMidlight=TRgb::Color256(color256lightlutab[borderColors.iBack.Color256()]);
	borderColors.iLight=TRgb::Color256(color256lightlutab[borderColors.iMidlight.Color256()]);

	return borderColors;
	}

/** 
   Auxilliary function for TestCaseID tbrdrcol-DrawColorCubeBackgroundNow
  
   This method gets a set of border colors in aBorderColors.
   Lighter and darker tones in the set are derived from the background color
   aBackgroundColor using an algorithm operating on the HSL value of this color
   or a lookup table depending on the display mode aMode. The outline color
   aOutlineColor is simply incorporated into the border color set.
 */
void CSimpleControl::GetHslDerivedBorderColors(TGulBorder::TColors& aBorderColors,TRgb aBackgroundColor,TRgb aOutlineColor,const TDisplayMode& aMode) const
{
	switch (aMode)
		{
	case EColor256:
	default:
		{
		THsl hsl = ColorConverter::RgbToHsl(aBackgroundColor);
		const TInt baseLumen = hsl.Lumen();
		const TInt minLumen = (hsl.Lumen() > 130) ? 50 : 10;

		// MidLight
		hsl.SetLumen( (baseLumen+280)/2 );
		if (hsl.Lumen() > 230) 
			hsl.SetLumen(230);
		aBorderColors.iMidlight = ColorConverter::HslToRgb(hsl);

		// Light 
		//
		// This is too harsh and should be tempered
		//
		hsl.SetLumen((hsl.Lumen() + 280) / 2);
		aBorderColors.iLight = ColorConverter::HslToRgb(hsl);	

		// Mid
		hsl.SetLumen( (baseLumen + minLumen) / 2 );
		hsl.SetLumen( (hsl.Lumen() + minLumen) / 2 );
		aBorderColors.iMid = ColorConverter::HslToRgb(hsl);
		
		// Dark
		hsl.SetLumen( minLumen );
		aBorderColors.iDark = ColorConverter::HslToRgb(hsl);
		
		// Line
		aBorderColors.iLine = aOutlineColor;
		
		// Back
		aBorderColors.iBack = aBackgroundColor;
		}
		break;
		}
	}


/**
   Auxiliary function for all Test Cases
  
   This method prepares the test step's user interface and prepares it
   to start the tests. As part of user interface it creates a control
   on which the tests are carried out.
   
 */
void CSimpleAppUi::ConstructL()
    {
    //BaseConstructL(ENoAppResourceFile);
	CTestCoeAppUi::ConstructL();
    
	iSimpleControl=new(ELeave) CSimpleControl( iStep );
    iSimpleControl->ConstructL();
    AddToStackL(iSimpleControl);
 
	AutoTestManager().StartAutoTest();
   }

CSimpleAppUi::~CSimpleAppUi()
/**
   Destructor
 */
	{
	RemoveFromStack(iSimpleControl);
    delete iSimpleControl;
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CTestAppUi. The method initiates border
   drawing tests.
   
 */
void CSimpleAppUi::RunTestStepL(TInt aNextStep)
	{
	if(KMaxNumAttempt <  aNextStep)
		{
		
		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		return;
		}
//#ifdef FORCE_AUTO
	User::After(TTimeIntervalMicroSeconds32(500000));
//#endif	
	
	iSimpleControl->iColCubeIndex = ( iSimpleControl->iColCubeIndex + 10 ) % 255;
    iSimpleControl->DrawColorCubeBackgroundNow();
	
	TBuf<256> buf;
	buf.Format(_L("Draw color background with index %d\n"), iSimpleControl->iColCubeIndex);
	INFO_PRINTF1(buf);
	}

//----------

CTestBrdrColStep::CTestBrdrColStep()
/**
   Constructor
 */
	{
	SetTestStepName(KTestBrdrColStep);
	}

CTestBrdrColStep::~CTestBrdrColStep()
/**
   Destructor
 */
	{
	}

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object.
   
 */
void CTestBrdrColStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();

	CSimpleAppUi* appUi= new (ELeave) CSimpleAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the test step's user interface object and
   launches the test step.
   
 */
TVerdict CTestBrdrColStep::doTestStepL() // main function called by E32
	{
	PreallocateHALBuffer();

	SetTestStepID(_L("UIF-tbrdrcol-DrawColorCubeBackgroundNow"));

	__UHEAP_MARK;

	CEikonEnv* coe=new CEikonEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();

	REComSession::FinalClose();	
	__UHEAP_MARKEND;

	RecordTestResultL();
	CloseTMSGraphicsStep();

	return TestStepResult();
	}





