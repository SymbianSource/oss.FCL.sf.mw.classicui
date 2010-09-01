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
* Description:  PslnGSPlugin implementation.
*
*/

#ifndef C_PSLNGSPLUGIN_H
#define C_PSLNGSPLUGIN_H

#include <gsplugininterface.h>
#include <aknview.h>
#include <ConeResLoader.h>
#include <eikclb.h>
#include <AknServerApp.h>

class CAknNavigationDecorator;
class CAknViewAppUi;
class CAknNullService;

// This plugin's UID.
const TUid KPslnGSPluginUID = { 0x102818ED };

// CLASS DECLARATION

/**
* CPslnGSPlugin.
*
*
*
*/
class CPslnGSPlugin : public CGSPluginInterface,
                      public MAknServerAppExitObserver
    {
    public:

        /**
        * Symbian OS two-phased constructor
        * @param aInitParams initialization parameters.
        * @return new instance of CPslnGSPlugin.
        */
        static CPslnGSPlugin* NewL( TAny* aInitParams );

        /**
        * Destructor.
        */
        ~CPslnGSPlugin();

        /**
        * From CAknView.
        * This view's Id.
        * @return This plugin's UID.
        */
        TUid Id() const;

        /**
        * From CGSPluginInterface.
        * @param aCaption this plugin's caption.
        */
        void GetCaptionL( TDes& aCaption ) const;

        /**
        * From CGSPluginInterface.
        * @return this plugin's provider category.
        */
        TInt PluginProviderCategory() const;

        /**
        * From CGSPluginInterface.
        * @return this plugin's item type.
        */
        TGSListboxItemTypes ItemType();

        /**
        * From CGSPluginInterface.
        * @param aKey key name.
        * @param aValue key value.
        */
        void GetValue( const TGSPluginValueKeys aKey,
                       TDes& aValue );

        /**
        * From CGSPluginInterface.
        * @param aSelectionType selection type.
        */
        void HandleSelection( const TGSSelectionTypes aSelectionType );

        /**
        * From CGSPluginInterface.
        * @param aIconType UID Icon type UID of the icon to be created.
        * @return Pointer of the icon. NOTE: Ownership of this icon is
        *         transferred to the caller.
        */
        CGulIcon* CreateIconL( const TUid aIconType );

    private:

        /**
        * C++ default constructor.
        */
        CPslnGSPlugin();

        /**
        * Symbian OS default constructor.
        */
        void ConstructL();

        /**
        * From CAknView.
        * This implementation is empty because this class, being just a dialog,
        * does not implement the CAknView finctionality.
        */
        void DoActivateL( const TVwsViewId& aPrevViewId,
                          TUid aCustomMessageId,
                          const TDesC8& aCustomMessage );

        /**
        * From CAknView.
        * This implementation is empty because this class, being just a dialog,
        * does not implement the CAknView finctionality.
        */
        void DoDeactivate();

        /**
        * Opens localized resource file.
        */
        void OpenLocalizedResourceFileL(
            const TDesC& aResourceFileName,
            RConeResourceLoader& aResourceLoader );

        /**
        * Launches provisioning application.
        */
        void LaunchThemesAppL();

    private: // Data

        /**
        * Resource loader for this plugin's resources.
        */
        RConeResourceLoader iResources;

        /**
        * AVKON NULL Service.
        * Own.
        */
        CAknNullService* iNullService;
    };

#endif // C_PSLNGSPLUGIN_H
// End of File
