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
* Description:  Attribute filter for File Selection Dialog
*
*/


#ifndef CAKNATTRIBUTEFILTER_H
#define CAKNATTRIBUTEFILTER_H

// INCLUDES
#include <e32base.h>
#include <MAknFileFilter.h>

// FORWARD DECLARATIONS
class TEntry;
class TResourceReader;

// CLASS DEFINITION
/**
*  A filter class that checks if attributes of a file match
*  with filter's ones.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
NONSHARABLE_CLASS(CAknAttributeFilter) : public CBase, public MAknFileFilter
	{
	public:		// Constructors and destructors

		/**
		* Static constructor, leaves a pointer to itself to the cleanup stack.
		* @param aReader A reference to a resource reader.
		*/
		IMPORT_C static CAknAttributeFilter* NewLC( TResourceReader& aReader );

		IMPORT_C ~CAknAttributeFilter();

	public:		// Functions from base classes

        /**
        * From MAknFileFilter
        */
		IMPORT_C TBool Accept( const TDesC& aDriveAndPath, const TEntry& aEntry ) const;

	private:	// Constructors and destructors

		CAknAttributeFilter();

		/**
		* Second phase of construction. Constructs itself from a resource.
		* @param aReader A reference to a resource reader.
		*/
		void ConstructFromResourceL( TResourceReader& aReader );

	private:	// Data

		// Own: Filter attributes. Constants are defined in F32FILE.H.
		TUint iAttributes;

		// Own: Defines whether the filter is an include or an exclude filter.
		TInt iFilterStyle;
	};

#endif // CAKNATTRIBUTEFILTER_H

// End of File
