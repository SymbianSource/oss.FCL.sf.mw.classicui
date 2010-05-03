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


#include <w32std.h>
#include <coecntrl.h>
#include <avkon.rsg>
#include <eikenv.h>
#include <GULBORDR.H>
#include <coecobs.h>
#include <eiklbx.h>

#include "bctestdompopup.hrh"
#include <bctestdompopup.rsg>
#include "bctestdompopupcase.h"
#include "bctestdompopupcontainer.h"
#include "bctestdompopupapp.h"

#include <AknSctDialog.h>
#include <AknSDData.h>
#include <aknlists.h>
#include <AknPopupform.h>
#include <AknSettingCache.h>
#include <aknsgcc.h>
#include <aknshortcuts.h>

#include <s32mem.h>



// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCDomainTestPopupCase* CBCDomainTestPopupCase::NewL( CBCDomainTestPopupContainer* 
    aContainer )
    {
    CBCDomainTestPopupCase* self = new( ELeave ) CBCDomainTestPopupCase( 
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
CBCDomainTestPopupCase::CBCDomainTestPopupCase( CBCDomainTestPopupContainer* 
    aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCDomainTestPopupCase::~CBCDomainTestPopupCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCDomainTestPopupCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupCase::BuildScriptL()
    { 
    // Add script as your need.   
      AddTestL( DELAY(1), LeftCBA, KeyOK, LeftCBA, Down, KeyOK, LeftCBA, 
          Down, Down, KeyOK, LeftCBA, Down, Down, Down, KeyOK, Down, Up,
          LeftCBA, TEND );   
    }
    
// ---------------------------------------------------------------------------
// CBCDomainTestPopupCase::RunL
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline4 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestFunctionL();
            break;
        case EBCTestCmdOutline2:
            TestOtherL();
            break;
        case EBCTestCmdOutline3:
            TestOtherElseL();
            break;
        case EBCTestCmdOutline4:
            TestLeftL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control 
            // instead of this.
            iControl = new( ELeave ) CCoeControl();            
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCDomainTestPopupCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCDomainTestPopupCase::TestFunctionL()
    {
    // Test some API here
    _LIT( KCAknPopupForm, "CAknPopupForm" );
    _LIT( KSetSizeAndPosition, "SetSizeAndPosition" );
    _LIT( KSetTitleL, "SetTitleL" ); 
    _LIT( KSetTextL, "SetTextL" );
    _LIT( KSetTimeout, "SetTimeout" );
    _LIT( KSetTone, "SetTone" );
    _LIT( KDraw, "draw()" );
    _LIT( KSetPopupFormType, "SetPopupFormType" );
    _LIT( KProgressInfo, "ProgressInfo" );
    _LIT( KSetCallback, "SetCallback" );
    _LIT( KIncrementProgressBarAndDraw, "IncrementProgressBarAndDraw" );
    _LIT( KSetProgressBarAndDraw, "SetProgressBarAndDraw" );
    _LIT( KGetControlByControlType, "GetControlByControlType" );
    _LIT( KSetImageL, "SetImageL" );
    _LIT( KHandleResourceChange, "HandleResourceChange" );
    _LIT( KTextIsScrollable, "TextIsScrollable" );
    _LIT( KFlags, "Flags" );
    _LIT( KGetControlByControlTypeL, "GetControlByControlTypeL" );
    _LIT( KDeleteControl, "DeleteControl" );
    _LIT( KCAknPopupFormDestroy, "KCAknPopupFormDestroy" );
            
    CAknPopupForm* popform = new ( ELeave ) CAknPopupForm();
    AssertNotNullL( popform,KCAknPopupForm  );
    delete popform;
    popform = NULL;
       
    TTone ttone = ENoTone;
    TInt  ttimeout = 3000;
    TPopupFormType ttype = EAknQuery;
    
    popform = CAknPopupForm::NewL();
    CleanupStack::PushL( popform );
    AssertNotNullL( popform, KCAknPopupForm );
    CleanupStack::PopAndDestroy();
    popform = NULL;
    
    popform = CAknPopupForm::NewLC( ttone );
    AssertNotNullL( popform, KCAknPopupForm );
    CleanupStack::PopAndDestroy();
    popform = NULL;
    
    popform = CAknPopupForm::NewL( ttone );    
    CleanupStack::PushL( popform );
    AssertNotNullL( popform, KCAknPopupForm );
    CleanupStack::PopAndDestroy();
    popform = NULL;
    
    popform = CAknPopupForm::NewLC();
    AssertNotNullL( popform, KCAknPopupForm );
    CleanupStack::PopAndDestroy();
    popform = NULL;
    
    popform = new ( ELeave ) CAknPopupForm( ttone, ttimeout, ttype );
    AssertNotNullL( popform, KCAknPopupForm );   
    popform->PrepareLC( R_BCTESTPOPUPS_ATTRIB_SET_DIALOG );

    TSize tsize;
    popform->SetSizeAndPosition( tsize );
    AssertTrueL( ETrue, KSetSizeAndPosition );
    
    _LIT( KTitle,"title" );    
    popform->SetTitleL( KTitle );
    AssertTrueL( ETrue, KSetTitleL );
    
    TBuf<32> *ttxt = NULL;  
    popform->SetTextL( ttxt );
    AssertTrueL( ETrue, KSetTextL );
    popform->SetTimeout( 0 );
    AssertTrueL( ETrue, KSetTimeout );
    popform->SetTone( ttone );
    AssertTrueL( ETrue, KSetTone );
    popform->SetPopupFormType( ttype );
    AssertTrueL( ETrue, KSetPopupFormType );
    popform->ProgressInfo();
    AssertTrueL( ETrue, KProgressInfo );
    MPopupFormProgressCallback* callback = NULL;
    popform->SetCallback( callback );   
    AssertTrueL( ETrue, KSetCallback );
    
    TInt tinc = 10;
    popform->IncrementProgressBarAndDraw( tinc );
    AssertTrueL( ETrue, KIncrementProgressBarAndDraw );
    popform->SetProgressBarAndDraw( tinc );
    AssertTrueL( ETrue, KSetProgressBarAndDraw  );
    popform->GetControlByControlType( 1 );
    AssertTrueL( ETrue, KGetControlByControlType );
    CEikImage* timage = NULL;
    popform->SetImageL( timage );
    AssertTrueL( ETrue, KSetImageL );
    popform->HandleResourceChange( 0 ); 
    AssertTrueL( ETrue, KHandleResourceChange );
    popform->TextIsScrollable();
    AssertTrueL( ETrue, KTextIsScrollable );
    popform->Flags();
    AssertTrueL( ETrue, KFlags );
    
    popform->GetControlByControlTypeL( EPopupFormUnknown );
    AssertTrueL( ETrue, KGetControlByControlTypeL );
   
    popform->DeleteControl( EPopupFormUnknown );
    AssertTrueL( ETrue, KDeleteControl );   
    
    popform->DrawNow();
    AssertTrueL( ETrue, KDraw );
    
    CleanupStack::PopAndDestroy( popform );
    AssertTrueL( ETrue, KCAknPopupFormDestroy );
    popform = NULL;
     
    }
// ---------------------------------------------------------------------------
// CBCDomainTestPopupCase::TestOtherL
// ---------------------------------------------------------------------------
//    

void  CBCDomainTestPopupCase::TestOtherL()
    {
    //  aknsgcc.h
    _LIT( KPrepareForAppExit, "PrepareForAppExit" ); 
    _LIT( KHandleChangeL, "HandleChangeL" );
    _LIT( KAknSrv, "AknSrv" ); 
    _LIT( KBlockServerStatusPaneRedrawsL, "BlockServerStatusPaneRedrawsL" );
    _LIT( KRedrawServerStatusPane, "RedrawServerStatusPane" );
    _LIT( KCreateL, "CreateL" );
    _LIT( KScreenMode, "KScreenMode" );
    _LIT( KCalculateScreenMode, "KCalculateScreenMode" );
    _LIT( KDrawSynchronizer, "DrawSynchronizer" );
    _LIT( KSetSystemFaded, "SetSystemFaded" ); 
    _LIT( KPixelsAndRotation, "PixelsAndRotation" );
    _LIT( KCalculatePixelsAndRotation, "CalculatePixelsAndRotation" ); 
    _LIT( KSetKeyBlockMode, "SetKeyBlockMode" ); 
    _LIT( KSetKeyboardRepeatRate, "SetKeyboardRepeatRate" );
    _LIT( KCurrentStatuspaneResource, "CurrentStatuspaneResource" ); 
    _LIT( KLayoutConfig, "LayoutConfig" );
    _LIT( KLayoutConfigBuf, "LayoutConfigBuf" );
    _LIT( KIsSystemFaded, "KIsSystemFaded" );
        
    CAknSgcClient::CreateL();
    AssertTrueL( ETrue, KCreateL );
	CAknSgcClient::HandleChangeL();
	AssertTrueL( ETrue, KHandleChangeL );
	CAknSgcClient::AknSrv();
	AssertTrueL( ETrue, KAknSrv );

    //MAknSgcStatusPaneRedrawCoordinator* pSpRedrawCoord = NULL;
	//CAknSgcClient::SetStatusPaneRedrawCoordinator( pSpRedrawCoord);
	//delete pSpRedrawCoord; mem leak
	 
	CAknSgcClient::PrepareForAppExit();
	AssertTrueL( ETrue, KPrepareForAppExit ); 
	CAknSgcClient::BlockServerStatusPaneRedrawsL();
	AssertTrueL( ETrue, KBlockServerStatusPaneRedrawsL );
	CAknSgcClient::RedrawServerStatusPane();
    AssertTrueL( ETrue, KRedrawServerStatusPane );
	CAknSgcClient::DrawSynchronizer();
    AssertTrueL( ETrue, KDrawSynchronizer );
	 
	CAknSgcClient::SetSystemFaded( EFalse );
	AssertTrueL( ETrue, KSetSystemFaded );
	CAknSgcClient::IsSystemFaded();
	AssertTrueL( ETrue, KIsSystemFaded );
	CAknSgcClient::PixelsAndRotation();
	AssertTrueL( ETrue, KPixelsAndRotation );
	CAknSgcClient::CalculatePixelsAndRotation( EFalse, EFalse, EFalse, EFalse );
	AssertTrueL( ETrue, KCalculatePixelsAndRotation );
	CAknSgcClient::ScreenMode();
	AssertTrueL( ETrue, KScreenMode );
	CAknSgcClient::CalculateScreenMode( EFalse, EFalse, EFalse );
	AssertTrueL( ETrue, KCalculateScreenMode );
	 
    
    AssertTrueL( ETrue, KCalculateScreenMode );
    CAknSgcClient::SetKeyBlockMode( EEnableKeyBlock );
    AssertTrueL( ETrue, KSetKeyBlockMode );
    CAknSgcClient::SetKeyboardRepeatRate( EAknApplicationDefaulRepeatRate );
    AssertTrueL( ETrue, KSetKeyboardRepeatRate );
    CAknSgcClient::CurrentStatuspaneResource();
    AssertTrueL( ETrue, KCurrentStatuspaneResource );
    CAknSgcClient::LayoutConfig();
    AssertTrueL( ETrue, KLayoutConfig );
    CAknSgcClient::LayoutConfigBuf();
    AssertTrueL( ETrue, KLayoutConfigBuf );
    
    //  aknshortcuts.h
    _LIT( KCTextlstboxModel, "CTextlstboxModel" ); 
    _LIT( KCTextListItemDrawer, "CTextListItemDrawer" ); 
    _LIT( KConstructL, "ConstructL" ); 
    _LIT( KRunL, "RunL()" ); 
    _LIT( KShortcutValueForNextList, "ShortcutValueForNextList" ); 
    _LIT( KSetShortcutValueFromPrevList, "SetShortcutValueFromPrevList" );
    _LIT( KProcessCommandL, "ProcessCommandL" ); 
    _LIT( KOfferKeyEventL, "OfferKeyEventL" ); 
    _LIT( KRecursionLock, "RecursionLock" ); 
    _LIT( KRecursionUnlock, "RecursionUnlock" );
    _LIT( KStartTimerL, "StartTimerL" ); 

    CDesCArray* txtarray = CEikonEnv::Static()->ReadDesCArrayResourceL( 
        R_BCTESTLIST_ITEM_SINGLE1 );
    CleanupStack::PushL( txtarray );    
    
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();    
    AssertNotNullL( model, KCTextlstboxModel );
    CleanupStack::PushL( model );
    model->ConstructL( txtarray );
    AssertTrueL( ETrue, KConstructL );
    
    CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer();
    AssertNotNullL( drawer, KCTextListItemDrawer );
    CleanupStack::PushL( drawer );
    drawer->ConstructL( CEikonEnv::Static()->NormalFont() );
    
    CEikListBox* lstbox = new( ELeave ) CEikListBox();
    AssertNotNullL( lstbox, KCTextListItemDrawer );
    CleanupStack::PushL( lstbox );    
    
    
    TGulBorder border( TGulBorder::ESingleGray );
    lstbox->ConstructL( model, drawer, iContainer, border, 
        EAknListBoxSelectionList | EAknListBoxViewerFlags );    
    AssertTrueL( ETrue, KCTextListItemDrawer );
    
    CBCListBoxCuts* lstboxcuts = new ( ELeave ) CBCListBoxCuts( lstbox );
    CleanupStack::PushL( lstboxcuts );
    AssertNotNullL( lstboxcuts, KCTextListItemDrawer );
     
    lstboxcuts->ConstructL();
    AssertTrueL( ETrue, KCTextListItemDrawer );
    lstboxcuts->DoTest( CBCListBoxCuts::ENewItemFocused );
    AssertTrueL( ETrue, KCTextListItemDrawer );
    lstboxcuts->DoActionL( CBCListBoxCuts::EAssertNotFetched );
    AssertTrueL( ETrue, KCTextListItemDrawer );
    lstboxcuts->ShortcutValueForNextList();
    AssertTrueL( ETrue, KShortcutValueForNextList );
    
    TInt tvalue = 0;
    lstboxcuts->SetShortcutValueFromPrevList( tvalue );
    AssertTrueL( ETrue, KSetShortcutValueFromPrevList );
    lstboxcuts->ProcessCommandL( tvalue );
    AssertTrueL( ETrue, KProcessCommandL );
    
    CBCShortCutsImp* lstimp = new ( ELeave )
        CBCShortCutsImp( lstbox );
        
    //TTypeUid ttypeid = 0;
    //stimp->MopSupplyObject( ttypeid ); //not implement
    delete lstimp;
    
    TKeyEvent keyEvent = { EKeyEnter, EStdKeyEnter, 0, 0  };
    lstboxcuts->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );
    
    lstboxcuts->RecursionLock();
    AssertTrueL( ETrue, KRecursionLock );
    lstboxcuts->RecursionUnlock();
    AssertTrueL( ETrue, KRecursionUnlock );
    
    lstboxcuts->StartTimerL( CBCListBoxCuts::EShortcutActiveTimeout );
    AssertTrueL( ETrue, KStartTimerL );
    lstboxcuts->RunL();
    AssertTrueL( ETrue, KRunL );
    
    CleanupStack::PopAndDestroy( lstboxcuts );
    CleanupStack::PopAndDestroy( lstbox );
    CleanupStack::Pop( drawer );
    CleanupStack::Pop( model );
    CleanupStack::Pop( txtarray );
    }
    
// ---------------------------------------------------------------------------
// CBCDomainTestPopupCase::TestOtherElseL
// ---------------------------------------------------------------------------
//    

void  CBCDomainTestPopupCase::TestOtherElseL()
    {
    
    //  aknsctdialog.h 
    _LIT( KCAknCharMapDialog, "CAknCharMapDialog" ); 
    _LIT( KShowNoPictographs, "ShowNoPictographs" );
    _LIT( KShowPictographsFirst, "ShowPictographsFirst" ); 
    _LIT( KHandleDialogPageEventL, "HandleDialogPageEventL" ); 
    _LIT( KHandleResourceChange, "HandleResourceChange" );
    _LIT( KDisableRecentCharsRow, "DisableRecentCharsRow" ); 
    _LIT( KLockNumericKeys, "LockNumericKeys" ); 
    _LIT( KShowAnotherTable, "ShowAnotherTable" ); 
    _LIT( KKCAknCharMapDialogDestroy, "KKCAknCharMapDialogDestroy" );    
    
                
    _LIT( tmp,"specialchars" );
    TBuf<32> specialchars( tmp );
	CAknCharMapDialog* mapdlg = new ( ELeave ) 
	    CAknCharMapDialog( EAknSCTLowerCase, specialchars, 
	    R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
	AssertNotNullL( mapdlg, KCAknCharMapDialog );
	
	mapdlg->SetContainerWindowL( *iContainer );
    
	mapdlg->ShowNoPictographs();
	AssertTrueL( ETrue, KShowNoPictographs );
	
    mapdlg->ShowPictographsFirst();
    AssertTrueL( ETrue, KShowPictographsFirst );
        	 	  
	mapdlg->HandleDialogPageEventL( MEikDialogPageObserver::EUnknownType );
    AssertTrueL( ETrue, KHandleDialogPageEventL );
    
    mapdlg->HandleResourceChange( 1 );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    mapdlg->DisableRecentCharsRow();	 
    AssertTrueL( ETrue, KDisableRecentCharsRow );
    
    mapdlg->LockNumericKeys( ETrue );
    AssertTrueL( ETrue, KLockNumericKeys );
    
	mapdlg->ShowAnotherTable( R_AVKON_SPECIAL_CHARACTER_TABLE_DIALOG );
	AssertTrueL( ETrue, KShowAnotherTable );
	 	
    delete mapdlg;
    AssertTrueL( ETrue, KKCAknCharMapDialogDestroy );
    
    _LIT( KCAknSDData, "CAknSDData" );
    _LIT( KExternalizeL, "ExternalizeL" ); 
    _LIT( KInternalizeL, "InternalizeL" );
    _LIT( KCreateLC, "CreateLC()" );
    _LIT( KInsertGlobalListQueryItemIdsL, "InsertGlobalListQueryItemIdsL" );
        
    TInt pDialogIndex = R_AVKON_SPECIAL_CHARACTER_TABLE_DIALOG;
    _LIT8(pAdditionalData, "addData" );
    TBuf8<32> pData( pAdditionalData );
    
    CAknSDData* sdata = CAknSDData::NewL( KUidBCTestDomPopup,
         pDialogIndex, pData);
    CleanupStack::PushL( sdata );
    AssertNotNullL( sdata, KCAknSDData );
          
    RStoreWriteStream storewrite;
    CBufStore* store = CBufStore::NewLC( 1024 );     
    TStreamId steamid = storewrite.CreateLC( *store );    
    AssertTrueL( ETrue, KCreateLC );
    
    sdata->ExternalizeL( storewrite );
    AssertTrueL( ETrue, KExternalizeL ); 
    CleanupStack::PopAndDestroy();     
     
    RStoreReadStream  rdstream;
    rdstream.OpenLC( *store, steamid );
     
    sdata->InternalizeL( rdstream );
    AssertTrueL( ETrue, KInternalizeL );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy();
     
    RArray<TInt> idarray;
    sdata->InsertGlobalListQueryItemIdsL( idarray );
    AssertTrueL( ETrue, KInsertGlobalListQueryItemIdsL );
    CleanupStack::PopAndDestroy( sdata );
     
    // AknSettingCache.h
    _LIT( KSettingCache, "SettingCache" ); 
    _LIT( KRegisterPluginL, "RegisterPluginL" ); 
    _LIT( KDeRegisterPlugin, "DeRegisterPlugin" ); 
    
    CAknSettingCache& setcache = CAknEnv::Static()->SettingCache();
    setcache.Update( EStdKeyNull );
    AssertTrueL( ETrue, KSettingCache );
      
    MAknSettingCacheUpdatePlugin* tplugin = NULL;
    setcache.RegisterPluginL( tplugin );
    AssertTrueL( ETrue, KRegisterPluginL );
    setcache.DeRegisterPlugin( tplugin );
    AssertTrueL( ETrue, KDeRegisterPlugin );
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupCase::TestLeftL
// ---------------------------------------------------------------------------
//     
void CBCDomainTestPopupCase::TestLeftL()
    {
    _LIT( KCBCPopupForm, "CBCPopupForm" ); 
    _LIT( KSetWaitAnimationResourceIndex, "SetWaitAnimationResourceIndex" ); 
    _LIT( KLayoutAndDraw, "LayoutAndDraw" );
    _LIT( KPlayTone, "PlayTone" ); 
    _LIT( KSoundSystem, "SoundSystem" ); 
    _LIT( KPostLayoutDynInitL, "PostLayoutDynInitL" );
    _LIT( KOfferKeyEventL, "OfferKeyEventL" );
    _LIT( KHandlePointerEventL, "HandlePointerEventL" );
    _LIT( KStaticDeleteL, "StaticDeleteL" );
    _LIT( KOkToExitL, "OkToExitL" );
    _LIT( KExecuteLD, "ExecuteLD" );
    _LIT( KCAknPopupForm, "KCaknPopuopForm()" );
    _LIT( KActivateL," ActivageL()" );
    _LIT( KInsertControlL, "InsertControlL" );
    _LIT( KDeleteControl, "DeleteControl" );
    _LIT( KRunLD, "KRunLD" );
    _LIT( KProcessFinishedL, " KProcessFinishedL " );
    
    CBCPopupForm* popform = CBCPopupForm::NewL();
    AssertNotNullL( popform, KCBCPopupForm );
    popform->PrepareLC( R_BCTESTPOPUPS_DIALOG );    
    AssertTrueL( ETrue, KCBCPopupForm );
    
    CAknPopupForm* tform = new ( ELeave ) CAknPopupForm(); 
    AssertNotNullL( tform, KCAknPopupForm );
    
    popform->StaticDeleteL( tform );
    AssertTrueL( ETrue, KStaticDeleteL );
    popform->OkToExitL( R_BCTESTPOPUPS_DIALOG );
    AssertTrueL( ETrue, KOkToExitL );
    popform->InsertControlL( 0, R_BCTESTPOPUP_DLG_LINE );
    AssertTrueL( ETrue, KInsertControlL ); 
   
    popform->DeleteControl( EAknCtPopupField );
    AssertTrueL( ETrue, KDeleteControl );   

    popform->RunLD();
    AssertTrueL( ETrue, KRunLD );
    
    popform->ActivateL();
    AssertTrueL( ETrue, KActivateL );
    
    popform->LayoutAndDraw();  
    AssertTrueL( ETrue, KLayoutAndDraw );
    
    popform->PlayTone();
    AssertTrueL( ETrue, KPlayTone );
    
    popform->SoundSystem();
    AssertTrueL( ETrue, KSoundSystem );
  
    popform->PostLayoutDynInitL();
    AssertTrueL( ETrue, KPostLayoutDynInitL );
    
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };
    popform->OfferKeyEventL(keyEvent, EEventNull );
    AssertTrueL( ETrue, KOfferKeyEventL );
    
    TPointerEvent tevent;
    tevent.iType = TPointerEvent::EButton1Down;
    popform->HandlePointerEventL( tevent );
    AssertTrueL( ETrue, KHandlePointerEventL  );

    popform->SetWaitAnimationResourceIndex( -1 );
    AssertTrueL( ETrue, KSetWaitAnimationResourceIndex );
    
    popform->ProcessFinishedL();          
    AssertTrueL( ETrue, KProcessFinishedL );
    
    _LIT( tmp,"specialchars" );
    TBuf<32> specialchars( tmp );

    CBCTestCharMapDlg* charmapdlg = new ( ELeave ) CBCTestCharMapDlg( 
         EAknSCTUpperCase, specialchars );
	charmapdlg->ExecuteLD( R_AVKON_URL_SPECIAL_CHARACTER_TABLE_DIALOG );
	_LIT( KHandleControlEventL, " CAknCharMapDialog::HandleControlEventL() " );
	AssertTrueL( ETrue, KOkToExitL );	
	AssertTrueL( ETrue, KHandleControlEventL );	
	AssertTrueL( ETrue, KExecuteLD );	

    }
//end of file
 
