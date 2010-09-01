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
#include <cdlrefs.h>
#include <cdlengine.h>
#include <cdlexplorer.h>
#include <cdluserpackageexplorer.h>
#include <bctestdomcdl.rsg>
#include <stringloader.h> 

#include "bctestdomcdlchangeobserver.h"
#include "bctestdomcdlcase.h"
#include "bctestdomcdlcontainer.h"
#include "bctestdomcdl.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomCdlCase* CBCTestDomCdlCase::NewL( 
    CBCTestDomCdlContainer* aContainer )
    {
    CBCTestDomCdlCase* self = new( ELeave ) CBCTestDomCdlCase( 
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
CBCTestDomCdlCase::CBCTestDomCdlCase( 
    CBCTestDomCdlContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomCdlCase::~CBCTestDomCdlCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCdlCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL(DELAY(1), LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCdlCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::RunL( TInt aCmd )
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
// CBCTestDomCdlCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::PrepareCaseL( TInt aCmd )
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
// CBCTestDomCdlCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestDomCdlCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    } 

// ---------------------------------------------------------------------------
// CBCTestDomCdlCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestDomCdlCase::TestFunctionL()
    {
    
    TestCdlRefsL();
    TestCdlInstanceL();
    TestCdlUidsL();
    TestCdlNamesL();
    TestMCdlChangeObserverL();
    TestCdlEngineL();
    TestCdlExplorerUtilsL();
    TestCCdlInstanceExplorerBaseL();
    TestCCdlUserPackageExplorerL();
    }
    
    
// ---------------------------------------------------------------------------
// CBCTestDomCdlCase::TestCdlRefsL()  
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::TestCdlRefsL()   
    {
    CCdlRefs* cdlRefs = CCdlRefs::NewL();
    CleanupStack::PushL( cdlRefs );//push
    _LIT( msiLogNewL, "CCdlRefs::NewL()" );
    AssertNotNullL( cdlRefs, msiLogNewL );
    _LIT( msiLogNewLC, "CCdlRefs::NewLC()" );
    AssertTrueL( ETrue, msiLogNewLC );
     

    CCdlRefs::TIterator iter = cdlRefs->Begin();
    _LIT( msiLogBegin, "CCdlRefs::Begin()" );
    AssertTrueL( ETrue, msiLogBegin );
    
    
    CCdlRefs::TIterator iter2( iter );
    _LIT( msiLogTIterator, "CCdlRefs::TIterator()" );
    AssertTrueL( ETrue, msiLogTIterator );

    ++iter2;
    _LIT( msiLogTIteratorPlus, "CCdlRefs::operator++()" );
    AssertTrueL( ETrue, msiLogTIteratorPlus );
    
    TUid testUid =  { 0x174657FC };
    cdlRefs->Begin( testUid );
    _LIT( msiLogBegin2, "CCdlRefs::Begin( TUid )" );
    AssertTrueL( ETrue, msiLogBegin2 );
    
    TBuf<10> name;
    cdlRefs->Begin( name );
    _LIT( msiLogBegin3, "CCdlRefs::Begin(const TDesC&)" );
    AssertTrueL( ETrue, msiLogBegin3 );

    cdlRefs->End();
    _LIT( msiLogEnd, "CCdlRefs::End()" );
    AssertTrueL( ETrue, msiLogEnd );

    HBufC* nameValue = StringLoader::LoadLC( R_BCTEST_TEXT ); //push
    
    TCdlRef tCdlref;
    tCdlref.iId = 0;
    tCdlref.iUid = testUid;
    tCdlref.iName = nameValue;
    
    cdlRefs->AppendL( tCdlref );
    _LIT( msiLogAppendL, "CCdlRefs::AppendL(const TCdlRef&)" );
    AssertTrueL( ETrue, msiLogAppendL );

    CCdlRefs* cdlRefs2 = CCdlRefs::NewL();
    CleanupStack::PushL( cdlRefs2 );//push

    cdlRefs->AppendL( *cdlRefs2 );
    _LIT( msiLogAppendL2, "CCdlRefs::AppendL(const CCdlRefCollection&)" );
    AssertTrueL( ETrue, msiLogAppendL2 );
    
    TBuf<10> homeName;
    TCdlRef ref;
    ref.iId = 1;
    ref.iUid = testUid;
    ref.iName = nameValue;
   
    TCdlArray<TCdlRef> refs;
    refs.iArray = &ref;
    refs.iCount = 1;

    cdlRefs->AppendL( homeName, refs );
    _LIT( msiLogAppendL3, "CCdlRefs::AppendL(const TDesC&,...)" );
    AssertTrueL( ETrue, msiLogAppendL3 );
    
    cdlRefs->InsertL( cdlRefs->Begin(), tCdlref );
    _LIT( msiLogInsertL, "CCdlRefs::InsertL()" );
    AssertTrueL( ETrue, msiLogInsertL );
    
    cdlRefs->Delete( iter );
    _LIT( msiLogDelete, "CCdlRefs::Delete(const TIterator&)" );
    AssertTrueL( ETrue, msiLogDelete );
    
    cdlRefs->Delete( cdlRefs->Begin(), cdlRefs->End() );
    _LIT( msiLogDelete2, "CCdlRefs::Delete(const TIterator&,const TIterator&)" );
    AssertTrueL( ETrue, msiLogDelete2 );

    TBuf<10> delName;
    cdlRefs->Delete( delName );
    _LIT( msiLogDelete3, "CCdlRefs::Delete(const TDesC&)" );
    AssertTrueL( ETrue, msiLogDelete3 );
    
    cdlRefs->Names();
    _LIT( msiLogNames, "CCdlRefs::Names()" );
    AssertTrueL( ETrue, msiLogNames );
    
    CCdlUids* uids = cdlRefs->UidsLC();//push
    _LIT( msiLogUidsLC, "CCdlRefs::UidsLC()" );
    AssertNotNullL( uids, msiLogUidsLC );

    cdlRefs->SubsetByUidLC( testUid );//push
    _LIT( msiLogSubsetByUidLC, "CCdlRefs::SubsetByUidLC(TUid )" );
    AssertTrueL( ETrue, msiLogSubsetByUidLC );

    cdlRefs->SubsetByUidsLC( *uids );//push
    _LIT( msiLogSubsetByUidsLC, "CCdlRefs::SubsetByUidsLC(const CCdlUids&)" );
    AssertTrueL( ETrue, msiLogSubsetByUidsLC );

    TBuf<10> names;
    cdlRefs->SubsetByNameLC( names );//push
    _LIT( msiLogSubsetByNameLC, "CCdlRefs::SubsetByNameLC(const TDesC& )" );
    AssertTrueL( ETrue, msiLogSubsetByNameLC );

    cdlRefs->MergeAndReplaceL( *cdlRefs2 );
    _LIT( msiLogMergeAndReplaceL, "CCdlRefs::MergeAndReplaceL()" );
    AssertTrueL( ETrue, msiLogMergeAndReplaceL );

    cdlRefs->AddLayerL( *cdlRefs2 );
    _LIT( msiLogAddLayerL, "CCdlRefs::AddLayerL()" );
    AssertTrueL( ETrue, msiLogAddLayerL);

    HBufC8* tmpbuf = cdlRefs->ExportL( );
    delete tmpbuf;
    _LIT( msiLogExportL, "CCdlRefs::ExportL()" );
    AssertTrueL( ETrue, msiLogExportL);
    _LIT( msiLogExportLC, "CCdlRefs::ExportLC()" );
    AssertTrueL( ETrue, msiLogExportLC);

    HBufC8* buf8 = HBufC8::NewMaxLC( 32 );//push
    TPtr8 ptr = buf8->Des();
    TChar theChar = 0;
    ptr.Zero();
    ptr.AppendFill( theChar, 8 );

    cdlRefs->ImportL( *buf8 );
    _LIT( msiLogImportL, "CCdlRefs::ImportL()" );
    AssertTrueL( ETrue, msiLogImportL);
    
    cdlRefs->CountRefs();
    _LIT( msiLogCountRefs, "CCdlRefs::CountRefs()" );
    AssertTrueL( ETrue, msiLogCountRefs());
    
    cdlRefs->AppendL( tCdlref );
    cdlRefs->Ref(0);
    _LIT( msiLogRef, "CCdlRefs::Ref()" );
    AssertTrueL( ETrue, msiLogRef);

    CleanupStack::PopAndDestroy( 8 );    

    _LIT( msiLogDes, "CCdlRefs::~CCdlRefs()" );
    AssertTrueL( ETrue, msiLogDes );
                                        
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlCase::TestCdlInstanceL()  
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::TestCdlInstanceL()  
    {
    
    TUid testUid =  { 0x174657FC };
    CCdlRefs* newRefs = CdlEngine::AllAvailableRefsLC();//push
    SCdlInterface face = { 0,0,0,{testUid.iUid},0,0,0,0 };

    CCdlInstance* inst = CCdlInstance::NewL( newRefs->Ref(0), &face );
    CleanupStack::PushL( inst );//push
    _LIT( msiLogNewL, "CCdlInstance::NewL()" );
    AssertNotNullL( inst, msiLogNewL );
    _LIT( msiLogNewLC, "CCdlInstance::NewLC()" );
    AssertTrueL( ETrue, msiLogNewLC );
    
    inst->Ref();
    _LIT( msiLogRef, "CCdlInstance::Ref()" );
    AssertTrueL( ETrue, msiLogRef );

    inst->SubLayer();
    _LIT( msiLogSubLayer, "CCdlInstance::SubLayer()" );
    AssertTrueL( ETrue, msiLogSubLayer );

    inst->LastAccessedRef();
    _LIT( msiLogLastAccessedRef, "CCdlInstance::LastAccessedRef()" );
    AssertTrueL( ETrue, msiLogLastAccessedRef );

    TFileName fileName;
    inst->FileNameRelativeToLastAccessedInstance( fileName );
    _LIT( msiLogAccesse, "CCdlInstance::FileNameRelativeToLastAccessedInstance()" );
    AssertTrueL( ETrue, msiLogAccesse );

    TUid testUid2 =  { 0x174609FC };
    CCdlRefs* newRefs2 = CdlEngine::AllAvailableRefsLC();//push
    SCdlInterface face2 = { 0,0,0,{testUid2.iUid},0,0,0,0 };

    CCdlInstance* inst2 = CCdlInstance::NewL( newRefs2->Ref(0), &face2 );
    CleanupStack::PushL( inst2 );//push
    
    _LIT( msiLogBool, "CCdlInstance::operator==" );
    if( inst2 == inst)
    {
    AssertTrueL( ETrue, msiLogBool );
    }
    else
    {
    AssertTrueL( ETrue, msiLogBool );
    }
    
    TInt cdlApiId = 0;
    inst->GetData( cdlApiId );
    _LIT( msiLogGetData, "CCdlInstance::GetData()" );
    AssertTrueL( ETrue, msiLogGetData );

    inst->GetFunction( cdlApiId );
    _LIT( msiLogGetFunction, "CCdlInstance::GetFunction()" );
    AssertTrueL( ETrue, msiLogGetFunction );
    
    CleanupStack::PopAndDestroy(4);                                        
  
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCdlCase::TestCdlUidsL() 
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::TestCdlUidsL()
    {
    
    CCdlUids* uids = CCdlUids::NewLC();//push
    _LIT( msiLogNewLC, "CCdlUids::NewLC()" );
    AssertNotNullL( uids, msiLogNewLC );
    _LIT( msiLogCCdlUids, "CCdlUids::CCdlUids()" );
    AssertTrueL( ETrue, msiLogCCdlUids );
 
    TUid testUid =  { 0x174657FC };
    uids->AddL( testUid );
    _LIT( msiLogAddL, "CCdlUids::AddL()" );
    AssertTrueL( ETrue, msiLogAddL );


    uids->Remove( testUid );
    _LIT( msiLogRemove, "CCdlUids::Remove()" );
    AssertTrueL( ETrue, msiLogRemove );


    CCdlUids* uids2 = CCdlUids::NewLC();//push
    uids->AddL( *uids2 );
    _LIT( msiLogAddL2, "CCdlUids::AddL(const CCdlUids& )" );
    AssertTrueL( ETrue, msiLogAddL2 );

    uids->Remove( *uids2 );
    _LIT( msiLogRemove2, "CCdlUids::Remove(const CCdlUids&)" );
    AssertTrueL( ETrue, msiLogRemove2 );


    uids->FindIndex( testUid );
    _LIT( msiLogFindIndex, "CCdlUids::FindIndex()" );
    AssertTrueL( ETrue, msiLogFindIndex );

    uids->IntersectionLC( *uids2 );//push
    _LIT( msiLogIntersectionLC, "CCdlUids::IntersectionLC()" );
    AssertTrueL( ETrue, msiLogIntersectionLC );

    TBuf8<10> buf;
    uids->ImportL( buf );
    _LIT( msiLogImportL, "CCdlUids::ImportL()" );
    AssertTrueL( ETrue, msiLogImportL );

    uids->Export();
    _LIT( msiLogExport, "CCdlUids::Export()" );
    AssertTrueL( ETrue, msiLogExport );

    CleanupStack::PopAndDestroy(3);
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCdlCase:TestCdlNamesL() 
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::TestCdlNamesL() 
    {
    CCdlNames* names = CCdlNames::NewLC();//push
    _LIT( msiLogNewLC, "CCdlNames::NewLC()" );
    AssertNotNullL( names, msiLogNewLC );
    _LIT( msiLogCCdlNames, "CCdlNames::CCdlNames()" );
    AssertTrueL( ETrue, msiLogCCdlNames );

    TBuf<10> buf;
    names->AddL( buf );
    _LIT( msiLogAddL, "CCdlNames::AddL()" );
    AssertTrueL( ETrue, msiLogAddL );

    names->FindIndex( buf );
    _LIT( msiLogFindIndex, "CCdlNames:: FindIndex()" );
    AssertTrueL( ETrue, msiLogFindIndex );

    HBufC8* buf8 = HBufC8::NewMaxLC( 32 );//push
    TPtr8 ptr = buf8->Des();
    TChar theChar = 0;
    ptr.Zero();
    ptr.AppendFill( theChar, 8 );
    
    names->ImportL( *buf8 );
    _LIT( msiLogImportL, "CCdlNames::ImportL()" );
    AssertTrueL( ETrue, msiLogImportL );

    HBufC8* delname = names->ExportL();
    _LIT( msiLogExportL, "CCdlNames::ExportL()" );
    AssertTrueL( ETrue, msiLogExportL );
    _LIT( msiLogExportLC, "CCdlNames::ExportLC()" );
    AssertTrueL( ETrue, msiLogExportLC );
    delete delname;
    
    CleanupStack::PopAndDestroy(2);

    _LIT( msiLogDes, "CCdlNames::~CCdlNames()" );
    AssertTrueL( ETrue, msiLogDes );

    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlCase:TestMCdlChangeObserverL() 
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::TestMCdlChangeObserverL()  
    {
    MCdlChangeObserver obser;

    CCdlUids* uids = CCdlUids::NewLC();//push
    
    obser.HandleCustomisationChangeL( *uids );
    _LIT( msiLogHandleCustomisationChangeL, "MCdlChangeObserver::HandleCustomisationChangeL()" );
    AssertTrueL( ETrue, msiLogHandleCustomisationChangeL );
    
    obser.HandleAvailableRefsChangeL();
    _LIT( msiLogHandleAvailableRefsChangeL, "MCdlChangeObserver::HandleAvailableRefsChangeL()" );
    AssertTrueL( ETrue, msiLogHandleAvailableRefsChangeL );
    
    CleanupStack::PopAndDestroy( uids );

    _LIT( msiLogDes, "MCdlChangeObserver::~MCdlChangeObserver" );
    AssertTrueL( ETrue, msiLogDes );
 
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlCase:TestCdlEngineL()
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::TestCdlEngineL() //CdlEngine::FindCustomisationFilesLC(), memory leak!!
    {
    CdlEngine::IsCdlEngineCreated();
    _LIT( msiLogIsCdlEngineCreated, "CdlEngine::IsCdlEngineCreated()" );
    AssertTrueL( ETrue, msiLogIsCdlEngineCreated );

    CCdlEngineRef* cdlEngine = CdlEngine::CreateCdlEngineL();
    CleanupStack::PushL( cdlEngine );//push
    _LIT( msiLogCreateCdlEngineL, "CdlEngine::CreateCdlEngineL()" );
    AssertNotNullL( cdlEngine, msiLogCreateCdlEngineL );
    
    CdlEngine::StartGlobalCustomisationL();
    _LIT( msiLogCustomisationL, "CdlEngine::StartGlobalCustomisationL()" );
    AssertTrueL( ETrue, msiLogCustomisationL );
 
    TUid testUid =  { 0x5675708D };

    SCdlInterface sCdlI;
    sCdlI.iUid = testUid;
    CdlEngine::IsCustomisationStarted( &sCdlI );
    _LIT( msiLogIsCustomisationStarted, "CdlEngine::IsCustomisationStarted()" );
    AssertTrueL( ETrue, msiLogIsCustomisationStarted );

    CdlEngine::RequireCustomisationL( &sCdlI );
    _LIT( msiLogRequireCustomisationL, "CdlEngine::RequireCustomisationL()" );
    AssertTrueL( ETrue, msiLogRequireCustomisationL );

    CBCTestMCdlChangeObserver* obser = new(ELeave) CBCTestMCdlChangeObserver();
    CleanupStack::PushL( obser );//push
    CdlEngine::SetCustomisationChangeObserverL( obser, testUid );
    _LIT( msiLogSCC, "CdlEngine::SetCustomisationChangeObserverL()" );
    AssertTrueL( ETrue, msiLogSCC );

    CdlEngine::LastApiId();
    _LIT( msiLogLastApiId, "CdlEngine::LastApiId()" );
    AssertTrueL( ETrue, msiLogLastApiId );

    CCdlRefs* cdlRef = CdlEngine::FindInstancesLC( testUid );//push
    _LIT( msiLogFindInstancesLC, "CdlEngine::FindInstancesLC()" );
    AssertNotNullL( cdlRef, msiLogFindInstancesLC );

    CdlEngine::SetAvailableRefsChangeObserverL( obser );
    _LIT( msiLogSCO, "CdlEngine::SetAvailableRefsChangeObserverL()" );
    AssertTrueL( ETrue, msiLogSCO );

    CdlEngine::SetLocalStateL( *cdlRef );
    _LIT( msiLogSetLocalStateL, "CdlEngine::SetLocalStateL()" );
    AssertTrueL( ETrue, msiLogSetLocalStateL );

    CdlEngine::SetGlobalStateL( *cdlRef );
    _LIT( msiLogSetGlobalStateL, "CdlEngine::SetGlobalStateL()" );
    AssertTrueL( ETrue, msiLogSetGlobalStateL );

    CCdlUids* uids = CCdlUids::NewLC();//push
    uids->AddL( testUid );
    CCdlRefs* cdlRef3 = CdlEngine::LocalStateLC( *uids );//push
    _LIT( msiLogLocalStateLC, "CdlEngine::LocalStateLC()" );
    AssertNotNullL( cdlRef3, msiLogLocalStateLC );
    
    CCdlRefs* cdlRef4 = CdlEngine::GlobalStateLC( *uids );//push
    _LIT( msiLogGlobalStateLC, "CdlEngine::GlobalStateLC()" );
    AssertTrueL( ETrue, msiLogGlobalStateLC );

    CdlEngine::EnableGlobalCustomisationL( *uids , ETrue);
    _LIT( msiLogEGC, "CdlEngine::EnableGlobalCustomisationL()" );
    AssertTrueL( ETrue, msiLogEGC );
    
    TBuf<10> lift;
    TBuf<10> right;
    CdlEngine::CompareNames( lift, right );
    _LIT( msiLogCompareNames, "CdlEngine::CompareNames()" );
    AssertTrueL( ETrue, msiLogCompareNames );

    CdlEngine::CustomisationInstance( testUid );
    _LIT( msiLogCustomisationInstance, "CdlEngine::CustomisationInstance()" );
    AssertTrueL( ETrue, msiLogCustomisationInstance );

    CCdlRefs* cdlRef2 = CdlEngine::AllAvailableRefsLC();//push
    _LIT( msiLogAllAvailableRefsLC, "CdlEngine::AllAvailableRefsLC()" );
    AssertTrueL( ETrue, msiLogAllAvailableRefsLC );

    TCdlRef cdlref = cdlRef2->Ref( 0 );
    CdlEngine::LoadCustomisationL( cdlref );
    _LIT( msiLogLoadCustomisationL, "CdlEngine::LoadCustomisationL()" );
    AssertTrueL( ETrue, msiLogLoadCustomisationL );

    CdlEngine::GetData( cdlref.iUid, 0 );
    _LIT( msiLogGetData, "CdlEngine::GetData()" );
    AssertTrueL( ETrue, msiLogGetData );

    CdlEngine::GetFunction( cdlref.iUid, 0 );
    _LIT( msiLogGetFunction, "CdlEngine::GetFunction()" );
    AssertTrueL( ETrue, msiLogGetFunction );

    CdlEngine::LastAccessedRef( cdlref.iUid );
    _LIT( msiLogLastAccessedRef, "CdlEngine::LastAccessedRef()" );
    AssertTrueL( ETrue, msiLogLastAccessedRef );

    TFileName fileName;
    CdlEngine::FileNameRelativeToLastAccessedInstance( cdlref.iUid, fileName );
    _LIT( msiLogFNRT, "CdlEngine::FileNameRelativeToLastAccessedInstance()" );
    AssertTrueL( ETrue, msiLogFNRT );

    CCdlRefCollection* cdlRefColl = CdlEngine::FileContentsLC( fileName );//push
    _LIT( msiLogFileContentsLC, "CdlEngine::FileContentsLC()" );
    AssertNotNullL( cdlRefColl, msiLogFileContentsLC );
    
    //CdlEngine::FindCustomisationFilesLC();

    CleanupStack::PopAndDestroy(8);
    
    _LIT( msiLogCdlEngineRef, "CCdlEngineRef::~CCdlEngineRef" );
    AssertNotNullL( cdlRefColl, msiLogCdlEngineRef );

    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlCase:TestCdlExplorerUtilsL()
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::TestCdlExplorerUtilsL() 
    {
    TUid testUid =  { 0x174657FC };
    CCdlRefs* newRefs = CdlEngine::AllAvailableRefsLC();//push
    SCdlInterface face = { 0,0,0,{testUid.iUid},0,0,0,0 };

    CCdlInstance* inst = CCdlInstance::NewL( newRefs->Ref(0), &face );
    CleanupStack::PushL( inst );//push

    CdlExplorerUtils::CreateRefsLC( *inst );//push
    _LIT( msiLogCreateRefsLC, "CdlExplorerUtils::CreateRefsLC()" );
    AssertTrueL( ETrue, msiLogCreateRefsLC );
    
    HBufC* nameValue = StringLoader::LoadLC( R_BCTEST_TEXT );//push
    TCdlRef ref;
    ref.iId = 1;
    ref.iUid = testUid;
    ref.iName = nameValue;
   
    TCdlArray<TCdlRef> refs;
    refs.iArray = &ref;
    refs.iCount = 1;
   
    CdlExplorerUtils::CreateRefsLC( *inst, refs );//push
    _LIT( msiLogCreateRefsLC2, "CdlExplorerUtils::CreateRefsLC(const CCdlInstance&,..)" );
    AssertTrueL( ETrue, msiLogCreateRefsLC2 );
     
    CleanupStack::PopAndDestroy(5);                                        
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlCase:TestCCdlInstanceExplorerBaseL() 
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::TestCCdlInstanceExplorerBaseL() 
    {
    CBCTestDomCdlInst* cdiExp = new(ELeave) CBCTestDomCdlInst;
    CleanupStack::PushL( cdiExp );//push
     
    cdiExp->FindLC();//push
    _LIT( msiLogFindLC, "CCdlInstanceExplorerBase::FindLC(TUid)" );
    AssertTrueL( ETrue, msiLogFindLC );
     
    CleanupStack::PopAndDestroy(2);                                        
    _LIT( msiLogDesc, "::~CCdlInstanceExplorerBase()" );
    AssertTrueL( ETrue, msiLogDesc );
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlCase:TestCCdlUserPackageExplorerL()
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlCase::TestCCdlUserPackageExplorerL()  //a private api can't be tested.
    {
    CCdlUserPackageExplorer* cdiUPE = new(ELeave) CCdlUserPackageExplorer();
    CleanupStack::PushL( cdiUPE );//push
     
    cdiUPE->ConstructL();
    _LIT( msiLogConstructL, "CCdlUserPackageExplorer::ConstructL()" );
    AssertTrueL( ETrue, msiLogConstructL );
     
    CleanupStack::PopAndDestroy(1);                                        
    _LIT( msiLogDesC, "CCdlUserPackageExplorer::~CCdlUserPackageExplorer()" );
    AssertTrueL( ETrue, msiLogDesC );
    
    }

