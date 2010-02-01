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
* Description:  Wallpaper view.
*
*/



#ifndef CPSLNWALLPAPERVIEW_H
#define CPSLNWALLPAPERVIEW_H

//  INCLUDES
#include "PslnBaseView.h"
#include <cenrepnotifyhandler.h>
#include <mpslnfwmsklabelobserver.h>

class CRepository;

// CLASS DECLARATION

/**
*  Wallpaper view within personalization application.
*  Possible to define current Idle background image.
*
*  @since S60 v3.1
*/
class CPslnWallpaperView : public CPslnBaseView,
                           public MCenRepNotifyHandlerCallback,
                           public MPslnFWMSKObserver
    {
    public:

        /**
        * Two-phased constructor.
        * @return new instance of CPslnWallpaperView.
        */
        static CPslnWallpaperView* NewLC();

        /**
        * Destructor.
        */
        virtual ~CPslnWallpaperView();

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
        * From MPslnFWMSKObserver.
        * Checks if the MSK label needs to be adjusted.
        */
        void CheckMiddleSoftkeyLabelL();

    private:

        /* From MCenRepNotifyHandlerCallback. */
        void HandleNotifyInt( TUint32 aId, TInt aNewValue );

        /* From MCenRepNotifyHandlerCallback. */
        void HandleNotifyGeneric( TUint32 aId );

        /* From MCenRepNotifyHandlerCallback. */
        void HandleNotifyError(
            TUint32 aId,
            TInt aError,
            CCenRepNotifyHandler* aHandler );

        /* From CAknView. */
        void DoActivateL(
            const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId,
            const TDesC8& aCustomMessage );

        /**
        * From MEikMenuObserver.
        * Changes MenuPane dynamically.
        */
        void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

        /* From CPslnBaseView. */
        void HandleListBoxSelectionL();
        
        /**
        * From CPslnBaseView.
        */
        void HandleListBoxItemHighlightL();        

        /* From CPslnBaseView. */
        void NewContainerL();

        /* From CPslnBaseView. */
        void SetTitlePaneL( TInt& aResourceId );
        
        /* From CPslnBaseView. */
        TInt CbaResourceId( const TVwsViewId& aPrevViewId,TUid aCustomMessageId );
        
        /**
        * C++ default constructor.
        */
        CPslnWallpaperView();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        /* Shows MGFetch query */
        TBool ShowBackgroundImageListL();

        /* Request container to update itself. */
        void UpdateContainer();

        /* Remove command and label from MSK */
        void RemoveCommandFromMSK();

        /* Updates current item. */
        TInt UpdateCurrentItem();

    private: // data

        /**
        * Personalization repository that contains wallpaper image path.
        * Own.
        */
        CRepository* iWallpaperRepository;

        /**
        * Notifier for changes in the above repository.
        * Own.
        */
        CCenRepNotifyHandler* iWallpaperNotifier;

        // Currently active wallpaper type.
        TInt iActiveWallpaper;
        
        /**
        * Ture if Wallpaper Setting Dialog is Running.
        */
        TBool iWpDlgRunnig;
    };

#endif      // CPSLNWALLPAPERVIEW_H

// End of File
