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
* Description:  AknConf setting list component
 *
*/


#ifndef C_AKNCONFSETTINGLIST_H
#define C_AKNCONFSETTINGLIST_H


#include <aknsettingitemlist.h>

class CRepository;

/**
 *  AknConf setting list component
 */
class CAknConfSettingList : public CAknSettingItemList
    {

public:

    /**
     * Destructor.
     */
    ~CAknConfSettingList();
    
    /**
     * Setting item calls this when the opened setting page is closed.
     *
     * @param aOkPressed ETrue if ok was pressed.
     * @param aValue New value of the setting.
     * @param aCenRepKey The setting cen rep key.
     */
    void SettingPageClosed( TBool aOkPressed, 
                            const TInt& aValue, 
                            const TInt& aCenRepKey );

    /**
     * Resets the cenrep values to initial state.
     */
    virtual void ResetValues() = 0;

// from base class CAknSettingItemList

    /**
     * Framework method to create a setting item based upon the user id aSettingId. The 
     * client code decides what type to contruct. new (ELeave) must then be used and the resulting 
     * pointer returned. Ownership is thereafter base class's responsiblity.
     *
     * @param aSettingId	ID to use to determine the type of the setting item
     * @return a constructed (not 2nd-stage constructed) setting item.
     */
    CAknSettingItem* CreateSettingItemL( TInt aIdentifier );

protected:

    CAknConfSettingList();

    /**
     * Symbian second phase constructor. Should be used by sub classes.
     *
     * @param aCenRepUid Central repository UID. 
     * @param aResourceFile Resource file to be added to CONE.
     */
    void ConstructL(
            const TUid& aCenRepUid,
            const TDesC& aResourceFile );

    /**
     * Returns the pointer to data value that corresponds the setting id.
     * Provides also the setting cen rep key.
     *
     * @param aId ID to determine the type of the setting item.
     * @param aCenRepKey Setting cen rep key.
     * @return Pointer to data value.
     */
    virtual TInt* DataValuePointer( const TInt& aId, TInt& aCenRepKey ) = 0;
    
    /**
     * Gets and sets setting value from cenrep according to given setting id.
     *
     * @param aId ID to determine the type of the setting item.
     * @param aCenRepKey Setting cen rep key.
     * @return Pointer to setting value.
     */
    TInt* ValueFromCenRep(  const TInt& aId, TInt& aCenRepKey  );

protected:

    /**
     * Central repository.
     * Own.
     */
    CRepository* iCenRep;

    /**
     * Resource file offset value.
     */
    TInt iResourceOffset;

    };

#endif // C_AKNCONFSETTINGLIST_H
