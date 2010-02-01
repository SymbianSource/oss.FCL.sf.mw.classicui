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

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <vwsdefpartner.h>
#endif
#include "AknSoftNotificationParameters.h"

EXPORT_C CAknSoftNotificationParameters* CAknSoftNotificationParameters::NewL(
    const TDesC& aResourceFile,
    TInt aNoteResourceId,
    TInt aPriority,
    TInt aSoftkeys,
    CAknNoteDialog::TTone aTone)
    {
    return NewL( 
        aResourceFile,
        aNoteResourceId,
        aPriority,
        aSoftkeys,
        aTone,
        KNullViewId,
        KNullUid,
        0,
        KNullDesC8());
    }

EXPORT_C CAknSoftNotificationParameters* CAknSoftNotificationParameters::NewL(
    const TDesC& aResourceFile,
    TInt aNoteResourceId,
    TInt aPriority,
    TInt aSoftkeys,
    CAknNoteDialog::TTone aTone,
    TVwsViewId aViewId,
    TUid aCustomMessageId,
    TInt aAcceptKeyId,
    const TDesC8& aViewActivationMsg )
    {
    CAknSoftNotificationParameters* self = new (ELeave) CAknSoftNotificationParameters; 
    CleanupStack::PushL(self);

    self->iResourceFile = aResourceFile.AllocL();
    self->iNoteResourceId = aNoteResourceId; 
    self->iPriority = aPriority;
    self->iSoftkeys = aSoftkeys;
    self->iTone = aTone;
    self->iViewId.iAppUid = aViewId.iAppUid;
    self->iViewId.iViewUid = aViewId.iViewUid;

    if ( self->iViewId.iAppUid != KNullUid )     
        {
        self->iCustomMessageId = aCustomMessageId;
        self->iAcceptSoftKey = aAcceptKeyId;
        self->iViewActivationMsg = aViewActivationMsg.AllocL();
        }

    CleanupStack::Pop();
    return self;
    }

EXPORT_C CAknSoftNotificationParameters::~CAknSoftNotificationParameters()
    {
    delete iResourceFile;
    delete iViewActivationMsg;
    }

EXPORT_C CAknSoftNotificationParameters* CAknSoftNotificationParameters::NewL()
    {
    return (new (ELeave) CAknSoftNotificationParameters);
    }
    
//  End of File  
