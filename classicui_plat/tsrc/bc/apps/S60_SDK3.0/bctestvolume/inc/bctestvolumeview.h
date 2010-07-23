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
* Description:         Declares view for application.
*
*/









#ifndef C_BCTESTVOLUMEVIEW_H
#define C_BCTESTVOLUMEVIEW_H

// INCLUDES
#include <aknview.h>

// CONSTANTS

// FORWARD DECLARATIONS
class CBCTestVolumeContainer;

// CLASS DECLARATION

/**
* CBCTestVolumeView view class.
*/
class CBCTestVolumeView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CBCTestVolumeView* NewL();
        
        /**
        * Destructor.
        */
        virtual ~CBCTestVolumeView();

    public: // New function

        /**
        * Requests to display next outline.
        */
        void DisplayNextOutlineL();

        /**
        * Getter of the container.
        */
        CBCTestVolumeContainer* Container() const;

    public: // From CAknView

        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */
        TUid Id() const;

        /**
        * From CAknView, HandleCommandL.
        * Handles the commands. If the command is command which is require to
        * display outline-screen, the command is reported to container class.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

        /**
        * From CAknView, HandleStatusPaneSizeChange.
        * Changes the rectangle of main pane.
        */

    private: // New functions
    
        /**
        * Default constructor.
        */
        CBCTestVolumeView();
        
        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();            

        /**
        * Sets title text to status-pane.
        * @param aCommand Command selected in menu.
        */
        void IndicateTitlePaneTextL( const TInt aCommand );

    private: // From CAknView

        /**
        * From AknView, DoActivateL.
        * Creates the Container class object.
        * @param aPrevViewId aPrevViewId is not used.
        * @param aCustomMessageId aCustomMessageId is not used.
        * @param aCustomMessage aCustomMessage is not used.
        */
        void DoActivateL(const TVwsViewId& aPrevViewId,
			 TUid aCustomMessageId,
			 const TDesC8& aCustomMessage );

        /**
        * From AknView, DoDeactivate.
        * Deletes the Container class object.
        */
        void DoDeactivate();

    private: // Data
        TInt iCurrentOutline;
        CBCTestVolumeContainer* iContainer; // own
    };

#endif  // C_BCTESTVOLUMEVIEW_H

// End of File
