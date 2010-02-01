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


#ifndef AKNFILEFILTERFACTORY_H
#define AKNFILEFILTERFACTORY_H

// INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class TResourceReader;
class MAknFileFilter;

// CLASS DEFINITION
/**
*  A static factory class that creates filters for filtering files.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
class AknFileFilterFactory
	{
	public:		// New methods

		/**
		* A static method that creates a filter derived from
		* MAknFileFilter and leaves the pointer to it to cleanup stack.
		* @param aReader A reference to a resource reader initialized with
		*        a FILTER resource.
		* @return Returns a pointer to the created filter.
		*/
		IMPORT_C static MAknFileFilter* CreateFilterLC( TResourceReader& aReader );

	};

#endif // AKNFILEFILTERFACTORY_H

// End of File
