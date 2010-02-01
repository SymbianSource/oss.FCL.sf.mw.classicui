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


#include <barsread.h> // TResourceReader
#include <f32file.h>

#include "CAknAttributeFilter.h"
#include "CAknCommonDialogsBase.h" // Panic codes
#include "CommonDialogs.hrh"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknAttributeFilter::CAknAttributeFilter
//
//
// -----------------------------------------------------------------------------
//
CAknAttributeFilter::CAknAttributeFilter()
	:	iAttributes( KEntryAttNormal )
	{
	}

// -----------------------------------------------------------------------------
// CAknAttributeFilter::ConstructFromResourceL
//
// -----------------------------------------------------------------------------
//
void CAknAttributeFilter::ConstructFromResourceL( TResourceReader& aReader )
	{
	// Attribute data strings
	_LIT( KAttReadOnly,	"R" );
	_LIT( KAttHidden,	"H" );
	_LIT( KAttSystem,	"S" );
	_LIT( KAttVolume,	"V" );
	_LIT( KAttDir,		"D" );
	_LIT( KAttArchive,	"A" );

	// Read filter style
	iFilterStyle = aReader.ReadInt16();

	// Check that filter style is correct
	__ASSERT_DEBUG( iFilterStyle == EInclusiveFilter || iFilterStyle == EExclusiveFilter,
		User::Panic( KCFDPanicText, ECFDPanicInvalidFilterStyle ) );

	// Read the amount of data entries
	TInt dataCount( aReader.ReadInt16() );

	for( TInt index( 0 ); index < dataCount; index++ )
		{
		// Read filter attributes
		TPtrC data( aReader.ReadTPtrC() );

		// Find attributes from resource data descriptor
		if( data.FindF( KAttReadOnly )	!= KErrNotFound ) { iAttributes |= KEntryAttReadOnly; }
		if( data.FindF( KAttHidden )	!= KErrNotFound ) { iAttributes |= KEntryAttHidden; }
		if( data.FindF( KAttSystem )	!= KErrNotFound ) { iAttributes |= KEntryAttSystem; }
		if( data.FindF( KAttVolume )	!= KErrNotFound ) { iAttributes |= KEntryAttVolume; }
		if( data.FindF( KAttDir )		!= KErrNotFound ) { iAttributes |= KEntryAttDir; }
		if( data.FindF( KAttArchive )	!= KErrNotFound ) { iAttributes |= KEntryAttArchive; }
		}
	}

// -----------------------------------------------------------------------------
// CAknAttributeFilter::NewLC
//
// -----------------------------------------------------------------------------
//
EXPORT_C CAknAttributeFilter* CAknAttributeFilter::NewLC( TResourceReader& aReader )
	{
	CAknAttributeFilter* self = new( ELeave ) CAknAttributeFilter();
	CleanupStack::PushL( self );
	self->ConstructFromResourceL( aReader );
	return self;
	}

// Destructor
EXPORT_C CAknAttributeFilter::~CAknAttributeFilter()
	{
	}


// -----------------------------------------------------------------------------
// CAknAttributeFilter::Accept
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknAttributeFilter::Accept(
	const TDesC& /*aDriveAndPath*/, const TEntry& aEntry ) const
	{
	// If attributes of the entry match with the attributes of the filter then accept it.
	// Finally switch the result ( 0->1, 1->0 ) if the filter is an exclusive filter.
	return ( ( iAttributes & aEntry.iAtt ) == iAttributes ) ^ iFilterStyle;
	}

// End of File
