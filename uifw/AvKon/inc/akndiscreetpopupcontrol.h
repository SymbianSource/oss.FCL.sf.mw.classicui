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
* Description:  Avkon discreet popup control
*
*/

#ifndef C_AKNDISCREETPOPUPCONTROL_H
#define C_AKNDISCREETPOPUPCONTROL_H

#include <AknControl.h>
#include <AknsConstants.h>
#include <babitflags.h>
#include <touchfeedback.h>


class CAknAppUi;
class CAknDiscreetPopupDrawer;
class CGulIcon;
class MEikCommandObserver;

/**
 *  Akn Discreet Popup control.
 *  Discreet popup actual control.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknDiscreetPopupControl ) : public CAknControl
    {

public:
    
    /**  Discreet popup control action definition */
    enum TAknDiscreetPopupAction
        {
        EAknDiscreetPopupShow = 1,
        EAknDiscreetPopupHide,
        EAknDiscreetPopupAnotherLaunched
        };

    /**
     * Two-phased constructor.
     *
     * @param aGlobal ETrue if global.
     * @param aTitle First line of text. 
     * @param aText Second line of text.
     * @param aIcon Icon.
     * @param aSkinId Icon skin item id.
     * @param aBitmapFile Icon bitmap file.
     * @param aBitmapId Icon bitmap id.
     * @param aMaskId Icon mask id.
     * @param aFlags Popup duration.
     * @param aCommand Popup command id.
     * @param aPopupId Popup id.
     * @param aCommandObserver Popup command observer.
     */
    IMPORT_C static CAknDiscreetPopupControl* NewL( 
        const TBool aGlobal,
        const TDesC& aTitle, 
        const TDesC& aText,
        CGulIcon* aIcon,
        const TAknsItemID& aSkinId,
        const TDesC& aBitmapFile,
        const TInt& aBitmapId,
        const TInt& aMaskId,
        const TInt& aFlags,
        const TInt& aCommand,
        const TInt& aPopupId,
        MEikCommandObserver* aCommandObserver );

    /**
     * Two-phased constructor.
     * 
     * @param aGlobal ETrue if global.
     * @param aResourceId Popup resource id.
     * @param aResourceFile Popup resource file.
     * @param aCommand Popup command id.
     * @param aPopupId Popup id.
     * @param aCommandObserver Popup command observer.
     */
    IMPORT_C static CAknDiscreetPopupControl* NewL( 
        const TBool aGlobal,
        const TInt& aResourceId,
        const TDesC& aResourceFile,
        const TInt& aCommand,
        const TInt& aPopupId,
        MEikCommandObserver* aCommandObserver );

    /**
     * Two-phased constructor.
     * 
     * @param aGlobal ETrue if global.
     * @param aTitle First line of text. 
     * @param aText Second line of text.
     * @param aIcon Icon.
     * @param aSkinId Icon skin item id.
     * @param aBitmapFile Icon bitmap file.
     * @param aBitmapId Icon bitmap id.
     * @param aMaskId Icon mask id.
     * @param aFlags Popup duration.
     * @param aCommand Popup command id.
     * @param aPopupId Popup id.
     * @param aCommandObserver Popup command observer.
     */
    static CAknDiscreetPopupControl* NewLC( 
        const TBool aGlobal,
        const TDesC& aTitle, 
        const TDesC& aText, 
        CGulIcon* aIcon, 
        const TAknsItemID& aSkinId,
        const TDesC& aBitmapFile,
        const TInt& aBitmapId,
        const TInt& aMaskId,
        const TInt& aFlags, 
        const TInt& aCommand,
        const TInt& aPopupId, 
        MEikCommandObserver* aCommandObserver );

    /**
     * Two-phased constructor.
     * 
     * @param aGlobal ETrue if global.
     * @param aCommand Popup command id.
     * @param aPopupId Popup id.
     * @param aCommandObserver Popup command observer.
     */
    static CAknDiscreetPopupControl* NewLC( 
        const TBool aGlobal,
        const TInt& aCommand,
        const TInt& aPopupId,
        MEikCommandObserver* aCommandObserver );

    /**
    * Destructor.
    */
    virtual ~CAknDiscreetPopupControl();

    /**
     * Handles discreet popup action.
     * 
     * @param aType Popup action type.
     *
     * @since S60 v5.2
     */
    IMPORT_C void HandleDiscreetPopupActionL( const TInt& aType );

    /**
     * Returns unique id of this popup control.
     *
     * @since S60 v5.2
     * @return Id of this popup control.
     */
    IMPORT_C TInt PopupId();

    /**
     * Timer callback.
     *
     * @since S60 v5.2
     * @param aObject
     * @return
     */
    static TInt TimeOut( TAny* aObject );

// from base class CAknControl

    /**
     * From CAknControl.
     * Sets this control as visible or invisible.
     *
     * @since S60 v5.2
     * @param aVisible ETrue to make the control visible, EFalse to make it invisible.
     */
    void MakeVisible( TBool aVisible );

private:

    /**
     * C++ constructor.
     */
    CAknDiscreetPopupControl( const TBool& aGlobal, 
                              const TInt& aFlags,
                              const TInt& aCommand,
                              const TInt& aPopupId, 
                              MEikCommandObserver* aCommandObserver );
 
    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Constructs the popup drawer.
     *
     * @param aTitleText First text row.
     * @param aBodyText Second text row.
     * @param aIcon Popup icon.
     * @param aSkinId Icon skin item id.
     * @param aBitmapFile Icon bitmap file.
     * @param aBitmapId Icon bitmap id.
     * @param aMaskId Icon mask id.
     */
    void ConstructDrawerL( const TDesC& aTitleText, 
                           const TDesC& aBodyText,
                           CGulIcon* aIcon,
                           const TAknsItemID& aSkinId = KAknsIIDNone,
                           const TDesC& aBitmapFile = KNullDesC,
                           const TInt& aBitmapId = 0,
                           const TInt& aMaskId = 0 );

    /**
     * Constructs the popup from resources.
     *
     * @param aResourceId Resource id.
     * @param aResourceFile Resource file.
     */
    void ConstructFromResourceL( 
            const TInt& aResourceId,
            const TDesC& aResourceFile );
            
    /**
     * Performs operations needed on timer callback.
     */
    void DoTimeOut();
        
    /**
     * Popup exit when popup is completely invisible.
     */
    void RequestExitL();

    /**
     * Notifies command observer of user command.
     */
    void NotifyObserverL();
    
    /**
     * Requests tactile feedback for popup.
     *
     * @param aType Feedback type.
     */
    void ImmediateFeedback( TTouchLogicalFeedback aType );

    /**
     * Updates popup window nonfading status.
     */
    void UpdateNonFadingStatus();

    /**
     * Sets pressed down state.
     * 
     * @param aPressedDown ETrue if popup is pressed-down.
     */
    void SetPressedDownState( const TBool& aPressedDown );

    /**
     * Shows the popup.
     */
    void ShowPopupL();

    /**
     * Hides the popup.
     */
    void HidePopup();

    /**
     * Provides app ui of this control.
     * 
     * @return AppUi.
     */
    CAknAppUi* AppUi();

    /**
     * Plays popup tone if one defined.
     */
    void PlayTone();

// from base class CAknControl

    /**
     * From CAknControl.
     * Constructs the control from a resource file.
     *
     * @since S60 v5.2
     * @param aReader The resource reader, with which to access the 
     * control's resource values.
     */
    void ConstructFromResourceL( TResourceReader &aReader );

    /**
     * From CAknControl.
     * Draws the control.
     *
     * @since S60 v5.2
     * @param aRect The region of the control to be redrawn.
     */
    void Draw( const TRect& aRect ) const;

    /**
     * From CAknControl.
     * Handles a change to the control's resources.
     *
     * @since S60 v5.2
     * @param aType A message UID value.
     */
    void HandleResourceChange( TInt aType );

    /**
     * From CAknControl.
     * Handles pointer events.
     *
     * @since S60 v5.2
     * @param aPointerEvent The pointer event. 
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

private: // data

    /**
     * The window group of the popup, if global.
     */
    RWindowGroup iWindowGroup;

    /**
     * Transparency factor. Between KAlphaMin and KAlphaMax.
     */
    TInt iAlpha;

    /**
     * Timer
     * Own.
     */
    CPeriodic* iTimer;

    /**
     * Popup flags.
     */
    TInt iFlags;
        
    /**
     * Command associated with this popup.
     */
    TInt iCommand;
    
    /**
     * Unique id of this popup.
     */
    TInt iPopupId;
        
    /**
     * Command observer.
     * Not own.
     */
    MEikCommandObserver* iCommandObserver;

    /**
     * Popup drawer.
     * Own.
     */
    CAknDiscreetPopupDrawer* iDrawer;
    
    /**
     * Internal control flags.
     */
    TBitFlags iInternalFlags;
    
    /**
     * Touch feedback instance.
     * Not own.
     */
    MTouchFeedback* iFeedBack;
    
    /**
     * Time stamp for tracking popup fade in / fade out.
     */
    TTime iFadeTime;
    
    };

#endif // C_AKNDISCREETPOPUPCONTROL_H
