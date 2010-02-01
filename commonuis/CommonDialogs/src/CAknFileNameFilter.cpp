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


#include <barsread.h>
#include <f32file.h>

#include "CAknFileNameFilter.h"
#include "CAknCommonDialogsBase.h"
#include "CommonDialogs.hrh"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknFileNameFilter::CAknFileNameFilter
//
//
// -----------------------------------------------------------------------------
//
CAknFileNameFilter::CAknFileNameFilter()
	:	iWildCards( 2 )
	{
	}

// -----------------------------------------------------------------------------
// CAknFileNameFilter::ConstructFromResourceL
//
// -----------------------------------------------------------------------------
//
void CAknFileNameFilter::ConstructFromResourceL( TResourceReader& aReader )
	{
	// Read filter style
	iFilterStyle = aReader.ReadInt16();

	// Check that filter style is correct
	__ASSERT_DEBUG( iFilterStyle == EInclusiveFilter || iFilterStyle == EExclusiveFilter,
		User::Panic( KCFDPanicText, ECFDPanicInvalidFilterStyle ) );

	// Read the amount of wildcards
	TInt wildCardCount( aReader.ReadInt16() );

	// Check that wildcard amount is valid
	__ASSERT_DEBUG( wildCardCount >= 0,
		User::Panic( KCFDPanicText, ECFDPanicInvalidAttributeFilterDataCount ) );

	TPtrC data;
	for( TInt index( 0 ); index < wildCardCount; index++ )
		{
		// Read wildcars
		data.Set( aReader.ReadTPtrC() );

		// Check that it's length is valid
		__ASSERT_DEBUG( data.Length() >= 0,
			User::Panic( KCFDPanicText, ECFDPanicInvalidFileNameFilterDataLength ) );

		// Append wildcard to an array
		iWildCards.AppendL( data );
		}
	}

// -----------------------------------------------------------------------------
// CAknFileNameFilter::NewLC
//
// -----------------------------------------------------------------------------
//
EXPORT_C CAknFileNameFilter* CAknFileNameFilter::NewLC( TResourceReader& aReader )
	{
	CAknFileNameFilter* self = new( ELeave ) CAknFileNameFilter();
	CleanupStack::PushL( self );
	self->ConstructFromResourceL( aReader );
	return self;
	}

// Destructor
EXPORT_C CAknFileNameFilter::~CAknFileNameFilter()
	{
	}


// -----------------------------------------------------------------------------
// CAknFileNameFilter::Accept
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknFileNameFilter::Accept( const TDesC& /*aDriveAndPath*/, const TEntry& aEntry ) const
	{
	// Boolean value to state if an entry is accepted or not.
	// If style is inclusive filter, entry is not accepted by default and
	// if style is exclusive filter, entry is accepted by default
	TBool entryIsAccepted( iFilterStyle );
	TInt index( 0 );
	TInt wildCardCount( iWildCards.Count() );
	// While there are wildcards to check, do
	while( index < wildCardCount )
		{
		if( !aEntry.IsDir() )
			{
			// If the filename of the entry matches to the wildcard of the filter, accept
			// If the filter is an exclude filter, inverse the result
			entryIsAccepted =
				( ! ( aEntry.iName.MatchF( iWildCards[ index ] ) == KErrNotFound ) ) ^ iFilterStyle;
			}
		else // If an entry is a directory, accept it automatically
			{
			entryIsAccepted = ETrue;
			}
		// If state has changed (inclusive filter accepts an entry or
		// exclusive filter rejects an entry), exit
		if( entryIsAccepted != iFilterStyle )
			{
			return entryIsAccepted;
			}
		index++;
		}
	return entryIsAccepted;
	}

// End of File
