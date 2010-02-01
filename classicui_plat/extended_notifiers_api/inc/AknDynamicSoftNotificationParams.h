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
* Description:  Parameter container class for dynamic softnotifications
*
*/

#ifndef AKNDYNAMICSOFTNOTIFICATIONPARAMS_H
#define AKNDYNAMICSOFTNOTIFICATIONPARAMS_H

// INCLUDES
#include <e32std.h>
#include <vwsdef.h>         // For TVwsViewId
#include <aknnotedialog.h>  // For CAknNoteDialog::TTone

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <vwsdefpartner.h>
#endif

// CLASS DECLARATION

/**
*  Parameter container class for dynamic soft notifications.
*
*  @lib AknNotifyPlugin.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS( TAknDynamicSoftNotificationParams )
    {
public: // constructor

    /**
     * Constructor.
     *
     * @param aPriority Priority of the soft notification. Priority has to be in
     *        range from 1000 (low) to 3000 (high). It's however strongly adviced
     *        to use priority only from range 1000...1300.
     * @param aTone Tone played by soft notification.
     */
    IMPORT_C TAknDynamicSoftNotificationParams(
        TInt aPriority,
        CAknNoteDialog::TTone aTone = CAknNoteDialog::ENoTone );
    
public: // new methods

    /**
     * Sets view activation parameters. Used when user accepts the soft
     * notification.
     * NOTE: Will not create internal copy of given data. (aCustomMsg)
     * 
     * @param aViewId Launched view when user accepts the soft note.
     * @param aPluralViewId Launched view when user accepts the soft note.
     *        If soft notification count > 1.
     *        If equal to KNullViewId -> aViewId is used.
     * @param aCustomMsgId Custom uid sent to launched view.
     * @param aCustomMsg   Custom data sent to launched view.
     */
    IMPORT_C void SetViewActivationParams(
        TVwsViewId aViewId,
        TVwsViewId aPluralViewId = KNullViewId,
        TUid aCustomMsgId = KNullUid,
        const TDesC8& aCustomMsg = KNullDesC8 );

    /**
     * Set custom softkeys for dynamic soft notification.
     * NOTE: Will not create internal copy of given data.
     * 
     * @param aLeftSoftkey Label for left softkey (default SHOW).
     * @param aRightSoftkey Label for right softkey (default EXIT).
     */
    IMPORT_C void SetSoftkeys(
        const TDesC& aLeftSoftkey,
        const TDesC& aRightSoftkey );
    
    /**
     * Set texts for ungrouped dynamic soft notification.
     * NOTE: Will not create internal copy of given data.
     * 
     * @param aSingularLabel Text shown on soft notification when count == 1.
     * @param aPluralLabel Text shown on soft notification when count > 1.
     */
    IMPORT_C void SetNoteLabels(
        const TDesC& aSingularLabel,
        const TDesC& aPluralLabel );

    /**
     * Set texts for grouped dynamic soft notification. If these labels are
     * not defined, the dynamic notification will not show in grouped view.
     * NOTE: Will not create internal copy of given data.
     * 
     * @param aSingularLabel Text shown on grouped notification when count == 1.
     * @param aPluralLabel Text shown on grouped notification when count > 1.
     */
    IMPORT_C void SetGroupLabels(
        const TDesC& aSingularLabel,
        const TDesC& aPluralLabel );
    
    /**
     * Set image/icon to be shown in non-grouped soft notification. The maximum
     * size for bitmap images is 300x300 pixels. Bigger images will be ignored.
     * NOTE: Will not create internal copy of given data.
     * 
     * @param aImageData Binary data for image/icon.
     */
    IMPORT_C void SetImageData( 
        const TDesC8& aImageData );

    /**
     * Enable observing of this dynamic soft notification.
     */
    IMPORT_C void EnableObserver();        

public: // Non-exported
    
    /**
     * Externalize internal state into stream.
     * 
     * @param aStream Destination stream.
     */
    void ExternalizeL( RWriteStream& aStream ) const;

private: // new methods

    /**
     * Externalize text into stream.
     * 
     * @param aStream Target stream.
     * @param aText Externalized text.
     */
    void ExternalizeTextL( RWriteStream& aStream, const TDesC16& aText ) const;

    /**
     * Externalize text into stream.
     * 
     * @param aStream Target stream.
     * @param aText Externalized text.
     */
    void ExternalizeTextL( RWriteStream& aStream, const TDesC8& aText ) const;

private: // data

    /// Soft notification priority.
	TInt iPriority;
	/// Tone played when soft note is shown.
    CAknNoteDialog::TTone iTone;

    /// Activated view when soft note is accepted.
    TVwsViewId iViewId;
    /// Activated view when soft note is accepted (count > 1).
    TVwsViewId iPluralViewId;
    /// Custom message uid to be delivered to new view.
    TUid iCustomMessageId;
    /// Custom data message to be delivered to new view.
    TPtrC8 iCustomMessage;

    /// Left softkey label.
    TPtrC iLeftSoftkey;
    /// Right softkey label.
    TPtrC iRightSoftkey;
    
	/// Soft notification text label.
	TPtrC iNoteSingularLabel;
    /// Soft notification text label (count > 1).
	TPtrC iNotePluralLabel;
    /// Soft notification text label in group form.
	TPtrC iGroupSingularLabel;
    /// Soft notification text label in group form (count > 1).
	TPtrC iGroupPluralLabel;

	/// Soft notification image data.
	TPtrC8 iImageData;
	
	/// Is this notification observed or not.
	TBool iEnableObserver;
	
	/// Reserved for future use.
	TAny* iReserved1;
    /// Reserved for future use.
    TAny* iReserved2;
    };

#endif // AKNDYNAMICSOFTNOTIFICATIONPARAMS
