/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Activates sound content, if part of the skin.
*
*/


// INCLUDE FILES
#include <AknsUtils.h>
#include <AknsSrvClient.h>
#include <pathinfo.h>
#include <driveinfo.h>
#include <eikenv.h>

// Psln specific.
#include "pslnprofilesettingsloader.h"
#include "PslnSoundActivator.h"
#include "PslnConst.h"
#include "PslnDebug.h"


// CONSTANTS
// Path and filename of wrapper dll.
_LIT( KPslnProfilesSettingsLoaderName,
    "\\system\\libs\\PslnProfileSettingsLoader.dll");

// TYPE DEFINITIONS
// Profiles tone setter.
typedef TAny* (*NewProfilesSetterL)();

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnSoundActivator::CPslnSoundActivator()
    {
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnSoundActivator* CPslnSoundActivator::NewLC()
    {
    CPslnSoundActivator* self = new( ELeave ) CPslnSoundActivator;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
void CPslnSoundActivator::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CPslnSoundActivator::~CPslnSoundActivator()
    {
    delete iProfilesSetter;
    if( iProfilesDllLoaded )
        {
        iProfilesDll.Close();
        }
    iSoundArray.Reset();
    iSoundArray.Close();
    }

// -----------------------------------------------------------------------------
// CPslnSoundActivator::CollectSoundsL
// -----------------------------------------------------------------------------
//
void CPslnSoundActivator::CollectSoundsL( const TDesC& aSkinPath, TInt& aCount )
    {
    PSLN_TRACE_DEBUG("CPslnSoundActivator::CollectSoundsL BEGIN");
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    if ( !skin )
        {
        return;
        }
    iSoundArray.Reset();

    TInt i = KErrNotFound;
    while( KPslnSoundItems[++i] != KAknsIIDNone )
        {
        CAknsStringItemData* data =
            static_cast<CAknsStringItemData*>(
            skin->CreateUncachedItemDataL(
                KPslnSoundItems[i],
                EAknsITString ) );
        if ( data )
            {
            CleanupStack::PushL( data );

            PSLN_TRACE_DEBUG("CPslnSoundActivator::CollectSoundsL skin item found");
            HBufC* fullName = HBufC::NewLC( KMaxFileName );
            TPtr fullNamePtr = fullName->Des();

            if ( aSkinPath.Length() > 0 )
                {
                FindSoundFile( fullNamePtr, data->String(), aSkinPath );
                }
            else
                {
                PSLN_TRACE_DEBUG("CPslnSoundActivator::CollectSoundsL empty path" );
                // @todo - start going through all the drives available.
                }

            if( fullNamePtr.Length() > 0 )
                {
                PSLN_TRACE_DEBUG("CPslnSoundActivator::CollectSoundsL file found");
                TPslnSoundActivatorEntry entry;
                entry.iFullName = fullNamePtr;
                entry.iID = KPslnSoundItems[i];
                iSoundArray.AppendL( entry );
                }

            CleanupStack::PopAndDestroy( 2, data ); // data, fullName
            }
        }
    aCount = iSoundArray.Count();
    PSLN_TRACE_DEBUG("CPslnSoundActivator::CollectSoundsL END");
    }

// -----------------------------------------------------------------------------
// CPslnSoundActivator::ActivateToProfilesL
// -----------------------------------------------------------------------------
//
void CPslnSoundActivator::ActivateToProfilesL()
    {
    PSLN_TRACE_DEBUG("CPslnSoundActivator::ActivateToProfilesL BEGIN");

    // Profiles tone setter dll loading.
    if( !iProfilesDllLoaded )
        {
        PSLN_TRACE_DEBUG("CPslnSoundActivator::ActivateToProfilesL about load");
        if( iProfilesDll.Load( KPslnProfilesSettingsLoaderName ) == KErrNone )
            {
            PSLN_TRACE_DEBUG("CPslnSoundActivator::ActivateToProfilesL loaded");
            iProfilesDllLoaded = ETrue;
            // Request the entry function
            NewProfilesSetterL profilesSetter =
                (NewProfilesSetterL) iProfilesDll.Lookup( KPslnDllEntryPoint );
            if( profilesSetter )
                {
                PSLN_TRACE_DEBUG("CPslnSoundActivator::ActivateToProfilesL create");
                // Create the class
                iProfilesSetter =
                    (CPslnProfileSettingsLoader*) (*profilesSetter)();
                }
            }
        }
    // The wrapper failed to load.
    if ( !iProfilesSetter )
        {
        User::Leave( KErrNotFound );
        }

    MoveSoundFilesL();

    // Activate all tones to all profiles.
    for( TInt i = 0; i < iSoundArray.Count(); i++ )
        {
        TPslnSoundActivatorEntry entry = iSoundArray[i];
        PSLN_TRACE_DEBUG1("CPslnSoundActivator::ActivateToProfilesL tone %d", i);
        PSLN_TRACE_DEBUG1("CPslnSoundActivator::ActivateToProfilesL minor ID %d", entry.iID.iMinor);
        PSLN_TRACE_DEBUG1("CPslnSoundActivator::ActivateToProfilesL name lenght %d ", iSoundArray[i].iFullName.Length() );
        iProfilesSetter->SetToneForProfilesL(
            entry.iID.iMinor,
            entry.iFullName );
        }
    }

// -----------------------------------------------------------------------------
// CPslnSoundActivator::FindSoundFile
// -----------------------------------------------------------------------------
//
void CPslnSoundActivator::FindSoundFile(
    TDes& aFullName, const TDesC& aSoundFile, const TDesC& aSkinPath )
    {
    aFullName.Copy( aSkinPath );
    aFullName.Append( aSoundFile );
    }

// -----------------------------------------------------------------------------
// CPslnSoundActivator::MoveSoundFilesL
// -----------------------------------------------------------------------------
//
void CPslnSoundActivator::MoveSoundFilesL()
    {
    RAknsSrvSession skinsrv;
    User::LeaveIfError( skinsrv.Connect() );
    CleanupClosePushL( skinsrv );

    RFs& fs = CEikonEnv::Static()->FsSession();

    for( TInt i = 0; i < iSoundArray.Count(); i++ )
        {
        TPslnSoundActivatorEntry entry = iSoundArray[i];

        HBufC* targetPath = NULL;
        TFileName filename;
       
        // Sort out path to which store the sound file.
        TInt driveId;
        User::LeaveIfError( 
            RFs::CharToDrive( entry.iFullName[0], driveId ) );

        TUint driveStatus;
        User::LeaveIfError( 
            DriveInfo::GetDriveStatus( fs, driveId, driveStatus ) );

        if ( driveStatus & DriveInfo::EDriveReadOnly )
            {
            // If ROM, then let's store to phone memory.
            User::LeaveIfError(
                DriveInfo::GetDefaultDrive( 
                    DriveInfo::EDefaultPhoneMemory, 
                    driveId ) );
            }

        User::LeaveIfError( 
            PathInfo::GetRootPath( filename, driveId ) );       
        filename.Append( PathInfo::SoundsPath() );
        targetPath = filename.AllocLC();

        TParsePtrC parse( entry.iFullName );
        TFileName* targetFile = new (ELeave) TFileName;
        CleanupStack::PushL( targetFile );
        targetFile->Copy( *targetPath );
        targetFile->Append( parse.NameAndExt() );

        skinsrv.CopySoundFile( entry.iFullName, *targetFile );
        if ( iProfilesSetter )
            {
            PSLN_TRACE_DEBUG("CPslnSoundActivator::MoveSoundFilesL indicate to mgx");
            PSLN_TRACE_DEBUG1("CPslnSoundActivator: Move to \"%S\" ", targetFile );

            iProfilesSetter->IndicateFileUpdationL( *targetFile );
            }
        iSoundArray[i].iFullName = *targetFile;
        PSLN_TRACE_DEBUG1("CPslnSoundActivator: Move2 lenght %d ", iSoundArray[i].iFullName.Length() );
        CleanupStack::PopAndDestroy( 2, targetPath );
        }
    CleanupStack::PopAndDestroy(); //skinsrv
    }

//  End of File
