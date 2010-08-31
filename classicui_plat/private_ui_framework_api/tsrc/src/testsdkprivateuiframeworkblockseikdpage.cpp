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
* Description:  test private_ui_framework_api
*
*/



// [INCLUDE FILES]

#include <eikcapc.h>
#include <eikdpage.h>
#include <barsread.h>
#include <akndialog.h>
#include <testsdkprivateuiframework.rsg>

#include "testsdkprivateuiframework.h"
#include "testsdkprivateuiframework.hrh"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPSetFormLayoutL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestDPSetFormLayoutL( CStifItemParser& /*aItem*/ )
    {
    class CTestDialog : public CAknDialog
        {
        public:
        CEikCaptionedControl* GetCapCtrl(){ return this->Line( EFormOne );}
        };
    CTestDialog* dlg = new ( ELeave ) CTestDialog;
    dlg->PrepareLC( R_PRIVATEUIFRAMTEST_FORMDLG );
    
    CEikCaptionedControl *capctrl = dlg->GetCapCtrl();
    
    CEikDialogPage *page = const_cast<CEikDialogPage*>( capctrl->DialogPage() );
    CEikDialogPage::TFormLayoutSelection layout = CEikDialogPage::ESingle;
    page->SetFormLayout( layout );
    STIF_ASSERT_NOT_NULL( page );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    } 

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestDPFormLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSdkPrivateUiFramework::TestDPFormLayoutL( CStifItemParser& /*aItem*/ )
    {
    class CTestDialog : public CAknDialog
        {
        public:
        CEikCaptionedControl* GetCapCtrl(){ return this->Line( ESinglePageIdOne );}
        };
    CTestDialog* dlg = new ( ELeave ) CTestDialog;
    dlg->PrepareLC( R_PRIVATEUIFRAMTEST_DIALOG );
    
    CEikCaptionedControl *capctrl = dlg->GetCapCtrl();
    
    const CEikDialogPage *page = capctrl->DialogPage();
    page->FormLayout();
    STIF_ASSERT_NOT_NULL( page );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// End of File


