/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Class defining a specific skin within Psln.
*
*/


#include <AknsSkinUID.h>

#include "PslnSkinNameEntry.h"
#include "PslnConst.h"
#include "PslnDebug.h"

#ifdef RD_MULTIPLE_DRIVE
#include <driveinfo.h>
#endif //RD_MULTIPLE_DRIVE

// Compares Unicode values based on the value itself AND character identity
// AND accent AND case.
const TInt KPslnCollationLvl3 = 3;

// ======== MEMBER FUNCTIONS ========

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnSkinNameEntry* CPslnSkinNameEntry::NewL()
    {
    CPslnSkinNameEntry* self = new( ELeave ) CPslnSkinNameEntry;    
    CleanupStack::PushL( self );
    self->BaseConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CPslnSkinNameEntry::~CPslnSkinNameEntry()
    {
    delete iName;
    }

// -----------------------------------------------------------------------------
// CPslnSkinNameEntry::GetName
// -----------------------------------------------------------------------------
//
void CPslnSkinNameEntry::GetName( TDes& aDst ) const
    {
    CopyHonoringSize( aDst, iName );
    }

// -----------------------------------------------------------------------------
// CPslnSkinNameEntry::SetNameL
// -----------------------------------------------------------------------------
//
void CPslnSkinNameEntry::SetNameL( const TDesC& aName )
    {
    HBufC* name = aName.AllocL();
    delete iName;
    iName = name;
    name = NULL;
    }

// -----------------------------------------------------------------------------
// CPslnSkinNameEntry::Location
// -----------------------------------------------------------------------------
//
TAknSkinSrvSkinPackageLocation CPslnSkinNameEntry::Location() const
    {
    return iLocation;
    }

// -----------------------------------------------------------------------------
// CPslnSkinNameEntry::SetLocation
// -----------------------------------------------------------------------------
//
void CPslnSkinNameEntry::SetLocation( 
    const TAknSkinSrvSkinPackageLocation aLocation )
    {
    iLocation = aLocation;
    }

// -----------------------------------------------------------------------------
// CPslnSkinNameEntry::PkgID
// -----------------------------------------------------------------------------
//
TAknsPkgID CPslnSkinNameEntry::PkgID() const
    {
    return iPID;
    }

// -----------------------------------------------------------------------------
// CPslnSkinNameEntry::SetPkgID
// -----------------------------------------------------------------------------
//
void CPslnSkinNameEntry::SetPkgID( const TAknsPkgID& aPID )
    {
    iPID = aPID;
    }

// -----------------------------------------------------------------------------
// CPslnSkinNameEntry::LinearOrder
// -----------------------------------------------------------------------------
//
TInt CPslnSkinNameEntry::LinearOrder( 
    const CPslnSkinNameEntry& aFirst, 
    const CPslnSkinNameEntry& aSecond )
    {
    // Default system skin is always less than anything else
    if( aFirst.iPID != aSecond.iPID )
        {
        if( aFirst.iPID == KAknsPIDProductDefaultSkin )
            {
            return -1;
            }
        if( aSecond.iPID == KAknsPIDProductDefaultSkin )
            {
            return 1;
            }
        }

    // If there are empty names, they are less than something else
    if( !aFirst.iName && aSecond.iName )
        {
        return -1;
        }
    if( aFirst.iName && !aSecond.iName )
        {
        return 1;
        }
    if( !aFirst.iName && !aSecond.iName )
        {
        return 0;
        }

    // Otherwise, compare names (they are NULL-checked at this point)
    PSLN_TRACE_DEBUG2("CPslnSkinNameEntry: Comparing \"%S\" and \"%S\"", 
        aFirst.iName, aSecond.iName );
    return aFirst.iName->CompareC( *aSecond.iName, KPslnCollationLvl3, NULL );
    }

// -----------------------------------------------------------------------------
// CPslnSkinNameEntry::LocationFromPath
// -----------------------------------------------------------------------------
//
TAknSkinSrvSkinPackageLocation CPslnSkinNameEntry::LocationFromPath( 
    const TDesC& aPath )
    {
#ifndef RD_MULTIPLE_DRIVE
    TBuf<1> driveLetterBuf;
    driveLetterBuf.CopyUC( aPath.Left(1) );
    if( driveLetterBuf.Compare( KPslnMMCDriveLetter ) == 0 )
        {
        return EAknsSrvMMC;
        }
    return EAknsSrvPhone;
#else
    RFs fs;
    if ( KErrNone != fs.Connect() )
        {
        // not sure the default value if failed
        return EAknsSrvPhone;
        }

    TInt drive = EDriveC;
    TUint driveStatus = 0;
    TAknSkinSrvSkinPackageLocation skinLoc = EAknsSrvPhone;
    TInt err = RFs::CharToDrive( aPath[0], drive );
    err = DriveInfo::GetDriveStatus( fs, drive, driveStatus );
    if ( driveStatus & DriveInfo::EDriveExternallyMountable )
        {
        skinLoc = EAknsSrvMMC;
        }

    fs.Close();
    return skinLoc;
#endif // RD_MULTIPLE_DRIVE
    }

// -----------------------------------------------------------------------------
// CPslnSkinNameEntry::CopyHonoringSize
// -----------------------------------------------------------------------------
//
void CPslnSkinNameEntry::CopyHonoringSize( TDes& aDst, const TDesC* aSrc )
    {
    if( aSrc )
        {
        CopyHonoringSize( aDst, *aSrc );
        }
    else
        {
        aDst.Zero();
        }
    }

// -----------------------------------------------------------------------------
// CPslnSkinNameEntry::CopyHonoringSize
// -----------------------------------------------------------------------------
//
void CPslnSkinNameEntry::CopyHonoringSize( TDes& aDst, const TDesC& aSrc )
    {
    aDst.Copy( aSrc.Left( aDst.MaxLength() ) );
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnSkinNameEntry::BaseConstructL( CAknsSrvSkinInformationPkg* aInfo )
    {  
    if ( aInfo )
        {
        SetLocation( LocationFromPath( aInfo->IniFileDirectory() ) );
        SetPkgID( aInfo->PID() );
        SetNameL( aInfo->Name() );
        }
    }

// -----------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnSkinNameEntry::CPslnSkinNameEntry() 
    : iLocation( EAknsSrvPhone ), iPID( KAknsNullPkgID )
    {
    }

// End of File.


