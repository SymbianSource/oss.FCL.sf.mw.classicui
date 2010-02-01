/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Text scrolling functionality.
*  
*
*
*/


#ifndef AKNMARQUEECONTROL_H
#define AKNMARQUEECONTROL_H

#include <coecntrl.h>
#include <coemain.h>
#include <babitflags.h>

// FORWARD DECLARATIONS
class TAknTextComponentLayout;

/**
* Marquee control for AVKON
*
*/
NONSHARABLE_CLASS(CAknMarqueeControl) : public CCoeControl, MCoeForegroundObserver
    {
    public:
	
        /**
        * Two-phased constructor.
        * @param aLoops Max number of loops to be executed
        * @param aScrollAmount The amount of pixels scrolled per iteration
        * @param aScrollDelay The interval between iterations
        */
        IMPORT_C static CAknMarqueeControl* NewL(const TInt aLoops = 1, 
                        const TInt aScrollAmount = 6, const TInt aScrollDelay = 1000000);

        /**
        * Two-phased constructor.
        * @param aLoops Max number of loops to be executed
        * @param aScrollAmount The amount of pixels scrolled per iteration
        * @param aScrollDelay The interval between iterations
        */
        IMPORT_C static CAknMarqueeControl* NewLC(const TInt aLoops = 1, 
                        const TInt aScrollAmount = 6, const TInt aScrollDelay = 1000000);
        
        /** 
        * set redraw event callback
        *
        */
        IMPORT_C void SetRedrawCallBack( TCallBack& aRedrawEventCallback );

        /** 
        * Draws text in the current position. 
        * After the marquee object is created calling this should be enough.
        * @return ETrue = All the loops have been executed, EFalse = There are loops to be executed.
        */
        IMPORT_C TBool DrawText( CWindowGc& aGc,
                                 const TRect& aTextRect,
                                 const TDesC& aText,
                                 const TInt aBaselineOffset,
                                 const CGraphicsContext::TTextAlign aAlign,
                                 const CFont& aFont );

        /** 
        * Draws text in the current position. 
        * After the marquee object is created calling this should be enough.
        * @since S60 3.1
        * @deprecated, use version taking color as last parameter instead
        * @param aGc Graphics context.
        * @param aRect Parent rectangle for the text layout.
        * @param aTextLayout Text layout that is used to draw the text.
        * @param aText Text to marquee.
        * @param aFont Font used in drawing. If this is NULL then the font is
        * taken from the aTextLayout.
        * @return ETrue = All the loops have been executed, EFalse = There are loops to be executed.
        */
        IMPORT_C TBool DrawText( CWindowGc& aGc,
                                 const TRect& aRect,
                                 const TAknTextComponentLayout& aTextLayout,
                                 const TDesC& aText,
                                 const CFont* aFont );

        /** 
        * Draws text in the current position. 
        * After the marquee object is created calling this should be enough.
        * @since S60 3.1
        * @param aGc Graphics context.
        * @param aRect Parent rectangle for the text layout.
        * @param aTextLayout Text layout that is used to draw the text.
        * @param aText Text to marquee.
        * @param aFont Font used in drawing. If this is NULL then the font is
        * taken from the aTextLayout.
        * @param aColor Color of the text        
        * @return ETrue = All the loops have been executed, EFalse = There are loops to be executed.
        */
        IMPORT_C TBool DrawText( CWindowGc& aGc,
                                 const TRect& aRect,
                                 const TAknTextComponentLayout& aTextLayout,
                                 const TDesC& aText,
                                 const CFont* aFont,
                                 TRgb  aColor );

    	/**
    	* Enable or disable logical to visual reordering in text drawing.
        * By default, it is enabled. This has any effect only when bidirectional text
        * is rendered.
        *
        * If the text is converted to visual order prior to passing it to DrawText methods
        * of this class, then the conversion should be disabled by calling this method.
        *
    	* @since 3.1
    	* @param aUseConversion Enable or disable conversion.
    	*/
	    IMPORT_C void UseLogicalToVisualConversion( TBool aUseConversion );
       
        /** 
        * Starts scrolling the text.
        *
        */
        IMPORT_C void Start();

        /** 
        * Stops scrolling the text.
        *
        */
        IMPORT_C void Stop();

        /** 
        * Resets the animation data.
        * 
        */
        IMPORT_C void Reset();
	
	    /** 
        * Is marquee on?
        *
        */
    #ifdef __WINS__
        IMPORT_C const TBool IsMarqueeOn();
    #else
    	IMPORT_C TBool IsMarqueeOn();
    #endif // __WINS__
        
        /** 
        * Sets the amount of pixels the text moves per animation loop
        *
        */
	    IMPORT_C void SetSpeedInPixels(TInt aSpeed);
	    
        /** 
        * Sets the delay between loops.
        *
        */
        IMPORT_C void SetDelay(TInt aDelay); 
        
        /** 
        * Sets the animation interval (=frames/second)
        *
        */
	    IMPORT_C void SetInterval(TInt aInterval);
        
        /** 
        * Sets the maximum number of loops to be executed.
        *
        */
        IMPORT_C void SetLoops(TInt aLoops);    
        
        /** 
        * Enables / disables marquee feature but does NOT start it yet.
        * 
        */
        IMPORT_C void EnableMarquee(TBool aEnable); // ETrue = ON, EFalse = OFF

        /** 
        * Destructor
        *
        */
        virtual ~CAknMarqueeControl();

        // from CCoeControl

        /**
         * From @c CCoeControl
         *
         * Handles fade and unfade message for stops and starts scrolling the text.
         *
         * @param aType Type of resource change.
         */        
        void HandleResourceChange( TInt aType );
        
    protected:

    private:
    
    enum TMarqueeFlags
        {
        // Is marquee enabled or not
        EFlagIsOn,
        // RTL when the first directional character is LTR character
        EFlagIsWestern,
        // If true, there needs to be a delay before the scrolling starts
        EFlagIsBeginningOfLoop,
        // Is conversion needed
        EFlagUseVisualToLogicalConversion,
        // In case of two-lined lists etc, this flag is turned on
        // when the text has been scrolled all the way to the left/right.
        EFlagIsWaitingForCallBack
        };
        
        /** 
        * Default constructor
        *
        */
        CAknMarqueeControl(const TInt aLoops, const TInt aScrollAmount, const TInt aScrollDelay);

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

	    /**
        * advance text and issue a callback to parent
        */
        void DoScroll();

	    /**
        * static callback for periodic timer
        */
        static TInt ScrollEvent(TAny * aPtr);

        /**
        * From CCoeControl
        */
        void Draw(const TRect& aRect) const;

    private: // Functions from MCoeForegroundObserver

	    /**
	    * Handles the application coming to the foreground.
	    */
	    void HandleGainingForeground();

	    /**
	    * Handles the application going into the background.
	    */
	    void HandleLosingForeground();
	
    private:    // Data
    
	    CPeriodic* iPeriodicTimer;        // creates scrolling events
	    TInt       iDelta;                // The difference between the old and new position in pixels
	    TInt       iDelay;                // Delay between loops in microseconds
	    TInt       iSpeed;                // Amount of pixels the text moves in a frame
	    TInt       iInterval;             // The interval between frame updates (= "frames/second")
        TCallBack  iCallBack;             // Callback to parent
        TInt       iLoops;                // Amount of loops executed
        TInt       iMaxLoops;             // Amount of loops *to be executed*
        TBitFlags  iFlags;
        TBool      iLastCharacter;        // It is ETrue if last character has appeared, otherwise.
    };

#endif // AKNMARQUEECONTROL_H
