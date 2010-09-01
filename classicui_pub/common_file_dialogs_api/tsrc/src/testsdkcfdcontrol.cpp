/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test CAknMemorySelectionSettingPage.h
 *
*/


// [INCLUDE FILES]

#include <eikenv.h>
#include <aknappui.h> 
#include <testsdkcfd.rsg>

#include "testsdkcfdcontrol.h"

// CONSTS
const TInt KBufSize = 32;

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestControl::NewL
// -----------------------------------------------------------------------------
//
CTestControl* CTestControl::NewL()
    {
    CTestControl* self = new (ELeave) CTestControl;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestControl::~CTestControl
// -----------------------------------------------------------------------------
//
CTestControl::~CTestControl(){}

// -----------------------------------------------------------------------------
// CTestControl::CTestControl
// -----------------------------------------------------------------------------
//
CTestControl::CTestControl(){};

// -----------------------------------------------------------------------------
// CTestControl::ConstructL
// -----------------------------------------------------------------------------
//
void CTestControl::ConstructL()
    {
    CreateWindowL();
    //add controls
    SetRect(CEikonEnv::Static()->EikAppUi()->ClientRect());
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestControl::Draw
// -----------------------------------------------------------------------------
//
void CTestControl::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestControl::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestControl::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestControl::TestSettingPageRunLDL
// -----------------------------------------------------------------------------
//
TInt CTestControl::TestSettingPageRunLDL(CStifItemParser& aItem)
    {
    TInt num = 0;
    TBool backvalue = EFalse;
    CAknMemorySelectionDialog::TMemory memorytype = CAknMemorySelectionDialog::EMemoryCard;
    TInt err = aItem.GetNextInt(num);
    if (err != KErrNone)
        return err;
    switch (num)
        {
        case 1:
            {
            backvalue = CAknMemorySelectionSettingPage::RunDlgLD(memorytype, this);
            break;
            }
        case 2:
            {
            TBuf<KBufSize> tempbuf(_L("Example"));
            backvalue = CAknMemorySelectionSettingPage::RunDlgLD(memorytype, tempbuf, NULL);
            break;
            }
        case 3:
            {
            backvalue = CAknMemorySelectionSettingPage::RunDlgLD(memorytype, 
                    R_TEST_MEMORY_SELECTION_DIALOG, NULL, NULL, NULL);
            break;
            }
        default:
            return KErrNotSupported;
        }
    if (backvalue)
        {
        //press key arrowup before playing dlg
        CAknMemorySelectionDialog::EPhoneMemory == memorytype? err = 0 : err = KErrUnknown;
        }
    else
        {
        CAknMemorySelectionDialog::EMemoryCard == memorytype? err = 0 : err = KErrUnknown;
        }
    return err;
    }

// -----------------------------------------------------------------------------
// CTestControl::OkToExitL
// -----------------------------------------------------------------------------
//
TBool CTestControl::OkToExitL( CAknMemorySelectionDialog::TMemory /*aMemory*/ )
    {
    // it is only for testing, no used
    return ETrue;
    }
// End of file
