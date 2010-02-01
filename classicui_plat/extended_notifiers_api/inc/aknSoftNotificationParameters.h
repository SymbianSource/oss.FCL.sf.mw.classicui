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
* Description:  Utility implementation for CAknSoftNotificationParameters.
*
*/

#ifndef AKN_SOFT_NOTIFICATION_PARAMETERS
#define AKN_SOFT_NOTIFICATION_PARAMETERS

// INCLUDES
#include <vwsdef.h> // For view server definitions
#include <aknnotedialog.h> // For CAknNoteDialog::TTone

// CLASS DECLARATION

/**
*  Utility implementation for CAknSoftNotificationParameters
*
*  @lib AknNotifyPlugin.lib
*  @since S60 1.2
*/
class CAknSoftNotificationParameters : public CBase
    {
public: // constructors and destructor

    /**
    * Static constructor for creating custom soft notification parameters. 
    * Initializes the member variables with null values.
    *
    * @return The new object for custom soft notification parameters.
    */
    IMPORT_C static CAknSoftNotificationParameters* NewL();

    /**
    * Static constructor for creating custom soft notification parameters.
    *
    * @param aResourceFile Full resource file name (containing drive and path).
    * @param aNoteResourceId Resource ID in given resource file.
    *                        Must be a resource of type AVKON_NOTE.
    * @param aPriority Priority for soft notification.
    * @param aSoftkeys Resource ID for softkeys. Must be from avkon.rsg.
    * @param aTone Tone for soft notification.
    * @return The new object for custom soft notification parameters.
    */
    IMPORT_C static CAknSoftNotificationParameters* NewL(
        const TDesC& aResourceFile,
        TInt aNoteResourceId,
        TInt aPriority,
        TInt aSoftkeys,
        CAknNoteDialog::TTone aTone );

    /**
    * Static constructor for creating custom soft notification parameters.
    *
    * @param aResourceFile Full resource file name (containing drive and path).
    * @param aNoteResourceId Resource ID in given resource file.
    *                        Must be a resource of type AVKON_NOTE.
    * @param aPriority Priority for soft notification.
    * @param aSoftkeys Resource ID for softkeys. Must be from avkon.rsg.
    * @param aTone Tone for soft notification.
    * @param aViewId View ID of the view where to switch in case user chooses
    *                accept softkey in the soft notification.
    * @param aCustomMessageId Custom Uid sent to the view in the view activation process.
    * @param aAcceptKeyId ID of a softkey used for accepting the query. Exiting type softkeys 
    *                     (e.g. "cancel", "exit", "back", "done", etc.) should not be used.
    * @param aViewActivationMsg Custom message sent to the view in
    *                           the view activation process.
    * @return The new object for custom soft notification parameters.
    */
    IMPORT_C static CAknSoftNotificationParameters* NewL(
        const TDesC& aResourceFile,
        TInt aNoteResourceId,
        TInt aPriority,
        TInt aSoftkeys,
        CAknNoteDialog::TTone aTone,
        TVwsViewId aViewId,
        TUid aCustomMessageId,
        TInt aAcceptKeyId,
        const TDesC8& aViewActivationMsg );

    /**
    * Destructor.
    */
    IMPORT_C ~CAknSoftNotificationParameters();

    /**
    * Sets the texts to be used when the soft notification is displayed in grouped form.
    * Calling this method with non-null parameter also indicates that the soft notification
    * supports grouped form.
    *
    * @param aGroupedTextsID Resource identifier pointing to AVKON_GROUPED_NOTE_TEXTS resource.
    *                        The resource can have singular and plural labels. See avkon.rh for 
    *                        details.
    */
    inline void SetGroupedTexts( TInt aGroupedTextsID )
        {iGroupedTextResourceId = aGroupedTextsID;}
 
    /** 
    * Legacy support. Sets the plural view ID.
    *
    * @param aViewId Plural view ID.
    */
    inline void SetPluralViewId( const TVwsViewId& aViewId )
        {iPluralViewId = aViewId;}

protected:
    CAknSoftNotificationParameters(){}

protected: // data
    HBufC* iResourceFile;
    TInt iNoteResourceId; // must point to resource of type AVKON_NOTE
    TInt iPriority;
    TInt iSoftkeys;
    CAknNoteDialog::TTone iTone;

    // view activation related parameters
    TVwsViewId iViewId;
    TUid iCustomMessageId;
    TInt iAcceptSoftKey;
    HBufC8* iViewActivationMsg; // owned

public: // friend classes
    friend class CAknSoftNotificationSubject;
    friend class CAknSoftNotifier;

protected: // new data
    TVwsViewId iPluralViewId;
    TInt iGroupedTextResourceId;
    };

#endif // AKN_SOFT_NOTIFICATION_PARAMETERS
