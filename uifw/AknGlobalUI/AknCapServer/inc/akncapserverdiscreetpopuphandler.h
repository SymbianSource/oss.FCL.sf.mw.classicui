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
* Description: Avkon cap server discreet popup handler
*
*/

#ifndef C_AKNCAPSERVERDISCREETPOPUPHANDLER_H
#define C_AKNCAPSERVERDISCREETPOPUPHANDLER_H

#include <coecobs.h>
#include <coemain.h>
#include <eikcmobs.h>

class CAknDiscreetPopupControl;

/**
 * Data storage class for cap server discreet popup data.
 */
NONSHARABLE_CLASS( TAknCapServerDiscreetPopupData )
    {

public:

    /**
     * Cap server command id.
     */
    TInt iCommandId;

    /**
     * App uid to be launched.
     */
    TUid iAppUid;

    /**
     * View uid to be activated.
     */
    TUid iViewUid;

    /**
     * Discreet popup control.
     */
    CAknDiscreetPopupControl* iPopupControl;

    /**
     * Server message.
     */
    RMessagePtr2 iMessage;

    };


/**
 * Avkon cap server discreet popup handler takes care of showing
 * global discreet popups.
 */
NONSHARABLE_CLASS( CAknCapServerDiscreetPopupHandler )
    : 
    public CCoeStatic, 
    public MEikCommandObserver, 
    public MCoeControlObserver
    {

public:

    /**
     * Destructor.
     */
    ~CAknCapServerDiscreetPopupHandler();

    /**
     * Handles discreet popup message received by cap server.
     * 
     * @param aMessage Server message.
     */
    static void HandleDiscreetPopupMessageL( const RMessage2& aMessage );

    /**
     * Creates AknCapServerDiscreetPopupHandler.
     * 
     */
    static void CreateDiscreetPopupHandlerL();

private:

    /**
     * C++ constructor.
     */
    CAknCapServerDiscreetPopupHandler();

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Provides the discreet popup handler singleton.
     *
     * @return Discreet popup handler instance.
     */
    static CAknCapServerDiscreetPopupHandler* InstanceL();

    /**
     * Handles discreet popup message received by cap server.
     *
     * @param aMessage Server message.
     */
    void DoHandleDiscreetPopupMessageL( const RMessage2& aMessage );

    /**
     * Launches global discreet popup defined in resources.
     *
     * @param aMessage Server message.
     */
    void LaunchFromResourceL( const RMessage2& aMessage );

    /**
     * Launches global discreet popup defined with parameters.
     *
     * @param aMessage Server message.
     */
    void LaunchWithParamsL( const RMessage2& aMessage );

    /**
     * Handles request cancellation.
     *
     * @param aMessage Server message.
     */
    void HandleRequestCancellationL( const RMessage2& aMessage );

    /**
     * Handles query in user global discreet popup rect
     * 
     * @param aMessage Server message.
     */    
    void HandleQueryInUseRect( const RMessage2& aMessage );
    
    /**
     * Shows popup.
     *
     * @param aCommandId Popup command id.
     * @param aPopup Popup control.
     * @param aAppUid Application uid.
     * @param aViewUid View uid.
     * @param aMessage Server message.
     */
    void ShowPopupL( 
            const TInt& aCommandId,
            CAknDiscreetPopupControl* aPopup,
            const TUid& aAppUid,
            const TUid& aViewUid,
            const RMessage2& aMessage );

    /**
     * Provides the next available command id.
     *
     * @return Next available command id.
     */
    TInt NextAvailableCommandId();
    
    /**
     * Publish a RProperty indicates the running global discreet popup changed,
     * either new global discreet popup being displayed, or existing global dis-
     * creet popup quit
     * 
     * @since v5.2
     */
    void NotifyRunningGlobalDiscreetPopupChanged();

// from base class MEikCommandObserver

    /**
     * Processes user commands.
     *
     * @param aCommandId ID of the command to respond to.
     */
    void ProcessCommandL( TInt aCommandId );

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
     * Active popup's data.
     */
    RArray<TAknCapServerDiscreetPopupData> iPopupDataArray;

    /**
     * Cap server app ui.
     */
    CCoeAppUi* iAppUi;
    
    };


#endif // C_AKNCAPSERVERDISCREETPOPUPHANDLER_H
