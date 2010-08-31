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
* Description:  Global list query dialog implementation.
*
*/

#include <uikon.hrh> // EKeyOk
#include "AknListQueryNotificationDialog.h"
#include "AknNotifyPlugin.hrh"
#include "avkon.hrh"

CAknListQueryNotificationDialog::CAknListQueryNotificationDialog( 
    TInt* aIndex,
    MAknListQueryNotificationCallback* aCallBack,
    CAknListQueryNotificationDialog** aSelfPtr)
    : CAknListQueryDialog(aIndex), iCallBack(aCallBack), iSelfPtr(aSelfPtr)
    {
    }

CAknListQueryNotificationDialog::~CAknListQueryNotificationDialog()
    {
    if (iSelfPtr) 
        {
        *iSelfPtr = NULL;
        }
    }

TKeyResponse CAknListQueryNotificationDialog::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType)
    {
    if ((iPanning || iFlick) && (aKeyEvent.iCode == EKeyDownArrow || aKeyEvent.iCode == EKeyUpArrow))
        {
        return EKeyWasNotConsumed;
        }

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

    return CAknListQueryDialog::OfferKeyEventL(aKeyEvent, aType);
    }

void CAknListQueryNotificationDialog::HandleListBoxEventL(
        CEikListBox* aListBox, 
        TListBoxEvent aEventType)
    {
    if (AknLayoutUtils::PenEnabled())
        {
        switch (aEventType)
            {
            case EEventPanningStarted:
                {
                iPanning = ETrue;
                }
                break;
            case EEventPanningStopped:
                {
                iPanning = EFalse;
                }
                break;
            case EEventFlickStarted:
                {
                iFlick = ETrue;
                }
                break;
            case EEventFlickStopped:
                {
                iFlick = EFalse;
                }
                break;
            default:
                {
                break;
                }
            }
        }
    CAknListQueryDialog::HandleListBoxEventL(aListBox, aEventType);
    }

TBool CAknListQueryNotificationDialog::OkToExitL(TInt aButtonId)
    {
    TInt ret = -1;
    if (aButtonId != EAknSoftkeyCancel)
        {
        ret = ListBox()->CurrentItemIndex();
        }
    iCallBack->QueryDismissedL(ret);
    if (aButtonId == EAknSoftkeyCancel || aButtonId == EAknSoftkeyOk)
        {
        return ETrue;
        }
    return EFalse;
    }

void CAknListQueryNotificationDialog::CEikDialog_Reserved_1()
    {
    }

void CAknListQueryNotificationDialog::CEikDialog_Reserved_2()
    {
    }

void CAknListQueryNotificationDialog::CAknDialog_Reserved()
    {
    }

void CAknListQueryNotificationDialog::CAknQueryDialog_Reserved()
    {
    }

// End of file
