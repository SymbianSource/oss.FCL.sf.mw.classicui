/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  AVKON notifier client for setting the state of
*                status pane's battery pane.
*
*/


#ifndef __AKNBATTERYNOTIFY_H__
#define __AKNBATTERYNOTIFY_H__

#include <AknNotify.h>

/**
* Notifier client implementation for the system application to
* control the battery pane state.
*
* @lib aknnotify.lib
* @since 0.9
*/
NONSHARABLE_CLASS( CAknBatteryNotify ) : public CAknNotifyBase
    {
    // Friend class is the system application that can change state of
    // battery indicator.
    friend class CSysApAppUi;

    friend class CIndicViewContainer;

private:

    /**
    * Two-phased constructor.
    */
    IMPORT_C static CAknBatteryNotify* NewL();

    /**
    * Two-phased constructor.
    */
    IMPORT_C static CAknBatteryNotify* NewLC();

    /**
    * Destructor.
    */
    IMPORT_C ~CAknBatteryNotify();

    /**
    * Sets the battery level.
    * @param  aLevel  The battery level, accepts values from 0 to 7.
    */
    IMPORT_C void SetBatteryLevelL( TInt aLevel );

    /**
    * Starts the charging animation in the battery pane.
    */
    IMPORT_C void StartChargingL();

    /**
    * Stops the charging animation in the battery pane.
    */
    IMPORT_C void StopChargingL();

    /**
    * @deprecated
    */
    IMPORT_C void NotChargingL();

    /**
    * Changes the battery icon on the battery pane.
    * For the possible states @see TAknBatteryIndicatorStates in @c avkon.hrh
    * @param  aState  The battery icon state.
    */
    IMPORT_C void SetBatteryStateL( TInt aState );

    /**
    * Default C++ constructor.
    */
    CAknBatteryNotify();

    /**
    * Symbian 2nd-phase constructor.
    */
    void ConstructL();
    };

#endif // __AKNBATTERYNOTIFY_H__
