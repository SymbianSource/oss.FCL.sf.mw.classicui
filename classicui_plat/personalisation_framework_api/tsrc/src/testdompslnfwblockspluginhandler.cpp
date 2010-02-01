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
* Description:  Test pslnfwpluginhandler.h
 *
*/


// [INCLUDE FILES]
#include <pslnfwpluginhandler.h>
#include "testdompslnframework.h"

const TInt KPluginUid = 0x101F84A5;

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWPHNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWPHNewL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWPHNewL, "In TestPlsnFWPHNewL" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWPHNewL );
    // Print to log file
    iLog->Log( KTestPlsnFWPHNewL );

    CAknViewAppUi* appui  = static_cast<CAknViewAppUi*>( CEikonEnv::Static()->AppUi() );
    iFWPHandler = CPslnFWPluginHandler::NewL( appui );
    STIF_ASSERT_NOT_NULL( iFWPHandler );

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWPHNewLWithArray
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWPHNewLWithArrayL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWPHNewLWithArray, "In TestPlsnFWPHNewLWithArray" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWPHNewLWithArray );
    // Print to log file
    iLog->Log( KTestPlsnFWPHNewLWithArray );

    CArrayPtrFlat<CPslnFWPluginInterface>* array = 
        new ( ELeave ) CArrayPtrFlat<CPslnFWPluginInterface>( 1 );
    CleanupStack::PushL( array );

    CAknViewAppUi* appui  = static_cast<CAknViewAppUi*>( CEikonEnv::Static()->AppUi() );

    iFWPHandler = CPslnFWPluginHandler::NewL( appui, array );
    STIF_ASSERT_NOT_NULL( iFWPHandler );
    CleanupStack::Pop( array );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWPHDelete
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWPHDelete( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWPHDelete, "In TestPlsnFWPHDelete" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWPHDelete );
    // Print to log file
    iLog->Log( KTestPlsnFWPHDelete );

    delete iFWPHandler;
    iFWPHandler = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWPHLoadPluginsLWithArray
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWPHLoadPluginsLWithArrayL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWPHLoadPluginsLWithArray, "In TestPlsnFWPHLoadPluginsLWithArray" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWPHLoadPluginsLWithArray );
    // Print to log file
    iLog->Log( KTestPlsnFWPHLoadPluginsLWithArray );

    CArrayPtrFlat<CPslnFWPluginInterface>* array = 
        new ( ELeave ) CArrayPtrFlat<CPslnFWPluginInterface>( 1 );
    CleanupStack::PushL( array );
    
    TRAP_IGNORE( iFWPHandler->LoadPluginsL( array ) );
    CleanupStack::Pop( array );

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWPHLoadPluginsLWithId
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWPHLoadPluginsLWithId( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWPHLoadPluginsLWithId, "In TestPlsnFWPHLoadPluginsLWithId" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWPHLoadPluginsLWithId );
    // Print to log file
    iLog->Log( KTestPlsnFWPHLoadPluginsLWithId );

    TInt err;
    TRAP(err, iFWPHandler->LoadPluginL( TUid::Uid( KPluginUid ) ) );

    return err;

    }
