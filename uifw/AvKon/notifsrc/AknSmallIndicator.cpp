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
* Description: 
*
*/

#include "AknSmallIndicator.h"
#include <AknNotifyStd.h>
#include <AknNotifySignature.h>

const TInt KIndicatorTap = 0xFFFF;

EXPORT_C CAknSmallIndicator* CAknSmallIndicator::NewL(TUid aIndicatorUid)
    {
    CAknSmallIndicator* self = NewLC(aIndicatorUid);
    CleanupStack::Pop();    // self
    return self;
    }

EXPORT_C CAknSmallIndicator* CAknSmallIndicator::NewLC(TUid aIndicatorUid)
    {
    CAknSmallIndicator* self = new(ELeave) CAknSmallIndicator;
    CleanupStack::PushL(self);
    self->ConstructL(aIndicatorUid);
    return self;
    }

EXPORT_C CAknSmallIndicator::~CAknSmallIndicator()
    {
    }

CAknSmallIndicator::CAknSmallIndicator() : CAknNotifyBase(KAknSmallIndicatorUid)
    {
    }

void CAknSmallIndicator::ConstructL(TUid aIndicatorUid)
    {
    CAknNotifyBase::ConstructL();
    iIndicatorUid = aIndicatorUid;
    }

EXPORT_C void CAknSmallIndicator::SetIndicatorStateL(TInt aState)
    {
    RThread thread;
    
    if ( thread.HasCapability( ECapabilityWriteDeviceData ) )
        {
        TPckgBuf<SAknNotifierPackage<SAknSmallIndicatorParams> > pckg;
        pckg().iParamData.iSmallIndicatorUid = iIndicatorUid;
        pckg().iParamData.iValue = aState;
        TBuf8<1> resp;
        StartOrUpdateL(pckg, resp);
        }
        
    thread.Close();
    }

EXPORT_C void CAknSmallIndicator::CAknNotifyBase_Reserved()
    {
    }

EXPORT_C void CAknSmallIndicator::HandleIndicatorTapL()
    {
    TPckgBuf<SAknNotifierPackage<SAknSmallIndicatorParams> > pckg;
    pckg().iParamData.iSmallIndicatorUid = iIndicatorUid;
    pckg().iParamData.iValue = KIndicatorTap;
    TBuf8<1> resp;
    StartOrUpdateL(pckg, resp);     
    }
    
// End of File
