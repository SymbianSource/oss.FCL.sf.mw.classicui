/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


// INCLUDES

#include "CAknFileSelectionDialog.h"

#include <barsread.h>   // TResourceReader
#include <eikfrlb.h>    // CEikFormattedCellListBox
#include <aknlists.h>   // CAknPopupList
#include <avkon.mbg>
#include <aknconsts.h>
#include <commondialogs.mbg>
#include <AknIconArray.h>
#include <AknsUtils.h>
#include <AknsConstants.h>
#include <commondialogs.rsg>

#include "CAknFileSelectionModel.h"
#include "CAknFileSelectionEventHandler.h"
#include "CAknCommonDialogsPopupList.h"
#include "AknFileFilterFactory.h"
#include "AknCFDUtility.h"

// CONSTANTS

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?classname::?classname
//
//
// -----------------------------------------------------------------------------
//
CAknFileSelectionDialog::CAknFileSelectionDialog( TCommonDialogType aDialogType )
    :   iDialogType( aDialogType ),
        iExecuted( EFalse )
    {
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::ConstructFromResourceL
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionDialog::ConstructFromResourceL( TInt aResourceId )
    {
    BaseConstructL();
    iModel = CAknFileSelectionModel::NewL( iDialogType, *iCoeEnv );

    if( aResourceId )
        {
        // If a resource id is given, read settings from it.
        ReadFromResourceL( aResourceId );
        }
    // After user resource is read, "patch" the missing values with defaults
    // by reading all missing settings from default resource.
    SetResourceId( aResourceId, iDialogType );
    ReadFromResourceL( aResourceId );

    iEventHandler = CAknFileSelectionEventHandler::NewL(
        iCoeEnv, iModel, iDialogType, iObserver,
        ( const HBufC*& ) iLeftSoftkeyFile,
        ( const HBufC*& ) iLeftSoftkeyFolder,
        ( const HBufC*& ) iRightSoftkeyRootFolder,
        ( const HBufC*& ) iRightSoftkeySubfolder );
    }


// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::NewL
//
// -----------------------------------------------------------------------------
//
EXPORT_C CAknFileSelectionDialog* CAknFileSelectionDialog::NewL(
    TCommonDialogType aDialogType )
    {
    return NewL( aDialogType, 0 );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::NewL
//
// -----------------------------------------------------------------------------
//
EXPORT_C CAknFileSelectionDialog* CAknFileSelectionDialog::NewL(
    TCommonDialogType aDialogType,
    TInt aResourceId )
    {
    CAknFileSelectionDialog* self = new( ELeave ) CAknFileSelectionDialog( aDialogType );
    CleanupStack::PushL( self );
    self->ConstructFromResourceL( aResourceId );
    CleanupStack::Pop();
    return self;
    }

// Destructor
EXPORT_C CAknFileSelectionDialog::~CAknFileSelectionDialog()
    {
    delete iModel;
    delete iEventHandler;
    delete iDefaultFolder;
    delete iRootPath;
    delete iTitle;
    delete iRightSoftkeySubfolder;
    delete iRightSoftkeyRootFolder;
    delete iLeftSoftkeyFolder;
    delete iLeftSoftkeyFile;
    }


// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::SetObserver
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileSelectionDialog::SetObserver(
    MAknFileSelectionObserver* aObserver )
    {
    iObserver = aObserver;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::AddFilterL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileSelectionDialog::AddFilterL( MAknFileFilter* aFilter )
    {
    iModel->AddFilterL( aFilter );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::SetDefaultFolderL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileSelectionDialog::SetDefaultFolderL( const TDesC& aDefaultFolder )
    {
    AknCFDUtility::AllocateIfValidL( iDefaultFolder, aDefaultFolder );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::SetTitleL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileSelectionDialog::SetTitleL( const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iTitle, aText );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::SetLeftSoftkeyFileL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileSelectionDialog::SetLeftSoftkeyFileL( const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iLeftSoftkeyFile, aText );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::SetLeftSoftkeyFolderL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileSelectionDialog::SetLeftSoftkeyFolderL( const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iLeftSoftkeyFolder, aText );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::SetRightSoftkeyRootFolderL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileSelectionDialog::SetRightSoftkeyRootFolderL( const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iRightSoftkeyRootFolder, aText );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::SetRightSoftkeySubfolderL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFileSelectionDialog::SetRightSoftkeySubfolderL( const TDesC& aText )
    {
    AknCFDUtility::AllocateIfValidL( iRightSoftkeySubfolder, aText );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::ExecuteL
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknFileSelectionDialog::ExecuteL( TDes& aFileName )
    {
    __ASSERT_DEBUG( iTitle && iLeftSoftkeyFolder && iLeftSoftkeyFile &&
        iRightSoftkeyRootFolder && iRightSoftkeySubfolder,
        User::Panic( KCFDPanicText, ECFDPanicTitleOrSoftkeyNotSet ) );
	
    // Initialize model and set default values
    if( ( !iExecuted ) &&
        ( !PrepareL( aFileName ) ) )
        {
        // If root folder is empty, do not browse, returns ESelectionKey
        if( AknCFDUtility::IsRemoteDrive( aFileName ) )
            {
        	return ERightSoftkey;
            }
        else
            {
        	return ESelectionKey;
            }
        }

    // Listbox creation
    CEikFormattedCellListBox* listBox =
        new( ELeave ) CAknSingleGraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );
    TBool isEndKeyPress = EFalse;
    CAknCommonDialogsPopupList* popupList = CAknCommonDialogsPopupList::NewL(
        *iEventHandler, listBox, AknPopupLayouts::EMenuGraphicWindow, isEndKeyPress );
    CleanupStack::PushL( popupList );
    listBox->ConstructL( popupList, 0 ); // Listbox construction
    listBox->CreateScrollBarFrameL( ETrue ); // Create scroll indicator
    listBox->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff,
        CEikScrollBarFrame::EAuto );
    // Pass model to listbox
    listBox->Model()->SetItemTextArray( iModel );
    // Set model ownership type
    listBox->Model()->SetOwnershipType( ELbmDoesNotOwnItemArray );

    // Add icons to listbox, granularity 15
    CEikonEnv* eikEnv = CEikonEnv::Static();
    CAknIconArray* iconArray = new( ELeave ) CAknIconArray( 20 );
    CleanupStack::PushL( iconArray );

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    // Add folder icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray,
        skin, KAknsIIDQgnPropFolderSmall, KAvkonBitmapFile,
        EMbmAvkonQgn_prop_folder_small, EMbmAvkonQgn_prop_folder_small_mask );
    
    // Add file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray,         
        skin, KAknsIIDQgnPropFileSmall, KAvkonBitmapFile,
        EMbmAvkonQgn_prop_file_small, EMbmAvkonQgn_prop_file_small_mask );
    
    // Add sub folder icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray,
        skin, KAknsIIDQgnPropFolderSubSmall, KAvkonBitmapFile,
        EMbmAvkonQgn_prop_folder_sub_small, EMbmAvkonQgn_prop_folder_sub_small_mask );
    
    // Add current folder icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray,
        skin, KAknsIIDQgnPropFolderCurrent, KAvkonBitmapFile,
        EMbmAvkonQgn_prop_folder_current, EMbmAvkonQgn_prop_folder_current_mask );

    // Add image file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray, skin,
        KAknsIIDQgnPropFmgrFileImage, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_fmgr_file_image, EMbmCommondialogsQgn_prop_fmgr_file_image_mask );
    
    // Add graphical message image file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray, skin,
        KAknsIIDQgnPropFmgrFileGms, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_fmgr_file_gms, EMbmCommondialogsQgn_prop_fmgr_file_gms_mask );
    
    // Add link file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray, skin,
        KAknsIIDQgnPropFmgrFileLink, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_fmgr_file_link, EMbmCommondialogsQgn_prop_fmgr_file_link_mask );
    
    // Add voicerec file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray, skin,
        KAknsIIDQgnPropFmgrFileVoicerec, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_fmgr_file_voicerec, EMbmCommondialogsQgn_prop_fmgr_file_voicerec_mask );
    
    // Add sound file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray, skin,
        KAknsIIDQgnPropFmgrFileSound, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_fmgr_file_sound, EMbmCommondialogsQgn_prop_fmgr_file_sound_mask );
    
    // Add playlist file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray, skin,
        KAknsIIDQgnPropFmgrFilePlaylist, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_fmgr_file_playlist, EMbmCommondialogsQgn_prop_fmgr_file_playlist_mask );
    
    // Add compo file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray, skin,
        KAknsIIDQgnPropFmgrFileCompo, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_fmgr_file_compo, EMbmCommondialogsQgn_prop_fmgr_file_compo_mask );
    
    // Add note file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray, skin,
        KAknsIIDQgnPropNrtypNote, KAvkonBitmapFile,
        EMbmAvkonQgn_prop_nrtyp_note, EMbmAvkonQgn_prop_nrtyp_note_mask );
    
    // Add sis file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray, skin,
        KAknsIIDQgnPropAmSis, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_am_sis, EMbmCommondialogsQgn_prop_am_sis_mask );
    
    // Add video file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray, skin,
        KAknsIIDQgnPropFmgrFileVideo, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_fmgr_file_video, EMbmCommondialogsQgn_prop_fmgr_file_video_mask );
    
    // Add game file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray, skin,
        KAknsIIDQgnPropFmgrFileGame, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_fmgr_file_game, EMbmCommondialogsQgn_prop_fmgr_file_game_mask );
        
    // Add java file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray,         
        skin, KAknsIIDQgnPropAmMidlet, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_am_midlet, EMbmCommondialogsQgn_prop_am_midlet_mask );
    
    // Add unknow file type icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray,         
        skin, KAknsIIDQgnPropFmgrFileOther, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_fmgr_file_other, EMbmCommondialogsQgn_prop_fmgr_file_other_mask );
   
    // Add empty folder icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray,         
        skin, KAknsIIDQgnPropFolderEmpty, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_folder_empty, EMbmCommondialogsQgn_prop_folder_empty_mask );
        
    // Add flash file icon.
    AknCFDUtility::AppendSkinnedImageToArrayL( *eikEnv, *iconArray,         
        skin, KAknsIIDQgnPropFileSwfSmall, KCommonDialogsBitmapFile,
        EMbmCommondialogsQgn_prop_file_swf_small, EMbmCommondialogsQgn_prop_file_swf_small_mask );
    
    // Set icon array
    listBox->ItemDrawer()->FormattedCellData()->SetIconArrayL( iconArray );
    CleanupStack::Pop(); // iconArray

    popupList->SetTitleL( *iTitle );

    TInt focus( 0 );
    TInt topIndex( 0 );
    if( iExecuted )
        {
        // File selection has been executed already before, get the last
        // selection from the index stack:
        iEventHandler->PopIndices( topIndex, focus);
        }
    CListBoxView* view = listBox->View();
    if( focus > 0 )
        {
        view->SetCurrentItemIndex( focus );
        }
    if( topIndex > 0 )
        {
        view->SetTopItemIndex( topIndex );
        }

    iEventHandler->ResetSoftkeyStatus();
    iEventHandler->UpdateSoftkeysL( focus, popupList->ButtonGroupContainer() );

    TBool returnValue( popupList->ExecuteLD() );
    if( returnValue )
        {
        TInt selectedIndex( listBox->CurrentItemIndex() );
        iModel->GetCurrentPath( aFileName );
        const TEntry& entry = iModel->Entry( selectedIndex );
        if( ( selectedIndex ) || ( !AknCFDUtility::DirectoriesOnly( iDialogType ) ) )
            {
            aFileName.Append( entry.iName );
            if( entry.IsDir() )
                {
                // Append trailing backslash to a folder name, ignore return value
                AknCFDUtility::AddTrailingBackslash( aFileName );
                }
            }
        }

    CleanupStack::Pop(); // popupList
    CleanupStack::PopAndDestroy(); // listBox

    iExecuted = ETrue;
    
    if ( isEndKeyPress )
        {
        User::Leave( KErrAbort );
        }

    return returnValue;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::RunDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknFileSelectionDialog::RunDlgLD(
    TDes& aFileName,
    const TDesC& aDefaultFolder,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( 0, aFileName, aDefaultFolder, KNullDesC, aObserver );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::RunDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknFileSelectionDialog::RunDlgLD(
    TDes& aFileName,
    const TDesC& aDefaultFolder,
    const TDesC& aTitle,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( 0, aFileName, aDefaultFolder, aTitle, aObserver );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::RunDlgLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknFileSelectionDialog::RunDlgLD(
    TDes& aFileName,
    const TDesC& aDefaultFolder,
    TInt aResourceId,
    MAknFileSelectionObserver* aObserver )
    {
    return RunL( aResourceId, aFileName, aDefaultFolder, KNullDesC, aObserver );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::RunL
//
//
// -----------------------------------------------------------------------------
//
TBool CAknFileSelectionDialog::RunL(
    TInt aResourceId,
    TDes& aFileName,
    const TDesC& aDefaultFolder,
    const TDesC& aTitle,
    MAknFileSelectionObserver* aObserver )
    {
    CAknFileSelectionDialog* self;
    self = CAknFileSelectionDialog::NewL( ECFDDialogTypeSelect, aResourceId );
    CleanupStack::PushL( self );
    self->SetDefaultFolderL( aDefaultFolder );
    self->SetTitleL( aTitle );
    self->iObserver = aObserver;

    TBool returnValue( self->ExecuteL( aFileName ) );

    CleanupStack::PopAndDestroy(); // self
    return returnValue;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::PrepareL
//
//
// -----------------------------------------------------------------------------
//
TBool CAknFileSelectionDialog::PrepareL( const TDesC& aFileName )
    {
    // A root path written in resource file overrides the root path in parameter
    // If the root path field is not defined in resource, parameter is used
    TPtrC rootPath = iRootPath ? ( const TDesC& ) ( *iRootPath ) : aFileName;
    TInt itemCount( iModel->SetPathL( rootPath ) );
    if( itemCount <= 0 )
        {
        if( iDialogType == ECFDDialogTypeSelect )
            {
            // In select dialog allow open empty list
            return ETrue;
            }
        // The root folder is empty, or returned error
        return EFalse;
        }
        
    if( iDefaultFolder )
        {
        // This is a path variable that has the remaining path that needs
        // to be gone into
        
        //TPath remainingPath( *iDefaultFolder );
        HBufC *bufRemainingPath = HBufC::NewLC(KMaxPath);
        *bufRemainingPath = *iDefaultFolder;
        TPtr remainingPath = bufRemainingPath->Des();

        TInt folderIndex( 0 );
        TInt topIndex( 0 );
        if( AknCFDUtility::AddTrailingBackslash( remainingPath ) == KErrNone )
            {
            TInt folderCount( AknCFDUtility::DirectoryCount( remainingPath ) );
            TInt backslashPosition;
            
            //TPath currentFolder;
            HBufC *bufCurrentFolder = HBufC::NewLC(KMaxPath);
            TPtr currentFolder = bufCurrentFolder->Des();
            
            for( TInt index( 0 ); index < folderCount; index++ )
                {
                backslashPosition = remainingPath.Locate( TChar( '\\' ) );
                if( backslashPosition != KErrNotFound )
                    {
                    currentFolder = remainingPath.Left( backslashPosition + 1 );
                    remainingPath.Delete( 0, backslashPosition + 1 );
                    }

                folderIndex = iModel->FolderIndex( currentFolder );
                if( folderIndex < KErrNone )
                    {
                    break;
                    }

                const TInt KNumberOfViewableItems( 5 );

                // Focused item is in the middle
                topIndex = folderIndex - KNumberOfViewableItems / 2;

                // Check boundaries
                if( topIndex < 0 )
                    {
                    topIndex = 0;
                    }
                else if( topIndex + KNumberOfViewableItems > itemCount - 1 )
                    // itemCount - 1 == the last index
                    {
                    topIndex = itemCount - 1 - KNumberOfViewableItems;
                    }

                if( iEventHandler->HandleEventL(
                    MAknCommonDialogsEventObserver::ESelectionKeyPress,
                    folderIndex, topIndex, NULL ) !=
                    MAknCommonDialogsEventObserver::EItemsUpdated )
                    {
                    break;
                    }
                }
                
			CleanupStack::PopAndDestroy();// bufCurrentFolder              
                
            }
        // If we find that the folder we are going into first is empty,
        // we must come back one folder, because CAknPopupList::ExecuteLD
        // won't run if listbox has 0 items
        if( iModel->MdcaCount() == 0 )
            {
            iEventHandler->HandleEventL(
                MAknCommonDialogsEventObserver::ERightSoftkeyPress,
                folderIndex, topIndex, NULL );
            }
            
            
		CleanupStack::PopAndDestroy();// bufRemainingPath              
            
        }


    return ETrue;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::SetResourceId
//
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionDialog::SetResourceId( TInt& aResourceId, TCommonDialogType aType ) const
    {
    switch( aType )
        {
        case ECFDDialogTypeBrowse:
            {
            aResourceId = R_CFD_DEFAULT_BROWSE_FILE_SELECTION;
            break;
            }
        case ECFDDialogTypeMove:
            {
            aResourceId = R_CFD_DEFAULT_MOVE_FILE_SELECTION;
            break;
            }
        case ECFDDialogTypeSave:
            {
            aResourceId = R_CFD_DEFAULT_SAVE_FILE_SELECTION;
            break;
            }
        case ECFDDialogTypeCopy:
            {
            aResourceId = R_CFD_DEFAULT_COPY_FILE_SELECTION;
            break;
            }
        default:
            {
            aResourceId = R_CFD_DEFAULT_SELECT_FILE_SELECTION;
            break;
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionDialog::ReadFromResourceL
//
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionDialog::ReadFromResourceL( TInt aResourceId )
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
    AknCFDUtility::AllocateIfNullL( iTitle, reader.ReadTPtrC() );
    AknCFDUtility::AllocateIfNullL( iLeftSoftkeyFile, reader.ReadTPtrC() );
    AknCFDUtility::AllocateIfNullL( iLeftSoftkeyFolder, reader.ReadTPtrC() );
    AknCFDUtility::AllocateIfNullL( iRightSoftkeyRootFolder, reader.ReadTPtrC() );
    AknCFDUtility::AllocateIfNullL( iRightSoftkeySubfolder, reader.ReadTPtrC() );
    AknCFDUtility::AllocateIfNullL( iRootPath, reader.ReadTPtrC() );
    AknCFDUtility::AllocateIfNullL( iDefaultFolder, reader.ReadTPtrC() );

    // Read filter count from resource
    TInt numOfFilters( reader.ReadInt16() );
    // Create filters and pass ownership to model
    MAknFileFilter* filter;
    for( TInt index( 0 ); index < numOfFilters; index++ )
        {
        filter = AknFileFilterFactory::CreateFilterLC( reader );
        iModel->AddFilterL( filter ); // Ownership is transferred to the model
        CleanupStack::Pop(); // filter
        }
    CleanupStack::PopAndDestroy(); // reader
    }

//  End of File
