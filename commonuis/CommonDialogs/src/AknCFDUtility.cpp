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
* Description:  Utility class to provide common functionalities internally.
*
*/



#include <coemain.h>
#include <bautils.h>
#include <AknIconArray.h>
#include <eikenv.h>
#include <AknsUtils.h>
#include <gulicon.h>
#include <fbs.h>
#include <driveinfo.h>
#include <StringLoader.h>
#include <commondialogs.rsg>
#include "AknCFDUtility.h"
#include <AknUtils.h>

_LIT(KFreeFormate, "%.1f");

const TInt KListBoxEntryMaxLength( KMaxFileName + 32 );
const TInt KFreeLen = 10; 
const TInt KNoIndex = -1;
const TInt KHundredNum = 100;
const TInt KThousandNum = 1024;
const TInt KMegaNum = 1024*1024;
const TInt KGigaNum = 1024*1024*1024;
// ======== MEMBER FUNCTIONS ========

#pragma message("TODO: CFDUtilityDUMMY is still not updated identical to CFDUtility")


// ---------------------------------------------------------------------------
// AknCFDUtility::DriveInfoL
// aDriveInfo.iDriveStatus is set according the error code given by RFs
// functions. Drive status differs slightly from RFs error codes. This is
// because CFD functionality does need most of the error codes. Few drive
// status codes are sufficient. This should simplify CFD error handling.
// ---------------------------------------------------------------------------
//
TInt AknCFDUtility::DriveInfoL( const TDriveNumber aDriveNumber,
                            TCFDDriveInfo& aDriveInfo)
    {
    TInt error;
    TFullName fsName;
    TDriveInfo driveInfo;
    TVolumeInfo volumeInfo;
        
    aDriveInfo.iVolumeLabel.Des().Zero();
    aDriveInfo.iDriveNumber = aDriveNumber;
    aDriveInfo.iDiskSpace = KDiskSpaceNotAvailable;
    aDriveInfo.iMediaType = EMediaNotPresent;
    aDriveInfo.iDriveStatus = EDriveOK;

    //iConnectionState: KMountStronglyConnected, KMountNotConnected
    aDriveInfo.iConnectionState = NULL;
    aDriveInfo.iStatus = NULL;

    RFs& fs = CCoeEnv::Static()->FsSession();
    _LIT( KFat, "Fat" );
    
    // Check drive's media status
    error = DriveInfo::GetDriveStatus( fs, aDriveNumber, aDriveInfo.iStatus );
    if( error )
        {
        aDriveInfo.iStatus = DriveInfo::EDriveCorrupt;
        return error;
        }

    // Check if the drive is already mounted
    error = fs.FileSystemName( fsName, aDriveNumber );
    if( error )
        {
        aDriveInfo.iDriveStatus = EDriveNotReady;
        return error;
        }

    // check if MMC already mounted
    if( fsName.Length() == 0 )
        {
        // MMC drive isnt mounted at present, so try it now....
        error = fs.MountFileSystem( KFat, aDriveInfo.iDriveNumber );

        // If it's a locked MMC and the password is already known it'll be
        // unlocked automatically when it's mounted., otherwise the mount will
        // return with KErrLocked.....
        switch( error )
            {
            case KErrNone:
                {
                // OK to continue...
                break;
                }
            case KErrLocked:
                {
                aDriveInfo.iDriveStatus = EDriveLocked;
                return error;                
                }
            default:
                {
                aDriveInfo.iDriveStatus = EDriveNotReady;
                return error;
               }
            }
        }
    error = fs.Drive( driveInfo, aDriveNumber );
    if( error )
        {
        aDriveInfo.iDriveStatus = EDriveNotReady;
        return error;
        }
    aDriveInfo.iMediaType = driveInfo.iType;

    // MMC is in slot
    if( driveInfo.iMediaAtt & KMediaAttLocked )
        {
        aDriveInfo.iDriveStatus = EDriveLocked;
        return error;
        }
        
    if( driveInfo.iDriveAtt & KDriveAttRemote )
        {
        // Initialize volumeInfo.
        error = fs.Volume( volumeInfo, aDriveNumber );
        volumeInfo.iName.Des().Zero();

        if ( !error )
            {            
            TPtr ptr = volumeInfo.iName.Des();
            // Get remote drive name, RFs::Volume() can only got the name
            // which is less than 11, so use GetDriveName to got the name.
            error = fs.GetDriveName( aDriveNumber, ptr );
            }
        }
    else
        {
        error = fs.Volume( volumeInfo, aDriveNumber );
        }
    
    if( error )
        {
        aDriveInfo.iDriveStatus = EDriveNotReady;
        return error;
        }
        
#pragma message("TODO: Disk space checking for remote drives might need different implementation (CRsfwMountMan?).")

    TInt64 free( volumeInfo.iFree );
    aDriveInfo.iDiskSpace = free;
    aDriveInfo.iVolumeLabel = volumeInfo.iName;

    // If type is remote drive and aConnectionState is required
    if( driveInfo.iDriveAtt & KDriveAttRemote )
        {
//        TChar driveLetter;
//        fs.DriveToChar( aDriveNumber, driveLetter );
//        
//           // This statement migth cause leave.. to be solved
//        CRsfwMountMan* mountMgr = CRsfwMountMan::NewL( 0, NULL );
//        TRsfwMountInfo mountInfo;
//        error = mountMgr->GetMountInfo( driveLetter, mountInfo );
//        delete mountMgr;
//        aDriveInfo.iConnectionState = mountInfo.iMountStatus.iConnectionState;
//        if( error ||
//            mountInfo.iMountStatus.iConnectionState != KMountStronglyConnected )
//            {
//            aDriveInfo.iDriveStatus = EDriveNotReady;
//            return error;
//            }
        }
    return error;
    }


// ---------------------------------------------------------------------------
// AknCFDUtility::DriveStatusL
// ---------------------------------------------------------------------------
//
TCFDDriveStatus AknCFDUtility::DriveStatusL( const TDriveNumber aDriveNumber )
    {
#pragma message("TODO: Find out the actual functions needed for checking drive status - this might be too heavy checking.")

    RFs& fs = CCoeEnv::Static()->FsSession();
    _LIT( KFat, "Fat" );

    // Check if the drive is already mounted
    TFullName fsName;
    TInt error( fs.FileSystemName( fsName, aDriveNumber ) );
    if( error )
        {
        return EDriveNotReady;
        }

    // check if MMC already mounted
    if( fsName.Length() == 0 )
        {
        // MMC drive isnt mounted at present, so try it now....
        error = fs.MountFileSystem( KFat, aDriveNumber );

        // If it's a locked MMC and the password is already known it'll be
        // unlocked automatically when it's mounted., otherwise the mount will
        // return with KErrLocked.....
        switch( error )
            {
            case KErrNone:
                {
                // OK to continue...
                break;
                }
            case KErrLocked:
                {
                return EDriveLocked;
                }
            default:
                {
                return EDriveNotReady;
                }
            }
        }
    TDriveInfo driveInfo;
    error = fs.Drive( driveInfo, aDriveNumber );
    if( error )
        {
        return EDriveNotReady;
        }

    // MMC is in slot
    if( driveInfo.iMediaAtt & KMediaAttLocked )
        {
        return EDriveLocked;
        }

    TVolumeInfo volumeInfo;
    error = fs.Volume( volumeInfo, aDriveNumber );
    if( error )
        {
        return EDriveNotReady;
        }

    // If type is remote drive and aConnectionState is required
    if( driveInfo.iDriveAtt & KDriveAttRemote )
        {
//        TChar driveLetter;
//        fs.DriveToChar( aDriveNumber, driveLetter );
//        // This statement migth cause leave.. to be solved
//        CRsfwMountMan* mountMgr = CRsfwMountMan::NewL( 0, NULL );
//        TRsfwMountInfo mountInfo;
//        error = mountMgr->GetMountInfo( driveLetter, mountInfo );
//        delete mountMgr;
//
//        if( error ||
//            mountInfo.iMountStatus.iConnectionState != KMountStronglyConnected )
//            {
//            return EDriveNotReady;
//            }
        }
    return EDriveOK;
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::DriveNumber
// ---------------------------------------------------------------------------
//
TInt AknCFDUtility::DriveNumber( const TDesC& aPath )
    {
    TDriveUnit unit( aPath );
    return TInt( unit );
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::DirectoryCount
// ---------------------------------------------------------------------------
//
TInt AknCFDUtility::DirectoryCount( const TDesC& aPath )
    {
    TInt pathLength( aPath.Length() );
    if( pathLength == 0 )
        {
        return 0;
        }
    TInt directoryCount( 0 );
    TUint character( 0 );
    for( TInt index( 0 ); index < pathLength; index++ )
        {
        // Find backslash characters from path
        character = aPath[ index ];
        if( character == '\\' )
            {
            directoryCount++;
            }
        }
    // If the path doesn't end to a backslash
    if( character != '\\' )
        {
        // Add folder count with one
        // e.g. "Nokia\Images" would return 1 folder but it should
        // return 2, like "Nokia\Images\" does
        directoryCount++;
        }
    return directoryCount;
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::AddTrailingBackslash
// ---------------------------------------------------------------------------
//
TInt AknCFDUtility::AddTrailingBackslash( TDes& aPath )
    {
    TInt descriptorLength( aPath.Length() );
    if( descriptorLength == 0 )
        {
        return KErrBadDescriptor;
        }
    // Check if path ends to a backslash
    if( aPath[ descriptorLength - 1 ] == '\\' )
        {
        return KErrNone;
        }
    // Check that descriptor has space for one character
    if( aPath.MaxLength() == descriptorLength )
        {
        return KErrOverflow;
        }
    aPath.Append( TChar( '\\' ) );
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::RemoveTrailingBackslash
// ---------------------------------------------------------------------------
//
TInt AknCFDUtility::RemoveTrailingBackslash( TDes& aPath )
    {
    TInt descriptorLength( aPath.Length() );
    if( descriptorLength == 0 )
        {
        return KErrBadDescriptor;
        }
    // Check if path already ends to a backslash
    if( aPath[ descriptorLength - 1 ] == '\\' )
        {
        aPath.Delete( descriptorLength - 1, 1 );
        }
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::AllocateIfValidL
// ---------------------------------------------------------------------------
//
void AknCFDUtility::AllocateIfValidL( HBufC*& aDestination, const TDesC& aSource )
    {
    if( aSource.Length() )
        {
        delete aDestination;
        aDestination = NULL;
        aDestination = aSource.AllocL();
        }
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::AllocateOrNullL
// ---------------------------------------------------------------------------
//
void AknCFDUtility::AllocateOrNullL( HBufC*& aDestination, const TDesC& aSource )
    {
    delete aDestination;
    aDestination = NULL;
    if( aSource.Length() )
        {
        aDestination = aSource.AllocL();
        }
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::AllocateIfNullL
// ---------------------------------------------------------------------------
//
void AknCFDUtility::AllocateIfNullL( HBufC*& aDestination, const TDesC& aSource )
    {
    if( !aDestination )
        {
        AllocateOrNullL( aDestination, aSource );
        }
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::AppendImageToArrayL
// ---------------------------------------------------------------------------
//
void AknCFDUtility::AppendImageToArrayL(
    CEikonEnv& /*aEnv*/, CAknIconArray& aArray,
    const TDesC& aBitmapFile, TInt aBitmapId, TInt aMaskId )
    {
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconLC(
            bitmap, mask, aBitmapFile, aBitmapId, aMaskId );
    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( mask );

    // Ownership is transferred to CGulIcon
    CGulIcon* icon = CGulIcon::NewL( bitmap, mask );

    CleanupStack::Pop( 2 ); // mask, bitmap
    CleanupStack::PushL( icon );
    aArray.AppendL( icon ); // Ownership is transferred to CAknIconArray
    CleanupStack::Pop( icon ); // icon
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::AppendSkinnedImageToArrayL
// ---------------------------------------------------------------------------
//
void AknCFDUtility::AppendSkinnedImageToArrayL( CEikonEnv& /*aEnv*/,
                                             CAknIconArray& aArray,
                                             MAknsSkinInstance* aSkin,
                                             const TAknsItemID& aItemID,
                                             const TDesC& aBitmapFile,
                                             TInt aBitmapId,
                                             TInt aMaskId,
                                             TBool aColorIcon)
    {        
    TRgb defaultColour( KRgbBlack );

    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    if( aColorIcon )      
        {
        AknsUtils::GetCachedColor( aSkin, defaultColour, 
                                KAknsIIDQsnIconColors, 
                                EAknsCIQsnIconColorsCG13 );
        AknsUtils::CreateColorIconLC( aSkin, aItemID, 
                                KAknsIIDQsnIconColors, 
                                EAknsCIQsnIconColorsCG13, bitmap, mask, 
                                aBitmapFile, aBitmapId, aMaskId, 
                                defaultColour );

        // Ownership is transferred to CGulIcon
        CGulIcon* icon = CGulIcon::NewL( bitmap, mask );
        CleanupStack::Pop( 2 ); // mask, bitmap
        CleanupStack::PushL( icon );
        aArray.AppendL( icon ); // Ownership is transferred to CAknIconArray
        CleanupStack::Pop( icon ); // icon 	
        }
    else
        {
        AknsUtils::CreateIconL( aSkin, aItemID, bitmap, mask, aBitmapFile,
                                aBitmapId, aMaskId );
        CleanupStack::PushL( bitmap );
        CleanupStack::PushL( mask );
 
        // Ownership is transferred to CGulIcon
        CGulIcon* icon = CGulIcon::NewL( bitmap, mask );
        CleanupStack::Pop( 2 ); // mask, bitmap
        CleanupStack::PushL( icon );
        aArray.AppendL( icon ); // Ownership is transferred to CAknIconArray
        CleanupStack::Pop( icon ); // icon 	
        }
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::DirectoriesOnly
// ---------------------------------------------------------------------------
//
TBool AknCFDUtility::DirectoriesOnly( TCommonDialogType aType )
    {
    if ( aType == ECFDDialogTypeMove ||
        aType == ECFDDialogTypeSave ||
        aType == ECFDDialogTypeBrowse  ||
        aType == ECFDDialogTypeCopy )
        {
        return ETrue;
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// AknCFDUtility::ReadDynamicDrivesL
// ---------------------------------------------------------------------------
//
void AknCFDUtility::ReadDynamicDrivesL(
    CDesCArrayFlat& aRootPathArray, TInt aIncludedMedias )
    {
//#ifdef _DEBUG
//    CDesCArray* mediaTypeStrings = new (ELeave) CDesCArrayFlat(10);
//    CleanupStack::PushL( mediaTypeStrings );
//
//    // TMediaType enumeration as string representation for debugging.
//    mediaTypeStrings->AppendL( _L( "EMediaNotPresent" ) );
//    mediaTypeStrings->AppendL( _L( "EMediaUnknown" ) );
//    mediaTypeStrings->AppendL( _L( "EMediaFloppy" ) );
//    mediaTypeStrings->AppendL( _L( "EMediaHardDisk" ));
//    mediaTypeStrings->AppendL( _L( "EMediaCdRom" ));
//    mediaTypeStrings->AppendL( _L( "EMediaRam" ));
//    mediaTypeStrings->AppendL( _L( "EMediaFlash" ));
//    mediaTypeStrings->AppendL( _L( "EMediaRom"  ));
//    mediaTypeStrings->AppendL( _L( "EMediaRemote" ));
//    mediaTypeStrings->AppendL( _L( "EMediaNANDFlash" ));
//    _LOG( "[CFDUtility] Drive info: " );
//#endif // _DEBUG
//
//    // Get list of drives dynamically (move this to CFDUtility?)
//    RFs& fs = CCoeEnv::Static()->FsSession();
//    TDriveList driveList;
//
//    CRsfwMountMan* mountMgr = CRsfwMountMan::NewL( 0, NULL );
//    CleanupStack::PushL( mountMgr );
//    mountMgr->GetRemoteMountListL( driveList );
//    CleanupStack::PopAndDestroy( mountMgr );
//
//    _LOG1( "[CFDUtility] driveList:%S", &driveList );
//
//    TChar driveLetter;
//    TInt driveNumber = 0;
//    _LIT( KDrivePath, "%c:\\" );
//    TDriveInfo driveInfo;
//
//    for( TInt i = 0; i < driveList.Length(); i++ )
//        {
//        driveLetter = driveList[ i ];
//        User::LeaveIfError( fs.CharToDrive( driveLetter, driveNumber ) );
//        User::LeaveIfError( fs.Drive( driveInfo, driveNumber ) );
//
//#ifdef _DEBUG
//        TPtrC mediaType( mediaTypeStrings->MdcaPoint( driveInfo.iType ) );
//        _LOG4( "[CFDUtility] %c:, ID:%d, Type:%S (%d)",
//               TUint( driveLetter ),
//               driveNumber,
//               &mediaType,
//               driveInfo.iType );
//#endif // _DEBUG
//        // If drive does not already exist and it is required in included
//        // media types, append drive letter to rootpaths in correct format:
//        if( !DriveAlreadyExists( aRootPathArray, driveLetter ) &&
//            IsIncludedMedia( driveInfo, aIncludedMedias ) )
//            {
//            TBuf<5> driveBuf;            
//            TDesC16 drivePath(KDrivePath);
//            driveBuf.Format( drivePath, &driveLetter );
//            aRootPathArray.AppendL( driveBuf );
//            }
//
//        }
//
//#ifdef _DEBUG
//    CleanupStack::PopAndDestroy( mediaTypeStrings );
//#endif // _DEBUG
    }


// ---------------------------------------------------------------------------
// AknCFDUtility::DriveAlreadyExists
// ---------------------------------------------------------------------------
//
TBool AknCFDUtility::DriveAlreadyExists( CDesCArrayFlat& aRootPathArray,
                                      TChar aDriveLetter )
    {
    // Check that a drive does not already exist in roothpaths. This is done by
    // comparing the first letter in the descriptor. Both compared are
    // converted to upper case before comparison to prevent case mismatch.
    TBool driveAlreadyExists = EFalse;
    aDriveLetter = aDriveLetter.GetUpperCase();
    for( TInt i = 0; i < aRootPathArray.MdcaCount(); i++ )
        {
        TPtrC drive = aRootPathArray.MdcaPoint( i ).Left( 1 );
        TChar driveLetter = drive[0];
        driveLetter = driveLetter.GetUpperCase();
        if( driveLetter == aDriveLetter )
            {
            driveAlreadyExists = ETrue;
            break;
            }
        }
    _LOG1( "[CFDUtility] driveAlreadyExists=%d", driveAlreadyExists );
    return driveAlreadyExists;
    }


// ---------------------------------------------------------------------------
// AknCFDUtility::IsIncludedMedia
// ---------------------------------------------------------------------------
//
TBool AknCFDUtility::IsIncludedMedia( TDriveInfo aDriveInfo,
                                   TInt aIncludedMedias )
    {
    TBool isIncludedMedia = EFalse;
    TMediaType aMediaType = aDriveInfo.iType;

    // Check each included media type bitflag:
    if( aIncludedMedias & AknCommonDialogsDynMem::EMemoryTypePhone )
        {
        // Different memory types mapped to phone memory are not clear.
        // Therefore this is left empty for the time being. However
        // Most application logic is based on division between phone and
        // MMC memory.

        // TODO: Maybe could use EDriveC?
        _LOG( "[CFDUtility] Checking for EMemoryTypePhone" );
        }
    if( aIncludedMedias & AknCommonDialogsDynMem::EMemoryTypeMMC )
        {
        // Different memory types mapped to phone memory are not clear.
        // Therefore this is left empty for the time being. However
        // Most application logic is based on division between phone and
        // MMC memory.

        // TODO: Maybe could use EDriveE?
        _LOG( "[CFDUtility] Checking for EMemoryTypeMMC" );
        }
    if( aIncludedMedias & AknCommonDialogsDynMem::EMemoryTypeRemote )
        {
        _LOG( "[CFDUtility] Checking for EMemoryTypeRemote" );
        if( aMediaType == EMediaRemote )
            {
            isIncludedMedia = ETrue;
            }
        }
    _LOG1( "[CFDUtility] isIncludedMedia=%d", isIncludedMedia );
    return isIncludedMedia;
    }


// ---------------------------------------------------------------------------
// AknCFDUtility::EffectiveDriveCountL
// ---------------------------------------------------------------------------
//
TInt AknCFDUtility::EffectiveDriveCountL()
    {
    // Great! So any drive will be counted except Z: and D: (hey it's simple!)
    // which should not be visible to user in any case. Or should they be:
    // are these just RAM and ROM in S60, not in any Symbian specification???
    // Naturally, C: and E: are also constants extending the Symbian
    // specification.
    // So... Count the drives essential and visible to the user. But if the
    // drive media is not present or it is locked?
    //
    // Check if there are more than one effective drives.

    RFs& fs = CCoeEnv::Static()->FsSession();
    TDriveList driveList;

    // Use new Symbian function to get all drives by using filter flags.
    TInt error = fs.DriveList( driveList, KDriveAttExclude | KDriveAttRom );
    if( error )
        {
        return KErrGeneral;
        }
    
    TInt effectiveDriveCount = 0;
    TCFDDriveStatus driveInfo;
    for( TInt i = 0; i < KMaxDrives; i++ )
        {
        if( driveList[i] && i != EDriveD && i != EDriveZ )
            {
            driveInfo = EDriveNotReady ;
            driveInfo = AknCFDUtility::DriveStatusL( TDriveNumber( i ) );
            // count only if it is available
            if (driveInfo != EDriveNotReady)
                {
                effectiveDriveCount++;
                }
            }
        }
    
    return effectiveDriveCount;
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::IsRemoteDrive
// ---------------------------------------------------------------------------
//
TBool AknCFDUtility::IsRemoteDrive( const TDesC& aDrive )
    {
    TBool ret( EFalse );
    TDriveInfo drvInfo;
    TDriveUnit driveUnit( aDrive);
    RFs& fs = CCoeEnv::Static()->FsSession();

    if ( fs.Drive( drvInfo, TInt( driveUnit) ) == KErrNone )
        {
        if ( drvInfo.iDriveAtt & KDriveAttRemote )
            {
            ret = ETrue;
            }
        }
    return ret;
    }


// ---------------------------------------------------------------------------
// AknCFDUtility::DriveMemoryTypeL
// ---------------------------------------------------------------------------
//
AknCommonDialogsDynMem::TMemoryTypes
    AknCFDUtility::DriveMemoryTypeL( const TDriveNumber& aDrive )
    {
    // Set default value to device memory just in case.
    AknCommonDialogsDynMem::TMemoryTypes
        memoryType( AknCommonDialogsDynMem::EMemoryTypePhone );
     
    TCFDDriveInfo driveInfo;
    AknCFDUtility::DriveInfoL( aDrive , driveInfo );

    // Listbox items are differend depending on the media type.
    if ( driveInfo.iStatus & DriveInfo::EDriveInternal )
        {
        // Internal drives including device memory and internal mass storage
        if ( driveInfo.iStatus & DriveInfo::EDriveExternallyMountable )
            {
            // Internal mass storage drive
            memoryType =
                AknCommonDialogsDynMem::EMemoryTypeInternalMassStorage;
            }
        else
            {
            // Device memory drive
            memoryType = AknCommonDialogsDynMem::EMemoryTypePhone;
            }
        }
    else if( driveInfo.iStatus & DriveInfo::EDriveRemovable  )
        {
        // External MMC
        memoryType = AknCommonDialogsDynMem::EMemoryTypeMMCExternal;
        }
    else if ( ( driveInfo.iStatus & DriveInfo::EDriveRemote )
        && ( driveInfo.iMediaType == EMediaRemote ) )
        // 2 conditions used here just for sure
        {
        // Remote drive
        memoryType = AknCommonDialogsDynMem::EMemoryTypeRemote;
        }
    return memoryType;
    }


// ---------------------------------------------------------------------------
// AknCFDUtility::SetSecondRowTextL
// ---------------------------------------------------------------------------
//
void AknCFDUtility::SetSecondRowTextL( TInt64 aFreeSpace, TDes& aUnitBuf )
    {
    _LIT( KTempString0, "0U" ); //For find "Free: %0U[05] %1U"
    _LIT( KTempString1, "1U" ); //For find "Free: %0U[05] %1U"
    _LIT( KDefinedString, "qtn_memc_free_memory_var_units_dot" );
    TReal64 tempNum = aFreeSpace;   
    HBufC* unitBuf = NULL;
    HBufC* loadBuf = NULL;
    HBufC* tempBuf1 = HBufC::NewLC( KListBoxEntryMaxLength );
    HBufC* tempBuf2 = HBufC::NewLC( KListBoxEntryMaxLength );
    HBufC* hBuf = HBufC::NewLC( KListBoxEntryMaxLength );
    TPtr tempBufPtr1( tempBuf1->Des() );
    TPtr tempBufPtr2( tempBuf2->Des() );
    TPtr hBufPtr( hBuf->Des() );
    if (( aFreeSpace >= 0 ) && ( aFreeSpace < KHundredNum ))
        {
        unitBuf = StringLoader::LoadLC(
                                R_CFD_QTN_MEMC_UNITS_BYTE,
                                CCoeEnv::Static());
        TPtr unitString = unitBuf->Des();
        loadBuf = StringLoader::LoadLC(
                                R_CFD_QTN_MEMC_FREE_MEMORY_VAR_UNITS,
                                CCoeEnv::Static());
        StringLoader::Format(
            tempBufPtr1,
            *loadBuf,
            KNoIndex,
            tempNum
            );
        StringLoader::Format(
            aUnitBuf,
            tempBufPtr1,
            KNoIndex,
            unitString
            );
        }
    else
        { 
                        
        if (( aFreeSpace >= KHundredNum ) && ( aFreeSpace < KMegaNum ))
            {
            tempNum /= KThousandNum; // Divide to kilobytes
            tempNum = TReal32( TInt( tempNum * 10 ) ) / 10;
            unitBuf = StringLoader::LoadLC(
                                    R_CFD_QTN_MEMC_UNITS_KILOBYTE,
                                    CCoeEnv::Static());                              
            }
        else if (( aFreeSpace >= KMegaNum ) && ( aFreeSpace < KGigaNum ))
            {                             
            tempNum /= KMegaNum; // Divide to Megabytes
            tempNum = TReal32( TInt( tempNum * 10 ) ) / 10;
            unitBuf = StringLoader::LoadLC(
                                    R_CFD_QTN_MEMC_UNITS_MEGABYTE,
                                    CCoeEnv::Static());            
            }
        else if (aFreeSpace >= KGigaNum )   
            {
            tempNum /= KGigaNum; // Divide to Gigabytes
            tempNum = TReal32( TInt( tempNum * 10 ) ) / 10;
            unitBuf = StringLoader::LoadLC(
                                    R_CFD_QTN_MEMC_UNITS_GIGABYTE,
                                    CCoeEnv::Static());            
            }
        
		if ( !unitBuf )
		    {
            User::Leave( KErrArgument );
            }
        
        
        loadBuf = StringLoader::LoadLC(
                            R_CFD_QTN_MEMC_FREE_MEMORY_VAR_UNITS_DOT,
                            CCoeEnv::Static());
                            
        if( loadBuf &&
            ( loadBuf->Des().Find( KTempString0 ) == KErrNotFound ||
            loadBuf->Des().Find( KTempString1 ) == KErrNotFound ) )
            {
            aUnitBuf.Copy( KDefinedString );
            }
        else
            {
            // Change string formate.
            TBuf<KFreeLen> buf;
            buf.Format(KFreeFormate, tempNum);
            StringLoader::Format( tempBufPtr1, *loadBuf, 0, buf );                   
    
            TPtr unitString = unitBuf->Des();
            StringLoader::Format( tempBufPtr2, *tempBuf1, 1, unitString );  
            aUnitBuf.Format( tempBufPtr2, tempNum );	
            }

        }

    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( aUnitBuf ); // Localize digits

    CleanupStack::PopAndDestroy( loadBuf );  
    CleanupStack::PopAndDestroy( unitBuf );   
    CleanupStack::PopAndDestroy( hBuf );
    CleanupStack::PopAndDestroy( tempBuf2 );
    CleanupStack::PopAndDestroy( tempBuf1 );
    
    }

// ---------------------------------------------------------------------------
// AknCFDUtility::UserVisibleDriveCountL
// ---------------------------------------------------------------------------
//
TInt AknCFDUtility::UserVisibleDriveCountL( TInt aIncludedMedias )
    {
    TInt visibleDriveCount = 0;
    
    TInt driveCount = 0;
    TDriveList driveList;
    RFs& fs = CCoeEnv::Static()->FsSession();
    
    User::LeaveIfError( DriveInfo::GetUserVisibleDrives(
        fs, driveList, driveCount, KDriveAttAll ) );
    
    if ( driveCount > 0 )
        {
        // Convert EMemoryTypeMMC to EMemoryTypeInternalMassStorage & 
        // EMemoryTypeMMCExternal if include.
        if( aIncludedMedias & AknCommonDialogsDynMem::EMemoryTypeMMC )
            {
            aIncludedMedias = aIncludedMedias |
                AknCommonDialogsDynMem::EMemoryTypeInternalMassStorage
                | AknCommonDialogsDynMem::EMemoryTypeMMCExternal;
            aIncludedMedias &= ( ~AknCommonDialogsDynMem::EMemoryTypeMMC );
            }
        
        TDriveNumber driveNumber;
        AknCommonDialogsDynMem::TMemoryTypes memoryType;
        TCFDDriveStatus driveStatus;
        for( TInt i = 0; i < KMaxDrives; i++ )
            {
            if( driveList[i] )
                {
                driveNumber = TDriveNumber( i );
                memoryType = DriveMemoryTypeL( driveNumber );
                if( memoryType & aIncludedMedias )
                    {
                    driveStatus = EDriveNotReady ;
                    driveStatus = AknCFDUtility::DriveStatusL( driveNumber );
                    // count only if it is available
                    if( driveStatus != EDriveNotReady )
                        {
                        visibleDriveCount++;
                        }
                    }
                }
            }
        }
    
    return visibleDriveCount;
    }
    
// End of File

