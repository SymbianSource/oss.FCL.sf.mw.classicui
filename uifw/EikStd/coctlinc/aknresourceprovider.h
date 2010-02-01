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



#ifndef C_AKNRESOURCEPROVIDER_H
#define C_AKNRESOURCEPROVIDER_H


#include <e32def.h>
#include <e32base.h>

class MAknResourceItem;


/**
*  The resource provider class.
*
*  CAknResourceProvider stores and distributes MAknResourceItem type
*  resource items.
*
*  @lib eikcoctl
*  @since S60 v5.0
*/
NONSHARABLE_CLASS( CAknResourceProvider ) : public CBase
    {

public:

    /**
     * NewL.
     * Two-phased constructor.
     * @return a pointer to the created instance of CAknResourceProvider.
     */
    static CAknResourceProvider* NewL();

    /**
     * ~CAknResourceProvider
     * Virtual Destructor.
     */
    virtual ~CAknResourceProvider();

    /**
     * Returns a resource item duplicate by the resource item id.
     * @param aId Resource item id
     * @param aResource Resource item duplicate
     * @return Resource item id, KErrNotFound if the item was not
     * found by the specified id.
     */
    TInt GetResourceL( TUint aId, MAknResourceItem*& aResource );

    /**
     * Handles resource changes, for example layout and skin changes 
     * @param aType the type of resource change
     */
    void HandleResourceChange( TInt aType );

    /**
     * Adds the given resource item to the resource array. If there
     * exists a resource item with the same id in the array, it is 
     * first removed.
     * @param aId Resource item id
     * @param aResource Resource item to be added
     */
    void SetResourceL( TUint aId, const MAknResourceItem* aResource );

private:

    /**
     * CAknResourceProvider.
     * C++ default constructor.
     */
    CAknResourceProvider();

    /**
     * Deletes a resource item in the resource array by the specified
     * index.
     * @param aIndex Resource item index
     */
    void DeleteResourceByIndex( TUint aIndex );

private: // data

    /**
     * Resource array.
     */
    RPointerArray<MAknResourceItem> iResourceArray;

    };


#endif // C_AKNRESOURCEPROVIDER_H
