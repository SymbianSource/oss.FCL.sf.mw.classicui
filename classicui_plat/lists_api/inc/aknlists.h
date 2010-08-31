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

#ifndef __AKNLISTS_H__
#define __AKNLISTS_H__

#include <eikclb.h>
#include <eikfrlb.h>
#include <eikslb.h>
#include <AknGrid.h>
#include <AknUtils.h>

#include <AknPanic.h>


class TAknTextLineLayout;
class MAknsSkinInstance;
class MAknsControlContext;

/** THIS FILE INCLUDES:
 *  1) All listbox layouts specified in Avkon LAF specification
 *      a) General list pane descendants
 *      b) Pop up window list pane descendants
 *      c) Grid panes
 *  2) Utilities that help building listbox layouts based on LAF specification
 *  3) Other helper classes that handle listbox behavior
 */


//
//
// Helper template definitions.
// (these are before concrete listbox classes because they're needed for inheritance)
//


/**
 * This adds correct horizontal and vertival lines to the listbox and handles empty listbox!
 *
 * This class is only useful if you're writing your own list layout. 
 * Please use the predefined layouts instead, for example CAknSingleStyleListBox.
 */
template<class T>
class AknListBoxLinesTemplate : public T
    {
public:
    /** AknListBoxLinesTemplate
     *
     * Read AVKON_LISTBOX_LINES resources. 
     *
     * The following predefined lines are available:
     * R_LIST_PANE_LINES_A_COLUMN
     * R_LIST_PANE_LINES_AB_COLUMN
     * R_LIST_PANE_LINES_AB_COLUMN_X
     * R_LIST_PANE_LINES_AB_COLUMN_XX
     * R_LIST_PANE_LINES_BC_COLUMN
     * R_LIST_PANE_LINES_BC_COLUMN_X
     * R_LIST_PANE_LINES_BC_COLUMN_XX
     * 
     */
    IMPORT_C AknListBoxLinesTemplate(TInt aResourceId);
    /** SizeChanged()
     * 
     * Determines position of the lines
     */
    IMPORT_C void SizeChanged();
    /** Draw()
     * 
     * Draws the lines
     */
    IMPORT_C void Draw(const TRect& aRect) const;
    /** CountComponentControls()
     * 
     * Choose controls to use as child controls
     */
    IMPORT_C TInt CountComponentControls() const;
    /** CountComponentControls()
     * 
     * Choose controls to use as child controls
     */
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

private:
    TInt iSpare0;                           // was iResourceId;
    TAknLayoutRect iVertLine1, iVertLine2;  // not used
    TAknLayoutRect iHoriLine;               // not used
    TBool iResized;
    TInt iSpare[2];
    };

/**
 * Empty layout for popup lists
 */

template<class T>
class AknPopupListEmpty : public T
    {
   /**
    * Draws empty list when needed. See AknDraw::DrawEmptyList().
    */
    IMPORT_C virtual void Draw(const TRect &aRect) const;
    };


	/** 
	* Avkon version of eikon's column listbox.
	* Content for list items are tab-separated strings.
	*
	* See methods 
	*   CEikListBox::ConstructFromResourceL()
	*   CEikListBox::ConstructL()
	*   CEikTextListBox::SetItemArray()
	*   CEikColumnListBoxData::SetIconArray()
	* 
	* Related flags for ConstructL() (avkon.hrh)
	*   EAknListBoxSelectionList
	*   EAknListBoxMenuList
	*   EAknListBoxMarkableList
	*   EAknListBoxMultiselectionList
	*   EAknListBoxViewerFlags
	*
	* Related flags for dialogs (avkon.hrh)
	*   EAknDialogSelectionList
	*   EAknDialogMenuList
	*   EAknDialogMultiselectionList
	*
	* @since Series 60 0.9
	*
	*/
class CAknColumnListBox : public CEikColumnListBox
    {
public:
    /** 
	* Creates new @c CAknColumnListBoxView object and returns pointer to it.
	* @return Pointer to the list box view which displays the list items which
	* are currently visible in a list box.
    */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
    
    /** 
    * Creates @c CAknFilteredTextListBoxModel object.
    */
    IMPORT_C virtual void CreateModelL();

    /** 
    * Listbox rectangle calculation. Rounds down the height of the rectangle
    * (if necessary) so that only a whole number of items can be displayed
    * inside the list box.
    * @param aRect The size of the listbox.
    * @return The number of pixels reduced.
    */
    IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const;
    
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: // listbox use only
	IMPORT_C virtual void CEikListBox_Reserved(); 
    };


//
// These define what features are needed --> you can remove shortcuts from ALL lists by changing these..
// Templates available: AknListBoxLinesTemplate<> AknListBoxShortCutTemplate<>
typedef AknListBoxLinesTemplate<CAknColumnListBox > CEikColumnListBoxTypedef;
typedef AknListBoxLinesTemplate<CEikFormattedCellListBox > CEikFormattedCellListBoxTypedef;
typedef AknListBoxLinesTemplate<CEikSettingsListBox > CEikSettingsListBoxTypedef;
typedef CAknGrid CAknSelectionGridTypedef;

// Templates available: AknListBoxShortCutTemplate<> AknListBoxLinesTemplate<>
#define AKNCOLUMNLISTBOXNAME(x) AknListBoxLinesTemplate<CAknColumnListBox >(x)
#define AKNDOUBLELISTBOXNAME(x) AknListBoxLinesTemplate<CEikFormattedCellListBox >(x)
#define AKNSETTINGLISTBOXNAME(x) AknListBoxLinesTemplate<CEikSettingsListBox >(x)

// Templates available: AknListBoxLinesTemplate<>, AknListBoxShortCutTemplate<>
#define AKNCOLUMNLISTBOX AknListBoxLinesTemplate<CAknColumnListBox >
#define AKNFORMATTEDLISTBOX AknListBoxLinesTemplate<CEikFormattedCellListBox >
#define AKNSETTINGSLISTBOX AknListBoxLinesTemplate<CEikSettingsListBox >
#define AKNGRID CAknGrid







//
//
// Derived listboxes (Use these in applications!)
// These are only for full screen lists -- the Rect() of the list must be ClientRect()
//
//


/**
 * list_single_pane
 *
 * list item string format: "\tTextLabel\t0\t1"
 * where 0 and 1 are indexes to icon array
 */

class CAknSingleStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);  
private:
    void SizeChangedL();
    };

/**
 * list_single_number_pane
 *
 * list item string format: "2\tTextLabel\t0\t1"
 * where 0 and 1 are indexes to icon array
 */

class CAknSingleNumberStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleNumberStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);   
private:
    void SizeChangedL();
    };

/**
 * list_single_heading_pane
 *
 * list item string format: "Heading\tTextLabel\t0\t1"
 * where 0 and 1 are indexes to icon array
 *
 */

class CAknSingleHeadingStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleHeadingStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 

protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    
   /** MakeViewClassInstanceL()
    *
    * Chooses which listbox view class to use
    */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
private:
    void SizeChangedL();
    };


/**
 * list_single_graphic_pane
 *
 * list item string format: "0\tTextLabel\t1\t2"
 * where 0,1,2 are index to the icon array 
 */

class CAknSingleGraphicStyleListBox : public CEikColumnListBoxTypedef
    {
public: 
    IMPORT_C CAknSingleGraphicStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };

/**
 * list_single_Graphic_heading_pane
 *
 * list item string format: "0\tHeading\tTextLabel\t1\t2"
 * where 0,1,2 are index to the icon array 
 */

class CAknSingleGraphicHeadingStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleGraphicHeadingStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);    
protected:
    IMPORT_C virtual void CreateItemDrawerL();
   /** MakeViewClassInstanceL()
    *
    * Chooses which listbox view class to use
    */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
private:
    void SizeChangedL();
    };

/**
 * list_single_number_heading_pane
 *
 * list item string format: "1\tHeading\tTextLabel\t2\t3"
 * where 2 and 3 are indexes to icon array
 */

class CAknSingleNumberHeadingStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleNumberHeadingStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
protected:
    IMPORT_C virtual void CreateItemDrawerL();
   /** MakeViewClassInstanceL()
    *
    * Chooses which listbox view class to use
    */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
private:
    void SizeChangedL();
    };

/**
 * list_single_large_pane
 *
 * list item string format: "1\tTextLabel\t0\t0"
 * where 0 is an index to icon array
 */

class CAknSingleLargeStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleLargeStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);   
private:
    void SizeChangedL();
    };

/**
 * list_double_pane and list_big_single_pane
 *
 * list item string format: " \tFirstLabel\tSecondLabel\t0\t0"
 * where 0 is an index to icon array
 */

class CAknDoubleStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDoubleStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };

/**
 * list_twoline_pane
 *
 * list item string format: " \tFirstLongLabel\t\t0"
 * where 0 is an index to icon array
 */

class CAknDoubleStyle2ListBox : public CAknDoubleStyleListBox
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C void CreateItemDrawerL();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
    void SizeChangedL();
    };

 /**
 * list_double_number_pane and list_big_single_number_pane
 *
 * list item string format: "1\tFirstLabel\t\t0\t0"
 * list item string format: "1\tFirstLabel\tSecondLabel\t0\t0"
 * where 0 is an index to icon array
 *
 */

class CAknDoubleNumberStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDoubleNumberStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };

/**
 * list_double_time_pane
 */

class CAknDoubleTimeStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDoubleTimeStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
    void SizeChangedL();
    };

/**
 * list_double_large_pane
 *
 * list item string format: "1\tFirstLabel\tSecondLabel\t0\t0"
 *
 * where 0 is an index of small (13x13) icon in icon array
 *   and 1 is an index of a thumbnail image
 *
 * Good thumbnail image sizes for this list are:
 *   30x40, 36x44, 40x30, 40x48, 44x36.
 */

class CAknDoubleLargeStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDoubleLargeStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };


/**
 * list_double_graphic_pane
 *
 * list item string format: "0\tFirstLabel\tSecondLabel\t0"
 * where 0 is index to icon array
 *
 */

class CAknDoubleGraphicStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDoubleGraphicStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };


/** 
 * list_double2_graphic_pane
 *
 * list item string format: "0\tFirstLabel\tSecondLabel\t0"
 * where 0 is index to icon array
 *
 */

class CAknDouble2GraphicStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDouble2GraphicStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();

	/** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C void CreateItemDrawerL();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };


/**
 * list_double2_large_graphic_pane
 *
 * list item string format: "1\tFirstLabel\tSecondLabel\t0"
 *
 * where 0 is an index of small (13x13) icon in icon array
 *   and 1 is an index of a thumbnail image
 *
 */

class CAknDouble2LargeStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDouble2LargeStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };


/**
*  list_double2_graphic_large_graphic_pane
*
*  This is similar but not identical to
*  java list CAknDouble2GraphicLargeStyleListBox
*
*  list item string format: "0\t1\tFirstLabel\tSecondLabel\t2\t3"
*
*  where 0 (mandatory), 2 and 3 (optional) are an index of small icon
*  in icon array and 1 (mandatory) is an index of a thumbnail image
*
*  @lib avkon
*  @since Series 60 2.8
*/

class CAknDouble2GraphicLargeGraphicStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDouble2GraphicLargeGraphicStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);   
private:
    void SizeChangedL();
    };


/**
 * list_double2_graphic_pane
 *
 * list item string format: "1\tFirstLabel\tSecondLabel\t0"
 * where 0 is an index to icon array
 *
 */

class CAknFormDoubleGraphicStyleListBox : public CAknDoubleGraphicStyleListBox
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };
typedef CAknFormDoubleGraphicStyleListBox CAknSingleBigHeadingGraphicListBox;

/**
 * list_double2_pane
 *
 * list item string format: " \tFirstLabel\tSecondLabel\t0"
 * where 0 is an index to icon array
 */

class CAknFormDoubleStyleListBox : public CAknDoubleStyleListBox
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };
typedef CAknFormDoubleStyleListBox CAknSingleBigHeadingListBox;


/**
 * list_setting_pane and list_big_single_setting_pane
 *
 * list item string format: "\tFirstLabel\t\tValueText"
 * list item string format: "\tFirstLabel\t0\t"
 * list item string format: "\tFirstLabel\t\tValueText\t*"
 * list item string format: "\tFirstLabel\t\t\t\tSecondLabel"
 * where 0 is an index to icon array
 */

class CAknSettingStyleListBox : public CEikSettingsListBoxTypedef
    {
public:
    IMPORT_C CAknSettingStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };

/**
 * list_setting_number_pane and list_big_single_setting_number_pane
 *
 * list item string format: "1\tFirstLabel\t\tValueText"
 * list item string format: "2\tFirstLabel\t0\t"
 * list item string format: "3\tFirstLabel\t\tValueText\t*"
 * list item string format: "4\tFirstLabel\t\t\t\tSecondLabel"
 * where 0 is an index to icon array
 * and 1..4 is list item number shown on screen
 */
class CAknSettingNumberStyleListBox : public CEikSettingsListBoxTypedef
    {
public:
    IMPORT_C CAknSettingNumberStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };


//
// Use the popup styles with CAknPopupList and CAknListQueryDialog
//

/**
 * list_single_popup_menu_pane
 *
 * list item string format: "FirstLabel\t0"
 *
 * where 0 is an index to icon array
 */

class CAknSinglePopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
    void SizeChangedL();
    };

/**
 * list_single_graphic_popup_menu_pane
 *
 * list item string format: "0\tLabel"
 *
 * where 0 is an index to icon array
 */

class CAknSingleGraphicPopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);  
private:
    void SizeChangedL();
    };

/**
 * list_single_graphic_bt_popup_menu_pane
 *
 * list item string format: "0\tLabel"
 *
 * where 0 is an index to icon array
 *
 */

class CAknSingleGraphicBtPopupMenuStyleListBox : public CAknSingleGraphicPopupMenuStyleListBox
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C virtual void SizeChanged();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);    
    };

/**
 * list_single_heading_popup_menu_pane
 *
 * list item string format: "Heading\tLabel"
 *
 */

class CAknSingleHeadingPopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    IMPORT_C CAknSingleHeadingPopupMenuStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);    
protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
private:
    void SizeChangedL();
    };


/**
 * list_single_graphic_heading_popup_menu_pane
 *
 * list item string format: "0\tHeading\tLabel"
 *
 * where 0 is an index to icon array
 *
 */

class CAknSingleGraphicHeadingPopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>

    {
public:
    IMPORT_C CAknSingleGraphicHeadingPopupMenuStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
private:
    void SizeChangedL();
    };

/**
 * list_double_popup_menu_pane
 *
 * list item string format: "FirstLabel\tSecondLabel"
 *
 */

class CAknDoublePopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
private:
    void SizeChangedL();
    };

/**
 * list_single_popup_submenu_pane
 *
 * DO NOT USE
 *
 */

class CAknSinglePopupSubmenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
    };


/**
 * list_double_large_graphic_popup_menu_pane
 *
 * list item string format: "0\tFirstLabel\tSecondLabel"
 *
 * where 0 is an index to icon array
 *
 */

class CAknDoubleLargeGraphicPopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
private:
    void SizeChangedL();
    };


/**
 * list_double2_popup_menu_pane
 *
 * list item string format: "FirstLabel\tSecondLabel"
 *
 */

class CAknDouble2PopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);  
protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
private:
    void SizeChangedL();
    };
    
    
/**
 * list_single_2graphic_pane_cp2
 *
 * list item string format: "0\t1\tTextLabel\t2\t3"
 *
 * where 0,1,2,3 are index to the icon array 
 */

class CAknSingle2GraphicPopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    IMPORT_C CAknSingle2GraphicPopupMenuStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
    void SizeChangedL();
    };



/**
 * list_double_graphic_pane
 *
 * list item string format: "0\tFirstLabel\tSecondLabel\t1\t2"
 * where 0 is index to icon array
 *
 */
class CAknDoubleGraphicPopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    IMPORT_C CAknDoubleGraphicPopupMenuStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
    void SizeChangedL();
    };
    
// --- end of popup styles



/** list_set_pane
 * Setting Page component uses this
 *
 * list item string format: "1\tShortLabel"
 * list item string format: "\t\tLongLabel"
 *
 */
class CAknSetStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    IMPORT_C void ConstructWithWindowL(const CCoeControl *aParent, TInt aFlags);
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    IMPORT_C void Draw(const TRect& aRect) const;
    IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 

protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
   /** MakeViewClassInstanceL()
    *
    * Chooses which listbox view class to use
    */
    IMPORT_C CListBoxView *MakeViewClassInstanceL();
private:
    void SizeChangedL();
    };

/** list_form_graphic_pane
 * Form popup field should use this
 *
 * list item string format: "1\tShortLabel"
 * list item string format: "\t\tLongLabel"
 *
 */
class CAknFormGraphicStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    IMPORT_C void ConstructWithWindowL(const CCoeControl *aParent, TInt aFlags);
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the grid for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    /** Listbox rectangle calculation.
     */
    IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect &aRect) const;
     /**
     * From CCoeControl
     * Handles pointerevents of popupfield's list
     * @param aPointerEvent pointerevent to be handled
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 
private:
    void SizeChangedL();
	};

class CAknFormGraphicWideStyleListBox : public CAknFormGraphicStyleListBox
    {
public:
    IMPORT_C void SizeChanged();
    IMPORT_C TSize MinimumSize();
    // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);  
private:
    void SizeChangedL();
    };


/** grid_app_pane
 * Application Shell uses this (note that part of layout needs to be done
 * inside application -- the listbox will not be in correct position on the
 * screen by just using this -- see listapp)
 *
 * list item string format: "1\tLabel"
 * list item string format: "1\tLabel\t1"
 */

/**
 * grid_pinb_pane
 *
 * list item string format: "1"
 * list item string format: "1\t1"
 * list item string format: "1\t1\t1"
 * list item string format: "1\t\t1"
 */

class CAknPinbStyleGrid : public CAknSelectionGridTypedef
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the grid
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the grid for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();

    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 

private:    
    void SizeChangedL();
    };


/**
 * grid_qdial_pane
 */

class CAknQdialStyleGrid : public CAknSelectionGridTypedef
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the grid
     */
    IMPORT_C virtual void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the grid for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();

    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 

private:
    void SizeChangedL();
    };

/**
 * grid_cale_month_pane
 */

class CAknCaleMonthStyleGrid : public CAknSelectionGridTypedef
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the grid for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From CCoeControl.     
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);  

private:
    void SizeChangedL();
    };



//
//
// Here we have itemdrawer/view modifications needed by the lists
//
//

// This class is to keep drawing routines that depend on avkon and which we cannot place to
// eikstd or uikon because of that.

	/**
 	* A view that provides empty lists for use with find pane
 	* @since Series 60 0.9
 	*/
class CAknColumnListBoxView : public CColumnListBoxView
    {
public:

	/**
	* Enables find in empty list. Basically same as @c SetFindEmptyListState()
	* when it is set @c ETrue.
	*/
    IMPORT_C void EnableFindEmptyList();
    
    /**
    * Sets find in empty list visible or hides it.
    * @param aUsedWithFind Setter to set find visible or to hide it.
    */
    IMPORT_C void SetFindEmptyListState(TBool aUsedWithFind);
    
    /**
    * Draws empty list with or without find depending if it has been enabled.
    * @param aClientRect The client rectangle.
    */
    IMPORT_C void DrawEmptyList(const TRect &aClientRect) const;
    
    /**
    * Calls @c CColumnListBoxView::CalcBottomItemIndex() and removes filtering
    * from find box if new list items are added. Called by listbox control when
    * either the size of the listbox or the number of items in its model has
    * changed.
    */
    IMPORT_C virtual void CalcBottomItemIndex();
    TBool GetFindEmptyListState();    
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
private:
    TBool iEmptyListWithFind;
    };

/**
 * empty list for settings item editing
 */

class CAknSetStyleListBoxView : public CFormattedCellListBoxView
    {
public:
    IMPORT_C void DrawEmptyList(const TRect &aClientRect) const ;
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
    };


/**
 * Horizontal lines and empty list support for views
 */

class CSingleHeadingStyleView : public CAknColumnListBoxView
    {
public:
    IMPORT_C void Draw(const TRect* ) const;
    IMPORT_C void DrawEmptyList(const TRect& aClientRect) const;
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
    };

/**
 * Horizontal lines support for item drawer.
 */
class CSingleHeadingStyleItemDrawer : public CColumnListBoxItemDrawer 
    {
public:
    IMPORT_C CSingleHeadingStyleItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CColumnListBoxData* aColumnData);
    IMPORT_C ~CSingleHeadingStyleItemDrawer();

    IMPORT_C virtual void DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const;

public:
    IMPORT_C void SetTopItemIndex(TInt aTop);

private:
    TInt iTopItemIndex;
	CCoeEnv* iCoeEnv;
    };

/**
 * Thumbnail image positioning for double large styles.
 */
class CDoubleLargeStyleItemDrawer : public CFormattedCellListBoxItemDrawer
    {
public:
    IMPORT_C CDoubleLargeStyleItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CFormattedCellListBoxData* aFormattedCellData, CEikListBox *aListBox);
    IMPORT_C void DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const;
private:
	IMPORT_C void CFormattedCellListBoxItemDrawer_Reserved();
private:
    CEikListBox *iListBox_tmp;
    };


/**
 * Word wrapping for double2 styles
 */
class CWordWrappedFormattedCellItemDrawer : public CFormattedCellListBoxItemDrawer
    {
public:
    IMPORT_C CWordWrappedFormattedCellItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CFormattedCellListBoxData* aFormattedCellData, CEikListBox *aListBox, TInt aSubCell, TInt aSubCell2);
    IMPORT_C void DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const;
    IMPORT_C void DrawItemText(TInt aItemIndex,
			       const TRect &aItemTextRect,
			       TBool aItemIsCurrent,
			       TBool,
			       TBool aItemIsSelected) const;
private:
	IMPORT_C void CFormattedCellListBoxItemDrawer_Reserved();
private:
    TInt iSubCell, iSubCell2;
    };

//
//
//  here starts section for building new listboxes.
//

//
// This is helper class that makes the conversion between European LAF and
// different listbox itemdrawer implementations.
//
// Notice, this CEikListBox is a good friend with this class.
//
// 

/** AknListBoxLayouts
 * Building listbox layouts from European Avkon LAF.
 *
 * The LAF specification has 3 kinds of tables:
 *   Graphics tables
 *   Text tables
 *   Pane coordinates
 * The graphics tables map to SetupColumnGfxCell() and SetupFormGfxCell()
 * The text tables map to SetupColumnTextCell() and SetupFormGfxCell()
 * The pane coordinates map to SetupListboxPos().
 *
 * This class is mostly useless if you don't have LAF specification available!
 *
 * You probably want to use predefined layouts; See CAknSingleStyleListBox.
 *
 * NOTE: This class is old design. You should consider looking at aknutils.h: AknLayoutUtils
 *       whenever you want to build things from the LAF specification. 
 */

class AknListBoxLayouts
    {
public:
    /**
     * Setup borders etc.
     */
    IMPORT_C static void SetupStandardListBox(CEikListBox& aListBox);
     /**
     * Setup grid position
     * since 2.0
     */
    static void SetupGridPos(CAknGrid& aGrid,
                     const TAknWindowLineLayout &aLayout);
   /**
     * Setup grid position
     */
    IMPORT_C static void SetupGridPos(CAknGrid& aGrid,
    			     TInt l, 
    			     TInt t, 
    			     TInt /*r*/, 
    			     TInt /*b*/, 
    			     TInt W, 
    			     TInt H);
    /**
     * Setup list position
     */
    IMPORT_C static void SetupListboxPos(CEikListBox& aListBox,
				TInt startx, 
    				TInt starty, 
    				TInt,
    				TInt, 
    				TInt /*width*/, 
    				TInt height);

    /*
    * non-exported new internal version
    */
    static void SetupListboxPosL( CEikListBox& aListBox,
                                  const TAknWindowLineLayout& aLayout ); // layout of first item
        
    /**
     * Setup text foreground and background colors to default
     */
    IMPORT_C static void SetupStandardColumnListbox(CColumnListBoxItemDrawer* aItemDrawer);	
    /**
     * Setup text foreground and background colors to default
     */
    IMPORT_C static void SetupStandardFormListbox(CFormattedCellListBoxItemDrawer* aItemDrawer);
    /**
     * Setup text foreground and background colors to default
     */
    IMPORT_C static void SetupStandardGrid(CAknGrid& aGrid);
    
    /**
     * Setup a single graphics cell of list item
     */
    IMPORT_C static void SetupColumnGfxCell(CEikListBox& aListBox, 
				   CColumnListBoxItemDrawer* aItemDrawer, 
				   TInt index,
				   TInt l, 
				   TInt t, 
				   TInt r, 
				   TInt b, 
				   TInt W, 
				   TInt H, 
				   TInt startx, 
				   TInt endx);
    
    /**
     * Setup a single text cell of list item
     */
    IMPORT_C static void SetupColumnTextCell(CEikListBox& aListBox, 
				    CColumnListBoxItemDrawer* aItemDrawer, 
				    TInt index,
				    const CFont *font, 
				    TInt /*C*/, 
				    TInt lm, 
				    TInt rm, 
				    TInt B, 
				    TInt /*W*/, 
				    CGraphicsContext::TTextAlign aAlign, 
				    TInt startx, 
				    TInt endx);
    /**
     * Setup a single text cell of list item
     */
    IMPORT_C static void SetupColumnTextCell(CEikListBox& aListBox, 
				    CColumnListBoxItemDrawer* aItemDrawer, 
				    TInt index,
				    const TAknTextLineLayout &aLayout,
				    TInt startx, 
				    TInt endx); // use with aknlayoutcompiler

    /**
     * Setup a single graphics cell of list item
     */
    IMPORT_C static void SetupFormGfxCell(CEikListBox& aListBox, 
				 CFormattedCellListBoxItemDrawer* aItemDrawer, 
				 TInt index,
				 TInt l, 
				 TInt t, 
				 TInt /*r*/, 
				 TInt /*b*/, 
				 TInt W, 
				 TInt H, 
				 TPoint p1, 
				 TPoint p2);


    /**
     * Setup a single graphics cell of list item
     *
     * This version is needed for grid cells. (the FormGfxCell works in
     * most cases, but this is needed if you want exact positioning of
     * the erased area..)
     */
    IMPORT_C static void SetupGridFormGfxCell(CAknGrid& aListBox, 
				 CFormattedCellListBoxItemDrawer* aItemDrawer, 
				 TInt index,
				 TInt l, 
				 TInt t, 
				 TInt /*r*/, 
				 TInt /*b*/, 
				 TInt W, 
				 TInt H, 
				 TPoint aP1, 
				 TPoint aP2);
    /**
     * Setup a single graphics cell of list item
     *
     * This version is needed for grid cells. (the FormGfxCell works in
     * most cases, but this is needed if you want exact positioning of
     * the erased area..)
     * since 2.6
     */

    IMPORT_C static void SetupGridFormGfxCell(CAknGrid& aGrid,
                 CFormattedCellListBoxItemDrawer* aItemDrawer, 
                 TInt aIndex,
                 const TAknWindowLineLayout& aLine,
                 TPoint& aP1, 
                 TPoint& aP2);         

    /**
     * Setup a single text cell of list item
     */    
    IMPORT_C static void SetupFormTextCell(CEikListBox& aListBox, 
				  CFormattedCellListBoxItemDrawer* aItemDrawer, 
				  TInt index,
				  const CFont *font, 
				  TInt /*C*/, 
				  TInt lm,
				  TInt /*rm*/, 
				  TInt B, 
				  TInt W, 
				  CGraphicsContext::TTextAlign aAlign, 
				  TPoint p1, 
				  TPoint p2);
    /**
     * Setup a single text cell of list item
     *
     * This is for removing flicker for settings
     *
     */
    IMPORT_C static void SetupFormAntiFlickerTextCell(CEikListBox& aListBox, 
				  CFormattedCellListBoxItemDrawer* aItemDrawer, 
				  TInt index,
				  const CFont *font, 
				  TInt /*C*/, 
				  TInt lm,
				  TInt /*rm*/, 
				  TInt B, 
				  TInt W, 
				  CGraphicsContext::TTextAlign aAlign, 
				  TPoint p1, 
				  TPoint p2);

    /**
     * Setup a single text cell of list item
     */
    IMPORT_C static void SetupFormTextCell(CEikListBox& aListBox, 
				  CFormattedCellListBoxItemDrawer* aItemDrawer, 
				  TInt index,
				  const TAknTextLineLayout &aLayout,
				  const TPoint &p1, 
				  const TPoint &p2); // use with layout compiler
    /**
     * Setup a single text cell of list item
     *
     * This is for removing flicker for settings
     */
    IMPORT_C static void SetupFormAntiFlickerTextCell(CEikListBox& aListBox, 
				  CFormattedCellListBoxItemDrawer* aItemDrawer, 
				  TInt index,
				  const TAknTextLineLayout &aLayout,
				  const TPoint &p1, 
				  const TPoint &p2); // use with layout compiler

    /**
     * Setup a graphic element for a column listbox using aknlayout.dll
     */
    IMPORT_C static void SetupColumnGfxCell(CEikListBox& aListBox, 
				   CColumnListBoxItemDrawer* aItemDrawer, 
				   TInt aIndex,
				   const TAknWindowLineLayout &aLayout,
				   TInt startx, 
				   TInt endx);

    /**
     * Setup a single graphics cell of list item using aknlayout.dll
     */
    IMPORT_C static void SetupFormGfxCell(CEikListBox& aListBox, 
				 CFormattedCellListBoxItemDrawer* aItemDrawer, 
				 TInt index,
				 const TAknWindowLineLayout &aLayout,
				 const TPoint &p1, 
				 const TPoint &p2);


    /**
     * Setup a graphic element for a column listbox using aknlayout.dll
     */
    IMPORT_C static void SetupListboxPos(CEikListBox& aListBox, 
				   const TAknWindowLineLayout &aLayout);
				   
    /**
     * This function returns a correct offset to revise layout data.
     *
     * Attention: The function is only effective for QHD lanscape model. 
     * It always return 0 in QVGA, QVGA2, VGA and VAG3. 
     * A panic will take place if it is used in other models.
     *
     * @since S60 5.0
     *
     * @param aScreenRect Size of Screen.
     * @return Offset of listscroll_menu_pane's layout 
     */
    static TInt AdjustPopupLayoutData( const TRect& aScreenRect );				   
    };

/**
* General utilities relating to listboxes
*
* @since Series 60 0.9
*/
class AknListBoxUtils
    {
public:
    /**
    * This function is similar to @c HandleItemRemovalL(). This function has
    * to call when the items should be removed. If a leave occurs the framework
    * generates a Symbian Leave code.
    * @param aListBox A pointer to @c CEikListBox object.
    * @param aValueOfCurrentItemIndexBeforeRemoval A current item index value 
    * before removal.
    * @param aCurrentItemWasRemoved @c ETrue if removed @c EFalse if not.
    */
    IMPORT_C static void HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aValueOfCurrentItemIndexBeforeRemoval, TBool aCurrentItemWasRemoved);
    
    /**
    * This function should be called after one or more items have been removed.
    * If a leave occurs the framework generates a Symbian Leave code. 
    * @param aListBox A pointer to @c CEikListBox object.
    * @param aValueOfCurrentItemIndexBeforeRemoval A current item index value 
    * before removal.
    * @param aIndexesToRemovedItems A thin templated base class for arrays of
    * fixed length objects.
    */
    IMPORT_C static void HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aValueOfCurrentItemIndexBeforeRemoval, CArrayFix<TInt> &aIndexesToRemovedItems);

    /** 
    * @deprecated
    */
    IMPORT_C static TBool ListBoxLinesShown(MAknsSkinInstance *aInstance, MAknsControlContext *aCc);
    };

#endif






