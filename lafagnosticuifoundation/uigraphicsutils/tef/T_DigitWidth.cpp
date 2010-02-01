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
//

/**
 @file 
 @internalComponent - Internal Symbian test code  
*/

#include <gdi.h>
#include <gulutil.h>
#include <bitdev.h>
#include <fbs.h>
#include "T_DigitWidth.h"

CTestFont::CTestFont(CT_DigitWidth* aDigitWidth):iDigitWidth(aDigitWidth)
	{
	}

CTestFont::~CTestFont()
	{
	}

TUid CTestFont::DoTypeUid() const
	{
	return TUid::Uid(1010);
	}

TInt CTestFont::DoHeightInPixels() const
	{
	return 12;
	}

TInt CTestFont::DoAscentInPixels() const
	{
	return 10;
	}

TInt CTestFont::DoCharWidthInPixels(TChar aChar) const
	{
	switch (aChar)
		{
	//EDigitTypeWestern = 0x0030
	case 0x0030:
		return 6;
	case 0x0031:
		return 6;
	case 0x0032:
		return 6;
	case 0x0033:
		return 6;
	case 0x0034:
		return 6;
	case 0x0035:
		return 7;  //widest
	case 0x0036:
		return 6;
	case 0x0037:
		return 6;
	case 0x0038:
		return 6;
	case 0x0039:
		return 6;
	//EDigitTypeArabicIndic = 0x0660
	case 0x0660:
		return 8;
	case 0x0661:
		return 8;
	case 0x0662:
		return 9; //widest
	case 0x0663:
		return 8;
	case 0x0664:
		return 8;
	case 0x0665:
		return 8;
	case 0x0666:
		return 8;
	case 0x0667:
		return 8;
	case 0x0668:
		return 8;
	case 0x0669:
		return 8;
	//EDigitTypeEasternArabicIndic = 0x6F0
	case 0x06F0:
		return 4;
	case 0x06F1:
		return 4;
	case 0x06F2:
		return 4;
	case 0x06F3:
		return 4;
	case 0x06F4:
		return 4;
	case 0x06F5:
		return 4;
	case 0x06F6:
		return 4;
	case 0x06F7:
		return 4;
	case 0x06F8:
		return 4;
	case 0x06F9:
		return 5; //widest
	//EDigitTypeDevanagari = 0x0966
	case 0x0966:
		return 11;//widest
	case 0x0967:
		return 10;
	case 0x0968:
		return 10;
	case 0x0969:
		return 10;
	case 0x096A:
		return 10;
	case 0x096B:
		return 10;
	case 0x096C:
		return 10;
	case 0x096D:
		return 10;
	case 0x096E:
		return 10;
	case 0x096F:
		return 10;
	//EDigitTypeThai = 0x0E50
	case 0x0E50:
		return 15;
	case 0x0E51:
		return 15;
	case 0x0E52:
		return 15;
	case 0x0E53:
		return 15;
	case 0x0E54:
		return 15;
	case 0x0E55:
		return 15;
	case 0x0E56:
		return 15;
	case 0x0E57:
		return 15;
	case 0x0E58:
		return 16;//widest
	case 0x0E59:
		return 15;
		}
	iDigitWidth->TEST(EFalse);
	return 0;
	}

TInt CTestFont::DoTextWidthInPixels(const TDesC& aText) const
	{
	TInt total = 0;
	const TText* p = aText.Ptr();
	const TText* end = p + aText.Length();
	for (;p != end; ++p)
		total += CharWidthInPixels(*p);
	return total;
	}

TInt CTestFont::DoBaselineOffsetInPixels() const
	{
	return 10;
	}

TInt CTestFont::DoTextCount(const TDesC& aText,TInt aWidthInPixels) const
	{
	TInt excess;
	return TextCount(aText, aWidthInPixels, excess);
	}

TInt CTestFont::DoTextCount(const TDesC& aText,TInt aWidthInPixels,TInt& aExcessWidthInPixels) const
	{
	aExcessWidthInPixels = aWidthInPixels;
	const TText* start = aText.Ptr();
	const TText* end = start + aText.Length();
	const TText* p = start;
	TInt width;
	while (p != end
		&& (width = CharWidthInPixels(*p)) <= aExcessWidthInPixels)
		{
		aExcessWidthInPixels -= width;
		++p;
		}
	return p - start;
	}

TInt CTestFont::DoMaxCharWidthInPixels() const
	{
	return 10;
	}

TInt CTestFont::DoMaxNormalCharWidthInPixels() const
	{
	return 10;
	}

TFontSpec CTestFont::DoFontSpecInTwips() const
	{
	return TFontSpec(KTestFontName, 12);
	}


/*void CTestFont::testResult(TInt aResult)
	{
	if (aResult==1)
		INFO_PRINTF1(_L("test passed\n"));
//	else
//		INFO_PRINTF1(_L("test failed\n"));
	}*/

TInt CT_DigitWidth::TestFindWidthOfWidestDigitType(CFont* aFont, TDigitType aDigitType)
	{
	TFindWidthOfWidestDigitType finder(aDigitType);
    return finder.MaximumWidthInPixels(*aFont);
	}

void CT_DigitWidth::TestFontsL()
	{
	CTestFont font(this);
	TFontSpec font_spec = font.FontSpecInTwips();

	INFO_PRINTF1(_L("-------------\r\n"));
	INFO_PRINTF2(_L("Font: %S\r\n"), &(font_spec.iTypeface.iName));

	TInt maxWidth = 0;

	maxWidth = TestFindWidthOfWidestDigitType(&font, EDigitTypeWestern);
	INFO_PRINTF2(_L("EDigitTypeWestern, MaxWidth=%d\r\n"), maxWidth);
	TEST(maxWidth == 7);

	maxWidth = TestFindWidthOfWidestDigitType(&font, EDigitTypeArabicIndic);
	INFO_PRINTF2(_L("EDigitTypeArabicIndic, MaxWidth=%d\r\n"), maxWidth);
	TEST(maxWidth == 9);

	maxWidth = TestFindWidthOfWidestDigitType(&font, EDigitTypeEasternArabicIndic);
	INFO_PRINTF2(_L("EDigitTypeEasternArabicIndic, MaxWidth=%d\r\n"), maxWidth);
	TEST(maxWidth == 5);

	maxWidth = TestFindWidthOfWidestDigitType(&font, EDigitTypeDevanagari);
	INFO_PRINTF2(_L("EDigitTypeDevanagari, MaxWidth=%d\r\n"), maxWidth);
	TEST(maxWidth == 11);

	maxWidth = TestFindWidthOfWidestDigitType(&font, EDigitTypeThai);
	INFO_PRINTF2(_L("EDigitTypeThai, MaxWidth=%d\r\n"), maxWidth);
	TEST(maxWidth == 16);
	}

void CT_DigitWidth::DoTestsL()
    {

	INFO_PRINTF1(_L("Test WidestDigitType"));
	TestFontsL();
    
	}



CT_DigitWidth::~CT_DigitWidth()
/**
   Destructor
 */
	{
	}


CT_DigitWidth::CT_DigitWidth()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KT_DigitWidth);
	}


TVerdict CT_DigitWidth::doTestStepL()
{
	INFO_PRINTF1(_L("Test Started"));

	__UHEAP_MARK;

	INFO_PRINTF1(_L("Digit Width"));

    TRAPD(err, DoTestsL());
    TEST(err==KErrNone);


	INFO_PRINTF1(_L("Test Finished"));

    __UHEAP_MARKEND;

	return TestStepResult();
}
