/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/


// INCLUDE FILES
#include <eikmenup.h> // for CEikMenuPane
#include <bautils.h> // BaflUtils
#include <eikenv.h> // CEikonEnv
#include "finditemmenu.h"
#include <finditemengine.h>
#include "finditemdialogpanic.h"
#include <finditemmenu.rsg>
#include <ConeResLoader.h>

#include <ItemFinder.h>

#include <commonphoneparser.h> // Phonenumber parser

#include <apgcli.h> // RApaLsSession for WMLBrowser launch
#include <apgtask.h>

#ifndef RD_VIRTUAL_PHONEBOOK
#include <CPbkContactEngine.h> // Phonebook Engine
#include <RPbkViewResourceFile.h> // Phonebook view dll resource loader
#include <cpbkdatasaveappui.h> // for PbkDataSaveAppUi
#include <CPbkFieldsInfo.h> // Phonebook field types
#else // RD_VIRTUAL_PHONEBOOK
#include <AiwServiceHandler.h> // CAiwServiceHandler
#include <AiwContactAssignDataTypes.h> // AiwContactAssign
#endif // !RD_VIRTUAL_PHONEBOOK

#include "finditem.hrh"
#include <FindItemui.rsg>
#include <aknnotewrappers.h>

#include <featmgr.h>

#include <centralrepository.h>
#include <CommonUiInternalCRKeys.h>

#include <AiwCommon.hrh>

// Callback query
#include <aknlists.h>
#include <aknPopup.h>
#include <StringLoader.h>

#include "FindItemVoIPExtension.h"

#include "FindItemMenuWrapper.h"
#include <akncontext.h> // AknContextPane

#include <baclipb.h> // CClipboard

#include "commonuimpengineapiloader.h"

// LOCAL CONSTANTS AND MACROS

// Resource files
_LIT( KResFileName, "z:\\resource\\finditemmenu.rsc" );
_LIT( KDialogResourceName, "z:\\resource\\finditemui.rsc" );
_LIT( KCommonUiMPEngineApiLoaderName, "z:\\sys\\bin\\commonuimpengineapiloader.dll" );

enum  TFindUIAddCNList  //handling popup indeces, update there if order of
                        // query items changes
    {
    EFindUISenderNumber = 0,
    EFindUICallbackNumber = 1
    };


_LIT( KRtspUrlAddress, "rtsp://" );

const TInt KMaxMenuTextLength = 40;

// Maximum length of Browser bookmark
const TInt KMaxBookmarkNameLength = 50;

// Entry point for dynamically loaded dlls.
const TInt KMPEngineApiDllEntryPoint = 1;

// TYPE DEFINITIONS
typedef TAny* (*MPEngineApiL)();


// ============================= MEMBER FUNCTIONS ==============================
// -----------------------------------------------------------------------------
// CFindItemMenu::CFindItemMenu
//  C++ default constructor.
// -----------------------------------------------------------------------------
//
CFindItemMenu::CFindItemMenu() :
    iCoeEnv( CCoeEnv::Static() ),
    iResLoader( *iCoeEnv ),
    iSenderDescType( CItemFinder::EPhoneNumber ),
    iSenderHighlighted( EFalse )
#ifdef RD_VOIP_REL_2_2
    ,iMenuItemFlags( NULL ) // all menu items allowed
#endif // RD_VOIP_REL_2_2
    {
    }

// -----------------------------------------------------------------------------
// CFindItemMenu::ConstructL
//  Second-phase constructor
// -----------------------------------------------------------------------------
//
void CFindItemMenu::ConstructL( const TInt aCommandId )
    {
    iFindItemCommandId = aCommandId;
    iFindItemMenuItemAdded = EFalse;

    iDialData = CAiwDialDataExt::NewL();

    iMMSFeatureSupported =
        FeatureManager::FeatureSupported( KFeatureIdMMS );

    iFindItemVoIPExtension = CFindItemVoIPExtension::NewL();

    iAudioMessagingFeatureSupported =
        FeatureManager::FeatureSupported( KFeatureIdAudioMessaging );

    iEmailOverSmsFeatureSupported =
        FeatureManager::FeatureSupported( KFeatureIdEmailOverSms );

    iEmailUiFeatureSupported =
        FeatureManager::FeatureSupported( KFeatureIdEmailUi );

    LoadResourceFileL();
    }

// -----------------------------------------------------------------------------
// CFindItemMenu::NewL
//  Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CFindItemMenu* CFindItemMenu::NewL( const TInt aCommandId )
    {
    CFindItemMenu* self = CFindItemMenu::NewLC( aCommandId );
    CleanupStack::Pop();
    return self;
    }

// -----------------------------------------------------------------------------
// CFindItemMenu::NewLC
//  Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CFindItemMenu* CFindItemMenu::NewLC( const TInt aCommandId )
    {

    CFindItemMenu* self = new (ELeave) CFindItemMenu;
    CleanupStack::PushL( self );
    self->ConstructL( aCommandId );
    return self;
    }

// -----------------------------------------------------------------------------
// CFindItemMenu::~CFindItemMenu
//  Default destructor
// -----------------------------------------------------------------------------
//
CFindItemMenu::~CFindItemMenu()
    {
    delete iMPEngineApi;
    if( iMPEngineDllLoaded )
        {
        iMPEngineDll.Close();
        }

    // Unload the resourcefile
    iResLoader.Close();
    delete iFindItemMenuItemString;
    delete iFindItemUrlItemString;
    delete iFindItemMailItemString;
    delete iFindItemPhoneItemString;

    delete iFindItemVoIPExtension;

    if ( FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
        {
        delete iFindItemTelInternetItemString;
        }

#ifndef RD_VIRTUAL_PHONEBOOK
    delete iPbkEngine;
    delete iPbkDataSave;
    if ( iRPbkResourceFile )
        {
        iRPbkResourceFile->Close();
        }
    delete iRPbkResourceFile;
#endif // !RD_VIRTUAL_PHONEBOOK
    
    delete iSenderDescriptor;

    delete iServiceHandler;

    delete iCommonUiRepositoryWatcher;
    delete iCommonUiRepository;


    delete iCallbackNumber;

    delete iDialData;

    delete iSenderDisplayText;
    }

// -----------------------------------------------------------------------------
// CFindItemMenu::LoadResourceFileL
//  Loads the resource for menuitems
// -----------------------------------------------------------------------------
//
void CFindItemMenu::LoadResourceFileL()
    {
    TFileName fileName( KResFileName );
    iResLoader.OpenL( fileName );

    // Read menu item's names from resource r_finditemmenu_menu_item
    iFindItemMenuItemString =
            iCoeEnv->AllocReadResourceL( R_FINDITEMMENU_MENU_ITEM );
    iFindItemUrlItemString =
            iCoeEnv->AllocReadResourceL( R_FINDITEMMENU_URL_ITEM );
    iFindItemMailItemString =
            iCoeEnv->AllocReadResourceL( R_FINDITEMMENU_MAIL_ITEM );
    iFindItemPhoneItemString =
            iCoeEnv->AllocReadResourceL( R_FINDITEMMENU_PHONE_ITEM );
    if ( FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
        {
        iFindItemTelInternetItemString =
            iCoeEnv->AllocReadResourceL( R_FINDITEMMENU_TELINTERNET_ITEM );
        }
   }

// -----------------------------------------------------------------------------
// CFindItemMenu::CommandIsValidL
//  Allows the application's HandleCommandL() method to switch appropriately
//  on menuselections
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CFindItemMenu::CommandIsValidL( const TInt aCommandId ) const
    {
    if ( (iFindItemMenuItemAdded && ( aCommandId > iFindItemCommandId &&
          aCommandId <= (iFindItemCommandId + (iFindItemVoIPExtension->IsVoIPSupported()?4:3)))) // traditional find
         ||
        (!iFindItemMenuItemAdded &&
        // normal autofind command. Let call ui to handle the VoIP profile
        // count.
        ( ( aCommandId >= EFindItemCmdCall &&
            aCommandId <= EFindItemCmdSendAudio ) ||
        // or autofind AIW command
        ( iServiceHandler &&
        ( iServiceHandler->ServiceCmdByMenuCmd( aCommandId ) == KAiwCmdCall ||
        iServiceHandler->ServiceCmdByMenuCmd( aCommandId ) ==
             KAiwCmdAssign ) ) ) ) )
        {
        return ETrue;
        }
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CFindItemMenu::DisplayFindItemMenuItemL
//
//  Inserts the FindItem menu item into menupane
// -----------------------------------------------------------------------------
//
EXPORT_C void CFindItemMenu::DisplayFindItemMenuItemL(
    CEikMenuPane& aMenuPane,
    const TInt aIndex )
    {
    // Call this from DynInitMenuPaneL to add a find item menu item to your menu
    AddMenuItemL(
        aMenuPane,
        iFindItemCommandId,
        aIndex,
        R_FINDITEMMENU_MENU,
        *iFindItemMenuItemString );

    iFindItemMenuItemAdded = ETrue;
    }

// -----------------------------------------------------------------------------
// CFindItemMenu::DisplayFindItemCascadeMenuL
//  Displays the FindItem cascade menu
// -----------------------------------------------------------------------------
//
EXPORT_C void CFindItemMenu::DisplayFindItemCascadeMenuL(
    CEikMenuPane& aMenuPane ) const
    {
    // Call this from DynInitMenuPaneL to add a find item's cascading menu
    // items to your menu
    if ( iFindItemMenuItemAdded )
        {
        AddMenuItemL(
            aMenuPane,
            iFindItemCommandId + 1,
            0,
            0,
            *iFindItemPhoneItemString );

        if ( iFindItemVoIPExtension->IsVoIPSupported() )
            {
            AddMenuItemL(
                aMenuPane,
                iFindItemCommandId + 4,
                0,
                0,
                *iFindItemTelInternetItemString );
            }

        if ( iEmailUiFeatureSupported )
            {
            AddMenuItemL(
                aMenuPane,
                iFindItemCommandId + 2,
                0,
                0,
                *iFindItemMailItemString );
            }

        AddMenuItemL(
            aMenuPane,
            iFindItemCommandId + 3,
            0,
            0,
            *iFindItemUrlItemString );
        }
    }

// -----------------------------------------------------------------------------
// AddMenuItemL
//  Adds the menu item to menupane
// -----------------------------------------------------------------------------
//
void CFindItemMenu::AddMenuItemL(
    CEikMenuPane& aMenuPane,
    TInt aCommandId,
    TInt aIndex,
    TInt aCascadeId,
    const TDesC& aText ) const
    {
    CEikMenuPaneItem::SData data;
    data.iCascadeId = aCascadeId;
    data.iFlags = 0;
    data.iText = aText;
    data.iCommandId = aCommandId;
    if ( aIndex == 0 )
        {
        aMenuPane.AddMenuItemL( data );
        }
    else
        {
        aMenuPane.AddMenuItemL( data, aIndex );
        }
    }

// -----------------------------------------------------------------------------
// CFindItemEngine::TFindItemSearchCase CFindItemMenu::SearchCase
//  Gives a search case for a command id
//  Use the return value when creating a CFindItemDialog.
// -----------------------------------------------------------------------------
//
EXPORT_C CFindItemEngine::TFindItemSearchCase CFindItemMenu::SearchCase(
    const TInt aCommandId ) const
    {
    switch ( aCommandId - iFindItemCommandId )
        {
        case 1:
            return CFindItemEngine::EFindItemSearchPhoneNumberBin;
        case 2:
            return CFindItemEngine::EFindItemSearchMailAddressBin;
        case 3:
            return CFindItemEngine::EFindItemSearchURLBin;
        case 4:
            return static_cast<CFindItemEngine::TFindItemSearchCase>
                ( CFindItemEngine::EFindItemSearchPhoneNumberBin |
                CFindItemEngine::EFindItemSearchMailAddressBin );
        default:
            __ASSERT_DEBUG( 0, Panic( ENoSearchCase ) );
            return CFindItemEngine::EFindItemSearchPhoneNumberBin;
        }
    }

EXPORT_C void CFindItemMenu::AddItemFindMenuL(
    CItemFinder* aItemFinder,
    CEikMenuPane* aMenuPane,
    TInt aIndex,
    const TDesC& aSenderDescriptor,
    TBool aKnownSender,
    TBool aIsContextMenu )
    {
    // create items
    iIsSenderKnown = aKnownSender;
    delete iSenderDescriptor;
    iSenderDescriptor = 0;
    iSenderDescriptor = aSenderDescriptor.AllocL();
    
    iAutomaticFind = aItemFinder;
    
    iMenuPane = aMenuPane;

    iIndex = aIndex;

    iIsContextMenu = aIsContextMenu;

    UpdateItemFinderMenuL();
    }
      
EXPORT_C void CFindItemMenu::UpdateItemFinderMenuL(
    TInt aResource,
    CEikMenuPane* aMenuPane )
    {
    if ( !iServiceHandler )
        {
        AttachItemFinderMenuL( 0 ); // param not really used
        }

    CItemFinder::TItemType itemType = iAutomaticFind ? iAutomaticFind->CurrentItemExt().iItemType : CItemFinder::ENoneSelected;    
    if ( aResource != -1 && aMenuPane )
        {
         if( aResource == R_FINDMENU_CALLUI_AIW_SUBMENU )
            {
            //Show full call command when number type is not SIP URI or
            //number type is phone number or
            //it is possible to call sender or callback number
            if ( ( itemType != CItemFinder::EEmailAddress ||
                ( itemType == CItemFinder::EEmailAddress &&
                !iFindItemVoIPExtension->VoIPProfilesExistL() ) ) &&
                ( itemType == CItemFinder::EPhoneNumber ||
                ( iSenderDescriptor->Length() &&
                iSenderDescType == CItemFinder::EPhoneNumber ) ||
                ( iCallbackNumber && iCallbackNumber->Length() ) ) )
                {
                iServiceHandler->InitializeMenuPaneL(
                    *aMenuPane,
                    aResource,
                    EFindMenuPlaceHolderCallUI,
                    iServiceHandler->InParamListL() );
                }
            //Show only Internet call command in Call submenu when
            //Number type is SIP URI
            else
                {
                CAiwGenericParamList* inList = CAiwGenericParamList::NewLC();

                // SIP Address
                TAiwGenericParam param( EGenericParamSIPAddress );
                inList->AppendL( param );

                iServiceHandler->InitializeMenuPaneL(
                    *aMenuPane,
                    aResource,
                    EFindMenuPlaceHolderCallUI,
                    *inList );

                CleanupStack::PopAndDestroy(); // inList
                }

            return;
            }

#ifdef RD_VIRTUAL_PHONEBOOK
        // Aiw Contacts
        else if ( aResource == R_FINDMENU_CONTACTS_AIW_SUBMENU )
            {
            if ( ( ( ( !iIsSenderKnown && iSenderDescriptor->Length() ) ||
                iCallbackNumber ) &&
                itemType == CItemFinder::ENoneSelected ) ||
                itemType != CItemFinder::ENoneSelected )
                {
                using namespace AiwContactAssign;

                CAiwGenericParamList& inList = iServiceHandler->InParamListL();

                // Contact Assign Data
                TAiwGenericParam param( EGenericParamContactAssignData );
                TAiwSingleContactAssignDataV1 assignData;
                assignData.SetFlags( 0 ); // Reset
                param.Value().Set(
                    TAiwSingleContactAssignDataV1Pckg( assignData ) );
                inList.AppendL( param );

                // Contact Data Type
                param.Reset();
                param.SetSemanticId( EGenericParamPhoneNumber );
                inList.AppendL( param );

                iServiceHandler->InitializeMenuPaneL(
                    *aMenuPane,
                    aResource,
                    EFindMenuCmdLast,
                    inList );

                return;
                }
            }
#endif // RD_VIRTUAL_PHONEBOOK

#ifndef RD_VIRTUAL_PHONEBOOK
        else if ( iPbkDataSave )
            {
            iPbkDataSave->DynInitMenuPaneL( aResource, aMenuPane );
            }
#endif // !RD_VIRTUAL_PHONEBOOK

        return;
        }

    TInt index = iIndex;

    TBuf<KMaxMenuTextLength> tempBuf;

    // Adds menu items depending the selected item
    switch ( itemType )
        {
        case CItemFinder::EPhoneNumber:
            {
#ifdef RD_VOIP_REL_2_2
            if ( FeatureManager::FeatureSupported(KFeatureIdCommonVoip ) )
                {
                // show call menu if allowed
                if ( !( iMenuItemFlags & CFindItemMenu::ECallItem ) )
                    {
                    // Call
                    iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_CALL );
                    AddMenuItemL(
                        *iMenuPane,
                        EFindItemCmdCall,
                        ( iIsContextMenu ? EFindItemContextMenuPlaceHolder : index ),
                        0,
                        tempBuf );
                    }
                 // if context menu, we will show call item anyway
                 else if ( iIsContextMenu )
                    {
                    // Call
                    iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_CALL );
                    AddMenuItemL(
                        *iMenuPane,
                        EFindItemCmdCall,
                        EFindItemContextMenuPlaceHolder,
                        0,
                        tempBuf );
                    }
                }
            else
                {
                // Call
                iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_CALL );
                AddMenuItemL(
                    *iMenuPane,
                    EFindItemCmdCall,
                    ( iIsContextMenu ? EFindItemContextMenuPlaceHolder : index ),
                    0,
                    tempBuf );
                }
            index = EFindItemCmdCall;
#else
            // Call
            iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_CALL );
            AddMenuItemL(
                *iMenuPane,
                EFindItemCmdCall,
                ( iIsContextMenu ? EFindItemContextMenuPlaceHolder : index ),
                0,
                tempBuf );
            index = EFindItemCmdCall;
#endif // RD_VOIP_REL_2_2
            // Write
            iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_MESSAGE_SUB );
            AddMenuItemL(
                *iMenuPane,
                EFindItemSubMenuSend,
                index,
               0,//R_FINDITEM_NUMBER_MESSAGE_SUBMENU,
                tempBuf );
            index = EFindItemSubMenuSend;

            break;
            }
        case CItemFinder::EUrlAddress:
            {
            iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_GOTO_URL );

            // check if not rstp    
            if ( iAutomaticFind->CurrentItemExt().iItemDescriptor->FindF( KRtspUrlAddress ) == KErrNotFound )
                {
                AddMenuItemL(
                    *iMenuPane,
                    EFindItemCmdGoToUrl,
                    ( iIsContextMenu ? EFindItemContextMenuPlaceHolder : index ),
                    0,
                    tempBuf);
                index = EFindItemCmdGoToUrl;

                if ( !iIsContextMenu )
                    {
                    // Add bookmark
                    iCoeEnv->ReadResourceL(
                        tempBuf, R_FINDITEMMENU_ADD_BOOKMARK );
                    AddMenuItemL(
                        *iMenuPane,
                        EFindItemCmdAddToBookmark,
                        index,
                        0,
                        tempBuf );
                    index = EFindItemCmdAddToBookmark;
                    }
                }
            else
                {
                AddMenuItemL(
                    *iMenuPane,
                    EFindItemCmdGoToRstp,
                    ( iIsContextMenu ? EFindItemContextMenuPlaceHolder : index ),
                    0,
                    tempBuf );
                index = EFindItemCmdGoToRstp;

                if ( !iIsContextMenu )
                    {
                    iCoeEnv->ReadResourceL(
                        tempBuf, R_FINDITEMMENU_ADD_TO_GALLERY );
                    AddMenuItemL(
                        *iMenuPane,
                        EFindItemCmdAddToGallery,
                        index,
                        0,
                        tempBuf );
                    index = EFindItemCmdAddToGallery;
                    }
                }
            break;
            }
        case CItemFinder::EEmailAddress:
            {
            // Checks VoIP profile count and local variation
            if ( iIsContextMenu && iFindItemVoIPExtension->VoIPProfilesExistL() )
                {
                //Call
                iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_CALL );
                AddMenuItemL(
                    *iMenuPane,
                    EFindItemCmdCall,
                    EFindItemContextMenuPlaceHolder,
                    0,
                    tempBuf );
                index = EFindItemCmdCall; // Replaces the call ui menu when email
                                          // field is selected.
                }

            // Write
            if( iEmailOverSmsFeatureSupported || iMMSFeatureSupported ||
                iEmailUiFeatureSupported ) // Sometimes submenu can be empty.
                {
                iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_MESSAGE_SUB );
                AddMenuItemL(
                    *iMenuPane,
                    EFindItemSubMenuSend,
                    ( ( iIsContextMenu &&
                        !iFindItemVoIPExtension->VoIPProfilesExistL() ) ?
                            EFindItemContextMenuPlaceHolder : index ),
                    0,//R_FINDITEM_EMAIL_MESSAGE_SUBMENU,
                    tempBuf );
                index = EFindItemSubMenuSend;
                }
            break;
            }
        case CItemFinder::EUriScheme:
            {
            // Use
            iCoeEnv->ReadResourceL( tempBuf, R_QTN_OPTIONS_SCHEME_USE );
            AddMenuItemL(
                *iMenuPane,
                EFindItemCmdUse,
                ( iIsContextMenu ? EFindItemContextMenuPlaceHolder : index ),
                0,
                tempBuf );
            index = EFindItemCmdUse;
            break;
            }
        default:
            {
            // Something else, probably nothing selected or new type which we
            // don't support.
            break;
            }
        }
    // Call
    if (
        ( itemType == CItemFinder::ENoneSelected ) &&
        (
            (
            iSenderDescriptor->Length() &&
            iSenderDescType == CItemFinder::EPhoneNumber ||
            iSenderDescriptor->Length() &&
            iSenderDescType == CItemFinder::EEmailAddress &&
            iFindItemVoIPExtension->VoIPProfilesExistL()
            )
        ||
            ( iCallbackNumber && iCallbackNumber->Length()  ) )

        ||
            ( itemType == CItemFinder::EEmailAddress &&
            iFindItemVoIPExtension->VoIPProfilesExistL() &&
            !iIsContextMenu )
        )
        {
#ifdef RD_VOIP_REL_2_2
        if ( FeatureManager::FeatureSupported(KFeatureIdCommonVoip ) )
            {
            if ( !iMenuItemFlags & CFindItemMenu::ECallItem )
                {
                iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_CALL );
                AddMenuItemL(
                    *iMenuPane,
                    EFindItemCmdCall,
                    iIndex,
                    0,
                    tempBuf ); // this goes always first
                if ( index == iIndex )
                    {
                    index = EFindItemCmdCall; // other commands are added after this.
                    }
                }
            }
        else
            {
            iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_CALL );
            AddMenuItemL(
                *iMenuPane,
                EFindItemCmdCall,
                iIndex,
                0,
                tempBuf ); // this goes always first
            if ( index == iIndex )
                {
                index = EFindItemCmdCall; // other commands are added after this.
                }
            }
#else
        iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_CALL );
        AddMenuItemL(
            *iMenuPane,
            EFindItemCmdCall,
            iIndex,
            0,
            tempBuf ); // this goes always first
        if ( index == iIndex )
            {
            index = EFindItemCmdCall; // other commands are added after this.

            }
#endif // RD_VOIP_REL_2_2
        }
    // Highlight status
    TInt highlight = 0;
    if ( iCommonUiRepository )
        {
        iCommonUiRepository->Get( KCuiAutomaticHighlight, highlight );
        }
    if ( !iIsContextMenu )
        {
        // Activate/Deactivate find
        if ( highlight )
            {
            iCoeEnv->ReadResourceL( tempBuf, R_QTN_FIND_DEACTIVATE_OPTION );
            AddMenuItemL(
                *iMenuPane,
                EFindItemCmdDisableAutoFind,
                index,
                0,
                tempBuf );
            }
        else
            {
            iCoeEnv->ReadResourceL( tempBuf, R_QTN_FIND_ACTIVATE_OPTION );
            AddMenuItemL(
                *iMenuPane,
                EFindItemCmdEnableAutoFind,
                index,
                0,
                tempBuf );
            }

        // Copy

        TInt len = 0;
        if ( iAutomaticFind && iAutomaticFind->CurrentItemExt().iItemType != CItemFinder::ENoneSelected )
              {
              HBufC* item = iAutomaticFind->CurrentSelection().AllocLC();  
              len = item->Length();
              CleanupStack::PopAndDestroy( ); 
              }

        if( (!iAutomaticFind || len != 0) && 
            highlight &&        
            ( itemType != CItemFinder::ENoneSelected || 
            iSenderHighlighted ) )
            {
            iCoeEnv->ReadResourceL( tempBuf, R_FINDITEMMENU_COPY );
            AddMenuItemL(
                *iMenuPane,
                EFindItemCmdCopy,
                index,
                0,
                tempBuf );
            }

       
        }

     // Add to contacts
     if ( ( itemType != CItemFinder::EUriScheme ) &&
        !( itemType == CItemFinder::EUrlAddress &&
        iIsContextMenu ) &&
        ( ( ( ( !iIsSenderKnown &&
        iSenderDescriptor->Length() ) ||
        iCallbackNumber ) &&
        itemType == CItemFinder::ENoneSelected ) ||
        itemType != CItemFinder::ENoneSelected ) )
        {
        AddMenuItemL(
            *iMenuPane,
            EFindItemCmdCreateContactCard,
            index,
            0,
            KNullDesC );
#ifndef RD_VIRTUAL_PHONEBOOK
        iPbkDataSave->AddMenuItemsL(
            iMenuPane,
            EFindItemCmdCreateContactCard );
#else
         iMenuPane->SetItemDimmed(
            EFindItemCmdCreateContactCard, ETrue );
            iMenuPane->AddMenuItemsL(
            R_FINDMENU_CONTACTS_AIW_ITEM,
            EFindItemCmdCreateContactCard );
#endif // !RD_VIRTUAL_PHONEBOOK
        }
    // Diming
    if ( !iIsContextMenu )
        {
        TInt dummy = 0;
        if ( iMenuPane->MenuItemExists( EFindItemMenuPlaceHolder, dummy ) )
            {
            iMenuPane->SetItemDimmed( EFindItemMenuPlaceHolder, ETrue );
            }
        }
    else
        {
        TInt dummy = 0;
        if ( iMenuPane->MenuItemExists( EFindItemContextMenuPlaceHolder, dummy ) )
            {
            iMenuPane->SetItemDimmed( EFindItemContextMenuPlaceHolder, ETrue );
            }
        }
    // Replace cmd call with AIW menu if more than one option available in AIW
    // menu
    // Note: count of VoIP profiles is not static. If phone contains VoIP
    // profiles there must be Internet call command in call submenu.
    TInt dummy = 0;
    if ( ( !iHideCallMenu ||
        ( iFindItemVoIPExtension->IsVoIPSupported() &&
        iFindItemVoIPExtension->VoIPProfilesExistL() ) ) &&
        iMenuPane->MenuItemExists( EFindItemCmdCall, dummy ) )
        {
        iMenuPane->SetItemDimmed( EFindItemCmdCall, ETrue );
        iMenuPane->AddMenuItemsL(
            R_FINDMENU_CALLUI_AIW_ITEM,
            EFindItemCmdCall );
        }
    }

EXPORT_C void CFindItemMenu::HandleItemFinderCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EFindItemCmdCall:
            {
            CallL();
            break;
            }
        case EFindItemSubMenuSend:
           {
           break;
           }

        case EFindItemCmdGoToUrl:
            {
            
            break;
            }
        case EFindItemCmdGoToRstp:
            {
            
            break;
            }

        case EFindItemCmdAddToBookmark:
            {
            AddToBookmarkL();
            break;
            }
        case EFindItemCmdCreateContactCardSub1:
        case EFindItemCmdCreateContactCardSub2:
        case EFindItemCmdCreateContactCardSub3:
            {
            CreateContactCardL( aCommand );
            // Restore original client application icon back to context pane.
            CEikStatusPane* statusPane =
                ( (CAknAppUi*)CEikonEnv::Static()->EikAppUi() )->StatusPane();
            CCoeControl* contextControl =
                statusPane->ControlL( TUid::Uid( EEikStatusPaneUidContext ) );
            CAknContextPane* contextPane =
                static_cast<CAknContextPane*>( contextControl );
            contextPane->SetPictureToDefaultL();
            break;
            }
        case EFindItemCmdAddToGallery:
            {
            AddToGalleryL();
            break;
            }

        case EFindItemCmdDisableAutoFind:
            {
            if (iCommonUiRepository)
                {
                iCommonUiRepository->Set( KCuiAutomaticHighlight, 0 );
                }
            AutoFindStatusChangedL();
            break;
            }

        case EFindItemCmdEnableAutoFind:
            {
            if (iCommonUiRepository)
                {
                iCommonUiRepository->Set( KCuiAutomaticHighlight, 1 );
                }
            AutoFindStatusChangedL();
            break;
            }

        case EFindItemCmdUse:
            {
            break;
            }

        case EFindItemCmdCopy:
            {
            CopyToClipboardL();
            break;
            }
        default:
            {
            TInt aiwCmd = iServiceHandler->ServiceCmdByMenuCmd( aCommand );            
            TBool calltypeInternetCall( EFalse );
            if ( iFindItemVoIPExtension->VoIPProfilesExistL() && iAutomaticFind && iAutomaticFind->CurrentItemExt().iItemType == CItemFinder::EEmailAddress )
                {
                calltypeInternetCall = ETrue;
                }

            // Call via Aiw
            if ( aiwCmd == KAiwCmdCall && FormatDialDataL( calltypeInternetCall ) )
                {
                if ( !iDialData )
                    {
                    break;
                    }

                CAiwGenericParamList& paramList =
                    iServiceHandler->InParamListL();

                iDialData->FillInParamListL( paramList );

                iServiceHandler->ExecuteMenuCmdL(
                    aCommand,
                    paramList,
                    iServiceHandler->OutParamListL(),
                    0, // No options used.
                    0 ); // no dial results are wanted.
                }
#ifdef RD_VIRTUAL_PHONEBOOK
             // Contacts via Aiw
            else if ( aiwCmd == KAiwCmdAssign )
                {
                CreateContactCardL( aCommand );
                }
#endif // RD_VIRTUAL_PHONEBOOK
            break;
            }
        }
    }

EXPORT_C void CFindItemMenu::HandleCallL( const TDesC& aSenderDescriptor )
    {
    AttachItemFinderMenuL( 0 ); // Make sure that this get called even if
                                // caller won't call this

    delete iSenderDescriptor;
    iSenderDescriptor = 0;
    iSenderDescriptor = aSenderDescriptor.AllocL();

    CallL();
    }

EXPORT_C void CFindItemMenu::HandleVoIPCallL( const TDesC& aSenderDescriptor )
    {
    AttachItemFinderMenuL( 0 ); // Make sure that this get called even if
                                // caller won't call this

    delete iSenderDescriptor;
    iSenderDescriptor = 0;
    iSenderDescriptor = aSenderDescriptor.AllocL();

    VoIPCallL();
    }

void CFindItemMenu::CallL()
    {
    if ( !iDialData )
        {
        return;
        }

    if ( !FormatDialDataL( EFalse ) )
        {
        return;
        }

    // Create Call W/O Menu
    CAiwGenericParamList& paramList =
        iServiceHandler->InParamListL();

    iDialData->FillInParamListL( paramList );

    iServiceHandler->ExecuteServiceCmdL(
        KAiwCmdCall,
        paramList,
        iServiceHandler->OutParamListL(),
        0, // No options used.
        NULL );
    }

void CFindItemMenu::VoIPCallL()
    {
    if ( !iDialData )
        {
        return;
        }
  if ( !FormatDialDataL( ETrue ) ||
       !iFindItemVoIPExtension->IsVoIPSupported() )
        {
        return;
        }

    // Create Call W/O Menu
    CAiwGenericParamList& paramList = iServiceHandler->InParamListL();

    iDialData->FillInParamListL( paramList );

    iServiceHandler->ExecuteServiceCmdL(
        KAiwCmdCall,
        paramList,
        iServiceHandler->OutParamListL(),
        0, // No options used.
        NULL );
    }

void CFindItemMenu::SendMessageL( const TUid aMtmUid )
    {
	
    }

void CFindItemMenu::GoToUrlL( TUid /*aHandlerAppUid*/ )
   {
    // Scheme handler can handle this
   }

void CFindItemMenu::AddToBookmarkL()
    {
    // Read default name from resources
    RConeResourceLoader ldr( *iCoeEnv );

    TFileName dialogResource( KDialogResourceName );

    ldr.OpenL( dialogResource );
    CleanupClosePushL( ldr );

    // Read default name from resources
    HBufC* defaultName =
        iCoeEnv->AllocReadResourceLC( R_FINDITEM_DEFAULT_BOOKMARK_NAME );

    TBuf<KMaxBookmarkNameLength> retName;
    retName.Copy( defaultName->Des() );

    // Query bookmark name from user
    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( retName );
    dlg->SetMaxLength( KMaxBookmarkNameLength );
    if ( !dlg->ExecuteLD( R_FINDITEM_BOOKMARK_QUERY_DIALOG ) )
        {
        // User press cancel - do not add bookmark
        CleanupStack::PopAndDestroy( 2 ); // defaultName, resourceLoader
        return;
        }

    HBufC* msgBuffer = iCoeEnv->AllocReadResourceLC( R_FINDITEM_BOOKMARK_SAVED );
    CAknConfirmationNote* note = new (ELeave)CAknConfirmationNote( ETrue );
    note->ExecuteLD( *msgBuffer );

    CleanupStack::PopAndDestroy( 3 ); // resourceLoader,
                                      // defaultName, msgBuffer
    }

void CFindItemMenu::CreateContactCardL( TInt aCommandId )
    {
    CItemFinder::TItemType itemType = iSenderDescType; // default
    HBufC* item = 0;
    if ( iAutomaticFind && iAutomaticFind->CurrentItemExt().iItemType != CItemFinder::ENoneSelected )
        {
        item = iAutomaticFind->CurrentItemExt().iItemDescriptor->AllocLC();
        itemType = iAutomaticFind->CurrentItemExt().iItemType;
        }
    else if ( !iCallbackNumber ) // default type if ok
        {
        item = iSenderDescriptor->AllocLC();        
        }
    else if ( iIsSenderKnown || !iSenderDescriptor->Length() )
        {
        // callbacknumber exists and sender's address is already in phonebook
        //  or sender's number is NULL
        item = iCallbackNumber->AllocLC();
        }
    else
        {
        TInt index = 0;
        item = ChooseNumberQueryL( index );
        if (item)
            {
            CleanupStack::PushL( item );
            if ( index == EFindUICallbackNumber ) // sender type is still
                                                  // default
                {
                itemType = CItemFinder::EPhoneNumber;
                }
            }
        else
            {
            return;
            }
        }
#ifndef RD_VIRTUAL_PHONEBOOK
    CArrayPtrFlat<CPbkFieldInfo> *fieldArray =
        new(ELeave)CArrayPtrFlat<CPbkFieldInfo>( 1 );
    CleanupStack::PushL( fieldArray );

    for ( TInt i = 0; i < iPbkEngine->FieldsInfo().Count(); i++ )
        {
        CPbkFieldInfo* fieldInfo = iPbkEngine->FieldsInfo()[ i ];
        // Only interested in text storage fields
        if ( !( fieldInfo->FieldStorageType() == KStorageTypeText ) )
            {
            continue;
            }

        if ( itemType == CItemFinder::EPhoneNumber &&
            ( fieldInfo->IsPhoneNumberField() ||
#ifdef __VOIP 
            iFindItemVoIPExtension->IsVoIPSupported() && 
#else
            iVoIPFeatureSupported &&
#endif 
            fieldInfo->FieldId() == EPbkFieldIdVOIP ) )
            {
            fieldArray->AppendL( fieldInfo );
            }
        else if ( itemType == CItemFinder::EEmailAddress &&
            ( fieldInfo->FieldId() == EPbkFieldIdEmailAddress ||
#ifdef __VOIP 
			iFindItemVoIPExtension->IsVoIPSupported() && 
#else
            iVoIPFeatureSupported &&
#endif 
            fieldInfo->FieldId() == EPbkFieldIdVOIP ) )
            {
            fieldArray->AppendL(fieldInfo);
            }
        else if ( ( itemType == CItemFinder::EUrlAddress ||
            itemType == CItemFinder::EUriScheme ) &&
            fieldInfo->FieldId() == EPbkFieldIdURL )
            {
            fieldArray->AppendL( fieldInfo );
            }
        }
#endif // !RD_VIRTUAL_PHONEBOOK

    TPtr itemDes = item->Des();

#ifndef RD_VIRTUAL_PHONEBOOK
    iPbkDataSave->HandleCommandL( aCommandId, *fieldArray, *item );
    CleanupStack::PopAndDestroy( 2 ); // fieldArray, item
#else //RD_VIRTUAL_PHONEBOOK
    using namespace AiwContactAssign;

    CAiwGenericParamList& inList = iServiceHandler->InParamListL();

    // Contact Assign Data.
    TAiwGenericParam param( EGenericParamContactAssignData );
    TAiwSingleContactAssignDataV1 assignData;
    assignData.SetFlags( 0 );
    param.Value().Set( TAiwSingleContactAssignDataV1Pckg( assignData ) );
    inList.AppendL( param );

    // Contact Data Type.
    param.Reset();
    switch( itemType ) // Resolve type.
        {
        case CItemFinder::EPhoneNumber:                      // Phone number
            param.SetSemanticId( EGenericParamPhoneNumber );
            // convert phone number.
            CommonPhoneParser::ParsePhoneNumber(
                itemDes, CommonPhoneParser::EPhoneClientNumber );
            break;
        case CItemFinder::EEmailAddress:                     // E-mail
            param.SetSemanticId( EGenericParamEmailAddress );
            break;
       case CItemFinder::EUrlAddress:                        // URL
       case CItemFinder::EUriScheme:                         // URI
            param.SetSemanticId( EGenericParamURL );
            break;
        default:
            CleanupStack::PopAndDestroy( 1 ); // item
            return; // unknown item type.
        }
    param.Value().Set( itemDes );
    inList.AppendL( param );

    iServiceHandler->ExecuteMenuCmdL(
        aCommandId,
        inList,
        iServiceHandler->OutParamListL(),
        0,
        &iCallback );
    CleanupStack::PopAndDestroy( 1 ); // item
#endif // !RD_VIRTUAL_PHONEBOOK
    }

void CFindItemMenu::AddToGalleryL()
    {
    //no need to do anything ,due to the remove of AknCommonDialogs
    }

EXPORT_C void CFindItemMenu::SetSenderDescriptorType(
    CItemFinder::TItemType aType )
    {
    iSenderDescType = aType;
    }

EXPORT_C void CFindItemMenu::AttachItemFinderMenuL( TInt /*aResource*/ )
    {
    if ( iServiceHandler ) // this method should be called once and only once.
        {
        return;
        }
#ifndef RD_VIRTUAL_PHONEBOOK
    iRPbkResourceFile = new (ELeave)RPbkViewResourceFile( *iCoeEnv );
    iRPbkResourceFile->OpenL();
    iPbkEngine = CPbkContactEngine::NewL();
    iPbkDataSave = CPbkDataSaveAppUi::NewL( *iPbkEngine );
#endif // !RD_VIRTUAL_PHONEBOOK

    TRAPD( ret, iCommonUiRepository = CRepository::NewL( KCRUidCommonUi ) );
    if ( ret == KErrNone )
        {
        iCommonUiRepositoryWatcher = CCommonUiRepositoryWatcher::NewL(
            KCRUidCommonUi,
            KCuiAutomaticHighlight,
            CCenRepNotifyHandler::EIntKey,
            TCallBack( AutoFindStatusChanged, this ),
            iCommonUiRepository );
        }

    // AIW
    iServiceHandler = CAiwServiceHandler::NewL();

    //  Call UI
    iServiceHandler->AttachMenuL(
        R_FINDMENU_CALLUI_AIW_SUBMENU,
        R_FINDMENU_CALLUI_AIW_INTEREST );

    CMyMenuPane* callUiMenu =
        new (ELeave) CMyMenuPane( (MEikMenuObserver*)this ); // not used really
    CleanupStack::PushL( callUiMenu );
    TResourceReader callUiReader;
    iCoeEnv->CreateResourceReaderLC(
        callUiReader, R_FINDMENU_CALLUI_AIW_SUBMENU );
    callUiMenu->ConstructFromResourceL( callUiReader );
    CleanupStack::PopAndDestroy(); // callUiReader

    iServiceHandler->InitializeMenuPaneL(
        *(CEikMenuPane*)callUiMenu,
        R_FINDMENU_CALLUI_AIW_SUBMENU,
        EFindMenuPlaceHolderCallUI,
        iServiceHandler->InParamListL() );

    if ( callUiMenu->NumberOfItemsInPane() < 2 )
        {
        iHideCallMenu = ETrue;
        }

    iServiceHandler->AttachL( R_FINDMENU_CALLUI_AIW_INTEREST );
    CleanupStack::PopAndDestroy(); // callUiMenu

#ifdef RD_VIRTUAL_PHONEBOOK
    // Contacts
    iServiceHandler->AttachMenuL(
        R_FINDMENU_CONTACTS_AIW_SUBMENU,
        R_FINDMENU_CONTACTS_AIW_INTEREST );
#endif // RD_VIRTUAL_PHONEBOOK
    }

void CFindItemMenu::AutoFindStatusChangedL()
    {
    if ( iAutomaticFind )
        {
        TInt value = 0;
        if ( iCommonUiRepository )
            {
            iCommonUiRepository->Get( KCuiAutomaticHighlight, value );
            }
        if ( value == 1 )
            {
            iAutomaticFind->SetFindModeL( CItemFinder::EUrlAddress|CItemFinder::EEmailAddress|CItemFinder::EPhoneNumber );
            }
        else
            {
            iAutomaticFind->SetFindModeL( 0 );
            }
        }
    }

TInt CFindItemMenu::AutoFindStatusChanged( TAny* aThis )
    {
    CFindItemMenu* me = (CFindItemMenu*)aThis;
    TRAPD( err, me->AutoFindStatusChangedL() );
    return err;
    }

TBool CFindItemMenu::FormatDialDataL( TBool aFormatVoIPDialData )
    {
    if ( !iDialData )
        {
        return EFalse;
        }

    TBool numberSelected = ( iAutomaticFind && iAutomaticFind->CurrentItemExt().iItemType == CItemFinder::EPhoneNumber );

    TBool SIPURISelected = 
        ( aFormatVoIPDialData && 
            iAutomaticFind &&
                iFindItemVoIPExtension->VoIPProfilesExistL() &&
                    iAutomaticFind->CurrentItemExt().iItemType == CItemFinder::EEmailAddress );

    HBufC* parsedNumber = NULL ;
    // Foucs in text body and a phone number has been selected
    // Takes number from selected item when SIP URI is selected.
    if ( numberSelected || SIPURISelected )
        {
        parsedNumber = iAutomaticFind->CurrentItemExt().iItemDescriptor->AllocLC();
        }
    else if ( !iCallbackNumber ) // Focus in address control with callback
                                 // number
        {
        parsedNumber = iSenderDescriptor->AllocLC();
        }                  
    else if ( !( iSenderDescType == CItemFinder::EPhoneNumber && iSenderDescriptor->Length() ) )
        // Eg. Email over Sms with callback number
        {
        parsedNumber = iCallbackNumber->AllocLC();
        }
    else  // both callback number and sender number, use query
        {                   
        TInt dummy = 0;
        parsedNumber = ChooseNumberQueryL( dummy );
        if( parsedNumber )
            {
            CleanupStack::PushL( parsedNumber );
            }
        else
            {
            return EFalse;
            }
        }
    TPtr numberPtr = parsedNumber->Des();

    using namespace AIWDialDataExt;
    CommonPhoneParser::ParsePhoneNumber(
        numberPtr, CommonPhoneParser::EPhoneClientNumber );
    __ASSERT_ALWAYS( parsedNumber->Length() <= KMaximumPhoneNumberLength,
        Panic( ETooLongItem ) );
    AknTextUtils::ConvertDigitsTo( numberPtr, EDigitTypeWestern );
#ifdef RD_VOIP_REL_2_2
    if ( FeatureManager::FeatureSupported(KFeatureIdCommonVoip ) )
        {
        if ( aFormatVoIPDialData )
            {
            // sets call type for VoIP
            iDialData->SetCallType( CAiwDialData::EAIWVoiP );
            }
        }
#endif // RD_VOIP_REL_2_2
    iDialData->SetPhoneNumberL( numberPtr );

    CleanupStack::PopAndDestroy(); // number;
    return ETrue;
    }

void CFindItemMenu::LaunchGenericUriL()
    {
	
    }

EXPORT_C void CFindItemMenu::SetCallbackNumber( const TDesC& aPhoneNumber )
    {
    delete iCallbackNumber;
    iCallbackNumber = 0;
    iCallbackNumber = aPhoneNumber.Alloc();    
    }

HBufC* CFindItemMenu::ChooseNumberQueryL( TInt& aIndex )
    {
    HBufC* ret = 0;

    // First phase construction of menu list
    CAknSingleHeadingPopupMenuStyleListBox* phoneNumberList =
        new (ELeave) CAknSingleHeadingPopupMenuStyleListBox;
    CleanupStack::PushL( phoneNumberList );

    // Create a popuplist to show the menu list in
    CAknPopupList* popupList =
        CAknPopupList::NewL( phoneNumberList, R_AVKON_SOFTKEYS_OK_CANCEL );
    CleanupStack::PushL( popupList );
    // Second phase construction of popupList
    phoneNumberList->ConstructL( popupList,EAknListBoxMenuList );

    // Set up menu items
    CTextListBoxModel* model = phoneNumberList->Model();
    model->SetOwnershipType( ELbmOwnsItemArray );

    CDesCArray* phoneNumberListArray =
        static_cast<CDesCArray*>( model->ItemTextArray() );

    HBufC* title;
    title = StringLoader::LoadLC( R_QTN_SMS_USENUMBER );
    popupList->SetTitleL( *title );
    CleanupStack::PopAndDestroy( title );

    _LIT( KStringHeader, "%S\t%S" );
    TBuf <256> string;
    HBufC* head;
    // sender item
    head = StringLoader::LoadLC( R_QTN_SMS_USENUMBER_FROM );
    string.Format( KStringHeader(), head, iSenderDescriptor );
    phoneNumberListArray->AppendL ( string);
    CleanupStack::PopAndDestroy( head );
    // callback number
    head = StringLoader::LoadLC( R_QTN_SMS_USENUMBER_CALLBACK );
    string.Format( KStringHeader(), head, iCallbackNumber );
    phoneNumberListArray->AppendL( string );
    CleanupStack::PopAndDestroy( head );

    CleanupStack::Pop( popupList );

    if ( popupList->ExecuteLD() )
        {
        ret = ( phoneNumberList->CurrentItemIndex() == EFindUICallbackNumber ) ?
            iCallbackNumber->AllocL() : iSenderDescriptor->AllocL();
        aIndex = phoneNumberList->CurrentItemIndex();
        }

    CleanupStack::PopAndDestroy( phoneNumberList );

    return ret;
    }

// -----------------------------------------------------------------------------
// TInt CFindItemMenu::LoadMPEngineApiL
// Load MPEngine Api.
// -----------------------------------------------------------------------------
void CFindItemMenu::LoadMPEngineApiL()
   {
   // Memo saving dll loading.
   if( !iMPEngineDllLoaded )
        {
        if( iMPEngineDll.Load( KCommonUiMPEngineApiLoaderName ) == KErrNone )
            {
            iMPEngineDllLoaded = ETrue;
            // Request the entry function
            MPEngineApiL mpengineApi =
                (MPEngineApiL) iMPEngineDll.Lookup( KMPEngineApiDllEntryPoint );
            if( mpengineApi )
                {
                // Create the class
                iMPEngineApi = (CCommonUiMPEngineApiLoader*) (*mpengineApi)();
                }
            }
        }
    // The wrapper failed to load.
    if ( !iMPEngineApi )
        {
        User::Leave( KErrNotFound );
        }
    }

// -----------------------------------------------------------------------------
// TInt CFindItemMenu::CopyToClipboardL
//
// -----------------------------------------------------------------------------
void CFindItemMenu::CopyToClipboardL()
    {       
    HBufC* item = 0;
    TInt len = 0;
    if ( iAutomaticFind && iAutomaticFind->CurrentItemExt().iItemType != CItemFinder::ENoneSelected )
        {
        item = iAutomaticFind->CurrentSelection().AllocLC();                        
        len = item->Length();
        }
    else if( iSenderHighlighted )
        {
        item = iSenderDisplayText->AllocLC();
        len = item->Length();
        }            
    __ASSERT_DEBUG( len > 0, Panic( ENoItemSelected ) );        

    CPlainText* plainText = CPlainText::NewL( CPlainText::ESegmentedStorage, len );
    CleanupStack::PushL( plainText );
    plainText->InsertL( 0, *item );

    CClipboard* cb = CClipboard::NewForWritingLC( iCoeEnv->FsSession() );
    plainText->CopyToStoreL( cb->Store(), cb->StreamDictionary(), 0, len );
    cb->CommitL();
    
    CleanupStack::PopAndDestroy( 3 ); // item, plainText, cb
    // fix for EJCU-7K98TM 
    CAknNoteDialog* dlg = new (ELeave) CAknNoteDialog();
    dlg->SetTimeout(CAknNoteDialog::EShortTimeout);
    dlg->SetTone(CAknNoteDialog::ENoTone);
    dlg->ExecuteLD( R_AVKON_NOTE_CONF_COPIED );
    // fix end
    }

EXPORT_C void CFindItemMenu::SetSenderHighlightStatus( TBool aStatus )
    {
    iSenderHighlighted = aStatus;
    }

EXPORT_C void CFindItemMenu::SetSenderDisplayText( const TDesC& aText )
    {
    delete iSenderDisplayText;
    iSenderDisplayText = 0;
    iSenderDisplayText = aText.Alloc();
    }

#ifdef RD_VOIP_REL_2_2
EXPORT_C void CFindItemMenu::SetMenuItemVisibility( 
    CFindItemMenu::TMenuItem aItem, 
    TBool aVisible )
    {
    if ( aVisible )
        {
        // iMenuItemFlags, 0 = visible
        iMenuItemFlags &= ~(TInt)aItem;
        }
    else
        {
        // iMenuItemFlags, 1 = not allowed
        iMenuItemFlags |= (TInt)aItem;
        } 
    }
#else
EXPORT_C void CFindItemMenu::SetMenuItemVisibility( 
    CFindItemMenu::TMenuItem /*aItem*/, 
    TBool /*aVisible*/ )
    {
    }
#endif // RD_VOIP_REL_2_2
CCommonUiRepositoryWatcher* CCommonUiRepositoryWatcher::NewL(
    const TUid aUid,
    const TUint32 aKey,
    CCenRepNotifyHandler::TCenRepKeyType aKeyType,
    TCallBack aCallBack,
    CRepository* aRepository )
    {
    CCommonUiRepositoryWatcher* self =
        new(ELeave) CCommonUiRepositoryWatcher(
            aUid, aKey, aCallBack, aRepository );

    CleanupStack::PushL( self );
    self->ConstructL( aKeyType );
    CleanupStack::Pop( self );

    return self;
    }

CCommonUiRepositoryWatcher::~CCommonUiRepositoryWatcher()
    {
    if ( iNotifyHandler )
        {
        iNotifyHandler->StopListening();
        }
    delete iNotifyHandler;
    }

CCommonUiRepositoryWatcher::CCommonUiRepositoryWatcher(
    const TUid aUid,
    const TUint32 aKey,
    TCallBack aCallBack,
    CRepository* aRepository )
    : iUid( aUid ),
    iKey( aKey ),
    iCallBack( aCallBack ),
    iRepository( aRepository )
    {
    }

void CCommonUiRepositoryWatcher::ConstructL(
    CCenRepNotifyHandler::TCenRepKeyType aKeyType )
    {
    iNotifyHandler =
        CCenRepNotifyHandler::NewL( *this, *iRepository, aKeyType, iKey );
    iNotifyHandler->StartListeningL();
    }

void CCommonUiRepositoryWatcher::ConstructL()
    {
    iNotifyHandler = CCenRepNotifyHandler::NewL( *this, *iRepository );
    iNotifyHandler->StartListeningL();
    }

TUint32 CCommonUiRepositoryWatcher::ChangedKey()
    {
    return iChangedKey;
    }

void CCommonUiRepositoryWatcher::HandleNotifyInt(
    TUint32 aKey,
    TInt aNewValue )
    {
#ifdef _DEBUG
    RDebug::Print(_L("CCommonUiRepositoryWatcher::HandleNotifyInt aKey=%d, aNewValue=%d"), aKey, aNewValue);
#endif
    (void)aNewValue;
    iChangedKey = aKey;
    iCallBack.CallBack();
    iChangedKey = NCentralRepositoryConstants::KInvalidNotificationId;
    }

void CCommonUiRepositoryWatcher::HandleNotifyError(
    TUint32 /*aKey*/,
    TInt /*aError*/,
    CCenRepNotifyHandler* /*aHandler*/ )
    {
    }


EXPORT_C TInt MPBAiwNotify::HandleNotifyL(TInt /*aCmdId*/, TInt aEventId,
        CAiwGenericParamList& aEventParamList,
        const CAiwGenericParamList& /*aInParamList*/)
    {
    if (aEventId == KAiwEventError)
        {
        if (aEventParamList.Count() > 0)
            {
            TInt32 err = aEventParamList[0].Value().AsTInt32();
            User::Leave(err);                
            }
        }
    return KErrNone;
    }    

//  End of File
