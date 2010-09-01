/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <avkon.hrh>
#include <AknsConstants.h>

#include <eikbgfty.h>
#include <eikenv.h>
#include <eikcolib.h>
#include <eikbtgpc.h>
#include <eikcmbut.h>
#include <eikbutb.h>
#include <s32file.h>
#include <eikcba.h>
#include <eikcmbut.h>
#include <barsread.h>
#include <avkon.mbg>
#include <eiklbbut.h>
#include <coecntrl.h>
#include <eikmnbut.h>
#include <eikbtgps.h>
#include <eikbtgrp.h>

#include <akniconutils.h>
#include <bctestbuttons.rsg>
#include <bctestbuttons.mbg>

#include "bctestbuttonscase.h"
#include "bctestbuttonscontainer.h"
#include "bctestbuttons.hrh"
#include "streamlogger.h"

_LIT( KStreamName, "c:\\BCTestLog\\buttontest.txt" );
#ifdef __WINS__
_LIT( KButtonIconFile1, "z:\\resource\\apps\\BCTestButtons.mbm" );
#else
_LIT( KButtonIconFile1, "c:\\resource\\apps\\BCTestButtons.mbm" );
#endif

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestButtonsCase* CBCTestButtonsCase::NewL(
    CBCTestButtonsContainer* aContainer )
    {
    CBCTestButtonsCase* self = new( ELeave ) CBCTestButtonsCase(
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
CBCTestButtonsCase::CBCTestButtonsCase(
    CBCTestButtonsContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestButtonsCase::~CBCTestButtonsCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::ConstructL()
    {
    BuildScriptL();
    iEnv = CEikonEnv::Static();
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::BuildScriptL()
    {
    // Add script as your need.
	AddTestL( DELAY(1), TEND);
    TInt loop = EBCTestCmdMaxOutline - EBCTestCmdTestEikBgftyAndEikBtgpcL;
    for ( TInt i = 0; i < loop; i++ )
        {
        AddTestL( LeftCBA, REP( Down, i ), KeyOK, TEND );
        }
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdTestEikBgftyAndEikBtgpcL  || aCmd > EBCTestCmdMaxOutline )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the
    // control created in PrepareCaseL.
    switch ( aCmd )
        {
        case EBCTestCmdTestEikBgftyAndEikBtgpcL:
            TestEikBgftyAndEikBtgpcL();
            break;
        case EBCTestCmdTestEikButbAndEikCbaL:
            TestEikButbAndEikCbaL();
            break;
        case EBCTestCEikCommandButtonL:
            TestCEikCommandButtonL();
            break;
        case EBCTestCEikTwoPictureCmdL:
            TestCEikTwoPictureCmdL();
            break;
        case EBCTestCEikInverterCmdL:
            TestCEikInverterCmdL();
            break;
        case EBCTestCEikTextBtnL:
            TestCEikTextBtnL();
            break;
        case EBCTestCEikBitmapBtnL:
            TestCEikBitmapBtnL();
            break;
        case EBCTestCEikLabeledBtnL:
            TestCEikLabeledBtnL();
            break;
        case EBCTestMnbutAndBtgpsAndBtgrpL:
            TestMnbutAndBtgpsAndBtgrpL();
            break;
         case EBCTestCba:
            TestCbaButtonL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestEikBgftyAndEikBtgpcL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestEikBgftyAndEikBtgpcL()
    {
    // Test some API for class EikButtonGroupFactory
    TBCTestCommandObserver commandObserver;
    TInt resourceId = R_BCTESTBUTTONS_MENU;

    RWindowGroup& parentWg = iEnv->RootWin();
    TUint flags = 0;

    EikButtonGroupFactory::TCreationData creationData(
        CEikButtonGroupContainer::EView, &commandObserver,
        resourceId, &parentWg, flags,
        CEikButtonGroupContainer::EVertical );
    _LIT( KTCreationData, "TCreationData test" );
    AssertTrueL( ETrue, KTCreationData );

    // Test some API for class CEikButtonGroupFactoryArray
    CEikButtonGroupFactoryArray::AppendFactoryFunctionL(
        CEikCoCtlLibrary::ButtonGroupFactory() );
    _LIT( KAppendFactoryFunctionL, "AppendFactoryFunctionL test" );
    AssertTrueL( ETrue, KAppendFactoryFunctionL );

    CEikButtonGroupFactoryArray::RemoveFactoryFunction(
        CEikCoCtlLibrary::ButtonGroupFactory() );
    _LIT( KRemoveFactoryFunction, "RemoveFactoryFunction test" );
    AssertTrueL( ETrue, KRemoveFactoryFunction );

    // Test some API for class CEikButtonGroupContainer
    TInt resourceIdForToolbar = R_BCTESTBUTTONS_TOOLBAR;
    CEikButtonGroupContainer* buttonGroupContainer1 =
        CEikButtonGroupContainer::NewL( CEikButtonGroupContainer::EView,
        CEikButtonGroupContainer::EVertical, &commandObserver,
        resourceIdForToolbar, CEikButtonGroupContainer::EAddToStack );
    CleanupStack::PushL( buttonGroupContainer1 );
    _LIT( KNewL, "NewL test" );
    AssertTrueL( ETrue, KNewL );
    CleanupStack::PopAndDestroy( buttonGroupContainer1 );

    CEikButtonGroupContainer* buttonGroupContainer2 =
        CEikButtonGroupContainer::NewL( CEikButtonGroupContainer::EView,
        CEikButtonGroupContainer::EVertical, &commandObserver,
        resourceIdForToolbar, *iContainer,
        CEikButtonGroupContainer::EAddToStack);
    CleanupStack::PushL( buttonGroupContainer2 );
    _LIT( KNewLWithCCoeControl, "NewL WithCCoeControl test" );
    AssertTrueL( ETrue, KNewLWithCCoeControl );
    CleanupStack::PopAndDestroy( buttonGroupContainer2 );


    CEikButtonGroupContainer* buttonGroupContainer3 =
        CEikButtonGroupContainer::NewL( CEikButtonGroupContainer::EView,
        CEikButtonGroupContainer::EVertical, &commandObserver,
        resourceIdForToolbar, parentWg,
        CEikButtonGroupContainer::EAddToStack );
    CleanupStack::PushL( buttonGroupContainer3 );
    _LIT( KNewLWithRWindowGroup, "NewL With RWindowGroup test" );
    AssertTrueL( ETrue, KNewLWithRWindowGroup );
    CleanupStack::PopAndDestroy( buttonGroupContainer3 );

    CEikButtonGroupContainer* buttonGroupContainer4 =
        CEikButtonGroupContainer::Current();

    _LIT( KCurrent, "Current test" );
    AssertTrueL( ETrue, KCurrent );

    TInt resourceIdForCba = R_BCTESTBUTTONS_CBA_OPTIONS_NEXT;
    buttonGroupContainer4->SetCommandSetL( resourceIdForCba );
    _LIT( KSetCommandSetL, "SetCommandSetL test" );
    AssertTrueL( ETrue, KSetCommandSetL );

    buttonGroupContainer4->AddCommandSetToStackL( resourceIdForCba );
    _LIT( KAddCommandSetToStackL, "AddCommandSetToStackL test" );
    AssertTrueL( ETrue, KAddCommandSetToStackL );

    TInt commandId = EAknSoftkeyOptions;
    TInt position = buttonGroupContainer4->PositionById( commandId );
    _LIT( KPositionById, "PositionById test" );
    AssertTrueL( ETrue, KPositionById );

  // SetCommand Testing Starts
    
 //    _LIT( KButtonIconFile1, "c:\\resource\\apps\\BCTestButtons.mbm" );
    TInt normal0 = 0;
    TInt normal1 = 1;
    CFbsBitmap * normalBitmap1;
    CFbsBitmap * normalBitmap2;
    _LIT( KSetSample, "Sample" );
    TBufC<16> tbSample;
    tbSample = KSetSample;
    
  	TBufC<64> tbBMPFileName;
 	tbBMPFileName = KButtonIconFile1;


	buttonGroupContainer4->SetCommandL(position, EAknSoftkeyOptions, KPositionById);
    buttonGroupContainer4->SetCommandSetL( resourceIdForCba );
    _LIT( KSetCommand1, "SetCommand 1 test" );
    AssertTrueL( ETrue, KSetCommand1 );
    

    normalBitmap1 = AknIconUtils::CreateIconL( KButtonIconFile1, normal0 );
    CleanupStack::PushL( normalBitmap1 );
    normalBitmap2 = AknIconUtils::CreateIconL( KButtonIconFile1, normal1 );
    CleanupStack::PushL( normalBitmap2 );
	buttonGroupContainer4->SetCommandL(position, EAknSoftkeyOptions, *normalBitmap1, *normalBitmap2);
    buttonGroupContainer4->SetCommandSetL( resourceIdForCba );
    _LIT( KSetCommand2, "SetCommand 2 test" );
    AssertTrueL( ETrue, KSetCommand2 );
    CleanupStack::PopAndDestroy(normalBitmap2);
    CleanupStack::PopAndDestroy(normalBitmap1);

    


    normalBitmap1 = AknIconUtils::CreateIconL( KButtonIconFile1, normal0 );
    CleanupStack::PushL( normalBitmap1 );
    normalBitmap2 = AknIconUtils::CreateIconL( KButtonIconFile1, normal1 );
    CleanupStack::PushL( normalBitmap2 );
 	buttonGroupContainer4->SetCommandL(position, EAknSoftkeyOptions, tbSample, *normalBitmap1, *normalBitmap2);
    buttonGroupContainer4->SetCommandSetL( resourceIdForCba );
    _LIT( KSetCommand3, "SetCommand 3 test" );
    AssertTrueL( ETrue, KSetCommand3 );
    CleanupStack::PopAndDestroy(normalBitmap2);
    CleanupStack::PopAndDestroy(normalBitmap1);


 	buttonGroupContainer4->SetCommandL(position, resourceIdForCba);
    buttonGroupContainer4->SetCommandSetL( resourceIdForCba );
    _LIT( KSetCommand6, "SetCommand 6 test" );
    AssertTrueL( ETrue, KSetCommand6 );
 
 	buttonGroupContainer4->SetCommandL(EAknSoftkeyOptions, tbSample);
    buttonGroupContainer4->SetCommandSetL( resourceIdForCba );
    _LIT( KSetCommand7, "SetCommand 7 test" );
    AssertTrueL( ETrue, KSetCommand7 );
 
    normalBitmap1 = AknIconUtils::CreateIconL( KButtonIconFile1, normal0 );
    CleanupStack::PushL( normalBitmap1 );
    normalBitmap2 = AknIconUtils::CreateIconL( KButtonIconFile1, normal1 );
    CleanupStack::PushL( normalBitmap2 );
 	buttonGroupContainer4->SetCommandL(EAknSoftkeyOptions, *normalBitmap1, *normalBitmap2);
    buttonGroupContainer4->SetCommandSetL( resourceIdForCba );
    _LIT( KSetCommand8, "SetCommand 8 test" );
    AssertTrueL( ETrue, KSetCommand8 );
 
 	buttonGroupContainer4->SetCommandL(EAknSoftkeyOptions, tbSample, *normalBitmap1, *normalBitmap2);
    buttonGroupContainer4->SetCommandSetL( resourceIdForCba );
    _LIT( KSetCommand9, "SetCommand 9 test" );
    AssertTrueL( ETrue, KSetCommand9 );
    CleanupStack::PopAndDestroy(normalBitmap2);
    CleanupStack::PopAndDestroy(normalBitmap1);


  // SetCommand Testing Ends

 
 // AddCommand Testing Starts

  	TRAPD(err, buttonGroupContainer4->AddCommandL (position, EAknSoftkeyOptions, tbSample));
  	if(err != KErrNotSupported)
  		User::Leave(err);
    _LIT( KAddCommand1, "AddCommand 1 test" );
    AssertTrueL( ETrue, KAddCommand1 );

 
    normalBitmap1 = AknIconUtils::CreateIconL( KButtonIconFile1, normal0 );
    CleanupStack::PushL( normalBitmap1 );
    normalBitmap2 = AknIconUtils::CreateIconL( KButtonIconFile1, normal1 );
    CleanupStack::PushL( normalBitmap2 );
 	TRAP(err, buttonGroupContainer4->AddCommandL (position, EAknSoftkeyOptions, *normalBitmap1, *normalBitmap2));
  	if(err != KErrNotSupported)
  		User::Leave(err);
    _LIT( KAddCommand2, "AddCommand 2 test" );
    AssertTrueL( ETrue, KAddCommand2 );
    CleanupStack::PopAndDestroy(normalBitmap2);
    CleanupStack::PopAndDestroy(normalBitmap1);

 
    normalBitmap1 = AknIconUtils::CreateIconL( KButtonIconFile1, normal0 );
    CleanupStack::PushL( normalBitmap1 );
    normalBitmap2 = AknIconUtils::CreateIconL( KButtonIconFile1, normal1 );
    CleanupStack::PushL( normalBitmap2 );
 	TRAP(err, buttonGroupContainer4->AddCommandL (position, EAknSoftkeyOptions, tbSample, *normalBitmap1, *normalBitmap2));
  	if(err != KErrNotSupported)
  		User::Leave(err);
    _LIT( KAddCommand3, "AddCommand 3 test" );
    AssertTrueL( ETrue, KAddCommand3 );
    CleanupStack::PopAndDestroy(normalBitmap2);
    CleanupStack::PopAndDestroy(normalBitmap1);

 	TRAP(err, buttonGroupContainer4->AddCommandL (position, EAknSoftkeyOptions, tbBMPFileName, normal0, normal1));
  	if(err != KErrNotSupported)
  		User::Leave(err);
    _LIT( KAddCommand4, "AddCommand 4 test" );
    AssertTrueL( ETrue, KAddCommand4 );

 	TRAP(err, buttonGroupContainer4->AddCommandL (position, EAknSoftkeyOptions, tbSample, tbBMPFileName, normal0, normal1));
  	if(err != KErrNotSupported)
  		User::Leave(err);
    _LIT( KAddCommand5, "AddCommand 5 test" );
    AssertTrueL( ETrue, KAddCommand5 );
// AddCommand Testing Ends

 
// AddCommandToStack Testing Starts
 	buttonGroupContainer4->AddCommandToStackL(position, EAknSoftkeyOptions, tbSample);
    buttonGroupContainer4->RemoveCommandFromStack( position, EAknSoftkeyOptions);
    _LIT( KAddCommandToStack1, "AddCommandToStack 1 test" );
    AssertTrueL( ETrue, KAddCommandToStack1 );
   
    
    normalBitmap1 = AknIconUtils::CreateIconL( KButtonIconFile1, normal0 );
    CleanupStack::PushL( normalBitmap1 );
    normalBitmap2 = AknIconUtils::CreateIconL( KButtonIconFile1, normal1 );
    CleanupStack::PushL( normalBitmap2 );
 	buttonGroupContainer4->AddCommandToStackL (position, EAknSoftkeyOptions, *normalBitmap1, *normalBitmap2);
    buttonGroupContainer4->RemoveCommandFromStack( position, EAknSoftkeyOptions);
    _LIT( KAddCommandToStack2, "AddCommandToStack 2 test" );
    AssertTrueL( ETrue, KAddCommandToStack2 );
    CleanupStack::PopAndDestroy(normalBitmap2);
    CleanupStack::PopAndDestroy(normalBitmap1);

    normalBitmap1 = AknIconUtils::CreateIconL( KButtonIconFile1, normal0 );
    CleanupStack::PushL( normalBitmap1 );
    normalBitmap2 = AknIconUtils::CreateIconL( KButtonIconFile1, normal1 );
    CleanupStack::PushL( normalBitmap2 );
 	buttonGroupContainer4->AddCommandToStackL (position, EAknSoftkeyOptions, tbSample, *normalBitmap1, *normalBitmap2);
    buttonGroupContainer4->RemoveCommandFromStack( position, EAknSoftkeyOptions);
    _LIT( KAddCommandToStack3, "AddCommandToStack 3 test" );
    AssertTrueL( ETrue, KAddCommandToStack3 );
    CleanupStack::PopAndDestroy(normalBitmap2);
    CleanupStack::PopAndDestroy(normalBitmap1);


 

 	buttonGroupContainer4->AddCommandToStackL(position, resourceIdForCba);
    buttonGroupContainer4->RemoveCommandFromStack( position, EAknSoftkeyOptions);
    _LIT( KAddCommandToStack6, "AddCommandToStack 6 test" );
    AssertTrueL( ETrue, KAddCommandToStack6 );
 
 
    _LIT( KOptions, "Options" );
	buttonGroupContainer4->SetCommandL(position, EAknSoftkeyOptions, KOptions);
// AddCommandToStack Testing ends
    buttonGroupContainer4->RemoveCommandFromStack( position, commandId);
    _LIT( KRemoveCommandFromStack, "RemoveCommandFromStack test" );
    AssertTrueL( ETrue, KRemoveCommandFromStack );

    buttonGroupContainer4->SetDefaultCommand( commandId );
    _LIT( KSetDefaultCommand, "SetDefaultCommand test" );
    AssertTrueL( ETrue, KSetDefaultCommand );

    TSize size1 = buttonGroupContainer4->CalcMinimumSizeL( resourceIdForCba );
    _LIT( KCalcMinimumSizeL, "CalcMinimumSizeL test" );
    AssertTrueL( ETrue, KCalcMinimumSizeL );

    buttonGroupContainer4->CleanupCommandPushL( position );
    _LIT( KCleanupCommandPushL, "CleanupCommandPushL test" );
    AssertTrueL( ETrue, KCleanupCommandPushL );

    TInt countForCleanupCommandPop = 1;
    buttonGroupContainer4->CleanupCommandPop( countForCleanupCommandPop );
    _LIT( KCleanupCommandPop, "CleanupCommandPop test" );
    AssertTrueL( ETrue, KCleanupCommandPop );
// CleanupCommand Test Starts
    buttonGroupContainer4->CleanupCommandPushL( position );
    buttonGroupContainer4->CleanupCommandPop( );
    _LIT( KCleanupCommandPopInline, "CleanupCommandPop inline test" );
    AssertTrueL( ETrue, KCleanupCommandPopInline );
    

    buttonGroupContainer4->AddCommandSetToStackL( resourceIdForCba );
    buttonGroupContainer4->CleanupCommandPushL( position );
    buttonGroupContainer4->CleanupCommandPopAndDestroy ( );
    _LIT( KCleanupCommandPopAndDestroy1, "CleanupCommandPopAndDestroy 1 inline test" );
    AssertTrueL( ETrue, KCleanupCommandPopAndDestroy1 );
    

    buttonGroupContainer4->AddCommandSetToStackL( resourceIdForCba );
    buttonGroupContainer4->CleanupCommandPushL( position );
    buttonGroupContainer4->CleanupCommandPopAndDestroy (1);
    _LIT( KCleanupCommandPopAndDestroy2, "CleanupCommandPopAndDestroy 2 inline test" );
    AssertTrueL( ETrue, KCleanupCommandPopAndDestroy2 );
    
// CleanupCommand Test Ends

// ButtonGroupType Test Starts

	CEikButtonGroupContainer::TUse bgtType = buttonGroupContainer4->ButtonGroupType();
    _LIT( KButtonGroupType, "ButtonGroupType inline test" );
    AssertTrueL( ETrue, KButtonGroupType );

// ButtonGroupType Test Ends




    TInt maxCommands = buttonGroupContainer4->MaxCommands();
    _LIT( KMaxCommands, "MaxCommands test" );
    AssertTrueL( ETrue, KMaxCommands );

    TInt buttonCount = buttonGroupContainer4->ButtonCount();
    _LIT( KButtonCount, "ButtonCount test" );
    AssertTrueL( ETrue, KButtonCount );

    TBool dimmed = ETrue;
    buttonGroupContainer4->DimCommand( commandId, dimmed );
    _LIT( KDimCommand, "DimCommand test" );
    AssertTrueL( ETrue, KDimCommand );

    TBool isCommandDimmed = buttonGroupContainer4->IsCommandDimmed( commandId );
    _LIT( KIsCommandDimmed, "IsCommandDimmed test" );
    AssertTrueL( ETrue, KIsCommandDimmed );

    TBool visible = ETrue;
    buttonGroupContainer4->MakeCommandVisible( commandId, visible );
     _LIT( KMakeCommandVisible, "MakeCommandVisible test" );
    AssertTrueL( ETrue, KMakeCommandVisible );

    TBool isCommandVisible = buttonGroupContainer4->IsCommandVisible( commandId );
    _LIT( KIsCommandVisible, "IsCommandVisible test" );
    AssertTrueL( ETrue, KIsCommandVisible );

    buttonGroupContainer4->AnimateCommand( commandId );
    _LIT( KAnimateCommand1, "AnimateCommand test" );
    AssertTrueL( ETrue, KAnimateCommand1 );
#ifdef __S60_32__

//Test Cases for 3.2 Start
    CEikButtonGroupContainer::TCommandPosition commandPosition = CEikButtonGroupContainer::ELeftSoftkeyPosition;
    TBool dimmedByPosition = ETrue;
    
    buttonGroupContainer4->DimCommandByPosition( commandPosition, dimmedByPosition );
    _LIT( KDimCommandByPosition, "DimCommandByPosition test" );
    AssertTrueL( ETrue, KDimCommandByPosition );

    buttonGroupContainer4->IsCommandDimmedByPosition( commandPosition );
    _LIT( KIsCommandDimmedByPosition, "IsCommandDimmedByPosition test" );
    AssertTrueL( ETrue, KIsCommandDimmedByPosition );

    buttonGroupContainer4->MakeCommandVisibleByPosition( commandPosition, dimmedByPosition );
    _LIT( KMakeCommandVisibleByPosition, "MakeCommandVisibleByPosition test" );
    AssertTrueL( ETrue, KMakeCommandVisibleByPosition );

    buttonGroupContainer4->IsCommandVisibleByPosition( commandPosition );
    _LIT( KIsCommandVisibleByPosition, "IsCommandVisibleByPosition test" );
    AssertTrueL( ETrue, KIsCommandVisibleByPosition );

    buttonGroupContainer4->AnimateCommandByPosition( commandPosition );
    _LIT( KAnimateCommandByPosition, "AnimateCommandByPosition test" );
    AssertTrueL( ETrue, KAnimateCommandByPosition );

    buttonGroupContainer4->UpdatedCommandObserverExists( commandPosition );
    _LIT( KUpdatedCommandObserverExists, "UpdatedCommandObserverExists test" );
    AssertTrueL( ETrue, KUpdatedCommandObserverExists );


//Test Cases for 3.2 Ends

#endif /* __S60_32__ */



    CEikButtonGroupContainer::TLocation location =
        buttonGroupContainer4->Location();
    _LIT( KLocation, "Location test" );
    AssertTrueL( ETrue, KLocation );

#ifndef _DEBUG
    CEikCommandButton* commandButton1 =
        buttonGroupContainer4->CommandButtonOrNull( commandId );
    CleanupStack::PushL( commandButton1 );
    _LIT( KCommandButtonOrNull, "CommandButtonOrNull test" );
    AssertTrueL( ETrue, KCommandButtonOrNull );
    CleanupStack::PopAndDestroy( commandButton1 );
#endif

    TRect rect = iContainer->Rect();
    buttonGroupContainer4->SetBoundingRect( rect );
    _LIT( KSetBoundingRect, "SetBoundingRect test" );
    AssertTrueL( ETrue, KSetBoundingRect );

    buttonGroupContainer4->ReduceRect( rect );
    _LIT( KReduceRect, "ReduceRect test" );
    AssertTrueL( ETrue, KReduceRect );

    CCoeControl* coeControl =
        buttonGroupContainer4->ControlOrNull( commandId );
    _LIT( KControlOrNull, "ControlOrNull test" );
    AssertTrueL( ETrue, KControlOrNull );

#ifndef _DEBUG
    CEikCommandButton* commandbutton2 =
        buttonGroupContainer4->ButtonById( commandId );
    _LIT( KButtonById, "ButtonById test" );
    AssertTrueL( ETrue, KButtonById );
#endif

    TInt keyId = 1;
    buttonGroupContainer4->UpdateHotKey( commandId,
        CEikButtonGroupContainer::EShowHotKey, keyId);
    _LIT( KUpdateHotKey, "UpdateHotKey test" );
    AssertTrueL( ETrue, KUpdateHotKey );

    TInt pos = 1;
    buttonGroupContainer4->UpdateCommandObserverL( pos, commandObserver );
    _LIT( KUpdateCommandObserverL, "UpdateCommandObserverL test" );
    AssertTrueL( ETrue, KUpdateCommandObserverL );

    buttonGroupContainer4->RemoveCommandObserver( pos );
    _LIT( KRemoveCommandObserver, "RemoveCommandObserver test" );
    AssertTrueL( ETrue, KRemoveCommandObserver );

    TBool delayActivation = buttonGroupContainer4->DelayActivation();
    _LIT( KDelayActivation, "DelayActivation test" );
    AssertTrueL( ETrue, KDelayActivation );

    TSize minimumSize1 = buttonGroupContainer4->MinimumSize();
    _LIT( KMinimumSize1, "MinimumSize test" );
    AssertTrueL( ETrue, KMinimumSize1 );

    TKeyEvent keyEvent1 = { EKeyPause, EStdKeySpace, 0, 0  };
    TKeyResponse keyresponse =
        buttonGroupContainer4->OfferKeyEventL( keyEvent1, EEventKey );
    _LIT( KOfferKeyEventL1, "OfferKeyEventL test" );
    AssertTrueL( ETrue, KOfferKeyEventL1 );

    RFs& tempServer = iEnv->FsSession();
    tempServer.Delete( KStreamName );
    RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer,
        KStreamName, EFileWrite ) );
    CleanupClosePushL( fWrite );
    buttonGroupContainer4->WriteInternalStateL( fWrite );
    CleanupStack::PopAndDestroy( &fWrite );
    tempServer.Delete( KStreamName );
    _LIT( KWriteInternalStateL1, "WriteInternalStateLtest test" );
    AssertTrueL( ETrue, KWriteInternalStateL1);

    buttonGroupContainer4->Reserved_MtsmPosition();
    _LIT( KReserved_MtsmPosition, "Reserved_MtsmPosition" );
    AssertTrueL( ETrue, KReserved_MtsmPosition );

    buttonGroupContainer4->Reserved_MtsmObject();
     _LIT( KReserved_MtsmObject, "Reserved_MtsmObject test" );
    AssertTrueL( ETrue, KReserved_MtsmObject );

    TBool isCommandInGroup = buttonGroupContainer4->IsCommandInGroup( commandId );
    _LIT( KIsCommandInGroup, "IsCommandInGroup test" );
    AssertTrueL( ETrue, KIsCommandInGroup );

    buttonGroupContainer4->ReplaceCommand( commandId, resourceIdForCba );
    _LIT( KReplaceCommand, "ReplaceCommand test" );
    AssertTrueL( ETrue, KReplaceCommand );
    }

// --------------------------------------------------------------------------
// TBCTestCommandObserver::ProcessCommandL
// ---------------------------------------------------------------------------
//
void TBCTestCommandObserver::ProcessCommandL( TInt )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestEikButbAndEikCbaL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestEikButbAndEikCbaL()
    {
    // Test some API for class TEikButtonCoordinator
    TEikButtonCoordinator coordinator;
    _LIT( KTEikButtonCoordinator, "TEikButtonCoordinator test" );
    AssertTrueL( ETrue, KTEikButtonCoordinator );

    CEikButtonBase* chosenButton = new( ELeave ) CEikButtonBase();
    CleanupStack::PushL( chosenButton );
    coordinator.SetChosenButton( chosenButton );
     _LIT( KSetChosenButton, "SetChosenButton test" );
    AssertTrueL( ETrue, KSetChosenButton );
    CleanupStack::PopAndDestroy( chosenButton );
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::SetupCommandBtnL
// ---------------------------------------------------------------------------
//
CEikCommandButton* CBCTestButtonsCase::SetupCommandBtnL()
    {
    //1. just new
    CEikCommandButton* commandButton = new( ELeave )CEikCommandButton();
    CleanupStack::PushL( commandButton );

    //2. construct from res
    TResourceReader reader1;
    iEnv->CreateResourceReaderLC( reader1, R_BCTESTBUTTONS_CMBUT );
    commandButton->ConstructFromResourceL( reader1 );
    _LIT( KConstructFromResourceL1, "ConstructFromResourceL test" );
    AssertTrueL( ETrue, KConstructFromResourceL1 );
    CleanupStack::PopAndDestroy(); //reader1

    return commandButton;
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TeardownCommandBtnL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TeardownCommandBtnL(CEikCommandButton* aBtn)
    {
    CleanupStack::PopAndDestroy( aBtn );
    _LIT( KDesCommandButton, "~CommandButton() test" );
    AssertTrueL( ETrue, KDesCommandButton );
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestSetBtnLayoutL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestSetBtnLayoutL()
    {
    CEikCommandButton* commandButton = SetupCommandBtnL();

    commandButton->SetButtonLayout( CEikCommandButton::ETextRightPictureLeft );
    _LIT( KSetButtonLayout, "TSetButtonLayout test" );
    AssertTrueL( ETrue, KSetButtonLayout);

    TeardownCommandBtnL(commandButton);
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestExcessSpace
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestExcessSpace()
    {
    CEikCommandButton* commandButton = SetupCommandBtnL();

    commandButton->SetExcessSpace( CEikCommandButton::EShare );
    _LIT( KSetExcessSpace, "SetExcessSpace test" );
    AssertTrueL( ETrue, KSetExcessSpace );

    TeardownCommandBtnL(commandButton);
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestStuff
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestStuff()
    {
    CEikCommandButton* commandButton = SetupCommandBtnL();

    _LIT( KText, "xxxxxxxxx" );
    commandButton->SetTextL( KText );
    _LIT( KSetTextL1, "SetTextL test" );
    AssertTrueL( ETrue, KSetTextL1 );

    CEikLabel* label = commandButton->Label();
    _LIT( KLabel1, "Label test" );
    AssertTrueL( ETrue, KLabel1 );

    commandButton->SetDisplayContent( CEikCommandButton::ETextOnly );
    _LIT( KSetDisplayContent, "SetDisplayContent test" );
    AssertTrueL( ETrue, KSetDisplayContent );

    TeardownCommandBtnL(commandButton);
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestImgBtnL()
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestImgBtnL()
    {
    CEikCommandButton* commandButton = SetupCommandBtnL();

 //   _LIT( KButtonIconFile1, "c:\\resource\\apps\\BCTestButtons.mbm" );
    TInt normal1 = 1;
    CFbsBitmap * normalBitmap1 = AknIconUtils::CreateIconL( KButtonIconFile1, normal1 );
    CleanupStack::PushL( normalBitmap1 );

    commandButton->SetPictureL( normalBitmap1, NULL );
    _LIT( KSetPictureL1, "SetPictureL test" );
    AssertTrueL( ETrue, KSetPictureL1 );

    CEikImage* image = commandButton->Picture();
    _LIT( KPicture, "Picture test" );
    AssertTrueL( ETrue, KPicture );

    CleanupStack::Pop(normalBitmap1);

    TeardownCommandBtnL(commandButton);
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestStackRelatedL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestStackRelatedL()
    {
    // stack realated have issues
    CEikCommandButton* commandButton = SetupCommandBtnL();

 //   _LIT( KButtonIconFile2, "c:\\resource\\apps\\BCTestButtons.mbm" );
    TInt normal2 = 1;
    CFbsBitmap * normalBitmap2 = AknIconUtils::CreateIconL( KButtonIconFile1, normal2 );
    CleanupStack::PushL( normalBitmap2 );

    TInt commandId2 = EProgCmdAutoTest;
    TBuf<10> buf2 = _L( "xxxxxxx" );
    commandButton->AddCommandToStackL( commandId2, &buf2, normalBitmap2, normalBitmap2 );
    _LIT( KAddCommandToStackL, "AddCommandToStackL test" );
    AssertTrueL( ETrue, KAddCommandToStackL );

    CleanupStack::Pop( normalBitmap2 );

    TBool removeCommandFromStack = commandButton->RemoveCommandFromStack( R_BCTESTBUTTONS_CBA_OPTIONS_NEXT );
    _LIT( KRemoveCommandFromStack, "RemoveCommandFromStack test" );
    AssertTrueL( ETrue, KRemoveCommandFromStack );

    TInt popCommandFromStack = commandButton->PopCommandFromStack();
    _LIT( KPopCommandFromStack, "PopCommandFromStack test" );
    AssertTrueL( ETrue, KPopCommandFromStack );

    TeardownCommandBtnL(commandButton);
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestCommandButtonBaseL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestCommandButtonBaseL()
    {
    CEikCommandButton* commandButton = SetupCommandBtnL();

    commandButton->CEikCommandButtonBase::LayoutComponents();
    _LIT( KLayoutComponents,
        "LayoutComponents for CEikCommandButtonBase test" );
    AssertTrueL( ETrue, KLayoutComponents );

    commandButton->CEikCommandButtonBase::SetDefault( ETrue );
    _LIT( KSetDefault, "SetDefault for CEikCommandButtonBase test" );
    AssertTrueL( ETrue, KSetDefault );

    /*iCmdBtnBase = new( ELeave )CBCTestCmdBtnBase();
    iContainer->SetControl( iCmdBtnBase );
    _LIT( KDraw, "Draw for CEikCommandButtonBase test" );
    AssertTrueL( ETrue, KDraw );*/

    commandButton->CEikCommandButtonBase::FocusChanged( ENoDrawNow );
    _LIT( KFocusChanged, "FocusChanged for CEikCommandButtonBase test" );
    AssertTrueL( ETrue, KFocusChanged );

    CArrayFixFlat<TCoeColorUse>* colorUseList2 =
        new( ELeave ) CArrayFixFlat<TCoeColorUse>( 1 );
    TCoeColorUse colorUse2;
    colorUseList2->AppendL( colorUse2 );
    commandButton->CEikCommandButtonBase::GetColorUseListL( *colorUseList2 );
    CleanupStack::PushL( colorUseList2 );
    _LIT( KGetColorUseListL2,
        "GetColorUseListL for CEikCommandButtonBase test" );
    AssertTrueL( ETrue, KGetColorUseListL2 );
    CleanupStack::PopAndDestroy( colorUseList2 );

    TKeyEvent keyEvent3 = { EKeyPause, EStdKeySpace, 0, 0  };
    TKeyResponse keyResponse =
        commandButton->CEikCommandButtonBase::OfferKeyEventL(
        keyEvent3, EEventNull );
    _LIT( KOfferKeyEventL3, "OfferKeyEventL for CEikCommandButtonBase test" );
    AssertTrueL( ETrue, KOfferKeyEventL3 );

    commandButton->CEikCommandButtonBase::ActivateL();
    _LIT( KActivateL2, "ActivateL for CEikCommandButtonBase test" );
    AssertTrueL( ETrue, KActivateL2 );

    commandButton->CEikCommandButtonBase::UpdateComponentAlignment();
    _LIT( KUpdateComponentAlignment,
        "UpdateComponentAlignment for CEikCommandButtonBase test" );
    AssertTrueL( ETrue, KUpdateComponentAlignment );


    TeardownCommandBtnL(commandButton);
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestButtonBaseL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestButtonBaseL()
    {
    CEikCommandButton* commandButton = SetupCommandBtnL();

    CBCTestBtnBase* btnBase = new( ELeave )CBCTestBtnBase();
    CleanupStack::PushL( btnBase );

    CEikButtonBase* buttonBase = new( ELeave ) CEikButtonBase();
    CleanupStack::PushL( buttonBase );
    btnBase->CEikButtonBase::CopyDrawStateTo( buttonBase );
    CleanupStack::PopAndDestroy( buttonBase );
    _LIT( KCopyDrawStateTo, "CopyDrawStateTo for CEikButtonBase test" );
    AssertTrueL( ETrue, KCopyDrawStateTo );

    TBool isPressed = btnBase->CEikButtonBase::IsPressed();
    _LIT( KIsPressed, "IsPressed for CEikButtonBase test" );
    AssertTrueL( ETrue, KIsPressed );

    btnBase->CEikButtonBase::SetAllowTristate();
    _LIT( KSetAllowTristate, "SetAllowTristate for CEikButtonBase test" );
    AssertTrueL( ETrue, KSetAllowTristate );

    CleanupStack::PopAndDestroy( btnBase );

    CArrayFixFlat<TCoeColorUse>* colorUseList3 =
        new( ELeave ) CArrayFixFlat<TCoeColorUse>( 1 );
    TCoeColorUse colorUse3;
    colorUseList3->AppendL( colorUse3 );
    commandButton->CEikButtonBase::GetColorUseListL( *colorUseList3 );
    CleanupStack::PushL( colorUseList3 );
    _LIT( KGetColorUseListL3,
        "GetColorUseListL for CEikButtonBase test" );
    AssertTrueL( ETrue, KGetColorUseListL3 );
    CleanupStack::PopAndDestroy( colorUseList3 );

    TCoeInputCapabilities capabilities =
        commandButton->CEikButtonBase::InputCapabilities();
    _LIT( KInputCapabilities, "InputCapabilities for CEikButtonBase test" );
    AssertTrueL( ETrue, KInputCapabilities );

    TKeyEvent keyEvent4 = { EKeyPause, EStdKeySpace, 0, 0  };
    TKeyResponse keyResponse4 =
        commandButton->CEikButtonBase::OfferKeyEventL(
        keyEvent4, EEventNull );
    _LIT( KOfferKeyEventL4, "OfferKeyEventL for CEikButtonBase test" );
    AssertTrueL( ETrue, KOfferKeyEventL4 );

    TEikButtonCoordinator butCoord;
    commandButton->CEikButtonBase::SetCoordinator( &butCoord );
    _LIT( KSetCoordinator, "SetCoordinator for CEikButtonBase test" );
    AssertTrueL( ETrue, KSetCoordinator );

    commandButton->CEikButtonBase::SetIgnoreNextPointerUp();
    _LIT( KSetIgnoreNextPointerUp, "SetIgnoreNextPointerUp for CEikButtonBase test" );
    AssertTrueL( ETrue, KSetIgnoreNextPointerUp );

    TeardownCommandBtnL(commandButton);
    }
// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestCEikCommandButton
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestCEikCommandButtonL()
    {
    // Test some API for class CEikCommandButtonBase
    TestSetBtnLayoutL();
    TestExcessSpace();
    TestStuff();
    TestImgBtnL();
    TestCommandButtonBaseL();
    TestButtonBaseL();

    CEikCommandButton* commandButton = SetupCommandBtnL();

//    _LIT( KButtonIconFile1, "c:\\resource\\apps\\BCTestButtons.mbm" );
    TInt normal1 = 1;
    CFbsBitmap * normalBitmap1 = AknIconUtils::CreateIconL( KButtonIconFile1, normal1 );
    CleanupStack::PushL( normalBitmap1 );

    TInt commandId = R_BCTESTBUTTONS_CBA_OPTIONS_NEXT;
    TBuf<10> buf = _L( "xxxxxxx" );
    commandButton->SetCommandL( commandId, &buf, normalBitmap1, normalBitmap1 );
    _LIT( KSetCommandL, "SetCommandL test" );
    AssertTrueL( ETrue, KSetCommandL );

    CleanupStack::Pop(normalBitmap1);

    TPointerEvent pointerEvent1 = { TPointerEvent::EButton1Up,
         EModifierAutorepeatable, TPoint( 20,20 ), TPoint( 0,0 ) };
    commandButton->HandlePointerEventL( pointerEvent1 );
    _LIT( KHandlePointerEventL1, "HandlePointerEventL test" );
    AssertTrueL( ETrue, KHandlePointerEventL1 );

    commandButton->UpdateComponentAlignment();
    _LIT( KUpdateComponentAlignment, "UpdateComponentAlignment test" );
    AssertTrueL( ETrue, KUpdateComponentAlignment );

    commandButton->SetPictureFromFileL( AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_marked_add, EMbmAvkonQgn_indi_marked_add_mask );
    _LIT( KSetPictureFromFileL1, "SetPictureFromFileL test" );
    AssertTrueL( ETrue, KSetPictureFromFileL1 );

    TestStackRelatedL();

    TeardownCommandBtnL(commandButton);
    }

CEikTwoPictureCommandButton* CBCTestButtonsCase::SetupTwoPictureCmdL()
    {
    //1. just new
    CEikTwoPictureCommandButton* twoPictureCommandButton =
        new( ELeave ) CEikTwoPictureCommandButton();
    CleanupStack::PushL( twoPictureCommandButton );
    _LIT( KCEikTwoPictureCommandButton, "CEikTwoPictureCommandButton() test" );
    AssertTrueL( ETrue, KCEikTwoPictureCommandButton );

    //2. construct from res
    TResourceReader reader2;
    iEnv->CreateResourceReaderLC( reader2, R_BCTESTBUTTONS_PICMBUT );
    twoPictureCommandButton->ConstructFromResourceL( reader2 );
    _LIT( KConstructFromResourceL2,
        "ConstructFromResourceL For CEikTwoPictureCommandButton test" );
    AssertTrueL( ETrue, KConstructFromResourceL2 );
    CleanupStack::PopAndDestroy(); //reader2

    return twoPictureCommandButton;
    }

void CBCTestButtonsCase::TeardownTwoPictureCmdL(CEikTwoPictureCommandButton* aBtn)
    {
    CleanupStack::PopAndDestroy( aBtn );
    _LIT( KDesCEikTwoPictureCommandButton, "~CEikTwoPictureCommandButton() test" );
    AssertTrueL( ETrue, KDesCEikTwoPictureCommandButton );
    }

void CBCTestButtonsCase::TestSetTwoPicturesL()
    {
    CEikTwoPictureCommandButton* twoPictureCommandButton = SetupTwoPictureCmdL();

//    _LIT( KButtonIconFile2, "c:\\resource\\apps\\BCTestButtons.mbm" );
    TInt normal2 = 1;
    CFbsBitmap * normalBitmap2 = AknIconUtils::CreateIconL( KButtonIconFile1, normal2 );
    CleanupStack::PushL( normalBitmap2 );

    twoPictureCommandButton->SetTwoPicturesL( normalBitmap2, NULL, NULL, NULL);
    _LIT( KSetTwoPicturesL, "SetTwoPicturesL test" );
    AssertTrueL( ETrue, KSetTwoPicturesL );

    CleanupStack::Pop(normalBitmap2);
    TeardownTwoPictureCmdL( twoPictureCommandButton );
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestCEikTwoPictureCmd
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestCEikTwoPictureCmdL()
    {
    // Test some API for class CEikTwoPictureCommandButton
    CEikTwoPictureCommandButton* twoPictureCommandButton = SetupTwoPictureCmdL();

    TestSetTwoPicturesL();

    TBool isSecondPictureOwnedExternally =
        twoPictureCommandButton->IsSecondPictureOwnedExternally();
    _LIT( KIsSecondPictureOwnedExternally, "IsSecondPictureOwnedExternally test" );
    AssertTrueL( ETrue, KIsSecondPictureOwnedExternally );

    CEikImage* eikImage =  twoPictureCommandButton->Picture();
    _LIT( KPicture2, "Picture test" );
    AssertTrueL( ETrue, KPicture2 );

    _LIT( KText2,"xxxxxxxxxx" );
    twoPictureCommandButton->SetTextL( KText2 );
    _LIT( KSetTextL2, "SetTextL For CEikTwoPictureCommandButton test" );
    AssertTrueL( ETrue, KSetTextL2 );

//    _LIT( KButtonIconFile3, "c:\\resource\\apps\\BCTestButtons.mbm" );
    TInt normal3 = 1;
    CFbsBitmap * normalBitmap3 = AknIconUtils::CreateIconL( KButtonIconFile1, normal3 );
    CleanupStack::PushL( normalBitmap3 );

    twoPictureCommandButton->SetSecondPicture( normalBitmap3, NULL );
    _LIT( KSetSecondPicture3, "SetSecondPicture test" );
    AssertTrueL( ETrue, KSetSecondPicture3 );

    CleanupStack::Pop(normalBitmap3);

    twoPictureCommandButton->SetSecondPictureOwnedExternally( EFalse );
    _LIT( KSetSecondPictureOwnedExternally, "SetSecondPictureOwnedExternally test" );
    AssertTrueL( ETrue, KSetSecondPictureOwnedExternally );

    twoPictureCommandButton->ActivateL();
    _LIT( KActivateL1, "ActivateL test" );
    AssertTrueL( ETrue, KActivateL1 );

    TPointerEvent pointerEvent2 = { TPointerEvent::EButton1Up,
         EModifierAutorepeatable, TPoint( 20,20 ), TPoint( 0,0 ) };
    twoPictureCommandButton->HandlePointerEventL( pointerEvent2 );
    _LIT( KHandlePointerEventL2,
        "HandlePointerEventL For CEikTwoPictureCommandButton test" );
    AssertTrueL( ETrue, KHandlePointerEventL2 );

    CBCTestTwoPicture* twoPicture = new( ELeave ) CBCTestTwoPicture();
    CleanupStack::PushL( twoPicture );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTBUTTONS_PICMBUT );
    twoPicture->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader

    _LIT( KStreamName2, "c:\\BCTestLog\\buttontest.txt" );
    RFs& tempServer2 = iEnv->FsSession();
    tempServer2.Delete( KStreamName2 );
    RFileWriteStream fWrite2;
    User::LeaveIfError( fWrite2.Create( tempServer2,
        KStreamName2, EFileWrite ) );
    CleanupClosePushL( fWrite2 );
    twoPicture->WriteInternalStateL( fWrite2 );
    CleanupStack::PopAndDestroy( &fWrite2 );
    CleanupStack::PopAndDestroy( twoPicture );
    _LIT( KWriteInternalStateL2, "WriteInternalStateL test" );
    AssertTrueL( ETrue, KWriteInternalStateL2 );


    TeardownTwoPictureCmdL( twoPictureCommandButton );

    }

CEikInverterCommandButton* CBCTestButtonsCase::SetupInverterCmdL()
    {
    //1. just new
    CEikInverterCommandButton* inverterCommandButton = new( ELeave ) CEikInverterCommandButton();
    CleanupStack::PushL( inverterCommandButton );
    _LIT( KCEikInverterCommandButton, "CEikInverterCommandButton test" );
    AssertTrueL( ETrue, KCEikInverterCommandButton );

    return inverterCommandButton;
    }

void CBCTestButtonsCase::TeardownInverterCmdL(CEikInverterCommandButton* aBtn)

    {
    CleanupStack::PopAndDestroy( aBtn );
    _LIT( KDesCEikInverterCommandButton, "~CEikInverterCommandButton() test" );
    AssertTrueL( ETrue, KDesCEikInverterCommandButton );
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestCEikInverterCmdL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestCEikInverterCmdL()
    {
    // Test some API for class CEikInverterCommandButton
    CEikInverterCommandButton* inverterCommandButton = SetupInverterCmdL();

    TPointerEvent pointerEvent3 = { TPointerEvent::EButton1Up,
         EModifierAutorepeatable, TPoint( 20,20 ), TPoint( 0,0 ) };
    inverterCommandButton->HandlePointerEventL( pointerEvent3 );
    _LIT( KHandlePointerEventL3, "HandlePointerEventL For CEikInverterCommandButton test" );
    AssertTrueL( ETrue, KHandlePointerEventL3 );

    CBCTestInverterCmdButton* inverterBtn = new( ELeave ) CBCTestInverterCmdButton();
    CleanupStack::PushL( inverterBtn );
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTBUTTONS_CMBUT );
    inverterBtn->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader

    _LIT( KStreamName2, "c:\\BCTestLog\\buttontest.txt" );
    RFs& tempServer2 = iEnv->FsSession();
    tempServer2.Delete( KStreamName2 );
    RFileWriteStream fWrite2;
    User::LeaveIfError( fWrite2.Create( tempServer2,
        KStreamName2, EFileWrite ) );
    CleanupClosePushL( fWrite2 );
    inverterBtn->WriteInternalStateL( fWrite2 );
    CleanupStack::PopAndDestroy( &fWrite2 );
    //WriteInternalStateL(RWriteStream& aWriteStream)
    CleanupStack::PopAndDestroy( inverterBtn );
    _LIT( KWriteInternalStateL3, "WriteInternalStateL test" );
    AssertTrueL( ETrue, KWriteInternalStateL3 );

    TeardownInverterCmdL( inverterCommandButton );
    }

CEikTextButton* CBCTestButtonsCase::SetupTextBtnL()
    {
    //1. just new
    CEikTextButton* textButton = new( ELeave ) CEikTextButton();
    CleanupStack::PushL( textButton );
    _LIT( KCEikTextButton, "CEikTextButton test" );
    AssertTrueL( ETrue, KCEikTextButton );
    //2. construct from res
    TResourceReader reader3;
    iEnv->CreateResourceReaderLC( reader3, R_BCTESTBUTTONS_TXTBUT );
    textButton->ConstructFromResourceL( reader3 );
    _LIT( KConstructFromResourceL3, "ConstructFromResourceL For CEikTextButton test" );
    AssertTrueL( ETrue, KConstructFromResourceL3 );
    CleanupStack::PopAndDestroy(); //reader3
    return textButton;
    }

void CBCTestButtonsCase::TeardownTextBtnL( CEikTextButton* aBtn )

    {
    CleanupStack::PopAndDestroy( aBtn );
    _LIT( KDesCEikTextButton, "~CEikTextButton() test" );
    AssertTrueL( ETrue, KDesCEikTextButton );
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestCEikTextBtnL()
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestCEikTextBtnL()
    {
    // Test some API for class CEikTextButton
    CEikTextButton* textButton = SetupTextBtnL();

    _LIT( KText3, "xxxxxxxxxxx" );
    textButton->SetTextL( KText3, CEikCommandButtonBase::EFirst );
    _LIT( KSetTextL3, "SetTextL For CEikTextButton test" );
    AssertTrueL( ETrue, KSetTextL3 );

    CEikLabel* label2 = textButton->Label( CEikCommandButtonBase::EFirst );
    _LIT( KLabel2, "Label test" );
    AssertTrueL( ETrue, KLabel2 );

    TPointerEvent pointerEvent4 = { TPointerEvent::EButton1Up,
         EModifierAutorepeatable, TPoint( 20,20 ), TPoint( 0,0 ) };
    textButton->HandlePointerEventL( pointerEvent4 );
    _LIT( KHandlePointerEventL4, "HandlePointerEventL For CEikTextButton test" );
    AssertTrueL( ETrue, KHandlePointerEventL4 );

    TeardownTextBtnL( textButton );
    }

CEikBitmapButton* CBCTestButtonsCase::SetupBitmapBtnL()
    {
    //1. just new
    CEikBitmapButton* bitmapButton = new( ELeave ) CEikBitmapButton();
    CleanupStack::PushL( bitmapButton );
    _LIT( KCEikBitmapButton, "CEikBitmapButton test" );
    AssertTrueL( ETrue, KCEikBitmapButton );
    //2. construct from res
    TResourceReader reader4;
    iEnv->CreateResourceReaderLC( reader4, R_BCTESTBUTTONS_BMPBUT );
    bitmapButton->ConstructFromResourceL( reader4 );
    _LIT( KConstructFromResourceL4, "ConstructFromResourceL For CEikBitmapButton test" );
    AssertTrueL( ETrue, KConstructFromResourceL4 );
    CleanupStack::PopAndDestroy();//reader4

    return bitmapButton;
    }
void CBCTestButtonsCase::TeardownBitmapBtnL( CEikBitmapButton* aBtn )
    {
    CleanupStack::PopAndDestroy( aBtn );
    _LIT( KDesCEikBitmapButton, "~CEikBitmapButton test" );
    AssertTrueL( ETrue, KDesCEikBitmapButton );
    }
// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestCEikBitmapBtnL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestCEikBitmapBtnL()
    {
    CEikBitmapButton* bitmapButton = SetupBitmapBtnL();

    // Test some API for class CEikBitmapButton
//    _LIT( KButtonIconFile3, "c:\\resource\\apps\\BCTestButtons.mbm" );
    TInt normal3 = 1;
    CFbsBitmap * normalBitmap3 = AknIconUtils::CreateIconL(
        KButtonIconFile1, normal3 );
    CleanupStack::PushL( normalBitmap3 );

    bitmapButton->SetPictureL( normalBitmap3, NULL,
        CEikCommandButtonBase::EFirst );
    _LIT( KSetPictureL3, "SetPictureL for CEikBitmapButton test" );
    AssertTrueL( ETrue, KSetPictureL3 );

    CleanupStack::Pop( normalBitmap3 );

    bitmapButton->SetPictureFromFileL( KButtonIconFile1,
        EMbmBctestbuttonsSampleicon, EMbmBctestbuttonsSampleiconmask,
        CEikCommandButtonBase::ESecond );
    _LIT( KBitmapBtn1, "CEikBitmapButton::SetPictureFromFileL" );
    AssertTrueL( ETrue, KBitmapBtn1 );

    CEikImage* picture = bitmapButton->Picture( CEikCommandButtonBase::EFirst );
    _LIT( KPicture1, "Picture For CEikTextButton test" );
    AssertTrueL( ETrue, KPicture1 );


    TPointerEvent pointerEvent5 = { TPointerEvent::EButton1Up,
         EModifierAutorepeatable, TPoint( 20,20 ), TPoint( 0,0 ) };
    bitmapButton->HandlePointerEventL( pointerEvent5 );
    _LIT( KHandlePointerEventL5, "HandlePointerEventL For CEikBitmapButton test" );
    AssertTrueL( ETrue, KHandlePointerEventL5 );

    TeardownBitmapBtnL( bitmapButton );
    }

CEikLabeledButton* CBCTestButtonsCase::SetupLabeledBtnLC()
    {
    //1. just new
    CEikLabeledButton* labeledButton = new( ELeave ) CEikLabeledButton();
    CleanupStack::PushL( labeledButton );
    _LIT( KCEikLabeledButton, "CEikLabeledButton test" );
    AssertTrueL( ETrue, KCEikLabeledButton );

    //2. construct from res
    TInt hotKeyCode = 1;
    TInt flags = 1;
    CEikCommandButton* commandButton = new( ELeave )CEikCommandButton();
    CleanupStack::PushL( commandButton );
    labeledButton->ConstructL( commandButton, hotKeyCode, flags );
    _LIT( KConstructL, "ConstructL For CEikLabelButton test" );
    AssertTrueL( ETrue, KConstructL );
    CleanupStack::Pop( commandButton );
    CleanupStack::PopAndDestroy( labeledButton );

    labeledButton = new( ELeave ) CEikLabeledButton();
    CleanupStack::PushL( labeledButton );
    TResourceReader reader5;
    iEnv->CreateResourceReaderLC( reader5, R_BCTESTBUTTONS_LBBUT );
    labeledButton->ConstructFromResourceL( reader5 );
    _LIT( KConstructFromResourceL5, "ConstructFromResourceL For CEikLabeledButton test" );
    AssertTrueL( ETrue, KConstructFromResourceL5 );
    CleanupStack::PopAndDestroy(); //reader5

    return labeledButton;
    }

void CBCTestButtonsCase::TeardownLabeledBtnL( CEikLabeledButton* aBtn )
    {
    CleanupStack::PopAndDestroy( aBtn );
    _LIT( KDesCEikLabeledButton, "~CEikLabeledButton test" );
    AssertTrueL( ETrue, KDesCEikLabeledButton );
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestCEikLabeledBtnL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestCEikLabeledBtnL()
    {
    // Test some API for class CEikLabeledButton
    CEikLabeledButton* labeledButton = SetupLabeledBtnLC();

    CEikCommandButtonBase* commandButtonBase = labeledButton->Button();
    _LIT( KButton, "Button test" );
    AssertTrueL( ETrue, KButton );

    CEikLabel* label3 = labeledButton->Label();
    _LIT( KLabel3, "Label For CEikLabeledButton test" );
    AssertTrueL( ETrue, KLabel3 );

    TInt hotKeyCode2 = labeledButton->HotKeyCode();
    _LIT( KHotKeyCode2, "HotKeyCode For CEikLabeledButton test" );
    AssertTrueL( ETrue, KHotKeyCode2 );

    TBool showsHotKey = labeledButton->ShowsHotKey();
    _LIT( KShowsHotKey, "ShowsHotKey test" );
    AssertTrueL( ETrue, KShowsHotKey );

    TBool plainHotKey = labeledButton->PlainHotKey();
    _LIT( KPlainHotKey, "PlainHotKey test" );
    AssertTrueL( ETrue, KPlainHotKey );

    labeledButton->Animate();
    _LIT( KAnimate1, "Animate test" );
    AssertTrueL( ETrue, KAnimate1 );

    labeledButton->UpdateHotKey( EAknSoftkeyOk, CEikLabeledButton::EShowHotKey );
    _LIT( KUpdateHotKey2, "UpdateHotKeytest" );
    AssertTrueL( ETrue, KUpdateHotKey2 );

    TKeyEvent keyEvent2 = { EKeyPause, EStdKeySpace, 0, 0  };
    TKeyResponse keyResponse = labeledButton->OfferKeyEventL( keyEvent2, EEventNull );
    _LIT( KOfferKeyEventL2, "OfferKeyEventL For CeikLabeledButton test" );
    AssertTrueL( ETrue, KOfferKeyEventL2 );

    TSize size2 = labeledButton->MinimumSize();
    _LIT( KMinimumSize2, "MinimumSize test" );
    AssertTrueL( ETrue, KMinimumSize2 );

    labeledButton->SetContainerWindowL( *iContainer );
    _LIT( KSetContainerWindowL, "SetContainerWindowL test" );
    AssertTrueL( ETrue, KSetContainerWindowL );

    labeledButton->SetDimmed( ETrue );
    _LIT( KSetDimmed, "SetDimmed test" );
    AssertTrueL( ETrue, KSetDimmed );

    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) CArrayFixFlat<TCoeColorUse>( 1 );
    TCoeColorUse colorUse;
    colorUseList->AppendL( colorUse );
    labeledButton->GetColorUseListL( *colorUseList );
    CleanupStack::PushL( colorUseList );
    _LIT( KGetColorUseListL, "GetColorUseListL test" );
    AssertTrueL( ETrue, KGetColorUseListL );
    CleanupStack::PopAndDestroy( colorUseList );

    TInt type = 1;
    labeledButton->HandleResourceChange( type );
    _LIT( KHandleResourceChange, "HandleResourceChange test" );
    AssertTrueL( ETrue, KHandleResourceChange );

    TCoeInputCapabilities inputCapablilities = labeledButton->InputCapabilities();
    _LIT( KInputCapabilities, "InputCapabilities test" );
    AssertTrueL( ETrue, KInputCapabilities );


    TPointerEvent pointerEvent6 = { TPointerEvent::EButton1Up,
         EModifierAutorepeatable, TPoint( 20,20 ), TPoint( 0,0 ) };
    labeledButton->HandlePointerEventL( pointerEvent6 );
    _LIT( KHandlePointerEventL6, "HandlePointerEventL test" );
    AssertTrueL( ETrue, KHandlePointerEventL6 );

    TeardownLabeledBtnL( labeledButton );
    }


// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestMnbutAndBtgpsAndBtgrpL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestMnbutAndBtgpsAndBtgrpL()
    {
    // Test some API for class CEikMenuButton
    CBCTestMenuButton* menuButton = new( ELeave ) CBCTestMenuButton();
    CleanupStack::PushL( menuButton );
    _LIT( KCEikMenuButton, "CEikMenuButton test" );
    AssertTrueL( ETrue, KCEikMenuButton );

    menuButton->SetContainerWindowL( *iContainer );

    TResourceReader reader6;
    iEnv->CreateResourceReaderLC( reader6, R_BCTESTBUTTONS_MNBUT );
    menuButton->ConstructFromResourceL( reader6 );
    _LIT( KConstructFromResourceL6, "ConstructFromResourceL For CEikMenuButton test" );
    AssertTrueL( ETrue, KConstructFromResourceL6 );
    CleanupStack::PopAndDestroy(); //reader6

    menuButton->SetMenuPaneId( R_BCTESTBUTTONS_MENU );
    _LIT( KSetMenuPaneId, "SetMenuPaneId test" );
    AssertTrueL( ETrue, KSetMenuPaneId );

    TBCTestMenuObserver menuObserver;
    menuButton->LaunchPopupMenuL( &menuObserver );
    _LIT( KLaunchPopupMenuL, "LaunchPopupMenuL test" );
    AssertTrueL( ETrue, KLaunchPopupMenuL );

    menuButton->Animate();
    _LIT( KAnimate2, "Animatet For CEikMenuButton test" );
    AssertTrueL( ETrue, KAnimate2 );

    RFs& tempServer = iEnv->FsSession();
    tempServer.Delete( KStreamName );
    RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer,
        KStreamName, EFileWrite ) );
    CleanupClosePushL( fWrite );
    menuButton->WriteInternalStateL( fWrite );
    CleanupStack::PopAndDestroy( &fWrite );
    tempServer.Delete( KStreamName );
    _LIT( KMenuWriteInternal, "CEikMenuButton::WriteInternalStateL" );
    AssertTrueL( ETrue, KMenuWriteInternal );

    TPointerEvent pointerEvent7 = { TPointerEvent::EButton1Up,
         EModifierAutorepeatable, TPoint( 20,20 ), TPoint( 0,0 ) };
    menuButton->HandlePointerEventL( pointerEvent7 );
    _LIT( KHandlePointerEventL7, "HandlePointerEventL For CEikMenuButton test" );
    AssertTrueL( ETrue, KHandlePointerEventL7 );

     CleanupStack::PopAndDestroy( menuButton );
    _LIT( KDesCEikMenuButton, "~CEikMenuButton() test" );
    AssertTrueL( ETrue, KDesCEikMenuButton );

    // Test some API for class CEikButtonGroupStack
    TSize minimumSize3 = CEikButtonGroupStack::MinimumSize();
     _LIT( KMinimumSize, "MinimumSizetest For CEikMenuButton" );
    AssertTrueL( ETrue, KMinimumSize );
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsCase::TestCbaButtonL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsCase::TestCbaButtonL()
{
    _LIT( KSetButtonGroupFlags, " SetButtonGroupFlags " );
    _LIT( KSetSkinBackgroundId, " SetSkinBackgroundId " );
    _LIT( KOfferCommandListL, " OfferCommandListL( array )" );
    _LIT( KOfferCommandListResL, " OfferCommandListL( resource ) " );
    _LIT( KIsCommandInGroup, " IsCommandInGroup " );
    _LIT( KReplaceCommand, " ReplaceCommand " );
    _LIT( KHandlePointerEventL, "HandlePointerEventL" );
    
    TInt resourceid = R_BCTESTBUTTONS_MENU;
    TBCTestCommandObserver commandobserver;
    
    RWindowGroup& parentwg = iEnv->RootWin();
    TUint flags = 0;

    EikButtonGroupFactory::TCreationData creationData(
        CEikButtonGroupContainer::EView, &commandobserver,
        resourceid, &parentwg, flags, CEikButtonGroupContainer::EVertical );
     
    TInt toolbarresid = R_BCTESTBUTTONS_TOOLBAR;
    
    CEikButtonGroupContainer* buttongroup1 = CEikButtonGroupContainer::NewL( 
        CEikButtonGroupContainer::EView, CEikButtonGroupContainer::EVertical, 
        &commandobserver, toolbarresid, parentwg,
        CEikButtonGroupContainer::EAddToStack );
    CleanupStack::PushL( buttongroup1 );
    CleanupStack::PopAndDestroy( buttongroup1 );

    CEikButtonGroupContainer* buttongroup = CEikButtonGroupContainer::Current();
    
    CEikCba *eikcba = static_cast<CEikCba*>( buttongroup->ButtonGroup() );
    
    eikcba->SetButtonGroupFlags( 0 );
    AssertTrueL( ETrue, KSetButtonGroupFlags );
    
    eikcba->SetSkinBackgroundId( KAknsIIDQsnBgAreaControlIdle );
    AssertTrueL( ETrue, KSetSkinBackgroundId );
    
    TInt toolbarresourceid = R_BCTESTBUTTONS_CBA_OPTIONS_NEXT;
    TInt commandid = EAknSoftkeyOptions;
    TInt res;
    
    RArray<TInt> arr;
    arr.Append( commandid );
    TRAP( res, eikcba->OfferCommandListL( arr ) );
    AssertTrueL( ETrue, KOfferCommandListL );
    arr.Close();
    
    eikcba->IsCommandInGroup( commandid );
    AssertTrueL( ETrue, KIsCommandInGroup );
    eikcba->ReplaceCommand( commandid, toolbarresourceid );
    AssertTrueL( ETrue, KReplaceCommand );
   
    TRAP( res, eikcba->OfferCommandListL( commandid ) );
    AssertTrueL( ETrue, KOfferCommandListResL );
    
    CEikCbaButton* cbabutton = (CEikCbaButton*) buttongroup->ControlOrNull(commandid);
    TPointerEvent pevent = { TPointerEvent::EButton1Up,
         EModifierCapsLock, TPoint( 0,0 ), TPoint( 0,0 ) };   
    TRAP( res, cbabutton->HandlePointerEventL( pevent ) );
    AssertTrueL( ETrue, KHandlePointerEventL );
    
    	
	
}

// --------------------------------------------------------------------------
// TBCTestMenuObserver::SetEmphasis
// ---------------------------------------------------------------------------
//
void TBCTestMenuObserver::SetEmphasis( CCoeControl*, TBool )
    {
    }
// --------------------------------------------------------------------------
// TBCTestMenuObserver::ProcessCommandL
// ---------------------------------------------------------------------------
//
void TBCTestMenuObserver::ProcessCommandL( TInt )
    {

    }







