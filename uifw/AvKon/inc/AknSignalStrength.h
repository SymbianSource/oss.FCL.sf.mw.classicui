/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Control to show signal strength indicator on the
*                status pane's signal pane.
*
*/


#ifndef AKNSIGNALSTRENGTH_H
#define AKNSIGNALSTRENGTH_H

#include <coecntrl.h>


/**
* A signal icon control in the status pane's signal pane
* The control draws signal icon indicator graphics.
*/

NONSHARABLE_CLASS(CAknSignalStrength) : public CCoeControl
	{
public:
    
    /**
    * Destructor
    */
    ~CAknSignalStrength();

	static CAknSignalStrength* NewL();

    static CAknSignalStrength* NewLC();

    void SetSignalLevel(TInt aLevel);

    TInt SignalLevel();
protected: // From CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    void SizeChanged();

    /**
    * From CCoeControl. Handles the position change events.
    */
	void PositionChanged();

    /**
	 * Handles a change to the control's resources of type aType
	 * which are shared across the environment.
	 * @param aType Event type.
	 */
	void HandleResourceChange( TInt aType );

          
private: // From CCoeControl
    virtual void Draw(const TRect& aRect) const;

private:
    /**
    * Standard constructor
    */
    CAknSignalStrength();

    void LoadDefaultBitmapsL();

    void LoadStaconBitmapsL();

    void LoadFlatBitmapsL();
    
    void DeleteBitmaps();

    void DrawInNormalStatusPane(const TRect& aRect) const;

    void DrawInStaconPane(const TRect& aRect) const;

    void DrawInFlatStatusPane(const TRect& aRect) const;

private:
    TInt        iSignalLevel;
    TInt        iDefaultSignalBitmapOffset;
    TInt        iStaconSignalBitmapOffset;
    TInt        iFlatSignalBitmapOffset;

    CFbsBitmap* iDefaultSignalIndicatorBitmap;
    CFbsBitmap* iDefaultSignalIndicatorBitmapMask;
    CFbsBitmap* iDefaultNoSignalIndicatorBitmap;
    CFbsBitmap* iDefaultNoSignalIndicatorBitmapMask;

    CFbsBitmap* iStaconLeftSideSignalIndicatorBitmap;
    CFbsBitmap* iStaconLeftSideSignalIndicatorBitmapMask;
    CFbsBitmap* iStaconRightSideSignalIndicatorBitmap;
    CFbsBitmap* iStaconRightSideSignalIndicatorBitmapMask;    
    CFbsBitmap* iStaconNoSignalIndicatorBitmap;
    CFbsBitmap* iStaconNoSignalIndicatorBitmapMask;

    CFbsBitmap* iFlatSignalIndicatorBitmap;
    CFbsBitmap* iFlatSignalIndicatorBitmapMask;
    CFbsBitmap* iFlatNoSignalIndicatorBitmap;
    CFbsBitmap* iFlatNoSignalIndicatorBitmapMask;

    TSize       iLastDefaultSize;
    TSize       iLastStaconSize;
    TSize       iLastFlatSize;
    };

#endif // AKNSIGNALSTRENGTH_H
