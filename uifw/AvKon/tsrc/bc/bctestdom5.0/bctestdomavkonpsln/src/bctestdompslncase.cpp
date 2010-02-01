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
* Description:  ?Description
*
*/


#include <w32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <barsread.h>
#include <badesca.h>
#include <pslnfwiconhelper.h>
#include <pslnfwpluginhandler.h>
#include <coneresloader.h>
#include <aknappui.h> 
#include <eikspane.h> 
#include <aknnavide.h>
#include <pslnfwappthemehandler.h>
#include <xnodt.h>
#include <xnthememanagement.h>
#include <aknform.h> 
#include <sortutil.h>

#include <bctestdomavkonpsln.rsg>

#include "bctestdompslncase.h"
#include "bctestdomavkonpslncontainer.h"
#include "bctestdomavkonpslnext.h"
#include "bctestdomavkonpsln.hrh"

//    CONSTANTS

const TInt KPluginUid = 0x101F84AF;

_LIT( KFilePath, "z:\\resource\\psln.rsc" );
_LIT( KFileName, "psln.rsc" );
_LIT( KFileDir, "z:\\resource\\" );
_LIT8( KMessage, "1");

// =========================== MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomPslnCase* CBCTestDomPslnCase::NewL( CBCTestDomAvkonPslnContainer* 
    aContainer )
    {
    CBCTestDomPslnCase* self = new( ELeave ) CBCTestDomPslnCase( 
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
CBCTestDomPslnCase::CBCTestDomPslnCase( CBCTestDomAvkonPslnContainer* 
    aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomPslnCase::~CBCTestDomPslnCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomPslnCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomPslnCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomPslnCase::BuildScriptL()
    { 
    const TInt scripts[] =
        {
        LeftCBA,
        REP( Down, 4 ),
        LeftCBA
        };
    AddTestScriptL( scripts, sizeof(scripts)/sizeof(TInt) );     
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomPslnCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomPslnCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdOutline5 )
        {
        return;
        }
    switch ( aCmd )  
        {
        case EBCTestCmdOutline5:
            TestPslnFWBaseContainerL();
            TestPslnFWBaseViewL();
            TestFWIconHelperL();
            TestFWPluginHandlerL();
            TestPslnFWAppThemeHandlerL();
            break;
        default:
            break;
        }
    }


// ---------------------------------------------------------------------------
// CBCTestDomJPLangCase::TestPslnFWBaseContainerL()
// ---------------------------------------------------------------------------
//       
void CBCTestDomPslnCase::TestPslnFWBaseContainerL()
    {
    
    _LIT( KCPslnFWBaseContainer, 
        "CPslnFWBaseContainer::CPslnFWBaseContainer() invoked" );
    _LIT( KDes, 
        "CPslnFWBaseContainer::~CPslnFWBaseContainer() invoked" );
    _LIT( KConstructL, 
        "CPslnFWBaseContainer::ConstructL() invoked" );
    _LIT( KSetMiddleSoftkeyObserver, 
        "CPslnFWBaseContainer::SetMiddleSoftkeyObserver() invoked" );
    _LIT( KHandleResourceChange, 
        "CPslnFWBaseContainer::HandleResourceChange() invoked" );                        
    _LIT( KCountComponentControls, 
        "CPslnFWBaseContainer::CountComponentControls() invoked" ); 
    _LIT( KComponentControl, 
        "CPslnFWBaseContainer::ComponentControl() invoked" ); 
    _LIT( KOfferKeyEventL, 
        "CPslnFWBaseContainer::OfferKeyEventL() invoked" ); 
                             
    TRect rect( 0, 0, 0, 0 );
    CPslnFWBaseContainer* container = new ( ELeave ) CPslnFWBaseContainerExt;
    CleanupStack::PushL( container );
    AssertTrueL( ETrue, KCPslnFWBaseContainer );
    
    CMPslnFWMSKObserverExt* observer = new ( ELeave ) CMPslnFWMSKObserverExt;
    CleanupStack::PushL( observer );
    
    container->ConstructL( rect );
    AssertTrueL( ETrue, KConstructL );
    container->SetFocus( EDrawNow );
    
    container->SetMiddleSoftkeyObserver( observer );
    AssertTrueL( ETrue, KSetMiddleSoftkeyObserver );
    
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };
    CCoeControl* ctrl = container;
    
    ctrl->HandleResourceChange( 0 );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    ctrl->CountComponentControls();
    AssertTrueL( ETrue, KCountComponentControls );
    
    ctrl->ComponentControl( 0 );
    AssertTrueL( ETrue, KComponentControl );
    
    ctrl->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );
    
    AssertTrueL( ETrue, KDes );
    
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::Pop( container );
    delete container;
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomJPLangCase::TestPslnFWBaseView()
// ---------------------------------------------------------------------------
//    
void CBCTestDomPslnCase::TestPslnFWBaseViewL()
    {
    
    _LIT( KCPslnFWBaseView, "CPslnFWBaseView::CPslnFWBaseView() invoked" );
    _LIT( KConstructL, "CPslnFWBaseView::ConstructL() invoked" );   
    _LIT( KSetCurrentItem, "CPslnFWBaseView::SetCurrentItem() invoked" );    
    _LIT( KSetNaviPaneL, "CPslnFWBaseView::SetNaviPaneL() invoked" );    
    _LIT( KContainer, "CPslnFWBaseView::Container() invoked" );    
    _LIT( KOpenLocalizedResourceFileL, 
        "CPslnFWBaseView::OpenLocalizedResourceFileL() invoked" );       
    _LIT( KOpenLocalizedResourceFileLOverload, 
        "CPslnFWBaseView::OpenLocalizedResourceFileL() Overload invoked" );           
    _LIT( KSetNaviPaneDecorator, 
        "CPslnFWBaseView::SetNaviPaneDecorator() invoked" );         
    _LIT( KDoDeactivate, "CPslnFWBaseView::DoDeactivate() invoked" );          
    _LIT( KSetTabIndex, "CPslnFWBaseView::SetTabIndex() invoked" );              
    _LIT( KGetTabIndex, "CPslnFWBaseView::GetTabIndex() invoked" );          
    _LIT( KCreateNaviPaneContextL, 
        "CPslnFWBaseView::CreateNaviPaneContextL() invoked" );          
    _LIT( KCreateContainerL, "CPslnFWBaseView::CreateContainerL() invoked" );
    _LIT( KDoActivateL, "CPslnFWBaseView::DoActivateL() invoked" );
    _LIT( KSetNaviPaneLOverload, 
        "CPslnFWBaseView::SetNaviPaneL() overload invoked" );    
    _LIT( KNewContainerL, "CPslnFWBaseView::NewContainerL() invoked" );          
    _LIT( KHandleListBoxEventL, 
        "CPslnFWBaseView::HandleListBoxEventL() overload invoked" );
    _LIT( KSetMiddleSoftKeyLabelL, 
        "CPslnFWBaseView::SetMiddleSoftKeyLabelL() overload invoked" );          
    _LIT( KHandleCommandL, "CPslnFWBaseView::HandleCommandL() invoked" );          
    _LIT( KSetTitlePaneL, "CPslnFWBaseView::SetTitlePaneL() invoked" );  
    _LIT( KDes, "CPslnFWBaseView::~CPslnFWBaseView() invoked" );
            
                                
    CPslnFWBaseViewExt* view = new ( ELeave ) CPslnFWBaseViewExt();
    CleanupStack::PushL( view );
    
    AssertNotNullL( view, KCPslnFWBaseView );

    view->ConstructL();
    AssertTrueL( ETrue, KConstructL ); 
    view->SetCurrentItem( 0 );
    AssertTrueL( ETrue, KSetCurrentItem );
    
    view->SetNaviPaneL();
    AssertTrueL( ETrue, KSetNaviPaneL );
    
    view->Container();
    AssertTrueL( ETrue, KContainer );

    RConeResourceLoader loader( *CCoeEnv::Static() );
    TRAPD( res, view->OpenLocalizedResourceFileL( KFilePath, loader  ) );
    AssertTrueL( ETrue, KOpenLocalizedResourceFileL );
    
    TRAP( res, view->OpenLocalizedResourceFileL( KFileName, loader, &KFileDir ) );
    AssertTrueL( ETrue, KOpenLocalizedResourceFileLOverload );
     
    CAknAppUi* appui = static_cast<CAknAppUi*>( CCoeEnv::Static()->AppUi() );
    CEikStatusPane* pane = appui->StatusPane (); 
    CAknNavigationControlContainer* container = 
        static_cast<CAknNavigationControlContainer*>( 
        pane->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) ) );
    
    CAknForm* frm = new( ELeave ) CAknForm();
    CleanupStack::PushL( frm );
    frm->ConstructL();
    CleanupStack::Pop( frm );
    
    CAknNavigationDecorator* decorate = 
        CAknNavigationDecorator::NewL( container, frm );
    CleanupStack::PushL( decorate );
    
    view->SetNaviPaneDecorator( decorate );
    AssertTrueL( ETrue, KSetNaviPaneDecorator );
    
    view->DoDeactivate();
    AssertTrueL( ETrue, KDoDeactivate );
    
    view->SetTabIndex( 0 );
    AssertTrueL( ETrue, KSetTabIndex );
    
    view->GetTabIndex();
    AssertTrueL( ETrue, KGetTabIndex );
    
    view->CreateNaviPaneContextL( 0 );
    AssertTrueL( ETrue, KCreateNaviPaneContextL );
    
    view->CreateContainerL();
    AssertTrueL( ETrue, KCreateContainerL );
    
    view->NewContainerL();
    AssertTrueL( ETrue, KNewContainerL );
    
    TVwsViewId viewid;
    view->DoActivateL( viewid, KNullUid, KMessage );
    AssertTrueL( ETrue, KDoActivateL );
    
    view->SetNaviPaneL( 0 );
    AssertTrueL( ETrue, KSetNaviPaneLOverload );
    
    view->HandleListBoxEventL( NULL,
        MEikListBoxObserver::EEventEnterKeyPressed );
    AssertTrueL( ETrue, KHandleListBoxEventL );
    
    view->SetMiddleSoftKeyLabelL( R_BCTEST_AVKONPSLN_LABEL, 0 );
    AssertTrueL( ETrue, KSetMiddleSoftKeyLabelL );
    
    view->HandleCommandL( 0 );
    AssertTrueL( ETrue, KHandleCommandL );
    
    view->SetTitlePaneL( res );
    AssertTrueL( ETrue, KSetTitlePaneL );
   
    CleanupStack::Pop( decorate );
    CleanupStack::PopAndDestroy( view );
    AssertTrueL( ETrue, KDes );
    
    delete decorate;
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomPslnCase::TestPslnFWBaseView()
// ---------------------------------------------------------------------------
//  
void CBCTestDomPslnCase::TestFWIconHelperL()
    {
    _LIT( KNewL, "CPslnFWIconHelper::NewL() invoked ");
    _LIT( KAddIconsToSettingItemsL, 
        "CPslnFWIconHelper::AddIconsToSettingItemsL() invoked ");
    _LIT( KGetLocalizedStringLC, 
        "CPslnFWIconHelper::GetLocalizedStringLC() invoked ");
    _LIT( KDestruct, "CPslnFWIconHelper::~CPslnFWIconHelper() invoked ");          

    CPslnFWIconHelper* helper = CPslnFWIconHelper::NewL();
    CleanupStack::PushL( helper );
    AssertNotNullL( helper, KNewL );
    
    CEikColumnListBox* textList = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( textList );
    
    textList->ConstructL( iContainer );
    
    helper->AddIconsToSettingItemsL( ETrue, 0, textList );
    AssertTrueL( ETrue, KAddIconsToSettingItemsL );
    
    TRAP_IGNORE( helper->GetLocalizedStringLC( KFilePath, 0, CCoeEnv::Static() ) );
    AssertTrueL( ETrue, KGetLocalizedStringLC );
    CleanupStack::Pop( textList );
    delete textList;
    
    CleanupStack::Pop( helper );
    delete helper;
    AssertTrueL( ETrue, KDestruct );
    }

// ---------------------------------------------------------------------------
// CBCTestDomPslnCase::TestFWPluginHandlerL()
// ---------------------------------------------------------------------------
//  
void CBCTestDomPslnCase::TestFWPluginHandlerL()
    {
    
    _LIT( KNewL, "CPslnFWPluginHandler::NewL() invoked" );
    _LIT( KNewLOverload, "CPslnFWPluginHandler::NewL() overload invoked" );
    _LIT( KLoadPluginL, "CPslnFWPluginHandler::LoadPluginL() invoked" );
    _LIT( KLoadPluginLOverLoad, 
        "CPslnFWPluginHandler::LoadPluginL() overload invoked" );
    _LIT( KDes, "CPslnFWPluginHandler::~CPslnFWPluginHandler() invoked" );
    
    CArrayPtrFlat<CPslnFWPluginInterface>* array = 
        new ( ELeave ) CArrayPtrFlat<CPslnFWPluginInterface>( 1 );
    CleanupStack::PushL( array );
                  
    CAknViewAppUi* appui  = static_cast<CAknViewAppUi*>
        ( CEikonEnv::Static()->AppUi() );

    CPslnFWPluginHandler* handle = 
        CPslnFWPluginHandler::NewL( appui, array );
    CleanupStack::PushL( handle );
    AssertNotNullL( handle, KNewL );
    
    CleanupStack::Pop( handle );
    CleanupStack::Pop( array );
    
    delete handle;
    AssertTrueL( ETrue, KDes );
    handle = NULL;
    
    array->Reset();
    delete array;
    
    handle = CPslnFWPluginHandler::NewL( appui );
    CleanupStack::PushL( handle );
    AssertNotNullL( handle, KNewLOverload );
    
    CPslnFWPluginInterface* inf = handle->LoadPluginL( TUid::Uid( KPluginUid ) );
    AssertTrueL( ETrue, KLoadPluginL );
    
    delete inf;
    
    TRAP_IGNORE( handle->LoadPluginsL( array ) );
    AssertTrueL( ETrue, KLoadPluginLOverLoad );
    
    CleanupStack::Pop( handle );
    delete handle;
    handle = NULL;

    }

// ---------------------------------------------------------------------------
// CBCTestDomPslnCase::TestPslnFWAppThemeHandlerL()
// ---------------------------------------------------------------------------
//  
void CBCTestDomPslnCase::TestPslnFWAppThemeHandlerL()
    {
    //Added "CSortUtil::NewL()".
    CSortUtil* sortUtil = CSortUtil::NewL();
    CleanupStack::PushL( sortUtil );
    _LIT( KCSortUtil, "CSortUtil::NewL" );
    AssertTrueL( ETrue, KCSortUtil );
    CleanupStack::PopAndDestroy( sortUtil );     
    
    _LIT( KCPslnFWAppThemeHandler, "CPslnFWAppThemeHandler::NewL() invoked" );
    _LIT( KSetApplicationSkinL, 
        "CPslnFWAppThemeHandler::SetApplicationSkinL() invoked" );
    _LIT( KGetApplicationSkinsL, 
        "CPslnFWAppThemeHandler::GetApplicationSkinsL() invoked" );
    _LIT( KCancelGetApplicationSkins, 
        "CPslnFWAppThemeHandler::CancelGetApplicationSkins() invoked" );
    _LIT( KSetApplicationSkinAndExitL, 
        "CPslnFWAppThemeHandler::SetApplicationSkinAndExitL() invoked" );
    _LIT( KDes, "CPslnFWAppThemeHandler::~CPslnFWAppThemeHandler() invoked" );
    
    CXnODT* odt = CXnODT::NewL();
    CleanupStack::PushL( odt );
    CArrayPtrFlat<CXnODT>* array = 
        new ( ELeave ) CArrayPtrFlat<CXnODT>( 1 );
    CleanupStack::PushL( array );
    
    array->AppendL( odt, 0 );
    CMPslnFWAppThemeObserverExt* observer = new ( ELeave ) 
        CMPslnFWAppThemeObserverExt;
    CleanupStack::PushL( observer );
    
    CPslnFWAppThemeHandler* handler = 
        CPslnFWAppThemeHandler::NewL( *observer, *array );
    CleanupStack::PushL( handler );
    AssertNotNullL( handler, KCPslnFWAppThemeHandler );
    
    TXnServiceCompletedMessage msg = 
        handler->GetApplicationSkinsL( TUid::Uid( KPluginUid ) );
    AssertTrueL( ETrue, KGetApplicationSkinsL );
    
    handler->SetApplicationSkinL( *odt );
    AssertTrueL( ETrue, KSetApplicationSkinL );
   
    handler->CancelGetApplicationSkins();
    AssertTrueL( ETrue, KCancelGetApplicationSkins );
    
    handler->SetApplicationSkinAndExitL( *odt );
    AssertTrueL( ETrue, KSetApplicationSkinAndExitL );
    
    CleanupStack::PopAndDestroy( handler );
    AssertTrueL( ETrue, KDes );
    array->Reset();
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( odt );
    
    }
//end of file
