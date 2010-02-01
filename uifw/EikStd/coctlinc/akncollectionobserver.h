/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Collection observer interface.
*
*/

#ifndef M_AKNCOLLECTIONOBSERVER_H
#define M_AKNCOLLECTIONOBSERVER_H

class CAknItemActionMenu;

/**
 * Collection observer.
 *
 * This interface is intended for those objects that are interested
 * of collection state and need to receive collection notifications.
 *
 * @lib eikcoctl
 * @since S60 v5.2
 */
class MAknCollectionObserver
    {
public:

    /**
     * This method is used to set the item action menu to observer.
     * 
     * @param aItemActionMenu Item action menu. 
     */
    virtual void SetItemActionMenu( CAknItemActionMenu* aItemActionMenu ) = 0;

    /**
     * This method is called when there are changes in collection state.
     * 
     * @param aCollectionVisible ETrue if changed collection is visible.
     */
    virtual void CollectionChanged( TBool aCollectionVisible ) = 0;

    /**
     * This method returns ETrue if collection observer is active.
     * 
     * @return ETrue if observer is active.
     */
    virtual TBool Active() const = 0;

    };

#endif // M_AKNCOLLECTIONOBSERVER_H
