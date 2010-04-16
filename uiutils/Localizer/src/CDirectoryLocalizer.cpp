/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Source file
*
*/


//  INCLUDE FILES
#include <barsread.h>
#include <bautils.h>
#include <coemain.h>
#include <directorylocalizer.rsg>
#ifdef RD_MULTIPLE_DRIVE
 #include <pathinfo.h>
#endif // RD_MULTIPLE_DRIVE

#include "CDirectoryLocalizer.h"

//  LOCAL CONSTANTS AND MACROS

// A resource file that contains the default directories and their localized names
// Note for code inspector: make sure the path is correct
_LIT( KDLDefaultResourceFile, "z:\\resource\\directorylocalizer.rsc" );

// Total number of default localized directories is 13.
// 8 * 2 = 16, leaves some room for app specific additions without reallocation
const TInt KDLEntryGranularity = 8;

// Entry index of an entry that was never found
const TInt KDLEntryNotFound = -1;


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::CDirectoryLocalizer
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CDirectoryLocalizer::CDirectoryLocalizer()
    :   iCurrentEntry( -1 ),
        iIconIndices( KDLEntryGranularity )
    {
    }

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDirectoryLocalizer::ConstructL()
    {
    // Initialize the arrays to hold the data
    iPaths = new( ELeave ) CArrayPtrFlat< TDesC >( KDLEntryGranularity );
    iLocalizedNames = new( ELeave ) CArrayPtrFlat< TDesC >( KDLEntryGranularity );
    iExtraData = new( ELeave ) CArrayPtrFlat< TDesC >( KDLEntryGranularity );
    }

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CDirectoryLocalizer* CDirectoryLocalizer::NewL()
    {
    CDirectoryLocalizer* self = new( ELeave ) CDirectoryLocalizer();
    CleanupStack::PushL( self );
    self->ConstructL();
    
    // Will be set to NULL if CCoeEnv does not exist
    CCoeEnv* cone = CCoeEnv::Static();
    RFs fsSession;
    if( cone )
        {
        // Get a fs session from CCoeEnv
        fsSession = cone->FsSession();
        }
    else
        {
        // Create own fs session (take care for also closing it)
        User::LeaveIfError( fsSession.Connect() ) ;
        CleanupClosePushL( fsSession );
        }
        
    // Get the correct language version
    TFileName resourceFileName( KDLDefaultResourceFile );
    BaflUtils::NearestLanguageFile( fsSession, resourceFileName );

    RResourceFile resourceFile;
    resourceFile.OpenL( fsSession, resourceFileName );  // Open the resource file
    CleanupClosePushL( resourceFile );

    // The argument of ConfirmSignatureL has no meaning.
    // Declaration of the method is ConfirmSignatureL(TInt /*aSignature*/);
    resourceFile.ConfirmSignatureL( 0 );

    // Read the resource containing the default entries.
    HBufC8* defaultEntries = resourceFile.AllocReadLC( R_DIRECTORYLOCALIZER_DEFAULT_ENTRIES );
    TResourceReader reader;
    reader.SetBuffer( defaultEntries );

    // Add the default entries to the localizer
    self->AddFromResourceL( reader );

    CleanupStack::PopAndDestroy();  // defaultEntries
    CleanupStack::PopAndDestroy();  // resourceFile.Close()
    if( !cone )
        {
        // If created new fs session - close it:
        CleanupStack::PopAndDestroy();  // fsSession.Close()
        }
    CleanupStack::Pop();            // self
    return self;
    }

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CDirectoryLocalizer* CDirectoryLocalizer::NewL( TResourceReader& aReader )
    {
    CDirectoryLocalizer* self = new( ELeave ) CDirectoryLocalizer();
    CleanupStack::PushL( self );
    self->ConstructL();
    self->AddFromResourceL( aReader );
    CleanupStack::Pop();
    return self;
    }

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CDirectoryLocalizer* CDirectoryLocalizer::NewL( TInt aResourceId )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, aResourceId );
    CDirectoryLocalizer* self = NewL( reader );
    CleanupStack::PopAndDestroy();      // reader
    return self;
    }

// Destructor
EXPORT_C CDirectoryLocalizer::~CDirectoryLocalizer()
    {
    if( iPaths )
        {
        iPaths->ResetAndDestroy();
        }
    if( iLocalizedNames )
        {
        iLocalizedNames->ResetAndDestroy();
        }
    if( iExtraData )
        {
        iExtraData->ResetAndDestroy();
        }
    delete iPaths;
    delete iLocalizedNames;
    delete iExtraData;
    iIconIndices.Close();       // RArray going out of scope. Must Close().
    }

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::AddFromResourceL
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CDirectoryLocalizer::AddFromResourceL( TResourceReader& aReader )
    {
    // Read the amount of entries in the resource
    TInt directoryCount( aReader.ReadInt16() );

    // read directory data from the resource
    for ( TInt i( 0 ); i < directoryCount; i++ )
        {
        // Read path
        HBufC* desc = aReader.ReadHBufCL();     // returns NULL if the resource string is empty
        // an entry must always have a path
        __ASSERT_ALWAYS( desc, User::Panic( _L("DirLocalizer"), 0 ) );
        CleanupStack::PushL( desc );
        iPaths->AppendL( desc );
        CleanupStack::Pop();

        // Read logical name
        desc = aReader.ReadHBufCL();
        // an entry must always have a logical name
        __ASSERT_ALWAYS( desc, User::Panic( _L("DirLocalizer"), 0 ) );
        CleanupStack::PushL( desc );
        iLocalizedNames->AppendL( desc );
        CleanupStack::Pop();

        // Read extra data
        desc = aReader.ReadHBufCL();    // Append also null pointer to the array
        CleanupStack::PushL( desc );    // Nulls will be handled in ExtraData()
        iExtraData->AppendL( desc );
        CleanupStack::Pop();

        // Read icon index
        iIconIndices.Append( aReader.ReadInt16() );
        }
    }

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::AddFromResourceL
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CDirectoryLocalizer::AddFromResourceL( TInt aResourceId )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, aResourceId );
    this->AddFromResourceL( reader );
    CleanupStack::PopAndDestroy();      // reader
    }

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::SetFullPath
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
#ifdef RD_MULTIPLE_DRIVE
EXPORT_C void CDirectoryLocalizer::SetFullPath( const TDesC& aFullPath )
    {
    TBool localizationNeeded( EFalse );
    // Will be set to NULL if CCoeEnv does not exist
    CCoeEnv* cone = CCoeEnv::Static();
    RFs fs;
    if( cone )
        {
        // Get a fs session from CCoeEnv
        fs = cone->FsSession();
        }
    else
        {
        // Create own fs session (take care for also closing it)
        User::LeaveIfError( fs.Connect() ) ;
        CleanupClosePushL( fs );
        }  
    if ( aFullPath.Length() > 0 )
        {
        TInt drive = TDriveUnit( aFullPath );
        TDriveInfo driveInfo;        
        if ( fs.Drive( driveInfo, drive ) == KErrNone )
            {
            // No localization for remote drives
            localizationNeeded = !( driveInfo.iDriveAtt & KDriveAttRemote );
            }
        }
    
    if( !cone )
        {
        // If created new fs session - close it:
        CleanupStack::PopAndDestroy();  // fsSession.Close()
        }
    if ( localizationNeeded )
        {
        TInt pathType( PathInfo::PathType( aFullPath ) );
        if ( pathType != PathInfo::ENotSystemPath )
            {
            TInt count ( iPaths->Count() );
            for ( TInt i( 0 ); i < count; i++ )
                {                
                if ( PathInfo::PathType( *( iPaths->At( i ) ) ) == pathType )
                    {
                    iCurrentEntry = i;
                    return;
                    }
                }
            }
        }
    iCurrentEntry = KDLEntryNotFound;   // Didn't find a match
    }
 
#else // RD_MULTIPLE_DRIVE 
EXPORT_C void CDirectoryLocalizer::SetFullPath( const TDesC& aFullPath )
    {
    // Looks up aFullPath in the entry list. The operation is case-insensitive
    TInt count ( iPaths->Count() );

    for ( TInt i( 0 ); i < count; i++ )
        {
        if ( ( iPaths->At( i )->CompareF( aFullPath ) ) == 0 )  // if the descriptors are equal after folding
            {
            iCurrentEntry = i;
            return;
            }
        }
    iCurrentEntry = KDLEntryNotFound;   // Didn't find a match
    } 
#endif // RD_MULTIPLE_DRIVE

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::IsLocalized
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CDirectoryLocalizer::IsLocalized() const
    {
    if ( iCurrentEntry == KDLEntryNotFound )    // SetFullPath() hadn't found the path from the list
        {
        return EFalse;
        }
    else
        {
        return ETrue;
        }
    }

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::LocalizedName
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C const TDesC& CDirectoryLocalizer::LocalizedName() const
    {
    if ( iCurrentEntry == KDLEntryNotFound )    // SetFullPath() hadn't found the path from the list
        {
        return KNullDesC;
        }
    else
        {
        return *iLocalizedNames->At( iCurrentEntry );
        }
    }

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::ExtraData
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C const TDesC& CDirectoryLocalizer::ExtraData() const
    {
    if ( iCurrentEntry == KDLEntryNotFound )    // SetFullPath() hadn't found the path from the list
        {
        return KNullDesC;
        }
    else
        {
        TDesC* desc = iExtraData->At( iCurrentEntry );
        if ( desc == NULL )     // ExtraData might be a NULL ( see AddFromResourceL() )
            {
            return KNullDesC;
            }
        else
            {
            return *desc;
            }
        }
    }

// -----------------------------------------------------------------------------
// CDirectoryLocalizer::Icon
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CDirectoryLocalizer::Icon() const
    {
    if ( iCurrentEntry == KDLEntryNotFound )    // SetFullPath() hadn't found the path from the list
        {
        return KErrGeneral;
        }
    else
        {
        return iIconIndices[ iCurrentEntry ];
        }
    }

//  End of File
