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
* Description:  test protected for CAknSelectionListDialog
*
*/

#ifndef C_TESTSDKLISTSSELECTIONLISTDIALOG_H
#define C_TESTSDKLISTSSELECTIONLISTDIALOG_H

#include <aknselectionlist.h>

#include "testsdklists.h"
/**
 * class for testing protected API of CAknSelectionListDialog
 */    
class CTestSDKListsSelectionListDialog : public CAknSelectionListDialog
{
public:
    /**
    * Default constructor.
    */
    CTestSDKListsSelectionListDialog( TInt &aIndex, MDesCArray *aArray, MEikCommandObserver *aCommand );

    /**
    * Destructor.
    */        
    virtual ~CTestSDKListsSelectionListDialog();

    /** SelectionListProcessCommandL() handles selection list and markable list
     *  default commands.
     *
     *  For markable lists, this method handles EAknCmdMark, EAknCmdUnmark, EAknMarkAll, EAknUnmarkAll
     *  defined in options menu pane R_AVKON_MENUPANE_MARKABLE_LIST.
     */
    virtual void SelectionListProcessCommandL(TInt aCommand);

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
    virtual TBool IsAcceptableListBoxType(TInt aControlType, TBool &aIsFormattedCellList) const;

    /** ProcessCommandL()
    * From CAknDialog. Processes commands and passes commands to FindBox and ListBox as needed.
    * @param aCommandId id of the command.
    */
    void ProcessCommandL( TInt aCommandId );

    /** PreLayoutDynInitL()
    * From CAknDialog.
    */
    void PreLayoutDynInitL();

    /** PreLayoutDynInitL()
    * From CAknDialog.
    */
    void PostLayoutDynInitL();

    /** SetSizeAndPosition()
    * From CAknDialog.
    * Sets dialog's size to whole main pane.
    * @param aSize ignored
    */
    void SetSizeAndPosition(const TSize &aSize);

    /** OkToExitL()
    * From CAknDialog.
    * This is not called if the Cancel button is activated unless the EEikDialogFlagNotifyEsc flag has been set.
    * @param aButtonId The ID of the button that was activated.
    */
    TBool OkToExitL( TInt aButtonId );

    /** HandleListBoxEventL()
    * From MEikListBoxObserver
    * Handles listbox events.
    * @param aListBox currently ignored
    * @param aEventType type of the listbox event
    */
    void HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType );

    /** CountComponentControls()
    * From CCoeControl
    */
    TInt CountComponentControls() const;

    /** ComponentControl()
    * From CCoeControl
    */
    CCoeControl* ComponentControl( TInt aIndex ) const;

    /** OfferKeyEventL()
    * From CCoeControl
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

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
    SEikControlInfo CreateCustomControlL(TInt aControlType);

    /** ListBox()
    * accessor to listbox control
    * @return a pointer to the listbox
    */
    virtual CEikListBox *ListBox() const;

    /** FindBox()
    * accessor to findbox control
    * @return a pointer to the findbox
    */
    CAknSearchField *FindBox() const;

    /** IsFormattedCellListBox()
    * used to check whether listbox control is a CEikFormattedCellListBox or a CEikColumnListBox.
    * If you derive from IsAcceptableListBoxType() you must take care of the aIsFormattedCellListParameter to
    * make this method to work correctly.
    * @return whether listbox control is a CEikFormattedCellListBox
    */
    TBool IsFormattedCellListBox() const;

    /** Draw()
    * from CCoeControl
    */
    void Draw(const TRect&) const;
};

#endif /*C_TESTSDKLISTSSELECTIONLISTDIALOG_H*/
