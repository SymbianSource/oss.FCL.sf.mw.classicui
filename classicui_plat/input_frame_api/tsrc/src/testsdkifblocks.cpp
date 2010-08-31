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
* Description:  input_frame_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akninfrm.h>
#include <akniconutils.h> 
#include <eikedwin.h> 
#include <w32std.h>
#include <barsread.h> 
#include <testsdkif.rsg> 
#include <aknsframebackgroundcontrolcontext.h> 
#include <avkon.mbg>

#include "testsdkif.h"
#include "testsdkifcontainer.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKIF::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKIF::Delete() 
    {
    if ( iInputFrame )
        {
        delete iInputFrame;
        iInputFrame = NULL;
        }
    

    }

// -----------------------------------------------------------------------------
// CTestSDKIF::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        
        ENTRY( "TestIFNewL", CTestSDKIF::TestIFNewL ),
        ENTRY( "TestIFNewWithIconL", CTestSDKIF::TestIFNewWithIconL ),
        ENTRY( "TestIFdelete", CTestSDKIF::TestIFdelete ),
        ENTRY( "TestIFField", CTestSDKIF::TestIFField ),
        ENTRY( "TestIFSetInfoTextL", CTestSDKIF::TestIFSetInfoTextL ),
        ENTRY( "TestIFSetLineState", CTestSDKIF::TestIFSetLineState ),
        ENTRY( "TestIFHandleControlEventL", CTestSDKIF::TestIFHandleControlEventL ),
        ENTRY( "TestIFOfferKeyEventL", CTestSDKIF::TestIFOfferKeyEventL ),
        ENTRY( "TestIFMinimumSize", CTestSDKIF::TestIFMinimumSize ),
        ENTRY( "TestIFConstructFromResourceL", CTestSDKIF::TestIFConstructFromResourceL ),
        ENTRY( "TestIFSetInputContextL", CTestSDKIF::TestIFSetInputContextL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


// -----------------------------------------------------------------------------
// CTestSDKIF::TestIFNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::TestIFNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkif, "testsdkif" );
    _LIT( KTestIFNewL, "In TestIFNewL" );
    TestModuleIf().Printf( 0, Ktestsdkif, KTestIFNewL );
    // Print to log file
    iLog->Log( KTestIFNewL );

    
    iInputFrameContainer = new (ELeave) CInputFrameContainer() ;
    TRect rect( 10, 10, 10, 10 );
    iInputFrameContainer->ConstructL( rect );


    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    bmp->Load( AknIconUtils::AvkonIconFileName());
    
    iInputFrame = CAknInputFrame::NewL( iInputFrameContainer, EFalse, 
            AknIconUtils::AvkonIconFileName(), EMbmAvkonQgn_graf_tab_21, 
            EMbmAvkonQgn_graf_tab_21_mask, 0 );
    
    CleanupStack::Pop( bmp );
    delete iInputFrameContainer;
    iInputFrameContainer = NULL;

    
    STIF_ASSERT_NOT_NULL( iInputFrame );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKIF::TestIFNewLWithIcon
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::TestIFNewWithIconL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkif, "testsdkif" );
    _LIT( KTestIFNewLWithIcon, "In TestIFNewLWithIcon" );
    TestModuleIf().Printf( 0, Ktestsdkif, KTestIFNewLWithIcon );
    // Print to log file
    iLog->Log( KTestIFNewLWithIcon );


    CEikEdwin* edwin = new( ELeave ) CEikEdwin();
    CleanupStack::PushL( edwin );

    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );

    CGulIcon* icon = CGulIcon::NewL( bmp );
    CleanupStack::PushL( icon );
    iInputFrame = CAknInputFrame::NewL( edwin, EFalse, icon );
    CleanupStack::Pop( icon );
    CleanupStack::Pop( bmp );
    CleanupStack::Pop( edwin );

    STIF_ASSERT_NOT_NULL( iInputFrame );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKIF::TestIFdelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::TestIFdelete( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkif, "testsdkif" );
    _LIT( KTestIFNewLWithIcon, "In TestIFNewLWithIcon" );
    TestModuleIf().Printf( 0, Ktestsdkif, KTestIFNewLWithIcon );
    // Print to log file
    iLog->Log( KTestIFNewLWithIcon );
    
    delete iInputFrame;
    iInputFrame = NULL;
    
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKIF::TestIFField
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::TestIFField( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkif, "testsdkif" );
    _LIT( KTestIFField, "In TestIFField" );
    TestModuleIf().Printf( 0, Ktestsdkif, KTestIFField );
    // Print to log file
    iLog->Log( KTestIFField );

    CCoeControl* coectl = iInputFrame->Field( );
    
    STIF_ASSERT_NOT_NULL( coectl );
    
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKIF::TestIFSetInfoTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::TestIFSetInfoTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkif, "testsdkif" );
    _LIT( KTestIFSetInfoTextL, "In TestIFSetInfoTextL" );
    TestModuleIf().Printf( 0, Ktestsdkif, KTestIFSetInfoTextL );
    // Print to log file
    iLog->Log( KTestIFSetInfoTextL );

    TBufC<128> buf(_L("test"));
 
    TBool err = KErrNone;
    TRAP ( err, iInputFrame->SetInfoTextL( buf ));
    
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKIF::TestIFSetLineState
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::TestIFSetLineState( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkif, "testsdkif" );
    _LIT( KTestIFSetLineState, "In TestIFSetLineState" );
    TestModuleIf().Printf( 0, Ktestsdkif, KTestIFSetLineState );
    // Print to log file
    iLog->Log( KTestIFSetLineState );

    iInputFrame->SetLineState( ETrue );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKIF::TestIFHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::TestIFHandleControlEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkif, "testsdkif" );
    _LIT( KTestIFHandleControlEventL, "In TestIFHandleControlEventL" );
    TestModuleIf().Printf( 0, Ktestsdkif, KTestIFHandleControlEventL );
    // Print to log file
    iLog->Log( KTestIFHandleControlEventL );

    
    
    TBool err = KErrNone;
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
   
    TRAP ( err, iInputFrame->HandleControlEventL( control, MCoeControlObserver::EEventStateChanged ));
    CleanupStack::Pop( control );
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKIF::TestIFOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::TestIFOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkif, "testsdkif" );
    _LIT( KTestIFOfferKeyEventL, "In TestIFOfferKeyEventL" );
    TestModuleIf().Printf( 0, Ktestsdkif, KTestIFOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestIFOfferKeyEventL );
   
    TKeyEvent kEvent;
    kEvent.iCode = 0;
    kEvent.iModifiers = EModifierKeyUp;
    kEvent.iRepeats = 0;
    kEvent.iScanCode = EStdKeyPageUp;
    TBool err = KErrNone;
   
    TRAP ( err, iInputFrame->OfferKeyEventL( kEvent, EEventKeyUp ));
    
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKIF::TestIFMinimumSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::TestIFMinimumSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkif, "testsdkif" );
    _LIT( KTestIFMinimumSize, "In TestIFMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkif, KTestIFMinimumSize );
    // Print to log file
    iLog->Log( KTestIFMinimumSize );
    
    TSize size = iInputFrame->MinimumSize();
    STIF_ASSERT_NOT_NULL( &size );
    return KErrNone;
 
   


    

    }
// -----------------------------------------------------------------------------
// CTestSDKIF::TestIFConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::TestIFConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkif, "testsdkif" );
    _LIT( KTestIFConstructFromResourceL, "In TestIFConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestsdkif, KTestIFConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestIFConstructFromResourceL ); 
    TBool err = KErrNone;
    iInputFrameContainer = new (ELeave) CInputFrameContainer() ;
    TRect rect( 10, 10, 10, 10 );
    iInputFrameContainer->ConstructL( rect );
    iInputFrame->SetContainerWindowL( *iInputFrameContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_INPUT);
    
//    TRAP ( err, iInputFrame->ConstructFromResourceL( reader ) );
    iInputFrame->ConstructFromResourceL( reader );
    
    delete iInputFrameContainer;
    iInputFrameContainer = NULL;
    CleanupStack::PopAndDestroy();

    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKIF::TestIFSetInputContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKIF::TestIFSetInputContextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkif, "testsdkif" );
    _LIT( KTestIFSetInputContext, "In TestIFSetInputContext" );
    TestModuleIf().Printf( 0, Ktestsdkif, KTestIFSetInputContext );
    // Print to log file
    iLog->Log( KTestIFSetInputContext );
   
    iInputFrame->SetInputContext( NULL );    

    return KErrNone;
    }
//  [End of File]
