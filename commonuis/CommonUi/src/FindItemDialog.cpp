/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include <avkon.hrh>
#include <aknappui.h>
#include <eikrted.h> // for CRichTextEditor
#include <txtrich.h> // for CRichText
#include <AknUtils.h> // for AknUtils
#include <eikmenup.h> // for CEikMenuPane
#include <eikmenub.h> // for CEikMenuBar
#include <e32keys.h> // for TKeyCode
#include <akntitle.h> // for CAknTitlePane
#include <aknnavi.h> // for NaviPane
#include <aknnavide.h> // for CAknNavigationDecorator
#include <aknnotedialog.h> // for CAknNoteDialog
#include <akncontext.h> // for AknContextPane
#include <bautils.h> // BaflUtils
#include <eikbtgpc.h> // for ButtonGroupContainer
#include <uikon.hrh> // for EKeyOk

#include <apgcli.h> // RApaLsSession for WMLBrowser launch

#ifndef RD_VIRTUAL_PHONEBOOK
#include <CPbkContactEngine.h> // Phonebook Engine
#include <RPbkViewResourceFile.h> // Phonebook view dll resource loader
#include <cpbkdatasaveappui.h> // for PbkDataSaveAppUi
#include <CPbkFieldsInfo.h> // Phonebook field types
#else // RD_VIRTUAL_PHONEBOOK
#include <AiwServiceHandler.h> // CAiwServiceHandler
#include <AiwContactAssignDataTypes.h> // AiwContactAssign
#endif // !RD_VIRTUAL_PHONEBOOK

#include <commonphoneparser.h> // Phonenumber parser

#include <baclipb.h> // For CClipboard

#include <aknnotewrappers.h>

#include <finditemui.rsg>

#include <featmgr.h>

#include "finditemdialogpanic.h"
#include "finditemdialog.h"
#include "finditem.hrh"
#include "finditemcontroller.h"

#include <bldvariant.hrh>
#include <find.hlp.hrh> // for help context
#include <hlplch.h> // For HlpLauncher

#include <aknlayout.cdl.h>
#include <applayout.cdl.h>
#include <AiwCommon.hrh>

#include "FindItemVoIPExtension.h"
#include "FindItemMenuWrapper.h"

#include <AknDef.h> // KEikDynamicLayoutVariantSwitch
#include <AknsBasicBackgroundControlContext.h>
#include <AknsUtils.h> // MAknsSkinInstance
#include <AknsDrawUtils.h> // AknsDrawUtils
#include <aknlayoutscalable_apps.cdl.h>

#include <txtfrmat.h>  // for TCharFormat

#include <aknnavilabel.h> // for changing the lable of navipane

#include <AknTasHook.h> // for testability hooks
_LIT( KResFileName, "z:\\resource\\finditemui.rsc" );

// Panic
_LIT( KFindItemPanic, "FindItemDialog" );
// Space for WML Browser's parameter
_LIT( KSpace, " " );
// Position indicator in navipane
_LIT( KPosIndicator, "%d/%d" );
// Period and space constant for inserting paragraphs
_LIT( KPeriodAndSpace, ". " );

// Point where edwin changes from full to band formatting
const TInt KFullFormattingUpperThreshold = 2000;
// If edwin is using band formatting, there should be enough
// paragraphs to make it faster.
const TInt KLengthOfRecommendedParagraph = 500;
// Maximum length of Browser bookmark
const TInt KMaxBookmarkNameLength = 50;

// Wap Browser's constants UId
const TUid KWapUid = { 0x10008D39 };

// magic number for Wml browser to open the URL
_LIT( KWmlBrowserParameter, "4");

_LIT( KRtspUrlAddress, "rtsp://" );
_LIT( KHhttpAddress, "http://" );

const TInt KCommonUiEdwinLines = 7;

const TUid KCommonUIUid = { 0x100058FD };

/**
* Class to
*/
class CRichTextEditorContainer
    : public CEikBorderedControl
    {
    public: // Constructors and destructors

        /**
        * Constructor.
        */
        CRichTextEditorContainer();

        /**
        * Destructor.
        */
        ~CRichTextEditorContainer();

    public: // Functions from base classes

        /**
        * From CCoeControl
        */
        void ConstructFromResourceL( TResourceReader& aReader );

        /**
        * From CCoeControl
        */
        void SizeChanged();

        /**
        * From CCoeControl.
        */
        void Draw( const TRect& aRect ) const;

        /**
        * From CCoeControl
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

        /**
        * From CCoeControl
        */
        void HandleResourceChange( TInt aType );

        /**
        * From CCoeControl
        */
        TSize MinimumSize();

    public: // data

        // Rich text editor.
        CEikRichTextEditor* iEditor;

        TInt iRows;

        // Background context.
        CAknsBasicBackgroundControlContext* iBgContext;
    };

const CFindItemEngine::TFindItemSearchCase KSearchTelInternetNumber =
    static_cast<CFindItemEngine::TFindItemSearchCase>
        ( CFindItemEngine::EFindItemSearchPhoneNumberBin |
        CFindItemEngine::EFindItemSearchMailAddressBin );

// -----------------------------------------------------------------------------
// Panic
//
// -----------------------------------------------------------------------------
GLDEF_C void Panic( TFindItemDialogPanic aPanic )
    {
    User::Panic( KFindItemPanic, aPanic );
    }

NONSHARABLE_CLASS(PBAiwNotify): public MAiwNotifyCallback
    {
public:
    // aiw call back funtion
    // Fix for ESLM-7XH9UM: we must return true for the   
    // phonebook to know it can exit    
    TInt HandleNotifyL(TInt aCmdId, TInt aEventId,
            CAiwGenericParamList& aEventParamList,
            const CAiwGenericParamList& aInParamList);
    };

TInt PBAiwNotify::HandleNotifyL(TInt /*aCmdId*/, TInt aEventId,
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
    // Fix for ESLM-7XH9UM: we must return true for the   
    // phonebook to know it can exit    
    return ETrue;
    }    

NONSHARABLE_CLASS(CItemFinderExtension) : public CBase
	{
public: 
	~CItemFinderExtension(); 
	static CItemFinderExtension* NewL(); 
	
	//new function
public:
	PBAiwNotify* CallBack();
	
private: 
	CItemFinderExtension(); 
	void ConstructL();	
	
public:
	PBAiwNotify iCallBack;
	};

CItemFinderExtension::~CItemFinderExtension()
	{
	
	}

CItemFinderExtension* CItemFinderExtension::NewL()
	{
	CItemFinderExtension* self = new ( ELeave )CItemFinderExtension;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

PBAiwNotify* CItemFinderExtension::CallBack()
	{
	return &iCallBack;
	}

CItemFinderExtension::CItemFinderExtension()
	{
	
	}

void CItemFinderExtension::ConstructL()
	{
	
	}



// ================= MEMBER FUNCTIONS =======================

// -----------------------------------------------------------------------------
// CFindItemDialog::~CFindItemDialog
//  Default destructor
// -----------------------------------------------------------------------------
//
EXPORT_C CFindItemDialog::~CFindItemDialog()
    {
    AKNTASHOOK_REMOVE();
    // Remove from stack
    iEikonEnv->RemoveFromStack( this );
    // Unload the resourcefile
    iResLoader.Close();
    delete iController;
    // Put the application's title back
    if ( iTitlePane && iOldTitle )
        {
        iTitlePane->SetText( iOldTitle ); // takes ownership of iOldTitle
        }
    delete iNaviDecorator;
    delete iSBFrame;
    delete iItemArrayForScrollBar;

#ifndef RD_VIRTUAL_PHONEBOOK
    delete iPbkDataSave;
    delete iPbkEngine;
    iPbkResourceFile.Close();
#endif //RD_VIRTUAL_PHONEBOOK
    delete iIdle;

    delete iServiceHandler;
    delete iFindItemVoIPExtension;

    delete iBgContext;

    delete iTitleText;

    delete iDialData;
    
    delete iExtension;
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::CFindItemDialog
//  Default constructor
// -----------------------------------------------------------------------------
//
CFindItemDialog::CFindItemDialog(
    const TDesC& aPlainText,
    const CFindItemEngine::TFindItemSearchCase aSearchCase )
    : iPlainText( aPlainText ),
    iSearchCase( aSearchCase ),
#ifndef RD_VIRTUAL_PHONEBOOK
    iPbkResourceFile( *iCoeEnv ),
#endif // !RD_VIRTUAL_PHONEBOOK
    iResLoader( *iCoeEnv )
    {
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::NewL
//  Two-phased constructor
// -----------------------------------------------------------------------------
//
EXPORT_C CFindItemDialog* CFindItemDialog::NewL(
    const TDesC& aPlainText,
    const CFindItemEngine::TFindItemSearchCase aSearchCase )
    {
    CFindItemDialog* self =
        new(ELeave) CFindItemDialog( aPlainText, aSearchCase );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    AKNTASHOOK_ADDL( self, "CFindItemDialog" );
    return self;
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::ConstructL
//  EPOC constructor
// -----------------------------------------------------------------------------
//
void CFindItemDialog::ConstructL()
    {
    // Must tell CONE where to find dialog resource
    TFileName fileName( KResFileName );
    iResLoader.OpenL( fileName );

    // Call the base class' two-phased constructor
    CAknDialog::ConstructL( R_AVKON_FORM_MENUBAR );

#ifndef RD_VIRTUAL_PHONEBOOK
    iPbkEngine = CPbkContactEngine::NewL();
    iPbkResourceFile.OpenL();
    iPbkDataSave = CPbkDataSaveAppUi::NewL( *iPbkEngine );
#endif // RD_VIRTUAL_PHONEBOOK

    // Set up the StatusPane
    CEikStatusPane *sp =
         ( (CAknAppUi*)iEikonEnv->EikAppUi() )->StatusPane();
    // Fetch pointer to the default title pane control
    iTitlePane =
        (CAknTitlePane *)sp->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) );
    // save the old Title
    const TDesC* title = iTitlePane->Text();
    iOldTitle = title->AllocL();

    // Fetch pointer to the default navi pane control
    iNaviPane =
        ( CAknNavigationControlContainer *)sp->ControlL(
            TUid::Uid( EEikStatusPaneUidNavi ) );

    // AIW
    iServiceHandler = CAiwServiceHandler::NewL();

    // CallUi
    iServiceHandler->AttachMenuL(
        R_FINDITEM_CALLUI_AIW_SUBMENU,
        R_FINDITEM_CALLUI_AIW_INTEREST );

    CMyMenuPane* callUiMenu = new (ELeave)CMyMenuPane( this );
    CleanupStack::PushL( callUiMenu );
    TResourceReader callUiReader;
    iEikonEnv->CreateResourceReaderLC(
        callUiReader, R_FINDITEM_CALLUI_AIW_SUBMENU );
    callUiMenu->ConstructFromResourceL( callUiReader );
    CleanupStack::PopAndDestroy(); // callUiReader

    iServiceHandler->InitializeMenuPaneL(
        *(CEikMenuPane*)callUiMenu,
        R_FINDITEM_CALLUI_AIW_SUBMENU,
        EFindMenuPlaceHolderCallUI,
        iServiceHandler->InParamListL() );

    if ( callUiMenu->NumberOfItemsInPane() < 2 )
        {
        iHideCallMenu = ETrue;
        }

    iServiceHandler->AttachL( R_FINDITEM_CALLUI_AIW_INTEREST );
    CleanupStack::PopAndDestroy(); // callUiMenu

#ifdef RD_VIRTUAL_PHONEBOOK
    // Contacts
    iServiceHandler->AttachMenuL(
        R_FINDITEM_CONTACTS_AIW_SUBMENU,
        R_FINDITEM_CONTACTS_AIW_INTEREST );
#endif // RD_VIRTUAL_PHONEBOOK

    iDialData = CAiwDialDataExt::NewL();

    iHelpFeatureSupported =
        FeatureManager::FeatureSupported( KFeatureIdHelp );

    iAudioMessagingFeatureSupported =
        FeatureManager::FeatureSupported( KFeatureIdAudioMessaging );

    iMMSFeatureSupported =
        FeatureManager::FeatureSupported( KFeatureIdMMS );

    iEmailOverSmsFeatureSupported =
        FeatureManager::FeatureSupported( KFeatureIdEmailOverSms );

    iEmailUiFeatureSupported =
        FeatureManager::FeatureSupported( KFeatureIdEmailUi );

    iFindItemVoIPExtension = CFindItemVoIPExtension::NewL();
    
    iExtension = CItemFinderExtension::NewL();
    }


// -----------------------------------------------------------------------------
// CFindItemDialog::DoCopyToClipboardL
//  Copies the selected item to EPOC clipboard
// -----------------------------------------------------------------------------
//
void CFindItemDialog::CopyToClipboardL()
    {
    __ASSERT_DEBUG( iEdwin->SelectionLength() > 0, Panic( ENoItemSelected ) );

    // CEikEdwin::ClipboardL cannot be used due to the underlining.
    TCursorSelection selection = iEdwin->Selection();
    TInt length = selection.Length();
    HBufC* number = HBufC::NewLC( length );
    TPtr numberPtr = number->Des();
    numberPtr.Append( iPlainText.Mid( selection.LowerPos(), length ) );
    CPlainText* plainText =
        CPlainText::NewL( CPlainText::ESegmentedStorage, length );
    CleanupStack::PushL( plainText );
    plainText->InsertL( 0, *number );

    CClipboard* cb = CClipboard::NewForWritingLC( iCoeEnv->FsSession() );
    plainText->CopyToStoreL( cb->Store(),cb->StreamDictionary(), 0, length );
    cb->CommitL();
    CleanupStack::PopAndDestroy(3); // number, plainText, cb

    CAknNoteDialog* dlg = new (ELeave) CAknNoteDialog();
    dlg->SetTimeout(CAknNoteDialog::EShortTimeout);
    dlg->SetTone(CAknNoteDialog::ENoTone);
    dlg->ExecuteLD( R_AVKON_NOTE_CONF_COPIED );
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::CreateContactCardL
//  Creates a contact card from selected item
// -----------------------------------------------------------------------------
//
void CFindItemDialog::CreateContactCardL( TInt aCommandId )
    {
    __ASSERT_DEBUG( iEdwin->SelectionLength() > 0, Panic( ENoItemSelected ) );

    // Hide options menu if showing
    if ( CAknDialog::MenuShowing() )
        {
        CAknDialog::HideMenu();
        }

    CFindItemEngine::SFoundItem selecteditem;
    TBool founditem = iController->Item( selecteditem );

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
        if ( iFindItemVoIPExtension->IsVoIPSupported() &&
            iSearchCase == KSearchTelInternetNumber )
            {
            if ( fieldInfo->FieldId() == EPbkFieldIdVOIP ||
                ( fieldInfo->FieldId() == EPbkFieldIdEmailAddress &&
                founditem && selecteditem.iItemType ==
                    CFindItemEngine::EFindItemSearchMailAddressBin ) ||
                ( fieldInfo->IsPhoneNumberField() &&
                founditem && selecteditem.iItemType ==
                    CFindItemEngine::EFindItemSearchPhoneNumberBin ) )
                {
                fieldArray->AppendL( fieldInfo );
                }
            }
        else if ( iSearchCase & CFindItemEngine::EFindItemSearchPhoneNumberBin &&
            ( fieldInfo->IsPhoneNumberField() ||
                iFindItemVoIPExtension->IsVoIPSupported() &&
                fieldInfo->FieldId() == EPbkFieldIdVOIP ) )
            {
            fieldArray->AppendL( fieldInfo );
            }
        else if ( iSearchCase & CFindItemEngine::EFindItemSearchMailAddressBin &&
            ( fieldInfo->FieldId() ==  EPbkFieldIdEmailAddress ||
                iFindItemVoIPExtension->IsVoIPSupported() &&
                fieldInfo->FieldId() == EPbkFieldIdVOIP ) )
            {
            fieldArray->AppendL( fieldInfo );
            }
        else if ( iSearchCase & CFindItemEngine::EFindItemSearchURLBin &&
            fieldInfo->FieldId() == EPbkFieldIdURL )
            {
            fieldArray->AppendL( fieldInfo );
            }
        }
#endif // !RD_VIRTUAL_PHONEBOOK

    // Get the selected item
    TCursorSelection selection = iEdwin->Selection();
    HBufC* item = HBufC::NewLC( selection.Length() );
    TPtr itemDes = item->Des();
    itemDes.Append(
        iPlainText.Mid( selection.LowerPos(), selection.Length() ) );

    // Handle command
#ifndef RD_VIRTUAL_PHONEBOOK
    iPbkDataSave->HandleCommandL( aCommandId, *fieldArray, *item );
    CleanupStack::PopAndDestroy( 2 ); // fieldArray, item
#else // RD_VIRTUAL_PHONEBOOK
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
    switch( selecteditem.iItemType ) // Resolve type.
        {
        case CFindItemEngine::EFindItemSearchPhoneNumberBin:    // Phone number
            param.SetSemanticId( EGenericParamPhoneNumber );
            // convert phone number.
            CommonPhoneParser::ParsePhoneNumber(
                itemDes, CommonPhoneParser::EPhoneClientNumber );
            break;
        case CFindItemEngine::EFindItemSearchMailAddressBin:    // E-mail
            param.SetSemanticId( EGenericParamEmailAddress );
            break;
        case CFindItemEngine::EFindItemSearchURLBin:            // URL
        case CFindItemEngine::EFindItemSearchScheme:            // URI
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
        iExtension->CallBack() );
    CleanupStack::PopAndDestroy( 1 ); // item
#endif // !RD_VIRTUAL_PHONEBOOK
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::SendMessageL
//  Sends message (SMS, MMS or E-mail) to selected item
// -----------------------------------------------------------------------------
//
void CFindItemDialog::SendMessageL( const TUid aMtmUid )
    {
	
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::LaunchGenericUriL
//  Handles URIs launching. If parent application is Browser,
//  launches URLs to same Browser window. On other cases passes
//  URI to Schemehandler.
// -----------------------------------------------------------------------------
//
TBool CFindItemDialog::LaunchGenericUriL()
    {
    HideMenu();
    __ASSERT_DEBUG( iEdwin->SelectionLength() > 0, Panic( ENoItemSelected ) );

    TCursorSelection selection = iEdwin->Selection();

    HBufC* itemtext =
        HBufC::NewLC( selection.Length() + KHhttpAddress().Length() );
    TPtr itemtextPtr = itemtext->Des();
    itemtextPtr.Append(
        iPlainText.Mid( selection.LowerPos(), selection.Length() ) );

    TBool isUrl = EFalse;

    // Link is url, if it starts with "http"
    const TDesC& pref = itemtextPtr.Left( 4 );
    if ( pref.CompareF( KHhttpAddress().Left( 4 ) ) == 0 )
        {
        isUrl = ETrue;
        }

    // old url types need prefix in order to work w/ schemehandler
    if ( !( isUrl || pref.CompareF( KRtspUrlAddress().Left( 4 ) ) == 0 ) )
        {
        itemtextPtr.Insert( 0, KHhttpAddress );
        isUrl = ETrue;
        }

    TInt length = itemtextPtr.Length();

    // Get the current app's UID
    TUid appUid = iEikonEnv->EikAppUi()->Application()->AppDllUid();

    // If current app is Browser and we have URL, we open it to this same
    // Browser window
    if ( appUid == KWapUid && isUrl )
        {
        GoToUrlL( itemtextPtr );
        CleanupStack::PopAndDestroy(); // itemtext
        return ETrue;
        }
    // If current app is other than Browser, use schemehandler for launching
    // file

    CleanupStack::PopAndDestroy(); // itemtext
    return EFalse;
    }


// -----------------------------------------------------------------------------
// CCFindItemDialog::GoToUrlL
//  Goes to URL (selected item) using Browser
// -----------------------------------------------------------------------------
//
void CFindItemDialog::GoToUrlL( const TPtr& aItemtextPtr )
    {
    TInt paramLength = aItemtextPtr.Length();
    paramLength += 2; // 2 = length of the first parameter + space

    HBufC *parameters = HBufC::NewLC( paramLength );
    TPtr paramPtr = parameters->Des();
    paramPtr.Copy( KWmlBrowserParameter );
    paramPtr.Append( KSpace );
    paramPtr.Append( aItemtextPtr.Mid( 0, aItemtextPtr.Length() ) );

    TApaTaskList taskList( iEikonEnv->WsSession() );
    TApaTask task = taskList.FindApp( KWapUid );
    if ( task.Exists() )
        {
        HBufC8* param8 = HBufC8::NewLC( parameters->Length() );
        param8->Des().Append( *parameters );
        task.SendMessage( TUid::Uid( 0 ), *param8 ); // Uid is not used
        CleanupStack::PopAndDestroy(); // param8
        }
    else
        {
        // should not happen
        }

    CleanupStack::PopAndDestroy(); // parameters

    // Close Find Item dialog as it was launched from Browser
    TryExitL( EAknSoftkeyBack );
    }


// -----------------------------------------------------------------------------
// CFindItemDialog::AddToBookmarkL
//  Adds the selected item to bookmarks
// -----------------------------------------------------------------------------
//
void CFindItemDialog::AddToBookmarkL()
    {
    __ASSERT_DEBUG( iEdwin->SelectionLength() > 0, Panic( ENoItemSelected ) );

    // Read default name from resources
    HBufC* defaultName =
        iEikonEnv->AllocReadResourceLC( R_FINDITEM_DEFAULT_BOOKMARK_NAME );

    TBuf<KMaxBookmarkNameLength> retName;
    retName.Copy ( defaultName->Des() );
    CleanupStack::PopAndDestroy( ); //defaultName

    // Query bookmark name from user
    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( retName );
    dlg->SetMaxLength( KMaxBookmarkNameLength );
    if ( !dlg->ExecuteLD( R_FINDITEM_BOOKMARK_QUERY_DIALOG ) )
        {
        // User press cancel - do not add bookmark
        return;
        }
    
    TCursorSelection selection = iEdwin->Selection();
    
    HBufC* msgBuffer =
        iCoeEnv->AllocReadResourceLC( R_FINDITEM_BOOKMARK_SAVED );
    CAknConfirmationNote* note = new (ELeave)CAknConfirmationNote( ETrue );
    note->ExecuteLD( *msgBuffer );

    CleanupStack::PopAndDestroy();   // magBuffer
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::ProcessCommandL
//  Prosesses menu commands
// -----------------------------------------------------------------------------
//
EXPORT_C void CFindItemDialog::ProcessCommandL( TInt aCommandId )
    {
    CAknDialog::ProcessCommandL( aCommandId );
    switch (aCommandId)
        {
        // General cmds
        case EFindItemCmdNextItem:
            {
            iController->NextItemL();
            break;
            }
        case EFindItemCmdPrevItem:
            {
            iController->PrevItemL();
            break;
            }
        case EFindItemCmdExit:
            {
            HideMenu();
            STATIC_CAST( MEikCommandObserver*,
                iEikonEnv->EikAppUi())->ProcessCommandL( EAknCmdExit );
            return;
            }
        case EFindItemCmdCreateContactCardSub1:
        case EFindItemCmdCreateContactCardSub2:
        case EFindItemCmdCreateContactCardSub3:
            {
            CreateContactCardL( aCommandId );
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
        // Phone number cmds
        case EFindItemCmdCall:
            { // bit awkward but correct functionality provided.
            TKeyEvent keyEvent;
            keyEvent.iCode = EKeyPhoneSend;
            OfferKeyEventL( keyEvent, EEventKey );
            break;
            }
        // fix for FAMZ-7JVQ4Y
        case EFindItemSubMenuSend:
           {
           break;
           }
        case EFindItemCmdGoToUrl:
            {
            if ( LaunchGenericUriL() )
                {
                return;
                }
            break;
            }
        case EFindItemCmdAddToBookmark:
            {
            AddToBookmarkL();
            break;
            }
        case EAknCmdHelp:
            {
            if( iHelpFeatureSupported )
                {
                CArrayFixFlat<TCoeHelpContext>* helps = new ( ELeave ) CArrayFixFlat<TCoeHelpContext>( 1 );
                CleanupStack::PushL( helps );
                TCoeHelpContext helpContext;
                GetHelpContext( helpContext );
                helps->AppendL( helpContext );
                HlpLauncher::LaunchHelpApplicationL(
                    iEikonEnv->WsSession(),
                    helps );
                CleanupStack::Pop(helps);
                }
            break;
            }
        case EFindItemCmdCopy:
            {
            CopyToClipboardL();
            break;
            }
        // The command was not known, so lets offer it to AIWFW
        default:
            {
            if ( !iDialData )
                {
                break;
                }

            TInt aiwCmd = iServiceHandler->ServiceCmdByMenuCmd( aCommandId );

            // Calls via AIW
            if ( aiwCmd == KAiwCmdCall &&(
                iSearchCase & CFindItemEngine::EFindItemSearchPhoneNumberBin ||
                iFindItemVoIPExtension->VoIPProfilesExistL() &&
                ( iSearchCase & CFindItemEngine::EFindItemSearchMailAddressBin ||
                iSearchCase == KSearchTelInternetNumber ) ) )
                {
                FormatDialDataL( aCommandId );

                CAiwGenericParamList& paramList =
                    iServiceHandler->InParamListL();

                iDialData->FillInParamListL( paramList );

                iServiceHandler->ExecuteMenuCmdL(
                    aCommandId,
                    paramList,
                    iServiceHandler->OutParamListL(),
                    0, // No options used.
                    0 ); // no dial results are wanted.
                }
#ifdef RD_VIRTUAL_PHONEBOOK
            // Contacts via AIW
            else if ( aiwCmd == KAiwCmdAssign )
                {
                CreateContactCardL( aCommandId );
                }
#endif // RD_VIRTUAL_PHONEBOOK
            break;
            }
        }
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::DynInitMenuPaneL
//  Initializes items on the menu
// -----------------------------------------------------------------------------
//
EXPORT_C void CFindItemDialog::DynInitMenuPaneL(
    TInt aMenuId,
    CEikMenuPane* aMenuPane )
    {
    if ( iServiceHandler->HandleSubmenuL( *aMenuPane ) )
        {
        return;
        }

    CFindItemEngine::SFoundItem item;
    TBool founditem = iController->Item( item );

    if ( aMenuId == R_FINDITEM_CALLUI_AIW_SUBMENU )
        {
        if ( iFindItemVoIPExtension->IsVoIPSupported() &&
            ( iSearchCase ==
                CFindItemEngine::EFindItemSearchMailAddressBin ||
            ( iSearchCase == KSearchTelInternetNumber &&
            founditem && item.iItemType ==
                CFindItemEngine::EFindItemSearchMailAddressBin ) ) )
            {
            CAiwGenericParamList* inList = CAiwGenericParamList::NewLC();

            // SIP Address
            TAiwGenericParam param( EGenericParamSIPAddress );
            inList->AppendL( param );

            iServiceHandler->InitializeMenuPaneL(
                *aMenuPane,
                aMenuId,
                EFindMenuPlaceHolderCallUI,
                *inList );

            CleanupStack::PopAndDestroy(); // genericParamList
            }
        else
            {
            iServiceHandler->InitializeMenuPaneL(
                *aMenuPane,
                aMenuId,
                EFindMenuPlaceHolderCallUI,
                iServiceHandler->InParamListL() );
            }
        return;
        }

#ifdef RD_VIRTUAL_PHONEBOOK
    if ( aMenuId == R_FINDITEM_CONTACTS_AIW_SUBMENU )
        {
        using namespace AiwContactAssign;

        CAiwGenericParamList& inList = iServiceHandler->InParamListL();

        // Contact Assign Data
        TAiwGenericParam param( EGenericParamContactAssignData );
        TAiwSingleContactAssignDataV1 assignData;
        assignData.SetFlags( 0 ); // Reset
        param.Value().Set( TAiwSingleContactAssignDataV1Pckg( assignData ) );
        inList.AppendL( param );

        // Type Phone Number
        param.Reset();
        param.SetSemanticId( EGenericParamPhoneNumber );
        inList.AppendL( param );

        iServiceHandler->InitializeMenuPaneL(
            *aMenuPane,
            aMenuId,
            EFindMenuCmdLast,
            inList );

        return;
        }
#endif  // RD_VIRTUAL_PHONEBOOK

    if (aMenuId == R_AVKON_FORM_MENUPANE)
        {
        TInt resource = 0;

        if ( iSearchCase == KSearchTelInternetNumber )
            {
            resource = R_FINDITEM_TELINTERNETNUMBER_MENU;
            }
        else if ( iSearchCase & CFindItemEngine::EFindItemSearchURLBin )
            {
            resource = R_FINDITEM_URL_ADDRESS_MENU;
            }
        else if ( iSearchCase & CFindItemEngine::EFindItemSearchMailAddressBin )
            {
            resource = R_FINDITEM_MAIL_ADDRESS_MENU;
            }
        else if ( iSearchCase & CFindItemEngine::EFindItemSearchPhoneNumberBin )
            {
            resource = R_FINDITEM_PHONENUMBER_MENU;
            }
        else
           {
           ;
           }

        aMenuPane->AddMenuItemsL( resource, EAknFormMaxDefault - 1, ETrue );

        if ( iSearchCase == KSearchTelInternetNumber &&
            iFindItemVoIPExtension->VoIPProfilesExistL() ||
            iSearchCase == KSearchTelInternetNumber &&
            !iFindItemVoIPExtension->VoIPProfilesExistL() &&
            founditem &&
            item.iItemType ==
                CFindItemEngine::EFindItemSearchPhoneNumberBin ||
            iSearchCase & CFindItemEngine::EFindItemSearchMailAddressBin &&
            iFindItemVoIPExtension->VoIPProfilesExistL() )
            {
            aMenuPane->SetItemDimmed( EFindItemCmdCall, ETrue );
            aMenuPane->AddMenuItemsL(
                R_FINDITEM_CALLUI_AIW_ITEM,
                EFindItemCmdCall);
            }
        else if ( iSearchCase == KSearchTelInternetNumber &&
            !iFindItemVoIPExtension->VoIPProfilesExistL() ||
            iSearchCase & CFindItemEngine::EFindItemSearchMailAddressBin &&
            !iFindItemVoIPExtension->VoIPProfilesExistL() )
            {
            aMenuPane->DeleteMenuItem(EFindItemCmdCall);
            }
        else if (
            iSearchCase & CFindItemEngine::EFindItemSearchPhoneNumberBin &&
            !iHideCallMenu )
            {
            aMenuPane->SetItemDimmed( EFindItemCmdCall, ETrue );
            aMenuPane->AddMenuItemsL(
                R_FINDITEM_CALLUI_AIW_ITEM,
                EFindItemCmdCall );
            }

        aMenuPane->DeleteMenuItem( EAknFormCmdEdit );
        aMenuPane->DeleteMenuItem( EAknFormCmdAdd );
        aMenuPane->DeleteMenuItem( EAknFormCmdSave );
        aMenuPane->DeleteMenuItem( EAknFormCmdLabel );
        aMenuPane->DeleteMenuItem( EAknFormCmdDelete );

#ifndef RD_VIRTUAL_PHONEBOOK
        iPbkDataSave->AddMenuItemsL(
            aMenuPane,
            EFindItemCmdCreateContactCard );
#else
        aMenuPane->SetItemDimmed( EFindItemCmdCreateContactCard, ETrue );
        aMenuPane->AddMenuItemsL(
            R_FINDITEM_CONTACTS_AIW_ITEM,
            EFindItemCmdCreateContactCard );
#endif // !RD_VIRTUAL_PHONEBOOK

        // Delete next/prev item items from menu if a last/next
        // item is currently selected (or if sensitive menu)
        if ( iController->FirstItem() || iIsSensitiveMenu )
            {
            aMenuPane->DeleteMenuItem( EFindItemCmdPrevItem );
            }
        if ( iController->LastItem() || iIsSensitiveMenu )
            {
            aMenuPane->DeleteMenuItem( EFindItemCmdNextItem );
            }

        if ( iIsSensitiveMenu )
            {
            aMenuPane->DeleteMenuItem( EFindItemCmdExit );
            if( iHelpFeatureSupported )
                {
                aMenuPane->DeleteMenuItem( EAknCmdHelp );
                }
            iIsSensitiveMenu = EFalse;
            }

        // No send message submenu for e-mail.
        if ( iSearchCase == CFindItemEngine::EFindItemSearchMailAddressBin &&
            !iEmailOverSmsFeatureSupported && !iEmailUiFeatureSupported &&
            !iMMSFeatureSupported )
            {
            aMenuPane->SetItemDimmed( EFindItemSubMenuSend, ETrue );
            }
        }
    else
        {
        // we are in Create contact submenu
        // this does nothing if we're not, so this is safe
#ifndef RD_VIRTUAL_PHONEBOOK
        iPbkDataSave->DynInitMenuPaneL( aMenuId, aMenuPane );
#endif // !RD_VIRTUAL_PHONEBOOK
        }
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::OfferKeyEventL
//  Handles key events
// -----------------------------------------------------------------------------
//
EXPORT_C TKeyResponse CFindItemDialog::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    // Only interested in standard key events
    if ( aType != EEventKey )
        {
        return EKeyWasNotConsumed;
        }

    // If a menu is showing offer key events to it.
    if ( CAknDialog::MenuShowing() )
        {
        return CAknDialog::OfferKeyEventL( aKeyEvent, aType );
        }

    TInt code = aKeyEvent.iCode;
    TBool founditem = EFalse;

    switch ( code )
        {
        case EKeyRightArrow:
            iController->NextItemL();
            break;
        case EKeyDownArrow:
            iController->MoveDownL();
            break;
        case EKeyLeftArrow:
            iController->PrevItemL();
            break;
        case EKeyUpArrow:
            iController->MoveUpL();
            break;
        case EKeyOK:
        case EKeyEnter:
            iIsSensitiveMenu = ETrue;
            iMenuBar->SetMenuType(CEikMenuBar::EMenuContext);
            CAknDialog::DisplayMenuL();
            break;
        case EKeyPhoneSend:
            if ( !iDialData )
                {
                break;
                }

            CFindItemEngine::SFoundItem item;
            founditem = iController->Item( item );

            if ( iSearchCase ==
                    CFindItemEngine::EFindItemSearchPhoneNumberBin ||
                iFindItemVoIPExtension->VoIPProfilesExistL() &&
                ( iSearchCase ==
                    CFindItemEngine::EFindItemSearchMailAddressBin ||
                iSearchCase == KSearchTelInternetNumber ) ||
                iSearchCase == KSearchTelInternetNumber && founditem &&
                item.iItemType ==
                    CFindItemEngine::EFindItemSearchPhoneNumberBin )
                {
                FormatDialDataL( code );

                // Create Call W/O Menu
                CAiwGenericParamList& paramList =
                    iServiceHandler->InParamListL();
                
                if ( iFindItemVoIPExtension->VoIPProfilesExistL() &&
                    ( iSearchCase ==
                    CFindItemEngine::EFindItemSearchMailAddressBin ||
                    iSearchCase == KSearchTelInternetNumber ) )
                    {
                    //voip
                    iDialData->SetCallType( CAiwDialData::EAIWVoiP );    
                    }

                iDialData->FillInParamListL( paramList );

                iServiceHandler->ExecuteServiceCmdL(
                    KAiwCmdCall,
                    paramList,
                    iServiceHandler->OutParamListL(),
                    0, // No options used.
                    NULL ); // Dial results are not wanted.
                }
            break;
        default:
            return CAknDialog::OfferKeyEventL( aKeyEvent, aType );
        }
    return EKeyWasConsumed;
    }


// -----------------------------------------------------------------------------
// CFindItemDialog::OkToExitL
// called by framework when the OK button is pressed
// -----------------------------------------------------------------------------
//
TBool CFindItemDialog::OkToExitL( TInt aButtonId )
{
    if ( aButtonId == EAknSoftkeyOptions )
        {
        // Show the options menu
        iIsSensitiveMenu = EFalse;
        iMenuBar->SetMenuType(CEikMenuBar::EMenuOptions);
        return CAknDialog::OkToExitL( aButtonId );
        }
    if ( aButtonId == EAknSoftkeyContextOptions )
        {
        // Show context sensitive menu. In this case it would
        // be normal menu with some items removed
        iIsSensitiveMenu = ETrue;
        iMenuBar->SetMenuType(CEikMenuBar::EMenuContext);
        return CAknDialog::OkToExitL( EAknSoftkeyOptions );
        }
    if ( aButtonId == EAknSoftkeyBack || aButtonId == EAknSoftkeyExit )
        {
        // Close Find Item
        return ETrue;
        }
    return EFalse;
}

// -----------------------------------------------------------------------------
// CFindItemDialog::PreLayoutDynInitL
// called by framework before dialog is shown
// -----------------------------------------------------------------------------
//
void CFindItemDialog::PreLayoutDynInitL()
    {
    // Fetch a pointer to richtext editor
    iEdwinContainer = STATIC_CAST(
        CRichTextEditorContainer*, Control( EFindItemRichTxtEditorContainer ) );
    iEdwin = iEdwinContainer->iEditor;

    // Create a controller, and thus create an engine and
    // execute the search algorithm
    iController =
        CFindItemController::NewL(
            this, iEdwin->RichText(), iPlainText, iSearchCase );

    iItemArrayForScrollBar = new (ELeave) CArrayFixFlat<TInt>( 2 );
    iController->FillScrollBarItemsArrayL( iItemArrayForScrollBar );
    CreateScrollBarFrameL();
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::PostLayoutDynInitL
//  called by framework before dialog is shown (don't affect layout)
// -----------------------------------------------------------------------------
//
void CFindItemDialog::PostLayoutDynInitL()
    {
    if ( !( iEdwin->TextView() ) )
        {
        // There was no memory to create a text view.
        // CRichTextEditor doesn't leave if that happens? so let's leave here.
        User::Leave( KErrNoMemory );
        }

    CFindItemEngine::SFoundItem item;
    TBool anyFound = iController->Item( item );

    // Skin Support
    iBgContext =
        CAknsBasicBackgroundControlContext::NewL(
            KAknsIIDQsnBgAreaMain, Rect(), EFalse );

    // Editor
    iEdwin->SetTextL( &iPlainText );
    
    // change the color of the text according to the skin color
    TRgb color;
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TInt error = AknsUtils::GetCachedColor(skin, color, KAknsIIDQsnTextColors, 
    												EAknsCIQsnTextColorsCG6 );
    if(error==KErrNone)
    	{
      	TCharFormat charFormat;
    	TCharFormatMask charFormatMask;
    	charFormatMask.SetAttrib(EAttColor);
    	charFormat.iFontPresentation.iTextColor = color; 
    
    	CRichText * richText = NULL;
    	richText = iEdwin->RichText();
    	if( NULL!=richText )
    		{
    		TInt length = richText->DocumentLength();
    		length++;
    		// apply the color to text
    		TRAP_IGNORE(richText->ApplyCharFormatL( charFormat, charFormatMask, 0, length ));
    		}
       	}
    if ( anyFound )
        {
        // Insert paragraphs inside the text if needed, i.e. if text is
        // bandformatted and there's not enough paragraphs already. The
        // paragraphs needs to be inserted so that the length of the document
        // won't change, i.e. replace ". " with "." + paragraph
        TInt docLength = iEdwin->RichText()->DocumentLength();
        if ( docLength >= KFullFormattingUpperThreshold &&
             iEdwin->RichText()->ParagraphCount() <=
                ( docLength / KLengthOfRecommendedParagraph ) )
            {
            TInt i = 1;
            while ( ( KLengthOfRecommendedParagraph * i ) <
                    iPlainText.Length() )
                {
                TInt endOfSentence =
                    iPlainText.Right(
                        iPlainText.Length() -
                            KLengthOfRecommendedParagraph * i ).FindF(
                                KPeriodAndSpace );
                if ( endOfSentence != KErrNotFound )
                    {
                    iEdwin->RichText()->DeleteL(
                        endOfSentence + 1 +
                            ( KLengthOfRecommendedParagraph * i ), 1 );
                    iEdwin->RichText()->InsertL(
                        endOfSentence + 1 +
                            ( KLengthOfRecommendedParagraph * i ),
                        CEditableText::EParagraphDelimiter );
                    }
                i++;
                }
            }

        iController->MarkFoundItemsL();
        iEdwin->NotifyNewFormatL();

        // 'Cheating' - AllowBlankSpace flag doesn't work when scrolling pages,
        // so insert paragraph delimiters
        for ( TInt i = 0; i < iRows; i++ )
            {
            TRAP_IGNORE( iEdwin->RichText()->InsertL(
                iEdwin->RichText()->DocumentLength(),
                CEditableText::EParagraphDelimiter ) );
            }

        }

    iEikonEnv->EikAppUi()->AddToStackL( this, ECoeStackPriorityDialog );

    // Observe pointer events
    CEikCaptionedControl* capCC = Line( EFindItemRichTxtEditorContainer );
    capCC->SetPointerEventObserver( this );

    iTappingOffset = iEdwin->Rect().iTl - Rect().iTl;
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::SelectionChangedL
//  Selects the given item.
//  Gets called by controller via CFindItemDialogCallBack.
// -----------------------------------------------------------------------------
//
void CFindItemDialog::SelectionChangedL(
    const CFindItemEngine::SFoundItem& aItem )
    {
    iEdwin->SetSelectionL( aItem.iStartPos, aItem.iLength + aItem.iStartPos );
    UpdateScrollIndicatorL();
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::SelectionChangedL
//  Selects the given item and scrolls the edit window.
//  Gets called by controller via CFindItemDialogCallBack.
// -----------------------------------------------------------------------------
//
void CFindItemDialog::SelectionChangedL(
    const CFindItemEngine::SFoundItem& aItem,
    const TBool aNext )
    {
    const TInt startPos = aItem.iStartPos;
    const TInt endPos = aItem.iStartPos + aItem.iLength;
    TPoint dummy;
    __ASSERT_DEBUG(
        endPos <= iEdwin->TextLength(), Panic( EItemOutOfDocumentRange ) );

    // Scroll the display if needed
    if ( aNext )
        {
        while ( !( iEdwin->TextLayout()->PosInBand( startPos, dummy ) ) )
            {
            // Unselect text if display needs to be scrolled
            iEdwin->ClearSelectionL();
            // Scroll page down
            iEdwin->MoveDisplayL( TCursorPosition::EFPageDown );
            }
        }
    else
        {
        while ( !( iEdwin->TextLayout()->PosInBand( startPos, dummy ) ) )
            {
            // Unselect text if display needs to be scrolled
            iEdwin->ClearSelectionL();
            // Scroll page down
            iEdwin->MoveDisplayL( TCursorPosition::EFPageUp );
            }
        }

    // First see if the string fits to the band and then make the selection
    if( iEdwin->TextLayout()->PosInBand( startPos, dummy ) &&
       !iEdwin->TextLayout()->PosInBand( endPos, dummy ) )
        iEdwin->SetSelectionL( startPos, endPos ); // startPos first so that we
                                                   // can see the start of the
                                                   // string
    else
        iEdwin->SetSelectionL( endPos, startPos ); // endPos first because
                                                   // otherwise selection will
                                                   // change the first
                                                   // visible line.

    // Set up the navipane
    // To avoid flickering a new label has to be
    // pushed before deleting the old one
    //CAknNavigationDecorator* oldDecorator = iNaviDecorator;
    //CleanupStack::PushL( oldDecorator );
    //iNaviDecorator = NULL;
    UpdateNaviPaneL();
    //CleanupStack::PopAndDestroy(); // oldDecorator
    //oldDecorator = NULL;
    UpdateScrollIndicatorL();
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::AtSameLine
//  Returns whether items are at the same line
// -----------------------------------------------------------------------------
//
TBool CFindItemDialog::AtSameLine( const TInt& aItem1, const TInt& aItem2 )
    {
    TInt error = KErrNone;    
    // DocPosToXyPosL can't leave, because of the flag EFWholeTBoxesOnly see SDK!    
    TBool pos1 = EFalse;
    TPoint point1;
    TRAP( error, pos1 = iEdwin->TextLayout()->DocPosToXyPosL( 
        aItem1, point1, CLayoutData::EFWholeTBoxesOnly ) );
    if ( error != KErrNone )
        {
        return EFalse;
        }
    TBool pos2 = EFalse;        
    TPoint point2;
    TRAP( error, pos2 = iEdwin->TextLayout()->DocPosToXyPosL( 
        aItem2, point2, CLayoutData::EFWholeTBoxesOnly ) );
    if ( error != KErrNone )
        {
        return EFalse;
        }    
    if ( !pos1 || !pos2 || point1.iY != point2.iY )
        {
        return EFalse;
        }
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::ExecuteLD
//  Calls CAknDialog's  ExecuteLD() with correct resourceId
// -----------------------------------------------------------------------------
//

EXPORT_C TInt CFindItemDialog::ExecuteLD()
    {
    return CAknDialog::ExecuteLD( R_FINDITEM_DIALOG );
    }


// -----------------------------------------------------------------------------
// CFindItemDialog::CreateScrollBarFrameL
//  Creates the scrollbarframe
// -----------------------------------------------------------------------------
//
void CFindItemDialog::CreateScrollBarFrameL()
    {
    iSBFrame = new(ELeave) CEikScrollBarFrame( this, NULL, ETrue );

    // Check which type of scrollbar is to be shown
    if ( AknLayoutUtils::DefaultScrollBarType( iAvkonAppUi ) ==
            CEikScrollBarFrame::EDoubleSpan )
        {
        // For EDoubleSpan type scrollbar

         // window owning scrollbar
        iSBFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse, ETrue, EFalse );

        iSBFrame->SetTypeOfVScrollBar( CEikScrollBarFrame::EDoubleSpan );
        }
    else
        {
        // For EArrowHead type scrollbar
        iSBFrame->SetTypeOfVScrollBar( CEikScrollBarFrame::EArrowHead );
        }

    iSBFrame->SetScrollBarVisibilityL(
        CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );

    iSBFrame->SetScrollBarFrameObserver( this );

    iThumbPos = 0;
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::ActivateL
//  Initializes and activates the dialog.
// -----------------------------------------------------------------------------
//
void CFindItemDialog::ActivateL()
    {
    CFindItemEngine::SFoundItem item;
    TBool anyFound = iController->Item( item );

    if ( anyFound )
        {
        // These has to be done after the CAknDialog::ExecuteLD is called
        CAknDialog::ActivateL();

        // set up a new title
        TInt resource = 0;

        if ( iSearchCase == KSearchTelInternetNumber )
            {
            resource = R_FINDITEM_TITLE_TELINTERNET;
            }
        else if ( iSearchCase & CFindItemEngine::EFindItemSearchURLBin )
            {
            resource = R_FINDITEM_TITLE_URL;
            }
        else if ( iSearchCase & CFindItemEngine::EFindItemSearchMailAddressBin )
            {
            resource = R_FINDITEM_TITLE_MAIL;
            }
        else if ( iSearchCase & CFindItemEngine::EFindItemSearchPhoneNumberBin )
            {
            resource = R_FINDITEM_TITLE_PHONE;
            }
        else
          {
          __ASSERT_ALWAYS( 0, Panic( ENoSearchCase ) );
          return;
          }

        iTitleText = iEikonEnv->AllocReadResourceL( resource );

        // Set the correct titlepane text
        if ( iTitleText )
            {
            iTitlePane->SetTextL( iTitleText->Des() );
            }

        // Set up NaviPane ( if items were found )
        if ( iController->ItemCount() >= 1 )
            {
            if ( iNaviDecorator )
                {
                delete iNaviDecorator;
                iNaviDecorator = NULL;
                }
            UpdateNaviPaneL();
            }

        UpdateScrollIndicatorL();

        iEdwin->TextView()->SetSelectionVisibilityL( ETrue );
        iEdwin->SetSelectionL( item.iStartPos, item.iLength + item.iStartPos );
        }
    else
        {// Let's show a information note if no items were found
        HBufC* infoNote =
            iEikonEnv->AllocReadResourceLC(
                R_FINDITEM_NO_ITEMS_FOUND_NOTE_MSG );
        CAknInformationNote* note = new (ELeave) CAknInformationNote( ETrue );
        note->ExecuteLD( *infoNote );
        CleanupStack::PopAndDestroy(); // infoNote

        MakeVisible( EFalse );
        CEikButtonGroupContainer* cba = CEikButtonGroupContainer::Current();
        if( cba )
            {
            // To avoid user press "option" while dialog is closing
            // TSW error: EBYU-7QWC37
            cba->SetCommandSetL( R_AVKON_SOFTKEYS_EMPTY );  
            }
        
        delete iIdle;
        iIdle = 0;
        iIdle = CIdle::NewL( CActive::EPriorityIdle );
        iIdle->Start( TCallBack( DeleteMe, this ) );
        }

    }

void CFindItemDialog::DeleteMeL()
    {
    TryExitL( EAknSoftkeyBack );
    }

TInt CFindItemDialog::DeleteMe( TAny* aThis )
    {
    TRAPD( err, ( (CFindItemDialog*)aThis )->DeleteMeL() );
    return err;
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::UpdateScrollIndicatorL
//  Updates the scrollindicator
// -----------------------------------------------------------------------------
//
void CFindItemDialog::UpdateScrollIndicatorL()
    {
    if ( !iSBFrame )
        {
        return;
        }

    TEikScrollBarModel hSbarModel;
    TEikScrollBarModel vSbarModel;

    // Count scrollbar position
    TInt position = iController->Position();

    TInt i = 0;
    while ( i < iItemArrayForScrollBar->Count() &&
        position >= iItemArrayForScrollBar->At( i ) )
        {
        i++;
        }

    // If text is longer than KFullFormattingUpperThreshold (=2000) chars
    // it's impossible to count lines instead of items. That's why
    // for the first and last item, thumbposition needs to be added "manually".
    if ( iPlainText.Length() >= KFullFormattingUpperThreshold )
        {
        if ( iController->IsAtSameLineAsFirstItem() )
            {
            i = 0;
            }
        else if ( iController->IsAtSameLineAsLastItem() )
            {
            i = iItemArrayForScrollBar->Count() + 1;
            }
        }

    vSbarModel.iThumbPosition = i;
    vSbarModel.iScrollSpan= iItemArrayForScrollBar->Count() + 1;
    vSbarModel.iThumbSpan = 1;

    TEikScrollBarFrameLayout layout;
    if ( iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan )
        {
        // For EDoubleSpan type scrollbar
        if ( vSbarModel.iThumbPosition + vSbarModel.iThumbSpan >
                vSbarModel.iScrollSpan )
            {
            // Not let scrollbar values overflow
            vSbarModel.iThumbPosition =
                vSbarModel.iScrollSpan - vSbarModel.iThumbSpan;
            }
        TAknDoubleSpanScrollBarModel hDsSbarModel( hSbarModel );
        TAknDoubleSpanScrollBarModel vDsSbarModel( vSbarModel );
        TRect rect( Position(), Rect().Size() );        
        ButtonGroupContainer().ReduceRect( rect );        
        rect.Move( -Position() );
        layout.iTilingMode = TEikScrollBarFrameLayout::EInclusiveRectConstant;
        iSBFrame->TileL( &hDsSbarModel, &vDsSbarModel, rect, rect, layout );
        iSBFrame->SetVFocusPosToThumbPos( vDsSbarModel.FocusPosition() );
        }
    else
        {
        // For EArrowHead type scrollbar
        TRect rect( Rect() );
        iSBFrame->TileL( &hSbarModel, &vSbarModel, rect, rect, layout );
        iSBFrame->SetVFocusPosToThumbPos( vSbarModel.iThumbPosition );
        }

    iThumbPos = iSBFrame->VerticalScrollBar()->ThumbPosition();
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::UpdateNaviPaneL
//  Updates the Navipane
// -----------------------------------------------------------------------------
//
void CFindItemDialog::UpdateNaviPaneL()
    {
    TBuf<16> naviText;
    naviText.Format(
        KPosIndicator, iController->Position() + 1, iController->ItemCount() );

    if(NULL == iNaviDecorator)
    	{
    	iNaviDecorator = iNaviPane->CreateNavigationLabelL( naviText );
       	iNaviDecorator->SetNaviDecoratorObserver( this );  
       	iNaviDecorator->MakeScrollButtonVisible( ETrue );
       	}
    else
    	{
    	// Change the label on Nave pane control...
    	CAknNaviLabel * label =( CAknNaviLabel* )iNaviDecorator->DecoratedControl();
    	label->SetTextL(naviText);
    	}

    // Dimm arrows if needed
    if ( iController->LastItem() )
        {
        iNaviDecorator->SetScrollButtonDimmed(
            CAknNavigationDecorator::ERightButton, ETrue);
        }
    else
        {
        iNaviDecorator->SetScrollButtonDimmed(
            CAknNavigationDecorator::ERightButton, EFalse );
        }
    if ( iController->FirstItem() )
        {
        iNaviDecorator->SetScrollButtonDimmed(
            CAknNavigationDecorator::ELeftButton, ETrue );
        }
    else
        {
        iNaviDecorator->SetScrollButtonDimmed(
            CAknNavigationDecorator::ELeftButton, EFalse );
        }
    iNaviPane->PushL( *iNaviDecorator );
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::GetHelpContext
// This function is called when Help application is launched.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CFindItemDialog::GetHelpContext(
    TCoeHelpContext& aContext ) const
    {
    if( iHelpFeatureSupported )
        {
        aContext.iMajor = KCommonUIUid;
        aContext.iContext = KFIND_HLP;
        }
    }

void CFindItemDialog::FormatDialDataL( TInt aCommandId )
    {
    if ( !iDialData )
        {
        return;
        }

    __ASSERT_DEBUG( iEdwin->SelectionLength() > 0, Panic( ENoItemSelected ) );

    (void)aCommandId;
    
    TCursorSelection selection = iEdwin->Selection();
    HBufC* number = HBufC::NewLC( selection.Length() );
    TPtr numberPtr = number->Des();
    numberPtr.Append(
        iPlainText.Mid( selection.LowerPos(), selection.Length() ) );

    using namespace AIWDialDataExt;
    __ASSERT_ALWAYS(
        number->Length() <= KMaximumPhoneNumberLength, Panic( ETooLongItem ) );
    AknTextUtils::ConvertDigitsTo( numberPtr, EDigitTypeWestern );
    iDialData->SetPhoneNumberL( numberPtr );

    CleanupStack::PopAndDestroy(); // number;
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::CreateInternetCallL
// This function is called when Internet call command is pressed.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CFindItemDialog::CreateInternetCallL()
    {
    if ( iFindItemVoIPExtension->VoIPProfilesExistL() &&
       ( iSearchCase & CFindItemEngine::EFindItemSearchPhoneNumberBin ||
       iSearchCase & CFindItemEngine::EFindItemSearchMailAddressBin ||
       iSearchCase == KSearchTelInternetNumber ) )
        {
        if ( !iDialData )
            {
            return;
            }

        FormatDialDataL( EKeyPhoneSend ); //That number is formated correctly

        // Create Call W/O Menu
        CAiwGenericParamList& paramList = iServiceHandler->InParamListL();

        iDialData->FillInParamListL( paramList );

        iServiceHandler->ExecuteServiceCmdL(
            KAiwCmdCall,
            paramList,
            iServiceHandler->OutParamListL(),
            0, // No options used.
            NULL ); // Dial results are not wanted.
        }
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::IsSendKeyCallVoIP
// -----------------------------------------------------------------------------
//
TBool CFindItemDialog::IsSendKeyCallVoIP() const
    {
    return iFindItemVoIPExtension->IsPreferredTelephonyVoIP();
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::HandleResourceChange
//
// -----------------------------------------------------------------------------
void CFindItemDialog::HandleResourceChange( TInt aType )
    {
	//Update Horizantal Scroll bar color if skin changes
    if( aType == KAknsMessageSkinChange)
    	{
    	CAknScrollBar *scrollBar = iSBFrame->VerticalScrollBar();
    	scrollBar->HandleResourceChange(aType);
    	}
    CAknDialog::HandleResourceChange( aType );
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::SizeChanged
// -----------------------------------------------------------------------------
//
void CFindItemDialog::SizeChanged()
    {
    CAknDialog::SizeChanged();

    if ( AknLayoutUtils::ScalableLayoutInterfaceAvailable() )
        {
        using namespace AknLayoutScalable_Apps;
        iRows = list_single_mce_message_pane_ParamLimits().LastRow();
        }
    else
        {
        iRows = KCommonUiEdwinLines;
        }

    if ( iBgContext )
        {
        iBgContext->SetRect( Rect() );
        }

    iTappingOffset = iEdwin->Rect().iTl - Rect().iTl;

    TRAP_IGNORE( UpdateScrollIndicatorL() );
    }

// ----------------------------------------------------------------------------
// CFindItemDialog::CreateCustomControlL
// from MEikDialogPageObserver
// ----------------------------------------------------------------------------
//
SEikControlInfo CFindItemDialog::CreateCustomControlL( TInt aControlType )
    {
    SEikControlInfo info = { 0, 0, 0 };
    if ( aControlType == EFindItemCtRichTxtEditorContainer )
        {
        iEdwinContainer = new(ELeave)CRichTextEditorContainer;
        info.iControl = iEdwinContainer;
        }
    return info;
    }

// ----------------------------------------------------------------------------
// CFindItemDialog::SupplyMopObject
// ----------------------------------------------------------------------------
//
TTypeUid::Ptr CFindItemDialog::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == MAknsControlContext::ETypeId )
        {
        return MAknsControlContext::SupplyMopObject( aId, iBgContext );
        }
    return CAknDialog::MopSupplyObject( aId );
    }

// ----------------------------------------------------------------------------
// CFindItemDialog::FocusChanged
// ----------------------------------------------------------------------------
//
void CFindItemDialog::FocusChanged( TDrawNow /*aDrawNow*/ )
    {
    if ( IsFocused() && iTitleText )
        {
        TRAP_IGNORE( iTitlePane->SetTextL( iTitleText->Des() ) );
        }
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::PointerEvent
// -----------------------------------------------------------------------------
//
 bool CFindItemDialog::PointerEvent(
    CEikCaptionedControl* /*aControl*/,
    const TPointerEvent& aPointerEvent )
    {
    if ( AknLayoutUtils::PenEnabled() &&
        aPointerEvent.iType == TPointerEvent::EButton1Down )
        {
        TPoint tapPoint( aPointerEvent.iPosition - iTappingOffset );        
        TInt pos = 0;
        TInt len = iEdwin->TextLayout()->PosRangeInBand( pos );
        CFindItemEngine::SFoundItem item;
        TRect rect;
        TInt i = 0;
        while ( i < iController->ItemCount() ) // Check visible rects
            {
            if ( !iController->Item( i, item ) ) // Get item.
                {
                break; // Error: invalid item.
                };
            TInt end = item.iStartPos + item.iLength - 1;                            
            if ( end < pos )
                {
                i++;
                continue; // item not visible.                
                };                                            
            TInt start = item.iStartPos;
            if ( start >= ( pos + len ) )
                {
                break; // item not visible.
                }
            TInt lastLine = iEdwin->TextLayout()->GetLineNumber( end );
            TInt nextLine = 0;
            TInt lastPos = start;
            do // Check all rects of one item.
                {     
                TInt error = KErrNone;                   
                TRAP( error, rect = iEdwin->TextLayout()->GetLineRectL( start, end ) );
                if ( error == KErrNone )
                    {
                    if ( rect.Contains( tapPoint ) ) // Item rect tapped.
                        {                                    
                        TRAP( error, iController->TappedItemL( i ) ); // Change selection
                        if ( error != KErrNone )
                            {
                            return false; // Error: no selection made.
                            }
                        iIsSensitiveMenu = ETrue;
                        iMenuBar->SetMenuType( CEikMenuBar::EMenuContext );
                        TRAP_IGNORE( CAknDialog::DisplayMenuL() );
                        return false; // Hit, no further handling.
                        }
                    }                 
                else
                    {
                    return false; // Error: no rect.
                    }                                                    
                TPoint midPoint( rect.iBr.iX, ( rect.iBr.iY + rect.iTl.iY) / 2 );
                TRAP( error, lastPos = iEdwin->TextLayout()->XyPosToDocPosL( midPoint ) );            
                if ( error != KErrNone )
                    {
                    return false; // Error: no last pos.
                    }
                start = lastPos + 1;
                nextLine = iEdwin->TextLayout()->GetLineNumber( lastPos );                       
                } while ( nextLine != lastLine ); 
            i++;
            }
        }
    return false;   // No hit, no further handling.
    }

// -----------------------------------------------------------------------------
// CFindItemDialog::HandleScrollEventL
// -----------------------------------------------------------------------------
//
void CFindItemDialog::HandleScrollEventL(
    CEikScrollBar* aScrollBar,
    TEikScrollEvent aEventType )
    {
    TInt oldPos = iThumbPos;
    iThumbPos = aScrollBar->ThumbPosition();
    if ( iThumbPos == oldPos )
        {
        return; // not moved.
        }

    switch( aEventType )
        {
        case EEikScrollUp:
        case EEikScrollPageUp:
            iController->PrevItemL();
            break;
        case EEikScrollDown:
        case EEikScrollPageDown:
            iController->NextItemL();
            break;
        case EEikScrollThumbDragVert:
            if ( iThumbPos < oldPos )
                {
                iController->PrevItemL();
                }
            else
                {
                iController->NextItemL();
                }
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CFindItemDialog::HandleNaviDecoratorEventL
// ----------------------------------------------------------------------------
//
void CFindItemDialog::HandleNaviDecoratorEventL( TInt aEventID )
    {
    switch( aEventID )
        {
        case MAknNaviDecoratorObserver::EAknNaviDecoratorEventLeftTabArrow:
            iController->PrevItemL();    
            break;
        case MAknNaviDecoratorObserver::EAknNaviDecoratorEventRightTabArrow:
            iController->NextItemL();
            break;
        default:
            break;
        }    
    }   

//
// CONTAINER CLASS
//

// -----------------------------------------------------------------------------
// CRichTextEditorContainer:CRichTextEditorContainer
// -----------------------------------------------------------------------------
//
CRichTextEditorContainer::CRichTextEditorContainer()
    {
    }

// -----------------------------------------------------------------------------
// CRichTextEditorContainer:ConstructFromResourceL
// -----------------------------------------------------------------------------
//
void CRichTextEditorContainer::ConstructFromResourceL(
    TResourceReader& aReader )
    {
    iEditor = new (ELeave)CEikRichTextEditor;
    iEditor->SetContainerWindowL( *this );

    iEditor->ConstructFromResourceL( aReader );

    iBgContext =
        CAknsBasicBackgroundControlContext::NewL(
            KAknsIIDQsnBgAreaMain, Rect(), EFalse );
    if ( iBgContext )
        {
        iEditor->SetSkinBackgroundControlContextL( iBgContext );
        }
    }

// -----------------------------------------------------------------------------
// CRichTextEditorContainer::MinimumSize
// -----------------------------------------------------------------------------
//
TSize CRichTextEditorContainer::MinimumSize()
    {
    return iAvkonAppUi->ClientRect().Size();
    }

//------------------------------------------------------------------------------
// CRichTextEditorContainer::~CRichTextEditorContainer
// -----------------------------------------------------------------------------
//
CRichTextEditorContainer::~CRichTextEditorContainer()
    {
    delete iEditor;
    delete iBgContext;
    }

// -----------------------------------------------------------------------------
// CRichTextEditorContainer::SizeChanged
// -----------------------------------------------------------------------------
//
void CRichTextEditorContainer::SizeChanged()
    {
    if ( iEditor )
        {
        if ( AknLayoutUtils::ScalableLayoutInterfaceAvailable() )
            {
            using namespace AknLayoutScalable_Apps;
            iRows = list_single_mce_message_pane_ParamLimits().LastRow();
            }
        else
            {
            iRows = KCommonUiEdwinLines;
            }
        AknLayoutUtils::LayoutEdwin(
            iEditor,
            Rect(),
            AppLayout::Multiline_Message_writing_texts_Line_3( iRows ) );

        if ( iBgContext )
            {
            iBgContext->SetRect( Rect() );
            TRAP_IGNORE( iEditor->SetSkinBackgroundControlContextL( iBgContext ) );
            }
        // change the color of the text according to the skin color
        // this is needed if finditemdialog is active and theme is changed.
        TRgb color;
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TInt error = AknsUtils::GetCachedColor(skin, color, KAknsIIDQsnTextColors, 
        												EAknsCIQsnTextColorsCG6 );
        if(error==KErrNone)
        	{
           	TCharFormat charFormat;
        	TCharFormatMask charFormatMask;
        	charFormatMask.SetAttrib(EAttColor);
        	charFormat.iFontPresentation.iTextColor = color; 
     
        	CRichText * richText = NULL;
        	richText = iEditor->RichText();
        	if( NULL!=richText )
        		{
        		TInt length = richText->DocumentLength();
        		length++;
        		// apply the color to the text
        		TRAP_IGNORE(richText->ApplyCharFormatL( charFormat, charFormatMask, 0, length ));
        		}
           	}
        }
    }

// -----------------------------------------------------------------------------
// CRichTextEditorContainer::HandleResourceChange
//
// -----------------------------------------------------------------------------
void CRichTextEditorContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KAknsMessageSkinChange ||
        aType == KEikDynamicLayoutVariantSwitch )
        {
        SizeChanged();
        }
    }

// -----------------------------------------------------------------------------
// CRichTextEditorContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CRichTextEditorContainer::CountComponentControls() const
    {
    return iEditor ? 1 : 0;
    }

// -----------------------------------------------------------------------------
// CRichTextEditorContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CRichTextEditorContainer::ComponentControl(
    TInt /*aIndex*/ ) const
    {
    return iEditor;
    }

// -----------------------------------------------------------------------------
// CRichTextEditorContainer::Draw
// -----------------------------------------------------------------------------
//
void CRichTextEditorContainer::Draw( const TRect& /*aRect*/ ) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    CWindowGc& gc = SystemGc();
    if ( !AknsDrawUtils::Background( skin, cc, this, gc, Rect() ) )
        {
        gc.SetPenStyle( CGraphicsContext::ENullPen );
        gc.SetBrushColor( AKN_LAF_COLOR( 0 ) );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.DrawRect( Rect() );
        }
    }

// End of File
