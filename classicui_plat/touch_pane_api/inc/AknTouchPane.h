/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  File contains the concrete touch pane class.
*
*/



#ifndef AKNTOUCHPANE_H
#define AKNTOUCHPANE_H

#include <coecntrl.h>
#include <babitflags.h>
#include <AknWsEventObserver.h>

class CAknAppUi;
class CAknButton;
class MAknTouchPaneObserver;
class CAknsBasicBackgroundControlContext;
class CAknsFrameBackgroundControlContext;
class MAknFepPenSupportInterface;
class TAknTouchPaneItem;

// have been deprecated

/**
*  CAknTouchPane.
*
*  @lib eikcoctl.lib
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CAknTouchPane  ) : public CCoeControl,
                                      public MCoeControlObserver,
                                      public MCoeControlBackground,
                                      public MAknWsEventObserver
    {

public:

    /** Touch pane visibility mode. */
    enum TVisibilityMode
        {
        /** The visiblity is automatically updated whenever the visibility
            or resource ID of status pane is changed. The touch pane is set
            visible only when compatible status pane is visible. */
        EAutomaticVisibilityChanges = 1,
        /** The visibility is not automatically changed, and user can set
            the visibility with @c MakeVisible() method. */
        EManualVisibilityChanges = 2
        };

    /**
    * Two-phased constructor.
    */
    IMPORT_C static CAknTouchPane* NewL();

    /**
     * Two-phased constructor. Construct the touch pane from the specified
     * resource.
     * @param aResourceId Resource ID specifying the resource.
     */
    IMPORT_C static CAknTouchPane* NewL( TInt aResourceId );

    /**
     * Destructor.
     */
    ~CAknTouchPane();

    /**
     * Reduces the given rectangle from the side that overlaps with
     * touch pane.
     * @param aBoundingRect Rectangle to be modified.
     */
    IMPORT_C void ReduceRect( TRect& aBoundingRect ) const;

    /**
     * Sets the touch pane's observer.
     * @param aObserver Observer.
     */
    IMPORT_C void SetObserver( MAknTouchPaneObserver* aObserver );

    /**
     * Sets the visibility mode. By default, the automatic visibility changes
     * are enabled, which means that the touch pane visibility is updated
     * whenever the visibility or resource ID of status pane is changed.
     * @param aMode Visibility mode.
     */
    IMPORT_C void SetVisibilityMode( TVisibilityMode aMode );

    /**
     * Allows input method activation. This method is called by the FEP to
     * set the input method icon dimmed, when input method activation is
     * not allowed, and to not dimmed, when input method activation is
     * allowed.
     * @param aValue ETrue to allow input method activation, EFalse to
     *   disallow it.
     */
    IMPORT_C void AllowInputMethodActivation( TBool aValue );

    /**
     * Changes the state of the input method icon. This method is called by
     * the FEP, when the touch input window is opened or closed. 
     * @param aActivated ETrue to change the state of the icon to activated
     *   (pressed down), EFalse to change it back to normal state.
     */
    IMPORT_C void SetInputMethodIconActivated( TBool aActivated );

    /**
     * Refreshes touch pane icons. This method is called by the framework,
     * whenever application gains foreground or new application view is
     * activated. Applications should call this, when touch pane has to
     * change the state of some of its icons, for example, when the help
     * context of application changes so that the dimming of help icon
     * has to be switched.
     */
    IMPORT_C void RefreshL();

    /**
     * Sets the interface, which is used by the touch pane to activate
     * and to deactivate input method window. Recurring calls will replace
     * the previously used interface with the new one. The ownership of
     * the interface is not transferred.
     * @param aFepPenSupportInterface Interface to FEP, which can be used
     *   to activate and deactivate input method window.
     */
    IMPORT_C void SetFepPenSupportInterface(
        MAknFepPenSupportInterface* aFepPenSupportInterface );

    /**
     * Handles status pane size change.
     * This method is called from status pane whenever it changes its size
     * as a result of resource change or visibility change.
     */
    void HandleStatusPaneSizeChange( TInt aInitialResourceId,
        TInt aLastRequestedResourceId );

// from base classes

    /**
     * From CCoeControl. Returns number of controls inside the control.
     * @return Number of component controls.
     */
    IMPORT_C TInt CountComponentControls() const;

    /**
     * From CCoeControl. Returns a control determined by control index.
     * @param anIndex Index of a control to be returned.
     * @return Pointer to control.
     */
    IMPORT_C CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
     * From MCoeControlBackground. Draw the background for a given control.
     * The method is intented to be called by the component controls fo touch
     * pane to draw their backgrounds.
     * @param aGc Graphics context used for drawing.
     * @param aControl The control being drawn.
     * @param aRect The area to be redrawn.
     */
    IMPORT_C void Draw( CWindowGc& aGc, const CCoeControl& aControl,
        const TRect& aRect ) const;

    /**
     * From MCoeControlObserver. Handles an event from an observed control.
     * @param aControl The control that sent the event.
     * @param aEventType The event type.
     */
    IMPORT_C void HandleControlEventL( CCoeControl *aControl,
        TCoeEvent aEventType );

    /**
     * From CCoeControl. Handles a change to the control's resources.
     * @param aType A message UID value.
     */
    IMPORT_C void HandleResourceChange( TInt aType );

    /**
     * From CCoeControl. Sets the control visible or invisible.
     * @param aVisible ETrue to make the control visible, EFalse to
     *   to make control invisible.
     */
    IMPORT_C void MakeVisible( TBool aVisible );

    /**
     * From CCoeControl. Handles key events.
     * @param aKeyEvent The key event.
     * @param aType The type of key event.
     * @return Indicates whether or not the key event was used by this
     *    control.
     */
    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
        TEventCode aType );

    /**
     * From MAknWsEventObserver. Handles window server events.
     */
    void HandleWsEventL( const TWsEvent& aEvent, CCoeControl* aDestination );

protected:

// from base classes

    /**
     * From CCoeControl. Handles pointer events.
     */
    IMPORT_C void HandlePointerEventL( const TPointerEvent &aPointerEvent );

    /**
     * From CCoeControl. Responds to changes in the position of a control. 
     */
    IMPORT_C void PositionChanged();

    /**
     * From CCoeControl. Sets the size and position of the components.
     */
    IMPORT_C void SizeChanged();

private:

    /**
     * C++ default constructor.
     */
    CAknTouchPane();

    /**
     * Symbian 2nd phase constructor.
     */
    void ConstructL( RArray<TAknTouchPaneItem>& aItems );

    // Activates application shell.
    void ActivateApplicationShellL();
    // Activates application swapper.
    void ActivateFastSwapL() const;
    // Activated idle view.
    void ActivateIdleViewL() const;
    // Rotates the screen.
    void RotateScreenL() const;
    // Activates/deactivates stylus input.
    void ActivateStylusInputL( TBool aActivate ) const;
    // Activates/deactivates popup toolbar.
    void ActivateToolbarL( TBool aActivate ) const;
    // Activates/deactivate help.
    void ActivateHelpL( TBool aActivate );
    // Activates/deactivates dialler.
    void ActivateDiallerL( TBool aActivate );
    // Activates/deactivates contacts.
    void ActivateContactsL( TBool aActivate );

    // Creates the specified touch pane component.
    CAknButton* ConstructDefaultComponentL( TInt aId );
    // Notifies the observer of a change in touch pane's size or position.
    void ReportSizeChange() const;
    // Sets the required properties for control to be touch pane's component. 
    void SetDefaultPropertiesL( CCoeControl* aControl );
    // Sets the size and position of touch pane's window from layout data.
    void SetWindowLayout();
    // Registers the positions of component controls.
    void RegisterControlPositions() const;
    // Removes the registered positions of component controls.
    void DeregisterControlPositions() const;
    // Updates buttons.
    void DoRefresh();

// from base classes
    
    /**
     * From CCoeControl. Draws the control.
     */
    void Draw( const TRect& aRect ) const;

private: // Data

    CAknAppUi* iAppUi; // not owned

    // Component controls
    CAknButton* iShellIcon;
    CAknButton* iSwapperIcon;
    CAknButton* iIdleViewIcon;
    CAknButton* iDiallerIcon;
    CAknButton* iRotateIcon;
    CAknButton* iHelpIcon;
    CAknButton* iInputMethodIcon;
    CAknButton* iToolbarIcon;
    CAknButton* iContactsIcon;

    // Touch pane's observer
    MAknTouchPaneObserver* iObserver; // not owned

    // Background control context
    CAknsBasicBackgroundControlContext* iBgContext;

    // Frame control context
    CAknsFrameBackgroundControlContext* iFrameContext;

    // Interface for activating/deactivating input method
    MAknFepPenSupportInterface* iFepPenSupportInterface; // not owned

    // UID of the application owning the touch pane
    TUid iUid;

    // Flags
    TBitFlags32 iFlags;

    };

#endif // AKNTOUCHPANE_H  

// End of File
