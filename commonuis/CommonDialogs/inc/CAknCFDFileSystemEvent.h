/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  New memory selection setting item to support multiple drives.
*
*/

#ifndef CAKNCFDFILESYSTEMEVENT_H_
#define CAKNCFDFILESYSTEMEVENT_H_

// INCLUDES
#include <e32base.h>
#include <f32file.h>

// FORWARD DECLARATIONS
class MAknCFDFileSystemObserver;

// CLASS DECLARATION

/**
*  This class listens file system events
*
*  @lib CommonDialogs.lib
*  @since s60 5.0
*/
NONSHARABLE_CLASS(CAknCFDFileSystemEvent) : public CActive
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CAknCFDFileSystemEvent* NewL( RFs& aFs, 
        		MAknCFDFileSystemObserver& aObserver,
                TNotifyType aNotifyType, 
                const TDesC& aFullPath = KNullDesC );

        /**
        * Destructor.
        */
        virtual ~CAknCFDFileSystemEvent();
    public:

        /**
        * Sets file system event
        * @since s60 5.0
        */
        void Setup();

        /**
        * This calls refresh if file system event has happened
        * @since s60 5.0
        */
        void CheckFileSystemEvent();
    protected:  // Functions from base classes
        /**
        * From CActive Called when asynchronous request has completed
        * @since s60 5.0
        */
        void RunL();

        /**
        * From CActive Called when asynchronous request has failed
        * @since s60 5.0
        */
        TInt RunError( TInt aError );

        /**
        * From CActive Called when asynchronous request was cancelled
        * @since s60 5.0
        */
        void DoCancel();

    private:
        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL( const TDesC& aFullPath );

        /**
        * C++ default constructor.
        */
        CAknCFDFileSystemEvent(
                RFs& aFs, 
                MAknCFDFileSystemObserver& aObserver,
                TNotifyType aNotifyType );
    
    private:
        // Ref: Reference to opened File System session
        RFs& iFs;

        // Ref: This object is called when RunL occurs
        MAknCFDFileSystemObserver& iObserver;
        
        // Type of the notify, entry or disk.
        TNotifyType iNotifyType;
        
        // Full path of folder from where notification is needed
        HBufC* iFullPath;

        // Indicates if the event has been received
        TBool iIsReceived;
    };

#endif /*CAKNCFDFILESYSTEMEVENT_H_*/
