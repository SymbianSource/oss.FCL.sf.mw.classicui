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
* Description:  Control to show battery strength indicator on the
*                status pane's battery pane.
*
*/


#ifndef AKNBATTRERYSTRENGTH_H
#define AKNBATTRERYSTRENGTH_H

#include <coecntrl.h>


/**
* A signal icon control in the status pane's signal pane
* The control draws signal icon indicator graphics.
*/

NONSHARABLE_CLASS(CAknBatteryStrength) : public CCoeControl
	{
public:
    
    /**
    * Destructor
    */
    ~CAknBatteryStrength();

	static CAknBatteryStrength* NewL();

    static CAknBatteryStrength* NewLC();

    void SetBatteryLevel(TInt aLevel);

    TInt BatteryLevel();

    void SetRecharging(TBool aRecharging);

    TBool Recharging();

public: // From CCoeControl

    /**
	 * Handles a change to the control's resources of type aType
	 * which are shared across the environment.
	 * @param aType Event type.
	 */
	void HandleResourceChange( TInt aType );

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
    virtual void Draw(const TRect& aRect) const;

private:
    /**
    * Standard constructor
    */
    CAknBatteryStrength();

    void LoadDefaultBitmapsL();

    void LoadStaconBitmapsL();

    void LoadFlatBitmapsL();
    
    void DeleteBitmaps();

    void DrawInNormalStatusPane(const TRect& aRect) const;

    void DrawInStaconPane(const TRect& aRect) const;

    void DrawInFlatStatusPane(const TRect& aRect) const;
    
private:
    TInt        iBatteryLevel;
    TBool       iRecharging;
    TInt        iDefaultBatteryBitmapOffset;
    TInt        iStaconBatteryBitmapOffset;
    TInt        iFlatBatteryBitmapOffset;
    
    CFbsBitmap* iDefaultBatteryIndicatorBitmap;
    CFbsBitmap* iDefaultBatteryIndicatorBitmapMask;
    
    CFbsBitmap* iStaconLeftSideBatteryIndicatorBitmap;
    CFbsBitmap* iStaconLeftSideBatteryIndicatorBitmapMask;
    CFbsBitmap* iStaconRightSideBatteryIndicatorBitmap;
    CFbsBitmap* iStaconRightSideBatteryIndicatorBitmapMask;

    CFbsBitmap* iFlatBatteryIndicatorBitmap;
    CFbsBitmap* iFlatBatteryIndicatorBitmapMask;

    TSize        iLastDefaultSize;
    TSize        iLastStaconSize;
    TSize        iLastFlatSize;
    };

#endif // AKNBATTERYSTRENGTH_H
