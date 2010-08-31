/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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
*  Description: Indicator for double span scroll bar.
*
*/

#ifndef __AKNDOUBLESPANSCROLLINDICATOR_H
#define __AKNDOUBLESPANSCROLLINDICATOR_H

#include <coecntrl.h>
#include "eikscrlb.h"

#include "AknDoubleSpanScrollIndicatorItem.h"

class CAknDoubleSpanScrollIndicatorBGExtension;

NONSHARABLE_CLASS( TBitmapFx )
    {
public:    
    struct TRGB
        {
        TInt iR;
        TInt iG;
        TInt iB;
        };
    struct THSL
        {
        TInt iH;
        TInt iS;
        TInt iL;
        };
    
    static void PixelEffect( TUint16* aPixelData );
    static TInt HueToRGB( TInt v1, TInt v2, TInt aH );
    };

NONSHARABLE_CLASS(CAknDoubleSpanScrollIndicator) : public CCoeControl
    {            
public: // public construction and destruction methods
   
   /**
    * Two-phased constructor.
    *
    * @since    2.6
    * @return   Newly constructed object.
    */
    static CAknDoubleSpanScrollIndicator* NewL(CEikScrollBar::TOrientation aOrientation);

   /**
    * Destructor.
    *
    * @since    2.6
    */
    ~CAknDoubleSpanScrollIndicator(); 

public: // new methods

   /**
    * Sets values for the indicator.
    *
    * @since    2.6
    * @param    aScrollSpan       Size of the scrolled list.
    * @param    aFocusPosition    Position of the current field in the list.
    * @param    aWindowSize       Size of the visible part of the list.
    * @param    aFieldPosition    Size of the current field. (Optional double span)
    * @param    aFieldSize        Position inside the current field. (Optional double span)  
    *
    */
    void SetIndicatorValues(TInt aScrollSpan, TInt aFocusPosition, TInt aWindowSize, TInt aFieldPosition, TInt aFieldSize);
    
   /**
    * Gets a value from the indicator.
    *
    * @since    2.6
    * @return   Size of the scrolled list. 
    *
    */
    TInt ScrollSpan();

   /**
    * Gets a value from the indicator.
    *
    * @since    2.6
    * @return   Position of the current field in the list. 
    *
    */
    TInt FocusPosition();

   /**
    * Gets a value from the indicator.
    *
    * @since    2.6
    * @return   Size of the visible part of the list. 
    *
    */
    TInt WindowSize();

   /**
    * Gets a value from the indicator.
    *
    * @since    2.6
    * @return   Size of the current field. (Optional double span) 
    *
    */
    TInt FieldPosition();
    
   /**
    * Gets a value from the indicator.
    *
    * @since    2.6
    * @return   Position inside the current field. (Optional double span) 
    *
    */
    TInt FieldSize();

   /**
    * Sets flag which tells wheter indicator should assume transparent background
    * instead of drawing a background from skin system.
    * 
    * @since    2.6
    * @param    aTransparentBackground   If ETrue, then indicator does not try to 
    *                                    draw background. Otherwise background is
    *                                    drawn normally.
    */
    void SetTransparentBackground(TBool aTransparentBackground);    

   /**
    * Gets flag which tells wheter indicator should assume transparent background
    * instead of drawing a background from skin system.
    * 
    * @since    2.6
    * @retrun   If ETrue, then indicator does not try to 
    *           draw background. Otherwise background is drawn normally.
    */
    TBool TransparentBackground();    

   /**
    * Gets the width of the indicator graphics.
    *
    * @since    2.8
    * @return   Width of the indicator.  
    *
    */
    TInt IndicatorWidth();

    /**
     * @since 3.1
     * TInt aOwnsWindow is zero if non-window, else window owning
     */
    void SetAsWindowOwning(TBool aOwnsWindow);

private: // methods from CCoeControl
    void Draw(const TRect& aRect) const; 
       void SizeChanged();                  
public:
    void HandleResourceChange(TInt aType);
    
    /**
    * Is the scrollbar drawing its background from background context
    * or are the scrollbar graphics drawn on top of current graphics on display
    *
    * @since    3.0
    * @return   The background drawing state 
    *
    */    
    TBool DrawBackgroundState();
    
    /**
    * Set the background drawing of the scrollbar. If ETrue, scrollbar draws 
    * background from background context.
    *
    * @since    3.0
    * @param    aDraw If ETrue, background is drawn, otherwise drawing is skipped
    */
    void SetDrawBackgroundState(TBool aDraw);            

    /**
    * Get the current calculated thumb (handle) span in pixels.
    *
    * @since    5.0
    * @return   The thumb span in pixels
    */
    TInt GetCurrentThumbSpanInPixels();
    
    /**
    * Get the current calculated thumb (handle) position in pixels
    * relative to the iTl of the scrollbar's shaft.
    *
    * @since    5.0
    * @return   The thumb position in pixels
    */
    TInt GetCurrentThumbPositionInPixels();

    /**
    * Sets the handle drag highlight.
    *
    * @since    5.0
    * @param    aHandleHighlight If ETrue, turn the handle highlight on.
    */
    void SetHandleHighlight( TBool aHandleHighlight );
    
    /**
    * Gets the status of the handle drag highlight.
    *
    * @since    5.0
    * @return   ETrue, if the handle highlight is on.
    */
    TBool HandleHighlight() const;
    
    /**
    * Sets the touch area control.
    *
    * @since    5.0
    * @param    aTouchAreaControl A pointer to the control which is drawn
    *           along with this indicator.
    */
    void SetTouchAreaControl( CCoeControl* aTouchAreaControl );
    
    /**
    * Sets the background drag highlight.
    *
    * @since    5.0
    * @param    aHandleHighlight If ETrue, turn the handle highlight on.
    */
    void SetBackgroudHighlight( TBool aBackgroudHighlight );
    
    /**
    * Gets the status of the background drag highlight.
    *
    * @since    5.0
    * @return   ETrue, if the handle highlight is on.
    */
    TBool BackgroudHighlight() const;
    
private: // new methods

   /**
    * C++ default constructor.
    *
    * @since    2.6
    */
    CAknDoubleSpanScrollIndicator();
    
   /**
    * By default Symbian 2nd phase constructor is private.
    *
    * @since    2.6
    */
    void ConstructL(CEikScrollBar::TOrientation aOrientation);

   /**
    * Checks and if needed modifies values for drawing.
    *
    * @since    2.6
    * @param    aScrollSpan       Size of the scrolled list.
    * @param    aFocusPosition    Position of the current field in the list.
    * @param    aWindowSize       Size of the visible part of the list.
    * @param    aFieldPosition    Size of the current field. (Optional double span)
    * @param    aFieldSize        Position inside the current field. (Optional double span)  
    *
    */
    void CheckValues(TInt& aScrollSpan, TInt& aFocusPosition, TInt& aWindowSize, TInt& aFieldPosition, TInt& aFieldSize) const;
        
   /**
    * Calculates rects for different indicator parts to be used in drawing phase.
    *
    * @since    2.6
    */
    void CalculateRects();    
    
   /**
    * Creates items (that contain the bitmaps) for the scrollbar.
    *
    * @since    2.6
    */
    void CreateScrollBarItemsL();    

    TInt ScrollHandleMaxVisibleSizeInPixels();
    TInt HandleBackgroundMinSizeInPixels();
    TInt HandleMinSizeInPixels();

    /**
    * Handles background drawing
    * 
    * @since    3.1
    *
    */
    void DrawBackground() const;
    
    /**
    * Handles background bitmap creation for window owning scrollbar
    * 
    * @since    3.1
    *
    */
    void CreateBackgroundBitmapL();
    
    /**
    * Layout scrollbar handle
    * 
    * @since    3.1
    *
    */
    void LayoutHandleGraphics();
    
    /**
    * Used for highlighting handle skin graphics. Takes a bitmap, creates 
    * a copy and optionally applies an effect for the pixels in the
    * bitmap. Returns the new bitmap, so caller must take ownership.
    * Note that the effect only works for EColor64K bitmaps.
    *
    * @since    5.0
    * @param    aSource The source bitmap.
    * @param    aCopyOnly If ETrue, doesn't apply effect.
    * @return   The new bitmap.
    */
    CFbsBitmap* CopyAndApplyEffectL( const CFbsBitmap* aSource, TBool aCopyOnly = EFalse );
    
    CAknDoubleSpanScrollIndicatorItem* LoadScrollIndicatorItemL(
            const TAknsItemID &aTopId,
            const TAknsItemID &aMidId,
            const TAknsItemID &aBottomId);

    void DrawTiled(
            CWindowGc& aGc, const TRect& aRect, 
            CAknDoubleSpanScrollIndicatorItem *aIndicatorItem) const;
    
    void UpdateScrollBarLayout();
    
private: // data
    TInt iScrollSpan;           // Size of the scrolled list.
    TInt iFocusPosition;        // Position of the current field in the list.
    TInt iWindowSize;           // Size of the visible part of the list. 
    TInt iFieldPosition;        // Size of the current field. (Optional double span)
    TInt iFieldSize;            // Position inside the current field. (Optional double span)
    TBool iOwnsWindow;            // Is window owning
    TInt iSpare;

    TRect iBackgroundRect;       // Rect for scrollbar background.
    TRect iHandleBackgroundRect; // Rect for scrollbar handle background.
    TRect iHandleRect;           // Rect for scrollbar handle. 
    
    TBool iTransparentBackground;  // A flag which tells if we have transparent bg
    TBool iDrawBackground; // do  we draw any background
    
    TBool iHandleHighlight; // is handle drag highlight on?
    
    TBool iBackgroundHighlight; //is background highlight on?
   
    
    mutable TBool iDrawBackgroundBitmap; // do we draw the background to the background bitmap before it is drawn
    TRect iOldRect; // the old scb retangle, to optimize unneccessary resizing

    CEikScrollBar::TOrientation iOrientation;    // Vertical or horizontal scrollbar
    
    CAknDoubleSpanScrollIndicatorItem* iBackgroundBar;
    CAknDoubleSpanScrollIndicatorItem* iHighlightBackgroundBar;
    CAknDoubleSpanScrollIndicatorItem* iHandleBar;
    CAknDoubleSpanScrollIndicatorItem* iHighlightHandleBar;
 
    
    TInt iHeadItemSize;
    TInt iMidItemSize;
    TInt iTailItemSize;
    
    CCoeControl* iTouchAreaControl; // Not own.
    };

#endif

