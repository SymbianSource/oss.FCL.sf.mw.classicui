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
* Description:  Resource item interface
*
*/



#ifndef M_AKNRESOURCEITEM_H
#define M_AKNRESOURCEITEM_H


/**
*  The resource interface.
*
*  Classes that implement this interface can be stored and distributed 
*  by CAknResourceProvider  class.
*
*  @lib eikcoctl
*  @since S60 v5.0
*/
class MAknResourceItem
    {

public:

    /**
     * Duplicates the item and the resources it holds
     * and returns the created resource item.
     * @return Duplication result
     */
    virtual MAknResourceItem* DuplicateL() = 0;

    /**
     * Returns the resource item id.
     * @return Resource item id.
     */
    virtual TInt Id() const = 0;

    /**
     * Returns ETrue if the aType resource change applies
     * to this resource item. Otherwise EFalse.
     * @param aType Resource change type
     * @return ETrue if resource change applies to 
     * the resource item.
     */
    virtual TBool Invalidate( TInt aType ) = 0;

    /**
     * Virtual destructor.
     */
    virtual ~MAknResourceItem(){};

    };


#endif // M_AKNRESOURCEITEM_H
