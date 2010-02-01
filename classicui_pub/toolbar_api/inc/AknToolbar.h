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
* Description:  Popup toolbar component
*
*/



#ifndef __AKNTOOLBAR_H__
#define __AKNTOOLBAR_H__

//  INCLUDES
#include <avkon.hrh> // TAknOrientation
#include <AknControl.h> // CCoeControl
#include <coecobs.h>    // MCoeControlObserver
#include <eikcmobs.h>   // MEikCommandObserver
#include <AknPopupFader.h>
#include <babitflags.h>
#include <AknsItemID.h>

// FORWARD DECLARATIONS
class CAknButton;
class CAknToolbarItem;
class CAknToolbarExtension;
class MAknToolbarObserver;
class CEikButtonGroupContainer;
class TAknWindowComponentLayout;
class CAknsFrameBackgroundControlContext;
class CAknsBasicBackgroundControlContext;


// DisableToolbarL leaves with this value if toolbar is shown, since toolbar
// should not be shown when disabling/enabling toolbar. 
const TInt KErrToolbarShown = -101;   

// CLASS DECLARATION

/**
*  The class to provide toolbar for the application
*
*  @lib eikcoctl.lib
*  @since Series 60 3.1
*/
class CAknToolbar : public CAknControl, public MCoeControlObserver, 
    public MCoeControlBackground, public MEikCommandObserver, 
    public MAknFadedComponent
    {
    public: //Enumerations: 

    enum TEventModifiers {
        ELongPress = 1,
        ELongPressEnded = 2,
    };

    public: // Constructors and destructor

        /**
         * Two-phased constructor.
         *
         * @param aResourceId The ID for this component's resource
         * @return Pointer to the created toolbar object
         */
        IMPORT_C static CAknToolbar* NewL( const TInt aResourceId );

        /**
         * Two-phased constructor.
         *
         * @param aResourceId The ID for this component's resource
         * @return Pointer to the created toolbar object
         */
        IMPORT_C static CAknToolbar* NewLC( const TInt aResourceId );

        /**
         * Destructor
         */
        ~CAknToolbar();

    public: // From base class

        /**
         * From CCoeControl.
         * Gets the number of controls contained in a compound control.
         *
         * @return The number of component controls contained by this control.
         */
         IMPORT_C TInt CountComponentControls() const;

         /**
         * From CCoeControl.
         * Gets the specified component of a compound control.
         *
         * @param aIndex The index of the control to get
         * @return The component control with an index of aIndex.
         */
        IMPORT_C CCoeControl* ComponentControl( TInt aIndex ) const ;

        /**
         * From CCoeControl.
         * Handles pointer events.
         *
         * @param aPointerEvent The pointer event. 
         */
        IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );

        /**
         * From CCoeControl.
         * Handles a change to the control's resources.
         *
         * @param aType A message UID value.
         */
        IMPORT_C void HandleResourceChange( TInt aType );

        /**
         * From MCoeControlObserver.
         * Handles an event from an observed toolbar item.
         *
         * @param aControl The control which sent the event
         * @param aEventType The event type
         */
        IMPORT_C void HandleControlEventL( CCoeControl* aControl, 
                                           TCoeEvent aEventType );

        /**
         * From CCoeControl.
         * Responds to changes in the position of a toolbar.
         */
        IMPORT_C void PositionChanged();

        /**
         * From MEikCommandObserver.
         * Processes user commands.
         *
         * @param TInt aCommandId  ID of the command to respond to.
         */
        IMPORT_C void ProcessCommandL( TInt aCommandId );

        /**
         * From CCoeControl.
         * Sets toolbar dimmed. Doesn't redraw.
         *
         * @param aDimmed is ETrue to dim the toolbar, 
         *      EFalse to set the toolbar as not dimmed
         */
        IMPORT_C void SetDimmed( TBool aDimmed );

        /**
         * From CCoeControl.
         * Handles key events.
         *
         * @param aKeyEvent The key event
         * @param aType The type of key event: EEventKey, EEventKeyUp
         *      or EEventKeyDown.
         * @return TKeyResponse Indicates whether or not the key event was used
         *      by this control.
         */
        IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                              TEventCode aType );

        /**
         * From CCoeControl.
         * Gets the control's input capabilities.
         *
         * @return The control's input capabilities.
         */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;

        /**
         * From MCoeControlBackground.
         * Draw the background for a given control.
         * The text drawer that shall be used to draw text on the specific
         * background can be fetched through the GetTextDrawer() method.
         *
         * @param aGc Graphics context used for drawing.
         * @param aControl The control being drawn (may be a child of the drawer).
         * @param aRect The area to be redrawn.
         */
        IMPORT_C void Draw( CWindowGc& aGc,
                            const CCoeControl& aControl,
                            const TRect& aRect ) const;

    public: // New functions

        /**
         * Gets a pointer to the specified control.
         *
         * @param aControlId The ID of the control for which a pointer is
         *      required.
         * @return Pointer to the control with the specified ID.
         */
        IMPORT_C CCoeControl* ControlOrNull( const TInt aControlId ) const;

        /**
         * Shows or hides toolbar. Position of the top left corner should be set
         * in advance. Toolbar set visible with this method is by default focusing.
         * Does nothing if toolbar is disabled.
         * @param aVisible ETrue to show it, EFalse to hide it.
         */
        IMPORT_C void SetToolbarVisibility( const TBool aVisible );

        /**
        * Shows or hides toolbar. Position of the top left corner should be set
        * in advance. This overload of the method allows toolbar to be set
        * non-focusing. Does nothing if toolbar is disabled. 
        * @param aVisible ETrue to show it, EFalse to hide it.
        * @param aFocusing ETrue to set toolbar focusing, otherwise EFalse.
        */
        IMPORT_C void SetToolbarVisibility( const TBool aVisible, 
                                            const TBool aFocusing );

        /**
         * Dims (greys out) or undims a toolbar item.
         *
         * @param aCommandId The command (as defined in an .hrh file)
         *      associated with this toolbar item. This identifies the toolbar
         *      item, whose text is to be dimmed or un-dimmed.
         * @param aDimmed Use ETrue to dim this toolbar item or EFalse to
         *      un-dim this toolbar item.
         * @param aDrawNow Should be ETrue for the item to be redrawn.
         */
        IMPORT_C void SetItemDimmed( const TInt aCommandId,
                                     const TBool aDimmed,
                                     const TBool aDrawNow );

        /**
         * Hides or unhides a toolbar item.
         *
         * @param aCommandId The command (as defined in an .hrh file)
         *      associated with this toolbar item. This identifies the toolbar
         *      item, which will be set to hidden or unhidden.
         * @param aHide Use ETrue to hide this toolbar item or EFalse to
         *      unhide this toolbar item.
         * @param aDrawNow Should be ETrue for the toolbar to be redrawn.
         */
        IMPORT_C void HideItem( const TInt aCommandId,
                                const TBool aHide,
                                const TBool aDrawNow );

        /**
         * Sets the observer for the toolbar.
         *
         * @param aObserver A pointer to the observer. Ownership is not changed.
         */
        IMPORT_C void SetToolbarObserver( MAknToolbarObserver* aObserver );

        /**
         * Returns a pointer to the toolbar observer.
         *
         * @return Pointer to the toolbar observer.
         */
        IMPORT_C MAknToolbarObserver* ToolbarObserver();

        /**
         * Adds one item to the end of the toolbar. Takes ownership.
         * Leaves with value KErrNotSupported, if the control type is not
         * supported by toolbar (see CAknToolbar::IsSupportedItemType()).
         *
         * @param aItem The control.
         * @param aType The type of the new toolbar item.
         * @param aCommandId The command ID for this item.
         * @param aFlags The flags.
         */
        IMPORT_C void AddItemL( CCoeControl* aItem, 
                                const TInt aType, 
                                const TInt aCommandId, 
                                const TInt aFlags );

        /**
         * Adds one item to the specified place. Takes ownership.
         * Leaves with value KErrNotSupported, if the control type is not
         * supported by toolbar (see CAknToolbar::IsSupportedItemType()).
         *
         * @param aItem The control.
         * @param aType The type of the new toolbar item.
         * @param aCommandId The command ID for this item.
         * @param aFlags The flags.
         * @param aIndex The index in array at which item should be added.
         */
        IMPORT_C void AddItemL( CCoeControl* aItem,
                                const TInt aType,
                                const TInt aCommandId,
                                const TInt aFlags,
                                const TInt aIndex );

        /**
         * Removes one item from the toolbar.
         *
         * @param aCommandId The ID of the item which should be removed.
         */
        IMPORT_C void RemoveItem( const TInt aCommandId );

        /**
         * Returns ETrue if the type of the item can be included in the
         * toolbar.
         *
         * @return ETrue for the supported type, otherwise EFalse.
         */
        IMPORT_C TBool IsSupportedItemType( const TInt aType ) const;

        /**
         * Changes the command ID for the initially focused item when toolbar is
         * shown or gain focus. Notice that, if this item is not visible, then
         * focus will be according default behaviour. Normally, focus will be on
         * the first item, if KAknToolbarMiddleItemFocused flag was not used.
         *
         * @param aCommandId The command ID for the item to get focus.
         */
        IMPORT_C void SetInitialFocusedItem( const TInt aCommandId );

        /**
         * Called by the framework to handle the emphasising or
         * de-emphasising of a toolbar window when it is needed. 
         * 
         * @param aEmphasis ETrue to emphasize the menu, EFalse otherwise.
         */
        IMPORT_C void SetEmphasis( const TBool aEmphasis );

        /**
         * Returns toolbar visibility at this moment
         *
         * @return ETrue, if toolbar is shown.
         */
        IMPORT_C TBool IsShown() const;

        /**
         * Specifies whether toolbar should be shown with sliding effect or not.
         * By default toolbar is shown with sliding.
         *
         * @param aSlide ETrue for sliding effect, EFalse without sliding.
         */
        IMPORT_C void SetWithSliding( const TBool aSlide );

        /**
         * Sets whether the toolbar should be closed or remain open after the
         * specified command is issued from the toolbar.
         *
         * @param aCommandId The command.
         * @param aClose ETrue, if toolbar should be close.
         */
        IMPORT_C void SetCloseOnCommand( const TInt aCommandId,
                                         const TBool aClose );

        /**
         * Sets whether the toolbar should be closed after a command is issued
         * from the toolbar. This method affects every command on the toolbar.
         *
         * @param aClose ETrue, if toolbar should be closed.
         */
        IMPORT_C void SetCloseOnAllCommands( const TBool aClose );
        
        /**
         * Sets toolbar orientation.
         * 
         * @param aOrientation Orientation that should be used for toolbar.
         * @since 3.2
         */
        IMPORT_C void SetOrientation( const TAknOrientation aOrientation );
        
        /**
         * Updates transparent toolbar's background. 
         * @since 3.2
         */
        IMPORT_C void UpdateBackground();
         
        /**
         * Shows toolbar again after it has been hidden for background changing 
         * purposes
         * 
         * @since 3.2
         */
        void ShowToolbarForBackgroundUpdate(); 
        
        /**
         * Disables/Enables toolbar so that it cannot/can be activated from e.g. 
         * touch pane. Needed especially if a dialog is on the screen and 
         * toolbar is not wished to be shown. Leaves with value KErrToolbarShown
         * if called when toolbar is shown. 
         * 
         * @param aDisable ETrue if toolbar should be disabled 
         * 
         * @since S60 3.2
         */
        IMPORT_C void DisableToolbarL( TBool aDisable ); 

        /**
         * Checks if toolbar is disabled. 
         * 
         * @return ETrue if toolbar is disabled, EFalse if not 
         * 
         * @since S60 3.2
         */
        IMPORT_C TBool IsToolbarDisabled() const; 
        
        /**
         * Moves highlight from one item to another. Leaves with 
         * value KErrNotFound if item not found. 
         * 
         * @param aCommandId command id of the item to be focused.           
         * 
         * @since S60 3.2
         */
        IMPORT_C void SetFocusedItemL( const TInt aCommandId ); 

        /**
         * Returns command id of focused item. 
         * 
         * @return command id of focused item. Returns KErrNotFound if 
         * no item is focused. 
         * 
         * @since S60 3.2
         */
        IMPORT_C TInt FocusedItem() const; 

        /**
         * Takes focus away from edwin or other controls if needed. Called by 
         * AknAppUi from HandleWsEventL when a pointer event is targeted to 
         * other control than toolbar. 
         * 
         * @since S60 3.2
         */
        void PrepareForFocusLossL(); 

        /**
         * Returns event modifiers defined in TEventModifiers in this header. 
         * This can be used by applications in OfferToolbarEventL to know if 
         * the event sent was for example a long press event. Information is
         * valid only during OfferToolbarEventL. 
         * 
         * @return event modifiers
         * @since S60 3.2
         */
        IMPORT_C TInt EventModifiers() const; 

        /**
         * Returns the flags of toolbar. Flags are defined in eikon.hrh.  
         * @return toolbar flags
         * @since S60 3.2
         */
        IMPORT_C TInt ToolbarFlags() const; 

        /*
         * Count faded components
         * @return then number of faded components
         */
        TInt CountFadedComponents(); 

        /*
         * Returns faded components by index
         * @return faded component
         */
        CCoeControl* FadedComponent( TInt aIndex ); 

        /*
         * Reduces main pane rect if it intersects with toolbar's rect
         * @param aBoundingRect the rect to reduce
         */
        void ReduceRect( TRect& aBoundingRect ) const; 

        /**
         * Sets the resource id for toolbar softkeys. If cba allready exists 
         * then changes the existing softkeys and redraws toolbar cba.  
         * @param aSoftkeyResourceId ID of the resource structure specifying 
         * the command buttons.
         * @since S60 3.2
         */
        IMPORT_C void SetSoftkeyResourceIdL( TInt aSoftkeyResourceId ); 

        /**
         * Extension notifies of its events using this method
         * aCommandId command id of the button
         */
        void ExtensionEventL( TInt aCommandId ); 

        /**
         * Returns the index of the toolbar item inside of the iVisibleItems
         * array.
         *
         * @param aControl The control which index is needed.
         * @return Index of the toolbar item.
         */
        TInt ToolbarVisibleIndexByControl( const CCoeControl* aControl ) const;

        /**
         * Returns pointer to toolbar extension if available
         * @return toolbar extension or NULL
         */
        IMPORT_C CAknToolbarExtension* ToolbarExtension() const;  		

        /**
         * Calls DynInitToolbar with extensions commmand id
         * 
         */
        void DynInitExtensionL( CCoeControl* aControl ); 

        /**
         * Callback for sliding toolbar.
         */
        static TInt ReadyToSlide( TAny* aThis ); 

        /**
         * Slide toolbar
         */
        void SlideWithIdle(); 

        /**
         * Hides/Unhides toolbar items temporarily. When called with ETrue 
         * toolbar draws just background in landscape and is hidden in portrait. 
         * Calling with EFalse returns the situation to normal, so drawing the 
         * items normally in portrait and landscape. Use this method only with
         * fixed toolbar! 
         *  
         * @param aHide ETrue if hiding items, EFalse if unhiding.  
         */
        IMPORT_C void HideItemsAndDrawOnlyBackground( TBool aHide ); 

        /**
         * Hides/Unhides toolbar items temporarily. When called with ETrue
         * toolbar draws just background in landscape and is hidden in portrait. 
         * Toolbar window priority is changed to priority passed in parameter.
         * Priority should be one of the window priority values defined in 
         * TCoeWinPriority. Default priority is ECoeWinPriorityLow.
         * Note that if toolbar is already hidden, the toolbar window priority
         * is still changed to priority passed in parameter.
         * Calling the function HideItemsAndDrawOnlyBackground with EFalse returns
         * the situation to normal, so drawing the items normally in portrait 
         * and landscape. Use this method only with fixed toolbar! 
         *  
         * @param aHide ETrue if hiding items, EFalse if unhiding.
         * @param aPriority Ordinal priority of toolbar window.  
         */
        IMPORT_C void HideItemsAndDrawOnlyBackground( TBool aHide, TInt aPriority ); 
        /**
         * Sets the skin background for fixed toolbar. The new background is used 
         * for all the subsequent drawing operations. This method does not itself 
         * cause a repaint. 
         *
         * @internal     
         *
         * @param aIID Skin item ID of the new background. This is one of the constants
         *             defined in AknsConstants.h, and the usual values are KAknsIIDQsnBgScreen
         * @since S60 5.0
         */
        IMPORT_C void SetSkinBackgroundId( const TAknsItemID& aIID );


    protected: // From base class

        /**
         * From CCoeControl.
         * Responds to size changes to sets the size and position of 
         * the contents of this control.
         */
        IMPORT_C void SizeChanged();

        /**
         * From CCoeControl.
         * This function is called whenever a control gains or loses focus.
         *
         * @param aDrawNow Contains the value that was passed to it by SetFocus().
         */
        IMPORT_C void FocusChanged( TDrawNow aDrawNow );

        /**
         * From CAknControl.
         * For future extensions.
         *
         * @param aInterface The ID for the extension interface.
         */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

        /**
         * From CCoeControl.
         * Retrieves an object of the same type as that encapsulated in aId.
         *
         * @param aId An encapsulated object type ID.
         * @return Encapsulated pointer to the object provided. 
         *      Note that the encapsulated pointer may be NULL.
         */
        IMPORT_C TTypeUid::Ptr MopSupplyObject( TTypeUid aId );

    private: // Constructors

        /**
         * C++ default constructor.
         */
        CAknToolbar();

        /**
         * Symbian 2nd phase constructor.
         */
        void ConstructL();

    private: // From base class

        /**
         * From CCoeControl.
         * Constructs controls from a resource file.
         * Hides the one defined in base class.
         *
         * @param aReader The resource reader with which to access
         *      the control's resource values.
         */
        IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

        /**
         * From CCoeControl.
         * Draw a control called by window server.
         *
         * @param aRect The region of the control to be redrawn. 
         *      Co-ordinates are relative to the control's origin (top left corner).
         */
        IMPORT_C void Draw( const TRect& aRect ) const;

    private: // New functions

        /**
         * Constructs controls from a resource file.
         *
         * @param aResourceId The ID for this component's resource.
         */
        void ConstructFromResourceL( const TInt aResourceId );

        /**
         * Constructs one of the toolbar items.
         *
         * @param aReader The resource reader with which to access the control's
         *      resource values.
         * @return Constructed toolbar item.
         */
        CAknToolbarItem* ConstructControlLC( TResourceReader& aReader );

        /**
         * Calculates size and position of the toolbar depending on the
         * number and size of the toolbar items.
         *
         * @return Toolbar rectangular.
         */
        TRect CalculateSizeAndPosition();

        /**
         * Calculates rects that are used in calculating the size
         * and position of the toolbar items
         *
         * @param aMainPaneRect main pane rect
         * @param aToolbarRect rect for toolbar
         * @param aGridPaneRect rect for grid pane
         * @param aCellPaneRect rect for cell pane
         */
        void CalculateRects( TRect& aMainPaneRect, TRect& aToolbarRect,
            TRect& aGridPaneRect, TRect& aCellPaneRect );

        /**
         * Calculates the position and size of the control rect
         * 
         * @param aCurrentCellPaneRect current cell pane rect is needed to 
         * get correct control rect from layout data. 
         * @return control rect for the toolbar item
         */
        TRect CalculateControlRect( TRect& aCurrentCellPaneRect ); 

        /**
         * Checks the number of visible items, and if too few the toolbar CBA is
         * deleted. If last time there were too few items then toolbar CBA is 
         * created again. Also the ordinal position of the toolbar is set if 
         * there are changes to previous situation. 
         * 
         * @return ETrue if too few items are visible, EFalse if not 
         */
        TBool TooFewItemsVisible(); 

        /**
         * Returns toolbar item object for the specified control.
         *
         * @param aControl Pointer to the control.
         * @return Pointer to the toolbar item.
         */
        CAknToolbarItem* ToolbarItemByControl( const CCoeControl* aControl ) const;

        /**
         * Returns toolbar item object for the specified command ID.
         *
         * @param aId The command ID of the item.
         * @return Pointer to the toolbar item.
         */
        CAknToolbarItem* ToolbarItemById( const TInt aId ) const;

        /**
         * Returns the index of the toolbar item inside of the iItems array.
         *
         * @param aId The command ID of the item
         * @return Index of the toolbar item.
         */
        TInt ToolbarItemIndexById( const TInt aId ) const;

        /**
         * Returns the index of the toolbar item inside of the iItems array.
         *
         * @param aControl The control which index is needed.
         * @return Index of the toolbar item.
         */
        TInt ToolbarItemIndexByControl( const CCoeControl* aControl ) const;

        /**
         * Returns the index of the toolbar item inside of the iVisibleItems
         * array.
         *
         * @param aId The command ID of the item.
         * @return Index of the toolbar item.
         */
        TInt ToolbarVisibleIndexById( const TInt aId ) const;  

        /**
         * Draws toolbar with sliding effect.
         *
         * @param aEndPos The position of the top left corner of toolbar at 
         * the end of animation.
         */
        void SlideToolbar( const TPoint& aEndPos );

        /**
         * Changes CBA text if all items are dimmed.
         */
        void SetRightCbaTextL();

        /**
         * Returns next non-dimmed and non-hidden control index.
         *
         * @param aStartIndex The index of the item from which the search
         *      should be started.
         * @param aMoveForward ETrue if search is done from lower index to
         *      the higher one.
         * @return The index of next non-dimmed and non-hidden item.
         */
        TInt GetNextSelectableItemIndex( TInt aStartIndex,
                                        TBool aMoveForward );

        /**
         * Moves highlight from one item to another. It also will change 
         * softkey text for the focused toolbar.
         *
         * @param aItemIndex The index for the newly focused item.
         * @param aDrawNow Specifies whether the item should be redrawn.
         * @param aMoveForward Specifies whether the next item in the array
         *      should be selected when the item with aItemIndex is dimmed.
         * @param aPrepareControl Specifies whether PrepareForFocusLossL() or
         *      PrepareForFocusGainL() functions should be called.
         */
        void MoveHighlightL( TInt aItemIndex,
                              const TBool aDrawNow,
                              const TBool aMoveForward = ETrue,
                              const TBool aPrepareControl = ETrue );

        /**
         * Makes toolbar visible and activates it. Position of the top left 
         * corner should be set in advance. Also use SetFocus() to specify
         * whether toolbar gets key events or not.
         */
        void ShowToolbarL();

        /**
         * Hides toolbar.
         */
        void HideToolbarL();

        /**
         * Sets the focus to the middle or the first item, depending on the
         * toolbar flags.
         *
         * @param aDrawNow if the newly focused item should be redrawn.
         */
        void InitFocusedItemL( const TBool aDrawNow );

        /**
         * Sets the flag to be on or off and also calls
         * CCoeControl::MakeVisible().
         */
        void SetShown( const TBool aShown );

        /**
         * Selects/deselects the toolbar item at given index.
         */
        void SelectItemL( const TInt aIndex, const TBool aSelect );

        /**
         * Gets rect from layout data.
         */
        TRect RectFromLayout( const TRect& aParent,
            const TAknWindowComponentLayout& aComponentLayout ) const;
        
        /**
         * Callback to get notified when ready to show toolbar again
         */
        static TInt WaitForScreenSwitch(TAny* aThis); 

        /**
         * Hides toolbar so that screen capture can be taken from the 
         * background in order to update it. 
         */
        void HideToolbarForBackgroundUpdate(); 
        
        /**
         * Updates control positions so that tooltips are positioned correctly
         */
        void UpdateControlPositions();

        /**
        * Shows toolbar via CIdle. As a result, toolbar's window priority is 
        * setted after the application's container window. This places toolbar
        * to the right place in the window tree.
        */
        void ShowViaIdle();
        
        /**
        * Callback for delayed toolbar showing.
        */
        static TInt ShowDelayedToolbar( TAny* aThis );


        /**
         * Fades behind toolbar
         * @param aFade if ETrue then fade
         */
        void FadeBehindPopup( TBool aFade ); 

        /**
         * Sets buttons to check their touchable areas when tapped 
         */
        void CheckHitAreas( ); 

        /**
         * Counts buttons of fixed tool bar and adds button(s) if needed
         * There has to bee at leas three buttons in fixed toolbar.
         */
        void CheckFixedToolbarButtonsL();

        /**
         * Draws backgrounds of fixed toolbar
         * @param aGc Graphics context used for drawing.
         * @param aControl The control being drawn (may be a child of the drawer).
         * @param aRect The area to be drawn.
         */
        void DrawFixedBackgroundL( CWindowGc& aGc, 
                                   const CCoeControl& aControl, 
                                   const TRect& aRect ) const;
                                   
        /**
        * Adjusts button's properties depending on the toolbar's features.
        */                                   
        void AdjustButton( CAknButton& aButton );
        
        /**
        * Adjusts all buttons' properties depending on the toolbar's features.
        */
        void AdjustAllButtons();
        
        /**
        * Adjusts toolbar's and overlying dialog's window positions so that
        * dialog is displayed on top of the toolbar.
        */
        void SetOrdinalPositions() const;

        /**
        * Updates control visibility based on toolbar visibility and 
        * buttons visibility inside toolbar.
        */
        void UpdateControlVisibility();
	
        /*
         * Update item tooltip position
         */
        void UpdateItemTooltipPosition();
        
    private: // Member variables

        // Array for toolbar items
        RPointerArray<CAknToolbarItem> iItems;

        // Array for visible toolbar items
        RPointerArray<CAknToolbarItem> iVisibleItems;

        // Toolbar flags
        TInt iFlags;

        // Observer to report toolbar item events, not owned
        MAknToolbarObserver* iToolbarObserver;

        // Index of focused item, used with focusable toolbar
        TInt iFocusedItem;

        // Index of selected item, used with focusable and non-focusable toolbar
        TInt iSelectedItem;

        // Toolbar cba, used with focusable toolbar
        // own
        CEikButtonGroupContainer* iToolbarCba;

        // Resource id for toolbar
        TInt iToolbarResourceId;

        // The default focused item
        TInt iInitialFocusedItem;

        // Last focused item before focus was lost
        TInt iLastFocusedItem;

        // Toolbar frame context
        // own
        CAknsFrameBackgroundControlContext* iFrameContext;

        // Toolbar background context
        // own
        CAknsBasicBackgroundControlContext* iBgContext;
        
        // Toolbar orientation
        TAknOrientation iOrientation;
        
        // Transparency bitmap
        // own
        // this member variable is deserted
        CFbsBitmap* iBgBitmap;

        // This is used to call ShowToolbarForBackgroundChange after toolbar has
        // been hidden 
        // own
        CIdle* iIdle;
        
        // Highlight bitmap
        // this member variable is deserted
        CFbsBitmap* iHighlightBitmap; 

        // Highlight mask 
        // this member variable is deserted
        CFbsBitmap* iHighlightMask; 
        
        // event modifiers
        TInt iEventModifiers; 
	
	    // Background fader
        TAknPopupFader iFader;
	    
	    // Softkey resource
        TInt iSoftkeyResource; 
	    
        // Used to store previous item that had pointerevents
        TInt iPreviousItem;

        // Item that catches point down event
        TInt iDownItem;

	    // Step for toolbar sliding
	    TInt iStep; 

	    // End position for toolbar sliding 
	    TInt iEndPos;
	    
	    // Internal flags used to store toolbar's properties
	    TBitFlags iInternalFlags;
	    
	    // Background area to be drawn when not enough visible items
	    // to cover the toolbar area
	    TRect iBgRect;

        // Toolbar window priority if set in HideItemsAndDrawOnlyBackground
	    TInt iDrawingPriority;

	    /*
	     * Background theme ID user defined. And in default, its value is 
	     * KAknsIIDNone is used and toolbar draw background with the current skin  
	     */
	    TAknsItemID iBgIID;
    };

#endif // __AKNTOOLBAR_H__

// End of File
