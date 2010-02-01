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
* Description:  Global list message query dialog implementation.
*
*/

#include <uikon.hrh> // EKeyOk
#include "AknListMsgQueryNotificationDialog.h"
#include "AknNotifyPlugin.hrh"
#include "avkon.hrh"

CAknListMsgQueryNotificationDialog::CAknListMsgQueryNotificationDialog(
    TInt* aIndex,
    MAknListQueryNotificationCallback* aCallBack,
    CAknListMsgQueryNotificationDialog** aSelfPtr,
    TInt aAcceptKeyId,
    TInt aCancelKeyId)
: CAknListQueryDialog(aIndex), 
  iCallBack(aCallBack), 
  iSelfPtr(aSelfPtr), 
  iAcceptKeyId(aAcceptKeyId), 
  iCancelKeyId(aCancelKeyId)
    {
    }

CAknListMsgQueryNotificationDialog::~CAknListMsgQueryNotificationDialog()
    {
    if (iSelfPtr) 
        {
        *iSelfPtr = NULL;
        }
    }

TKeyResponse CAknListMsgQueryNotificationDialog::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType)
    {
    
    if (aKeyEvent.iScanCode == EStdKeyYes)
        {
        return EKeyWasConsumed;
        }
    
    if (aType != EEventKey)
        {
        return EKeyWasNotConsumed;
        }
    
    TInt code = aKeyEvent.iCode;
    
    switch (code)
        {
        case EKeyOK:
            TryExitL(EAknSoftkeyOk);
            return EKeyWasConsumed;
        case EKeyEscape:
            TryExitL(EAknSoftkeyCancel);
            return EKeyWasConsumed;
        default:
            break;
        }

    return CAknListQueryDialog::OfferKeyEventL(aKeyEvent,aType);
    }

TBool CAknListMsgQueryNotificationDialog::OkToExitL(TInt aButtonId)
    {
    TInt ret = -1;

    // Get the current item index only if the command is an accept command.
    if (aButtonId == EAknSoftkeyOk || (iAcceptKeyId && aButtonId == iAcceptKeyId))
        {
        ret = ListBox()->CurrentItemIndex();
        }
        
    iCallBack->QueryDismissedL(ret);
    
    if (aButtonId == EAknSoftkeyCancel                || 
        aButtonId == EAknSoftkeyOk                    ||
        (iCancelKeyId && (aButtonId == iCancelKeyId)) || 
        (iAcceptKeyId && (aButtonId == iAcceptKeyId)))
        {
        return ETrue;
        }
        
    return EFalse;        
    }

// End of file
