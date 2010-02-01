/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Main state view for Psln application.
*
*/


#ifndef CPSLNMAINVIEW_H
#define CPSLNMAINVIEW_H

//  INCLUDES
#include "PslnBaseView.h"

// FORWARD DECLARATIONS
class CPslnFWPluginHandler;
class CPslnFWPluginInterface;

// CLASS DECLARATION

/**
*  Main state view for Psln application.
*  This view contains folders for other views.
*
*  @since S60 v3.1
*/
class CPslnMainView : public CPslnBaseView
    {
    public:

        /**
        * Two-phased constructor.
        * @return new instance of CPslnMainView.
        */
        static CPslnMainView* NewLC();

        /**
        * Destructor.
        */
        virtual ~CPslnMainView();

        /**
        * From CAknView.
        * Returns view id.
        * @return An unsigned integer (view id).
        */
        TUid Id() const;

        /**
        * From MEikCommandObserver.
        * Handles commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

        /**
        * Returns active view index.
        * @return active view index.
        */
        TInt ActiveView() const;

        /**
        * Sets active folder.
        * @param aIndex new active folder index.
        */
        void SetActiveFolder( TInt aIndex );

        /**
        * Returns Uid of currently selected folder.
        * @return Uid of currently selected folder.
        */
        TInt ActiveFolderUid();

        /**
        * Sets active folder.
        * @param aUid new active folder uid.
        */
        void SetActiveFolder( TUid aUid );

    private:

        /**
        * From CAknView.
        */
        void DoActivateL(
            const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId,
            const TDesC8& aCustomMessage );

        /**
        * From MEikMenuObserver.
        * Changes MenuPane dynamically
        */
        void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

        /**
        * From CPslnBaseView.
        */
        void HandleListBoxSelectionL();
        
        /**
        * From CPslnBaseView.
        */
        void HandleListBoxItemHighlightL();

        /**
        * From CPslnBaseView.
        */
        void NewContainerL();

        /**
        * From CPslnBaseView.
        * Empty implementation of virtual method.
        */
        void SetTitlePaneL( TInt& /*aResourceId*/ ) {};

        /**
        * From CPslnBaseView.
        */
        void ConstructViewArrayL();
    
        /**
        * From CPslnBaseView
        */
        TInt CbaResourceId( const TVwsViewId& aPrevViewId,TUid aCustomMessageId );
        
        /**
        * C++ default constructor.
        */
        CPslnMainView();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        /* Tries to launch local view from UI class. */
        void DoActivateLocalViewL();
        
        /**
        * Locate the specific view's position in list via view id.
        * @param aViewId The specific view's id
        * @return Specific view's postion in list
        */
        TInt GetListboxItemIndexByViewId(const TVwsViewId& aViewId) const;
    
    private:    // Data

        // View id's for Psln views.
        RArray<TUid> iViewIds;

    };

#endif      // CPSLNMAINVIEW_H

// End of File
