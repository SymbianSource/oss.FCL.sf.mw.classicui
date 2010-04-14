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
* Description: Item action menu register.
*
*/

#ifndef C_AKNITEMACTIONMENUREGISTER_H
#define C_AKNITEMACTIONMENUREGISTER_H

#include <coemain.h>

class MAknCollection;
class MAknCollectionObserver;
class CAknItemActionMenuRegisterArray;
class CAknItemActionMenu;
class MObjectProvider;
class CAknView;

/**
 * Item action menu register.
 *
 * @lib eikcoctl
 * @since S60 v5.2
 */
NONSHARABLE_CLASS( AknItemActionMenuRegister ) : public CCoeStatic
    {

public:

    /**
     * Sets constructing menu bar owner. This method should be called
     * from constructing components that have menu bar (e.g. CAknView,
     * CAknDialog). This way the item action menu can be linked
     * to correct menu bar.
     * 
     * @internal
     * @param aMenuBarOwner Pointer to constructing menu bar owner.
     */
    IMPORT_C static void SetConstructingMenuBarOwnerL(
            MObjectProvider* aMenuBarOwner );

    /**
     * Sets a menu bar owner that overrides all other possible menubar
     * providers. This menu bar owner is meant to be temporary and should be
     * set by components that:
     *  -May contain a listbox.
     *  -Have their own menubar.
     * 
     * When such a component is destroyed it must call this method again with
     * NULL paramater to unregister the overriding menu bar owner.
     *
     * @internal
     * @param aMenuBarOwner Pointer to overriding menu bar owner.
     * @param aFlags        Flags, not currently used.
     */
    IMPORT_C static void SetOverridingMenuBarOwnerL(
            MObjectProvider* aMenuBarOwner, TUint aFlags = 0 );

    /**
     * Sets the current constructing menubar owner to NULL if it matches to
     * aMenuBarOwner. Otherwise constructing menubar owner is not modified.
     * 
     * @internal
     * @param aMenuBarOwner Pointer to constructing menubar owner. 
     */
    IMPORT_C static void RemoveConstructingMenuBarOwner( 
            MObjectProvider* aMenuBarOwner );
    
    /**
     * Registers a collection.
     * 
     * @internal
     * @param aCollection Collection to be registered.
     * @param aMenuBarOwner Owner of the menubar that collection will be
     *        registered with.
     * @return Item action menu the collection was registered to.
     */
    static CAknItemActionMenu* RegisterCollectionL(
            MAknCollection& aCollection, MObjectProvider* aMenuBarOwner );

    /**
     * Registers item action menu to aMenuBar.
     * 
     * @internal
     * @param aMenuBar Calling menu bar.
     */
    static void RegisterMenuBarL( CEikMenuBar& aMenuBar );

    /**
     * Unregisters menu bar.
     * 
     * @internal
     * @param aMenuBar Calling menu bar.
     */
    static void UnregisterMenuBar( CEikMenuBar& aMenuBar );

    /**
     * Registers aItemActionMenu to menu bar.
     * 
     * @internal
     * @param aItemActionMenu Calling item action menu.
     */
    static void RegisterItemActionMenuL( CAknItemActionMenu& aItemActionMenu );

    /**
     * Unregisters item action menu.
     * 
     * @internal
     * @param aItemActionMenu Calling item action menu.
     */
    static void UnregisterItemActionMenu(
            CAknItemActionMenu& aItemActionMenu );

    /**
     * Registers collection observer.
     * 
     * @internal
     * @param aObserver Collection observer.
     */
    static void RegisterCollectionObserverL(
            MAknCollectionObserver& aObserver );

    /**
     * Unregisters collection observer.
     * 
     * @internal
     * @param aObserver Collection observer.
     */
    static void UnregisterCollectionObserver(
            MAknCollectionObserver& aObserver );

    /**
     * Destructor.
     */
    virtual ~AknItemActionMenuRegister();

private:

    /**
     * C++ constructor.
     */
    AknItemActionMenuRegister();

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Returns ETrue if application is single click compatible.
     * 
     * @return ETrue if application is single click compatible.
     */
    static TBool AppUiSingleClickCompatible();

    /**
     * Provides register instance.
     * 
     * @return Item action menu register instance.
     */
    static AknItemActionMenuRegister* Instance();

    /**
     * Registers collection.
     * 
     * @param aCollection State to be registered.
     * @param aMenuBarOwner Owner of the menubar that collection will be
     *        registered with.
     * @return Item action menu the collection was registered to.
     */
    CAknItemActionMenu* DoRegisterCollectionL(
            MAknCollection& aCollection, MObjectProvider* aMenuBarOwner );

    /**
     * Registers item action menu to aMenuBar.
     * 
     * @param aMenuBar Calling menu bar.
     */
    void DoRegisterMenuBarL( CEikMenuBar& aMenuBar );

    /**
     * Unregisters menu bar.
     * 
     * @param aMenuBar Calling menu bar.
     */
    void DoUnregisterMenuBar( CEikMenuBar& aMenuBar );

    /**
     * Registers aItemActionMenu to menu bar.
     * 
     * @param aItemActionMenu Calling item action menu.
     */
    void DoRegisterItemActionMenuL( CAknItemActionMenu& aItemActionMenu );

    /**
     * Unregisters item action menu.
     * 
     * @param aItemActionMenu Calling item action menu.
     */
    void DoUnregisterItemActionMenu( CAknItemActionMenu& aItemActionMenu );

    /**
     * Registers collection observer.
     * 
     * @param aObserver Collection observer.
     */
    void DoRegisterCollectionObserverL(
            MAknCollectionObserver& aObserver );

    /**
     * Unregisters collection observer.
     * 
     * @param aObserver Collection observer.
     */
    void DoUnregisterCollectionObserver( MAknCollectionObserver& aObserver );

    /**
     * Returns the pointer to visible dialog menu bar.
     * 
     * @param aAppUi AppUi.
     * @return Visible dialog menu bar.
     */
    CEikMenuBar* DialogMenuBar( CAknAppUi* aAppUi );

    /**
     * Returns the pointer to active view menu bar.
     * 
     * @param aAppUi AppUi.
     * @return Active view menu bar.
     */
    CEikMenuBar* ViewMenuBar( CAknAppUi* aAppUi );

    /**
     * Returns the pointer to constructing object menu bar.
     * 
     * @return Constructing object menu bar.
     */
    CEikMenuBar* ConstructingObjectMenuBar();

    /**
     * Returns the pointer to overriding object menu bar.
     * 
     * @return Overriding object menu bar.
     */
    CEikMenuBar* OverridingObjectMenuBar();
    
    /**
     * Returns pointer to component that owns the current view. This is either
     * application UI, active view or a dialog. This component is the one that
     * owns the possible menubar.
     * 
     * @return Current view owner.
     */
    MObjectProvider* Owner() const;
    
    /**
     * Returns pointer to currently active view.
     * 
     * @param aAppUi Application UI.
     * @return Active view or NULL.
     */
    CAknView* View( CAknAppUi* aAppUi ) const;
    
    /**
     * Returns pointer to current application UI.
     * 
     * @return Application UI or NULL.
     */
    static CAknAppUi* AppUI();
    

    /**
     * Registers collection to item action menu.
     * Creates and sets item action menu to menu bar
     * if one is not found. If menu bar is not found, item action menu
     * is stored to iUnregisteredMenus for later usage.
     * 
     * @param aMenuBar Menu bar
     * @param aCollection Collection to be registered.
     * @return Pointer to item action menu collection was registered to.
     */
    CAknItemActionMenu* RegisterStateToItemActionMenuL(
            CEikMenuBar* aMenuBar,
            MAknCollection& aCollection );

    /**
     * Provides pointer to the current menu bar.
     * 
     * @internal
     * @return Pointer to menu bar.
     */
    CEikMenuBar* FindCurrentMenuBar();

    /**
     * Adds register entry.
     * 
     * @param aMenuBar Menu bar.
     * @param aItemActionMenu Item action menu.
     */
    void AddRegisterEntryL(
            CEikMenuBar& aMenuBar, CAknItemActionMenu& aItemActionMenu );

    /**
     * Adds observers that have the same owner and aItemAction to the menu.
     * 
     * @param aItemActionMenu Item action menu.
     */
    void AddObserversToItemActionMenuL( CAknItemActionMenu& aItemActionMenu );

    /**
     * Creates register instance. 
     *
     * @return Item action menu register instance.
     */
    static AknItemActionMenuRegister* CreateInstanceL();

    /**
     * Sets constructing menu bar owner and checks if the current is a dialog.
     * And when setting the correct menu bar owner from a dialog to NULL 
     * checking if a correct menubar can be found for the unregistered 
     * item action menu. 
     */
    void DoSetConstructingMenuBarOwnerL( MObjectProvider* aMenuBarOwner ); 

    /**
     * Sets the current constructing menubar owner to NULL if it matches to
     * aMenuBarOwner. Otherwise constructing menubar owner is not modified.
     * 
     * @internal
     * @param aMenuBarOwner Pointer to constructing menubar owner. 
     */
    void DoRemoveConstructingMenuBarOwner( 
            MObjectProvider* aMenuBarOwner );

private: // data

    /**
     * Data class for unregistered menus.
     *
     * @lib eikcoctl
     * @since S60 v5.2
     */
    class TAknUnregisteredMenuData
        {
        public:
            /**
             * Pointer to unregistered menu owner.
             */
            MObjectProvider* iOwner;

            /**
             * Pointer to unregistered menu.
             */
            CAknItemActionMenu* iMenu;
        };

    /**
     * Data class for unregistered observers.
     */
    class TAknUnregisteredObserverData
        {

    public:
        /**
         * C++ constructor.
         */
        TAknUnregisteredObserverData(
                CEikMenuBar* aMenuBar,
                MAknCollectionObserver& aObserver,
                MObjectProvider* aOwner );

    public:
        /**
         * Reference to menu bar.
         */
        CEikMenuBar* iMenuBar;

        /**
         * Observer.
         */
        MAknCollectionObserver& iObserver;
        
        /**
         * Current menubar owner.
         */
        MObjectProvider* iOwner;
        };

    /**
     * Menu bar owner that is currently being constructed.
     * Not own.
     */
    MObjectProvider* iMenuBarOwner;

    /**
     * Indicates if current menubar owner is a dialog
     */
    TBool iIsConstructingDialog; 
    
    /**
     * Unregistered menu data.
     */
    RArray<TAknUnregisteredMenuData> iUnregisteredMenus;

    /**
     * Unregistered menu observers.
     */
    RArray<TAknUnregisteredObserverData> iUnregisteredObservers;

    /**
     * Register array.
     * Own.
     */
    CAknItemActionMenuRegisterArray* iRegisterArray;

    /**
     * Menu bar owner used to override all other menubar providers.
     * Not own.
     */
    MObjectProvider* iOverridingMenuBarOwner;
    };

#endif // C_AKNITEMACTIONMENUREGISTER_H

