/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#if !defined(__EIKCLBD_H__)
#define __EIKCLBD_H__

#include <e32base.h>
#include <gdi.h>

#include <eiklbd.h>
#include <avkon.hrh>
#include <babitflags.h>    // for TBitFlags32

class CWindowGc;
class CGulIcon;
class CColumnListBoxDataExtension;
class MAknsControlContext;
class CCoeControl;
class TAknsItemID;
class CAknsEffectAnim;
class CAknsListBoxBackgroundControlContext;
class CAknLayoutData;
class TAknWindowLineLayout;
class TAknTextLineLayout;
class TAknWindowComponentLayout;
class TAknTextComponentLayout;
class MAknsSkinInstance;

/**
* A callback interface for overriding highlight animation input layer
* preparation in derived classes. Usually drawing the background under the
* highlight rect will yield the right kind of result. The size of the render
* target is equal to item cell size.
*
* @since 3.0
*/
class MColumnListBoxAnimBackgroundDrawer
    {
    public:

        /**
         * Draws the background under the current highlight.
         *
         * Should be implemented in the derived class .
         *
         * @param aGc bitmapped graphics context to be drawn.
         * @return @c ETrue if Succeeded.
         */
        virtual TBool DrawHighlightAnimBackground( CFbsBitGc& aGc ) const = 0;
    };

/**
 * The @c CColumnListBoxData class handles the data required to draw a column 
 * list box.
 *
 * The class performs drawing for @c CColumnListBoxItemDrawer. Columns are 
 * numbered from 0 from left to right, and extra column data can be set 
 * for each.
 *
 * N.B.: The standard width of a column drawn by @c CColumnListListBoxData is  
 * 0 pixels, so at the very least a column width should be set for each column 
 * in a column list box.    
 *
 * This class is not intended for user derivation. 
 */
class CColumnListBoxData : public CListBoxData
    {
    friend class CColumnListBoxDataExtension;
public:

    /**
     * Represents the colours used within the border and for the optional 
     * single pixel border outlines.
     *
     * These colours are stored using @c TRgb values.
     */
    class TColors
        {
    public:

        /**
         * C++ default constructor.
         */
        IMPORT_C TColors();
    public:

        /**
         * Stores text Color.
         */
        TRgb iText;

        /**
         * Stores background color.
         */
        TRgb iBack;

        /**
         * Stores highLighted text color.
         */ 
        TRgb iHighlightedText;

        /**
         * Stores highlighted background colour.
         */
        TRgb iHighlightedBack;
        };

public:

    /**
     * Two-phased constructor.
     *
     * Allocates and constructs a column list box data object.
     *
     * Constructs an array in which the column data is held.
     *
     * @return New @c CColumnListBoxData.
     */
    IMPORT_C static CColumnListBoxData* NewL();
    
    /**
     * Destructor.
     */
    IMPORT_C ~CColumnListBoxData();

public:

    /**
     * Gets the index of the last defined column.
     *
     * @return The index of the last defined column or @c KErrNotFound if no 
     *         column has been defined.
     */
    IMPORT_C TInt LastColumn() const;
    
    /**
     * Gets the specified column’s width in pixels.
     *
     * @param aColumn The index of the column for which the width is obtained.
     * @return The specified column’s width in pixels. Zero is returned if no 
     *         column exists at the specified index.
     */
    IMPORT_C TInt ColumnWidthPixel(TInt aColumn) const;

    /**
     * Sets the specified column’s width in pixels.
     * 
     * If the column does not exist, one is added at the specified index, 
     * with the specifed width.
     *
     * @param aColumn The index of the column for which the width is to be set.
     * @param aWidth The width in pixels.
     */
    IMPORT_C void SetColumnWidthPixelL(TInt aColumn,TInt aWidth);
    
    /**
    * Not used in S60.
    */
    IMPORT_C TInt ColumnHorizontalGap(TInt aColumn) const;

    /**
    * Not used in S60.
    */
    IMPORT_C void SetColumnHorizontalGapL(TInt aColumn,TInt aGap);

    /**
     * Gets column's baseline.
     *
     * @param aColumn target column.
     * @return Vertical position.
     */
    IMPORT_C TInt ColumnBaselinePos(TInt aColumn) const;

    /**
     * Sets columns baseline position.
     *
     * @param aColumn Target column.
     * @param aPos Wanted position.
     */
    IMPORT_C void SetColumnBaselinePosL(TInt aColumn,TInt aPos);

    /**
     * Gets column's margins.
     *
     * @param aColumn Target column.
     * @return The columns margins.
     */
    IMPORT_C TMargins ColumnMargins(TInt aColumn) const;
    
    /**
     * Sets column's margins.
     *
     * @param aColumn Target column.
     * @param aMargins Wanted margins.
     */
    IMPORT_C void SetColumnMarginsL(TInt aColumn,TMargins aMargins);
    
    /**
     * Gets font used by the column.
     *
     * @param aColumn Target column.
     * @return Used font.
     */
    IMPORT_C const CFont* ColumnFont(TInt aColumn) const;

    /**
     * Sets column's font.
     *
     * @param aColumn Target column.
     * @param aFont Wanted font.
     */
    IMPORT_C void SetColumnFontL(TInt aColumn,const CFont* aFont);

    /**
     * Gets the text alignment for the specified column.
     *
     * @param  aColumn The index of the column for which the alignment 
     *         is obtained.
     * @return The text alignment for the specified column. The default 
     *         is @c ELeft.
     */
    IMPORT_C CGraphicsContext::TTextAlign ColumnAlignment(TInt aColumn) const;
    
    /**
     * Sets the text alignment for the specified column.
     *
     * If the column does not exist, it is added with the specified index 
     * to the array.
     *
     * @param aColumn The index of the column for which alignment is set.
     * @param aAlign The text alignment to use. The default is @c ELeft.
     */
    IMPORT_C void SetColumnAlignmentL(TInt aColumn,
                                      CGraphicsContext::TTextAlign aAlign);

    /**
    * Not used in S60.
    */
    IMPORT_C CGraphicsContext::TPenStyle ColumnSeparatorStyle(
                                                        TInt aColumn) const;
    /**
    * Not used in S60.
    */
    IMPORT_C void SetColumnSeparatorStyleL(TInt aColumn, 
                                           CGraphicsContext::TPenStyle aStyle);

    /**
     * Checks whether the column is optional.
     *
     * @param aColumn Target column.
     * @return @c ETrue if the column is optional.
     */
    IMPORT_C TBool ColumnIsOptional(TInt aColumn) const;
    
    /**
     * Sets whether the column is optional.
     *
     * @param aColumn Target column.
     * @param aIsOptional Wanted setting, @c ETrue if column is optional.
     */
    IMPORT_C void SetOptionalColumnL(TInt aColumn,TBool aIsOptional);

    /**
     * Checks whether the column contains graphics.
     *
     * @param aColumn Target column.
     * @return @c ETrue if column contains graphics.
     */
    IMPORT_C TBool ColumnIsGraphics(TInt aColumn) const;

    /**
     * Sets whether the column shows graphics.
     *
     * @param aColumn Target column.
     * @param aIsGraphics Wanted setting.
     */
    IMPORT_C void SetGraphicsColumnL(TInt aColumn,TBool aIsGraphics);

    /**
     * Checks if the column is a number.
     *
     * @param aColumn Target column.
     * @return @c ETrue if it is a number.
     */
    IMPORT_C TBool ColumnIsNumber(TInt aColumn) const;

    /**
     * Sets whether the column is a number. 
     *
     * @param aColumn Target columun.
     * @param aIsNumber Wanted setting. @c ETrue if it is a number.
     */
    IMPORT_C void SetNumberColumnL(TInt aColumn,TBool aIsNumber);

    /**
     * Gets the icon array. 
     *
     * These icons contain the bitmaps that are displayed in graphical columns.
     *
     * @return Pointer to the icon array.
     */
    IMPORT_C CArrayPtr<CGulIcon>* IconArray() const;

    /**
     * Sets icon array.
     *
     * @param aArray Wanted icon collection .
     */
    IMPORT_C void SetIconArray(CArrayPtr<CGulIcon>* aArray);

    /**
     * Gets TextClipGap, the gap between words in a text clip, for the 
     * given column.
     *
     * @param aSubCellIndex Index to target column.
     * @return TextClipGap.
     */
    IMPORT_C TInt ColumnTextClipGap(TInt aSubCellIndex) const;
    
    /**
     * Sets columns TextClipGap, the gap between words in a text clip.
     *
     * @param aSubCellIndex Index of the target column.
     * @param aSize Wanted TextClipGap size. 
     */
    IMPORT_C void SetColumnTextClipGapL(TInt aSubCellIndex, TInt aSize);
    
    /**
     * Gets the specified font for the specified column.
     *
     * @param aItemProperties Whether the required font is:
     *        bold, italic, bold and italic or normal.
     * @param aColumn The index of the column for which the font is obtained.
     * @return The specified column’s, specified font. Null, the 
     *         default, if no font is set for the column.
     */
    IMPORT_C CFont* Font(const TListItemProperties& aItemProperties, 
                         TInt aColumn) const;

    /**
     * Gets the specified column’s surrounding rectangle.
     *
     * @param aColumn The index of the column for which the rectangle 
     *                is obtained.
     * @param aRect On return contains the specified column’s rectangle.
     * @return @c ETrue if successful. @c EFalse if a non-existent column 
     *               was specified.
     */
    IMPORT_C TBool MakeColumnRect( TInt aColumn, TRect& aRect );

    /**
     * Draws a single row.
     *
     * The text @c aText is parsed into columns and is split using 
     * @c KColumnListSeparator. Text or bitmaps are drawn according to whether 
     * the column has been set as a graphical column 
     * (see @c SetGraphicsColumnL()). Column cells within the row are drawn 
     * from left to right.
     *
     * @param aItemProperties The properties of each column in the row.
     * @param aGc The graphics context to draw into.
     * @param aText The text to parse and draw.
     * @param aRect Bounding rectangle for the entire row.
     * @param aHighlight @c ETrue to draw the item highlighted. 
     *        @c EFalse otherwise.
     * @param aColors The colours to use if the item is highlighted.
     */
    IMPORT_C virtual void Draw(const TListItemProperties& aItemProperties, 
                               CWindowGc& aGc,
                               const TDesC* aText,
                               const TRect& aRect,
                               TBool aHighlight,
                               const TColors& aColors) const;
                               
    /**
    * internal
    */
    void DrawSimple(const TListItemProperties& aItemProperties, CWindowGc& aGc,const TDesC* aText,const TRect& aRect,TBool aHighlight,const TColors& aColors) const;
    /**
     * Sets position of listbox line.
     *
     * @param aPosition Wanted position.
     */
    IMPORT_C void SetSeparatorLinePosition(
                                        TAknSeparatorLinePosition aPosition);

    /**
     * Gives out separator line position.
     *
     * @return Separator position.
     */
    IMPORT_C TAknSeparatorLinePosition SeparatorLinePosition() const;

    /**
     * 
     * @deprecated
     *
     * Gives out layout data for separator line drawing.
     *
     * @return Requested layout data.
     */
    IMPORT_C CAknLayoutData *LayoutData() const;
    
    /**
     * 
     * @deprecated
     *
     * Checks if the layout has been initialized.
     *
     * @return @c ETrue if initialized.
     */
    IMPORT_C TBool LayoutInit() const;
    
    /**
     * 
     * @deprecated
     *
     * Sets the initialization .
     *
     * @param aValue Wanted value (@c ETrue = initialized).
     */
    IMPORT_C void SetLayoutInit(TBool aValue) const;

    /**
     * Enables / disables underlining per text column,
     * if and only if @c TListItemProperties also has underlining enabled.
     * If this method is not called and @c TListItemProperties has underlining
     * enabled, drawing will revert to old style where only first text column
     * will be underlined.
     *
     * @since S60 3.0
     * @param aUnderlinedColumns Bitmask of columns to be underlined.
     */    
    IMPORT_C void SetColumnUnderlined( TBitFlags32 aUnderlinedColumns );

private:
    struct SColumn
        {
        TInt iColumn; // Must be first entry
        TInt iWidth;
        TMargins iMargins;
        TInt iVerticalCap;
        const CFont* iBaseFont;
        TInt iActualFontIndex;
        TBool iGraphics;
    TBool iOptional;
    TInt iBaseline;
        CGraphicsContext::TTextAlign iAlign;
    CGraphicsContext::TPenStyle iSeparator;
    TInt iTextClipGap;
    TBool iNumberColumn;
    // the next are for storing x-coordinates of a column for the drawing algorithm.
    __MUTABLE TInt iX;
    __MUTABLE TInt iEndX;
        };
protected:

    /**
     * C++ default constructor.
     */
    IMPORT_C CColumnListBoxData();

    /**
     * A second phase constructor. 
     *
     * Highlight animation will be created by default (if it is provided 
     * by the skin).
     */
    IMPORT_C void ConstructLD();

    /**
     * Second phase constructor for subclasses that want to override highlight
     * animation creation.
     *
     * @since 3.0
     * @param aAnimationIID Skin item identifier of the constructed animation. 
     *        Passing @c KAknsIIDNone will disable highlight animation.
     */
    IMPORT_C void ConstructLD( const TAknsItemID& aAnimationIID );

private:
    
    IMPORT_C TInt ColumnX(TInt aColumn) const;
    IMPORT_C void SetColumnXL(TInt aColumn,TInt aX) const; // note, const! (do not affect external state)
    //
    IMPORT_C TInt ColumnEndX(TInt aColumn) const;
    IMPORT_C void SetColumnEndXL(TInt aColumn,TInt aEndX) const; // note, Const!

    void AddColumnL(TInt aColumn);
    SColumn& At(TInt aArrayIndex);
    const SColumn& At(TInt aArrayIndex) const;
    TBool FindColumnIndex(TInt& aArrayIndex,TInt aColumn) const;
    void FindColumnIndexOrAddL(TInt& aArrayIndex,TInt aColumn);
    TInt AddActualFontL(const CFont* aBaseFont);
    void SetUnderlineStyle( TListItemProperties aProperties, CWindowGc& aGc, TInt aColumn ) const;
    void DoConstructL( const TAknsItemID& aAnimationIID );
public:

    /**
     * Gets @c CCoeControl for component.
     *
     * @return Pointer to the used @c CCoeControl.
     */
    IMPORT_C CCoeControl *Control() const;
    
    /**
     * Sets @c CCoeControl for current component.
     *
     * @param aControl Current listbox control instance, cannot be any 
     *        other control.
     */
    IMPORT_C void SetControl(CCoeControl *aControl);
    
    /**
     * Gets background skin context.
     *
     * @return Component's skin control context.
     */
    IMPORT_C MAknsControlContext* SkinBackgroundContext() const;
    
    /**
     * Sets background skin context. Changes ownership as well.
     *
     * @param aContext Wanted background skin control context.
     */
    void SetSkinBackgroundContext(
                    CAknsListBoxBackgroundControlContext *aContext); 
                    // takes ownership
    
    /**
     * Sets style for the skin fot list tiles.
     *
     * @param aId Wanted skins item ID.
     * @param aTileRect Skin tile size. 
     */
    IMPORT_C void SetSkinStyle(const TAknsItemID *aId, 
                               const TRect &aTileRect);

    /**
     * Sets skin style for the end of the list. 
     *
     * @param aId Wanted skins item ID. 
     * @param aRect Skin tile size. 
     */
    IMPORT_C void SetListEndSkinStyle(const TAknsItemID *aId, 
                                      const TRect &aRect);

    /**
     * Sets skin for the highlighted frame.
     *
     * @param aFrameId Wanted skin's item ID for the frame.
     * @param aFrameCenterId Wanted skin's item ID for the center of the frame.
     */
    IMPORT_C void SetSkinHighlightFrame(const TAknsItemID *aFrameId, 
                                        const TAknsItemID *aFrameCenterId);

    /**
     * Enables/Disables skin.
     *
     * @param aEnabled Sets whether the skins are enable or disabled
     *                 @c ETrue for enabling skins.
     */
    IMPORT_C void SetSkinEnabledL(TBool aEnabled);
    
    /**
     * Creates a pictograph interface for the @c CColumnListBoxData.
     */
    void CreatePictographInterfaceL();

    /**
     * Creates a marquee control for the @c CColumnListBoxData and redraw.
     */
    void CreateMarqueeControlL();
    
    /**
     * Resets marquee control. 
     */
    void ResetMarquee();
    
    /**
     * Gets current marquee item index.
     *
     * @return Current marquee item index.
     */
    TInt CurrentMarqueeItemIndex();
    
    /**
     * Sets the index for current marquee item.
     *
     * @param aIndex Item index.
     */
    void SetCurrentMarqueeItemIndex(TInt aIndex);
    
    /**
     * Enables or disables the marquee. 
     *
     * @param aEnable @c ETrue = On. @c EFalse = Off.
     */
    IMPORT_C void EnableMarqueeL(TBool aEnable); 

    /**
     * Sets the font attached to the cell for each row separately.
     *
     * @param aRow Index number of the row.
     * @param aColumn Index number of the column.
     * @param aFont Font to be used.
     */
    IMPORT_C void SetColumnFontForRowL(TInt aRow, 
                                       TInt aColumn, 
                                       const CFont* aFont);

    /**
     * Gets the font attached to the row and cell.
     *
     * @param aRow Index number of the row.
     * @param aColumn Index number of the column.
     * @return Font handle.
     */
    IMPORT_C const CFont* RowAndColumnFont(TInt aRow,TInt aColumn) const;

    /**
     * Sets the current list item index. Since S60 2.6 causes highlight 
     * animation tochange its background (only if the current item index 
     * changes). Do not call this method if the index is not the current 
     * item index.
     *
     * @since S60 2.6
     * @param aIndex The new index for the current item.
     */
    void SetCurrentItemIndex(TInt aIndex);

    /**
     * Sets the subcell icon size.
     *
     * @since S60 2.8
     * @param aIndex Index of the sub cell. 
     * @param aSize Size of the sub cell icon.
     */
    IMPORT_C void SetSubCellIconSize(TInt aIndex, TSize aSize);

    /**
     * Gets subcell icon size.
     *
     * @param aIndex Index of the wanted subcell.
     * @return Size of the subcell.
     */
    TSize GetSubCellIconSize(TInt aIndex);

    /**
     * Gets the highlight animation .
     *
     * @since S60 3.0
     * @return @c CAknsEffectAnim that is used for when the highlighted list 
     *         is drawn. May return NULL, in this case the normal skinned
     *         highlight should be drawn. This pointer is valid only during  
     *         the draw -> you should not store it locally outside draw scope.
     */
    IMPORT_C const CAknsEffectAnim* HighlightAnim() const;
    
    /**
     * This method should be called before drawing animated highlight. It will
     * sync the animation with the background under the current highlight (only
     * when current item index has changed).
     *
     * @since S60 3.0
     */
    IMPORT_C void AboutToDrawHighlightAnim() const;
    
    /**
     * Sets the observer for overriding default highlight input layer drawing
     * functionality. Note that you should still call 
     * @c AboutToDrawHighlightAnim (it will call the observer if it is set).
     *
     * @since S60 3.0
     * @param aDrawer New background drawer.
     */
    IMPORT_C void SetHighlightAnimBackgroundDrawer( 
                                MColumnListBoxAnimBackgroundDrawer* aDrawer );

    /**
     * Changes item cell size & resizes highlight animation. Called by list 
     * when item cell size changes. If you are using non-standard highlight 
     * sizes make sure to sync the list item cell size.
     *
     * @since S60 3.0
     * @param aSizeInPixels New size in pixels for the Item cell.
     */
    IMPORT_C void SetItemCellSize( const TSize& aSizeInPixels );
    
    /**
    * @return ETrue if highlight animation exists, EFalse otherwise.
    *
    * @since 3.1
    */
    IMPORT_C TBool HasHighlightAnim() const;
    /**
    * The preferred method for drawing highlight animation in derived classes.
    * Before calling this method you should check that highlight animation
    * exists by calling HasHighlightAnim. In case of draw failure you should
    * default to normal skinned highlight drawing. For example:
    *
    * TBool drawOk = EFalse;
    *
    * if( HasHighlightAnim() )
    *     {
    *     drawOk = DrawHighlightAnim( gc, rect );
    *     }
    *
    * if( !drawOk )
    *     {
    *     ...do normal skinned draw
    *     }
    *
    * @param aGc   Graphics context for blitting animation frame
    * @param aRect Target rect for blitting animation frame
    * @return The draw status, ETrue if drawing was ok, EFalse otherwise.
    *
    * @since 3.1
    */
    IMPORT_C TBool DrawHighlightAnim( CBitmapContext& aGc, const TRect& aRect ) const;

    void FocusGained();
    
    /**
     * Called when the @c CColumnListBoxData is unselected. Informs the 
     * @c CColumnListBoxData extension that the focus has been lost.
     */
    void FocusLost();
    
    /**
     * Handles changing of an resource. Only supports skin change.
     *
     * @param aType Defines the resource that has changed. 
     */
    void HandleResourceChange( TInt aType );
    
    /**
     * Setup skin control context for handling background skins.
     * if no skin control context is found one is created.
     */
    void SetupSkinContextL();
    
    /**
     * Sets text colour. 
     *
     * @param aTextColor Wanted colour.
     */
    void SetESSTextColor(TRgb aTextColor);
    
    /**
     * Sets text colour for highlighted text.
     *
     * @param aHighlightedTextColor Wanted colour.
     */
    void SetESSHighlightedTextColor(TRgb aHighlightedTextColor);

    IMPORT_C void SetGraphicSubCellL(TInt aSubCell,const TAknWindowLineLayout &aGraphicLayout);
    IMPORT_C void SetTextSubCellL(TInt aSubCell,const TAknTextLineLayout &aTextLayout);
    IMPORT_C void SetConditionalSubCellL(TInt aSubCell, const TAknTextLineLayout &aTextLayout,TInt aAffectedSubCell);
    IMPORT_C void SubCellsMightIntersect( const TBool aMightIntersect );

    IMPORT_C void SetStretchableGraphicSubCellL(TInt aSubCell, 
        const TAknWindowComponentLayout& aNormalLayout, 
        const TAknWindowComponentLayout& aStretchedLayout);
    IMPORT_C void SetStretchableTextSubCellL(TInt aSubCell,                                      
        const TAknTextComponentLayout& aNormalLayout, 
        const TAknTextComponentLayout& aStretchedLayout);
    IMPORT_C void SetStretchableConditionalSubCellL(TInt aSubCell,
        const TAknTextComponentLayout& aNormalLayout,
        const TAknTextComponentLayout& aStretchedLayout,
        TInt aNormalSubCell,
        TInt aStretchedSubCell );
    IMPORT_C void ResetSLSubCellArray();                                           
    TBool UsesScalableLayoutData() const;
    void EnableStretching(const TBool aEnabled);
    IMPORT_C TBool StretchingEnabled() const;
protected:
    
    /**
     * Wraps the text drawing functinality with & without marquee into one 
     * function, so that inherited classes can modify their own drawing 
     * behaviour more easily.
     *
     * @since S60 2.8
     * @param aGc Window graphics context controller.
     * @param aTextRect The area where the text is drawn.
     * @param aText The whole text. Not clipped.
     * @param aClippedText Clipped / truncated text.
     * @param aBaselineOffset An offset from the top of the box to the text 
     *        baseline.
     * @param aAlign The text alignment mode (default is left, rather 
     *        than centre or right). 
     * @param aFont Wanted font.
     * @param aHighlight Does the current item have highlight.
     * @param aIsTextClipped Is the current item clipped.
     */
    IMPORT_C void DrawText(CWindowGc& aGc, 
                           const TRect& aTextRect, 
                           const TDesC& aText, 
                           const TDesC& aClippedText, 
                           const TInt aBaselineOffset,
                           const CGraphicsContext::TTextAlign aAlign, 
                           const CFont& aFont,
                           const TBool aHighlight, 
                           const TBool aIsTextClipped) const;

public:
    /**
     * Customizes marquee default behaviour. 
     *
     * Use this before enabling marquee ( @c EnableMarqueeL() ), otherwise 
     * marquee behaviour will change during animation.
     *
     * @since S60 2.8
     * @param aLoops Max number of loops to be executed.
     * @param aScrollAmount The amount of pixels scrolled per 
     *        iteration.
     * @param aScrollDelay The interval between iterations.
     */
    IMPORT_C void SetMarqueeParams(const TInt aLoops, 
                                   const TInt aScrollAmount, 
                                   const TInt aScrollDelay);

    /**
     * Customizes marquee default behaviour. 
     *
     * @since S60 2.8
     * @param aLoops Max number of loops to be executed.
     * @param aScrollAmount The amount of pixels scrolled per iteration. 
     * @param aScrollDelay The interval between iterations.
     * @param aInterval The interval between frame updates.
     */
    IMPORT_C void SetMarqueeParams(const TInt aLoops, 
                                   const TInt aScrollAmount, 
                                   const TInt aScrollDelay, 
                                   const TInt aInterval);                        
    /**
    * Tells whether current item has clipped text cells
    * @since S60 3.2
    * @return bitfield of clipped columns
    */
    IMPORT_C TUint32 CurrentItemTextWasClipped() const;
        
    /**
    * Returns ETrue if kinetic scrolling is enabled.
    * @internal
    * @since S60 5.0
    * @return ETrue if kinetic scrolling feature is enabled.
    */
    TBool KineticScrollingEnabled() const;

private:
    void DrawHighLight( CWindowGc& aGc, const TRect& aRect,
                        TBool aHighlight,
                        MAknsSkinInstance* aSkin ) const;
        
    void CheckIfSubCellsIntersect( TAknTextLineLayout* aLayouts,
                                   TBool* aResults, const TDesC& aText,
                                   const TRect& aItemRect ) const;
    /**
    * @internal helper
    */
    void BitBltColored( CWindowGc&      aGc,
                        TBool           aHighlight,
                        const CGulIcon* aIcon,
                        TInt            aSubcell,
                        TBool           aColorIcon,
                        const TRect&    aGraphicRect ) const;


        
private:
    CArrayFix<SColumn>* iColumnArray;
    CColumnListBoxDataExtension *iExtension;
    };

#endif // __EIKCLBD_H__

// End of File
