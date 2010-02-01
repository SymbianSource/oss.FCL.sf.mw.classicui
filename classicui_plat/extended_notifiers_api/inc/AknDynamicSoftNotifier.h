/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Client API for Dynamic Avkon soft notifications.
*
*/

#ifndef AKNDYNAMICSOFTNOTIFIER_H
#define AKNDYNAMICSOFTNOTIFIER_H

// INCLUDES
#include <e32base.h>
#include <AknCapServerClient.h>

// FORWARD DECLARATION
class TAknDynamicSoftNotificationParams;
class CAknDynamicSoftNoteObserver;
class CAknDynamicNotifier;
class CAknSDData;

/**
 * Observer interface for dynamic soft notifications.
 * 
 * @see CAknDynamicSoftNotifier
 * @since S60 3.2
 * @lib AknNotify.DLL
 */
class MAknDynamicSoftNoteObserver
    {
public: // New methods    
    
    /**
     * Dynamic soft notification was accepted by user.
     *
     * @param aNoteId Identification of notification.
     */
    virtual void NotificationAccepted( TInt aNoteId ) = 0;
    
    /**
     * Dynamic soft notification was canceled by user.
     *
     * @param aNoteId Identification of notification.
     */
    virtual void NotificationCanceled( TInt aNoteId ) = 0;
        
    
protected: // protected destructor
    
    /// Virtual destructor.
    virtual ~MAknDynamicSoftNoteObserver() {};
    };

/**
 * Client API for dynamic Avkon soft notifications.
 *
 * @since S60 3.2
 * @lib AknNotify.DLL
 */
NONSHARABLE_CLASS( CAknDynamicSoftNotifier ) : public CBase
    {
public:
    /// Static constructor.
    IMPORT_C static CAknDynamicSoftNotifier* NewL();

    /// Static constructor.
    IMPORT_C static CAknDynamicSoftNotifier* NewLC();

    /// Destructor.
    IMPORT_C ~CAknDynamicSoftNotifier();

    /**
     * Adds a dynamic soft notification. If a dynamic soft notification with
     * exactly the same id already exists, its count is increased by aCount.
     *
     * @param aParams Dynamic soft notification parameters.
     * @param aNoteId Dynamic soft notification identification.
     *        - If note is found: Old notification is updated.
     *        - If note is not found: method will return the id of
     *          newly created notification.
     *        - If not provided: New note is always created.
     * @param aCount Addition count.
     * @return ID ID of created or updated notification. Can be the same
     *         as aNoteId.
     */
    IMPORT_C TInt AddDynamicNotificationL(
        TAknDynamicSoftNotificationParams& aParams,
        TInt aNoteId = KErrUnknown,
        TInt aCount = 1 );

    /**
     * Sets the absolute count of a dynamic soft notification with
     * given id. If such notification did not exist already,
     * it is created.
     *
     * @param aParams Dynamic soft notification parameters.
     * @param aNoteId Dynamic soft notification identification.
     *        - If such note is found, then that is updated
     *        - If note is not found, then method will return the id of
     *          newly created notification.
     *        - Use KErrUnknown if you want to create a new dynamic soft 
     *          notification.
     * @param aCount Absolute count.
     * @return ID ID of created or updated notification. Can be the same
     *         as aNoteId.
     */
    IMPORT_C TInt SetDynamicNotificationCountL(
        TAknDynamicSoftNotificationParams& aParams,
        TInt aNoteId,
        TInt aCount );

    /**
     * Cancels dynamic soft notification of the given identification.
     *
     * @param aNoteId Dynamic soft notification identification.
     */
    IMPORT_C void CancelDynamicNotificationL( TInt aNoteId );
 
    /**
     * Add dynamic soft notification observer. 
     * Leaves with KErrAlreadyExists if same NoteId is added twice.
     * Does not take ownership of the observer.
     * 
     * @param aNoteId Soft notification id. 
     * @param aObserver Observer for notification. 
     */
    IMPORT_C void StartObservingL( 
        TInt aNoteId, 
        MAknDynamicSoftNoteObserver* aObserver );
    
    /**
     * Stop observing the specific soft notification.
     * 
     * @param aNoteId Soft notification id. 
     */
    IMPORT_C void StopObserving( TInt aNoteId );

    /**
     * Sets additional information to be sent to secondary display.
     * Takes ownership of object.
     * Must be called before sending data to notifier to have effect.
     * 
     * @param aData Data to be sent to cover UI.
     * @internal to S60
     */
    IMPORT_C void SetSecondaryDisplayData( CAknSDData* aData );
    
public: // Non-exported    
     
    /**
     * Deletes given observer and removes it from the internal array.
     * 
     * @param aObserver Observer to be deleted.
     */    
    void DeleteObserver( CAknDynamicSoftNoteObserver* aObserver );
    
    
    /**
     * Getter for secondary display data.
     * 
     * @return Instance of secondary display data if set.
     */
    CAknSDData* SecondaryDisplayData();
    
private:
    
    /// Constructor.
    CAknDynamicSoftNotifier();

    /// 2nd phase constructor.
    void ConstructL();

    /**
     * Internalizes parameters into buffer and sends it to server.
     *
     * @param aNoteId Notification Identifier which is to be updated. 
     * @param aCount Count of soft notifications.
     * @param aCancel ETrue : Cancel soft notification.
     * @param aAddCount  ETrue  : Count is added to previous count.
     *                   EFalse : Count is absolute value.
     * @param aParams Parameters for dynamic soft notification.
     * @return Identification of created or updated dynamic notification. 
     */
    TInt SendMessageL(
        TInt aNoteId,
        TInt aCount,
        TBool aCancel,
        TBool aAddCount,
        TAknDynamicSoftNotificationParams& aParams );

    /**
     * Find Observer of the given notification id.
     * 
     * @param aNoteId Soft notification id.
     * @return KErrNotFound or index of the observer. 
     */
    TInt FindByNoteId( TInt aNoteId ) const;        
    
private: // Data
    /// Own. Array of observed soft notifications.
    RPointerArray<CAknDynamicSoftNoteObserver> iObservers;
    /// Own. Secondary display custom data.
    CAknSDData* iSecondaryDisplayData;
    /// Own. Notifier handle.
    CAknDynamicNotifier* iNotifier;
    };

#endif // AKNDYNAMICSOFTNOTIFIER_H
