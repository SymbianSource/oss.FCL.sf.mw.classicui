/*
* Copyright (c) 2008-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Resource provider
*
*/


#include "aknresourceprovider.h"
#include "aknresourceitem.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknResourceProvider* CAknResourceProvider::NewL()
    {
    CAknResourceProvider* self = new ( ELeave ) CAknResourceProvider;
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknResourceProvider::~CAknResourceProvider()
    {
    iResourceArray.ResetAndDestroy();
    }


// ----------------------------------------------------------------------------
// Returns a resource item duplicate by the resource item id.
// ----------------------------------------------------------------------------
//
TInt CAknResourceProvider::GetResourceL( TUint aId,
                                        MAknResourceItem*& aResource )
    {
    for ( int i = 0; i < iResourceArray.Count(); i++ )
        {
        if ( iResourceArray[i]->Id() == aId )
            {
            aResource = iResourceArray[i]->DuplicateL();
            return aId;
            }
        }
    return KErrNotFound;
    }


// ---------------------------------------------------------------------------
// Handles resource changes, for example layout and skin changes.
// ---------------------------------------------------------------------------
//
void CAknResourceProvider::HandleResourceChange( TInt aType )
    {
    for ( int i = 0; i < iResourceArray.Count(); i++ )
        {
        if ( iResourceArray[i]->Invalidate( aType ) )
            {
            DeleteResourceByIndex( i );
            }
        }
    }


// ---------------------------------------------------------------------------
// Adds the given resource item to the resource array. If there
// exists a resource item with the same id in the array, it is first removed.
// ---------------------------------------------------------------------------
//
void CAknResourceProvider::SetResourceL( TUint aId, 
                                        const MAknResourceItem* aResource )
    {
    for ( int i = 0; i < iResourceArray.Count(); i++ )
        {
        if ( iResourceArray[i]->Id() == aId )
            {
            DeleteResourceByIndex( i );
            }
        }
    iResourceArray.AppendL( aResource );
    }


// ---------------------------------------------------------------------------
// C++ default constructor can NOT contain any code that might leave.
// ---------------------------------------------------------------------------
//
CAknResourceProvider::CAknResourceProvider()
    {
    // No implementation required
    }


// ---------------------------------------------------------------------------
// Deletes a resource item in the resource array by the specified index.
// ---------------------------------------------------------------------------
//
void CAknResourceProvider::DeleteResourceByIndex( TUint aIndex )
    {
    if ( aIndex < iResourceArray.Count() )
        {
        MAknResourceItem* removeItem = iResourceArray[aIndex];
        iResourceArray.Remove( aIndex );
        delete removeItem;
        }
    }
