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


#ifndef C_AKNCONFGESTURESETTINGLIST_H
#define C_AKNCONFGESTURESETTINGLIST_H


#include "aknconfsettinglist.h"

class CRepository;

/**
 *  AknConf setting list component
 */
class CAknConfGestureSettingList : public CAknConfSettingList
    {

public:

    static CAknConfGestureSettingList* NewL();
    
    /**
     * Destructor.
     */
    ~CAknConfGestureSettingList();

    /**
     * Resets the cenrep values to initial state.
     */
    void ResetValues();

private:

    CAknConfGestureSettingList();

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

private:

    /**
     * Settings data values.
     */
    TInt iTapThreshold;
    TInt iLongTapThreshold;
    TInt iDoubleTapThreshold;
    TInt iDragThreshold;
    TInt iFlickBuffer;
    TInt iFlickSpeedThreshold;
    TInt iFlickDetectionTime;
    TInt iFlickChangeSensitivity;
    TInt iPinchInitialThreshold;
    TInt iPinchMovementThreshold;
    TInt iPinchDirectionChangeSensitivity;
    TInt iPinchDirectionResetSensitivity;
    TInt iPinchDimensionThreshold;
    TInt iPinchMaximumConfirmationDuration;
    
    };

#endif // C_AKNCONFGESTURESETTINGLIST_H
