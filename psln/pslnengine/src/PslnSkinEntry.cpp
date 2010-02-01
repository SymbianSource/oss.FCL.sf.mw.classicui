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
* Description:  One skin entry in skin store.
*
*/


#include <AknsSkinUID.h>

#include "PslnConst.h"
#include "PslnSkinEntry.h"
#include "PslnDebug.h"

// ============================ MEMBER FUNCTIONS =============================
// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnSkinEntry* CPslnSkinEntry::NewL( CAknsSrvSkinInformationPkg* aInfo )
    {
    CleanupStack::PushL( aInfo );

    CPslnSkinEntry* self = new( ELeave ) CPslnSkinEntry;

    self->iInfo = aInfo;
    self->iProtection = aInfo->ProtectionType();
    CleanupStack::Pop( aInfo );
    
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CPslnSkinEntry::~CPslnSkinEntry()
    {
    delete iInfo;
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::GetSkinPath
// -----------------------------------------------------------------------------
//
EXPORT_C void CPslnSkinEntry::GetSkinPath( TDes& aDst ) const
    {
    CopyHonoringSize( aDst, iInfo->Directory() );
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::IsCorrupted
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnSkinEntry::IsCorrupted() const
    {
    return iInfo->IsCorrupted();
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::IsSupportAnimBg
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnSkinEntry::IsSupportAnimBg() const
    {
    return iInfo->IsSupportAnimBg();
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::Protection
// -----------------------------------------------------------------------------
//
EXPORT_C TAknsSkinSrvSkinProtectionType CPslnSkinEntry::Protection() const
    {
    return iProtection;
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::FullName
// -----------------------------------------------------------------------------
//
EXPORT_C TDesC& CPslnSkinEntry::FullName() const
    {
    return iInfo->FullName();
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::IsOnMassDrive
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnSkinEntry::IsOnMassDrive() const
    {
    return iInternalState.IsSet( EPslnSkinEntryStateMassDrive );
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::IsOnMemoryCard
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CPslnSkinEntry::IsOnMemoryCard() const
    {
    return iInternalState.IsSet( EPslnSkinEntryStateMemoryCard );
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::GetIniPath
// -----------------------------------------------------------------------------
//
void CPslnSkinEntry::GetIniPath( TDes& aDst ) const
    {
    CopyHonoringSize( aDst, iInfo->IniFileDirectory() );
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::SetProtection
// -----------------------------------------------------------------------------
//
void CPslnSkinEntry::SetProtection(
    const TAknsSkinSrvSkinProtectionType aProtection )
    {
    iProtection = aProtection;
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::SetDeleteFlag
// -----------------------------------------------------------------------------
//
void CPslnSkinEntry::SetDeleteFlag( const TBool& aValue )
    {
    if ( aValue && iInternalState.IsClear( EPslnSkinEntryStateDeleted ) )
        {
        iInternalState.Set( EPslnSkinEntryStateDeleted );
        }
    else if ( !aValue && iInternalState.IsSet( EPslnSkinEntryStateDeleted ) )
        {
        iInternalState.Clear( EPslnSkinEntryStateDeleted );
        }
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::IsDeleteFlag
// -----------------------------------------------------------------------------
//
TBool CPslnSkinEntry::IsDeleteFlag() const
    {
    return iInternalState.IsSet( EPslnSkinEntryStateDeleted );
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::LinearOrder
// -----------------------------------------------------------------------------
//
TInt CPslnSkinEntry::LinearOrder( 
    const CPslnSkinEntry& aFirst, 
    const CPslnSkinEntry& aSecond )
    {
    return CPslnSkinNameEntry::LinearOrder( aFirst, aSecond );
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::SetMemoryCardFlag
// -----------------------------------------------------------------------------
//
void CPslnSkinEntry::SetMemoryCardFlag( const TBool& aValue )
    {
    if ( aValue && iInternalState.IsClear( EPslnSkinEntryStateMemoryCard ) )
        {
        iInternalState.Set( EPslnSkinEntryStateMemoryCard );
        }
    else if ( !aValue && iInternalState.IsSet( EPslnSkinEntryStateMemoryCard ) )
        {
        iInternalState.Clear( EPslnSkinEntryStateMemoryCard );
        }
    }

// -----------------------------------------------------------------------------
// CPslnSkinEntry::SetMassDriveFlag
// -----------------------------------------------------------------------------
//
void CPslnSkinEntry::SetMassDriveFlag( const TBool& aValue )
    {
    if ( aValue && iInternalState.IsClear( EPslnSkinEntryStateMassDrive ) )
        {
        iInternalState.Set( EPslnSkinEntryStateMassDrive );
        }
    else if ( !aValue && iInternalState.IsSet( EPslnSkinEntryStateMassDrive ) )
        {
        iInternalState.Clear( EPslnSkinEntryStateMassDrive );
        }
    }

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnSkinEntry::CPslnSkinEntry()
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnSkinEntry::ConstructL()
    {
    BaseConstructL( iInfo );
    }

//  End of File  
