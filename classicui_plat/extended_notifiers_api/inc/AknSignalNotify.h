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
* Description:  AVKON Notifier client for setting signal pane data.
*
*/


#ifndef __AKNSIGNALNOTIFY_H__
#define __AKNSIGNALNOTIFY_H__

#include <AknNotify.h>

NONSHARABLE_CLASS( CAknSignalNotify ) : public CAknNotifyBase
    {
    // Friend class is the system application that can change state of 
    // signal indicator. 
    friend class CSysApAppUi;

    friend class CIndicViewContainer;

private:

    /**
    * Two-phased constructor.
    */
    IMPORT_C static CAknSignalNotify* NewL();
    
    /**
    * Two-phased constructor.
    */
    IMPORT_C static CAknSignalNotify* NewLC();
    
    /**
    * Destructor.
    */
    IMPORT_C ~CAknSignalNotify();

    /**
    * Set signal level to the signal pane on the status pane.
    * This method is also used to set signal pane to show offline mode
    * icon by using @c KAknSignalOffLineMode as the @c aLevel parameter.
    *
    * @param  aLevel  Signal level (0-7 or @c KAknSignalOffLineMode).
    */
    IMPORT_C void SetSignalLevelL( TInt aLevel );

    /**
    *  Set GPRS indicator state.
    *
    *  Note that the @c EAknSignalGprsIndicatorOff can only be set if
    *  the previous signal state was one of the GPRS states.
    *
    *  Available states from @c avkon.hrh:
    *    - EAknSignalGprsIndicatorOff = 0,
    *    - EAknSignalGprsIndicatorAvailable,  // Same as EAknSignalGprsIndicatorOff
    *    - EAknSignalGprsIndicatorAttached,
    *    - EAknSignalGprsIndicatorEstablishingContext,
    *    - EAknSignalGprsIndicatorContext,
    *    - EAknSignalGprsIndicatorSuspended
    *
    *  @param aGprsState GPRS indicator state.
    */
    IMPORT_C void SetGprsStateL( TInt aGprsState );

    /**
    *  Set Common packet data indicator state.
    *
    *  Note that the @c EAknSignalCommonPacketDataIndicatorOff can only
    *  be set if the previous signal state was one of the
    *  Common packet data states.
    *
    *  Available states from @c avkon.hrh:
    *   - EAknSignalCommonPacketDataIndicatorOff = 0x100,
    *   - EAknSignalCommonPacketDataIndicatorAvailable, // Same as EAknSignalCommonPacketDataIndicatorOff
    *   - EAknSignalCommonPacketDataIndicatorAttached,
    *   - EAknSignalCommonPacketDataIndicatorEstablishingContext,
    *   - EAknSignalCommonPacketDataIndicatorContext,
    *   - EAknSignalCommonPacketDataIndicatorSuspended,
    *   - EAknSignalCommonPacketDataIndicatorMultipdp
    *
    *  @since 2.6
    *
    *  @param  aCommonPacketDataState  Common packet data indicator state.
    */
    IMPORT_C void SetCommonPacketDataStateL( TInt aCommonPacketDataState );

    /**
    *  Set EDGE indicator state.
    *
    *  Note that the @c EAknSignalEdgeIndicatorOff can only be set if
    *  the previous signal state was one of the EDGE states.
    *
    *  Available states from @c avkon.hrh:
    *   - EAknSignalEdgeIndicatorOff = 0x400,
    *   - EAknSignalEdgeIndicatorAvailable,
    *   - EAknSignalEdgeIndicatorAttached,
    *   - EAknSignalEdgeIndicatorEstablishingContext, 
    *   - EAknSignalEdgeIndicatorContext,
    *   - EAknSignalEdgeIndicatorSuspended,
    *   - EAknSignalEdgeIndicatorMultipdp    
    *
    *  @since 3.0
    *
    *  @param  aEdgeState  EDGE indicator state.
    */
    IMPORT_C void SetEdgeStateL( TInt aEdgeState );

    /**
    *  Set WCDMA indicator state.
    *
    *  Note that the @c EAknSignalWcdmaIndicatorOff can only be set if
    *  the previous signal state was one of the WCDMA states.
    *
    *  Available states from @c avkon.hrh:
    *   - EAknSignalWcdmaIndicatorOff = 0x200,  
    *   - EAknSignalWcdmaIndicatorAvailable,  
    *   - EAknSignalWcdmaIndicatorAttached,
    *   - EAknSignalWcdmaIndicatorEstablishingContext, 
    *   - EAknSignalWcdmaIndicatorContext,
    *   - EAknSignalWcdmaIndicatorMultipdp
    *   - EAknSignalWcdmaIndicatorSuspended
    *   
    *  @since 2.6
    *
    *  @param  aWcdmaState  WCDMA indicator state.
    */
    IMPORT_C void SetWcdmaStateL( TInt aWcdmaState );

    /**
    *  Set HSDPA indicator state.
    *
    *  Note that the @c EAknSignalHsdpaIndicatorOff can only be set if
    *  the previous signal state was one of the HSDPA states.
    *
    *  Available states from @c avkon.hrh:
    *   - EAknSignalHsdpaIndicatorOff 
    *   - EAknSignalHsdpaIndicatorAvailable,
    *   - EAknSignalHsdpaIndicatorAttached,
    *   - EAknSignalHsdpaIndicatorEstablishingContext, 
    *   - EAknSignalHsdpaIndicatorContext,
    *   - EAknSignalHsdpaIndicatorSuspended,
    *   - EAknSignalHsdpaIndicatorMultipdp    
    *
    *  @since 3.1
    *
    *  @param  aHsdpaState  HSDPA indicator state.
    */
    IMPORT_C void SetHsdpaStateL( TInt aHsdpaState );

    /** 
    *  Set CDMA indicator state.
    *
    *  The CDMA states can only be used if the @c __PROTOCOL_CDMA feature
    *  flag has been defined.
    *
    *  Note that the @c EAknSignalCdmaIndicatorOff can only be set if
    *  the previous signal state was one of the CDMA states.
    *
    *  Available states from @c avkon.hrh:
    *  - EAknSignalCdmaIndicatorOff = 0x300,
    *  - EAknSignalCdmaIndicatorNoService,  
    *  - EAknSignalCdmaIndicatorAvailable,
    *  - EAknSignalCdmaIndicatorNotAvailable, 
    *  - EAknSignalCdmaIndicatorActive,
    *  - EAknSignalCdmaIndicatorDormant,
    *  - EAknSignalCdmaIndicatorSending,
    *  - EAknSignalCdmaIndicatorReceiving
    *
    *  @since 2.7
    *
    *  @param  aCdmaState  CDMA indicator state.
    */
    IMPORT_C void SetCdmaStateL( TInt aCdmaState );

private:

    /**
    * Default C++ constructor.
    */
    CAknSignalNotify();
    
    
    /**
    * Second-phase constructor.
    */
    void ConstructL();
    
    /**
    * Sends the signal state change request.
    *
    * @param  aState  New signal state.
    */
    void SetStateL( TInt aState );

private:

    /**
    * Reserved for future use.
    */
    IMPORT_C void CAknNotifyBase_Reserved();
    };

#endif // __AKNSIGNALNOTIFY_H__
