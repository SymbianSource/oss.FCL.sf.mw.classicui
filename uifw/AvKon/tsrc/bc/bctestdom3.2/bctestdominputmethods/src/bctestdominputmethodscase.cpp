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


 // INCLUDE FILES
#include <w32std.h>
#include <coecntrl.h>
#include <pticore.h>
#include <peninputclient.h>
#include <ptihwrrecognizer.h>
#include <ptiengine.h> 
#include <ptiuserdicentry.h> 
#include <peninputserverhandler.h>
#include <peninputgenericitutcustomization.h>

#include "bctestdompeninputclient.h"
#include "bctestdominputmethodscase.h"
#include "bctestdominputmethodscontainer.h"
#include "bctestdominputmethods.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomInputMethodsCase* CBCTestDomInputMethodsCase::NewL( 
    CBCTestDomInputMethodsContainer* aContainer )
    {
    CBCTestDomInputMethodsCase* self = new( ELeave ) CBCTestDomInputMethodsCase( 
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
CBCTestDomInputMethodsCase::CBCTestDomInputMethodsCase( 
    CBCTestDomInputMethodsContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomInputMethodsCase::~CBCTestDomInputMethodsCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomInputMethodsCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomInputMethodsCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomInputMethodsCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL(DELAY(1), LeftCBA, KeyOK,TEND);    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomInputMethodsCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomInputMethodsCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
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
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestDomInputMethodsCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestDomInputMethodsCase::PrepareCaseL( TInt aCmd )
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
// CBCTestDomInputMethodsCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestDomInputMethodsCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestDomInputMethodsCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestDomInputMethodsCase::TestFunctionL() //memory leak, TestPtiCoreL(); 
    {
    TestPenInputServerHandlerL();
    TestRPeninputServerL();  
    TestPtiCoreL();
    TestCHwrRecognizerL();
    }

void CBCTestDomInputMethodsCase::TestPenInputServerHandlerL()
    {
    CPenInputServerHandler* penISH = CPenInputServerHandler::NewL();
    CleanupStack::PushL( penISH );//push
    _LIT( msiLogNewL, "CPenInputServerHandler::NewL()" );
    AssertNotNullL( penISH, msiLogNewL );
    
    penISH->ConnectServer();
    _LIT( msiLogConnect, "CPenInputServerHandler::ConnectServer()" );
    AssertTrueL( ETrue, msiLogConnect );
 
    penISH->SetUiLayout( 0 );
    _LIT( msiLogSetUi, "CPenInputServerHandler::SetUiLayout()" );
    AssertTrueL( ETrue, msiLogSetUi );

    penISH->ActivateUiLayout( EFalse );
    _LIT( msiLogActivateUi, "CPenInputServerHandler::ActivateUiLayout()" );
    AssertTrueL( ETrue, msiLogActivateUi );

    penISH->SendCommandToServer( 0 );
    _LIT( msiLogSendCommand1, "CPenInputServerHandler::SendCommandToServer(TInt)" );
    AssertTrueL( ETrue, msiLogSendCommand1 );

    penISH->SendCommandToServer( 0, 0 );
    _LIT( msiLogSendCommand2, "CPenInputServerHandler::SendCommandToServer(TInt,TInt)" );
    AssertTrueL( ETrue, msiLogSendCommand2 );

    TBuf<10> param;
    penISH->SendCommandToServer( 0, param );
    _LIT( msiLogSendCommand3, "CPenInputServerHandler::SendCommandToServer(TInt,TDesC&)" );
    AssertTrueL( ETrue, msiLogSendCommand3 );

    //TItutBmp itutBmp;
    //TItutKey itutkey(0, itutBmp, itutBmp, itutBmp, itutBmp, 0);
    //penISH->SendNewKeyToServer( 0, itutkey );
    //_LIT( msiLogSendCommand4, "CPenInputServerHandler::SendCommandToServer(TInt,TItutKey&)" );
    //AssertTrueL( ETrue, msiLogSendCommand4 );

    TFepInputContextFieldData data;
    penISH->SetIcfText( data );
    _LIT( msiLogSetIcfText, "CPenInputServerHandler::SetIcfText()" );
    AssertTrueL( ETrue, msiLogSetIcfText );

    //TItutPromptText promptText;
    //penISH->SendPromptTextToServer( 0, promptText );
    //_LIT( msiLogSendPrompt, "CPenInputServerHandler::SendPromptTextToServer()" );
    //AssertTrueL( ETrue, msiLogSendPrompt );

    penISH->DisconnectServer();
    _LIT( msiLogDisconnect, "CPenInputServerHandler::DisconnectServer()" );
    AssertTrueL( ETrue, msiLogDisconnect );
    
    CleanupStack::PopAndDestroy( penISH );
    _LIT( msiLogDes, "CPenInputServerHandler::~CPenInputServerHandler()" );
    AssertTrueL( ETrue, msiLogDes );

    }


// ---------------------------------------------------------------------------
// CBCTestDomInputMethodsCase::TestRPeninputServerL
// ---------------------------------------------------------------------------
//   
void CBCTestDomInputMethodsCase::TestRPeninputServerL()
    {
    //RPeninputServer didn't init private data(two points), 
    //so, use User::AllocZL alloc mem and init points.
    RPeninputServer* penInput = 
    static_cast<RPeninputServer*>( User::AllocZL( sizeof( RPeninputServer ) ) );
    CleanupStack::PushL( penInput );//push
    
    TInt error = penInput->Connect(); 
    _LIT( msiLogConnect, "RPeninputServer::Connect()" );
    AssertTrueL( ETrue, msiLogConnect );
   
    penInput->Version();
    _LIT( msiLogVersion, "RPeninputServer::Version()" );
    AssertTrueL( ETrue, msiLogVersion );
    
    TInt cmd = 0;
    TBuf8<10> buf;
    
    penInput->HandleCommand( cmd );
    _LIT( msiLogHandleCommand, "RPeninputServer::HandleCommand()" );
    AssertTrueL( ETrue, msiLogHandleCommand );
    
    penInput->HandleCommand( cmd, buf );
    _LIT( msiLogHandleCommand2, "RPeninputServer::HandleCommand( , )" );
    AssertTrueL( ETrue, msiLogHandleCommand2 );
    
    penInput->HandleCommand( cmd, buf, cmd );
    _LIT( msiLogHandleCommand3, "RPeninputServer::HandleCommand( , ,)" );
    AssertTrueL( ETrue, msiLogHandleCommand3 );
    
    penInput->IsVisible();
    _LIT( msiLogIsVisible, "RPeninputServer::IsVisible()" );
    AssertTrueL( ETrue, msiLogIsVisible );
    
    const TUid testUid =  { 0x174657FC };
    penInput->SetUiLayoutId( testUid );
    _LIT( msiLogSetUiLayoutId, "RPeninputServer::SetUiLayoutId()" );
    AssertTrueL( ETrue, msiLogSetUiLayoutId );
    
    penInput->SetUiLayoutId( testUid, buf );
    _LIT( msiLogSetUiLayoutId2, "RPeninputServer::SetUiLayoutId( , )" );
    AssertTrueL( ETrue, msiLogSetUiLayoutId2 );
    
    TPoint pos;
    penInput->SetUiLayoutPos( pos );
    _LIT( msiLogSetUiLayoutPos, "RPeninputServer::SetUiLayoutPos()" );
    AssertTrueL( ETrue, msiLogSetUiLayoutPos );
    
    penInput->UiLayoutPos(); 
    _LIT( msiLogUiLayoutPos, "RPeninputServer::UiLayoutPos()" );
    AssertTrueL( ETrue, msiLogUiLayoutPos );
    
    penInput->ResourceChanged( cmd );
    _LIT( msiLogResourceChanged, "RPeninputServer::ResourceChanged()" );
    AssertTrueL( ETrue, msiLogResourceChanged );
    
    penInput->ActivateLayout( EFalse );
    _LIT( msiLogActivateLayout, "RPeninputServer::ActivateLayout()" );
    AssertTrueL( ETrue, msiLogActivateLayout );
    
    TBuf<10> buf16;
    penInput->GetServerEventData( buf16 );
    _LIT( msiLogGetServerEventData, "RPeninputServer::GetServerEventData()" );
    AssertTrueL( ETrue, msiLogGetServerEventData );
    
    penInput->ServerEventDataNum();
    _LIT( msiLogServerEventDataNum, "RPeninputServer::ServerEventDataNum()" );
    AssertTrueL( ETrue, msiLogServerEventDataNum );

    
    TDisplayMode displayMode = EGray2;
    penInput->SetDisplayMode( displayMode, displayMode );
    _LIT( msiLogSetDisplayMode, "RPeninputServer::SetDisplayMode();" );
    AssertTrueL( ETrue, msiLogSetDisplayMode );
 
    penInput->ClearServerEvent();
    _LIT( msiLogClearServerEvent, "RPeninputServer::ClearServerEvent();" );
    AssertTrueL( ETrue, msiLogClearServerEvent );

    TInt language = 1;
    TInt pluginMode = 0;
    RArray<TInt> implmentationIds;
    penInput->GetImePluginIdListL( language, pluginMode, implmentationIds);
    _LIT( msiLogGetImePluginIdListL, "RPeninputServer::GetImePluginIdListL();" );
    AssertTrueL( ETrue, msiLogGetImePluginIdListL );
    
    penInput->SetForeground( EFalse );
    _LIT( msiLogSetForeground, "RPeninputServer::SetForeground()" );
    AssertTrueL( ETrue, msiLogSetForeground );
 
    penInput->IsForeground();
    _LIT( msiLogIsForeground, "RPeninputServer::IsForeground()" );
    AssertTrueL( ETrue, msiLogIsForeground );

    CMPenUiA* penUi = new( ELeave ) CMPenUiA();
    CleanupStack::PushL( penUi );//push

    CPenUiNotificationHandler* handler= CPenUiNotificationHandler::NewL( penUi ,penInput);
    CleanupStack::PushL( handler );//push
    
    penInput->AddPeninputServerObserverL( handler );
    _LIT( msiLogAddPSO, "RPeninputServer::AddPeninputServerObserverL()" );
    AssertTrueL( ETrue, msiLogAddPSO );
    
    penInput->AddPenUiActivationHandler(penUi, 0);
    _LIT( msiLogAddPUH, "RPeninputServer::AddPenUiActivationHandler()" );
    AssertTrueL( ETrue, msiLogAddPUH );

    RArray<TInt> languageLists(5);
    penInput->PenSupportLanguagesL( languageLists );
    _LIT( msiLogPenSupportLanguagesL, "RPeninputServer::PenSupportLanguagesL();" );
    AssertTrueL( ETrue, msiLogPenSupportLanguagesL );

    penInput->RemovePeninputServerObserver();;
    _LIT( msiLogRemovePeninputServerObserver, "RPeninputServer::RemovePeninputServerObserver();" );
    AssertTrueL( ETrue, msiLogRemovePeninputServerObserver );
    
    penInput->RemovePenUiActivationHandler();
    _LIT( msiLogRemovePenUiActivationHandler, "RPeninputServer::RemovePenUiActivationHandler()" );
    AssertTrueL( ETrue, msiLogRemovePenUiActivationHandler );

    languageLists.Close();
    implmentationIds.Close();
    
    penInput->Close();
    _LIT( msiLogClose, "RPeninputServer::Close()" );
    AssertTrueL( ETrue, msiLogClose );
 
    CleanupStack::PopAndDestroy(3);  

    RPeninputServer penInput2 = RPeninputServer();
    _LIT( msiLogInit, "RPeninputServer::RPeninputServer()" );
    AssertTrueL( ETrue, msiLogInit );
      
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomInputMethodsCase::TestPtiCoreL
// ---------------------------------------------------------------------------
//   
void CBCTestDomInputMethodsCase::TestPtiCoreL()
    {
   
    TUid coreUid =  { 0xa00040ad };//from CBCTestDomPtiCore
    
    CBCTestDomPtiCore* ptiCore = static_cast<CBCTestDomPtiCore*>(CPtiCore::CreateCoreL( coreUid ));
    CleanupStack::PushL( ptiCore );//push
    _LIT( msiLogCreateCoreL, "CPtiCore::CreateCoreL()" );
    AssertNotNullL( ptiCore, msiLogCreateCoreL );

    ptiCore->ListCoresLC();//push
    _LIT( msiLogListCoresLC, "CPtiCore::ListCoresLC()" );
    AssertTrueL( ETrue, msiLogListCoresLC );
    
    TInt size = 16;
    HBufC8* buf=HBufC8::NewL( size );
    CleanupStack::PushL( buf );//push
    TPtrC8 ptr8 = buf->Des();
    ptiCore->SetCurrentInputSequence(ptr8);
    _LIT( msiLogSCI, "CPtiCore::SetCurrentInputSequence()" );
    AssertTrueL( ETrue, msiLogSCI );

    ptiCore->CommitCurrentWord();
    _LIT( msiLogCCW, "CPtiCore::CommitCurrentWord()" );
    AssertTrueL( ETrue, msiLogCCW );

    ptiCore->GetCurrentWord();
    _LIT( msiLogGCW, "CPtiCore::GetCurrentWord()" );
    AssertTrueL( ETrue, msiLogGCW );
    
    ptiCore->NumberOfCandidates();
    _LIT( msiLogNOC, "CPtiCore::NumberOfCandidates()" );
    AssertTrueL( ETrue, msiLogNOC );

    ptiCore->GetCandidatePage();
    _LIT( msiLogGetCandidatePage, "CPtiCore::GetCandidatePage()" );
    AssertTrueL( ETrue, msiLogGetCandidatePage );

    ptiCore->NextCandidatePage();
    _LIT( msiLogNextCandidatePage, "CPtiCore::NextCandidatePage()" );
    AssertTrueL( ETrue, msiLogNextCandidatePage );

    ptiCore->PreviousCandidatePage();
    _LIT( msiLogPCP, "CPtiCore::PreviousCandidatePage()" );
    AssertTrueL( ETrue, msiLogPCP );

    ptiCore->MoreCandidatePages();
    _LIT( msiLogMCP, "CPtiCore::MoreCandidatePages()" );
    AssertTrueL( ETrue, msiLogMCP );

    ptiCore->PhoneticSpellingCount();	
    _LIT( msiLogPSC, "CPtiCore::PhoneticSpellingCount()" );
    AssertTrueL( ETrue, msiLogPSC );

    ptiCore->SelectedPhoneticSpelling(); 
    _LIT( msiLogSPS, "CPtiCore::SelectedPhoneticSpelling()" );
    AssertTrueL( ETrue, msiLogSPS );

    ptiCore->IsToneMarkValidForSpelling();
    _LIT( msiLogITMV, "CPtiCore::IsToneMarkValidForSpelling()" );
    AssertTrueL( ETrue, msiLogITMV );

    ptiCore->CompositionData();
    _LIT( msiLogCD, "CPtiCore::CompositionData()" );
    AssertTrueL( ETrue, msiLogCD );

    TPtiCharConversion charType = EPtiUcs2ToUtf8;
    ptiCore->Convert(charType, NULL, 0, NULL);
    _LIT( msiLogConvert, "CPtiCore::Convert()" );
    AssertTrueL( ETrue, msiLogConvert );
    
    TBuf<1> tembuf;
    TPtiSpelling spellType = EPtiStrokes;
    ptiCore->GetSpelling(0,tembuf, spellType);
    _LIT( msiLogGetSpelling, "CPtiCore::GetSpelling()" );
    AssertTrueL( ETrue, msiLogGetSpelling );

    TPtiEngineInputMode inputMode = EPtiEngineInputModeNone;
    TPtiKey ptiKey = EPtiKeyNone;
    TPtiTextCase testCase = EPtiCaseLower;
    ptiCore->SetExternalKeyMapL( inputMode, ptiKey, tembuf, testCase );    
    _LIT( msiLogSEK, "CPtiCore::SetExternalKeyMapL()" );
    AssertTrueL( ETrue, msiLogSEK );

    ptiCore->GetFirstCandidate( tembuf );
    _LIT( msiLogGFC, "CPtiCore::GetFirstCandidate()" );
    AssertTrueL( ETrue, msiLogGFC );
    
    ptiCore->GetNextCandidate( tembuf );
    _LIT( msiLogGNC, "CPtiCore::GetNextCandidate()" );
    AssertTrueL( ETrue, msiLogGNC );
    
    ptiCore->GetPreviousCandidate( tembuf );
    _LIT( msiLogGPCE, "CPtiCore::GetPreviousCandidate()" );
    AssertTrueL( ETrue, msiLogGPCE );

    CPtiUserDictionary* dict = NULL;
    ptiCore->NumberOfEntriesInUserDictionary( dict );
    _LIT( msiLogUD, "CPtiCore::NumberOfEntriesInUserDictionary()" );
    AssertTrueL( ETrue, msiLogUD );
 
    ptiCore->DetachUserDictionary( dict );
    _LIT( msiLogDUD, "CPtiCore::DetachUserDictionary()" );
    AssertTrueL( ETrue, msiLogDUD );

    ptiCore->AttachUserDictionary( dict );
    _LIT( msiLogAUD, "CPtiCore::AttachUserDictionary()" );
    AssertTrueL( ETrue, msiLogAUD );

    CPtiUserDictionary* userDict = ptiCore->CreateEmptyUserDictionaryL( 512 );
    delete userDict;
    _LIT( msiLogCEUD, "CPtiCore::CreateEmptyUserDictionaryL()" );
    AssertTrueL( ETrue, msiLogCEUD );

    TPtiUserDictionaryEntry mptiUD;
    CPtiUserDictionary* dict2 = NULL;
    ptiCore->AddUserDictionaryEntry( mptiUD, dict2 );
    _LIT( msiLogAddDict, "CPtiCore::AddUserDictionaryEntry()" );
    AssertTrueL( ETrue, msiLogAddDict );

    ptiCore->GetUserDictionaryEntry( 0, mptiUD, dict2 );
    _LIT( msiLogGetDict, "CPtiCore::GetUserDictionaryEntry()" );
    AssertTrueL( ETrue, msiLogGetDict );
    
    ptiCore->RemoveUserDictionaryEntry( mptiUD, dict2 );
    _LIT( msiLogRemDict, "CPtiCore::RemoveUserDictionaryEntry()" );
    AssertTrueL( ETrue, msiLogRemDict );
    
    TBuf<10> inputStr;
    RPointerArray<HBufC> array;
    ptiCore->GetCandidatesByInputString( inputStr, array, ETrue );    
    _LIT( msiLogGetCadt, "CPtiCore::GetCandidatesByInputString()" );
    AssertTrueL( ETrue, msiLogGetCadt );
    array.Close();
    
    ptiCore->ReadingTextL();
    _LIT( msiLogReadingTextL, "CPtiCore::ReadingTextL()" );
    AssertTrueL( ETrue, msiLogReadingTextL );
 
    CDesCArray* desList = new (ELeave) CDesCArrayFlat(1);
    CleanupStack::PushL( desList );//push
    ptiCore->GetCandidateListL( *desList );
     _LIT( msiLogGCL, "CPtiCore::GetCandidateListL()" );
    AssertTrueL( ETrue, msiLogGCL );

    ptiCore->GetNextWordCandidateListL( *desList );
     _LIT( msiLogGetNextW, "CPtiCore::GetNextWordCandidateListL()" );
    AssertTrueL( ETrue, msiLogGetNextW );

    CleanupStack::PopAndDestroy( desList ); 

    ptiCore->SetCandidatePageLength( 0 );
    _LIT( msiLogSCPL, "CPtiCore::SetCandidatePageLength()" );
    AssertTrueL( ETrue, msiLogSCPL );

    ptiCore->GetPhoneticSpelling( 0 ); 
    _LIT( msiLogGet, "CPtiCore::GetPhoneticSpelling()" );
    AssertTrueL( ETrue, msiLogGet );
    
    ptiCore->SelectPhoneticSpelling( 0 );
    _LIT( msiLogSelect, "CPtiCore::GetPhoneticSpelling()" );
    AssertTrueL( ETrue, msiLogSelect );
    
    TText toneMark = 0;
    ptiCore->ToneMark( toneMark );
    _LIT( msiLogToneMark, "CPtiCore::ToneMark()" );
    AssertTrueL( ETrue, msiLogToneMark );
    
    ptiCore->SetPredictiveChineseChar( tembuf );
    _LIT( msiLogSet, "CPtiCore::SetPredictiveChineseChar()" );
    AssertTrueL( ETrue, msiLogSet );

    ptiCore->SetToneMark( 0 );
    _LIT( msiLogSetToneMark, "CPtiCore::SetToneMark()" );
    AssertTrueL( ETrue, msiLogSetToneMark );

    CleanupStack::PopAndDestroy(3);  
    ptiCore->Descecom( 1 );

    _LIT( msiLogDesc, "CPtiCore::~CPtiCore()" );
    AssertTrueL( ETrue, msiLogDesc );

    } 
    
// ---------------------------------------------------------------------------
// CBCTestDomInputMethodsCase::TestCHwrRecognizerL
// ---------------------------------------------------------------------------
//   
void CBCTestDomInputMethodsCase::TestCHwrRecognizerL()
    {
    TInt impId = 0xa00040a9;  //from CBCTestDomHwrRecognizer

    CHwrRecognizer* hwrRec =  CHwrRecognizer::NewL(impId);
    CleanupStack::PushL( hwrRec );//push
    _LIT( msiLogNewL, "CHwrRecognizer::NewL()" );
    AssertNotNullL( hwrRec, msiLogNewL );

    hwrRec->GetRange();
    _LIT( msiLogGetRange, "CHwrRecognizer::GetRange()" );
    AssertTrueL( ETrue, msiLogGetRange );

    hwrRec->GetCandidateNum();
    _LIT( msiLogGCN, "CHwrRecognizer::GetCandidateNum()" );
    AssertTrueL( ETrue, msiLogGCN );

    hwrRec->GetAuxCandidateNum();
    _LIT( msiLogGACN, "CHwrRecognizer::GetAuxCandidateNum()" );
    AssertTrueL( ETrue, msiLogGACN );

    hwrRec->StrokeEndMark();
    _LIT( msiLogSEM, "CHwrRecognizer::StrokeEndMark()" );
    AssertTrueL( ETrue, msiLogSEM );

    hwrRec->RemoveAllAuxRange();
    _LIT( msiLogRAAR, "CHwrRecognizer::RemoveAllAuxRange()" );
    AssertTrueL( ETrue, msiLogRAAR );

    hwrRec->McrBeginSessionL();
    _LIT( msiLogMBS, "CHwrRecognizer::McrBeginSessionL()" );
    AssertTrueL( ETrue, msiLogMBS );
 
    RArray<TInt> result;

    hwrRec->ListAvailableLanguagesL( result );
    _LIT( msiLogAvailL, "CHwrRecognizer::ListAvailableLanguagesL()" );
    AssertTrueL( ETrue, msiLogAvailL );

    TUid temId = { 0x10aa85f };
    hwrRec->ListGivenAvailableLanguagesL( temId, result );
    _LIT( msiLogLGL, "CHwrRecognizer::ListGivenAvailableLanguagesL()" );
    AssertTrueL( ETrue, msiLogLGL );
    result.Close();
   
    TRecognitionRange range;
    hwrRec->SetRange( range );
    _LIT( msiLogSetRange, "CHwrRecognizer::SetRange()" );
    AssertTrueL( ETrue, msiLogSetRange );
   
    hwrRec->AddAuxiliaryRange ( range );
    _LIT( msiLogAR, "CHwrRecognizer::AddAuxiliaryRange()" );
    AssertTrueL( ETrue, msiLogAR );

    hwrRec->RemoveAuxiliaryRange ( 0 );
    _LIT( msiLogRAR, "CHwrRecognizer::RemoveAuxiliaryRange()" );
    AssertTrueL( ETrue, msiLogRAR );

    hwrRec->SetCandidateNum( 0 );
    _LIT( msiLogSCN, "CHwrRecognizer::SetCandidateNum()" );
    AssertTrueL( ETrue, msiLogSCN );
    
    TSize size;
    hwrRec->SetInputAreaSize( size );
    _LIT( msiLogSIAS, "CHwrRecognizer::SetInputAreaSize()" );
    AssertTrueL( ETrue, msiLogSIAS );
  
    TBuf<10> bufVer;
    hwrRec->GetEngineVersion( bufVer );
    _LIT( msiLogGEV, "CHwrRecognizer::GetEngineVersion()" );
    AssertTrueL( ETrue, msiLogGEV );
    
    hwrRec->GetDictVersion( bufVer );
    _LIT( msiLogGDV, "CHwrRecognizer::GetDictVersion()" );
    AssertTrueL( ETrue, msiLogGDV );
    
    hwrRec->EnableWordRecognition( ETrue );
    _LIT( msiLogEWR, "CHwrRecognizer::EnableWordRecognition()" );
    AssertTrueL( ETrue, msiLogEWR );
    
    TInt intpos = 0;
    hwrRec->GetTopGuideLinePos( intpos );
    _LIT( msiLogGTGLP, "CHwrRecognizer::GetTopGuideLinePos()" );
    AssertTrueL( ETrue, msiLogGTGLP );

    hwrRec->GetBottomGuideLinePos( intpos );
    _LIT( msiLogGBGLP, "CHwrRecognizer::GetBottomGuideLinePos()" );
    AssertTrueL( ETrue, msiLogGBGLP );

    hwrRec->SetAuxCandidateNum( intpos );
    _LIT( msiLogSACN, "CHwrRecognizer::SetAuxCandidateNum()" );
    AssertTrueL( ETrue, msiLogSACN );
    
    TLanguage language = ELangTest;
    RArray<TUid> impIdList;
    hwrRec->ListImplementationsL( language, impIdList );
    _LIT( msiLogLImp, "CHwrRecognizer::ListImplementationsL()" );
    AssertTrueL( ETrue, msiLogLImp );
    impIdList.Close();
    
    TLatinLetterOrder order = ELowerFirst;
    hwrRec->SetFirstLetterOrder ( order );
    _LIT( msiLogSFLO, "CHwrRecognizer::SetFirstLetterOrder()" );
    AssertTrueL( ETrue, msiLogSFLO );
    
    TAknEditorNumericKeymap numberMode = EAknEditorStandardNumberModeKeymap;
    hwrRec->SetNumberMode( numberMode );
    _LIT( msiLogSNM, "CHwrRecognizer::SetNumberMode()" );
    AssertTrueL( ETrue, msiLogSNM );
    
    TBufC<10> symbolSet;
    hwrRec->SetPermittedSymbolSet( symbolSet );
    _LIT( msiLogSPSS, "CHwrRecognizer::SetPermittedSymbolSet()" );
    AssertTrueL( ETrue, msiLogSPSS );

    RArray<TPoint> traceData;
    RPointerArray<HBufC> aResult;
    hwrRec->Recognize( traceData, aResult );
    _LIT( msiLogRecognize, "CHwrRecognizer::Recognize()" );
    AssertTrueL( ETrue, msiLogRecognize );

    hwrRec->McrEndSessionL( aResult );
    _LIT( msiLogMES, "CHwrRecognizer::McrEndSessionL()" );
    AssertTrueL( ETrue, msiLogMES );

    hwrRec->RecognizeWithCharSet( traceData, aResult, symbolSet);
    _LIT( msiLogRecognizeW, "CHwrRecognizer::RecognizeWithCharSet()" );
    AssertTrueL( ETrue, msiLogRecognizeW );

    hwrRec->McrAddStrokesL( traceData, aResult );
     _LIT( msiLogASL, "CHwrRecognizer::McrAddStrokesL()" );
    AssertTrueL( ETrue, msiLogASL );

    THwrUdmRange scriptType;
    scriptType.iScript = 0;
    scriptType.iRange = 0;
    hwrRec->SymbolModelValid( symbolSet, traceData, scriptType, bufVer );
    _LIT( msiLogSMV, "CHwrRecognizer::SymbolModelValid()" );
    AssertTrueL( ETrue, msiLogSMV );
    traceData.Close();
  
    TUid testUid = { 0xa00040a9 }; //from CBCTestDomHwrRecognizer
    
    CHwrRecognizer* hwrRec2 = CHwrRecognizer::NewL( ELangTest, testUid );
    CleanupStack::PushL( hwrRec2 );//push
    _LIT( msiLogNewL2, "CHwrRecognizer::NewL(const TLanguage,...)" );
    AssertTrueL( ETrue, msiLogNewL2 );

    TRAPD( error, hwrRec->QueryUdmInterfaceL() )
    
    if( error )
    {
    _LIT( msiLogErr, "CHwrRecognizer::QueryUdmInterfaceL(),but leave -5!" );
    AssertTrueL( ETrue, msiLogErr );
    }
    else
    {
    _LIT( msiLogQUI, "CHwrRecognizer::QueryUdmInterfaceL()" );        
    AssertTrueL( ETrue, msiLogQUI );
    _LIT( msiLogUdm, "CHwrRecognizer::IsSupportUdm()" );        
    AssertTrueL( ETrue, msiLogUdm );
    }
    CleanupStack::PopAndDestroy( hwrRec2 ); //popAndDestory
    CleanupStack::PopAndDestroy( hwrRec );//popAndDestory

    CBCTestDomHwrRecognizer* hwrRec3 = CBCTestDomHwrRecognizer::NewL( impId );
    CleanupStack::PushL( hwrRec3 );//push
    
    hwrRec3->IsSupportUdm();
    _LIT( msiLogIsSupport, "CHwrRecognizer::IsSupportUdm()" );        
    AssertTrueL( ETrue, msiLogIsSupport );

    hwrRec3->LoadUdmL( EUdmSymbol );
    _LIT( msiLogLoadUdmL, "CHwrRecognizer::LoadUdmL()" );        
    AssertTrueL( ETrue, msiLogLoadUdmL );
    
    hwrRec3->UnLoadUdmL( EUdmSymbol );
    _LIT( msiLogUnLoadUdmL, "CHwrRecognizer::UnLoadUdmL()" );        
    AssertTrueL( ETrue, msiLogUnLoadUdmL );

    RArray<TInt> list;
    hwrRec3->GetModelIndexListL( EUdmSymbol, list, scriptType );
    _LIT( msiLogGetModel, "CHwrRecognizer::GetModelIndexListL()" );        
    AssertTrueL( ETrue, msiLogGetModel );
    list.Close();
    
    RArray<TPoint> model;
    TInt index = 0;
    TPtrC symbolName;
    hwrRec3->GetSymbolModelL( EUdmSymbol, index, symbolName, model, index, index );
    _LIT( msiLogGetSymbol, "CHwrRecognizer::GetSymbolModelL()" );        
    AssertTrueL( ETrue, msiLogGetSymbol );
    model.Close();

    CleanupStack::PopAndDestroy( hwrRec3 );//popAndDestory

    _LIT( msiLogDesc, "CHwrRecognizer::~CHwrRecognizer()" );
    AssertTrueL( ETrue, msiLogDesc);

    }

