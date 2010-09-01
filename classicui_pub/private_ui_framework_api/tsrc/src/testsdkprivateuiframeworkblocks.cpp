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
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <s32strm.h>

#include "testsdkprivateuiframework.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSdkPrivateUiFramework::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        ENTRY( "TestEAHandlePointerEventL", CTestSdkPrivateUiFramework::TestEAHandlePointerEventL ),
        
        ENTRY( "TestBPCEikButtonPanelL", CTestSdkPrivateUiFramework::TestBPCEikButtonPanelL ),
        ENTRY( "TestBPConstructL", CTestSdkPrivateUiFramework::TestBPConstructL ),
        ENTRY( "TestBPAddButtonL", CTestSdkPrivateUiFramework::TestBPAddButtonL ),
        ENTRY( "TestBPSetHorizontalL", CTestSdkPrivateUiFramework::TestBPSetHorizontalL ),
        ENTRY( "TestBPButtonIdL", CTestSdkPrivateUiFramework::TestBPButtonIdL ),
        ENTRY( "TestBPAddButtonIntL", CTestSdkPrivateUiFramework::TestBPAddButtonIntL ),
        ENTRY( "TestBPButtonByIdL", CTestSdkPrivateUiFramework::TestBPButtonByIdL ),
        ENTRY( "TestBPLabeledButtonByIdL", CTestSdkPrivateUiFramework::TestBPLabeledButtonByIdL ),
        ENTRY( "TestBPMakeButtonVisibleL", CTestSdkPrivateUiFramework::TestBPMakeButtonVisibleL ),
        ENTRY( "TestBPButtonForKeyL", CTestSdkPrivateUiFramework::TestBPButtonForKeyL ),
        ENTRY( "TestBPResetMinimumSizeL", CTestSdkPrivateUiFramework::TestBPResetMinimumSizeL ),
        ENTRY( "TestBPSetMinButtonWidthL", CTestSdkPrivateUiFramework::TestBPSetMinButtonWidthL ),
        ENTRY( "TestBPSetCommandObserverL", CTestSdkPrivateUiFramework::TestBPSetCommandObserverL ),
        ENTRY( "TestBPConstructFromResourceL", CTestSdkPrivateUiFramework::TestBPConstructFromResourceL ),
        ENTRY( "TestBPMinimumSizeL", CTestSdkPrivateUiFramework::TestBPMinimumSizeL ),
        ENTRY( "TestBPGetColorUseListL", CTestSdkPrivateUiFramework::TestBPGetColorUseListL ),
        ENTRY( "TestBPHandleResourceChangeL", CTestSdkPrivateUiFramework::TestBPHandleResourceChangeL ),
        ENTRY( "TestBPOfferKeyEventL", CTestSdkPrivateUiFramework::TestBPOfferKeyEventL ),
        ENTRY( "TestBPHandlePointerEventL", CTestSdkPrivateUiFramework::TestBPHandlePointerEventL ),
        ENTRY( "TestBPDoWriteInternalStateL", CTestSdkPrivateUiFramework::TestBPDoWriteInternalStateL ),
        ENTRY( "TestBPHandleControlEventL", CTestSdkPrivateUiFramework::TestBPHandleControlEventL ),

        ENTRY( "TestDPSetFormLayoutL", CTestSdkPrivateUiFramework::TestDPSetFormLayoutL ),
        ENTRY( "TestDPFormLayoutL", CTestSdkPrivateUiFramework::TestDPFormLayoutL ),
        
        ENTRY( "TestDKHandlePointerEventL", CTestSdkPrivateUiFramework::TestDKHandlePointerEventL ),
        ENTRY( "TestDWHandlePointerEventL", CTestSdkPrivateUiFramework::TestDWHandlePointerEventL ),
        
        ENTRY( "TestKEYWriteInternalStateLL", CTestSdkPrivateUiFramework::TestKEYWriteInternalStateLL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//the CEikHotKeyControlImpl class is used to test CEikHotKeyControl class function
class CEikHotKeyControlImpl : public CEikHotKeyControl
	{
	public:
		CEikHotKeyControlImpl(): CEikHotKeyControl( NULL, NULL )
		{
		}
		void TestWriteInternalStateL(RWriteStream& aWriteStream)
			{
			WriteInternalStateL( aWriteStream );
			}
	};

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::TestKEYWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSdkPrivateUiFramework::TestKEYWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    
//    CEikHotKeyControlImpl *hotKeyControl = new ( ELeave )CEikHotKeyControlImpl();
//    RWriteStream aWriteStream;
//    CleanupStack::PushL( hotKeyControl );
//    hotKeyControl->TestWriteInternalStateL( aWriteStream );
//    CleanupStack::PopAndDestroy( hotKeyControl );
    return KErrNone;
    
    }

//  [End of File]


