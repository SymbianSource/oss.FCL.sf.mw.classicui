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
* Description:  AVKON notifier client for setting the state of
*                status pane's battery pane.
*
*/


#include "AknBatteryNotify.h"
#include <AknNotifyStd.h>
#include <AknNotifySignature.h>

//----------------------------------------------------------------------------
// CAknBatteryNotify::NewL
// Two-phased constructor.
//----------------------------------------------------------------------------
//
EXPORT_C CAknBatteryNotify* CAknBatteryNotify::NewL()
    {
    CAknBatteryNotify* self = NewLC();
    CleanupStack::Pop( self );
    return self;
    }


//----------------------------------------------------------------------------
// CAknBatteryNotify::NewLC
// Two-phased constructor.
//----------------------------------------------------------------------------
//
EXPORT_C CAknBatteryNotify* CAknBatteryNotify::NewLC()
    {
    CAknBatteryNotify* self = new (ELeave) CAknBatteryNotify;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


//----------------------------------------------------------------------------
// CAknBatteryNotify::~CAknBatteryNotify
// Destructor.
//----------------------------------------------------------------------------
//
EXPORT_C CAknBatteryNotify::~CAknBatteryNotify()
    {
    }


//----------------------------------------------------------------------------
// CAknBatteryNotify::CAknBatteryNotify
// Default C++ constructor.
//----------------------------------------------------------------------------
//
CAknBatteryNotify::CAknBatteryNotify() :
    CAknNotifyBase( KAknBatteryNotifierUid )
    {
    }


//----------------------------------------------------------------------------
// CAknBatteryNotify::ConstructL
// Second phase constructor.
//----------------------------------------------------------------------------
//
void CAknBatteryNotify::ConstructL()
    {
    CAknNotifyBase::ConstructL();
    }


//----------------------------------------------------------------------------
// CAknBatteryNotify::SetBatteryLevelL
// Sets the battery level.
//----------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryNotify::SetBatteryLevelL( TInt aLevel )
    {
    TPckgBuf< SAknNotifierPackage<SAknBatteryNotifyParams> > pckg;
    pckg().iParamData.iType  = SAknBatteryNotifyParams::ESetValue;
    pckg().iParamData.iValue = aLevel;
    TBuf8<1> resp;
    StartOrUpdateL( pckg, resp );
    }


//----------------------------------------------------------------------------
// CAknBatteryNotify::StartChargingL
// Starts the recharging animation.
//----------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryNotify::StartChargingL()
    {
    TPckgBuf< SAknNotifierPackage<SAknBatteryNotifyParams> > pckg;
    pckg().iParamData.iType = SAknBatteryNotifyParams::ERecharge;
    TBuf8<1> resp;
    StartOrUpdateL( pckg, resp );
    }


//----------------------------------------------------------------------------
// CAknBatteryNotify::StopChargingL
// Stops the recharging animation.
//----------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryNotify::StopChargingL()
    {
    TPckgBuf< SAknNotifierPackage<SAknBatteryNotifyParams> > pckg;
    pckg().iParamData.iType = SAknBatteryNotifyParams::EStopRecharge;
    TBuf8<1> resp;
    StartOrUpdateL( pckg, resp );
    }


//----------------------------------------------------------------------------
// CAknBatteryNotify::NotChargingL
// Deprecated, current implementation stops the recharging animation.
//----------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryNotify::NotChargingL()
    {
    TPckgBuf< SAknNotifierPackage<SAknBatteryNotifyParams> > pckg;
    pckg().iParamData.iType = SAknBatteryNotifyParams::ENoRecharge;
    TBuf8<1> resp;
    StartOrUpdateL( pckg, resp );
    }


//----------------------------------------------------------------------------
// CAknBatteryNotify::SetBatteryStateL
// Sets the battery icon state.
//----------------------------------------------------------------------------
//
EXPORT_C void CAknBatteryNotify::SetBatteryStateL( TInt aState )
    {
    TPckgBuf< SAknNotifierPackage<SAknBatteryNotifyParams> > pckg;
    pckg().iParamData.iType         = SAknBatteryNotifyParams::ESetState;
    pckg().iParamData.iBatteryState = aState;
    TBuf8<1> resp;
    StartOrUpdateL( pckg, resp );
    }

// End of File
