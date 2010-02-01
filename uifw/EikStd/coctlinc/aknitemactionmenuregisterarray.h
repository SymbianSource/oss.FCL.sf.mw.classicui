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
* Description: Item action menu register array.
*
*/

#ifndef C_AKNITEMACTIONMENUREGISTERARRAY_H
#define C_AKNITEMACTIONMENUREGISTERARRAY_H

#include <e32base.h>

class CAknItemActionMenu;
class CEikMenuBar;
class MAknCollectionObserver;

/**
 * Item action menu register array.
 *
 * @lib eikcoctl
 * @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknItemActionMenuRegisterArray ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknItemActionMenuRegisterArray* NewL();

    /**
     * Two-phased constructor.
     */
    static CAknItemActionMenuRegisterArray* NewLC();

    /**
     * Destructor.
     */
    virtual ~CAknItemActionMenuRegisterArray();

    /**
     * Adds entry to register. Item action menu ownership transfers.
     * 
     * @param aMenuBar Menu bar
     * @param aItemActionMenu Item action menu
     */
    void AddEntryL(
            CEikMenuBar& aMenuBar,
            CAknItemActionMenu& aItemActionMenu );

    /**
     * Unregisters menu bar.
     * 
     * @param aMenuBar Calling menu bar.
     */
    void UnregisterMenuBar( CEikMenuBar& aMenuBar );

    /**
     * Unregisters item action menu.
     * 
     * @param aItemActionMenu Calling item action menu.
     */
    void UnregisterItemActionMenu( CAknItemActionMenu& aItemActionMenu );

    /**
     * Registers collection observer.
     * 
     * @param aMenuBar Menu bar.
     * @param aObserver Collection observer.
     */
    TBool RegisterCollectionObserverL(
            CEikMenuBar& aMenuBar, MAknCollectionObserver& aObserver );

    /**
     * Unregisters collection observer.
     * 
     * @param aObserver Collection observer.
     */
    void UnregisterCollectionObserver( MAknCollectionObserver& aObserver );

private:

    /**
     * C++ constructor.
     */
    CAknItemActionMenuRegisterArray();

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Removes entry from register.
     * 
     * @param aIndex Index to be removed.
     */
    void RemoveEntry( TInt aIndex );

private: // data

    /**
     * Class representing single entry in register.
     */
    NONSHARABLE_CLASS( CRegisterEntry ) : public CBase
        {

    public:
        /**
         * Two-phased constructor.
         */
        static CRegisterEntry* NewL(
                CEikMenuBar& aMenuBar, CAknItemActionMenu& aItemActionMenu );

        /**
         * Two-phased constructor.
         */
        static CRegisterEntry* NewLC(
                CEikMenuBar& aMenuBar, CAknItemActionMenu& aItemActionMenu );

        /**
         * Destructor.
         */
        virtual ~CRegisterEntry();

        /**
         * Removes menu bar.
         */
        void RemoveMenuBar();

        /**
         * Provides entry menu bar.
         * 
         * @return Menu bar.
         */
        CEikMenuBar* MenuBar();

        /**
         * Removes item action menu.
         */
        void RemoveItemActionMenu();

        /**
         * Provides entry item action menu.
         * 
         * @return Item action menu.
         */
        CAknItemActionMenu* ItemActionMenu();

    private:
        /**
         * C++ constructor.
         */
        CRegisterEntry(
                CEikMenuBar& aMenuBar, CAknItemActionMenu& aItemActionMenu );

        /**
         * Symbian 2nd phase constructor.
         */
        void ConstructL();

    private: // data
        /**
         * Menu bar.
         * Not own.
         */
        CEikMenuBar* iMenuBar;

        /**
         * Item action menu.
         * Own.
         */
        CAknItemActionMenu* iActionMenu;
        };
    
    /**
     * Register array.
     */
    RPointerArray<CRegisterEntry> iRegisterArray;
    };

#endif // C_AKNITEMACTIONMENUREGISTERARRAY_H
