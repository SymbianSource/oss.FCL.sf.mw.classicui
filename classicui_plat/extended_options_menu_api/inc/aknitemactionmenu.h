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
* Description: Item action menu.
*
*/

#ifndef C_AKNITEMACTIONMENU_H
#define C_AKNITEMACTIONMENU_H

#include <e32base.h>
#include <eikmobs.h>

class MAknCollection;
class MAknCollectionObserver;
class CAknStylusPopUpMenu;
class CEikMenuBar;
class CAknItemActionMenuData;

/**
 * Item action menu.
 * 
 * Classes implementing @c MAknCollection interface can launch
 * item specific action menu using this class. Item specific
 * commands are fetched from the current menu bar and handled like
 * any other options menu commands.
 * 
 * Collections that wish to use item action menu should register themselves
 * using static call RegisterCollectionL. This call returns pointer to item
 * action menu instance (ownership does not transfer to caller). Pointer to
 * item action menu can be used to launch the menu. When there is no need
 * for item action menu usage in collection anymore, collection should be
 * removed with method RemoveCollection.
 * 
 * Simplified example:
 * @code
 * // Initialization (NOTE: ownership does not transfer!) 
 * iItemActionMenu = CAknItemActionMenu::RegisterCollectionL( *this );
 * 
 * // Show menu
 * if ( iItemActionMenu->InitMenuL() )
 *     {
 *     iItemActionMenu->ShowMenuL( position );
 *     }
 * 
 * // Remove collection
 * iItemActionMenu->RemoveCollection( *this );
 * @endcode
 *
 * @lib eikcoctl
 * @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknItemActionMenu ) : public CBase,
                                          public MEikMenuObserver
    {

public:

    /**
     * Two-phased constructor.
     * 
     * @internal
     * @param aCollection Collection.
     */
    static CAknItemActionMenu* NewL( MAknCollection& aCollection );

    /**
     * Two-phased constructor.
     * 
     * @internal
     * @param aCollection Collection.
     */
    static CAknItemActionMenu* NewLC( MAknCollection& aCollection );

    /**
     * Destructor.
     */
    virtual ~CAknItemActionMenu();

    /**
     * Adds collection to the item action menu of this view / dialog / appUi.
     * 
     * @param aCollection Collection implementing MAknCollection interface.
     * @return Pointer to the item action menu instance.
     * Ownership does not transfer to caller.
     */
    IMPORT_C static CAknItemActionMenu* RegisterCollectionL(
            MAknCollection& aCollection );

    /**
     * Removes collection of this item action menu.
     * 
     * @param aCollection Collection to be removed.
     */
    IMPORT_C void RemoveCollection( MAknCollection& aCollection );

    /**
     * Initializes this item action menu. Menu should be initialized
     * before it can be shown with ShowMenuL.
     * 
     * @return ETrue if item action menu has content. EFalse otherwise.
     */
    IMPORT_C TBool InitMenuL();

    /**
     * Shows this item action menu.
     * 
     * @param aPosition Menu position relative to screen.
     * @param aFlags Flags - not used.
     */
    IMPORT_C void ShowMenuL(
            const TPoint& aPosition,
            TUint aFlags = 0 );

    /**
     * Notifies that collection has been changed.
     * 
     * @param aCollection Changed collection.
     */
    IMPORT_C void CollectionChanged( MAknCollection& aCollection );

    /**
     * Sets menu bar to item action menu.
     * 
     * @internal
     * @param aMenuObserver Menu bar observer.
     * @param aMenuBar Pointer to menu bar.
     */
    void SetMenuBar(
            MEikMenuObserver* aMenuObserver,
            CEikMenuBar* aMenuBar );

    /**
     * Provides collection highlight state.
     * 
     * @internal
     * @return ETrue if collection highlight is visible.
     */
    TBool CollectionHighlightVisible() const;

    /**
     * Provides collection softkey state.
     * 
     * @internal
     * @param aVisibleCollection ETrue if state should be defined according
     * to topmost visible collection, EFalse if invisible.
     * @return ETrue if collection item specific softkey should be visible.
     */
    TBool CollectionSoftkeyVisible( TBool aVisibleCollection = ETrue ) const;

    /**
     * Adds collection to this item action menu.
     *
     * @param aCollection New collection.
     */
    void AddCollectionStateL( MAknCollection& aCollection );

    /**
     * Provides reference to this item action menu data.
     *
     * @return Reference to item action menu data.
     */
    CAknItemActionMenuData& MenuData();

    /**
     * Registers collection observer.
     *
     * @internal
     * @param aObserver Collection observer.
     */
    void RegisterCollectionObserverL( MAknCollectionObserver& aObserver );

    /**
     * Removes collection observer.
     *
     * @internal
     * @param aObserver Collection observer.
     */
    void RemoveCollectionObserver( MAknCollectionObserver& aObserver );

    /**
     * Provides item action menu collection count.
     *
     * @internal
     * @return Collection count.
     */
    TInt CollectionCount() const;

private:

    /**
     * C++ constructor.
     */
    CAknItemActionMenu();

    /**
     * Symbian second-phase constructor.
     *
     * @param aCollection Collection.
     */
    void ConstructL( MAknCollection& aCollection );

    /**
     * Fills query dialog with menu data and launches it.
     * 
     * @param aHeading Dialog heading.
     * @return Selected menu data index.
     */
    TInt LaunchSubMenuQueryL( const TDesC& aHeading );

    /**
     * Notifies collection change to active observer.
     * 
     * @param aCollectionVisible ETrue if collection that changed is visible.
     */
    void NotifyChangeToActiveObserver( TBool aCollectionVisible = ETrue );

// from MEikMenuObserver
    /**
     * Called by the framework to handle the emphasising
     * or de-emphasising of a menu window.
     * 
     * @param aMenuControl The menu control.
     * @param aEmphasis ETrue to emphasize the menu, EFalse otherwise.
     */
    void SetEmphasis( CCoeControl* aMenuControl, TBool aEmphasis );

    /**
     * Processes user commands.
     * 
     * @param aCommandId ID of the command to respond to.
     */
    void ProcessCommandL( TInt aCommandId );

    /**
     * Unregisters item action menu
     */
    void UnregisterMenu(); 

private: // data

    /**
     * Menu control.
     * Own.
     */
    CAknStylusPopUpMenu* iPopupMenu;

    /**
     * Menu bar observer.
     * Not own.
     */
    MEikMenuObserver* iMenuBarObserver;

    /**
     * Menu bar.
     * Not own.
     */
    CEikMenuBar* iMenuBar;

    /**
     * Menu pane.
     * Own.
     */
    CEikMenuPane* iMenuPane;

    /**
     * Collections.
     */
    RPointerArray<MAknCollection> iStates;

    /**
     * Collection observers.
     */
    RPointerArray<MAknCollectionObserver> iObservers;

    /**
     * Boolean ensuring that item action menu is not unregistered during 
     * command processing. 
     */
    TBool iProcessingCommand;
    
    /**
     * Menu data.
     * Own.
     */
    CAknItemActionMenuData* iMenuData;
    };

#endif // C_AKNITEMACTIONMENU_H
