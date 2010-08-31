/*
* Copyright (c) 1998-1999 Nokia Corporation and/or its subsidiary(-ies).
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



#if !defined(__EIKLBD_H__)
#define __EIKLBD_H__

#include <e32base.h>
#include <gdi.h>
#include <w32std.h>
#include <eiklbx.h>

class TListItemProperties;
class CListBoxDataExtension;
class MAknsControlContext;

/**
 * The data container class @c TListFontBoundValues class holds size
 * properties of the fonts used in list boxes.
 *
 * @since ER5U
 */
class TListFontBoundValues
    {
public:  // Constructors and destructor

        /**
        * Default C++ constructor
        */
        IMPORT_C TListFontBoundValues();

public:     // Data

        /**
         * The maximum permitted width of list box characters in pixels.
         */
        TInt iMaxNormalCharWidthInPixels;

        /**
         * The list box height in pixels.
         */
        TInt iHeightInPixels;
    };

/**
 * The @c CListBoxData class is the base class for list box data classes.
 * It stores one or more instances of fonts in normal, bold and italic styles.
 *
 * @since ER5U
 */
class CListBoxData : public CBase
    {

    // friend classes
    friend class CListItemDrawer;

public:  // Constructors and destructor

    /**
     * C++ default constructor.
     */
    IMPORT_C CListBoxData();
    
    /**
     * Destructor
     */
    IMPORT_C ~CListBoxData();

public: // New functions

    /**
     * By default Symbian 2nd phase constructor is private. 
     * This one is public.
     *
     * @param aBaseFont Parameter not used in the code.
     */
    IMPORT_C void ConstructL(const CFont* aBaseFont);
    
    /**
     * Returns a pointer to the type of font wanted.
     *
     * @param aItemProperties Definition of font type wanted.
     * @return CFont* Handle to the font or NULL.
     */
     IMPORT_C virtual CFont* 
            Font(const TListItemProperties& aItemProperties) const;

    /**
     * Sets properties (underlining on / off, pen colorm and font) of
     * graphical context.
     *
     * @param aItemProperties Contains properties to set.
     * @param aGc Target of settings.
     */
    IMPORT_C void SetupGc(const TListItemProperties& aItemProperties,
                          CWindowGc& aGc) const;

    /**
     * Queries boundary values of font size.
     *
     * @retun TListFontBoundValues& Reference to boundary value object.
     */
    IMPORT_C const TListFontBoundValues& FontBoundValues() const;

    /**
     * Sets a new height of fonts
     *
     * @param aFontHeightInTwips New height for fonts.
     * @return TInt Symbian error code, @c KErrNone if success.
     */
     IMPORT_C TInt SetFontHeight(TInt aFontHeightInTwips);

    /**
     * Setter for a search string used for viewing search results
     *
     * @param aSearchString The search string.
     */
    IMPORT_C void SetSearchStringL(const TDesC* aSearchString);

    /**
     * Query is search string set
     *
     * @return TBool @c ETrue if search string set and has non zero length.
     *         @c EFalse if no search string set or length is 0.
     */
    IMPORT_C TBool IsSearchString() const;
    
    /**
     * Draws list item text. Supports different drawing for the search string.
     *
     * @param aGc Graphics context used.
     * @param aItemTextRect The item's text rectangle.
     * @param aItemText Text of the item.
     * @param aItemFont Used font.
     * @param aBaseLineOffset Item's base line offset.
     * @param aAlign Text alignment. 
     *        Default alignment is @c CGraphicsContext::ELeft
     */
    IMPORT_C void DrawItem(CWindowGc& aGc,
                           const TRect& aItemTextRect,
                           const TDesC& aItemText,
                           const CFont& aItemFont,
                           const TInt aBaseLineOffset,
                           const CGraphicsContext::TTextAlign aAlign = 
                                 CGraphicsContext::ELeft) const;

    /**
     * Sets list item's text alignment.
     *
     * @param aAlign Text alignment to use.
     */
    inline void SetAlignmentL(CGraphicsContext::TTextAlign aAlign);

    /**
     * Queries used text alignment.
     *
     * @return CGraphicsContext::TTextAlign The text alignment.
     */
    inline CGraphicsContext::TTextAlign Alignment() const;

    /**
     * Access to skin contexts from plain listboxes.
     *
     * @since Series 60 2.0
     * @return MAknsControlContext* Used skin context
     */
    IMPORT_C MAknsControlContext* SkinBackgroundControlContext() const;

    protected:

    /**
     * Sets a background skinning context. Set @c NULL to disable background
     * skinning.
     *
     * @since Series 60 2.0
     * @param aContext Background skinning context.
     */
    IMPORT_C void 
        SetSkinBackgroundControlContextL(MAknsControlContext* aContext);
    
    /**
     * Sets whether skins are enabled.
     *
     * @param aEnabled @c EFalse disable skinning, @c ETrue enable
     */
	IMPORT_C void SetSkinEnabledL(TBool aEnabled);

protected:

    NONSHARABLE_CLASS(CFontsWithStyle) : public CBase
        {

    public:  // Constructors and destructor
        
        /**
         * C++ default constructor.
         */
        CFontsWithStyle();
        
        /**
         * Destructor.
         */
        ~CFontsWithStyle();

	public: // new functions

        /**
         * Releases fonts when they are no longer required.
         */
		IMPORT_C void ReleaseFonts();

        /**
         * Getter for used font style
         * 
         * @return TFontStyle Used font style
         */
		IMPORT_C TFontStyle FontStyle();

        /**
         * Setter for used font style
         *
         * @return aFontStyle Font style to use.
         */
		IMPORT_C void SetFontStyle(TFontStyle aFontStyle);

    public: // data 

        /**
         * @c CArrayPtrFlat<CFont> is used instead of @c CFont*,
         * because in some subclasses this structure
         * can contain more than 1 font.
         */
        CArrayPtrFlat<CFont>* iFonts;

    private: // data

        /**
         * Font style in use
         */
        TFontStyle iFontStyle;
        };

    /**
     * Constructs a new font based on the base font and font style given.
     * Constructed font is added to @c CFontsWithStyle.
     *
     * @param aBaseFont Base fontused in construction
     * @param aFontStyle A new font's style
     * @param aFonts New font is added to this font container.
     */
    IMPORT_C void ConstructFontL(const CFont* aBaseFont, 
                                 TFontStyle aFontStyle, 
                                 CFontsWithStyle& aFonts);

    /**
     * Updates width and heigh information. Used when font is changed. 
     *
     * @param aFont A font from which bound values are taken.
     */
    IMPORT_C void UpdateFontBoundValues(const CFont& aFont);
    
    /**
     * Changes fonts' height. Takes new height as argument and regenerates 
     * font set so that height is modified.
     *
     * @param aFonts Font set to modify
     * @param aFontHeightInTwips New font height
     */
    IMPORT_C TInt RegenerateFonts(CFontsWithStyle& aFonts,
                                  TInt aFontHeightInTwips);

protected:

    /**
     * Normal style font
     */
    CFontsWithStyle iNormalFont;
    
    /**
     * Bold style font
     */
    CFontsWithStyle iBoldFont;
    
    /**
     * Italic style font
     */
    CFontsWithStyle iItalicFont;
    
    /**
     * Font with normal and italic styles
     */
    CFontsWithStyle iBoldItalicFont;
    
    /**
     * String used in list box search field.
     */
    HBufC* iSearchString;

private:

    IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();

private:

    TListFontBoundValues iFontBoundValues;
	CGraphicsContext::TTextAlign iAlign;

private:

    CListBoxDataExtension* iLBDExtension;
    };

// Inline functions 
inline void CListBoxData::SetAlignmentL(CGraphicsContext::TTextAlign aAlign)
	{iAlign=aAlign;}

inline CGraphicsContext::TTextAlign CListBoxData::Alignment() const
	{return iAlign;}

#endif

// End of File