/*
* Copyright (c) 2007-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface for controlling the universal status
*                indicator popup.
*
*/


#ifndef C_AKNINDICATORPOPUP_H
#define C_AKNINDICATORPOPUP_H

// INCLUDES

#include <e32base.h>
#include <coecobs.h> // MCoeControlObserver

// FORWARD DECLARATIONS

class CAknPreviewPopUpController;
class MAknPreviewPopUpObserver;
class CAknIndicatorPopupContent;
class CAknIndicatorPlugin;

/**
*  Universal status indicator popup.
*
*  A floating popup containing information about the active status
*  indicators and possibly links associated with the indicators.
*  Links are activated via touch UI.
*
*  @lib avkon.lib
*  @since 5.0
*/
NONSHARABLE_CLASS( CAknIndicatorPopup ) : public CBase,
                                          public MCoeControlObserver
    {
public:

    /**
    * Two-phased constructor.
    *
    * @return New instance of @c CAknIndicatorPopup.
    */
    static CAknIndicatorPopup* NewL();

    /**
    * Two-phased constructor, which leaves the created instance
    * on the cleanup stack.
    *
    * @return New instance of @c CAknIndicatorPopup.
    */
    static CAknIndicatorPopup* NewLC();

    /**
    * Destructor.
    */
    ~CAknIndicatorPopup();

    /**
    * Shows the popup.
    * If it's already visible nothing happens.
    */
    void ShowPopup();

    /**
    * Hides the popup.
    */
    void HidePopup();

    /**
    * Sets the position of the popup.
    *
    * @param  aPoint  Top-right position of the popup.
    */
    void SetPosition( const TPoint& aPoint );
    /**
    * Sets the bottom-right position of the popup.
    *
    * This method should be used instead of @c SetPosition to set the popup
    * position in layouts in which the universal indicator popup is populated
    * from bottom up (i.e. when the universal indicator pane and small digital
    * clock pane are located on the bottom of the screen and the universal
    * indicator popup grows upwards when indicators are added to it.
    *
    * @param  aPoint  Bottom-right position of the popup.
    */
    void SetBottomPosition( const TPoint& aPoint );

    /**
    * Sets the signal icon of the popup to correspond 
    * the signal state.
    *
    * @param  aState  New signal indicator state.
    */
    void SetSignalStateL( TInt aState );
    
    /**
    * Sets the battery icon of the popup to correspond 
    * the battery state.
    *
    * @param  aState  New battery indicator state.
    */
    void SetBatteryStateL( TInt aState );
    
    /**
    * Adds an indicator item to the popup.
    *
    * @param  aIndicatorUid  UID of the indicator to be added.
    * @param  aText          Text to be displayed with the indicator icon.
    * @param  aTextType      Type of the text (link or description).
    * @param  aIcon          Indicator icon, default icon used if @c NULL.
    * @param  aPlugin        Pointer to the indicator's ECOM plugin.
    * @param  aPriority      Priority of the item. Items of lowest priority
    *                        value will be shown in the popup if all
    *                        of them do not fit.
    */
    void AddItemL( TInt aIndicatorUid,
                   const TDesC& aText,
                   TInt aTextType,
                   const CGulIcon* aIcon,
                   CAknIndicatorPlugin* aPlugin,
                   TInt aPriority );

    /**
    * Removes an indicator item from the popup.
    *
    * @param  aIndicatorUid  UID of the indicator to be removed.
    */
    void RemoveItem( TInt aIndicatorUid );

    /**
    * Informs the popup content about visibility change.
    *
    * @param  aVisible  @c ETrue if the popup is visible,
    *                   @c EFalse otherwise.
    */
    void SetContentVisible( TBool aVisible );

    /**
    * Sets the observer which handles the events received from
    * the preview popup controller of this popup.
    *
    * @param  aObserver  Reference to the observer.
    */
    void SetObserverL( const MAknPreviewPopUpObserver& aObserver );

    /**
    * Removes the observer of the preview popup controller.
    *
    * @param  aObserver  Reference to the observer.
    */
    void RemoveObserver( const MAknPreviewPopUpObserver& aObserver );

    /**
    * Gets pointer to the preview popup controller.
    *
    * @return  The preview popup controller.
    */
    const CAknPreviewPopUpController* Controller() const;

    /**
    * Updates the data shown on the popup for the specified indicator.
    *
    * @param aIndicatorUid  UID of the indicator to be updated.
    */
    void UpdatePopupIndicatorL( TInt aIndicatorUid );

    /**
    * Updates the data shown on the popup for all active indicators.
    */
    void UpdateAllPopupIndicatorsL();

public: // From base class @c MCoeControlObserver.

    /**
    * Handles events received from the content.
    *
    * @param  aControl    The control that sent the event.
    * @param  aEventType  The event type.
    */
    virtual void HandleControlEventL( CCoeControl* aControl,
                                      TCoeEvent aEventType );

private:

    /**
    * Default constructor.
    */
    CAknIndicatorPopup();

    /**
    * 2nd phase constructor.
    */
    void ConstructL();

private: // Member data

    /** Top-left corner of the popup. */
    TPoint iPosition;

    /**
    * Controller for the actual popup.
    * Own.
    */
    CAknPreviewPopUpController* iController;

    /**
    * Content of the popup.
    * Own.
    */
    CAknIndicatorPopupContent* iContent;
    };

#endif // C_AKNINDICATORPOPUP_H
