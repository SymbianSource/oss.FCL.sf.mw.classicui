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
#include "AknSystemListPopup.h"

CAknListQueryNotificationDialog::CAknListQueryNotificationDialog( 
    TInt* aIndex,
    MAknListQueryNotificationCallback* aCallBack,
    CAknListQueryNotificationDialog** aSelfPtr)
    : CAknListQueryDialog(aIndex)
    , iCallBack(aCallBack)
    , iSelfPtr(aSelfPtr)
    , iPointerUpEaten(EFalse)
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
    
    iPointerUpEaten = EFalse;
    
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
    // Fix the problem where the pointer up event is handled to close the power menu key,
    // when the popup shows on the top of power menu before releasing the tap.
    if (iPointerUpEaten && AknLayoutUtils::PenEnabled() && aButtonId == EAknSoftkeyOk)
        {
        iPointerUpEaten = EFalse;
        //Fix the problem where the pointer up event is handled to active the power menu item
        //when lock screen happans before releasing the tap on power menu item
        if(((CAknGlobalListQuerySubject*)iCallBack)->IsKeyLockEnable())
            {
            aButtonId = EAknSoftkeyCancel;
            }
        else
            {
            return EFalse;
            }
        }
    
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

void CAknListQueryNotificationDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    iPointerUpEaten = EFalse;
    
    if (aPointerEvent.iType == TPointerEvent::EButton1Up && (!IsFocused() || ((CAknGlobalListQuerySubject*)iCallBack)->IsKeyLockEnable()))
        {
        iPointerUpEaten = ETrue;
        }
    
    CAknListQueryDialog::HandlePointerEventL(aPointerEvent);
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
