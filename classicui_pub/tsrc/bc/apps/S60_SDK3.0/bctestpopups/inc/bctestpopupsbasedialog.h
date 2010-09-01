/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares test bc for popups base dialog.
*
*/









#ifndef BCTESTPOPUPSBASEDIALOG_H
#define BCTESTPOPUPSBASEDIALOG_H

#include <aknform.h>

/**
 * CBCTestPopupsBaseDialog
 */
class CBCTestPopupsBaseDialog : public CAknForm
    {
    public: // Constructors and destructor

        /**
        * Destructor.
        */
        virtual ~CBCTestPopupsBaseDialog();
        
        /**
        * Constructor.
        */
        CBCTestPopupsBaseDialog();

    public: // From CAknDialog

        /**
        * From CAknDialog, DynInitMenuPaneL.
        * Dims "Label", "Add" and "Delete" menu items.
        * @param aResourceId 
        * @param aMenuPane Pointer to menu-pane object.
        */
        virtual void DynInitMenuPaneL( TInt aResourceId,
                                       CEikMenuPane* aMenuPane );

        /**
        * From CAknDialog, ProcessCommandL.
        * @param aResourceId
        */
        virtual void ProcessCommandL( TInt aCommandId );

	protected: // From CAknDialog

        /**
        * From CAknDialog, OkToExitL.
        * @param aButtonId 
        */
        virtual TBool OkToExitL( TInt aButtonId );

    private: // From CEikDialog

        /**
        * From CEikDialog, PreLayoutDynInitL.
        * Initialises the dialog's controls before the dialog is sized 
        * and layed out.
        */
        void PreLayoutDynInitL();

        /**
        * From CEikDialog, PostLayoutDynInitL.
        * Initialises the dialog's controls after the dialog has been sized
        * but before it has been activated.
        */
        void PostLayoutDynInitL();

    };

#endif  // BCTESTPOPUPSBASEDIALOG_H


