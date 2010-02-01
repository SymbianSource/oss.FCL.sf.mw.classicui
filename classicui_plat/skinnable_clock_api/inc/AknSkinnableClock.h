/*
* Copyright (c) 2006-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Control for AVKON's skinnable clock.
*
*/


#ifndef C_AKNSKINNABLECLOCK_H
#define C_AKNSKINNABLECLOCK_H

// INCLUDES
#include <coecntrl.h>
#include <e32property.h>
#include <hwrmlight.h>

// FORWARD DECLARATIONS
class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;
class CAknSkinnableClockChangeHandler;
class CAknSkinnableClockFace;
class CAknSkinnableClock;

/**
 * Clock control that displays analogue or digital clock with skinning.
 *
 * This is a public (non-SDK) class visible outside the library.
 * This class is not intended for further derivation.
 *
 * @since 2.0
 *
 * @internal
 */
NONSHARABLE_CLASS( CAknSkinnableClock ) : public CCoeControl,
                                          public MCoeControlHitTest,
                                          public MCoeMessageMonitorObserver, 
                                          public MHWRMLightObserver
    {
public: // Constructors and destructor

    /**
    * Two-phased constructor.
    *
    * @since 2.0
    *
    * @param  aContainerWindow   Container window for the clock component.
    *
    * @param  aFormatFromLocale  Boolean flag to indicate whether the clock
    *                            format should be updated from the locale.
    *
    * @param  aContextPaneClock  Boolean flag that indicates whether the
    *                            clock is in the context pane.
    *
    * @return Newly constructed object.
    */
    IMPORT_C static CAknSkinnableClock* NewL( CCoeControl* aContainerWindow,
                                              const TBool aFormatFromLocale,
                                              const TBool aContextPaneClock );

    /**
    * Destructor.
    */
    IMPORT_C virtual ~CAknSkinnableClock();

public: // New functions

    /**
    * Updates the double buffer and redraws the clock.
    */
    IMPORT_C void UpdateDisplay();

    /**
    * Sets the format of the clock.
    *
    * @param  aFormat  New clock format.
    */
    IMPORT_C void SetFormatL( const TClockFormat aFormat );


    /**
    * Updates time and locale state of the clock.
    */
    void TimeOrLocaleChanged();

private: // New functions


    /**
    * Timer callback for clock updates
    *
    * @param  aThis  Pointer to the skinnable clock instance.
    *
    * @return Always returns @c KErrNone.
    */
    static TInt TimerCallback( TAny* aThis );

    /**
    * Gets the display mode for the buffer.
    *
    * @return Display mode suitable for the buffer.
    */
    TDisplayMode BufferDisplayMode();

    /**
    * Checks whether the clock is currently in the context pane.
    *
    * @return @c ETrue if the clock is visible in context pane,
    *         @c EFalse otherwise.
    */
    TBool IsVisibleInContextPane() const;

    /**
    * Starts the clock timer.
    * Used when the clock gains visibility.
    */
    void StartTimer();

    /**
    * Stops the clock timer.
    * Used when the clock loses visibility.
    */
    void StopTimer();

    /**
    * Called when the clock control gains foreground.
    */
    void ForegroundGainedL();

public: // From base class @c CCoeControl.

    /**
    * Handles the resource change events.
    *
    * @param  aType  Resource change type.
    */
    void HandleResourceChange( TInt aType );

    /**
    * Check if pointer event should be handled or not,
    * If in idle - then handle.
    *
    * @param  aPoint    The position to test.
    * @param  aControl  Control.
    *
    * @return @c ETrue if pointer event should be handled, @c EFalse if not.
    */
    TBool HitRegionContains( const TPoint &aPoint,
                             const CCoeControl &aControl ) const;

    /**
    * Responds to changes in the position of the control.
    */
    IMPORT_C virtual void PositionChanged();

public: // From base class @c MCoeMessageMonitorObserver.

    /**
    * Used to receive event from window server
    * when the visibility of the window changes.
    *
    * @param  aEvent  The window server event.
    */
    void MonitorWsMessage( const TWsEvent& aEvent );

private: // From base class @c CCoeControl.

    /**
    * Draws the clock.
    *
    * @param  aRect  The rectangle to be drawn.
    */
    void Draw( const TRect& aRect ) const;

private:

    /**
    * C++ default constructor.
    *
    * @param  aFormatFromLocale  Boolean flag to indicate whether the clock
    *                            format should be updated from the locale.
    *
    * @param  aContextPaneClock  Boolean flag that indicates whether the
    *                            clock is in the context pane.
    */
    CAknSkinnableClock( const TBool aFormatFromLocale,
                        const TBool aContextPaneClock );

    /**
    * Second-phase constructor.
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

public: // From base class @c CCoeControl.

    /**
    * Handles pointer events by launching the clock application.
    *
    * @param  aPointerEvent  Pointer event to be handled.
    */
    IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );

    /**
    * Changes the control visibility.
    *
    * @param  aVisible  @c ETrue to make the control visible,
    *                   @c EFalse otherwise.
    */
    virtual void MakeVisible( TBool aVisible );

protected: // From base class @c CCoeControl.

    /**
    * Handles size change events.
    */
    void SizeChanged();

private:

    /**
     * From MHWRMLightObserver
     * @since Series 60 3.1
     */
    void LightStatusChanged(TInt aTarget, CHWRMLight::TLightStatus aStatus);

private: // Member data

    /**
    * Clock timer.
    * Own.
    */
    CPeriodic* iTimer;

    /**
    * Change handler to monitor changes in system time or locale.
    * Own.
    */
    CAknSkinnableClockChangeHandler* iHandler;

    /**
    * Double buffer to which the clock graphics are drawn.
    * Own.
    */
    CFbsBitmap* iDoubleBuffer;

    /**
    * The graphics device into which the double buffer is drawn.
    * Own.
    */
    CFbsBitmapDevice* iDoubleBufferDev;

    /**
    * Graphics context for the double buffer.
    * Own.
    */
    CFbsBitGc* iDoubleBufferGc;

    /** Current display format of the clock. */
    TClockFormat iClockFormat;

    /** Defines whether or not the clock format is updated from the locale. */
    TBool iFormatFromLocale;

    /** Defines whether or not the clock control is in the status pane. */
    TBool iContextPaneClock;

    /**
    * Pointer to the class which draws the time graphics to the double buffer.
    * Own.
    */
    CAknSkinnableClockFace* iFace;

    /**
    * Defines whether or not the clock control has full or
    * partial foreground.
    */
    TBool iInForeground;

    /** Contains the time currently drawn to the bitmap. */
    TDateTime iTimeInBitmap;

    /** For registering MHWRMLightObserver. */
    CHWRMLight* iLight;
    };

#endif // C_AKNSKINNABLECLOCK_H

// End of File
