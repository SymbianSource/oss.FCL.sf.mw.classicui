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
#include <s32file.h>    // RFileWriteStream, RFileReadStream
#include <barsread.h>   // TResourceReader
#include <eikmenup.h>   // CEikMenuPane
#include <coecntrl.h>
#include <aiwservicehandler.h>

#include "bctestservicehandlercase.h"
#include "bctestservicehandlerappui.h"
#include "bctestservicehandlercontainer.h"
#include "bctestservicehandler.hrh"
#include <bctestservicehandler.rsg>

_LIT( KTextCriteriaItemNullNewL,            "CAiwCriteriaItem::NewL()" );
_LIT( KTextCriteriaItemNullNewLC,           "CAiwCriteriaItem::NewLC()" );
_LIT( KTextCriteriaItemSetServiceClass,     "CAiwCriteriaItem::SetServiceClass(const TUid& aServiceUid)" );
_LIT( KTextCriteriaItemSetContentTypeL,     "CAiwCriteriaItem::SetContentTypeL(const TDesC8& aContentType)" );
_LIT( KTextCriteriaItemServiceClass,        "CAiwCriteriaItem::ServiceClass()" );
_LIT( KTextCriteriaItemContentType,         "CAiwCriteriaItem::ContentType()" );
_LIT( KTextCriteriaItemSetOptions,          "CAiwCriteriaItem::SetOptions(TUint aOptions)" );
_LIT( KTextCriteriaItemOptions,             "CAiwCriteriaItem::Options()" );
_LIT( KTextCriteriaItemMaxProviders,        "CAiwCriteriaItem::MaxProviders()" );
_LIT( KTextCriteriaItemDefaultProvider,     "CAiwCriteriaItem::DefaultProvider()" );
_LIT( KTextCriteriaItemSetDefaultProvider,  "CAiwCriteriaItem::SetDefaultProvider(TInt aDefault)" );
_LIT( KTextCriteriaItemSetMaxProviders,     "CAiwCriteriaItem::SetMaxProviders(TInt aMaxProviders)" );
_LIT( KTextCriteriaItemRomOnly,             "CAiwCriteriaItem::RomOnly()" );

_LIT( KTextServiceHandlerNewL,              "CAiwServiceHandler::NewL()" );
_LIT( KTextServiceHandlerNewLC,             "CAiwServiceHandler::NewLC()" );
_LIT( KTextServiceHandlerReset,             "CAiwServiceHandler::Reset()" );
_LIT( KTextServiceHandlerNbrOfProviders,    "CAiwServiceHandler::NbrOfProviders(const CAiwCriteriaItem* aCriteria)" );
_LIT( KTextServiceHandlerGetInterest,       "CAiwServiceHandler::GetInterest(RCriteriaArray& aInterest)" );
_LIT( KTextServiceHandlerGetCriteria,       "CAiwServiceHandler::GetCriteria(TInt aId)" );
_LIT( KTextServiceHandlerInParamListL,      "CAiwServiceHandler::InParamListL()" );
_LIT( KTextServiceHandlerOutParamListL,     "CAiwServiceHandler::OutParamListL()" );
_LIT( KTextServiceHandlerServiceCmdByMenuCmd,   "CAiwServiceHandler::ServiceCmdByMenuCmd(TInt aMenuCmdId)" );
_LIT( KTextServiceHandlerExecuteMenuCmdL,   "CAiwServiceHandler::ExecuteMenuCmdL(TInt aMenuCmdId, const CAiwGenericParamList& aInParamList, CAiwGenericParamList& aOutParamList, TUint aCmdOptions = 0, MAiwNotifyCallback* aCallback = NULL)" );
_LIT( KTextServiceHandlerIsSubMenuEmpty,    "CAiwServiceHandler::IsSubMenuEmpty(TInt aSubMenuId)" );
_LIT( KTextServiceHandlerIsAiwMenu,         "CAiwServiceHandler::IsAiwMenu(TInt aMenuResourceId)" );
_LIT( KTextServiceHandlerHandleSubmenuL,    "CAiwServiceHandler::HandleSubmenuL(CEikMenuPane& aPane)" );
_LIT( KTextServiceHandlerReportMenuLaunch,  "CAiwServiceHandler::ReportMenuLaunch()" );
_LIT( KTextServiceHandlerExecuteServiceCmdL, "CAiwServiceHandler::ExecuteServiceCmdL(const TInt& aCmdId, const CAiwGenericParamList& aInParamList, CAiwGenericParamList& aOutParamList, TUint aCmdOptions = 0, MAiwNotifyCallback* aCallback = 0)" );
_LIT( KTextServiceHandlerInitializeMenuPaneL, "CAiwServiceHandler::InitializeMenuPaneL(CEikMenuPane& aMenuPane, TInt aMenuResourceId, TInt aBaseMenuCmdId, const CAiwGenericParamList& aInParamList)" );
_LIT( KTextServiceHandlerInitializeMenuPaneL2, "CAiwServiceHandler::InitializeMenuPaneL(CEikMenuPane& aMenuPane, TInt aMenuResourceId, TInt aBaseMenuCmdId, const CAiwGenericParamList& aInParamList, TBool aUseSubmenuTextsIfAvailable)" ); 

_LIT( KTextNotifyCallbackHandleNotifyL,     "MAiwNotifyCallback::HandleNotifyL(TInt aCmdId, TInt aEventId, CAiwGenericParamList& aEventParamList, const CAiwGenericParamList& aInParamList)" );
_LIT( KTextNotifyCallbackEventStarted,      "KAiwEventStarted" );
_LIT( KTextNotifyCallbackEventCompleted,    "KAiwEventCompleted" );
_LIT( KTextNotifyCallbackEventCanceled,     "KAiwEventCanceled" );
_LIT( KTextNotifyCallbackEventError,        "KAiwEventError" );
_LIT( KTextNotifyCallbackEventOutParamCheck,"KAiwEventOutParamCheck" );
_LIT( KTextNotifyCallbackEventInParamCheck, "KAiwEventInParamCheck" );
_LIT( KTextNotifyCallbackEventStopped,      "KAiwEventStopped" );
_LIT( KTextNotifyCallbackEventQueryExit,    "KAiwEventQueryExit" );

_LIT( KTextGenericParam,                    "TAiwGenericParam()" );
_LIT( KTextGenericParam2,                   "TAiwGenericParam(TGenericParamId aSemanticId)" );
_LIT( KTextGenericParam3,                   "TAiwGenericParam(TGenericParamId aSemanticId, const TAiwVariant& aValue)" );
_LIT( KTextGenericParamSetSemanticId,       "TAiwGenericParam::SetSemanticId(TGenericParamId aSemanticId)" );
_LIT( KTextGenericParamSemanticId,          "TAiwGenericParam::SetSemanticId() const" );
_LIT( KTextGenericParamValue,               "TAiwGenericParam::Value()" );
_LIT( KTextGenericParamConstValue,          "TAiwGenericParam::Value() const" );
_LIT( KTextGenericParamReset,               "TAiwGenericParam::Reset()" );
_LIT( KTextGenericParamEquals,              "operator==(const TAiwGenericParam& aLhs, const TAiwGenericParam& aRhs)" );
_LIT( KTextGenericParamNotEqual,            "operator!=(const TAiwGenericParam& aLhs, const TAiwGenericParam& aRhs)" );

_LIT( KTextGenericParamListNewL,            "CAiwGenericParamList::NewL()" );
_LIT( KTextGenericParamListNewL2,           "CAiwGenericParamList::NewL(RReadStream& aReadStream)" );
_LIT( KTextGenericParamListNewLC,           "CAiwGenericParamList::NewLC()" );
_LIT( KTextGenericParamListNewLC2,          "CAiwGenericParamList::NewLC(RReadStream& aReadStream)" );
_LIT( KTextGenericParamListCount,           "CAiwGenericParamList::Count()" );
_LIT( KTextGenericParamListCount2,          "CAiwGenericParamList::Count(TGenericParamId aSemanticId, TVariantTypeId aDataType) const" );
_LIT( KTextGenericParamListIndex,           "CAiwGenericParamList::operator[](TInt aIndex) const" );
_LIT( KTextGenericParamListAppendL,         "CAiwGenericParamList::AppendL(const TAiwGenericParam& aParam)" );
_LIT( KTextGenericParamListAppendL2,        "CAiwGenericParamList::AppendL(const CAiwGenericParamList& aList)" );
_LIT( KTextGenericParamListRemove,          "CAiwGenericParamList::Remove()" );
_LIT( KTextGenericParamListReset,           "CAiwGenericParamList::Reset()" );
_LIT( KTextGenericParamListFindFirst,       "CAiwGenericParamList::FindFirst(TInt& aIndex, TGenericParamId aSemanticId, TVariantTypeId aDataType) const" );
_LIT( KTextGenericParamListFindNext,        "CAiwGenericParamList::FindNext(TInt& aIndex, TGenericParamId aSemanticId, TVariantTypeId aDataType) const" );
_LIT( KTextGenericParamListExternalizeL,    "CAiwGenericParamList::ExternalizeL(RWriteStream& aStream) const" );
_LIT( KTextGenericParamListSize,            "CAiwGenericParamList::Size()" );
_LIT( KTextGenericParamListInternalizeL,    "CAiwGenericParamList::ExternalizeL(RReadStream& aStream)" );
_LIT( KTextGenericParamListPackForServerL,  "CAiwGenericParamList::PackForServerL(TIpcArgs& aArgs)" );
_LIT( KTextGenericParamListUnpackFromClientL, "CAiwGenericParamList::UnpackFromClientL(const RMessage2& aArgs)" );

_LIT( KTextVariantEmptyConstructor,         "TAiwVariant()" );
_LIT( KTextVariantIntegerConstructor,       "TAiwVariant(TInt32 aValue)" );
_LIT( KTextVariantUidConstructor,           "TAiwVariant(const TUid& aValue)" );
_LIT( KTextVariantTimeConstructor,          "TAiwVariant(const TTime& aValue)" );
_LIT( KTextVariantDesConstructor,           "TAiwVariant(const TDesC& aValue)" );
_LIT( KTextVariantBufferConstructor,        "TAiwVariant(const HBufC* aValue)" );
_LIT( KTextVariantDes8Constructor,          "TAiwVariant(const TDesC8& aValue)" );
_LIT( KTextVariantFileConstructor,          "TAiwVariant(const RFile& aValue)" );
_LIT( KTextVariantSourceConstructor,        "TAiwVariant(const TAiwVariant& aSrc)" );
_LIT( KTextVariantAssignment,               "TAiwVariant::operator=(const TAiwVariant& aValue)" );
_LIT( KTextVariantTypeId,                   "TAiwVariant::TypeId()" );
_LIT( KTextVariantIsEmpty,                  "TAiwVariant::IsEmpty()" );
_LIT( KTextVariantGetInteger,               "TAiwVariant::Get(TInt32& aValue)" );
_LIT( KTextVariantGetUid,                   "TAiwVariant::Get(TUid& aValue)" );
_LIT( KTextVariantGetPtr16,                 "TAiwVariant::Get(TPtrC& aValue)" );
_LIT( KTextVariantGetTime,                  "TAiwVariant::Get(TTime& aValue)" );
_LIT( KTextVariantGetPtr8,                  "TAiwVariant::Get(TPtrC8& aValue)" );
_LIT( KTextVariantGetFile,                  "TAiwVariant::Get(RFile& aValue)" );
_LIT( KTextVariantAsTInt32,                 "TAiwVariant::AsTInt32()" );
_LIT( KTextVariantAsTUid,                   "TAiwVariant::AsTUid()" );
_LIT( KTextVariantAsDes,                    "TAiwVariant::AsDes()" );
_LIT( KTextVariantAsTTime,                  "TAiwVariant::AsTTime()" );
_LIT( KTextVariantAsData,                   "TAiwVariant::AsData()" );
_LIT( KTextVariantAsFileHandle,             "TAiwVariant::AsFileHandle()" );
_LIT( KTextVariantReset,                    "TAiwVariant::Reset()" );
_LIT( KTextVariantSetInteger,               "TAiwVariant::Set(TInt32 aValue)" );
_LIT( KTextVariantSetUid,                   "TAiwVariant::Set(const TUid aValue)" );
_LIT( KTextVariantSetTime,                  "TAiwVariant::Set(const TTime aValue)" );
_LIT( KTextVariantSetDes16,                 "TAiwVariant::Set(const TDesC& aValue)" );
_LIT( KTextVariantSetBuffer,                "TAiwVariant::Set(const HBufC* aValue)" );
_LIT( KTextVariantSetDes8,                  "TAiwVariant::Set(const TDesC8& aValue)" );
_LIT( KTextVariantSetFile,                  "TAiwVariant::Set(const RFile& aValue)" );
_LIT( KTextVariantTimeAssignment,           "TAiwVariant::operator=(const TTime& aValue)" );
_LIT( KTextVariantUidAssignment,            "TAiwVariant::operator=(const TUid& aValue)" );
_LIT( KTextVariantIntegerAssignment,        "TAiwVariant::operator=(TInt32 aValue)" );
_LIT( KTextVariantDes16Assignment,          "TAiwVariant::operator=(const TDesC& aValue)" );
_LIT( KTextVariantBufferAssignment,         "TAiwVariant::operator=(const HBufC* aValue)" );
_LIT( KTextVariantDes8Assignment,           "TAiwVariant::operator=(const TDesC8& aValue)" );
_LIT( KTextVariantFileAssignment,           "TAiwVariant::operator=(const RFile& aValue)" );
_LIT( KTextVariantEquals,                   "operator==(const TAiwVariant& aLhs, const TAiwVariant& aRhs)" );
_LIT( KTextVariantNotEqual,                 "operator!=(const TAiwVariant& aLhs, const TAiwVariant& aRhs)" );

_LIT( KBuffer,                              "Abc" );
_LIT8( KContentMimeType,                    "*" );

_LIT(KFileName,                             "C:\\data\\testfile.txt" );

const TInt KBufferSize = 3;
const TInt KMaxProviders = 3;
const TInt KDefaultProvider = 0x12312312;
const TInt32 KDefaultValue = 10;
const TInt KDefaultUidValue = 123456;


class RTestSession : public RSessionBase
	{
public:
	TInt Create( RServer2 aServer, TRequestStatus& aStatus )
		{
		return CreateSession( aServer,
		                      TVersion(),
		                      2,
		                      EIpcSession_Sharable,
		                      NULL,
		                      &aStatus);
		}
		
	inline void Send( const TIpcArgs& aArgs, TRequestStatus& aStatus )
		{
		RSessionBase::SendReceive( ETestFunction, aArgs, aStatus );
		}
	};
	
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestServiceHandlerCase* CBCTestServiceHandlerCase::NewL( 
    CBCTestServiceHandlerContainer* aContainer )
    {
    CBCTestServiceHandlerCase* self = new( ELeave ) CBCTestServiceHandlerCase( 
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
CBCTestServiceHandlerCase::CBCTestServiceHandlerCase( 
    CBCTestServiceHandlerContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestServiceHandlerCase::~CBCTestServiceHandlerCase()
    {
    delete iCriteria;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestServiceHandlerCase::ConstructL()
    {
    BuildScriptL();
    iCriteria = CAiwCriteriaItem::NewL();
    }
    
// ---------------------------------------------------------------------------
// CBCTestServiceHandlerCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestServiceHandlerCase::BuildScriptL()
    {
    // Add script as your need.
    
    // Tests the CAiwServiceHandler methods
    AddTestL( DELAY(1), REP(LeftCBA,2), TEND );
    
    // Tests the CAiwCriteriaItem methods
    AddTestL( LeftCBA, Down, LeftCBA, TEND );
    
    // Tests the TAiwGenericParam methods
    AddTestL( LeftCBA, REP(Down,2), LeftCBA, TEND );
    
    // Tests the CAiwGenericParamList methods
    AddTestL( LeftCBA, REP(Down,3), LeftCBA, TEND );
    
    // Tests the TAiwVariant methods
    AddTestL( LeftCBA, REP(Down,4), LeftCBA, TEND );
    }
    
// ---------------------------------------------------------------------------
// CBCTestServiceHandlerCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestServiceHandlerCase::RunL( TInt aCmd )
    {    
    if ( aCmd < EBCTestCmdOutline1 || aCmd >= EBCTestCmdMaxOutline )
        {
        return;
        }
            
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestServiceHandlerFunctions();
            break;
            
        case EBCTestCmdOutline2:
            TestCriteriaItemFunctions();
            break;
            
        case EBCTestCmdOutline3:
            TestGenericParamFunctions();
            break;
            
        case EBCTestCmdOutline4:
            TestGenericParamListFunctions();
            break;
            
        case EBCTestCmdOutline5:
            TestVariantFunctions();
            break;
   
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestServiceHandlerCase::PrepareCaseL( TInt /*aCmd*/ )
    {    
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestServiceHandlerCase::ReleaseCaseL()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerCase::TestServiceHandlerFunctions
// ---------------------------------------------------------------------------
//    
void CBCTestServiceHandlerCase::TestServiceHandlerFunctions()
    {
    CAiwServiceHandler* serviceHandler;
    CAiwCriteriaItem*   nullCriteria;
      
    serviceHandler = CAiwServiceHandler::NewL();
    CleanupStack::PushL( serviceHandler );
    AssertNotNullL( serviceHandler, KTextServiceHandlerNewL );
    CleanupStack::PopAndDestroy( serviceHandler );
    
    serviceHandler = CAiwServiceHandler::NewLC();
    AssertNotNullL( serviceHandler, KTextServiceHandlerNewLC );
            
    serviceHandler->Reset();
    AssertTrueL( ETrue, KTextServiceHandlerReset );

    serviceHandler->GetCriteria( EAiwPlaceholder );
    AssertTrueL( ETrue, KTextServiceHandlerGetCriteria );
        
    nullCriteria = CAiwCriteriaItem::NewLC();
    TInt providers = serviceHandler->NbrOfProviders( nullCriteria );
    AssertIntL( 0, providers, KTextServiceHandlerNbrOfProviders );
    CleanupStack::PopAndDestroy( nullCriteria );
            
    serviceHandler->Reset();
    RCriteriaArray interest;
    CleanupClosePushL( interest );
    serviceHandler->GetInterest( interest );
    AssertTrueL( ETrue, KTextServiceHandlerGetInterest );
    CleanupStack::PopAndDestroy( &interest );
            
    CAiwGenericParamList& inParamList = serviceHandler->InParamListL();
    AssertTrueL( ETrue, KTextServiceHandlerInParamListL );
            
    CAiwGenericParamList& outParamList = serviceHandler->OutParamListL();
    AssertTrueL( ETrue, KTextServiceHandlerOutParamListL );
            
    TInt serviceCmd = serviceHandler->ServiceCmdByMenuCmd( NULL );
    AssertIntL( KAiwCmdNone, serviceCmd, KTextServiceHandlerServiceCmdByMenuCmd );
                   
    serviceHandler->ExecuteMenuCmdL( EAiwPlaceholder,
                                     serviceHandler->InParamListL(),
                                     serviceHandler->OutParamListL(),
                                     KAiwOptASyncronous,
                                     this );
    AssertTrueL( ETrue, KTextServiceHandlerExecuteMenuCmdL );
      
    TBool isEmpty = serviceHandler->IsSubMenuEmpty( R_BCTESTSERVICEHANDLER_MENU );
    AssertTrueL( !isEmpty, KTextServiceHandlerIsSubMenuEmpty );
            
    TBool isAiwMenu = serviceHandler->IsAiwMenu( R_BCTESTSERVICEHANDLER_MENU );
    AssertTrueL( !isAiwMenu, KTextServiceHandlerIsAiwMenu );

    serviceHandler->ReportMenuLaunch();
    AssertTrueL( ETrue, KTextServiceHandlerReportMenuLaunch );
            
    serviceHandler->ExecuteServiceCmdL( KAiwCmdNone,
                                        serviceHandler->InParamListL(),
                                        serviceHandler->OutParamListL() );
    AssertTrueL( ETrue, KTextServiceHandlerExecuteServiceCmdL );

    CEikMenuPane* menuPane = new (ELeave) CEikMenuPane( this );
    CleanupStack::PushL( menuPane );
    
    serviceHandler->InitializeMenuPaneL( *menuPane,
                                         R_BCTESTSERVICEHANDLER_MENU,
                                         EAiwPlaceholder,
                                         serviceHandler->InParamListL() );
    AssertTrueL( ETrue, KTextServiceHandlerInitializeMenuPaneL );
                                         
    serviceHandler->InitializeMenuPaneL( *menuPane,
                                         R_BCTESTSERVICEHANDLER_MENU,
                                         EAiwPlaceholder,
                                         serviceHandler->InParamListL(),
                                         ETrue );
    AssertTrueL( ETrue, KTextServiceHandlerInitializeMenuPaneL2 );
                                         
    TBool submenuHandled = serviceHandler->HandleSubmenuL( *menuPane );
    AssertTrueL( !submenuHandled, KTextServiceHandlerHandleSubmenuL );
                             
    CleanupStack::PopAndDestroy( menuPane ); // menuPane                                         
    CleanupStack::PopAndDestroy( serviceHandler ); // serviceHandler
                                                      
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerCase::TestCriteriaItemFunctions
// ---------------------------------------------------------------------------
//     
void CBCTestServiceHandlerCase::TestCriteriaItemFunctions()
    {
   
    CAiwCriteriaItem* firstCriteria;
    CAiwGenericParamList* paramList;
    TUid menuUid;
    menuUid.iUid = KAiwClassMenu;
    
    AssertNotNullL( iCriteria, KTextCriteriaItemNullNewL );
    firstCriteria = CAiwCriteriaItem::NewLC();
    AssertNotNullL( firstCriteria, KTextCriteriaItemNullNewLC );
    CleanupStack::PopAndDestroy( firstCriteria );
                    
    iCriteria->SetServiceClass( menuUid );
    AssertIntL( KAiwClassMenu, iCriteria->ServiceClass().iUid, KTextCriteriaItemSetServiceClass );
    AssertTrueL( ETrue, KTextCriteriaItemServiceClass );
 
             
    iCriteria->SetContentTypeL( KContentMimeType );
    AssertTrueL( ETrue, KTextCriteriaItemSetContentTypeL );
    AssertTrueL( iCriteria->ContentType() == KContentMimeType, KTextCriteriaItemContentType );
            
    iCriteria->SetMaxProviders( KMaxProviders );
    AssertIntL( KMaxProviders, iCriteria->MaxProviders(), KTextCriteriaItemSetMaxProviders );
    AssertTrueL( ETrue, KTextCriteriaItemMaxProviders );
            
    iCriteria->SetDefaultProvider( KDefaultProvider );
    AssertIntL( KDefaultProvider, iCriteria->DefaultProvider().iUid, KTextCriteriaItemSetDefaultProvider );
    AssertTrueL( ETrue, KTextCriteriaItemDefaultProvider );
    
   
    iCriteria->SetOptions( AIW_OPTIONS_ROM_ONLY );
    AssertIntL( AIW_OPTIONS_ROM_ONLY, iCriteria->Options(), KTextCriteriaItemSetOptions );
    AssertTrueL( ETrue, KTextCriteriaItemOptions );
    AssertTrueL( iCriteria->RomOnly(), KTextCriteriaItemRomOnly );
    
    paramList = CAiwGenericParamList::NewLC();
    HandleNotifyL( KAiwCmdNone, KAiwEventStarted, *paramList, *paramList );
            
    CleanupStack::PopAndDestroy( paramList ); //paramList         
    
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerCase::TestGenericParamFunctions
// ---------------------------------------------------------------------------
//     
void CBCTestServiceHandlerCase::TestGenericParamFunctions()
    {
    TUid uid;
    uid.iUid = KDefaultUidValue;
    TAiwGenericParam nullParam;
    
    TAiwGenericParam genericParam;
    AssertNotNullL( &genericParam,  KTextGenericParam );
    TAiwGenericParam genericParam2( EGenericParamUnspecified );
    AssertNotNullL( &genericParam2, KTextGenericParam2 );
    TAiwGenericParam genericParam3( EGenericParamHelpItem, uid );
    AssertNotNullL( &genericParam3, KTextGenericParam3 );
    TAiwGenericParam genericParam4;
            
    genericParam.SetSemanticId( EGenericParamLandmark );
    AssertIntL( EGenericParamLandmark, genericParam.SemanticId(), KTextGenericParamSetSemanticId );
    AssertIntL( EGenericParamLandmark, genericParam.SemanticId(), KTextGenericParamSemanticId );
    
    TAiwVariant& nullValue = nullParam.Value();
    AssertTrueL( nullValue.IsEmpty(), KTextGenericParamValue );
    const TAiwVariant& constValue = nullParam.Value();
    AssertTrueL( constValue.IsEmpty(), KTextGenericParamConstValue );
            
    genericParam.Reset();
    AssertTrueL( ETrue, KTextGenericParamReset );
            
    AssertTrueL( genericParam4 == nullParam, KTextGenericParamEquals );
            
    AssertTrueL( genericParam != genericParam3, KTextGenericParamNotEqual );
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerCase::TestGenericParamListFunctions
// ---------------------------------------------------------------------------
//     
void CBCTestServiceHandlerCase::TestGenericParamListFunctions()
    {
    TInt count;
    TInt index;
    TInt err;
    TUid testUid;
    testUid.iUid = 123;
    CAiwGenericParamList* genericParamList;
    CAiwGenericParamList* secondParamList;
    TAiwVariant variant( testUid );
    TAiwGenericParam genericParam( 1, variant );//EGenericParamCharSet
            
    RFs fsSession;   
    User::LeaveIfError( fsSession.Connect() );
    CleanupClosePushL( fsSession );
        
    genericParamList = CAiwGenericParamList::NewL();
    CleanupStack::PushL( genericParamList );
    AssertNotNullL( genericParamList, KTextGenericParamListNewL );
    
    RFile writeFile;
    CleanupClosePushL( writeFile );
    err = writeFile.Open( fsSession, KFileName, EFileStream | EFileWrite | EFileShareAny );
    if (err == KErrNotFound)
        { 
        // File does not exist - create it
        err = writeFile.Create( fsSession, KFileName, EFileStream | EFileWrite | EFileShareAny );    
        }
    
    RFileWriteStream writeStream = RFileWriteStream( writeFile );
    CleanupClosePushL( writeStream );
    
    genericParamList->ExternalizeL( writeStream );
    AssertTrueL( ETrue, KTextGenericParamListExternalizeL );
    
    CleanupStack::PopAndDestroy( 3, genericParamList );
    
    RFile readFile;
    CleanupClosePushL( readFile );
    err = readFile.Open( fsSession, KFileName, EFileStream | EFileRead | EFileShareReadersOnly );
    RFileReadStream readStream = RFileReadStream( readFile );
    CleanupClosePushL( readStream );
            
    genericParamList = CAiwGenericParamList::NewL( readStream );
    CleanupStack::PushL( genericParamList );
    AssertNotNullL( genericParamList, KTextGenericParamListNewL2 );
    CleanupStack::PopAndDestroy( 3, &readFile );

    RFile readFile2;
    CleanupClosePushL( readFile2 );
    err = readFile2.Open( fsSession, KFileName, EFileStream | EFileRead | EFileShareReadersOnly );
    RFileReadStream readStream2 = RFileReadStream( readFile2 );
    CleanupClosePushL( readStream2 );
                     
    genericParamList = CAiwGenericParamList::NewLC( readStream2 );
    AssertNotNullL( genericParamList, KTextGenericParamListNewLC2 );
    
    RFile readFile3;
    CleanupClosePushL( readFile3 );
    err = readFile3.Open( fsSession, KFileName, EFileStream | EFileRead | EFileShareReadersOnly );
    RFileReadStream readStream3 = RFileReadStream( readFile3 );
    CleanupClosePushL( readStream3 );
    
    genericParamList->InternalizeL( readStream3 );
    AssertTrueL( ETrue, KTextGenericParamListInternalizeL );
    
    CleanupStack::PopAndDestroy( 6, &fsSession ); // readStream3, readFile3, genericParamList,
                                                  // readStream2, readFile2, fsSession
    
    genericParamList = CAiwGenericParamList::NewLC();
    AssertNotNullL( genericParamList, KTextGenericParamListNewLC );
            
    count = genericParamList->Count();
    AssertIntL( 0, count, KTextGenericParamListCount );
    count = genericParamList->Count( EGenericParamLandmarkId, EVariantTypeNull );
    AssertIntL( 0, count, KTextGenericParamListCount2 );

    index = 0;
    genericParamList->AppendL( genericParam );
    AssertTrueL( ETrue, KTextGenericParamListAppendL );
    const TAiwGenericParam& paramFromList = (*genericParamList)[index];
    AssertTrueL( ETrue, KTextGenericParamListIndex );
            
    secondParamList = CAiwGenericParamList::NewLC();
    genericParamList->AppendL( *secondParamList );
    AssertNotNullL( genericParamList, KTextGenericParamListAppendL2 );
            
    TBool removed = genericParamList->Remove( EGenericParamLandmarkDatabase );
    AssertTrueL( removed == EFalse, KTextGenericParamListRemove );

    genericParamList->Reset();
    AssertTrueL( ETrue, KTextGenericParamListReset );
    
    CleanupStack::PopAndDestroy( secondParamList );
            
    index = 0;
    genericParamList->FindFirst( index,
                                 EGenericParamMnMapViewOptions,
                                 EVariantTypeDesC );
    AssertIntL( KErrNotFound, index, KTextGenericParamListFindFirst );
            
    index = 0;
    genericParamList->FindNext( index,
                                EGenericParamMnGeocodingOptions,
                                EVariantTypeDesC8 );
    AssertIntL( KErrNotFound, index, KTextGenericParamListFindNext );
                        
    genericParamList->Size();
    AssertTrueL( ETrue, KTextGenericParamListSize );
                   
    TIpcArgs args;
    genericParamList->AppendL( genericParam );
    HBufC8* msgBuf = genericParamList->PackForServerL( args );
    CleanupStack::PushL( msgBuf );
    AssertNotNullL( msgBuf, KTextGenericParamListPackForServerL );
    
    // Test server handle
    RServer2  server;
    
    // Test message handle
    RMessage2 message;
    
    // Test session handle
    RTestSession session;
    
    TRequestStatus sessionCreation;
    TRequestStatus firstMessageReceived;
    TRequestStatus argumentsReceived;
    TRequestStatus secondMessageReceived;
    
    // Test server is created
    User::LeaveIfError( server.CreateGlobal( KNullDesC ) );
    CleanupClosePushL( server );
    
    // Test session is created
    User::LeaveIfError( session.Create( server, sessionCreation ) );
    CleanupClosePushL( session );
    
    // Server receives and completes the session creation message
    server.Receive( message, firstMessageReceived );
    User::WaitForRequest( firstMessageReceived );
    message.Complete( KErrNone );
    User::WaitForRequest( sessionCreation );
    
    // Parameters of genericParamList are sent via session to server
    session.Send( args, argumentsReceived );
    
    // Server receives the parameters
    server.Receive( message, secondMessageReceived );
    User::WaitForRequest( secondMessageReceived );
    
    genericParamList->UnpackFromClientL( message );
    AssertTrueL( ETrue, KTextGenericParamListUnpackFromClientL );
    
    // Parameters are received and handled -> message is completed
    message.Complete( KErrNone );
    User::WaitForRequest( argumentsReceived );
               
    CleanupStack::PopAndDestroy( 4, genericParamList  ); // session, server, msgBuf,
                                                         // genericParamList
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerCase::TestVariantFunctions
// ---------------------------------------------------------------------------
//     
void CBCTestServiceHandlerCase::TestVariantFunctions()
    {
    TBool       match = EFalse;
    TInt32      value = KDefaultValue;
    TInt32      getValue;
    TUid        uidValue;
    TUid        getUidValue;
    TTime       timeValue;
    TTime       getTimeValue;
    HBufC16*    buffer16;
    HBufC16*    getBuffer16;
    HBufC8*     buffer8;
    HBufC8*     getBuffer8;
    TPtrC16     getPtr16Value;
    TPtrC8      getPtr8Value;
    TAiwVariant source;
    TAiwVariant getVariant;
    TAiwVariant assignedVariant;
    
    buffer16 = HBufC16::NewLC( KBufferSize );
    getBuffer16 = HBufC16::NewLC( KBufferSize );
    buffer8 = HBufC8::NewLC( KBufferSize );
    getBuffer8 = HBufC8::NewLC( KBufferSize );
    TPtr8 ptr8 = buffer8->Des();
    TPtr8 getPtr8 = getBuffer8->Des();
    TPtr16 ptr16 = buffer16->Des();
    TPtr16 getPtr16 = getBuffer16->Des();
    ptr8.Append( KBuffer );
    ptr16.Append( KBuffer );
    
    TAiwVariant emptyVariant;
    AssertNotNullL( &emptyVariant, KTextVariantEmptyConstructor );
    
    TAiwVariant integerVariant( value );
    AssertNotNullL( &integerVariant, KTextVariantIntegerConstructor );
    
    TAiwVariant uidVariant( uidValue );
    AssertNotNullL( &uidVariant, KTextVariantUidConstructor );
    
    TAiwVariant timeVariant( timeValue );
    AssertNotNullL( &timeVariant, KTextVariantTimeConstructor );
    
    TAiwVariant desVariant( ptr16 );
    AssertNotNullL( &desVariant, KTextVariantDesConstructor );
    
    TAiwVariant bufVariant( buffer16 );
    AssertNotNullL( &bufVariant, KTextVariantBufferConstructor );
    
    TAiwVariant des8Variant( ptr8 );
    AssertNotNullL( &des8Variant, KTextVariantDes8Constructor );
    
    RFile fileHandle;
    CleanupClosePushL( fileHandle );
    TAiwVariant fileVariant( fileHandle );
    AssertNotNullL( &fileVariant, KTextVariantFileConstructor );
    
    TAiwVariant sourceVariant( source );
    AssertNotNullL( &sourceVariant, KTextVariantSourceConstructor );
    
    assignedVariant = source;
    AssertNotNullL( &assignedVariant, KTextVariantAssignment );
    
    timeVariant.TypeId();
    AssertTrueL( ETrue, KTextVariantTypeId );
    
    TBool isEmpty = emptyVariant.IsEmpty();
    AssertTrueL( ETrue, KTextVariantIsEmpty );
    
    match = integerVariant.Get( getValue );
    AssertTrueL( match, KTextVariantGetInteger );
    
    match = uidVariant.Get( getUidValue );
    AssertTrueL( match, KTextVariantGetUid );
    
    match = desVariant.Get( getPtr16Value );
    AssertTrueL( match, KTextVariantGetPtr16 );
    
    match = timeVariant.Get( getTimeValue );
    AssertTrueL( match, KTextVariantGetTime );
    
    match = des8Variant.Get( getPtr8Value );
    AssertTrueL( match, KTextVariantGetPtr8 );
    
    RFile getFileHandleValue;
    CleanupClosePushL( getFileHandleValue );
    match = fileVariant.Get( getFileHandleValue );
    AssertTrueL( match, KTextVariantGetFile );
    
    getValue = integerVariant.AsTInt32();
    AssertIntL( KDefaultValue, getValue, KTextVariantAsTInt32 );
    
    getUidValue = uidVariant.AsTUid();
    AssertIntL( uidValue.iUid, getUidValue.iUid, KTextVariantAsTUid );
    
    getPtr16 = desVariant.AsDes();
    AssertTrueL( getPtr16 == ptr16, KTextVariantAsDes );
    
    getTimeValue = timeVariant.AsTTime();
    AssertTrueL( getTimeValue == timeValue, KTextVariantAsTTime );
    
    getPtr8 = des8Variant.AsData();
    AssertTrueL( getPtr8 == ptr8, KTextVariantAsData );
    
    getFileHandleValue = fileVariant.AsFileHandle();
    AssertTrueL( getFileHandleValue == fileHandle, KTextVariantAsFileHandle );
    
    emptyVariant.Reset();
    AssertTrueL( ETrue, KTextVariantReset );
    
    integerVariant.Set( KDefaultValue );
    AssertTrueL( ETrue, KTextVariantSetInteger );
    
    uidVariant.Set( uidValue );
    AssertTrueL( ETrue, KTextVariantSetUid );
    
    timeVariant.Set( timeValue );
    AssertTrueL( ETrue, KTextVariantSetTime );
    
    desVariant.Set( ptr16 );
    AssertTrueL( ETrue, KTextVariantSetDes16 );
    
    bufVariant.Set( buffer16 );
    AssertTrueL( ETrue, KTextVariantSetBuffer );
    
    des8Variant.Set( ptr8 );
    AssertTrueL( ETrue, KTextVariantSetDes8 );
    
    fileVariant.Set( fileHandle );
    AssertTrueL( ETrue, KTextVariantSetFile );
    
    timeVariant = timeValue;
    AssertTrueL( ETrue, KTextVariantTimeAssignment );
    
    uidVariant = uidValue;
    AssertTrueL( ETrue, KTextVariantUidAssignment );
    
    integerVariant = KDefaultValue;
    AssertTrueL( ETrue, KTextVariantIntegerAssignment );
    
    desVariant = ptr16;
    AssertTrueL( ETrue, KTextVariantDes16Assignment );
    
    bufVariant = buffer16;
    AssertTrueL( ETrue, KTextVariantBufferAssignment );
    
    des8Variant = ptr8;
    AssertTrueL( ETrue, KTextVariantDes8Assignment );
    
    fileVariant = fileHandle;
    AssertTrueL( ETrue, KTextVariantFileAssignment );
    
    AssertTrueL( assignedVariant == source, KTextVariantEquals );
    
    AssertTrueL( integerVariant != emptyVariant, KTextVariantNotEqual );
        
    CleanupStack::PopAndDestroy( 6, buffer16 ); // getFileHandleValue, fileHandle,
                                                // getBuffer8, buffer8,
                                                // getBuffer16, buffer16
    }
       
TInt CBCTestServiceHandlerCase::HandleNotifyL(
                                    TInt /*aCmdId*/,
                                    TInt aEventId,
                                    CAiwGenericParamList& /*aEventParamList*/,
                                    const CAiwGenericParamList& /*aInParamList*/ )
    {
    AssertTrueL( ETrue, KTextNotifyCallbackHandleNotifyL );
    
    switch (aEventId)
        {
        case KAiwEventStarted:
            AssertTrueL( ETrue, KTextNotifyCallbackEventStarted );
            break;
        case KAiwEventCompleted:
            AssertTrueL( ETrue, KTextNotifyCallbackEventCompleted );
            break;
        case KAiwEventCanceled:
            AssertTrueL( ETrue, KTextNotifyCallbackEventCanceled );
            break;
        case KAiwEventError:
            AssertTrueL( ETrue, KTextNotifyCallbackEventError );
            break;
        case KAiwEventOutParamCheck:
            AssertTrueL( ETrue, KTextNotifyCallbackEventOutParamCheck );
            break;
        case KAiwEventInParamCheck:
            AssertTrueL( ETrue, KTextNotifyCallbackEventInParamCheck );
            break;
        case KAiwEventStopped:
            AssertTrueL( ETrue, KTextNotifyCallbackEventStopped );
            break;
        case KAiwEventQueryExit:
            AssertTrueL( ETrue, KTextNotifyCallbackEventQueryExit );
            break;
        default:
            break;
        }
        
    return KErrNone;
    }
    
void CBCTestServiceHandlerCase::SetEmphasis( CCoeControl* /*aMenuControl*/,
                                             TBool /*aEmphasis*/ )
    {
    }

void CBCTestServiceHandlerCase::ProcessCommandL( TInt /*aCommandId*/ )
    {
    }

