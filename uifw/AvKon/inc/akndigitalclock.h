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
* Description:  Digital clock control for status pane.
*
*/


#ifndef C_AKNDIGITALCLOCK_H
#define C_AKNDIGITALCLOCK_H

// INCLUDES
#include <AknControl.h>

// FORWARD DECLARATIONS
class CAknDigitalClockChangeHandler;

// CLASS DECLARATION

/**
* Clock control that displays simple digital clock without skinning.
*
* This class is not intended for further derivation.
*
* @since 3.1
*
* @internal
*/
NONSHARABLE_CLASS( CAknDigitalClock ) : public CAknControl
    {
public: // Constructors and destructor

    /**
    * Two-phased constructor.
    *
    * @param  aContainerWindow  Container window for the clock component.
    *
    * @param  aInStatusPane     Specifies whether or not this control
    *                           is used in the status pane's clock pane.
    *
    * @return Newly constructed object.
    */
    static CAknDigitalClock* NewL( CCoeControl* aContainerWindow,
                                   TBool aInStatusPane = EFalse );

    /**
    * Destructor.
    */
    virtual ~CAknDigitalClock();

public: // New functions

    /**
     * Sets color.
     */
    void SetColor( TRgb aColor );

    /**
     * Sets layout for the time. This method automatically
     * overrides given font, align and rects. Color is not overridden.
     */
    void SetTimeLayout( TAknTextLineLayout aTimeLayout );

    /**
     * Clears given layout.
     */
    void ClearTimeLayout();

    /**
     * Starts the clock timer.
     * Used when the clock becomes visible.
     */
    void StartTimer();

    /**
     * Stops the clock timer.
     * Used when the clock becomes non-visible.
     */
    void StopTimer();
    
    /**
     * Adjusts the clock position in status pane in certain status pane
     * layouts when time format is changed.
     */
    void AdjustPositionL();

private: // New functions

    /**
     * Timer callback for clock updates
     *
     * @param aThis Pointer to the skinnable clock instance.
     *
     * @return Always returns @c KErrNone.
     */
    static TInt TimerCallback( TAny* aThis );

public: // Functions from CCoeControl

    /**
     * Handles the resource change.
     *
     * @param  aType  Resource change type.
     */
    void HandleResourceChange( TInt aType );

private: // Functions from @c CCoeControl

    /**
     * Draws the clock.
     *
     * @param aRect Not used.
     */
    void Draw( const TRect& aRect ) const;

private:

    /**
     * C++ default constructor.
     */
    CAknDigitalClock( TBool aInStatusPane );

    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();

public:
    /**
     * From @c CCoeControl.
     *
     * Handles pointer events by changing clock between digital/analog.
     *
     * @param  aPointerEvent  Pointer event to be handled.
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

private: // Member data

    CPeriodic*                      iTimer;
    CAknDigitalClockChangeHandler*  iHandler;
    TRgb                            iColor;
    TAknTextLineLayout              iTimeLayout;
    TBool                           iTimeLayoutInUse;
    TInt                            iTimeFormat;
    TInt                            iFlags;
    };

#endif // C_AKNDIGITALCLOCK_H

// End of File
