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
* Description:  Test akndialog.h
*
*/

//INCLUDE
#include <avkon.rsg>
#include <akndialog.h>
#include <eikmenup.h> 
#include <testsdkqueries.rsg>
#include <avkon.hrh>
#include <eikdialg.h>
#include <aknscontrolcontext.h> 
#include <coemop.h>
#include <aknqueryvalue.h>

#include "testsdkqueries.h"
#include "testsdkakndialgprotected.h"
#include "testsdkqueriesview.h"
#include "testsdkqueriescontainer.h"

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgCAknDialog
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgCAknDialogL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgCAknDialog, "In TestDlgCAknDialog" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgCAknDialog );
    // Print to log file
    iLog->Log( KTestDlgCAknDialog );
    
    TInt err = KErrNone;
    
    iDialog = new (ELeave) CAknDialog();

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgConstructL, "In TestDlgConstructL" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgConstructL );
    // Print to log file
    iLog->Log( KTestDlgConstructL );
    
    TInt err = KErrNone;
    
    TRAP( err, iDialog->ConstructL( R_AVKON_MENUPANE_EXIT ) );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgDelete( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgDelete, "In TestDlgDelete" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgDelete );
    // Print to log file
    iLog->Log( KTestDlgDelete );
    
    TInt err = KErrNone;
    
    delete iDialog;
    iDialog = NULL;
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgExecuteLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgExecuteLD( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgExecuteLD, "In TestDlgExecuteLD" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgExecuteLD );
    // Print to log file
    iLog->Log( KTestDlgExecuteLD );
    
    TInt err = KErrNone;
    
    TRAP( err, iDialog->ExecuteLD( R_AVKON_DIALOG_QUERY_VALUE_NUMBER ) );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgPrepareLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgPrepareLC( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgPrepareLC, "In TestDlgPrepareLC" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgPrepareLC );
    // Print to log file
    iLog->Log( KTestDlgPrepareLC );
    
    TInt err = KErrNone;
    
    iDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
        
    CleanupStack::PopAndDestroy( iDialog );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgRunLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgRunLD( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgRunLD, "In TestDlgRunLD" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgRunLD );
    // Print to log file
    iLog->Log( KTestDlgRunLD );
    
    TInt err = KErrNone;
    
    iDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    iDialog->RunLD();       
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgSetEmphasis
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgSetEmphasisL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgSetEmphasis, "In TestDlgSetEmphasis" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgSetEmphasis );
    // Print to log file
    iLog->Log( KTestDlgSetEmphasis );
    
    TInt err = KErrNone;
    
    CCoeControl* menuControl = new (ELeave) CCoeControl();
    
    iDialog->SetEmphasis( menuControl, ETrue );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgDynInitMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgDynInitMenuPaneL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgDynInitMenuPaneL, "In TestDlgDynInitMenuPaneL" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgDynInitMenuPaneL );
    // Print to log file
    iLog->Log( KTestDlgDynInitMenuPaneL );
    
    TInt err = KErrNone;

    iDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    
    CEikMenuPane* menuPane = new( ELeave ) CEikMenuPane( iDialog );
    CleanupStack::PushL( menuPane );  
        
    iDialog->DynInitMenuPaneL( R_TESTQUERY_LISTQUERY_MENU, menuPane );
       
    CleanupStack::PopAndDestroy( menuPane );
    CleanupStack::PopAndDestroy( iDialog );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgProcessCommandL, "In TestDlgProcessCommandL" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgProcessCommandL );
    // Print to log file
    iLog->Log( KTestDlgProcessCommandL );
    
    TInt err = KErrNone;

    iDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    
    TRAP( err, iDialog->ProcessCommandL( 0 ) );
    
    CleanupStack::PopAndDestroy( iDialog );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgOfferKeyEventL, "In TestDlgOfferKeyEventL" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestDlgOfferKeyEventL );
    
    TInt err = KErrNone;

    iDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyEscape;
    TEventCode type = EEventKey;
    
    TRAP( err, iDialog->OfferKeyEventL( keyEvent, type ) );

    CleanupStack::PopAndDestroy( iDialog );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgFocusChanged
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgFocusChanged, "In TestDlgFocusChanged" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgFocusChanged );
    // Print to log file
    iLog->Log( KTestDlgFocusChanged );
    
    TInt err = KErrNone;

    iDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    
    TDrawNow drawNow = EDrawNow;
    iDialog->FocusChanged( drawNow );

    CleanupStack::PopAndDestroy( iDialog );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgHandlePointerEventL, "In TestDlgHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestDlgHandlePointerEventL );
    
    TInt err = KErrNone;

    iDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    TRAP( err, iDialog->HandlePointerEventL( event ) );

    CleanupStack::PopAndDestroy( iDialog );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgOkToExitL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgOkToExitL, "In TestDlgOkToExitL" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgOkToExitL );
    // Print to log file
    iLog->Log( KTestDlgOkToExitL );
    
    TInt err = KErrNone;
    
    iTestDialog = new (ELeave) CTestSDKQueriesDialg();

    iTestDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );
    
    TInt buttonId = EAknSoftkeyMark;
    TRAP( err, iTestDialog->OkToExitL( buttonId ) );

    CleanupStack::PopAndDestroy( iTestDialog );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgDisplayMenuL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgDisplayMenuL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgDisplayMenuL, "In TestDlgDisplayMenuL" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgDisplayMenuL );
    // Print to log file
    iLog->Log( KTestDlgDisplayMenuL );
    
    TInt err = KErrNone;
    
    iTestDialog = new (ELeave) CTestSDKQueriesDialg();

    iTestDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER );

    TRAP( err, iTestDialog->DisplayMenuL() );

    CleanupStack::PopAndDestroy( iTestDialog );    
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgHideMenu
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgHideMenuL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgHideMenu, "In TestDlgHideMenu" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgHideMenu );
    // Print to log file
    iLog->Log( KTestDlgHideMenu );
    
    TInt err = KErrNone;

    
    iTestDialog = new (ELeave) CTestSDKQueriesDialg();

    iTestDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER ); 
    
    iTestDialog->HideMenu();

    CleanupStack::PopAndDestroy( iTestDialog );   
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgMenuShowing
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgMenuShowingL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgMenuShowing, "In TestDlgMenuShowing" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgMenuShowing );
    // Print to log file
    iLog->Log( KTestDlgMenuShowing );
    
    TInt err = KErrNone;
    
    iTestDialog = new (ELeave) CTestSDKQueriesDialg();

    iTestDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER ); 
    
    iTestDialog->MenuShowing();

    CleanupStack::PopAndDestroy( iTestDialog );   
        
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgSizeChanged
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgSizeChanged, "In TestDlgSizeChanged" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgSizeChanged );
    // Print to log file
    iLog->Log( KTestDlgSizeChanged );
    
    TInt err = KErrNone;
    
    iTestDialog = new (ELeave) CTestSDKQueriesDialg();

    iTestDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER ); 
    
    iTestDialog->SizeChanged();

    CleanupStack::PopAndDestroy( iTestDialog );   
        
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgDraw
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgDraw, "In TestDlgDraw" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgDraw );
    // Print to log file
    iLog->Log( KTestDlgDraw );
    
    TInt err = KErrNone;
    
    iTestDialog = new (ELeave) CTestSDKQueriesDialg();

    iTestDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER ); 
    
    iTestDialog->SetContainerWindowL( *iContainer );
    
    iContainer->ActivateGc();
    TRect rect;
    iTestDialog->Draw( rect );
    iContainer->DeactivateGc();
    
    CleanupStack::PopAndDestroy( iTestDialog );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDlgMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDlgMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdkqueries, "testsdkqueries" );
    _LIT( KTestDlgMopSupplyObject, "In TestDlgMopSupplyObject" );
    TestModuleIf().Printf( 0, Ktestsdkqueries, KTestDlgMopSupplyObject );
    // Print to log file
    iLog->Log( KTestDlgMopSupplyObject );
    
    TInt err = KErrNone;    
    
    iTestDialog = new (ELeave) CTestSDKQueriesDialg();

    iTestDialog->PrepareLC( R_AVKON_DIALOG_QUERY_VALUE_NUMBER ); 

    TTypeUid uid( MAknsControlContext::ETypeId );
    iTestDialog->MopSupplyObject( uid );

    CleanupStack::PopAndDestroy( iTestDialog );           
    
    return err;
    }

//End file



