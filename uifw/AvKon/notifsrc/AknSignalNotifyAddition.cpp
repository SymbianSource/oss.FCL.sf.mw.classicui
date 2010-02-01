/*
* Copyright (c) 2003-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32base.h>
#include <AknNotifyStd.h>
#include "AknSignalNotifyAddition.h"
#include <avkon.hrh>
#include <AknNotifySignature.h>

EXPORT_C CAknSignalNotifyAddition::~CAknSignalNotifyAddition()
    {
    // only close the connection, notifier is not cancelled.
    // Assume that it is cancelled by CAknSignalNotify.
    iNotify.Close();
    }

CAknSignalNotifyAddition::CAknSignalNotifyAddition() 
    {
    }

EXPORT_C CAknSignalNotifyAddition* CAknSignalNotifyAddition::NewL()
    {
    CAknSignalNotifyAddition* self = NewLC();
    CleanupStack::Pop();    // self
    return self;
    }

EXPORT_C CAknSignalNotifyAddition* CAknSignalNotifyAddition::NewLC()
    {
    CAknSignalNotifyAddition* self = new(ELeave) CAknSignalNotifyAddition;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CAknSignalNotifyAddition::ConstructL()
    {
    Connect();
    }

void CAknSignalNotifyAddition::Connect()
    {
    // Only open the connection, notifier is not started.
    // Assume that it is started by CAknSignalNotify.
    TInt error = iNotify.Connect();
    TBuf8<1> dummy;
    iNotify.StartNotifier(KAknMemoryCardDialogUid,dummy,dummy); // does not exist anymore ...
    if (error == KErrNone)
        {
        iConnected = ETrue;
        }
    }


void CAknSignalNotifyAddition::UpdateL(const TDesC8& aBuffer,TDes8& aResponse)
    {
    if (!iConnected)
        {
        Connect(); // try reconnecting
        }
    iNotify.UpdateNotifier(KAknSignalNotifierUid, aBuffer, aResponse);
    }

EXPORT_C void CAknSignalNotifyAddition::SetNaviPaneBackgroundTypeL(TInt aType)
    {
    TPckgBuf<SAknNotifierPackage<SAknSignalNotifyParams> > pckg;
    switch (aType)
        {
        case EAknNaviPaneBackgroundTypeWipe:
            {
            pckg().iParamData.iGprsState = EAknSignalGprsIndicatorBgTypeWipe;
            break;
            }
        case EAknNaviPaneBackgroundTypeSolid:
            {
            pckg().iParamData.iGprsState = EAknSignalGprsIndicatorBgTypeSolid;
            break;
            }
        default:
            {
            pckg().iParamData.iGprsState = EAknSignalGprsStateNotChanged;
            }
        }
    pckg().iParamData.iValue = EAknSignalStateNotChanged;
    TBuf8<1> resp;
    UpdateL(pckg, resp);
    }

// End of File
