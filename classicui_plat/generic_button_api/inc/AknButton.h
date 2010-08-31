/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Button component.
*
*/



#ifndef __AKNBUTTON_H__
#define __AKNBUTTON_H__

//  INCLUDES
#include <AknControl.h>
#include <AknIconUtils.h>
#include <AknUtils.h>

// FORWARD DECLARATIONS
class CGulIcon;
class CAknButton;
class CAknButtonExtension; 
class CAknInfoPopupNoteController;
class CAknButtonStateExtension;
class CAknPictographInterface;
class CAknsFrameBackgroundControlContext;
class CAknResourceProvider;

// CLASS DECLARATION

/**
*  Class which represents one of the button states. 
*
*  @lib eikcoctl.lib
*  @since Series 60 3.1
*/
class CAknButtonState : public CBase
    {           
    public: // Constructors and destructors

        /**
         * Destructor.
         */
        IMPORT_C ~CAknButtonState();

    protected: // Constructors and destructors

        /**
         * Constructor.
         *
         * @param aFlags The flags for the button state
         */
        IMPORT_C CAknButtonState( const TInt aFlags );

        /**
         * Symbian 2nd phase constructor.
         *
         * @param aIcon The icon for the normal state. Takes ownership.
         * @param aDimmedIcon The icon for the dimmed state. Takes ownership.
         * @param aPressedIcon The icon for the pressed down. Takes ownership.
         * @param aHoverIcon The icon for the hover state. Takes ownership.
         * @param aText The text inside the button.
         * @param aHelpText The text for the tooltip.
         */
        IMPORT_C void ConstructL( CGulIcon* aIcon,
                                  CGulIcon* aDimmedIcon, 
                                  CGulIcon* aPressedIcon,
                                  CGulIcon* aHoverIcon,
                                  const TDesC& aText, 
                                  const TDesC& aHelpText );

        /**
         * Symbian 2nd phase constructor.
         *
         * @param aFilePath The path to the file which contains icons.
         * @param aBmpId The bitmap ID for the normal state icon.
         * @param aMaskId The mask ID for the normal state icon.
         * @param aDimmedBmpId The bitmap ID for the dimmed state icon.
         * @param aDimmedMaskId The mask ID for the dimmed state icon.
         * @param aPressedBmpId The bitmap ID for the pressed down state.
         * @param aPressedMaskId The mask ID for the pressed down state.
         * @param aHoverBmpId The bitmap ID for the hover state icon.
         * @param aHoverMaskId The mask ID for the hover state icon.
         * @param aText The text inside the button.
         * @param aHelpText The text for the tooltip.
         * @param aId Item ID of the masked bitmap to be created for skin 
         *          specific icon.
         * @param aDimmedId Item ID of the dimmed masked bitmap to be created
         *          for skin specific icon.
         * @param aPressedId Item ID of the pressed masked bitmap to be created
         *          for skin specific icon.
         * @param aHoverId Item ID of the masked hover bitmap to be created
         *          for skin specific icon.
         */
        IMPORT_C void ConstructL( const TDesC& aFilePath, 
                                  const TInt aBmpId, 
                                  const TInt aMaskId,
                                  const TInt aDimmedBmpId, 
                                  const TInt aDimmedMaskId,
                                  const TInt aPressedBmpId, 
                                  const TInt aPressedMaskId,
                                  const TInt aHoverBmpId,
                                  const TInt aHoverMaskId,
                                  const TDesC& aText, 
                                  const TDesC& aHelpText,
                                  const TAknsItemID& aId = KAknsIIDNone, 
                                  const TAknsItemID& aDimmedId = KAknsIIDNone, 
                                  const TAknsItemID& aPressedId = KAknsIIDNone,
                                  const TAknsItemID& aHoverId = KAknsIIDNone );

    public: // New functions

        /**
         * Provides the icon for the normal state.
         *
         * @return The icon for the normal state.
         */
        IMPORT_C const CGulIcon* Icon() const;

        /**
         * Provides the icon for the dimmed state.
         *
         * @return The icon for the dimmed state.
         */
        IMPORT_C const CGulIcon* DimmedIcon() const;

        /**
         * Provides the icon for the pressed down (not released) state.
         *
         * @return The icon for the pressed down (not released) state.
         */
        IMPORT_C const CGulIcon* PressedIcon() const;
        
        /**
         * Provides the icon for the hover state.
         *
         * @return The icon for the hover state.
         */
        IMPORT_C const CGulIcon* HoverIcon() const;

        /**
         * Provides the text inside the button.
         *
         * @return The button text.
         */
        IMPORT_C const TDesC& Text() const;

        /**
         * Provides the text inside the help note.
         *
         * @return The tooltip text.
         */
        IMPORT_C const TDesC& HelpText() const;

        /**
         * Provides the flags for the state.
         *
         * @return The state flags.
         */
        IMPORT_C TInt Flags() const;

        /**
         * Sets the icon for the normal state. Takes ownership.
         *
         * @param aIcon The icon for the normal state.
         */
        IMPORT_C void SetIcon( CGulIcon* aIcon );

        /**
         * Sets the icon for the dimmed state. Takes ownership.
         *
         * @param aDimmedIcon The icon for the dimmed state.
         */
        IMPORT_C void SetDimmedIcon( CGulIcon* aDimmedIcon );

        /**
         * Sets the icon for the pressed down state. Takes ownership.
         *
         * @param aPressedIcon The icon for the pressed down state.
         */
        IMPORT_C void SetPressedIcon( CGulIcon* aPressedIcon );

        /**
         * Sets the icon for the hover state. Takes ownership.
         *
         * @param aHoverIcon The icon for the hover state.
         */
        IMPORT_C void SetHoverIcon( CGulIcon* aHoverIcon );

        /**
         * Sets the text inside the button.
         *
         * @param aText The text inside the button.
         */
        IMPORT_C void SetTextL( const TDesC& aText );

        /**
         * Sets the text inside the help note.
         *
         * @param aHelpText The text inside the tooltip.
         */
        IMPORT_C void SetHelpTextL( const TDesC& aHelpText );

        /**
         * Sets the flags for the state.
         *
         * @param aFlags The flags for the state.
         */
        IMPORT_C void SetFlags( const TInt aFlags );
        
        /**
         * Sets the icon for the normal state
         *
         * @param aFlags The flags for the state.
         */
        void UpdateIconL( const TDesC& aFilePath, 
                          const TInt aBmpId, 
                          const TInt aMaskId,
                          const TInt aDimmedBmpId, 
                          const TInt aDimmedMaskId,
                          const TInt aPressedBmpId, 
                          const TInt aPressedMaskId,
                          const TInt aHoverBmpId,
                          const TInt aHoverMaskId,
                          const TAknsItemID& aId = KAknsIIDNone, 
                          const TAknsItemID& aDimmedId = KAknsIIDNone, 
                          const TAknsItemID& aPressedId = KAknsIIDNone,
                          const TAknsItemID& aHoverId = KAknsIIDNone );
        
        
        
    protected: // New functions

        /**
         * Constructs controls from a resource file.
         * @param aReader The resource reader with which to access the
         *          control's resource values.
         */
        IMPORT_C virtual void ConstructFromResourceL( TResourceReader& aReader );

        /**
         * Updates the size of icons. Called from CAknButton::SizeChanged() 
         * function.
         *
         * @param aRect The new rectangle for the icons.
         * @param aScaleMode The scale mode which was set for the button.
         */
        IMPORT_C virtual void SizeChanged( const TRect& aRect, 
                                           TScaleMode aScaleMode );

        /**
         * @return ETrue if the button has valid text (not empty and not space).
         */
        IMPORT_C TBool HasText() const;

        /**
         * @return ETrue if the button has valid tooltip text (not empty and 
         *          not space).
         */
        IMPORT_C TBool HasHelp() const;
        
        /**
        * Handles changes in state's environment.
        *
        * @since S60 3.2.
        * @param aType Resource change's type.
        */
        void HandleResourceChange( TInt aType );
        
        /**
        * Sets default scaling mode.
        *
        * @since S60 3.2
        * @param aScaleMode Scaling mode.
        */
        void SetIconScaleMode( const TScaleMode aScaleMode );

    private: // new functions

        /**
         * Creates one icon based on the specified file path and IDs.
         *
         * @param aIcon The icon object which is created and returned. 
         *      Will be deleted if it is not NULL on entry.
         * @param aFilePath The path to the file which contains icons.
         * @param aBmpId The bitmap ID for the icon.
         * @param aMaskId The mask ID for the icon.
         * @param aId Item ID of the masked bitmap to be created for skin 
         *      specific icon.
         */
        void CreateButtonIconL( CGulIcon*& aIcon, const TDesC& aFilePath, 
                                TInt aBmpId, TInt aMaskId, 
                                const TAknsItemID& aId = KAknsIIDNone ) const;
                                
        /**
         * Loads one icon based on the specified file path and IDs. If the icon
         * is already loaded it is deleted and replaced with a reloaded copy.
         *
         * @since S60 3.2
         * @param aIcon The icon object which is created and returned. 
         *      Will be deleted if it is not NULL on entry.
         * @param aFilePath The path to the file which contains icons.
         * @param aBmpId The bitmap ID for the icon.
         * @param aMaskId The mask ID for the icon.
         * @param aId Item ID of the masked bitmap to be created for skin 
         *      specific icon.
         */
        void LoadButtonIcon( CGulIcon*& aIcon ) const;
                                
        /**
         * Replaces the given icon with a new one. If the original icon had its
         * size set then the new icon is scaled to that size.
         *
         * @since S60 3.2
         */
        void ReplaceIcon( CGulIcon*& aIcon, CGulIcon* aNewIcon );
                          
        /**
        * Scales all icons.
        *
        * @since S60 3.2
        * @param aSize New icon size.
        * @param aScaleMode Scaling mode.
        * @return KErrNone or an error code.
        */
        TInt ScaleIcons( const TSize& aSize, TScaleMode aScaleMode );

        /**
         * @return The extension object.
         */
        CAknButtonStateExtension* Extension() const;

        /**
         * @return The scalemode of the ButtonState
         */
        TScaleMode ScaleMode() const;
        
        /**
         * @param aDimmedIconCreatedByButton ETrue, if the dimmed icon of the state is 
         * created by owning Button
         */
        void SetGeneratedDimmedIcon( TBool aDimmedIconCreatedByButton );

        friend class CAknButton;

    protected: // data
        CGulIcon*   iIcon;                      // bitmaps for normal state
        CGulIcon*   iDimmedIcon;                // bitmaps for dimmed icon
        CGulIcon*   iPressedIcon;               // bitmaps for pressed but not activated state
        CGulIcon*   iHoverIcon;                 // bitmaps for hover icon
        HBufC*      iText;                      // text for normal state
        HBufC*      iHelpText;                  // text which is shown as a help
        TInt        iFlags;                     // flags for the state
        CAknButtonStateExtension* iExtension;   // for future extensions
    };


// CLASS DECLARATION

/**
*  Generic button class.
*
*  @lib eikcoctl.lib
*  @since Series 60 3.1
*/
class CAknButton : public CAknControl
    {
    public: // Enumerations

        enum TAlignment
            {
            ECenter, /* align center vertically or horizontally */
            ETop, /* align to top vertically */
            EBottom, /* align to bottom vertically */
            ERight, /* align to right horizontally */
            ELeft /* align to left horixontally */
            };

        enum TTooltipPosition
            {
            EPositionTop = 1, /* Tool tip alignment vertically to top */
            EPositionBottom, /* Tool tip alignment vertically to bottom */
            EPositionLeft, /* Tool tip alignment horizontally to left */
            EPositionRight /* Tool tip alignment horizontally to right */
            };
            
        enum TTextAndIconAlignment
            {
            EIconBeforeText, /* Icon and text side by side Icon first */
            EIconAfterText,  /* Icon and text side by side Text first */
            EIconUnderText,  /* Icon and text one upon the other Icon under the text */
            EIconOverText,   /* Icon and text one upon the other Icon over the text */
            EOverlay         /* Icon and text overlaid */
            };            

        enum TButtonEvent
            {
            ELongPressEvent = 100, /* Observer event for long press event */
            ELongPressEndedEvent   /* Observer event for long press ended event */
            };

    public: // Constructors and destructors
    
        /**
         * Two-phased constructor.
         * Constructs an empty button.
         */
        IMPORT_C static CAknButton* NewL();
        
        /**
         * Two-phased constructor. Constructs an empty button.
         */
        IMPORT_C static CAknButton* NewLC();
        
        /**
         * Two-phased constructor. Constructs the button from resources.
         *
         * @param aReader is the resource reader with which to access 
         *      the control's resource values.
         */
        IMPORT_C static CAknButton* NewL( TResourceReader& aReader );
        
        /**
         * Two-phased constructor. Constructs the button from resources.
         *
         * @param aReader is the resource reader with which to access 
         *      the control's resource values. 
         */
        IMPORT_C static CAknButton* NewLC( TResourceReader& aReader ); 
        
        /**
         * Two-phased constructor. Constructs the button from resources.
         * 
         * @param aResourceId is the ID for this component's resource.
         */
        IMPORT_C static CAknButton* NewL( const TInt aResourceId );
        
        /**
         * Two-phased constructor. Constructs the button from resources. 
         * 
         * @param aResourceId is the ID for this component's resource.
         */
        IMPORT_C static CAknButton* NewLC( const TInt aResourceId );

        /**
         * Two-phased constructor. Constructs one state button.
         *
         * @param aIcon The icon for the normal state. Takes ownership.
         * @param aDimmedIcon The icon for the dimmed state. Takes ownership.
         * @param aPressedIcon The icon for the pressed down. Takes ownership.
         * @param aHoverIcon The icon for the hover state. Takes ownership.
         * @param aText The text inside the button.
         * @param aHelpText The text for the tooltip.
         * @param aButtonFlags The flags for the button.
         * @param aStateFlags The flags for the first state.
         */
        IMPORT_C static CAknButton* NewL( CGulIcon* aIcon, 
                                          CGulIcon* aDimmedIcon,
                                          CGulIcon* aPressedIcon,
                                          CGulIcon* aHoverIcon,
                                          const TDesC& aText, 
                                          const TDesC& aHelpText, 
                                          const TInt aButtonFlags,
                                          const TInt aStateFlags );

        /**
         * Two-phased constructor. Constructs one state button.
         *
         * @param aIcon The icon for the normal state. Takes ownership.
         * @param aDimmedIcon The icon for the dimmed state. Takes ownership.
         * @param aPressedIcon The icon for the pressed down. Takes ownership.
         * @param aHoverIcon The icon for the hover state. Takes ownership.
         * @param aText The text inside the button.
         * @param aHelpText The text for the tooltip.
         * @param aButtonFlags The flags for the button.
         * @param aStateFlags The flags for the first state.
         */
        IMPORT_C static CAknButton* NewLC( CGulIcon* aIcon, 
                                           CGulIcon* aDimmedIcon,
                                           CGulIcon* aPressedIcon,
                                           CGulIcon* aHoverIcon,
                                           const TDesC& aText, 
                                           const TDesC& aHelpText, 
                                           const TInt aFlags,
                                           const TInt aStateFlags );

        /**
         * Two-phased constructor. Constructs one state button.
         *
         * @param aFilePath The path to the file which contains icons.
         * @param aBmpId The bitmap ID for the normal state icon.
         * @param aMaskId The mask ID for the normal state icon.
         * @param aDimmedBmpId The bitmap ID for the dimmed state icon.
         * @param aDimmedMaskId The mask ID for the dimmed state icon.
         * @param aPressedBmpId The bitmap ID for the pressed down state.
         * @param aPressedMaskId The mask ID for the pressed down state.
         * @param aHoverBmpId The bitmap ID for the hover state.
         * @param aHoverMaskId The mask ID for the hover state.
         * @param aText The text inside the button.
         * @param aHelpText The text for the tooltip.
         * @param aButtonFlags The flags for the button.
         * @param aStateFlags The flags for the first state.
         * @param aId Item ID of the masked bitmap to be created for skin 
         *      specific icon.
         * @param aDimmedId Item ID of the dimmed masked bitmap to be created 
         *      for skin specific icon.
         * @param aPressedId Item ID of the pressed masked bitmap to be created 
         *      for skin specific icon.
         * @param aHoverId Item ID of the masked hover bitmap to be created
         *      for skin specific icon.
         */
        IMPORT_C static CAknButton* NewL( const TDesC& aFilePath, 
                                          const TInt aBmpId, 
                                          const TInt aMaskId,
                                          const TInt aDimmedBmpId, 
                                          const TInt aDimmedMaskId,
                                          const TInt aPressedBmpId, 
                                          const TInt aPressedMaskId,
                                          const TInt aHoverBmpId,
                                          const TInt aHoverMaskId,
                                          const TDesC& aText, 
                                          const TDesC& aHelpText, 
                                          const TInt aButtonFlags, 
                                          const TInt aStateFlags,
                                          const TAknsItemID& aId = KAknsIIDNone, 
                                          const TAknsItemID& aDimmedId = KAknsIIDNone, 
                                          const TAknsItemID& aPressedId = KAknsIIDNone,
                                          const TAknsItemID& aHoverId = KAknsIIDNone );

        /**
         * Two-phased constructor. Constructs one state button.
         *
         * @param aFilePath The path to the file which contains icons.
         * @param aBmpId The bitmap ID for the normal state icon.
         * @param aMaskId The mask ID for the normal state icon.
         * @param aDimmedBmpId The bitmap ID for the dimmed state icon.
         * @param aDimmedMaskId The mask ID for the dimmed state icon.
         * @param aPressedBmpId The bitmap ID for the pressed down state.
         * @param aPressedMaskId The mask ID for the pressed down state.
         * @param aHoverBmpId The bitmap ID for the hover state.
         * @param aHoverMaskId The mask ID for the hover state.
         * @param aText The text inside the button.
         * @param aHelpText The text for the tooltip.
         * @param aButtonFlags The flags for the button.
         * @param aStateFlags The flags for the first state.
         * @param aId Item ID of the masked bitmap to be created for skin 
         *      specific icon.
         * @param aDimmedId Item ID of the dimmed masked bitmap to be created 
         *      for skin specific icon.
         * @param aPressedId Item ID of the pressed masked bitmap to be created 
         *      for skin specific icon.
         * @param aHoverId Item ID of the hover state masked bitmap to be
         *      created for skin specific icon.
         */
        IMPORT_C static CAknButton* NewLC( const TDesC& aFilePath, 
                                           const TInt aBmpId, 
                                           const TInt aMaskId,
                                           const TInt aDimmedBmpId, 
                                           const TInt aDimmedMaskId,
                                           const TInt aPressedBmpId, 
                                           const TInt aPressedMaskId, 
                                           const TInt aHoverBmpId,
                                           const TInt aHoverMaskId,
                                           const TDesC& aText, 
                                           const TDesC& aHelpText, 
                                           const TInt aButtonFlags, 
                                           const TInt aStateFlags,
                                           const TAknsItemID& aId = KAknsIIDNone, 
                                           const TAknsItemID& aDimmedId = KAknsIIDNone, 
                                           const TAknsItemID& aPressedId = KAknsIIDNone,
                                           const TAknsItemID& aHoverId = KAknsIIDNone );

        /**
         * Destructor.
         */
        IMPORT_C virtual ~CAknButton();

    public: // Functions from base class

        /**
         * Sets control as ready to be drawn.
         */
        IMPORT_C void ActivateL();

        /**
         * Constructs controls from a resource file.
         *
         * @param aReader The resource reader, with which to access the 
         *      control's resource values.
         */
        IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

        /**
         * Handles a change to the control's resources.
         *
         * @param aType is a message UID value.
         */
        IMPORT_C void HandleResourceChange( TInt aType );

        /**
         * Returns the control's minimum required size. It does not include the
         * size of the highlight. However, it includes current margins.
         * Use HighlightRect() function to get highlight rectangle for the 
         * focused button.
         *
         * @return The minimum size required by the control.
         */
        IMPORT_C TSize MinimumSize();

        /**
         * Sets button dimmed. Does not redraw the button. Note: This function
         * does not affect the flag set with function CCoeControl::SetDimmed(),
         * since button needs to get pointer events, even if it is dimmed.
         * The value of the flag can be enquired using CAknButotn::IsDimmed().
         *
         * @param aDimmed is ETrue to dim the button, EFalse to set the button 
         *      as not dimmed.
         */
        IMPORT_C void SetDimmed( TBool aDimmed );

        /**
         * Handles key events.
         *
         * @param aKeyEvent The key event.
         * @param aType The type of key event: EEventKey, EEventKeyUp or 
         *      EEventKeyDown.
         */
        IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, 
                                              TEventCode aType );
        
        /**
         * Sets this control as visible or invisible.
         *
         * @param aVisible ETrue to make the control visible, EFalse to make 
         *      it invisible.
         */
        IMPORT_C void MakeVisible( TBool aVisible );

        /**
         * This function is called by the dialog framework immediately before 
         * it removes keyboard focus from a control within a dialog.
         * Currently has empty implementation.
         */
        IMPORT_C void PrepareForFocusLossL();

        /**
         * Prepares the control for gaining focus.
         * Must be used before calling SetFocus() function in case when help 
         * note should be shown.
         */
        IMPORT_C void PrepareForFocusGainL(); 

        /**
         * Handles pointer events.
         *
         * @param aPointerEvent The pointer event.
         */
        IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );

        /**
         * Responds to changes in the position of a control.
         */
        IMPORT_C virtual void PositionChanged();  

    public: // New functions

        /**
         * Constructs controls from a resource file.
         *
         * @param aResourceId The ID for this component's resource.
         */
        IMPORT_C void ConstructFromResourceL( const TInt aResourceId );

        /**
         * Sets button state.
         *
         * @param aStateIndex The index for the state, starts from 0.
         * @param aDrawNow ETrue to redraw the button.
         */
        IMPORT_C virtual void SetCurrentState( const TInt aStateIndex, 
                                               const TBool aDrawNow );

        /**
         * Adds one more state for the button to the end of state array.
         *
         * @param aIcon The icon object containing a bitmap and a mask (if 
         *      there is one) for the button.
         * @param aDimmedIcon The icon object containing a bitmap and a mask 
         *      (if there is one) for the dimmed case.
         * @param aPressedIcon The icon object containing a bitmap and a mask
         *      (if there is one) for the case when button is pressed.
         * @param aHoverIcon The icon object containingg a bitmap and a mask
         *      for the case when the pointer is hovering over the button.
         * @param aText is the text.
         * @param aHelpText is the text for the tooltip.
         * @param aStateFlags The flags for the state.
         */
        IMPORT_C virtual void AddStateL( CGulIcon* aIcon, 
                                         CGulIcon* aDimmedIcon, 
                                         CGulIcon* aPressedIcon,
                                         CGulIcon* aHoverIcon,
                                         const TDesC& aText, 
                                         const TDesC& aHelpText, 
                                         const TInt aStateFlags );

        /**
         * Adds one more state for the button.
         *
         * @param aFilePath The path to the file which contains icons.
         * @param aBmpId The bitmap ID for the normal state icon.
         * @param aMaskId The mask ID for the normal state icon.
         * @param aDimmedBmpId The bitmap ID for the dimmed state icon.
         * @param aDimmedMaskId The mask ID for the dimmed state icon.
         * @param aPressedBmpId The bitmap ID for the pressed down state.
         * @param aPressedMaskId The mask ID for the pressed down state.
         * @param aHoverBmpId The bitmap ID for the hover state.
         * @param aHoverMaskId The mask ID for the hover state.
         * @param aHoverId Item ID of the hover state masked bitmap to be
         *      created for skin specific icon.
         * @param aText is the text.
         * @param aHelpText is the text for the tooltip.
         * @param aStateFlags The flags for the state.
         * @param aId Item ID of the masked bitmap to be created for skin 
         *      specific icon. Use KAknsIIDNone when it is not needed.
         * @param aDimmedId Item ID of the dimmed masked bitmap to be created 
         *      for skin specific icon. Use KAknsIIDNone when it is not needed.
         * @param aPressedId Item ID of the pressed masked bitmap to be created 
         *      for skin specific icon. Use KAknsIIDNone when it is not needed.
         * @param aHoverId Item ID of the hover state masked bitmap to be
         *      created for skin specific icon.
         */
        IMPORT_C virtual void AddStateL( const TDesC& aFilePath, 
                                         const TInt aBmpId, 
                                         const TInt aMaskId,
                                         const TInt aDimmedBmpId, 
                                         const TInt aDimmedMaskId,
                                         const TInt aPressedBmpId, 
                                         const TInt aPressedMaskId, 
                                         const TInt aHoverBmpId,
                                         const TInt aHoverMaskId,
                                         const TDesC& aText,
                                         const TDesC& aHelpText,
                                         const TInt aStateFlags,
                                         const TAknsItemID& aId, 
                                         const TAknsItemID& aDimmedId, 
                                         const TAknsItemID& aPressedId,
                                         const TAknsItemID& aHoverId );
        
        /**
         * Adds one more state for the button to the end of state array.
         *
         * @param  aIcon         The icon object containing a bitmap and
         *                       a mask (if there is one) for the button.
         * @param  aDimmedIcon   The icon object containing a bitmap and a mask 
         *                       (if there is one) for the dimmed case.
         * @param  aPressedIcon  The icon object containing a bitmap and a mask
         *                       (if there is one) for the case when
         *                       button is pressed.
         * @param  aHoverIcon    The icon object containingg a bitmap and
         *                       a mask for the case when the pointer is
         *                       hovering over the button.
         * @param  aText         is the text.
         * @param  aHelpText     is the text for the tooltip.
         * @param  aStateFlags   The flags for the state.
         * @param  aCommandId    Command to be attached with the state.
         */
        void AddStateL( CGulIcon* aIcon, 
                        CGulIcon* aDimmedIcon, 
                        CGulIcon* aPressedIcon,
                        CGulIcon* aHoverIcon,
                        const TDesC& aText, 
                        const TDesC& aHelpText, 
                        const TInt aStateFlags,
                        const TInt aCommandId );

        /**
         * Sets the button flags.
         *
         * @param aFlags which can be combination of: KAknButtonTextLeft, 
         *      KAknButtonSizeFitText, KAknButtonNoFrame, KAknButtonKeyRepeat,
         *      KAknButtonReportOnKeyDown, KAknButtonNoFramePressEvent,
         *      KAknButtonRequestExitOnButtonUpEvent, KAknButtonReportOnLongPress.
         */
        IMPORT_C void SetButtonFlags( const TInt aFlags );

        /** 
         * Sets specified frame IDs. Can be used when default frame is not 
         * suitable. Use KAknsIIDNone value in case when some frame or center
         * drawing is not needed or KAknsIIDDefault when the default button
         * frame should be used.
         *
         * @param aFrameId The item ID of the entire frame.
         * @param aCenterId The item ID of the center part of the frame.
         * @param aLatchedFrameId The item ID of the entire frame for button 
         *      in latched state.
         * @param aLatchedCenterId The item ID of the center part of the 
         *      frame for button in latched state.
         * @param aDimmedFrameId The item ID of the entire frame for a button
         *      in dimmed state.
         * @param aDimmedCenterId The item ID of the center part of the frame
         *      for a button in dimmed state.
         * @param aPressedFrameId The item ID of the entire frame for a 
         *      button in pressed state.
         * @param aPressedCenterId is the item ID of the center part of the 
         *      frame for a button in pressed state.
         * @param aLatchedDimmedFrameId The item ID of the entire frame for 
         *      a button in latched and dimmed state.
         * @param aLatchedDimmedCenterId The item ID of the center part of 
         *      the frame for a button in latched and dimmed state.
         */
        IMPORT_C void SetFrameAndCenterIds( const TAknsItemID& aFrameId, 
                                            const TAknsItemID& aCenterId,
                                            const TAknsItemID& aLatchedFrameId, 
                                            const TAknsItemID& aLatchedCenterId,
                                            const TAknsItemID& aDimmedFrameId, 
                                            const TAknsItemID& aDimmedCenterId,
                                            const TAknsItemID& aPressedFrameId, 
                                            const TAknsItemID& aPressedCenterId,
                                            const TAknsItemID& aLatchedDimmedFrameId, 
                                            const TAknsItemID& aLatchedDimmedCenterId );

        /** 
         * Sets specified background IDs. Can be used when default frame is not
         * suitable and the backgound is composed of only single image instead
         * of frame and center. SetFrameAndCenterIds() function can also be used
         * for this purpose by giving the same backround ID for both frame and
         * center. This allows also some of the states to be composed of frames
         * and the others from single backgound images. Use KAknsIIDNone value
         * in case when some backgound drawing is not needed or KAknsIIDDefault
         * when the default button frame should be used.
         *
         * @param aBackgroundId The item ID of the entire frame.
         * @param aLatchedBackgroundId The item ID of the background for the
         *      button in latched state.
         * @param aDimmedBackgroundId The item ID of the background for the
         *      button in dimmed state.
         * @param aPressedBackgroundId The item ID of the background for the 
         *      button in pressed state.
         * @param aLatchedDimmedBackgroundId The item ID of the background for 
         *      the button in latched and dimmed state.
         */
        IMPORT_C void SetBackgroundIds( const TAknsItemID& aBackgroundId, 
                                        const TAknsItemID& aLatchedBackgroundId, 
                                        const TAknsItemID& aDimmedBackgroundId, 
                                        const TAknsItemID& aPressedBackgroundId, 
                                        const TAknsItemID& aLatchedDimmedBackgroundId );

        /**
         * Sets some specific text font.
         *
         * @param aFont The font, which should be used for the text inside the 
         *      text button.
         */
        IMPORT_C void SetTextFont( const CFont* aFont );

        /**
         * Sets the color table and color index for the button text. It will be
         * used on button drawing, if color of the text shouldn't be taken from
         * text layout.
         *
         * @param aTextColorTableId Id for the color table 
         * @param aTextColorIndex Index of the color inside color table.
         */
        IMPORT_C void SetTextColorIds( const TAknsItemID& aTextColorTableId, 
                                       const TInt aTextColorIndex );

        /**
         * Sets the horizontal alignment for the text inside the button. It
         * will be used, if alignment shouldn't be taken from text layout. By
         * default it will be centered.
         *
         * @param aHorizontalAlignment The horizontal alignment for the text.
         */
        IMPORT_C void SetTextHorizontalAlignment( 
            const CGraphicsContext::TTextAlign aHorizontalAlignment );

        /**
         * Sets the vertical alignment for the text inside the button. It will 
         * be used if alignment shouldn't be taken from text layout. By default 
         * it will be centered.
         *
         * @param aVerticalAlignment The vertical alignment for the text.
         */
        IMPORT_C void SetTextVerticalAlignment( 
            const CAknButton::TAlignment aVerticalAlignment );

        /**
         * Sets the icon and text alignment for a button having both
         *
         * @param aAlignment. TTextAndIconAlignment
         */
        IMPORT_C void SetTextAndIconAlignment( 
            const CAknButton::TTextAndIconAlignment aAlignment );

        /**
         * Sets the text underline style for the text inside the button. By
         * default no underline is used.
         *
         * @param aUnderlineStyle The style of underline.
         */
        IMPORT_C void SetTextUnderlineStyle( TFontUnderline aUnderlineStyle );

        /**
         * Sets the scale mode for the icon inside the button. 
         * The default is EAspectRatioNotPreserved.
         *
         * @param aScaleMode The scale mode.
         */
        IMPORT_C void SetIconScaleMode( const TScaleMode aScaleMode );

        /**
         * Sets the horizontal alignment for the icon inside the button.
         * By default it will be centered.
         *
         * @param aHorizontalAlignment The horizontal alignment for the icon.
         */
        IMPORT_C void SetIconHorizontalAlignment( 
            const CAknButton::TAlignment aHorizontalAlignment );

        /**
         * Sets the vertical alignment for the icon inside the button.
         * By default it will be centered.
         *
         * @param aVerticalAlignment The vertical alignment for the icon.
         */
        IMPORT_C void SetIconVerticalAlignment( 
            const CAknButton::TAlignment aVerticalAlignment );
            
        /**
         * Sets the delay before the help text is shown and also specifies the 
         * time for how long help text is visible.
         *
         * @param aBeforeTimeout The delay in milliseconds before text help note 
         *      is shown. The default is 150 milliseconds.
         * @param aInViewTimeout The interval in milliseconds during which help 
         *      text note is shown. The default is 3000 milliseconds.
         */
        IMPORT_C void SetHelpNoteTimeouts( const TInt aBeforeTimeout, 
                                           const TInt aInViewTimeout );

        /**
         * Sets the interval for key repeat.
         *
         * @param aKeyRepeatDelay The initial delay, after which the key repeat is
                started. The default is 500 milliseconds.
         * @param aKeyRepeatInterval The interval in milliseconds, in which key
         *      repeat events should be reported. The default is 500 milliseconds.
         */
        IMPORT_C void SetKeyRepeatInterval( const TInt aKeyRepeatDelay, 
                                            const TInt aKeyRepeatInterval );
        
        /**
         * Sets the interval for long press. When KAknButtonReportOnLongPress
         * flag is set for the button, button will notify observer with 
         * KAknButtonLongPressEvent as the event type, after button has been
         * pressed for the specified time.
         * 
         * @param aLongPressInterval The time interval in milliseconds, after
         *      which the long press event should be reported. The default
         *      value is 800 milliseconds.
         */
        IMPORT_C void SetLongPressInterval( const TInt aLongPressInterval );

        /**
         * Returns the index of the button state.
         */
        IMPORT_C TInt StateIndex() const;

        /**
         * Enables pictograph drawing in the button text.
         * Only effective in Japanese variant.
         * By default, it is disabled.
         *
         * @param aInterface Used pictograph interface owned by the caller.
         */
        IMPORT_C void EnablePictographsL( CAknPictographInterface& aInterface );

        /**
         * Disables pictograph drawing in the button text.
         * Only effective in Japanese variant.
         * By default, it is disabled.
         */
        IMPORT_C void DisablePictographs();

        /**
         * It will change the default highlight rectangle around 
         * the focused button.
         *
         * @param aRect The highlight rectangle.
         */
        IMPORT_C void SetHighlightRect( const TRect& aRect );

        /**
         * Gets the highlight rectangle around the button.
         *
         * @return The higlight rectangle around the button.
         */
        IMPORT_C TRect HighlightRect() const;

        /**
         * Sets the tooltip position.
         *
         * @param aPosition The position of the tooltip.
         */
        IMPORT_C void SetTooltipPosition( const TTooltipPosition aPosition );

        /**
         * Sets whether button should send an EEventRequestExit event to command
         * observer on button up event.
         *
         * @param aRequestExit ETrue if button should request exit.
         */
        IMPORT_C void SetRequestExit( const TBool aRequestExit );

        /**
         * Tests if the control is dimmed. This function overrides the function
         * declared in CCoeControl, and returns the value which is set and unset
         * using CAknButton::SetDimmed().
         *
         * @return ETrue if the control is dimmed, EFalse if it is not dimmed.
         */
        IMPORT_C TBool IsDimmed() const;

        /**
         * Sets the help text for dimmed button.
         *
         * @param aHelpText The text inside the tooltip.
         */
        IMPORT_C void SetDimmedHelpTextL( const TDesC& aHelpText );

        /**
         * Check if point is within buttons visible area, when
         * KAknButtonHitTest flag is enabled
         *
         * @param aPoint Location to check.
         * @param aCheckHitArea if need to check the hit area for fixed 
         *        toolbar button
         */
        TBool HitAreaContainsL( const TPoint& aPoint, TBool aCheckHitArea ) const; 
        
        /**
         * Returns the current state of the button.
         *
         * @return the current state of the button
         */
        IMPORT_C CAknButtonState* State() const;

        /**
         * Returns the state of the button under specified index.
         *
         * @param aStateIndex The index for the state.
         * @return the state of the button.
         */
        IMPORT_C CAknButtonState* State( const TInt aStateIndex ) const;

        /**
         * Returns the flags of button. The flags are defined in eikon.hrh.
         * @return Button flags.
         * @since S60 3.2
         */
        IMPORT_C TInt ButtonFlags() const;

        /**
        * Sets button's margins. These define the free area inside the button
        * where content is placed. Note that calling this function overrides
        * default margins that are scaled automatically depending on the 
        * current screen layout. If this function is called then the caller
        * is responsible for updating margins whenever the layout changes.
        *
        * @since S60 3.2
        * @param aMargins New marginals.
        */
        IMPORT_C void SetMargins( const TMargins8& aMargins );
        
        /**
        * Sets icon size for the button. Calling this function overrides the
        * default size that is scaled automatically depending on the current
        * screen layout. If this function is called then the caller is
        * responsible for updating icon size whenever the layout changes.
        *
        * @since S60 3.2
        * @param aSize New icon size.
        * @return KErrNone if the operation succeeded, otherwise an error code.
        */
        IMPORT_C TInt SetIconSize( const TSize& aSize );

        /**
        * Checks if the button uses default margins.
        *
        * @since S60 3.2
        *
        * @return ETrue if default margins are used.
        */
        TBool UsesDefaultMargins() const;  

        /**
         * Sets tooltip to hide or show itself when background faded.
         *
         * @since S60 3.2
         * @param aHide should be ETrue if hiding, EFalse if showing
         */
        void HideTooltipWhenAppFaded( TBool aHide ); 


        /**
         */
        void CheckHitArea();
        
        /**
         * Resets button to unpressed state.
         *
         * @since S60 5.0
         */
        IMPORT_C void ResetState();
        
        /**
        * Sets button to use additional masks during drawing. Calling this
        * method forces button to bypass the normal drawing routine i.e. 
        * method DrawMaskedL is executed instead of Draw.
        *
        * @since S60 5.0
        * @param aMaskedDraw ETrue to use additional mask.
        */
        void UseMaskedDraw( TBool aMaskedDraw );

        /**
        * Registers resource provider.
        * @param aProvider New resource provider.
        */
        void RegisterResourceProvider( CAknResourceProvider* aProvider );

        /**
        * Unregisters resource provider.
        */
        void UnregisterResourceProvider();
        
        CAknsFrameBackgroundControlContext* BgContext();
        
        /**
        * Removes the currently active state from the button,
        * and sets the current state to the previous one.
        */
        void RemoveCurrentState();

        /**
        * Returns the button touchable area.
        *
        * @since S60 5.0
        * @return Button touch area
        */
        TRect TouchArea() const;

    protected: // Constructors

        /**
         * C++ constructor for the one state button.
         *
         * @param aFlags The flags for the button
         */
        IMPORT_C CAknButton( const TInt aFlags );

        /**
         * Symbian 2nd phase constructor.
         */
        IMPORT_C void ConstructL();

        /**
         * Symbian 2nd phase constructor.
         *
         * @param aIcon The icon for the normal state. Takes ownership.
         * @param aDimmedIcon The icon for the dimmed state. Takes ownership.
         * @param aPressedIcon The icon for the pressed down. Takes ownership.
         * @param aHoverIcon The icon for the hover state.
         * @param aText The text inside the button.
         * @param aHelpText The text for the tooltip.
         * @param aStateFlags The flags for the first state.
         */
        IMPORT_C void ConstructL( CGulIcon* aIcon, 
                                  CGulIcon* aDimmedIcon, 
                                  CGulIcon* aPressedIcon,
                                  CGulIcon* aHoverIcon,
                                  const TDesC& aText, 
                                  const TDesC& aHelpText, 
                                  const TInt aStateFlags );

        /**
         * Symbian 2nd phase constructor.
         *
         * @param aFilePath The path to the file which contains icons.
         * @param aBmpId The bitmap ID for the normal state icon.
         * @param aMaskId The mask ID for the normal state icon.
         * @param aDimmedBmpId The bitmap ID for the dimmed state icon.
         * @param aDimmedMaskId The mask ID for the dimmed state icon.
         * @param aPressedBmpId The bitmap ID for the pressed down state.
         * @param aPressedMaskId The mask ID for the pressed down state.
         * @param aHoverBmpId The bitmap ID for the hover state icon.
         * @param aHoverMaskId The mask ID for the hover state icon.
         * @param aText The text inside the button.
         * @param aHelpText The text for the tooltip.
         * @param aStateFlags The flags for the first state.
         * @param aId Item ID of the masked bitmap to be created for skin 
         *      specific icon.
         * @param aDimmedId Item ID of the dimmed masked bitmap to be created 
         *      for skin specific icon.
         * @param aPressedId Item ID of the pressed masked bitmap to be created 
         *      for skin specific icon.
         * @param aHoverId Item ID of the masked hover bitmap to be created
         *      for skin specific icon.
         */
        IMPORT_C void ConstructL( const TDesC& aFilePath, 
                                  const TInt aBmpId, 
                                  const TInt aMaskId,
                                  const TInt aDimmedBmpId, 
                                  const TInt aDimmedMaskId,
                                  const TInt aPressedBmpId, 
                                  const TInt aPressedMaskId, 
                                  const TInt aHoverBmpId,
                                  const TInt aHoverMaskId,
                                  const TDesC& aText, 
                                  const TDesC& aHelpText, 
                                  const TInt aStateFlags,
                                  const TAknsItemID& aId = KAknsIIDNone, 
                                  const TAknsItemID& aDimmedId = KAknsIIDNone, 
                                  const TAknsItemID& aPressedId = KAknsIIDNone,
                                  const TAknsItemID& aHoverId = KAknsIIDNone );

    protected: // Functions from base class

        /**
         * Responds to size changes to sets the size and position of the 
         * contents of this control.
         */
        IMPORT_C void SizeChanged();

        /**
         * This function is called whenever a control gains or loses focus.
         *
         * @param aDrawNow Contains the value that was passed to it by SetFocus().
         */
        IMPORT_C void FocusChanged( TDrawNow aDrawNow );

        /**
         * For future extensions
         * 
         * @param aInterface The ID for the extension interface.
         */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    protected: // New functions

        /**
         * Changes the state of the button to the next one.
         *
         * @return the current state index
         */
        IMPORT_C TInt ChangeState( TBool aDrawNow );

        /**
         * Returns the text, which will be displayed inside the button 
         * for the current state.
         */
        IMPORT_C const TDesC&  GetCurrentText() const;

        /**
         * Returns icon for the current state.
         */
        IMPORT_C const CGulIcon* GetCurrentIcon() const;

        /**
         * Shows help text for a certain period of time.
         */
        IMPORT_C void ShowHelpL();

        /**
         * Hides help text after certain interval.
         */
        IMPORT_C void HideHelp();


   private: // Functions from base class

        /**
         * From CCoeControl. Draws the control. Called by window server.
         */
        IMPORT_C void Draw( const TRect& aRect ) const;  

    private: // New functions

        /**
         * Continues drawing of the button which has only text.
         */
        void DrawTextButton( CWindowGc& aGc ) const;

        /**
         * Continues drawing of the button which has only an icon in it.
         */
        void DrawIconButton( CWindowGc& aGc ) const;

        /**
         * Continues drawing of the button which has both text and icon.
         */
        void DrawTextAndIconButton( CWindowGc& aGc ) const;
        
        /**
         * Starts the long press timer.
         */
        void StartLongPressTimerL();

        /**
         * Stops the long press timer.
         */
        void StopLongPressTimer();

        /**
         * Starts the timer for the key repeat.
         */
        void StartKeyRepeatTimerL();

        /**
         * Stops the key repeat timer.
         */
        void StopKeyRepeatTimer();

        /**
         * Called after timeout is over.
         */
        static TInt ReportKeyRepeatL( TAny* aThis );

        /**
         * Asserts that extension class object exists.
         *
         * @return Extension object.
         */
        CAknButtonExtension* Extension() const;

        /**
         * Updates tooltip position.
         */
        void UpdateTooltipPosition();

        /**
         * Checks whether toolbar should send an EEventRequestExit event to
         * command observe on button up event.
         *
         * @return ETrue if event should be sent, EFalse otherwise.
         */
        TBool RequestExit() const;

        /**
         * Gets the rectangele reserved for button content excluding frame.
         *
         * @return Content rectangle.
         */
        TRect ContentRect() const;

        /**
         * Checks whether button needs redrawing when it is pressed or released.
         *
         * @return ETrue, if redraw is needed, othewise EFalse.
         */
        TBool NeedsRedrawWhenPressed() const;

        /**
         * Returns the ID of specified skin item.
         */
        TAknsItemID SkinIID( const TInt aIndex ) const;
        
        /**
        * Calculates default margins.
        */
        void CalculateDefaultMargins();
        
        /**
        * Scales all icons.
        *
        * @return KErrNone or an error code.
        */
        TInt ScaleIcons();
        
        /**
        * Gets the correct text color.
        *
        * @return Text color.
        */
        TRgb TextColor() const;

        /**
        * Generates the pressed down bitmaps
        * if flag KAknButtonPressedDownFrame is set and button has no frame
        */
        void CreatePressedDownFrameL();
        
        /**
         * Calculates color's luminance. 
         */
        TInt CalculateLuminance( const TRgb& aColor ) const; 

        /**
         * Converts outline color, if fill color is too similar to outline color
         * 
         * @aFillColor fill color
         * @aOutlineColor outline color
         */
        void ConvertColorsForOutlineEffect( TRgb& aFillColor, TRgb& aOutlineColor ) const; 

        /**
         * Gets text colors 
         * 
         * @aPenColor pen color
         * @aBrushColor brush color 
         */
        void GetTextColors( TRgb& aPenColor, TRgb& aBrushColor ) const; 
        
        /**
         * Sets new state index 
         * 
         * @param aNewIndex New state index
         */
        void SetStateIndexL( TInt aNewIndex );

    protected: // Data

        // array to keep states
        CArrayPtrFlat<CAknButtonState>* iStates;

        // button flags
        TInt iFlags;

        // current button state index
        TInt iStateIndex;

        // flag to define whether the button is pressed
        TBool iButtonPressed;

        // number of drag events, needed to distinguish when it is outside 
        // the button.
        TInt iNumberOfDragEvents; 

        // Flag which shows whether key down event was reported before key up 
        // event was sent to the button, because some controls consume key down 
        // but don't consume key up events which might cause of button state 
        // when it is not expected
        TBool iKeyDownReported;

        // Background control context for button's frame
        CAknsFrameBackgroundControlContext* iBgContext;

        // Customized highlight rectangular around the button if the default one
        // won't be used
        TRect iHighlightRect;

        // text button specific data  
        const CFont*                    iFont;                // font for the text inside the button
        TAlignment                      iVerticalAlignment;   // vertical alignment for the text. Centered by default
        CGraphicsContext::TTextAlign    iHorizontalAlignment; // horizontal alignment for the text. Centered by default
        TAknsItemID                     iTextColorTableId;    // id for the color table 
        TInt                            iTextColorIndex;      // index of the color in color table

        // icon button specific data
        TScaleMode  iScaleMode; // scale mode for the icon, by default it is EAspectRatioNotPreserved

        // tooltip specific data
        TInt        iHelpNoteWaitInterval;         // interval in milliseconds between the time when the button got focused and the help text is shown
        TInt        iHelpNoteInViewInterval;       // interval during which help text is shown in milliseconds
        CAknInfoPopupNoteController* iHelpNote;    // component to show help text
        HBufC*      iDimmedHelpText;               // help text in case if the button is dimmed, not used currently
        TBool       iShowHelp;                     // flag which specifies whether help note should be shown 

        // Key repeat handling
        CPeriodic* iKeyRepeatTimer; // timer to report key repeats
        TInt iKeyRepeatDelay;       // initial delay for key repeats
        TInt iKeyRepeatInterval;    // time interval for key repeats
    
    private:
        CAknButtonExtension* iExtension;

    };


#endif // __AKNBUTTON_H__

// End of File
