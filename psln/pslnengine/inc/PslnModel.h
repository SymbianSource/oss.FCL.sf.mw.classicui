/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef C_PSLNMODEL_H
#define C_PSLNMODEL_H

#include <ScreensaverpluginIntDef.h>
#include <AknsSrvClient.h>
#include <babitflags.h>
#include <cenrepnotifyhandler.h>

// Determines the type of skin list.
enum TPslnSkinNameType
    {
    // list name
    EPslnSkinNameTypeList = 0,
    // title name
    EPslnSkinNameTypeTitle
    };
    
// What kind of scren saver activation it is.
enum TPslnScreenSaverActivation
    {
    // Preview is activated.
    EPslnScreenSaverPreviewActivation = 0,
    // Preview is deactivated, and "real" screen saver is activated,
    EPslnScreenSaverPreviewDeactivation,
    // Real screen saver is activated straight away.
    EPslnScreenSaverActivation
    };
    
// Defines actions for a transtion effects
enum TPslnTransitionEffectAction
    {
    // Used only for enum range validation 
    EPslnTransitionEffectDummyFirst = -1,
    
    // -- begin of real values --
    
    // Start theme preview transtion effect
    EPslnTransitionEffectStartPreview,    
    // Start theme activation transtion effect
    EPslnTransitionEffectStartThemeActivation,
    // Stop the current transition effect
    EPslnTransitionEffectStop,
    
    // -- end of real values --
    
    // Used only for enum range validation 
    EPslnTransitionEffectDummyLast
    };

class MAknsSkinChangeObserver;
class MPslnScreenSaverECOMObserver;
class CEikonEnv;
class CPslnSkinStore;
class CRepository;
class CPslnSkinEntry;
class CPslnSkinNameEntry;
class TAknsPkgID;
class CPslnWallpaperUtilsLoader;
class CPslnEcomListener;
class CPslnBrowserLaunchLoader;
class CCenRepNotifyHandler;

// Maximum number of characters in Screen saver txt.
const TInt KPslnMaxLengthOfScreenSaverText = 15;

// CLASS DEFINITIONS

// Inner class for skin name entry.
class TPslnSkinNameEntry
    {
    public:
        // Package ID.
        TAknsPkgID iPid;
        // Skin list name.
        HBufC* iListName;
        // Skin title name.
        HBufC* iTitleName;
    };

// Auxiliary class for screen saver info.
class CPslnScreenSaverInfo : public CBase
    {
    public:

        // Symbian OS two-phased constructor.
        static CPslnScreenSaverInfo* NewL() 
            {
            CPslnScreenSaverInfo* self = new (ELeave) CPslnScreenSaverInfo;
            CleanupStack::PushL( self );
            self->ConstructL();
            CleanupStack::Pop( self );
            return self;
            };

        // Destructor.
         ~CPslnScreenSaverInfo()
             {
             delete iScreenSaverTxt;
             iScreenSaverTxt = NULL;
             delete iFileName;
             iFileName = NULL;
             }
    private:

        // Symbian OS second phase constructor.
        void ConstructL()
            {
            iScreenSaverTxt = HBufC::NewL( KPslnMaxLengthOfScreenSaverText );
            iFileName = HBufC::NewL( KMaxFileName );
            };

        // C++ default constructor.
        CPslnScreenSaverInfo() 
            {
            iScreenSaverType = 1; // magic, default value
            };

    public:
        // Filename for screensaver, if applicable.
        HBufC* iFileName;
        // Text, if any, shown in the screensaver.
        HBufC* iScreenSaverTxt;
        // Type of screen saver.
        TInt iScreenSaverType;
    };

/**
* CPslnModel is the model class of Psln app.
* It provides functions to get and set setting values.
*/
NONSHARABLE_CLASS( CPslnModel ): 
    public CBase, 
    public MCenRepNotifyHandlerCallback
    {
    public:

        /**
        * Two-phased constructor.
        * @param aObserver observer for skin changes.
        * @return new instance of CPslnModel.
        */
        IMPORT_C static CPslnModel* NewL( MAknsSkinChangeObserver* aObserver );

        /**
        * Deprecated.
        * @return NULL.
        */
        IMPORT_C static CPslnModel* NewL();

        /**
        * Destructor
        */
        IMPORT_C ~CPslnModel();

        /**
        * Deprecated.
        */
        IMPORT_C TBool ActivateSkinL( const TDesC8& aPreviewType,
            const TInt aActiveSkinIndex );

        /**
        * Activates screen saver as set by user.
        * @param aItemIndex screensaver to activate.
        * @param aActivationType screensaver activation type 
        *       (activation/deactivation/preview).
        * @return error code, or KErrNone on success.
        */
        IMPORT_C TInt ActivateScreenSaver( 
            const TInt aItemIndex,
            TPslnScreenSaverActivation aActivationType );

        /**
        * Disables skin notify changes.
        *
        * Creates and pushes internal class CPslnActivationGuard to the
        * stack. When CPslnActivationGuard is constructed, SkinSrvSession's 
        * DisableSkinChangeNotify is called, and thus skin notify changes are 
        * disabled. When CPslnActivationGuard is popped from stack, 
        * SkinSrvSession's EnableSkinChangeNotify is called automatically and thus,
        * skin notify changes are again active. 
        */
        IMPORT_C void GuardActivationLC();

        /**
        * Starts skin download.
        */
        IMPORT_C void DownloadSkinL();

        /**
        * Sets Idle Wallpaper.
        * @param aImagePath Path and filename of new wallpaper.
        * @return error code, or KErrNone on success.
        */
        IMPORT_C TInt SetBackgroundImagePath( const TDesC& aImagePath );

        /**
        * Invokes screensaver plugins PluginFunction for e.g. configuring
        * the screensaver.
        * @param aIndex screensaver index to use.
        * @param aFunction screensaver function to call.
        */
        IMPORT_C void InvokeSSPluginFunctionL( 
            TInt aIndex, 
            TScPluginCaps aFunction );

        /**
        * Updates skins from server, UI skins list, and screensaver array.
        */
        IMPORT_C void PerformCompleteUpdateL();

        /**
        * Creates screen saver array.
        */
        IMPORT_C void LoadScreensaverArrayL();

        /**
        * Gets the visible skin by its UI index.
        * Ownership is not transferred.
        * @param aIndex skin index.
        * @return pointer to skin entry.
        */
        IMPORT_C CPslnSkinEntry* VisibleSkin( const TInt aIndex );

        /**
        * Gets the name of the skin.
        * @param aIndex skin index to use.
        * @param aSkinName localized skin name.
        * @param aType which skin name to fetch (list/title name).
        */
        IMPORT_C void GetSkinNameByIndex( const TInt aIndex, TDes& aSkinName, 
            const TPslnSkinNameType aType ) const;

        /**
        * Checks whether the current (or given) skin is active.
        * @param aSkinIndex skin index to use.
        * @return ETrue is given skin index is currently active skin.
        */
        IMPORT_C TBool IsActiveSkinSelected ( 
            TInt aSkinIndex = KErrNotFound ) const;

        /**
        * Deprecated since 5.0.
        */
        IMPORT_C TAknSkinSrvSkinPackageLocation LocationOfSkin( const TInt aIndex );

        /**
        * Returns skin index of active skin.
        * @return skin index of active skin.
        */
        IMPORT_C TInt ActiveSkinIndex() const;

        /**
        * Returns skin index of currently highlighted skin.
        * @return skin index of highlighted skin.
        */
        IMPORT_C TInt CurrentSelectedSkinIndex() const;

        /**
        * Returns number of found skins.
        * @return number of found skins.
        */
        IMPORT_C TInt NumberOfSkins() const;

        /**
        * Returns screensaver name array.
        * @return screensaver name array.
        */
        IMPORT_C const MDesC16Array& ScreensaverNames() const;

        /**
        * Checks if selected screensaver has the requested capability
        * @param aIndex index of screensaver in screensaver array.
        * @param aCapability requested capability.
        * @return ETrue if screensaver has the capability, EFalse otherwise.
        */
        IMPORT_C TBool ScreensaverHasCapability(
            const TInt aIndex,
            const TScPluginCaps aCapability ) const;

        /**
        * Returns protection type of skin.
        * @param aIndex skin index to use.
        * @return protection type of skin.
        */
        IMPORT_C TAknsSkinSrvSkinProtectionType ProtectionOfSkin(
            const TInt aIndex );

        /**
        * Checks if the skin can be activated.
        * @param aItemIndex skin index to use.
        * @return ETrue, if skin can be activated.
        */
        IMPORT_C TBool IsValidForActivation( const TInt aItemIndex );

        /**
        * Checks if the skin can be previewed.
        * @param aItemIndex skin index to use.
        * @return ETrue, if skin can be previewed.
        */
        IMPORT_C TBool IsValidForPreview( const TInt aItemIndex );
        
        /**
        * Checks if the skin support animated background.
        * @param aItemIndex skin index to use.
        * @return ETrue, if skin support animation background.
        */
        IMPORT_C TBool IsSupportAnimBg( TInt aItemIndex );

        /**
        * Sets the given skin index as currently highlighted one.
        * @param aCurrentSkinIndex skin index.
        */
        IMPORT_C void SetCurrentSelectedSkinIndex(
            const TInt aCurrentSkinIndex );

        /**
        * Deprecated.
        */
        IMPORT_C TInt SetCurrentPropertyType( const TInt aProperty,
            const TInt aCurItemIndex );

        /**
        * Gets currently active index of given property.
        * @param aProperty property type - either wallpaper or screensaver.
        * @return index of currently active property, or error code.
        */
        IMPORT_C TInt CurrentPropertyIndex( const TInt aProperty );

        /**
        * Enables (or disables) notifications from ECOM framework.
        * When ECOM state is changed, PslnModel will check that it's 
        * screensaver list is up to date. Changes in the list are 
        * indicated to observer class.
        * @param aActive if ETrue, notifications are subscribed, otherwise
        *                subscription is terminated.
        * @param aObserver observer for notifications.
        */
        IMPORT_C void EnableScreenSaverNotifications( 
            const TBool& aActive, 
            MPslnScreenSaverECOMObserver& aObserver );

        /**
        * Deprecated.
        */
        IMPORT_C TBool ActivateSkinL(
            const TDesC8& aPreviewType,
            const TInt aActiveSkinIndex, 
            const TBool& aActivateFromPreview );
            
        /**
        * Activates the entire skin.
        * @since 3.2
        * @param aActiveSkinIndex skin index of active skin.
        * @return ETrue, if skin activation is successful.
        */    
        IMPORT_C TBool ActivateSkinL( const TInt aActiveSkinIndex );            

        /**
        * Gets currently active index of given property. 
        * This is leaving version of CurrentPropertyIndex (see above).
        * @param aProperty property type - either wallpaper or screensaver.
        * @return index of currently active property, or error code.
        */
        IMPORT_C TInt CurrentPropertyIndexL( const TInt aProperty );

        /**
        * Sets transition effects enabled/disabled as given in the parameter.
        * @param aEffectValue used as bitmask. Value of zero enables all effects, 
        *                     and value of KMaxTInt disables all effects.
        *                     All other values are considered as invalid.
        * @return KErrArgument if aEffectValue is not zero or KMaxTInt.
        *         Otherwise return value is what is given out by CRepository::Set().
        * 
        * @since 3.2
        */
        IMPORT_C TInt SetTransitionEffectsL( const TInt aEffectValue );

        /**
        * Gets current transition effect value.
        * @return in error cases returns KErrNotFound, 
        *         otherwise returns current repository value.
        *        
        * @since 3.2
        */
        IMPORT_C TInt GetTransitionEffectStateL();

        /**
        * Checks if the screensaver is installed on memory card.
        * @param aScreensaverIndex screensaver index
        * @return ETrue, if screensaver is installed to the memory card.
        * 
        * @since 3.2
        */
        IMPORT_C TBool IsScreenSaverOnMemoryCard( const TInt aIndex ) const;

        /**
        * Sets a given property (wallpaper or screensaver) as active.
        * @param aProperty property type - either wallpaper or screensaver.
        * @param aCurItemIndex item index that is currently active.
        * @return KErrNone always.
        *
        * @since 3.2
        */
        IMPORT_C void SetCurrentPropertyTypeL( const TInt aProperty,
            const TInt aCurItemIndex );

        /**
        * Checks if a skin with given index is on memory card,
        * @param aIndex skin index from application.
        * @return ETrue if skin is on memory card, EFalse otherwise.
        *
        * @since 5.0
        */
        IMPORT_C TBool IsThemeOnMemoryCard( const TInt& aIndex );

        /**
        * Checks if a skin with given index is on mass drive,
        * @param aIndex skin index from application.
        * @return ETrue if skin is on memory card, EFalse otherwise.
        *
        * @since 5.0
        */
        IMPORT_C TBool IsThemeOnMassDrive( const TInt& aIndex );

        /**
        * Checks if the screensaver is installed on mass drive.
        * @param aScreensaverIndex screensaver index
        * @return ETrue, if screensaver is installed to the mass drive.
        * 
        * @since 5.0
        */
        IMPORT_C TBool IsScreenSaverOnMassDrive( const TInt& aIndex ) const;

        /**
        * Returns skin server session.
        * @return skin server session.
        * 
        * @since 3.2
        */
        IMPORT_C RAknsSrvSession SkinSrvSession() const;

        /**
        * Starts or stops transition effects.
        * 
        * @param aAction specifies actions for transition effects. 
        * The value can be one of the values defined in TPslnTransitionEffectAction.
        * @since 3.2
        */
        IMPORT_C void TransEffect(TInt aAction) const;

        /**
        * Set current screensaver to default screensaver.
        */
        IMPORT_C void SetScreenSaverToDefault();
        
		/**
        * Set Animated Background state
		* @param aValue specifies actions for animation background. 
        * 0 mean enable animation effect, KMaxTInt means disable all animation effect.
        * @since 9.2
        */
        IMPORT_C TInt SetAnimBackground( TInt aValue );
		
		/**
        * Get Animated Background state.
		*
		* @return 0, if animation is enable; KMaxTInt if animation is disable.
        * @since 9.2
        */
        IMPORT_C TInt AnimBackgroundState() const;        

        
    private:

        /**
        * Gets the separately localized name of the skin, if any.
        * @param aPID package ID to use.
        * @param aSkinName localized skin name.
        * @param aType which skin name to fetch (list/title name).
        * @return ETrue, if localized skin name was found.
        */
        TBool GetSeparatelyLocalizedSkinName(
            const TAknsPkgID aPID, TDes& aSkinName,
            const TPslnSkinNameType aType ) const;


        /**
        * Default C++ contructor
        */
        CPslnModel();

        /**
        * Symbian default constructor
        */
        void ConstructL( MAknsSkinChangeObserver* aObserver );

        /**
        * Loads the separately localized skin names resource.
        */
        void LoadSkinNamesResourceL();

        /**
        * Finds screensavers from the given path and appends them to the
        * screensaver list.
        * @return ETrue if screensavers were found, EFalse otherwise.
        */
        TBool FindAndAppendScreensaversL();

        /**
        * Updates the skin information from the server and
        * the list of visible skins.
        */
        void UpdateFromServerL();

        /**
        * Updates the list of visible skins.
        */
        void UpdateVisibleSkinListL();

        /**
        * Activates skin that is currently selected.
        */
        void SetActiveSkinL();

        /**
        * Launches query dialog for screensaver name.
        * @return EFalse, if user cancelled the query.
        */
        TBool QueryAndSetScreensaverTextL();

        /* Gets full name of skin. */
        const TDesC& GetSkinFullName( const TInt aItemIndex );
    
        /* Gets the name of the skin. */
        void GetSkinNameByPID( const TAknsPkgID aPID, TDes& aSkinName,
            const TPslnSkinNameType aType ) const;

        /* Activates default skin. */
        void ActivateDefaultSkinL();

        /* Gets default text for text screensaver. */
        void GetDefaultTextToScreensaverL( TDes& aDisplayText );

        /* Gets wallpaper item index. */
        TInt GetWallPaperItemIndex();

        /* Gets wallpaper item index. */
        TInt GetScreenSaverItemIndexL();
        
        /* Find the aFileName in iScreensaverFilenameArr, and return the index */
        TInt GetScreenSaverIndexByFileName(const TDesC &aFileName) const;
        
        /* Get screen saver object type from index */
        TInt GetScreensaverTypeByIndex(TInt aIndex);

        /* Loads AknsWallpaperUtils to memory. */
        void LoadWallpaperUtilsL();

        /* Strips file path information from screensaver UID. */
        TPtrC GetRealScreenSaverUid( const TInt aIndex );

        /* Leaving version of ActivateScreenSaver. */
        void ActivateScreenSaverL( 
            const TInt aItemIndex, 
            TPslnScreenSaverActivation aActivationType );

        /* Loads browser launcher dll to memory. */
        void LoadBrowserLaunchL();        

        /**
        * Checks the status of the skin file.
        * @param aIndex skin index from application.
        * @return ETrue if skin file is exist and can be accessed.
        *   EFalse if an error occured or didn't exist.
        */
        TBool SkinFileExist( const TInt& aIndex  );
        
        /**
        * From MCenRepNotifyHandlerCallback.
        */
        void HandleNotifyInt(TUint32 aId, TInt aNewValue);
        
        /* Gets transition effect value and initialize CenRep notify handler. */
        void InitTransitionEffectVauleL();
        
        /* if KPslnSupportScreenSaverSelectionNone is supported return true, or false */
        TBool IsSupportScreenSaverNoneOption() const;
        
    private: // Data

        /*
        * Skin store.
        * Own.
        */
        CPslnSkinStore* iSkinStore;

        /*
        * Array of visible skins.
        * Own.
        */
        RPointerArray<CPslnSkinNameEntry>* iVisibleSkinArr;

        /*
        * Skin server session.
        */
        RAknsSrvSession iSkinSrvSession;

        /*
        * CenRep object for skin keys.
        * Own.
        */
        CRepository* iSkinsRepository;

        /*
        * CenRep object for screen saver keys.
        * Own.
        */
        CRepository* iScreenSaverRepository;

        /*
        * CenRep object for themes application keys.
        * Own.
        */
        CRepository* iThemesAppRepository;

        /*
        * Pointer to eikon environment. Stored to avoid repeated fetches.
        * Not own.
        */
        CEikonEnv* iEikEnv;

        /*
        * Currently highlighted skin index.
        */
        TInt iCurrentSkinIndex;

        /*
        * Active skin index.
        */
        TInt iActiveSkinIndex;

        /*
        * Array of skin names.
        */
        RArray<TPslnSkinNameEntry> iSkinNames;

        /*
        * Array of screensaver filenames.
        * Own.
        */
        CDesC16ArrayFlat* iScreensaverFilenameArr;

        /*
        * Array of screensaver names.
        * Own.
        */
        CDesC16ArrayFlat* iScreensaverNameArr;

        /*
        * Array of screensaver capabilities.
        */
        RArray<TInt> iScreensaverCapsArr;

        /*
        * Active screensaver information.
        * Own.
        */
        CPslnScreenSaverInfo* iScreenSaverInfo;

        /*
        * A handle to a dynamically loadable DLL.
        */
        RLibrary iWallpaperDll;

        /*
        * Loads Wallpaper Utils DLL dynamically to memory.
        * Allows use of the DLL through this pointer, but only for
        * methods implemented within the wrapper.
        * Own.
        */
        CPslnWallpaperUtilsLoader* iWallpaperSetter;

        /**
         * Listens to ECOM for screensaver plugin changes.
         * Own.
         */
        CPslnEcomListener* iScreenSaverListener;

        /*
        * A handle to a dynamically loadable DLL.
        */
        RLibrary iBrowserLaunchDll;

        /*
        * Loads Wallpaper Utils DLL dynamically to memory.
        * Allows use of the DLL through this pointer, but only for
        * methods implemented within the wrapper.
        * Own.
        */
        CPslnBrowserLaunchLoader* iBrowserLauncher;

        /*
        * Internal state of the class.
        */
        enum TPslnModelState
            {
            // initial state
            EPslnModelStateInitial = 0x00000000,
            // wallpaper dll has been loaded
            EPslnModelStateWallpaperDllLoaded = 0x00000001,
            // has the default enable CR key for transition effects been read
            EPslnModelStateTransitionEnableCRKeyRead = 0x00000002,
            // is skin being previewed
            EPslnModelStateSkinPreviewed = 0x00000004,
            // browser launch dll has been loaded
            EPslnModelStateBrowserLaunchDllLoaded = 0x00000008,
            // localized skin names have been loaded
            EPslnModelStateSkinNamesLoaded = 0x00000010
            };
        TBitFlags iInternalState;

        /**
        * Default mask for enable transition effects.
        */
        TInt iEffectsDefaultEnableMask;
        
        /**
        * Transition effect setting value.
        */
        TInt iTransitionEffectValue;
        
        /**
        * A pointer to Central Repository notification handling.
        * Used to monitor the change of KThemesTransitionEffects.
        * Own.
        */
        CCenRepNotifyHandler *iThemesAppCenRepNotifyHandler;
    };

#endif // C_PSLNMODEL_H

// End of File
