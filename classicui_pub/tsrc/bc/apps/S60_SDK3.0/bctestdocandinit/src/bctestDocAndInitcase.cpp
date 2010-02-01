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
#include <eikenv.h>
#include <apmstd.h>
#include <PathInfo.h>
#include <apgcli.h>
#include <apmrec.h> 
#include <bautils.h> // for BaflUtils::DeleteFile
#include "bctestdocandinitcase.h"
#include "bctestdocandinitcontainer.h"
#include "bctestdocandinit.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDocAndInitCase* CBCTestDocAndInitCase::NewL( 
    CBCTestDocAndInitContainer* aContainer )
    {
    CBCTestDocAndInitCase* self = new( ELeave ) CBCTestDocAndInitCase( 
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
CBCTestDocAndInitCase::CBCTestDocAndInitCase( 
    CBCTestDocAndInitContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDocAndInitCase::~CBCTestDocAndInitCase()
    {
  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDocAndInitCase::ConstructL()
    {    
        BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDocAndInitCase::BuildScriptL()
    { 
       const TInt scripts[] =
        {
        DELAY( 1 ), // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        LeftCBA, 
        LeftCBA, KeyOK,
        LeftCBA, KeyOK,
        LeftCBA, KeyOK,
        LeftCBA, LeftCBA, KeyOK,
        DELAY( 15 ),         
        LeftCBA,
        DELAY( 1 ), 
        REP(Down, 1 ), 
        LeftCBA
        };
    AddTestScriptL( scripts, sizeof( scripts )/sizeof( TInt ) );
 
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDocAndInitCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdDoc || aCmd > EBCTestCmdInit )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )  
        {
        case EBCTestCmdDoc:
            Cleanup();
            TestDocument1L();
            TestDocument2L();
            break;
        case EBCTestCmdInit:
            TestInitializationL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestDocAndInitCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdDoc||EBCTestCmdInit:
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
// CBCTestDocAndInitCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestDocAndInitCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }
    
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestInitialization
// ---------------------------------------------------------------------------
//     
void CBCTestDocAndInitCase::TestInitializationL()
    {
        TestAppUiFactoryL();
        TestCoCtlLibraryL();
        TestCtlLibraryL();
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestAppUiFactory  (Test class CEikAppUiFactory)
// ---------------------------------------------------------------------------
// 
void CBCTestDocAndInitCase::TestAppUiFactoryL()
    {
    CEikAppUiFactory* factory = new( ELeave ) CEikAppUiFactory();
    CleanupStack::PushL( factory );
    _LIT( KCEikAppUiFactory, "CEikAppUiFactory::CEikAppUiFactory() invoked" );
    AssertNotNullL( factory, KCEikAppUiFactory );
    
    factory->TouchPane();  
    _LIT( KTouchPane , "CEikAppUiFactory::TouchPane() invoked" );  
    AssertTrueL( ETrue, KTouchPane );
    
    factory->CurrentPopupToolbar();
    _LIT( KCurrentPopupToolbar, 
    "CEikAppUiFactory::CurrentPopupToolbar() invoked" );
    AssertTrueL( ETrue, KCurrentPopupToolbar );
    
    CAknToolbar* popup = factory->PopupToolbar();
    _LIT( KPopupToolbar, "CEikAppUiFactory::PopupToolbar() invoked" );  
    AssertTrueL( ETrue, KPopupToolbar );   
    
    factory->SetViewPopupToolbar( popup );  
    _LIT( KSetViewPopupToolbar, 
    "CEikAppUiFactory::SetViewPopupToolbar() invoked" );
    AssertTrueL( ETrue, KSetViewPopupToolbar );

    CleanupStack::PopAndDestroy( factory );    
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestCoCtlLibrary  (Test class CEikCoCtlLibrary)
// ---------------------------------------------------------------------------
// 
void CBCTestDocAndInitCase::TestCoCtlLibraryL()
    {
    CEikCoCtlLibrary::ButtonGroupFactory();
    _LIT( KButtonGroupFactory , 
    "CEikCoCtlLibrary::ButtonGroupFactory() invoked" );
    AssertTrueL( ETrue, KButtonGroupFactory );
    
    CEikCoCtlLibrary::ControlFactory();
    _LIT( KControlFactory , "CEikCoCtlLibrary::ControlFactory() invoked" );
    AssertTrueL( ETrue, KControlFactory );
    
    CEikCoCtlLibrary::ResourceFile();
    _LIT( KResourceFile , "CEikCoCtlLibrary::ResourceFile() invoked" );
    AssertTrueL( ETrue, KResourceFile );
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestCtlLibrary (Test class CEikCtlLibrary)
// ---------------------------------------------------------------------------
// 
void CBCTestDocAndInitCase::TestCtlLibraryL()
    {
    CEikCtlLibrary::ResourceFile();
    _LIT( KResourceFile , "CEikCtlLibrary::ResourceFile() invoked" );
    AssertTrueL( ETrue, KResourceFile );
    
    CEikCtlLibrary::ControlFactory();
    _LIT( KControlFactory , "CEikCtlLibrary::ControlFactory() invoked" );
    AssertTrueL( ETrue, KControlFactory );
    
    CEikCtlLibrary::InitializeL();
    _LIT( KInitializeL , "CEikCtlLibrary::InitializeL() invoked" );
    AssertTrueL( ETrue, KInitializeL );
    
    CEikCtlLibrary::ButtonGroupFactory();
    _LIT( KButtonGroupFactory , 
    "CEikCtlLibrary::ButtonGroupFactory() invoked" );
    AssertTrueL( ETrue, KButtonGroupFactory );
    }
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestDocument1(Test class CDocumentHandler)
// ---------------------------------------------------------------------------
//    
void CBCTestDocAndInitCase::TestDocument1L()
    {
    CDocumentHandler *docHandler = CDocumentHandler::NewL();
    _LIT( KNewL1 , "CDocumentHandler::NewL() invoked" );
    AssertNotNullL( docHandler, KNewL1 );    
       
    docHandler->SetExitObserver( this );
    _LIT( KSetExitObserver , 
    "CDocumentHandler::SetExitObserver(MAknServerAppExitObserver*) invoked" );
    AssertTrueL( ETrue, KSetExitObserver );
    
    docHandler->InParamListL();
    _LIT( KInParamListL , "CDocumentHandler::InParamListL() invoked" );
    AssertTrueL( ETrue, KInParamListL );
    
    TDataType dataType;    
    _LIT( KEmbeddedFileName, "C:\\BCTestLog\\DocHandleEmbedded.txt" );
    RFs& fs = CEikonEnv::Static()->FsSession();
    RFile embeddedFile;
    if( embeddedFile.Open( fs, KEmbeddedFileName, 
                           EFileWrite | EFileShareAny ) != KErrNone ){
        embeddedFile.Create( fs, KEmbeddedFileName, 
                             EFileWrite | EFileShareAny );
    }
    _LIT8( KContent, "Content Text" );
    embeddedFile.Write( KContent );
    TInt error;
    error = docHandler->OpenFileEmbeddedL( KEmbeddedFileName, dataType );
    _LIT( KOpenFileEmbeddedL1 , 
    "CDocumentHandler::OpenFileEmbeddedL(const TDesC&,TDataType&) invoked" );
    AssertIntL( KErrNone, error, KOpenFileEmbeddedL1 );

    error = docHandler->OpenFileEmbeddedL( embeddedFile, dataType );
    _LIT( KOpenFileEmbeddedL2 , 
    "CDocumentHandler::OpenFileEmbeddedL(RFile&,TDataType&) invoked" );
    AssertIntL( KErrNone, error, KOpenFileEmbeddedL2 );

    TBuf<32> fileName;
    docHandler->CheckFileNameExtension( fileName, dataType );
    _LIT( KCheckFileNameExtension ,
    "CDocumentHandler::CheckFileNameExtension(TDes&,TDataType&) invoked" );
    AssertTrueL( ETrue, KCheckFileNameExtension );
    
    TBool canOpen = docHandler->CanOpenL( dataType );
    _LIT( KCanOpenL , "CDocumentHandler::CanOpenL(TDataType&) invoked" );
    AssertTrueL( canOpen, KCanOpenL );

    TBool canHandle = docHandler->CanHandleL( dataType );  
    _LIT( KCanHandleL , "CDocumentHandler::CanHandleL(TDataType&) invoked" );
    AssertTrueL( canHandle, KCanHandleL );

    TBool canSave = docHandler->CanSaveL( dataType );
    _LIT( KCanSaveL , "CDocumentHandler::CanSaveL(TDataType&) invoked" );
    AssertTrueL( canSave, KCanSaveL );

    docHandler->GetPath( fileName );
    _LIT( KGetPath, "CDocumentHandler::GetPath(TDes&) invoked" );
    AssertTrueL( ETrue, KGetPath );
    
    RFile tempFile;
    _LIT( KTempFileName, "C:\\BCTestLog\\Temp.txt" );
    docHandler->SaveTempFileL( KContent, dataType, KTempFileName, tempFile );
    _LIT( KSaveTempFileL, "CDocumentHandler::SaveTempFileL() invoked" );
    AssertTrueL( ETrue, KSaveTempFileL );
    
    tempFile.Close();

    TUid uid;
    docHandler->HandlerAppUid( uid );
    _LIT( KHandlerAppUid, "CDocumentHandler::HandlerAppUid(TUid&) invoked" );
    AssertTrueL( ETrue, KHandlerAppUid );

    embeddedFile.Close();    

    docHandler->OutParamList();
    _LIT( KOutParamList , "CDocumentHandler::OutParamList() invoked" );
    AssertTrueL( ETrue, KOutParamList );
    
//	CleanupStack::PopAndDestroy();	//iDocument
    delete docHandler;
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestDocument2  (Test class CDocumentHandler)
// ---------------------------------------------------------------------------
//   
void CBCTestDocAndInitCase::TestDocument2L()
    {
    _LIT8( KMyMimeType, "text/vnd.bctest" );
    _LIT( KOldFileName, "C:\\BCTestLog\\DocHandleEmbedded.txt" );
    _LIT( KOpenFileName, "C:\\BCTestLog\\DocInitOpen.txt" );
    _LIT( KNewFileName, "C:\\BCTestLog\\DocInitNew.txt" );
    _LIT8( KContentText, "Content Text" );
    TDataType dataType( KMyMimeType );
    CEikProcess* proc = CEikonEnv::Static()->Process();
    CDocumentHandler *doc = CDocumentHandler::NewL(proc);
    CleanupStack::PushL( doc );
    _LIT( KNewL2 , "CDocumentHandler::NewL(CEikProcess*) invoked" );
    AssertNotNullL( doc, KNewL2 );

    RFs& fs = CEikonEnv::Static()->FsSession();
    RFile File1;
    if ( File1.Open( fs, KOpenFileName, EFileWrite | EFileShareAny ) 
                                                       != KErrNone ){
        File1.Create( fs, KOpenFileName, EFileWrite | EFileShareAny );
    }
       
    TInt move = doc->MoveL( KOldFileName, KOpenFileName, dataType, 0 );
    _LIT( KMoveL, "CDocumentHandler::MoveL() invoked" );
    AssertIntL( KErrNone, move, KMoveL );

    TInt save = doc->SaveL(KContentText, dataType, 0 );
    _LIT( KSaveL, "CDocumentHandler::SaveL() invoked" );
    AssertIntL( KErrNone, save, KSaveL );
    
    TInt copy = doc->CopyL( File1, KNewFileName, dataType, 0 );
    _LIT( KCopyL1, "CDocumentHandler::CopyL() invoked" );
    AssertIntL( KErrNone, copy, KCopyL1 );
    
   	File1.Close();

	copy = doc->CopyL( KOpenFileName, KNewFileName, dataType, 0 );
	_LIT( KCopyL2 ,
	"CDocumentHandler::CopyL(TDesC8&,TDesC&,TDataType&,TUint) invoked" );
    AssertIntL( KErrNone, copy, KCopyL2 );

    TInt error = doc->SilentMoveL( KOpenFileName, KNewFileName, 
        PathInfo::PhoneMemoryRootPath(), dataType, 0 );
    _LIT( KSilentMoveL, "CDocumentHandler::SilentMoveL() invoked" );
    AssertIntL( KErrNone, error, KSilentMoveL );
     
    CleanupStack::PopAndDestroy( doc ); 
    _LIT( KUCDocumentHandler, 
    "CDocumentHandler::~CDocumentHandler() invoked" );
    AssertTrueL( ETrue, KUCDocumentHandler );
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::HandleServerAppExit (from MAknServerAppExitObserver)
// ---------------------------------------------------------------------------
//
void CBCTestDocAndInitCase::HandleServerAppExit( TInt /*aReason*/ )
    {
    }
void CBCTestDocAndInitCase::Cleanup()
    {
    RFs& fs = CEikonEnv::Static()->FsSession();
    _LIT( KPathAndPrefix1, "C:\\data\\others\\unname*");
    _LIT( KPathAndPrefix2, "C:\\data\\others\\DocInit*");
    BaflUtils::DeleteFile( fs, KPathAndPrefix1 );
    BaflUtils::DeleteFile( fs, KPathAndPrefix2 );
    }
