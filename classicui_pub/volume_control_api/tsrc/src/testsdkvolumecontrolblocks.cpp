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
* Description:  volume_control_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <barsread.h> 

#include <aknvolumecontrol.h>
#include <testsdkvolumecontrol.rsg>

#include "testsdkvolumecontrol.h"
#include "testsdkvolumecontainer.h"
#include "testsdkvolumeview.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestVCConstructorL", CTestSDKVolumeControl::TestVCConstructorL ),
        ENTRY( "TestVCDelete", CTestSDKVolumeControl::TestVCDelete ),
        ENTRY( "TestVCConstructFromResourceL", CTestSDKVolumeControl::TestVCConstructFromResourceL ),
        ENTRY( "TestVCSetValue", CTestSDKVolumeControl::TestVCSetValue ),
        ENTRY( "TestVCValue", CTestSDKVolumeControl::TestVCValue ),
        ENTRY( "TestVCSetRange", CTestSDKVolumeControl::TestVCSetRange ),
        ENTRY( "TestVCGetRange", CTestSDKVolumeControl::TestVCGetRange ),
        ENTRY( "TestVCHandleResourceChange", CTestSDKVolumeControl::TestVCHandleResourceChange ),
        ENTRY( "TestVCCreateBitmapL", CTestSDKVolumeControl::TestVCCreateBitmapL ),
        ENTRY( "TestVCCreateSetStyleListBoxIconL", 
                CTestSDKVolumeControl::TestVCCreateSetStyleListBoxIconL ),
        ENTRY( "TestVCCreateSetDynRangeStyleListBoxIconL", 
                CTestSDKVolumeControl::TestVCCreateSetDynRangeStyleListBoxIconL ),
        ENTRY( "TestVCHandlePointerEventL", CTestSDKVolumeControl::TestVCHandlePointerEventL ),
        ENTRY( "TestVCHandleNaviDecoratorEventL", 
                CTestSDKVolumeControl::TestVCHandleNaviDecoratorEventL ),


        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCConstructorL( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCConstructorL, "In TestVCConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCConstructorL );
    // Print to log file
    iLog->Log( KTestVCConstructorL );

    iVolumeControl = new (ELeave) CAknVolumeControl();
    STIF_ASSERT_NOT_NULL( iVolumeControl );

    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCDelete( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCDelete, "In TestVCDelete" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCDelete );
    // Print to log file
    iLog->Log( KTestVCDelete );

    delete iVolumeControl;
    iVolumeControl = NULL;

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCConstructFromResourceL( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCConstructFromResourceL, "In TestVCConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestVCConstructFromResourceL );
    iVolumeView = CVolumeControlView::NewL();

    iVolumeContainer = new( ELeave ) CVolumeControlContainer();


    iVolumeContainer->SetMopParent( iVolumeView );
    iVolumeContainer->ConstructL( iVolumeView->ClientRect() );
    CCoeEnv::Static()->AppUi()->AddToStackL( iVolumeContainer );
    iVolumeContainer->MakeVisible(ETrue);
    TResourceReader reader;
    iVolumeControl->SetContainerWindowL( *iVolumeContainer );
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTVOLUME_VOLUMECONTROL );
    TBool err = KErrNone;
    TRAP( err, iVolumeControl->ConstructFromResourceL( reader ) );
   
    CleanupStack::PopAndDestroy( );


    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCSetValue
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCSetValue( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCSetValue, "In TestVCSetValue" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCSetValue );
    // Print to log file
    iLog->Log( KTestVCSetValue );
    TInt value = 1;

    iVolumeControl->SetValue( value );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCValue
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCValue( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCValue, "In TestVCValue" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCValue );
    // Print to log file
    iLog->Log( KTestVCValue );
    TInt value = iVolumeControl->Value();
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCSetRange
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCSetRange( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCSetRange, "In TestVCSetRange" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCSetRange );
    // Print to log file
    iLog->Log( KTestVCSetRange );
    TInt minimumValue = 1;
    TInt maximumValue = 9;
    iVolumeControl->SetRange( minimumValue, maximumValue );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCGetRange
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCGetRange( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCGetRange, "In TestVCGetRange" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCGetRange );
    // Print to log file
    iLog->Log( KTestVCGetRange );
    TInt minimumValue;
    TInt maximumValue;
    iVolumeControl->GetRange( minimumValue, maximumValue );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCHandleResourceChange
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCHandleResourceChange( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCHandleResourceChange, "In TestVCHandleResourceChange" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCHandleResourceChange );
    // Print to log file
    iLog->Log( KTestVCHandleResourceChange );
    TInt type = 0;
    iVolumeControl->HandleResourceChange( type );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCCreateBitmapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCCreateBitmapL( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCCreateBitmapL, "In TestVCCreateBitmapL" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCCreateBitmapL );
    // Print to log file
    iLog->Log( KTestVCCreateBitmapL );
    TInt value = 0;
    TBool err = KErrNone;
    TRAP( err, CFbsBitmap* bitmap = iVolumeControl->CreateBitmapL( value ) );

    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCCreateSetStyleListBoxIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCCreateSetStyleListBoxIconL( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCCreateSetStyleListBoxIconL, "In TestVCCreateSetStyleListBoxIconL" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCCreateSetStyleListBoxIconL );
    // Print to log file
    iLog->Log( KTestVCCreateSetStyleListBoxIconL );
    TInt value = 0;
    TBool err = KErrNone;
    TRAP( err, CGulIcon* gulIcon = iVolumeControl->CreateSetStyleListBoxIconL( value ) );

    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCCreateSetDynRangeStyleListBoxIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCCreateSetDynRangeStyleListBoxIconL( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCCreateSetDynRangeStyleListBoxIconL, "In TestVCCreateSetDynRangeStyleListBoxIconL" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCCreateSetDynRangeStyleListBoxIconL );
    // Print to log file
    iLog->Log( KTestVCCreateSetDynRangeStyleListBoxIconL );
    TInt value = 0;
    TInt minimum = 0;
    TInt maximum = 9;
    TBool err = KErrNone;
    TRAP( err, CGulIcon* gulIcon = 
    iVolumeControl->CreateSetDynRangeStyleListBoxIconL( value, minimum, maximum ) );

    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCHandlePointerEventL( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCHandlePointerEventL, "In TestVCHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestVCHandlePointerEventL );
    TPointerEvent pointerEvent;
    pointerEvent.iType = TPointerEvent::EButton1Down;
    TBool err = KErrNone;
    TRAP( err, iVolumeControl->HandlePointerEventL( pointerEvent ) );

    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKVolumeControl::TestVCHandleNaviDecoratorEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKVolumeControl::TestVCHandleNaviDecoratorEventL( CStifItemParser& /*aItem */ )
    {

    // Print to UI
    _LIT( Ktestsdkvolumecontrol, "testsdkvolumecontrol" );
    _LIT( KTestVCHandleNaviDecoratorEventL, "In TestVCHandleNaviDecoratorEventL" );
    TestModuleIf().Printf( 0, Ktestsdkvolumecontrol, KTestVCHandleNaviDecoratorEventL );
    // Print to log file
    iLog->Log( KTestVCHandleNaviDecoratorEventL );
    TInt eventID = 0;
    TBool err = KErrNone;
    TRAP( err, iVolumeControl->HandleNaviDecoratorEventL( eventID ) );

    return err;

    }
//  [End of File]
