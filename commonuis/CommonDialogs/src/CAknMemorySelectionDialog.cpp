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
* Description:  Dialog used to selection target memory
*
*/



#include <aknlists.h>   // Listboxes
#include <eikbtgpc.h>   // CEikButtonGroupContainer
#include <barsread.h>   // TResourceReader
#include <aknmemorycardui.mbg>
#include <avkon.mbg>
#include <AknIconArray.h>
#include <aknconsts.h> // KAvkonBitmapFile
#include <AknsConstants.h> // KAknsIIDQgnPropPhoneMemcLarge etc.
#include <AknsUtils.h>
#include <commondialogs.rsg> // Common dialogs resource IDs
#include <pathinfo.h> //PathInfo
#include <driveinfo.h> //DriveInfo

#include "CAknMemorySelectionDialog.h"
#include "AknCommonDialogsDynMem.h"
#include "CAknCommonDialogsPopupList.h"
#include "CAknMemorySelectionEventHandler.h"
#include "CAknMemorySelectionModel.h"
#include "MAknCommonDialogsEventObserver.h"
#include "AknCFDUtility.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::CAknMemorySelectionDialog
// ---------------------------------------------------------------------------
//
CAknMemorySelectionDialog::CAknMemorySelectionDialog(
    TCommonDialogType aDialogType )
    :   iDialogType( aDialogType ),
        iRootPathArray( EMemoryCount ),
        iDefaultFolderArray( EMemoryCount )
    {
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::ConstructFromResourceL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialog::ConstructFromResourceL(
    TInt aResourceId,
    TBool aShowUnavailableDrives )
    {
    // EMemoryTypePhone|EMemoryTypeMMC are the drives used in legacy code.
    ConstructFromResourceL( aResourceId, aShowUnavailableDrives,
        AknCommonDialogsDynMem::EMemoryTypePhone
        | AknCommonDialogsDynMem::EMemoryTypeMMC );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::ConstructFromResourceL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialog::ConstructFromResourceL(
    TInt aResourceId,
    TBool aShowUnavailableDrives,
    TInt aIncludedMedias )
    {
    BaseConstructL();

    iIncludedMedias = aIncludedMedias;
    if( iIncludedMedias & AknCommonDialogsDynMem::EMemoryTypeMMC )
        {
        iIncludedMedias = iIncludedMedias |
            AknCommonDialogsDynMem::EMemoryTypeInternalMassStorage
            | AknCommonDialogsDynMem::EMemoryTypeMMCExternal;
        iIncludedMedias &= ( ~AknCommonDialogsDynMem::EMemoryTypeMMC );
        }

    if( aResourceId )
        {
        // If a resource id is given, read settings from it.
        ReadFromResourceL( aResourceId, ETrue );
        }

    // After user resource is read, "patch" the missing values with defaults
    // by reading all missing settings from default resource.
    SetResourceId( aResourceId, iDialogType );
    ReadFromResourceL( aResourceId, EFalse );

    if( !iRootPathArray.Count() )
        {
        GetSystemPathsL();
        }

    MAknMemorySelectionModel::TListBoxLayout layout(
        MAknMemorySelectionModel::ELayoutPopupMenu );
    if( iDialogType == ECFDDialogTypeDefaultSetting )
        {
        layout = MAknMemorySelectionModel::ELayoutSettingPage;
        }
    else if( AknCFDUtility::DirectoriesOnly( iDialogType ) )
        {
        layout = MAknMemorySelectionModel::ELayoutDoublePopup;
        }

    // Add dynamic drives to iRootPathArray if they're required:
    if( aIncludedMedias & AknCommonDialogsDynMem::EMemoryTypeRemote )
        {
        // Enable dynamic drives, this means iRootPathArray items are dynamic.
        iDynamicDrivesEnabled = ETrue;
        AknCFDUtility::ReadDynamicDrivesL( iRootPathArray, aIncludedMedias );
        }

    // Create model of listbox listing the drives in iRootPathArray:
    iModel = CAknMemorySelectionModel::NewL(
        iCoeEnv, &iRootPathArray, aShowUnavailableDrives, layout );
    iEventHandler = CAknMemorySelectionEventHandler::NewL(
            iCoeEnv, iModel, iObserver );

#ifdef _DEBUG
    _LOG( "[CAknMemorySelectionDialog] iRootPathArray: " );
    for( TInt irp = 0; irp < iRootPathArray.MdcaCount(); irp++ )
        {
        TPtrC text = iRootPathArray.MdcaPoint( irp );
        _LOG1( "%S", &text );
        }
    _LOG( "[CAknMemorySelectionDialog] iDefaultFolderArray: " );
    for( TInt rpa = 0; rpa < iDefaultFolderArray.MdcaCount(); rpa++ )
        {
        TPtrC text = iDefaultFolderArray.MdcaPoint( rpa );
        _LOG1( "%S", &text );
        }
#endif //_DEBUG
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemorySelectionDialog* CAknMemorySelectionDialog::NewL(
    TCommonDialogType aDialogType,
    TBool aShowUnavailableDrives )
    {
    return NewL( aDialogType, 0, aShowUnavailableDrives );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemorySelectionDialog* CAknMemorySelectionDialog::NewL(
    TCommonDialogType aDialogType,
    TInt aResourceId,
    TBool aShowUnavailableDrives )
    {
    if( aDialogType == ECFDDialogTypeDefaultSetting )
        {
    	User::Leave( KErrNotSupported );
        }
    CAknMemorySelectionDialog* self =
        new( ELeave ) CAknMemorySelectionDialog( aDialogType );
    CleanupStack::PushL( self );
    self->ConstructFromResourceL( aResourceId, aShowUnavailableDrives );
    CleanupStack::Pop(); // self
    return self;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemorySelectionDialog* CAknMemorySelectionDialog::NewL(
    TCommonDialogType aDialogType,
    TInt aResourceId,
    TBool aShowUnavailableDrives,
    TInt aIncludedMedias )
    {
    if( aDialogType == ECFDDialogTypeDefaultSetting )
        {
    	User::Leave( KErrNotSupported );
        }
    CAknMemorySelectionDialog* self =
        new( ELeave ) CAknMemorySelectionDialog( aDialogType );
    CleanupStack::PushL( self );
    self->ConstructFromResourceL( aResourceId,
                                  aShowUnavailableDrives,
                                  aIncludedMedias );
    CleanupStack::Pop(); // self
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemorySelectionDialog::~CAknMemorySelectionDialog()
    {
    delete iEventHandler;
    delete iModel;
    delete iTitle;
    delete iLeftSoftkey;
    delete iRightSoftkey;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::SetObserver
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionDialog::SetObserver(
    MAknMemorySelectionObserver* aObserver )
    {
    // The observer could not be called, so the following code is useless
    iObserver = aObserver;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::SetTitleL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionDialog::SetTitleL( const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iTitle, aText );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::SetLeftSoftkeyL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionDialog::SetLeftSoftkeyL( const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iLeftSoftkey, aText );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::SetRightSoftkeyL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionDialog::SetRightSoftkeyL( const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iRightSoftkey, aText );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::GetItem
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionDialog::GetItem( TInt aIndex, TDes& aItem )
    {
    iModel->GetItem( aIndex, aItem );
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::GetMemories
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionDialog::GetMemories(
    TMemory aSelectedMemory,
    TDes* aRootPath,
    TDes* aDefaultFolder )
    {
    if( iDynamicDrivesEnabled )
        {
        // When dynamic drives are enabled, parameter aSelectedMemory is not
        // of type TMemory but TInt indexing the selected listbox item.
        // GetDrivePaths handles this logic.
        GetDrivePaths( aSelectedMemory, aRootPath, aDefaultFolder );
        }
    else
        {
        // aSelectedMemory is fixed enum pointing either Phone or MMC memory.
        // This is needed for CommonDialogs legacy implementation.
        if( aRootPath )
            {
            __ASSERT_DEBUG( ( aSelectedMemory >= 0 )
                && ( aSelectedMemory < iRootPathArray.Count() ),
                User::Panic( KCFDPanicText, ECFDPanicOutOfBounds ) );
            *aRootPath = iRootPathArray[ aSelectedMemory ];
            }
        if( aDefaultFolder )
            {
            __ASSERT_DEBUG( ( aSelectedMemory >= 0 ) &&
                            ( aSelectedMemory < iDefaultFolderArray.Count() ),
                User::Panic( KCFDPanicText, ECFDPanicOutOfBounds ) );
            *aDefaultFolder = iDefaultFolderArray[ aSelectedMemory ];
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::ExecuteL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknCommonDialogsBase::TReturnKey CAknMemorySelectionDialog::ExecuteL(
    TMemory& aSelectedMemory )
    {
    return ExecuteL( aSelectedMemory, NULL, NULL );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::ExecuteL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknCommonDialogsBase::TReturnKey CAknMemorySelectionDialog::ExecuteL(
    TMemory& aSelectedMemory,
    TDes* aRootPath,
    TDes* aDefaultFolder )
    {
    __ASSERT_DEBUG( iTitle && iLeftSoftkey && iRightSoftkey,
        User::Panic( KCFDPanicText, ECFDPanicTitleOrSoftkeyNotSet ) );

    TBool doubleStyle( AknCFDUtility::DirectoriesOnly( iDialogType ) );
    CEikFormattedCellListBox* listBox = NULL;
    if( doubleStyle )
        {
        listBox = new( ELeave ) CAknDoubleLargeGraphicPopupMenuStyleListBox();
        }
    else
        {
        listBox = new( ELeave ) CAknSingleGraphicPopupMenuStyleListBox();
        }
    CleanupStack::PushL( listBox );

    AknPopupLayouts::TAknPopupLayouts layout( doubleStyle ?
        AknPopupLayouts::EMenuDoubleLargeGraphicWindow :
        AknPopupLayouts::EMenuGraphicWindow );
    TBool isEndKeyPress = EFalse;
    CAknCommonDialogsPopupList* popupList =
        CAknCommonDialogsPopupList::NewL(
            *iEventHandler, listBox, layout, isEndKeyPress );
    CleanupStack::PushL( popupList );

    listBox->ConstructL( popupList, 0 );
    listBox->CreateScrollBarFrameL( ETrue ); // Create scroll indicator
    listBox->ScrollBarFrame()->SetScrollBarVisibilityL(
        CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );

    listBox->Model()->SetItemTextArray( iModel );
    // Set model ownership type
    listBox->Model()->SetOwnershipType( ELbmDoesNotOwnItemArray );

    // Icons:
    // Granularity, 5 icons
    CAknIconArray* iconArray = new( ELeave ) CAknIconArray( 5 );
    CleanupStack::PushL( iconArray );
    LoadIconsL( iconArray, doubleStyle );
    listBox->ItemDrawer()->FormattedCellData()->SetIconArrayL( iconArray );
    CleanupStack::Pop(); // iconArray

    popupList->SetTitleL( *iTitle ); // Set title
    CEikButtonGroupContainer* cba = popupList->ButtonGroupContainer();
    MEikButtonGroup* buttonGroup = cba->ButtonGroup();
    cba->SetCommandL( buttonGroup->CommandId( 0 ), *iLeftSoftkey );
    cba->SetCommandL( buttonGroup->CommandId( 2 ), *iRightSoftkey );

    listBox->View()->SetCurrentItemIndex( aSelectedMemory );

    CleanupStack::Pop(); // popupList (deleted in ExecuteLD)
    // Execute the popup dialog
    TBool returnValue( popupList->ExecuteLD() );

    if( returnValue )
        {
        aSelectedMemory = TMemory( listBox->CurrentItemIndex() );
        GetMemories( aSelectedMemory, aRootPath, aDefaultFolder );
        }
    CleanupStack::PopAndDestroy(); // listBox
    return TReturnKey( returnValue );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::RunDlgLD
// A wrapper for RunL.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknMemorySelectionDialog::RunDlgLD(
    TMemory& aSelectedMemory,
    MAknMemorySelectionObserver* aObserver )
    {
    return RunL( 0, aSelectedMemory,
        NULL, NULL, KNullDesC, aObserver );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::RunDlgLD
// A wrapper for RunL.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknMemorySelectionDialog::RunDlgLD(
    TMemory& aSelectedMemory,
    const TDesC& aTitle,
    MAknMemorySelectionObserver* aObserver )
    {
    return RunL( 0, aSelectedMemory,
        NULL, NULL, aTitle, aObserver );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::RunDlgLD
// A wrapper for RunL.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknMemorySelectionDialog::RunDlgLD(
    TMemory& aSelectedMemory,
    TInt aResourceId,
    TDes* aRootPath, TDes* aDefaultFolder,
    MAknMemorySelectionObserver* aObserver )
    {
    return RunL( aResourceId, aSelectedMemory,
        aRootPath, aDefaultFolder, KNullDesC, aObserver );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::GetDrivePaths
// ---------------------------------------------------------------------------
//
TInt CAknMemorySelectionDialog::GetDrivePaths(
    TInt aLbxIndex,
    TDes* aRootPath,
    TDes* aDefaultFolder )
    {
    if ( aLbxIndex >= 0 )
        {
        if( aRootPath && ( iRootPathArray.Count() > aLbxIndex ))
            {
            // aRootPath is required.
            *aRootPath = iRootPathArray[ aLbxIndex ];
            }
        if( aDefaultFolder && ( iDefaultFolderArray.Count() > aLbxIndex ))
            {
            // aDefaultFolder is required.
            *aDefaultFolder = iDefaultFolderArray[ aLbxIndex ];
            }
        return KErrNone;
        }
    else
        return KErrNotFound;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::LoadIconsL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialog::LoadIconsL( CAknIconArray* aIconArray,
                                            TBool aDoubleStyle )
    {
    CEikonEnv* eikEnv = CEikonEnv::Static();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    if( aDoubleStyle )
        {
        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropPhoneMemcLarge, KAvkonBitmapFile,
            EMbmAvkonQgn_prop_phone_memc_large,
            EMbmAvkonQgn_prop_phone_memc_large_mask );
        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropMmcMemcLarge, KAvkonBitmapFile,
            EMbmAvkonQgn_prop_mmc_memc_large,
            EMbmAvkonQgn_prop_mmc_memc_large_mask );
        /**
        * !!! NOTE !!!
        * Inserting NULL pointers so the aIconArray count is always same
        * regardless the if(doubleStyle) clause. In doubleStyle the icons
        * are actually replaced by localized strings.
        */
        aIconArray->AppendL( NULL );// Uses mmc_locked string instead.
        aIconArray->AppendL( NULL );// Uses mmc_non string insterad.

        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropRemoteDriveMemcLarge, KAvkonBitmapFile,
            EMbmAvkonQgn_prop_remote_drive_memc_large,
            EMbmAvkonQgn_prop_remote_drive_memc_large_mask );

        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnIndiConnectionOnAdd, KAvkonBitmapFile,
            EMbmAvkonQgn_indi_connection_on_add,
            EMbmAvkonQgn_indi_connection_on_add_mask );
        }
    else
        {
        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropPhoneMemc, KMemoryCardUiBitmapFile,
            EMbmAknmemorycarduiQgn_prop_phone_memc,
            EMbmAknmemorycarduiQgn_prop_phone_memc_mask );
        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropMmcMemc, KMemoryCardUiBitmapFile,
            EMbmAknmemorycarduiQgn_prop_mmc_memc,
            EMbmAknmemorycarduiQgn_prop_mmc_memc_mask );
        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropMmcLocked, KMemoryCardUiBitmapFile,
            EMbmAknmemorycarduiQgn_prop_mmc_locked,
            EMbmAknmemorycarduiQgn_prop_mmc_locked_mask );
        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropMmcNon, KMemoryCardUiBitmapFile,
            EMbmAknmemorycarduiQgn_prop_mmc_non,
            EMbmAknmemorycarduiQgn_prop_mmc_non_mask );
        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropRemoteDriveMemc, KMemoryCardUiBitmapFile,
            EMbmAvkonQgn_prop_remote_drive_memc,
            EMbmAvkonQgn_prop_remote_drive_memc_mask );

        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnIndiConnectionOnAdd, KMemoryCardUiBitmapFile,
            EMbmAvkonQgn_indi_connection_on_add,
            EMbmAvkonQgn_indi_connection_on_add_mask );
        }
    _LOG1( "[CAknMemorySelectionDialog] aIconArray count=%d",
           aIconArray->Count() );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::NumberOfItems
// ---------------------------------------------------------------------------
//
TInt CAknMemorySelectionDialog::NumberOfItems() const
    {
    return iModel->MdcaCount();
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::RunL
// ---------------------------------------------------------------------------
//
TBool CAknMemorySelectionDialog::RunL(
    TInt aResourceId,
    TMemory& aSelectedMemory,
    TDes* aRootPath,
    TDes* aDefaultFolder,
    const TDesC& aTitle,
    MAknMemorySelectionObserver* aObserver
    )
    {
    CAknMemorySelectionDialog* self = CAknMemorySelectionDialog::NewL(
        ECFDDialogTypeNormal, aResourceId, ETrue );
    CleanupStack::PushL( self );

    self->iObserver = aObserver;
    self->SetTitleL( aTitle );

    TBool returnValue(
        self->ExecuteL( aSelectedMemory, aRootPath, aDefaultFolder ) );

    CleanupStack::PopAndDestroy();
    return returnValue;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::SetResourceId
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialog::SetResourceId(
    TInt& aResourceId, TCommonDialogType aDialogType ) const
    {
    switch( aDialogType )
        {
        case ECFDDialogTypeMove:
            {
            aResourceId = R_CFD_DEFAULT_MOVE_MEMORY_SELECTION;
            break;
            }
        case ECFDDialogTypeSave:
            {
            aResourceId = R_CFD_DEFAULT_SAVE_MEMORY_SELECTION;
            break;
            }
        case ECFDDialogTypeSelect:
            {
            aResourceId = R_CFD_DEFAULT_SELECT_MEMORY_SELECTION;
            break;
            }
        case ECFDDialogTypeCopy:
            {
            aResourceId = R_CFD_DEFAULT_COPY_MEMORY_SELECTION;
            break;
            }
        case ECFDDialogTypeDefaultSetting:
            {
            aResourceId = R_CFD_DEFAULT_DEFAULT_MEMORY_SELECTION;
            break;
            }
        default:
            {
            aResourceId = R_CFD_DEFAULT_MEMORY_SELECTION;
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::ReadFromResourceL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialog::ReadFromResourceL(
    TInt aResourceId, TBool aResourceDefined )
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
    // Read title.
    AknCFDUtility::AllocateIfNullL( iTitle, reader.ReadTPtrC() );
    // Read left softkey text.
    AknCFDUtility::AllocateIfNullL( iLeftSoftkey, reader.ReadTPtrC() );
    // Read right softkey text.
    AknCFDUtility::AllocateIfNullL( iRightSoftkey, reader.ReadTPtrC() );

    TBool readLocations = ETrue; // This is for debugging
    if( readLocations && aResourceDefined )
        {
        // Read number of LOCATION structures.
        TInt locations( reader.ReadInt16() );
        // There must be either 0 or 2 or more locations because
        // user doesn't have to define locations.
        // If they are not defined, defaults C:\ and E:\ are used.
        // If locations are defined, there must be at least two of them.
        __ASSERT_DEBUG( locations == 0 || locations >= 2,
            User::Panic( KCFDPanicText, ECFDPanicNoLocationStructures ) );

        TPtrC temp;
        TPath rootPath;
        for( TInt index( 0 ); index < locations; index++ )
            {
            temp.Set( reader.ReadTPtrC() );
            // Check that root path is defined
            // Descriptor must be at least 3 chars long (X:\).
            __ASSERT_DEBUG( temp.Length() >= 3,
                User::Panic( KCFDPanicText,
                             ECFDPanicRootPathNotDefined ) );

             // Must not return an error
            __ASSERT_DEBUG( AknCFDUtility::DriveNumber( temp ) >= 0,
                User::Panic( KCFDPanicText,
                             ECFDPanicRootPathNotDefined ) );

            rootPath.Zero();
            TDriveNumber drive =
                ( TDriveNumber )AknCFDUtility::DriveNumber( temp );
            if( drive == EDriveC )
                {
                rootPath = PathInfo::PhoneMemoryRootPath();
                }
            else
                {
                // There is an issue with the function PathInfo::MemoryCardRootPath(),
                // so use this method to get MemoryCardRootPath.
                TChar driveLetter;
                _LIT( KPathTail, ":\\" );
                User::LeaveIfError(
                    DriveInfo::GetDefaultDrive(
                            DriveInfo::EDefaultRemovableMassStorage,
                            driveLetter ) );
                rootPath.Append( driveLetter );
                rootPath.Append( KPathTail );
                }
            TBool rightRootPath = EFalse;
            if ( temp.FindC( rootPath ) == 0 )
                {
                // Use user's root path, part of user defines
                // (lowercase) may be replaced by rootPath
                rootPath.Append( temp.Right( temp.Length() - 
                    rootPath.Length() ) );
                rightRootPath = ETrue;
                }
            iRootPathArray.AppendL( rootPath );

			temp.Set( reader.ReadTPtrC() );
            if ( rightRootPath )
                {
                iDefaultFolderArray.AppendL( temp );
                }
            else
                {
                iDefaultFolderArray.AppendL( KNullDesC );
                }
            }
        } // if readLocations
    CleanupStack::PopAndDestroy(); // reader
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionDialog::GetSystemPaths
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialog::GetSystemPathsL()
    {
    iRootPathArray.AppendL( PathInfo::PhoneMemoryRootPath() );
    // There is an issue with the function PathInfo::MemoryCardRootPath(),
    // so use this method to get MemoryCardRootPath.
    TPath rootPath;
    TChar driveLetter;
    rootPath.Zero();
    _LIT( KPathTail, ":\\" );
    User::LeaveIfError(
        DriveInfo::GetDefaultDrive(
                DriveInfo::EDefaultRemovableMassStorage,
                driveLetter ) );
    rootPath.Append( driveLetter );
    rootPath.Append( KPathTail );
    iRootPathArray.AppendL( rootPath );
    iDefaultFolderArray.AppendL( KNullDesC );
    iDefaultFolderArray.AppendL( KNullDesC );
    }
