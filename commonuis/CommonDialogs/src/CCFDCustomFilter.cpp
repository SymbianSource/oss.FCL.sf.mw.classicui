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


// INCLUDE FILES
#include "CCFDCustomFilter.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CCFDCustomFilter::CCFDCustomFilter
//
//
// -----------------------------------------------------------------------------
//
CCFDCustomFilter::CCFDCustomFilter( MAknFileFilter* aFilter )
	:	iFilter( aFilter )
    {
    }

// Destructor
CCFDCustomFilter::~CCFDCustomFilter()
    {
    }


// -----------------------------------------------------------------------------
// CCFDCustomFilter::Accept
//
//
// -----------------------------------------------------------------------------
//
TBool CCFDCustomFilter::Accept( const TDesC& aDriveAndPath, const TEntry& aEntry ) const
	{
	return iFilter->Accept( aDriveAndPath, aEntry );
	}

//  End of File  
