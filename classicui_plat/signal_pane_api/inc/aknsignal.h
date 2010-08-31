/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef AKNSIGNAL_H
#define AKNSIGNAL_H

#include <coecntrl.h>

class CEikImage;
class CAknSignalPaneExtension;
class CAknSignalIcon;
class CAknSignalStrength;
class CAknSignalDataObserver;

/**
* A default control in the status pane's signal pane
* The control draws signal strength indicator graphics.
*/

class CAknSignalPane : public CCoeControl
	{
public:
    /**
    * Standard constructor
    */
    IMPORT_C CAknSignalPane();

    /**
    * Destructor
    */
    IMPORT_C ~CAknSignalPane();

    /**
    * Resource constructor.
    * @param aReader Resource reader.
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    /**
    * Sets signal strength value to the signal indicator.
    * @param aLevel Signal strength value ( 0 - 7 ).
    */
    IMPORT_C void SetSignalLevel(TInt aLevel);

    /**
    * Gets signal strength value from the signal indicator.
    * @return Signal strength value ( 0 - 7 ).
    */
    TInt SignalLevel();

    /**
    * Gets signal state value from the signal indicator.
    * @return Signal state value.
    */
    TInt SignalState();

    /**
    * Disables possible icon animation.
    */
    void DisableAnimation();
    
    /** 
    * Set GPRS state. Available GRRS state are:
    * EAknSignalGprsIndicatorOff, EAknSignalGprsIndicatorAvailable,
    * EAknSignalGprsIndicatorContext, EAknSignalGprsIndicatorSuspended,
    * EAknSignalGprsIndicatorMultipdp.
    * 
    * @param aGprsIconState GPRS state.
    */
    IMPORT_C void ShowGprsIcon(TInt aGprsIconState);

    /**
    * Set common packet data state. Available states are:
    * EAknSignalCommonPacketDataIndicatorOff,
    * EAknSignalCommonPacketDataIndicatorAvailable,
    * EAknSignalCommonPacketDataIndicatorContext,
    * EAknSignalCommonPacketDataIndicatorSuspended,
    * EAknSignalCommonPacketDataIndicatorMultipdp.
    * 
    * @param aCommonPacketDataIconState Common packet data state.
    * @since 2.6
    */
    IMPORT_C void ShowCommonPacketDataIcon(TInt aCommonPacketDataIconState);

    /**
    * Set WCDMA state. Available WCDMA states are:
    * EAknSignalWcdmaIndicatorOff,
    * EAknSignalWcdmaIndicatorAvailable,
    * EAknSignalWcdmaIndicatorAttached,
    * EAknSignalWcdmaIndicatorEstablishingContext,
    * EAknSignalWcdmaIndicatorContext,
    * EAknSignalWcdmaIndicatorMultipdp
    * 
    * @param aWcdmaIconState WCDMA state.
    * @since 2.6
    */
    IMPORT_C void ShowWcdmaIcon(TInt aWcdmaIconState);

    /**
    * Set HSDPA state. Available HSDPA states are:
    * EAknSignalHsdpaIndicatorOff,
    * EAknSignalHsdpaIndicatorAvailable,
    * EAknSignalHsdpaIndicatorAttached,
    * EAknSignalHsdpaIndicatorEstablishingContext,
    * EAknSignalHsdpaIndicatorContext,
    * EAknSignalHsdpaIndicatorMultipdp
    * 
    * @param aHsdpaIconState HSDPA state.
    * @since 3.1
    */
    IMPORT_C void ShowHsdpaIcon(TInt aHsdpaIconState);

    /**
    * Set CDMA state. Available CDMA states are:
    * EAknSignalCdmaIndicatorOff,
    * EAknSignalCdmaIndicatorNoService,
    * EAknSignalCdmaIndicatorAvailable,
    * EAknSignalCdmaIndicatorNotAvailable, 
    * EAknSignalCdmaIndicatorActive,
    * EAknSignalCdmaIndicatorDormant,
    * EAknSignalCdmaIndicatorSending,
    * EAknSignalCdmaIndicatorReceiving
    *
    * @param aCdmaIconState CDMA state.
    * @since 2.7
    */
    IMPORT_C void ShowCdmaIcon(TInt aCdmaIconState);

    /**
    * Set EDGE (egprs) state. Available EDGE states are:
    * EAknSignalEdgeIndicatorOff,
    * EAknSignalEdgeIndicatorAvailable,
    * EAknSignalEdgeIndicatorAttached,
    * EAknSignalEdgeIndicatorEstablishingContext,
    * EAknSignalEdgeIndicatorContext,
    * EAknSignalEdgeIndicatorMultipdp
    * 
    * @param aEdgeIconState EDGE state.
    * @since 3.0
    */
    IMPORT_C void ShowEdgeIcon(TInt aEdgeIconState);


    /**
    * @deprecated
    *
    * Set the background type. This method is used by the UI framework for 
    * for syncronizing this components background type with navipane 
    * background type.
    *
    * Available backgroud types are:
    *      EAknNaviPaneBackgroundTypeNotDefined
    *      EAknNaviPaneBackgroundTypeWipe
    *      EAknNaviPaneBackgroundTypeSolid
    *
    * @param aType Background type.
    * @since 2.1
    */
    IMPORT_C void SetNaviPaneBackgroundType(TInt aType);

public:
    /**
    * From CCoeControl. Handles pointer event
    * @param aPointerEvent Pointer event to be handled
    */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

protected: // From CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    IMPORT_C void SizeChanged();

    /**
    * From CCoeControl. Handles the position change events.
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

private:
    IMPORT_C void ConstructL();

private: // From CCoeControl
    IMPORT_C virtual void Draw(const TRect& aRect) const;

private:
   	static TInt TickerCallback(TAny* aThis);
    TInt DoTick();
    void DrawInNormalStatusPane(const TRect& aRect) const;
    void DrawInSmallStatusPane(const TRect& aRect) const;
    void DrawInFlatStatusPane(const TRect& aRect) const;
    void DrawInStaconPane(const TRect& aRect) const;
    CFbsBitmap* SignalIconBitmap() const;
    CFbsBitmap* SignalIconBitmapMask() const;
    void SetContainerWindowNonFading(TBool aNonFading);    
	void LoadSignalIconL(TInt aIconState, TInt aColorIndex);

private:
    // Private flags for internal statemachines, iSpare taken into use
    TInt iPrivateFlags;
    CAknSignalIcon* iSignalIconControl;
    CAknSignalStrength* iSignalStrengthControl;
   	CPeriodic* iTicker;
    CAknSignalDataObserver* iDataObserver;
    TInt iSignalState;
	CAknSignalPaneExtension* iExtension;
    };

#endif // AKNSIGNAL_H
