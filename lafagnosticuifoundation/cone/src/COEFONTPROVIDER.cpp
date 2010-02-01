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
// class CCoeFontProvider 
// 
//

#include <coefontprovider.h>
#include <coecntss.h>

CCoeFontProvider::TFont::TFont(const TCoeFont& aCoeFont, TInt aZoomFactor, const CFont* aFont) : 
                iCoeFont(aCoeFont), iZoomFactor(aZoomFactor), iFont(aFont) 
    { 
    } 

TInt CCoeFontProvider::TFont::Compare(const TFont& aFirst, const TFont& aSecond) 
    {                 
    const TInt comp = TCoeFont::Compare(aFirst.iCoeFont, aSecond.iCoeFont); 
    if(comp) 
    	{
    	return comp; 
    	}
            
    return (aFirst.iZoomFactor - aSecond.iZoomFactor); 
    } 

/** Standard Symbian factory method. Uses a default typeface

@publishedAll
@released
*/
EXPORT_C CCoeFontProvider* CCoeFontProvider::NewL() 
    { 
    return NewL(CCoeControlStaticSettings::SystemTypeface()); 
    } 

/** Standard Symbian factory method. Typeface to use is provided by caller.

@param aTypefaceName Typeface to use.
@publishedAll
@released
*/
EXPORT_C CCoeFontProvider* CCoeFontProvider::NewL(const TDesC& aTypefaceName) 
    { 
    CCoeFontProvider* self = new (ELeave) CCoeFontProvider(aTypefaceName); 
    CleanupStack::PushL(self); 
    self->ConstructL(); 
    CleanupStack::Pop(self); 
    return self; 
    } 

/** Constructor
*/
CCoeFontProvider::CCoeFontProvider(const TDesC& aTypefaceName) 
    { 
    iTypeface.iName = aTypefaceName; 
    } 

/** Symbian second-phase constructor
*/
void CCoeFontProvider::ConstructL() 
    { 
    CCoeControlStaticSettings::GetLogicalToPixelFontSizesL(iLogicalToPixelSizes);
    } 

CCoeFontProvider::~CCoeFontProvider() 
    { 
    ReleaseAllFonts(); 
    iLogicalToPixelSizes.Reset(); 
    iLogicalToPixelSizes.Close();
    } 

void CCoeFontProvider::ReleaseAllFonts() 
    { 
    TInt count = iFonts.Count(); 
    while(count--) 
        { 
        CCoeEnv::Static()->ScreenDevice()->ReleaseFont(const_cast<CFont*>(iFonts[count].iFont)); 
        } 
    iFonts.Reset(); 
    } 

/** Change the typeface

@param aTypeface The typeface to use
@publishedAll
@released
*/
EXPORT_C void CCoeFontProvider::SetTypeface(TTypeface aTypeface) 
    { 
    if(iTypeface.iName.CompareF(aTypeface.iName) == 0) 
        { 
        iTypeface = aTypeface; 
        ReleaseAllFonts(); 
        
        CCoeAppUi* appUi = static_cast<CCoeAppUi*>(CCoeEnv::Static()->AppUi()); 
        if(appUi) 
        	{
        	appUi->NotifyFontChange(*this);
        	}
        } 
    } 

/** Use the system typeface

@publishedAll
@released
*/
EXPORT_C void CCoeFontProvider::UseSystemTypeface() 
    {        
    const TDesC& systemTypeFaceName = CCoeControlStaticSettings::SystemTypeface();
    const TBool oldNameNull = (!iTypeface.iName.Length()); 
    if(iTypeface.iName.CompareF(systemTypeFaceName) == 0)
        { 
        iTypeface.iName = systemTypeFaceName; 
        ReleaseAllFonts(); 

        if(!oldNameNull) 
            { 
            CCoeAppUi* appUi = static_cast<CCoeAppUi*>(CCoeEnv::Static()->AppUi()); 
            if(appUi) 
            	{
            	appUi->NotifyFontChange(*this); 
            	}        
            } 
        } 
    } 

/** Return the current typeface

@publishedAll
@released
*/
EXPORT_C TTypeface CCoeFontProvider::Typeface() const 
    { 
    return iTypeface; 
    } 

/** Returns the closest available match to the specified logical font and zoom factor.
Note that all CFont objects referenced through this method are owned by the font provider. 
Thus do not explicitly release the font object after use!

A default font provider is made available by the CCoeEnv singleton and returned from 
CCoeControl::FindFontProvider() if no overriding font provider has been attached to 
the control tree.

For an example of how to use this function, see CCoeControl::ScreenFont().

@see CCoeControl::ScreenFont()
@see CCoeControl::FindFontProvider()
@see CCoeControl::AccumulatedZoom()

@param aFont The requested logical font.
@param aZoomFactor Zoom factor used when deriving the font height.
@return The closest matching available font.
@publishedAll
@released
*/
EXPORT_C const CFont& CCoeFontProvider::Font(const TCoeFont& aFont, const TZoomFactor& aZoomFactor) const 
    { 
    const TInt index = iFonts.FindInOrder(TFont(aFont, aZoomFactor.ZoomFactor()), TLinearOrder<TFont>(TFont::Compare)); 
    if(index != KErrNotFound) 
    	{
    	return *iFonts[index].iFont; 
    	}
                
    const TInt heightInPixels = (aFont.LogicalSize() != TCoeFont::EUndefinedSize) ? iLogicalToPixelSizes[aFont.LogicalSize()] : aFont.HeightInPixels(); 
    
    TFontSpec fontSpec; 
    fontSpec.iTypeface = iTypeface; 
    fontSpec.iHeight = aZoomFactor.GraphicsDeviceMap()->VerticalPixelsToTwips(heightInPixels);        // don't care about the zoom just yet 
    fontSpec.iFontStyle = aFont.Style(); 

    CFont* font = NULL; 
    TInt err = KErrNone; 
    if(aFont.IsNonZooming()) 
    	{
        err = const_cast<MGraphicsDeviceMap*>(aZoomFactor.GraphicsDeviceMap())->GetNearestFontToMaxHeightInTwips(font, fontSpec,fontSpec.iHeight);
    	}
    else
		{
        err = const_cast<TZoomFactor&>(aZoomFactor).GetNearestFontToMaxHeightInTwips(font, fontSpec, fontSpec.iHeight);     // here, consider the zoom
		} 
	if (err != KErrNone)
		{
		//error has occured so just return normal font.
		const CFont* normalFont = CCoeEnv::Static()->NormalFont();
		return *normalFont;
		}

    err = iFonts.InsertInOrder(TFont(aFont, aZoomFactor.ZoomFactor(), font), TLinearOrder<TFont>(TFont::Compare)); 
	if (err != KErrNone)
		{
		//error has occured so just return normal font.
		const CFont* normalFont = CCoeEnv::Static()->NormalFont();
		return *normalFont;
		}
		
    return *font; 
    } 
    
/** flushes the array & refetches the logical-to-pixel mapping. Called when global control settings are updated

@internalTechnology
*/
void CCoeFontProvider::RefetchPixelMappingL()
	{
	CCoeControlStaticSettings::GetLogicalToPixelFontSizesL(iLogicalToPixelSizes);
	ReleaseAllFonts();
	}

