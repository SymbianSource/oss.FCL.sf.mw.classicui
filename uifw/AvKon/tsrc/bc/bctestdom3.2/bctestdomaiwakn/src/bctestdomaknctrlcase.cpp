/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#include <coecntrl.h>
#include <aknenv.h> 
#include <aknconsts.h>
#include <bctestdomaiwakn.rsg>
#include <ecom.h>
#include <finditemmenu.rsg>
#include <aknjavalists.h>       // for testing APIs in aknjavalists.h
#include <akninputblock.h>      // for testing APIs in AknInputBlock.h
#include <aknindicator.h>       // for testing APIs in aknindicator.h    
#include <aknindicatorplugin.h> // for testing APIs in aknindicatorplugin.h
#include <aknindicatorpluginimpluids.hrh>
#include <aknincallbubblenotify.h>      
#include <aknfilefilterfactory.h> 
#include <aknglobalpopupprioritycontroller.h> 
#include <aknappgrid.h> // for testing APIs in aknappgrid.h


#include "bctestdomaknctrlcase.h" 
#include "bctestdomaiwakncontainer.h" 
#include "bctestdomaiwakn.hrh"
#include "bctestdomaiwaknview.h"
#include "bctestdomaknanimview.h"  // for testing APIs in aknanimview.h
#include "bctestdomaknindicatorcontainer.h" 
#include "bctestdomakncharmap.h" // for testing APIs in akncharmap.h
#include "bctestdomaknbatterypane.h" 
#include "bctestdomaknanimdata.h" 


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknCtrlCase* CBCTestDomAknCtrlCase::NewL( 
    CBCTestDomAiwAknContainer*  aContainer )
    {
    CBCTestDomAknCtrlCase* self = new( ELeave ) CBCTestDomAknCtrlCase( 
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknCtrlCase::CBCTestDomAknCtrlCase( 
    CBCTestDomAiwAknContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknCtrlCase::~CBCTestDomAknCtrlCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAknCtrlCase::ConstructL()
    { 
    BuildScriptL();
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknCtrlCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomAknCtrlCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), 
              //  EBCTestDomCmdOutline3
              LeftCBA,REP( Down, 2 ), LeftCBA,
              
              TEND );    
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknCtrlCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomAknCtrlCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestDomCmdOutline3 )
        {
        return;
        }        

    switch ( aCmd )  
        {
        case EBCTestDomCmdOutline3:    
            {   
            // test Ctrl classes         
            TestAknBattery();//Ctrl 
            TestAknCharMap(); //Ctrl  
             
            TestAknFileFilterFactory(); //Not Ctrl  
                          
            TestAknGlobalPopupPriorityController(); // Not Ctrl                 
            TestAknIncallBubbleNotify();//Not Ctrl            
            TestAknIndicator();  //Ctrl           
            TestAknInputBlock();  //Ctrl     
                    
            TestListBox(); ////Ctrl ,skip 1 API   
            }
            break;                                            
        default:            
            break;
        }
    }

// ---------------------------------------------------------------------------
// From class MEikMenuObserver.
// ---------------------------------------------------------------------------
//
void CBCTestDomAknCtrlCase::ProcessCommandL(TInt /*aCommandId*/) 
    {    
    }
    
// ---------------------------------------------------------------------------
// From class MEikMenuObserver.
// ---------------------------------------------------------------------------
//
void CBCTestDomAknCtrlCase::SetEmphasis(
    CCoeControl* /*aMenuControl*/,
    TBool /*aEmphasis*/)
    {    
    }    
     

// ---------------------------------------------------------------------------
// CBCTestDomAknCtrlCase::TestAknBattery()
// Indirectly test APIs in aknbattery.h through bctestdomaknbatterypane.h
// Test Result: OK,SKIP 1 private API which can NOT be test.
//           
// ---------------------------------------------------------------------------
//      
void CBCTestDomAknCtrlCase::TestAknBattery()
    {
    CBCTestDomAknBatteryPane*  batteryPane = 
        new( ELeave ) CBCTestDomAknBatteryPane();
    CleanupStack::PushL( batteryPane );
    _LIT( 
        KCAknBatteryPane, 
        "CAknBatteryPane() test" );
    AssertNotNullL( batteryPane,  KCAknBatteryPane);      
    
    batteryPane->SetContainerWindowL( *iContainer );
    

    TResourceReader resourceReader;
    CCoeEnv::Static()->CreateResourceReaderLC( 
        resourceReader, 
        R_BCTESTDOMAIWAKN_AKNBATTERY_BATTERY_PANE );
    batteryPane->ConstructFromResourceL(resourceReader);  
    CleanupStack::PopAndDestroy(); // resourceReader
    _LIT( 
        KCAknBatteryPaneConstructL, 
        "CAknBatteryPane::ConstructL() test" );
    AssertTrueL( ETrue,  KCAknBatteryPaneConstructL );     
    _LIT( 
        KCAknBatteryPaneConstructFromResourceL, 
        "CAknBatteryPane::ConstructFromResourceL() test" );
    AssertTrueL( ETrue,  KCAknBatteryPaneConstructFromResourceL );     
    
    
    
    batteryPane->SetBatteryLevel( 0 ); 
    _LIT( 
        KCAknBatteryPaneSetBatteryLevel, 
        "CAknBatteryPane::SetBatteryLevel() test" );
    AssertTrueL( ETrue,  KCAknBatteryPaneSetBatteryLevel );     
        
    TRect  listboxRect( 0,0,20,20 );    
    batteryPane->SetRect( listboxRect );
    _LIT( 
        KCAknBatteryPaneSizeChanged, 
        "CAknBatteryPane::SizeChanged() test" );
    AssertTrueL( ETrue,  KCAknBatteryPaneSizeChanged ); 
    
    TPoint  newPosition( 1,1 );
    batteryPane->SetPosition( newPosition );
    _LIT( 
        KCAknBatteryPanePositionChanged, 
        "CAknBatteryPane::PositionChanged() test" );
    AssertTrueL( ETrue,  KCAknBatteryPanePositionChanged ); 
    
    batteryPane->HandleResourceChange( KEikColorResourceChange ); 
    _LIT( 
        KCAknBatteryPaneHandleResourceChange, 
        "CAknBatteryPane::HandleResourceChange() test" );
    AssertTrueL( ETrue,  KCAknBatteryPaneHandleResourceChange ); 
    
    batteryPane->CountComponentControls(); 
    _LIT( 
        KCAknBatteryPaneCountComponentControls, 
        "CAknBatteryPane::CountComponentControls() test" );
    AssertTrueL( ETrue,  KCAknBatteryPaneCountComponentControls ); 

    batteryPane->ComponentControl( 0 ) ; 
    _LIT( 
        KCAknBatteryPaneComponentControl, 
        "CAknBatteryPane::ComponentControl() test" );
    AssertTrueL( ETrue,  KCAknBatteryPaneComponentControl ); 
    
    batteryPane->DrawDeferred( ) ;
    _LIT( 
        KCAknBatteryPaneDraw, 
        "CAknBatteryPane::Draw() test" );
    AssertTrueL( ETrue,  KCAknBatteryPaneDraw ); 
    
    

    CleanupStack::PopAndDestroy( batteryPane );           
    _LIT( 
        KDelCAknBatteryPane, 
        "~CAknBatteryPane() test" );
    AssertTrueL( ETrue,  KDelCAknBatteryPane );     
    
    }
         
// ---------------------------------------------------------------------------
// CBCTestDomAknCtrlCase::TestAknCharMap()
// test APIs in AknCharMap.h
// Test Result: OK
//              
// ---------------------------------------------------------------------------
//        
void   CBCTestDomAknCtrlCase::TestAknCharMap()
    {   
    CBCTestDomCAknCharMap*  charMap = 
        new( ELeave ) CBCTestDomCAknCharMap();// create CAknCharMap
    CleanupStack::PushL( charMap ) ;       
    _LIT( 
        KCAknCharMap, 
        "CAknCharMap() test" );
    AssertNotNullL( charMap,  KCAknCharMap);             
    
    RWindow* window = (RWindow*)iContainer->DrawableWindow();
    charMap->SetContainerWindowL( *window ); 
    charMap->ConstructMenuSctRowFromDialogL( 
        R_AVKON_EMAIL_ADDR_SPECIAL_CHARACTER_TABLE_DIALOG );
    _LIT( 
        KConstructMenuSctRowFromDialogL, 
        "CAknCharMap::ConstructMenuSctRowFromDialogL() test" );
    AssertTrueL( ETrue,  KConstructMenuSctRowFromDialogL );         
        
    charMap->SetCharacterCaseL( EAknSCTUpperCase  );
    _LIT( 
        KCAknCharMapSetCharacterCaseL, 
        "CAknCharMap::SetCharacterCaseL() test" );
    AssertTrueL( ETrue,  KCAknCharMapSetCharacterCaseL );         
        
    TBuf<4> specialChars;
    charMap->SetBuffer( specialChars );
    _LIT( 
        KCAknCharMapSetBuffer, 
        "CAknCharMap::SetBuffer() test" );
    AssertTrueL( ETrue,  KCAknCharMapSetBuffer );         
    
     
    const TRect menuSctRect( 0, 0, 200, 200 );    
    charMap->SetMenuSctRect( menuSctRect );
    _LIT( 
        KCAknCharMapSetMenuSctRect, 
        "CAknCharMap::SetMenuSctRect() test" );
    AssertTrueL( ETrue,  KCAknCharMapSetMenuSctRect ); 
      
    charMap->HeightInRows();
     _LIT( 
        KCAknCharMapHeightInRows, 
        "CAknCharMap::HeightInRows() test" );
    AssertTrueL( ETrue,  KCAknCharMapHeightInRows );         
 
    charMap->MinimumSize();
    _LIT( 
        KCAknCharMapMinimumSize, 
        "CAknCharMap::MinimumSize() test" );
    AssertTrueL( ETrue,  KCAknCharMapMinimumSize );         
     
    TKeyEvent keyEvent;
    keyEvent.iCode = '5' ;
    charMap->OfferKeyEventL( keyEvent, EEventNull );
    _LIT( 
        KCAknCharMapOfferKeyEventL, 
        "CAknCharMap::OfferKeyEventL() test" );
    AssertTrueL( ETrue,  KCAknCharMapOfferKeyEventL );         
     
    
    charMap->InputCapabilities();
    _LIT( 
        KCAknCharMapInputCapabilities, 
        "CAknCharMap::InputCapabilities() test" );
    AssertTrueL( ETrue,  KCAknCharMapInputCapabilities );         
    
    charMap->ActivateL();
    _LIT( 
        KCAknCharMapActivateL, 
        "CAknCharMap::ActivateL() test" );
    AssertTrueL( ETrue,  KCAknCharMapActivateL );         
     
    charMap->SizeChanged();
    _LIT( 
        KCAknCharMapSizeChanged, 
        "CAknCharMap::SizeChanged() test" );
    AssertTrueL( ETrue,  KCAknCharMapSizeChanged );         
     
    
    charMap->HandleResourceChange( KAknsMessageSkinChange );
    _LIT( 
        KCAknCharMapHandleResourceChange, 
        "CAknCharMap::HandleResourceChange() test" );
    AssertTrueL( ETrue,  KCAknCharMapHandleResourceChange );         
     
    charMap->CountComponentControls();  
    _LIT( 
        KCAknCharMapCountComponentControls, 
        "CAknCharMap::CountComponentControls() test" );
    AssertTrueL( ETrue,  KCAknCharMapCountComponentControls );         
      
    const TInt controlIndex = 0;
    charMap->ComponentControl( controlIndex  );
    _LIT( 
        KCAknCharMapComponentControl, 
        "CAknCharMap::ComponentControl() test" );
    AssertTrueL( ETrue,  KCAknCharMapComponentControl );         

    TPointerEvent pointerEvent;
    pointerEvent.iType  = TPointerEvent::EButton1Up ;
    charMap->HandlePointerEventL( pointerEvent );
    _LIT( 
        KCAknCharMapHandlePointerEventL, 
        "CAknCharMap::HandlePointerEventL() test" );
    AssertTrueL( ETrue,  KCAknCharMapHandlePointerEventL );         

    charMap->SetObserver( NULL );  
    _LIT( 
        KCAknCharMapSetObserver, 
        "CAknCharMap::SetObserver() test" );
    AssertTrueL( ETrue,  KCAknCharMapSetObserver );         

    charMap->HighlightSctRow( EFalse );
    _LIT( 
        KCAknCharMapHighlightSctRow, 
        "CAknCharMap::HighlightSctRow() test" );
    AssertTrueL( ETrue,  KCAknCharMapHighlightSctRow );     
    
    CleanupStack::PopAndDestroy( charMap ); // delete charMap
    _LIT(KDelCAknCharMap, 
        "~CAknCharMap() test" );
    AssertTrueL( ETrue,  KDelCAknCharMap ); 
    
    
    charMap = new( ELeave ) CBCTestDomCAknCharMap();
    CleanupStack::PushL( charMap ); 
    window = (RWindow*)iContainer->DrawableWindow();
    charMap->SetContainerWindowL( *window );                 
    TResourceReader resourceReader;
    CCoeEnv::Static()->CreateResourceReaderLC( 
        resourceReader, //
        R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE ); 
     charMap->ConstructFromResourceL( resourceReader ); 
    CleanupStack::PopAndDestroy(); // resourceReader       
    _LIT( 
        KAnimDataConstructFromResourceL, 
        "CAknCharMap::ConstructFromResourceL() test" );
    AssertTrueL( ETrue,  KAnimDataConstructFromResourceL );         
    CleanupStack::PopAndDestroy( charMap ); // delete charMap, 2nd time


    charMap = new( ELeave ) CBCTestDomCAknCharMap();
    CleanupStack::PushL( charMap );
    window = (RWindow*)iContainer->DrawableWindow();
    charMap->SetContainerWindowL( *window );          
    charMap->ConstructMenuSctRowL( 
        R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    _LIT( 
        KConstructMenuSctRowLResourceId, 
        "CAknCharMap::ConstructMenuSctRowL(aResourceId) test" );
    AssertTrueL( ETrue,  KConstructMenuSctRowLResourceId );         
    CleanupStack::PopAndDestroy( charMap ); // delete charMap, 2rd time
   
   
    charMap = new( ELeave ) CBCTestDomCAknCharMap();
    CleanupStack::PushL( charMap );
    window = (RWindow*)iContainer->DrawableWindow();
    charMap->SetContainerWindowL( *window );          
    charMap->ConstructMenuSctRowL();      
    _LIT( 
        KConstructMenuSctRowL, 
        "CAknCharMap::ConstructMenuSctRowL() test" );
    AssertTrueL( ETrue,  KConstructMenuSctRowL );         
    CleanupStack::PopAndDestroy( charMap ); 
  
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknCtrlCase::TestAknFileFilterFactory()
// test APIs in AknFileFilterFactory.h 
// Test Result: OK
//           
// ---------------------------------------------------------------------------
//   
void CBCTestDomAknCtrlCase::TestAknFileFilterFactory()
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( 
        reader, 
        R_BCTESTDOMAIWAKN_AKNFILEFILTERFACTORY_FILTER );// RESOURCE  FILTER 
    AknFileFilterFactory::CreateFilterLC( reader ); //static function 
    _LIT( KCreateFilterLC, "CreateFilterLC() test" );
    AssertTrueL( ETrue,  KCreateFilterLC );     
 
    CleanupStack::PopAndDestroy(2); // reader and Filter
    }
       
// ---------------------------------------------------------------------------
// CBCTestDomAknCtrlCase::TestAknGlobalPopupPriorityController()
// test static APIs in aknglobalpopupprioritycontroller.h ..
// Test Result: OK
//           
// ---------------------------------------------------------------------------
//   
void CBCTestDomAknCtrlCase::TestAknGlobalPopupPriorityController()
    {
    AknGlobalPopupPriorityController::EnablePriorityControlL();
    _LIT( 
        KEnablePriorityControlL, 
        "EnablePriorityControlL() test" );
    AssertTrueL( ETrue,  KEnablePriorityControlL ); 
    

    RWindowGroup & rootWinGroup = CCoeEnv::Static()->RootWin() ;       
    TInt ordinalPosition = rootWinGroup.OrdinalPosition();
    AknGlobalPopupPriorityController::SetRootWinOrdinalPosition( 
        ordinalPosition );
    _LIT( 
        KSetRootWinOrdinalPosition, 
        "SetRootWinOrdinalPosition() test" );
    AssertTrueL( ETrue,  KSetRootWinOrdinalPosition );   
    
      
    AknGlobalPopupPriorityController::SetPopupPriorityL( *iContainer, 0);
    _LIT( 
        KSetPopupPriorityL, 
        "SetPopupPriorityL() test" );
    AssertTrueL( ETrue,  KSetPopupPriorityL );      
    
    
    AknGlobalPopupPriorityController::RemovePopupPriority( *iContainer );
    _LIT( 
        KRemovePopupPriority, 
        "RemovePopupPriority() test" );
    AssertTrueL( ETrue,  KRemovePopupPriority );      
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknCtrlCase::TestAknIncallBubbleNotify()
// test APIs in   AknIncallBubbleNotify.h                            
// ---------------------------------------------------------------------------
//  
void CBCTestDomAknCtrlCase::TestAknIncallBubbleNotify()
    {    
    CAknIncallBubble*  incallBubble = CAknIncallBubble::NewL();
    CleanupStack::PushL( incallBubble );
    _LIT( KlBubbleNewL, "CAknIncallBubble::NewL() test" );
    AssertNotNullL( incallBubble, KlBubbleNewL );     
    
    
    CleanupStack::PopAndDestroy( incallBubble );   
    _LIT( 
        KDestructor, 
        "~CAknIncallBubble() test" );
    AssertTrueL( ETrue, KDestructor );          
    
    
    incallBubble = CAknIncallBubble::NewLC();
    _LIT( 
        KlBubbleNewLC, 
        "CAknIncallBubble::NewLC() test" );
    AssertNotNullL( incallBubble, KlBubbleNewLC );     
    
    
    TInt bubbleflags = -1;
    incallBubble->SetIncallBubbleFlagsL( bubbleflags );
    _LIT( 
        KSetIncallBubbleFlagsL, 
        "CAknIncallBubble::SetIncallBubbleFlagsL() test" );
    AssertTrueL( ETrue,  KSetIncallBubbleFlagsL );     
    
    
    incallBubble->SetIncallBubbleAllowedInIdleL( EFalse );
    _LIT( 
        KSetIncallBubbleAllowedInIdleL, 
        "CAknIncallBubble::SetIncallBubbleFlagsL() test" );
    AssertTrueL( ETrue,  KSetIncallBubbleAllowedInIdleL );      
    
    
    incallBubble->SetIncallBubbleAllowedInUsualL( EFalse );
     _LIT( 
        KSetIncallBubbleAllowedInUsualL, 
        "CAknIncallBubble::SetIncallBubbleFlagsL() test" );
    AssertTrueL( ETrue,  KSetIncallBubbleAllowedInUsualL );  
    
    CleanupStack::PopAndDestroy( incallBubble ); 
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknCtrlCase::TestAknIndicator()
// test APIs in aknindicator.h and  aknindicatorplugin.h    
// test Result: OK.                         
// ---------------------------------------------------------------------------
//  
void CBCTestDomAknCtrlCase::TestAknIndicator()
    {
    // test APIs in aknindicator.h
    // test Result: OK.   
    CBCTestDomAknIndicatorContainer* indicatorPane = 
        CBCTestDomAknIndicatorContainer::NewLC();
    
    TInt ctrlIndex = 0;
    CCoeControl* indicatorControl = 
        indicatorPane->ComponentControl( ctrlIndex );    
    CAknIndicator*  aknIndicator = 
        static_cast<CAknIndicator*> ( indicatorControl ); 
           
    if( aknIndicator )
        {
        aknIndicator->SetIndicatorObserver( NULL );
        _LIT( 
            KSetIndicatorObserver, 
            "CAknIndicator::SetIndicatorObserver() test" );
        AssertTrueL( ETrue,  KSetIndicatorObserver );     
        
        TPointerEvent  pointerEvent ;
        pointerEvent.iType = TPointerEvent::EMove;
        aknIndicator->HandlePointerEventL( pointerEvent );
        _LIT( 
            KHandlePointerEventL, 
            "CAknIndicator::HandlePointerEventL() test" );
        AssertTrueL( ETrue,  KHandlePointerEventL );
        }


    CleanupStack::PopAndDestroy( indicatorPane );    
   
    
    TUid pluginUid = TUid::Uid( KImplUIDMessagingIndicatorsPlugin );
    CAknIndicatorPlugin* aknIndicatorPlugin = NULL;
    TRAPD(err, 
        aknIndicatorPlugin =
        CAknIndicatorPlugin::NewL( pluginUid )
        );    
    CleanupStack::PushL( aknIndicatorPlugin );
    _LIT( KPluginNewL, "CAknIndicatorPlugin::NewL() test" );     
    AssertIntL( err, err, KPluginNewL );
    
    CleanupStack::Pop( aknIndicatorPlugin );   
    delete aknIndicatorPlugin;
    _LIT( KDestructor, "~CAknIndicatorPlugin() test" );
    AssertTrueL( ETrue, KDestructor );              
    
    REComSession::FinalClose(); 
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknCtrlCase::TestAknInputBlock()
// test APIs in AknInputBlock.h     
// test Result: OK.  
// ---------------------------------------------------------------------------
//  
void CBCTestDomAknCtrlCase::TestAknInputBlock()
    {
    
    CAknInputBlock* aknInputBlock = CAknInputBlock::NewLC();
    _LIT( KNewLC, "CAknInputBlock::NewLC() test" );
    AssertNotNullL( aknInputBlock, KNewLC ); 
    
    
    CleanupStack::PopAndDestroy( aknInputBlock ); 
    _LIT( KDestructor, "~CAknInputBlock() test" );
    AssertTrueL( ETrue, KDestructor ); 
    
    aknInputBlock = CAknInputBlock::NewCancelHandlerLC( NULL );
    _LIT( KNewCancelHandlerLC, "CAknInputBlock::NewCancelHandlerLC() test" );
    AssertNotNullL( aknInputBlock, KNewCancelHandlerLC ); 
    CleanupStack::PopAndDestroy( aknInputBlock ); 
    
    aknInputBlock = CAknInputBlock::NewCancelActiveLC( NULL );
    _LIT( KNewCancelActiveLC, "CAknInputBlock::NewCancelActiveLC() test" );
    AssertNotNullL( aknInputBlock, KNewCancelActiveLC ); 
    CleanupStack::PopAndDestroy( aknInputBlock ); 
    
    aknInputBlock = CAknInputBlock::NewCancelDeleteLC( NULL );
    _LIT( KNewCancelDeleteLC, "CAknInputBlock::NewCancelDeleteLC() test" );
    AssertNotNullL( aknInputBlock, KNewCancelDeleteLC ); 
    
    aknInputBlock->SetCancelHandler( NULL );
    _LIT( KSetCancelHandler, "CAknInputBlock::SetCancelHandler() test" );
    AssertTrueL( ETrue,  KSetCancelHandler ); 
    
    aknInputBlock->SetCancelActive( NULL );
    _LIT( KSetCancelActive, "CAknInputBlock::SetCancelActive() test" );
    AssertTrueL( ETrue,  KSetCancelActive ); 
    
    aknInputBlock->SetCancelDelete( NULL );
    _LIT( KSetCancelDelete, "CAknInputBlock::SetCancelDelete() test" );
    AssertTrueL( ETrue,  KSetCancelDelete ); 
    
    aknInputBlock->Cancel();
    _LIT( KCancel, "CAknInputBlock::Cancel() test" );
    AssertTrueL( ETrue,  KCancel ); 
    
    CleanupStack::PopAndDestroy( aknInputBlock );     
    }
 
// ---------------------------------------------------------------------------
// CBCTestDomAknCtrlCase::TestListBox()
// test APIs in AknJavaLists.h   and aknappgrid.h *  
// test Result: APIs in AknJavaLists.h are OK;
//              APIs in aknappgrid.h  SKIP 1.                        
// ---------------------------------------------------------------------------
//          
void CBCTestDomAknCtrlCase::TestListBox()  
    {
    //test APIs in AknJavaLists.h
    CAknDouble2GraphicLargeStyleListBox* double2ListBox = 
        new( ELeave ) CAknDouble2GraphicLargeStyleListBox();
    CleanupStack::PushL( double2ListBox );
    _LIT( 
        KAknDouble2ListBox, 
        "CAknDouble2GraphicLargeStyleListBox instance created" );
    AssertNotNullL( double2ListBox, KAknDouble2ListBox );
   
      
    double2ListBox->ConstructL(NULL,EAknListBoxSelectionList);
    _LIT( KCreateItemDrawerL, "CreateItemDrawerL() test" );
    AssertTrueL( ETrue, KCreateItemDrawerL ); 
        
    TRect  listboxRect( 0,0,20,20 );    
    double2ListBox->SetRect( listboxRect );

    double2ListBox->SizeChanged();
    _LIT( KSizeChanged, "SizeChanged() test" );
    AssertTrueL( ETrue, KSizeChanged ); 
     
    double2ListBox->MinimumSize();
    _LIT( KMinimumSize, "MinimumSize() test" );
    AssertTrueL( ETrue, KMinimumSize ); 
 
    CleanupStack::PopAndDestroy( double2ListBox ); 
    
  
    CAknSingle2GraphicStyleListBox* single2ListBox = 
        new( ELeave ) CAknSingle2GraphicStyleListBox() ;  
    CleanupStack::PushL( single2ListBox );
    _LIT( 
        KCAknSingle2GraphicStyleListBox, 
        "CAknDouble2GraphicLargeStyleListBox instance created" );
    AssertNotNullL( single2ListBox, KCAknSingle2GraphicStyleListBox );

    single2ListBox->SetContainerWindowL( *iContainer );   
    single2ListBox->ConstructL(NULL,EAknListBoxSelectionList);
    _LIT( 
        KSingle2ListBoxCreateItemDrawerL, 
        "CAknSingle2GraphicStyleListBox::CreateItemDrawerL() test" );
    AssertTrueL( ETrue, KSingle2ListBoxCreateItemDrawerL ); 
    
    single2ListBox->SetRect( listboxRect );

    single2ListBox->SizeChanged();
    _LIT( KSingle2ListBoxSizeChanged, 
        "CAknSingle2GraphicStyleListBox::SizeChanged() test" );
    AssertTrueL( ETrue, KSingle2ListBoxSizeChanged ); 
    
    
    single2ListBox->MinimumSize();
    _LIT( KSingle2ListBoxMinimumSize, 
        "CAknSingle2GraphicStyleListBox::MinimumSize() test" );
    AssertTrueL( ETrue, KSingle2ListBoxMinimumSize );     
     
    
    single2ListBox->UseEmptyIconSpace( EFalse );
    _LIT( 
        KSingle2ListBoxUseEmptyIconSpace, 
        "UseEmptyIconSpace() test" );
    AssertTrueL( ETrue, KSingle2ListBoxUseEmptyIconSpace ); 
    
    CleanupStack::PopAndDestroy( single2ListBox ); 
    
    //test APIs in aknappgrid.h    
    CAknAppStyleGrid* appStyleGrid = 
        new( ELeave ) CAknAppStyleGrid();//test CAknAppStyleGrid,start  
    CleanupStack::PushL( appStyleGrid );
    _LIT( 
        KCAknAppStyleGrid, 
        "CAknDouble2GraphicLargeStyleListBox instance created" );
    AssertNotNullL( appStyleGrid, KCAknAppStyleGrid );
    
    appStyleGrid->SetContainerWindowL( *iContainer ); 
       
    appStyleGrid->ConstructL( iContainer );
    _LIT( 
        KAppStyleGridConstructL, 
        "CAknAppStyleGrid::ConstructL() test" );
    AssertTrueL( ETrue, KAppStyleGridConstructL ); 
 
    
    appStyleGrid->SetRect( listboxRect );
    appStyleGrid->SizeChanged();
    _LIT( 
        KAppStyleGridSizeChanged, 
        "CAknAppStyleGrid::SizeChanged() test" );
    AssertTrueL( ETrue, KAppStyleGridSizeChanged ); 
     
    appStyleGrid->MinimumSize();
    _LIT( 
        KAppStyleGridMinimumSize, 
        "CAknAppStyleGrid::MinimumSize() test" );
    AssertTrueL( ETrue, KAppStyleGridMinimumSize ); 
     
    appStyleGrid->SetShortcutEnabledL( EFalse );
    _LIT( 
        KAppStyleGridSetShortcutEnabledL, 
        "CAknAppStyleGrid::CreateItemDrawerL() test" );
    AssertTrueL( ETrue, KAppStyleGridSetShortcutEnabledL ); 
   

    iContainer->DrawNow();//implicitly test DrawBackgroundAroundGrid(.)
    _LIT( 
        KAppStyleGridDrawBackgroundAroundGrid, 
       "CAknAppStyleGrid::DrawBackgroundAroundGrid() test" );
    AssertTrueL( ETrue, KAppStyleGridDrawBackgroundAroundGrid ); 
    
     
    CleanupStack::PopAndDestroy( appStyleGrid );   
    }
 
 
