/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  View for compa mode settings.
*
*/


#ifndef AKNCOMPAGS_H
#define AKNCOMPAGS_H

#include <aknsettingpage.h>
#include <gsbaseview.h>
#include <ConeResLoader.h>
#include <gsplugininterface.h>


const TUid KAknCompaGSUid = { 0x2001114A };
_LIT( KAknCompaGSIconDirAndName, "z:avkon.mbm"); // Use KDC_BITMAP_DIR
_LIT( KAknCompaGSResourceFileName, "z:akncompagsrsc.rsc" );


class CAknViewAppUi;
class CAknCompaGSContainer;
class CAknCompaGSModel;


/**
*  CAknCompaGS view class for compa mode settings
*  Handles viewing of setting items.
*  @since Series 60_5.0
*
*/
class CAknCompaGS : public CGSBaseView
    {
    public: // Constructors and destructor

        /**
        * Symbian OS two-phased constructor
        * @return GS connection view.
        */
        static CAknCompaGS* NewL( TAny* aInitParams );

        /**
        * Destructor
        */
        ~CAknCompaGS();

    public: // From CGSPluginInterface

        /**
        * @see CGSPluginInterface header file.
        */
        void GetCaptionL( TDes& aCaption ) const;

        /**
        * See base class.
        */
        CGulIcon* CreateIconL( const TUid aIconType );

        /**
        * @see CGSPluginInterface header file.
        */
        TInt PluginProviderCategory() const;

        /**
        * @see CGSPluginInterface header file.
        */
        TBool Visible() const;

    public: // from base classes

        /**
        * Returns view id.
        * @return TUid
        */
        TUid Id() const;

        /**
        * Handles commands.
        * @param aCommand Command to be handled.
        *
        */
        void HandleCommandL( TInt aCommand );

    public: // new

        CAknCompaGSContainer* Container();

    protected: // From CAknView

        void DoActivateL( const TVwsViewId& aPrevViewId,
                          TUid aCustomMessageId,
                          const TDesC8& aCustomMessage );

    protected:

        /**
        * C++ default constructor.
        */
        CAknCompaGS();

        /**
        * Symbian OS default constructor.
        *
        */
        void ConstructL();

    private: // from CGSBaseView

        void NewContainerL();
        void HandleListBoxSelectionL();

    private:
        CAknCompaGSModel *iModel;
        TVwsViewId iPrevViewId;
        RConeResourceLoader iResourceLoader;

    };

#endif //AKNCOMPAGS_H

// End of File
