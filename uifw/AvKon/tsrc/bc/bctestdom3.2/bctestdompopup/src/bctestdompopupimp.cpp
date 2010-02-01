/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#include "bctestdompopupcase.h"

#include <e32property.h>
#include <AvkonInternalCRKeys.h>
#include <AknCharMap.h>
#include <akndialog.h>

#include <AknShortcuts.h>
#include <COEMOP.H>

TInt ECharMapDialogItemLockNumericKeys = 0x02;

// -----------------------------------------------------------------------------
// CAknCharMapDialog::~CAknCharMapDialog
//
// ~CAknCharMapDialog isn't a IMPORT_C api,so be re-implemented here.
// -----------------------------------------------------------------------------
//
CAknCharMapDialog::~CAknCharMapDialog()
    {
    iAvkonEnv->CancelWsBufferRequest( iWsBufferRequestId );
    delete iExtension;
    }

// -----------------------------------------------------------------------------
// CAknCharMap::CharacterCase()
// CharacterCase() isn't a IMPORT_C api,so be re-implemented here
// -----------------------------------------------------------------------------
//
TInt CAknCharMap::CharacterCase()
    {
    return iCharCase;
    }
    
// -----------------------------------------------------------------------------
// CAknCharMapDialogExtension::CAknCharMapDialogExtension
//
// Constructor of extension
// -----------------------------------------------------------------------------
//
CAknCharMapDialogExtension::CAknCharMapDialogExtension(CAknCharMapDialog* aCaller)
    :iFlags(0), iQwertyMode(EFalse), iCaller(aCaller)
    {
    }

// -----------------------------------------------------------------------------
// CAknCharMapDialogExtension::~CAknCharMapDialogExtension
//
// Destructor of extension
// -----------------------------------------------------------------------------
//
CAknCharMapDialogExtension::~CAknCharMapDialogExtension()
    {
    // Stop subscribe in PubSub
    if (iQwertyModeStatusSubscriber)
        {
        iQwertyModeStatusSubscriber->StopSubscribe();
        }
    iQwertyModeStatusProperty.Close();
    delete iQwertyModeStatusSubscriber;
    }

// -----------------------------------------------------------------------------
// CAknCharMapDialogExtension::NewL
//
// Symbian 2 phase constructor
// -----------------------------------------------------------------------------
//
CAknCharMapDialogExtension* CAknCharMapDialogExtension::NewL(CAknCharMapDialog* aCaller)
    { // static
    CAknCharMapDialogExtension* self = new (ELeave) CAknCharMapDialogExtension(aCaller);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// -----------------------------------------------------------------------------
// CAknCharMapDialogExtension::ConstructL
//
// Symbian construction
// -----------------------------------------------------------------------------
//
void CAknCharMapDialogExtension::ConstructL()
    {
    // Start also listening qwerty mode status.
    User::LeaveIfError(iQwertyModeStatusProperty.Attach(KCRUidAvkon,
        KAknQwertyInputModeActive));

    iQwertyModeStatusSubscriber = new (ELeave) CSubscriber(
        TCallBack(QwertyModeChangeNotification, this), iQwertyModeStatusProperty);

    iQwertyModeStatusSubscriber->SubscribeL();

    iOldCharCase=-1; // no default character case at beginning
    }

TInt CAknCharMapDialogExtension::QwertyModeChangeNotification(TAny* aObj)
    {
    if (aObj != NULL)
        {
        static_cast<CAknCharMapDialogExtension*>(aObj)->HandleQwertyModeChangeNotification();
        return KErrNone;
        }
    else
        {
        return KErrArgument;
        }
    }

void CAknCharMapDialogExtension::SetCharacterCaseIfRequiredL()
    {
    TInt value = 0;
    iQwertyModeStatusProperty.Get(value);
    iQwertyMode = value;

    CAknCharMap* charmapControl =
            STATIC_CAST(CAknCharMap*, iCaller->Control(EAknSCTQueryContentId));

    if ( (iQwertyMode) == (charmapControl->CharacterCase() == EAknSCTQwerty) )
        {
        // No change for Qwerty mode
        return;
        }

    if (iQwertyMode)
        {
        iFlags |= ECharMapDialogItemLockNumericKeys;

        iOldCharCase=charmapControl->CharacterCase();
        charmapControl->SetCharacterCaseL(EAknSCTQwerty);
        }
    else
        {
        iFlags &= (!ECharMapDialogItemLockNumericKeys);
        if (iOldCharCase!=-1)
            {
            charmapControl->SetCharacterCaseL(iOldCharCase);
            }
        else
            {
            charmapControl->SetCharacterCaseL(EAknSCTLowerCase);
            iOldCharCase = EAknSCTLowerCase;
            }
        }
    }
void CAknCharMapDialogExtension::HandleQwertyModeChangeNotification()
    {
    TInt value = 0;
    iQwertyModeStatusProperty.Get(value);
    iQwertyMode = value;

    CAknCharMap* charmapControl =
            STATIC_CAST(CAknCharMap*, iCaller->Control(EAknSCTQueryContentId));

    if ( (iQwertyMode) == (charmapControl->CharacterCase() == EAknSCTQwerty) )
        {
        // No change for Qwerty mode
        return;
        }

    if (iQwertyMode)
        {
        iFlags |= ECharMapDialogItemLockNumericKeys;

        iOldCharCase=charmapControl->CharacterCase();
        charmapControl->SetCharacterCaseL(EAknSCTQwerty);
        }
    else
        {
        iFlags &= (!ECharMapDialogItemLockNumericKeys);
        if (iOldCharCase!=-1)
            {
            charmapControl->SetCharacterCaseL(iOldCharCase);
            }
        else
            {
            charmapControl->SetCharacterCaseL(EAknSCTLowerCase);
            iOldCharCase = EAknSCTLowerCase;
            }
        }
    }

// CAknCharMapDialogExtension::CSubscriber
CAknCharMapDialogExtension::CSubscriber::CSubscriber(TCallBack aCallBack, RProperty& aProperty)
    : CActive(EPriorityNormal), iCallBack(aCallBack), iProperty(aProperty)
    {
    CActiveScheduler::Add(this);
    }

CAknCharMapDialogExtension::CSubscriber::~CSubscriber()
    {
    Cancel();
    }

void CAknCharMapDialogExtension::CSubscriber::SubscribeL()
    {
    if (!IsActive())
        {
        iProperty.Subscribe(iStatus);
        SetActive();
        }
    }

void CAknCharMapDialogExtension::CSubscriber::StopSubscribe()
    {
    Cancel();
    }

void CAknCharMapDialogExtension::CSubscriber::RunL()
    {
    if (iStatus.Int() == KErrNone)
        {
        iCallBack.CallBack();
        SubscribeL();
        }
    }

void CAknCharMapDialogExtension::CSubscriber::DoCancel()
    {
    iProperty.Cancel();
    }

