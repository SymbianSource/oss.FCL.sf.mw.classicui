/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Global list message query dialog declaration.
*
*/

#ifndef __AKNLISTMSGQUERYNOTIFICATIONDIALOG__
#define __AKNLISTMSGQUERYNOTIFICATIONDIALOG__

#include <AknQueryDialog.h>
#include <aknlistquerydialog.h>
#include "AknListQueryNotificationDialog.h"

NONSHARABLE_CLASS(CAknListMsgQueryNotificationDialog) : public CAknListQueryDialog
    {
public:
    CAknListMsgQueryNotificationDialog( 
        TInt* aIndex,
        MAknListQueryNotificationCallback* aCallBack,
        CAknListMsgQueryNotificationDialog** aSelfPtr,
        TInt aAcceptKeyId,
        TInt aCancelKeyId);

    ~CAknListMsgQueryNotificationDialog();
    
    TKeyResponse OfferKeyEventL( 
        const TKeyEvent& aKeyEvent,
        TEventCode aType );

protected:
    TBool OkToExitL(TInt aButtonId);
    
private: 
    MAknListQueryNotificationCallback* iCallBack;
    CAknListMsgQueryNotificationDialog** iSelfPtr;
    TInt iAcceptKeyId;
    TInt iCancelKeyId;
    };

#endif // __AKNLISTMSGQUERYNOTIFICATIONDIALOG__

// End of File
