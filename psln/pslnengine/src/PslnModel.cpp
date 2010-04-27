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
* Description:  Model class for Psln application.
*
*/


// Psln specific.
#include "PslnModel.h"
#include "PslnDiskUtil.h"
#include "PslnFeatures.h"
#include "PslnSkinEntry.h"
#include "PslnSkinStore.h"
#include "PslnEcomListener.h"
#include "PslnDebug.h"
#include "PslnConst.h"

// Wrapper for wallpaper utils.
#include "pslnwallpaperutilsloader.h"
#include "pslnbrowserlaunchloader.h"

// Resources
#include <psln.rsg>
#include <pslnskinnames.rsg>

// Generic
#include <StringLoader.h>
#include <data_caging_path_literals.hrh>
#include <f32file.h>
#include <hal.h>

// UI libraries
#include <AknsSkinUID.h>
#include <AknsConstants.h>
#include <eikenv.h>
#include <AknQueryDialog.h>

// Misc
#include <bautils.h>
#include <mmf/common/mmfcontrollerpluginresolver.h> // For CleanupResetAndDestroyPushL

// Central Repository and Publish&Subscribe keys.
#include <centralrepository.h>
#include <e32property.h>
#include "pslninternalcrkeys.h"
#include <AknSkinsInternalCRKeys.h>             // wallpaper, screen saver
#include <ScreensaverInternalCRKeys.h>          // KScreenSaverObject
#include <ScreensaverInternalPSKeys.h>          // KScreenSaverPreviewMode
#include <cenrepnotifyhandler.h>

// For enabling first component transition effect
#include <gfxtranseffect/gfxtranseffect.h>
#include <akntranseffect.h>
#ifdef RD_MULTIPLE_DRIVE
#include <driveinfo.h>
#endif //RD_MULTIPLE_DRIVE


// CONSTANTS
// Path of skin files.
_LIT( KPslnSkinNamesFile,"z:PslnSkinNames.rsc" );
// Preview mode activated.
const TInt KPslnActivatePreviewMode = 1;

// Default item index.
const TInt KPslnDefaultItemIndex = 0;

// Screen saver type: user defined text
const TInt KPslnSsText = 0;
// Screen saver type: date & time
const TInt KPslnSsDate = 1;
// Screen saver type: object
const TInt KPslnSsObject = 3;
// Screen saver type: none
const TInt KPslnSsNone = 4;

// Granularity of screen saver array.
const TInt KPslnSsArrayGranularity = 5;
// Length of drive number descriptor.
const TInt KPslnDriveNumberLength = 2;
// Free RAM required when activating transition effects.
const TInt KPslnTransitionEffectRAMThreshold = 2000000;
// Maximum of text length in text screensaver for APAC.
// For western variant, value is taken directly from resources.
const TInt KPslnSsTextDialogAPACMaxLength = 7;
// Path to wallpaper utils.
_LIT( KPslnWallpaperUtilsLoaderName, 
     "\\system\\libs\\PslnWallpaperUtilsLoader.dll");
_LIT( KPslnBrowserLaunchLoaderName, 
     "\\system\\libs\\PslnBrowserLaunchLoader.dll");
// Screen saver UID is stored like [ss_uid]. This is the end mark.
_LIT( KPslnScreenSaverUidEndMark, "]" );

// CLASS DECLARATIONS

class CPslnActivationGuard : public CBase
    {
    public:
        virtual ~CPslnActivationGuard()
            {
            PSLN_TRACE_DEBUG("CPslnActivationGuard::destructor");
            iModel->SkinSrvSession().EnableSkinChangeNotify();
            }

        static CPslnActivationGuard* NewL( CPslnModel* aModel )
            {
            PSLN_TRACE_DEBUG("CPslnActivationGuard::NewL");
            CPslnActivationGuard* self = new (ELeave) CPslnActivationGuard();
            self->iModel = aModel;
            PSLN_TRACE_DEBUG("CPslnActivationGuard DisableSkinChangeNotify");
            aModel->SkinSrvSession().DisableSkinChangeNotify();
            return self;
            }

    private:
        CPslnModel* iModel;
    };

// TYPE DEFINITIONS
// Wallpaper Utils entry.
typedef TAny* (*NewWallpaperUtilsL)();

// Browser Launcher entry.
typedef TAny* (*NewBrowserLauncherL)();


// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CPslnModel* CPslnModel::NewL( MAknsSkinChangeObserver* aObserver )
    {
    PSLN_TRACE_DEBUG("CPslnModel::NewL");
    CPslnModel* self = new(ELeave) CPslnModel;

    CleanupStack::PushL( self );
    self->ConstructL( aObserver );
    CleanupStack::Pop( self );

    PSLN_TRACE_DEBUG("CPslnModel::NewL OK");
    return self;
    }

// -----------------------------------------------------------------------------
// Two-phased constructor. Simpler version for PslnFramework use.
// Deprecated.
// -----------------------------------------------------------------------------
//
EXPORT_C CPslnModel* CPslnModel::NewL()
    {
    CPslnModel* self = new(ELeave) CPslnModel;
    return self;
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
EXPORT_C CPslnModel::~CPslnModel()
    {
    PSLN_TRACE_DEBUG("CPslnModel::destructor");

    delete iSkinsRepository;
    delete iScreenSaverRepository;
    iSkinSrvSession.Close();

    while( iSkinNames.Count() )
        {
        delete iSkinNames[0].iListName;
        delete iSkinNames[0].iTitleName;
        iSkinNames.Remove(0);
        }
    iSkinNames.Close();

    delete iScreensaverFilenameArr;
    delete iScreensaverNameArr;
    iScreensaverCapsArr.Reset();

    delete iSkinStore;
    if( iVisibleSkinArr )
        {
        iVisibleSkinArr->ResetAndDestroy();
        delete iVisibleSkinArr;
        }
    delete iScreenSaverInfo;

    delete iWallpaperSetter;
    if( iInternalState.IsSet( EPslnModelStateWallpaperDllLoaded  ) )
        {
        iWallpaperDll.Close();
        }

    delete iBrowserLauncher;
    if( iInternalState.IsSet( EPslnModelStateBrowserLaunchDllLoaded ) )
        {
        iBrowserLaunchDll.Close();
        }

    // If client is bad-behaving and has not cancelled listening, 
    // cancel itself.
    if ( iScreenSaverListener )
        {
        if ( iScreenSaverListener->IsActive() )
            {
            iScreenSaverListener->Cancel();
            }
        delete iScreenSaverListener;
        // NUllified here, just in case if client later decides to try and
        // destroy this.
        iScreenSaverListener = NULL;
        }
        
    if(iThemesAppCenRepNotifyHandler)
        {
        iThemesAppCenRepNotifyHandler->StopListening();
        delete iThemesAppCenRepNotifyHandler;
        }
    delete iThemesAppRepository;
    }

// -----------------------------------------------------------------------------
// Activate a Skin.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::ActivateSkinL(
    const TDesC8& /*aPreviewType*/,
    const TInt /*aActiveSkinIndex*/ )
    {
    PSLN_TRACE_DEBUG("CPslnModel::ActivateSkinL -- depricated!!");
    User::Leave( KErrNotSupported );
    return EFalse;
    }

// -----------------------------------------------------------------------------
// Activate a screen saver.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::ActivateScreenSaver( const TInt aItemIndex, 
    TPslnScreenSaverActivation aActivationType )
    {
    PSLN_TRACE_DEBUG("CPslnModel::ActivateScreenSaver");
    TRAPD( err, ActivateScreenSaverL( aItemIndex, aActivationType ) );
    PSLN_TRACE_DEBUG1("CPslnModel::ActivateScreenSaver %d", err );
    return err;
    }

// -----------------------------------------------------------------------------
// CPslnModel::GuardActivationLC
// -----------------------------------------------------------------------------
//
EXPORT_C void  CPslnModel::GuardActivationLC()
    {
    PSLN_TRACE_DEBUG("CPslnModel::GuardActivationLC");
    CleanupStack::PushL( CPslnActivationGuard::NewL( this ) );
    }

// -----------------------------------------------------------------------------
// Download a skin.
// -----------------------------------------------------------------------------
//
EXPORT_C void CPslnModel::DownloadSkinL()
    {
    PSLN_TRACE_DEBUG("CPslnModel::DownloadSkinL BEGIN");
    PSLN_TRACE_DEBUG("CPslnModel::DownloadSkinL Load DLL");
    LoadBrowserLaunchL();
    if ( iBrowserLauncher )
        {
        PSLN_TRACE_DEBUG("CPslnModel::DownloadSkinL Launch embedded browser");
        TRAPD( error, 
               iBrowserLauncher->LaunchBrowserStandaloneL( ) );
        if ( error != KErrNone )
            {
            PSLN_TRACE_DEBUG1("CPslnModel::DownloadSkinL Handle exit: %d", error );
            }
        if ( error == KErrNoMemory )
            {
            PSLN_TRACE_DEBUG("CPslnModel::DownloadSkinL OOM");
            User::Leave( error );
            }
        }
    PSLN_TRACE_DEBUG("CPslnModel::DownloadSkinL END");
    }

// -----------------------------------------------------------------------------
// Set Background image path name.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::SetBackgroundImagePath( const TDesC& aImagePath )
    {
    PSLN_TRACE_DEBUG("CPslnModel::SetBackgroundImagePath");

    TRAP_IGNORE( LoadWallpaperUtilsL() );
    TInt retVal = KErrNone;
    if ( iWallpaperSetter )
        {
        if( aImagePath.Length() > 0 )
            {
            retVal = iWallpaperSetter->SetIdleWallpaper(
                aImagePath, 
                CCoeEnv::Static(),
                R_PSLN_SKINS_LOADING_IMAGE,
                R_PSLN_GENERAL_WAIT_NOTE );
            }
        else
            {
            retVal = iWallpaperSetter->SetIdleWallpaper( KNullDesC, NULL );
            }
        }
    else
        {
        retVal = KErrNoMemory;
        }
    return retVal;
    }

// ---------------------------------------------------------------------------
// CPslnModel::InvokeSSPluginFunctionL
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnModel::InvokeSSPluginFunctionL(
    TInt aIndex,
    TScPluginCaps aFunction )
    {
    PSLN_TRACE_DEBUG("CPslnModel::InvokeSSPluginFunctionL");
    if ( !iScreensaverFilenameArr || iScreensaverFilenameArr->Count() == 0 )
        {
        User::Leave( KErrNotFound );
        }

    if( aIndex >= iScreensaverFilenameArr->MdcaCount() )
        {
        User::Leave( KErrArgument );
        }
        
    if(aFunction == EScpCapsConfigure &&
       aIndex == GetScreenSaverIndexByFileName(KPslnScreenSaverTypeText))
        {
        TBool ret = QueryAndSetScreensaverTextL();
        if ( !ret )
            {
            User::Leave( KErrCancel );
            }
        return;
        }

    // Convert the UID of the given screensaver plugin from text to integer
    // The string format of the UID: [12345678]
    // The number inside the brackets in hexadecimal format
    TLex lex( iScreensaverFilenameArr->MdcaPoint( aIndex ) );
    // Skip the first character: '['
    lex.Get();
    TUint screenSaverPluginImpUid;
    // Get the UID
    TInt err = lex.Val( screenSaverPluginImpUid, EHex );
    PSLN_TRACE_DEBUG1("CPslnModel::InvokeSSPluginFunctionL lexed: %d", err );
    User::LeaveIfError( err );

    CScreensaverPluginInterfaceDefinition* plugin =
        CScreensaverPluginInterfaceDefinition::NewL(
        TUid::Uid( screenSaverPluginImpUid ) );
    CleanupStack::PushL( plugin );

    err = plugin->PluginFunction( aFunction, iEikEnv );
    PSLN_TRACE_DEBUG1("CPslnModel::InvokeSSPluginFunctionL call return: %d", err );
    CleanupStack::PopAndDestroy( plugin );

    if( err == KErrCancel && aIndex == CurrentPropertyIndexL( KPslnScreenSettingId ) )
        {
        SetScreenSaverToDefault();
        }
    
    User::LeaveIfError( err );
    }

// ---------------------------------------------------------------------------
// CPslnModel::PerformCompleteUpdateL
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnModel::PerformCompleteUpdateL()
    {
    PSLN_TRACE_DEBUG("CPslnModel::PerformCompleteUpdateL");

    if ( iInternalState.IsClear( EPslnModelStateSkinNamesLoaded ) )
        {
        LoadSkinNamesResourceL();
        }
    UpdateFromServerL();
    SetActiveSkinL();

    PSLN_TRACE_DEBUG("CPslnModel::PerformCompleteUpdateL COMPLETED");
    }

// ---------------------------------------------------------------------------
// CPslnModel::LoadScreensaverArrayL
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnModel::LoadScreensaverArrayL()
    {
    PSLN_TRACE_DEBUG("CPslnModel::LoadScreensaverArrayL");

    // Destroy old arrays, if any
    delete iScreensaverNameArr;
    iScreensaverNameArr = NULL;
    delete iScreensaverFilenameArr;
    iScreensaverFilenameArr = NULL;
    iScreensaverCapsArr.Reset();

    // Load default items
    iScreensaverNameArr = iEikEnv->ReadDesC16ArrayResourceL(
        R_SCREEN_SAVER_SETTING_PAGE_LBX );

    // Add descriptors for system screensavers
    iScreensaverFilenameArr =
        new (ELeave) CDesC16ArrayFlat( KPslnSsArrayGranularity );
    iScreensaverFilenameArr->AppendL( KPslnScreenSaverTypeDateTime );
    iScreensaverFilenameArr->AppendL( KPslnScreenSaverTypeText );

    // System screensavers have no capabilities
    User::LeaveIfError( iScreensaverCapsArr.Append( EFalse ) );
    User::LeaveIfError( iScreensaverCapsArr.Append( EScpCapsConfigure ) );

    if ( IsSupportScreenSaverNoneOption() )
        {
        iScreensaverFilenameArr->InsertL(0, KPslnScreenSaverTypeNone ); 
        User::LeaveIfError( iScreensaverCapsArr.Insert( 0, EFalse ) );
        }
    else
        {
        iScreensaverNameArr->Delete(0);
        }

    FindAndAppendScreensaversL();
    }

// ---------------------------------------------------------------------------
// CPslnModel::VisibleSkin
// ---------------------------------------------------------------------------
//
EXPORT_C CPslnSkinEntry* CPslnModel::VisibleSkin( const TInt aIndex )
    {
    PSLN_TRACE_DEBUG("CPslnModel::VisibleSkin");
    if ( !iSkinStore )
        {
        TRAPD( err, iSkinStore = CPslnSkinStore::NewL( this ) );
        if ( err != KErrNone )
            {
            return NULL;
            }
        }
    CPslnSkinEntry* visibleSkin = NULL;
    if ( iVisibleSkinArr )
        {
        if( ( aIndex >= 0 ) && ( aIndex < iVisibleSkinArr->Count() ) )
            {
            CPslnSkinNameEntry* nameEntry = (*iVisibleSkinArr)[aIndex];
            visibleSkin = iSkinStore->Find(
                nameEntry->PkgID(), nameEntry->Location() );
            }
        }
    return visibleSkin;
    }

// -----------------------------------------------------------------------------
// Get a skin's name by index.
// -----------------------------------------------------------------------------
//
EXPORT_C void CPslnModel::GetSkinNameByIndex( const TInt aIndex, TDes& aSkinName,
    const TPslnSkinNameType aType ) const
    {
    PSLN_TRACE_DEBUG("CPslnModel::GetSkinNameByIndex");

    TAknsPkgID pid = KAknsNullPkgID;
    if ( iVisibleSkinArr )
        {
        if( ( aIndex >= 0 ) && ( aIndex < iVisibleSkinArr->Count() ) )
            {
            pid = (*iVisibleSkinArr)[aIndex]->PkgID();
            }
        }

    GetSkinNameByPID( pid, aSkinName, aType );
    }

// -----------------------------------------------------------------------------
// Return if the selected skin is activated.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::IsActiveSkinSelected( TInt aSkinIndex ) const
    {
    PSLN_TRACE_DEBUG("CPslnModel::IsActiveOfSkinSelected");

    TInt skinIndex = iCurrentSkinIndex;
    if ( aSkinIndex >= 0 )
        {
        skinIndex = aSkinIndex;
        }
    return ( iActiveSkinIndex == skinIndex );
    }

// -----------------------------------------------------------------------------
// CPslnModel::LocationOfSkin
// Deprecated.
// -----------------------------------------------------------------------------
//
EXPORT_C TAknSkinSrvSkinPackageLocation CPslnModel::LocationOfSkin(
    const TInt aIndex )
    {
    PSLN_TRACE_DEBUG("CPslnModel::LocationOfSkin");
    TAknSkinSrvSkinPackageLocation skinLocation = EAknsSrvPhone;
    CPslnSkinEntry* entry = VisibleSkin( aIndex );
    if( entry )
        {
        skinLocation = entry->Location();
        }
    return skinLocation;
    }

// -----------------------------------------------------------------------------
// Return the active skin index.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::ActiveSkinIndex () const
    {
    PSLN_TRACE_DEBUG("CPslnModel::ActiveSkinIndex");
    return iActiveSkinIndex;
    }

// -----------------------------------------------------------------------------
// Return the skin index of the selection currently active.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::CurrentSelectedSkinIndex () const
    {
    PSLN_TRACE_DEBUG("CPslnModel::CurrentSelectedSkinIndex");
    return iCurrentSkinIndex;
    }

// -----------------------------------------------------------------------------
// Get number of skins.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::NumberOfSkins() const
    {
    PSLN_TRACE_DEBUG("CPslnModel::NumberOfSkins");
    TInt numberOfSkins = 0;
    if ( iVisibleSkinArr )
        {
        numberOfSkins = iVisibleSkinArr->Count();
        }
    return numberOfSkins;
    }

// ---------------------------------------------------------------------------
// CPslnModel::ScreensaverNames
// ---------------------------------------------------------------------------
//
EXPORT_C const MDesC16Array& CPslnModel::ScreensaverNames() const
    {
    PSLN_TRACE_DEBUG("CPslnModel::ScreensaverNames");
    return *iScreensaverNameArr;
    }

// ---------------------------------------------------------------------------
// CPslnModel::ScreensaverHasCapability
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::ScreensaverHasCapability(
    const TInt aIndex,
    const TScPluginCaps aCapability ) const
    {
    PSLN_TRACE_DEBUG("CPslnModel::ScreensaverHasCapability");
    if( ( aIndex < 0 ) || ( aIndex >= iScreensaverCapsArr.Count() ) )
        {
        return EFalse;
        }

    return ( iScreensaverCapsArr[ aIndex ] & aCapability );
    }

// -----------------------------------------------------------------------------
// CPslnModel::ProtectionOfSkin
// -----------------------------------------------------------------------------
//
EXPORT_C TAknsSkinSrvSkinProtectionType CPslnModel::ProtectionOfSkin(
    const TInt aIndex )
    {
    PSLN_TRACE_DEBUG("CPslnModel::ProtectionOfSkin");
    TAknsSkinSrvSkinProtectionType skinProtectionType = EAknsSrvNoProtection;
    CPslnSkinEntry* entry = VisibleSkin( aIndex );
    if( entry )
        {
        skinProtectionType = entry->Protection();
        }
    return skinProtectionType;
    }

// -----------------------------------------------------------------------------
// CPslnModel::IsValidForActivation
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::IsValidForActivation( const TInt aItemIndex )
    {
    PSLN_TRACE_DEBUG("CPslnModel::IsValidForActivation");
    CPslnSkinEntry* skinEntry = VisibleSkin( aItemIndex );
    return ( skinEntry && !skinEntry->IsCorrupted() );
    }

// -----------------------------------------------------------------------------
// CPslnModel::IsValidForPreview
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::IsValidForPreview( const TInt aItemIndex )
    {
    PSLN_TRACE_DEBUG("CPslnModel::IsValidForPreview");
    CPslnSkinEntry* skinEntry = VisibleSkin( aItemIndex );
    if( !skinEntry )
        {
        return EFalse;
        }
        
    if( skinEntry->IsCorrupted() )
        {
        return EFalse;
        }
    TInt type = skinEntry->Protection();
    if( type != EAknsSrvNoProtection && type != EAknsSrvProtected )
        {
        return EFalse;
        }
        
    TBool skinFileExist = SkinFileExist( aItemIndex );
    if( !skinFileExist )
        {
        return EFalse;
        }

    return ETrue;
    }

// -----------------------------------------------------------------------------
// Checks if the skin support animated background.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::IsSupportAnimBg( TInt aItemIndex )
    {
    CPslnSkinEntry* skinEntry = VisibleSkin( aItemIndex );
    return skinEntry && skinEntry->IsSupportAnimBg();
    }
	
// -----------------------------------------------------------------------------
// Set current selected skin index.
// -----------------------------------------------------------------------------
//
EXPORT_C void CPslnModel::SetCurrentSelectedSkinIndex(
    const TInt aCurrentSkinIndex )
    {
    PSLN_TRACE_DEBUG1("CPslnModel::SetCurrentSelectedSkinIndex:%d", aCurrentSkinIndex );
    if ( aCurrentSkinIndex >= 0 )
        {
        iCurrentSkinIndex = aCurrentSkinIndex;
        }
    // If given index is negative, assume that first skin is selected.
    else
        {
        iCurrentSkinIndex = 0;
        }
    }

// -----------------------------------------------------------------------------
// CPslnModel::SetCurrentPropertyType
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::SetCurrentPropertyType(
    const TInt /*aProperty*/, const TInt /*aCurItemIndex*/ )
    {
    // deprecated.
    return KErrNotSupported;
    }

// -----------------------------------------------------------------------------
// Get a Skin's Properties Type index.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::CurrentPropertyIndex( const TInt aProperty )
    {
    PSLN_TRACE_DEBUG1("CPslnModel::CurrentPropertyIndex:%d", aProperty );
    TInt currentIndex = KErrNotFound;
    TRAP_IGNORE( currentIndex = CurrentPropertyIndexL( aProperty ) );
    PSLN_TRACE_DEBUG1("CPslnModel::CurrentPropertyIndex return:%d", currentIndex );
    return currentIndex;
    }

// -----------------------------------------------------------------------------
// Starts to listen for ECOM screensaver changes.
// -----------------------------------------------------------------------------
//
EXPORT_C void CPslnModel::EnableScreenSaverNotifications(
    const TBool& aActive, MPslnScreenSaverECOMObserver& aObserver )
    {
    PSLN_TRACE_DEBUG("CPslnModel::EnableScreenSaverNotifications" );
    if ( aActive )
        {
        // Create listening class (active object)
        TRAP_IGNORE(
            iScreenSaverListener = CPslnEcomListener::NewL( *this, aObserver ) );
        }
    else
        {
        // Check if model has already destroyed this.
        if ( iScreenSaverListener )
            {
            if ( iScreenSaverListener->IsActive() )
                {
                iScreenSaverListener->Cancel();
                }
            delete iScreenSaverListener;
            iScreenSaverListener = NULL;
            }
        }
    }

// -----------------------------------------------------------------------------
// Activates skin. This overloaded version knows in which state the activation 
// is requested.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::ActivateSkinL(
    const TDesC8& /*aPreviewType*/,
    const TInt /*aActiveSkinIndex*/,
    const TBool& /*aActivateFromPreview*/ )
    {
    PSLN_TRACE_DEBUG("CPslnModel::ActivateSkinL -- depricated!!");
    User::Leave( KErrNotSupported );
    return EFalse;
    }

// -----------------------------------------------------------------------------
// Activates skin. 
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::ActivateSkinL(
    const TInt aActiveSkinIndex )
    {
    PSLN_TRACE_DEBUG("CPslnModel::ActivateSkinL");

    TInt indexToActivate = aActiveSkinIndex;
    if( aActiveSkinIndex == KErrNotFound )
        {
        indexToActivate = iActiveSkinIndex;
        }
    PSLN_TRACE_DEBUG1("CPslnModel::ActivateSkinL activate skin index=%d", indexToActivate );
    // Get skin's full name.
    HBufC* fullName = HBufC::NewLC( KMaxFileName );
    TPtr fullNamePtr = fullName->Des();
    fullNamePtr = GetSkinFullName( indexToActivate );

    if ( !PslnDiskUtil::QueryAndSetAutomatedL( iSkinSrvSession, fullNamePtr ) )
        {
        CleanupStack::PopAndDestroy( fullName );
        PSLN_TRACE_DEBUG("CPslnModel::ActivateSkinL set autom. not ok");
        return EFalse;
        }
    CleanupStack::PopAndDestroy( fullName );

    // Find out the skin package ID
    CPslnSkinEntry* activeEntry = VisibleSkin( indexToActivate );
    if ( !activeEntry )
        {
        PSLN_TRACE_DEBUG("CPslnModel::ActivateSkinL NULL entry");
        User::Leave( KErrGeneral );
        }

    TAknsPkgID activeSkinPid = activeEntry->PkgID();
    // Activate whole skin
    PSLN_TRACE_DEBUG("CPslnModel::ActivateSkinL set all definition sets");
    TInt error = iSkinSrvSession.SetAllDefinitionSets( activeSkinPid );
    
    // For enabling first component transition effect
    GfxTransEffect::Enable();
    
    if ( error != KErrNone )
        {
        PSLN_TRACE_DEBUG1("CPslnModel::ActivateSkinL error when setting definition sets: %d", error );
        User::LeaveIfError( error );
        }
        
    // Otherwise, save to shareddata
    TAknsPkgIDBuf pidBuf;
    activeSkinPid.CopyToDes( pidBuf );

    iSkinsRepository->Set(
        KPslnActiveSkinUid,
        pidBuf );
    iSkinsRepository->Set(
        KPslnActiveSkinLocation,
        activeEntry->Location() );
        
    iActiveSkinIndex = indexToActivate;
    return ETrue;
    }

// -----------------------------------------------------------------------------
// Leaving version of CurrentPropertyIndex.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::CurrentPropertyIndexL( const TInt aProperty )
    {
    PSLN_TRACE_DEBUG1("CPslnModel::CurrentPropertyIndex prop=%d", aProperty );

    TInt itemIndex = KErrNotFound;

    switch( aProperty )
        {
        case KPslnBgIdleSettingId:
            {
            itemIndex = GetWallPaperItemIndex();
            break;
            }
        case KPslnScreenSettingId:
            {
            itemIndex = GetScreenSaverItemIndexL();
            break;
            }
        default:
            break;
        }
    return itemIndex;
    }

// -----------------------------------------------------------------------------
// Sets transition effects.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::SetTransitionEffectsL( const TInt aEffectValue )
    {
    PSLN_TRACE_DEBUG("CPslnModel::SetTransitionEffectsL");
    TInt retVal = KErrNone;

    // For the first time only, read default enable mask.
    if ( iInternalState.IsClear( EPslnModelStateTransitionEnableCRKeyRead ) )
        {
        // Initialize to enable all.
        iEffectsDefaultEnableMask = EPslnEnableAllEffects;

        retVal = iThemesAppRepository->Get( 
            KThemesDefaultTransitionEffects, 
            iEffectsDefaultEnableMask );
        if ( retVal == KErrNone )
            {            
            iInternalState.Set( EPslnModelStateTransitionEnableCRKeyRead );
            }
        }

    // Only accept default mask, zero or max value.
    if ( aEffectValue != iEffectsDefaultEnableMask && 
         aEffectValue != EPslnEnableAllEffects &&
         aEffectValue != EPslnDisableAllEffects )
        {
        retVal = KErrArgument;
        }
    else
        {
        if ( aEffectValue == EPslnEnableAllEffects ||
             aEffectValue == iEffectsDefaultEnableMask )
            {
            TInt freeRAM = 0;
            HAL::Get( HALData::EMemoryRAMFree, freeRAM );
            if ( freeRAM < KPslnTransitionEffectRAMThreshold )
                {
                return KErrNoMemory;
                }
            }

        // Use mask, if activating effects.
        TInt effectValue = aEffectValue;
        if ( aEffectValue != EPslnDisableAllEffects )
            {
            effectValue = iEffectsDefaultEnableMask;
            }

        iThemesAppRepository->Set( 
            KThemesTransitionEffects, 
            effectValue );
        }
        
    // Need to have TFXSrv running before calling enable
    const TInt KWaitForTFXServerStart( 100000 );
    User::After( KWaitForTFXServerStart );
    // For enabling first component transition effect
    GfxTransEffect::Enable();
    
    PSLN_TRACE_DEBUG1("CPslnModel::SetTransitionEffectsL %d", retVal );
    return retVal;
    }

// -----------------------------------------------------------------------------
// Gets current value of transition effects.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::GetTransitionEffectStateL()
    {
    if( PslnFeatures::IsSupported( KPslnSupportFastPreviewTheme ) )
        {
        return iTransitionEffectValue;
        }
    

    PSLN_TRACE_DEBUG("CPslnModel::GetTransitionEffectStateL");
    TInt effectsValue = KErrNone;

    TInt error = iThemesAppRepository->Get( KThemesTransitionEffects, effectsValue );
    if ( error != KErrNone || effectsValue < 0 )
        {
        PSLN_TRACE_DEBUG2("CPslnModel::GetTransitionEffectStateL Error: %d %d", error, effectsValue );
        effectsValue = KErrNotFound;
        }

    PSLN_TRACE_DEBUG1("CPslnModel::GetTransitionEffectStateL return %d", effectsValue );
    return effectsValue;
    }

// -----------------------------------------------------------------------------
// Get Animated Background state
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::AnimBackgroundState() const
    {   
    TInt value = KErrNone;
    TInt error = iThemesAppRepository->Get( KThemesAnimBackgroundSupport, value );
    if ( error != KErrNone || value < 0 )
        {
        value = KMaxTInt;
        }

    return value;
    }

// -----------------------------------------------------------------------------
// Set Animated Background state
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CPslnModel::SetAnimBackground( TInt aValue )
    {
    ASSERT( aValue == EPslnEnableAllEffects ||
            aValue == EPslnDisableAllEffects );
    
    TInt retVal = KErrNone;
    if ( aValue == EPslnEnableAllEffects )
        {
        TInt freeRAM = 0;
        HAL::Get( HALData::EMemoryRAMFree, freeRAM );
        if ( freeRAM < KPslnTransitionEffectRAMThreshold )
            {
            return KErrNoMemory;
            }
        }
    iThemesAppRepository->Set( KThemesAnimBackgroundSupport, aValue );
        
    return retVal;
    }
	
// -----------------------------------------------------------------------------
// Checks if screensaver is on memory card.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::IsScreenSaverOnMemoryCard( const TInt aIndex ) const
    {
    if ( !iScreensaverFilenameArr || iScreensaverFilenameArr->Count() == 0 )
        {
        return EFalse;
        }

    TLex lex( iScreensaverFilenameArr->MdcaPoint( aIndex ) );
    // Skip the first character: '['
    lex.Get();
    TUint screenSaverPluginImpUid;
    TInt currentDrive = EDriveC;
    // Get the UID
    lex.Val( screenSaverPluginImpUid, EHex );
    // Skip character: ']'
    lex.Get();
    // Get the drive
    if ( !lex.Eos() )
        {
        // Find out which drive the plugin is on
        if ( lex.Val( currentDrive ) != KErrNone )
            {
            return EFalse;
            }
        }
#ifndef RD_MULTIPLE_DRIVE
    if ( currentDrive == EDriveE )
        {
        return ETrue;
        }
    return EFalse;
#else
    RFs& fs = iEikEnv->FsSession();

    TUint driveStatus = 0;
    TBool retVal = EFalse;
    TInt err = DriveInfo::GetDriveStatus( fs, currentDrive, driveStatus );
    if ( driveStatus & DriveInfo::EDriveExternallyMountable &&
         driveStatus & DriveInfo::EDriveRemovable )
        {
        retVal = ETrue;
        }
    return retVal;
#endif // RD_MULTIPLE_DRIVE
    }

// -----------------------------------------------------------------------------
// Sets currently active content (screensaver/wallpaper) index.
// -----------------------------------------------------------------------------
//
EXPORT_C void CPslnModel::SetCurrentPropertyTypeL(
    const TInt aProperty, const TInt aCurItemIndex )
    {
    PSLN_TRACE_DEBUG2("CPslnModel::SetCurrentPropertyTypeL prop=%d index=%d", 
        aProperty, aCurItemIndex );

    if( aCurItemIndex < KPslnDefaultItemIndex )
        {
        User::Leave( KErrArgument );
        }

    TInt retVal = KErrNone;
    switch( aProperty )
        {
        case KPslnBgIdleSettingId:
            retVal = iSkinsRepository->Set( KPslnWallpaperType, aCurItemIndex );
            break;
        case KPslnScreenSettingId:
            {
            TInt screensaverType = GetScreensaverTypeByIndex(aCurItemIndex);
            if ( screensaverType == KPslnSsText )
                {
                // Query text if necessary
                TBool ret = QueryAndSetScreensaverTextL();
                if ( !ret )
                    {
                    User::Leave( KErrCancel );
                    }
                }
            
            if ( screensaverType == KPslnSsObject )
                {
                retVal = iScreenSaverRepository->Set(
                    KScreenSaverPluginName,
                    iScreensaverFilenameArr->MdcaPoint( aCurItemIndex ) );
                }
            else
                {
                retVal = iScreenSaverRepository->Set(
                    KScreenSaverPluginName,
                    KNullDesC );
                }
                
            retVal = iScreenSaverRepository->Set(
                KScreenSaverObject,
                screensaverType );
            
            break;
            }
        default:
            break;
        }
    User::LeaveIfError( retVal );
    }

// -----------------------------------------------------------------------------
// Checks if the theme is on memory card.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::IsThemeOnMemoryCard( const TInt& aIndex )
    {
#ifndef RD_MULTIPLE_DRIVE
    return EFalse;
#else
    PSLN_TRACE_DEBUG("CPslnModel::IsThemeOnMemoryCard");
    TBool isThemeOnMemoryCard = EFalse;
    CPslnSkinEntry* entry = VisibleSkin( aIndex );
    if( entry )
        {
        isThemeOnMemoryCard = entry->IsOnMemoryCard();
        }
    return isThemeOnMemoryCard;
#endif //RD_MULTIPLE_DRIVE
    }

// -----------------------------------------------------------------------------
// Checks if the theme is on mass memory.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::IsThemeOnMassDrive( const TInt& aIndex  )
    {
#ifndef RD_MULTIPLE_DRIVE
    return EFalse;
#else
    PSLN_TRACE_DEBUG("CPslnModel::IsThemeOnMassDrive");
    TBool isThemeOnMemoryCard = EFalse;
    CPslnSkinEntry* entry = VisibleSkin( aIndex );
    if( entry )
        {
        isThemeOnMemoryCard = entry->IsOnMassDrive();
        }
    return isThemeOnMemoryCard;
#endif //RD_MULTIPLE_DRIVE
    }

// -----------------------------------------------------------------------------
// Checks if the screensaver is on mass memory.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnModel::IsScreenSaverOnMassDrive( const TInt& aIndex ) const
    {
#ifndef RD_MULTIPLE_DRIVE
    return EFalse;
#else

    if ( !iScreensaverFilenameArr || iScreensaverFilenameArr->Count() == 0 )
        {
        return EFalse;
        }

    TLex lex( iScreensaverFilenameArr->MdcaPoint( aIndex ) );
    // Skip the first character: '['
    lex.Get();
    TUint screenSaverPluginImpUid;
    TInt currentDrive = EDriveC;
    // Get the UID
    lex.Val( screenSaverPluginImpUid, EHex );
    // Skip character: ']'
    lex.Get();
    // Get the drive
    if ( !lex.Eos() )
        {
        // Find out which drive the plugin is on
        if ( lex.Val( currentDrive ) != KErrNone )
            {
            return EFalse;
            }
        }

    RFs& fs = iEikEnv->FsSession();

    TUint driveStatus = 0;
    TBool retVal = EFalse;
    TInt err = DriveInfo::GetDriveStatus( fs, currentDrive, driveStatus );
    
    // It is mass memory, if it is externally mountable, but not removable.
    if ( driveStatus & DriveInfo::EDriveExternallyMountable &&
         !( driveStatus & DriveInfo::EDriveRemovable ) )
        {
        retVal = ETrue;
        }
    return retVal;
#endif // RD_MULTIPLE_DRIVE
    }

// -----------------------------------------------------------------------------
// Shares skin server session.
// -----------------------------------------------------------------------------
//
EXPORT_C RAknsSrvSession CPslnModel::SkinSrvSession() const
    { 
    return iSkinSrvSession;
    }
    
// -----------------------------------------------------------------------------
// Starts or stops transition effects.
// -----------------------------------------------------------------------------
//    
EXPORT_C void CPslnModel::TransEffect(TInt aAction) const
    {
    __ASSERT_DEBUG( EPslnTransitionEffectDummyFirst < aAction && 
                    aAction < EPslnTransitionEffectDummyLast,
                    User::Panic(_L("Invalid action for CPslnModel::TransEffect"), 1) );
                    
    switch (aAction)
        {
        case EPslnTransitionEffectStartPreview:
             GfxTransEffect::BeginFullScreen( /*AknTransEffect::EApplicationExit*/1500, TRect(), 
                                      AknTransEffect::EParameterType,
                                      AknTransEffect::GfxTransParam( KUidPsln ) );    
             break;                                               
        case EPslnTransitionEffectStartThemeActivation:
             GfxTransEffect::BeginFullScreen( /*AknTransEffect::EApplicationExit*/1501, TRect(), 
                                      AknTransEffect::EParameterType,
                                      AknTransEffect::GfxTransParam( KUidPsln ) );             
             break;                                      
        
        case EPslnTransitionEffectStop:
             GfxTransEffect::EndFullScreen(); 
             break;            
        }
    }
    
// ---------------------------------------------------------------------------
// Set current screensaver to default screensaver.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnModel::SetScreenSaverToDefault()
    {
    // Default Screensaver is Date
    iScreenSaverRepository->Set(
        KScreenSaverObject,
        KPslnSsDate );
    iScreenSaverRepository->Set(
        KScreenSaverPluginName,
        KNullDesC );
        
    }

// -----------------------------------------------------------------------------
// CPslnModel::GetSeparatelyLocalizedSkinName
// -----------------------------------------------------------------------------
//
TBool CPslnModel::GetSeparatelyLocalizedSkinName(
    const TAknsPkgID aPID, TDes& aSkinName,
    const TPslnSkinNameType aType ) const
    {
    PSLN_TRACE_DEBUG("CPslnModel::GetSeparatelyLocalizedSkinName");
    TBool retValue = EFalse;
    TInt i = KErrNone;
    for( ; i < iSkinNames.Count(); i++ )
        {
        if( iSkinNames[i].iPid == aPID )
            {
            switch( aType )
                {
                case EPslnSkinNameTypeList:
                    aSkinName = *iSkinNames[i].iListName;
                    break;
                case EPslnSkinNameTypeTitle:
                    aSkinName = *iSkinNames[i].iTitleName;
                    break;
                }
            retValue = ETrue;
            break; // break the for loop
            }
        }
    return retValue;
    }


// -----------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnModel::CPslnModel()
    {
    PSLN_TRACE_DEBUG("CPslnModel::constructor");
    iEikEnv = CEikonEnv::Static();
    iActiveSkinIndex = KErrNotFound;
    iCurrentSkinIndex = KErrNotFound;
    iInternalState.ClearAll();
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnModel::ConstructL( MAknsSkinChangeObserver* aObserver )
    {
    PSLN_TRACE_DEBUG("CPslnModel::ConstructL");

    PSLN_TRACE_DEBUG("CPslnModel::ConstructL CenRep");
    iSkinsRepository = CRepository::NewL( KCRUidPersonalisation );
    iScreenSaverRepository = CRepository::NewL( KCRUidScreenSaver );
    iThemesAppRepository = CRepository::NewL( KCRUidThemes );

    // Connect to skin server.
    User::LeaveIfError( iSkinSrvSession.Connect( aObserver ) );
    
    if( PslnFeatures::IsSupported( KPslnSupportFastPreviewTheme ) )
        {
        InitTransitionEffectVauleL();
        }

    PSLN_TRACE_DEBUG("CPslnModel::ConstructL OK");
    }

// -----------------------------------------------------------------------------
// Loads the skin name resource file
// -----------------------------------------------------------------------------
//
void CPslnModel::LoadSkinNamesResourceL()
    {
    PSLN_TRACE_DEBUG("CPslnModel::LoadSkinNamesResourceL");
    TParse* fp = new (ELeave) TParse;
    fp->Set( KPslnSkinNamesFile, &KDC_APP_RESOURCE_DIR, NULL );
    TFileName filename = fp->FullName();
    delete fp;

    BaflUtils::NearestLanguageFile( iEikEnv->FsSession(), filename );
    TResourceReader reader;
    TInt resourceFileOffset = iEikEnv->AddResourceFileL( filename );
    iEikEnv->CreateResourceReaderLC( reader, R_PSLN_SKINNAME_LIST );

    TInt items = reader.ReadInt16();
    for( TInt i = 0; i < items; i++ )
        {
        TInt pid1 = reader.ReadInt32();
        TInt pid2 = reader.ReadInt32();
        HBufC16* listname = reader.ReadHBufC16L();
        CleanupStack::PushL( listname );
        HBufC16* titlename = reader.ReadHBufC16L();
        CleanupStack::PushL( titlename );

        TPslnSkinNameEntry entry;
        entry.iPid.Set( pid2, pid1 );
        entry.iListName = listname;
        entry.iTitleName = titlename;
        User::LeaveIfError( iSkinNames.Append( entry ) );

        // Title and list name are deleted in the model's destructor.
        CleanupStack::Pop( 2, listname ); // titlename, listname
        }
    CleanupStack::PopAndDestroy(); // reader

    if( resourceFileOffset )
        {
        iEikEnv->DeleteResourceFile( resourceFileOffset );
        }

    iInternalState.Set( EPslnModelStateSkinNamesLoaded );
    PSLN_TRACE_DEBUG("CPslnModel::LoadSkinNamesResourceL DONE");
    }

// ---------------------------------------------------------------------------
// CPslnModel::FindAndAppendScreensaversL
// ---------------------------------------------------------------------------
//
TBool CPslnModel::FindAndAppendScreensaversL()
    {
    PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL");

    TBool found = EFalse;

    RImplInfoPtrArray screenSaverList;
    CleanupResetAndDestroyPushL( screenSaverList );

    CScreensaverPluginInterfaceDefinition::ListImplementationsL( screenSaverList );

    const TInt ssCount = screenSaverList.Count();

    for( TInt i = 0; i < ssCount; i++ )
        {
        PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL Plugin found");

        CImplementationInformation* implInfo = screenSaverList[i];

        // The the screensaver ecom plugin implementation UID will be used in place of
        // screensaver file name
        // The string format of the UID: [12345678]
        // The number inside the brackets in hexadecimal format
        TUid impUid = implInfo->ImplementationUid();

        // Stash plugin drive number after the UID.
        HBufC* ssName = HBufC::NewLC( KMaxUidName + KPslnDriveNumberLength );
        TPtr ssNamePtr = ssName->Des();
        ssNamePtr = impUid.Name();
        ssNamePtr.AppendNum( implInfo->Drive() );

        // Query plugin name.
        MScreensaverPlugin* plugin = NULL;

        TRAPD( err, plugin = static_cast<MScreensaverPlugin*>(
            CScreensaverPluginInterfaceDefinition::NewL(
                TUid::Uid( impUid.iUid  ) ) ) );

        PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL Getting caps");

        if ( err == KErrNone )
            {
            CleanupStack::PushL( plugin );

            PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL Getting caps");

            // Convert the string stored in OpaqueData to an integer
            // It is the string represantation of TScPluginCaps values
            // opaque_data has the type TDescC8 so we have to use TLex8
            TLex8 lex(implInfo->OpaqueData());
            PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL After Getting caps");
            TInt capabilities = EScpCapsNone;
            TInt err2 = KErrNone;
            if ( !lex.Eos() )
                {
                err2 = lex.Val( capabilities );
                }
            PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL After Eos check");
            if ( err2 != KErrNone )
                {
                PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL Failed");
                // skip the failing plugin
                CleanupStack::Pop( plugin ); // using PopAndDestroy fails here.
                delete plugin;
                plugin = NULL;
                break;
                }

            // Append screensaver name.
            PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL Do Check");
            if ( plugin && iScreensaverNameArr )
                {
                if ( plugin->Name() != KNullDesC )
                    {
                    PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL Trying to add Name");
                    iScreensaverNameArr->AppendL( plugin->Name() );
                    }
                else
                    {
                    PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL Trying to add DisplayName");
                    iScreensaverNameArr->AppendL( implInfo->DisplayName() );
                    }
                }
            CleanupStack::Pop( plugin ); // using PopAndDestroy fails here.
            delete plugin;
            plugin = NULL;

            PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL CapsArr Append");
            User::LeaveIfError(
                iScreensaverCapsArr.Append( capabilities ) );
            PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL CapsArrAppend OK");

            found = ETrue;

            PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL Append");
            if ( iScreensaverFilenameArr )
                {
                iScreensaverFilenameArr->AppendL( ssNamePtr );
                }
            }
        CleanupStack::PopAndDestroy( ssName );
        }
    PSLN_TRACE_DEBUG("CPslnModel::FindAndAppendScreensaversL COMPLETED");
    CleanupStack::PopAndDestroy( &screenSaverList );
    return found;
    }

// ---------------------------------------------------------------------------
// CPslnModel::UpdateFromServerL
// ---------------------------------------------------------------------------
//
void CPslnModel::UpdateFromServerL()
    {
    PSLN_TRACE_DEBUG("CPslnModel::UpdateFromServerL");
    if ( !iSkinStore )
        {        
        iSkinStore = CPslnSkinStore::NewL( this );
        }
    iSkinStore->UpdateAllSkinsL( iEikEnv->FsSession() );
    UpdateVisibleSkinListL();
    }

// ---------------------------------------------------------------------------
// CPslnModel::UpdateVisibleSkinListL
// ---------------------------------------------------------------------------
//
void CPslnModel::UpdateVisibleSkinListL()
    {
    PSLN_TRACE_DEBUG("CPslnModel::UpdateVisibleSkinListL");
    if( iVisibleSkinArr )
        {
        iVisibleSkinArr->ResetAndDestroy();
        delete iVisibleSkinArr;
        iVisibleSkinArr = NULL;
        }

    if ( iSkinStore )
        {
        iVisibleSkinArr = iSkinStore->CreateNameArrayL();
        }    
    }

// -----------------------------------------------------------------------------
// CPslnModel::SetActiveSkinL
// -----------------------------------------------------------------------------
//
void CPslnModel::SetActiveSkinL()
    {
    PSLN_TRACE_DEBUG("CPslnModel::SetActiveSkinL");

    TInt activeSkinLocation = KErrNotFound;

    iSkinsRepository->Get(
        KPslnActiveSkinLocation,
        activeSkinLocation );

    // If skin is from memory card, check memory card status.
    if( activeSkinLocation == EAknsSrvMMC )
        {
        if( PslnDiskUtil::MmcStatus() < 0 )
            {
            // If skin is on memory card, and there is access error, 
            // activate default skin.
            ActivateDefaultSkinL();
            return;
            }
        }

    TAknsPkgIDBuf pidBuf;
    iSkinsRepository->Get(
        KPslnActiveSkinUid,
        pidBuf );

    TAknsPkgID activeSkinPid;
    activeSkinPid.SetFromDesL( pidBuf );

    if ( !iVisibleSkinArr )
        {
        User::Leave( KErrGeneral );
        }
    TInt activeSkinIndex = KErrNotFound;
    for( TInt i = 0; i < iVisibleSkinArr->Count(); i++ )
        {
        CPslnSkinNameEntry* nameEntry = (*iVisibleSkinArr)[i];
        if ( !nameEntry )
            {
            User::Leave( KErrGeneral );
            }
        if( ( activeSkinPid == nameEntry->PkgID() ) &&
            ( activeSkinLocation == nameEntry->Location() ) )
            {
            activeSkinIndex = i;
            break;
            }
        }

    if( activeSkinIndex == KErrNotFound )
        {
        // If the currently active skin no longer exists, activate the default.
        ActivateDefaultSkinL();
        return;
        }

    iActiveSkinIndex = activeSkinIndex;
    }

// -----------------------------------------------------------------------------
// Screen saver text query
// -----------------------------------------------------------------------------
//
TBool CPslnModel::QueryAndSetScreensaverTextL()
    {
    PSLN_TRACE_DEBUG("CPslnModel::QueryAndSetScreensaverTextL");

    HBufC* displayText = HBufC::NewLC( KPslnMaxNumberOfScreenSaverText );
    TPtr txtPtr = displayText->Des();

    TInt error = iScreenSaverRepository->Get( KScreenSaverText, txtPtr );

    // Just load the default text if nothing was set in the skin settings.
    if ( ( txtPtr.Length() == 0 ) || ( error != KErrNone ) )
        {
        GetDefaultTextToScreensaverL( txtPtr );
        }

    // Set text to query.
    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL(
        txtPtr,
        CAknQueryDialog::ENoTone );
    dlg->SetPredictiveTextInputPermitted( ETrue );

    // If in APAC region, set dialog length dynamically.
    if ( PslnFeatures::IsAPACSupported() )
        {        
        dlg->SetMaxLength( KPslnSsTextDialogAPACMaxLength );
        }

    TBool retValue = EFalse;
    // Show query for Screen saver txt.
    if( dlg->ExecuteLD( R_PSLN_SCREEN_SAVER_TEXT_QUERY_DIALOG ) )
        {
        error = iScreenSaverRepository->Set( KScreenSaverText, txtPtr );
        if ( error == KErrNone )
            {
            retValue = ETrue;
            }
        }
    CleanupStack::PopAndDestroy( displayText );
    return retValue;
    }


// ---------------------------------------------------------------------------
// CPslnModel::GetSkinFullName
// ---------------------------------------------------------------------------
//
const TDesC& CPslnModel::GetSkinFullName( const TInt aItemIndex )
    {
    PSLN_TRACE_DEBUG("CPslnModel::GetSkinFullName");
    CPslnSkinEntry* skinEntry = VisibleSkin( aItemIndex );
    if ( skinEntry )
        {
        return skinEntry->FullName();
        }
    return KNullDesC;
    }

// -----------------------------------------------------------------------------
// CPslnModel::GetSkinNameByPID
// -----------------------------------------------------------------------------
//
void CPslnModel::GetSkinNameByPID( const TAknsPkgID aPID, TDes& aSkinName,
    const TPslnSkinNameType aType ) const
    {
    PSLN_TRACE_DEBUG("CPslnModel::GetSkinNameByPID");

    aSkinName = KNullDesC;

    if( GetSeparatelyLocalizedSkinName( aPID, aSkinName, aType ) )
        {
        return;
        }

    if ( iSkinStore )
        {
        CPslnSkinEntry* entry = iSkinStore->Find( aPID, EAknsSrvAll );
        if ( entry )
            {
            entry->GetName( aSkinName );
            }
        }
    }

// ---------------------------------------------------------------------------
// CPslnModel::ActivateDefaultSkinL
// ---------------------------------------------------------------------------
//    
void CPslnModel::ActivateDefaultSkinL()
    {
    PSLN_TRACE_DEBUG("CPslnModel::ActivateDefaultSkinL");
    GuardActivationLC();
    ActivateSkinL( KPslnSeries60SkinIndex );
    CleanupStack::PopAndDestroy(); // activation guard
    }

// ---------------------------------------------------------------------------
// Sets default text to parameter.
// ---------------------------------------------------------------------------
//
void CPslnModel::GetDefaultTextToScreensaverL( TDes& aDisplayText )
    {
    PSLN_TRACE_DEBUG("CPslnModel::GetDefaultTextToScreensaverL");
    HBufC* strBuffer = NULL;
    strBuffer = StringLoader::LoadLC( R_PSLN_SCREEN_SAVER_DEFAULT_TEXT );
    if ( strBuffer )
        {
        aDisplayText = strBuffer->Des();
        }
    CleanupStack::PopAndDestroy( strBuffer );
    }

// ---------------------------------------------------------------------------
// Gets wallpaper item index. Same as above, but can leave.
// ---------------------------------------------------------------------------
//    
TInt CPslnModel::GetWallPaperItemIndex()
    {
    PSLN_TRACE_DEBUG("CPslnModel::GetWallPaperItemIndexL");
    TInt itemIndex = KErrNotFound;

    TInt error = iSkinsRepository->Get( KPslnWallpaperType, itemIndex );
    if ( error != KErrNone )
        {
        itemIndex = KPslnDefaultItemIndex;
        }
    if ( itemIndex == KPslnDefaultItemIndex )
        {
        // Verify that key values are coherent.
        TFileName wallpaperPath;
        error = iSkinsRepository->Get( KPslnIdleBackgroundImagePath, wallpaperPath );
        if ( wallpaperPath.Length() > 0 )
            {
            // Wallpaper image is defined, but type is claimed as None.
            // Assume that image is desired.
            itemIndex = 1;
            }
        }

    return itemIndex;
    }

// ---------------------------------------------------------------------------
// Gets screensaver item index. Same as above, but can leave.
// ---------------------------------------------------------------------------
//     
TInt CPslnModel::GetScreenSaverItemIndexL()
    {
    PSLN_TRACE_DEBUG("CPslnModel::GetScreenSaverItemIndexL");
    TInt screenObjectType = KErrNotFound;
    TInt error = KErrNone;
    
    error = iScreenSaverRepository->Get( 
        KScreenSaverObject, screenObjectType );
        
    if ( error != KErrNone )
        {
        return KErrNotFound;
        }

    if ( screenObjectType == KPslnSsNone && !IsSupportScreenSaverNoneOption() )
        {
        //if "none" option is not supported and the settings of cenrep is none
        //then change it to the default screen saver - "date".
        screenObjectType = KPslnSsDate;
        }
        
    switch ( screenObjectType )
        {
        case KPslnSsNone:
            return GetScreenSaverIndexByFileName(KPslnScreenSaverTypeNone);
        case KPslnSsDate:
            return GetScreenSaverIndexByFileName(KPslnScreenSaverTypeDateTime);
        case KPslnSsText:
            return GetScreenSaverIndexByFileName(KPslnScreenSaverTypeText);
        case KPslnSsObject:
            break;
        default:
            return KErrNotFound;
        }

    TInt itemIndex = KErrNotFound;
    HBufC* screenSaverFileName = HBufC::NewLC( KMaxFileName );
    TPtr ssFilePtr = screenSaverFileName->Des();
    error = iScreenSaverRepository->Get(
        KScreenSaverPluginName,
        ssFilePtr );

    // Try to look for ']'.
    TInt eqPos = ssFilePtr.Find( KPslnScreenSaverUidEndMark );

    // If not found, use the whole string.
    if( eqPos == KErrNotFound )
        {
        eqPos = ssFilePtr.Length();
        }
    // strip all characters right of it.
    ssFilePtr = ssFilePtr.Left( eqPos + 1 );

    if ( error == KErrNone && iScreensaverFilenameArr )
        {
        // Loop through all the screensavers.
        for( TInt i = 0; i < iScreensaverFilenameArr->MdcaCount(); i++ )
            {
            TPtrC ssNamePtr = GetRealScreenSaverUid( i );
            if( ssNamePtr.CompareF( ssFilePtr ) == 0 )
                {
                itemIndex = i;
                break;
                }
            }
        }
    CleanupStack::PopAndDestroy( screenSaverFileName );
    return itemIndex;
    }

// ---------------------------------------------------------------------------
// Dynamically loads AknsWallpaperUtils to memory.
// ---------------------------------------------------------------------------
//
void CPslnModel::LoadWallpaperUtilsL()
    {
    // Wallpaper utils dll loading.
    if( iInternalState.IsClear( EPslnModelStateWallpaperDllLoaded ) )
        {
        PSLN_TRACE_DEBUG("CPslnModel::LoadWallpaperUtilsL about load");
        if( iWallpaperDll.Load( KPslnWallpaperUtilsLoaderName ) == KErrNone )
            {
            PSLN_TRACE_DEBUG("CPslnModel::LoadWallpaperUtilsL loaded");
            iInternalState.Set( EPslnModelStateWallpaperDllLoaded );
            // Request the entry function
            NewWallpaperUtilsL wallpaperUtils =
                (NewWallpaperUtilsL) iWallpaperDll.Lookup( KPslnDllEntryPoint );
            if( wallpaperUtils )
                {
                PSLN_TRACE_DEBUG("CPslnModel::LoadWallpaperUtilsL create");
                // Create the class
                iWallpaperSetter =
                    (CPslnWallpaperUtilsLoader*) (*wallpaperUtils)();
                }
            }
        }
    if ( !iWallpaperSetter )
        {
        User::Leave( KErrNotFound );
        }
    }

// -----------------------------------------------------------------------------
// This function removes file information from ScreenSaver UID.
// -----------------------------------------------------------------------------
//
TPtrC CPslnModel::GetRealScreenSaverUid( const TInt aIndex )
    {
    PSLN_TRACE_DEBUG("CPslnModel::GetRealScreenSaverUid");
    // Look for ']' - this indicates the end of screensaver UID. 
    TInt eqPos = 
        iScreensaverFilenameArr->MdcaPoint( aIndex ).Find( 
            KPslnScreenSaverUidEndMark );
    // If not found, use the whole string.
    if( eqPos == KErrNotFound )
        {
        eqPos = iScreensaverFilenameArr->MdcaPoint( aIndex ).Length();
        }
    // strip all characters right of it.
    return iScreensaverFilenameArr->MdcaPoint( aIndex ).Left( eqPos + 1 );
    }

// -----------------------------------------------------------------------------
// This is leaving version of ActivateScreenSaver.
// -----------------------------------------------------------------------------
//
void CPslnModel::ActivateScreenSaverL( const TInt aItemIndex, 
    TPslnScreenSaverActivation aActivationType )
    {
    PSLN_TRACE_DEBUG("CPslnModel::ActivateScreenSaver");
    
    TInt error = KErrNone;
    if ( aActivationType == EPslnScreenSaverPreviewActivation )
        {
        // get screen saver type to be previewed
        TInt previewSsType = GetScreensaverTypeByIndex( aItemIndex );
        if ( previewSsType == KErrNotFound )
            {
            User::Leave( KErrNotFound );
            }

        // create CScreenSaverInfo object to backup the current screensaver settings
        if ( !iScreenSaverInfo )
            {
            iScreenSaverInfo = CPslnScreenSaverInfo::NewL();
            }
        
        //backup current screensaver settings
        error = iScreenSaverRepository->Get(
            KScreenSaverObject,
            iScreenSaverInfo->iScreenSaverType );

        if ( previewSsType == KPslnSsText )
            {
            TPtr ptr = iScreenSaverInfo->iScreenSaverTxt->Des();
            error = iScreenSaverRepository->Get(
                KScreenSaverText,
                ptr );
            }
        else if ( previewSsType == KPslnSsObject )
            {
            TPtr ptr = iScreenSaverInfo->iFileName->Des();
            error = iScreenSaverRepository->Get(
                KScreenSaverPluginName,
                ptr );
            }
            
        //set values to screen saver needed to preview
        if ( previewSsType == KPslnSsText )
            {
            // Load the default text.
            if ( iScreenSaverInfo->iScreenSaverTxt->Length() == 0 )
                {
                HBufC* screensaverText = HBufC::NewLC( KPslnMaxNumberOfScreenSaverText );
                TPtr ptr = screensaverText->Des();

                GetDefaultTextToScreensaverL( ptr );
                
                error = iScreenSaverRepository->Set(
                    KScreenSaverText,
                    ptr );

                CleanupStack::PopAndDestroy(screensaverText);
                }
            }
        else if ( previewSsType == KPslnSsObject )
            {
            // Get Screen saver filename based on index.
            if( ( aItemIndex >= 0 ) && ( aItemIndex < iScreensaverFilenameArr->Count() ) )
                {
                TPtrC ptr = iScreensaverFilenameArr->MdcaPoint( aItemIndex );
                error = iScreenSaverRepository->Set(
                    KScreenSaverPluginName,
                    ptr );
                }
            }
            
        error = iScreenSaverRepository->Set(
            KScreenSaverObject,
            previewSsType );
            
        // Set preview mode active, the screensaver is listening the value.
        error = RProperty::Set(
            KPSUidScreenSaver,
            KScreenSaverPreviewMode,
            KPslnActivatePreviewMode );     
        }
    else if ( aActivationType == EPslnScreenSaverPreviewDeactivation )
        {
        TInt previewSsType = KErrNotFound;
        error = iScreenSaverRepository->Get(
            KScreenSaverObject,
            previewSsType );

        //restore the screen saver settings.
        if ( previewSsType == KPslnSsObject )
            {
            error = iScreenSaverRepository->Set(
                KScreenSaverPluginName,
                iScreenSaverInfo->iFileName->Des() );
            }
        else if ( previewSsType == KPslnSsText )
            {
            error = iScreenSaverRepository->Set(
                KScreenSaverText,
                iScreenSaverInfo->iScreenSaverTxt->Des() );
            }
            
        if ( error == KErrNone )
            {        
            error = iScreenSaverRepository->Set(
                KScreenSaverObject,
                iScreenSaverInfo->iScreenSaverType );
            }
        }
    else
        {
        User::Leave( KErrNotSupported );      
        }   
    }

// ---------------------------------------------------------------------------
// Dynamically loads browser launcher dll to memory.
// ---------------------------------------------------------------------------
//
void CPslnModel::LoadBrowserLaunchL()
    {
    // Browser launch dll loading.
    if( iInternalState.IsClear( EPslnModelStateBrowserLaunchDllLoaded ) )
        {
        PSLN_TRACE_DEBUG("CPslnModel::LoadBrowserLaunchL about load");
        if( iBrowserLaunchDll.Load( KPslnBrowserLaunchLoaderName ) == KErrNone )
            {
            PSLN_TRACE_DEBUG("CPslnModel::LoadBrowserLaunchL loaded");
            iInternalState.Set( EPslnModelStateBrowserLaunchDllLoaded );
            // Request the entry function
            NewBrowserLauncherL browserLaucnher =
                (NewBrowserLauncherL) iBrowserLaunchDll.Lookup( KPslnDllEntryPoint );
            if( browserLaucnher )
                {
                PSLN_TRACE_DEBUG("CPslnModel::LoadBrowserLaunchL create");
                // Create the class
                iBrowserLauncher =
                    (CPslnBrowserLaunchLoader*) (*browserLaucnher)();
                }
            }
        }
    if ( !iBrowserLauncher )
        {
        User::Leave( KErrNotFound );
        }
    }
    
// -----------------------------------------------------------------------------
// CPslnModel::SkinFileExist
// -----------------------------------------------------------------------------
//
TBool CPslnModel::SkinFileExist( const TInt& aIndex  )
    {
    if( !IsThemeOnMemoryCard(aIndex) )
        {
        return ETrue;
        }
    
    TFileName fullname;
    fullname = GetSkinFullName( aIndex );
    
    TInt filehandle = 0;
    TInt fileserverhandle = iSkinSrvSession.OpenBitmapFile( fullname, filehandle );

    RFile file;
    TInt errorcode = file.AdoptFromServer( fileserverhandle, filehandle );
    file.Close();
    
    if ( errorcode == KErrNone )
        {
        return ETrue;
        }
    
    return EFalse;
    }
        
// ---------------------------------------------------------------------------
// Used to notify the client about changes for integer value keys.
// ---------------------------------------------------------------------------
//
void CPslnModel::HandleNotifyInt(TUint32 aId, TInt aNewValue)
    {
    if( aId == KThemesTransitionEffects )
        {
        iTransitionEffectValue = aNewValue;
        }
    }
    
// ---------------------------------------------------------------------------
// Gets transition effect value and initialize CenRep notify handler.
// ---------------------------------------------------------------------------
//
void CPslnModel::InitTransitionEffectVauleL()
    {
    iTransitionEffectValue = KErrNone;

    TInt error = iThemesAppRepository->Get( KThemesTransitionEffects, iTransitionEffectValue );
    if ( error != KErrNone || iTransitionEffectValue < 0 )
        {
        iTransitionEffectValue = KErrNotFound;
        }
    
    iThemesAppCenRepNotifyHandler = 
         CCenRepNotifyHandler::NewL(*this, *iThemesAppRepository,
            CCenRepNotifyHandler::EIntKey, KThemesTransitionEffects);
    iThemesAppCenRepNotifyHandler->StartListeningL();

    }

// -----------------------------------------------------------------------------
// Get screen saver object type from index.
// -----------------------------------------------------------------------------
//
TInt CPslnModel::GetScreensaverTypeByIndex(TInt aIndex)
    {
    if(aIndex < 0 || aIndex >= iScreensaverFilenameArr->MdcaCount())
        {
        return KErrNotFound;
        }
        
    TPtrC ptr = iScreensaverFilenameArr->MdcaPoint(aIndex);
    if(ptr.Compare(KPslnScreenSaverTypeNone) == 0)
        {
        return KPslnSsNone;
        }
    if(ptr.Compare(KPslnScreenSaverTypeDateTime) == 0)
        {
        return KPslnSsDate;
        }
    if(ptr.Compare(KPslnScreenSaverTypeText) == 0)
        {
        return KPslnSsText;
        }
    
    return KPslnSsObject;
    }

// ---------------------------------------------------------------------------
// Get screensaver item index from filename
// ---------------------------------------------------------------------------
//  
TInt CPslnModel::GetScreenSaverIndexByFileName(const TDesC &aFileName) const
    {
    for( TInt i = 0; i < iScreensaverFilenameArr->MdcaCount(); i++ )
        {
        if( aFileName.Compare((*iScreensaverFilenameArr)[i]) == 0 )
            {
            return i;
            }
        }
    return KErrNotFound;
    }

// ---------------------------------------------------------------------------
// Get if the "None" screen saver is supported.
// ---------------------------------------------------------------------------
//      
TBool CPslnModel::IsSupportScreenSaverNoneOption() const
    {
    return PslnFeatures::IsSupported( KPslnSupportScreenSaverSupportNoneOption );
    }
    
    

//  End of File

