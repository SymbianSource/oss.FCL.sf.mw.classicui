/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Psln application base view class.
*
*/


#ifndef C_PSLNBASEVIEW_H
#define C_PSLNBASEVIEW_H

#include <aknview.h>
#include <eikclb.h>

#include "psln.hrh"
#include "PslnConst.h"

class CPslnBaseContainer;
class CPslnUi;
class CPslnModel;
class CAknNavigationDecorator;

/**
*  CPslnBaseView base view class.
*
*/
class CPslnBaseView : public CAknView, public MEikListBoxObserver
    {
    public: // Constructors and destructor

        /**
        * C++ default constructor
        */
        CPslnBaseView();

        /**
        * Destructor.
        */
        ~CPslnBaseView();

    protected:

        /**
        * From MEikListBoxObserver.
        * Handles listbox events.
        * @param aListBox Listbox where the event occurred.
        * @param aEventType Event type.
        */
        void HandleListBoxEventL( CEikListBox* aListBox,
            TListBoxEvent aEventType );

        /**
        * From CAknView.
        * Called when view is activated.
        * @param aPrevViewId previous view id.
        * @param aCustomMessageId custom message id.
        * @param aCustomMessage custom message content.
        */
        void DoActivateL(
            const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId,
            const TDesC8& aCustomMessage );

        /**
        * From CAknView.
        * Called when view is deactivated.
        */
        void DoDeactivate();

        /**
        * Creates container for this view.
        */
        virtual void CreateContainerL();

        /**
        * Creates a new container for this view.
        * Sub-class should implement this, as this is called by this
        * base class from DoActivateL.
        */
        virtual void NewContainerL() = 0;

        /**
        * Sets navi pane for the view.
        */
        virtual void SetNaviPaneL();

        /**
        * Called by HandleListBoxEventL.
        * Handles list box selections.
        */
        virtual void HandleListBoxSelectionL() = 0;

        /**
        * Adds given resource text as MSK to CBA.
        *
        * @param aResourceId middle softkey label.
        * @param aCommandId command that should be performed when MSK
        *        is pressed.
        * @since S60 v3.1
        */
        virtual void SetMiddleSoftKeyLabelL(
            const TInt aResourceId,
            const TInt aCommandId );

        /**
        * From MEikMenuObserver.
        * Changes MenuPane dynamically.
        */
        virtual void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

        /**
        * Sets title pane to a view.
        * @since 5.0
        */
        virtual void SetTitlePaneL( TInt& aResourceId ) = 0;
        
       /**
        *Get the resorce id for CBA, The derived view change the CBA resource by overriding
        *this function.
        * @since 5.0
        */
        virtual TInt CbaResourceId( const TVwsViewId& aPrevViewId,TUid aCustomMessageId );
        
    private:

        /* Remove container. */
        void RemoveContainer();

    protected: // Data

        /**
        * Container.
        * Not own.
        */
        CPslnBaseContainer* iContainer;

        /**
        * Application UI.
        * Not own.
        */
        CPslnUi* iPslnUi;

        /**
        * Model.
        * Not own.
        */
        CPslnModel* iModel;

        /**
        * Currently selected item.
        */
        TInt  iCurrentItem;

        /**
        * Navi pane.
        * Own.
        */
        CAknNavigationDecorator* iNaviPaneContext;
    };

#endif // C_PSLNBASEVIEW_H

// End of File
