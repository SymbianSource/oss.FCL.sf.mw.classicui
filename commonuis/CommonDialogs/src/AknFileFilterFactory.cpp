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
#include "AknFileFilterFactory.h"

#include <barsread.h>   // TResourceReader

#include "CAknFileNameFilter.h"
#include "CAknAttributeFilter.h"
#include "CommonDialogs.hrh"
#include "CAknCommonDialogsBase.h"  // Panic codes

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// AknFileFilterFactory::CreateFilterLC
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C MAknFileFilter* AknFileFilterFactory::CreateFilterLC( TResourceReader& aReader )
	{
	// Read the type of the filter
	TInt filterType( aReader.ReadInt16() );

	// Create desired filter
	switch( filterType )
		{
		case EFilenameFilter:
			{
			return CAknFileNameFilter::NewLC( aReader );
			}
		case EAttributeFilter:
			{
			return CAknAttributeFilter::NewLC( aReader );
			}
		default:
			{
			// Filter type is invalid
			User::Panic( KCFDPanicText, ECFDPanicInvalidFilterType );
			}
		}

	// Avoid warning
	return NULL;
	}

// End of File
