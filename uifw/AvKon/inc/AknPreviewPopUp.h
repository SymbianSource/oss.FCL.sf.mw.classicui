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
* Description:  View part of the preview popup component.
*
*/


#ifndef AKNPREVIEWPOPUP_H
#define AKNPREVIEWPOPUP_H

// INCLUDES
#include <AknControl.h>
#include <coecobs.h>
#include <AknsItemID.h>

// FORWARD DECLARATIONS
class CFbsBitmap;
class CAknPreviewPopUpController;
class CAknsFrameBackgroundControlContext;
class TAknWindowComponentLayout;
class CAknButton;

/**
*  Preview popup.
*
*  @lib avkon.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS( CAknPreviewPopUp ) : public CAknControl,
                                        public MCoeControlObserver,
                                        public MCoeControlBackground
    {    
    public: // Constructors and destructor

        /**
        * Two-phased constructor.
        * @param aContent Reference to the content of preview popup.
        * @param aController Reference to the controller of this popup.
        * @param aStyle Used layout style.
        */
  	    static CAknPreviewPopUp* NewL( CCoeControl& aContent,
  	                                   CAknPreviewPopUpController& aController,
                                       const TInt aStyle );

  	    /**
        * Destructor.
        */
      	~CAknPreviewPopUp();
      	
    public: // New functions

        /**
        * Shows the preview popup.
        */
        void Show();
        
        /**
        * Hides the preview popup.
        */
        void Hide();
        
        /**
        * Return flags specified during construction.
        * @return Used flags.
        */
        TInt Flags() const;
        
        /**
        * Sets optional heading text. If heading text is already set the
        * current text is replaced. When set also a closing icon is shown if 
        * the currently active layout supports stylus.
        * @param aText Heading text.
        */
        void SetHeadingTextL( const TDesC& aText );
        
    public: // Functions from base classes
    
        /**
        * From CCoeControl. Gets the control's minimum required size.
        * @return The minimum size required by the control.
        */
        TSize MinimumSize();
    	
      	/**
      	* From CCoeControl. Handles a change to the control's resources.
      	* @param aType A message UID value.
      	*/
      	void HandleResourceChange( TInt aType );
      	
      	/**
      	* From MCoeControlObserver. Handles an event from an observed control.
      	* @param aControl The control that sent the event.
	    * @param aEventType The event type.
      	*/
      	void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );
      	
      	/**
        * From MCoeControlBackground. Draws the background for a given control.
        * @param aGc Graphics context used for drawing.
        * @param aControl The control being drawn.
        * @param aRect The area to be redrawn.
      	*/
      	void Draw( CWindowGc& aGc, const CCoeControl& aControl,
      	           const TRect& aRect ) const;
  
        /**
        * From CCoeControl. Sets this control as visible or invisible.
        * @param aVisible ETrue to make the control visible, EFalse to make it
        *        invisible.
        */
        void MakeVisible( TBool aVisible );
        
        /**
        * From CCoeControl. Gets the number of component controls contained by 
        * this control.
        * @return The number of component controls contained by this control.
        */
        TInt CountComponentControls() const;
        
        /**
        * From CCoeControl. Gets the specified control contained by this
        * control.
        * @param aIndex The index of the control to get.
        * @return The component control with an index on aIndex
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;
        
    protected: // Functions from base classes

        /**
        * From CCoeControl. Responds to changes to the size and position of the
        * contents of this control.
        */
        void SizeChanged();
        
        /**
        * From CCoeControl. Handles pointer events. 
        * @param aPointerEvent The pointer event.
        */
        void HandlePointerEventL( const TPointerEvent& aPointerEvent );
        
        /**
        * From CCoeControl. Handles key events.
        * @param aKeyEvent The key event.
        * @param aType The type of the event.
        */
        TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, 
                                     TEventCode aType );
        
        /**
        * From CCoeControl. Retrieves an object of the same type as that 
        * encapsulated in aId.
        * @param aId An encapsulated object id.
        * @return Pointer to the object provider.
        */
        TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
        
    private: // Constructors
    
        /**
        * C++ default constructor.
        */   
      	CAknPreviewPopUp( CCoeControl& aContent,
      	                  CAknPreviewPopUpController& aController,
                          const TInt aStyle );

      	/**
      	* Symbian 2nd phase constructor.
      	*/
    	void ConstructL();

    private: // Functions from base classes

        /**
        *  From CCoeControl. Draws the backgound graphics of this control.
        */
        void Draw( const TRect& aRect ) const;
  	
    private: // New functions
    
        /**
        * Gets the correct layout data depending on the used layout.
        * @return Layout data for the center of the popup.
        */
        TAknWindowComponentLayout CenterLayout();
        
        /**
        * Creates the closing icon if heading pane is visible and pen
        * support enabled in the current layout.
        */
        void CreateClosingIconL();
        
        /**
        * Checks if the heading should be drawn.
        *
        * @return ETrue if the heading should be drawn.
        */
        TBool HasHeading() const;
        
        /**
        * Draws background.
        * @param aGc Graphics context.
        * @param aRect Rect to draw.
        */
        void DrawBackground( CWindowGc& aGc, const TRect& aRect ) const;
        
    private: // Data
    
        // skin context
        CAknsFrameBackgroundControlContext* iBgContext;

        // application specific content
        CCoeControl& iContent;
        
        // controller of the preview popup
        CAknPreviewPopUpController& iController;
        
        // frame graphics id
        TAknsItemID iFrameId;
        
        // center graphics id
        TAknsItemID iCenterId;
        
        // layout id
        TInt iFlags;
        
        // heading text
        HBufC* iHeadingText;
        
        // closing icon
        CAknButton* iClosingIcon;
        
        
        // If the content of this control has pointer grabbed, the popup is not 
        // hidden. This boolean tells other pointer event than event drag event 
        // has occured so then pointer grab does not matter and popup can be closed. 
        TBool iCloseMenu;
        
        // It is true when user clicks the popup, transfer pointer up event to its child control
        TBool iAllowUpEvent;

    };

#endif // AKNPREVIEWPOPUP_H

//  End of File  
