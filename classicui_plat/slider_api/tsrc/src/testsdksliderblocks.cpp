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
* Description:  slider_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknslider.h>
#include <coemain.h> 
#include <fbs.h> 
#include <avkon.hrh>
#include <coecntrl.h>

#include <barsread.h>
#include <testsdkslider.rsg>


#include "testsdkslider.h"
#include "testsdkslidercontainer.h"
#include "testsdksliderview.h"
#include "testsdksliderprotectedclass.h"
// [const data]

const TInt kMinimumValue = 0;
const TInt kMaxmumValue = 100;
const TInt kStep = 2;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSlider::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKSlider::Delete() 
    {


    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestSliderConstructorL", CTestSDKSlider::TestSliderConstructorL ),
        ENTRY( "TestSliderDelete", CTestSDKSlider::TestSliderDelete ),
        ENTRY( "TestSliderSetValueL", CTestSDKSlider::TestSliderSetValueL ),
        ENTRY( "TestSliderValue", CTestSDKSlider::TestSliderValue ),
        ENTRY( "TestSliderSetRange", CTestSDKSlider::TestSliderSetRange ),
        ENTRY( "TestSliderGetRange", CTestSDKSlider::TestSliderGetRange ),
        ENTRY( "TestSliderSetStepSize", CTestSDKSlider::TestSliderSetStepSize ),
        ENTRY( "TestSliderSetMinimumTextL", CTestSDKSlider::TestSliderSetMinimumTextL ),
        ENTRY( "TestSliderSetMaximumTextL", CTestSDKSlider::TestSliderSetMaximumTextL ),
        ENTRY( "TestSliderSetDecimalPlaces", CTestSDKSlider::TestSliderSetDecimalPlaces ),
        ENTRY( "TestSliderDecimalPlaces", CTestSDKSlider::TestSliderDecimalPlaces ),
        ENTRY( "TestSliderSetGraphicsL", CTestSDKSlider::TestSliderSetGraphicsL ),
        ENTRY( "TestSliderUseDefaultGraphics", CTestSDKSlider::TestSliderUseDefaultGraphics ),
        ENTRY( "TestSliderUsesDefaultGraphicsReturnTBool", CTestSDKSlider::TestSliderUsesDefaultGraphicsReturnTBool ),
        ENTRY( "TestSliderSetPositionIndicators", CTestSDKSlider::TestSliderSetPositionIndicators ),
        ENTRY( "TestSliderPositionIndicators", CTestSDKSlider::TestSliderPositionIndicators ),
        ENTRY( "TestSliderOrientation", CTestSDKSlider::TestSliderOrientation ),
        ENTRY( "TestSliderSetTicksEnabled", CTestSDKSlider::TestSliderSetTicksEnabled ),
        ENTRY( "TestSliderTicksEnabled", CTestSDKSlider::TestSliderTicksEnabled ),
        ENTRY( "TestSliderSetTickInterval", CTestSDKSlider::TestSliderSetTickInterval ),
        ENTRY( "TestSliderTickInterval", CTestSDKSlider::TestSliderTickInterval ),
        ENTRY( "TestSliderCreateBitmapL", CTestSDKSlider::TestSliderCreateBitmapL ),
        ENTRY( "TestSliderCreateBitmapWithValuL", CTestSDKSlider::TestSliderCreateBitmapWithValuL ),
        ENTRY( "TestSliderCreateSetStyleListBoxIconL", CTestSDKSlider::TestSliderCreateSetStyleListBoxIconL ),
        ENTRY( "TestSliderCreateSetStyleListBoxIconWithValuL", CTestSDKSlider::TestSliderCreateSetStyleListBoxIconWithValuL ),
        ENTRY( "TestSliderEnableDragL", CTestSDKSlider::TestSliderEnableDragL ),
        ENTRY( "TestSliderConstructFromResourceL", CTestSDKSlider::TestSliderConstructFromResourceL ),
        ENTRY( "TestSliderConstructFromResourceWithControlL", CTestSDKSlider::TestSliderConstructFromResourceWithControlL ),
        ENTRY( "TestSliderHandleResourceChange", CTestSDKSlider::TestSliderHandleResourceChange ),
        ENTRY( "TestSliderNumberOfLines", CTestSDKSlider::TestSliderNumberOfLines ),
        ENTRY( "TestSliderCreateValueTextInHBufCL", CTestSDKSlider::TestSliderCreateValueTextInHBufCL ),
        ENTRY( "TestSliderCountComponentControlsL", CTestSDKSlider::TestSliderCountComponentControlsL ),
        ENTRY( "TestSliderComponentControlL", CTestSDKSlider::TestSliderComponentControlL ),
        ENTRY( "TestSliderHandlePointerEventL", CTestSDKSlider::TestSliderHandlePointerEventL ),
        ENTRY( "TestSliderSetValueTextL", CTestSDKSlider::TestSliderSetValueTextL ),
        ENTRY( "TestSliderFocusChanged", CTestSDKSlider::TestSliderFocusChanged ),




        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderConstructorL, "In TestSliderConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderConstructorL );
    // Print to log file
    iLog->Log( KTestSliderConstructorL );

    iSlider = new (ELeave) CAknSlider;
    STIF_ASSERT_NOT_NULL( iSlider );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderDelete( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderDelete, "In TestSliderDelete" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderDelete );
    // Print to log file
    iLog->Log( KTestSliderDelete );

    delete iSlider;
    iSlider = NULL;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderSetValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderSetValueL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderSetValueL, "In TestSliderSetValueL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderSetValueL );
    // Print to log file
    iLog->Log( KTestSliderSetValueL );
   
    TBool err = KErrNone;
    
    TInt value = iSlider->Value();
    TRAP ( err, iSlider->SetValueL( value ) );
    
    
    return err;  
    }



// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderValue
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderValue( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderValue, "In TestSliderValue" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderValue );
    // Print to log file
    iLog->Log( KTestSliderValue );

    TInt value = iSlider->Value();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderSetRange
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderSetRange( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderSetRange, "In TestSliderSetRange" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderSetRange );
    // Print to log file
    iLog->Log( KTestSliderSetRange );

    iSlider->SetRange( kMinimumValue,kMaxmumValue );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderGetRange
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderGetRange( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderGetRange, "In TestSliderGetRange" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderGetRange );
    // Print to log file
    iLog->Log( KTestSliderGetRange );
    TInt minimumValue = 0;
    TInt maxmumValue = 100;
    
    iSlider->GetRange( minimumValue, maxmumValue );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderGetRange
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderSetStepSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderSetStepSize, "In TestSliderSetStepSize" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderSetStepSize );
    // Print to log file
    iLog->Log( KTestSliderSetStepSize );
    
    iSlider->SetStepSize( kStep );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderSetMinimumTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderSetMinimumTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderSetMinimumTextL, "In TestSliderSetMinimumTextL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderSetMinimumTextL );
    // Print to log file
    iLog->Log( KTestSliderSetMinimumTextL );
    
    TBool err = KErrNone;
    TBufC<128> buf( _L("MiniTEST") );
    TRAP ( err, iSlider->SetMinimumTextL( buf ) );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderSetMaximumTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderSetMaximumTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderSetMaximumTextL, "In TestSliderSetMaximumTextL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderSetMaximumTextL );
    // Print to log file
    iLog->Log( KTestSliderSetMaximumTextL );
    
    TBool err = KErrNone;
    TBufC<128> buf( _L("MaxTEST") );
    TRAP ( err, iSlider->SetMaximumTextL( buf ) );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderSetDecimalPlaces
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderSetDecimalPlaces( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderSetDecimalPlaces, "In TestSliderSetDecimalPlaces" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderSetDecimalPlaces );
    // Print to log file
    iLog->Log( KTestSliderSetDecimalPlaces );

    iSlider->SetDecimalPlaces( kMinimumValue );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderDecimalPlaces
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderDecimalPlaces( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderDecimalPlaces, "In TestSliderDecimalPlaces" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderDecimalPlaces );
    // Print to log file
    iLog->Log( KTestSliderDecimalPlaces );

    TInt decimal = iSlider->DecimalPlaces();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderSetGraphicsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderSetGraphicsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderSetGraphicsL, "In TestSliderSetGraphicsL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderSetGraphicsL );
    // Print to log file
    iLog->Log( KTestSliderSetGraphicsL );

    TInt value = iSlider->Value();
    CFbsBitmap* bitmap = iSlider->CreateBitmapL( value, R_TESTSLIDER_SLIDER );
    
    iSlider->SetGraphics( kMinimumValue, bitmap, kMinimumValue );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderUseDefaultGraphics
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderUseDefaultGraphics( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderUseDefaultGraphics, "In TestSliderUseDefaultGraphics" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderUseDefaultGraphics );
    // Print to log file
    iLog->Log( KTestSliderUseDefaultGraphics );
    iSlider->UseDefaultGraphics( kMinimumValue );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderUsesDefaultGraphicsReturnTBool
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderUsesDefaultGraphicsReturnTBool( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderUsesDefaultGraphicsReturnTBool, "In TestSliderUsesDefaultGraphicsReturnTBool" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderUsesDefaultGraphicsReturnTBool );
    // Print to log file
    iLog->Log( KTestSliderUsesDefaultGraphicsReturnTBool );
    TBool defaltGraphics;
    defaltGraphics = iSlider->UsesDefaultGraphics( kMinimumValue );
    STIF_ASSERT_FALSE( defaltGraphics );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderSetPositionIndicators
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderSetPositionIndicators( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderSetPositionIndicators, "In TestSliderSetPositionIndicators" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderSetPositionIndicators );
    // Print to log file
    iLog->Log( KTestSliderSetPositionIndicators );
    
    iSlider->SetPositionIndicators( kMinimumValue );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderPositionIndicators
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderPositionIndicators( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderPositionIndicators, "In TestSliderPositionIndicators" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderPositionIndicators );
    // Print to log file
    iLog->Log( KTestSliderPositionIndicators );
    
    TUint32 positionIndicators = iSlider->PositionIndicators();
    TUint32 minimumValue =0;
    STIF_ASSERT_NOT_EQUALS( minimumValue, positionIndicators );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderOrientation
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderOrientation( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderOrientation, "In TestSliderOrientation" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderOrientation );
    // Print to log file
    iLog->Log( KTestSliderOrientation );

    TAknOrientation Orientation = iSlider->Orientation();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderSetTicksEnabled
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderSetTicksEnabled( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderSetTicksEnabled, "In TestSliderSetTicksEnabled" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderSetTicksEnabled );
    // Print to log file
    iLog->Log( KTestSliderSetTicksEnabled );

    iSlider->SetTicksEnabled( ETrue );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderTicksEnabled
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderTicksEnabled( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderTicksEnabled, "In TestSliderTicksEnabled" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderTicksEnabled );
    // Print to log file
    iLog->Log( KTestSliderTicksEnabled );

    TBool ticksEnabled = iSlider->TicksEnabled();
    STIF_ASSERT_FALSE( ticksEnabled );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderSetTickInterval
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderSetTickInterval( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderSetTickInterval, "In TestSliderSetTickInterval" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderSetTickInterval );
    // Print to log file
    iLog->Log( KTestSliderSetTickInterval );
   
    iSlider->SetTickInterval( kMinimumValue );
   

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderTickInterval
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderTickInterval( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderTickInterval, "In TestSliderTickInterval" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderTickInterval );
    // Print to log file
    iLog->Log( KTestSliderTickInterval );
   
    TUint tickInterval = iSlider->TickInterval();
    TUint minimumValue = 0;
    STIF_ASSERT_EQUALS( minimumValue, tickInterval );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderCreateBitmapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderCreateBitmapL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderCreateBitmapL, "In TestSliderCreateBitmapL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderCreateBitmapL );
    // Print to log file
    iLog->Log( KTestSliderCreateBitmapL );

    TInt value = iSlider->Value();
    CFbsBitmap* bitmap = CAknSlider::CreateBitmapL( value, R_TESTSLIDER_SLIDER);
    STIF_ASSERT_NOT_NULL( bitmap );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderCreateBitmapWithValuL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderCreateBitmapWithValuL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderCreateBitmapWithValuL, "In TestSliderCreateBitmapWithValuL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderCreateBitmapWithValuL );
    // Print to log file
    iLog->Log( KTestSliderCreateBitmapWithValuL );

    TInt value = iSlider->Value();
    TInt minimumValue = 0;
    TInt maxmumValue = 100;

    CFbsBitmap* bitmap = CAknSlider::CreateBitmapL( value, minimumValue, maxmumValue);
    STIF_ASSERT_NOT_NULL( bitmap );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderCreateSetStyleListBoxIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderCreateSetStyleListBoxIconL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderCreateSetStyleListBoxIconL, "In TestSliderCreateSetStyleListBoxIconL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderCreateSetStyleListBoxIconL );
    // Print to log file
    iLog->Log( KTestSliderCreateSetStyleListBoxIconL );

    TInt value = iSlider->Value();


    CGulIcon* gulIcon = CAknSlider::CreateSetStyleListBoxIconL( value, R_TESTSLIDER_SLIDER );
    STIF_ASSERT_NOT_NULL( gulIcon );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderCreateSetStyleListBoxIconWithValuL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderCreateSetStyleListBoxIconWithValuL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderCreateSetStyleListBoxIconWithValuL, "In TestSliderCreateSetStyleListBoxIconWithValuL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderCreateSetStyleListBoxIconWithValuL );
    // Print to log file
    iLog->Log( KTestSliderCreateSetStyleListBoxIconWithValuL );

    TInt value = iSlider->Value();
    TInt minimumValue = 0;
    TInt maxmumValue = 100;

    CGulIcon* gulIcon = CAknSlider::CreateSetStyleListBoxIconL( value, minimumValue, maxmumValue );
    STIF_ASSERT_NOT_NULL( gulIcon );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderEnableDragL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderEnableDragL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderEnableDragL, "In TestSliderEnableDragL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderEnableDragL );
    // Print to log file
    iLog->Log( KTestSliderEnableDragL );
    
    iSliderView = CSliderView::NewL();
    iSliderContainer = new( ELeave ) CSliderContainer();
    iSliderContainer->SetMopParent( iSliderView );
    iSliderContainer->ConstructL( iSliderView->ClientRect() );
    CCoeEnv::Static()->AppUi()->AddToStackL( iSliderContainer );
    iSliderContainer->MakeVisible( ETrue );
    iSlider->SetContainerWindowL( *iSliderContainer ); 

    iSlider->EnableDrag();

    
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderConstructFromResourceL, "In TestSliderConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestSliderConstructFromResourceL );
   
    TBool err = KErrNone;
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSLIDER_SLIDER );

    TRAP ( err, iSlider->ConstructFromResourceL( reader ));
    CleanupStack::PopAndDestroy();
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderConstructFromResourceWithControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderConstructFromResourceWithControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderConstructFromResourceWithControlL, "In TestSliderConstructFromResourceWithControlL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderConstructFromResourceWithControlL );
    // Print to log file
    iLog->Log( KTestSliderConstructFromResourceWithControlL );
   
    TBool err = KErrNone;
    TResourceReader reader;

    TInt value = iSlider->Value();
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSLIDER_SLIDER );
    CCoeControl* parent = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( parent );
    TRAP ( err, iSlider->ConstructFromResourceL( parent, value, reader ));
   
    CleanupStack::PopAndDestroy( 2 );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderHandleResourceChange
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderHandleResourceChange( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderHandleResourceChange, "In TestSliderHandleResourceChange" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderHandleResourceChange );
    // Print to log file
    iLog->Log( KTestSliderHandleResourceChange );

    iSlider->HandleResourceChange( kMinimumValue );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderNumberOfLines
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderNumberOfLines( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderNumberOfLines, "In TestSliderNumberOfLines" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderNumberOfLines );
    // Print to log file
    iLog->Log( KTestSliderNumberOfLines );

    TInt expect = 0;
    TInt numberOfLines = iSlider->NumberOfLines();
    STIF_ASSERT_NOT_EQUALS( expect, numberOfLines);

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderCreateValueTextInHBufCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderCreateValueTextInHBufCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderCreateValueTextInHBufCL, "In TestSliderCreateValueTextInHBufCL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderCreateValueTextInHBufCL );
    // Print to log file
    iLog->Log( KTestSliderCreateValueTextInHBufCL );

    TInt value = iSlider->Value();
    HBufC* buf = CAknSlider::CreateValueTextInHBufCL( value, R_TESTSLIDER_SLIDER);
    STIF_ASSERT_NOT_NULL( buf );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderCountComponentControlsL, "In TestSliderCountComponentControlsL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderCountComponentControlsL );
    // Print to log file
    iLog->Log( KTestSliderCountComponentControlsL );
    CTestAknSlider* slider = new (ELeave) CTestAknSlider;
    TResourceReader reader;

    TInt value = 0;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSLIDER_SLIDER);
    CCoeControl* parent = new ( ELeave ) CCoeControl();
    CleanupStack::PushL(parent);
    slider->ConstructFromResourceL( parent, value, reader );
    TInt componentControls = slider->CountComponentControls();
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderComponentControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderComponentControlL, "In TestSliderComponentControlL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderComponentControlL );
    // Print to log file
    iLog->Log( KTestSliderComponentControlL );
    CTestAknSlider* slider = new (ELeave) CTestAknSlider;
    TResourceReader reader;

    TInt value = 0;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSLIDER_SLIDER);
    CCoeControl* parent = new ( ELeave ) CCoeControl();
    CleanupStack::PushL(parent);
    slider->ConstructFromResourceL( parent, value, reader );
    TInt cindex = 0;
    CCoeControl* control = slider->ComponentControl( cindex );
    CleanupStack::PopAndDestroy( 2 );
    STIF_ASSERT_NOT_NULL( control );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderHandlePointerEventL, "In TestSliderHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestSliderHandlePointerEventL );

    TPointerEvent event;

    event.iType = TPointerEvent::EButton1Down;

    event.iModifiers = 0;

    TPoint eventPos( 10, 30);

    event.iPosition = eventPos;

    event.iParentPosition = eventPos;

    TBool err = KErrNone;

    TRAP( err, iSlider->HandlePointerEventL( event ) );


    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderSetValueTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderSetValueTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderSetValueTextL, "In TestSliderSetValueTextL" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderSetValueTextL );
    // Print to log file
    iLog->Log( KTestSliderSetValueTextL );

    CTestAknSlider* slider = new (ELeave) CTestAknSlider;
    TResourceReader reader;

    TInt value = 0;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSLIDER_SLIDER);
    CCoeControl* parent = new ( ELeave ) CCoeControl();
    CleanupStack::PushL(parent);
    slider->ConstructFromResourceL( parent, value, reader );
    TBool err = KErrNone;
    TRAP( err, slider->SetValueTextL() );
    CleanupStack::PopAndDestroy( 2 );
 
    return err;
    

    }
// -----------------------------------------------------------------------------
// CTestSDKSlider::TestSliderFocusChanged
// -----------------------------------------------------------------------------
//
TInt CTestSDKSlider::TestSliderFocusChanged( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkslider, "testsdkslider" );
    _LIT( KTestSliderFocusChanged, "In TestSliderFocusChanged" );
    TestModuleIf().Printf( 0, Ktestsdkslider, KTestSliderFocusChanged );
    // Print to log file
    iLog->Log( KTestSliderFocusChanged );

    iSlider->FocusChanged( ENoDrawNow );

    return KErrNone;
    

    }
//  [End of File]
