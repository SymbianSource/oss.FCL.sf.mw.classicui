/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description : Interface for observer to be notified when a drive
*               inserted/removed or a remote drive connected/disconnected.
*/


#ifndef M_MAKNMEMORYSELECTIONDRIVEOBSERVER_H
#define M_MAKNMEMORYSELECTIONDRIVEOBSERVER_H

/**
*  Observer class that can be set to observe if a drive has been
*  inserted/removed and remote drive has been connected/disconnected.
*
*  @lib CommonDialogs.lib
*  @since S60 3.1
*/
class MAknMemorySelectionDriveObserver
    {

public:

// Constructors and destructor

    /**
     * A virtual destructor to ensure that correct destructor gets called.
     * Must have an empty implementation.
     */
    virtual ~MAknMemorySelectionDriveObserver() { };

// New functions

    /**
     * Get's called when user inserts/removes a drive
     *  or connects/disconnects a remote drive.
     */
    virtual void NotifyDrivesChangedL(
        const MDesCArray* aItemArray) = 0;

    };


#endif // M_MAKNMEMORYSELECTIONDRIVEOBSERVER_H

