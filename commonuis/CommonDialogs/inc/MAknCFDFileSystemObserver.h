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
* Description:  Interface for observer to be notified when MMC inserted
*
*/


#ifndef MAKNCFDFILESYSTEMOBSERVER_H_
#define MAKNCFDFILESYSTEMOBSERVER_H_

/**
*  Observer class that can be set to observe if file system have some change.
*
*  @lib CommonDialogs.lib
*  @since S60 5.0
*/
class MAknCFDFileSystemObserver
    {

public:

    // Constructors and destructor
    /**
     * A virtual destructor to ensure that correct destructor gets called.
     * Must have an empty implementation.
     */
    virtual ~MAknCFDFileSystemObserver() { };

    // New functions
    /**
     * Get's called when file system have some changed.
     */
    virtual void NotifyFileSystemChangedL() = 0;

    };

#endif /*MAKNCFDFILESYSTEMOBSERVER_H_*/
