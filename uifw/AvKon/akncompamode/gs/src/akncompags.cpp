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
* Description:  View for compa mode settings
*
*/


#include "akncompags.h"
#include "akncompagsmodel.h"
#include "akncompagscontainer.h"
#include "akncompags.hrh"

#include <avkon.mbg> // icons
#include <akncompagsrsc.rsg>
#include <gsfwviewuids.h>
#include <gsprivatepluginproviderids.h>

#include <AknQueryDialog.h>
#include <aknradiobuttonsettingpage.h>
#include <aknViewAppUi.h>
#include <StringLoader.h>
#include <bautils.h>
#include <coeaui.h>
#include <eikfrlbd.h>
#include <ecom/implementationproxy.h>
#include <hlplch.h>             // For HlpLauncher

#include <gscommon.hrh>

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaGS::CAknCompaGS()
  : iResourceLoader( *iCoeEnv )
    {
    }

// --------------------------------------------------------------------------
// Create a compa-mode settings plugin
// --------------------------------------------------------------------------
CAknCompaGS* CAknCompaGS::NewL( TAny* /*aInitParams*/ )
    {
    CAknCompaGS* self = new( ELeave ) CAknCompaGS ();

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaGS::ConstructL()
    {
    TParse parse;
    parse.Set( KAknCompaGSResourceFileName,
               &KDC_RESOURCE_FILES_DIR, NULL );
    TFileName fileName( parse.FullName() );

    // Get language of resource file
    BaflUtils::NearestLanguageFile( iCoeEnv->FsSession(), fileName );

    // Open resource file
    iResourceLoader.OpenL( fileName );

    iModel = CAknCompaGSModel::NewL();

    BaseConstructL( R_AKNCOMPAGS_VIEW );
    }


// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaGS::~CAknCompaGS()
    {
    iResourceLoader.Close();
    delete iModel;
    }

// --------------------------------------------------------------------------
// Return plugin implementation ID
// --------------------------------------------------------------------------
TUid CAknCompaGS::Id() const
    {
    return KAknCompaGSUid;
    }

// --------------------------------------------------------------------------
// Get caption of the plugin (localized name of the view)
// --------------------------------------------------------------------------
void CAknCompaGS::GetCaptionL( TDes& aCaption ) const
    {
    // the resource file is already opened.
    HBufC* result = StringLoader::LoadL( R_AKNCOMPAGS_LIST_CAPTION );

    aCaption.Copy( *result );
    delete result;
    }

// --------------------------------------------------------------------------
// Return ID of plugin provider category
// --------------------------------------------------------------------------
TInt CAknCompaGS::PluginProviderCategory() const
    {
    // To identify as internal plug-in.
    return KGSPluginProviderInternal;
    }

// --------------------------------------------------------------------------
// Return if the plugin should be visible in the settings framework
// --------------------------------------------------------------------------
TBool CAknCompaGS::Visible() const
    {
    return iModel->FeatureEnabled();
    }


// --------------------------------------------------------------------------
// Handle command
// --------------------------------------------------------------------------
void CAknCompaGS::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EGSMSKCmdAppChange:
            HandleListBoxSelectionL();
            break;
        case EGSCmdAppChange:
            HandleListBoxSelectionL();
            break;
        case EAknSoftkeyBack:
            iAppUi->ActivateLocalViewL( iPrevViewId.iViewUid );
            break;
        case EAknCmdHelp:
            HlpLauncher::LaunchHelpApplicationL(
                iEikonEnv->WsSession(), iAppUi->AppHelpContextL() );
            break;
        default:
            iAppUi->HandleCommandL( aCommand );
            break;
        }
    }

// --------------------------------------------------------------------------
// Return container
// --------------------------------------------------------------------------
CAknCompaGSContainer* CAknCompaGS::Container()
    {
    return static_cast<CAknCompaGSContainer*>( iContainer );
    }


// --------------------------------------------------------------------------
// Create container
// --------------------------------------------------------------------------
void CAknCompaGS::NewContainerL()
    {
    iContainer = new( ELeave ) CAknCompaGSContainer;
    }

// --------------------------------------------------------------------------
// Activate view
// --------------------------------------------------------------------------
void CAknCompaGS::DoActivateL( const TVwsViewId& aPrevViewId,
                                     TUid aCustomMessageId,
                                     const TDesC8& aCustomMessage )
    {
    iPrevViewId = aPrevViewId;

    CGSBaseView::DoActivateL( aPrevViewId, aCustomMessageId, aCustomMessage );
    }

// --------------------------------------------------------------------------
// Handle list box selection
// --------------------------------------------------------------------------
void CAknCompaGS::HandleListBoxSelectionL()
    {
    const TInt currentFeatureId = Container()->CurrentFeatureId();

    switch ( currentFeatureId )
        {
        case KCompaGSIdState:
            {
            TBool newValue = !iModel->CompaAppState();
            iModel->SetCompaAppState(newValue);
            Container()->UpdateListBoxL( currentFeatureId, newValue );
            }
            break;
       default:
            break;
        }
    }

// --------------------------------------------------------------------------
// Create icon of desired type
// --------------------------------------------------------------------------
CGulIcon* CAknCompaGS::CreateIconL( const TUid aIconType )
    {
    CGulIcon* icon;
    TParse* fp = new( ELeave ) TParse();
    CleanupStack::PushL( fp );
    fp->Set( KAknCompaGSIconDirAndName, &KDC_BITMAP_DIR, NULL );

    if( aIconType == KGSIconTypeLbxItem )
        {
        icon = AknsUtils::CreateGulIconL(
        AknsUtils::SkinInstance(),
        KAknsIIDNone,
        fp->FullName(),
        EMbmAvkonQgn_prop_folder_apps_medium,
        EMbmAvkonQgn_prop_folder_apps_medium_mask );
        }
    else
        {
        icon = CGSPluginInterface::CreateIconL( aIconType );
        }

    CleanupStack::PopAndDestroy( fp );

    return icon;
    }

// --------------------------------------------------------------------------
// Return factory functions for ECOM interface implementations
// --------------------------------------------------------------------------
EXPORT_C const TImplementationProxy* ImplementationGroupProxy( 
    TInt& aTableCount )
    {
    static const TImplementationProxy KAknCompaGSImplementationTable[] = 
        {
        IMPLEMENTATION_PROXY_ENTRY( 0x2001114A, CAknCompaGS::NewL )
        };

    aTableCount = sizeof( KAknCompaGSImplementationTable ) 
        / sizeof( TImplementationProxy );
    return KAknCompaGSImplementationTable;
    }
