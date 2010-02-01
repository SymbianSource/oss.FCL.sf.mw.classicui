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
* Description:  Client API for Avkon soft notifications.   
*
*/

#ifndef __AKNSOFTNOTIFIER_H__
#define __AKNSOFTNOTIFIER_H__

#include <AknNotify.h>
#include <AknNotifyStd.h>

class CAknPrivateSoftNoteParameters;
class CAknSoftNotificationParameters;
class CAknSoftNotifierExt;



NONSHARABLE_CLASS(CAknSoftNotifier) : public CAknNotifyBase
    {
    public:
        IMPORT_C static CAknSoftNotifier* NewL();
        IMPORT_C static CAknSoftNotifier* NewLC();
        IMPORT_C ~CAknSoftNotifier();

        /**
        * Add new soft notification of type 'aType'. If the notification of
        * type 'aType' already exists number of items is increased by one.
        * Optional dynamic notification text can also be set.
        *       
        * Please note that this method cannot be used with custom soft notifications
        *
        * @param aType The type of the soft notification. Types can be found
        *        in AknNotifyStd.h 
        * @param aText Dynamic text to the notification.
        */
        IMPORT_C void AddNotificationL(
            TAknSoftNotificationType aType, TPtrC* aText = NULL );

        /**
        * Add new soft notification of type 'aType'. The number of items is
        * set to 'aCount'.
        *       
        * Please note that this method cannot be used with custom soft notifications
        *
        * @param aType The type of the soft notification. Types can be found
        *        in AknNotifyStd.h
        * @param aCount The number of items for this type, e.g, missed calls,
        *        voice mails
        */
        IMPORT_C void AddNotificationL(
            TAknSoftNotificationType aType, TInt aCount );
    
        /**
        * Set number of notifications of type 'aType'. This overrides current
        * value. Optional dynamic notification text can also be set.
        *       
        * Please note that this method cannot be used with custom soft notifications
        * 
        * @param aType The type of the soft notification.
        *        Types can be found in AknNotifyStd.h
        * @param aCount Number of item is the notification.
        * @param aText Dynamic text to the notification. (Not implemented in
        *        current release).
        */
        IMPORT_C void SetNotificationCountL(
            TAknSoftNotificationType aType, TInt aCount, TPtrC* aText = NULL );

        /**
        * Cancels soft notification of type 'aType'.
        *       
        * Please note that this method cannot be used with custom soft notifications
        *
        * @param aType The type of the soft notification.
        * Types can be found in AknNotifyStd.h
        */
        IMPORT_C void CancelSoftNotificationL( TAknSoftNotificationType aType );

        /**
        * Adds a custom soft notification. If a custom soft notification with
        * exactly the same parameters already exists,
        * its count is increased by aCount.
        *
        * @param aParams custom soft notification parameters
        * @param aCount count
        */
        IMPORT_C void AddCustomNotificationL(
            CAknSoftNotificationParameters& aParams, TInt aCount = 1 );

        /**
        * Sets the absolute count of a custom soft notification with
        * given parameters. If such notification did not exist already,
        * it is created.
        */
        IMPORT_C void SetCustomNotificationCountL(
            CAknSoftNotificationParameters& aParams, TInt aCount );

        /**
        * Cancels custom soft notification with the given parameters.
        */
        IMPORT_C void CancelCustomSoftNotificationL(
            CAknSoftNotificationParameters& aParams );

    private:
        /**
        * Tell the soft notes if the phone is in idle state or not.
        * Soft notes do not display unless the phone is in idle state.
        *
        * @param aIdleState Is phone in idle state
        */
        IMPORT_C void SetIdleStateL( TBool aIdleState );

    private:
        IMPORT_C void CAknNotifyBase_Reserved();
        CAknSoftNotifier();
        void ConstructL();

        void PrepareBufferL( 
            TAknSoftNotificationType aType, 
            TInt aCount, 
            TPtrC* aText, 
            TBool aCancel, 
            TBool aAddCount,
            CAknSoftNotificationParameters* aParams = NULL);

    private: // data
        CBufFlat* iBuffer;
        TPtrC8 iBufferPtr;

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
        CAknSoftNotifierExt* iExt;
#endif
    public: // NCN updates phone idle information
        friend class CNcnSNNotifier;
        friend class CSimpleAppUi;
        
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
        friend class CAknSoftNotifierExt;
#endif
    };

#endif // __AKNSOFTNOTIFIER_H__
