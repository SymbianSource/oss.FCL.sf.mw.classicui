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
* Description:  Filter for file selection.
*
*/


#ifndef CAKNFILENAMEFILTER_H
#define CAKNFILENAMEFILTER_H

// INCLUDES
#include <badesca.h> // CDesCArrayFlat
#include <MAknFileFilter.h>

// FORWARD DECLARATIONS
class TResourceReader;

//  CLASS DEFINITION
/**
*  A filter class that checks if the filename of a file matches
*  with the wildcards of the filter.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
NONSHARABLE_CLASS(CAknFileNameFilter) : public CBase, public MAknFileFilter
	{
	public:		// Constructors and destructors

		/**
		* Static constructor, leaves a pointer to itself to the cleanup stack.
		* @param aReader A reference to a resource reader.
		*/
		IMPORT_C static CAknFileNameFilter* NewLC( TResourceReader& aReader );

		IMPORT_C ~CAknFileNameFilter();

	public:		// Functions from base classes

		/**
		* From MAknFileFilter
		*/
		IMPORT_C TBool Accept( const TDesC& aDriveAndPath, const TEntry& aEntry ) const;

	private:	// Constructors and destructors

		CAknFileNameFilter();

		/**
		* Second phase of construction. Constructs itself from a resource.
		* @param aReader A reference to a resource reader.
		*/
		void ConstructFromResourceL( TResourceReader& aReader );

	private:	// Data

		// Own: Wildcards of the filter.
		CDesCArrayFlat iWildCards;

		// Own: Defines if the filter is an include or an exclude filter.
		TInt iFilterStyle;
	};

#endif // CAKNFILENAMEFILTER_H

// End of File
