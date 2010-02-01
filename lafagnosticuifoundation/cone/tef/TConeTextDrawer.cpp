// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#include "TCone7Step.h"


/**
This test will draw a multi-line TBidiText clockwise one and a half laps from top left
to top right (via bottom right to bottom left), in 9 steps.
It draws a rectangle around clipping area (if any)  
*/
TBool CCtlTestTextDrawer::TestTextDrawer(TInt aTextIndex, TBool aHorizontal, TRect *aClipRect, TRgb* aTextCol, TBool aCleanBackground, TBool aUp)
	{	
	ActivateGc();
	CWindowGc& gc = SystemGc();
	TRect rect = Rect();
	if(aCleanBackground)
		{
		gc.Clear(rect);
		}
	TRgb textColor = aTextCol ? *aTextCol : KRgbBlack;
	
	CCoePlainTextDrawer* plainTextDrawer = CCoePlainTextDrawer::New(textColor);
	XCoeTextDrawer textDrawer(*plainTextDrawer);
	textDrawer.SetClipRect(aClipRect ? *aClipRect : rect);

	if(aClipRect)
		{
		gc.SetPenColor(KRgbRed);
		gc.DrawRect(*aClipRect);
		gc.SetPenColor(textColor);
		}
		
	TMargins8 margin;
	margin.iLeft = 10;
	margin.iRight = 20;
	margin.iTop = 30;
	margin.iBottom = 50;

	textDrawer.SetMargins(margin);
	TSize deltaMargin = margin.SizeDelta();

	if(deltaMargin != TSize(0, 0)) 
		{
		TRect marginRect;
		if(aHorizontal)
			{
			marginRect = margin.InnerRect(rect);
			}
		else
			{//adjust matgins border to rotated text
			marginRect = rect;
			if(aUp)
				{
				marginRect.iTl.iX += margin.iTop;
				marginRect.iTl.iY += margin.iRight;
				marginRect.iBr.iX -= margin.iBottom;
				marginRect.iBr.iY -= margin.iLeft;
				}
			else
				{
				marginRect.iTl.iX += margin.iBottom;
				marginRect.iTl.iY += margin.iLeft;
				marginRect.iBr.iX -= margin.iTop;
				marginRect.iBr.iY -= margin.iRight;
				}
			}
		gc.DrawRect(marginRect);
		}
	
	TGulAlignment textAlign;
	switch(aTextIndex)
		{
		// Test left, center, and right alignment with no application language set.
		// This should result in left, center, and right alignment, as the script is LeftToRight (English).
	case 0:
		textAlign = TGulAlignment(EHLeftVTop);
		break;
	case 1:
		textAlign = TGulAlignment(EHCenterVTop);
		break;
	case 2:
		textAlign = TGulAlignment(EHRightVTop);
		break;
		
		// Test left, center, and right MIRRORED alignment with Hebrew (RightToLeft) application language set.
		// This shall result in the text being aligned right, center, and left, rather than the other way around
	case 3:
		textAlign = TGulAlignment(EHLeftVBottom);
		plainTextDrawer->SetAppLanguage(ELangHebrew);
		break;
	case 4:
		textAlign = TGulAlignment(EHCenterVBottom);
		plainTextDrawer->SetAppLanguage(ELangHebrew);
		break;
	case 5:
		textAlign = TGulAlignment(EHRightVBottom);
		plainTextDrawer->SetAppLanguage(ELangHebrew);
		break;
		
		// Test ABSOLUTE left, center, and right alignment with Hebrew (RightToLeft) application language set.
		// This shall result in NO mirroring, i.e. text being displayed left, center, right.
	case 6:
		textAlign = TGulAlignment(EHLeftVTop);
		textAlign.SetAbsoluteHAlignment(ETrue);
		plainTextDrawer->SetAppLanguage(ELangHebrew);
		break;
	case 7:
		textAlign = TGulAlignment(EHCenterVTop);
		textAlign.SetAbsoluteHAlignment(ETrue);
		plainTextDrawer->SetAppLanguage(ELangHebrew);
		break;
	case 8:
		textAlign = TGulAlignment(EHRightVTop);
		textAlign.SetAbsoluteHAlignment(ETrue);
		plainTextDrawer->SetAppLanguage(ELangHebrew);
		break;
	default:
		ASSERT(0);	
		};


	textDrawer->SetAlignment(textAlign);
	
	TBidiText* bidiText = TBidiText::NewL(KMultipleLineText(), 4);
	bidiText->WrapText(rect.Width(), *iFont);
	aHorizontal ?
			textDrawer.DrawText(gc, *bidiText, rect, *iFont) :
			textDrawer.DrawTextVertical(gc, *bidiText, rect, *iFont, aUp);
	
	delete bidiText;
	
	DeactivateGc();
	iCoeEnv->Flush();
	
	return (textColor == textDrawer->TextColor());
	}

void CCtlTestTextDrawer::WidthOfText(TInt aLine, TInt& aWidthInPixels) const
	{
	TPtrC textInGivenLine(TCoeTextTypeAdaptor(KMultipleLineText).LineOfText(aLine, aWidthInPixels, *iFont));
	}

CCtlTestTextDrawer::CCtlTestTextDrawer()
	{
	}

const CFont& CCtlTestTextDrawer::FontUsed() const
	{
	return *iFont;
	}
	
CCtlTestTextDrawer::~CCtlTestTextDrawer()
	{
	iCoeEnv->ReleaseScreenFont(iFont);
	}

void CCtlTestTextDrawer::ConstructL()
	{
	TFontSpec fs;
	_LIT(KTextFont,"DejaVu Sans Mono");
	fs.iTypeface.iName = KTextFont;
	fs.iHeight = 150;
	iFont = iCoeEnv->CreateScreenFontL(fs);
	CreateWindowL();
	Window().SetBackgroundColor(KRgbCyan);
	}

