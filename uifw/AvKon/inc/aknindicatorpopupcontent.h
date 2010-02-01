/*
* Copyright (c) 2007,2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Content that is shown inside a universal status
*                indicator popup.
*
*/


#ifndef C_AKNINDICATORPOPUPCONTENT_H
#define C_AKNINDICATORPOPUPCONTENT_H

// INCLUDES

#include <AknControl.h>

// FORWARD DECLARATIONS

class CAknIndicatorPopupItem;
class CAknIndicatorPlugin;
class CAknDigitalClock;
class CAknBatteryIcon;
class CAknSignalIcon;
class MTouchFeedback;

/**
*  Class providing content for the status indicator popup.
*
*  @lib avkon.lib
*  @since 5.0
*/
NONSHARABLE_CLASS( CAknIndicatorPopupContent ) : public CAknControl
    {
public:

    /**
    * Control event types sent by the content to the parent.
    */
    enum TAknIndicatorPopupEvent
        {
        /**
        * Event sent for closing the popup when a link item is tapped.
        */
        EAknIndicatorPopupTapEvent = 0x11
        };

public:

    /**
    * Two-phased constructor.
    *
    * @return  New instance of @c CAknIndicatorPopupContent.
    */
    static CAknIndicatorPopupContent* NewL();

    /**
    * Two-phased constructor, which leaves the created instance
    * on the cleanup stack.
    *
    * @return  New instance of @c CAknIndicatorPopupContent.
    */
    static CAknIndicatorPopupContent* NewLC();

    /**
    * Destructor.
    */
    ~CAknIndicatorPopupContent();

public: // From base class @c CCoeControl.

    /**
    * Returns the minimum size of the control.
    *
    * @return  Minimum size.
    */
    virtual TSize MinimumSize();

    /**
    * Handles changes to the control's resources.
    *
    * @aParam  aType  Type of resource change.
    */
    virtual void HandleResourceChange( TInt aType );

    /**
    * Handles pointer events.
    *
    * @param  aPointerEvent  The pointer event.
    */
    virtual void HandlePointerEventL( const TPointerEvent& aPointerEvent );

    /**
    * Returns the amount of component controls.
    *
    * @return  The component control count.
    */
    virtual TInt CountComponentControls() const;

    /**
    * Returns the pointer to a component control.
    *
    * @param   aIndex  Index of the component control.
    *
    * @return  The component control.
    */
    virtual CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
    * Sets the container window of the control.
    *
    * @param  aContainer  The container window.
    */
    virtual void SetContainerWindowL( const CCoeControl& aContainer );

public: // New methods.

    /**
    * Adds an indicator item to the popup.
    *
    * @param  aIndicatorUid  UID of the indicator to be added.
    * @param  aText          Text to be displayed with the indicator icon.
    * @param  aTextType      Type of the text (link or description).
    * @param  aIcon          Indicator icon, default icon used if @c NULL.
    * @param  aPlugin        Pointer to the indicator's ECOM plugin.
    * @param  aPriority      Priority of the item, items of lowest priority
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
    * Indicate the content about the visibility of the popup.
    *
    * @param  aVisible  @c ETrue if the content is visible,
    *                   @c EFalse otherwise.
    */
    void SetContentVisible( TBool aVisible );
    
    /**
    * Sets the battery indicator state.
    *
    * @param  aState  New battery indicator state.
    */
    void SetBatteryStateL( TInt aState );
    
    /**
    * Sets the signal indicator state.
    *
    * @param  aState  New signal indicator state.
    */
    void SetSignalStateL( TInt aState );

    /**
    * Updates the indicator's text and icon on the popup.
    * Called by the indicator ECOM plugins when they wish
    * to update the indicator item on the popup.
    *
    * @param  aUid  UID of the indicator to be updated.
    */
    void HandlePluginUpdateL( TInt aUid );

    /**
    * Updates the text and icon shown on the popup for all active indicators.
    * Called by the framework when the popup is shown to ensure
    * valid data on the popup.
    */
    void UpdateAllIndicatorsL();

private:

    /**
    * Default constructor.
    */
    CAknIndicatorPopupContent();

    /**
    * 2nd phase constructor.
    */
    void ConstructL();

    /**
    * Sorts the indicators items array in priority order.
    */
    void PrioritizeIndicatorsL();

    /**
    * For supporting area registry -based Tactile Feedback.
    */
    void UpdateFeedbackAreas();

    /**
    * Updates the graphics used by the popup
    * when active skin is changed.
    */
    void LoadIconsL();

    /**
     * Which popup item get pointer event? It has to be 
     * EAknIndicatorPluginLinkText type.
     *
     * @param aPoint position of the pointer event.
     * @return a pointer of item, NULL means no item get pointer event.
     */
    CAknIndicatorPopupItem* TappedItem(const TPoint& aPoint) const;
    

private: // From base class @c CCoeControl.

    /**
    * Sets new rect for the items
    */
    virtual void SizeChanged();

    /**
    * Draws the control, called by window server.
    *
    * @param  aRect  The region of the control to be redrawn.
    *                Co-ordinates are relative to the control's
    *                origin (top left corner).
    */
    virtual void Draw( const TRect& aRect ) const;

private: // Member data

    /**
    * Array which holds pointers to the indicator items.
    */
    RPointerArray<CAknIndicatorPopupItem> iItems;

    /**
    * Clock control.
    * Own.
    */
    CAknDigitalClock* iClock;
    
    /**
    * Battery icon control.
    * Own.
    */
    CAknBatteryIcon* iBattery;
    
    /**
    * Battery indicator plugin.
    * Own.
    */
    CAknIndicatorPlugin* iBatteryPlugin;
    
    /**
    * Signal icon control.
    * Own.
    */
    CAknSignalIcon* iSignal;

    /**
    * Signal indicator plugin.
    * Own.
    */
    CAknIndicatorPlugin* iSignalPlugin;

    /**
    * Touch responsive rectangle of the battery pane.
    */
    TRect iBatteryArea;
    
    /**
    * Touch responsive rectangle of the signal pane.
    */
    TRect iSignalArea;

    /**
    * Signal state.
    */
    TInt iSignalState;

    /**
    * Internal state flags.
    */
    TInt iFlags;

    /**
    * For Tactile Feedback support
    */
    MTouchFeedback* iFeedback;

    /**
    * Separator line graphics.
    * Own.
    */
    CGulIcon* iSeparatorIcon;

    /**
    * Switch of press down effect.
    */
    TBool iEnablePressedDownState;
    
    /**
    * Area of press down effect on signal.
    */
    TRect iSignalPressedDownArea;
    
    /**
    * Area of press down effect on clock.
    */
    TRect iClockPressedDownArea;
    
    /**
    * Previous pressed down item.
    * Not own.
    */
    CBase* iPreviousPressedDownItem;
    
    /**
    * Current rect of press down effect
    */
    TRect iPressedDownRect;
    };

#endif // C_AKNINDICATORPOPUPCONTENT_H
