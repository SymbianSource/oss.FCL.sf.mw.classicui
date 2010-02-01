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
#include <bautils.h>
#include <s32file.h>
#include <testsdkprivateuiframework.rsg>

#include "testsdkprivateuiframobserver.h"
#include "testsdkprivateuiframework.h"
#include "testsdkprivateuiframework.hrh"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPCEikButtonPanelL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPCEikButtonPanelL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonPanel *buttonPanel=new( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );

    STIF_ASSERT_NOT_NULL( buttonPanel );
    CleanupStack::PopAndDestroy( buttonPanel );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPConstructL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonPanel * buttonPanel = new ( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    buttonPanel->ConstructL();
    CleanupStack::PopAndDestroy();
    STIF_ASSERT_NOT_NULL( buttonPanel );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPAddButtonL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPAddButtonL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonPanel *buttonPanel=new( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    CEikLabeledButton* labeledButton = new( ELeave ) CEikLabeledButton();
    CleanupStack::PushL( labeledButton );
    buttonPanel->ConstructL();
    TResourceReader panelReader;
    CEikonEnv::Static()->CreateResourceReaderLC( panelReader, R_PRIVATEUIFRAMTEST_BUTTON_PANEL );
    buttonPanel->ConstructFromResourceL( panelReader );
    buttonPanel->AddButtonL( labeledButton, EPRIVATEUIFRAMTestPrivateUIBtn1 ); 
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( labeledButton );
    CleanupStack::PopAndDestroy( buttonPanel );
    STIF_ASSERT_NOT_NULL( buttonPanel );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPAddButtonIntL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPAddButtonIntL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonPanel *buttonPanel=new( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    CEikLabeledButton* labeledButton = new( ELeave ) CEikLabeledButton();
    CleanupStack::PushL( labeledButton );
    buttonPanel->ConstructL();
    TResourceReader panelReader;
    CEikonEnv::Static()->CreateResourceReaderLC( panelReader, R_PRIVATEUIFRAMTEST_BUTTON_PANEL );
    buttonPanel->ConstructFromResourceL( panelReader );
    buttonPanel->AddButtonL( labeledButton, EPRIVATEUIFRAMTestPrivateUIBtn1,1 ); 
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( labeledButton );
    CleanupStack::PopAndDestroy( buttonPanel );
    STIF_ASSERT_NOT_NULL( buttonPanel );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPSetHorizontalL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPSetHorizontalL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonPanel * buttonPanel = new ( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    STIF_ASSERT_NOT_NULL( buttonPanel );
    buttonPanel->SetHorizontal();
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPButtonIdL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPButtonIdL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonPanel * buttonPanel = new ( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    STIF_ASSERT_NOT_NULL( buttonPanel );
    CCoeControl* coecontrol=new ( ELeave )CCoeControl();
    CleanupStack::PushL( coecontrol );
    TInt id = buttonPanel->ButtonId( coecontrol );
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPButtonByIdL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPButtonByIdL(CStifItemParser& /*aItem*/)
    {
    CEikButtonPanel * buttonPanel = new ( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    STIF_ASSERT_NOT_NULL( buttonPanel );
    CCoeControl* coecontrol=new ( ELeave )CCoeControl();
    CleanupStack::PushL( coecontrol );
    TInt id = buttonPanel->ButtonId( coecontrol );
    buttonPanel->ButtonById( id );
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPLabeledButtonByIdL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPLabeledButtonByIdL(CStifItemParser& /*aItem*/)
    {
    CEikButtonPanel * buttonPanel = new ( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    STIF_ASSERT_NOT_NULL( buttonPanel );
    CCoeControl* coecontrol=new ( ELeave )CCoeControl();
    CleanupStack::PushL( coecontrol );
    TInt id = buttonPanel->ButtonId( coecontrol );
    buttonPanel->LabeledButtonById( id );
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPMakeButtonVisibleL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPMakeButtonVisibleL(CStifItemParser& /*aItem*/)
    {
    CEikButtonPanel * buttonPanel = new ( ELeave )CEikButtonPanel();
    CleanupStack::PushL(buttonPanel);
    STIF_ASSERT_NOT_NULL( buttonPanel );
    CCoeControl* coecontrol=new ( ELeave )CCoeControl();
    CleanupStack::PushL(coecontrol);
    TInt id = buttonPanel->ButtonId(coecontrol);
    buttonPanel->MakeButtonVisible( id, ETrue );
    CleanupStack::PopAndDestroy( 2);
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPButtonForKeyL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPButtonForKeyL(CStifItemParser& /*aItem*/)
    {
    CEikButtonPanel * buttonPanel = new ( ELeave )CEikButtonPanel();
    CleanupStack::PushL(buttonPanel);
    STIF_ASSERT_NOT_NULL( buttonPanel );
    CCoeControl* coecontrol=new ( ELeave )CCoeControl();
    CleanupStack::PushL(coecontrol);
    TInt id = buttonPanel->ButtonId(coecontrol);
    buttonPanel->ButtonForKey( 1, id );
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPResetMinimumSizeL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPResetMinimumSizeL(CStifItemParser& /*aItem*/)
    {
    CEikButtonPanel * buttonPanel = new ( ELeave )CEikButtonPanel();
    CleanupStack::PushL(buttonPanel);
    buttonPanel->ResetMinimumSize();
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPSetMinButtonWidthL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPSetMinButtonWidthL(CStifItemParser& /*aItem*/)
    {
    CEikButtonPanel * buttonPanel = new ( ELeave )CEikButtonPanel();
    CleanupStack::PushL(buttonPanel);
    buttonPanel->SetMinButtonWidth( 1 );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPSetCommandObserverL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPSetCommandObserverL(CStifItemParser& /*aItem*/)
    {
    CEikButtonPanel * buttonPanel = new ( ELeave )CEikButtonPanel();
    CleanupStack::PushL(buttonPanel);
    CTestSdkPrivateUiFramObserver* privateuiframobserver = new ( ELeave )CTestSdkPrivateUiFramObserver;
    CleanupStack::PushL( privateuiframobserver );
    buttonPanel->SetCommandObserver( privateuiframobserver );
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPConstructFromResourceL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonPanel *buttonPanel=new( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    TResourceReader panelReader;
    CEikonEnv::Static()->CreateResourceReaderLC( panelReader, R_PRIVATEUIFRAMTEST_BUTTON_PANEL );
    buttonPanel->ConstructFromResourceL( panelReader );
    CleanupStack::PopAndDestroy( 2 );
    STIF_ASSERT_NOT_NULL( buttonPanel );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPMinimumSizeL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonPanel *buttonPanel=new( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    buttonPanel->ConstructL();
    buttonPanel->ResetMinimumSize();
    buttonPanel->MinimumSize();
    CleanupStack::PopAndDestroy();
    STIF_ASSERT_NOT_NULL( buttonPanel );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPGetColorUseListL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    
    CEikButtonPanel *buttonPanel=new( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    CArrayFix<TCoeColorUse>* colorlist =
                             new ( ELeave ) CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( colorlist );
    buttonPanel->GetColorUseListL( *colorlist );
    CleanupStack::PopAndDestroy( 2 );
    STIF_ASSERT_NOT_NULL( buttonPanel );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPHandleResourceChangeL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonPanel *buttonPanel=new( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    STIF_ASSERT_NOT_NULL( buttonPanel );
    buttonPanel->HandleResourceChange( 1 );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPOfferKeyEventL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPOfferKeyEventL(CStifItemParser& /*aItem*/)
    {
    CEikButtonPanel *buttonPanel = new( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    STIF_ASSERT_NOT_NULL( buttonPanel );
    TKeyEvent KeyEvent;
    buttonPanel->OfferKeyEventL( KeyEvent, EEventKey) ;
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPHandlePointerEventL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPHandlePointerEventL(CStifItemParser& /*aItem*/)
    {
    CEikButtonPanel *buttonPanel = new( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    STIF_ASSERT_NOT_NULL( buttonPanel );
    TPointerEvent PointerEvent;
    buttonPanel->HandlePointerEventL( PointerEvent );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPDoWriteInternalStateL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPDoWriteInternalStateL(CStifItemParser& /*aItem*/)
    {
    CEikButtonPanel *buttonPanel=new( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    CTestSdkPrivateUiFramButtonPanel *privateuiframbuttonpanel = new( ELeave )CTestSdkPrivateUiFramButtonPanel;
    CleanupStack::PushL(privateuiframbuttonpanel);
    
    _LIT( KTestFile, "c:\\TestFile.dat" );
       
    RFs fsSession;
    RFile fileCreate;
    User::LeaveIfError( fsSession.Connect() ); 
    if( !( BaflUtils::FileExists( fsSession, KTestFile ) ))
        {
        fileCreate.Create( fsSession,KTestFile,EFileWrite );
        fileCreate.Close();
        }
    User::LeaveIfError( fileCreate.Open( fsSession, KTestFile, EFileWrite ) );
    RFileWriteStream writestream( fileCreate );
    writestream.PushL();
    privateuiframbuttonpanel->DoWriteInternalStateL( writestream );
    writestream.CommitL();
    writestream.Release();
    writestream.Pop();
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestBPHandleControlEventL
// -----------------------------------------------------------------------------
//

TInt CTestSdkPrivateUiFramework::TestBPHandleControlEventL(CStifItemParser& /*aItem*/)
    {
    CEikButtonPanel *buttonPanel = new( ELeave )CEikButtonPanel();
    CleanupStack::PushL( buttonPanel );
    CEikLabeledButton* labeledButton = new( ELeave ) CEikLabeledButton();
    CleanupStack::PushL( labeledButton );
    buttonPanel->HandleControlEventL( labeledButton, 
            MCoeControlObserver::EEventRequestCancel);  
    STIF_ASSERT_NOT_NULL( buttonPanel );
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// End of File


