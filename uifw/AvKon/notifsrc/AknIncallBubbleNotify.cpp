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

#include <AknIncallBubbleNotify.h>
#include <AknNotifyStd.h>
#include <AknNotifySignature.h>
#include <avkon.hrh>

EXPORT_C CAknIncallBubble* CAknIncallBubble::NewL()
    {
    CAknIncallBubble* self = NewLC();
    CleanupStack::Pop();    // self
    return self;
    }

EXPORT_C CAknIncallBubble* CAknIncallBubble::NewLC()
    {
    CAknIncallBubble* self = new(ELeave) CAknIncallBubble;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

EXPORT_C CAknIncallBubble::~CAknIncallBubble()
    {
    }

CAknIncallBubble::CAknIncallBubble() : CAknNotifyBase(KAknIncallBubbleUid)
    {
    }

void CAknIncallBubble::ConstructL()
    {
    CAknNotifyBase::ConstructL();
    }

EXPORT_C void CAknIncallBubble::SetIncallBubbleFlagsL(const TInt aFlags)
    {
    TPckgBuf<SAknNotifierPackage<SAknIncallBubbleParams> > pckg;
    TInt flags = aFlags;
    flags &= ~EAknStatusBubbleReservedInternal; // clear internal flag
    pckg().iParamData.iIncallBubbleFlags = flags;       
    TBuf8<1> resp;
    StartOrUpdateL(pckg, resp);
    }

EXPORT_C void CAknIncallBubble::SetIncallBubbleAllowedInIdleL(TBool aAllowed)
    {
    TPckgBuf<SAknNotifierPackage<SAknIncallBubbleParams> > pckg;
    TInt flags = 0;
    flags |= EAknStatusBubbleReservedInternal; 
    if (aAllowed)
        {
        flags |= 0x1;
        }
    else
        {
        flags |= 0x0;
        }
    pckg().iParamData.iIncallBubbleFlags = flags;
    TBuf8<1> resp;
    StartOrUpdateL(pckg, resp);
    }

EXPORT_C void CAknIncallBubble::SetIncallBubbleAllowedInUsualL(TBool aAllowed)
    {
    TPckgBuf<SAknNotifierPackage<SAknIncallBubbleParams> > pckg;
    TInt flags = 0;
    flags |= EAknStatusBubbleReservedInternal; 
    if (aAllowed)
        {
        flags |= 0x4;
        }
    else
        {
        flags |= 0x2;
        }
    pckg().iParamData.iIncallBubbleFlags = flags;
    TBuf8<1> resp;
    StartOrUpdateL(pckg, resp);
    }

EXPORT_C void CAknIncallBubble::CAknNotifyBase_Reserved()
    {
    }

// End of File
