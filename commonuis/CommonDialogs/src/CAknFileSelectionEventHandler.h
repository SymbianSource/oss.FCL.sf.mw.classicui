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
* Description:  The event handler to handle events of list box in dialog.
*
*/


#ifndef C_AKNFILESELECTIONEVENTHANDLER_H
#define C_AKNFILESELECTIONEVENTHANDLER_H

// INCLUDES
#include <cstack.h>
#include <f32file.h>

#include "MAknCommonDialogsEventObserver.h"
#include "CAknCommonDialogsBase.h"

// FORWARD DECLARATIONS
class MAknFileSelectionObserver;
class CAknFileSelectionModel;

// CLASS DEFINITION
/**
*  A class that handles events reported from an UI class in file selection.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
NONSHARABLE_CLASS(CAknFileSelectionEventHandler) : public CBase, public MAknCommonDialogsEventObserver
    {
    public:     // Constructors and destructors

        /**
        * Static constructor.
        * @param aCoeEnv A pointer to control environment.
        * @param aModel A pointer to file selection model.
        * @param aDialogType Type of the dialog.
        * @param aObserver A reference to a pointer to an observer which is
        *        asked if the selected item can be selected.
        * @param aLeftSoftkeyFile Left softkey text when a file is focused.
        * @param aLeftSoftkeyFolder Left softkey text when a folder is focused.
        * @param aRightSoftkeyRootFolder Right softkey text when user browses
        *        in the root folder.
        * @param aRightSoftkeySubfolder Right softkey text when user browses
        *        in a subdirectory.
        * @return Returns a pointer to an instance of itself.
        */
        static CAknFileSelectionEventHandler* NewL(
            CCoeEnv* aCoeEnv,
            CAknFileSelectionModel* aModel,
            const TCommonDialogType& aDialogType,
            MAknFileSelectionObserver*& aObserver,
            const HBufC*& aLeftSoftkeyFile,
            const HBufC*& aLeftSoftkeyFolder,
            const HBufC*& aRightSoftkeyRootFolder,
            const HBufC*& aRightSoftkeySubfolder );

        ~CAknFileSelectionEventHandler();

    public:     // New methods

        /**
        * Pushes listbox indices to stack.
        * @param aTopIndex Index of the topmost item in the listbox window.
        * @param aFocus Index of the item focused.
        */
        void PushIndicesL( TInt aTopIndex, TInt aFocus );

        /**
        * Pops listbox indexes from stack. Sets values to 0 if stack is empty.
        * @param aTopIndex Index of the topmost item in the listbox window.
        * @param aFocus Index of the item focused.
        */
        void PopIndices( TInt& aTopIndex, TInt& aFocus );

        /**
        * Resets current softkeys to EFirstTime.
        */
        void ResetSoftkeyStatus();

        /**
        * Updates softkey texts if they need to be changed.
        * @param aCurrentItemIndex Index of the currently selected item.
        * @param aContainer A pointer to a button group container to update buttons.
        */
        void UpdateSoftkeysL( TInt aCurrentItemIndex, CEikButtonGroupContainer* aContainer );

    public:     // Functions from base classes

        /**
        * From MAknCommonDialogsEventObserver
        */
        TAction HandleEventL(
            TEvent aEvent,
            TInt& aFocusedItemIndex,
            TInt& aTopItemIndex,
            CEikButtonGroupContainer* aContainer );

    private:    // Enumerations

        /**
        * Enumerations for softkey statuses.
        * If softkey status has changed the text must be redrawn.
        */
        enum TSoftkeyStatus
            {
            EFirstTime = -1,
            ESKNotVisible,
            ESKFileFocused,
            ESKFolderFocused,
            ESKInRootFolder,
            ESKInSubfolder
            };

        /**
        * A small container class.
        */
        class TFocusItem
            {
            public:
                inline TFocusItem( TInt aTopIndex, TInt aFocus );
                TInt iTopIndex; // Index of the first item in listbox view.
                TInt iFocus; // Index of the focused item.
            };

    private:    // Constructors and destructors

        void ConstructL();

        /**
        * Constructor.
        * @param aCoeEnv A pointer to control environment.
        * @param aModel A pointer to file selection model.
        * @param aDialogType Type of the dialog.
        * @param aObserver A reference to a pointer to an observer which is
        *        asked if the selected item can be selected.
        * @param aLeftSoftkeyFile Left softkey text when a file is focused.
        * @param aLeftSoftkeyFolder Left softkey text when a folder is focused.
        * @param aRightSoftkeyRootFolder Right softkey text when user browses
        *        in the root folder.
        * @param aRightSoftkeySubfolder Right softkey text when user browses
        *        in a subdirectory.
        */
        CAknFileSelectionEventHandler(
            CCoeEnv* aCoeEnv,
            CAknFileSelectionModel* aModel,
            const TCommonDialogType& aType,
            MAknFileSelectionObserver*& aObserver,
            const HBufC*& aLeftSoftkeyFile,
            const HBufC*& aLeftSoftkeyFolder,
            const HBufC*& aRightSoftkeyRootFolder,
            const HBufC*& aRightSoftkeySubfolder );

    private:    // Data

        // Own: Left softkey status
        TSoftkeyStatus iCurrentLeftSoftkey;

        // Own Right softkey status.
        TSoftkeyStatus iCurrentRightSoftkey;

        // Own: Stack for listbox focuses.
        CStack<TFocusItem, ETrue> iStack;

        // Ref: Pointer to control environment
        CCoeEnv* iCoeEnv;

        // Ref: Pointer to file selection engine
        CAknFileSelectionModel* iModel;

        TEntry  iEntry;

        // Ref: Dialog type
        const TCommonDialogType& iDialogType;

        // Ref: File selection observer
        MAknFileSelectionObserver*& iObserver;

        // Ref: Softkey text
        const HBufC*& iLeftSoftkeyFile;

        // Ref: Softkey text
        const HBufC*& iLeftSoftkeyFolder;

        // Ref: Softkey text
        const HBufC*& iRightSoftkeyRootFolder;

        // Ref: Softkey text
        const HBufC*& iRightSoftkeySubfolder;
    };


// Constructor for TFocusItem object

inline CAknFileSelectionEventHandler::TFocusItem::TFocusItem(
    TInt aTopIndex,
    TInt aFocus )
    :   iTopIndex( aTopIndex ),
        iFocus( aFocus )
    {
    }

#endif // C_AKNFILESELECTIONEVENTHANDLER_H
