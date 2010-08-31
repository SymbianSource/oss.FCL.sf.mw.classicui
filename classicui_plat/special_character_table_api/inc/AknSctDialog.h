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
*     Dialog class for support of Series 60 Special character table
*
*/


#ifndef AKNSCTDIALOG_H
#define AKNSCTDIALOG_H

#include <AknDialog.h>// <eikdialg.h>
#include <aknCharMap.h>

class CAknCharMapDialogExtension;

/**
 * Special character table dialog for AVKON. The dialog contains special
 * character table.
 */
class CAknCharMapDialog : public CAknDialog
    {
public:

    /**
    * AVKON special character table constructor.
    *
    * @param aCharCase Character case for special character table
    *      (EAknSCTLowerCase or EAknSCTUpperCase).
    * @param aSpecialChar Reference to the buffer where selected special characters are put.
    * @param aCharSetResourceId Optional parameter to set editor specific
    *      special character table. If the value is omitted, default AVKON
    *      special character table is shown.
    *
    */
    IMPORT_C CAknCharMapDialog(TInt aCharCase, TDes& aSpecialChars, TInt aCharSetResourceId = 0);

    ~CAknCharMapDialog();

public: // from CEikDialog

    /**
    * Prepares and runs the dialog and returns the id of the button used to dismiss
    * it. The dialog is constructed from the resource with id aResourceId and is destroyed
    * on exit.
    *
    * @param aResourceId Resource id for special character table dialog resource.
    * @return Id of the button used to dismiss dialog.
    *
    */
    IMPORT_C TInt ExecuteLD(TInt aResourceId);

public: // from CCoeControl
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode);

    /**
     * Handles a change to the control's resources of type aType
     * which are shared across the environment, e.g. colors or fonts.
     *
     * @since ER5U
     */
    IMPORT_C void HandleResourceChange(TInt aType);

protected: // from CEikDialog
    IMPORT_C virtual TBool OkToExitL(TInt);
    IMPORT_C virtual void PreLayoutDynInitL();
    IMPORT_C virtual void SetSizeAndPosition(const TSize& aSize);

private:
    IMPORT_C virtual void CEikDialog_Reserved_1();
    IMPORT_C virtual void CEikDialog_Reserved_2();

private: // new function
    IMPORT_C virtual void CAknCharMapDialog_Reserved();

public:
    /*
    * The SCT never shows the pictographs table.
    *
    * @since 2.6
    */
    IMPORT_C void ShowNoPictographs();

    /**
    * When the SCT is opened, it shows pictographs table.
    *
    * @since 2.6
    */
    IMPORT_C void ShowPictographsFirst();
    
    /**
    * Set the emotion mode for the special character table.
    *
    * @param aEmotionMode The emotion mode for the special character table 
    *      (EAknCharMapEmotionUse, EAknCharMapEmotionFirst, EAknCharMapEmotionNoUse).
    * * @since 9.2
    */
    IMPORT_C void SetEmotionMode(TAknCharMapEmotionMode aEmotionMode);

    /**
    * When the SCT is opened, it shows another width table.
    *
    * @param aCharCase another character case type
    * @since 2.6
    */
    IMPORT_C void ShowAnotherTable(TInt aCharCase);

    /**
    * From MCoeControlObserver
    *
    * @param aControl pointer to observed
    * @param aEventType event to be handled
    */
    IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

    /**
    * From MDialogPageObserver
    *
    * @param aEventID event to be handled
    */
    IMPORT_C void HandleDialogPageEventL(TInt aEventID);

    /**
    * Sets locking status for numeric keys. If this is called with ETrue,
    * then cursor can't be moved with numeric keys.
    *
    * @param aLockStatus  Numeric key lock status. ETrue disables numeric keys
    *                     cursor movement, EFalse enables it.
    */
    IMPORT_C void LockNumericKeys(TBool aLockStatus);

    /**
    * Hides the first row that shows recent characters.
    *
    * @since 3.2
    */
    IMPORT_C void DisableRecentCharsRow();

    /**
    * From CoeControl
    * @since 3.2
    * Handles pointer events
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private: // helpers
    void DoLayout();
private:
    /**
     * Change layout when pressing '*' key or EStdKeyLeftFunc(or EStdKeyRightFunc) key.
     */
    void SwitchTablesOrPagesL();
    TBool SwitchTablesL();
    void SwitchPagesL();
    void RefreshTitleAndNavi();

    void ChangeCategoryL(const TInt aCategory);
    void ChangeLayoutL(const TBool aLayoutChanged);
    void SetSoftKeyL(const TBool aDrawNow = EFalse);

private:
    TDes* iSpecialChars;
    TInt iCharCase;
    TInt iCharSetResourceId;
    TInt iWsBufferRequestId;
    CAknCharMapDialogExtension *iExtension;
    };

#endif  // AKNSCTDIALOG_H
