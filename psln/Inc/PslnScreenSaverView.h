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
* Description:  Provides Psln Application Screensaver view.
*
*/



#ifndef CPSLNSCREENSAVERVIEW_H
#define CPSLNSCREENSAVERVIEW_H

//  INCLUDES
#include "PslnPropertySubscriber.h"

// Base classes
#include "PslnBaseView.h"
#include "mpslnscreensaverecomobserver.h"
#include <mpslnfwmsklabelobserver.h>
#include <cenrepnotifyhandler.h>

#include <psmclient.h>
#include <psmclientobserver.h>

class CAknWaitDialog;

/**
*  CPslnBaseView view class.
*  Provides Psln Application Screensaver view.
*
*  @since S60 v3.1
*/
class CPslnScreenSaverView : public CPslnBaseView,
                             public MPslnScreenSaverECOMObserver,
                             public MPslnFWMSKObserver,
                             public MCenRepNotifyHandlerCallback,
                             public MPsmClientObserver
    {
    public:

        /**
        * Two-phased constructor.
        */
        static CPslnScreenSaverView* NewLC();

        /**
        * Destructor.
        */
        virtual ~CPslnScreenSaverView();

        /**
        * From CAknView.
        * Returns view id.
        * @return An unsigned integer (view id).
        */
        TUid Id() const;

        /**
        * From MEikCommandObserver .
        * Handles commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

        /**
        * From MPslnScreenSaverECOMObserver.
        * Called when there is a change in ECOM plugins.
        */
        void HandlePluginListChangeL();

        /**
        * From MPslnFWMSKObserver.
        * Checks if the MSK label needs to be adjusted.
        */
        void CheckMiddleSoftkeyLabelL();

        /**
        * From MPsmClientObserver.
        * Notify when the power save mode is changed.
        */
        void PowerSaveModeChanged( const TPsmsrvMode aMode );

        /**
        * From MPsmClientObserver.
        * Notify when some wrong with the power save mode change.
        */
        void PowerSaveModeChangeError( const TInt aError );
        
    private:

        /**
        * Callback for exiting Screensaver preview mode.
        * @param aPtr pointer to get reference to self.
        * @return error code.
        */
        static TInt HandlePreviewModeChanged( TAny* aPtr );

        /**
        * Callback for changes in Screensaver preview state.
        * @param aPtr pointer to get reference to self.
        * @return error code.
        */
        static TInt HandlePreviewStateChanged( TAny* aPtr );

        /**
        * From CAknView.
        * Called when view is about to activate.
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
        * From MEikMenuObserver.
        * Changes MenuPane dynamically.
        */
        void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

        /**
        * From MProgressDialogCallback.
        * Called when wait note is removed.
        */
        void DialogDismissedL( TInt aButtonId );

        /**
        * From CPslnBaseView.
        * Handles listbox selection.
        */
        void HandleListBoxSelectionL();
              
        /**
        * From CPslnBaseView.
        */
        void HandleListBoxItemHighlightL();

        /**
        * From CPslnBaseView.
        * Creates new container.
        */
        void NewContainerL();

        /**
        * From CPslnBaseView.
        */
        void SetTitlePaneL( TInt& aResourceId );

        /* From MCenRepNotifyHandlerCallback. */
        void HandleNotifyInt( TUint32 aId, TInt /*aNewValue*/ );

        /* From MCenRepNotifyHandlerCallback. */
        void HandleNotifyGeneric( TUint32 aId );

        /* From MCenRepNotifyHandlerCallback. */
        void HandleNotifyError(
            TUint32 aId,
            TInt aError,
            CCenRepNotifyHandler* aHandler );

        /**
        * Handles screensaver activation command.
        */
        void HandleScreenSaverActivationL( TInt aCurrentItem );

        /**
        * Handles screensaver preview command.
        */
        void HandleScreenSaverPreviewL( TInt aCurrentItem );

        /**
        * Handles screensaver settings command.
        */
        void HandleScreenSaverSettingsL( TInt aCurrentItem );

        /**
        * Launches opening note.
        */
        void LaunchNote();

        /**
        * Same as above, but might leave.
        */
        void LaunchNoteL();

        /**
        * Removes opening note and stops listening for screensaver preview
        * state changes.
        */
        void RemoveNote();

        /**
        * Same as above, but might leave.
        */
        void RemoveNoteL();

        /**
        * Checks if screensaver function can be called, and if so makes
        * the call through PslnEngine.
        */
        void DoInvokeScreenSaverFunctionL(
            const TInt aCurrentItem,
            const TScPluginCaps aType );

        /**
        * Creates preview mode subscriber.
        */
		void CreatePreviewModeSubscriberL();

        /**
        * Creates preview state subscriber.
        */
        void CreatePreviewStateSubscriberL();

        /**
        * Remove command and label from MSK.
        */
        void RemoveCommandFromMSK();

        /**
        * Is 'Change' command visible.
        */
        TBool IsChangeCommandVisibleL() const;

        /**
        * Is 'Apply' command visible.
        */
        TBool IsApplyCommandVisibleL() const;
        
        /**
        * C++ default constructor.
        */
        CPslnScreenSaverView();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private:

        /**
        * Publish & Subscribe item for setting Preview mode.
        */
        RProperty iPreviewModeProperty;

        /**
        * Publish & Subscribe item for setting Preview state.
        */
        RProperty iPreviewStateProperty;

        /**
        * Publish & Subscribe listener for Preview mode.
        * Own.
        */
        CPslnPropertySubscriber* iPreviewModeSubscriber;

        /**
        * Publish & Subscribe listener for Preview state.
        * Own.
        */
        CPslnPropertySubscriber* iPreviewStateSubscriber;

        /**
        * Wait note wrapper.
        * Own.
        */
        CAknWaitDialog* iWaitDlg;

        /**
        * Index of plugin screensaver that is previewed.
        */
        TInt iScreenSaverPreviewIndex;

        /**
        * Repository for active screensaver.
        * Own.
        */
        CRepository* iScreenSaverRepository;

        /**
        * Notifier for changes in the screensaver repository.
        * Own.
        */
        CCenRepNotifyHandler* iScreenSaverNotifier;
        CPsmClient *iPsmClient;

    };

#endif      // CPSLNSCREENSAVERVIEW_H

// End of File
