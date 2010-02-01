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
* Description:  Discreet popup
*
*/

#ifndef C_AKNDISCREETPOPUP_H
#define C_AKNDISCREETPOPUP_H


#include <coemain.h>
#include <AknsConstants.h>
#include <coecobs.h>

class CAknDiscreetPopupControl;
class MEikCommandObserver;
class CGulIcon;
class CAknDiscreetPopupServerHandler;

/**
 * Discreet popup is used for notifying user of system generated or user 
 * activated events without blocking the flow of usage.
 *
 * The popup duration can be
 * 1) Short (by default). It is used when the user can expect a note to appear,
 * like confirmations, and when the nature of the message is positive,
 * i.e. the attempted operation was successful. The duration is 1.5 seconds.
 * 2) Long (KAknDiscreetPopupDurationLong flag). It is used when the note may 
 * appear spontaneously, i.e. without user action, or if the message content 
 * is not what the user probably expected (e.g. an error). 
 * The duration is 3.0 seconds. 
 *
 * @lib avkon
 * @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknDiscreetPopup ) : public CCoeStatic,
                                         public MCoeControlObserver
    {

public:

    /**
     * Destructor.
     */
    ~CAknDiscreetPopup();

    /**
     * Displays a local discreet popup which is created according 
     * to given parameters.Local discreet popup is an application-specific 
     * discreet popup that is visible when the parent application is active 
     * and visible. 
     *
     * Title text is the only compulsory parameter.
     * Icon can be provided either
     * 1) By providing CGulIcon object with aIcon parameter or
     * 2) By providing icon skin id and bitmap file information.
     * If CGulIcon object is provided, skin and bitmap information is ignored.
     * Popup can inform its command observer that it has been tapped 
     * through MEikCommandObserver interface.
     *
     * Possible discreet popup flags are:
     * 
     * KAknDiscreetPopupDurationLong for long discreet popup duration.
     * Default duration is short.
     * 
     * KAknDiscreetPopupConfirmationTone - popup plays the confirmation tone.
     * KAknDiscreetPopupWarningTone - popup plays the warning tone.
     * KAknDiscreetPopupErrorTone - popup plays the error tone.
     * By default no tone is played.
     * 
     * @since S60 v5.2
     * @param aTitle First line of text. 
     * @param aText Second line of text.
     * @param aIcon Icon.
     * @param aSkinId Icon skin item id.
     * @param aBitmapFile Icon bitmap file.
     * @param aBitmapId Icon bitmap id.
     * @param aMaskId Icon mask id.
     * @param aFlags Popup flags.
     * @param aCommand Popup command id.
     * @param aCommandObserver Popup command observer.
     * @return Unique id for popup. 
     * @panic EAknPanicNotSupported The method is called from application
     * without existing CCoeEnv.
     */
    IMPORT_C static TInt ShowLocalPopupL( 
        const TDesC& aTitle, 
        const TDesC& aText = KNullDesC, 
        CGulIcon* aIcon = NULL, 
        const TAknsItemID& aSkinId = KAknsIIDNone,
        const TDesC& aBitmapFile = KNullDesC,
        const TInt aBitmapId = 0,
        const TInt aMaskId = 0,
        const TInt aFlags = 0, 
        const TInt aCommand = 0, 
        MEikCommandObserver* aCommandObserver = NULL );

    /**
     * Displays a local discreet popup which is created according 
     * to given resource id.Local discreet popup is an application-specific
     * discreet popup that is visible when the parent application is active 
     * and visible. 
     *
     * Popup can inform its command observer that it has been tapped 
     * through MEikCommandObserver interface.
     * 
     * @param aResourceId Discreet popup resource id.
     * @param aCommand Popup command id.
     * @param aCommandObserver Popup command observer.
     * @return Unique id for popup. 
     * @panic EAknPanicNotSupported The method is called from application
     * without existing CCoeEnv.
     */
    IMPORT_C static TInt ShowLocalPopupL( 
        const TInt aResourceId, 
        const TInt aCommand = 0, 
        MEikCommandObserver* aCommandObserver = NULL );

    /**
     * Displays a global discreet popup which is created according 
     * to given parameters. Global discreet notifications remains 
     * visible when user navigates from application to another. 
     *
     * Title text is the only compulsory parameter.
     *
     * Possible discreet popup flags are:
     * 
     * KAknDiscreetPopupDurationLong for long discreet popup duration.
     * Default duration is short.
     * 
     * KAknDiscreetPopupConfirmationTone - popup plays the confirmation tone.
     * KAknDiscreetPopupWarningTone - popup plays the warning tone.
     * KAknDiscreetPopupErrorTone - popup plays the error tone.
     * By default no tone is played.
     * 
     * Note: If caller does not have an existing control environment (CCoeEnv),
     * CAknDiscreetPopup::InitL should be called to initialize discreet popup
     * before calling this method. In addition, CAknDiscreetPopup::Release
     * should be called when there is no need for discreet popup anymore.
     * Otherwise all allocated resources will not be freed.
     *
     * @since S60 v5.2
     * @param aTitle First line of text. 
     * @param aText Second line of text.
     * @param aSkinId Icon skin item id.
     * @param aBitmapFile Icon bitmap file.
     * @param aBitmapId Icon bitmap id.
     * @param aMaskId Icon mask id.
     * @param aFlags Popup flags.
     * @param aCommand Popup command id.
     * @param aCommandObserver Popup command observer.
     * @param aAppUid Application uid to be launched.
     * @param aViewUid Application view uid to be activated.
     * @return Unique id for popup. 
     */
    IMPORT_C static TInt ShowGlobalPopupL( 
        const TDesC& aTitle, 
        const TDesC& aText = KNullDesC, 
        const TAknsItemID& aSkinId = KAknsIIDNone,
        const TDesC& aBitmapFile = KNullDesC,
        const TInt aBitmapId = 0,
        const TInt aMaskId = 0,
        const TInt aFlags = 0,
        const TInt aCommandId = 0,
        MEikCommandObserver* aCommandObserver = NULL,
        const TUid& aAppUid = TUid::Null(),
        const TUid& aViewUid = TUid::Null() );

    /**
     * Displays a global discreet popup which is created according 
     * to given resource id. Global discreet notifications remains 
     * visible when user navigates from application to another.
     * 
     * Note: If caller does not have an existing control environment (CCoeEnv),
     * CAknDiscreetPopup::InitL should be called to initialize discreet popup
     * before calling this method. In addition, CAknDiscreetPopup::Release
     * should be called when there is no need for discreet popup anymore.
     * Otherwise all allocated resources will not be freed.
     *
     * @since S60 v5.2
     * @param aResourceId Discreet popup resource id.
     * @param aResourceFile Discreet popup resource file path.
     * @param aCommand Popup command id.
     * @param aCommandObserver Popup command observer.
     * @param aAppUid Application uid to be launched.
     * @param aViewUid Application view uid to be activated.
     * @return Unique id for popup. 
     */
    IMPORT_C static TInt ShowGlobalPopupL( 
        const TInt aResourceId,
        const TDesC& aResourceFile,
        const TInt aCommandId = 0,
        MEikCommandObserver* aCommandObserver = NULL,
        const TUid& aAppUid = TUid::Null(),
        const TUid& aViewUid = TUid::Null() );

    /**
     * Initializes discreet popup when discreet popup
     * is launched in application with no existing CCoeEnv.
     * Note: This method is intended only for usage of those applications
     * that do not have an existing control environment (CCoeEnv) and should
	 * be called only once.
     * 
     * @panic EAknPanicNotSupported 
     * The method is called from application with existing CCoeEnv.
     */
    IMPORT_C static void InitL();

    /**
     * Releases discreet popup resources when discreet popup
     * is launched in application with no existing CCoeEnv.
     * Note: This method is intended only for usage of those applications
     * that do not have an existing control environment (CCoeEnv) and should
	 * be called only once when the application terminates.
     * 
     * @panic EAknPanicNotSupported 
     * The method is called from application with existing CCoeEnv.
     */
    IMPORT_C static void Release();

private:

    /**
     * C++ constructor.
     */
    CAknDiscreetPopup();

    /**
     * C++ constructor.
     */
    CAknDiscreetPopup( TBool aUseCoeEnv );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Provides the discreet popup singleton.
     *
     * @return Discreet popup instance.
     */
    static CAknDiscreetPopup* InstanceL();

    /**
     * Launches the local popup.
     *
     * @param aTitle First line of text. 
     * @param aText Second line of text.
     * @param aIcon Icon.
     * @param aSkinId Icon skin item id.
     * @param aBitmapFile Icon bitmap file.
     * @param aBitmapId Icon bitmap id.
     * @param aMaskId Icon mask id.
     * @param aFlags Popup flags.
     * @param aCommand Popup command id.
     * @param aCommandObserver Popup command observer.
     * @return Unique id for popup. 
     */
    TInt DoShowLocalL( 
        const TDesC& aTitle, 
        const TDesC& aText, 
        CGulIcon* aIcon, 
        const TAknsItemID& aSkinId,
        const TDesC& aBitmapFile,
        const TInt& aBitmapId,
        const TInt& aMaskId,
        const TInt& aFlags, 
        const TInt& aCommand, 
        MEikCommandObserver* aCommandObserver );

    /**
     * Launches the local popup, if the queues are empty. 
     * If not, the popup is added to a queue.
     *
     * @param aResourceId Discreet popup resource id.
     * @param aCommand Popup command id.
     * @param aCommandObserver Popup command observer.
     * @return Unique id for popup.
     */
    TInt DoShowLocalL( 
        const TInt& aResourceId, 
        const TDesC& aResourceFile,
        const TInt& aCommand,
        MEikCommandObserver* aCommandObserver );

    /**
     * Launches the global popup.
     *
     * @param aTitle First line of text. 
     * @param aText Second line of text.
     * @param aSkinId Icon skin item id.
     * @param aBitmapFile Icon bitmap file.
     * @param aBitmapId Icon bitmap id.
     * @param aMaskId Icon mask id.
     * @param aFlags Popup flags.
     * @param aCommand Popup command id.
     * @param aCommandObserver Popup command observer.
     * @param aAppUid Application uid to be launched.
     * @param aViewUid Application view uid to be activated.
     * @return Unique id for popup.
     */

    TInt DoShowGlobalL( 
        const TDesC& aTitle, 
        const TDesC& aText, 
        const TAknsItemID& aSkinId,
        const TDesC& aBitmapFile,
        const TInt& aBitmapId,
        const TInt& aMaskId,
        const TInt& aFlags,
        const TInt& aCommandId,
        MEikCommandObserver* aCommandObserver,
        const TUid& aAppUid,
        const TUid& aViewUid );

    /**
     * Launches the global popup.
     *
     * @param aResourceId Discreet popup resource id.
     * @param aResourceFile Discreet popup resource file path.
     * @param aCommand Popup command id.
     * @param aCommandObserver Popup command observer.
     * @param aAppUid Application uid to be launched.
     * @param aViewUid Application view uid to be activated.
     * @return Unique id for popup.
     */

    TInt DoShowGlobalL(
        const TInt& aResourceId,
        const TDesC& aResourceFile,
        const TInt& aCommandId,
        MEikCommandObserver* aCommandObserver,
        const TUid& aAppUid,
        const TUid& aViewUid );

    /**
     * This method shows the created popup control.
     *
     * @param aControl Created popup control.
     */
    void ShowPopupL( CAknDiscreetPopupControl* aControl );

    /**
     * This method deletes the popup and removes it from 
     * CAknDiscreetPopup popup list.
     *
     * @param aControl Closed popup control.
     */
    void DeletePopup( CAknDiscreetPopupControl* aControl );

    /**
     * Returns next available popup id.
     * 
     * @return Next available popup id.
     */
    TInt NextPopupId();

    /**
     * Checks if popup id is already in use among local popups.
     * 
     * @return ETrue if popup id is already in use.
     */
    TBool PopupIdInUse( const TInt& aPopupId );

// from base class MCoeControlObserver

    /**
     * Handles an event from an observed control.
     *
     * @param aControl The control that sent the event.
     * @param aEventType The event type. 
     */
    void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );

private: // data

    /**
     * Local popup array.
     */
    RPointerArray<CAknDiscreetPopupControl> iLocalPopups;
    
    /**
     * Ui server handler.
     * Own. 
     */
    CAknDiscreetPopupServerHandler* iServerHandler;

    /**
     * ETrue if CoeEnv exists.
     */
    TBool iUseCoeEnv;
    };


#endif // C_AKNDISCREETPOPUP_H
