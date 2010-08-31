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
* Description:  information_preview_popup_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eiklabel.h> 
#include <aknpreviewpopupcontroller.h>

#include "testsdkinformationpreviewpopup.h"
#include "testsdkippproviderclass.h"
#include "testsdkippobserver.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestIPPNewProviderL", CTestSDKInformationPreviewPopup::TestIPPNewProviderL ),
        ENTRY( "TestNewL", CTestSDKInformationPreviewPopup::TestIPPNewL ),
        ENTRY( "TestIPPNewProviderAndStyleL", 
                CTestSDKInformationPreviewPopup::TestIPPNewProviderAndStyleL ),
        ENTRY( "TestIPPNewStyleL", CTestSDKInformationPreviewPopup::TestIPPNewStyleL ),
        ENTRY( "TestIPPContentSizeInLayout", 
                CTestSDKInformationPreviewPopup::TestIPPContentSizeInLayout ),
        ENTRY( "TestIPPSetPopUpShowDelay", 
                CTestSDKInformationPreviewPopup::TestIPPSetPopUpShowDelay ),
        ENTRY( "TestIPPSetPopUpHideDelay", 
                CTestSDKInformationPreviewPopup::TestIPPSetPopUpHideDelay ),
        ENTRY( "TestIPPShowPopUp", CTestSDKInformationPreviewPopup::TestIPPShowPopUp ),
        ENTRY( "TestIPPHidePopUp", CTestSDKInformationPreviewPopup::TestIPPHidePopUp ),
        ENTRY( "TestIPPContentReadyL", CTestSDKInformationPreviewPopup::TestIPPContentReadyL ),
        ENTRY( "TestIPPSetPosition", 
                CTestSDKInformationPreviewPopup::TestIPPSetPosition ),
        ENTRY( "TestIPPSetPositionByHighlight", 
                CTestSDKInformationPreviewPopup::TestIPPSetPositionByHighlight ),
        ENTRY( "TestIPPAddObserverL", CTestSDKInformationPreviewPopup::TestIPPAddObserverL ),
        ENTRY( "TestIPPRemoveObserverL", CTestSDKInformationPreviewPopup::TestIPPRemoveObserverL ),
        ENTRY( "TestIPPUpdateContentSize",
                CTestSDKInformationPreviewPopup::TestIPPUpdateContentSize ),
        ENTRY( "TestIPPSize", CTestSDKInformationPreviewPopup::TestIPPSize ),
        ENTRY( "TestIPPSetHeadingTextL", CTestSDKInformationPreviewPopup::TestIPPSetHeadingTextL ),
        ENTRY( "TestIPPResetTimer", CTestSDKInformationPreviewPopup::TestIPPResetTimer ),
        





        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }



// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPNewProviderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPNewProviderL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPNewProviderL, "In TestIPPNewProviderL" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPNewProviderL );
    // Print to log file
    iLog->Log( KTestIPPNewProviderL );

    TRect rect( 120, 100, 200, 150);

    CEikLabel* label = new ( ELeave ) CEikLabel;
    CleanupStack::PushL( label );
    TBufC<128> buf(_L( "test" ));
    label->SetTextL( buf );
    
    label->SetRect(rect);
    
    
    CTestPreviewPopupProviderContent* provider = new ( ELeave ) CTestPreviewPopupProviderContent();
    CleanupStack::PushL( provider );
    iPopup = CAknPreviewPopUpController::NewL( *label, *provider );
    CleanupStack::Pop( 2 );
    STIF_ASSERT_NOT_NULL( iPopup );
    delete iPopup;
    iPopup = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPNewL, "In TestIPPNewL" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPNewL );
    // Print to log file
    iLog->Log( KTestIPPNewL );

    TRect rect( 120, 100, 200, 150);

    CEikLabel* label = new ( ELeave ) CEikLabel;
    CleanupStack::PushL( label );
    TBufC<128> buf(_L( "test" ));
    label->SetTextL( buf );
    
    label->SetRect(rect);
    
    
    iPopup = CAknPreviewPopUpController::NewL( *label );
    CleanupStack::Pop( label );
    STIF_ASSERT_NOT_NULL( iPopup );
    delete iPopup;
    iPopup = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPNewProviderAndStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPNewProviderAndStyleL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPNewProviderAndStyleL, "In TestIPPNewProviderAndStyleL" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPNewProviderAndStyleL );
    // Print to log file
    iLog->Log( KTestIPPNewProviderAndStyleL );

    TRect rect( 120, 100, 200, 150);

    CEikLabel* label = new ( ELeave ) CEikLabel;
    CleanupStack::PushL( label );
    TBufC<128> buf(_L( "test" ));
    label->SetTextL( buf );
    
    label->SetRect(rect);
    
    CTestPreviewPopupProviderContent* provider = new ( ELeave ) CTestPreviewPopupProviderContent();
    CleanupStack::PushL( provider );
    iPopup = CAknPreviewPopUpController::NewL( *label, *provider, CAknPreviewPopUpController::EPermanentMode );
    CleanupStack::Pop( 2 );
    STIF_ASSERT_NOT_NULL( iPopup );
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPNewStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPNewStyleL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPNewStyleL, "In TestIPPNewStyleL" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPNewStyleL );
    // Print to log file
    iLog->Log( KTestIPPNewStyleL );

    TRect rect( 120, 100, 200, 150);

    CEikLabel* label = new ( ELeave ) CEikLabel;
    CleanupStack::PushL( label );
    TBufC<128> buf(_L( "test" ));
    label->SetTextL( buf );
    
    label->SetRect(rect);


    iPopup = CAknPreviewPopUpController::NewL( *label, CAknPreviewPopUpController::EPermanentMode );
    CleanupStack::Pop( label );
    STIF_ASSERT_NOT_NULL( iPopup );
    delete iPopup;
    iPopup = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPContentSizeInLayout
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPContentSizeInLayout( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPContentSizeInLayout, "In TestIPPContentSizeInLayout" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPContentSizeInLayout );
    // Print to log file
    iLog->Log( KTestIPPContentSizeInLayout );

    CAknPreviewPopUpController::TAknPreviewPopUpContentSize contentSize = CAknPreviewPopUpController::ContentSizeInLayout();
    STIF_ASSERT_NOT_NULL( &contentSize );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPSetPopUpShowDelay
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPSetPopUpShowDelay( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPSetPopUpShowDelay, "In TestIPPSetPopUpShowDelay" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPSetPopUpShowDelay );
    // Print to log file
    iLog->Log( KTestIPPSetPopUpShowDelay );
    TTimeIntervalMicroSeconds32 delay = 100;

    iPopup->SetPopUpShowDelay( delay );
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPSetPopUpHideDelay
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPSetPopUpHideDelay( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPSetPopUpHideDelay, "In TestIPPSetPopUpHideDelay" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPSetPopUpHideDelay );
    // Print to log file
    iLog->Log( KTestIPPSetPopUpHideDelay );
    TTimeIntervalMicroSeconds32 delay = 100;

    iPopup->SetPopUpHideDelay( delay );
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPShowPopUp
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPShowPopUp( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPShowPopUp, "In TestIPPShowPopUp" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPShowPopUp );
    // Print to log file
    iLog->Log( KTestIPPShowPopUp );
    

    iPopup->ShowPopUp();
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPHidePopUp
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPHidePopUp( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPHidePopUp, "In TestIPPHidePopUp" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPHidePopUp );
    // Print to log file
    iLog->Log( KTestIPPHidePopUp );
    

    iPopup->HidePopUp();
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPContentReadyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPContentReadyL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPContentReadyL, "In TestIPPContentReadyL" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPContentReadyL );
    // Print to log file
    iLog->Log( KTestIPPContentReadyL );
    CTestPreviewPopupContent* content = new (ELeave) CTestPreviewPopupContent();
    CleanupStack::PushL( content );
    //CTestPreviewPopupProviderContent* provider = new ( ELeave ) CTestPreviewPopupProviderContent();
    //CleanupStack::PushL( provider );
    CAknPreviewPopUpController* popup = CAknPreviewPopUpController::NewL( *content );
    popup->ContentReady();
    CleanupStack::Pop( );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPSetPosition
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPSetPosition( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPSetPosition, "In TestIPPSetPosition" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPSetPosition );
    // Print to log file
    iLog->Log( KTestIPPSetPosition );
    
    iPopup->SetPosition( TPoint ( 120,100 ) );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPSetPositionByHighlight
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPSetPositionByHighlight( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPSetPositionByHighlight, "In TestIPPSetPositionByHighlight" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPSetPositionByHighlight );
    // Print to log file
    iLog->Log( KTestIPPSetPositionByHighlight );
    TRect rect( 120, 100, 200, 150);
    iPopup->SetPositionByHighlight( rect );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPAddObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPAddObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPAddObserverL, "In TestIPPAddObserverL" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPAddObserverL );
    // Print to log file
    iLog->Log( KTestIPPAddObserverL );

    CTestPreviewPopupContent* observer = new (ELeave) CTestPreviewPopupContent();
    CleanupStack::PushL( observer );
    TBool err = KErrNone;
    TRAP( err, iPopup->AddObserverL( *observer ) );
    CleanupStack::Pop( observer );

    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPRemoveObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPRemoveObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPRemoveObserverL, "In TestIPPRemoveObserverL" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPRemoveObserverL );
    // Print to log file
    iLog->Log( KTestIPPRemoveObserverL );

    CTestPreviewPopupContent* observer = new (ELeave) CTestPreviewPopupContent();
    CleanupStack::PushL( observer );

    iPopup->RemoveObserver( *observer );
    CleanupStack::Pop( observer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPUpdateContentSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPUpdateContentSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPUpdateContentSize, "In TestIPPUpdateContentSize" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPUpdateContentSize );
    // Print to log file
    iLog->Log( KTestIPPUpdateContentSize );

    iPopup->UpdateContentSize() ;
   

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPSize, "In TestIPPSize" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPSize );
    // Print to log file
    iLog->Log( KTestIPPSize );
    TSize size = iPopup->Size();
    STIF_ASSERT_NOT_NULL( &size );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPSetHeadingTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPSetHeadingTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPSetHeadingTextL, "In TestIPPSetHeadingTextL" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPSetHeadingTextL );
    // Print to log file
    iLog->Log( KTestIPPSetHeadingTextL );
    TBool err = KErrNone;
    TBufC<128> buf( _L("test") );
    TRAP( err, iPopup->SetHeadingTextL( buf ));
    

    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKInformationPreviewPopup::TestIPPResetTimer
// -----------------------------------------------------------------------------
//
TInt CTestSDKInformationPreviewPopup::TestIPPResetTimer( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinformationpreviewpopup, "testsdkinformationpreviewpopup" );
    _LIT( KTestIPPResetTimer, "In TestIPPResetTimer" );
    TestModuleIf().Printf( 0, Ktestsdkinformationpreviewpopup, KTestIPPResetTimer );
    // Print to log file
    iLog->Log( KTestIPPResetTimer );
    
    iPopup->ResetTimer();
    
    return KErrNone;
    }
//  [End of File]
