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
* Description:  Title pane's label.
*
*/


#ifndef C_AKNTITLEPANELABEL_H
#define C_AKNTITLEPANELABEL_H

// INCLUDES
#include <eiklabel.h>
#include <AknUtils.h>

// FORWARD DECLARATIONS
class TAknLayoutText;

// CLASS DECLARATION

/**
 * This class is the text label which is used in title pane to display
 * texts.
 *
 * @lib avkon.lib
 */
NONSHARABLE_CLASS( CAknTitlePaneLabel ) : public CEikLabel,
                                          public MCoeForegroundObserver
    {
public:

   /** 
    * Supported effects:
    *
    * EEffectNone: No effect is applied, drawing is done as in CEikLabel::Draw()
    *
    * EEffectFadeToLeft: Text is faded to left using alpha blending.
    *
    * EEffectFadeToRight: Text is faded to right using alpha blending.
    *
    * EEffectDefaultScroll: Default scrolling effect. Text is scrolled in the
    *                       text window and when end or beginning of the text
    *                       is visible the scrolling direction is reversed. 
    *
    * EEffectDefaultScrollWithFade: Same as EEffectDefaultScroll but text is
    *                               faded from the scrolling area start and end.
    *
    * EEffectLoopScroll: Loop scrolling effect. Text is scrolled in the
    *                    text window and when whole text has been scrolled
    *                    it starts again from the other side.
    *
    * EEffectLoopScrollWithFade: Same as EEffectLoopScroll but text is faded
    *                            from the scrolling area start and end.
    *
    * EEffectFadeOut: Text is transformed gradually from opaque to transparent.
    * 
    * EEffectFadeIn: Text is transformed gradually from transparent to opaque.
    *
    * EEffectScrollOnceWithFade: Text is scrolled once and during scrolling
    *                            text is faded a bit from both ends.
    *
    * EEffectPause: Does nothing but waits.
    *
    * EEffectToggleScrolledTextTruncation: Toggles wheter text is drawn
    *                                      as truncated or not.
    *
    */
    enum TAknTitlePaneLabelEffect
        {
        EEffectNone = 0,
        EEffectFadeToLeft,
        EEffectFadeToRight,
        EEffectDefaultScroll,
        EEffectDefaultScrollWithFade,        
        EEffectLoopScroll,
        EEffectLoopScrollWithFade,        
        EEffectFadeOut,
        EEffectFadeIn,
        EEffectScrollOnceWithFade,
        EEffectPause,
        EEffectToggleScrolledTextTruncation
        };
    
   /** 
    * Struct for holding effect related data.
    */
    struct SAknTitleLableEffect
        {
        SAknTitleLableEffect() : iEffect( 0 ),
                                 iEffectDuration( 0 ), 
                                 iEffectRect( 0, 0, 0, 0 ),
                                 iLabelRect( 0, 0, 0, 0 ),
                                 iTitleText( NULL ),
                                 iObserver( NULL )
                                 {};
                                 
        TInt                iEffect;
        TInt                iEffectDuration;   
        TRect               iEffectRect;
        TRect               iLabelRect;
        TAknLayoutText      iTextLayout;
        TAknTextLineLayout  iTextLayoutLine;
        HBufC*              iTitleText; // not owned
        CCoeControl*        iObserver;  // not owned
        };
    
    
    /** 
     * Constructor
     */
    CAknTitlePaneLabel();

    /** 
     * Destructor
     */
    ~CAknTitlePaneLabel();

    /** 
     * Sets given effect active.
     *
     * @param  aEffect          The effect to be activated
     *                          (@see TAknTitlePaneLabelEffect).
     * @param  aEffectRect      The rect where effect is to be activated.
     * @param  aEffectDuration  Duration of the effect.
     * @param  aTextLayout      TextLayout for title text.
     * @param  aTextLayoutLine  LayoutLine for title text.
     * @param  aTitleText       The text.
     */
    void SetTextEffect( TInt aEffect,
                        TRect aEffectRect,
                        TInt aEffectDuration,
                        TRect aLabelRect,
                        TAknLayoutText aTextLayout,
                        TAknTextLineLayout aTextLayoutLine,
                        HBufC* aTitleText,
                        CCoeControl* aObserver = NULL );

    /** 
     * Returns currently active text effect id.
     * @return Currently active text effect id.
     */
    TInt TextEffect();

    /** 
     * Returns title text as bitmap if available. Otherwise NULL.
     * @return  Title text drawn to a bitmap.
     *          Ownership of bitmap is not transferred.
     */
	CFbsBitmap* TextAsBitmap();
	
    /** 
     * Returns title text as mask bitmap if available. Otherwise NULL.
     * @return  Title text drawn to a bitmap.
     *          Ownership of bitmap is not transferred.
     */
	CFbsBitmap* TextAsMask();

    /** 
     * Returns currently active text length in pixels.
     * @return Text lenght in pixels
     */
    TInt TextLength();
	
    /** 
     * Initializes and clears effect queue.
     */
	void InitEffectQueueL();

    /** 
     * Adds given effect to queue.
     *
     * @param  aEffect  The effect to be added.
     */
	void AddToEffectQueueL( SAknTitleLableEffect aEffect );
	
    /** 
     * Activates effect queue. All effects from queue are executed.
     */
	void ActivateEffectQueue();

protected: // from @c CEikLabel
	
    /** 
     * Actually draws the text to screen.
     */
    void Draw( const TRect& aRect ) const;
    
    /**
	 * Handles a change to the control's resources of type aType
	 * which are shared across the environment, e.g. color scheme change.
	 *
	 * @param  aType  Event type.
	 */
    void HandleResourceChange( TInt aType );
    
public:
    
    /** 
     * Enables Japanese pictograph support.
     *
     * @param  aInterface  Interface to be used in drawing the pictographs,
     *                     ownership is not transferred.
     */
    void SetPictographInterface( CAknPictographInterface& aInterface );

    /** 
     * Marks given text as invalid. It is no more used for drawing text.
     */
    void InvalidateText();

    /** 
     * Tells whether effect queue is empty.
     *
     * @return  @c ETrue if queue is empty, @c EFalse otherwise.
     */
	TBool EffectQueueIsEmpty();

    /** 
     * Replaces control characters in the title text 
     * with a space (0x20) character.
     *
     * @param[in,out] aText     Text which control characters are
     *                          to be replaced.
     *
     * @param aReplaceLinefeeds Determine if linefeeds (0x0A) and and paragraph
     *                          separatoirs (0x2029) are also converted just
     *                          like other control characters.
     *        
     */
	void ReplaceControlCharacters( HBufC* aText, TBool aReplaceLinefeeds );

private: // from @c MCoeForegroundObserver

    /** 
     * Activates timer if needed.
     */
    void HandleGainingForeground();

    /** 
     * Cancels timer if active.
     */
    void HandleLosingForeground();

private:

    /** 
     * Initializes effect, creates needed bitmap contextes etc.
     */
    void InitEffectL();

    /** 
     * Initializes timer for e.g. scrolling effect
     *
     * @param  aDelay    Initial delay before the first timer event
     *                   in microseconds.
     * @param  aInterval Interval between the consequent events
     *                   in microseconds.
     */
    void InitTimerL( TInt aDelay, TInt aInterval );

    /** 
     * Cancels timer for e.g. scrolling effect
     */
    void CancelTimer();

    /** 
     * Clears and initalizes bitmaps that are used for drawing the text.
     */
    void InitBitmaps() const;
   
    /**
     * Draws the text without the truncation character (@c KEllipsis).
     * This is used with long texts that are scrolled, so that the
     * text is not truncated before the scrolling starts, but is
     * afterwards.
     * This function calls @c CEikLabel::Draw().
     *
     * @param  aRect  Passed to @c CEikLabel::Draw().
     */
    void DrawWithoutTruncationL( const TRect& aRect );
    
    /** 
     * Main function for drawing with effects. This method selects the proper
     * subroutine based on active effect. This function is intended to be used
     * instead of @c CEikLabel::Draw() functionality.
     *
     * If no effect is currently specified, this will call @c CEikLabel::Draw().
     *
     * @param  aRect  Passed to @c CEikLabel::Draw() if no effect is
     *                active.
     */
    void DrawWithEffect( const TRect& aRect ) const;	
	
    /** 
     * Draws the text into bitmap context using selected effect.
     */
	void DrawTextWithEffect() const;

    /** 
     * Draws the text into bitmap context using fade effect. Text is
     * faded by using alphablending.
     */
	void DrawTextWithFadeEffect() const;

    /** 
     * Draws the text into bitmap context using scroll effect. Text is
     * scrolled one pixels every time timer expires.
     */
	void DrawTextWithScrollEffect() const;

    /** 
     * Draws the text into bitmap context using scroll effect. Text is
     * scrolled one pixels every time timer expires. Additionally text is
     * faded from both sides to give scrolling a smoother look.
     */
	void DrawTextWithScrollAndFadeEffect() const;

    /** 
     * Static funtion which is called when timer expires.
     */
    static TInt EffectEvent( TAny* aPtr );

    /** 
     * Funtion which is called when timer expires.
     */
    void DoEffectEvent();

    /** 
     * Funtions which manipulate text when timer event happens.
     */
    TBool DoDefaultScrollEffectEvent();
    TBool DoLoopScrollEffectEvent();
    TBool DoScrollOnceEffectEvent();
    TBool DoFadeInEffectEvent();
    TBool DoFadeOutEffectEvent();
    TBool DoPauseEffectEvent();
    TBool DoToggleScrolledTextTruncationEffectEvent();
    	
    /** 
     * Test wheter text fits to screen at once.
     *
     * @return  @c ETrue  if truncation is needed,
     *          @c EFalse otherwise.
     */
	TBool TextNeedsTruncation() const;	    

    /** 
     * Test wheter selected effect requires timed events.
     *
     * @param  aEffect  Effect to be checked
     *                  (@see TAknTitlePaneLabelEffect).
     *
     * @return @c ETrue  if timed events are needed,
     *         @c EFalse otherwise.
     */
	TBool EffectEventsNeeded( TInt aEffect ) const;	    

    /** 
     * Test wheter selected effect requires bitmap devices.
     *
     * @param  aEffect  Effect to be checked
     *                  (@see TAknTitlePaneLabelEffect).
     *
     * @return @c ETrue  if bitmap devices are needed,
     *         @c EFalse otherwise.
     */
	TBool EffectBitmapsNeeded( TInt aEffect ) const;	    

    /** 
     * Calculates suitable step for scrolling text.
     *
     * @return  Step size in pixels
     */
    TInt ScrollStepInPixels() const;
    
    /** 
     * Sets next effect from queue active.
     */
    void NextEffect();

    /** 
     * Creates scrolling text from given text.
     *
     * @param[in] aOriginalText The text from which the scrolling text
     *                          will be created from
     */
    void CreateScrollingTextL( const HBufC* aOriginalText );


private: // Member variables
    
    /** Currently active effect */
    TInt  iEffect;
    
    /** Previously active effect */
    TInt  iPreviousEffect;
    
    /** Area where currently active effect is applied */
    TRect iEffectRect;
    
    /** Area where scrolling is applied */
    TRect iScrollRect;
    
    /** Size of this control when effect was last time set active */
    TSize iEffectLabelSize;
    
    /** Timer for effects that require changes often (scroll) */
    CPeriodic* iEffectTimer;
    
    /** Duration of the effects */
    TInt  iEffectDuration;
	
	/** Current position of scrolling text */
	TInt  iScrollPosition;
	
	/** Interval for scrolling text updates */
	TInt  iScrollInterval;
	
	/** Amount of pixels scrolling text is shifed each time that timer expires */
	TInt  iScrollStep;
	
	/** Determines the scrolling direction of the text */
	TBool  iScrollDirectionBackwards;     
    
    /** Alpha value for fade out text */
    TInt  iFadeInOutValue;
    
    /** Alpha value for fade in text */
    TInt  iFadeInOutStep;
    
    /** Phase where operator name effect is at the moment */
    TInt  iOperatorNamePhase;
    
    /** Title text, not owned */
	HBufC* iTitleText;
	
	/** Scrolled text without truncations but always in visual order, owned */
	HBufC* iScrollingText;
    
    /** Title text layout */
    TAknLayoutText iTextLayout;
    
    /** Title text layoutline */
    TAknTextLineLayout iTextLayoutLine;
    
    /** Calculated length of the text in pixels */
	TInt  iTextLength;
    
    /** Bitmap where text with effect is draw into */
    CFbsBitmap* iBitmap;
    
    /** Bitmap device where text with effect is draw into */
    CFbsBitmapDevice* iBitmapDevice;
    
    /** Bitmap context where text with effect is draw into */
    CFbsBitGc* iBitmapGc;
    
    /** Mask where texts mask with effect is draw into */
    CFbsBitmap* iMask;
    
    /** Mask device where texts mask with effect is draw into */
    CFbsBitmapDevice* iMaskDevice;
    
    /** Mask context where texts mask with effect is draw into */
    CFbsBitGc* iMaskGc;
    
    /**
     * Not owned. Observer, whose DrawNow() -method gets called if effect
     * has changed text outlook.
     */
    CCoeControl* iObserver;

    /** Queue which can store multiple effects. */
   	CArrayFixFlat<SAknTitleLableEffect>* iEffectQueue;
   	
   	/** Number of the next effect to be executed from effect queue */
   	TInt  iNextEffectInEffectQueue;
    
    /** The pictograph interface used to draw Japanese pictographs, not owned */
    CAknPictographInterface* iPictographInterface;
    
    /** Whether or not the current language is LTR (ETrue) or RTL (EFalse) */
    TBool  iWesternText;
    };

#endif // C_AKNTITLEPANELABEL_H
