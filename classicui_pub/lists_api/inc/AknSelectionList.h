/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Dialogs for selection service implementation.
*
*/


#ifndef __AKNSELECTIONLIST_H__
#define __AKNSELECTIONLIST_H__

#include <AknForm.h>
#include <aknview.h>
#include <AknUtils.h>
#include <aknPopup.h>
#include <avkon.rsg>

class CAknSelectionListDialogExtension;
class CAknMarkableListDialogExtension;

/** CAknSelectionListDialog is the actual interface to the applications.
*
* Use this class to get a full screen list.
*
* This class only works in whole main pane. Do not try to use
* this directly for other places. 
*
* @lib Avkon.lib
* @since S60 v1.0
*  
* resource definition for this class:
* @code
* RESOURCE DIALOG r_res_id_for_a_dialog
*   {
*   flags = EAknDialogSelectionList;
*   buttons = R_AVKON_SOFTKEYS_OPTIONS_BACK;
*   items =
*        {
*        DLG_LINE
*            {
*            type = EAknCtSingleGraphicListBox;
*            id = ESelectionListControl;
*            control = LISTBOX
*                {
*                flags = EAknListBoxSelectionList;
*                };
*            }
*     // the next dlg line is optional.
 *        ,
*        DLG_LINE
*            {
*             itemflags = EEikDlgItemNonFocusing;
*            id = EFindControl;
*            type = EAknCtSelectionListFixedFind;
*            }
*        };
*   }
* @endcode
* The listbox type can be one of the following (defined in avkon.hrh and aknlists.h):
 @verbatim
   EAknCtSingleListBox                (See CAknSingleStyleListBox)
   EAknCtSingleNumberListBox          (See CAknSingleNumberStyleListBox)
   EAknCtSingleHeadingListBox         (See CAknSingleHeadingStyleListBox)
   EAknCtSingleGraphicListBox         (See CAknSingleGraphicStyleListBox)
   EAknCtSingleGraphicHeadingListBox  (See CAknSingleGraphicHeadingStyleListBox)
   EAknCtSingleNumberHeadingListBox   (See CAknSingleNumberHeadingStyleListBox)
   EAknCtSingleLargeListBox           (See CAknSingleLargeStyleListBox)
   EAknCtDoubleListBox                (See CAknDoubleStyleListBox)
   EAknCtDoubleNumberListBox          (See CAknDoubleNumberStyleListBox)
   EAknCtDoubleTimeListBox            (See CAknDoubleTimeStyleListBox)
   EAknCtDoubleLargeListBox           (See CAknDoubleLargeStyleListBox)
   EAknCtDoubleGraphicListBox         (See CAknDoubleGraphicStyleListBox)
 @endverbatim
* The type field while defining find can be one of the following:
@verbatim
EAknCtSelectionListFixedFind
EAknCtSelectionListPopupFind
EAknCtSelectionListAdaptiveFind
@endverbatim
*
* The menubar you give for selection list dialog should have
* one of the following as one of its menu panes (defined in avkon.hrh):
@verbatim
R_AVKON_MENUPANE_SELECTION_LIST
R_AVKON_MENUPANE_SELECTION_LIST_WITH_FIND_POPUP
@endverbatim
* @code
* RESOURCE MENU_BAR r_res_id_for_a_menubar
* {
* titles =
*     {
*     MENU_TITLE { menu_pane = R_AVKON_MENUPANE_SELECTION_LIST; } 
*     };
* };
* @endcode
* C++ Usage:
* @code
*    TInt openedItem = 0;
*    MDesCArray *array = ...;
*    CAknSelectionListDialog *dialog = CAknSelectionListDialog::NewL(openedItem, array, R_RES_ID_FOR_A_MENUBAR);
*    TInt result = dialog->ExecuteLD(R_RES_ID_FOR_A_DIALOG);
*    if (result)
*        {
*        ...use openeditem here...
*        }
*    else
*        {
*        ...canceled...
*        }
*
* @endcode
* Alternatively, you can use:
* @code
*    TInt openedItem = 0;
*    MDesCArray *array = ...;
*    CAknSelectionListDialog *dialog = CAknSelectionListDialog::NewL(openedItem, array, R_RES_ID_FOR_A_MENUBAR);
*    dialog->PrepareLC(R_RES_ID_FOR_A_DIALOG);
*    // do some operations here, for example fill icon array 
*    TInt result = dialog->RunLD();
*    if (result)
*        {
*        ...
*        }
*    else
*        {
*        ...
*        }
* @endcode
*
* Often it is also useful to derive from CAknSelectionListDialog and implement OkToExitL(), constructors and the NewL() methods.
* OkToExitL() implementation helps with providing navigation with other dialogs; OkToExitL() is ideal place to launch
* new dialogs when a list item is selected. This way when backstepping, the state of the first dialog is preserved...
*
*
*/
class CAknSelectionListDialog : public CAknDialog, public MEikListBoxObserver
    {
public:
    /** CAknSelectionListDialog::NewL()
    *
    * Static factory constructor. Uses two phase construction and leaves nothing on the CleanupStack.
    * 
    * @param aOpenedItem   Variable to be modified when user selects a list item.
    * @param aArray        Content of list items; A tab-separated string with texts and indexes to icon array
    * @param aMenuBarResourceId Menu items to be shown in options menu
    * @param aCommand      Callback for state changes. EAknCmdOpen command is send by listbox. Options menu commands come here too.
    * @return A pointer to created object  
    */
    IMPORT_C static CAknSelectionListDialog *NewL( TInt &aOpenedItem, MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aCommand = 0 );

    /** CAknSelectionListDialog::NewLC()
    *
    * Static factory constructor. Uses two phase construction and leaves created object in CleanupStack.
    * 
    * @param aOpenedItem   Variable to be modified when user selects a list item.
    * @param aArray        Content of list items; A tab-separated string with texts and indexes to icon array
    * @param aMenuBarResourceId Menu items to be shown in options menu
    * @param aCommand      Callback for state changes. EAknCmdOpen command is send by listbox. Options menu commands come here too.
    * @return A pointer to created object  
    */
    IMPORT_C static CAknSelectionListDialog *NewLC( TInt &aOpenedItem, MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aCommand = 0 );

    /** ConstructL()
    * Second phase constructor.
    *
    * @param aMenuTitleResourceId Menu items to be shown in options menu. Same as aMenuBarResourceId of NewL(C).
    */
    IMPORT_C void ConstructL(TInt aMenuTitleResourceId);

public:
    /** CAknSelectionListDialog::TFindType
    *   Determines what kind of findbox should be used. Note, that a fixed findbox is not
    *   available with all list types.
    */
    enum TFindType
        {
         /** no findbox should be used */
        ENoFind,
        /** fixed findbox should be used */
        EFixedFind,
        /** popup findbox should be used */
        EPopupFind,
	   /** fixed findbox with adaptive search should be used */
        EAdaptiveFind
        };
        
    /** SetupFind()
    *
    * Provides a way to enable and disable find and find popup on runtime.
    * You still need entry with id EFindControl to resource file for the find, this is only for disabling
    * existing find element.
    *
    * @param aType type of findbox to be used.
    */
    IMPORT_C void SetupFind(TFindType aType);

    /** IconArray()
    *
    * Icons, images and thumbnails are in this array.
    *
    * The list items are tab separated strings with fixed format. Some of the numbers
    * in the list item strings are indexes to this array.
    *
    * This array can be modified by MDesCArray::MdcaPoint() method or at construction of
    * dialog; after PrepareLC() call.
    *
    * @return pointer to iconarray of the list
    */
    IMPORT_C CArrayPtr<CGulIcon>* IconArray() const;

    /**   SetIconArrayL()
    *
    * Icons, images and thumbnails are in this array.
    *
    * The list items are tab separated strings with fixed format. Some of the numbers
    * in the list item strings are indexes to this array.
    *
    * This array can be modified by MDesCArray::MdcaPoint() method or at construction of
    * dialog; after PrepareLC() call.
    *
    * @param aIcons a array containing icons.
    */
    IMPORT_C void SetIconArrayL(CArrayPtr<CGulIcon>* aIcons);

    /**
    * From CCoeControl.     
    * Handles pointer events
    * @param aPointerEvent     The pointer event.
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
        
protected:
    /** CAknSelectionListDialog()
    * Default constructor.
    */
    IMPORT_C CAknSelectionListDialog( TInt &aIndex, MDesCArray *aArray, MEikCommandObserver *aCommand );
    /** ~CAknSelectionListDialog()
    * Destructor.
    */        
    IMPORT_C ~CAknSelectionListDialog();
        
protected: // Customisation from derived classes
    /** SelectionListProcessCommandL() handles selection list and markable list
     *  default commands.
     *
     *  For markable lists, this method handles EAknCmdMark, EAknCmdUnmark, EAknMarkAll, EAknUnmarkAll
     *  defined in options menu pane R_AVKON_MENUPANE_MARKABLE_LIST.
     */
    IMPORT_C virtual void SelectionListProcessCommandL(TInt aCommand);

    /** IsAcceptableListBoxType(): Detection of list and grid layouts
    *
    * The CAknSelectionList only works with certain list and grid
    * layouts.
    *
    * You will get Panic() if you use your own list/grid layouts and
    * you do not have this method implemented!
    *
    * If you add new list layouts, you should implement this method to
    * publish the type of the layout using this method. This is especially
    * the case where you use CAknSelectionGrid with your own grid layout.
    * (as there are no predefined grid layouts, you need to do this
    * every time you use a selection grid)
    *
    * The following aControlTypes are already implemented and requires
    * no action:
    * @verbatim
     EAknCtSingleListBox
     EAknCtSingleNumberListBox
     EAknCtSingleHeadingListBox
     EAknCtSingleGraphicListBox
     EAknCtSingleGraphicHeadingListBox
     EAknCtSingleNumberHeadingListBox
     EAknCtSingleLargeListBox
     EAknCtDoubleListBox
     EAknCtDoubleNumberListBox
     EAknCtDoubleTimeListBox
     EAknCtDoubleLargeListBox
     EAknCtDoubleGraphicListBox
     EAknCtSettingListBox
     EAknCtSettingNumberListBox
     @endverbatim
    *
    * Any other layout requires you to inherit from CAknSelectionList
    * and implement the following methods:
    * @code
    * TBool IsAcceptableListBoxType(TInt aControlType, TBool &aIsFormattedCellList)
    *     {
    *     if (aControlType == EMyCtGridLayout)
    *         {
    *         // CAknGrid is-a formattedcelllistbox.
    *         aIsFormattedCellList = ETrue;
    *         return ETrue;
    *         }
    *     else
    *        {
    *        return EFalse;
    *        }
    *     }
    *
    * @endcode
    * See also CreateCustomControlL(). IsAcceptableListBoxType() and CreateCustomControlL() forms a pair that should
    * be implemented together.
    *
    * @param aControlType type of the control. Ignored in current default implementation.
    * @param aIsFormattedCellList returns whetehr list is a formatted cell listbox or a column listbox.
    * Ignored in current default implementation. In derived implementations this must be set according to
    * dialog's listbox type.
    * @return whether layout can be used
    */
    IMPORT_C virtual TBool IsAcceptableListBoxType(TInt aControlType, TBool &aIsFormattedCellList) const;
protected:
    /** ProcessCommandL()
    * From CAknDialog. Processes commands and passes commands to FindBox and ListBox as needed.
    * @param aCommandId id of the command.
    */
    IMPORT_C void ProcessCommandL( TInt aCommandId );

    /** PreLayoutDynInitL()
    * From CAknDialog.
    */
    IMPORT_C void PreLayoutDynInitL();

    /** PreLayoutDynInitL()
    * From CAknDialog.
    */
    IMPORT_C void PostLayoutDynInitL();

    /** SetSizeAndPosition()
    * From CAknDialog.
    * Sets dialog's size to whole main pane.
    * @param aSize ignored
    */
    IMPORT_C void SetSizeAndPosition(const TSize &aSize);

    /** OkToExitL()
    * From CAknDialog.
    * This is not called if the Cancel button is activated unless the EEikDialogFlagNotifyEsc flag has been set.
    * @param aButtonId The ID of the button that was activated.
    */
    IMPORT_C TBool OkToExitL( TInt aButtonId );

    /** HandleListBoxEventL()
    * From MEikListBoxObserver
    * Handles listbox events.
    * @param aListBox currently ignored
    * @param aEventType type of the listbox event
    */
    IMPORT_C void HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType );

    /** CountComponentControls()
    * From CCoeControl
    */
    IMPORT_C TInt CountComponentControls() const;

    /** ComponentControl()
    * From CCoeControl
    */
    IMPORT_C CCoeControl* ComponentControl( TInt aIndex ) const;

    /** OfferKeyEventL()
    * From CCoeControl
    */
    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

    /** CreateCustomControlL() creates own list or grid layouts.
    *
    * Normal implementation of this method is:
    *
    * @code
    * SEikControlInfo CreateCustomControlL(TInt aControlType)
    *     {
    *     CCoeControl *control = NULL;
    *     if ( aControlType == EMyCtGridLayout )
    *         {
    *         // CMyOddStyleGrid should be derived from CAknFormattedCellListBox or CEikColumnListBox.
    *         control = new(ELeave)CMyOddStyleGrid;
    *         } 
    *     SEikControlInfo info = {control,0,0};
    *     return info;
    *     }
    * @endcode
    * See also IsAcceptableListBoxType(). CreateCustomControlL() and IsAcceptableListBoxType() forms a pair that should
    * be implemented together.
    */
    IMPORT_C SEikControlInfo CreateCustomControlL(TInt aControlType);
protected:
    /** ListBox()
    * accessor to listbox control
    * @return a pointer to the listbox
    */
    IMPORT_C virtual CEikListBox *ListBox() const;

    /** FindBox()
    * accessor to findbox control
    * @return a pointer to the findbox
    */
    IMPORT_C CAknSearchField *FindBox() const;

    /** IsFormattedCellListBox()
    * used to check whether listbox control is a CEikFormattedCellListBox or a CEikColumnListBox.
    * If you derive from IsAcceptableListBoxType() you must take care of the aIsFormattedCellListParameter to
    * make this method to work correctly.
    * @return whether listbox control is a CEikFormattedCellListBox
    */
    IMPORT_C TBool IsFormattedCellListBox() const;

    /** Draw()
    * from CCoeControl
    */
    IMPORT_C void Draw(const TRect&) const;
private: 
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: 
    IMPORT_C virtual void CEikDialog_Reserved_1();
    IMPORT_C virtual void CEikDialog_Reserved_2();
private: 
    IMPORT_C virtual void CAknDialog_Reserved();
private: // new function 
    IMPORT_C virtual void CAknSelectionListDialog_Reserved();
protected:
    /** iEnterKeyPressed Set as ETrue if EAknCmdOpen is handled in
    * ProcessCommandL(). This will eventually cause OkToExitL() to
    * be called with EAknSoftkeyOk as aButtonId.
    */
    TBool iEnterKeyPressed;
protected:
    /** ExitViaIdle()
    *
    * Callback function to exit dialog after selecting something with
    * tapping it.  This prevents dialog to be destroyed before dialog
    * page's handlepointereventl is fully completed.
    * @param aSelectionList pointer to current CAknSelectionList
    */
    static TInt ExitViaIdle(TAny* aSelectionList );    
private:
    CAknSelectionListDialogExtension *iExtension;
private:
    CAknSearchField *iFindBox;
    TFindType iFindType;
    TInt *iSelectedItem;
    MDesCArray *iArray;
    MEikCommandObserver *iCmdObserver;
    TInt iDialogResourceId;
    TInt iSpare[4];
    };

/** CAknMarkableListDialog is an interface for applications
*
* The class provides a list with items markable with shift+selection_key.
*
* What this class does:
*
*   1) Setup listbox for markable list (resource file still needs to be correct for markable lists :)
*
*   2) Loading default bitmaps
*
*   3) Handles mark/unmark/mark all/unmark all and edit list options menu visibility
*
*   4) Handles mark/unmark/mark all/unmark all commands from options menu
*
*
*
* @lib Avkon.lib
* @since S60 v1.0
*
* resource definition for this class:
@code
* RESOURCE DIALOG r_res_id_for_a_dialog
*   {
*   flags = EAknDialogMarkableList;
*   buttons = R_AVKON_SOFTKEYS_OPTIONS_BACK;
*   items =
*        {
*        DLG_LINE
*            {
*            type = EAknCtSingleGraphicListBox;
*            id = ESelectionListControl;
*            control = LISTBOX
*                {
*                flags = EAknListBoxMarkableList;
*                };
*            }
*     // the next dlg line is optional.
*        ,
*        DLG_LINE
*            {
*             itemflags = EEikDlgItemNonFocusing;
*            id = EFindControl;
*            type = EAknCtSelectionListFixedFind;
*            }
*        };
*   }
@endcode

* The listbox type can be one of the following ( defined in avkon.hrh and aknlists.h ):
@verbatim
EAknCtSingleListBox                (See CAknSingleStyleListBox)
EAknCtSingleNumberListBox          (See CAknSingleNumberStyleListBox)
EAknCtSingleHeadingListBox         (See CAknSingleHeadingStyleListBox)
EAknCtSingleGraphicListBox         (See CAknSingleGraphicStyleListBox)
EAknCtSingleGraphicHeadingListBox  (See CAknSingleGraphicHeadingStyleListBox)
EAknCtSingleNumberHeadingListBox   (See CAknSingleNumberHeadingStyleListBox)
EAknCtSingleLargeListBox           (See CAknSingleLargeStyleListBox)
EAknCtDoubleListBox                (See CAknDoubleStyleListBox)
EAknCtDoubleNumberListBox          (See CAknDoubleNumberStyleListBox)
EAknCtDoubleTimeListBox            (See CAknDoubleTimeStyleListBox)
EAknCtDoubleLargeListBox           (See CAknDoubleLargeStyleListBox)
EAknCtDoubleGraphicListBox         (See CAknDoubleGraphicStyleListBox)
@endverbatim
*
* The type field while defining find can be one of the following:
@verbatim
EAknCtSelectionListFixedFind
EAknCtSelectionListPopupFind
EAknCtSelectionListAdaptiveFind
@endverbatim
*
* The menubar you give for markable list dialog should have
* one of the following as menu panes:
@verbatim
R_AVKON_MENUPANE_MARKABLE_LIST   to get edit list menu
R_AVKON_MENUPANE_MARKABLE_LIST_WITH_FIND_POPUP to get find and edit list
@endverbatim
*
* @code
* RESOURCE MENU_BAR r_res_id_for_a_menubar
*     {
*     titles =
*         {
*         MENU_TITLE { menu_pane = R_AVKON_MENUPANE_MARKABLE_LIST; }
*         };
*     };
* @endcode
*
* C++ Usage:
*
* @code
*    TInt openedItem = 0;
*    MDesCArray *arrayOfItems = ...; 
*    CArrayFix<TInt> *selectedItems = ...;
*    CAknMarkableListDialog *dialog = CAknMarkableListDialog::NewL(openedItem, selectedItems, arrayOfItems, R_RES_ID_FOR_A_MENUBAR);
*    TInt result = dialog->ExecuteLD(R_RES_ID_FOR_A_DIALOG);
*    if (result)
*        {
*        ...
*        }
*    else
*        {
*        ...
*        }
* @endcode
*
*/
class CAknMarkableListDialog : public CAknSelectionListDialog
    {
public:
    /** CAknMarkableListDialog::NewL()
    *
    * Static factory constructor. Uses two phase construction.
    * 
    * @param aOpenedItem        Variable to be modified when user
    *                           selects a list item.
    * @param aSelectedItems     array of selected items
    * @param aArray             Content of list items;
    *                           A tab-separated string with texts and indexes to icon array
    * @param aMenuBarResourceId Menu items to be shown in options menu.  May be NULL.
    * @param aOkMenuBarId       Resource id of a menu bar. This menu bar is displayed,
    *                           when there are marked items in the list
    *                           and user presses selection ( OK )  key.  May be NULL.
    * @param aObserver          Observer for the menu bar.  May be NULL.
    * @return A pointer to created object  
    */
    IMPORT_C static CAknMarkableListDialog *NewL( TInt &aOpenedItem,
                                                  CArrayFix<TInt> *aSelectedItems,
                                                  MDesCArray *aArray,
                                                  TInt aMenuBarResourceId,
                                                  TInt aOkMenuBarId,
                                                  MEikCommandObserver *aObserver =0 );
        
    /** CAknMarkableListDialog::NewL()
    *
    * Static factory constructor. Uses two phase construction.
    * Leaves created object to cleanup stack.
    * 
    * @param aOpenedItem        Variable to be modified when user
    *                           selects a list item.
    * @param aSelectedItems     array of selected items
    * @param aArray             Content of list items;
    *                           A tab-separated string with texts and indexes to icon array
    * @param aMenuBarResourceId Menu items to be shown in options menu. May be NULL.
    * @param aOkMenuBarId       Resource id of a menu bar. This menu bar is displayed,
    *                           when there are marked items in the list
    *                           and user presses selection ( OK )  key. May be NULL.
    * @param aObserver          Observer for the menu bar. May be NULL.
    * @return A pointer to created object  
    */
    IMPORT_C static CAknMarkableListDialog *NewLC( TInt &aOpenedItem,
                                                   CArrayFix<TInt> *aSelectedItems,
                                                   MDesCArray *aArray,
                                                   TInt aMenuBarResourceId,
                                                   TInt aOkMenuBarId,
                                                   MEikCommandObserver *aObserver =0 );

    /** ConstructL()
    * 2nd phase constructor.
    * @param aMenuTitleResourceId Menu items to be shown in options menu
    */
    IMPORT_C void ConstructL( TInt aMenuTitleResourceId );

    /* ~CAknMarkableListDialog()
    * Destructor.
    */
    IMPORT_C ~CAknMarkableListDialog();

public: // From CCoeControl
    /** HandlePointerEventL()
    * from CCoeControl.
    * @param aPointerEvent a pointer event.
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected:
    /** CAknMarkableListDialog()
    *
    * Default constructor.
    * @param aOpenedItem           Variable to be modified when user
    *                              selects a list item.
    * @param aSelectedItems        array of selected items
    * @param aArray                Content of list items;
    *                              A tab-separated string with texts and indexes to icon array
    * @param aMenuBarResourceId    Menu items to be shown in options menu. May be NULL.
    * @param aOkMenuBarResourceId  Resource id of a menu bar. This menu bar is displayed,
    *                              when there are marked items in the list
    *                              and user presses selection ( OK )  key. May be NULL.
    * @param aObserver             Observer for the menu bar. May be NULL.
    * @return                      A pointer to created object  
    */
    IMPORT_C CAknMarkableListDialog( TInt &aOpenedItem,
                                     CArrayFix<TInt> *aSelectedItems,
                                     MDesCArray *aArray,
                                     TInt aMenuBarResourceId,
                                     TInt aOkMenuBarResourceId,
                                     MEikCommandObserver *aObserver );
    /** PreLayoutDynInitL()
    * From CAknDialog.
    */
    IMPORT_C void PreLayoutDynInitL();

    /** PreLayoutDynInitL()
    * From CAknDialog.
    */
    IMPORT_C void PostLayoutDynInitL();

    /** SelectionListProcessCommandL() handles selection list and markable list
    *  default commands.
    *
    *  For markable lists, this method handles EAknCmdMark, EAknCmdUnmark, EAknMarkAll, EAknUnmarkAll
    *  defined in options menu pane R_AVKON_MENUPANE_MARKABLE_LIST.
    */
    IMPORT_C void SelectionListProcessCommandL(TInt aCommand);

    /** ProcessCommandL()
    * From CAknDialog. Processes commands and passes commands to FindBox and ListBox as needed.
    * @param aCommand id of the command.
    */
    IMPORT_C void ProcessCommandL(TInt aCommand);

    /** DynInitMenuPaneL()
    * From MEikCommandObserver
    * @param aResourceId resource id of the menu pane to be modified
    * @param aMenuPane pointer to menu pane to be modified
    */
    IMPORT_C void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane *aMenuPane);

    /** HandleListBoxEventL()
    * From MEikListBoxObserver
    * Handles listbox events.
    * @param aListBox currently ignored
    * @param aEventType type of the listbox event
    */
    IMPORT_C void HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType );

    /** OfferKeyEventL()
    * From CCoeControl
    */
    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

    /** OkToExitL()
    * From CAknDialog.
    * This is not called if the Cancel button is activated unless the EEikDialogFlagNotifyEsc flag has been set.
    * @param aButtonId The ID of the button that was activated.
    */
    IMPORT_C TBool OkToExitL(TInt aButtonId);

private:
    CArrayFix<TInt> *iSelectionIndexArray; // Not owned

protected:
    /**
    * resource id of the menu bar
    */
    TInt iMenuBarResourceId;

    /**
    * resource id of the OK menu bar
    */        
    TInt iOkMenuBarResourceId;

public: // DEPRECATED METHODS, DO NOT USE
    /** NewL()
    * @deprecated Do not use.
    */
    IMPORT_C static CAknMarkableListDialog *NewL(TInt &aOpenedItem, CArrayFix<TInt> *aSelectedItems,
                                                 MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aObserver =0);
    /** NewLC()
    * @deprecated Do  not use.
    */
    IMPORT_C static CAknMarkableListDialog *NewLC(TInt &aOpenedItem, CArrayFix<TInt> *aSelectedItems,
                                                  MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aObserver =0);
protected: // DEPRECATED METHODS, DO NOT USE
     /** CAknMarkableListDialog()
     * @deprecated Do not use.
     */
    IMPORT_C CAknMarkableListDialog(TInt &aValue, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, MEikCommandObserver *aObserver);

private: 
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: 
    IMPORT_C virtual void CEikDialog_Reserved_1();
    IMPORT_C virtual void CEikDialog_Reserved_2();
private: 
    IMPORT_C virtual void CAknDialog_Reserved();
private: 
    IMPORT_C virtual void CAknSelectionListDialog_Reserved();
private:  
    CAknMarkableListDialogExtension *iMarkableExtension;
private:
    TInt iSpare[2];
    };


typedef CAknSelectionListDialog CAknSelectionGridDialog;
typedef CAknMarkableListDialog CAknMarkableGridDialog;


#endif
