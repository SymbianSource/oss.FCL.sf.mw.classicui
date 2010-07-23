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
* Description:  info_popup_note_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akninfopopupnotecontroller.h>
#include <gulalign.h> 
#include <bassnd.h>



#include "testsdkinfopopupnote.h"


// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKInfoPopupNote::Delete() 
    {
    if ( infoPopupNoteController )
        {
        delete infoPopupNoteController;
        infoPopupNoteController = NULL;
        }
    }

// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        
        ENTRY( "TestIPNCNewL", CTestSDKInfoPopupNote::TestIPNCNewL ),
        ENTRY( "TestIPNCSetTimeDelayBeforeShow", CTestSDKInfoPopupNote::TestIPNCSetTimeDelayBeforeShow ),
        ENTRY( "TestIPNCSetTimePopupInView", CTestSDKInfoPopupNote::TestIPNCSetTimePopupInView ),
        ENTRY( "TestIPNCSetTextL", CTestSDKInfoPopupNote::TestIPNCSetTextL ),
        ENTRY( "TestIPNCShowInfoPopupNote", CTestSDKInfoPopupNote::TestIPNCShowInfoPopupNote ),
        ENTRY( "TestIPNCHideInfoPopupNote", CTestSDKInfoPopupNote::TestIPNCHideInfoPopupNote ),
        ENTRY( "TestIPNCAddObserverL", CTestSDKInfoPopupNote::TestIPNCAddObserverL ),
        ENTRY( "TestIPNCRemoveObserverL", CTestSDKInfoPopupNote::TestIPNCRemoveObserverL ),
        ENTRY( "TestIPNCSetPositionAndAlignment", CTestSDKInfoPopupNote::TestIPNCSetPositionAndAlignment ),
        ENTRY( "TestIPNCSetPositionByHighlight", CTestSDKInfoPopupNote::TestIPNCSetPositionByHighlight ),
        ENTRY( "TestIPNCRestoreDefaultPosition", CTestSDKInfoPopupNote::TestIPNCRestoreDefaultPosition ),
        ENTRY( "TestIPNCSetTooltipModeL", CTestSDKInfoPopupNote::TestIPNCSetTooltipModeL ),
        ENTRY( "TestIPNCSetTone", CTestSDKInfoPopupNote::TestIPNCSetTone ),
        ENTRY( "TestIPNCHideWhenAppFaded", CTestSDKInfoPopupNote::TestIPNCHideWhenAppFaded ),       // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCNewL, "In TestIPNCNewL" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCNewL );
    // Print to log file
    iLog->Log( KTestIPNCNewL );
    
    infoPopupNoteController = CAknInfoPopupNoteController::NewL();
    STIF_ASSERT_NOT_NULL( infoPopupNoteController );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCSetTimeDelayBeforeShow
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCSetTimeDelayBeforeShow( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCSetTimeDelayBeforeShow, "In TestIPNCSetTimeDelayBeforeShow" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCSetTimeDelayBeforeShow );
    // Print to log file
    iLog->Log( KTestIPNCSetTimeDelayBeforeShow );
   
    TBool err = KErrNone;
    TRAP( err, infoPopupNoteController->SetTimeDelayBeforeShow( 1 ));
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCSetTimePopupInView
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCSetTimePopupInView( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCSetTimePopupInView, "In TestIPNCSetTimePopupInView" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCSetTimePopupInView );
    // Print to log file
    iLog->Log( KTestIPNCSetTimePopupInView );
    
    TBool err = KErrNone;
    TRAP( err, infoPopupNoteController->SetTimePopupInView( 10 ));
   
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCSetTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCSetTextL, "In TestIPNCSetTextL" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCSetTextL );
    // Print to log file
    iLog->Log( KTestIPNCSetTextL );
   
    TBufC<128> buf (_L("test"));
    TBool err = KErrNone;
    TRAP( err, infoPopupNoteController->SetTextL( buf ));
   
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCShowInfoPopupNote
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCShowInfoPopupNote( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCShowInfoPopupNote, "In TestIPNCShowInfoPopupNote" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCShowInfoPopupNote );
    // Print to log file
    iLog->Log( KTestIPNCShowInfoPopupNote );
   
   
    TBool err = KErrNone;
    TRAP( err, infoPopupNoteController->ShowInfoPopupNote());
   
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCHideInfoPopupNote
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCHideInfoPopupNote( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCHideInfoPopupNote, "In TestIPNCHideInfoPopupNote" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCHideInfoPopupNote );
    // Print to log file
    iLog->Log( KTestIPNCHideInfoPopupNote );
   
   
    TBool err = KErrNone;
    TRAP( err, infoPopupNoteController->HideInfoPopupNote());
   
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCAddObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCAddObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCAddObserverL, "In TestIPNCAddObserverL" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCAddObserverL );
    // Print to log file
    iLog->Log( KTestIPNCAddObserverL );

    TBool err = KErrNone;
    
    TestSubAknInfoPopupNoteObserver aObserver;
    
    TRAP( err, infoPopupNoteController->AddObserverL( aObserver ));
   
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCRemoveObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCRemoveObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCRemoveObserverL, "In TestIPNCRemoveObserverL" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCRemoveObserverL );
    // Print to log file
    iLog->Log( KTestIPNCRemoveObserverL );
   
    
    TestSubAknInfoPopupNoteObserver observer;
    
    infoPopupNoteController->RemoveObserver( observer );
   
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCSetPositionAndAlignment
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCSetPositionAndAlignment( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCSetPositionAndAlignment, "In TestIPNCSetPositionAndAlignment" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCSetPositionAndAlignment );
    // Print to log file
    iLog->Log( KTestIPNCSetPositionAndAlignment );
   
    
    TPoint position;
    TGulAlignmentValue lignment;
    
    infoPopupNoteController->SetPositionAndAlignment( position, lignment );
   
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCSetPositionByHighlight
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCSetPositionByHighlight( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCSetPositionByHighlight, "In TestIPNCSetPositionByHighlight" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCSetPositionByHighlight );
    // Print to log file
    iLog->Log( KTestIPNCSetPositionByHighlight );
   
    
    TRect highlightRect;
    
    infoPopupNoteController->SetPositionByHighlight( highlightRect );
   
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCRestoreDefaultPosition
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCRestoreDefaultPosition( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCRestoreDefaultPosition, "In TestIPNCRestoreDefaultPosition" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCRestoreDefaultPosition );
    // Print to log file
    iLog->Log( KTestIPNCRestoreDefaultPosition );
   

    
    infoPopupNoteController->RestoreDefaultPosition();
   
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCSetTooltipModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCSetTooltipModeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCSetTooltipModeL, "In TestIPNCSetTooltipModeL" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCSetTooltipModeL );
    // Print to log file
    iLog->Log( KTestIPNCSetTooltipModeL );
 
    TBool err = KErrNone;
    
    TRAP( err, infoPopupNoteController->SetTooltipModeL( ETrue ));
   
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCSetTone
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCSetTone( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCSetTone, "In TestIPNCSetTone" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCSetTone );
    // Print to log file
    iLog->Log( KTestIPNCSetTone );
    
    
    
    
    infoPopupNoteController->SetTone( CAknInfoPopupNoteController::EConfirmationTone );
   
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKInfoPopupNote::TestIPNCHideWhenAppFaded
// -----------------------------------------------------------------------------
//
TInt CTestSDKInfoPopupNote::TestIPNCHideWhenAppFaded( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkinfopopupnote, "testsdkinfopopupnote" );
    _LIT( KTestIPNCHideWhenAppFaded, "In TestIPNCHideWhenAppFaded" );
    TestModuleIf().Printf( 0, Ktestsdkinfopopupnote, KTestIPNCHideWhenAppFaded );
    // Print to log file
    iLog->Log( KTestIPNCHideWhenAppFaded );
    
    
    
   
    infoPopupNoteController->HideWhenAppFaded( ETrue );
   
    return KErrNone;
    }
//  [End of File]
