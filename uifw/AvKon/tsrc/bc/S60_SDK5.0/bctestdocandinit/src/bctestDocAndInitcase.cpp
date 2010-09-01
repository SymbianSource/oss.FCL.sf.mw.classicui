/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
#include <eikenv.h>
#include <apmstd.h>
#include <PathInfo.h>
#include <apgcli.h>
#include <apmrec.h> 

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
        WAIT( 10 ),
        LeftCBA, 
        WAIT( 5 ),
        LeftCBA, 
        WAIT( 5 ),
        LeftCBA,
        WAIT( 5 ),
        LeftCBA, 
        DELAY( 15 ),         
        LeftCBA,
        DELAY( 1 ), 
        Down, 
        LeftCBA
        };
    AddTestScriptL( scripts, sizeof( scripts )/sizeof( TInt ) );
    }
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::DriveStatus
// ---------------------------------------------------------------------------
//
TCFDDriveStatus CBCTestDocAndInitCase::DriveStatus( const TDriveNumber aDriveNumber )
    {

    RFs& fs = CCoeEnv::Static()->FsSession();
    _LIT( KFat, "Fat" );

    // Check if the drive is already mounted
    TFullName fsName;
    TInt error( fs.FileSystemName( fsName, aDriveNumber ) );
    if( error )
        {
        return EDriveNotReady;
        }

    // check if MMC already mounted
    if( fsName.Length() == 0 )
        {
        // MMC drive isnt mounted at present, so try it now....
        error = fs.MountFileSystem( KFat, aDriveNumber );

        // If it's a locked MMC and the password is already known it'll be
        // unlocked automatically when it's mounted., otherwise the mount will
        // return with KErrLocked.....
        switch( error )
            {
            case KErrNone:
                {
                // OK to continue...
                break;
                }
            case KErrLocked:
                {
                return EDriveLocked;
                }
            default:
                {
                return EDriveNotReady;
                }
            }
        }
    TDriveInfo driveInfo;
    error = fs.Drive( driveInfo, aDriveNumber );
    if( error )
        {
        return EDriveNotReady;
        }

    // MMC is in slot
    if( driveInfo.iMediaAtt & KMediaAttLocked )
        {
        return EDriveLocked;
        }

    TVolumeInfo volumeInfo;
    error = fs.Volume( volumeInfo, aDriveNumber );
    if( error )
        {
        return EDriveNotReady;
        }

    return EDriveOK;
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
    switch ( aCmd )  
        {
        case EBCTestCmdDoc:
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
    _LIT( KEmbeddedFileName, "C:\\data\\Others\\DocHandleEmbedded.txt" );
    RFs& fs = CEikonEnv::Static()->FsSession();
    RFile embeddedFile;
    if( embeddedFile.Open( fs, KEmbeddedFileName, 
                           EFileWrite | EFileShareAny ) != KErrNone )
        {
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
    _LIT( KTempFileName, "C:\\data\\Others\\Temp.txt" );
    fs.Delete( KTempFileName );
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
    
    delete docHandler;
    }
  
// ---------------------------------------------------------------------------
// CBCTestDocAndInitCase::TestDocument2  (Test class CDocumentHandler)
// ---------------------------------------------------------------------------
//   
void CBCTestDocAndInitCase::TestDocument2L()
    {
    _LIT8( KMyMimeType, "text/vnd.bctest" );
    _LIT( KOldFileName, "C:\\data\\Others\\DocHandleEmbedded.txt" );
    _LIT( KOpenFileName, "C:\\data\\Others\\Open.txt" );
    _LIT( KOtherPath, "C:\\data\\Others\\" );
    
    _LIT( KNewFileName, "New.txt" );
    _LIT( KUnNameFile, "Unnamed" );
    TFileName path( KOtherPath );
    TFileName tmppath( KOtherPath );
    path.Append( KNewFileName );
    tmppath.Append( KUnNameFile );
    _LIT8( KContentText, "Content Text" );
    TDataType dataType( KMyMimeType );
    CEikProcess* proc = CEikonEnv::Static()->Process();
    CDocumentHandler *doc = CDocumentHandler::NewL(proc);
    CleanupStack::PushL( doc );
    _LIT( KNewL2 , "CDocumentHandler::NewL(CEikProcess*) invoked" );
    AssertNotNullL( doc, KNewL2 );

    RFs& fs = CEikonEnv::Static()->FsSession();
    RFile File1;
    fs.Delete( path );
    if ( File1.Open( fs, KOpenFileName, EFileWrite | EFileShareAny ) 
                                                       != KErrNone )
        {
        File1.Create( fs, KOpenFileName, EFileWrite | EFileShareAny );
        }
       
    TInt move = doc->MoveL( KOldFileName, KNewFileName, dataType, 0 );
    _LIT( KMoveL, "CDocumentHandler::MoveL() invoked" );
    AssertIntL( KErrNone, move, KMoveL );

    fs.Delete( tmppath );
    TInt save = doc->SaveL(KContentText, dataType, 0 );
    _LIT( KSaveL, "CDocumentHandler::SaveL() invoked" );
    AssertIntL( KErrNone, save, KSaveL );
    
    fs.Delete( path );
    TInt copy = doc->CopyL( File1, KNewFileName, dataType, 0 );
    _LIT( KCopyL1, "CDocumentHandler::CopyL() invoked" );
    AssertIntL( KErrNone, copy, KCopyL1 );
    
    File1.Close();

    fs.Delete( path );
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
