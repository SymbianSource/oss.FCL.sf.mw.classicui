/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
#include <barsread.h>
#include <eiklbbut.h>
#include <eikcmbut.h>
#include <aknbitmapanimation.h>
#include <eikcba.h>
#include <S32FILE.H>
#include <eikenv.h>
#include <eikbtgps.h>
#include <avkon.hrh>
#include <eikcmobs.h>
#include <eikbgfty.h>
#include <aknchoicelist.h>
#include <caknmemoryselectionsettingpage.h>
#include <CommonDialogs.rsg> // Common dialogs resource IDs
#include <caknmemoryselectionsettingitemmultidrive.h>
#include <caknmemoryselectiondialogmultidrive.h>
#include <caknfilenamepromptdialog.h>
#include <akncommondialogsdynmem.h>
#include <documenthandler.h>
#include <maknfileselectionobserver.h>
#include <aknfontaccess.h>
#include <AknColourSelectionGrid.h>
#include <aknsinglecolumnstyletreelist.h>
#include <aknsinglestyletreelist.h>
#include <avkon.mbg>
#include <aknsconstants.h>
#include <eikhkeyt.h>
#include <aknindicatorcontainer.h>
#include <akninfrm.h>
#include <eikedwin.h>
#include <eikfnlab.h>
#include <eikctlib.h>
#include <akninputlanguageinfo.h>
#include <aknnotedialog.h>
#include <aknnavide.h>
#include <aknpopupnotify.h>
#include <aknpopupsettingpage.h>
#include <aknpopuplayout.h>
#include <aknpopup.h>
#include <eikhfdlg.h>
#include <eikbtpan.h>
#include <aknquerydialog.h>
#include <aknclearer.h>
#include <aknsfld.h>
#include <S32MEM.H>
#include <aknsoundsystem.h>
#include <akntitle.h>
#include <akncommondialogs.h>
#include <akntoolbar.h>
#include <akntouchpane.h>
#include <aknlayoutfont.h>
#include <hwrmhaptics.h>
#include <AknsLayeredBackgroundControlContext.h>
#include <AknsImageAttributeData.h>
#include <aknappui.h>
#include <AknsItemDef.h>
#include <gdi.h>
#include <AknsListBoxBackgroundControlContext.h>
#include <AknsFrameBackgroundControlContext.h>
#include <AknStaticNoteDialog.h>
#include <aknmessagequerydialog.h>
#include <Aknedsts.h>
#include <AknIconArray.h>

#include <bctestmix50.rsg>
#include "bctestmix50patchcontrolcase.h"
#include "bctestmix50patchmisc.h"
#include "bctestmix50container.h"
#include "bctestmix50.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMix50PatchControlCase* CBCTestMix50PatchControlCase::NewL( CBCTestMix50Container* 
    aContainer )
    {
    CBCTestMix50PatchControlCase* self = new( ELeave ) CBCTestMix50PatchControlCase( 
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
CBCTestMix50PatchControlCase::CBCTestMix50PatchControlCase( CBCTestMix50Container* 
    aContainer )
    : iContainer( aContainer )
    {    
    iCoeEnv = CCoeEnv::Static();
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMix50PatchControlCase::~CBCTestMix50PatchControlCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(5), LeftCBA, Down, Down, LeftCBA, RightCBA, 
              RightCBA, RightCBA, RightCBA, RightCBA, RightCBA,
              RightCBA, RightCBA, RightCBA, RightCBA, RightCBA,
              RightCBA, RightCBA, RightCBA, RightCBA, RightCBA,
              RightCBA, RightCBA, RightCBA, RightCBA, RightCBA,
              RightCBA, RightCBA, RightCBA, RightCBA, RightCBA,
              RightCBA, RightCBA, RightCBA, RightCBA, RightCBA,
              RightCBA, RightCBA,
              TEND );
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::RunL( TInt aCmd )
    {
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )  
        {
        case EBCTestCmdOutline3:
            TestAnimationL();
            TestButtonsL();
            TestChoiceListL();
            TestCommonFileL();
        	TestSelectCommonFileL();
        	TestSaveCommonFileL();
            TestDocumentHandlerL();
            TestFontsL();
            TestGridsL();
            TestHListsAndHotkeysL();
            TestMiscellOneL();
            TestInitializationL();
            TestInputLanL();
            TestMenusL();
            TestNotesL();
            TestMiscellTwoL();
            TestPopupsL();
            TestUIFrmL();
            TestQueriesL();
            TestScrollerL();
            TestSearchfieldL();
            TestSettingPagesL();
            TestTitlePaneL();            
            TestAknToolbarL();
            TestAknTouchPaneL();
        	TestHapticsL();
        	TestImageTableItemDataL();
        	TestMBmpItemDataL();
        	TestColTableItemDataL();
        	TestBackgroundCCL();
        	TestAknLayoutUtilsL();
        	TestAknsUtilsL();
        	TestAknsDrawUtilsL();
        	TestDialogsL();
        	TestPopupL();
        	TestStatesL();
        	TestIpFieldEditorL();
        	TestIconArrayL();
            TestAknVolumeControlL();
            TestAknEnvL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::PrepareCaseL( TInt aCmd )
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
    // Pass the owner of iControl to iContainer.s
    iContainer->SetControlL( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestMix50PatchControlCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestAnimationL
// ---------------------------------------------------------------------------
//    
void CBCTestMix50PatchControlCase::TestAnimationL()
    {
    // Test bitmap animation api
    _LIT( KStrExcludeAnimationFrames, 
          "CAknBitmapAnimation::ExcludeAnimationFramesFromCache() invoked " );
    _LIT( KStrSetScaleModeForAnimationBackgroundFrame, 
          "SetScaleModeForAnimationBackgroundFrame() invoked" );
    
    CAknBitmapAnimation* ani= CAknBitmapAnimation::NewL();
    CleanupStack::PushL(ani);

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, 
            R_BCTEST_BMPANIM_DATA_ORG );
    ani->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();
    
    ani->SetScaleModeForAnimationBackgroundFrame( EAspectRatioNotPreserved );
    AssertTrueL( ETrue, KStrSetScaleModeForAnimationBackgroundFrame );
    
    ani->ExcludeAnimationFramesFromCache();
    AssertTrueL( ETrue, KStrExcludeAnimationFrames );
    CleanupStack::PopAndDestroy( ani );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestButtonsL
// ---------------------------------------------------------------------------
//    
void CBCTestMix50PatchControlCase::TestButtonsL()
    {
    // Test the button apis
    _LIT( KDrawNow, 
          "CEikCommandButtonBase::Draw() invoked" );
    _LIT( KButBaseWriteInternalStateL, 
          "CEikButtonBase::WriteInternalStateL() invoked" );
    _LIT( KDimCommandByPosition, 
          "CEikButtonGroupContainer::DimCommandByPosition() invoked");
    _LIT( KIsCommandDimmedByPosition, 
          "CEikButtonGroupContainer::IsCommandDimmedByPosition() invoked" );
    _LIT( KAnimateCommandByPosition, 
          "CEikButtonGroupContainer::AnimateCommandByPosition() invoked" );
    _LIT( KAnimateCommand, 
          "MEikButtonGroup::AnimateCommand() invoked");
    _LIT( KLbbutWriteInternalStateL, 
          "CEikLabeledButton::WriteInternalStateL() invoked");
    _LIT( KOfferCommandListL, 
          "CEikButtonGroupContainer::OfferCommandListL( array ) invoked" );
    _LIT( KOfferCommandListResL, 
          "CEikButtonGroupContainer::OfferCommandListL( resource ) invoked" );
    _LIT( KMEikOfferCommandListL, 
          "MEikEnhancedButtonGroup::OfferCommandListL( array ) invoked ");
    _LIT( KIsCommandInGroup, 
          "MEikEnhancedButtonGroup::IsCommandInGroup" );
    _LIT( KReplaceCommand, 
          "MEikEnhancedButtonGroup::ReplaceCommand" );
    
    CBCTestCommandButtonBase* cmdButtonBase = 
    		CBCTestCommandButtonBase::NewL();
    CleanupStack::PushL( cmdButtonBase );
    cmdButtonBase->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_BCTEST_CMDBT_LABEL );
    cmdButtonBase->ConstructLabelFromResourceL( 
            reader, CEikCommandButtonBase::EFirst );

    cmdButtonBase->ActivateGc();
    cmdButtonBase->Draw( iContainer->Rect() );
    cmdButtonBase->DeactivateGc();
    AssertTrueL( ETrue, KDrawNow );
    
    _LIT( KStreamName, "c:\\BCTestLog\\buttontest.txt" );
    RFs& tempServer = CEikonEnv::Static()->FsSession();
    tempServer.Delete( KStreamName );
    RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer,
            KStreamName, EFileWrite ) );
    CleanupClosePushL( fWrite );
    cmdButtonBase->WriteInternalStateL( fWrite );
    AssertTrueL( ETrue, KButBaseWriteInternalStateL );
    
    AssertTrueL( ETrue, KLbbutWriteInternalStateL);
    CleanupStack::PopAndDestroy( &fWrite );
    CleanupStack::PopAndDestroy(); // reader
    CleanupStack::PopAndDestroy( cmdButtonBase );

    CEikButtonGroupContainer* currentBtGrp = 
                    CEikButtonGroupContainer::Current();
    currentBtGrp->DimCommandByPosition( 
            CEikButtonGroupContainer::ELeftSoftkeyPosition, EFalse );
    AssertTrueL( ETrue, KDimCommandByPosition );
    
    currentBtGrp->MakeCommandVisibleByPosition( 
            CEikButtonGroupContainer::ELeftSoftkeyPosition, ETrue );
    
    currentBtGrp->IsCommandDimmedByPosition( 
            CEikButtonGroupContainer::ELeftSoftkeyPosition );
    AssertTrueL( ETrue,KIsCommandDimmedByPosition );
    
    currentBtGrp->AnimateCommandByPosition( 
            CEikButtonGroupContainer::ELeftSoftkeyPosition );
    AssertTrueL( ETrue, KAnimateCommandByPosition );
    
    
    TInt toolbarresourceid = R_BCTESTMIX50PATCH_CBA_OPTIONS_NEXT;
    TInt commandid = EAknSoftkeyOptions;
    currentBtGrp->AnimateCommand( commandid );
    AssertTrueL( ETrue, KAnimateCommand );
        
    RArray<TInt> arr;
    arr.Append( commandid );
    //TRAP( res, eikcba->OfferCommandListL( arr ) );
    currentBtGrp->OfferCommandListL( arr );
    AssertTrueL( ETrue, KOfferCommandListL );
    AssertTrueL( ETrue, KMEikOfferCommandListL );
    arr.Close();
        
    currentBtGrp->IsCommandInGroup( commandid );
    AssertTrueL( ETrue, KIsCommandInGroup );
    currentBtGrp->ReplaceCommand( commandid, toolbarresourceid );
    AssertTrueL( ETrue, KReplaceCommand );
       
    currentBtGrp->OfferCommandListL( commandid );
    AssertTrueL( ETrue, KOfferCommandListResL );
    
    currentBtGrp->MakeCommandVisibleByPosition( 
            CEikButtonGroupContainer::ELeftSoftkeyPosition, ETrue );
    
    TInt resourceId = R_BCTESTMIX50PATCH_CASE_MENU;

    RWindowGroup& parentWg = CCoeEnv::Static()->RootWin();
    TUint btgroupflags = 0;

    EikButtonGroupFactory::TCreationData creationData(
            CEikButtonGroupContainer::EView, this,
            resourceId, &parentWg, btgroupflags,
            CEikButtonGroupContainer::EVertical );
    _LIT( KTCreationData, "TCreationData test" );
    AssertTrueL( ETrue, KTCreationData );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestChoiceListL()
//  ChoiceListL test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestChoiceListL()
    {
    _LIT(KHandlePointerEvent, "CAknChoiceList::HandlePointerEvent() invoked");
    
    CDesCArrayFlat* itemArray = new ( ELeave ) CDesCArrayFlat( 8 );
    CleanupStack::PushL( itemArray );
    itemArray->AppendL( _L("orking") );
    itemArray->AppendL( _L("ll") );
    itemArray->AppendL( _L("sti") );
    itemArray->AppendL( _L("w") );
    CBCTestChoiceList *choiceList =static_cast<CBCTestChoiceList*> 
            ( CAknChoiceList::NewL( iContainer, itemArray,
                    CAknChoiceList::EAknChoiceListWithCurrentSelection ) );
    CleanupStack::PushL( choiceList );
    TPointerEvent pointerEvent;
    pointerEvent.iType  = TPointerEvent::EButton1Up ;
    choiceList->HandlePointerEventL( pointerEvent );
    AssertTrueL( ETrue, KHandlePointerEvent );
    
    CleanupStack::PopAndDestroy( choiceList );
    CleanupStack::Pop( itemArray );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestCommonFileL()
//  common file test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestCommonFileL()
    {
    _LIT( KSetTitleL, 
          "CAknMemorySelectionDialogMultiDrive::SetTitleL() invoked" );
    _LIT( KSetLeftSoftkeyL, 
          "CAknMemorySelectionDialogMultiDrivef::SetLeftSoftkeyL() invoked" );
    _LIT( KSetRightSoftkeyL, 
          "CAknMemorySelectionDialogMultiDrive::SetRightSoftkeyL() invoked" );
    _LIT( KGetItem, 
          "CAknMemorySelectionDialogMultiDrive::GetItem() invoked" );
    _LIT( KExecute1, 
          "CAknMemorySelectionDialogMultiDrive::ExecuteL1()invoked" );
    _LIT( KExecute2, 
          "CAknMemorySelectionDialogMultiDrive::ExecuteL2() invoked" );
    _LIT( KRunDlgLD13, 
          "CAknMemorySelectionDialogMultiDrive::RunDlgLD1()inovked" );
    _LIT( KRunDlgLD14, 
          "CAknMemorySelectionDialogMultiDrive::RunDlgLD2()invoked" );
    _LIT( KRunDlgLD15, 
          "CAknMemorySelectionDialogMultiDrive::RunDlgLD3()invoked" );
    _LIT( KRunDlgLD16, 
          "CAknMemorySelectionDialogMultiDrive::AddDrivePathsL()invoked" );
    _LIT( KCAknMemorySelectionSettingItemMultiDriveDes, 
          "~CAknMemorySelectionSettingItemMultiDrive()invoked");
    _LIT( KMultiDriveNewL1, 
          "CAknMemorySelectionDialogMultiDrive::NewL()1 invoked" );
    _LIT( KMultiDriveNewL2, 
          "CAknMemorySelectionDialogMultiDrive::NewL()2 invoked" );
    _LIT( KCAknMemorySelectionSettingItemMultiDrive, 
          "CAknMemorySelectionSettingItemMultiDrive() invoked");
    _LIT( KCompleteConstructionL, 
          "CAknMemorySelectionSettingItemMultiDrive::CompleteConstructionL(");
    _LIT( KSettingTextL, 
          "CAknMemorySelectionSettingItemMultiDrive::SettingTextL() invoked");
    _LIT( KLoadL, 
          "CAknMemorySelectionSettingItemMultiDrive::LoadL()invoked");
    _LIT( KStoreL, 
          "CAknMemorySelectionSettingItemMultiDrive::StoreL()invoked");
    
    TDriveNumber aSelDr = EDriveC;
    
    CAknMemorySelectionSettingItemMultiDrive* memSelection = 
            new ( ELeave ) CAknMemorySelectionSettingItemMultiDrive( 
            		R_BCTEST_MIX50PATCH_SETTING_PAGE, aSelDr );
    AssertTrueL( ETrue, KCAknMemorySelectionSettingItemMultiDrive );
    CleanupStack::PushL( memSelection );
    
    memSelection->CompleteConstructionL();
    AssertTrueL( ETrue, KCompleteConstructionL );
    
    memSelection->SettingTextL();
    AssertTrueL( ETrue, KSettingTextL );
    
    memSelection->LoadL();
    AssertTrueL( ETrue, KLoadL );
    
    memSelection->StoreL();
    AssertTrueL( ETrue, KStoreL );
    
    CleanupStack::PopAndDestroy( memSelection );
    AssertTrueL( ETrue, KCAknMemorySelectionSettingItemMultiDriveDes );
    
    TInt includedMedias = 5; 
    TCommonDialogType aDialogDr = ECFDDialogTypeNormal;    
         
    CAknMemorySelectionDialogMultiDrive* memSelDialogMulDriver =
            CAknMemorySelectionDialogMultiDrive::NewL( aDialogDr, ETrue );
    AssertNotNullL( memSelDialogMulDriver, KMultiDriveNewL1 );
    
    CleanupStack::PushL( memSelDialogMulDriver );           
    CleanupStack::PopAndDestroy( memSelDialogMulDriver );
        
    memSelDialogMulDriver = CAknMemorySelectionDialogMultiDrive::NewL( 
            aDialogDr, 0, EFalse, includedMedias );
    AssertNotNullL( memSelDialogMulDriver, KMultiDriveNewL2 );
    CleanupStack::PushL( memSelDialogMulDriver );           
       
    _LIT( tTxt, "Selection dialog title" );
    TBuf<16> aDefaultFolder( _L("c:\\") );
    TBuf<16> aRootPath( _L("d:\\") );
    TBuf<KMaxFileName> rText;
        
    memSelDialogMulDriver->SetTitleL( tTxt );
    AssertTrueL( ETrue, KSetTitleL );
        
    memSelDialogMulDriver->SetLeftSoftkeyL( _L("OK") );
    AssertTrueL( ETrue, KSetLeftSoftkeyL );
        
    memSelDialogMulDriver->SetRightSoftkeyL( _L("Cancel") );
    AssertTrueL( ETrue, KSetRightSoftkeyL );
        
    memSelDialogMulDriver->GetItem( 0, rText );
    AssertTrueL( ETrue, KGetItem );
        
    memSelDialogMulDriver->ExecuteL( aSelDr );
    AssertTrueL( ETrue, KExecute1); 
        
    memSelDialogMulDriver->ExecuteL( aSelDr, &rText, &aDefaultFolder );
    AssertTrueL( ETrue, KExecute2 );
            
    memSelDialogMulDriver->RunDlgLD( aSelDr );
    AssertTrueL( ETrue, KRunDlgLD13 );
        
    memSelDialogMulDriver->RunDlgLD( aSelDr, aDefaultFolder );
    AssertTrueL( ETrue, KRunDlgLD14 );
        
    memSelDialogMulDriver->RunDlgLD( aSelDr, 0 );
    AssertTrueL( ETrue, KRunDlgLD15 );
        
    memSelDialogMulDriver->AddDrivePathsL( aRootPath, aDefaultFolder );
    AssertTrueL( ETrue, KRunDlgLD16 );
            
    CleanupStack::PopAndDestroy( memSelDialogMulDriver );
    
    TBuf<KMaxFileName> fileName( _L("c:\\data\\testcommonfile.txt") );
    RFile file;
    file.Replace( CCoeEnv::Static()->FsSession(), fileName, EFileWrite );
    file.Close();
    
    CAknFileNamePromptDialog* promptDialog = CAknFileNamePromptDialog::NewL();
    CleanupStack::PushL( promptDialog );
    promptDialog->RenameL( fileName );
    CleanupStack::PopAndDestroy( promptDialog );
    } 

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestSelectCommonFileL()
// common file select api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestSelectCommonFileL()
	{
	_LIT( KTitle, "Common File Test " );
	_LIT( KRunSelectDlgLD, "AknCommonDialogsDynMem::RunSelectDlgLD()invoked");
	
	TBuf<KMaxFileName> folder(_L("c:\\data"));
	TBuf<KMaxFileName> fileName( _L("c:\\data\\testcommonfile.txt") );
	TInt res = R_BCTEST_MIX50PATCH_MEMORY_SELECTION_LOCATIONS;
    
    AknCommonDialogsDynMem::RunSelectDlgLD( 
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            res);
    
    AknCommonDialogsDynMem::RunSelectDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            res,
            KTitle());
    
    MonkFilter filter;
    AknCommonDialogsDynMem::RunSelectDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            res,
            &filter );
    
    AknCommonDialogsDynMem::RunSelectDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            res,
            0 );
    
    AknCommonDialogsDynMem::RunSelectDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            res,
            &filter );
    
    AknCommonDialogsDynMem::RunSelectDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            folder,
            res );    
    
    AknCommonDialogsDynMem::RunSelectDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            folder,
            res,
            &filter );
    
    AknCommonDialogsDynMem::RunSelectDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            folder,
            res,
            0 );
    
    AknCommonDialogsDynMem::RunSelectDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            folder,
            res,
            0,
            KTitle() ); 
    AssertTrueL( ETrue, KRunSelectDlgLD );
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestSaveCommonFileL()
//  Common file save api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestSaveCommonFileL()
	{
	_LIT( KTitle, "Common File Test " );
	_LIT( KRunSaveDlgLD, "AknCommonDialogsDynMem::RunSaveDlgLD()invoked");
	
	TBuf<KMaxFileName> folder(_L("c:\\data"));
	TBuf<KMaxFileName> fileName( _L("c:\\data\\testcommonfile.txt") );
	TInt res = R_BCTEST_MIX50PATCH_MEMORY_SELECTION_LOCATIONS;
	
    AknCommonDialogsDynMem::RunSaveDlgLD( 
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            res);
    
    
    AknCommonDialogsDynMem::RunSelectDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            res,
            KTitle());
    
    MonkFilter filter;
    AknCommonDialogsDynMem::RunSaveDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            res,
            &filter );
    
    AknCommonDialogsDynMem::RunSaveDlgLD(
    		AknCommonDialogsDynMem::EMemoryTypePhone, 
    		fileName,
    		res,
    		KTitle(),
    		KTitle() );
    
    
    AknCommonDialogsDynMem::RunSaveDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            res,
            0 );
    
    AknCommonDialogsDynMem::RunSaveDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            res,
            0, 
            KTitle() );
    
    AknCommonDialogsDynMem::RunSaveDlgLD(
            AknCommonDialogsDynMem::EMemoryTypePhone, 
            fileName,
            folder,
            res,
            0,
            KTitle() ); 
    AssertTrueL( ETrue, KRunSaveDlgLD );
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestDocumentHandlerL()
//  document handler api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestDocumentHandlerL()
    {
    _LIT( KOpenFile1, 
        "CDocumentHandler::OpenFileL(RFile&,TDataType&) invoked" );
    _LIT( KOpenFile2, 
        "CDocumentHandler::OpenFileL(TDesC&,TDataType&) invoked" );
    _LIT( KNewLC1, 
          "CDocumentHandler::NewLC() invoked" );
    _LIT( KNewLC2, 
          "CDocumentHandler::NewLC( CEikProcess* ) invoked" );
    _LIT( KGetProgressiveDownloadAppUidsL,
         "CDocumentHandler::GetProgressiveDownloadAppUidsL() invoked");
    _LIT( KCanHandleProgressivelyL,
         "CDocumentHandler::CanHandleProgressivelyL() invoked");
    
    CDocumentHandler *docHandler = CDocumentHandler::NewLC();
    AssertNotNullL( docHandler, KNewLC1 );
    CleanupStack::PopAndDestroy( docHandler );
    
    CEikProcess* proc = CEikonEnv::Static()->Process();
    docHandler = CDocumentHandler::NewLC( proc );
    AssertNotNullL( docHandler, KNewLC2 );
    
    TDataType dataType;    
    _LIT( KEmbeddedFileName, "C:\\BCTestLog\\DocHandleEmbedded.txt" );
    RFs& fs = CEikonEnv::Static()->FsSession();
    RFile embeddedFile;
    if( embeddedFile.Open( fs, KEmbeddedFileName, 
                           EFileWrite | EFileShareAny ) != KErrNone )
        {
        embeddedFile.Create( fs, KEmbeddedFileName, 
                             EFileWrite | EFileShareAny );
        }
    CleanupClosePushL( embeddedFile );
    _LIT8( KContent, "Content Text" );
    embeddedFile.Write( KContent );
    TInt error;
    error = docHandler->OpenFileL( embeddedFile, dataType );
    AssertIntL( KErrNone, error, KOpenFile1 );
    
    error = KErrNone;
    error = docHandler->OpenFileL( KEmbeddedFileName(), dataType );
    AssertIntL( KErrNone, error, KOpenFile2 );
    
    TUid uid = { 0 };
    docHandler->CanHandleProgressivelyL( dataType, uid );
    AssertTrueL( ETrue, KCanHandleProgressivelyL );
    
    RArray<TInt32> uidList;
    docHandler->GetProgressiveDownloadAppUidsL( uidList );
    CleanupClosePushL( uidList );
    AssertTrueL( ETrue, KGetProgressiveDownloadAppUidsL );
    
    CleanupStack::PopAndDestroy(); // uidList
    CleanupStack::PopAndDestroy(); // embeddedFile
    CleanupStack::PopAndDestroy( docHandler );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestChoiceListL()
//  ChoiceListL test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestFontsL()
    {
    _LIT( KGetFont1, 
         "AknFontAccess::GetFont( CBitmapDevice& , \
         TFontStyle ,TInt, TAknFontFamily ) invoked" );
    _LIT( KGetClosestFont1, 
         "AknFontAccess::GetClosestFont( CBitmapDevice& ,TFontStyle \
         ,TInt, TAknFontFamily ) invoked" );
    _LIT( KGetFont2, 
         "AknFontAccess::GetFont( CBitmapDevice& ,TFontStyle , \
         TInt, TDesC& )  invoked" );
    _LIT( KGetClosestFont2, 
         "AknFontAccess::GetClosestFont( CBitmapDevice& ,TFontStyle , \
         TInt, TDesC& )  invoked" );
    _LIT( KAknLayoutTest1, 
         "AknLayoutUtils::CreateLayoutFontFromSpecificationL( const  \
         TAknFontSpecification&) invoked" );
    _LIT( KAknLayoutTest2, 
          "AknLayoutUtils::CreateLayoutFontFromSpecificationL( const \
          TTypeface&,  const TAknFontSpecification& ) invoked" );
    
    TFontStyle fontStyle( EPostureItalic, EStrokeWeightBold, 
            EPrintPosSuperscript ); 
    const TInt KFontSizeInPixels=12;
    CBitmapDevice* dev = CCoeEnv::Static()->ScreenDevice();
    TInt fontSizeInTwips = dev->VerticalPixelsToTwips( KFontSizeInPixels );
    
    CFont* font =  AknFontAccess::GetFont( *dev, fontStyle, 
            fontSizeInTwips, AknFontAccess::EAknFontFamilySansSerif );
    AssertTrueL( ETrue, KGetFont1 );
    dev->ReleaseFont( font );
    
    font = NULL;
    font =  AknFontAccess::GetClosestFont( *dev, fontStyle, 
                fontSizeInTwips, AknFontAccess::EAknFontFamilySansSerif );
    AssertTrueL( ETrue, KGetClosestFont1 );
    dev->ReleaseFont( font );
    
    TBuf<14> fontName( _L( "courier") );
    font = NULL;
    font = AknFontAccess::GetFont( *dev, fontStyle, 
            fontSizeInTwips, fontName );
    AssertTrueL( ETrue, KGetFont2 );
    dev->ReleaseFont( font );
    
    font = NULL;
    font = AknFontAccess::GetClosestFont( *dev, fontStyle, 
                fontSizeInTwips, fontName );
    AssertTrueL( ETrue, KGetClosestFont2 );
    dev->ReleaseFont( font );
    
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknFontAccess::
        CreateLayoutFontFromSpecificationL( *dev, fontSpec );
    delete layoutFont;
    AssertTrueL( ETrue, KAknLayoutTest1 );
    
    TTypeface typeFace;
    layoutFont = AknFontAccess::CreateLayoutFontFromSpecificationL( *dev, typeFace, fontSpec );
    delete layoutFont;
    AssertTrueL( ETrue, KAknLayoutTest2 );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestGridsL()
//  Grids api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestGridsL()
    {
    _LIT( KHandleControlEventL, 
        " CAknColourSelectionGrid::HandleControlEventL() invoked");
    _LIT( KHandleDialogPageEventL, 
        " CAknColourSelectionGrid::HandleDialogPageEventL() invoked");
    
    CArrayFixFlat<TRgb>* array = new( ELeave ) CArrayFixFlat<TRgb>(1);
    CleanupStack::PushL( array );
    TRgb rgb = ( KRgbRed, KRgbGreen, KRgbBlue );
    array->AppendL( rgb );
    TBool noneChosen = ETrue;
    CAknColourSelectionGrid* colourSelectionGrid = 
                CAknColourSelectionGrid::NewL( 
                        array, ETrue, noneChosen, rgb );
    CleanupStack::PushL( colourSelectionGrid );
    
    colourSelectionGrid->HandleControlEventL( iContainer, 
            MCoeControlObserver::EEventRequestExit );
    AssertTrueL( ETrue, KHandleControlEventL );
    
    colourSelectionGrid->HandleDialogPageEventL( 
            MEikDialogPageObserver::EUnknownType );
    AssertTrueL( ETrue, KHandleDialogPageEventL );
    
    CleanupStack::PopAndDestroy( colourSelectionGrid );
    CleanupStack::PopAndDestroy( array );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestHListsAndHotkeysL()
//  hierarchical list and hot key api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestHListsAndHotkeysL()
    {
    
    _LIT( KChild, 
          "CAknTreeList::KChild() invoked " );
    _LIT( KVisibleItemIndex, 
          "CAknTreeList::VisibleItemIndex() invoked" );
    _LIT( KSort1, 
          "CAknTreeList::Sort( AknCustomTreeOrdering*, TBool ) invoked " );
    _LIT( KSort2, 
          "CAknTreeList::Sort( AknCustomTreeOrdering*, TBool, TBool ) invoked " );
    _LIT( KChildCount, 
          " CAknTreeList::ChildCount() invoked " );
    _LIT( KConstructFromResourceL, 
          "CEikHotKeyTable::ConstructFromResourceL() invoked" );
    _LIT( KAddItemL, 
          "CEikHotKeyTable::AddItemL() invoked" );
    _LIT( KHotKeyFromCommandId, 
          "CEikHotKeyTable::HotKeyFromCommandId() invoked" );
    _LIT( KRemoveItem, 
          "CEikHotKeyTable::RemoveItem()invoked" );
    _LIT( KReset, 
          "CEikHotKeyTable::Reset() invoked" );

    TInt index;
    TBool mark = ETrue;
    TBool draw=ETrue;
    CAknTreeList* list = CAknSingleStyleTreeList::NewLC();
        
    MAknCustomTreeOrdering* custom = NULL;
    list->Sort( custom, draw );
    AssertTrueL( ETrue, KSort1 );
    
    _LIT( KNodeText, "Node" );
        TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    static_cast<CAknSingleStyleTreeList*>( list )->AddNodeL( 
            KAknTreeIIDRoot,KNodeText, flags, EFalse );
    
    index = list->ChildCount(KAknTreeIIDRoot);
    AssertTrueL( ETrue, KChildCount );
    
    TAknTreeItemID item;
    item = list->Child( KAknTreeIIDRoot, index - 1 );
    AssertTrueL( ETrue, KChild );
    
    list->VisibleItemIndex( item );
    AssertTrueL( ETrue, KVisibleItemIndex );

    list->Sort(KAknTreeIIDRoot, mark, draw );
    AssertTrueL( ETrue, KSort2 );
    
    CleanupStack::PopAndDestroy( list );
    
    const TInt KModifierCode = 0;
    CEikHotKeyTable* hotKey = new( ELeave) CEikHotKeyTable();
    CleanupStack::PushL( hotKey );

    hotKey->ConstructFromResourceL( R_BCTEST_MIX50PATCH_HOTKEY_COMMAND );
    AssertTrueL( ETrue, KConstructFromResourceL );

    hotKey->AddItemL( EBCTestCmdOutline1, Key1, KModifierCode );
    AssertTrueL( ETrue, KAddItemL );

    hotKey->AddItemL( EBCTestCmdOutline1, Key1, EModifierCtrl );
    hotKey->AddItemL( EProgCmdAutoTest, Key2,
        EModifierShift|EModifierCtrl );

    TInt cmdId = hotKey->CommandIdFromHotKey( Key1, EModifierCtrl );
    _LIT( KCommandIdFromHotKey, "CEikHotKeyTable::CommandIdFromHotKey" );
    AssertTrueL( ETrue, KCommandIdFromHotKey );

    TInt keyCode;
    TInt kModifier;
    TBool flag = hotKey->HotKeyFromCommandId( EBCTestCmdOutline1, keyCode,
        kModifier );
    AssertTrueL( flag, KHotKeyFromCommandId );

    flag = hotKey->HotKeyFromCommandId( EProgCmdAutoTest, keyCode,
        kModifier );
    _LIT( KHotKeyFromCommandId1, "CEikHotKeyTable::HotKeyFromCommandId 1" );
    AssertTrueL( flag, KHotKeyFromCommandId1 );

    hotKey->RemoveItem( EBCTestCmdOutline1 );
    AssertTrueL( ETrue, KRemoveItem );

    hotKey->Reset();
    AssertTrueL( ETrue, KReset );

    CleanupStack::Pop( hotKey );
    delete hotKey;
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestMiscellOneL()
//  miscellaneous apis test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestMiscellOneL()
    {
    _LIT( KWriteInternalStateL, 
          "EikImage::WriteInternalStateL() invoked" );
    _LIT( KHandleResourceChange, 
          "CAknInputFrame::HandleResourceChange() invoked");
    _LIT( KReplaceIndicatorIconL, 
          "CAknIndicatorContainer::ReplaceIndicatorIconL()invoked");
    _LIT( KDraw, 
          "CEikFileNameLabel::Draw()invoked");
    
    CBCTestImage* image = new ( ELeave ) CBCTestImage;
    CleanupStack::PushL( image );
    
    _LIT( KFileName, "c:\\bctestlog\\image.txt" );
    RFs& fileSession = CCoeEnv::Static()->FsSession();
    RFileWriteStream fileStream;
    if ( fileStream.Open( fileSession, KFileName(), EFileWrite ) != KErrNone )
        {
        fileStream.Create( fileSession, KFileName(), EFileWrite );
        }
    CleanupClosePushL( fileStream );
    image->WriteInternalStateL( fileStream );
    AssertTrueL( ETrue, KWriteInternalStateL );
    
    CleanupStack::PopAndDestroy( &fileStream );
    CleanupStack::PopAndDestroy( image );
    
    // Test indicator container api
    CAknIndicatorContainer* indicator = 
        new( ELeave ) CAknIndicatorContainer();
    CleanupStack::PushL( indicator );
    indicator->ConstructL();
    TUid uId;
    uId = indicator->CreateIndicatorFromResourceL( 
            R_BCTEST_MIX50PATCH_INDICATOR, 
            CAknIndicatorContainer::EMultiColorIndicator );
    
    CFbsBitmap* bitmap( NULL );
    // Get bitmap for "abc" icon
    TAknsItemID skinId = KAknsIIDQgnStatCaseSmall;
    TInt bitmapId = EMbmAvkonQgn_stat_case_small;  
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();    
    AknsUtils::CreateIconLC( skin,
                             skinId,
                             bitmap,
                             AknIconUtils::AvkonIconFileName(),
                             bitmapId );    
                   
    TSize size;        
    User::LeaveIfError( AknIconUtils::GetContentDimensions( bitmap,
                                                                size ) );        
    CFbsBitmap* emptyMask = new (ELeave) CFbsBitmap();
    CleanupStack::PushL( emptyMask );
    User::LeaveIfError( emptyMask->Create( size, EGray2 ) );

    // Ownership of bitmap and newMask is transferred to indicator. 
    indicator->ReplaceIndicatorIconL( uId, EAknIndicatorStateOn, 
            CAknIndicatorContainer::ELayoutModeUsual, bitmap, emptyMask );
    AssertTrueL( ETrue, KReplaceIndicatorIconL );
    
    CleanupStack::Pop( 2, bitmap ); // CSI: 47,12 # emptyMask, bitmap
    CleanupStack::PopAndDestroy( indicator );
    
    // input frame api
    CEikEdwin* edwin = new( ELeave ) CEikEdwin();
    CleanupStack::PushL( edwin );
    edwin->ConstructL( 0, 30, 100, 1 );
    
    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    bmp->Load( AknIconUtils::AvkonIconFileName(), 
        EMbmAvkonQgn_stat_chi_pinyin );
    
    CGulIcon* icon = CGulIcon::NewL( bmp );
    CleanupStack::PushL( icon );
    
    CAknInputFrame* inputFrame = CAknInputFrame::NewL( edwin,
        EFalse, icon );
    CleanupStack::PushL( inputFrame );
    // POPUP_FIELD_SELECTION_BMP
    inputFrame->HandleResourceChange( KEikColorResourceChange );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    CleanupStack::PopAndDestroy( inputFrame );
    CleanupStack::Pop( icon );
    CleanupStack::Pop( bmp );
    CleanupStack::PopAndDestroy( edwin );
    
    // labels api
    CBCTestEikFileNameLabel* fileNameLabel = new( 
            ELeave ) CBCTestEikFileNameLabel;
    CleanupStack::PushL( fileNameLabel ); 
    fileNameLabel->ConstructL();
    fileNameLabel->SetContainerWindowL( *iContainer );
    fileNameLabel->ActivateGc();   
    fileNameLabel->Draw( iContainer->Rect() );
    AssertTrueL( ETrue, KDraw );
    fileNameLabel->DeactivateGc();
    
    CleanupStack::PopAndDestroy( fileNameLabel );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestInitializationL()
//  initialization api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestInitializationL()
    {
    _LIT( KResourceFile , 
          "CEikCtlLibrary::ResourceFile() invoked" );
    _LIT( KControlFactory , 
          "CEikCtlLibrary::ControlFactory() invoked" );
    _LIT( KInitializeL , 
          "CEikCtlLibrary::InitializeL() invoked" );
    _LIT( KButtonGroupFactory , 
          "CEikCtlLibrary::ButtonGroupFactory() invoked" );
    
    CEikCtlLibrary::ResourceFile();
    AssertTrueL( ETrue, KResourceFile );
    
    CEikCtlLibrary::ControlFactory();
    AssertTrueL( ETrue, KControlFactory );
    
    CEikCtlLibrary::InitializeL();
    AssertTrueL( ETrue, KInitializeL );
    
    CEikCtlLibrary::ButtonGroupFactory();
    AssertTrueL( ETrue, KButtonGroupFactory );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestInputLanL()
//  input language api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestInputLanL()
    {
    _LIT( KTAknInputLanguageCapabilities, 
          "TAknInputLanguageCapabilities::TAknInputLanguageCapabilities()  \
          invoked" );
    _LIT( KAssignCapability, 
          "TAknInputLanguageCapabilities::AssignCapability()invoked " );
    _LIT( KFilteredCapabilities, "TAknInputLanguageCapabilities:: \
          FilteredCapabilities()invoked" );
    _LIT( KHasCapability, "TAknInputLanguageCapabilities:: \
          HasCapability()invoked" );
    _LIT( KSetAllCapabilities, "TAknInputLanguageCapabilities:: \
          SetAllCapabilities()invoked" );
    _LIT( KMdcaCount,
          "CAknInputLanguageList::MdcaCount()invoked" );
    _LIT( KMdcaPoint, 
          "CAknInputLanguageList::MdcaPoint" );
    _LIT( KLanItem1, 
          "CAknInputLanguageItem::LanguageCode" );
    _LIT( KLanItem2, 
          "CAknInputLanguageItem::LanguageName" );
    _LIT( KLanItem3, "CAknInputLanguageItem::Capabilities" );
    _LIT( KCAknInputLanguageItemDes, 
          "CAknInputLanguageItem::~CAknInputLanguageItem() invoked" );
    _LIT( KCAknInputLanguageListDes, 
          "CAknInputLanguageList::~CAknInputLanguageList() invoked");
     
    CAknInputLanguageInfo* lanInfo =
            AknInputLanguageInfoFactory::CreateInputLanguageInfoL();
    CleanupStack::PushL( lanInfo );
    
    TAknInputLanguageCapabilities capFilter;
    AssertTrueL( ETrue, KAssignCapability );
    
    capFilter.AssignCapability( 
            TAknInputLanguageCapabilities::EMultitap, ETrue );
    AssertTrueL( ETrue, KAssignCapability);
    
    TAknInputLanguageCapabilities inputCap;
    TAknInputLanguageCapabilities desCap;
    AssertTrueL( ETrue, KTAknInputLanguageCapabilities );
     
    inputCap.AssignCapability( TInt ( 1 ),EFalse );
    AssertTrueL( ETrue, KAssignCapability );

    inputCap.FilteredCapabilities( desCap );
    AssertTrueL( ETrue, KFilteredCapabilities );

    inputCap.HasAnySupport();
    AssertTrueL( ETrue, KHasCapability );

    inputCap.HasCapability( TInt ( 1 ) );
    AssertTrueL( ETrue, KHasCapability );

    inputCap.SetAllCapabilities();
    AssertTrueL( ETrue, KSetAllCapabilities );
    
    CAknInputLanguageList* inputList = new ( 
            ELeave ) CAknInputLanguageList( TInt( 1 ) );
    CleanupStack::PushL( inputList );
    
    CArrayFixFlat<TInt>* codeList = new( ELeave ) CArrayFixFlat<TInt>( 1 );
    CleanupStack::PushL( codeList );    
    codeList->AppendL( ELangEnglish );
    
    lanInfo->AppendLanguagesL( inputList, codeList, capFilter );
    
    TInt cunt = inputList->MdcaCount();
    AssertTrueL( ETrue, KMdcaCount );
    
    TPtrC ptr = inputList->MdcaPoint( 0 );
    AssertTrueL( ETrue, KMdcaPoint );
    
    CAknInputLanguageItem* lanItem = (*inputList)[0];

    TLanguage code = lanItem->LanguageCode();
    AssertIntL( ELangEnglish, code, KLanItem1 );
    
    TPtrC name = lanItem->LanguageName();
    AssertTrueL( ETrue, KLanItem2 );
    
    TAknInputLanguageCapabilities cap = lanItem->Capabilities();
    AssertTrueL( ETrue, KLanItem3 );
    
    CleanupStack::PopAndDestroy( codeList );
    CleanupStack::PopAndDestroy( inputList );
    AssertTrueL( ETrue, KCAknInputLanguageListDes );
    AssertTrueL( ETrue, KCAknInputLanguageItemDes );
    CleanupStack::PopAndDestroy( lanInfo );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestMenusL()
//  menu api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestMenusL()
    {
    _LIT( KCTitleArray,"CTitleArray::CTitleArray() invoked" );
    _LIT( KAddTitleL, "CTitleArray::AddTitleL() invoked");
    _LIT( KCTitleArrayDes, "CTitleArray::~CTitleArray() invoked" );
    
    CEikMenuBar::CTitleArray* titleArray = new (
            ELeave ) CEikMenuBar::CTitleArray();
    AssertNotNullL( titleArray, KCTitleArray );
    CleanupStack::PushL( titleArray );
    
    CEikMenuBarTitle* titleBar = new (ELeave) CEikMenuBarTitle;
    CleanupStack::PushL( titleBar );
    titleArray->AddTitleL( titleBar ); // ownership transferred
    AssertTrueL( ETrue, KAddTitleL );
    
    CleanupStack::Pop( titleBar );
    CleanupStack::PopAndDestroy( titleArray );
    AssertTrueL( ETrue, KCTitleArrayDes );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestNotesL()
//  notes api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestNotesL()
    {
    _LIT( KExecuteDlgLD1, 
          "CAknNoteDialog::KExecuteDlgLD( const TTimeout,  \
          const TTone ,TInt ) invoked" );
    _LIT( KExecuteDlgLD2, 
          "CAknNoteDialog::KExecuteDlgLD( const TTone, TInt ) invoked" );
    _LIT( KExecuteDlgLD3, 
          "CAknNoteDialog::KExecuteDlgLD( TInt, TInt ) invoked" );
    CAknNoteDialog* noteDialog = new( ELeave ) CAknNoteDialog();  
    
    noteDialog->ExecuteDlgLD( R_BCTEST_MIX50PATCH_NOTE_ICON );
    AssertTrueL( ETrue, KExecuteDlgLD3 ); 
    noteDialog = NULL;
    
    noteDialog = new( ELeave ) CAknNoteDialog();
    noteDialog->ExecuteDlgLD( CAknNoteDialog::EConfirmationTone,
            R_BCTEST_MIX50PATCH_NOTE_ICON );
    AssertTrueL( ETrue, KExecuteDlgLD2 ); 
    noteDialog = NULL;
    
    noteDialog = new( ELeave ) CAknNoteDialog();
    noteDialog->ExecuteDlgLD( CAknNoteDialog::EShortTimeout, 
        CAknNoteDialog::EConfirmationTone, R_BCTEST_MIX50PATCH_NOTE_ICON );
    AssertTrueL( ETrue, KExecuteDlgLD1 ); 
    noteDialog = NULL;      
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestMiscellTwoL()
//  another miscellaneous apis test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestMiscellTwoL()
    {
    _LIT( KSetPreferredNaviDecoratorLayoutStyle , 
          "CAknNavigationControlContainer:: \
          SetPreferredNaviDecoratorLayoutStyle()invoked");
    _LIT( KHandleResourceChange, "CAknLocalScreenClearer:: \
            HandleResourceChange()invoked");
    _LIT( KTopContext, "CAknKeySoundSystem::TopContext()invoked");
    
    // Navigation pane api
    CAknNavigationControlContainer* navictlContainer = new ( ELeave )
         CAknNavigationControlContainer();
    CleanupStack::PushL( navictlContainer );
    navictlContainer->ConstructL();
    navictlContainer->SetPreferredNaviDecoratorLayoutStyle(
            CAknNavigationDecorator::ENaviControlLayoutNarrow );
    AssertTrueL( ETrue, KSetPreferredNaviDecoratorLayoutStyle );
    CleanupStack::PopAndDestroy( navictlContainer );
    
    // CAknLocalScreenClearer
    CAknLocalScreenClearer* clearer = CAknLocalScreenClearer::NewLC();
    clearer->HandleResourceChange( KEikColorResourceChange );
    AssertTrueL( ETrue, KHandleResourceChange );
    CleanupStack::PopAndDestroy( clearer );
    
    // CAknKeySoundSystem
    const TInt KUid = 100;
    CAknKeySoundSystem *aknsoundsystem = CAknKeySoundSystem::NewL( KUid );
    CleanupStack::PushL( aknsoundsystem );
    aknsoundsystem->TopContext();
    AssertTrueL( ETrue, KTopContext );
    CleanupStack::PopAndDestroy( aknsoundsystem );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestNotifierL()
//  notifier api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestNotifierL()
    {
    _LIT( KMsg, "CAknPopupNotify test test test!!!!" );
    _LIT( KPopupMessageL, "CAknPopupNotify::PopupMessageL()invoked");
    CAknPopupNotify* notifier = CAknPopupNotify::NewL();
    CleanupStack::PushL( notifier );
    notifier->PopupMessageL( KMsg() );
    AssertTrueL( ETrue, KPopupMessageL );
    CleanupStack::PopAndDestroy( notifier );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestPopupsL()
//  pop up dialog api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestPopupsL()
    {
    _LIT( KTAknPopupWindowLayoutDef, 
          "TAknPopupWindowLayoutDef::TAknPopupWindowLayoutDef() invoked" );
    _LIT( KFadedComponent, 
          "MAknFadedComponent::FadedComponent()invoked");
    _LIT( KCountFadedComponents, 
          "MAknFadedComponent::CountFadedComponents()invoked");

    TAknPopupWindowLayoutDef layout;
    AssertTrueL( ETrue, KTAknPopupWindowLayoutDef );  
    
    CBCTestFadedComponent* fadedComponent = new (
            ELeave ) CBCTestFadedComponent;
    CleanupStack::PushL( fadedComponent );
    
    TInt count = fadedComponent->CountFadedComponents();
    AssertTrueL( ETrue, KCountFadedComponents );
    
    fadedComponent->FadedComponent( count-1 );
    AssertTrueL( ETrue, KFadedComponent );
    
    CleanupStack::PopAndDestroy( fadedComponent );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestUIFrmL()
//  ui framework api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestUIFrmL()
    {
    _LIT( KAddButtonL, "CEikButtonPanel::AddButtonL() invoked " );
    
    // CEikButtonPanel
    CEikButtonPanel * panel = new ( ELeave )CEikButtonPanel();
    CleanupStack::PushL( panel );
    panel->ConstructL();
    
    CEikLabeledButton* button = new (ELeave) CEikLabeledButton;
    CleanupStack::PushL( button );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_BCTEST_MIX50PATCH_LBBUT );
    button->ConstructFromResourceL( reader );
    
    // ownership transferred
    panel->AddButtonL( button,EBCTestMix50PatchLabelledButton, 1 ); 
    AssertTrueL( ETrue, KAddButtonL );
    
    CleanupStack::PopAndDestroy(); // reader internal state
    CleanupStack::Pop( button );
    CleanupStack::PopAndDestroy( panel );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestQueriesL()
//  queries api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestQueriesL()
    {
    _LIT( KHeader, 
          " Query dialog header ");
    _LIT( KHandleQueryEditorSizeEventL, 
          "CAknQueryDialog::HandleQueryEditorSizeEventL()invoked");
    _LIT( KSetHeaderTextL, 
          "CAknQueryDialog::SetHeaderTextL()invoked");
    _LIT( KSetHeaderImageL, 
          "CAknQueryDialog::SetHeaderImageL()invoked");
    _LIT( KSetMediatorObserver, 
          "CAknListQueryDialog::SetMediatorObserver()invoked");
    _LIT( KSetMinimumAndMaximum1,  
    	  "CAknQueryControl::SetMinimumAndMaximum#1() invoked ");
    _LIT( KSetMinimumAndMaximum2,  
    	  "CAknQueryControl::SetMinimumAndMaximum#2() invoked ");
    _LIT( KSetMinimumAndMaximum3,  
    	  "CAknQueryControl::SetMinimumAndMaximum#3() invoked ");
    
    CAknQueryDialog* dialog = CAknQueryDialog::NewL();
    CleanupStack::PushL( dialog );
    
    dialog->HandleQueryEditorSizeEventL( NULL, 
            MAknQueryControlObserver::EQueryControltSizeChanging );
    AssertTrueL( ETrue, KHandleQueryEditorSizeEventL );
    
    dialog->SetHeaderTextL( KHeader() );
    AssertTrueL( ETrue, KSetHeaderTextL );

    CEikImage* image = new( ELeave ) CEikImage;
    CleanupStack::PushL( image ); // image
    
    CFbsBitmap* bmp = AknIconUtils::CreateIconL( 
            AknIconUtils::AvkonIconFileName(), 
            EMbmAvkonQgn_indi_speaker_active );  
    CleanupStack::PushL( bmp );

    image->SetPicture( bmp );
    dialog->SetHeaderImageL( image );
    AssertTrueL( ETrue, KSetHeaderImageL );
    
    CleanupStack::Pop( bmp ); 
    CleanupStack::Pop( image );
    CleanupStack::PopAndDestroy( dialog );
    
    CAknQueryDialog* dialog2 = CAknQueryDialog::NewL();
    dialog2->ExecuteLD( R_BCTESTAKNQUEDLG_ONELINE_DATA_QUERY, _L( "Hello" ) );
    TInt* index = new (ELeave) TInt( 1 );
    CleanupStack::PushL( index );
    
    CAknListQueryDialog* listDialog = new (
            ELeave ) CAknListQueryDialog( index );
    CleanupStack::PushL( listDialog );
    
    listDialog->SetMediatorObserver( NULL );
    AssertTrueL( ETrue, KSetMediatorObserver );
    
    CleanupStack::PopAndDestroy( listDialog );
    CleanupStack::PopAndDestroy( index );
    
    CAknQueryControl* duration = new(ELeave) CAknQueryControl();
    CleanupStack::PushL( duration );
    duration->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, R_BCTEST_DURATION_EDWIN_CONTROL );
    duration->ConstructFromResourceL( reader );
    const TTimeIntervalSeconds time( 1 );

    duration->SetMinimumAndMaximum( time, time );
    AssertTrueL( ETrue, KSetMinimumAndMaximum1 );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( duration );
    
    CAknQueryControl* number = new(ELeave) CAknQueryControl();
    CleanupStack::PushL( number );
    number->SetContainerWindowL( *iContainer );
    iCoeEnv->CreateResourceReaderLC( reader, R_BCTEST_NUMBER_EDWIN_CONTROL );
    number->ConstructFromResourceL( reader );

    number->SetMinimumAndMaximum( 1, 2 );
    AssertTrueL( ETrue, KSetMinimumAndMaximum2 );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( number );
    
    CAknQueryControl* date = new(ELeave) CAknQueryControl();
    CleanupStack::PushL( date );
    date->SetContainerWindowL( *iContainer );
    
    iCoeEnv->CreateResourceReaderLC( reader, R_BCTEST_DATE_EDWIN_CONTROL );
    date->ConstructFromResourceL( reader );

    const TReal r( 1 );
    date->SetMinimumAndMaximum( r, r );
    AssertTrueL( ETrue, KSetMinimumAndMaximum3 );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( date );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestScrollerL()
//  scroller api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestScrollerL()
    {
    _LIT( KDrawBackgroundState, 
          "CEikScrollBarFrame::DrawBackgroundState()invoked");
    _LIT( KSetScrollBarFrameObserver, 
          "CEikScrollBarFrame::SetScrollBarFrameObserver()invoked");
    _LIT( KSetScrollPopupInfoTextL, 
          "CAknDoubleSpanScrollBar::SetScrollPopupInfoTextL()invoked");
    
    CDesCArray* itemArray = new (ELeave) CDesCArrayFlat(2);
    CleanupStack::PushL( itemArray );
    itemArray->AppendL( _L("scroller api test") );
    
    CEikTextListBox* listBox = new (ELeave) CEikTextListBox;
    CleanupStack::PushL( listBox );
    
    listBox->ConstructL( iContainer );
    listBox->Model()->SetItemTextArray( itemArray );
    // ownership transferred
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray ); 
    
    CEikScrollBarFrame* scrollBarFrame = new( ELeave) CEikScrollBarFrame(
                    iContainer, listBox, ETrue );
    CleanupStack::PushL( scrollBarFrame );
    
    TBool vState;
    TBool hState;
    scrollBarFrame->DrawBackgroundState( hState, vState );
    AssertTrueL( ETrue, KDrawBackgroundState );
    
    scrollBarFrame->SetScrollBarFrameObserver( listBox );
    AssertTrueL( ETrue, KSetScrollBarFrameObserver );
    
    CleanupStack::PopAndDestroy( scrollBarFrame );
    CleanupStack::PopAndDestroy( listBox );
    CleanupStack::Pop( itemArray );
    
    _LIT( KInfoText, "scroll bar api test" );
    CAknDoubleSpanScrollBar* scrollBar = new
                        ( ELeave ) CAknDoubleSpanScrollBar( iContainer );
    CleanupStack::PushL( scrollBar );
    
    scrollBar->SetScrollPopupInfoTextL( KInfoText );
    AssertTrueL( ETrue, KSetScrollPopupInfoTextL );
    
    CleanupStack::PopAndDestroy( scrollBar );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestSearchfieldL()
//  search field apis test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestSearchfieldL()
    {
    _LIT( KSetAdaptiveGridChars, 
          "CAknSearchField::SetAdaptiveGridChars()invoked");
    _LIT( KShowAdaptiveSearchGrid, 
          "CAknSearchField::ShowAdaptiveSearchGrid()invoked");
    _LIT( KSetListColumnFilterFlags, 
          "CAknSearchField::SetListColumnFilterFlags()invoked");
    _LIT( KListColumnFilterFlags, 
          "CAknSearchField::ListColumnFilterFlags()invoked");
    _LIT( KAddAdaptiveSearchTextObserverL, 
          "CAknSearchField::AddAdaptiveSearchTextObserverL()invoked");
    _LIT( KRemoveAdaptiveSearchTextObserver, 
          "CAknSearchField::RemoveAdaptiveSearchTextObserver()invoked");
    _LIT( KAdaptiveSearchEnabled, 
          "CAknSearchField::AdaptiveSearchEnabled()invoked");
    _LIT( KLanguageChanged, 
          "CAknSearchField::LanguageChanged()invoked");
    _LIT( KHandlePointerEventL, 
          "CAknSearchField::HandlePointerEventL()invoked");
    _LIT( KAdaptiveChars, 
          "Eternity");
    
    const TInt KSearchFieldMaxLength = 128;
    CAknSearchField* searchField = CAknSearchField::NewL( 
            *iContainer, CAknSearchField::ESearch,
            NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( searchField );
    
    searchField->SetAdaptiveGridChars( KAdaptiveChars() );
    AssertTrueL( ETrue, KSetAdaptiveGridChars );
    
    searchField->ShowAdaptiveSearchGrid();
    AssertTrueL( ETrue, KShowAdaptiveSearchGrid );
    
    searchField->AdaptiveSearchEnabled();
    AssertTrueL( ETrue, KAdaptiveSearchEnabled );
    
    searchField->LanguageChanged();
    AssertTrueL( ETrue, KLanguageChanged );
    
    TBitFlags32 flag( 256 );
    searchField->SetListColumnFilterFlags( flag );
    AssertTrueL( ETrue, KSetListColumnFilterFlags );
    
    searchField->ListColumnFilterFlags();
    AssertTrueL( ETrue, KListColumnFilterFlags );
    
    TPointerEvent pointerEvent;
    pointerEvent.iType  = TPointerEvent::EButton1Up ;
    searchField->HandlePointerEventL( pointerEvent );
    AssertTrueL( ETrue, KHandlePointerEventL );
    
    CBCTestSearchfieldObserver* observer = new (
            ELeave ) CBCTestSearchfieldObserver;
    CleanupStack::PushL( observer );
    
    searchField->AddAdaptiveSearchTextObserverL( observer );
    AssertTrueL( ETrue, KAddAdaptiveSearchTextObserverL );
    
    searchField->RemoveAdaptiveSearchTextObserver( observer );
    AssertTrueL( ETrue, KRemoveAdaptiveSearchTextObserver );
    
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( searchField );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestSettingPagesL()
//  setting page apis test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestSettingPagesL()
    {
    _LIT( KSettingPage, 
          "SP Test" );
    _LIT( KVolumeWriteInternalStateL, 
          "CAknVolumeSettingPage::WriteInternalStateL()invoked" );
    _LIT( KIntegerWriteInternalStateL, 
          "CAknIntegerSettingPage::WriteInternalStateL()invoked" );
    _LIT( KTextWriteInternalStateL, 
          "CAknTextettingPage::WriteInternalStateL()invoked" );
    _LIT( KSliderWriteInternalStateL, 
          "CAknSliderSettingPage::WriteInternalStateL()invoked" );
    _LIT( KWriteInternalStateL, 
          "CAknVolumeSettingPage::WriteInternalStateL()invoked" );
    _LIT( KRadioButtonWriteInternalStateL, 
          "CAknVolumeSettingPage::WriteInternalStateL()invoked" );
    _LIT( KNumericPasswordWriteInternalStateL,
          "CAknVolumeSettingPage::WriteInternalStateL()invoked" );
    _LIT( KPasswordWriteInternalStateL, 
          "CAknVolumeSettingPage::WriteInternalStateL()invoked" );
    _LIT( KFieldWriteInternalStateL, 
          "CAknVolumeSettingPage::WriteInternalStateL()invoked" );
    _LIT( KAlphaPasswordWriteInternalStateL, 
          "CAknAlphaPasswordSettingPage::WriteInternalStateL()invoked" );
    _LIT( KCheckboxWriteInternalStateL, 
          "CAknVolumeSettingPage::WriteInternalStateL()invoked" );
    _LIT( KMenuShowing, 
          "CAknSettingPage::MenuShowing()invoked");
    _LIT( KWaiting, 
          "CAknSettingPage::Waiting()invoked"); 
    _LIT( KCheckAndSetDataValidity, 
          "CAknSettingPage::CheckAndSetDataValidity()invoked"); 
    _LIT( KTextLabel, 
          "CAknSettingPage::TextLabel()invoked"); 
    _LIT( KHandlePointerEventL, 
          "CAknIpFieldSettingPage::HandlePointerEventL()invoked"); 
    _LIT( KCheckboxHandleListBoxEventL, 
          "CAknCheckBoxSettingPage::HandleListBoxEventL()invoked"); 
    _LIT( KSettingPageConstructFromResource, 
    	  "CAknSettingPage::ConstructFromResource()#2 invoked");
    _LIT( KAknSettingPage, 
    	  "CAknSettingPage::CAknSettingPage()#2 invoked");

    
    TInt volumevalue = 3;
    TBuf<20> temp;
    temp.Append( KSettingPage() );
    CBCTestVolumeSettingPage* volumeSettingPage = new (
            ELeave ) CBCTestVolumeSettingPage( 
                    R_BCTEST_MIX50PATCH_VOLUME_SETTING_PAGE, volumevalue );
    
    CleanupStack::PushL( volumeSettingPage );
    volumeSettingPage->ConstructL();
    
    CBufFlat* buf = CBufFlat::NewL( 200 );
    CleanupStack::PushL( buf );
    
    RBufWriteStream stream;
    stream.Open( *buf );
    volumeSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KVolumeWriteInternalStateL );
    
    TInt test = 10;
    CBCTestIntegerSettingPage* integerSettingPage = new (ELeave) 
        CBCTestIntegerSettingPage( 
                R_BCTEST_MIX50PATCH_SETPAGE_TEXT_SETTING_PAGE, test );
    CleanupStack::PushL( integerSettingPage );
    integerSettingPage->ConstructL();
    
    integerSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KIntegerWriteInternalStateL );
    
    CBCTestTextSettingPage* textSettingPage = new ( 
            ELeave ) CBCTestTextSettingPage(
                    R_BCTEST_MIX50PATCH_SETPAGE_TEXT_SETTING_PAGE, temp );
    CleanupStack::PushL( textSettingPage );
    textSettingPage->ConstructL();
    
    textSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KTextWriteInternalStateL );
    
    CBCTestSliderSettingPage* sliderSettingPage = new (ELeave) 
            CBCTestSliderSettingPage( 
                    R_BCTEST_MIX50PATCH_SETPAGE_SLIDER_SETTING_PAGE, test );
    CleanupStack::PushL( sliderSettingPage );
    sliderSettingPage->ConstructL();
    
    sliderSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KSliderWriteInternalStateL );
    
    CBCTestPatchAknSettingPage* settingPage = new( ELeave )
            CBCTestPatchAknSettingPage( R_BCTEST_MIX50PATCH_SETTING_PAGE );
    CleanupStack::PushL( settingPage );
    settingPage->ConstructL();
//    settingPage->SetFocusToEditor();
    
    settingPage->MenuShowing();
    AssertTrueL( ETrue, KMenuShowing );
    
    settingPage->Waiting();
    AssertTrueL( ETrue, KWaiting );
    
    settingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KWriteInternalStateL );
    
    settingPage->CheckAndSetDataValidity();
    AssertTrueL( ETrue, KCheckAndSetDataValidity );
    
    settingPage->TextLabel();
    AssertTrueL( ETrue, KTextLabel );
    
    TInt currentItem(0);
    CDesCArrayFlat* array = CCoeEnv::Static()->ReadDesCArrayResourceL(
            R_BCTEST_MIX50PATCH_SETPAGE_LIST_ITEM_ARRAY );
    CleanupStack::PushL( array );
    
    CBCTestRadioButtonSettingPage* radioButtonSettingPage = new (ELeave) 
        CBCTestRadioButtonSettingPage( 
                R_BCTEST_MIX50PATCH_SETPAGE_RADIOBTN_SETPAGE, currentItem, array );
    CleanupStack::PushL( radioButtonSettingPage );
    radioButtonSettingPage->ConstructL();
    
    radioButtonSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KRadioButtonWriteInternalStateL );
    
    _LIT(KOldPassword, "TESTOLD");
    CBCTestNumericPasswordSettingPage* numericPwdSettingPage = new (ELeave)
            CBCTestNumericPasswordSettingPage(
                    R_BCTEST_MIX50PATCH_PASSWORD_SETTING_PAGE, temp, KOldPassword);
    CleanupStack::PushL( numericPwdSettingPage );
    numericPwdSettingPage->ConstructL();
    
    numericPwdSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KNumericPasswordWriteInternalStateL );
    
    CBCTestAlphaPasswordSettingPage* alphaPwdSettingPage = new (ELeave) 
            CBCTestAlphaPasswordSettingPage(
                    R_BCTEST_MIX50PATCH_PASSWORD_SETTING_PAGE, temp, KOldPassword);
    CleanupStack::PushL( alphaPwdSettingPage );
    alphaPwdSettingPage->ConstructL();
    
    alphaPwdSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KAlphaPasswordWriteInternalStateL );
    
    CBCTestPasswordSettingPage* pwdSettingPage = new (ELeave)
            CBCTestPasswordSettingPage( 
                    R_BCTEST_MIX50PATCH_PASSWORD_SETTING_PAGE, temp, KOldPassword );
    CleanupStack::PushL( pwdSettingPage );
    pwdSettingPage->ConstructL();
    
    pwdSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KPasswordWriteInternalStateL );
    
    TInetAddr ipAddr(10);
    CBCTestIpFieldSettingPage* ipFieldSettingPage = new (ELeave) 
            CBCTestIpFieldSettingPage(
                    R_BCTEST_MIX50PATCH_SETPAGE_IPADDRESS_SETTING_PAGE, ipAddr );
    CleanupStack::PushL( ipFieldSettingPage );
    ipFieldSettingPage->ConstructL();
    
    TPointerEvent pointerEvent;
    pointerEvent.iType  = TPointerEvent::EButton1Up ;
    ipFieldSettingPage->HandlePointerEventL( pointerEvent );
    AssertTrueL( ETrue, KHandlePointerEventL );
    
    ipFieldSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KFieldWriteInternalStateL );
    
    CSelectableItem* item = new( ELeave ) CSelectableItem( temp, EFalse );
    CleanupStack::PushL( item );            
    item->ConstructL();
    CSelectionItemList* itemList = new( ELeave ) CSelectionItemList( 1 );
    CleanupStack::PushL( itemList );            
    itemList->AppendL( item );
    CBCTestCheckBoxSettingPage* checkboxSettingPage = new( ELeave )
            CBCTestCheckBoxSettingPage( 
                    R_BCTESTLIST_CHECKBOX_SETTING_PAGE, itemList );
    CleanupStack::PushL( checkboxSettingPage );
    checkboxSettingPage->ConstructL();
    
    checkboxSettingPage->HandlePointerEventL( pointerEvent );
    AssertTrueL( ETrue, KCheckboxHandleListBoxEventL );
    
    checkboxSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KCheckboxWriteInternalStateL );
    
    CBCTestPatchAknSettingPage *sp = new (ELeave) 
    		CBCTestPatchAknSettingPage( R_AVKON_DEFAULT_SETTING_PAGE );
    CleanupStack::PushL( sp );
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader , R_BCTEST_MIX50PATCH_SETTING_PAGE );
    sp->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KSettingPageConstructFromResource );
    CleanupStack::PopAndDestroy(); // reader
    CleanupStack::PopAndDestroy( sp );
    
    CAknSettingPage* sp2 = new (ELeave) CAknSettingPage( &KSettingPage, 0, 0, 0, 0 );
    AssertNotNullL( sp2, KAknSettingPage );
    delete sp2;
    CleanupStack::PopAndDestroy( checkboxSettingPage );
    CleanupStack::PopAndDestroy( itemList );
    CleanupStack::PopAndDestroy( item );
    CleanupStack::PopAndDestroy( ipFieldSettingPage );
    CleanupStack::PopAndDestroy( pwdSettingPage );
    CleanupStack::PopAndDestroy( alphaPwdSettingPage );
    CleanupStack::PopAndDestroy( numericPwdSettingPage );
    CleanupStack::PopAndDestroy( radioButtonSettingPage );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( settingPage );
    CleanupStack::PopAndDestroy( sliderSettingPage );
    CleanupStack::PopAndDestroy( textSettingPage );
    CleanupStack::PopAndDestroy( integerSettingPage );
    CleanupStack::PopAndDestroy( buf );
    CleanupStack::PopAndDestroy( volumeSettingPage );  
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestTitlePaneL()
//  title pane apis test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestTitlePaneL()
    {
    _LIT ( KSetNumberOfVisibleTextRows, 
           "CAknTitlePane::SetNumberOfVisibleTextRows()invoked");
    CAknTitlePane* titlePane = new (ELeave) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    TInt numOfRows = titlePane->MaxNumberOfVisibleTextRows();
    titlePane->SetNumberOfVisibleTextRows( numOfRows );
    AssertTrueL( ETrue, KSetNumberOfVisibleTextRows );
    
    CleanupStack::PopAndDestroy( titlePane );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestChoiceListL()
//  ChoiceListL test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestAknToolbarL()
    {
    _LIT( KHideItemsAndDrawOnlyBackgroundWithTCoeWinPriority,
          "CAknToolbar::HideItemsAndDrawOnlyBackground with TCoeWinPriority" );
    _LIT( KHideItemsAndDrawOnlyBackground, 
          "CAknToolbar::HideItemsAndDrawOnlyBackground" );
    _LIT( KCountFadedComponents, 
          "CAknToolbar::CountFadedComponents" );
    _LIT( KFadedComponent, 
          "CAknToolbar::FadedComponent" );
    _LIT( KPrepareForFocusLoss, 
          "CAknToolbar::PrepareForFocusLossL" );
    
    // Test some API here
    CAknToolbar *toolBar = CAknToolbar::NewL( R_BCTEST_MIX50PATCH_TOOLBAR );
    CleanupStack::PushL( toolBar );
    
    toolBar->SetMopParent( iContainer );
    toolBar->HideItemsAndDrawOnlyBackground(ETrue); 
    AssertTrueL( ETrue, KHideItemsAndDrawOnlyBackground );
    
    toolBar->HideItemsAndDrawOnlyBackground(EFalse,ECoeWinPriorityLow);
    AssertTrueL( ETrue, KHideItemsAndDrawOnlyBackgroundWithTCoeWinPriority );
     
    toolBar->CountFadedComponents();
    AssertTrueL( ETrue, KCountFadedComponents );
      
    toolBar->FadedComponent(0);
    AssertTrueL( ETrue, KFadedComponent );
       
    toolBar->PrepareForFocusLossL();
    AssertTrueL( ETrue, KPrepareForFocusLoss );
    
    toolBar->SetToolbarObserver( this );
    this->MAknToolbarObserver_Reserved_1();
    _LIT( KAknToolbarObserver_r_Reserved_1, \
    "MAknToolbarObserver::MAknToolbarObserver_Reserved_1" );
    AssertTrueL( ETrue, KAknToolbarObserver_r_Reserved_1 );
    
    this->MAknToolbarObserver_Reserved_2();
    _LIT( KAknToolbarObserver_r_Reserved_2, \
    "MAknToolbarObserver::MAknToolbarObserver_Reserved_2" );
    AssertTrueL( ETrue, KAknToolbarObserver_r_Reserved_2 );
   
    CleanupStack::PopAndDestroy( toolBar );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestAknTouchPaneL()
// touch pane api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestAknTouchPaneL()
    {
    _LIT( KNewL, "NewL with resourceId test" );
    _LIT( KSetFepPenSupportInterface, 
          "CAknTouchPane::SetFepPenSupportInterface" );
    _LIT( KDraw, "CAknTouchPane::Draw" );
    
    if ( !AknLayoutUtils::PenEnabled() )
        {
        return;
        }

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_BCTEST_MIX50PATCH_TOUCHPANE );
    CleanupStack::PushL( touchPane );    
    AssertTrueL( ETrue, KNewL );
  
    TRect rect = iContainer->Rect();
 
    CBCTestFepPen* interface = new( ELeave ) CBCTestFepPen();
    CleanupStack::PushL( interface );
    touchPane->SetFepPenSupportInterface( interface );
   
    AssertTrueL( ETrue, KSetFepPenSupportInterface );
    CleanupStack::PopAndDestroy( interface );
    
    iContainer->ActivateGc();//necessary
    touchPane->Draw( iContainer->SystemGc(), *iContainer, rect );
    iContainer->DeactivateGc();
    AssertTrueL( ETrue, KDraw );    
    
    CleanupStack::PopAndDestroy( touchPane );    
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestChoiceListL()
//  ChoiceListL test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestAknEnvL()
    {
    _LIT( KTxtAknEnvSplitViewActive, "CAknEnv::SplitViewActive" );
    _LIT( KAknEnvRequestCommandMediationL, 
          "CAknEnv::RequestCommandMediationL" );
    _LIT( KAknEnvEndCommandMediation, "CAknEnv::EndCommandMediation" );
    
    CAknEnv* aknEnv = CAknEnv::Static();
    aknEnv->SplitViewActive();
    AssertTrueL( ETrue, KTxtAknEnvSplitViewActive );

    CEikButtonGroupContainer* cba = iAvkonAppUi->Cba();
    aknEnv->RequestCommandMediationL( *cba, *this );
    AssertTrueL( ETrue, KAknEnvRequestCommandMediationL );

    aknEnv->EndCommandMediation( *this );
    AssertTrueL( ETrue, KAknEnvEndCommandMediation );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestChoiceListL()
//  ChoiceListL test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestAknVolumeControlL()
    {
    _LIT( KTxtCAknVolumeControl, "CAknVolumeControl::CAknVolumeControl" );
    _LIT( KTxtConstructFromResourceL, "CAknVolumeControl::ConstructFromResourceL" );
    _LIT( KTxtMinimumSize, "CAknVolumeControl::MinimumSize" );
    
    CAknVolumeControl* volumeCtrl = new( ELeave ) CAknVolumeControl;
    CleanupStack::PushL( volumeCtrl );
    AssertNotNullL( volumeCtrl, KTxtCAknVolumeControl );
    volumeCtrl->SetContainerWindowL( *iContainer );
      
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_BCTEST_MIX50PATCH_SETPAGE_VOLUME );
    volumeCtrl->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KTxtConstructFromResourceL );
    CleanupStack::PopAndDestroy(); // reader
     
    TSize nSize = volumeCtrl->MinimumSize();
    AssertTrueL( ETrue, KTxtMinimumSize );
    
    CleanupStack::PopAndDestroy( volumeCtrl );
    volumeCtrl = NULL;  
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestHapticsL()
//  Haptics test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestHapticsL()
	{
	_LIT( KNewL1, "CHWRMHaptics::NewL(MHWRMHapticsObserver*,\
			MHWRMHapticsActuatorObserver* )" );
	_LIT( KNewL2, "CHWRMHaptics::NewL(MHWRMHapticsObserver*,\
			MHWRMHapticsActuatorObserver*, TRequestStatus& )" );
	CHWRMHaptics* haptics = CHWRMHaptics::NewL( NULL, NULL );
	CleanupStack::PushL(haptics);
	AssertNotNullL( haptics, KNewL1 );
	CleanupStack::PopAndDestroy(haptics);
	haptics = NULL;
	
	TRequestStatus rs = KRequestPending;
	haptics = CHWRMHaptics::NewL(NULL, NULL, rs);
	CleanupStack::PushL(haptics);
	AssertNotNullL( haptics, KNewL2 );
	User::WaitForRequest(rs);
	CleanupStack::PopAndDestroy(haptics);
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestImageTableItemDataL()
//  Image table item data test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestImageTableItemDataL()
	{
	_LIT(KSetImagesL, "CAknsImageTableItemData::SetImagesL() tested");
	_LIT(KImages, "CAknsImageTableItemData::Images() tested");
	_LIT(KImageIID, "CAknsImageTableItemData::ImageIID() tested");
	_LIT(KNumberOfImages, "CAknsImageTableItemData::NumberOfImages() tested");
	
//	CBCTestAknsImageItemData* itemData = new (ELeave) 
//			CBCTestAknsImageItemData( EAknsITImage );
//	CleanupStack::PushL( itemData );
//	
//	itemData->Type();
//	AssertTrueL( ETrue, KType );
//	
//	TAknsImageAttributeData attributeData;
//	itemData->SetAttributesL( attributeData );
//	AssertTrueL( ETrue, KSetAttributes );
//	
//	itemData->Attributes();
//	AssertTrueL( ETrue, KAttributes );
//	
//	CleanupStack::PopAndDestroy( itemData );
    CAknsImageTableItemData* itemData = CAknsImageTableItemData::NewL();
    CleanupStack::PushL(itemData);

    TAknsItemID skinIdArray[] = 
        {
        KAknsIIDQgnIndiSctClose,
        KAknsIIDQgnIndiAdaptSearchBackspace
        };
    
    //IMPORT_C void SetImagesL (const TInt aNumberOfImages, const TAknsItemID *aImages) 
    itemData->SetImagesL( sizeof( skinIdArray )/sizeof(skinIdArray[0]), skinIdArray );
    AssertTrueL( ETrue, KSetImagesL );
    
    itemData->Images();
    AssertTrueL( ETrue, KImages );
    
    itemData->ImageIID( itemData->NumberOfImages() - 1 );
    AssertTrueL( ETrue, KNumberOfImages );
    AssertTrueL( ETrue, KImageIID );

    CleanupStack::PopAndDestroy();  //itemData
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestMBmpItemDataL()
//  masked bitmap item data test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestMBmpItemDataL()
	{
	_LIT(KNewL, "CAknsMaskedBitmapItemData::NewL() tested");
	_LIT(KMask, "CAknsMaskedBitmapItemData::Mask() tested");
	_LIT(KSetMask, "CAknsMaskedBitmapItemData::SetMask() tested");
	_LIT(KDestroyAndSetMask, "CAknsMaskedBitmapItemData::DestroyAndSetMask() tested");
	
	CAknsMaskedBitmapItemData* bmpItemData = CAknsMaskedBitmapItemData::NewL();
	CleanupStack::PushL( bmpItemData );
	AssertTrueL( ETrue, KNewL );
	
	CFbsBitmap* bitmap = new(ELeave)CFbsBitmap;
	TSize screenSize = iAvkonAppUi->ApplicationRect().Size();
	bitmap->Create( screenSize, iCoeEnv->ScreenDevice()->DisplayMode() );
	bmpItemData->SetMask( bitmap );
	AssertTrueL( ETrue, KSetMask );
	
	bmpItemData->Mask();
	AssertTrueL( ETrue, KMask );
	
	CFbsBitmap* bitmap2 = new (ELeave)CFbsBitmap;
	bitmap2->Duplicate( EMbmAvkonQgn_note_ok );
	bmpItemData->DestroyAndSetMask( bitmap2 );
	AssertTrueL( ETrue, KDestroyAndSetMask );
	
	CleanupStack::PopAndDestroy( bmpItemData );
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestColTableItemDataL()
//  color table item data test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestColTableItemDataL()
	{
	_LIT(KNewL, "CAknsColorTableItemData::NewL() tested");
	_LIT(KSetColorsL, "CAknsColorTableItemData::SetColorsL() tested");
	_LIT(KColorIndexed, "CAknsColorTableItemData::ColorIndexed() tested");
	_LIT(KColorRgb, "CAknsColorTableItemData::ColorRgb() tested");
	_LIT(KGetColorL, "CAknsColorTableItemData::GetColorL() tested");
	
	const TInt numOfEntries = 2;
	CAknsColorTableItemData* itemData = CAknsColorTableItemData::NewL();
    CleanupStack::PushL( itemData );
    AssertTrueL( ETrue, KNewL );
	
	TAknsColorTableEntry colorTable[numOfEntries] = {	
			( 0, 0x000000 ),
			( 1, 0x555555 )
			};
	itemData->SetColorsL( numOfEntries, colorTable );
	AssertTrueL( ETrue, KSetColorsL );
	
	TInt index = itemData->ColorIndexed( numOfEntries-1 );
	AssertTrueL( ETrue, KColorIndexed );
	
	TRgb color = itemData->ColorRgb( numOfEntries - 1 );
	AssertTrueL( ETrue, KColorRgb );
	
	itemData->GetColorL( index, color );
	AssertTrueL( ETrue, KGetColorL );
	
	CleanupStack::PopAndDestroy( itemData );
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestBackgroundCCL()
// Background control context test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestBackgroundCCL()
	{
	_LIT( KNewL, "CAknsLayeredBackgroundControlContext::NewL() tested");
	_LIT( KSetLayerImage, 
			"CAknsLayeredBackgroundControlContext::SetLayerImage() tested");
	_LIT( KSetLayerRect, 
			"CAknsLayeredBackgroundControlContext::SetLayerRect() tested");
	_LIT( KLisboxNewL, "CAknsListBoxBackgroundControlContext::NewL()");
	_LIT( KSetTiledBitmap, 
			"CAknsListBoxBackgroundControlContext::SetTiledBitmap() tested");
	_LIT( KSetTiledRect, 
			"CAknsListBoxBackgroundControlContext::SetTiledRect() tested");
	_LIT( KSetBottomBitmap, 
			"CAknsListBoxBackgroundControlContext::SetBottomBitmap() tested");
	_LIT( KSetBottomRect, 
			"CAknsListBoxBackgroundControlContext::SetBottomRect() tested");
	_LIT( KSetParentContext, 
			"CAknsBasicBackgroundControlContext::SetParentContext() tested");
	_LIT( KControlContextOfParent, 
			"AknsDrawUtils::ControlContextOfParent() tested");
	_LIT( KLinearOrder, "TAknsItemID::LinearOrder");
	
	TInt const layers = 2;
	TRect rect( 0, 0 ,10, 10 );
    TAknsItemID skinIdArray[] = 
        {
        KAknsIIDQgnIndiSctClose,
        KAknsIIDQgnIndiAdaptSearchBackspace
        };
    TInt result = TAknsItemID::LinearOrder( 
    		KAknsIIDQgnIndiSctClose, 
    		KAknsIIDQgnIndiAdaptSearchBackspace );
    AssertTrueL( ETrue, KLinearOrder );
    
    CAknsLayeredBackgroundControlContext* cc = 
    		CAknsLayeredBackgroundControlContext::NewL(
    				KAknsIIDQsnBgAreaStatus, 
    				rect, 
    				EFalse, 
    				1);
    CleanupStack::PushL( cc );
    AssertNotNullL( cc, KNewL );
    CleanupStack::PopAndDestroy( cc );
    cc = NULL;
    
    cc = CAknsLayeredBackgroundControlContext::NewL(
				KAknsIIDQsnBgAreaStatus, 
				rect, 
				EFalse, 
				layers + 1);
    CleanupStack::PushL( cc );
    AssertNotNullL( cc, KNewL );
    
    for ( TInt n = 0; n < layers; n++ )
        {
        cc->SetLayerImage( n, KAknsIIDNone );                
        }
    AssertTrueL( ETrue, KSetLayerImage );
    
    for( TInt n = 0; n < layers; n++ )
    	{
    	cc->SetLayerRect( n, rect );
    	}
    AssertTrueL( ETrue, KSetLayerRect );
    CleanupStack::PopAndDestroy( cc );
    
    CAknsListBoxBackgroundControlContext* listboxcc = 
    	CAknsListBoxBackgroundControlContext::NewL(
    					KAknsIIDQsnBgAreaStatus,
    					rect,
    					EFalse,
    					KAknsIIDQgnIndiSctClose,
    					rect
    					);
    CleanupStack::PushL( listboxcc );
    AssertNotNullL( listboxcc, KLisboxNewL );
    
    listboxcc->SetTiledBitmap( KAknsIIDNone );
    AssertTrueL( ETrue, KSetTiledBitmap );
    
    listboxcc->SetTiledRect( rect );
    AssertTrueL( ETrue, KSetTiledRect );
    
    listboxcc->SetBottomBitmap( KAknsIIDNone );
    AssertTrueL( ETrue, KSetBottomBitmap );
    
    listboxcc->SetBottomRect( rect );
    AssertTrueL( ETrue, KSetBottomRect );
    
    listboxcc->SetParentContext( NULL );
    AssertTrueL( ETrue, KSetParentContext );
    CleanupStack::PopAndDestroy( listboxcc );
    
    AknsDrawUtils::ControlContextOfParent( iContainer );
    AssertTrueL( ETrue, KControlContextOfParent );
    
    CAknsFrameBackgroundControlContext* context = 
    		CAknsFrameBackgroundControlContext::NewL( 
    				KAknsIIDNone, rect, rect, EFalse );
    CleanupStack::PushL(context);

    context->SetFrame( KAknsIIDQsnBgAreaStatus );
    _LIT( KSetFrame, "CAknsFrameBackgroundControlContext::SetFrame" );
    AssertTrueL( ETrue, KSetFrame );
    
    TRect innerRect = TRect( 2, 2, 8, 8 );
    TRect outterRect = TRect ( 1, 1, 9, 9 );
    context->SetFrameRects( outterRect, innerRect );
    _LIT( KSetFrameRects, "CAknsFrameBackgroundControlContext::SetFrameRects" );
    AssertTrueL( ETrue, KSetFrameRects );
    
    context->SetCenter( KAknsIIDNone );
    _LIT( KSetCenter, "CAknsFrameBackgroundControlContext::SetCenter" );
    AssertTrueL( ETrue, KSetCenter );
    
    CleanupStack::PopAndDestroy();  //context
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestAknLayoutUtilsL()
// Akn layout utility apis test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestAknLayoutUtilsL()
	{
	
    CEikLabel* label = new(ELeave) CEikLabel;
    CleanupStack::PushL(label);
    TRect rect;
	label->SetContainerWindowL( *iContainer );
    AknLayoutUtils::SAknLayoutLabel layoutLabel;
    layoutLabel.iFont=0;
    layoutLabel.iC=1;
    layoutLabel.iL=1;
    layoutLabel.iR=1;
    layoutLabel.iB=1;
    layoutLabel.iW=1;
    layoutLabel.iJ=1;
    layoutLabel.iNumberOfLinesShown=1;

    // IMPORT_C void LayoutLabel (CEikLabel *aLabel, 
    // 		const TRect &aLabelParent, 
    //      const SAknLayoutLabel &aLayout, 
    //      const CFont *aCustomFont=0)
    AknLayoutUtils::LayoutLabel( label, rect, layoutLabel, 0 );
    _LIT( KLayoutLabel2, "AknsUtils::LayoutLabel#2" );
    AssertTrueL( ETrue, KLayoutLabel2 );
    
    // IMPORT_C TRect RectFromCoords (
    //		const TRect &aParent, 
    //		TInt h, 
    //		TInt l, 
    //		TInt r, 
    //		TInt B, 
    //		TInt W, 
    //		TInt LB=0)
    rect = AknLayoutUtils::RectFromCoords( rect, 1, 1, 1, 1, 1, 1 );
    _LIT( KRectFromCoords1, "AknsUtils::RectFromCoords#1" );
    AssertTrueL( ETrue, KRectFromCoords1 );
    
    CEikImage* image = new(ELeave)CEikImage;
    CleanupStack::PushL( image );
    TInt i = 1;
    TAknWindowLineLayout lineLayout( i );

    // IMPORT_C void LayoutImage (
    //		CEikImage *aImage, 
    //		const TRect &aParent, 
    //		const TAknWindowLineLayout &aLayout)
    AknLayoutUtils::LayoutImage( image, rect, lineLayout );
    _LIT( KLayoutImage2, "AknsUtils::LayoutImage#2" );
    AssertTrueL( ETrue, KLayoutImage2 );
    
    CCoeControl* control = new(ELeave) CCoeControl;
    CleanupStack::PushL( control );
    
    AknLayoutUtils::SAknLayoutControl layoutControl;
    layoutControl.iC=1;
    layoutControl.iL=1;
    layoutControl.iR=1;
    layoutControl.iB=1;
    layoutControl.iW=1;
    layoutControl.iH=1;

    // IMPORT_C void LayoutControl(
    //		CCoeControl *aControl, 
    //		const TRect &aControlParent, 
    //		const SAknLayoutControl &aLayout)
    AknLayoutUtils::LayoutControl( control, rect, layoutControl );
    _LIT( KLayoutControl2, "AknsUtils::LayoutControl#2" );
    AssertTrueL( ETrue, KLayoutControl2 );

    // IMPORT_C void LayoutControl (
    //		CCoeControl *aControl, 
    //		const TRect &aControlParent, 
    //		TInt, 
    //		TInt l, 
    //		TInt t, 
    //		TInt r, 
    //		TInt b, 
    //		TInt W, 
    //		TInt H)
    AknLayoutUtils::LayoutControl( control, rect, 1, 1, 1, 1, 1, 1, 1 );
    _LIT( KLayoutControl4, "AknsUtils::LayoutControl#4" );
    AssertTrueL( ETrue, KLayoutControl4 );
    
    CEikMfne *mfne = new(ELeave)CEikMfne();
    CleanupStack::PushL( mfne );
    AknLayoutUtils::SAknLayoutMfne layoutMfne;
    layoutMfne.iFont=0;
    layoutMfne.iC=1;
    layoutMfne.iL=1;
    layoutMfne.iR=1;
    layoutMfne.iB=1;
    layoutMfne.iW=1;
    layoutMfne.iJ=1;

    // IMPORT_C void LayoutMfne (
    //		CEikMfne *aMfne, 
    //		const TRect &aMfneParent, 
    //		const SAknLayoutMfne &aLayout)
    AknLayoutUtils::LayoutMfne( mfne, rect, layoutMfne );
    _LIT( KLayoutMfne2, "AknsUtils::LayoutMfne#2" );
    AssertTrueL( ETrue, KLayoutMfne2 );
    
    // IMPORT_C void LayoutMfne (
    //		CEikMfne *aMfne, 
    //		const TRect &aMfneParent, 
    //		TInt font, 
    //		TInt C, 
    //		TInt l, 
    //		TInt r, 
    //		TInt B, 
    //		TInt W, 
    //		TInt J)
    AknLayoutUtils::LayoutMfne( mfne, rect, 0, 0, 0, 0, 0, 0, 0 );
    _LIT( KLayoutMfne4, "AknsUtils::LayoutMfne#4" );
    AssertTrueL( ETrue, KLayoutMfne4 );
    
    CAknIntegerEdwin* edwin = CAknIntegerEdwin::NewL( 1, 2, 2 );
    CleanupStack::PushL( edwin );
    edwin->SetContainerWindowL( *iContainer );
    
    // IMPORT_C void LayoutEdwin (
    //		CEikEdwin *aEdwin, 
    //		const TRect &aEdwinParent, 
    //		TInt font, 
    //		TInt C, 
    //		TInt l, 
    //		TInt r, 
    //		TInt B, 
    //		TInt W, 
    //		TInt J, 
    //		TInt aNumberOfLinesShown, 
    //		TInt aNextLineBaseline, 
    //		const CFont *aCustomFont=0, 
    //		TBool aMinimizeEdwinView=EFalse )
    AknLayoutUtils::LayoutEdwin( 
    		edwin, rect, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EFalse );
    _LIT( KLayoutEdwin5, "AknsUtils::LayoutEdwin#5" );
    AssertTrueL( ETrue, KLayoutEdwin5 );

    // IMPORT_C void LayoutImage (
    //		CEikImage *aImage, 
    //		const TRect &aParent, 
    //		const SAknLayoutControl &aLayout)
    AknLayoutUtils::LayoutImage( image, rect, layoutControl );
    _LIT( KLayoutImage4, "AknsUtils::LayoutImage#4" );
    AssertTrueL( ETrue, KLayoutImage4 );
    
    // IMPORT_C void LayoutLabel (
    //		CEikLabel *aLabel, 
    //		const TRect &aLabelParent, 
    //		const SAknLayoutLabel &aLayout, 
    //		const CFont *aCustomFont=0)
    AknLayoutUtils::LayoutLabel( label, rect, layoutLabel, 0 );
    _LIT( KLayoutLabel5, "AknsUtils::LayoutLabel#5" );
    AssertTrueL( ETrue, KLayoutLabel5 );
    
    // IMPORT_C void LayoutEdwin (
    //		CEikEdwin *aEdwin, 
    //		const TRect &aEdwinParent, 
    //		const SAknLayoutEdwin &aLayout, 
    //		const CFont *aCustomFont=0, 
    //		TBool aMinimizeEdwinView=EFalse)
    AknLayoutUtils::SAknLayoutEdwin edwinLayout;
    edwinLayout.iFont=0;
    edwinLayout.iC=1;
    edwinLayout.iL=1;
    edwinLayout.iR=1;
    edwinLayout.iB=1;
    edwinLayout.iW=1;
    edwinLayout.iJ=1;
    edwinLayout.iNumberOfLinesShown=1;
    AknLayoutUtils::LayoutEdwin( edwin, rect, edwinLayout, 0, EFalse );
    _LIT( KLayoutEdwin2, "AknsUtils::LayoutEdwin#2" );
    AssertTrueL( ETrue, KLayoutEdwin2 );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( mfne );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( image ); 
    CleanupStack::PopAndDestroy( label ); 
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestAknsUtilsL()
// Akn skin utility apis test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestAknsUtilsL()
	{
    MAknsSkinInstance* instance = AknsUtils::SkinInstance();

    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    TRgb rgb = TRgb();

    //IMPORT_C static void CreateColorIconLC(
    // MAknsSkinInstance* aInstance, const TAknsItemID& aID,
    // const TAknsItemID& aColorID, const TInt aColorIndex,
    // CFbsBitmap*& aBitmap, CFbsBitmap*& aMask,
    // const TDesC& aFilename,
    // const TInt aFileBitmapId, const TInt aFileMaskId,
    // const TRgb aDefaultColor );
    _LIT(KAvkonBitmapFile, "z:\\resource\\apps\\avkon2.mbm");
    AknsUtils::CreateColorIconLC( 
    		instance, 
    		KAknsIIDQsnCpClockDigitalZero, 
    		KAknsIIDQsnCpClockDigitalZero, 
    		0, 
    		bitmap, 
    		mask,
    		KAvkonBitmapFile, 
    		0, 
    		0, 
    		rgb);
    _LIT( KCreateColorIconLC, "AknsUtils::CreateColorIconLC" );
    AssertTrueL( ETrue, KCreateColorIconLC );

    if( mask )
        CleanupStack::PopAndDestroy(  );
    if( bitmap )
        CleanupStack::PopAndDestroy(  );
    mask = bitmap = NULL;
    
    //IMPORT_C static void CreateColorIconL(
    // MAknsSkinInstance* aInstance, const TAknsItemID& aID,
    // const TAknsItemID& aColorID, const TInt aColorIndex,
    // CFbsBitmap*& aBitmap, CFbsBitmap*& aMask,
    // const TDesC& aFilename,
    // const TInt aFileBitmapId, const TInt aFileMaskId,
    // const TRgb aDefaultColor );
    AknsUtils::CreateColorIconL( 
    		instance, 
    		KAknsIIDQsnCpClockDigitalZero, 
    		KAknsIIDQsnCpClockDigitalZero, 
    		0, bitmap, 
    		mask, 
    		KAvkonBitmapFile, 
    		0, 
    		0, 
    		rgb);
    _LIT( KCreateColorIconL, "AknsUtils::CreateColorIconL" );
    AssertTrueL( ETrue, KCreateColorIconL );

    if( mask )
        delete mask;
    if( bitmap )
        delete bitmap;
    mask = bitmap = NULL;
    
    //IMPORT_C static void CreateIconL(
    // MAknsSkinInstance* aInstance, const TAknsItemID& aID,
    // CFbsBitmap*& aBitmap, CFbsBitmap*& aMask,
    // const TDesC& aFilename,
    // const TInt aFileBitmapId, const TInt aFileMaskId );
    AknsUtils::CreateIconL(
    		instance, 
    		KAknsIIDQsnCpClockDigitalZero, 
    		bitmap, 
    		mask, 
    		KAvkonBitmapFile, 
    		0, 
    		0);
    _LIT( KCreateIconL, "AknsUtils::CreateIconL" );
    AssertTrueL( ETrue, KCreateIconL );

    if( mask )
        delete mask;
    if( bitmap )
        delete bitmap;
    mask = bitmap = NULL;
    
    //IMPORT_C static void CreateIconL(
    // MAknsSkinInstance* aInstance, const TAknsItemID& aID,
    // CFbsBitmap*& aBitmap,
    // const TDesC& aFilename,
    // const TInt aFileBitmapId );
    AknsUtils::CreateIconL(
    		instance, 
    		KAknsIIDQsnCpClockDigitalZero, 
    		bitmap, 
    		KAvkonBitmapFile, 
    		0);
    _LIT( KCreateIconL1, "AknsUtils::CreateIconL#1" );
    AssertTrueL( ETrue, KCreateIconL1 );

    if( bitmap )
        delete bitmap;
    bitmap = NULL;
    
    //IMPORT_C static void CreateIconLC(
    // MAknsSkinInstance* aInstance, const TAknsItemID& aID,
    // CFbsBitmap*& aBitmap, CFbsBitmap*& aMask,
    // const TDesC& aFilename,
    // const TInt aFileBitmapId, const TInt aFileMaskId );
    AknsUtils::CreateIconLC(
    		instance, 
    		KAknsIIDQsnCpClockDigitalZero, 
    		bitmap,
    		mask, 
    		KAvkonBitmapFile, 
    		0, 
    		0);
    _LIT( KCreateIconLC, "AknsUtils::CreateIconLC" );
    AssertTrueL( ETrue, KCreateIconLC );

    if( mask )
        CleanupStack::PopAndDestroy(  );
    if( bitmap )
        CleanupStack::PopAndDestroy(  );
    mask = bitmap = NULL;
    
    //IMPORT_C static void CreateIconLC(
    // MAknsSkinInstance* aInstance, const TAknsItemID& aID,
    // CFbsBitmap*& aBitmap,
    // const TDesC& aFilename,
    // const TInt aFileBitmapId );
    AknsUtils::CreateIconLC(
    		instance, 
    		KAknsIIDQsnCpClockDigitalZero, 
    		bitmap, 
    		KAvkonBitmapFile, 
    		0);
    _LIT( KCreateIconLC1, "AknsUtils::CreateIconLC#1" );
    AssertTrueL( ETrue, KCreateIconLC1 );

    if( bitmap )
        CleanupStack::PopAndDestroy(  );
    bitmap = NULL;
    
    TAknsItemID itemID = KAknsIIDNone;

    //IMPORT_C void  GetCachedMaskedBitmap (
    //		MAknsSkinInstance *aInstance, 
    //		const TAknsItemID &aID, 
    //		CFbsBitmap *&aBitmap, 
    //		CFbsBitmap *&aMask)
    AknsUtils::GetCachedMaskedBitmap( instance, itemID, bitmap, mask );
    _LIT( KGetCachedMaskedBitmap, "AknsUtils::GetCachedMaskedBitmap" );
    AssertTrueL( ETrue, KGetCachedMaskedBitmap );
    
    if( mask )
        delete mask;
    if( bitmap )
        delete bitmap;
    mask = bitmap = NULL;
    
    TInt err = KErrNone;
    TPoint point = TPoint();
    CAknQueryDialog* dialog = CAknQueryDialog::NewL();
    CleanupStack::PushL( dialog );
    
    //IMPORT_C void RegisterControlPosition (
    // 		const CCoeControl *aControl) 
    AknsUtils::RegisterControlPosition( dialog );
    _LIT( KRegisterControlPosition, "AknsUtils::RegisterControlPosition" );
    AssertTrueL( ETrue, KRegisterControlPosition );
    
    //IMPORT_C void DeregisterControlPosition (
    //		const CCoeControl *aControl) 
    AknsUtils::DeregisterControlPosition( dialog );
    
    //IMPORT_C void RegisterControlPosition (
    //		const CCoeControl *aControl, 
    //		const TPoint &aPoint) 
    AknsUtils::RegisterControlPosition( dialog, point );
    _LIT( KRegisterControlPosition1, "AknsUtils::RegisterControlPosition#1" );
    AssertTrueL( ETrue, KRegisterControlPosition1 );
    
    //IMPORT_C TInt GetControlPosition (
    //		const CCoeControl *aControl, 
    //		TPoint &aScreenPos) 
    err = AknsUtils::GetControlPosition( dialog, point );
    _LIT( KGetControlPosition, "AknsUtils::GetControlPosition" );
    AssertTrueL( ETrue, KGetControlPosition );
    
    //IMPORT_C void DeregisterControlPosition (
    //		const CCoeControl *aControl) 
    AknsUtils::DeregisterControlPosition( dialog );
    _LIT( KDeregisterControlPosition, "AknsUtils::DeregisterControlPosition" );
    AssertTrueL( ETrue, KDeregisterControlPosition );
    
    CleanupStack::PopAndDestroy( dialog );
    
    //IMPORT_C void SetAvkonSkinEnabledL (
    // 		const TBool aEnabled) 
    AknsUtils::SetAvkonSkinEnabledL(EFalse);
    AknsUtils::AvkonSkinEnabled();
    _LIT( KAvkonSkinEnabled, "AknsUtils::AvkonSkinEnabled" );
    AssertTrueL( ETrue, KAvkonSkinEnabled );

    
    //IMPORT_C TInt GetCachedColor (
    //		MAknsSkinInstance *aInstance, 
    //		TRgb &aRgb, 
    //		const TAknsItemID &aID, 
    //		const TInt aIndex) 
    TInt color = AknsUtils::GetCachedColor( instance, rgb, itemID, 0 );
    _LIT( KGetCachedColor, "AknsUtils::GetCachedColor" );
    AssertTrueL( ETrue, KGetCachedColor );
    
    //IMPORT_C CFbsBitmap * GetCachedBitmap (
    //		MAknsSkinInstance *aInstance, 
    //		const TAknsItemID &aID) 
    bitmap = AknsUtils::GetCachedBitmap( NULL, itemID );
    _LIT( KGetCachedBitmap, "AknsUtils::GetCachedBitmap" );
    AssertTrueL( ETrue, KGetCachedBitmap );
    
    if( bitmap )
        delete bitmap;
    bitmap = NULL;
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestAknsDrawUtilsL()
// Akn skin utility apis test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestAknsDrawUtilsL()
	{
	
    TRect rect = TRect();
    MAknsSkinInstance* instance = AknsUtils::SkinInstance();

   	CWindowGc& gc = iCoeEnv->SystemGc();
   	MAknsControlContext* cc = AknsDrawUtils::ControlContext( iContainer );
   	
    gc.Activate( *iContainer->DrawableWindow() );

    //IMPORT_C TBool Background (
    //		MAknsSkinInstance *aInstance, 
    //		MAknsControlContext *aContext, 
    //		const CCoeControl *aControl, 
    //		CWindowGc &aGc, 
    //		const TRect &aRect) 
    TBool output = AknsDrawUtils::Background( instance, cc, iContainer, gc, rect );
    _LIT( KBackground1, "AknsDrawUtils::Background#1" );
    AssertTrueL( ETrue, KBackground1 );
    
    //IMPORT_C TBool Background (
    //		MAknsSkinInstance *aInstance, 
    //		MAknsControlContext *aContext, 
    //		const CCoeControl *aControl, 
    //		CWindowGc &aGc, 
    //		const TRect &aRect, 
    //		const TInt aDrawParam) 
    output = AknsDrawUtils::Background( 
    		instance,  cc, iContainer, gc, rect, KAknsDrawParamDefault );
    _LIT( KBackground2, "AknsDrawUtils::Background#2" );
    AssertTrueL( ETrue, KBackground2 );
    
    //IMPORT_C TBool BackgroundBetweenRects (
    //		MAknsSkinInstance *aInstance, 
    //		MAknsControlContext *aContext, 
    //		CWindowGc &aGc, 
    //		const TRect &aOuterRect, 
    //		const TRect &aInnerRect) 
    
    TRect innerRect = rect;
    innerRect.Shrink( 2, 2 );
    output = AknsDrawUtils::BackgroundBetweenRects(
    		instance, cc, gc, rect, innerRect );
    _LIT( KBackgroundBetweenRects, "AknsDrawUtils::BackgroundBetweenRects" );
    AssertTrueL( ETrue, KBackgroundBetweenRects );
    
    //IMPORT_C TBool BackgroundBetweenRects (
    //		MAknsSkinInstance *aInstance, 
    //		MAknsControlContext *aContext, 
    //		const CCoeControl *aControl, 
    //		CWindowGc &aGc, 
    //		const TRect &aOuterRect, 
    //		const TRect &aInnerRect) 
    output = AknsDrawUtils::BackgroundBetweenRects(
    		instance, cc, iContainer, gc, rect, innerRect);
    _LIT( KBackgroundBetweenRects1, "AknsDrawUtils::BackgroundBetweenRects#1" );
    AssertTrueL( ETrue, KBackgroundBetweenRects1 );
    
    //IMPORT_C TBool BackgroundBetweenRects (
    //		MAknsSkinInstance *aInstance, 
    //		MAknsControlContext *aContext, 
    //		const CCoeControl *aControl, 
    //		CWindowGc &aGc, 
    //		const TRect &aOuterRect, 
    //		const TRect &aInnerRect, 
    //		const TInt aDrawParam ) 
    output = AknsDrawUtils::BackgroundBetweenRects(
    		instance, cc, iContainer, gc, rect, innerRect, KAknsDrawParamDefault );
    _LIT( KBackgroundBetweenRects2, "AknsDrawUtils::BackgroundBetweenRects#2" );
    AssertTrueL( ETrue, KBackgroundBetweenRects2 );

    //IMPORT_C TBool DrawBackground (
    //		MAknsSkinInstance *aInstance, 
    //		MAknsControlContext *aContext, 
    //		const CCoeControl *aControl, 
    //		CBitmapContext &aGc, 
    //		const TPoint &aDstPos, 
    //		const TRect &aControlRect, 
    //		const TInt aDrawParam) 
    TPoint point = TPoint();
    output = AknsDrawUtils::DrawBackground(
    		instance, cc, iContainer, gc, point, rect, KAknsDrawParamDefault);
    _LIT( KDrawBackground, "AknsDrawUtils::DrawBackground" );
    AssertTrueL( ETrue, KDrawBackground );
    
    //IMPORT_C void DrawCachedImage (
    //		MAknsSkinInstance *aInstance, 
    //		CWindowGc &aGc, 
    //		const TRect &aRect, 
    //		const TAknsItemID &aID) 
    AknsDrawUtils::DrawCachedImage( instance, gc, rect, KAknsIIDNone );
    _LIT( KDrawCachedImagee, "AknsDrawUtils::DrawCachedImage" );
    AssertTrueL( ETrue, KDrawCachedImagee );
    
    //IMPORT_C TBool DrawFrame (
    //		MAknsSkinInstance *aInstance, 
    //		CWindowGc &aGc, 
    //		const TRect &aOuterRect, 
    //		const TRect &aInnerRect, 
    //		const TAknsItemID &aFrameID, 
    //		const TAknsItemID &aCenterID) 
    output = AknsDrawUtils::DrawFrame(
    		instance, gc, rect, innerRect, KAknsIIDNone, KAknsIIDNone );
    _LIT( KDrawFrame, "AknsDrawUtils::DrawFrame" );
    AssertTrueL( ETrue, KDrawFrame );
    
    gc.Deactivate();
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestDialogsL()
// Various dialogs api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestDialogsL()
	{
    //IMPORT_C CAknMessageQueryDialog();
    CAknMessageQueryDialog* messageDialog = new(ELeave) CAknMessageQueryDialog();
    CleanupStack::PushL( messageDialog );
    _LIT( KAknMessageQueryDialog, 
    		"CAknMessageQueryDialog::CAknMessageQueryDialog#5" );
    AssertTrueL( ETrue, KAknMessageQueryDialog );
    CleanupStack::PopAndDestroy( messageDialog );
    
    CAknQueryDialog* queryDialog = CAknQueryDialog::NewL();
    CleanupStack::PushL( queryDialog );
    
    _LIT( KPrompt, "Query dialog apis test" );
    queryDialog->ExecuteLD( 
    		R_BCTESTAKNQUEDLG_ONELINE_DATA_QUERY , KPrompt() );
    _LIT( KExecuteLD, "CAknQueryDialog::ExecuteLD#1" );
    AssertTrueL( ETrue, KExecuteLD );
    
    CleanupStack::Pop( queryDialog );
    
    //IMPORT_C CAknStaticNoteDialog(CEikDialog** aSelfPtr);
    iStaticNoteDialog = NULL;
    iStaticNoteDialog = new (ELeave) CAknStaticNoteDialog( 
    		REINTERPRET_CAST( CEikDialog**, &iStaticNoteDialog) );
    CleanupStack::PushL( iStaticNoteDialog );
    _LIT( KAknStaticNoteDialog1, 
    		"CAknStaticNoteDialog::CAknStaticNoteDialog#1" );
    AssertNotNullL( iStaticNoteDialog, KAknStaticNoteDialog1 );
    
    iStaticNoteDialog->SetNumberOfBorders( 1 );
    _LIT( KSetNumberOfBorders, "CAknStaticNoteDialog::SetNumberOfBorders");
    AssertTrueL( ETrue, KSetNumberOfBorders );
    
    CleanupStack::PopAndDestroy( iStaticNoteDialog );
    
//    IMPORT_C CAknNoteDialog(
//    		CEikDialog** aSelfPtr, 
//    		const TTone& aTone = ENoTone, 
//    		const TTimeout& aTimeout = ENoTimeout );
    iNoteDialog = NULL;
    iNoteDialog = new (ELeave)CBCTestAknNoteDialog(
    		REINTERPRET_CAST( CEikDialog**,&iNoteDialog ) );
    CleanupStack::PushL( iNoteDialog );
    CBCTestAknNoteDialog::OwnStaticDeleteL( iNoteDialog );
    CleanupStack::Pop();
    _LIT( KStaticDeleteL, "CAknNoteDialog::StaticDeleteL" );
    AssertTrueL( ETrue, KStaticDeleteL );
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestPopupsL()
// Popup control api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestPopupL()
	{
    CAknSinglePopupMenuStyleListBox* listbox = new(ELeave)CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( listbox );

    CAknPopupList* popupList = CAknPopupList::NewL( listbox, 
    		R_AVKON_SOFTKEYS_OK_BACK, AknPopupLayouts::EMenuWindow );
	CleanupStack::PushL( popupList );

    //IMPORT_C CAknPopupHeadingPane * Heading () const
    const CAknPopupHeadingPane* heading = popupList->Heading();
    _LIT( KHeading, "CAknPopupList::Heading#1" );
    AssertTrueL( ETrue, KHeading );
    
    CleanupStack::PopAndDestroy( 2 );  // popupList + listbox
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestStatesL()
// Kinds of states classes api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestStatesL()
	{
	TAknEditorCaseState caseState;
    _LIT( KTAknEditorCaseState, 
    		"TAknEditorCaseState::TAknEditorCaseState() invoked" );
    AssertTrueL( ETrue, KTAknEditorCaseState );
    
	caseState.SetCurrentCase( 0 );
    _LIT( KSetCurrentCase, 
    		"TAknEditorCaseState::SetCurrentCase() invoked" );
    AssertTrueL( ETrue, KSetCurrentCase );
	
	CAknEdwinState *edwinState = new (ELeave) CAknEdwinState;
	CleanupStack::PushL( edwinState );
	
	edwinState->SetFormAccessor( NULL );
    _LIT( KSetFormAccessor, 
    		"CAknEdwinState::SetFormAccessor() invoked" );
    AssertTrueL( ETrue, KSetFormAccessor );
    
    TCursorSelection cursorSelection( 0, 0 );
    edwinState->SetInlineEditSpan( cursorSelection );
    _LIT( KSetInlineEditSpan, 
    		"CAknEdwinState::SetInlineEditSpan() invoked" );
    AssertTrueL( ETrue, KSetInlineEditSpan );
    
    edwinState->SetNumericKeymap( EAknEditorStandardNumberModeKeymap );
    _LIT( KSetNumericKeymap, "CAknEdwinState::SetNumericKeymap() invoked" );
    AssertTrueL( ETrue, KSetNumericKeymap );
    
    edwinState->SetPermittedCases( 0 );
    _LIT( KSetPermittedCases, 
    		"CAknEdwinState::SetPermittedCases() invoked" );
    AssertTrueL( ETrue, KSetPermittedCases );
    
    edwinState->SetDefaultCase( 0 );
    _LIT( KSetDefaultCase, "CAknEdwinState::SetDefaultCase() invoked" );
    AssertTrueL( ETrue, KSetDefaultCase );
    
    edwinState->SetPermittedInputModes( 0 );
    _LIT( KSetPermittedInputModes, 
    		"CAknEdwinState::SetPermittedInputModes() invoked" );
    AssertTrueL( ETrue, KSetPermittedInputModes );
    
    edwinState->SpecialCharacterTableResourceId();
    _LIT( KSpecialCharacterTableResourceId, 
    		"CAknEdwinState::SpecialCharacterTableResourceId() invoked" );
    AssertTrueL( ETrue, KSpecialCharacterTableResourceId );
    
    edwinState->PermittedInputModes();
    _LIT( KPermittedInputModes, "CAknEdwinState::PermittedInputModes() invoked" );
    AssertTrueL( ETrue, KPermittedInputModes );
    
    edwinState->Flags();
    _LIT( KFlags, "CAknEdwinState::Flags() invoked" );
    AssertTrueL( ETrue, KFlags );
    
    edwinState->ReportAknEdStateEventL(
    		MAknEdStateObserver::EAknEdwinStateEventStateUpdate );
    _LIT( KReportAknEdStateEventL, 
    		"CAknEdwinState::ReportAknEdStateEventL() invoked" );
    AssertTrueL( ETrue, KReportAknEdStateEventL );
    
	CleanupStack::PopAndDestroy( edwinState );
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestStatesL()
// Kinds of states classes api test  
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestIpFieldEditorL()
	{
    TInetAddr minimumAddress;
    TInetAddr maximumAddress;
    TInetAddr initialAddress;
    minimumAddress.Input( _L("1.1.1.1") );
    maximumAddress.Input( _L("255.255.255.255") );
    initialAddress.Input( _L("192.168.1.1") );
    CAknIpFieldEditor *ipFieldEditor = CAknIpFieldEditor::NewL(
    		minimumAddress, maximumAddress, initialAddress );
    CleanupStack::PushL( ipFieldEditor );
    
    _LIT( KCAknIpFieldEditor, "CAknIpFieldEditor::CAknIpFieldEditor() invoked" );
    AssertNotNullL( ipFieldEditor, KCAknIpFieldEditor );
    
    ipFieldEditor->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, R_BCTEST_IP_FIELD );

    // IMPORT_C TInetAddr ReadIPAddress( TResourceReader& aResourceReader );
    ipFieldEditor->ReadIPAddress( reader );
    _LIT( KReadIPAddress, "CAknIpFieldEditor::ReadIPAddress() invoked" );
    AssertNotNullL( ipFieldEditor, KReadIPAddress );

    CleanupStack::PopAndDestroy(); // reader
    CleanupStack::PopAndDestroy( ipFieldEditor );
	}

// ---------------------------------------------------------------------------
// CBCTestMix50PatchControlCase::TestIconArrayL()
// Icon array apis test
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchControlCase::TestIconArrayL()
	{
    CAknIconArray* iconArray = new(ELeave)CAknIconArray( 5 );
    CleanupStack::PushL( iconArray );

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, R_AVKON_FIND_PANE_INDICATOR_ICONS );

    //IMPORT_C void AppendFromResourceL ( TResourceReader &aReader ) 
    _LIT( KAppendFromResourceL, 
    		"CAknMarkableListDialog::CAknMarkableListDialog#1() invoked");
    iconArray->AppendFromResourceL( reader );
    AssertTrueL( ETrue, KAppendFromResourceL );
    
	CleanupStack::PopAndDestroy(); // reader
    CleanupStack::PopAndDestroy( iconArray );
	}
