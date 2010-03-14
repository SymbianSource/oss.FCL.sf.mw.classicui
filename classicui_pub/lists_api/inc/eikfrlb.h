/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

// EIKFRLB.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKFRLB_H__)
#define __EIKFRLB_H__

#include <eiklbi.h>
#include <eiklbv.h>
#include <eiktxlbm.h>
#include <eiktxlbx.h>

class CFormattedCellListBoxData;

/**
 *  @c CFormattedCellListBoxItemDrawer draws a single list item and manages
 *  list item properties.
 *
 *  @lib avkon
 */
class CFormattedCellListBoxItemDrawer : public CTextListItemDrawer
	{
public:

    /**
     * C++ default constructor.
     * 
     * @param aTextListBoxModel The list box model class.
     * @param aFont Font to be used in listbox.
     * @param aFormattedCellData Pointer to the list layout drawer class.
     */
	IMPORT_C CFormattedCellListBoxItemDrawer(
            MTextListBoxModel* aTextListBoxModel, 
            const CFont* aFont, 
            CFormattedCellListBoxData* aFormattedCellData);
	
    /**
     * Destructor.
     */
    IMPORT_C ~CFormattedCellListBoxItemDrawer();

    /**
     * Gets the list layout drawer.
     * 
     * @return Pointer to the list layout drawer object.
     */
	IMPORT_C CFormattedCellListBoxData* FormattedCellData() const;

    /**
     * Gets the list layout drawer.
     * 
     * @return Pointer to the list layout drawer object.
     */
	IMPORT_C CFormattedCellListBoxData* ColumnData() const; 
    // for compability with columnlistbox itemdrawer

    /**
     * Draws an empty item to the list box.
     * 
     * @param aItemIndex Not used.
     * @param aItemRectPos Position for the list box item rectangle.
     * @param aViewIsDimmed Not used.
     */
    IMPORT_C virtual void DrawEmptyItem(TInt aItemIndex, TPoint aItemRectPos, 
                                        TBool aViewIsDimmed) const;

    /**
     * This function sets top item index.
     * 
     * @param aTop Item index value.
     */
	IMPORT_C void SetTopItemIndex(TInt aTop);

    /**
     * List item index and color and style properties.
     */
	struct SListProperties 
	    {
        /** List box item index. */
        TInt iItem; // must be first

        /** Colour and style properties for the list item. */
        TListItemProperties iProperties;
	    };

    /**
     * Clears all properties.
     */
	IMPORT_C void ClearAllPropertiesL();

    /** 
     * The SetProperties is convenience method for normal cases.
     * NOTE that it does NOT work correctly if you can insert/delete
     * items from the list -- You need to update all properties if
     * any changes to the item text array happen! Often it is convenient
     * to override the @c Properties() method. Further, use this only
     * for small lists.
     *
     * It has been implemented as sorted list of (index,Property) pairs.
     * 
     * If you're using find, aItemIndex for this method is the same as you give
     * in @c MdcaPoint() points the default @c Properties() does conversion 
     * between indexes.
     * 
     * @param aItemIndex List box item index.
     * @param properties Colour and style properties for the list box item.
     */
    IMPORT_C void SetPropertiesL(TInt aItemIndex, TListItemProperties properties);

    /**
     * Function for getting properties of a certain list box item.
     * 
     * @param aItemIndex The listbox item index.
     * @return Colour and style properties of wanted
     *         list box item.
     */
	IMPORT_C virtual TListItemProperties Properties(TInt aItemIndex) const;

    /**
     * Gets list box item cell size.
     * 
     * @return The list box item cell size.
     */
	TSize LafItemSize() { return iItemCellSize; }

public: // from CTextListItemDrawer

    /**
     * From @c CTextListItemDrawer.
     *
     * Draw an item in a list box.
     * 
     * @param aItemIndex The index into the model's item array of the item 
     *        to draw.
     * @param aItemTextRect The item’s text rectangle. 
     * @param aItemIsCurrent @c ETrue if the item is current. @c EFalse 
     *        otherwise.
     * @param aViewIsEmphasized @c ETrue if the view is emphasized. @c EFalse
     *        otherwise.
     * @param aItemIsSelected @c ETrue if the item is selected. @c EFalse 
     *        otherwise.
     */
	IMPORT_C void DrawItemText(TInt aItemIndex,const  TRect& aItemTextRect,
                               TBool aItemIsCurrent, TBool aViewIsEmphasized, 
                               TBool aItemIsSelected) const;

    /**
     * From @c CTextListItemDrawer.
     *
     * Draws an item tick mark. 
     *
     * A tick mark is used in multiple selection lists to indicate the item is
     * selected.
     *
     * This function is invoked by the framework to draw an item mark if 
     * @c iDrawMark is set. The mark should be drawn into this list item 
     * drawer's graphics context; by default, @c DrawItemMark() draws a tick 
     * using the standard symbol font.
     * 
     * This function does not need to be re-implemented for derived classes 
     * which do not draw item marks.
     * 
     * @param aItemIsSelected Whether the item to draw for is selected.
     * @param aViewIsDimmed Whether the item is dimmed. 
     * @param aMarkPos Position of the mark.
     */
	IMPORT_C void DrawItemMark(TBool aItemIsSelected, TBool aViewIsDimmed, 
                               const TPoint& aMarkPos) const;

public: // from CListItemDrawer

    /**
     * From @c CListItemDrawer.
     *
     * Gets the minimum size of a cell based on the font and the number of 
     * characters in the cell.
     * 
     * @return The minimum size for a cell in pixels.
     */
	IMPORT_C TSize MinimumCellSize() const;

    /**
     * From @c CListItemDrawer.
     *
     * Gets the width in pixels of the specified item.
     * 
     * @param aItemIndex The index of the item for which the width is obtained.
     * @return The specified item's width in pixels.
     */
	IMPORT_C TInt ItemWidthInPixels(TInt aItemIndex) const; 

    /**
     * From @c CListItemDrawer.
     *
     * Sets the item cell size.
     *
     * The cell size is the on-screen size of the entire item, including its 
     * text and its item mark.
     * 
     * @param aSizeInPixels New size for the item cell.
     */
    IMPORT_C void SetItemCellSize(const TSize& aSizeInPixels);

protected:
    
    /**
     * Draws current item rectangle.
     * 
     * @param aRect Current item rectangle.
     */
	void DrawCurrentItemRect(const TRect& aRect) const;

    /**
     * @c WordWrapListItem is used with @c CAknDouble* style listboxes.
     * If listbox does not have 2nd line defined, @c WordWrapListItem
     * wraps 1st line to 2nd line, if text does not fit to 1st line.
     * If listbox does have 2nd line defined, this method truncates
     * both lines.
     *
     * @internal
     * @param aTarget Where to place wrapped item string
     * @param aItemString Text to be wrapped
     * @param aFirstIndex index of 1st subcell to wrap
     * @param aSecondIndex index of 2nd subcell
     */
    void WordWrapListItem( TPtr& aTarget, 
                           const TDesC &aItemString, 
                           TInt aFirstIndex, 
                           TInt aSecondIndex,
                           TInt aItemIndex ) const;
    /**
    * @internal
    */
    void DrawBackgroundAndSeparatorLines( const TRect& aItemTextRect, 
        TBool aDrawSeparator ) const;
                        

private:

	IMPORT_C void CFormattedCellListBoxItemDrawer_Reserved();

protected:

    /**
     * Top item index.
     */
	TInt iTopItemIndex;

    /**
     * Array for list box item's properties.
     * Own.
     */
	CArrayFix<SListProperties>* iPropertyArray;

private:

	TInt iSpare;
	};


/** 
 * Avkon base class similar to uikon's column listbox.
 *
 * @code
 *  ListBox <>--> View ---> ItemDrawer ---> Model
 *  ListBox <>--> ItemDrawer <>---> Data
 *  ListBox <>--> Model <>---> MDesCArray <--- Array <>---> Engine
 * @endcode
 * 
 * Content for list items are tab-separated strings.
 *
 * See concrete classes derived from @c CEikFormattedCellListBox for details.
 *
 * Starting from 3.0 listbox uses highlight animations. Starting and stopping
 * animation is connected to focus events. To support highlight animations
 * properly you have to make sure that the list has focus when it has 'visual
 * focus'. Common issues:
 * - In many cases list is in a container which sits on top of the control
 *   stack. The container receives all focus events and should hand them to the
 *   list too. E.g. 
 * @code       void CContainer::FocusChanged( TDrawNow aDrawNow )
 *                 {
 *                 ... some code ...
 *                 if( iListBox )
 *                     iListBox->SetFocus( IsFocused(), aDrawNow );
 *                 }
 * @endcode
 * - When switching components programmatically, e.g. from one list to another
 *   in the same view, make sure that you remove focus from the other
 *   component.
 * - In more complex cases you may have to add a dummy interceptor control to
 *   the top of control stack to hand focus events to list.
 * - Make sure you handle resource changes correctly. If resource handle chain
 *   is solid it should reach @c CCoeControl::HandleResourceChange, which 
 *   informs child components about resource change.
 *
 * See methods
 *   @c CEikListBox::ConstructL()
 *   @c CEikTextListBox::SetItemTextArray()
 *   @c CEikFormattedCellListBoxData::SetIconArray()
 * 
 * Related flags for dialogs (@c avkon.hrh)
 *   @c EAknDialogSelectionList
 *   @c EAknDialogMenuList
 *   @c EAknDialogMultiselectionList
 *
 * Check also:
 *   @c CAknSelectionListDialog (@c aknselectionlist.h)
 *   @c CAknMarkableListDialog  (@c aknselectionlist.h)
 *   @c CAknPopupList           (@c aknpopup.h)
 *   @c CAknListQueryDialog     (@c aknquerydialog.h)
 *   @c CAknColumnListBox       (@c aknlists.h)
 *
 *  @lib avkon
 */
class CEikFormattedCellListBox : public CEikTextListBox 
	{

public:

    /**
     * C++ default constructor.
     */
	IMPORT_C CEikFormattedCellListBox();

    /**
     * Constructs list box from resource file. See @c LISTBOX resource 
     * definition.
     *
     * Flags: 
     *    @c EAknListBoxSelectionList, 
     *    @c EAknListBoxMenuList, 
     *    @c EAknListBoxMarkableList, 
     *    @c EAknListBoxMultiselectionList, 
     *    @c EAknListBoxViewerFlags
     * 
     * @param aReader Reference to resource reader @c TResourceReader object.
     */
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	
    /** 
     * By default Symbian 2nd phase constructor is private. Must be called 
     * if resource data is not used.
     * 
     * @param aParent Pointer to @c CCoeControl class, parent control.
     * @param aFlags Flags for @c CEikListBox constructor. Possible flags : 
     *        @c EAknListBoxSelectionList, 
     *        @c EAknListBoxMenuList, 
     *        @c EAknListBoxMarkableList, 
     *        @c EAknListBoxMultiselectionList, 
     *        @c EAknListBoxViewerFlags
	 */
	IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags);

public:

    /**
     * Gets model class of the list box.
     * 
     * @return Pointer to list box model class instance.
     */
	IMPORT_C CTextListBoxModel* Model() const;

    /**
    * Gets list box item drawer.
    * 
    * @return Pointer to item drawer object.
    */
	IMPORT_C CFormattedCellListBoxItemDrawer* ItemDrawer() const;

    /**
    * Sets icon sizes for visible list box items.
    */
    void SetIconSizes();

public:

	/**
     * Enable or disable logical to visual reordering in listbox data text
     * drawing. By default, it is enabled. This has any effect only when 
     * bidirectional text is rendered.
     *
     * If you convert text to visual order prior to passing it to the listbox
     * (for example by wrapping text to lines with methods in 
     * @c AknBidiTextUtils), then you should disable conversion in listbox 
     * by calling this method.
     *
     * @since S60 2.0
     * @param aUseConversion If @c ETrue enable conversion. 
     */
	IMPORT_C void UseLogicalToVisualConversion( TBool aUseConversion );

public:

    /**
     * This method needs to be called to enable extended drawing features such
     * as skinning, pictograph drawing and marquee text in the listbox draw
     * routine.
     *
     * Methods @c CEikFormattedCellListBox::ConstructL and
     * @c CEikFormattedCellListBox::ConstructFromResourceL call this method. 
     * So, you only need to call this if your listbox implementation does not 
     * call either of those.
     * 
     * This method can be safely called more than once.
     * Item drawer must be created before calling this method, or a panic is 
     * raised.
     *
     * @since S60 2.6
     * @panic EAknPanicListBoxItemDrawerNotCreated Panics if the item drawer 
     *        for the current class has not been defined.
     */
    IMPORT_C void EnableExtendedDrawingL();
    
    /**
    * Enables/disables list stretching. When a list is stretched its second line
    * is moved after the first line. This is intented for devices with a large
    * screen. This feature might be set as default by a product specific flag.
    *
    * Item drawer must be created before calling this method.
    *
    * @since S60 3.1
    * @param aEnabled ETrue to enable list stretching.
    */
    IMPORT_C void EnableStretching( const TBool aEnabled );

    /**
    * Hides the second row of a double style listbox. This feature is disabled
    * by default.
    *
    * @since S60 3.1
    * @param aHide ETrue to hide the second row.
    */
    IMPORT_C void HideSecondRow( const TBool aHide );
protected:

    /**
     * Creates item draver for the listbox.
     */
	IMPORT_C virtual void CreateItemDrawerL();

    /**
     * From @c CEikListBox.
     *
     * Rounds down the height of the rectangle (if necessary) so that only
     * a whole number of items can be displayed inside the list box.
     *
     * @param aRect The rectangle to be modified.
     * @return The number of pixels reduced.
     */
	IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(
                                    TRect &aRect) const;

public: // from CEikListBox

    /**
     * From @c CEikListBox.
     *
     * Creates the list box view.
     * 
     * @return Pointer to new list box view class instance.
     */
	IMPORT_C CListBoxView* MakeViewClassInstanceL();

    /**
     * From @c CEikListBox.
     *
     * Handles focus changes.
     *
     * The function emphasizes or de-emphasizes the view as needed, 
     * and shows or hides the matcher cursor.
     *
     * @param aDrawNow If @c EDrawNow, a redraw is performed immediately.
     */
    IMPORT_C void FocusChanged(TDrawNow aDrawNow);

public: // from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Gets the list of logical colors used to draw the control.
     * 
     * @param aColorUseList The color list.
     */
	IMPORT_C void GetColorUseListL(
        CArrayFix<TCoeColorUse>& aColorUseList) const;
	
    /**
     * From @c CCoeControl.
     *
     * Handles a change to the control's resources.
     *
     * @param aType A message UID value.
     */
    IMPORT_C void HandleResourceChange(TInt aType);
    
    /**
     * From @c CCoeControl.
     *
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected: // from MObjectProvider

    /**
     * From @c MObjectProvider.
     *
     * Retrieves an object of the same type as that encapsulated in aId. This 
     * function is used to allow controls to ask their owners for access to 
     * other objects that they own.
     * 
     * @param aId An encapsulated object type ID.
     * @return Encapsulates the pointer to the object provided. 
     *         Note that the encapsulated pointer may be NULL.
     */
	IMPORT_C virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

private: 

    /**
     * From @c CAknControl
     */
	IMPORT_C void* ExtensionInterface( TUid aInterface );

private: // listbox use only

	IMPORT_C virtual void CEikListBox_Reserved(); 

private: // data

    TInt iSpare;
};


/**
 *  @c CFormattedCellListBoxView draws all the list items and manages
 *  the area of the screen allocated for list itself. In particular,
 *  this class does not handle margins of the whole list.
 *
 *  @lib avkon
 */
class CFormattedCellListBoxView : public CListBoxView
	{

public: // from CListBoxView

    /**
     * From @c CListBoxView.
     *
     * Draws every visible item into the specified rectangle. 
     *
     * @param aClipRect The rectangle to draw into. This is not used.
     */
	IMPORT_C void Draw(const TRect* aClipRect = NULL) const;

    /**
     * From @c CListBoxView.
     *
     * Draws empty list. 
     *
     * @param aClientRect The rectangle to draw into.
     */
	IMPORT_C virtual void DrawEmptyList(const TRect &aClientRect) const;
	
    /**
     * From @c CListBoxView.
     *
     * Recalculates the index of the bottom item in the list from the top item
     * index and the size of the display. This function is called by the owning
     * list box control when either the size of the list box or the number of 
     * items in its model changes. 
     */
    IMPORT_C virtual void CalcBottomItemIndex();

private: // overridden from CListBoxView

	IMPORT_C virtual TAny* Reserved_1();
	};


#endif  // __EIKFRLB_H__

// End of File
