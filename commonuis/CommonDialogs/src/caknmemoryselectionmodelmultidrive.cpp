/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Model used in listbox of memory selection dialog which support
*                multiple drives. It is used to replace
*                CAknMemorySelectionModel
*
*/



#include <coemain.h>
#include <StringLoader.h>
#include <commondialogs.rsg>
#include <pathinfo.h> //PathInfo
#include <barsread.h>   // TResourceReader
#include <driveinfo.h> //DriveInfo
#include "caknmemoryselectionmodelmultidrive.h"
#include "CAknCommonDialogsBase.h"
#include "AknCFDUtility.h"

const TInt KListBoxEntryMaxLength( KMaxFileName + 32 );
const TInt KNoIndex = -1;
const TInt KIndexFirst = 0;
const TInt KIndexSecond = 1;
_LIT( KImageHeader, "%d" );
_LIT( KTabChar, "\t" );
_LIT( KSpaceChar, " " );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::CAknMemorySelectionModelMultiDrive
// ---------------------------------------------------------------------------
//
CAknMemorySelectionModelMultiDrive::CAknMemorySelectionModelMultiDrive(
    CCoeEnv* aCoeEnv,
    MDesCArray* aDriveArray,
    MDesCArray* aDefaultFolderArray,
    TInt aIncludedMedias,
    TBool aShowUnavailable,
    TListBoxLayout aLayout )
    :   iCoeEnv( aCoeEnv ),
        iDriveArray( aDriveArray ),
        iDefaultFolderArray( aDefaultFolderArray ),
        iIncludedMedias( aIncludedMedias ),
        iShowUnavailable( aShowUnavailable ),
        iLayout( aLayout )
    {
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::ConstructL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::ConstructL()
    {
    ReadResourcesL();
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::NewL
// ---------------------------------------------------------------------------
//
CAknMemorySelectionModelMultiDrive* CAknMemorySelectionModelMultiDrive::NewL(
    CCoeEnv* aCoeEnv,
    MDesCArray* aDriveArray,
    MDesCArray* aDefaultFolderArray,
    TInt aIncludedMedias,
    TBool aShowUnavailable,
    TListBoxLayout aLayout )
    {
    CAknMemorySelectionModelMultiDrive* self =
        new( ELeave ) CAknMemorySelectionModelMultiDrive(
            aCoeEnv, aDriveArray, aDefaultFolderArray,
            aIncludedMedias, aShowUnavailable, aLayout );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// Destructor
CAknMemorySelectionModelMultiDrive::~CAknMemorySelectionModelMultiDrive()
    {
    iListBoxArray.ResetAndDestroy();
    iListBoxArray.Close();
    iLocStringArray.ResetAndDestroy();
    iLocStringArray.Close();
    delete iDefDriveArray;
    iDefDriveArray = NULL;
    delete iDefDefaultFolderArray;
    iDefDefaultFolderArray = NULL;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::GetItem
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::GetItem( TInt aIndex, TDes& aItem )
    {
    aItem = iListBoxArray[ aIndex ]->Des();
    if( iLayout == ELayoutPopupMenu || iLayout == ELayoutDoublePopup )
        {
        // On layout with graphic, delete image index.
        _LIT( KTab, "\t" );
        TInt tabIndex( aItem.Find( KTab ) );
        if( tabIndex >= 0 )
            {
            aItem.Delete( 0, tabIndex + 1 );
            }
        if( iLayout == ELayoutDoublePopup )
            {
            tabIndex = aItem.Find( KTab );
            if( tabIndex >= 0 )
                {
                aItem = aItem.Left( tabIndex );
                }
            }
        }
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::UpdateItemsL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::UpdateItemsL()
    {
    TInt drive;
    TCFDDriveInfo driveInfo;

    // If array has items - reset it before updating
    iListBoxArray.ResetAndDestroy();
    _LOG( "[CAknMemorySelectionModelMultiDrive] iDriveArray: " );

    // Go through all drives
    for( TInt index( 0 ); index < iDriveArray->MdcaCount(); index++ )
        { 
        TPtrC text(iDriveArray->MdcaPoint( index ));
        _LOG1( "%S", &text );

        drive = AknCFDUtility::DriveNumber( iDriveArray->MdcaPoint( index ) );
        User::LeaveIfError( drive ); // Leaves if < 0
        AknCFDUtility::DriveInfoL( TDriveNumber( drive ), driveInfo );

        _LOG7( "\n[CAknMemorySelectionModelMultiDrive] TCFDDriveInfo \n DriveNum:%d \n Path:%S \n Media:%d \n Status:%d \n Label:%S \n Space:%d \n ConnectionState:%d",
               driveInfo.iDriveNumber,
               &text,
               driveInfo.iMediaType,
               driveInfo.iDriveStatus,
               &(driveInfo.iVolumeLabel),
               driveInfo.iDiskSpace,
               driveInfo.iConnectionState );

        AddItemToLbxL( driveInfo );
        } // for
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::MdcaCount
// ---------------------------------------------------------------------------
//
TInt CAknMemorySelectionModelMultiDrive::MdcaCount() const
    {
    return iListBoxArray.Count();
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::MdcaPoint
// ---------------------------------------------------------------------------
//
TPtrC CAknMemorySelectionModelMultiDrive::MdcaPoint( TInt aIndex ) const
    {
    return *iListBoxArray[ aIndex ];
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::ReadResourcesL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::ReadResourcesL()
    {
    HBufC* buffer;
    TInt resource;
    for( TInt locStrIndex( 0 ); locStrIndex < ETextCount; locStrIndex++ )
        {
        resource = 0;
        // Resource depends on the layout type (TListBoxLayout):
        switch( iLayout )
            {
            case ELayoutPopupMenu:
                {
                resource = ResourceIDForLayoutPopupMenuItem( locStrIndex );
                break;
                }
            case ELayoutSettingPage:
                {
                resource = ResourceIDForLayoutSettingPageItem( locStrIndex );
                break;
                }
            case ELayoutDoublePopup:
                {
                resource = ResourceIDForLayoutDoublePopupItem( locStrIndex );
                break;
                }
            default:
                {
                User::Panic( KCFDPanicText, ECFDPanicOutOfBounds );
                }
            }//iLayout

        if( resource )
            {
            buffer = NULL;
            buffer = iCoeEnv->AllocReadResourceLC( resource );
            User::LeaveIfError( iLocStringArray.Append( buffer ) );
            CleanupStack::Pop();
            }

        }//For loop

#ifdef _DEBUG
        _LOG( "[CAknMemorySelectionModelMultiDrive] iLocStringArray: " );
        for( TInt lsa = 0; lsa < iLocStringArray.Count(); lsa++ )
            {
            _LOG1( "%S",iLocStringArray[ lsa ] );
            }
#endif // _DEBUG
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::ResourceIDForLayoutPopupMenuItem
// ---------------------------------------------------------------------------
//
TInt CAknMemorySelectionModelMultiDrive::ResourceIDForLayoutPopupMenuItem(
    TInt aLocStrIndex )
    {
    TInt resource = 0;
    switch( aLocStrIndex )
        {
        case ETextDeviceMemory:
            {
            // qtn.mem.device.memory
            resource = R_CFD_QTN_MEM_DEVICE_MEMORY;
            break;
            }
        case ETextInternalMassStorage:
            {
            // qtn.mem.mass.storage
            resource = R_CFD_QTN_MEM_MASS_STORAGE;
            break;
            }
        case ETextInternalMassStorageUnavailable:
            {
            // qtn.mem.mass.storage.unavailable
            resource = R_CFD_QTN_MEM_MASS_STORAGE_UNAVAILABLE;
            break;
            }
        case ETextMMCDefaultName:
            {
            // If MMC's name is empty.
            // qtn.mem.memory.card.default
            resource = R_CFD_QTN_MEM_MEMORY_CARD_DEFAULT;
            break;
            }
        case ETextMMCNamed:
            {
            // If MMC's name is given.
            // qtn.mem.named.memory.card
            resource = R_CFD_QTN_MEM_NAMED_MEMORY_CARD;
            break;
            }
        case ETextMMCLocked:
            {
            // qtn.mem.memory.card.locked
            resource = R_CFD_QTN_MEM_MEMORY_CARD_LOCKED;
            break;
            }
        case ETextMMCUnavailable:
            {
            // qtn.mem.memory.card.unavailable
            resource = R_CFD_QTN_MEM_MEMORY_CARD_UNAVAILABLE;
            break;
            }
        case ETextRemoteDrive:
            {
            // qtn.memc.remote.drive
            resource = R_CFD_QTN_MEMC_REMOTE_DRIVE;
            break;
            }
        }
    return resource;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::ResourceIDForLayoutSettingPageItem
// ---------------------------------------------------------------------------
//
TInt CAknMemorySelectionModelMultiDrive::ResourceIDForLayoutSettingPageItem(
    TInt aLocStrIndex )
    {
    TInt resource = 0;
    switch( aLocStrIndex )
        {
        case ETextDeviceMemory:
            {
            // qtn.mem.device.memory.setting.list
            resource = R_CFD_QTN_MEM_DEVICE_MEMEORY_SETTING_LIST;
            break;
            }
        case ETextInternalMassStorage:
        case ETextInternalMassStorageUnavailable:
            {
            // qtn.mem.mass.storage.setting.list
            resource = R_CFD_QTN_MEM_MASS_STORAGE_SETTING_LIST;
            break;
            }
        case ETextMMCDefaultName:
        case ETextMMCLocked:
        case ETextMMCUnavailable:
            {
            // If MMC's name is empty.
            // qtn.mem.memory.card.defaul.setting.list
            resource = R_CFD_QTN_MEM_MEMORY_CARD_DEFAULT_SETTING_LIST;
            break;
            }
        case ETextMMCNamed:
            {
            // If MMC's name is given.
            // qtn.mem.named.memory.card.setting.list
            resource = R_CFD_QTN_MEM_NAMED_MEMORY_CARD_SETTING_LIST;
            break;
            }
        case ETextRemoteDrive:
            {
            // TODO: To get real value from UI spec
            resource = R_CFD_QTN_MEMC_REMOTE_DRIVE;
            break;
            }
        }
    return resource;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::ResourceIDForLayoutDoublePopupItem
// ---------------------------------------------------------------------------
//
TInt CAknMemorySelectionModelMultiDrive::ResourceIDForLayoutDoublePopupItem(
    TInt aLocStrIndex )
    {
    TInt resource = 0;
     switch( aLocStrIndex )
        {
        case ETextDeviceMemory:
            {
            // qtn.mem.device.memory.double.list
            resource = R_CFD_QTN_MEM_DEVICE_MEMORY_DOUBLE_LIST;
            break;
            }
        case ETextInternalMassStorage:
            {
            // qtn.mem.mass.storage.double.list
            resource = R_CFD_QTN_MEM_MASS_STORAGE_DOUBLE_LIST;
            break;
            }
        case ETextInternalMassStorageUnavailable:
            {
            // Unavailable:qtn.memc.mmc.unavailable.double
            // Only for second row
            resource = R_CFD_QTN_MEMC_MMC_UNAVAILABLE_DOUBLE;
            break;
            }
        case ETextMMCNamed:
            {
            // If MMC's name is given.
            // qtn.mem.named.memory.card.double
            resource = R_CFD_QTN_MEM_NAMED_MEMORY_CARD_DOUBLE;
            break;
            }
        case ETextMMCDefaultName:
            {
            // If MMC's name is empty.
            // qtn.mem.memory.card.default.double
            resource = R_CFD_QTN_MEM_MEMORY_CARD_DEFAULT_DOUBLE;
            break;
            }
        case ETextMMCLocked:
            {
            // qtn.memc.mmc.locked.double
            resource = R_CFD_QTN_MEMC_MMC_LOCKED_DOUBLE;
            break;
            }
        case ETextMMCUnavailable:
            {
            // qtn.memc.mmc.unavailable.double
            resource = R_CFD_QTN_MEMC_MMC_UNAVAILABLE_DOUBLE;
            break;
            }
        case ETextRemoteDrive:
            {
            // TODO: To be checked because of missing data in UI spec.
            resource = R_CFD_QTN_MEMC_REMOTE_DRIVE_DOUBLE_LIST;
            break;
            }
        }
    return resource;

    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::AddItemToLbxL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::AddItemToLbxL(
        const TCFDDriveInfo& aDriveInfo )
    {
    // Listbox items are differend depending on the media type.
    if ( aDriveInfo.iStatus & DriveInfo::EDriveInternal )
        {
        // Internal drives including device memory and internal mass storage
        if ( aDriveInfo.iStatus & DriveInfo::EDriveExternallyMountable )
            {
            // Internal mass storage drive
            AddInternalStorageItemToLbxL( aDriveInfo );
            }
        else
            {
            // Device memory drive
            AddDeviceMemoryItemToLbxL( aDriveInfo );
            }
        }
    else if( aDriveInfo.iStatus & DriveInfo::EDriveRemovable  )
        {
        // External mass storage drive, like external MMC
        AddMMCItemToLbxL( aDriveInfo );

        iHasMMCUnavailable = ( aDriveInfo.iDriveStatus == EDriveNotReady );
        }
    else if ( ( aDriveInfo.iStatus & DriveInfo::EDriveRemote )
        && ( aDriveInfo.iMediaType == EMediaRemote ) )
        // 2 conditions used here just for sure
        {
        // Remote drive
        AddRemoteItemToLbxL( aDriveInfo );
        }
    else
        {
        // Default
        // No actual use case for this yet.
        AddDefaultItemToLbxL( aDriveInfo );
        }
    }      

// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::AddDeviceMemoryItemToLbxL
// ---------------------------------------------------------------------------
void CAknMemorySelectionModelMultiDrive::AddDeviceMemoryItemToLbxL(
    const TCFDDriveInfo& aDriveInfo )
    {
    HBufC* lbxItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
    TPtr itemString( lbxItemBuf->Des() );
    HBufC* textItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
    TPtr textString( textItemBuf->Des() );
    TDriveUnit driveUnit( aDriveInfo.iDriveNumber );

    // Item text is affected by layout
    switch( iLayout )
        {
            case ELayoutPopupMenu:
                {
                // A-column icon:
                itemString.Format( KImageHeader, EIconDeviceMemory );
                itemString.Append( KTabChar );

                // 1st row text:
                // Drive letter needs to be added
                StringLoader::Format( textString,
                                      *iLocStringArray[ ETextDeviceMemory ],
                                      KNoIndex,
                                      driveUnit.Name() );
                itemString.Append( textString );
                break;
                }
            case ELayoutSettingPage:
                {
                // 1st row text:
                // Drive letter needs to be added
                StringLoader::Format( itemString,
                                      *iLocStringArray[ ETextDeviceMemory ],
                                      KNoIndex,
                                      driveUnit.Name() );
                break;
                }
            case ELayoutDoublePopup:
                {
                // A-column icon:
                itemString.Format( KImageHeader, EIconDeviceMemory );
                itemString.Append( KTabChar );

                // 1st row text:
                StringLoader::Format( textString,
                                      *iLocStringArray[ ETextDeviceMemory ],
                                      KNoIndex,
                                      driveUnit.Name() );
                itemString.Append( textString );
                itemString.Append( KTabChar );

                // 2nd row text:
                HBufC* buffer;
                TInt64 freeSpace = aDriveInfo.iDiskSpace;
                if ( freeSpace >= 0 )
                    {
                    buffer = HBufC::NewLC( KListBoxEntryMaxLength );  
                    TPtr unitStr( buffer->Des() );
                    AknCFDUtility::SetSecondRowTextL( freeSpace, unitStr );
                    }
                else
                    {
                    // Disk space is unavailable
                    buffer = StringLoader::LoadLC(
                                R_CFD_QTN_MEMC_SPACE_NOT_AVAILABLE,
                                iCoeEnv);
                    }
                itemString.Append( *buffer );//Free mem text
                CleanupStack::PopAndDestroy( buffer );
                break;
                }
            }

    // Finally!: append the formatted string to listbox
    User::LeaveIfError( iListBoxArray.Append( lbxItemBuf ) );
    CleanupStack::PopAndDestroy( textItemBuf );
    CleanupStack::Pop( lbxItemBuf );
    _LOG1(
        "[CAknMemorySelectionModelMultiDrive] Item string added to lbx array: %S",
           &itemString );
    _LOG1( "itemString length=%d", itemString.Length() );
    }

// --------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::AddInternalStorageItemToLbxL
//
//
// --------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::AddInternalStorageItemToLbxL(
    const TCFDDriveInfo& aDriveInfo )
    {
    HBufC* lbxItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
    TPtr itemString( lbxItemBuf->Des() );
    HBufC* textItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
    TPtr textString( textItemBuf->Des() );
    TDriveUnit driveUnit( aDriveInfo.iDriveNumber );

    // Item text is affected by layout
    switch( iLayout )
        {
        case ELayoutPopupMenu:
            {
            // A-column icon:
            if( aDriveInfo.iDriveStatus == EDriveOK )
                {
                itemString.Format( KImageHeader, EIconInternalMassStorage );
                }
            else
                {
                itemString.Format( KImageHeader,
                                   EIconInternalMassStorageUnavailable );
                }
            itemString.Append( KTabChar );

            // 1st row text:
            if( aDriveInfo.iDriveStatus == EDriveOK )
                {
                StringLoader::Format(
                    textString,
                    *iLocStringArray[ ETextInternalMassStorage ],
                    KNoIndex,
                    driveUnit.Name()
                    );
                }
            else
                {
                StringLoader::Format(
                    textString,
                    *iLocStringArray[ ETextInternalMassStorageUnavailable ],
                    KNoIndex,
                    driveUnit.Name()
                    );
                }
            itemString.Append( textString );
            break;
            }
        case ELayoutSettingPage:
            {
            // 1st row text:
            StringLoader::Format(
                    itemString,
                    *iLocStringArray[ ETextInternalMassStorage ],
                    KNoIndex,
                    driveUnit.Name()
                    );
            break;
            }
        case ELayoutDoublePopup:
            {
            // A-column icon:
            itemString.Format( KImageHeader, EIconInternalMassStorage );
            itemString.Append( KTabChar );

            // 1st row text:
            StringLoader::Format(
                    textString,
                    *iLocStringArray[ ETextInternalMassStorage ],
                    KNoIndex,
                    driveUnit.Name()
                    );
            itemString.Append( textString );
            itemString.Append( KTabChar );

            // 2nd row text:
            if ( aDriveInfo.iDriveStatus == EDriveOK )
                {
                HBufC* buffer;
                TInt64 freeSpace = aDriveInfo.iDiskSpace;
                if ( freeSpace >= 0 )
                    {
                    buffer = HBufC::NewLC( KListBoxEntryMaxLength );  
                    TPtr unitStr( buffer->Des() );
                    AknCFDUtility::SetSecondRowTextL( freeSpace, unitStr );
                    }
                else
                    {
                    // Disk space is unavailable
                    buffer = StringLoader::LoadLC(
                                R_CFD_QTN_MEMC_SPACE_NOT_AVAILABLE,
                                iCoeEnv);
                    }
                itemString.Append( *buffer );//Free mem text
                CleanupStack::PopAndDestroy( buffer );
                }
            else
                {
                itemString.Append(
                    *iLocStringArray[
                        ETextInternalMassStorageUnavailable ] );
                }
            break;
            }
        }

    // Finally!: append the formatted string to listbox
    User::LeaveIfError( iListBoxArray.Append( lbxItemBuf ) );
    CleanupStack::PopAndDestroy( textItemBuf );
    CleanupStack::Pop( lbxItemBuf );
    _LOG1( "[CAknMemorySelectionModelMultiDrive] Item string added to lbx array: %S", &itemString );
    _LOG1( "itemString length=%d", itemString.Length() );
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::AddMMCItemToLbxL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::AddMMCItemToLbxL(
    const TCFDDriveInfo& aDriveInfo )
    {
    HBufC* lbxItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
    TPtr itemString( lbxItemBuf->Des() );
    HBufC* textItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
    TPtr textString( textItemBuf->Des() );
    HBufC* textItemBuf2 = HBufC::NewLC( KListBoxEntryMaxLength );
    TPtr textString2( textItemBuf2->Des() );
    TDriveUnit driveUnit( aDriveInfo.iDriveNumber );

    // Item text is affected by layout
    switch( iLayout )
        {
        case ELayoutPopupMenu:
            {
            // A-column icon:
            switch ( aDriveInfo.iDriveStatus )
                {
                case EDriveNotReady:
                    {
                    itemString.Format( KImageHeader, EIconMMCUnavailable );
                    break;
                    }
                case EDriveLocked:
                    {
                    itemString.Format( KImageHeader, EIconMMCLocked );
                    break;
                    }
                 default: // Normal condition
                    {
                    itemString.Format( KImageHeader, EIconMMC );
                    break;
                    }
                }
            itemString.Append( KTabChar );

            // 1st row text:
            if( ( aDriveInfo.iDriveStatus == EDriveOK ) &&
                ( aDriveInfo.iVolumeLabel.Length() > 0 ) )
                {
                StringLoader::Format(
                    textString2,
                    *iLocStringArray[ ETextMMCNamed ],
                    KIndexFirst,
                    driveUnit.Name()
                    );
                StringLoader::Format(
                    textString,
                    textString2,
                    KIndexSecond,
                    aDriveInfo.iVolumeLabel
                    );
                }
            else if ( aDriveInfo.iDriveStatus == EDriveNotReady )
                {
                //textString.Format(
                //    *iLocStringArray[ ETextMMCUnavailable ],
                //    driveUnit.Name() );
                StringLoader::Format(
                    textString,
                    *iLocStringArray[ ETextMMCUnavailable ],
                    KNoIndex,
                    driveUnit.Name()
                    );
                }
            else if( aDriveInfo.iDriveStatus == EDriveLocked )
                {
                //textString.Format(
                //    *iLocStringArray[ ETextMMCLocked ],
                //    driveUnit.Name() );
                StringLoader::Format(
                    textString,
                    *iLocStringArray[ ETextMMCLocked ],
                    KNoIndex,
                    driveUnit.Name()
                    );
                }
            else
                {
                // Use default drive description
                //textString.Format(
                //    *iLocStringArray[ ETextMMCDefaultName ],
                //    driveUnit.Name() );
                StringLoader::Format(
                    textString,
                    *iLocStringArray[ ETextMMCDefaultName ],
                    KNoIndex,
                    driveUnit.Name()
                    );
                }
            itemString.Append( textString );

            break;
            }
        case ELayoutSettingPage:
            {
            // 1st row text:
            if( aDriveInfo.iVolumeLabel.Length() > 0 )
                {
                // Append drive name if it has one
                //itemString.Format(
                //    *iLocStringArray[ ETextMMCNamed ],
                //    driveUnit.Name(),
                //    aDriveInfo.iVolumeLabel
                //    );
                StringLoader::Format(
                    textString,
                    *iLocStringArray[ ETextMMCNamed ],
                    KIndexFirst,
                    driveUnit.Name()
                    );
                StringLoader::Format(
                    itemString,
                    textString,
                    KIndexSecond,
                    aDriveInfo.iVolumeLabel
                    );
                }
            else
                {
                //itemString.Format(
                //    *iLocStringArray[ ETextMMCDefaultName ],
                //    driveUnit.Name()
                //    );
                StringLoader::Format(
                    itemString,
                    *iLocStringArray[ ETextMMCDefaultName ],
                    KNoIndex,
                    driveUnit.Name()
                    );
                }
            break;
            }
        case ELayoutDoublePopup:
            {
            // A-column icon:
            if( aDriveInfo.iDriveStatus == EDriveNotReady )
                {
                itemString.Format( KImageHeader, EIconMMCUnavailable );
                }
            else
                {
                itemString.Format( KImageHeader, EIconMMC );
                }
            itemString.Append( KTabChar );

            // 1st row text:
            if( aDriveInfo.iVolumeLabel.Length() > 0 )
                {
                StringLoader::Format(
                    textString2,
                    *iLocStringArray[ ETextMMCNamed ],
                    KIndexFirst,
                    driveUnit.Name()
                    );
                StringLoader::Format(
                    textString,
                    textString2,
                    KIndexSecond,
                    aDriveInfo.iVolumeLabel
                    );
                }
            else
                {
                // Use default drive description
                //textString.Format(
                //    *iLocStringArray[ ETextMMCDefaultName ],
                //    driveUnit.Name()
                //   );
                StringLoader::Format(
                    textString,
                    *iLocStringArray[ ETextMMCDefaultName ],
                    KNoIndex,
                    driveUnit.Name()
                    );
                }
            itemString.Append( textString );
            itemString.Append( KTabChar );

            // 2nd row text:
            switch( aDriveInfo.iDriveStatus )
                {
                case EDriveNotReady:
                    {
                    itemString.Append(
                        *iLocStringArray[ ETextMMCUnavailable ] );
                    break;
                    }
                case EDriveLocked:
                    {
                    itemString.Append( *iLocStringArray[ ETextMMCLocked ] );
                    break;
                    }
                case EDriveOK:
                default:
                    {
                    HBufC* buffer;
                    TInt64 freeSpace = aDriveInfo.iDiskSpace;
                    if ( freeSpace >= 0 )
                        {
                        buffer = HBufC::NewLC( KListBoxEntryMaxLength );  
                        TPtr unitStr( buffer->Des() );
                        AknCFDUtility::SetSecondRowTextL( freeSpace, unitStr );
                        }
                    else
                        {
                        // Disk space is unavailable
                        buffer = StringLoader::LoadLC(
                                    R_CFD_QTN_MEMC_SPACE_NOT_AVAILABLE,
                                    iCoeEnv);
                        }
                    itemString.Append( *buffer );//Free mem text
                    CleanupStack::PopAndDestroy( buffer );
                    break;
                    }
                }
            break;
            }
        }

    // Finally!: append the formatted string to listbox
    User::LeaveIfError( iListBoxArray.Append( lbxItemBuf ) );
    CleanupStack::PopAndDestroy( 2 ); // textItemBuf2, textItemBuf
    CleanupStack::Pop( lbxItemBuf );
    _LOG1( "[CAknMemorySelectionModelMultiDrive] Item string added to lbx array: %S", &itemString );
    _LOG1( "itemString length=%d", itemString.Length() );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::AddRemoteItemToLbxL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::AddRemoteItemToLbxL( const TCFDDriveInfo& aDriveInfo )
    {
    HBufC* lbxItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
    TPtr itemString( lbxItemBuf->Des() );

    // Item text is affected by layout
    switch( iLayout )
        {
        case ELayoutPopupMenu:
            {
            // A-column icon:
            itemString.Format( KImageHeader, EIconRemoteDrive );
            itemString.Append( KTabChar );

            // 1st row text:
            if( aDriveInfo.iVolumeLabel.Length() > 0 )
                {
                // Append drive name if it has one
                itemString.Append( aDriveInfo.iVolumeLabel );
                }
            else
                {
                // Use default drive description
                itemString.Append( *iLocStringArray[ ETextRemoteDrive ] );
                }
            break;
            }
        case ELayoutSettingPage:
            {
            // 1st row text:
            if( aDriveInfo.iVolumeLabel.Length() > 0 )
                {
                // Append drive name if it has one
                itemString.Append( aDriveInfo.iVolumeLabel );
                }
            else
                {
                // Use default drive description
                itemString.Append( *iLocStringArray[ ETextRemoteDrive ] );
                }
            break;
            }
        case ELayoutDoublePopup:
            {
            // A-column icon:
            itemString.Format( KImageHeader, EIconRemoteDrive );
            itemString.Append( KTabChar );

            // 1st row text:
            if( aDriveInfo.iVolumeLabel.Length() > 0 )
                {
                // Append drive name if it has one
                itemString.Append( aDriveInfo.iVolumeLabel );
                itemString.Append( KTabChar );
                }
            else
                {
                // Use default drive description
                itemString.Append( *iLocStringArray[ ETextRemoteDrive ] );
                itemString.Append( KTabChar );
                }

            if( aDriveInfo.iDriveStatus == EDriveOK )
                {
                // 2nd row text:
                // Currently Remote drive does not support query for available
                // disk space, so just return " "
                _LIT( KEmptySpace, " ");
                itemString.Append( KEmptySpace ); 

                //if( aDriveInfo.iConnectionState == KMountStronglyConnected )
                //    {
                // D-column icon: Show active icon if drive has no error
                //    itemString.Append( KTabChar );
                //    itemString.AppendFormat(
                //      KImageHeader, EIconRemoteDriveActive );
                //    }
                //else // KMountNotConnected
                //    {
                    // D-column icon: Show active icon if drive has no error
                itemString.Append( KTabChar );
                //    }
                }
            else
                {
                // 2nd row text:
                itemString.Append( *iLocStringArray[ ETextMMCUnavailable ] );
                // D-column is empty if error.
                }
            break;
            }
        }

    // Finally!: append the formatted string to listbox
    User::LeaveIfError( iListBoxArray.Append( lbxItemBuf ) );
    CleanupStack::Pop( lbxItemBuf );
    _LOG1( "[CAknMemorySelectionModelMultiDrive] Item string added to lbx array: %S", &itemString );
    _LOG1( "itemString length=%d", itemString.Length() );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::AddDefaultItemToLbxL
//
// If drive has volume label, use it.
// Otherwise use drive letter for drive name.
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::AddDefaultItemToLbxL(
    const TCFDDriveInfo& aDriveInfo )
    {
    HBufC* lbxItemBuf = HBufC::NewLC( KListBoxEntryMaxLength );
    TPtr itemString( lbxItemBuf->Des() );
    TDriveUnit driveUnit( aDriveInfo.iDriveNumber );

    // Item text is affected by layout
    switch( iLayout )
        {
        case ELayoutSettingPage:
            {
            if( aDriveInfo.iVolumeLabel.Length() > 0 )
                {
                itemString.Append( driveUnit.Name() );
                itemString.Append( KSpaceChar );
                itemString.Append( aDriveInfo.iVolumeLabel );
                }
            else
                {
                itemString.Append( driveUnit.Name() );
                }
            break;
            }
        case ELayoutPopupMenu:
        case ELayoutDoublePopup:
            {
            itemString.Format( KImageHeader, EIconDeviceMemory );
            itemString.Append( KTabChar );

            if( aDriveInfo.iVolumeLabel.Length() > 0 )
                {
                itemString.Append( driveUnit.Name() );
                itemString.Append( KSpaceChar );
                itemString.Append( aDriveInfo.iVolumeLabel );
                }
            else
                {
                itemString.Append( driveUnit.Name() );
                }
            break;
            }
        }

    // Finally!: append the formatted string to listbox
    User::LeaveIfError( iListBoxArray.Append( lbxItemBuf ) );
    CleanupStack::Pop( lbxItemBuf );
    _LOG1( "[CAknMemorySelectionModelMultiDrive] Item string added to lbx array: %S", &itemString );
    _LOG1( "itemString length=%d", itemString.Length() );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::GetDrive
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::GetDrive( TInt aLbxItemIndex, TDes& aDrivePath )
    {
    if( aLbxItemIndex < iDriveArray->MdcaCount() )
        {
        aDrivePath = iDriveArray->MdcaPoint( aLbxItemIndex );
        }
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::HasUnavailbleMMC
// ---------------------------------------------------------------------------
//
TBool CAknMemorySelectionModelMultiDrive::HasUnavailbleMMC()
    {
    return iHasMMCUnavailable;
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::ReadUserDefinedDataL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::ReadUserDefinedDataL(
    TResourceReader& aReader, TInt aLocations )
    {
    if ( aLocations <= 0)
        {
        return;
        }
    
    iDefDriveArray = new ( ELeave ) CDesCArrayFlat( aLocations );
    iDefDefaultFolderArray = new ( ELeave ) CDesCArrayFlat( aLocations );
    for ( TInt i = 0; i < aLocations; i++ )
        {
        // read the location, save path and default folder in array
        TPath temp;
        temp.Copy( aReader.ReadTPtrC() );
        iDefDriveArray->AppendL( temp );
        temp.Copy( aReader.ReadTPtrC() );
        iDefDefaultFolderArray->AppendL( temp );
        }
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionModelMultiDrive::UpdateDataArraysL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionModelMultiDrive::UpdateDataArraysL()
    {
    TDriveList driveList;
    TInt driveCount;
    User::LeaveIfError( DriveInfo::GetUserVisibleDrives(
        iCoeEnv->FsSession(), driveList, driveCount, KDriveAttAll ) );
    TPath rootPath;
    TDriveNumber driveNumber;
    AknCommonDialogsDynMem::TMemoryTypes memoryType;
    
    CDesCArrayFlat* driveArray = STATIC_CAST( CDesCArrayFlat*, iDriveArray );
    CDesCArrayFlat* defaultFolderArray =
        STATIC_CAST( CDesCArrayFlat*, iDefaultFolderArray );
    driveArray->Reset();
    defaultFolderArray->Reset();
    
    if ( iDefDriveArray != NULL && iDefDefaultFolderArray != NULL )
        {
        for ( TInt i = 0; i < KMaxDrives; i++ )
            {
            TInt driveExist = driveList[i];
            if ( driveExist )
                {
                driveNumber = TDriveNumber( i );
                rootPath.Zero();
                memoryType = AknCFDUtility::DriveMemoryTypeL( driveNumber );
                if( memoryType & iIncludedMedias )
                    {
                    User::LeaveIfError(
                    PathInfo::GetRootPath( rootPath, driveNumber ) );
                    }
                else
                    {
                    continue;
                    }
                
                TBool isUserDefined = EFalse;
                // add right location even user's location with wrong sequence
                for ( TInt j = 0; j < iDefDriveArray->MdcaCount(); j++ )
                    {
                    // same drive info and user's root path must under c:\data\.
                    // try to get the location
                    if ( ( *iDefDriveArray )[j].FindC( rootPath ) == 0 )
                        {
                        // Use user's root path, part of user definiens
                        // (lowercase) may be replaced by system rootPath
                        rootPath.Append( ( *iDefDriveArray )[j].Right( 
                            ( *iDefDriveArray )[j].Length() - rootPath.Length() ) );
                        driveArray->AppendL( rootPath );
                        defaultFolderArray->AppendL( ( *iDefDefaultFolderArray )[j] );
                        isUserDefined = ETrue;
                        break;
                        }
                    }
                if ( !isUserDefined )
                    {
                    // user does not define location for this drive
                    // use the default
                    driveArray->AppendL( rootPath );
                    defaultFolderArray->AppendL( KNullDesC );
                    }
                }
            }
        }
    else
        {
        for ( TInt i=0; i<KMaxDrives; i++ )
            {
            TInt drive = driveList[i];
            driveNumber = TDriveNumber( i );
            if (drive)
                {
                memoryType = AknCFDUtility::DriveMemoryTypeL( driveNumber );
                if( memoryType & iIncludedMedias )
                    {
                    User::LeaveIfError(
                        PathInfo::GetRootPath( rootPath, driveNumber ) );
                    driveArray->AppendL( rootPath );
                    defaultFolderArray->AppendL( KNullDesC );
                    }
                }
            }
        }
    }

// End of File
