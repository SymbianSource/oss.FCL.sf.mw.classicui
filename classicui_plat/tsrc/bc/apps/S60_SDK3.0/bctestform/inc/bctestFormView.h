/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         view of application
*
*/









#ifndef BCTESTFORMVIEW_H
#define BCTESTFORMVIEW_H

// INCLUDES
#include <aknview.h>
#include <eikdialg.h>
#include <aknform.h>

// CONSTANTS

// FORWARD DECLARATIONS
class CBCTestFormContainer;

// CLASS DECLARATION

/**
* CBCTestFormView view class.
*
*/
class CBCTestFormView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CBCTestFormView* NewL();

        /**
        * Destructor.
        */
        virtual ~CBCTestFormView();

    public: // New functions

        /**
        *
        * @param aIndex
        */
        void DisplayNextOutlineL();
        CBCTestFormContainer* Container() const;

    public: // From CAknView.

        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */
        TUid Id() const;

        /**
        * From CAknView, HandleCommandL.
        * handles the commands. if the command is command which is require to
        * display outline-screen, the command is reported to container class.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

    private: // New functions
    
    	/**
        * Default constructor.
        */
        CBCTestFormView();
        
        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        /**
        * Set title text to status-pane
        * @param aCommand
        */
        void IndicateTitlePaneTextL( TInt aCommand );

    private: // From CAknView

        /**
        * From CAknView, DoActivateL.
        * Creates the Container class object.
        * @param aPrevViewId aPrevViewId is not used.
        * @param aCustomMessageId aCustomMessageId is not used.
        * @param aCustomMessage aCustomMessage is not used.
        */
        void DoActivateL(
            const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId,
            const TDesC8& aCustomMessage );

        /**
        * From CAknView, DoDeactivate.
        * Deletes the Container class object.
        */
        void DoDeactivate();

        /**
        *        Utility methods
        */
        void SetupAPIOutlineL(TInt aCommand);
    private: // Data

        CBCTestFormContainer* iContainer;
        TInt iCurrentOutline;

    };

/**
* CBCTestFormTestAdd container control class.
*/
class CBCTestFormTestAdd : public CAknForm
    {
    public: // Constructor and Detructor
        /**
        * Default constructor.
        */
        CBCTestFormTestAdd();

        /**
        * Destructor.
        */
        virtual ~CBCTestFormTestAdd();

    protected:
        /**
        * From CAknForm,
        * Add item for testing uses customised dialog.
        */
        void AddItemL();

    private:
        // In order to prevent adding controls which ID is the same.
        TInt iNewItemId;
    };

#endif // BCTestFormVIEW_H

// End of File
