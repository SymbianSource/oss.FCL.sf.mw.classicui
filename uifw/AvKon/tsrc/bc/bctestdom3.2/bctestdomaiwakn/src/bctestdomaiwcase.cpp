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
#include <aiwmenu.h>          //test aiwmenu.h

#include "bctestdomaiwcase.h" 
#include "bctestdomaiwakncontainer.h" 
#include "bctestdomaiwakn.hrh"
#include "bctestdomaiwaknview.h"
#include "bctestdomaiwserviceifmenu.h"
#include "bctestdomaknecsdetector.h"
#include "bctestdomaiwaknapp.h"   // test  AknLaunchAppService.h
#include "bctestdomaknanimview.h"  // test aknanimview.h
#include "bctestdomaknindicatorcontainer.h" 

const TInt KAiwCmdTestCAiwMenuPane =  0;
_LIT( KResFileNameForTestingCAiwMenuPane, "z:\\resource\\finditemmenu.rsc" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAiwCase* CBCTestDomAiwCase::NewL( 
    CBCTestDomAiwAknContainer* aContainer )
    {
    CBCTestDomAiwCase* self = 
        new( ELeave ) CBCTestDomAiwCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAiwCase::CBCTestDomAiwCase( CBCTestDomAiwAknContainer* 
    aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAiwCase::~CBCTestDomAiwCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwCase::ConstructL()
    { 
    BuildScriptL();
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAiwCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), 
              //  EBCTestDomCmdOutline1            
              LeftCBA,LeftCBA, 
              
              TEND );    
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAiwCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestDomCmdOutline1 )
        {
        return;
        }        
        
    switch ( aCmd )  
        {
        case EBCTestDomCmdOutline1:
            {
            TestAiwMenu();    
            TestAiwServiceIfMenu();
            
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
void CBCTestDomAiwCase::ProcessCommandL(TInt /*aCommandId*/) 
    {    
    }
    
// ---------------------------------------------------------------------------
// From class MEikMenuObserver.
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwCase::SetEmphasis(
    CCoeControl* /*aMenuControl*/,
    TBool /*aEmphasis*/)
    {    
    }    
    
// ---------------------------------------------------------------------------
// CBCTestDomAiwCase::TestAiwMenu()
// for test APIs  in aiwmenu.h .
// test Result: OK.  
// ---------------------------------------------------------------------------
//    
void CBCTestDomAiwCase::TestAiwMenu()
    {
     
    CEikMenuPane* eikMenuPane = 
        new(ELeave) CEikMenuPane(this);
    CleanupStack::PushL( eikMenuPane );
    
    TInt baseCmdId = 0;
    CAiwMenuPane  *  aiwMenupane =  
        new  CAiwMenuPane( *eikMenuPane, baseCmdId ); 
    CleanupStack::Pop( eikMenuPane );
    CleanupStack::PushL( aiwMenupane );
    _LIT( KCAiwMenuPane, "CAiwMenuPane() test" );
    AssertTrueL( ETrue, KCAiwMenuPane );

    
    TInt serviceCmd = 0;
    CEikMenuPaneItem::SData  menuItem ;
    TInt index = 0;
    aiwMenupane->AddMenuItemL(
        serviceCmd,
        menuItem, 
        index );
    _LIT( 
        KAddMenuItemLNoExtraText, 
        "AddMenuItemL(aServiceCmd,aMenuItem,aIndex)  test" );
    AssertTrueL( ETrue, KAddMenuItemLNoExtraText );
           
    
    TBuf<10> extraText;
    aiwMenupane->AddMenuItemL( 
        serviceCmd,
        menuItem, 
        index, 
        extraText );            
    _LIT( 
        KAddMenuItemLExtraText, 
        "AddMenuItemL(aServiceCmd,aMenuItem,aIndex,aExtraText)  test" );
    AssertTrueL( ETrue, KAddMenuItemLExtraText );
    
                
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(
        reader, 
        R_BCTESTDOMAIWAKN_CAIWMENUPANE_MENU );
    aiwMenupane->AddMenuItemsL( 
        reader, 
        KAiwCmdTestCAiwMenuPane , 
        index );
    _LIT( 
        KAddMenuItemsLWithReader, 
        "AddMenuItemsL(aReader,aServiceCmd,aIndex,aAddSeperator)  test" );
    AssertTrueL( ETrue, KAddMenuItemsLWithReader );    
    CleanupStack::PopAndDestroy(); // reader 
 
  
    
    TFileName resourceFileName( KResFileNameForTestingCAiwMenuPane  );
    aiwMenupane->AddMenuItemsL( 
        resourceFileName,R_FINDITEMMENU_MENU,
        serviceCmd,index );
 
   
    TInt dynCmdId = 0;
    TInt cmdId = aiwMenupane->MenuCmdId( dynCmdId);
    _LIT( KMenuCmdId, "MenuCmdId(dynCmdId)  test" );
    AssertTrueL( ETrue, KMenuCmdId );    
    
    
    TInt menuCmdId = 0;
    cmdId = aiwMenupane->DynCmdId( menuCmdId );
     _LIT( KDynCmdId, "DynCmdId(menuCmdId)  test" );
    AssertTrueL( ETrue, KDynCmdId ); 
    
    aiwMenupane->ServiceCmdId( dynCmdId );
     _LIT( KServiceCmdId, 
        "ServiceCmdId(dynCmdId)  test" );
    AssertTrueL( ETrue, KServiceCmdId ); 
        
    _LIT( KStrTile, "title" );
    TBuf<10> itemTitle(KStrTile);
    aiwMenupane->AddTitleItemL( itemTitle, index);      
     _LIT( KAddTitleItemL, 
        "KAddTitleItemL(itemTitle,index)  test" );
    AssertTrueL( ETrue, KAddTitleItemL );     
    
    
    CleanupStack::PopAndDestroy( aiwMenupane );
    _LIT( KDestructor, "~CAiwMenuPane()  test" );
    AssertTrueL( ETrue, KDestructor );

    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAiwCase::TestAiwServiceIfMenu()
// for test APIs  in AiwServiceIfBase.h and AiwServiceIfMenu.h .
// ---------------------------------------------------------------------------
//    
void CBCTestDomAiwCase::TestAiwServiceIfMenu()
    {
   
    CBCTestDomAiwServiceIfMenu* aiwServiceIfMenu = 
        CBCTestDomAiwServiceIfMenu::NewLC( );
    
    
    const CAiwMenuPane* aiwMenuPane =  
        aiwServiceIfMenu->MenuPane(); //
    _LIT( KLogMenuPane, 
        "CAiwServiceIfMenu::MenuPane() test" );
    AssertTrueL( ETrue, KLogMenuPane );
    
    

    aiwServiceIfMenu->TestFuncExtensionInterface();
    _LIT( KLogExtensionInterface, 
        "CAiwServiceIfMenu::ExtensionInterface() test" );
    AssertTrueL( ETrue, KLogExtensionInterface );
    
    CleanupStack::PopAndDestroy( aiwServiceIfMenu );
    _LIT( KLogDestructor, 
        "~CAiwServiceIfMenu() and ~CAiwServiceIfBase() test" );
    AssertTrueL( ETrue, KLogDestructor );
   
    }


