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
* Description:  Dynamic soft notification data store
*
*/

#ifndef AKNDYNAMICSOFTNOTIFICATIONDATA_H
#define AKNDYNAMICSOFTNOTIFICATIONDATA_H

// INCLUDES
#include <e32base.h>
#include <vwsdef.h> // For view server definitions
#include <aknnotedialog.h> // For CAknNoteDialog::TTone

// CLASS DECLARATION

/**
*  Dynamic soft notification data store.
*
*  @lib AknNotifyPlugin.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS( CAknDynamicNotificationData ) : public CBase
    {
public: // constructor

    /**
     * Static constructor. Construct data from stream.
     * @param aStream Source stream.
     * @return New CAknDynamicNotificationData instance.
     */
    static CAknDynamicNotificationData* NewL ( RReadStream& aStream );

    /**
     * Static constructor. Construct data from stream.
     * @param aStream Source stream.
     * @return New CAknDynamicNotificationData instance.
     */
    static CAknDynamicNotificationData* NewLC( RReadStream& aStream );
    
    /// Destructor.
    ~CAknDynamicNotificationData();
    
public: // new methods

    /**
     * Internalize data into stream.
     * @param aStream Destination stream.
     */
    void InternalizeL( RReadStream& aStream );

    /**
     * Externalize data from stream.
     * @param aStream Source stream.
     */
    void ExternalizeL( RWriteStream& aStream ) const;

    /**
     * Reset the Id of the soft notification.
     * @param aId New id of the notification.
     */
    void SetId( TInt aId );
    
    /**
     * @return Notification identification.
     */
    TInt Id() const;

    /**
     * @return Notification priority.
     */
    TInt Priority() const;
    
    /**
     * @return Notification tone.
     */
    CAknNoteDialog::TTone Tone() const;
    
    /**
     * @return Destination view when note is accepted.
     */
    TVwsViewId ViewId() const;

    /**
     * @return Destination view when note is accepted. When note count is > 1.
     */
    TVwsViewId PluralViewId() const;

    /**
     * @return Custom data uid for launched view.
     */
    TUid CustomMsgUid() const;

    /**
     * @return Custom data for launched view.
     */
    const TDesC8& CustomMsg() const;

    /**
     * @return Left softkey text.
     */
    const TDesC& LeftSoftkey() const;

    /**
     * @return Right softkey text.
     */
    const TDesC& RightSoftkey() const;
    
    /**
     * @return Text shown when count == 1.
     */
    const TDesC& SingularLabel() const;
    
    /**
     * @return Text shown when count > 1.
     */
    const TDesC& PluralLabel() const;

    /**
     * @return Text shown when count == 1. Only in grouped view.
     */
    const TDesC& SingularLabelGroup() const;

    /**
     * @return Text shown when count > 1. Only in grouped view.
     */
    const TDesC& PluralLabelGroup() const;
    
    /**
     * @return Flag whether the user events are wanted by the event manager. 
     */
    TBool EnableObserver() const;
    
    /**
     * @return Binary data for notification image.
     */
    const TDesC8& ImageData() const;
    
private: // new methods
    CAknDynamicNotificationData();
    void ConstructL( RReadStream& aStream );
    
    void ResetContent();
    
    HBufC8*  InternalizeText8L(  RReadStream& aStream ) const;
    HBufC16* InternalizeText16L( RReadStream& aStream ) const;
    
    void ExternalizeTextL( RWriteStream& aStream, const TDesC16* aText ) const;
    void ExternalizeTextL( RWriteStream& aStream, const TDesC8* aText ) const;
    
protected: // data

    /// Identification of the note.
    TInt iNoteId;
    /// Priority of the note (see AknSoftNotificationPlugin.cpp).
    TInt iPriority;
	/// Tone played when note is shown.
	CAknNoteDialog::TTone iTone;
    /// Flag whether the user events are wanted by the event manager. 
    TBool iEnableObserver;


    /// Launched view when count == 1.
    TVwsViewId iViewId;
    /// Launched view when count > 1.
    TVwsViewId iPluralViewId;
    /// Uid for the new view.
    TUid iCustomMessageId;
    /// Own. Custom message for new view.
    HBufC8* iCustomMessage;

    /// Own. Left softkey.
    HBufC* iLeftSoftkey;
    /// Own. Right softkey.
    HBufC* iRightSoftkey;
    
    /// Own. Single non-group label.
    HBufC* iNoteSingularLabel;
    /// Own. Plural non-group label.
    HBufC* iNotePluralLabel;
    /// Own. Single group label.
    HBufC* iGroupSingularLabel;
    /// Own. Plural group label.
    HBufC* iGroupPluralLabel;
    
	/// Own. Image data.
    HBufC8* iImageData;
    };

#endif // AKNDYNAMICSOFTNOTIFICATIONDATA_H
