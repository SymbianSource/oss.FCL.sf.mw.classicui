/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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







#include <eikenv.h>
#include <aknview.h>
#include <aknviewappui.h>
#include <eikdoc.h>
#include <s32file.h>

#include "bctestaknviewappui.h"
#include "bctestappfrm.hrh"
#include "streamlogger.h"
#include "bctestappfrmview.h"
#include "bctestappfrmappui.h"

const TUid KMonkViewID = { 2 };

// ----------------------------------------------------------------------------
// ctor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestAknViewAppUi::CBCTestAknViewAppUi(CAknViewAppUi* aUI, TUid aViewID)
    :iUI(aUI), iViewID(aViewID)
    {
    }

// ----------------------------------------------------------------------------
// dtor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestAknViewAppUi::~CBCTestAknViewAppUi()
    {
    }

// ----------------------------------------------------------------------------
// symbian 2nd phase ctor.
// ----------------------------------------------------------------------------
//
void CBCTestAknViewAppUi::ConstructL()
    {
    BuildScriptL();
    }

// ----------------------------------------------------------------------------
// symbian NewL.
// ----------------------------------------------------------------------------
//
CBCTestAknViewAppUi* CBCTestAknViewAppUi::NewL(CAknViewAppUi* aUI, TUid aViewID)
    {
    CBCTestAknViewAppUi* self = new ( ELeave ) CBCTestAknViewAppUi(aUI, aViewID);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// override the CBCTestCase::RunL, only response to the related command ID.
// ----------------------------------------------------------------------------
//
void CBCTestAknViewAppUi::RunL(int aCmd)
    {
    if(aCmd != EBCTestCmdViewAppUi) return;
    SetupL();
    TestL();
    TearDownL();
    }

// ----------------------------------------------------------------------------
// build the test scripts for this test case.
// ----------------------------------------------------------------------------
//
void CBCTestAknViewAppUi::BuildScriptL()
    {
    const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, 
        REP(Down, 2),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }

// ----------------------------------------------------------------------------
// test the volume setting page creation api.
// ----------------------------------------------------------------------------
//
void CBCTestAknViewAppUi::TestL()
    {
    TestActiateViewL();
    TestViewFacilityL();
    TestSplitViewL();
    TestOthersL();
    }

void CBCTestAknViewAppUi::TestActiateViewL(){
    iUI->ActivateLocalViewL(iViewID);
    AssertTrueL(ETrue, _L("CAknViewAppUi::ActivateLocalViewL(TUid) invoked.") );
    iUI->ActivateLocalViewL(iViewID, KNullUid, KNullDesC8 );
    AssertTrueL(ETrue, _L("CAknViewAppUi::ActivateLocalViewL(TUid, TUid, const TDesC8&) invoked.") );

    AssertTrueL(KNullUid==iUI->FocusedView(), _L("CAknViewAppUi::FocusedView() for split view ONLY") );
    AssertTrueL(EFalse==iUI->ViewShown(iViewID), _L("CAknViewAppUi::ViewShown() for split view ONLY") );
}

void CBCTestAknViewAppUi::TestViewFacilityL(){
    class CMonkView: public CAknView
    {
    public:
        TUid Id() const{ return KMonkViewID; }
        void DoActivateL( const TVwsViewId&, TUid, const TDesC8& ){}
        void DoDeactivate(){}
    };

    CAknView* view = new (ELeave) CMonkView;
    CleanupStack::PushL(view);
    iUI->AddViewL(view);
    CleanupStack::Pop(view);
    AssertTrueL(ETrue, _L("CAknViewAppUi::AddViewL() invoked.") );

    AssertTrueL(view == iUI->View(KMonkViewID), _L("CAknViewAppUI::View(TUid) got") );

    iUI->RemoveView(KMonkViewID);
    AssertTrueL(ETrue, _L("CAknViewAppUi::RemoveView() invoked.") );
}

void CBCTestAknViewAppUi::TestSplitViewL(){
    // not supported , omit
    AssertTrueL( EFalse == iUI->SplitViewActive(), _L("SplitViewActive() not support") );

    iUI->SetSplitViewL(KMonkViewID, iViewID, 0);
    AssertTrueL( ETrue, _L("SetSplitViewL() not support"));

    iUI->RemoveSplitViewL(KMonkViewID);

    AssertTrueL( KNullUid==iUI->FocusedView(), _L("CAknViewAppUi::FocusedView() not support") );
    AssertTrueL( EFalse==iUI->ViewShown(iViewID), _L("CAknViewAppUi::ViewShown() note support") );    
}

void CBCTestAknViewAppUi::TestOthersL(){
    static_cast<CBCTestAppFrmAppUi*>(iUI)->HandleStatusPaneSizeChange();
    AssertTrueL( ETrue, _L("CAknViewAppUi::HandleStautsPaneSizeChange() invoked"));
}
// ----------------------------------------------------------------------------
// prepare for the test.
// ----------------------------------------------------------------------------
//
void CBCTestAknViewAppUi::SetupL()
    {
    }

// ----------------------------------------------------------------------------
// do release jobs.
// ----------------------------------------------------------------------------
//
void CBCTestAknViewAppUi::TearDownL()
    {
    }

//end of file
