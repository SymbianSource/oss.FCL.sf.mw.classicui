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
#include "commondialogsdata.hrh"
// CONSTANTS
_LIT( KImageHeader, "%d\t" );
const TInt KFileExtNameSize = 10;
const TInt KEntryArrayGranularity( 10 );
const TInt KFilterArrayGranularity( 2 );
const TInt KIndexDataLen = 6;

// Store file ext name and right icon index
class TCFDFileTypes
    {
public:
    TBuf<KFileExtNameSize> iFileType;
    TInt iIconIndex;
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::CAknFileSelectionModel
//
//
// -----------------------------------------------------------------------------
//
CAknFileSelectionModel::CAknFileSelectionModel(
    const TCommonDialogType& aDialogType, CCoeEnv& aCoeEnv )
      : iDirectoryLevel( 0 ),
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
    iLocalizer = CDirectoryLocalizer::NewL();
    iEntryArray = new( ELeave ) CArrayPakFlat<TEntry>( KEntryArrayGranularity );
    iFilterArray = new( ELeave ) CArrayPtrSeg<MAknFileFilter>( KFilterArrayGranularity );
    iFileTypeArray = new ( ELeave ) CArrayFixFlat<TCFDFileTypes>( KEntryArrayGranularity );
    
    // Directories should be shown in front of files in list, 
    // create two arrays to save it respectively
    iLocalFileNameArray = new ( ELeave ) CDesC16ArraySeg( KEntryArrayGranularity );
    iLocalDirNameArray = new ( ELeave ) CDesC16ArraySeg( KEntryArrayGranularity );
    
    TResourceReader reader;
    iCoeEnv.CreateResourceReaderLC( reader, R_CDF_FILE_TYPE_ICON_SET );
    ReadFileExtNameAndIconIndexL( reader );
    CleanupStack::PopAndDestroy();//reader
    
    iStringBuf = HBufC::NewL(KMaxPath);
    
    User::LeaveIfError( iFs.Connect() );
    iRootFolderText = iCoeEnv.AllocReadResourceL( R_CFD_QTN_FLDR_ROOT_LEVEL );
    AddFilterL( CAknDataCagingFilter::NewLC() );
    CleanupStack::Pop();    //caging filter
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::ReadFileExtNameAndIconIndexL
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionModel::ReadFileExtNameAndIconIndexL( TResourceReader& aReader )
    {
    // File icon will be selected by file extname.
    TInt count( aReader.ReadInt16() );
    for ( TInt i = 0; i < count; i++ )
        {
        TCFDFileTypes type;
        type.iFileType.Copy( aReader.ReadTPtrC() );
        type.iIconIndex = aReader.ReadInt32();
        iFileTypeArray->AppendL( type );
        }
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
    iFs.Close();
    if ( iFileTypeArray )
        {
        iFileTypeArray->Reset();
        delete iFileTypeArray;
        }
    if ( iLocalFileNameArray )
        {
        iLocalFileNameArray->Reset();
        delete iLocalFileNameArray;
        }
    if ( iLocalDirNameArray )
        {
        iLocalDirNameArray->Reset();
        delete iLocalDirNameArray;
        }
    delete iStringBuf;

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
    // Open new sub-folder, directory level is increased
    iDirectoryLevel++;

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
    // Clear array contents
    iEntryArray->Reset();
    iLocalDirNameArray->Reset();
    iLocalFileNameArray->Reset();
    
    CDir* entryArray = ReadDirectory( iCurrentPath.DriveAndPath() );
    if ( !entryArray )
        {
        return KErrNotFound;
        }
    CleanupStack::PushL( entryArray );

    TInt itemCount( entryArray->Count() );
    // entry index in iEntryArray
    TInt entryIndex = 0;
    for ( TInt i( 0 ); i < itemCount; i++ ) // Add entry or not
        {
        TEntry entry = ( *entryArray )[i];
        if ( EntryIsAccepted( entry ) )
            {
             // Add entry
            if ( entry.IsDir() )
                {
            // Entry is a directory
                TFileTypeIcon folderIcon( EFolderIcon );
                
                if( !AknCFDUtility::IsRemoteDrive( iCurrentPath.Drive() ) )
                    {
                    if ( ContainsSubfolders( entry.iName ) )
                        {
                        folderIcon = ESubFolderIcon;
                        }
                    else if ( !ContainsFiles( entry.iName ) )
                        {
                        folderIcon = EFolderEmptyIcon;
                        }
                    }
                // List item uses localized name and icon index to show itself,
                // common dialogs need to give user the entry's iName, list item
                // need to bind unique entry. For sorting list and binding entry,
                // save icon index, localized name and right entry index of iEntryArray
                // in the element of iLocalDirNameArray and iLocalFileNameArray
                TFileName name( GetLocalizedName( entry.iName ) );
                // Append icon index number at the end of entry's localized name
                name.AppendNumFixedWidth( folderIcon, EDecimal, KIndexDataLen );
                // Append entry index number of iEntryArray in the end
                name.AppendNumFixedWidth( entryIndex, EDecimal, KIndexDataLen );
                iLocalDirNameArray->AppendL( name );
                }
            else
                {
                TInt icon(EUnknowTypeIcon);
                icon = GetIconForFileL( entry.iName );
                TFileName name( GetLocalizedName( entry.iName ) );
                name.AppendNumFixedWidth( icon, EDecimal, KIndexDataLen );
                name.AppendNumFixedWidth( entryIndex, EDecimal, KIndexDataLen );
                iLocalFileNameArray->AppendL( name );
                }
            entryIndex++;
            iEntryArray->AppendL( entry, sizeof( TEntry ) );
            }
        }
    
    CleanupStack::PopAndDestroy( entryArray );
    // Sort list item to show
    iLocalDirNameArray->Sort( ECmpCollated );
    iLocalFileNameArray->Sort( ECmpCollated );
    if ( AknCFDUtility::DirectoriesOnly( iDialogType ) )
        {
        // Set the current folder name as first item.
        TPtr folder = iStringBuf->Des();
        folder = iCurrentPath.DriveAndPath();
        AknCFDUtility::RemoveTrailingBackslash( folder ); // ignore error
        TParsePtr parsedFolder(folder);
        folder = parsedFolder.NameAndExt();
        TFileName name(folder);
        TEntry folderEntry;
        folderEntry.iName = name;
        if ( iDirectoryLevel == 0 )
            {
            name = iRootFolderText->Des();
            }
        else
            {
            folder = iCurrentPath.DriveAndPath();
            iLocalizer->SetFullPath( folder );
            if( iLocalizer->IsLocalized() )
                {
                name = iLocalizer->LocalizedName();
                }
            }
        name.AppendNumFixedWidth( EThisFolderIcon, EDecimal, KIndexDataLen );
        name.AppendNumFixedWidth( entryIndex, EDecimal, KIndexDataLen );
        iLocalDirNameArray->InsertL( 0, name );
        iEntryArray->AppendL( folderEntry, sizeof(TEntry) );
        }
    return iEntryArray->Count();
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::EntryIsAccepted
// -----------------------------------------------------------------------------
//
TBool CAknFileSelectionModel::EntryIsAccepted( const TEntry& aEntry ) const
    {
    TInt filterCount( iFilterArray->Count() );
    // Go through the filters while the entry is accepted
    for ( TInt i = 0 ; i < filterCount ; ++i )
        {
        if ( !( iFilterArray->At( i )->Accept(
                iCurrentPath.DriveAndPath(), aEntry ) ) )
            {
            // Some filter does not accept this entry
            return EFalse;
            }
        }
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::Entry
//
//
// -----------------------------------------------------------------------------
//
const TEntry& CAknFileSelectionModel::Entry( const TInt& aIndex ) const
    {
    TInt index = aIndex;
    // List item sequence is arranged in MdcaPoint()
    if ( aIndex < iLocalDirNameArray->Count() )
        {
        // Get right entry index of iEntryArray
        TLex lex((*iLocalDirNameArray)[aIndex].Right(KIndexDataLen));
        lex.Val( index );
        }
    else
        {
        TLex lex((*iLocalFileNameArray)[aIndex - iLocalDirNameArray->Count()].Right(KIndexDataLen));
        lex.Val( index );
        }
    return iEntryArray->At( index );
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
    // List items sequence follows the sequence of sorted array
    TPtr listItem = iStringBuf->Des();
    TInt icon(0);
    if ( aIndex < iLocalDirNameArray->Count() )
        {
        // Directories need to arrange at ahead of files
        TInt len = (*iLocalDirNameArray)[aIndex].Length();
        TLex lex( (*iLocalDirNameArray)[aIndex].Mid( 
            len - KIndexDataLen - KIndexDataLen, KIndexDataLen) );
        // Get icon index for the item
        lex.Val( icon );
        listItem.Format( KImageHeader, icon );
        // Append localized name as list item name
        listItem.Append((*iLocalDirNameArray)[aIndex].Left(
            len - KIndexDataLen - KIndexDataLen ) );
        }
    else
        {
        TInt len = (*iLocalFileNameArray)[aIndex - iLocalDirNameArray->Count()].Length();
        TLex lex( (*iLocalFileNameArray)[aIndex - iLocalDirNameArray->Count()].Mid( 
            len - KIndexDataLen - KIndexDataLen, KIndexDataLen) );
        lex.Val( icon );
        listItem.Format( KImageHeader, icon );
        listItem.Append((*iLocalFileNameArray)[aIndex - iLocalDirNameArray->Count()].Left(
            len - KIndexDataLen - KIndexDataLen ) );
        }
    return listItem;
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
    return ContainsContents( aFolder, KEntryAttDir | KEntryAttMatchExclusive );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::ContainsFiles
//
// -----------------------------------------------------------------------------
//
TBool CAknFileSelectionModel::ContainsFiles( const TDesC& aFolder )
    {
    return ContainsContents( aFolder, KEntryAttNormal );
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionModel::ContainsFiles
//
// -----------------------------------------------------------------------------
//
TBool CAknFileSelectionModel::ContainsContents(
    const TDesC& aFolder, TUint aAttMask )
    {
    TPath directory( iCurrentPath.DriveAndPath() );
    directory.Append( aFolder );
    AknCFDUtility::AddTrailingBackslash( directory ); // ignore error
    
    RDir dir;
    TBool ret( EFalse );
    if ( dir.Open( iFs, directory, aAttMask ) != KErrNone )
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
// -----------------------------------------------------------------------------
// CAknFileSelectionModel::AppendIconForFileL
//
// -----------------------------------------------------------------------------
//
TInt CAknFileSelectionModel::GetIconForFileL(const TDesC& aFileName ) const
    {
    TParsePtrC ptr( aFileName );
    TPtrC ptrc = ptr.Ext();
    for ( TInt i = 0; i < iFileTypeArray->Count(); i++ )
        {
        if ( ptrc.MatchF( (*iFileTypeArray)[i].iFileType ) == 0 )
            {
            return (*iFileTypeArray)[i].iIconIndex;
            }
        }
    return EUnknowTypeIcon;
    }

TPtrC CAknFileSelectionModel::GetLocalizedName(const TDesC& aFileName)
    {
    TParsePtrC parsedEntry( aFileName );
    TPtrC fileName( parsedEntry.NameAndExt() );

    TPtr itemWithImageIndex = iStringBuf->Des();
    
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

//  End of File
