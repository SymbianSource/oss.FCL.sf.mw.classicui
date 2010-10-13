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
* Description: Marking mode handler.
*
*/

#ifndef C_AKNMARKINGMODE_H
#define C_AKNMARKINGMODE_H

#include <e32base.h>

class CAknNavigationDecorator;
class CAknItemActionMenu;
class MAknCollection;
class MAknMarkingCollection;

typedef RPointerArray<MAknCollection> CollectionArray;

/**
 * Marking mode handler.
 *
 * @lib eikcoctl
 * @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknMarkingMode ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknMarkingMode* NewL(
            CAknItemActionMenu& aItemActionMenu,
            CollectionArray& aArray );

    /**
     * Destructor.
     */
    virtual ~CAknMarkingMode();

    /**
     * Sets visible collection multiple marking state.
     *
     * @internal
     * @param aActive ETrue if multiple marking should be active.
     */
    void SetCollectionMultipleMarkingState( TBool aActive );
    
    /**
     * Ends marking mode if collection allows it
     */
    void TryExitMarkingMode();

    /**
     * Returns ETrue if multiple marking state is active.
     *
     * @internal
     * @return ETrue if multiple marking is active.
     */
    TBool MultipleMarkingActive() const;

    /**
     * Returns ETrue if there are marked items in visible list that is
     * in multiple marking state.
     *
     * @internal
     * @return ETrue if items are currently marked.
     */
    TBool MarkedItems() const;
    
    /**
     * Returns ETrue if the collection has no items
     * 
     * @internal
     * @return ETrue if there are no items
     */
    TBool CollectionEmpty() const;
            
    /**
     * Marks all items in the collection.
     */
    void MarkAllL();
    
    /**
     * Unmarks all items in the collection.
     */
    void UnmarkAll();
    
    /**
     * Marks the currently selected item in the collection.
     */
    void MarkCurrentItemL();
    
    /**
     * Returns ETrue if current item can be marked
     * 
     * @internal
     * @return ETrue if current item can be marked
     */
    TBool CurrentItemMarkable();

private:

    /**
     * C++ constructor.
     */
    CAknMarkingMode(
            CAknItemActionMenu& aItemActionMenu,
            CollectionArray& aArray );

    /**
     * Returns marking collection received from aCollection.
     * 
     * @param aCollection Collection.
     * @return Marking collection object.
     */
    static MAknMarkingCollection* MarkingCollection(
            MAknCollection& aCollection );

    /**
     * Returns marking collection.
     * 
     * @return Marking collection object.
     */
    MAknMarkingCollection* MarkingCollection();
    
    /**
     * Returns the activated marking collection i.e the one with marking mode
     * turned on.
     * 
     * @return Active marking collection.
     */
    MAknMarkingCollection* ActiveMarkingCollection();

    /**
     * Updates navi pane when entering and exiting marking mode
     * 
     * @param  aEnable @c ETrue to set marking mode related text
     *                 @c EFalse to remove marking mode related text
     */
    void UpdateMarkingModeNaviPaneL( TBool aEnable );
    
private: // data

    /**
     * Collection array owned by CAknItemActionMenu.
     * Not own.
     */
    CollectionArray& iCollections;

    /**
     * Item action menu that owns this marking mode handler.
     * Not own.
     */
    CAknItemActionMenu& iItemActionMenu;
    
    /**
     * Marking mode navi pane decorator
     */
    CAknNavigationDecorator* iMarkingDecorator;     
    };

#endif // C_AKNMARKINGMODE_H
