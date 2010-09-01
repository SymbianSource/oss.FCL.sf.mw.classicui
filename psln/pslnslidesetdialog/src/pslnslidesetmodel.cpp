/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Model class for slide set dialog.
*
*/


// Central repository.
#include <centralrepository.h>
#include <pslninternalcrkeys.h>
#include "PslnVariationPrivateCRKeys.h"
#include "PslnVariant.hrh"
#include <AknSkinsInternalCRKeys.h>

// Notes & Dialogs
#include <AknGlobalNote.h>
#include <aknnotewrappers.h>

// Skin server.
#include <AknsWallpaperUtils.h>
#include <AknsSrvClient.h>

// Generic.
#include <bautils.h>

// Psln Slide set specific.
#include <pslnslidesetdialoginterface.h>
#include "pslnslidesetmodel.h"
#include "pslnslidesetconst.hrh"
#include "pslnslidesetconst.h"
#include <pslnslidesetdialogrsc.rsg>

// Slide set duration default value: 5 seconds.
const TInt KPslnSlideSetDefaultDuration = 5;
// Slide set backlight default value: off.
const TInt KPslnSlideSetBacklightOff = 0;
// Slide set interval default value: 10min.
const TInt KPslnSlideSetDefaultInterval = EPslnSlideSetInterval10Min;
// Slide set minimum duration is 5 second.
const TInt KPslnSlideSetMinDuration = 5;
// Slide set maximum duration is 60 seconds.
const TInt KPslnSlideSetMaxDuration = 60;
// Slide set maximum backlight period is 30secs.
const TInt KPslnSlideSetMaxBacklight = 30;
// Slide set minimum interval period is 1 min.
const TInt KPslnSlideSetMinInterval = EPslnSlideSetInterval1Min;
// Slide set maximum interval period is 1 day.
const TInt KPslnSlideSetMaxInterval = EPslnSlideSetInterval1Day;


// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnSlideSetModel::CPslnSlideSetModel() : iImageListChanged ( EFalse )
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CPslnSlideSetModel::ConstructL()
    {
    iRepository = CRepository::NewL( KCRUidThemes );
    iCoeEnv = CCoeEnv::Static();
    }

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CPslnSlideSetModel* CPslnSlideSetModel::NewL()
    {
    CPslnSlideSetModel* self = CPslnSlideSetModel::NewLC();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Two-phased constructor. Same as above, but leaves object to the 
// cleanup stack.
// ---------------------------------------------------------------------------
//
CPslnSlideSetModel* CPslnSlideSetModel::NewLC()
    {
    CPslnSlideSetModel* self = new( ELeave ) CPslnSlideSetModel;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CPslnSlideSetModel::~CPslnSlideSetModel()
    {
    delete iRepository;
    }

// ---------------------------------------------------------------------------
// Returns current selection for slide set type: random / image set.
// ---------------------------------------------------------------------------
//
TInt CPslnSlideSetModel::GetSlideSetType( const TInt aSlideSetType ) const
    {
    TInt imageSelection = KErrNotFound;

    TInt error = KErrNone;
    if ( aSlideSetType == EPslnScreensaverDialog )
        {
        error = iRepository->Get( 
            KThemesScreenSaverSlideSetType, 
            imageSelection );
        }
    else
        {
        error = iRepository->Get( 
            KThemesWallpaperSlideSetType, 
            imageSelection );
        }
    // In case of error, or invalid value, just return default value.
    if ( error != KErrNone ||
         ( imageSelection != KPslnSlideSetRandomIndex && 
           imageSelection != KPslnSlideSetImageSelImageSet ) )
        {
        if ( aSlideSetType == EPslnScreensaverDialog )
            {
            return KPslnSlideSetRandomIndex;
            }
        else
            {
            return KPslnSlideSetImageSelImageSet;
            }
        }
    return imageSelection;
    }

// ---------------------------------------------------------------------------
// Sets slide set type (random/image set).
// ---------------------------------------------------------------------------
//
TInt CPslnSlideSetModel::SetSlideSetType( 
        const TInt aSlideSetType, const TInt aValue )
    {
    TInt error = KErrNone;

    TInt prevValue = KErrNone; 
    if ( aSlideSetType == EPslnScreensaverDialog )
        {
        error = iRepository->Get( KThemesScreenSaverSlideSetType, prevValue );
        }
    else
        {
        error = iRepository->Get( KThemesWallpaperSlideSetType, prevValue );            
        }
    
    // Validate that value is valid and changed.
    if ( ( aValue == KPslnSlideSetImageSelImageSet || 
           aValue == KPslnSlideSetRandomIndex ) &&
         ( prevValue != aValue ) )
        {
        // Store selection.
        if ( aSlideSetType == EPslnScreensaverDialog )
            {
            error = iRepository->Set( KThemesScreenSaverSlideSetType, aValue );
            }
        else
            {
            error = iRepository->Set( KThemesWallpaperSlideSetType, aValue );
            }
        }
    else
        {
        error = KErrArgument;
        }
    return error;
    }

// ---------------------------------------------------------------------------
// Returns current selection for screensaver slide set duration.
// ---------------------------------------------------------------------------
//
TInt CPslnSlideSetModel::GetSlideSetDuration() const
    {
    TInt slideSetDuration = KPslnSlideSetDefaultDuration;
    TInt error = KErrNone;
    error = iRepository->Get( 
        KThemesScreenSaverSlideSetDuration, 
        slideSetDuration );
    if ( error != KErrNone )
        {
        // return default value in case of error.
        return KPslnSlideSetDefaultDuration;
        }
    return slideSetDuration;
    }

// ---------------------------------------------------------------------------
// Sets screensaver slide set duration.
// ---------------------------------------------------------------------------
//
TInt CPslnSlideSetModel::SetSlideSetDuration( const TInt aValue )
    {
    TInt error = KErrNone;
    TInt prevValue = KErrNone; 
    error = iRepository->Get( KThemesScreenSaverSlideSetDuration, prevValue );

    // Validate value and check that new value is different from previous
    // value.
    if ( ( aValue >= KPslnSlideSetMinDuration && 
           aValue <= KPslnSlideSetMaxDuration ) &&
         ( prevValue != aValue ) )
        {
        error = iRepository->Set( 
            KThemesScreenSaverSlideSetDuration, 
            aValue );
        }
    else
        {
        error = KErrArgument;
        }
    return error;
    }

// ---------------------------------------------------------------------------
// Returns current selection for screensaver slide set backlight period.
// ---------------------------------------------------------------------------
//
TInt CPslnSlideSetModel::GetSlideSetBacklight() const
    {
    TInt slideSetBacklight = KPslnSlideSetBacklightOff;
    TInt error = KErrNone;
    error = iRepository->Get( 
        KThemesScreenSaverSlideSetBacklight, 
        slideSetBacklight );
    if ( error != KErrNone )
        {
        // return default value in case of error.
        return KPslnSlideSetBacklightOff;
        }
    return slideSetBacklight;
    }

// ---------------------------------------------------------------------------
// Sets screensaver slide set backlight period.
// ---------------------------------------------------------------------------
//
TInt CPslnSlideSetModel::SetSlideSetBacklight( const TInt aValue )
    {
    TInt error = KErrNone;
    TInt prevValue = KErrNone; 
    error = iRepository->Get( KThemesScreenSaverSlideSetBacklight, prevValue );

    if ( ( aValue >= KPslnSlideSetBacklightOff ||
           aValue <= KPslnSlideSetMaxBacklight ) &&
         ( prevValue != aValue ) )
        {
        error = iRepository->Set( 
            KThemesScreenSaverSlideSetBacklight, 
            aValue );
        }
    else
        {
        error = KErrArgument;
        }
    return error;
    }

// ---------------------------------------------------------------------------
// Returns current selection for wallpaper slide set image change interval.
// ---------------------------------------------------------------------------
//
TInt CPslnSlideSetModel::GetSlideSetInterval() const
    {
    TInt slideSetInterval = KPslnSlideSetDefaultInterval;
    TInt error = KErrNone;
    error = iRepository->Get( 
        KThemesWallpaperSlideSetInterval, 
        slideSetInterval );
    if ( error != KErrNone )
        {
        // return default value in case of error.
        return KPslnSlideSetDefaultInterval;
        }
    return slideSetInterval;
    }

// ---------------------------------------------------------------------------
// Sets wallpaper slide set image change period.
// ---------------------------------------------------------------------------
//
TInt CPslnSlideSetModel::SetSlideSetInterval( const TInt aValue )
    {
    TInt error = KErrNone;
    TInt prevValue = KErrNone; 
    error = iRepository->Get( KThemesWallpaperSlideSetInterval, prevValue );

    if ( ( aValue >= KPslnSlideSetMinInterval ||
           aValue <= KPslnSlideSetMaxInterval ) && 
         ( prevValue != aValue ) )
        {
        error = iRepository->Set( KThemesWallpaperSlideSetInterval, aValue );
        }
    else
        {
        error = KErrArgument;
        }
    return error;
    }

// ---------------------------------------------------------------------------
// Stores list of image filenames to be used as slide set image set.
// ---------------------------------------------------------------------------
//
void CPslnSlideSetModel::SetImageListL( const TInt aSlideSetType, 
    CDesCArray& aSelectedFiles, const TInt aLaunchMode )
    {
    if ( aSlideSetType == EPslnWallpaperDialog )
        {
        if ( aLaunchMode == CPslnSlidesetDialogInterface::EPslnNormal )
            {
            TInt retVal = 
                AknsWallpaperUtils::SetSlidesetWallpaper( aSelectedFiles, NULL );
            if ( retVal != KErrNone )
                {
                // Show information note about image
                HBufC* prompt = iCoeEnv->AllocReadResourceLC( 
                        R_PSLN_SLIDE_SET_IMAGE_CORRUPTED );
                CAknInformationNote* note = 
                    new (ELeave) CAknInformationNote( ETrue );
                note->ExecuteLD( *prompt );
                CleanupStack::PopAndDestroy( prompt );
                }
            }
        // Write file names to file, if configuring only.
        else
            {
            TInt fileType = EAknsSrvInifileSSWP;
            StoreImageListToFileL( fileType, aSelectedFiles );
            }
        }
    else
        {
        TInt fileType = EAknsSrvInifileSSSS;
        StoreImageListToFileL( fileType, aSelectedFiles );
        }
    iImageListChanged = ETrue;
    }

// ---------------------------------------------------------------------------
// Check if the image file exists.
// ---------------------------------------------------------------------------
//
TBool CPslnSlideSetModel::SlideSetImageFileExistsL( 
    const TInt aSlideSetType ) const
    {    
    // Get file from server.
    RFile imgFile;
    OpenImageFileL( imgFile, aSlideSetType );
    CleanupClosePushL( imgFile );

    // Check if the file exists.
    TInt fileSize = 0;
    TBool retValue = EFalse;
    User::LeaveIfError( imgFile.Size( fileSize ) );

    // If file has size, then it exists.
    if ( fileSize > 0 )
        {
        retValue = ETrue;
        }

    CleanupStack::PopAndDestroy(); // imgFile
    return retValue;
    }

// ---------------------------------------------------------------------------
// Indicates whether or not setting values have been updated.
// ---------------------------------------------------------------------------
//
TBool CPslnSlideSetModel::HasDialogUpdatedValues() const
    {
    return iImageListChanged;
    }

// ---------------------------------------------------------------------------
// Counts how many images have been selected.
// ---------------------------------------------------------------------------
//
TInt CPslnSlideSetModel::GetImageCountInSlideSetL( 
    const TInt aSlideSetType ) const
    {
    // Get file from server.
    RFile imgFile;
    OpenImageFileL( imgFile, aSlideSetType );
    CleanupClosePushL( imgFile );

    TInt fileSize = 0;
    TInt imageCount = 0;
    User::LeaveIfError( imgFile.Size( fileSize ) );
    
    // If file size is zero => no images.
    if ( fileSize > 0 )
        {
        TFileText textFile;
        textFile.Set( imgFile );
        textFile.Seek( ESeekStart );
        
        RFs& fs = CCoeEnv::Static()->FsSession();
        // Count images from file.
        FOREVER
            {
            TFileName filename;
            if( textFile.Read( filename ) != KErrNone )
                {                
                break;
                }
            if ( BaflUtils::FileExists(fs, filename) )
            	{
            	imageCount++;
            	}
            }
        }
    CleanupStack::PopAndDestroy(); // imgFile
    return imageCount;
    }

// ---------------------------------------------------------------------------
// Sets feature support - see pslnslidesetconst.h for feature list.
// ---------------------------------------------------------------------------
//
void CPslnSlideSetModel::GetFeatureSupportL( TBitFlags& aFeatureBitFlags ) const
    {
    CRepository* featureRep = CRepository::NewLC( KCRUidThemesVariation );
    TInt value = KErrNone;
    featureRep->Get( KThemesLocalVariation, value );

    aFeatureBitFlags.ClearAll();

    //map value to feature flags
    if ( value & KPslnRandomSlideSets )
        {
        aFeatureBitFlags.Set( EPslnSlideSetFeatureRandom );
        }
    if ( value & KPslnRemoveSlideSetTimeout )
        {
        aFeatureBitFlags.Set( EPslnSlideSetBacklightRemoved );
        }

    CleanupStack::PopAndDestroy( featureRep );
    }

// ---------------------------------------------------------------------------
// Stores slide set image file names to file.
// ---------------------------------------------------------------------------
//
void CPslnSlideSetModel::StoreImageListToFileL( 
    const TInt aSlideSetType, CDesCArray& aSelectedFiles  ) const
    {
    // Get file from server.
    RFile imgFile;
    OpenImageFileL( imgFile, aSlideSetType );
    CleanupClosePushL( imgFile );
    User::LeaveIfError( imgFile.SetSize( 0 ) ); // possibly wipe existing file 

    // Finally, write image filenames to the file.
    TFileText textFile;
    textFile.Set( imgFile );
    textFile.Seek( ESeekStart );

    for ( TInt imgCount = 0; imgCount < aSelectedFiles.Count(); imgCount++ )
        {
        User::LeaveIfError( 
            textFile.Write( aSelectedFiles.MdcaPoint( imgCount ) ) );
        }
    imgFile.Flush();

    CleanupStack::PopAndDestroy(); // imgFile
    }

// ---------------------------------------------------------------------------
// Open image list file for operations.
// ---------------------------------------------------------------------------
//
void CPslnSlideSetModel::OpenImageFileL( RFile& aImageFile, const TInt aSlideSetType ) const
    {
    // First, connect to skin server.
    RAknsSrvSession skinsrv;
    User::LeaveIfError( skinsrv.Connect() );
    CleanupClosePushL( skinsrv );

    // Then get file handle.
    TInt fileserverhandle = 0;
    TInt filehandle = 0;
    // Validate type and open image file.
    if ( aSlideSetType == EAknsSrvInifileSSWP )
        {
        fileserverhandle = 
            skinsrv.OpenImageInifile( EAknsSrvInifileSSWP, filehandle );
        }
    else
        {
        fileserverhandle = 
            skinsrv.OpenImageInifile( EAknsSrvInifileSSSS, filehandle );

        }
    if ( fileserverhandle <= 0 || filehandle == 0 )
        {
        User::Leave( fileserverhandle );
        }

    // Finally adopt file from server.
    User::LeaveIfError( aImageFile.AdoptFromServer( fileserverhandle, filehandle ) );
    CleanupStack::PopAndDestroy(); // skinsrv
    }

// End of file
