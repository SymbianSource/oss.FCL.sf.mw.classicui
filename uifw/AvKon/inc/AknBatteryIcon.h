/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Control to show signal icon indicator on the
*                status pane's battery pane.
*
*/


#ifndef AKNBATTERYICON_H
#define AKNBATTERYICON_H

#include <coecntrl.h>


/**
* A battery icon control in the status pane's battery pane
* The control draws battery icon indicator graphics.
*/

NONSHARABLE_CLASS(CAknBatteryIcon) : public CCoeControl
	{
public:    
    /**
    * Destructor
    */
    ~CAknBatteryIcon();

    static CAknBatteryIcon* NewL();

    static CAknBatteryIcon* NewLC();
    
public: // From CCoeControl

    /**
    * From CCoeControl. Handles a change to the control's resources.
    */
    void HandleResourceChange( TInt aType );
    
public:
    
    /**
    * Changes the battery icon based on the indicator state.
    * @param  aIconState  State to be set, @see TAknBatteryIndicatorStates
    */
    void SetBatteryIconL( TInt aIconState );
    
    /**
    * Returns the current battery icon state.
    */
    TInt IconState();
    
protected: // From CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    void SizeChanged();

    /**
    * From CCoeControl. Handles the position change events.
    */
	void PositionChanged();

private: // From CCoeControl
    virtual void Draw( const TRect& aRect ) const;

private:
    /**
    * Standard constructor
    */
    CAknBatteryIcon();

    void ConstructL();

    void UpdateColorBitmapL( TInt aColorIndex );

    void DrawInNormalStatusPane( const TRect& aRect ) const;

    void DrawInStaconPane( const TRect& aRect ) const;

    void DrawInFlatStatusPane( const TRect& aRect ) const;
    
private:
    CFbsBitmap* iBatteryIcon;
    CFbsBitmap* iBatteryIconMask;
    TInt        iColorIndex;
    TInt        iIconState;
    };

#endif // AKNBATTERYICON_H
