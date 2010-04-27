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
* Description:  View class for general themes.
*
*/



#ifndef C_PSLNGENERALTHEMEVIEW_H
#define C_PSLNGENERALTHEMEVIEW_H

#include "PslnBaseView.h"
#include <mpslnfwmsklabelobserver.h>
#include "PslnGeneralThemeContainer.h"
#include <ConeResLoader.h>

/**
*  View class for general themes.
*
*  @since S60 v3.1
*/
class CPslnGeneralThemeView : public CPslnBaseView, 
                              public MPslnFWMSKObserver
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        * @return new instance of CPslnGeneralThemeView.
        */
        static CPslnGeneralThemeView* NewLC();

        /**
        * Destructor.
        */
        virtual ~CPslnGeneralThemeView();

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
        * Requests container to update skin data.
        * @param aCurrentIndex Current item index. If -1, remain old index.
        */
        void UpdateSkinListItemsL( TInt aCurrentIndex = KErrNotFound );

        /**
        * hightlight default skin.
        */
        void HightlightDefaultSkin();
        
        /**
        * From MPslnFWMSKObserver.
        * Checks if the MSK label needs to be adjusted.
        */
        void CheckMiddleSoftkeyLabelL();
        
        /**
        * Requests container to update skin data.
        */
        void UpdateSkinListItemsDColumnOnlyL();

    private:

        /**
        * From CAknView.
        */
        void DoActivateL(
            const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId,
            const TDesC8& aCustomMessage );

        /**
        * From CAknView.
        */
        void DoDeactivate();

        /**
        * From MEikMenuObserver.
        * Changes MenuPane dynamically.
        */
        void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

        /**
        * From CPslnBaseView.
        */
        void HandleListBoxSelectionL();

        /**
        * From CPslnBaseView.
        */
        void NewContainerL();

        /**
        * From CPslnBaseView.
        */
        void SetTitlePaneL( TInt& aResourceId );

        /* Remove command and label from MSK */
        void RemoveCommandFromMSK();

        /**
        * C++ default constructor.
        */
        CPslnGeneralThemeView();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();
        
        
    private:    // Data

    /**
    * Resource loader for common psln resources.
    */
    RConeResourceLoader iResourceLoaderCommon;

    /**
    * Download item index.
    */
    TInt iDownloadItemIndex;

    /**
    * Index to be used when skin is activated AFTER skin preview.
    * This is needed due to that user might highlight some other skin
    * after having selected previous skin for activation.
    */
    TInt iToBeActivatedSkinIndex;

    };

#endif      // C_PSLNGENERALTHEMEVIEW_H

// End of File
