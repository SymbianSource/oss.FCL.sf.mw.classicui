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
* Description:  test aknpointereventmodifier.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknpointereventmodifier.h>
#include <aknappui.h>
#include <coecntrl.h>

#include "testdompoieventmod.h"
#include "testdompoieventmodcontainer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMPoiEventMod::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMPoiEventMod::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestPush", CTestDOMPoiEventMod::TestPushL ),
        ENTRY( "TestPop", CTestDOMPoiEventMod::TestPopL ),
        ENTRY( "TestUpdate", CTestDOMPoiEventMod::TestUpdateL ),
        ENTRY( "TestHandlePointerEvent", CTestDOMPoiEventMod::TestHandlePointerEvent ),
        
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMPoiEventMod::TestPushL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPoiEventMod::TestPushL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdompoieventmod, "testdompoieventmod" );
    _LIT( KTestPush, "In Push" );
    TestModuleIf().Printf( 0, Ktestdompoieventmod, KTestPush );
    // Print to log file
    iLog->Log( KTestPush );

    CAknAppUiBase* appuiBase = static_cast<CAknAppUiBase*>( CEikonEnv::Static()->AppUi() );
    CAknPointerEventModifier* modifier = appuiBase->PointerEventModifier();
    CCoeControl* control = new ( ELeave ) CCoeControl;
    CleanupStack::PushL( control );
    CTestDOMPoiEventModContainer* parent = CTestDOMPoiEventModContainer::NewL();
    CleanupStack::PushL( parent );
    control->SetParent( parent );
    modifier->Push( *control, TRect() );

    modifier->Pop( *control );
    CleanupStack::PopAndDestroy( parent );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPoiEventMod::TestPopL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPoiEventMod::TestPopL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdompoieventmod, "testdompoieventmod" );
    _LIT( KTestPop, "In Pop" );
    TestModuleIf().Printf( 0, Ktestdompoieventmod, KTestPop );
    // Print to log file
    iLog->Log( KTestPop );

    CAknAppUiBase* appuiBase = static_cast<CAknAppUiBase*>( CEikonEnv::Static()->AppUi() );
    CAknPointerEventModifier* modifier = appuiBase->PointerEventModifier();
    CCoeControl* control = new ( ELeave ) CCoeControl;
    CleanupStack::PushL( control );
    CTestDOMPoiEventModContainer* parent = CTestDOMPoiEventModContainer::NewL();
    CleanupStack::PushL( parent );
    control->SetParent( parent );
    modifier->Push( *control, TRect() );

    modifier->Pop( *control );
    CleanupStack::PopAndDestroy( parent );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPoiEventMod::TestUpdateL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPoiEventMod::TestUpdateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdompoieventmod, "testdompoieventmod" );
    _LIT( KTestUpdate, "In Update" );
    TestModuleIf().Printf( 0, Ktestdompoieventmod, KTestUpdate );
    // Print to log file
    iLog->Log( KTestUpdate );

    CAknAppUiBase* appuiBase = static_cast<CAknAppUiBase*>( CEikonEnv::Static()->AppUi() );
    CAknPointerEventModifier* modifier = appuiBase->PointerEventModifier();
    CCoeControl* control = new ( ELeave ) CCoeControl;
    CleanupStack::PushL( control );
    CTestDOMPoiEventModContainer* parent = CTestDOMPoiEventModContainer::NewL();
    CleanupStack::PushL( parent );
    control->SetParent( parent );
    modifier->Push( *control, TRect() );

    modifier->Update( *control, TRect() );

    modifier->Pop( *control );
    CleanupStack::PopAndDestroy( parent );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPoiEventMod::TestHandlePointerEvent
// -----------------------------------------------------------------------------
//
TInt CTestDOMPoiEventMod::TestHandlePointerEvent( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdompoieventmod, "testdompoieventmod" );
    _LIT( KTestUpdate, "In Update" );
    TestModuleIf().Printf( 0, Ktestdompoieventmod, KTestUpdate );
    // Print to log file
    iLog->Log( KTestUpdate );

    CAknAppUiBase* appuiBase = static_cast<CAknAppUiBase*>( CEikonEnv::Static()->AppUi() );
    CAknPointerEventModifier* modifier = appuiBase->PointerEventModifier();
    CCoeControl* control = new ( ELeave ) CCoeControl;
    CleanupStack::PushL( control );
    CTestDOMPoiEventModContainer* parent = CTestDOMPoiEventModContainer::NewL();
    CleanupStack::PushL( parent );
    control->SetParent( parent );
    modifier->Push( *control, TRect() );

    TPointerEvent event;
    modifier->HandlePointerEvent( event, control );

    modifier->Pop( *control );
    CleanupStack::PopAndDestroy( parent );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }
//  [End of File]
