/*
* Copyright (c) 1998 Nokia Corporation and/or its subsidiary(-ies).
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



#include <eiklbx.h>     // to call static function ListBoxLaf()
#include <eiklbd.h>
#include <gdi.h>
#include <coemain.h>
#include <eikenv.h>
#include <eiklbi.h>
#include "laflbd.h"

#include "akntrace.h"

class MAknsControlContext;
//
// class CListBoxDataExtension
// (private class -- put all interface to CListBoxData instead)
// 

NONSHARABLE_CLASS(CListBoxDataExtension) : public CBase
	{
public:
	void ConstructL();
	~CListBoxDataExtension();
public:
	MAknsControlContext* iSkinControlContext;
	TBool iSkinEnabled;
	};

void CListBoxDataExtension::ConstructL()
	{
	}
CListBoxDataExtension::~CListBoxDataExtension()
	{
	}


///
/// class TListBoxBoundValues
///

EXPORT_C TListFontBoundValues::TListFontBoundValues()
	: iMaxNormalCharWidthInPixels(0), iHeightInPixels(0)
	{
	}

///
/// class CListBoxData
///

EXPORT_C CListBoxData::CListBoxData()
	: iAlign(CGraphicsContext::ELeft)
    {}

EXPORT_C CListBoxData::~CListBoxData()
    {
	delete iSearchString;
	delete iLBDExtension;
    }

EXPORT_C MAknsControlContext *CListBoxData::SkinBackgroundControlContext() const
	{
	if (iLBDExtension && iLBDExtension->iSkinEnabled)
		return iLBDExtension->iSkinControlContext;
	return NULL;
	}

EXPORT_C void CListBoxData::SetSkinBackgroundControlContextL(MAknsControlContext *aContext)
	{
	if (iLBDExtension)
		iLBDExtension->iSkinControlContext = aContext;
	}

EXPORT_C void CListBoxData::SetSkinEnabledL(TBool aEnabled)
	{
	if (iLBDExtension)
		iLBDExtension->iSkinEnabled = aEnabled;
	}

EXPORT_C void CListBoxData::ConstructL(const CFont* /* aBaseFont */)
    {
	iLBDExtension = new(ELeave)CListBoxDataExtension;
	iLBDExtension->ConstructL();
    }

EXPORT_C CFont* CListBoxData::Font(const TListItemProperties& aItemProperties) const
    {
    CArrayPtr<CFont>* fonts=NULL;
    if ((aItemProperties.IsBold()) && (aItemProperties.IsItalics()))
        {
        fonts=iBoldItalicFont.iFonts;
        }
    else if (aItemProperties.IsBold())
        {
        fonts=iBoldFont.iFonts;
        }
    else if (aItemProperties.IsItalics())
        {
        fonts=iItalicFont.iFonts;
        }
    else 
		fonts=iNormalFont.iFonts;
    if (!fonts || fonts->Count()==0)
		return NULL;
    return fonts->At(0);
    }

EXPORT_C
void CListBoxData::SetupGc( const TListItemProperties& aItemProperties,
                            CWindowGc& aGc) const
    {
    aGc.SetUnderlineStyle(aItemProperties.IsUnderlined() ? EUnderlineOn : EUnderlineOff);
    aGc.SetPenColor(aItemProperties.Color());
    CFont *font=Font(aItemProperties);
    if(font)
        {
        aGc.UseFont(font);
        }
    }

EXPORT_C const TListFontBoundValues& CListBoxData::FontBoundValues() const
    {
    return iFontBoundValues;
    }

EXPORT_C TInt CListBoxData::SetFontHeight(TInt aFontHeightInTwips)
    {
    TListFontBoundValues newValues;
    iFontBoundValues=newValues;
	TInt retVal = KErrNone;
    retVal = RegenerateFonts(iNormalFont, aFontHeightInTwips);
	if(retVal!=KErrNone)
		return retVal;
    retVal = RegenerateFonts(iBoldFont, aFontHeightInTwips);
	if(retVal!=KErrNone)
		return retVal;
    retVal = RegenerateFonts(iItalicFont, aFontHeightInTwips);
	if(retVal!=KErrNone)
		return retVal;
    retVal = RegenerateFonts(iBoldItalicFont, aFontHeightInTwips);
	return retVal;
    }

EXPORT_C TInt CListBoxData::RegenerateFonts(CFontsWithStyle& aFonts, TInt aFontHeightInTwips)
    {
	TInt retVal=KErrNone;
    if (aFonts.iFonts)
        {
		CGraphicsDevice* screenDevice=CCoeEnv::Static()->ScreenDevice();
        for (TInt ii=0 ; ii < aFonts.iFonts->Count(); ii++)
            {
            CFont* prevFont=aFonts.iFonts->At(ii);
            TFontSpec fontSpec=prevFont->FontSpecInTwips();
            fontSpec.iFontStyle=aFonts.FontStyle();
            fontSpec.iHeight=aFontHeightInTwips;
            CFont* font;
            retVal=screenDevice->GetNearestFontInTwips(font,fontSpec);
			if(retVal!=KErrNone)
				break;
			screenDevice->ReleaseFont(prevFont);
            aFonts.iFonts->At(ii)=font;
            UpdateFontBoundValues(*font);
            }
        }
	return retVal;
    }

EXPORT_C void CListBoxData::ConstructFontL(const CFont* aBaseFont, TFontStyle aFontStyle, CFontsWithStyle& aFonts)
    {
    // Notice! CColumnListBoxData::AddActualFontL function assumes, that
    // this function can leave only in the creation of an array or
    // in appending an item into array.If this fact changes. AddActualFontL
    // has to be rewritten.
    if (!aFonts.iFonts)
        {
        aFonts.iFonts=new (ELeave) CArrayPtrFlat<CFont> (1);
        }
    CFont* font;
    TFontSpec fontSpec=aBaseFont->FontSpecInTwips();
    fontSpec.iFontStyle=aFontStyle;
    User::LeaveIfError(CCoeEnv::Static()->ScreenDevice()->GetNearestFontInTwips(font,fontSpec));
    UpdateFontBoundValues(*font);
    aFonts.iFonts->AppendL(font);
    aFonts.SetFontStyle(aFontStyle);
    }

EXPORT_C void CListBoxData::UpdateFontBoundValues(const CFont& aFont)
    {
    if (iFontBoundValues.iMaxNormalCharWidthInPixels<aFont.MaxNormalCharWidthInPixels())
        {
        iFontBoundValues.iMaxNormalCharWidthInPixels=aFont.MaxNormalCharWidthInPixels();
        }
    if (iFontBoundValues.iHeightInPixels<aFont.HeightInPixels())
        {
        iFontBoundValues.iHeightInPixels=aFont.HeightInPixels();
        }
    }

EXPORT_C void CListBoxData::Reserved_1()
    {
    }

EXPORT_C void CListBoxData::Reserved_2()
    {
    }

//
// Class CListBoxData::CFontsWithStyle
//

CListBoxData::CFontsWithStyle::CFontsWithStyle()
                : iFonts (NULL)
    {
    }

CListBoxData::CFontsWithStyle::~CFontsWithStyle()
    {
	ReleaseFonts();
	delete iFonts;
    }

EXPORT_C void CListBoxData::CFontsWithStyle::ReleaseFonts()
    {
    if (iFonts)
        {
        for (TInt ii=0 ; ii < iFonts->Count(); ii++)
            {
            CCoeEnv::Static()->ScreenDevice()->ReleaseFont(iFonts->At(ii));
            }
        }
    }

EXPORT_C TFontStyle CListBoxData::CFontsWithStyle::FontStyle()
	{
	return iFontStyle;
	}


EXPORT_C void CListBoxData::CFontsWithStyle::SetFontStyle(TFontStyle aFontStyle)
	{
	iFontStyle=aFontStyle;
	}

/**
 * Set search string for search result viewing.
 */
EXPORT_C void CListBoxData::SetSearchStringL(const TDesC* aSearchString)
	{
	_AKNTRACE_FUNC_ENTER;
	if (aSearchString==NULL)
		{
		delete iSearchString;
		iSearchString = NULL;
		_AKNTRACE_FUNC_EXIT;
		return;
		}
	TInt length = aSearchString->Length();
	if (iSearchString)
		{
		if (length>iSearchString->Length())
			{
			iSearchString = iSearchString->ReAllocL(length);
			}
		}
	else
		{
		iSearchString = HBufC::NewL(length);
		}
	*iSearchString = *aSearchString;
	_AKNTRACE_FUNC_EXIT;
	}

/**
 * Returns ETrue if a search string with a non-zero length has been set for this list box.
 */
EXPORT_C TBool CListBoxData::IsSearchString() const
	{
	return (iSearchString && iSearchString->Length());
	}


/**
 * Font Draws list item text so that search string is drawed as bold underlined.
 */
EXPORT_C void CListBoxData::DrawItem(CWindowGc& aGc, const TRect& aItemTextRect,const TDesC& aItemText,
								const CFont& aItemFont,const TInt aBaseLineOffset,const CGraphicsContext::TTextAlign aAlign) const
	{
	_AKNTRACE_FUNC_ENTER;
	const TInt strPos=aItemText.FindF(*iSearchString);
	const TInt strLen = iSearchString->Length();

	if (strPos==KErrNotFound)	// if there's no search string treat as normal
		{
		/*Call to the laf code which is responsible for drawing a normal text string in a rectangle*/
		LafTextListItemDrawer::DrawNormalText(aItemText,aItemFont,aGc,aItemTextRect,aBaseLineOffset,aAlign);
		}
	else 
		{
		const CFont& boldFont=iBoldFont.iFonts?*(iBoldFont.iFonts->At(0)):aItemFont;
		/*Call to the laf code which is responsible for drawing a search text string in a rectangle*/
		LafListBoxData::DrawSearchText(aItemTextRect,aGc,aItemFont,boldFont,
										aItemText,strPos,strLen,aBaseLineOffset,aAlign);
		}
	_AKNTRACE_FUNC_EXIT;
	}
