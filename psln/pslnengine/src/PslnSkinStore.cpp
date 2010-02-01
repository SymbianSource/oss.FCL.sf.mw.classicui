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
* Description:  Skin store.
*
*/


// INCLUDE FILES

// Psln specific.
#include "PslnSkinStore.h"
#include "PslnModel.h"
#include "PslnSkinEntry.h"
#include "PslnDebug.h"

// Repository
#include <centralrepository.h>
#include <AknSkinsInternalCRKeys.h>
#include <AknsSkinUID.h>

#ifdef RD_MULTIPLE_DRIVE
#include <driveinfo.h>
#endif //RD_MULTIPLE_DRIVE

void CleanupDeleteArray( TAny* aArray )
    {
    static_cast<RPointerArray<CPslnSkinNameEntry>*>
        (aArray)->ResetAndDestroy();
    delete aArray;
    aArray = NULL;
    }

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CPslnSkinStore::CPslnSkinStore()
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnSkinStore::ConstructL( CPslnModel* aModel )
    {
    iModel = aModel;

    CRepository* repository = CRepository::NewLC( KCRUidPersonalisation );
    TInt value = KAknsNullPkgID.iNumber;
    iDefaultSkinPID.Set( KAknsPIDS60DefaultSkin );
    TBuf<32> buf;
    TAknsPkgID defaultSkin = KAknsNullPkgID;

    TInt err = repository->Get( KPslnDefaultSkinUID, buf );
    if ( err != KErrNone || buf.Length() == 0 )
        {
        err = repository->Get( KPslnDefaultSkinID, value );
        if( err == KErrNone )
            {
            defaultSkin.Set( TUid::Uid( value ) );
            }
        }
    else
        {
        TInt bufLength = buf.Length();
        // If its 8 characters long, its UID.
        // PIDs are 16 characters (8 ID + 8 timestamp)
        if ( bufLength == 8 )
            {
            // Let's try to set it directly as Hex.
            TLex hexLex( buf );
            TUint pid;
            err = hexLex.Val( pid, EHex );
            if (!err)
                {
                // UIDs have no timestamp.
                defaultSkin.Set( 0, pid );
                }
            }
        else
            {
            // The skin PID is set in CenRep in format <PID1><PID2> and
            // values are in hex.
            TLex lex ( buf.Left( 8 ) );
            TLex lex2 ( buf.Right( 8 ) );
            TUint pid;
            TUint timeStamp;
            err = lex.Val( pid, EHex );
            if ( !err )
                {
                err = lex2.Val( timeStamp, EHex );
                }
            if ( !err )
                {
                defaultSkin.Set( timeStamp, pid );
                }
            }
        }
    iDefaultSkinPID = defaultSkin;
    CleanupStack::PopAndDestroy( repository );
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnSkinStore* CPslnSkinStore::NewL( CPslnModel* aModel )
    {
    PSLN_TRACE_DEBUG("CPslnSkinStore::NewL");

    CPslnSkinStore* self = new( ELeave ) CPslnSkinStore;
    CleanupStack::PushL( self );
    self->ConstructL( aModel );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CPslnSkinStore::~CPslnSkinStore()
    {
    iSkinArray.ResetAndDestroy();
    }

// -----------------------------------------------------------------------------
// CPslnSkinStore::UpdateAllSkinsL
// -----------------------------------------------------------------------------
//
void CPslnSkinStore::UpdateAllSkinsL( RFs& aFsSession )
    {
    PSLN_TRACE_DEBUG("CPslnSkinStore::UpdateAllSkinsL");

    TInt i = KErrNone;

    // Mark all the existing skins
    for( ; i < iSkinArray.Count(); i++ )
        {
        CPslnSkinEntry* entry = iSkinArray[i];
        entry->SetDeleteFlag( ETrue );
        }
    UpdateAllSkinsL( EAknsSrvAll, aFsSession );

    // Remove any skins that haven't existed (they no longer exist)
    TInt skinCount = iSkinArray.Count() - 1;
    for( i = skinCount; i >= 0; i-- )
        {
        CPslnSkinEntry* entry = iSkinArray[i];
        if( entry && entry->IsDeleteFlag() )
            {
            delete entry;
            iSkinArray.Remove( i );
            }
        }

    // Then sort the array
    iSkinArray.Sort( CPslnSkinEntry::LinearOrder );

    // Finally, move default skin as first item in the array.
    i = KErrNotFound;
    skinCount = iSkinArray.Count() - 1;
    CPslnSkinEntry* entry = NULL;
    for( i = skinCount; i >= 0; i-- )
        {
        entry = iSkinArray[i];
        // move default theme first, if it is not already there.
        if ( ( entry->PkgID() == iDefaultSkinPID ) && ( i != 0 ) )
            {
            // Default skin found.
            iSkinArray.Remove( i );
            iSkinArray.Insert( entry, 0 );
            entry = NULL; // this is not owned by us.
            break;
            }
        }
    }

// -----------------------------------------------------------------------------
// CPslnSkinStore::Find
// -----------------------------------------------------------------------------
//
CPslnSkinEntry* CPslnSkinStore::Find( const TAknsPkgID& aPID, 
    TAknSkinSrvSkinPackageLocation aLocation )
    {
    PSLN_TRACE_DEBUG("CPslnSkinStore::Find");
    TBool allLocations = ( aLocation == EAknsSrvAll );
    CPslnSkinEntry* entry = NULL;

    for( TInt i = 0; i < iSkinArray.Count(); i++ )
        {
        entry = iSkinArray[i];

        // If PID matches AND
        // location mathes (or is looking from all locations).
        if( ( entry && entry->PkgID() == aPID ) &&
              ( ( allLocations ) ||
              ( entry->Location() == aLocation ) ) )
            {
            // this entry is the one we are looking for.
            break;
            }
        else
            {
            entry = NULL;
            }
        }

    return entry;
    }

// -----------------------------------------------------------------------------
// CPslnSkinStore::UpdateOrAddL
// -----------------------------------------------------------------------------
//
CPslnSkinEntry* CPslnSkinStore::UpdateOrAddL( 
    CAknsSrvSkinInformationPkg* aInfo, RFs& aFsSession )
    {
    PSLN_TRACE_DEBUG("CPslnSkinStore::UpdateOrAddL");

    if( !aInfo )
        {
        User::Leave( KErrArgument );
        }
    CleanupStack::PushL( aInfo );

    CPslnSkinEntry* entry = Find( aInfo->PID(),
        CPslnSkinEntry::LocationFromPath( aInfo->IniFileDirectory() ) );

#ifdef RD_MULTIPLE_DRIVE
    TInt drive = EDriveC;
    TUint driveStatus = 0;
    TFileName fileName;
#endif // RD_MULTIPLE_DRIVE

    if( entry )
        {
#ifdef RD_MULTIPLE_DRIVE
        entry->GetSkinPath( fileName );
        User::LeaveIfError( RFs::CharToDrive( fileName[0], drive ) );
        User::LeaveIfError( DriveInfo::GetDriveStatus( 
            aFsSession, drive, driveStatus ) );
        if ( driveStatus & DriveInfo::EDriveExternallyMountable &&
             driveStatus & DriveInfo::EDriveRemovable )
            {
            entry->SetMemoryCardFlag( ETrue );
            }
        else if ( driveStatus & DriveInfo::EDriveExternallyMountable )
            {
            entry->SetMassDriveFlag( ETrue );
            }
#endif // RD_MULTIPLE_DRIVE

        entry->SetProtection( aInfo->ProtectionType() );
        CleanupStack::PopAndDestroy( aInfo );
        }
    else
        {
        // Ownership of aInfo is transferred to CPslnSkinEntry.
        entry = CPslnSkinEntry::NewL( aInfo );
        CleanupStack::Pop( aInfo );
        CleanupStack::PushL( entry );

#ifdef RD_MULTIPLE_DRIVE
        entry->GetSkinPath( fileName );
        User::LeaveIfError( RFs::CharToDrive( fileName[0], drive ) );
        User::LeaveIfError( DriveInfo::GetDriveStatus( 
            aFsSession, drive, driveStatus ) );
        if ( driveStatus & DriveInfo::EDriveExternallyMountable &&
             driveStatus & DriveInfo::EDriveRemovable )
            {
            entry->SetMemoryCardFlag( ETrue );
            }
        else if ( driveStatus & DriveInfo::EDriveExternallyMountable )
            {
            entry->SetMassDriveFlag( ETrue );
            }
#endif // RD_MULTIPLE_DRIVE

        // Using Append instead of InsertInOrderAllowRepeats, since localized
        // names are not fetched yet for all the items.
        User::LeaveIfError( iSkinArray.Append( entry ) );
        CleanupStack::Pop( entry );
        }

    return entry;
    }

// -----------------------------------------------------------------------------
// CPslnSkinStore::CreateNameArray
// -----------------------------------------------------------------------------
//
RPointerArray<CPslnSkinNameEntry>* CPslnSkinStore::CreateNameArrayL()
    {
    PSLN_TRACE_DEBUG("CPslnSkinStore::CreateNameArray");
    RPointerArray<CPslnSkinNameEntry>* array =
        new RPointerArray<CPslnSkinNameEntry>();

    CleanupStack::PushL( TCleanupItem( CleanupDeleteArray, array ) );

    for( TInt i = 0; i < iSkinArray.Count(); i++ )
        {
        AppendEntryL( *array, i );
        }
    CleanupStack::Pop(); // TCleanupItem

    return array;
    }

// -----------------------------------------------------------------------------
// CPslnSkinStore::UpdateAllSkinsL
// -----------------------------------------------------------------------------
//    
void CPslnSkinStore::UpdateAllSkinsL(
    TAknSkinSrvSkinPackageLocation aLocation, RFs& aFsSession )
    {
    PSLN_TRACE_DEBUG("CPslnSkinStore::UpdateAllSkinsL");
    CArrayPtr<CAknsSrvSkinInformationPkg>* srvArray =
        iModel->SkinSrvSession().EnumerateSkinPackagesL( aLocation );

    while( srvArray && srvArray->Count() )
        {
        CAknsSrvSkinInformationPkg* info = srvArray->At( 0 );
        TRAP_IGNORE( UpdateOrAddL( info, aFsSession )->SetDeleteFlag( EFalse ) );
        srvArray->Delete( 0 );
        }

    if ( srvArray )
        {
        srvArray->ResetAndDestroy();
        }
    delete srvArray;
    }

// -----------------------------------------------------------------------------
// Appends entry to array.
// -----------------------------------------------------------------------------
// 
void CPslnSkinStore::AppendEntryL(
    RPointerArray<CPslnSkinNameEntry>& aArray, const TInt aIndex )
    {
    PSLN_TRACE_DEBUG("CPslnSkinStore::AppendEntryL");
    // Get entry.
    CPslnSkinEntry* entry = iSkinArray[aIndex];

    // Get name entry.
    CPslnSkinNameEntry* nameEntry = NULL;
    nameEntry = CPslnSkinNameEntry::NewL();
    nameEntry->SetPkgID( entry->PkgID() );
    nameEntry->SetLocation( entry->Location() );
    PSLN_TRACE_DEBUG("CPslnSkinStore::AppendEntryL.2");

    // Get name for the entry.
    HBufC* skinName = HBufC::NewLC( KMaxName );
    TPtr skinNamePtr = skinName->Des();
    entry->GetName( skinNamePtr );
    nameEntry->SetNameL( skinNamePtr );
    CleanupStack::PopAndDestroy( skinName );

    if( aArray.Append( nameEntry ) )
        {
        User::Leave( KErrGeneral );
        }
    }

//  End of File  
