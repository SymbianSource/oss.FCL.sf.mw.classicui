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
     * Registers a collection.
     * 
     * @internal
     * @param aCollection Collection to be registered.
     * @return Item action menu the collection was registered to.
     */
    static CAknItemActionMenu* RegisterCollectionL(
            MAknCollection& aCollection );

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
     * @return Item action menu the collection was registered to.
     */
    CAknItemActionMenu* DoRegisterCollectionL(
            MAknCollection& aCollection );

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
     CEikMenuBar* FindCurrentMenuBarL();

    /**
     * Adds register entry.
     * 
     * @param aMenuBar Menu bar.
     * @param aItemActionMenu Item action menu.
     */
    void AddRegisterEntryL(
            CEikMenuBar& aMenuBar, CAknItemActionMenu& aItemActionMenu );

    /**
     * Adds observers with aMenuBar to item action menu.
     * 
     * @param aMenuBar Menu bar.
     * @param aItemActionMenu Item action menu.
     */
    void AddObserversToItemActionMenuL(
            CEikMenuBar* aMenuBar, CAknItemActionMenu& aItemActionMenu );

    /**
     * Creates register instance. 
     *
     * @return Item action menu register instance.
     */
    static AknItemActionMenuRegister* CreateInstanceL();
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
                MAknCollectionObserver& aObserver );

    public:
        /**
         * Reference to menu bar.
         */
        CEikMenuBar* iMenuBar;

        /**
         * Observer.
         */
        MAknCollectionObserver& iObserver;
        };

    /**
     * Menu bar owner that is currently being constructed.
     * Not own.
     */
    MObjectProvider* iMenuBarOwner;

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

