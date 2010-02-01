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

#include "AknPopupNotify.h"
#include <AknNotifyStd.h>

EXPORT_C CAknPopupNotify* CAknPopupNotify::NewL()
    {
    CAknPopupNotify* self = NewLC();
    CleanupStack::Pop();    // self
    return self;
    }

EXPORT_C CAknPopupNotify* CAknPopupNotify::NewLC()
    {
    CAknPopupNotify* self = new(ELeave) CAknPopupNotify;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

EXPORT_C CAknPopupNotify::~CAknPopupNotify()
    {
    }

CAknPopupNotify::CAknPopupNotify() : CAknNotifyBase(KAknPopupNotifierUid)
    {
    }

void CAknPopupNotify::ConstructL()
    {
    CAknNotifyBase::ConstructL();
    }

EXPORT_C void CAknPopupNotify::PopupMessageL(const TDesC& aMessage)
    {
    TBuf8<1> resp;
    StartOrUpdateL(TPtrC8(reinterpret_cast<const TText8*>(aMessage.Ptr()), aMessage.Size()), resp);
    }

EXPORT_C void CAknPopupNotify::CAknNotifyBase_Reserved()
    {
    }

// End of File
