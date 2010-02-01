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
* Description: Item action menu data.
*
*/

#ifndef C_AKNITEMACTIONMENUDATA_H
#define C_AKNITEMACTIONMENUDATA_H

#include <e32base.h>

class CAknStylusPopUpMenu;
class MDesCArray;

/**
 * Menu pane item maximum text length.
 */
const TInt KMenuPaneItemTextLength( 40 );

/**
 * Menu pane item text buf.
 */
typedef TBuf<KMenuPaneItemTextLength> TMenuItemTextBuf;

/**
 * Item action menu data.
 *
 * @lib eikcoctl
 * @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknItemActionMenuData ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknItemActionMenuData* NewL();

    /**
     * Destructor.
     */
    virtual ~CAknItemActionMenuData();

    /**
     * Adds menu data item to menu data array.
     * 
     * @param aCommandId Menu item command id.
     * @param aCascadeId Menu item cascade id.
     * @param aText Menu item text.
     */
    void AddMenuItemToDataArrayL(
            TInt aCommandId, TInt aCascadeId, const TDesC& aText );

    /**
     * Adds menu data items styluspopupmenu.
     * 
     * @param aPopupMenu Stylus popup menu.
     */
    void AddMenuItemsToStylusPopupMenuL( CAknStylusPopUpMenu* aPopupMenu );

    /**
     * Provides menu items for query dialog.
     * 
     * @return Text array for query dialog.
     */
    MDesCArray* MenuItemsForQueryDialogL();

    /**
     * Returns menu item cascade id for requested index.
     * 
     * @param aIndex Menu item index + 1.
     * @return Menu item cascade id if it has one.
     * Otherwise 0.
     */
    TInt MenuItemCascadeId( TInt aIndex );

    /**
     * Returns menu item text for requested index.
     * 
     * @param aIndex Menu item index + 1.
     * @return Menu item text.
     */
    TDesC& MenuItemText( TInt aIndex );

    /**
     * Returns menu item command id for requested index.
     * 
     * @param aIndex Menu item index + 1.
     * @return Menu item command id.
     */
    TInt MenuItemCommandId( TInt aIndex );

    /**
     * Resets menu data array.
     */
    void Reset();

    /**
     * Returns menu data array item count.
     * 
     * @return Data array item count.
     */
    TInt Count() const;

private:

    /**
     * C++ constructor.
     */
    CAknItemActionMenuData();

private: // data

    /**
     * Single item action menu item data structure.
     */
    class TAknItemActionMenuData
        {

    public:

        /**
         * Menu item command id.
         */
        TInt iCommandId;

        /**
         * Menu item cascade id.
         */
        TInt iCascadeId;

        /**
         * Menu item text.
         */
        TMenuItemTextBuf iText;
        };

    /**
     * Menu data.
     */
    RArray<TAknItemActionMenuData> iMenuData;
    };

#endif // C_AKNITEMACTIONMENUDATA_H
