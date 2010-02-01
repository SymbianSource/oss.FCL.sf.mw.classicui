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
* Description:  test functions for testing aknAnimView.h
 *
*/


// [INCLUDE FILES]
#include <eikclb.h>
#include <aknlists.h>

#include "testdomextanimation.h"
#include "testdomextanimationcontainer.h"

// CONSTANTS
const TInt KContainerRectStartPointX = 0;
const TInt KContainerRectStartPointY = 0;
const TInt KContainerRectWidth = 100;
const TInt KContainerRectHeight = 100;


// FORWARD DECLARATION
class CTestAnimatedView: public CAknAnimatedView
    {
public:
    // CTestAnimatedView::CTestAnimatedView
    CTestAnimatedView(): CAknAnimatedView()
        {
        iViewUid.iUid = TUid::Null().iUid;
        }
    
    // CTestAnimatedView::AknViewActivatedL
    void AknViewActivatedL( const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId, const TDesC8& aCustomMessage )
        {
        CAknAnimatedView::AknViewActivatedL( aPrevViewId, aCustomMessageId, aCustomMessage );
        }
    
    // CTestAnimatedView::PreAnimateSetup
    void PreAnimateSetup()
        {
        CAknAnimatedView::PreAnimateSetup();
        }
    
    // CTestAnimatedView::PostAnimateSetup
    void PostAnimateSetup()
        {
        CAknAnimatedView::PostAnimateSetup();
        }
    
    //CTestAnimatedView::Id
    TUid Id() const { return iViewUid; }
    
    //CTestAnimatedView::DoActivateL
    void DoActivateL( const TVwsViewId& /*aPrevViewId*/,
            TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/ )
        {
        }
    
    //CTestAnimatedView::DoDeactivate
    void DoDeactivate() {}
    
private:
    
    //ViewUid
    TUid iViewUid;
    
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimViewCAknAnimatedViewL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimViewCAknAnimatedViewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimViewCAknAnimatedViewL, "In TestCAknAnimViewCAknAnimatedViewL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimViewCAknAnimatedViewL );
    // Print to log file
    iLog->Log( KTestCAknAnimViewCAknAnimatedViewL );
    
    CTestAnimatedView* animview = new ( ELeave ) CTestAnimatedView();
    CleanupStack::PushL( animview );
    
    STIF_ASSERT_NOT_NULL( animview );
    
    CleanupStack::PopAndDestroy( animview );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimViewSetAnimationDataL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimViewSetAnimationDataL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimViewSetAnimationDataL, "In TestCAknAnimViewSetAnimationDataL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimViewSetAnimationDataL );
    // Print to log file
    iLog->Log( KTestCAknAnimViewSetAnimationDataL );
    
    CTestAnimatedView* animview = new ( ELeave ) CTestAnimatedView();
    CleanupStack::PushL( animview );
    
    CAknAnimationData* animdata = new ( ELeave ) CAknAnimationData();
    CleanupStack::PushL( animdata );
    
    animview->SetAnimationData( animdata );
    
    CleanupStack::PopAndDestroy( animdata );
    CleanupStack::PopAndDestroy( animview );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimViewAknViewActivatedL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimViewAknViewActivatedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimViewAknViewActivatedL, "In TestCAknAnimViewAknViewActivatedL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimViewAknViewActivatedL );
    // Print to log file
    iLog->Log( KTestCAknAnimViewAknViewActivatedL );
    
    CTestAnimatedView* animview = new ( ELeave ) CTestAnimatedView();
    CleanupStack::PushL( animview );
    animview->BaseConstructL();
    
    TVwsViewId prevViewId( TUid::Uid( 1 ), TUid::Uid( 1 ) );
    _LIT8( KCustomMessage, "test" );
    animview->AknViewActivatedL( prevViewId, TUid::Null(), KCustomMessage );
    
    CleanupStack::PopAndDestroy( animview );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimViewPreAnimateSetupL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimViewPreAnimateSetupL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimViewPreAnimateSetupL, "In TestCAknAnimViewPreAnimateSetupL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimViewPreAnimateSetupL );
    // Print to log file
    iLog->Log( KTestCAknAnimViewPreAnimateSetupL );
    
    CTestAnimatedView* testanimview = new ( ELeave ) CTestAnimatedView;
    CleanupStack::PushL( testanimview );
    
    testanimview->PreAnimateSetup();
    
    CleanupStack::PopAndDestroy( testanimview );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimViewPostAnimateSetupL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimViewPostAnimateSetupL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimViewPostAnimateSetupL, "In TestCAknAnimViewPostAnimateSetupL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimViewPostAnimateSetupL );
    // Print to log file
    iLog->Log( KTestCAknAnimViewPostAnimateSetupL );
    
    CTestAnimatedView* testanimview = new ( ELeave ) CTestAnimatedView;
    CleanupStack::PushL( testanimview );
    
    testanimview->PostAnimateSetup();
    
    CleanupStack::PopAndDestroy( testanimview );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::TestCAknAnimViewSwapListBoxGcL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::TestCAknAnimViewSwapListBoxGcL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtAnimation, "TestDomExtAnimation" );
    _LIT( KTestCAknAnimViewSwapListBoxGcL, "In TestCAknAnimViewSwapListBoxGcL" );
    TestModuleIf().Printf( 0, KTestDomExtAnimation, KTestCAknAnimViewSwapListBoxGcL );
    // Print to log file
    iLog->Log( KTestCAknAnimViewSwapListBoxGcL );
    
    CTestAnimatedView* animview = new ( ELeave ) CTestAnimatedView();
    CleanupStack::PushL( animview );
    
    CWindowGc& windowGc = CCoeEnv::Static()->SystemGc();
    
    CTestDomExtAnimContainer* container = new ( ELeave ) CTestDomExtAnimContainer;
    CleanupStack::PushL( container );
    TRect rect( KContainerRectStartPointX, KContainerRectStartPointY, KContainerRectWidth, KContainerRectHeight );
    container->ConstructL( rect );
    
    CEikColumnListBox* listbox = new ( ELeave ) CAknSingleNumberStyleListBox;
    CleanupStack::PushL( listbox );
    listbox->ConstructL( container );
    
    animview->SwapListBoxGc( listbox, &windowGc );
    
    CleanupStack::PopAndDestroy( listbox );
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( animview );
    
    return KErrNone;
    }


//  [End of File]
