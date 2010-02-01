/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  The view part of the info pop-up note 
 *
*/


#ifndef CAKNINFOPOPUPNOTE_H
#define CAKNINFOPOPUPNOTE_H

//  INCLUDES
#include <AknUtils.h>
#include <e32std.h> // RPointerArray
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CAknsFrameBackgroundControlContext;
class CAknTextControl;
class CAknInfoPopupNoteController;
class TAknWindowComponentLayout;
class TAknLayoutScalableParameterLimits;

// CLASS DECLARATION

/**
 * CAknInfoPopupNote is the view part of popup. 
 * It draws frame, background and texts in popup. 
 * @lib avkon.lib
 * @since Series 60 3.0
 */
class CAknInfoPopupNote : public CCoeControl, public MCoeForegroundObserver
    {    
public:  // Constructors and destructor

    /**
     * Two-phased constructor.
     */
    static CAknInfoPopupNote* NewL( CAknInfoPopupNoteController& aController );
        
    /**
     * Destructor.
     */
    virtual ~CAknInfoPopupNote();

public: // New functions

    /**           
    * Popup will be shown after call to this function.
    */
    void ShowL();

    /**
    * Hides popup 
    */
    void Hide();
    
    /**
    * Set text to show in popup (setted in text control, in member data). 
    * If given text is too long for popup it is truncated.
    * @param aText Text to show in popup.
    */
    void SetTextL( const TDesC& aText );

    /**
    * Return text to be show in popup.
    * @return Popup text (setted in text control, in member data).
    */
    const TPtrC GetText() const;

    /**
    * Sets the position and alignment of the info pop-up note.
    * @since 3.1
    * @param aPosition The position where pop-up note is to be displayed.
    * @param aAlignment Specifies the part of pop-up note, which will be aligned
    *    with the given position.
    */
    void SetPositionAndAlignment( const TPoint& aPosition,
                                  const TGulAlignmentValue& aAlignment );

    /**
    * Sets the position of the info pop-up note so that it is aligned with the
    * given rectangle as specified in the LAF data. This is intented to be
    * used in conjunction with lists and grids if the application wishes to
    * implement a pop-up that follows lists/grids item highlight.
    * @since 3.1
    * @param aHighlightRect Screen-relative rectangle used to calculate 
    *       pop-up's position.
    */
    void SetPositionByHighlight( const TRect& aHighlightRect );

    /**
    * Restores the info pop-up note's default position discarding previously
    * set values to position and alignment.
    * @since 3.1
    */
    void RestoreDefaultPosition();

    /**
    * Sets the tooltip mode. When tooltip mode is on, info pop-up note is
    * displayed with only one line of text, and the width of the pop-up note
    * depends on the text lenght.
    * @since 3.1
    * @param aTooltipMode ETrue to set tooltip mode on, EFalse to set it off.
    */
    void SetTooltipModeL( const TBool aTooltipMode );

    /**
    * Whether info popup note will be automatically hidden 
    * or not when app ui is faded (true by default)
    * @since 3.1
    * @param aHide ETrue when hidden, EFalse when shown or controlled externally
    */
    void HideWhenAppFaded( const TBool aHide );

public: // From CCoeControl, compound control methods

    /**
    * Return count of used components (from CCoeControl)
    * @return Number of component controls, now returns always 1.
    */
    TInt CountComponentControls() const;    

    /**
    * Return pointer to used components (from CCoeControl)
    * @param aIndex 
    * @return Pointer to used components, now returns always iText member variable.
    */
    CCoeControl* ComponentControl( TInt /*aIndex*/ ) const;
    
    /**
    * Hide popup immediately and gives key event forward without consuming it.
    * @param aKeyEvent The key event.
    * @param aType The type of key event: EEventKey, EEventKeyUp or EEventKeyDown.
    * @return Indicates whether or not the key event was used by this control.
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
    
    /**
    * Sets this control as visible or invisible.
    * @param aVisible ETrue to make the control visible, EFalse to make it invisible.
    */
    void MakeVisible( TBool aVisible );

    /**
    * Handles a change to the control's resources.
    * @param aType A message UID value.
    */
    void HandleResourceChange( TInt aType );
    
    /**    
    * Handles pointer events
    */
	void HandlePointerEventL( const TPointerEvent& aPointerEvent );
	
public: // From MCoeForegroundObserver
    /**
    * Empty implementation.
    * @since S60 3.2
    */    
    void HandleGainingForeground();
    
    /**
    * Hides info popup note if HideWhenAppFaded is enabled.
    * @since S60 3.2
    */
    void HandleLosingForeground();

private: // From CCoeControl

    /**
    * Set some of layout things.
    */
    void SizeChanged();
    
private:

    /**
     * C++ default constructor.
     */
    CAknInfoPopupNote( CAknInfoPopupNoteController& aController );

    /**
     * Symbian 2nd phase constructor (by default it is private).
     */
    void ConstructL();

private: // From CCoeControl

    /**
    * Draw mainly the background of popup window
    * @param  const TRect& aRect popup window rect
    */
    void Draw( const TRect& aRect ) const;

private: // New functions

    // Sets the correct layout for pop-up note.
    void SetWindowLayoutL();

    // Sets the info pop-up note layout.
    void SetInfoPopupWindowLayoutL();

    // Set the tooltip layout.
    void SetTooltipWindowLayoutL();

    // Moves pop-up note to set floating position.
    void Relocate();

    // Adjusts pop-up note's position so it will fit the screen.
    void AdjustPosition( const TPoint& aFloatingPosition );

    // Gets rect from layout data.
    TRect RectFromLayout( const TRect& aParent,
        const TAknWindowComponentLayout& aComponentLayout ) const;

    // Selects the correct line variety depending on the number of lines.
    TInt SelectLineVariety( const TInt aNumberOfLines,
        const TAknLayoutScalableParameterLimits& aLimits ) const;
        
    // Selects the correct window variety depending on the number of lines.
    TInt SelectWindowVariety( const TInt aNumberOfLines,
        const TAknLayoutScalableParameterLimits& aLimits ) const; 

private: // Data

    // Skin context
    CAknsFrameBackgroundControlContext* iBgContext; // Own

    // Popoup frame rects
    TRect iOuterRect;
    TRect iInnerRect;

    // Used text control inside popup
    CAknTextControl* iText;

    // Controller of the popup
    CAknInfoPopupNoteController& iController;

    // Flag for toolip usage
    TBool iTooltipMode;

    TBool iHideWhenAppFaded;

    // Flag, position, and alignment for floating position usage
    TBool iFloatingPositionUsed;
    TPoint iFloatingPosition;
    TGulAlignmentValue iAlignment;

    };

#endif      // CAKNINFOPOPUPNOTE_H   
            
// End of File
