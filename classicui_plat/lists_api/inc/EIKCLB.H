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


#if !defined(__EIKCLB_H__)
#define __EIKCLB_H__


#include <eiklbi.h>
#include <eiktxlbx.h>
#include <eiklbed.h>

class CColumnListBoxData;


/**
 * Draws the contents of list box items.
 *
 * @since 5.0
 */
class CColumnListBoxItemDrawer : public CTextListItemDrawer
    {

public:
    /* C++ default constructor.
    *
    *  @since 3.2
    */
            
    IMPORT_C CColumnListBoxItemDrawer();
            
    /**
     * C++ default constructor.
     *
     * Initialises the list box item drawer with the specified model, 
     * font and data.
     *
     * @param aTextListBoxModel The model whose items will be drawn. 
     *        This provides the item text that is drawn using 
     *        @c DrawItemText().
     * @param aFont The font in which the items will be drawn. 
     * @param aColumnData The column list box data. This comprises: 
     *        the column widths, gaps, fonts, aligments and bitmaps.
     */

    IMPORT_C CColumnListBoxItemDrawer(MTextListBoxModel* aTextListBoxModel, 
                                      const CFont* aFont, 
                                      CColumnListBoxData* aColumnData);
 
    /**
     * Destructor.
     */
    IMPORT_C ~CColumnListBoxItemDrawer();

    /**
     * Gets a pointer to the column list box data as set during construction.
     * Does not transfer ownership.
     *
     * @return The column list box data.
     */
    IMPORT_C CColumnListBoxData* ColumnData() const;

public:


    /** 
     * The structure holding given item properties. 
     *
     * Used for storing information given through @c SetProperties() method.
     */
	struct SListProperties 
	    {
        /** Item identifier. */
	    TInt iItem; // must be first

        /** Properties of the item. */
	    TListItemProperties iProperties;
	    };

    /**
     * Clears all properties from the @c CColumnListBoxItemDrawer.
     */
    IMPORT_C void ClearAllPropertiesL();
	
   
    /**
     * Set the property for an item with @c aItemIndex 
     *
     * @param aItemIndex Item index
     * @param aProperty The new property setting
     * The SetProperties is convinience method for normal cases.
     * NOTE that it does NOT work correctly if you can insert/delete
     * items from the list -- You need to update all properties if
     * any changes to the item text array happen! Often it is convinient
     * to override the Properties() method. Further, use this only
     * for small lists as it causes O(n) time if you need to set
     * all properties.
     */
    IMPORT_C void SetPropertiesL(TInt aItemIndex, 
                                 TListItemProperties aProperty);

    /**
     * Get properties for an item. 
     *
     * @param aItemIndex Item's index for identifying.
     * @return Wanted property set.
     */
    IMPORT_C virtual TListItemProperties Properties(TInt aItemIndex) const;

public: // from CTextListItemDrawer

    /**
     * From @c CTextListItemDrawer.
     * 
     * Draw item text.
     *
     * @param aItemIndex Index of the item to draw. 
     * @param aItemTextRect Area to draw into. 
     * @param aItemIsCurrent @c ETrue if the item is current. 
     * @param aViewIsEmphasized @c ETrue if the view is emphasised.
     * @param aItemIsSelected @c ETrue if the item is selected.
     */
    IMPORT_C void DrawItemText(TInt aItemIndex,
                               const TRect& aItemTextRect,
                               TBool aItemIsCurrent,
                               TBool aViewIsEmphasized, 
                               TBool aItemIsSelected) const;
    // the next one is for avkon

    /**
     * Not used in S60.
     */
    IMPORT_C void DrawItemMark(TBool aItemIsSelected, 
                               TBool aViewIsDimmed, 
                               const TPoint& aMarkPos) const;

public: // from CListItemDrawer

    /**
     * From @c CListItemDrawer.
     *
     * Gets the minimum cell size.
     *
     * @return The minimum size for a cell. This is 
     *         TSize(0, 0) in @c CListItemDrawer.
     */
    IMPORT_C TSize MinimumCellSize() const;
	
    /**
     * From @c CListItemDrawer.
     *
     * Gets the width of the specified item.
     *
     * @param aItemIndex The index of the item whose width is to be returned. 
     * @return The width of the item. This is 0 in @c CListItemDrawer
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
	
    /**
     * Get Item Cell Size.
     *
     * @return Cell size of an item.
     */
    TSize LafItemSize() { return iItemCellSize; }

private: // from CListItemDrawer

    IMPORT_C TAny* Reserved_1();

private: // defining reserved method.

    IMPORT_C void CColumnListBoxItemDrawer_Reserved();

protected:

    /**
     * Draw the item background.
     *
     * Internal member, not intended for use.
     *
     * @param aRect Drawing area. 
     */
    void DrawCurrentItemRect(const TRect& aRect) const;
	
    /** 
     * Array of properties.
     */
    CArrayFix<SListProperties>* iPropertyArray;
	
    /** 
     * Not used. 
     */ 
    TInt iSpare;
    };


/**
 * Column list box control.
 *
 * This is a list box whose lines consist of cells that are grouped vertically 
 * into columns. The columns can be either textual or graphical, and column 
 * widths and fonts can be set explicitly through @c CColumnListBoxData.
 *
 * Starting from 3.0 listbox uses highlight animations. Starting and stopping
 * animation is connected to focus events. To support highlight animations
 * properly you have to make sure that the list has focus when it has 'visual
 * focus'. Common issues:
 * - In many cases list is in a container which sits on top of the control
 *   stack. The container receives all focus events and should hand them to the
 *   list too. E.g.
 *             void CContainer::FocusChanged( TDrawNow aDrawNow )
 *                 {
 *                 ... some code ...
 *                 if( iListBox )
 *                     iListBox->SetFocus( IsFocused(), aDrawNow );
 *                 }
 * - When switching components programmatically, e.g. from one list to another
 *   in the same view, make sure that you remove focus from the other
 *   component.
 * - In more complex cases you may have to add a dummy interceptor control to
 *   the top of control stack to hand focus events to list.
 * - Make sure you handle resource changes correctly. If resource handle chain
 *   is solid it should reach CCoeControl::HandleResourceChange, which informs
 */
class CEikColumnListBox : public CEikTextListBox
    {
public:
    /**
     * C++ default constructor.
     */
    IMPORT_C CEikColumnListBox();
    
    /**
     * Second-phase construction from a resource.
     * 
     * This function completes the construction of a column list box, 
     * initialising any members from the specified resource reader.
     *
     * @param aReader A resource file reader
     */
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
    
    /**
     * By default Symbian 2nd phase constructor is private.
     *
     * This function completes the construction of a column list box.
     *
     * @param aParent Parent control for the column list box.
     * @param aFlags Flags for the column list box. 
     */
    IMPORT_C void ConstructL( const CCoeControl* aParent,TInt aFlags=0);
    /**
    * Not supported in S60.
    */
    IMPORT_C void EditItemL(TInt aColumn, TInt aMaxLength);
protected:

    /**
     * This member is internal and not intended for use.
     */
    IMPORT_C virtual void CreateItemDrawerL();

    /**
     * Creates a new @c CTextListBoxModel 
     */
    IMPORT_C virtual void CreateModelL();

public:

    /**
     * Gets the list box model.
     *
     * @return Pointer to the model used by this list box
     */
    IMPORT_C CTextListBoxModel* Model() const;
 
    /**
     * Gets the object used by this list box to draw its items.
     *
     * @return A pointer to the list box drawer.
     */
    IMPORT_C CColumnListBoxItemDrawer* ItemDrawer() const;

    /**
     * This method needs to be called to enable extended drawing features 
     * such as skinning, pictograph drawing and marquee text in the listbox 
     * draw routine.
     *
     * Methods @c CEikFormattedCellListBox::ConstructL and
     * @c CEikFormattedCellListBox::ConstructFromResourceL call this method. 
     * So, you only need to call this if your listbox implementation does not 
     * call either of those.
     * 
     * This method can be safely called more than once.
     * Item drawer must be created before calling this method, or a 
     * panic is raised.
     *
     * @since S60 2.6
     */
    IMPORT_C void EnableExtendedDrawingL();

    /**
     * Helper function that setst icon sizes for visible list items
     */
    void SetIconSizes();

    /**
    * Enables/disables list stretching. When a column list is stretched its 
    * layout is optimized to take advantage of the extra screen space.
    * This is intented for devices with a large screen. This feature might be 
    * set as default by a product specific flag.
    *
    * Item drawer must be created before calling this method.
    *
    * @since S60 3.1
    * @param aEnabled ETrue to enable list stretching.
    */
    IMPORT_C void EnableStretching( const TBool aEnabled );
public: // from CEikListBox

    /**
     * From @c CEikListBox.
     * 
     * Creates the list box view.
     * The function is called by @ ConstructL() to create an instance of 
     * the appropriate list box view class for this list box. The returned
     * instance is owned by this object, and does not have to have its 
     * second-phase constructor run. This function is called by 
     * @c CreateViewL().
     *
     * @return Pointer to a newly constructed list box 
     *         view for this object. 
     */
    IMPORT_C CListBoxView* MakeViewClassInstanceL();
    
    /**
     * From @c CEikListBox
     * 
     * Handles focus changes.
     *
     * The function emphasises or de-emphasises the view as needed, and 
     * shows or hides the matcher cursor.
     *
     * @param aDrawNow If @c EDrawNow, a redraw is performed immediately
     */
    IMPORT_C void FocusChanged(TDrawNow aDrawNow);

public:	// from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Not used in S60
     * @param aColorUseList The colour list
     */
    IMPORT_C void GetColorUseListL(
                        CArrayFix<TCoeColorUse>& aColorUseList) const;

    /**
     * From @c CCoeControl.
     *
     * Handles a change to the control's resources.
     *
     * The types of resources handled are those which are shared across 
     * the environment, e.g. colours or fonts. For colour scheme changes, 
     * @c DrawDeferred() is called in order to redraw the control.
     * 
     * If overriding @c HandleResourceChange(), the implementation must 
     * include a base call to @c CCoeControl's @c HandleResourceChange().
     * 
     * @param aType A message UID value
     */
    IMPORT_C void HandleResourceChange(TInt aType);
	
    /**
     * From @c CCoeControl.
     *
     * Retrieves an object of the same type as that encapsulated in @c aId.
     * 
     * This function is used to allow controls to ask their owners for 
     * access to other objects that they own.
     * 
     * Other than in the case where NULL is returned, the object returned 
     * must be of the same object type - that is, the @c ETypeId member of the 
     * object pointed to by the pointer returned by this function must be 
     * equal to the @c iUid member of @c aUid.
     * 
     * @param aUid An encapsulated object type ID.
     * @return Pointer to the type UID of the wanted object. 
     */
    IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aUid);
    
    /**
     * From @c CCoeControl.
     *
     * Handles pointer events.
     *
     * This function gets called whenever a pointer event occurs in the 
     * control, i.e. when the pointer is within the control's extent, or when 
     * the control has grabbed the pointer. The control should implement this 
     * function to handle pointer events.
     * 
     * Note: events of type @c EButton1Down are processed before 
     * @c HandlePointerEventL() is called, in order to transfer keyboard 
     * focus to the control in which the @c EButton1Down event occurred.
     * 
     * If overriding @c HandlePointerEventL(), the implementation must 
     * include a base call to @c CCoeControl's @c HandlePointerEventL().
     *
     * @param aPointerEvent The pointer event
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
    IMPORT_C virtual void CEikListBox_Reserved(); // listbox use only
private: // data
    TInt iSpare;
    };

/**
 * The @c CEikColumnListBoxEditor class implements an item editor for 
 * column list boxes. 
 * Not supported in S60
 * @since ER5U
 */
class CEikColumnListBoxEditor : public CEikListBoxTextEditor
    {
public:
    IMPORT_C CEikColumnListBoxEditor(MListBoxModel* aModel);
    IMPORT_C ~CEikColumnListBoxEditor();
    IMPORT_C void ConstructL(TInt aColumn);   // just set column index
public: // from MEikListBoxEditor
    IMPORT_C TPtrC ItemText();
    IMPORT_C TBool UpdateModelL();
public: // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);    
protected:
    IMPORT_C TInt Column() const;
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
    TInt iColumnIndex; // refers to list box column
    };

class CColumnListBoxView : public CListBoxView
    {
public: // from CListBoxView

    /**
     * From @c CListBoxView 
     * Draws every visible item into the specified rectangle. 
     *
     * As implemented in @c CListBoxView, this function's argument is 
     * ignored and the internal viewing rectangle is used. See @c SetViewRect().
     *
     * @param aClipRect = NULL The rectangle to draw into, this is ignored
     */
    IMPORT_C void Draw(const TRect* aClipRect = NULL) const;
    
    /**
     * From @c CListBoxView
     * Recalculates the index of the bottom item in the list from the top item 
     * index and the size of the display. 
     *
     * This function is called by the owning list box control when either the 
     * size of the list box or the number of items in its model changes.
     */
	IMPORT_C virtual void CalcBottomItemIndex();

private: // overridden from CListBoxView	

    IMPORT_C virtual TAny* Reserved_1();

private: // data
    TInt iSpare;
    };

#endif // __EIKCLB_H__

// End of File