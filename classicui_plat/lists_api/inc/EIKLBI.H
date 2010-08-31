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




#if !defined(__EIKLBI_H__)
#define __EIKLBI_H__  

#include <e32base.h>
#include <gdi.h>


class CWindowGc;
class CListBoxData;
class TListItemProperties;
class TListFontBoundValues;
class MAknsControlContext;


/**
 * The @c CListItemDrawer class is the base class for the list box item drawers 
 * which handle drawing of the contents of list box items.
 * The items may optionally be markable.
 *
 * @since Symbian 5.0
 */
class CListItemDrawer : public CBase
    {

public:

    /**
     * Destructor.
     */
    IMPORT_C ~CListItemDrawer();

    /**
     * Draws the entire item.
     *
     * This function is called by the list box view. As implemented
     * in @c CListItemDrawer, this function draws the item text using 
     * @c DrawActualItem(), and an item mark using @c DrawItemMark().
     * 
     * @param aItemIndex Index of the item to draw. 
     * @param aItemRectPos Position of the rectangle to draw. 
     * @param aItemIsSelected Whether the item is selected. 
     * @param aItemIsCurrent Whether the item is current. 
     * @param aViewIsEmphasized Whether the list box view has the emphasised
     *        flag set (see @c CListBoxView::SetEmphasized()). 
     * @param aViewIsDimmed Whether the list box view has its dimmed flag set
     *        (see @c CListBoxView::SetDimmed()). 
     */
    IMPORT_C virtual void DrawItem(TInt aItemIndex, 
                                   TPoint aItemRectPos, 
                                   TBool aItemIsSelected, 
                                   TBool aItemIsCurrent, 
                                   TBool aViewIsEmphasized, 
                                   TBool aViewIsDimmed) const;

    /**
     * Clears the specified rectangle of this object's graphics context.
     *
     * @param aRect Rectangle to clear.
     */
    IMPORT_C virtual void ClearRect(const TRect& aRect) const;

    /**
     * Gets the width of the specified item.
     *
     * @param aItemIndex The index of the item whose width is to be returned. 
     * @return The width of the item. This is 0 in @c CListItemDrawer
     */
    IMPORT_C virtual TInt ItemWidthInPixels(TInt aItemIndex) const;

    /**
     * Gets the minimum cell size.
     *
     * @return The minimum size for a cell. This is @c TSize(0, 0) 
     *         in @c CListItemDrawer.
     */
    IMPORT_C virtual TSize MinimumCellSize() const;

    /**
     * Sets the graphics context which this object uses for drawing.
     *
     * @param aGc Pointer to the context to use.
     */
    IMPORT_C virtual void SetGc(CWindowGc* aGc);

    /**
     * Gets graphics context which is used for drawing.
     *
     * @return Pointer to the graphics context used for drawing.
     */
    IMPORT_C CWindowGc* Gc() const;

    /**
     * Sets the width of the column containing the mark.
     *
     * @param aWidthInPixels New width for the mark column.
     */
    IMPORT_C virtual void SetMarkColumnWidth(TInt aWidthInPixels);

    /**
     * Sets the width of the gap between the column containing the lists item 
     * marks and the text column.
     *
     * @param aGapInPixels New gap size.
     */
    IMPORT_C virtual void SetMarkGutter(TInt aGapInPixels);

    /**
     * Gets mark column width.
     *
     * @return Mark column width.
     */
    IMPORT_C TInt MarkColumn() const;

    /**
     * Gets the width of the gap between the column containig the lists item
     * marks and the text column.
     *
     * @return Size of the inter-column gutter.
     */
    IMPORT_C TInt MarkGutter() const;

    /**
     * Sets the item cell size.
     * The cell size is the on-screen size of the entire item, including 
     * its text and its item mark.
     *
     * @param aSizeInPixels New size for the item cell.
     */
    IMPORT_C virtual void SetItemCellSize(const TSize& aSizeInPixels);

    /**
     * Gets current item cell size.
     *
     * @since Symbian 3.0
     * @return Item cell size
     */
    IMPORT_C TSize ItemCellSize() const;

    /**
     * Sets the viewing rectangle for this item drawer.
     * This value is not used by the @c CListItemViewer, but may be used by its 
     * derived classes.
     *
     * @param aRect New value for @c iViewRect.
     */
    IMPORT_C virtual void SetViewRect(const TRect& aRect);

    /**
     * Sets whether item tick marks are drawn. 
     * 
     * If the draw mark flag iDrawMark is set, @c DrawItem() leaves space for 
     * the marks column to the left of the text column, and @c DrawItemMark()
     * draws the item marks.
     *
     * @param aDrawMark New value for iDrawMark.
     */
    IMPORT_C void SetDrawMark(TBool aDrawMark);

    /**
     * Gets a rectangle describing where the matcher cursor should be drawn.
     * The default behavious is to return uninitialised @c TRect.
     *
     * @deprecated
     * @param aMatchableText The text of the currently matched string.
     * @param aCharPos The position in the string of the character just matched
     *        in the current incremental match.
     * @param aItemCellYPos Y position of the item cell.
     * @param aCurrentItemIndex Item index for the current item.
     * @return Where the cursor should be drawn.
     */
    IMPORT_C virtual TRect MatcherCursorRect(const TDesC& aMatchableText, 
                                             TInt aCharPos, 
                                             TInt aItemCellYPos, 
                                             TInt aCurrentItemIndex ) const;

    /**
     * Gets the ascent of the matcher cursor.
     * 
     * This is obtained for the item at index @c aCurrentItemIndex.
     * The function returns 0 by default.
     *
     * @deprecated
     * @param aCurrentItemIndex Item index of the target item.
     * @return The height of the matcher cursor.
     */
    IMPORT_C virtual TInt MatcherCursorAscent( TInt aCurrentItemIndex ) const;

    /**
     * Not Used in S60.
     */
    IMPORT_C virtual void DrawItemMark(TBool aItemIsSelected, 
                                       TBool aViewIsDimmed, 
                                       const TPoint& aMarkPos) const;

    /**
     * Sets symbol font for the item drawer.
     * The symbol font is used to draw the standard tick item marks.
     *
     * @param aFont The font to be used.
     */
    IMPORT_C void SetSymbolFont(const CFont* aFont);

    /**
     * Sets the vertical gap between items in the list.
     *
     * @param aGapInPixels New value for the vertical gap between items 
     *        in pixels.
     */
    IMPORT_C void SetVerticalInterItemGap(TInt aGapInPixels);

    /**
     * Sets the font storage data for the item drawer and transfer ownership
     * of that data.
     *
     * @param aData Font storage data .
     */
    IMPORT_C void SetData(CListBoxData* aData);

    /**
     * Gets the font for the specified item.
     * 
     * The function returns @c NULL if no font storage data has been set.
     *
     * @param aItemIndex The index of the item for which the font is returned.
     * @return The item's font.
     */
    IMPORT_C CFont* Font(TInt aItemIndex) const;

    /**
     * Gets the colour and style properties of the specified item.
     *
     * @param aItemIndex The index of the item for which properties
     *        are obtained (Not Used).
     * @return The item's properties.
     */
    IMPORT_C virtual TListItemProperties Properties(TInt aItemIndex) const;

    /**
     * Draws the frame.
     * 
     * Uses the colours set with the fonts and colour functions described above.
     *
     * @deprecated
     * @param aGc The graphics context used to draw the frame.
     * @param aRect The frame's rectangle.
     * @param aFlags The item drawer flags.
     */
    IMPORT_C void DrawFrame(CWindowGc& aGc,
                            const TRect& aRect,
                            TInt aFlags) const;

public:

    /**
     * Provides list box attributes for handling multiple selections. These 
     * flags can be set using the @c CListItemDrawer::SetFlags function.
     */ 
    enum TFlags
        {
        /**
         * If set, specifies the inclusion of a gap into which a tick mark can
         * be drawn if the item is selected. This is used in the following 
         * @c CListItemDrawer class functions:
         *   @c DrawItem(),
         *   @c DrawItemMark(),
         *   @c SetDrawMark()
         */
        EDrawMarkSelection          = 0x0001,
        
        /**
         * If set, draws a highlight over a selected list item. This is used 
         * in the @c CTextListItemDrawer::DoDrawItemText() function.
         */
        EPaintedSelection           = 0x0002,
        
        /** This flag is not supported. */ 
        EDrawOnlyActiveSelection    = 0x0004,
        
        /** If set highlight is disabled. */
        EDisableHighlight = 0x0008,

        /** This flag indicates @c CListboxData to draw pressed down state 
         *  rather than normal highlight on item. Make sure checking this 
         *  flag in subclass's Draw method, if using a custom @c CListboxData 
         *  inheriting from @c CColumnListBoxData or @c CFormattedCellListBoxData.
         */
        EPressedDownState = 0x0010,

        /** This flag indicates the marquee is disabled. If it is set, @c CColumnListBoxData 
         *  or @c CFormattedCellListBoxData would disable maquee temporarily for 
         *  performance reason.
         */
        EDisableMarquee = 0x0020,

        /**
         * This flag indicates that highlight is disabled in list because of
         * single click style.
         */
        ESingleClickDisabledHighlight = 0x0040,
        
        /**
         * This flag indicates that single click mode is enabled.
         */
        ESingleClickEnabled = 0x0080
        };

public:

    /**
     * Provides attributes for list items
     */
    enum TListItemAttribute

        {
        /** Highlight for current text. */
        ECurrent    = 0x0001,       // may be drawn with a frame

        /**
         * Highlight for text when the listbox view is emphasized.
         *
         * This is used in the following @c CListBoxView class functions:
         * @c DrawItem(), @c DrawMatcherCursor(), @c SetEmphasized().
         */
        EEmphasized = 0x0002,       // special highlight (not selected)
        
        /**
         * Highlight for text that is selected. This is used in the following 
         * functions: @c CColumnListBoxItemDrawer::DrawItemText(), 
         * @c CHierarchicalListItemDrawer::DrawActualItem(), 
         * @c CDirContentsListItemDrawer::DrawActualItem().
         */
        ESelected   = 0x0004,       // usually different than emphasized
        
        /**
         * Sum of all the above attributes.
         * This last attribute is used to control that one can use only
         * valid attributes above. So do not use it at all.         
         */
        EMask       = 0x0007 // sum of all others attributes

        };

public:

    /**
     * Sets the colour used to draw non-highlighted text.
     *
     * @param aColor The text colour.
     */
    inline void SetTextColor(TRgb aColor);

    /**
     * Sets the colour used to draw the background for non-highlighted items.
     *
     * @param aColor The background colour.
     */
    inline void SetBackColor(TRgb aColor);

    /**
     * Sets the colour used to draw highlighted text.
     *
     * @param aColor The highlighted text colour.
     */
    inline void SetHighlightedTextColor(TRgb aColor);

    /**
     * Sets the colour used to draw the background for highlighted items.
     *
     * @param aColor The highlighted background colour.
     */
    inline void SetHighlightedBackColor(TRgb aColor);

    /**
     * Sets the colour used to draw dimmed text.
     *
     * @param aColor The dimmed text colour.
     */
    inline void SetDimmedTextColor(TRgb aColor);

    /**
     * Sets the colour used to draw the background for dimmed items.
     *
     * @param aColor The background colour for dimmed items.
     */
    inline void SetDimmedBackColor(TRgb aColor);

    /**
     * Gets the colour used to draw non-highlighted text.
     *
     * @return The text colour.
     */
    inline TRgb TextColor() const;

    /**
     * Gets the colour used to draw the background for non-highlighted items.
     *
     * @return Background colour.
     */
    inline TRgb BackColor() const;

    /**
     * Gets the colour used to draw highlighted text.
     *
     * @return The highlighted text colour.
     */
    inline TRgb HighlightedTextColor() const;

    /**
     * Gets the colour used to draw the background for highlighted items.
     *
     * @return The highlighted background colour.
     */
    inline TRgb HighlightedBackColor() const;

    /**
     * Gets the colour used to draw dimmed text.
     *
     * @return The dimmed text colour. 
     */
    inline TRgb DimmedTextColor() const;

    /**
     * Gets the colour used to draw the background for dimmed items.
     *
     * @return The background colour for dimmed items.
     */
    inline TRgb DimmedBackColor() const;

    /**
     * Gets the item drawer flags.
     *
     * @return The item drawer flags.
     */
    inline TInt Flags() const;

    /**
     * Sets the item drawer flags.
     *
     * @param aFlags The new item drawer flags.
     */
    IMPORT_C void SetFlags(TInt aFlags);

    /**
     * Sets the item drawer flags.
     *
     * @param aFlags The new item drawer flags.
     */
    IMPORT_C void ClearFlags(TInt aFlags);

    /**
     * Access to skin contexts.
     *
     * @since S60 2.0
     * @return Pointer to skin background control context.
     */
    IMPORT_C MAknsControlContext  *SkinBackgroundControlContext() const;
    /**
     * Ability to enable skins in listboxes.
     *
     * @since S60 2.0
     * @param aEnabled parameter for enabling/disabling skin.
     *        @c ETrue enables skin,
     *        @c EFalse disables skin
     */
    IMPORT_C void SetSkinEnabledL(TBool aEnabled);

protected:

    /**
     * C++ default constructor.
     */
    IMPORT_C CListItemDrawer();

    /**
     * Draws item text.
     * 
     * This function is called by @c CListItemDrawer::DrawItem() with 
     * appropriate arguments. Its purpose is to draw the actual item 
     * - everything other than the item mark - into the graphics context.
     *
     * @param aItemIndex Which item to draw. 
     * @param aActualItemRect Where the item should be drawn. 
     * @param aItemIsCurrent Whether the item is current. 
     * @param aViewIsEmphasized Whether the list box view is emphasised. 
     * @param aViewIsDimmed Whether the list box view is dimmed. 
     * @param aItemIsSelected Whether the list box item is selected.
     */
    virtual void DrawActualItem(TInt aItemIndex, 
                                const TRect& aActualItemRect, 
                                TBool aItemIsCurrent, 
                                TBool aViewIsEmphasized, 
                                TBool aViewIsDimmed, 
                                TBool aItemIsSelected) const = 0;

    /**
     * Resets the pen style, brush style, brush colour etc. to suitable 
     * starting values for this class. 
     * 
     * This function is called after every drawing operation.
     */
    IMPORT_C virtual void ResetGc() const;

    /**
     * Gets the colour used to draw tick marks. 
     *
     * A tick mark usually indicates that an item is selected.
     *
     * @return The tick mark colour.
     */
    inline TRgb MarkColor() const;

    /**
     * Gets the vertical gap between items in pixels.
     *
     * @return The vertical gap between items in pixels.
     */
    IMPORT_C TInt VerticalInterItemGap() const;
    
    /**
     * Sets up the graphics context for the specified item.
     *
     * @param aItemIndex The item for which the graphics context 
     *        will be set up.
     */
    IMPORT_C void SetupGc(TInt aItemIndex) const;

private:

    IMPORT_C virtual TAny* Reserved_1();

    inline TInt& VerticalInterItemGap();

    inline const CFont* SymbolFont() const;

    inline const CFont*& SymbolFont();

protected:
    
    /** Item's cell size. */
    TSize iItemCellSize;

    /** Mark gutter. */
    TInt iMarkGutter;

    /** Mark column width. */
    TInt iMarkColumnWidth;

    /** View area. */
    TRect iViewRect;

    /** Draw mark. */
    TBool iDrawMark;

    /** Graphics context controller. */
    CWindowGc* iGc;

    /** Color of text. */ 
    TRgb iTextColor;
    
    /** Background color. */
    TRgb iBackColor;

    /** Color of highlighted text. */
    TRgb iHighlightedTextColor; 

    /** Highlighted background color. */
    TRgb iHighlightedBackColor;

    /** Color of dimmed text. */
    TRgb iDimmedTextColor;

    /** Color of dimmed background. */
    TRgb iDimmedBackColor;

    /** Mark color. */
    TRgb iMarkColor;

    /** Data model. */
    CListBoxData* iData;

private:

    const CFont* iSymbolFont;

    TInt iVerticalInterItemGap;

    TInt iSpare;

    TUint iFlags;

    };




class MTextListBoxModel;


/**
 * Item drawer which can handle text.
 * 
 * Used by @c CListBoxView to draw individual list box items 
 * for a @c CEikTextListBox
 */
class CTextListItemDrawer : public CListItemDrawer
    {

public:

    /**
     * C++ default constructor.
     */
    IMPORT_C CTextListItemDrawer();
    
    /**
     * Destructor.
     */
    IMPORT_C ~CTextListItemDrawer();

    /**
     * C++ default constructor.
     *
     * Constructs a new text item drawer which draws the data of the specified 
     * model using the supplied font.
     *
     * @param aTextListBoxModel The model whose items will be drawn. 
     * @param aFont The font in which the items will be drawn.
     */
    IMPORT_C CTextListItemDrawer(MTextListBoxModel* aTextListBoxModel, 
                                 const CFont* aFont);

    /**
     * Handles 2nd phase construction.
     *
     * @param aFont The font in which the list box items will be drawn.
     */
    IMPORT_C void ConstructL(const CFont* aFont);

    /**
     * Draws the actual item contents for the specified item in the specified 
     * rectangle.
     *
     * @param aItemIndex Index of the item to draw. 
     * @param aActualItemRect Area to draw into. 
     * @param aItemIsCurrent @c ETrue if the item is current. 
     * @param aViewIsEmphasized @c ETrue if the view is emphasised. 
     * @param aViewIsDimmed Ignored
     * @param aItemIsSelected @c ETrue if the item is selected.
     */
    IMPORT_C virtual void DrawActualItem(TInt aItemIndex, 
                                         const TRect& aActualItemRect, 
                                         TBool aItemIsCurrent, 
                                         TBool aViewIsEmphasized, 
                                         TBool aViewIsDimmed,
                                         TBool aItemIsSelected) const;

    /**
     * Gets the width in pixels of the specified item.
     *
     * @param aItemIndex The index of the item for which the width is obtained.
     * @return The specified item’s width in pixels.
     */ 
    IMPORT_C virtual TInt ItemWidthInPixels(TInt aItemIndex) const;

    /**
     * Gets the minimum size of a cell based on the font and the number of 
     * characters in the cell.
     *
     * @return The minimum size for a cell, in pixels.
     */
    IMPORT_C virtual TSize MinimumCellSize() const;

    /**
     * Sets the graphics context.
     *
     * @param aGc The graphics context to use.
     */
    IMPORT_C virtual void SetGc(CWindowGc* aGc);

    /**
     * Sets the number of characters in a cell. 
     * This value affects only @c MinimumCellSize().
     *
     * @param aNumOfCharsToDisplayInCell Number of characters to 
     *        display in a cell.
     */
    IMPORT_C void SetCellWidthInChars(TInt aNumOfCharsToDisplayInCell);

    /**
     * Gets the position and size of the matcher cursor.
     *
     * @deprecated
     * @param aMatchableText String currently being matched. Not Used.
     * @param aCharPos Position within the string. Not Used.
     * @param aItemCellYPos Y position of the item cell in pixels. Not Used.
     * @param aCurrentItemIndex Item index for the current item. Not Used.
     * @return The rectangle covered by the matcher cursor, in pixels.
     */
    IMPORT_C virtual TRect MatcherCursorRect(const TDesC& aMatchableText, 
                                             TInt aCharPos, 
                                             TInt aItemCellYPos, 
                                             TInt aCurrentItemIndex ) const;

    /**
     * No Implementation. 
     *
     * Derived classes that deal with text and want to support incremental 
     * matching in listboxes need to redefine this function.
     * Should be used to get the ascent of the matcher cursor in pixels.
     *
     * @deprecated
     * @param aCurrentItemIndex Index of the current item. Not Used.
     * @return Always returns 0;
     */
    IMPORT_C virtual TInt MatcherCursorAscent( TInt aCurrentItemIndex ) const;

    /**
     * Sets the font.
     *
     * @param aFont The new font.
     */
    IMPORT_C void SetFont(const CFont* aFont);

    /**
     * Sets the search string.
     *
     * @param aSearchString The new search string.
     */
    IMPORT_C void SetSearchStringL(const TDesC* aSearchString);

    /**
     * Gets font for the specified item.
     *
     * @param aIndex The index of the target item.
     * @return Specified item's font.
     */
    IMPORT_C const CFont* Font(TInt aIndex) const;

    // SAPLAF new methods.


    /**
     * Sets item mark position.
     *
     * @param aPos The new position.
     */
    inline void SetItemMarkPosition(TInt aPos);

    /**
     * Gets item mark position.
     *
     * @return Position of the Item mark.
     */
    inline TInt ItemMarkPosition() const;

    /**
     * Sets the item mark replacement.
     *
     * @param aReplacement The new replacement descriptor.
     */
    inline void SetItemMarkReplacement(const TDesC &aReplacement);

    /**
     * Gets item mark replacement.
     *
     * @return Pointer to the replacement string.
     */
    inline TPtrC ItemMarkReplacement() const;

    /**
     * Sets item mark reverse to be active or not.
     *
     * @param aReverse The new setting.
     *        @c ETrue if item is marked reversed.
     */
    inline void SetItemMarkReverse(TBool aReverse);

    /**
     * Check if the item has been marked reversed is active.
     *
     * @return Indicates if active or not.
     *         @c ETrue if active
     */
    inline TBool ItemMarkReverse() const;


protected:

    /**
     * Draws text.
     *
     * This function is invoked by @c DrawItemText() to draw a string into a 
     * rectangular area of @c iGc.
     *
     * @param aDes The string to draw. 
     * @param aItemTextRect Area to draw into. 
     * @param aItemIsCurrent @c ETrue if the item is current. 
     * @param aViewIsEmphasized @c ETrue if the view is emphasised. 
     * @param aItemIsSelected @c ETrue if the item is selected. 
     * @param aItemIndex The item’s index.
     */
    IMPORT_C virtual void DoDrawItemText(const TDesC& aDes, 
                                         const TRect& aItemTextRect, 
                                         TBool aItemIsCurrent, 
                                         TBool aViewIsEmphasized, 
                                         TBool aItemIsSelected, 
                                         TInt aItemIndex) const;

    /**
     * Draw item text.
     * 
     * This function is invoked by @c DrawActualItem() to draw the item text.
     *
     * @param aItemIndex Index of the item to draw. 
     * @param aItemTextRect Area to draw into. 
     * @param aItemIsCurrent @c ETrue if the item is current. 
     * @param aViewIsEmphasized @c ETrue if the view is emphasised.
     * @param aItemIsSelected @c ETrue if the item is selected. 
     */
    IMPORT_C virtual void DrawItemText(TInt aItemIndex, 
                                       const TRect& aItemTextRect, 
                                       TBool aItemIsCurrent, 
                                       TBool aViewIsEmphasized, 
                                       TBool aItemIsSelected) const;

    /**
     * Resets the graphics context.
     * This function invokes @c CListItemDrawer::ResetGc() and resets the pen 
     * colour to @c iTextColor.
     */
    IMPORT_C virtual void ResetGc() const;

private:

    IMPORT_C virtual TAny* Reserved_1();

protected:

    /** List box model for the drawer. */
    MTextListBoxModel* iModel;

    /** Font used by the drawer. */
    const CFont* iFont;

private:
    
    TInt iNumOfCharsInCell;

    // AVKON LAF 

    TInt iItemMarkPos;

    TPtrC iItemMarkReplacement;

    TBool iItemMarkReverse;

    // AVKON LAF ENDS 

    };




/**
 * The @c TListItemProperties class packages together the color and 
 * style properties which can be applied when drawing the contents 
 * of list box items.
 *
 * @since Symbian ER5U
 */

class TListItemProperties

    {

public:

    /**
     * C++ default constructor.
     */
    IMPORT_C TListItemProperties();

public:

    /**
     * Sets whether the list item is drawn bold or not bold.
     *
     * @deprecated
     * @param aBold @c ETrue to draw the list item bold. 
     *        @c EFalse otherwise.
     */
    inline void SetBold(TBool aBold);

    /**
     * Tests whether the list item is drawn bold.
     *
     * @deprecated
     * @return @c ETrue if the list item is drawn bold. 
     *         @c EFalse otherwise.
     */
    inline TBool IsBold() const;

    /**
     * Sets whether or not the list item is drawn in italics.
     *
     * @deprecated
     * @param aItalics @c ETrue to draw the list item in italics. 
     *        @c EFalse otherwise.
     */
    inline void SetItalics(TBool aItalics);

    /**
     * Tests whether the list item is italicised.
     *
     * @deprecated
     * @return @c ETrue if the list item is drawn in italics. 
     *         @c EFalse otherwise.
     */
    inline TBool IsItalics() const;

    /**
     * Sets whether or not the list item is drawn with an underline.
     *
     * @param aUnderlined @c ETrue to draw the list item with an underline. 
     *        @c EFalse otherwise.
     */
    inline void SetUnderlined(TBool aUnderlined);

    /**
     * Test whether the list item is drawn with an underline.
     *
     * @return @c ETrue if the list item is drawn with an underline. 
     *         @c EFalse otherwise.
     */
    inline TBool IsUnderlined() const;

    /**
     * Sets list item dim state. 
     * 
     * An item is usually drawn dimmed to indicate that it cannot accept 
     * user input.
     *
     * @param aDimmed @c ETrue to draw the list item dimmed. @c EFalse otherwise.
     */
    inline void SetDimmed(TBool aDimmed);

    /**
     * Tests list item dim state. 
     *
     * An item is usually drawn dimmed to indicate that it cannot accept 
     * user input.
     *
     * @return @c ETrue if the list item is dimmed. 
     *         @c EFalse otherwise.
     */
    inline TBool IsDimmed() const;

    /**
     * Sets the list item’s colour.
     *
     * @param aColor The list item’s colour.
     */
    inline void SetColor(TRgb aColor);

    /**
     * Gets the list item’s colour.
     *
     * @return The list item’s colour.
     */
    inline TRgb Color() const;

    /**
     * Activate/deactivate separator after item.
     *
     * @deprecated
     * @param aSeparator Active/deactive selector.
     *        @c ETrue = Active.
     *        @c EFalse = Deactivated.
     */
    inline void SetSeparatorAfter(TBool aSeparator);

    /**
     * Check if separator after item is active.
     *
     * @deprecated
     * @return @c ETrue if Active.
     *         @c EFalse if Deactivated.
     */
    inline TBool IsSeparatorAfter() const;

    /**
     * Select to hide the item .
     *
     * @param aHidden Defines whether the item is hidden.
     *        @c ETrue = Hidden
     */
    inline void SetHiddenSelection(TBool aHidden);

    /**
     * Check if the item is hidden.
     *
     * @return @c ETrue if item is hidden.
     */
    inline TBool IsSelectionHidden() const;

private:

    TUint iFlags;

    TRgb iColor;

private:

    enum

        {

        ELbxItemBold        = 0x0001,

        ELbxItemItalics     = 0x0002,

        ELbxItemUnderlined  = 0x0004,

    ELbxItemDimmed      = 0x0008,

    ELbxItemSeparatorAfter  = 0x0010,
    
    ELbxItemSelectionHidden = 0x0020
    
        };

    };



//

// Inlines

//



inline void CListItemDrawer::SetTextColor(TRgb aColor)

    {iTextColor=aColor;}

inline void CListItemDrawer::SetBackColor(TRgb aColor)

    {iBackColor=aColor;}

inline void CListItemDrawer::SetHighlightedTextColor(TRgb aColor)

    {iHighlightedTextColor=aColor;}

inline void CListItemDrawer::SetHighlightedBackColor(TRgb aColor)

    {iHighlightedBackColor=aColor;}

inline void CListItemDrawer::SetDimmedTextColor(TRgb aColor)

    {iDimmedTextColor=aColor;}

inline void CListItemDrawer::SetDimmedBackColor(TRgb aColor)

    {iDimmedBackColor=aColor;}

inline TRgb CListItemDrawer::TextColor() const

    {return iTextColor;}

inline TRgb CListItemDrawer::BackColor() const

    {return iBackColor;}

inline TRgb CListItemDrawer::HighlightedTextColor() const

    {return iHighlightedTextColor;}

inline TRgb CListItemDrawer::HighlightedBackColor() const

    {return iHighlightedBackColor;}

inline TRgb CListItemDrawer::DimmedTextColor() const

    {return iDimmedTextColor;}

inline TRgb CListItemDrawer::DimmedBackColor() const

    {return iDimmedBackColor;}

inline TRgb CListItemDrawer::MarkColor() const

    {return iMarkColor;}

inline TInt CListItemDrawer::Flags() const

    {return iFlags;}



inline TBool TListItemProperties::IsItalics() const

    {return iFlags&ELbxItemItalics;}

inline TBool TListItemProperties::IsBold() const

    {return iFlags&ELbxItemBold;}

inline TBool TListItemProperties::IsUnderlined() const

    {return iFlags&ELbxItemUnderlined;}

inline TBool TListItemProperties::IsDimmed() const

    {return iFlags&ELbxItemDimmed;}

inline TBool TListItemProperties::IsSeparatorAfter() const

    {return iFlags&ELbxItemSeparatorAfter;}

inline TBool TListItemProperties::IsSelectionHidden() const

    {return iFlags&ELbxItemSelectionHidden;}



inline void TListItemProperties::SetColor(TRgb aColor)

    {iColor=aColor;}

inline TRgb TListItemProperties::Color() const

    {return iColor;}

inline void TListItemProperties::SetBold(TBool aBold)

    {

    if (aBold) 

        iFlags|=ELbxItemBold;

    else

        iFlags&=(~ELbxItemBold);

    }

inline void TListItemProperties::SetItalics(TBool aItalics)

    {

    if (aItalics)

        iFlags|=ELbxItemItalics;

    else

        iFlags&=(~ELbxItemItalics);

    }

inline void TListItemProperties::SetUnderlined(TBool aUnderlined)

    {

    if (aUnderlined)

        iFlags|=ELbxItemUnderlined;

    else

        iFlags&=(~ELbxItemUnderlined);

    }

inline void TListItemProperties::SetDimmed(TBool aDimmed)

    {

    if (aDimmed)

        iFlags|=ELbxItemDimmed;

    else

        iFlags&=(~ELbxItemDimmed);

    }



inline void TListItemProperties::SetSeparatorAfter(TBool aSeparator)

    {

    if (aSeparator) 

        iFlags|=ELbxItemSeparatorAfter;

    else

        iFlags&=(~ELbxItemSeparatorAfter);

    }


inline void TListItemProperties::SetHiddenSelection(TBool aBlocked)

    {

    if (aBlocked) 

        iFlags|=ELbxItemSelectionHidden;

    else

        iFlags&=(~ELbxItemSelectionHidden);

    }




 

// AVKON LAF 

inline void CTextListItemDrawer::SetItemMarkPosition(TInt aPos) { iItemMarkPos = aPos; }

inline TInt CTextListItemDrawer::ItemMarkPosition() const { return iItemMarkPos; }

inline void CTextListItemDrawer::SetItemMarkReplacement(const TDesC & aReplacement) { iItemMarkReplacement.Set(aReplacement); }

inline TPtrC CTextListItemDrawer::ItemMarkReplacement() const { return iItemMarkReplacement; }

inline void CTextListItemDrawer::SetItemMarkReverse(TBool aReverse) { iItemMarkReverse = aReverse; }
inline TBool CTextListItemDrawer::ItemMarkReverse() const { return iItemMarkReverse; }

// END OF AVKON LAF 



#endif  // __EIKLBI_H__

// End of File
