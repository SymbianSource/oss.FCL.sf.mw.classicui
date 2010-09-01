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
#include <e32const.h>
#include <coecntrl.h>
#include <barsread.h>
#include <badesca.h>
#include <fbs.h>
#include <aknnotedialog.h>
#include <eikalmct.h>
#include <eikslbd.h>
#include <eiksoftkeyimage.h>
#include <eikimage.h> 
#include <avkon.mbg>
#include <akniconutils.h>
#include <eiksrvui.h>
#include <tactilefeedbackserver.h>

#include "bctestdomeikcase.h"
#include "bctestdomavkonpslncontainer.h"
#include "bctestdomavkonpslnext.h"
#include "bctestdomavkonpsln.hrh"

//    CONSTANTS

const TInt KWidth = 25;
const TInt KHeight = 25;

_LIT( KText, "Text" );


// ============================ MEMBER FUNCTIONS ============================

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
class CEikServAppUi;
CBCTestDomEikCase* CBCTestDomEikCase::NewL( CBCTestDomAvkonPslnContainer* 
    aContainer )
    {
    CBCTestDomEikCase* self = new( ELeave ) CBCTestDomEikCase( 
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
CBCTestDomEikCase::CBCTestDomEikCase( CBCTestDomAvkonPslnContainer* 
    aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomEikCase::~CBCTestDomEikCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomEikCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomEikCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomEikCase::BuildScriptL()
    {
     
    const TInt scripts[] =
        {
        LeftCBA,
        Down,
        LeftCBA        
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));  
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomEikCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomEikCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdOutline2 )
        {
        return;
        }
    switch ( aCmd )  
        {
        case EBCTestCmdOutline2:
            TestServAppUiBaseL();
            TestAlarmControlL();
            TestSettingsListBoxDataL();
            TestEikSoftkeyImageL();
            break;
        default:
            break;
        }
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknCase::TestAlarmControlL()
// ---------------------------------------------------------------------------
//
void CBCTestDomEikCase::TestAlarmControlL()
    {
    _LIT( KCEikAlarmControl, "CEikAlarmControl::EikAlarmControl invoked" );
    _LIT( KConstructL, "CEikAlarmControl::ConstructL invoked" );
    _LIT( KDes, "CEikAlarmControl::~EikAlarmControl invoked" );
    
    CEikAlarmControl* contrl = new ( ELeave ) CEikAlarmControl( NULL, NULL );
    CleanupStack::PushL( contrl );
    AssertNotNullL( contrl, KCEikAlarmControl );
    contrl->ConstructL();
    AssertTrueL( ETrue, KConstructL );
    
    CleanupStack::PopAndDestroy( contrl );
    AssertTrueL( ETrue, KDes );
    
    // Testcase for class MTactileFeedbackServer
    //MTactileFeedbackServer::Instance();
    //_LIT( KMInstance, "MTactileFeedbackServer::Instance" );
    //AssertTrueL( ETrue, KMInstance );
    }

// ---------------------------------------------------------------------------
// CBCTestDomEikCase::TestSettingsListBoxDataL()
// ---------------------------------------------------------------------------
//    
void CBCTestDomEikCase::TestSettingsListBoxDataL()
    {
    
    _LIT( KCSettingsListBoxData, "CSettingsListBoxData::NewL invoked" );
    _LIT( KDes, "CSettingsListBoxData::~CSettingsListBoxData invoked" );
    _LIT( KDraw, "CSettingsListBoxData::Draw invoked" );
    
    CSettingsListBoxData* data = CSettingsListBoxData::NewL();
    CleanupStack::PushL( data );
    AssertNotNullL( data, KCSettingsListBoxData );
    
    iContainer->ActivateGc();
    TListItemProperties proper;
    CWindowGc& gc = iContainer->SystemGc();

    TRect rect( 0, 0, KWidth, KHeight );
    CFormattedCellListBoxData::TColors gulcolor;
    
    data->Draw( proper, gc, &KText, rect, ETrue, gulcolor );
    AssertTrueL( ETrue, KDraw );
    iContainer->DeactivateGc();
    
    CleanupStack::PopAndDestroy( data );
    AssertTrueL( ETrue, KDes );
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomEikCase::TestEikSoftkeyImageL()
// ---------------------------------------------------------------------------
//    
void CBCTestDomEikCase::TestEikSoftkeyImageL()
    {
    
    _LIT( KSetImage, "EikSoftkeyImage::SetImage() invoked" );
    _LIT( KSetLabel, "EikSoftkeyImage::SetLabel() invoked" );
    
    CEikButtonGroupContainer* container = CEikButtonGroupContainer::Current();
    EikSoftkeyImage::SetLabel( container, ETrue );
    AssertTrueL( ETrue, KSetLabel );
    
    CEikImage* image = new ( ELeave ) CEikImage;
    CleanupStack::PushL( image );
    CFbsBitmap* bmp = AknIconUtils::CreateIconL( AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_speaker_active );                    
    image->SetPicture( bmp );
   
    EikSoftkeyImage::SetImage( container, *image, ETrue );
    AssertTrueL( ETrue, KSetImage );
    CleanupStack::Pop( image );
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomEikCase::TestServAppUiBaseExtL()
// ---------------------------------------------------------------------------
//    
void CBCTestDomEikCase::TestServAppUiBaseL()
    {
 
    _LIT( KHideApplicationFromFswL,
        "CEikServAppUi::HideApplicationFromFswL() invoked" );
    _LIT( KActivateDisplayIfNeeded,
        "CEikServAppUi::ActivateDisplayIfNeeded() invoked" );
    _LIT( KNewLC, "CEikServAppUiBase::NewLC() invoked" );
    _LIT( KBringAlertGroupWinForwards, 
        "CEikServAppUiBase::BringAlertGroupWinForwards() invoked" );
    _LIT( KHandleResourceChangeL, 
        "CEikServAppUiBase::HandleResourceChangeL() invoked" );
    _LIT( KHandleThreadExitL, 
        "CEikServAppUiBase::HandleThreadExitL() invoked" );
    _LIT( KHandleForegroundEventL, 
        "CEikServAppUiBase::HandleForegroundEventL() invoked" );
    _LIT( KSuppressAppSwitching,
        "CEikServAppUiBase::SuppressAppSwitching() invoked" );
    
    CEikServAppUiBase* ui = CEikServAppUiBase::NewLC();
    AssertTrueL( ETrue, KNewLC );
    
    CEikServAppUi* appui = 
        static_cast<CEikServAppUi*>(CEikonEnv::Static()->AppUi());
        
    ui = static_cast<CEikServAppUiBase*>(CEikonEnv::Static()->AppUi());
    
    //CEikServAppUiBase::HandleForegroundEventL
    ui->CEikServAppUiBase::HandleForegroundEventL( EFalse );
    AssertTrueL( ETrue, KHandleForegroundEventL );
    //CEikServAppUi::ActivateDisplayIfNeeded()
    appui->CEikServAppUi::ActivateDisplayIfNeeded();
    AssertTrueL( ETrue, KActivateDisplayIfNeeded );
    
    //CEikServAppUi::HideApplicationFromFswL()
    appui->CEikServAppUi::HideApplicationFromFswL( 0, EFalse );
    AssertTrueL( ETrue, KHideApplicationFromFswL );
    
    //CEikServAppUiBase::BringAlertGroupWinForwards()
    appui->CEikServAppUiBase::BringAlertGroupWinForwards( ETrue );
    appui->CEikServAppUiBase::BringAlertGroupWinForwards( EFalse );
    AssertTrueL( ETrue, KBringAlertGroupWinForwards );
             
    //CEikServAppUiBase::HandleThreadExitL()
    RThread thread;
    appui->HandleThreadExitL( thread );
    AssertTrueL( ETrue, KHandleThreadExitL );
    appui->HandleForegroundEventL( ETrue );
    AssertTrueL( ETrue, KHandleForegroundEventL );
    
    //CEikServAppUiBase::SuppressAppSwitching()
    appui->SuppressAppSwitching( ETrue );
    appui->SuppressAppSwitching( EFalse );

    AssertTrueL( ETrue, KSuppressAppSwitching );
    
    //CEikServAppUiBase::HandleResourceChangeL()
    CEikAppUi* cui = appui;
    cui->HandleResourceChangeL( 0 );
    AssertTrueL( ETrue, KHandleResourceChangeL );
    
    MEikServAppUiSessionHandler* hand = 
        static_cast<CEikServAppUi*>(CEikonEnv::Static()->AppUi());
    hand->CycleTasksL( EForwards );
    hand->NotifyAlarmServerOfTaskChangeL();
   
    }
//end of file
