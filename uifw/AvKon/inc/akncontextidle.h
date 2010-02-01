/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  A default control in the status pane's context pane when 
*                status pane in the idle layout. 
*
*/


#ifndef C_AKNCONTEXTIDLE_H
#define C_AKNCONTEXTIDLE_H

// INCLUDE FILES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CAknSkinnableClock;

/**
 * Container control for skinnable clock displayed in the
 * context pane area of idle status pane.
 *
 * @lib avkon.lib
 */
NONSHARABLE_CLASS( CAknIdleContextPane ) : public CCoeControl
	{

public:

    /**
    * Standard constructor.
    */
    CAknIdleContextPane();
    
    /**
    * Destructor.
    */
    ~CAknIdleContextPane();
        
    /** 
    * Construct from resources.
    *
    * @param  aReader  Resource reader.
    */
    void ConstructFromResourceL( TResourceReader& aReader );

public: // From base class @c CCoeControl.

    /**
    * Returns the number of component controls.
    *
    * @return Amount of component controls.
    */
    TInt CountComponentControls() const;

    /**
    * Returns the specified component control.
    *
    * @param  aIndex  Index of the control.
    *
    * @return Pointer to the component control.
    */
    CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
    * Sets dimming state.
    *
    * @param  aDimmed  @c ETrue to set the control dimmed,
    *                  @c EFalse otherwise.
    */
	void SetDimmed( TBool aDimmed );

    /**
    * Handles the resource change events.
    *
    * @param  aType  Type of the resource change event.
    */
    void HandleResourceChange( TInt aType );
    
    
    /**
    * Handles visibility change events.
    *
    * @param  aType  @c ETrue to make the control visible,
    *                @c EFalse otherwise.
    */
    virtual void MakeVisible( TBool aVisible );

protected: // From base class @c CCoeControl.

    /**
    * Handles the size change events.
    */
    void SizeChanged();

private: // From base class @c CCoeControl.

    /**
    * Draws the control.
    */
    void Draw( const TRect& aRect ) const;

private:

    /**
    * Contained skinnable clock control.
    * Own.
    */
    CAknSkinnableClock* iClock;
    };

#endif // C_AKNCONTEXTIDLE_H
