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


#ifndef C_AKNCONFPHYSICSSETTINGLIST_H
#define C_AKNCONFPHYSICSSETTINGLIST_H


#include "aknconfsettinglist.h"

class CRepository;

/**
 *  AknConf setting list component
 */
class CAknConfPhysicsSettingList : public CAknConfSettingList
    {

public:

    static CAknConfPhysicsSettingList* NewL();
    
    /**
     * Destructor.
     */
    ~CAknConfPhysicsSettingList();

// from base class CAknSettingItemList

    /**
     * Resets the cenrep values to initial state.
     */
    void ResetValues();

    /**
     * Framework method to create a setting item based upon the user id aSettingId. The 
     * client code decides what type to contruct. new (ELeave) must then be used and the resulting 
     * pointer returned. Ownership is thereafter base class's responsiblity.
     *
     * @param aSettingId    ID to use to determine the type of the setting item
     * @return a constructed (not 2nd-stage constructed) setting item.
     */
    CAknSettingItem* CreateSettingItemL( TInt aIdentifier );

private:

    CAknConfPhysicsSettingList();

    void ConstructL();
    
    /**
     * Returns the pointer to data value that corresponds the setting id.
     * Provides also the setting cen rep key.
     *
     * @param aId ID to determine the type of the setting item.
     * @param aCenRepKey Setting cen rep key.
     * @return Pointer to data value.
     */
    TInt* DataValuePointer( const TInt& aId, TInt& aCenRepKey );
    
    /**
     * Gets and sets setting value from cenrep according to given setting id.
     *
     * @param aId ID to determine the type of the setting item.
     * @param aCenRepKey Setting cen rep key.
     * @return Pointer to setting value.
     */
    TInt* ValueFromCenRep(  const TInt& aId, TInt& aCenRepKey  );

private:

    /**
     * Settings data values.
     */
    TInt iMass;
    TInt iGravity;
    TInt iSurfaceSoftErp;
    TInt iSurfaceSoftCfm;
    TInt iHighlightTimeout;
    TInt iDragThreshold;
    TBool iFeatureEnabled;
    TInt iFrameDelay;
    TInt iMinFrameInterval;
    TInt iShortListEmptySpace;
    TInt iLongListEmptySpace;
    TInt iFpsLoggingEnabled;

    };

#endif // C_AKNCONFPHYSICSSETTINGLIST_H
