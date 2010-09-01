/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test protected for CAknMarkableListDialog
*
*/

#ifndef C_TESTSDKLISTSMARKABLELISTDIALOG_H
#define C_TESTSDKLISTSMARKABLELISTDIALOG_H

#include <aknselectionlist.h>

class CTestSDKListsMarkableListDialog : public CAknMarkableListDialog
{
public:
    /**
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
    CTestSDKListsMarkableListDialog( TInt &aOpenedItem,
                                     CArrayFix<TInt> *aSelectedItems,
                                     MDesCArray *aArray,
                                     TInt aMenuBarResourceId,
                                     TInt aOkMenuBarResourceId,
                                     MEikCommandObserver *aObserver );

    /** CAknMarkableListDialog()
    * @deprecated Do not use.
    */
    CTestSDKListsMarkableListDialog( TInt &aValue,
                            CArrayFix<TInt> *aSelectedItems,
                            MDesCArray *aArray,
                            MEikCommandObserver *aObserver);

    /*
    * Destructor.
    */
    virtual ~CTestSDKListsMarkableListDialog();

    /** 
     * PreLayoutDynInitL()
     * From CAknDialog.
     */
    void PreLayoutDynInitL();

    /** 
     * PreLayoutDynInitL()
     * From CAknDialog.
     */
    void PostLayoutDynInitL();

    /** SelectionListProcessCommandL() handles selection list and markable list
    *  default commands.
    *
    *  For markable lists, this method handles EAknCmdMark, EAknCmdUnmark, EAknMarkAll, EAknUnmarkAll
    *  defined in options menu pane R_AVKON_MENUPANE_MARKABLE_LIST.
    */
    void SelectionListProcessCommandL(TInt aCommand);

    /** ProcessCommandL()
    * From CAknDialog. Processes commands and passes commands to FindBox and ListBox as needed.
    * @param aCommand id of the command.
    */
    void ProcessCommandL(TInt aCommand);

    /** DynInitMenuPaneL()
    * From MEikCommandObserver
    * @param aResourceId resource id of the menu pane to be modified
    * @param aMenuPane pointer to menu pane to be modified
    */
    void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane *aMenuPane);

    /** HandleListBoxEventL()
    * From MEikListBoxObserver
    * Handles listbox events.
    * @param aListBox currently ignored
    * @param aEventType type of the listbox event
    */
    void HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType );

    /** OfferKeyEventL()
    * From CCoeControl
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

    /** OkToExitL()
    * From CAknDialog.
    * This is not called if the Cancel button is activated unless the EEikDialogFlagNotifyEsc flag has been set.
    * @param aButtonId The ID of the button that was activated.
    */
    TBool OkToExitL(TInt aButtonId);

    /** ListBox()
    * accessor to listbox control
    * @return a pointer to the listbox
    */
    virtual CEikListBox *ListBox() const;

};

#endif /*C_TESTSDKLISTSMARKABLELISTDIALOG_H*/
