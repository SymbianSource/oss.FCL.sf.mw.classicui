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
* Description:  Dialog used to selection target memory (drive) which supports
*                multiple drives.
*
*/



#include <aknlists.h>   // Listboxes
#include <eikbtgpc.h>   // CEikButtonGroupContainer
#include <barsread.h>   // TResourceReader
#include <aknmemorycardui.mbg>
#include <avkon.mbg>
#include <commondialogs.mbg>
#include <AknIconArray.h>
#include <aknconsts.h> // KAvkonBitmapFile
#include <AknsConstants.h> // KAknsIIDQgnPropPhoneMemcLarge etc.
#include <AknsUtils.h>
#include <commondialogs.rsg> // Common dialogs resource IDs
#include <pathinfo.h> //PathInfo
#include <driveinfo.h> //DriveInfo
#include "CAknMemorySelectionDialogMultiDrive.h"
#include "AknCommonDialogsDynMem.h"
#include "CAknCommonDialogsPopupList.h"
#include "CAknMemorySelectionEventHandler.h"
#include "caknmemoryselectionmodelmultidrive.h"
#include "MAknCommonDialogsEventObserver.h"
#include "AknCFDUtility.h"

const TInt KCFDGranularity = 2;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::CAknMemorySelectionDialogMultiDrive
// ---------------------------------------------------------------------------
//
CAknMemorySelectionDialogMultiDrive::CAknMemorySelectionDialogMultiDrive(
    TCommonDialogType aDialogType )
    :   iDialogType( aDialogType ),
        iRootPathArray( KCFDGranularity ),
        iDefaultFolderArray( KCFDGranularity )
    {
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::ConstructFromResourceL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialogMultiDrive::ConstructFromResourceL(
    TInt aResourceId,
    TBool aShowUnavailableDrives )
    {
    ConstructFromResourceL( aResourceId, aShowUnavailableDrives,
        AknCommonDialogsDynMem::EMemoryTypePhone
        | AknCommonDialogsDynMem::EMemoryTypeInternalMassStorage
        | AknCommonDialogsDynMem::EMemoryTypeMMCExternal
        | AknCommonDialogsDynMem::EMemoryTypeRemote );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::ConstructFromResourceL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialogMultiDrive::ConstructFromResourceL(
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
    TInt userDefinedId( 0 );
    if( aResourceId )
        {
        // If a resource id is given, read settings from it.
        userDefinedId = aResourceId;
        ReadFromResourceL( aResourceId );
        }

    // After user resource is read, "patch" the missing values with defaults
    // by reading all missing settings from default resource.
    SetResourceId( aResourceId, iDialogType );
    ReadFromResourceL( aResourceId );

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

    iModel = CAknMemorySelectionModelMultiDrive::NewL(
        iCoeEnv, &iRootPathArray, &iDefaultFolderArray,
        iIncludedMedias, aShowUnavailableDrives, layout );

    // Create model of listbox listing the drives in iRootPathArray:
    GetSystemDrivesL( userDefinedId );

    iEventHandler = CAknMemorySelectionEventHandler::NewL(
            iCoeEnv, iModel, NULL );


#ifdef _DEBUG
    _LOG( "[CAknMemorySelectionDialogMultiDrive] iRootPathArray: " );
    for( TInt irp = 0; irp < iRootPathArray.MdcaCount(); irp++ )
        {
        TPtrC text = iRootPathArray.MdcaPoint( irp );
        _LOG1( "%S", &text );
        }
    _LOG( "[CAknMemorySelectionDialogMultiDrive] iDefaultFolderArray: " );
    for( TInt rpa = 0; rpa < iDefaultFolderArray.MdcaCount(); rpa++ )
        {
        TPtrC text = iDefaultFolderArray.MdcaPoint( rpa );
        _LOG1( "%S", &text );
        }
#endif //_DEBUG
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemorySelectionDialogMultiDrive*
    CAknMemorySelectionDialogMultiDrive::NewL(
        TCommonDialogType aDialogType,
        TBool aShowUnavailableDrives )
    {
    return NewL( aDialogType, 0, aShowUnavailableDrives );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemorySelectionDialogMultiDrive*
    CAknMemorySelectionDialogMultiDrive::NewL(
        TCommonDialogType aDialogType,
        TInt aResourceId,
        TBool aShowUnavailableDrives )
    {
    if( aDialogType == ECFDDialogTypeDefaultSetting )
        {
    	User::Leave( KErrNotSupported );
        }
    CAknMemorySelectionDialogMultiDrive* self =
        new( ELeave ) CAknMemorySelectionDialogMultiDrive( aDialogType );
    CleanupStack::PushL( self );
    self->ConstructFromResourceL( aResourceId, aShowUnavailableDrives );
    CleanupStack::Pop(); // self
    return self;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknMemorySelectionDialogMultiDrive*
    CAknMemorySelectionDialogMultiDrive::NewL(
        TCommonDialogType aDialogType,
        TInt aResourceId,
        TBool aShowUnavailableDrives,
        TInt aIncludedMedias )
    {
    if( aDialogType == ECFDDialogTypeDefaultSetting )
        {
    	User::Leave( KErrNotSupported );
        }
    CAknMemorySelectionDialogMultiDrive* self =
        new( ELeave ) CAknMemorySelectionDialogMultiDrive( aDialogType );
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
EXPORT_C
    CAknMemorySelectionDialogMultiDrive::~CAknMemorySelectionDialogMultiDrive()
    {
    delete iEventHandler;
    delete iModel;
    delete iTitle;
    delete iLeftSoftkey;
    delete iRightSoftkey;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::SetTitleL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionDialogMultiDrive::SetTitleL(
    const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iTitle, aText );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::SetLeftSoftkeyL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionDialogMultiDrive::SetLeftSoftkeyL(
    const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iLeftSoftkey, aText );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::SetRightSoftkeyL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionDialogMultiDrive::SetRightSoftkeyL(
    const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iRightSoftkey, aText );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::GetItem
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknMemorySelectionDialogMultiDrive::GetItem(
    TInt aIndex, TDes& aItem )
    {
    iModel->GetItem( aIndex, aItem );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::ExecuteL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknCommonDialogsBase::TReturnKey
    CAknMemorySelectionDialogMultiDrive::ExecuteL(
        TDriveNumber& aSelectedDrive )
    {
    return ExecuteL( aSelectedDrive, NULL, NULL );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::ExecuteL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknCommonDialogsBase::TReturnKey
    CAknMemorySelectionDialogMultiDrive::ExecuteL(
        TDriveNumber& aSelectedDrive, TDes* aRootPath, TDes* aDefaultFolder )
    {
    __ASSERT_DEBUG( iTitle && iLeftSoftkey && iRightSoftkey,
        User::Panic( KCFDPanicText, ECFDPanicTitleOrSoftkeyNotSet ) );

    iModel->UpdateItemsL();
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

    // Set listener for popuplist anytime.
    TBool hasRemoteDrive =
        ( iIncludedMedias & AknCommonDialogsDynMem::EMemoryTypeRemote );
    iEventHandler->StartNotifyDisk( popupList, hasRemoteDrive );

    TInt selectedIndex = FindIndexByDrive( aSelectedDrive );
    if( selectedIndex == KErrNotFound )
        {
        selectedIndex = 0; // The first index
        }
        
    listBox->View()->SetCurrentItemIndex( selectedIndex );

    // Update CAB show.
    iEventHandler->HandleEventL(
    		MAknCommonDialogsEventObserver::EFocusChange,
    		selectedIndex,
    		selectedIndex,
    		popupList->ButtonGroupContainer() );
    
    CleanupStack::Pop(); // popupList (deleted in ExecuteLD)
    // Execute the popup dialog
    TBool returnValue = EFalse;
    TRAPD( err, returnValue = popupList->ExecuteLD() );
    
    if ( iEventHandler )
        {        
        iEventHandler->StopNotifyDisk();
        }
    
    if( returnValue )
        {
        selectedIndex = listBox->CurrentItemIndex();
        GetDrivePaths( selectedIndex, aRootPath, aDefaultFolder );
        aSelectedDrive = FindDriveByIndex( selectedIndex );
        }
    else if ( err )
        {
        User::Leave( err );
        }
    
    CleanupStack::PopAndDestroy(); // listBox
    return TReturnKey( returnValue );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::RunDlgLD
// A wrapper for RunL.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknMemorySelectionDialogMultiDrive::RunDlgLD(
    TDriveNumber& aSelectedDrive )
    {
    return RunL( 0, aSelectedDrive, NULL, NULL, KNullDesC );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::RunDlgLD
// A wrapper for RunL.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknMemorySelectionDialogMultiDrive::RunDlgLD(
    TDriveNumber& aSelectedDrive,
    const TDesC& aTitle )
    {
    return RunL( 0, aSelectedDrive, NULL, NULL, aTitle );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::RunDlgLD
// A wrapper for RunL.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknMemorySelectionDialogMultiDrive::RunDlgLD(
    TDriveNumber& aSelectedDrive,
    TInt aResourceId,
    TDes* aRootPath,
    TDes* aDefaultFolder )
    {
    return RunL(
        aResourceId, aSelectedDrive, aRootPath, aDefaultFolder, KNullDesC );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::RunL
// ---------------------------------------------------------------------------
//
TBool CAknMemorySelectionDialogMultiDrive::RunL(
    TInt aResourceId,
    TDriveNumber& aSelectedDrive,
    TDes* aRootPath,
    TDes* aDefaultFolder,
    const TDesC& aTitle
    )
    {
    CAknMemorySelectionDialogMultiDrive* self =
        CAknMemorySelectionDialogMultiDrive::NewL(
            ECFDDialogTypeNormal, aResourceId, ETrue );
    CleanupStack::PushL( self );

    self->SetTitleL( aTitle );

    TBool returnValue(
        self->ExecuteL( aSelectedDrive, aRootPath, aDefaultFolder ) );

    CleanupStack::PopAndDestroy();
    return returnValue;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::AddDrivePathsL
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknMemorySelectionDialogMultiDrive::AddDrivePathsL(
    const TDesC& aRootPath,
    const TDesC& aDefaultFolder
    )
    {
    // TODO: Verify paramters if they are valid.
    TInt rootPathCount=iRootPathArray.Count();
    TInt result = KErrNone;
    TPath path;
    for ( TInt i=0;i<rootPathCount;i++ )
        {
        path.Copy( iRootPathArray[i] );
        path.Append( aRootPath );
        AknCFDUtility::AddTrailingBackslash( path );
        iRootPathArray.Delete(i);
        iRootPathArray.Compress();
        iRootPathArray.InsertL( i, path );
        path.Copy( aDefaultFolder );
        AknCFDUtility::AddTrailingBackslash( path );
        iDefaultFolderArray.Delete(i);
        iDefaultFolderArray.Compress();
        iDefaultFolderArray.InsertL( i, path );
        }
    return result;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::GetDrivePaths
// ---------------------------------------------------------------------------
//
TInt CAknMemorySelectionDialogMultiDrive::GetDrivePaths(
    TDriveNumber aDrive,
    TDes* aRootPath,
    TDes* aDefaultFolder )
    {
    TInt index = FindIndexByDrive( aDrive );
    if ( index >= 0 )
        return GetDrivePaths( index, aRootPath, aDefaultFolder );
    return KErrNotFound;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::GetDrivePaths
// ---------------------------------------------------------------------------
//
TInt CAknMemorySelectionDialogMultiDrive::GetDrivePaths(
    TInt aLbxIndex,
    TDes* aRootPath,
    TDes* aDefaultFolder )
    {

    if ( ( aLbxIndex >= 0 )
        && ( iRootPathArray.Count() > aLbxIndex )
        && ( iDefaultFolderArray.Count() > aLbxIndex ) )
        {
        if( aRootPath )
            {
            *aRootPath = iRootPathArray[ aLbxIndex ];
            }
        if( aDefaultFolder )
            {
            *aDefaultFolder = iDefaultFolderArray[ aLbxIndex ];
            }
        return KErrNone;
        }
    else
        return KErrNotFound;
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::LoadIconsL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialogMultiDrive::LoadIconsL(
    CAknIconArray* aIconArray, TBool aDoubleStyle )
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
            skin, KAknsIIDQgnPropFmgrMmcSub, KCommonDialogsBitmapFile,
            EMbmCommondialogsQgn_prop_fmgr_mmc_sub,
            EMbmCommondialogsQgn_prop_fmgr_mmc_sub_mask );
        /**
        * !!! NOTE !!!
        * Inserting NULL pointers so the aIconArray count is always same
        * regardless the if(doubleStyle) clause. In doubleStyle the icons
        * are actually replaced by localized strings.
        */
        aIconArray->AppendL( NULL );// Uses mmc_locked string instead.

        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropFmgrMmcNoSub, KCommonDialogsBitmapFile,
            EMbmCommondialogsQgn_prop_fmgr_mmc_no_sub,
            EMbmCommondialogsQgn_prop_fmgr_mmc_no_sub_mask );

        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropRemoteDriveMemcLarge, KAvkonBitmapFile,
            EMbmAvkonQgn_prop_remote_drive_memc_large,
            EMbmAvkonQgn_prop_remote_drive_memc_large_mask );

        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnIndiConnectionOnAdd, KAvkonBitmapFile,
            EMbmAvkonQgn_indi_connection_on_add,
            EMbmAvkonQgn_indi_connection_on_add_mask,
            ETrue );
        //For Internal Mass Storage
        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropFmgrMs, KCommonDialogsBitmapFile,
            EMbmCommondialogsQgn_prop_fmgr_ms,
            EMbmCommondialogsQgn_prop_fmgr_ms_mask );
        //For unavailable Internal Mass Storage
        aIconArray->AppendL( NULL );// Uses string insterad.
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
            skin, KAknsIIDQgnPropMmcNon, KCommonDialogsBitmapFile,
            EMbmCommondialogsQgn_prop_fmgr_mmc_no_sub,
            EMbmCommondialogsQgn_prop_fmgr_mmc_no_sub_mask );

        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropRemoteDriveMemc, KAvkonBitmapFile,
            EMbmAvkonQgn_prop_remote_drive_memc,
            EMbmAvkonQgn_prop_remote_drive_memc_mask );

        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnIndiConnectionOnAdd, KAvkonBitmapFile,
            EMbmAvkonQgn_indi_connection_on_add,
            EMbmAvkonQgn_indi_connection_on_add_mask,
            ETrue );
        //For Internal Mass Storage
        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropFmgrMsSmall, KCommonDialogsBitmapFile,
            EMbmCommondialogsQgn_prop_fmgr_ms_small,
            EMbmCommondialogsQgn_prop_fmgr_ms_small_mask );
        //For unavailable Internal Mass Storage
        AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *aIconArray,
            skin, KAknsIIDQgnPropMmcNon, KMemoryCardUiBitmapFile,
            EMbmAknmemorycarduiQgn_prop_mmc_non,
            EMbmAknmemorycarduiQgn_prop_mmc_non_mask );
        }
    _LOG1( "[CAknMemorySelectionDialog] aIconArray count=%d",
           aIconArray->Count() );
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::NumberOfItems
// ---------------------------------------------------------------------------
//
TInt CAknMemorySelectionDialogMultiDrive::NumberOfItems() const
    {
    return iModel->MdcaCount();
    }


// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::SetResourceId
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialogMultiDrive::SetResourceId(
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
// CAknMemorySelectionDialogMultiDrive::ReadFromResourceL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialogMultiDrive::ReadFromResourceL( TInt aResourceId )
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
    // Read title.
    AknCFDUtility::AllocateIfNullL( iTitle, reader.ReadTPtrC() );
    // Read left softkey text.
    AknCFDUtility::AllocateIfNullL( iLeftSoftkey, reader.ReadTPtrC() );
    // Read right softkey text.
    AknCFDUtility::AllocateIfNullL( iRightSoftkey, reader.ReadTPtrC() );

    CleanupStack::PopAndDestroy(); // reader
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::GetSystemDrivesL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialogMultiDrive::GetSystemDrivesL( TInt aUserDefinedId )
    {
    TInt locations = 0;
    TResourceReader reader;
    if( aUserDefinedId )
        {        
        iCoeEnv->CreateResourceReaderLC( reader, aUserDefinedId );
        reader.ReadTPtrC();   //Rede title   
        reader.ReadTPtrC();   // Read left softkey text.
        reader.ReadTPtrC();   // Read right softkey text.
        locations = reader.ReadInt16();
        if ( locations > 0 )
            {
            // Read user defined data into model
            iModel->ReadUserDefinedDataL( reader, locations );
            }
        CleanupStack::PopAndDestroy(); // reader
        }
    
    //Update root path and default folder arrays.
    iModel->UpdateDataArraysL();
    
    // Updates items in listbox.
    iModel->UpdateItemsL();
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::FindIndexByDrive
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknMemorySelectionDialogMultiDrive::FindIndexByDrive(
    const TDriveNumber& aDrive)
    {
    TInt rootPathCount = iRootPathArray.Count();
    TInt lbxIndex = KErrNotFound; //return KErrNotFound if not found

    for ( TInt i=0;i<rootPathCount;i++ )
        {
        if ( AknCFDUtility::DriveNumber( iRootPathArray[i] ) == aDrive )
            {
            lbxIndex = i;
            break;
            }
        }
    return lbxIndex;
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::FindDriveByIndex
// ---------------------------------------------------------------------------
//
TDriveNumber CAknMemorySelectionDialogMultiDrive::FindDriveByIndex(
    const TInt aIndex )
    {
    return TDriveNumber(
        AknCFDUtility::DriveNumber( iRootPathArray[aIndex] ) );
    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::HasUnavailbleMMC
// ---------------------------------------------------------------------------
//
TBool CAknMemorySelectionDialogMultiDrive::HasUnavailbleMMC()
    {
    return iModel->HasUnavailbleMMC();

    }

// ---------------------------------------------------------------------------
// CAknMemorySelectionDialogMultiDrive::UpdateModelL
// ---------------------------------------------------------------------------
//
void CAknMemorySelectionDialogMultiDrive::UpdateModelL()
	{
	iModel->UpdateItemsL();
	}

