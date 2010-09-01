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
* Description:  a subclass of CAknDialog which has a CEikEdwin. This dialog is 
* to test smiley feature of CEikEdwin.
*
*/


#include "testedwindialog.h"
#include <eikedwin.h>
#include "testsdkeditors.hrh"

TestEdwinDialog::TestEdwinDialog()
    {
    }

TestEdwinDialog::~TestEdwinDialog()
    {
    }


void TestEdwinDialog::PreLayoutDynInitL() // initialize controls
    {
    CEikEdwin* editor = (CEikEdwin*) Control( EMyAppCmdSetnameEditor );
#ifdef FF_AVKON_EMOTION_ICON_ENABLED    
    editor->AddFlagToUserFlags( CEikEdwin::EAvkonEnableSmileySupport );
#endif    
    _LIT (KMyText , "Hello World");
    editor->SetTextL(&KMyText);
    editor->SetRect(TRect(50,50,300,300));
    }

void TestEdwinDialog::ProcessCommandL( TInt aCommandId )
    {
    CAknDialog::ProcessCommandL( aCommandId );
    }

TKeyResponse TestEdwinDialog::OfferKeyEventL
    ( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    return CAknDialog::OfferKeyEventL( aKeyEvent, aType );
    }


TInt TestEdwinDialog::RunDlgLD( TInt aResouceId )
    {
    TestEdwinDialog* dlg = new (ELeave) TestEdwinDialog();
        return dlg->ExecuteLD( aResouceId );
    }
