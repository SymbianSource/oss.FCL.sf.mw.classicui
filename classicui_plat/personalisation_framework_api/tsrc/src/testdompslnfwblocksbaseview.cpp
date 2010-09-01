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
* Description:  Test PslnFWBaseView.h
 *
*/


// [INCLUDE FILES]
#include <aknnavi.h>
#include <aknform.h>
#include <aknnavide.h>
#include <testdompslnframework.rsg>
#include <avkon.hrh>
#include <psln.hrh>
#include <stifparser.h>

#include "testdompslnfwbv.h"
#include "testdompslnframework.h"
#include "testdompslnfwappui.h"

_LIT( KFileName, "testdompslnframework.rsc" );
_LIT8( KMessage, "test message");

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVCPslnFWBaseView
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVCPslnFWBaseViewL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVCPslnFWBaseView, "In TestPlsnFWBVCPslnFWBaseView" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVCPslnFWBaseView );
    // Print to log file
    iLog->Log( KTestPlsnFWBVCPslnFWBaseView );

    iFWBView = new ( ELeave ) CTestPslnFWBaseView();
    STIF_ASSERT_NOT_NULL( iFWBView );

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVConstructL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVConstructL, "In TestPlsnFWBVConstructL" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVConstructL );
    // Print to log file
    iLog->Log( KTestPlsnFWBVConstructL );

    TInt err = KErrNone;
    TRAP( err, iFWBView->ConstructL() );
    return err;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVDelete
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVDelete( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVDelete, "In TestPlsnFWBVDelete" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVDelete );
    // Print to log file
    iLog->Log( KTestPlsnFWBVDelete );

    delete iFWBView;
    iFWBView=NULL;

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVSetCurrentItem
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVSetCurrentItem( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVSetCurrentItem, "In TestPlsnFWBVSetCurrentItem" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVSetCurrentItem );
    // Print to log file
    iLog->Log( KTestPlsnFWBVSetCurrentItem );

    TInt flag;
    TInt err = aItem.GetNextInt( flag );
    if( err != KErrNone)
        return err;
    switch ( flag )
        {
        case 1:
            iFWBView->SetCurrentItem( 0 );
            break;
        case 2:
            iFWBView->SetCurrentItem( 1 );
        default:
            break;
        }

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVContainer
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVContainer( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVContainer, "In TestPlsnFWBVContainer" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVContainer );
    // Print to log file
    iLog->Log( KTestPlsnFWBVContainer );

    iFWBView->Container();

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVOpenLocalizedResourceFileL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVOpenLocalizedResourceFileL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVOpenLocalizedResourceFileLw, "In TestPlsnFWBVOpenLocalizedResourceFileL" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVOpenLocalizedResourceFileLw );
    // Print to log file
    iLog->Log( KTestPlsnFWBVOpenLocalizedResourceFileLw );

    RConeResourceLoader loader( *CCoeEnv::Static() );
    
    TRAPD( err, iFWBView->OpenLocalizedResourceFileL( KFilePath, loader ) );

    return err;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVOpenLocalizedResourceFileLWithPathL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVOpenLocalizedResourceFileLWithPathL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVOpenLocalizedResourceFileLWithPathL, "In TestPlsnFWBVOpenLocalizedResourceFileLWithPathL" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVOpenLocalizedResourceFileLWithPathL );
    // Print to log file
    iLog->Log( KTestPlsnFWBVOpenLocalizedResourceFileLWithPathL );

    RConeResourceLoader loader( *CCoeEnv::Static() );
    
    TInt err = KErrNone;
    TRAP( err, iFWBView->OpenLocalizedResourceFileL( KFileName, loader, &KFileDir ) );

    return err;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVSetNaviPaneDecorator
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVSetNaviPaneDecoratorL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVSetNaviPaneDecorator, "In TestPlsnFWBVSetNaviPaneDecorator" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVSetNaviPaneDecorator );
    // Print to log file
    iLog->Log( KTestPlsnFWBVSetNaviPaneDecorator );

    CAknAppUi* appui = static_cast<CAknAppUi*>( CCoeEnv::Static()->AppUi() );
    CEikStatusPane* pane = appui->StatusPane ();
    CAknNavigationControlContainer* ncContainer =static_cast<CAknNavigationControlContainer*>(
        pane->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) ) );
    
    CAknForm* frm = new( ELeave ) CAknForm();
    CleanupStack::PushL( frm );
    frm->ConstructL();

    CAknNavigationDecorator* decorate = CAknNavigationDecorator::NewL( ncContainer, frm );
    CleanupStack::PushL( decorate );
    
    iFWBView->SetNaviPaneDecorator( decorate );
    
    CleanupStack::Pop( decorate );
    CleanupStack::Pop( frm );

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVDoActivateL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVDoActivateL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVDoActivateL, "In TestPlsnFWBVDoActivateL" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVDoActivateL );
    // Print to log file
    iLog->Log( KTestPlsnFWBVDoActivateL );

    TVwsViewId viewid;
    TInt err = KErrNone;
    TRAP( err, iFWBView->DoActivateL( viewid, KNullUid, KMessage ) );

    return err;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVDoDeactivate
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVDoDeactivateL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVDoDeactivate, "In TestPlsnFWBVDoDeactivate" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVDoDeactivate );
    // Print to log file
    iLog->Log( KTestPlsnFWBVDoDeactivate );

    //instantiating class CPslnFWBaseContainerExt ->iContainer
    iFWBView->ConstructL();

    iFWBView->DoDeactivate();

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVSetTabIndex
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVSetTabIndex( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVSetTabIndex, "In TestPlsnFWBVSetTabIndex" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVSetTabIndex );
    // Print to log file
    iLog->Log( KTestPlsnFWBVSetTabIndex );

    iFWBView->SetTabIndex( 0 );

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVGetTabIndex
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVGetTabIndex( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVGetTabIndex, "In TestPlsnFWBVGetTabIndex" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVGetTabIndex );
    // Print to log file
    iLog->Log( KTestPlsnFWBVGetTabIndex );

    TInt myTabIndex = 0;
    myTabIndex = iFWBView->GetTabIndex();
    TInt expected = -1;
    STIF_ASSERT_EQUALS( expected, myTabIndex );
    return KErrNone;
    }

// ========================test for the protected methods =======================

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVSetNaviPaneL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVSetNaviPaneL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVGetTabIndex, "In TestPlsnFWBVGetTabIndex" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVGetTabIndex );
    // Print to log file
    iLog->Log( KTestPlsnFWBVGetTabIndex );

    TInt err = KErrNone;
    TRAP( err, iFWBView->SetNaviPaneL() );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVCreateNaviPaneContextL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVCreateNaviPaneContextL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVGetTabIndex, "In TestPlsnFWBVGetTabIndex" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVGetTabIndex );
    // Print to log file
    iLog->Log( KTestPlsnFWBVGetTabIndex );

    TInt err = KErrNone;
    TRAP( err, iFWBView->CreateNaviPaneContextL( 0 ) );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVCreateContainerL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVCreateContainerL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVGetTabIndex, "In TestPlsnFWBVGetTabIndex" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVGetTabIndex );
    // Print to log file
    iLog->Log( KTestPlsnFWBVGetTabIndex );

    TInt err = KErrNone;
    TRAP( err, iFWBView->CreateContainerL() );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVNewContainerL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVNewContainerL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVGetTabIndex, "In TestPlsnFWBVGetTabIndex" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVGetTabIndex );
    // Print to log file
    iLog->Log( KTestPlsnFWBVGetTabIndex );

    TInt err = KErrNone;
    TRAP( err, iFWBView->NewContainerL() );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVSetNaviPaneLWithTIntL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVSetNaviPaneLWithTIntL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVGetTabIndex, "In TestPlsnFWBVGetTabIndex" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVGetTabIndex );
    // Print to log file
    iLog->Log( KTestPlsnFWBVGetTabIndex );

    TInt err = KErrNone;
    TRAP( err, iFWBView->SetNaviPaneL( 0 ) );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVSetMiddleSoftKeyLabelL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVSetMiddleSoftKeyLabelL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVGetTabIndex, "In TestPlsnFWBVGetTabIndex" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVGetTabIndex );
    // Print to log file
    iLog->Log( KTestPlsnFWBVGetTabIndex );

    TInt err = KErrNone;
    TRAP( err, iFWBView->SetMiddleSoftKeyLabelL( R_TESTPSLN_LABEL, 0 ) );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVHandleCommandL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVHandleCommandL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVGetTabIndex, "In TestPlsnFWBVGetTabIndex" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVGetTabIndex );
    // Print to log file
    iLog->Log( KTestPlsnFWBVGetTabIndex );
    
    CCoeAppUi* oldAppUi = new( ELeave ) CCoeAppUi();
    CTestDOMPslnFWAppUi* appUi = new( ELeave ) CTestDOMPslnFWAppUi();
    TInt err = KErrNone;
    oldAppUi = CCoeEnv::Static()->SetAppUi( appUi ); 
    if (iFWBView)
    {
    delete iFWBView;
    iFWBView = NULL;
    }
    iFWBView = new ( ELeave ) CTestPslnFWBaseView();
    TRAP( err, iFWBView->HandleCommandL( 0 ) );
    
    CCoeEnv::Static()->SetAppUi( oldAppUi );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::TestPlsnFWBVSetTitlePaneL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPSLNFramework::TestPlsnFWBVSetTitlePaneL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( Ktestdompslnframework, "testdompslnframework" );
    _LIT( KTestPlsnFWBVGetTabIndex, "In TestPlsnFWBVGetTabIndex" );
    TestModuleIf().Printf( 0, Ktestdompslnframework, KTestPlsnFWBVGetTabIndex );
    // Print to log file
    iLog->Log( KTestPlsnFWBVGetTabIndex );

    TInt resouceId = R_TESTPSLN_TITLE_RESOURCE;
    TInt err = KErrNone;
    TRAP( err, iFWBView->SetTitlePaneL( resouceId ) );

    return err;
    }
