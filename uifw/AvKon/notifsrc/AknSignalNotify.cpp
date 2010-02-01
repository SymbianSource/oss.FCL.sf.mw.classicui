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


#include "AknSignalNotify.h"
#include <AknNotifyStd.h>
#include <avkon.hrh>
#include <AknNotifySignature.h>

// ---------------------------------------------------------------------------
// CAknSignalNotify::NewL
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSignalNotify* CAknSignalNotify::NewL()
    {
    CAknSignalNotify* self = NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::NewLC
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSignalNotify* CAknSignalNotify::NewLC()
    {
    CAknSignalNotify* self = new (ELeave) CAknSignalNotify;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::~CAknSignalNotify
// Destructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSignalNotify::~CAknSignalNotify()
    {
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::CAknSignalNotify
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknSignalNotify::CAknSignalNotify() : CAknNotifyBase( KAknSignalNotifierUid )
    {
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::ConstructL
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknSignalNotify::ConstructL()
    {
    CAknNotifyBase::ConstructL();
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::SetSignalLevelL
// Sets the signal level of the signal pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalNotify::SetSignalLevelL( TInt aLevel )
    {
    TPckgBuf< SAknNotifierPackage<SAknSignalNotifyParams> >  pckg;
    pckg().iParamData.iGprsState = EAknSignalGprsStateNotChanged;
    pckg().iParamData.iValue     = aLevel;
    TBuf8<1> resp;
    StartOrUpdateL( pckg, resp );
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::SetGprsStateL
// Sets a GPRS icon to the signal pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalNotify::SetGprsStateL( TInt aGprsState )
    {
    if ( aGprsState >= 0 && aGprsState <= KAknSignalNumberOfGprsStates )
        {
        SetStateL( aGprsState );
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::CAknNotifyBase_Reserved
// Reserved for future use.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalNotify::CAknNotifyBase_Reserved()
    {
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::SetWcdmaStateL
// Sets a WCDMA icon to the signal pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalNotify::SetWcdmaStateL( TInt aWcdmaState )
    {
    if ( aWcdmaState >= EAknSignalWcdmaIndicatorOff && 
         aWcdmaState <= EAknSignalWcdmaIndicatorSuspended )
        {
        SetStateL( aWcdmaState );
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::SetHsdpaStateL
// Sets an HSDPA icon to the signal pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalNotify::SetHsdpaStateL( TInt aHsdpaState )
    {
    if ( aHsdpaState >= EAknSignalHsdpaIndicatorOff && 
         aHsdpaState <= EAknSignalHsdpaIndicatorMultipdp )
        {
        SetStateL( aHsdpaState );
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::SetCommonPacketDataStateL
// Sets a Common Packet Data icon to the signal pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalNotify::SetCommonPacketDataStateL(
    TInt aCommonPacketDataState )
    {
    if ( aCommonPacketDataState >= EAknSignalCommonPacketDataIndicatorOff  && 
         aCommonPacketDataState <= EAknSignalCommonPacketDataIndicatorMultipdp )
        {
        SetStateL( aCommonPacketDataState );
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::SetCdmaStateL
// Sets a CDMA icon to the signal pane.
// ---------------------------------------------------------------------------
//
#ifdef __PROTOCOL_CDMA
EXPORT_C void CAknSignalNotify::SetCdmaStateL( TInt aCdmaState )
    {
    // Only supported in CDMA builds.
    if ( aCdmaState >= EAknSignalCdmaIndicatorOff && 
         aCdmaState <= EAknSignalCdmaIndicatorReceiving )
        {
        SetStateL( aCdmaState );
        }
    }
#else
EXPORT_C void CAknSignalNotify::SetCdmaStateL( TInt /*aCdmaState*/ )
    {
    }
#endif // __PROTOCOL_CDMA


// ---------------------------------------------------------------------------
// CAknSignalNotify::SetCdmaStateL
// Sets an EDGE icon to the signal pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSignalNotify::SetEdgeStateL( TInt aEdgeState )
    {
    if ( aEdgeState >= EAknSignalEdgeIndicatorOff && 
         aEdgeState <= EAknSignalEdgeIndicatorMultipdp )
        {
        SetStateL( aEdgeState );
        }
    }


// ---------------------------------------------------------------------------
// CAknSignalNotify::SetCdmaStateL
// Sets the signal state icon to the signal pane.
// ---------------------------------------------------------------------------
//
void CAknSignalNotify::SetStateL( TInt aState )
    {
    TPckgBuf< SAknNotifierPackage<SAknSignalNotifyParams> > pckg;
    pckg().iParamData.iGprsState = aState;
    pckg().iParamData.iValue     = EAknSignalStateNotChanged;
    TBuf8<1> resp;
    StartOrUpdateL( pckg, resp );
    }

// End of File
