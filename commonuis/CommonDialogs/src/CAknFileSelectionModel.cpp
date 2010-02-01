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
#include "CAknFileSelectionModel.h"

#include <CDirectoryLocalizer.h>
#include <barsread.h>   // TResourceReader
#include <bautils.h>    // BaflUtils for checking if a path exists
#include <coemain.h>
#include <commondialogs.rsg>
#include <apmstd.h> // TDataType
#include <badesca.h>    //CDesC16Array

#include "MAknFileSelectionObserver.h"
#include "MAknFileFilter.h"
#include "AknCFDUtility.h"
#include "CAknDataCagingFilter.h"

// CONSTANTS
const TInt KEntryArrayGranularity( 10 );
const TInt KFilterArrayGranularity( 2 );

_LIT( KCFDMimeTypeImage, "image/*" );
_LIT( KCFDMimeTypeImageGms, "image/x-ota-bitmap" );
_LIT( KCFDMimeTypeRam, "audio/x-pn-realaudio-plugin" ); // = link
_LIT( KCFDMimeTypeAudioVoiceRec, "audio/amr*" );
_LIT( KCFDMimeTypeAudioVoiceRec2, "application/vnd.nokia.ringing-tone" );
_LIT( KCFDMimeTypeAudio, "audio/*" ); // = other sound files
_LIT( KCFDMimeTypePlaylist, "audio/*mpegurl*" );
_LIT( KCFDMimeTypeVideo, "video/*" );
_LIT( KCFDMimeTypeVideoRealMedia, "application/*n-realmedia" );
_LIT( KCFDMimeTypeVideoSdp, "application/sdp" );
_LIT( KCFDMimeTypeGame, "application/*game*" );
_LIT( KCFDMimeTypeNote, "text/*" );
_LIT( KCFDMimeTypeJava, "application/java-archive" );
_LIT( KCFDMimeTypeFlash, "application/x-shockwave-flash" );

_LIT( KCFDFileExtSis, ".sis" );
_LIT( KCFDFileExtSisx, ".sisx");
_LIT( KCFDFileExtMid, ".mid" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::CAknFileSelectionModel
//
//
// -----------------------------------------------------------------------------
//
CAknFileSelectionModel::CAknFileSelectionModel(
    const TCommonDialogType& aDialogType, CCoeEnv& aCoeEnv )
    :   iImageIndexArray( KEntryArrayGranularity ),
        iDirectoryLevel( 0 ),
        iDialogType( aDialogType ),
        iCoeEnv( aCoeEnv )
    {
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::ConstructL
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionModel::ConstructL()
    {
    User::LeaveIfError( iApaSession.Connect() );
    iLocalizer = CDirectoryLocalizer::NewL();
    iEntryArray = new( ELeave ) CArrayPakFlat<TEntry>( KEntryArrayGranularity );
    iFilterArray = new( ELeave ) CArrayPtrSeg<MAknFileFilter>( KFilterArrayGranularity );
    iItemWithImageIndex = HBufC::NewL(KMaxPath);
    User::LeaveIfError( iFs.Connect() );
    iRootFolderText = iCoeEnv.AllocReadResourceL( R_CFD_QTN_FLDR_ROOT_LEVEL );

    AddFilterL( CAknDataCagingFilter::NewLC() );
    CleanupStack::Pop();    //caging filter
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::NewL
//
// -----------------------------------------------------------------------------
//
CAknFileSelectionModel* CAknFileSelectionModel::NewL(
    const TCommonDialogType& aType, CCoeEnv& aCoeEnv )
    {
    CAknFileSelectionModel* self =
        new( ELeave ) CAknFileSelectionModel( aType, aCoeEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// Destructor
CAknFileSelectionModel::~CAknFileSelectionModel()
    {
    delete iRootFolderText;
    iImageIndexArray.Close();
    iFs.Close();

    delete iItemWithImageIndex;

    if ( iFilterArray )
        {
        iFilterArray->ResetAndDestroy();
        delete iFilterArray;
        }
    if ( iEntryArray )
        {
        iEntryArray->Reset();
        delete iEntryArray;
        }
    delete iLocalizer;


    iApaSession.Close();
    }


// -----------------------------------------------------------------------------
// CAknFileSelectionModel::SetPathL
//
//
// -----------------------------------------------------------------------------
//
TInt CAknFileSelectionModel::SetPathL( const TDesC& aPath )
    {
    HBufC * path = HBufC::NewLC( KMaxPath );
    *path = aPath;
    TPtr ptrPath = path->Des();

    TInt errorCode( AknCFDUtility::AddTrailingBackslash( ptrPath ) );
    if ( errorCode != KErrNone )
        {
        CleanupStack::PopAndDestroy();
        return errorCode;
        }

    errorCode = iParse.SetNoWild( ptrPath, NULL, NULL );

    if ( errorCode != KErrNone )
        {
        // Converting path to TParse was unsuccessful
        CleanupStack::PopAndDestroy();
        return errorCode;
        }
    TEntry entry;
    TInt err( iFs.Entry( ptrPath,entry ) );
    if (  err == KErrNotFound || err == KErrPathNotFound )
        {
        // Path doesn't exist
        CleanupStack::PopAndDestroy();
        return KErrPathNotFound;
        }

    // Set as current path
    iCurrentPath = iParse;
    // Reset directory level
    iDirectoryLevel = 0;


    errorCode = UpdateItemListL();

    CleanupStack::PopAndDestroy();

    return errorCode;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::AddFolderL
//
//
// -----------------------------------------------------------------------------
//
TInt CAknFileSelectionModel::AddFolderL( const TDesC& aFolder )
    {
    // Cache the directory level because SetPath resets it
    TInt level( iDirectoryLevel );

    // The engine only supports adding one folder at a time
    if ( AknCFDUtility::DirectoryCount( aFolder ) !=  1 )
        {
        return KErrNotSupported;
        }

    //TPath currentPath( iCurrentPath.DriveAndPath() );

    HBufC * bufCurrentPath = HBufC::NewLC(KMaxPath);
    *bufCurrentPath = iCurrentPath.DriveAndPath();
    TPtr currentPath = bufCurrentPath->Des();

    currentPath.Append( aFolder );

    TInt errorCode( SetPathL( currentPath ) );

    CleanupStack::PopAndDestroy(); //bufCurrentPath

    if ( errorCode < KErrNone )
        {
        return errorCode;
        }

    iDirectoryLevel = ++level;

    return errorCode;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::AddFilterL
// Ownership of filter is moved to the engine
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionModel::AddFilterL( MAknFileFilter* aFilter )
    {
    iFilterArray->AppendL( aFilter );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::GotoSubFolderL
//
//
// -----------------------------------------------------------------------------
//
TInt CAknFileSelectionModel::GotoSubFolderL( const TDesC& aFolder )
    {
    return AddFolderL( aFolder );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::GotoParentFolderL
//
//
// -----------------------------------------------------------------------------
//
TInt CAknFileSelectionModel::GotoParentFolderL()
    {
    TInt errorCode( KErrNotFound ); // Indicating under root situation
    if ( iDirectoryLevel > 0 )
        {
        errorCode = iCurrentPath.PopDir();
        if ( errorCode == KErrNone )
            {
            iDirectoryLevel--;
            errorCode = UpdateItemListL();
            }
        }
    return errorCode;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::UpdateItemListL
// -----------------------------------------------------------------------------
//
TInt CAknFileSelectionModel::UpdateItemListL()
    {
    iEntryArray->Reset();
    iImageIndexArray.Reset();

    CDir* entryArray = ReadDirectory( iCurrentPath.DriveAndPath() );
    if ( !entryArray )
        {
        return KErrNotFound;
        }
    CleanupStack::PushL( entryArray );

    TInt itemCount( entryArray->Count() );
    if ( itemCount > 0 )
        {
        TInt filterCount( iFilterArray->Count() );
        TInt filterIndex;
        TBool accepted;
        CDesC16Array* desC16FoldersArray = new ( ELeave )
                           CDesC16ArrayFlat( KEntryArrayGranularity );
        CleanupStack::PushL( desC16FoldersArray );
        CDesC16Array* desC16FilesArray = new ( ELeave )
                           CDesC16ArrayFlat( KEntryArrayGranularity );
        CleanupStack::PushL( desC16FilesArray );
        CArrayPakFlat<TEntry>* tmpFoldersArray = new( ELeave ) 
            CArrayPakFlat<TEntry>( KEntryArrayGranularity );
        CleanupStack::PushL( tmpFoldersArray );
        CArrayPakFlat<TEntry>* tmpFilesArray = new( ELeave ) 
            CArrayPakFlat<TEntry>( KEntryArrayGranularity );
        CleanupStack::PushL( tmpFilesArray );
            
        tmpFoldersArray->Reset();
        desC16FoldersArray->Reset();
        tmpFilesArray->Reset();
        desC16FilesArray->Reset();
        
        for ( TInt i( 0 ); i < itemCount; i++ ) // Generate filtered list
            {
            accepted = ETrue; // If there are no filters, accept the entry
            TEntry entry = ( *entryArray )[i];
            filterIndex = 0;
            // Go thru the filters while the entry is accepted
            while( ( filterIndex < filterCount ) && ( accepted ) )
                {
                accepted = iFilterArray->At( filterIndex )->Accept(
                    iCurrentPath.DriveAndPath(), entry );
                filterIndex++;
                }
            if ( accepted ) // Directory entry has passed all filters
                {
                 // Add filename to filtered list
                if ( entry.IsDir() )
                    {
                    desC16FoldersArray->AppendL( GetLocalizedName( entry.iName ) );
                    tmpFoldersArray->AppendL( entry, sizeof( TEntry ) );
                    }
                else
                    {
                    desC16FilesArray->AppendL( GetLocalizedName( entry.iName ) );
                    tmpFilesArray->AppendL( entry, sizeof( TEntry ) );
                    }
                }
            }
        
        TInt entryCount = 0;
        TInt index;
        TKeyArrayPak key( _FOFF( TEntry, iName ), ECmpCollated );
        
        // Add folder entries
        desC16FoldersArray->Sort( ECmpCollated );
        entryCount = desC16FoldersArray->MdcaCount();
        for( TInt j( 0 ); j < entryCount; j++ )
            {
            for( TInt k( 0 ); k < entryCount; k++ )
                {
                if( ( *desC16FoldersArray )[j] == 
                        GetLocalizedName( ( *tmpFoldersArray )[k].iName ) &&
                    iEntryArray->Find( ( *tmpFoldersArray )[k], key, index ) != 0 )
                    {
                    TEntry tmpEntry = ( *tmpFoldersArray )[k];
                    
                    iEntryArray->AppendL( tmpEntry, sizeof( TEntry ) );
                    
                    // Entry is a directory
                    TFileTypeIcon folderIcon( EFolderIcon );
                    
                    if( !AknCFDUtility::IsRemoteDrive( iCurrentPath.Drive() ) )
                        {
                        if ( ContainsSubfolders( tmpEntry.iName ) )
                            {
                            folderIcon = ESubFolderIcon;
                            }
                        else if ( !ContainsFiles( tmpEntry.iName ) )
                            {
                            folderIcon = EFolderEmptyIcon;
                            }
                        }
                    iImageIndexArray.Append( folderIcon );
                    
                    break;
                    }
                }
            }
        
        // Add file entries
        desC16FilesArray->Sort( ECmpCollated );
        entryCount = desC16FilesArray->MdcaCount();
        for( TInt j( 0 ); j < entryCount; j++ )
            {
            for( TInt k( 0 ); k < entryCount; k++ )
                {
                if( ( *desC16FilesArray )[j] == 
                        GetLocalizedName( ( *tmpFilesArray )[k].iName ) &&
                    iEntryArray->Find( ( *tmpFilesArray )[k], key, index ) != 0 )
                    {
                    TEntry tmpFile = ( *tmpFilesArray )[k];
                    
                    iEntryArray->AppendL( tmpFile, sizeof( TEntry ) );
                    
                    // Entry is a file
                    AppendIconForFileL( tmpFile.iName );
                    
                    break;
                    }
                }
            }
        
        CleanupStack::PopAndDestroy( tmpFilesArray );
        CleanupStack::PopAndDestroy( tmpFoldersArray );
        CleanupStack::Pop( desC16FilesArray );
        desC16FilesArray->Reset();
        delete desC16FilesArray;
        CleanupStack::Pop( desC16FoldersArray );
        desC16FoldersArray->Reset();
        delete desC16FoldersArray;
        }
    
    CleanupStack::PopAndDestroy( entryArray );
    
    if ( AknCFDUtility::DirectoriesOnly( iDialogType ) )
        {
        // Set the current folder name as first item.
        // Current folder is for example "E:\Images\Holiday\"
        // Remove trailing backslash, we get "E:\Images\Holiday"
        // Parse the path with TParse and ask for NameAndExt().
        // TParse interpretes "Holiday" as file name and returns it.

        HBufC * bufFolder = HBufC::NewLC(KMaxPath);
        * bufFolder = iCurrentPath.DriveAndPath() ;
        TPtr folder = bufFolder->Des();

        AknCFDUtility::RemoveTrailingBackslash( folder ); // ignore error

        TParsePtr parsedFolder(folder);

        folder = parsedFolder.NameAndExt();
        iFolderEntry.iName = folder;
        iEntryArray->InsertL( 0, iFolderEntry, sizeof( TEntry ) );
        iImageIndexArray.Insert( EThisFolderIcon, 0 );

        CleanupStack::PopAndDestroy(); //bufFolder
        }
    
    return iEntryArray->Count();
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::Entry
//
//
// -----------------------------------------------------------------------------
//
const TEntry& CAknFileSelectionModel::Entry( const TInt& aIndex ) const
    {
    return iEntryArray->At( aIndex );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::GetCurrentPath
//
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionModel::GetCurrentPath( TDes& aPath ) const
    {
    aPath = iCurrentPath.DriveAndPath();
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::DirectoryLevel
//
//
// -----------------------------------------------------------------------------
//
TInt CAknFileSelectionModel::DirectoryLevel() const
    {
    return iDirectoryLevel;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::FolderIndex
//
//
// -----------------------------------------------------------------------------
//
TInt CAknFileSelectionModel::FolderIndex( const TDesC& aFolder ) const
    {
    TInt arrayCount( iEntryArray->Count() ); // Number of items in entry array
    TPath folder( aFolder );
    TInt folderLength( folder.Length() );
    if ( folderLength > 0 )
        {
        // If the last character is backslash, delete it
        if ( folder[ folderLength - 1 ] == '\\' )
            {
            folder.Delete( folderLength - 1, 1 );
            }
        // Try to find the folder from list
        for ( TInt index( 0 ); index < arrayCount; index++ )
            {
            if ( folder.CompareF( iEntryArray->At( index ).iName ) == 0 )
                {
                // When found, return its index
                return index;
                }
            }
        }

    // Return not found if not found
    return KErrNotFound;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::MdcaCount
//
//
// -----------------------------------------------------------------------------
//
TInt CAknFileSelectionModel::MdcaCount() const
    {
    return iEntryArray->Count();
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::MdcaPoint
//
//
// -----------------------------------------------------------------------------
//
TPtrC CAknFileSelectionModel::MdcaPoint( TInt aIndex ) const
    {
    TEntry entry = iEntryArray->At( aIndex ); // reference
    TParsePtrC parsedEntry( entry.iName );
    TPtrC fileName( parsedEntry.NameAndExt() );
    TInt entryType( iImageIndexArray[ aIndex ] );

    TPtr itemWithImageIndex = iItemWithImageIndex->Des();

    switch( entryType )
        {
        case EThisFolderIcon:
            {
            if ( iDirectoryLevel == 0 )
                {
                // Root folder
                fileName.Set( iRootFolderText->Des() );
                }
            else
                {
                // Not the root folder
                iLocalizer->SetFullPath( iCurrentPath.DriveAndPath() );
                if ( iLocalizer->IsLocalized() ) // Localized?
                    {
                    // Folder name is localized
                    fileName.Set( iLocalizer->LocalizedName() );
                    }
                }
            break;
            }
        case EFolderIcon: // fall through
        case ESubFolderIcon:
        case EFolderEmptyIcon:
            {
            itemWithImageIndex = iCurrentPath.DriveAndPath();
            itemWithImageIndex.Append( entry.iName );
            // ignore error:
            AknCFDUtility::AddTrailingBackslash( itemWithImageIndex );
            iLocalizer->SetFullPath( itemWithImageIndex );
            if( iLocalizer->IsLocalized() )
                {
                fileName.Set( iLocalizer->LocalizedName() );
                }
            break;
            }
        default: // EFileIcon
            {
            break;
            }
        }

    _LIT( KImageHeader, "%d\t" );
    itemWithImageIndex.Format( KImageHeader, entryType );
    itemWithImageIndex.Append( fileName );

    return itemWithImageIndex;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::ReadDirectory
//
//
// -----------------------------------------------------------------------------
//
CDir* CAknFileSelectionModel::ReadDirectory( const TDesC& aDirectory )
    {
    // All attributes but system and hidden attribute
    TUint mask( KEntryAttMaskSupported & ~( KEntryAttSystem | KEntryAttHidden ) );
    CDir* entryArray = NULL;

    if ( AknCFDUtility::DirectoriesOnly( iDialogType ) )
        {
        // Keep old code for possible roll-back.
        /*
        mask &= ~KEntryAttDir;
        CDir* temp;
        iFs.GetDir( aDirectory, mask,
            ESortByName | EDirsFirst | EAscending, temp, entryArray );
        delete temp;
        */
        iFs.GetDir( aDirectory, KEntryAttDir | KEntryAttMatchExclusive,
            ESortByName | EAscending, entryArray );
        }
    else
        {
        iFs.GetDir( aDirectory, mask,
            ESortByName | EDirsFirst | EAscending, entryArray );
        }

    if ( entryArray )
        {
        // No errors. Remove possible system directory from list
        BaflUtils::RemoveSystemDirectory( *entryArray );
        }
    return entryArray;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::ContainsSubfolders
//
//
// -----------------------------------------------------------------------------
//
TBool CAknFileSelectionModel::ContainsSubfolders( const TDesC& aFolder )
    {
    TPath directory( iCurrentPath.DriveAndPath() );
    directory.Append( aFolder );
    AknCFDUtility::AddTrailingBackslash( directory ); // ignore error
    
    // Keep old code for possible roll-back
    /*
    CDir* array = ReadDirectory( directory );
    if( ( !array ) || ( array->Count() == 0 ) || ( !(* array)[ 0 ].IsDir() ) )
        {
        delete array;
        return EFalse;
        }
    delete array;
    return ETrue;
    */
    
    RDir dir;
    TBool ret( EFalse );
    if ( dir.Open(
        iFs, directory, KEntryAttDir | KEntryAttMatchExclusive ) != KErrNone )
        {
        return EFalse;
        }
    TEntry entry;
    if ( dir.Read( entry ) == KErrNone )
        {
        ret = ETrue;
        }
    dir.Close();
    return ret;
    }

void CAknFileSelectionModel::AppendIconForFileL(const TDesC& aFileName)
    {
    //TFileName absFileName( iCurrentPath.DriveAndPath() );
    HBufC *bufAbsFileName = HBufC::NewLC(KMaxPath);
    *bufAbsFileName = iCurrentPath.DriveAndPath();
    TPtr absFileName = bufAbsFileName->Des();

    absFileName.Append( aFileName );
    TUid uidIgnore;
    TDataType dataType;
    TInt err = iApaSession.AppForDocument( absFileName, uidIgnore, dataType );
    TInt iconIndex = EUnknowTypeIcon;
    CleanupStack::PopAndDestroy(); //bufAbsFileName

    if( err != KErrNone )
        {
        // Couldn't find out the data type, use generic file icon:
        iconIndex = EUnknowTypeIcon;
        }
    else
        {
        HBufC *bufDataTypeBuf = HBufC::NewLC(KMaxDataTypeLength);
        *bufDataTypeBuf = dataType.Des();
        TPtr dataTypeBuf = bufDataTypeBuf->Des();

        if( dataTypeBuf.MatchF( KCFDMimeTypeAudioVoiceRec ) == 0 ||
            dataTypeBuf.MatchF( KCFDMimeTypeAudioVoiceRec2 ) == 0 )
            {
            iconIndex = EVoiceRecFileIcon;
            }
        else if( dataTypeBuf.MatchF( KCFDMimeTypePlaylist ) == 0 )
            {
            iconIndex = EPlaylistFileIcon;
            }
        else if( dataTypeBuf.MatchF( KCFDMimeTypeRam ) == 0 )
            {
            iconIndex = ELinkFileIcon;
            }
        else if( dataTypeBuf.MatchF( KCFDMimeTypeAudio ) == 0 )
            {
            iconIndex = ESoundFileIcon;
            }
        else if( dataTypeBuf.MatchF( KCFDMimeTypeImageGms ) == 0 )
            {
            iconIndex = EGmsFileIcon;
            }
        else if( dataTypeBuf.MatchF( KCFDMimeTypeImage ) == 0 )
            {
            iconIndex = EImageFileIcon;
            }
        else if( dataTypeBuf.MatchF( KCFDMimeTypeVideo ) == 0 ||
                 dataTypeBuf.MatchF( KCFDMimeTypeVideoRealMedia ) == 0 ||
                 dataTypeBuf.MatchF( KCFDMimeTypeVideoSdp ) == 0 )
            {
            iconIndex = EVideoFileIcon;
            }
        else if( dataTypeBuf.MatchF( KCFDMimeTypeGame ) == 0 )
            {
            iconIndex = EGameFileIcon;
            }
        else if( dataTypeBuf.MatchF( KCFDMimeTypeNote ) == 0 )
            {
            iconIndex = ENoteFileIcon;
            }
        else if( dataTypeBuf.MatchF( KCFDMimeTypeJava ) == 0 )
            {
            iconIndex = EJavaFileIcon;
            }
        else if ( dataTypeBuf.MatchF( KCFDMimeTypeFlash ) == 0 )
            {
            iconIndex = EFlashFileIcon;
            }
        else
            {
            // Check from the file name extension, if it's a SIS file:
            //TParse fileName;
            //fileName.Set( aFileName, NULL, NULL );

            HBufC * bufFileName = aFileName.AllocLC();
            TPtr ptrFileName = bufFileName->Des();
            TParsePtr fileName(ptrFileName);

            TPtrC ext( fileName.Ext() );
            if( ext.CompareF( KCFDFileExtSis ) == 0
                || ext.CompareF( KCFDFileExtSisx ) == 0 )
                {
                iconIndex = ESisFileIcon;
                }
            // RApaLsSession does not recognize .mid's:
            else if( ext.CompareF( KCFDFileExtMid ) == 0 )
                {
                iconIndex = ESoundFileIcon;
                }
            else
                {
                iconIndex = EUnknowTypeIcon;
                }
            CleanupStack::PopAndDestroy(); //bufFileName

            }

        CleanupStack::PopAndDestroy(); //bufDataTypeBuf
        }
    iImageIndexArray.Append( iconIndex );
    }

TPtrC CAknFileSelectionModel::GetLocalizedName(const TDesC& aFileName)
    {
    TParsePtrC parsedEntry( aFileName );
    TPtrC fileName( parsedEntry.NameAndExt() );

    TPtr itemWithImageIndex = iItemWithImageIndex->Des();
    
    itemWithImageIndex = iCurrentPath.DriveAndPath();
    itemWithImageIndex.Append( aFileName);
    // ignore error:
    AknCFDUtility::AddTrailingBackslash( itemWithImageIndex );
    iLocalizer->SetFullPath( itemWithImageIndex );
    if( iLocalizer->IsLocalized() )
        {
        fileName.Set( iLocalizer->LocalizedName() );
        }
    return fileName;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::ContainsFiles
//
// -----------------------------------------------------------------------------
//
TBool CAknFileSelectionModel::ContainsFiles( const TDesC& aFolder )
    {
    TPath directory( iCurrentPath.DriveAndPath() );
    directory.Append( aFolder );
    AknCFDUtility::AddTrailingBackslash( directory ); // ignore error
    
    RDir dir;
    TBool ret( EFalse );
    if ( dir.Open(
        iFs, directory, KEntryAttNormal ) != KErrNone )
        {
        return EFalse;
        }
    TEntry entry;
    if ( dir.Read( entry ) == KErrNone )
        {
        ret = ETrue;
        }
    dir.Close();
    return ret;
    }
//  End of File
