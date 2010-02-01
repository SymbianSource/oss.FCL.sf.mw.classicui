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
// Tests border drawing using border colour & style.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#ifndef		__TBRDRCOL_H
#define		__TBRDRCOL_H


#include "appfwk_test_AppUi.h"

_LIT(KTestBrdrColStep, "TBrdrCol");

#define KBlockHeight 10
#define KBlockWidth 5


//!  A CTestBrdrColStep test class. 
/**
 Tests border drawing using border colour & style.
*/
class CTestBrdrColStep : public CTmsTestStep
	{
public:
	CTestBrdrColStep();
	~CTestBrdrColStep();
	//virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	};



//!  THsl. 
/**
 The THsl class is used for representation of colors using a hue, saturation and lumen model.
*/
class THsl
	{
public:
	inline THsl();
	inline THsl(TUint32 aValue);
	inline THsl(TInt aHue, TInt aSaturation, TInt aLumen);
	inline TInt Hue() const;
	inline TInt Saturation() const;
	inline TInt Lumen() const;
	void SetHue(TInt aHue);
	void SetSaturation(TInt aSaturation);
	void SetLumen(TInt aLumen);
private:
	TUint32 iValue;
	};


//!  ColorConverter. 
/**
 The ColorConverter class is used for color conversions.
*/
class ColorConverter
	{
public:
	static THsl	RgbToHsl(TRgb aRgb);
	static TRgb	HslToRgb(THsl aHsl);
	static TInt	HueToRgb(TInt aM1,TInt aM2,TInt aHue);
	};


//!  CSimpleControl. 
/**
 A simple control on which all tests are carried out.
*/
class CSimpleControl : public CCoeControl
    {
public:
	CSimpleControl( CTmsTestStep* aStep );
    void ConstructL();
	~CSimpleControl();

	void DrawColorCubeBackgroundNow();
	TInt iColCubeIndex;

private: // framework
	void Draw(const TRect& aRect) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private: // new function
	void DrawBorder(const TGulBorder& aBorder,CGraphicsContext& aGc,const TRect& aOuterRect,const TGulBorder::TColors& aColors) const;
	void DrawSoftBorder(const TGulBorder& aBorder,CGraphicsContext& aGc,const TRect& aOuterRect) const;
	void DrawClippedText(CWindowGc& aGc,const TDesC& aText,const TPoint& aPoint) const;
	TPoint DrawColorBlocks(const TPoint& startPoint, TInt startIndex, TInt numRows, TInt numCols) const;
	void DrawBorderColors(const TPoint& aPoint,const TGulBorder::TColors& aColors) const;
	void DrawSampleBorders(const TPoint& aPoint,const TGulBorder::TColors& aColors) const;
	void DrawNormalBackgroundNow();
	TRgb DarkRgb(TRgb aColor) const;
	TRgb LightRgb(TRgb aColor) const;
	TGulBorder::TColors	RGBBorderColors() const;
	TGulBorder::TColors	LookupBorderColors() const;
	void GetHslDerivedBorderColors(TGulBorder::TColors& aBorderColors,
												TRgb aBackgroundColor,TRgb aOutlineColor,const TDisplayMode& aMode) const;
public:
	enum TBorderForeignType {
		EJavaRaised=TGulBorder::EFlat|TGulBorder::EThreeStep|TGulBorder::EAddOnePixel, 
		EJavaSunken=TGulBorder::ESunken|TGulBorder::EThreeStep|TGulBorder::EAddOnePixel,
		EWindows3Raised=TGulBorder::EWithOutline|TGulBorder::EAddOneRoundingPixel|TGulBorder::ERaised|TGulBorder::EOneStep|TGulBorder::EAddTwoPixels,
		EWindows3Sunken=TGulBorder::EWithOutline|TGulBorder::EAddOneRoundingPixel|TGulBorder::ESunken|TGulBorder::EOneStep|TGulBorder::EAddTwoPixels,
		EBeOSRaised=TGulBorder::ERaised|TGulBorder::EThreeStep|TGulBorder::EAddOnePixel,
		EBeOSSunken=TGulBorder::ESunken|TGulBorder::EThreeStep|TGulBorder::EAddOnePixel,
		ENextRaised=TGulBorder::ERaised|TGulBorder::ETwoStep|TGulBorder::EAddOnePixel,
		ENextSunken=TGulBorder::ESunken|TGulBorder::ETwoStep|TGulBorder::EAddOnePixel,
		EMotifRaised=TGulBorder::ERaised|TGulBorder::EOneStep|TGulBorder::EAddTwoPixels,
		EMotifSunken=TGulBorder::ESunken|TGulBorder::EOneStep|TGulBorder::EAddTwoPixels
		};
private:
	TRgb iNeutralColor;
	CTmsTestStep*		iStep;
	};

//!  CSimpleAppUi. 
/**
 UI class to CTestBrdrColStep test step class.
*/
class CSimpleAppUi : public CTestCoeAppUi
    {
public:
	CSimpleAppUi(CTmsTestStep* aStep):
	  CTestCoeAppUi(aStep) {}
    void ConstructL();
	~CSimpleAppUi();
private:
    CSimpleControl* iSimpleControl;
private:
 	virtual void RunTestStepL(TInt aNextStep); 
   };


#endif


