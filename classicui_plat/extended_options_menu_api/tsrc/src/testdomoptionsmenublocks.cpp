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
* Description: This file contains testclass implementation.
*
*/
// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <aknappui.h>
#include <eikmenub.h>
#include <aknenv.h>
#include <eikenv.h>
#include <aknitemactionmenu.h>
#include <testdomoptionsmenu.rsg>
#include "testdomoptionsmenu.h"
#include "testoptionsmenu.h"


// -----------------------------------------------------------------------------
// CTestSDKDomMenu::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestDomOptionsMenu::Delete() 
    {
    delete iCollection;
    delete iEikMenuBarTitle;
    delete iEikMenuBar;
    
    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

// -----------------------------------------------------------------------------
// CTestDomOptionsMenu::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomOptionsMenu::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestIMRegisterCollectionL", CTestDomOptionsMenu::TestIMRegisterCollectionL ),
        ENTRY( "TestIMRemoveCollection", CTestDomOptionsMenu::TestIMRemoveCollection ),
        ENTRY( "TestIMShowMenuL", CTestDomOptionsMenu::TestIMShowMenuL ),
        ENTRY( "TestIMInitMenuL", CTestDomOptionsMenu::TestIMInitMenuL ),
        ENTRY( "TestIMCollectionChangedL", CTestDomOptionsMenu::TestIMCollectionChangedL ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestIMRegisterCollectionL
// -----------------------------------------------------------------------------
//
TInt CTestDomOptionsMenu::TestIMRegisterCollectionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKDomMenu, "TestSDKDomMenu" );
    _LIT( KTestIMRegisterCollectionL, "In TestIMRegisterCollectionL" );
    TestModuleIf().Printf( 0, KTestSDKDomMenu, KTestIMRegisterCollectionL );
    // Print to log file
    iLog->Log( KTestIMRegisterCollectionL );

    if( !iCollection )
    	{
    	iCollection = new(ELeave) TTestCollection;
    	}
    
    //since STIF does not enable single click now, can't get instance of CAknItemActionMenu. 
    //Hence following method will not be invoked.
    CAknItemActionMenu::RegisterCollectionL( *iCollection );    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestIMRemoveCollection
// -----------------------------------------------------------------------------
//
TInt CTestDomOptionsMenu::TestIMRemoveCollection( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKDomMenu, "TestSDKDomMenu" );
    _LIT( KTestIMRemoveCollection, "In TestIMRemoveCollection" );
    TestModuleIf().Printf( 0, KTestSDKDomMenu, KTestIMRemoveCollection );
    // Print to log file
    iLog->Log( KTestIMRemoveCollection );

    if( !iCollection )
    	{
    	iCollection = new(ELeave) TTestCollection;
    	}
    CEikMenuBar* old = CEikonEnv::Static()->AppUiFactory()->SwapMenuBar( iEikMenuBar );
    CAknItemActionMenu* menu = CAknItemActionMenu::RegisterCollectionL( *iCollection );
    if ( menu )
    	{
    	menu->RemoveCollection( *iCollection );
    	}
    CEikonEnv::Static()->AppUiFactory()->SwapMenuBar( old );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestIMShowMenuL
// -----------------------------------------------------------------------------
//
TInt CTestDomOptionsMenu::TestIMShowMenuL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKDomMenu, "TestSDKDomMenu" );
    _LIT( KTestIMShowMenuL, "In TestIMShowMenuL" );
    TestModuleIf().Printf( 0, KTestSDKDomMenu, KTestIMShowMenuL );
    // Print to log file
    iLog->Log( KTestIMShowMenuL );
    CEikMenuBar* old = CEikonEnv::Static()->AppUiFactory()->SwapMenuBar( iEikMenuBar );
    CAknItemActionMenu* menu = CAknItemActionMenu::RegisterCollectionL( *iCollection );
    if ( menu )
    	{
    	menu->InitMenuL();
    	menu->ShowMenuL( TPoint(0, 0) );
    	}
    CEikonEnv::Static()->AppUiFactory()->SwapMenuBar( old );
    return KErrNone;
 
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::TestIMInitMenuL
// -----------------------------------------------------------------------------
//
TInt CTestDomOptionsMenu::TestIMInitMenuL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKDomMenu, "TestSDKDomMenu" );
    _LIT( KTestIMInitMenuL, "In TestIMInitMenuL" );
    TestModuleIf().Printf( 0, KTestSDKDomMenu, KTestIMInitMenuL );
    // Print to log file
    iLog->Log( KTestIMInitMenuL );

    if( !iCollection )
    	{
    	iCollection = new(ELeave) TTestCollection;
    	}
    CEikMenuBar* old = CEikonEnv::Static()->AppUiFactory()->SwapMenuBar( iEikMenuBar );
    CAknItemActionMenu* menu = CAknItemActionMenu::RegisterCollectionL( *iCollection );
    if ( menu )
    	{
    	menu->InitMenuL();    	
    	}
    CEikonEnv::Static()->AppUiFactory()->SwapMenuBar( old );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomOptionsMenu::TestIMCollectionChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDomOptionsMenu::TestIMCollectionChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKDomMenu, "TestSDKDomMenu" );
    _LIT( KTestIMCollectionChangedL, "In TestIMCollectionChangedL" );
    TestModuleIf().Printf( 0, KTestSDKDomMenu, KTestIMCollectionChangedL );
    // Print to log file
    iLog->Log( KTestIMCollectionChangedL );

    if ( !iCollection )
    	{
    	iCollection = new (ELeave) TTestCollection;
    	}

    CEikMenuBar* old = CEikonEnv::Static()->AppUiFactory()->SwapMenuBar( iEikMenuBar );
    CAknItemActionMenu* menu = CAknItemActionMenu::RegisterCollectionL( *iCollection );
    if ( menu )
    	{
    	iEikMenuBar->TryDisplayMenuBarL();
        menu->CollectionChanged( *iCollection );
        iEikMenuBar->StopDisplayingMenuBar();
    	}
    	
    CEikonEnv::Static()->AppUiFactory()->SwapMenuBar( old );
    
    return KErrNone;
    }

//  [End of File] - Do not remove
