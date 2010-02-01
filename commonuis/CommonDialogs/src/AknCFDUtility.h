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
* Description:  Internal utility class for CFD. Do not export this header to
*                keep minimal maintenance effort (no BC breaks).
*
*/



#ifndef AKNCFDUTILITY_H
#define AKNCFDUTILITY_H

#include <f32file.h> // TDriveNumber
#include <CAknCommonDialogsBase.h> // TCommonDialogType
#include <badesca.h> // CDesCArray
#include <e32const.h> // KMaxFileName

#include "AknCommonDialogsDynMem.h"

class CEikonEnv;
class CAknIconArray;
class MAknsSkinInstance;
class TAknsItemID;

// Debug print convenience macros - no need to use ifdef in code.
#ifndef _LOG
    #ifdef _DEBUG
        // Print in debug mode:
        #define _LOG( msg ) RDebug::Print( _L( msg ) );
        #define _LOG1( msg, val1 ) RDebug::Print( _L( msg ), val1 );
        #define _LOG2( msg, val1, val2 ) RDebug::Print( _L( msg ), val1, val2 );
        #define _LOG3( msg, val1, val2, val3 ) RDebug::Print( _L( msg ), val1, val2, val3 );
        #define _LOG4( msg, val1, val2, val3, val4 ) RDebug::Print( _L( msg ), val1, val2, val3, val4 );
        #define _LOG5( msg, val1, val2, val3, val4, val5 ) RDebug::Print( _L( msg ), val1, val2, val3, val4, val5 );
        #define _LOG6( msg, val1, val2, val3, val4, val5, val6 ) RDebug::Print( _L( msg ), val1, val2, val3, val4, val5, val6 );
        #define _LOG7( msg, val1, val2, val3, val4, val5, val6, val7 ) RDebug::Print( _L( msg ), val1, val2, val3, val4, val5, val6, val7 );
    #else
        // No print in release mode:
        #define _LOG( msg ) ;
        #define _LOG1( msg, val1 ) ;
        #define _LOG2( msg, val1, val2 ) ;
        #define _LOG3( msg, val1, val2, val3 ) ;
        #define _LOG4( msg, val1, val2, val3, val4 ) ;
        #define _LOG5( msg, val1, val2, val3, val4, val5 ) ;
        #define _LOG6( msg, val1, val2, val3, val4, val5, val6 ) ;
        #define _LOG7( msg, val1, val2, val3, val4, val5, val6, val7 ) ;
    #endif // _DEBUG
#endif // _LOG

/**
* Drive status. This affects functionality and appearance of lbx drive item.
* Instead of numerous 'system wide error codes' CFD is interested only in these
* states of a drive. If adding more states, add to the end of this enum - do
* not alter the order.
*/
enum TCFDDriveStatus
    {
    EDriveOK = 0,   // drive is available, unlocked and formatted
    EDriveLocked,   // drive is locked
    EDriveNotReady  // drive is not inserted or the drive is corrupted or unformatted
    };

/**
 *  Data encapsulation class for CFD drive information. Used to draw list items
 *  and handle drive status logic inside CFD classes.
 */
class TCFDDriveInfo
    {
    public:
        TDriveNumber iDriveNumber;
        TBufC<KMaxFileName> iVolumeLabel; // User defined name for drive if given.
        TInt64 iDiskSpace; // Free space in drive (Byte), negative value indicates not available.
        TMediaType iMediaType;
        TCFDDriveStatus iDriveStatus;
        /**
         * Used for remote drives only:
         * KMountStronglyConnected or KMountNotConnected.
         */
        TInt iConnectionState;

        /**
         * Type: DriveInfo::TStatus
         * To be used to support multiple drives.
         */
        TUint iStatus;
    };

const TInt KDiskSpaceNotAvailable = -1; // Actually any negative value should do so checking should be done using 'i<0' operator.

/**
*  Static utility class for CFD
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
class AknCFDUtility
    {
    public:     // static methods

        /**
        * Reads information of a drive. This is the more convenient function to
        * get all necessary single drive information.
        *
        * NOTE: if reading drive info fails in some stage inside this function,
        * aDriveInfo.iDriveStatus will have a value different than EDriveOK -
        * in this case some data inside aDriveInfo wll not be updated. Check
        * implementation to see which data is updated correctly and can be used.
        *
        * @param aDriveNumber The drive to read information from.
        * @param aDriveInfo Will contain information of the drive.
        * @return KErrNone or system wide error codes...
        */
        static TInt DriveInfoL( const TDriveNumber aDriveNumber, TCFDDriveInfo& aDriveInfo );

        /**
        * Method for checking drive status. This is more efficient and simple
        * method to get drive status than DriveInfo() and should be used for
        * performance reasons and to maintain code simplicity. Only drive
        * status is checked in many places where any other drive information
        * is not needed and would be overkill.
        *
        * @param aDriveNumber Drive number of the drive, status is checked.
        * @return Status of the drive.
        */
        static TCFDDriveStatus DriveStatusL( const TDriveNumber aDriveNumber );

        /**
        * Returns drive number of a path.
        * @param aPath A path which must contain a drive, e.g: "C:\Nokia\"
        * @return Returns the number of the drive (enumeration TDriveNumber).
        *         If path contains no drive, returns KErrNotFound.
        */
        static TInt DriveNumber( const TDesC& aPath );

        /**
        * Returns the number of directories in a path.
        * Path must be format "Directory\Another\" in other words, w/o drive letter!
        * @param aPath A path from which directory count is calculated.
        * @return Returns the number of directories in a path.
        */
        static TInt DirectoryCount( const TDesC& aPath );

        /**
        * Adds trailing backslash to a path if it is missing.
        * Does nothing if already there.
        * @param aFolder A reference to a descriptor which is edited.
        * @return Returns system wide error code.
        */
        static TInt AddTrailingBackslash( TDes& aPath );

        /**
        * Removes trailing backslash from a path.
        * Does nothing if last character is something else than backslash
        * @param aFolder A reference to a descriptor which is edited.
        * @return Returns system wide error code.
        */
        static TInt RemoveTrailingBackslash( TDes& aPath );

        /**
        * Method for internal use only. See source.
        */
        static void AllocateIfValidL(
            HBufC*& aDestination, const TDesC& aSource );

        /**
        * Method for internal use only. See source.
        */
        static void AllocateOrNullL(
            HBufC*& aDestination, const TDesC& aSource );

        /**
        * Method for internal use only. See source.
        */
        static void AllocateIfNullL(
            HBufC*& aDestination, const TDesC& aSource );

        /**
        * DEPRECATED: Use AppendSkinnedImageToArrayL instead.
        *
        * Creates an icon and appends it to icon array using
        * CEikonEnv::CreateIconL.
        */
        static void AppendImageToArrayL( CEikonEnv& aEnv, CAknIconArray& aArray,
            const TDesC& aBitmapFile, TInt aBitmapId, TInt aMaskId );
           
        /**
        * Creates skinned icon and appends it to icon array.
        * If skinned icon is not found, Avkon bitmap is used.
        */
        static void AppendSkinnedImageToArrayL(
            CEikonEnv& aEnv, CAknIconArray& aArray,
            MAknsSkinInstance* aSkin, const TAknsItemID& aItemID,
            const TDesC& aBitmapFile, TInt aBitmapId, TInt aMaskId, TBool aColorIcon = EFalse );

        /**
        * Returns whether dialog type is a folder select dialog or not.
        */
        static TBool DirectoriesOnly( TCommonDialogType aType );

        /**
        * Reads dynamic drives and adds these to the rootpath array. Does not
        * add new drives in case they already exist in the array.
        * @param aRootPathArray Array of the already existing root paths which
        *        will be updated in case more drives exist.
        * @param aIncludedMedias bitflag list of desired media types.
        */
        static void ReadDynamicDrivesL( CDesCArrayFlat& aRootPathArray,
                                        TInt aIncludedMedias );

        /**
        * Checks if the drive already exists.
        * @param aRootPathArray An array of drives from which to check.
        * @param aDriveLetter Letter of the drive upon which is checked, if it
        *        already exists.
        * @return ETrue if drive already exists. Otherwise EFalse.
        */
        static TBool DriveAlreadyExists( CDesCArrayFlat& aRootPathArray,
                                         TChar aDriveLetter );

        /**
        * Checks if drive's type is in included medias list.
        * @param aDriveInfo info of the drive to be tested.
        * @param aIncludedMedias bitflag list of desired media types.
        * @return ETrue if drive's type is in included medias.
        */
        static TBool IsIncludedMedia( TDriveInfo aDriveInfo,
                                      TInt aIncludedMedias );

        /**
        * Counts effective drives: Drives which contain recognised media and
        * are not ROM or RAM. This function can be used to check if there are
        * more than one effective drives.
        *
        * This also handles default cases such as omitting EDriveD and EDriveZ
        * (ROM and RAM) because these drives should not be visible to the
        * user anyway.
        *
        * @return Number of effective drives.
        */
        static TInt EffectiveDriveCountL();
        
        /**
        * Check if one drive is a remote drive
        *
        * @since 3.2
        * @return If is a remote drive.
        */
        static TBool IsRemoteDrive( const TDesC& aDrive );
        
        /**
        * Get drive's memory type
        *
        * @since 5.0
        * @return The memory type of given drive. See TMemoryTypes.
        */
        static AknCommonDialogsDynMem::TMemoryTypes
            DriveMemoryTypeL( const TDriveNumber& aDrive );
    
        /**
         * Set free space count and unit indicating.
         * @param aFreeSpace free space with unit "Byte".
         * @param aUnitBuf return text.
         */
        static void SetSecondRowTextL( TInt64 aFreeSpace, TDes& aUnitBuf );
        
        /**
         * Get the count of user visible drives. This function can be used to
         * define if memory selection dialog should be used instead of file
         * selection dialog.
         * 
         * @param aIncludedMedias defines which medias are included in the
         *        dialog. See TMemoryTypes
         * @return Number of user visible drives.
         */
        static TInt UserVisibleDriveCountL( TInt aIncludedMedias );
    };

#endif // AKNCFDUTILITY_H
