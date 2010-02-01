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
* Description:  Test aknnavide.h
 *
*/


// [INCLUDE FILES]
#include <aknnavide.h>
#include <akndef.h>

#include "testsdknavipane.h"
#include "testsdknavipanenavideext.h"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestNaviDeNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeNewL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeNewL, "In TestNaviDeNewL" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeNewL );
    // Print to log file
    iLog->Log( KTestNaviDeNewL );

    if ( iNaviContainerDe != NULL )
        {
        delete iNaviContainerDe;
        iNaviContainerDe = NULL;
        }
    
    iNaviContainerDe = new (ELeave) CAknNavigationDecorator;
    STIF_ASSERT_NOT_NULL( iNaviContainerDe );

    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestNaviDeDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeDelete(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeDelete, "In TestNaviDeDelete" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeDelete );
    // Print to log file
    iLog->Log( KTestNaviDeDelete );
  
    delete iNaviContainerDe;
    iNaviContainerDe = NULL;
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeDecoratedControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeDecoratedControlL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeDecoratedControl, "In TestNaviDeDecoratedControl" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeDecoratedControl );
    // Print to log file
    iLog->Log( KTestNaviDeDecoratedControl );
  
    if ( iNaviContainerDe != NULL )
        {
        delete iNaviContainerDe;
        iNaviContainerDe = NULL;
        }
    
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
    
    CCoeControl* control = iNaviContainerDe->DecoratedControl();

    STIF_ASSERT_NOT_NULL( control );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeMakeScrollButtonVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeMakeScrollButtonVisibleL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeMakeScrollButtonVisible, "In TestNaviDeMakeScrollButtonVisible" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeMakeScrollButtonVisible );
    // Print to log file
    iLog->Log( KTestNaviDeMakeScrollButtonVisible );
  
    TInt err = KErrNone;
    
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
    
    TRAP( err, iNaviContainerDe->MakeScrollButtonVisible( ETrue ) );

    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeScrollButtonVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeScrollButtonVisibleL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeScrollButtonVisible, "In TestNaviDeScrollButtonVisible" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeScrollButtonVisible );
    // Print to log file
    iLog->Log( KTestNaviDeScrollButtonVisible );
  
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
    iNaviContainerDe->MakeScrollButtonVisible( ETrue );
    
    TBool isVisible = iNaviContainerDe->ScrollButtonVisible();
    
    STIF_ASSERT_TRUE( isVisible );


    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeSetScrollButtonDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeSetScrollButtonDimmedL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeSetScrollButtonDimmed, "In TestNaviDeSetScrollButtonDimmed" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeSetScrollButtonDimmed );
    // Print to log file
    iLog->Log( KTestNaviDeSetScrollButtonDimmed );
  
    TInt err = KErrNone;
    
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
    
    TRAP( err, iNaviContainerDe->SetScrollButtonDimmed( 
        CAknNavigationDecorator::ELeftButton, ETrue ) );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeIsScrollButtonDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeIsScrollButtonDimmedL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeIsScrollButtonDimmed, "In TestNaviDeIsScrollButtonDimmed" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeIsScrollButtonDimmed );
    // Print to log file
    iLog->Log( KTestNaviDeIsScrollButtonDimmed );
  
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
    
    iNaviContainerDe->SetScrollButtonDimmed( 
        CAknNavigationDecorator::ELeftButton, ETrue );

    TBool isDimmed = iNaviContainerDe->IsScrollButtonDimmed( 
        CAknNavigationDecorator::ELeftButton );
    
    STIF_ASSERT_TRUE( isDimmed );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeSetControlTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeSetControlTypeL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeSetControlType, "In TestNaviDeSetControlType" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeSetControlType );
    // Print to log file
    iLog->Log( KTestNaviDeSetControlType );
  
    TInt err = KErrNone;

    
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
    
    TRAP( err, iNaviContainerDe->SetControlType( 
        CAknNavigationDecorator::ETabGroup ) );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeControlTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeControlTypeL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeControlType, "In TestNaviDeControlType" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeControlType );
    // Print to log file
    iLog->Log( KTestNaviDeControlType );
      
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
    
    iNaviContainerDe->SetControlType( CAknNavigationDecorator::ETabGroup );
    
    CAknNavigationDecorator::TControlType controlType = 
        iNaviContainerDe->ControlType();
    
    STIF_ASSERT_EQUALS( controlType, CAknNavigationDecorator::ETabGroup ); 
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeSetNaviDecoratorObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeSetNaviDecoratorObserverL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeSetNaviDecoratorObserver, "In TestNaviDeSetNaviDecoratorObserver" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeSetNaviDecoratorObserver );
    // Print to log file
    iLog->Log( KTestNaviDeSetNaviDecoratorObserver );
  
    TInt err = KErrNone;
    
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
    CTestSDKNaviDecoratorObserver* deObserver = new (ELeave) 
        CTestSDKNaviDecoratorObserver();
    CleanupStack::PushL( deObserver );
    
    TRAP( err, iNaviContainerDe->SetNaviDecoratorObserver( deObserver ) );
    
    CleanupStack::PopAndDestroy();
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeHandlePointerEventL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeHandlePointerEventL, "In TestNaviDeHandlePointerEventL" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestNaviDeHandlePointerEventL );
  
    TInt err = KErrNone;
    
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
        
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
        
    TRAP( err, iNaviContainerDe->HandlePointerEventL( event ) );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeSetNaviControlLayoutStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeSetNaviControlLayoutStyleL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeSetNaviControlLayoutStyle, "In TestNaviDeSetNaviControlLayoutStyle" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeSetNaviControlLayoutStyle );
    // Print to log file
    iLog->Log( KTestNaviDeSetNaviControlLayoutStyle );
  
    TInt err = KErrNone;
    
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
        
    TRAP( err, iNaviContainerDe->SetNaviControlLayoutStyle( 
        CAknNavigationDecorator::ENaviControlLayoutNormal ) );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeNaviControlLayoutStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeNaviControlLayoutStyleL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeNaviControlLayoutStyle, "In TestNaviDeNaviControlLayoutStyle" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeNaviControlLayoutStyle );
    // Print to log file
    iLog->Log( KTestNaviDeNaviControlLayoutStyle );
  
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
        
    iNaviContainerDe->SetNaviControlLayoutStyle( 
        CAknNavigationDecorator::ENaviControlLayoutNormal );
    
    CAknNavigationDecorator::TAknNaviControlLayoutStyle style = 
        iNaviContainerDe->NaviControlLayoutStyle();
    
    STIF_ASSERT_EQUALS( style, 
        CAknNavigationDecorator::ENaviControlLayoutNormal );

    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeNaviControlLayoutStyleSupportedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeNaviControlLayoutStyleSupportedL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeNaviControlLayoutStyleSupported, "In TestNaviDeNaviControlLayoutStyleSupported" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeNaviControlLayoutStyleSupported );
    // Print to log file
    iLog->Log( KTestNaviDeNaviControlLayoutStyleSupported );
  
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
        
    iNaviContainerDe->SetNaviControlLayoutStyle( 
        CAknNavigationDecorator::ENaviControlLayoutNormal );
    
    TBool isSupport = iNaviContainerDe->NaviControlLayoutStyleSupported( 
        CAknNavigationDecorator::ENaviControlLayoutNormal );
    
    STIF_ASSERT_TRUE( isSupport );


    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeSetNaviControlLayoutModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeSetNaviControlLayoutModeL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeSetNaviControlLayoutMode, "In TestNaviDeSetNaviControlLayoutMode" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeSetNaviControlLayoutMode );
    // Print to log file
    iLog->Log( KTestNaviDeSetNaviControlLayoutMode );
  
    TInt err = KErrNone;
    
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
        
    TRAP( err, iNaviContainerDe->SetNaviControlLayoutMode( 
        CAknNavigationDecorator::ENaviControlLayoutModeAutomatic ) );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeNaviControlLayoutModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeNaviControlLayoutModeL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeNaviControlLayoutMode, "In TestNaviDeNaviControlLayoutMode" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeNaviControlLayoutMode );
    // Print to log file
    iLog->Log( KTestNaviDeNaviControlLayoutMode );
  
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
    
    iNaviContainerDe->SetNaviControlLayoutMode( 
        CAknNavigationDecorator::ENaviControlLayoutModeAutomatic );
    
    CAknNavigationDecorator::TAknNaviControlLayoutMode mode = 
        iNaviContainerDe->NaviControlLayoutMode();
    
    STIF_ASSERT_EQUALS( mode, 
        CAknNavigationDecorator::ENaviControlLayoutModeAutomatic ); 
    
    return KErrNone;

    }



// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeHandleResourceChangeL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeHandleResourceChange, "In TestNaviDeHandleResourceChange" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeHandleResourceChange );
    // Print to log file
    iLog->Log( KTestNaviDeHandleResourceChange );
  
    TInt err = KErrNone;
    
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
    
    TInt type = KEikDynamicLayoutVariantSwitch ;    
    
    TRAP( err, iNaviContainerDe->HandleResourceChange( type ) );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeSizeChangedL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeSizeChanged, "In TestNaviDeSizeChanged" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeSizeChanged );
    // Print to log file
    iLog->Log( KTestNaviDeSizeChanged );
  
    TInt err = KErrNone;
    
    iNaviContainerDeExt = STATIC_CAST( CTestSDKNavipaneNaviDeExt*, 
        iNaviContainer->CreateTabGroupL() );    
    
    TRAP( err, iNaviContainerDeExt->SizeChanged() );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeCountComponentControlsL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeCountComponentControls, "In TestNaviDeCountComponentControls" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeCountComponentControls );
    // Print to log file
    iLog->Log( KTestNaviDeCountComponentControls );
      
    iNaviContainerDeExt = STATIC_CAST( CTestSDKNavipaneNaviDeExt*, 
        iNaviContainer->CreateTabGroupL() );
    
    TInt count = iNaviContainerDeExt->CountComponentControls();
    
    STIF_ASSERT_EQUALS( count, 0 );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeComponentControlL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeComponentControl, "In TestNaviDeComponentControl" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeComponentControl );
    // Print to log file
    iLog->Log( KTestNaviDeComponentControl );
  
    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
      
    iNaviContainerDeExt = STATIC_CAST( CTestSDKNavipaneNaviDeExt*, 
        iNaviContainer->CreateTabGroupL() );
        
    CCoeControl* control = iNaviContainerDeExt->ComponentControl( 1 );
    
    STIF_ASSERT_NOT_NULL( control );
    
    return KErrNone;

    }


// -----------------------------------------------------------------------------
// CTestSDKNaviPane::TestNaviDeHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::TestNaviDeHandleControlEventL(
    CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( testsdknavipane, "testsdknavipane" );
    _LIT( KTestNaviDeHandleControlEventL, "In TestNaviDeHandleControlEventL" );
    TestModuleIf().Printf( 0, testsdknavipane,
        KTestNaviDeHandleControlEventL );
    // Print to log file
    iLog->Log( KTestNaviDeHandleControlEventL );
  
    TInt err = KErrNone;

    iNaviContainerDe = iNaviContainer->CreateTabGroupL();
      
    iNaviContainerDeExt = STATIC_CAST( CTestSDKNavipaneNaviDeExt*, 
        iNaviContainer->CreateTabGroupL() );
            
    MCoeControlObserver::TCoeEvent eventType = MCoeControlObserver::EEventStateChanged;
    CCoeControl* control = iNaviContainerDeExt->ComponentControl( 1 );
    
    TRAP( err, iNaviContainerDeExt->HandleControlEventL( control, eventType ) );
    return KErrNone;

    }
