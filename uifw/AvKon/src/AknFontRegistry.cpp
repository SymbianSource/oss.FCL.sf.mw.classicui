/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Stores list of AknLayoutFont pointers
*
*/


// INCLUDE FILES
#include "AknFontRegistry.h"
#include <AknLayoutFont.h>

// CONSTANTS

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknFontRegistry::CAknFontRegistry
// C++ default constructor can NOT contain any code that
// might leave.
// -----------------------------------------------------------------------------
//
CAknFontRegistry::CAknFontRegistry() : 
    iArray()
    {
    }

// -----------------------------------------------------------------------------
// CAknFontRegistry::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknFontRegistry* CAknFontRegistry::NewL()
    {
    CAknFontRegistry* self = new( ELeave )CAknFontRegistry();
    return self;
    }

    
// Destructor
CAknFontRegistry::~CAknFontRegistry()
    {
    iArray.Close();
    }

// -----------------------------------------------------------------------------
// Insert in order. It is assumed that the number of calls to IsRegister will 
// justify the overhead in performing the registration
// -----------------------------------------------------------------------------
//
void CAknFontRegistry::RegisterFont( const CAknLayoutFont* aFont )
    {
    // All errors ignored.  OOM is the only one that makes senses, and it should
    // fail gracefully in the case of OOM
    (void)iArray.InsertInAddressOrder( aFont );
    }

// -----------------------------------------------------------------------------
// Remove pointer from list. 
// -----------------------------------------------------------------------------
//
void CAknFontRegistry::DeRegisterFont( const CAknLayoutFont* aFont )
    {
    TInt found = FindFont( aFont );
    if ( found != KErrNotFound )
        {
        iArray.Remove( found );
        }
    // All error conditions ignored.  Should fail quietly.
    }

// -----------------------------------------------------------------------------
// Check pointer is in the list
// -----------------------------------------------------------------------------
//
TBool CAknFontRegistry::IsRegistered( const CFont* aFont ) const
    {
    return ( FindFont( aFont ) != KErrNotFound ) ;
    }

// -----------------------------------------------------------------------------
// Private method to look for the pointer
// -----------------------------------------------------------------------------
//
TInt CAknFontRegistry::FindFont( const CFont* aFont ) const
    {
    return iArray.FindInAddressOrder( aFont ); 
    }

//  End of File  
