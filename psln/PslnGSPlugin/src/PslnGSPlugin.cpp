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


// GS Framework and this plugin.
#include    "PslnGSPlugin.h"
#ifdef RD_CONTROL_PANEL
#include    <pslngsplugin.mbg>
#endif // RD_CONTROL_PANEL
#include    <gsparentplugin.h>
#include    <gscommon.hrh>
#include    <pslngspluginrsc.rsg>
#include    <gsprivatepluginproviderids.h>
#include    <gsfwviewuids.h>

// General services.
#include    <AknNullService.h>
#include    <bautils.h>
#include    <StringLoader.h>
#include    <AknsUtils.h>

// Themes application UID.
const TUid KPslnThemesAppUid = { 0x10005A32 };

// This application's resource file.
_LIT( KPslnGSPluginResourceFileName, "z:pslngspluginrsc.rsc" );

#ifdef RD_CONTROL_PANEL
    #ifdef __SCALABLE_ICONS
    // bitmap
    _LIT( KPslnGSPluginIconFileName, "\\resource\\apps\\pslngsplugin.mif");
    #else //__SCALABLE_ICONS
    // svg file
    _LIT( KPslnGSPluginIconFileName, "\\resource\\apps\\pslngsplugin.mbm");
    #endif //__SCALABLE_ICONS
#endif // RD_CONTROL_PANEL


// ========================= MEMBER FUNCTIONS ================================

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CPslnGSPlugin::CPslnGSPlugin() : iResources( *iCoeEnv ), iNullService( NULL )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CPslnGSPlugin::~CPslnGSPlugin()
    {
    iResources.Close();

    if ( iNullService )
        {
        delete iNullService;
        }
    }

// ---------------------------------------------------------------------------
// Symbian OS two-phased constructor
// ---------------------------------------------------------------------------
//
void CPslnGSPlugin::ConstructL()
    {
    BaseConstructL();

    OpenLocalizedResourceFileL( KPslnGSPluginResourceFileName, iResources );
    }

// ---------------------------------------------------------------------------
// Static constructor
// ---------------------------------------------------------------------------
//
CPslnGSPlugin* CPslnGSPlugin::NewL( TAny* /*aInitParams*/ )
    {
    CPslnGSPlugin* self = new( ELeave ) CPslnGSPlugin();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CPslnGSPlugin::Id
// -----------------------------------------------------------------------------
//
TUid CPslnGSPlugin::Id() const
    {
    return KPslnGSPluginUID;
    }

// -----------------------------------------------------------------------------
// CPslnGSPlugin::DoActivateL
// -----------------------------------------------------------------------------
//
void CPslnGSPlugin::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
                                  TUid /*aCustomMessageId*/,
                                  const TDesC8& /*aCustomMessage*/ )
    {
    }

// -----------------------------------------------------------------------------
// CPslnGSPlugin::DoDeactivate
// -----------------------------------------------------------------------------
//
void CPslnGSPlugin::DoDeactivate()
    {
    }

// ========================= From CGSPluginInterface ==================
// -----------------------------------------------------------------------------
// CPslnGSPlugin::GetCaptionL
// -----------------------------------------------------------------------------
//
void CPslnGSPlugin::GetCaptionL( TDes& aCaption ) const
    {
    HBufC* result = StringLoader::LoadL( R_PSLN_GS_PLUGIN_CAPTION );
    aCaption.Copy( *result );
    delete result;
    }

// -----------------------------------------------------------------------------
// CPslnGSPlugin::PluginProviderCategory
// -----------------------------------------------------------------------------
//
TInt CPslnGSPlugin::PluginProviderCategory() const
    {
    return KGSPluginProviderInternal;
    }

// -----------------------------------------------------------------------------
// CPslnGSPlugin::ItemType()
// -----------------------------------------------------------------------------
//
TGSListboxItemTypes CPslnGSPlugin::ItemType()
    {
    return EGSItemTypeSettingDialog;
    }

// -----------------------------------------------------------------------------
// CPslnGSPlugin::GetValue()
// -----------------------------------------------------------------------------
//
void CPslnGSPlugin::GetValue( const TGSPluginValueKeys /*aKey*/,
                                      TDes& /*aValue*/ )
    {
    }

// -----------------------------------------------------------------------------
// CPslnGSPlugin::HandleSelection()
// -----------------------------------------------------------------------------
//
void CPslnGSPlugin::HandleSelection(
    const TGSSelectionTypes /*aSelectionType*/ )
    {
    TRAP_IGNORE( LaunchThemesAppL() );
    }

// -----------------------------------------------------------------------------
// CPslnGSPlugin::CreateIconL()
// -----------------------------------------------------------------------------
//
CGulIcon* CPslnGSPlugin::CreateIconL( const TUid aIconType )
    {
    CGulIcon* icon;
#ifdef RD_CONTROL_PANEL
    if( aIconType == KGSIconTypeLbxItem )
        {
        icon = AknsUtils::CreateGulIconL(
            AknsUtils::SkinInstance(),
            KAknsIIDQgnPropCpPersoTheme,
            KPslnGSPluginIconFileName,
            EMbmPslngspluginQgn_prop_cp_perso_theme,
            EMbmPslngspluginQgn_prop_cp_perso_theme_mask );
        }
    else
        {
        icon = CGSPluginInterface::CreateIconL( aIconType );
        }
#else
    icon = CGSPluginInterface::CreateIconL( aIconType );
#endif // RD_CONTROL_PANEL
    return icon;
    }

// -----------------------------------------------------------------------------
// CPslnGSPlugin::OpenLocalizedResourceFileL()
// -----------------------------------------------------------------------------
//
void CPslnGSPlugin::OpenLocalizedResourceFileL(
    const TDesC& aResourceFileName,
    RConeResourceLoader& aResourceLoader )
    {
    // Find the resource file:
    TParse* parse = new (ELeave) TParse;
    CleanupStack::PushL( parse );
    parse->Set( aResourceFileName, &KDC_RESOURCE_FILES_DIR, NULL );
    TFileName* fileName = new (ELeave) TFileName( parse->FullName() );
    CleanupStack::PushL( fileName );

    // Open resource file:
    aResourceLoader.OpenL( *fileName );
    CleanupStack::PopAndDestroy( 2, parse ); // fileName, parse
    }

// -----------------------------------------------------------------------------
// CPslnGSPlugin::LaunchThemesAppL()
// -----------------------------------------------------------------------------
//
void CPslnGSPlugin::LaunchThemesAppL()
    {
    // Get the correct application data
    RWsSession ws;
    User::LeaveIfError( ws.Connect() );
    CleanupClosePushL( ws );

    // Find the task with uid
    TApaTaskList taskList(ws);
    TApaTask task = taskList.FindApp( KPslnThemesAppUid );

    if ( task.Exists() )
        {
        task.BringToForeground();
        }
    else
        {
        // Launch themes application as embedded.
        if ( iNullService )
            {
            delete iNullService;
            iNullService = NULL;
            }
        iNullService = CAknNullService::NewL( KPslnThemesAppUid, this );
        }
    CleanupStack::PopAndDestroy();  // ws
    }

// End of file
