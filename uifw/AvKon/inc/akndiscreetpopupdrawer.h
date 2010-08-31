/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Discreet popup drawer
*
*/

#ifndef C_AKNDISCREETPOPUPDRAWER_H
#define C_AKNDISCREETPOPUPDRAWER_H


#include <e32base.h>
#include <gdi.h>

class CAknDiscreetPopupControl;
class CGulIcon;
class CFbsBitmap;
class CFont;
class TAknWindowComponentLayout;
class TAknTextComponentLayout;

/**
 *  Discreet popup text data class.
 */
NONSHARABLE_CLASS( TAknDiscreetPopupTextData )
    {
public:

    /**
     * Popup text field font.
     */
    const CFont* iTextFont;

    /**
     * Popup text field rect.
     */
    TRect iTextRect;

    /**
     * Popup text field alignment.
     */
    CGraphicsContext::TTextAlign iTextAlignment;

    };

/**
 *  Discreet popup drawer.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknDiscreetPopupDrawer ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
     *
     * @param aControl Popup control.
     * @param aTitleText First line of text. 
     * @param aBodyText Second line of text.
     * @param aIcon Icon.
     * @param aSkinId Icon skin item id.
     * @param aBitmapFile Icon bitmap file.
     * @param aBitmapId Icon bitmap id.
     * @param aMaskId Icon mask id.
     * @param aAction ETrue if popup has action when tapped..
     */ 
    static CAknDiscreetPopupDrawer* NewL( CAknDiscreetPopupControl* aControl,
                                          const TDesC& aTitleText, 
                                          const TDesC& aBodyText, 
                                          CGulIcon* aIcon,
                                          const TAknsItemID& aSkinId,
                                          const TDesC& aBitmapFile,
                                          const TInt& aBitmapId,
                                          const TInt& aMaskId,
                                          const TBool& aAction );

    /**
     * Two-phased constructor.
     *
     * @param aControl Popup control.
     * @param aTitleText First line of text. 
     * @param aBodyText Second line of text.
     * @param aIcon Icon.
     * @param aSkinId Icon skin item id.
     * @param aBitmapFile Icon bitmap file.
     * @param aBitmapId Icon bitmap id.
     * @param aMaskId Icon mask id.
     * @param aAction ETrue if popup has action when tapped..
     */
    static CAknDiscreetPopupDrawer* NewLC( CAknDiscreetPopupControl* aControl,
                                           const TDesC& aTitleText, 
                                           const TDesC& aBodyText, 
                                           CGulIcon* aIcon,
                                           const TAknsItemID& aSkinId,
                                           const TDesC& aBitmapFile,
                                           const TInt& aBitmapId,
                                           const TInt& aMaskId,
                                           const TBool& aAction );

    /**
     * Destructor.
     */
    virtual ~CAknDiscreetPopupDrawer();

    /**
     * Sets popup and its components size and position.
     *
     * @return Popup rect.
     */
    TRect LayoutPopup();

    /**
     * Provides popup bitmap.
     * Does not transfer ownership.
     *
     * @param aSize Requested popup bitmap size.
     * @return Popup bitmap.
     */
    CFbsBitmap* PopupBitmap( const TSize& aSize );

    /**
     * Provides transparent mask for a bitmap.
     * Does not transfer ownership.
     *
     * @param aSize Bitmap size.
     * @param aAlpha Alpha factor.
     * @return Transparent mask.
     */
    CFbsBitmap* TransparentMask( const TSize& aSize, 
                                 const TInt& aAlpha );

private:

    /**
     * C++ constructor.
     */
    CAknDiscreetPopupDrawer( CAknDiscreetPopupControl* aControl, 
                             CGulIcon* aIcon,
                             const TBool& aAction );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL( const TDesC& aTitleText, 
                     const TDesC& aBodyText,
                     const TAknsItemID& aSkinId,
                     const TDesC& aBitmapFile,
                     const TInt& aBitmapId,
                     const TInt& aMaskId );

    /**
     * Creates popup bitmap.
     *
     * @param aRect Popup rect.
     */
    void CreatePopupBitmapL( const TRect& aRect );
    
    /**
     * Creates transparent mask for popup bitmap.
     *
     * @param aRect Popup rect.
     */
    void CreateTransparentMaskL( const TRect& aRect );

    /**
     * Draws the texts.
     *
     * @param aGc Bitmap graphics context.
     */
    void DrawTexts( CFbsBitGc* aGc );

    /**
     * Resolves popup layout type.
     */
    void ResolvePopupLayout();

    /**
     * Provides control eikon env.
     *
     * @return Control eikon env.
     */
    CEikonEnv* EikonEnv();

    /**
     * Returns ETrue if title text needs wrapping.
     * 
     * @param aLayoutType Current popup layout type. 
     * @return ETrue if title text needs wrapping.
     */
    TBool TitleTextNeedsWrapping( const TInt& aLayoutType );

    /**
     * Wraps long text to two lines.
     */
    void WrapTitleTextL();

    /**
     * Draws aText to aGc (in bidi enabled text rect location).
     *
     * @param aGc Bitmap graphics context.
     * @param aTextData Text data.
     * @param aText Text to be drawn.
     */
    static void DrawBidiEnabledText(
            CFbsBitGc* aGc,
            TAknDiscreetPopupTextData& aTextData,
            const TDesC& aText );

    /**
     * Creates icon of given parameters.
     *
     * @param aSkinId Icon skin id.
     * @param aBitmapFile Bitmap file.
     * @param aBitmapId Bitmap id.
     * @param aMaskId Mask id.
     */
    static CGulIcon* CreatePopupIconL(
            const TAknsItemID& aSkinId,
            const TDesC& aBitmapFile,
            const TInt& aBitmapId,
            const TInt& aMaskId );

    /**
     * Returns ETrue if image information is available
     * with given parameters.
     *
     * @param aSkinId Icon skin id.
     * @param aBitmapFile Bitmap file.
     * @param aBitmapId Bitmap id.
     */
    static TBool ImageInfoAvailable(
            const TAknsItemID& aSkinId,
            const TDesC& aBitmapFile,
            const TInt& aBitmapId );

    /**
     * Returns the specified layout rectangle.
     *
     * @param Component parent rect.
     * @param Component layout.
     * @return Layout rect.
     */
    static TRect RectFromLayout( 
        const TRect& aParent, 
        const TAknWindowComponentLayout& aComponentLayout );

    /**
     * Fills text data according to text layout.
     *
     * @param aTextData Text data.
     * @param aParent Component parent rect.
     * @param aComponentLayout Component layout.
     */
    static void TextDataFromLayout(
            TAknDiscreetPopupTextData& aTextData,
            const TRect& aParent, 
            const TAknTextComponentLayout& aComponentLayout );

    /**
     * Returns the specified text layout font.
     *
     * @param Component parent rect.
     * @param Component layout.
     * @param Text layout rect.
     * @return Text layout font.
     */
    static const CFont* FontFromLayout( 
        const TRect& aParent, 
        const TAknTextComponentLayout& aComponentLayout,
        TRect& aTextRect );

    /**
     * Provides popup rect.
     * 
     * @param aWindowVariety Window variety.
     * @param aRect Layout defined popup rect.
     */
    static void GetPopupRect( const TInt& aWindowVariety, TRect& aRect );

private: // data

    /**
     * Popup control of this drawer.
     * Not own.
     */
    CAknDiscreetPopupControl* iControl;

    /**
     * First line of text.
     * Own.
     */
    HBufC* iTitleText;

    /**
     * Second line of text, can be null.
     * Own.
     */
    HBufC* iBodyText;

    /**
     * Icon, can be null.
     * Own.
     */
    CGulIcon* iIcon;

    /**
     * Popup bitmap.
     * Own.
     */
    mutable CFbsBitmap* iPopupBitmap;

    /**
     * Transparent mask for popup bitmap.
     * Own.
     */
    mutable CFbsBitmap* iTransparentMask;

    /**
     * Popup layout type.
     */
    TInt iPopupLayoutType;

    /**
     * Icon rect.
     */
    TRect iIconRect;

    /**
     * Title text field data.
     */
    TAknDiscreetPopupTextData iTitleTextData;

    /**
     * Body text field data.
     */
    TAknDiscreetPopupTextData iBodyTextData;

    /**
     * ETrue if popup has action when tapped.
     */
    TBool iAction;

    };


#endif // C_AKNDISCREETPOPUPDRAWER_H
