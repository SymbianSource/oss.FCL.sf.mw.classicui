/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef AKNBATTERY_H
#define AKNBATTERY_H

#include <coecntrl.h>

class CEikImage;
class CAknBatteryIcon;
class CAknBatteryStrength;
class CAknBatteryDataObserver;

/**
* A default control in the status pane's battery pane. 
* The control draws battery strength indicator graphics.
*/
class CAknBatteryPane : public CCoeControl
    {
public:
    /**
    * Constructor.
    */
    IMPORT_C CAknBatteryPane();

    /**
    * Destructor.
    */
    IMPORT_C ~CAknBatteryPane();
    
    /**
    * Resource constructor.
    * @param aReader Resource reader.
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
    /**
    * Sets battery strength value to the battery indicator.
    * @param aLevel Battery strength value ( 0 - 7 ).
    */
    IMPORT_C void SetBatteryLevel(TInt aLevel);

    /**
    * Gets battery strength value from the battery indicator.
    * @return Battery strength value ( 0 - 7 ).
    */
	TInt BatteryLevel();

    /**
    * Sets battery recharging animation on/off.
    * @param aRecharging ETrue if animation is to be shown.
    */
    void SetRecharge(TBool aRecharging);

    /**
    * Tells if battery recharging animation is on/off.
    * @return ETrue if animation is to be shown.
    */
	TBool Recharging();
	
	/**
    * Gets the battery state value from the battery indicator.
    * @return  Battery state value.
    */
    TInt BatteryState();
    
    /**
    * Sets the battery state value for the battery indicator.
    * @param  aState  Battery state value.
    */
    void SetBatteryStateL( TInt aState );

protected: // From CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    IMPORT_C void SizeChanged();

    /**
    * From CCoeControl. Handle the position change events.
    */
	IMPORT_C void PositionChanged();

    /**
	 * Handles a change to the control's resources of type aType
	 * which are shared across the environment.
	 * @param aType Event type.
	 */
    IMPORT_C void HandleResourceChange( TInt aType );

    /**
    * From CCoeControl. Returns number of controls inside the context pane control.
    * @return Number of component controls.
    */
    IMPORT_C TInt CountComponentControls() const;

    /**
    * From CCoeControl. Returns a control determined by control id.
    * @param anIndex Index of a control to be returned.
    * @return Pointer to control
    */
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
    
public:
    /**
    * From CCoeControl. Handles pointer event
    * @param aPointerEvent Pointer event to be handled
    */
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
    IMPORT_C void ConstructL();
    
private: // From CCoeControl
    IMPORT_C virtual void Draw(const TRect& aRect) const;

private:
    void DrawInNormalStatusPane(const TRect& aRect) const;
    void DrawInFlatStatusPane(const TRect& aRect) const;
    void DrawInStaconPane(const TRect& aRect) const;
    void SetContainerWindowNonFading(TBool aNonFading);
	static TInt TickerCallback(TAny* aThis);
	TInt DoTick();
    
private:
    CAknBatteryIcon*         iBatteryIconControl;
    CAknBatteryStrength*     iBatteryStrengthControl;
    TInt                     iPrivateFlags;
    TInt                     iBatteryLevel;    
    CAknBatteryDataObserver* iDataObserver;
    CPeriodic* 			     iTicker;
    TBool                    iIsActiveIdle;
    };

#endif // AKNBATTERY_H
