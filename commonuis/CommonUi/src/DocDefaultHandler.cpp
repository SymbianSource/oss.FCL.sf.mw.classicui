/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Default Epoc-style content handler.
*
*/


#include <bautils.h>                // For NearestLanguageFile(..)
#include <eikdoc.h>                 // CEikDocument
#include <AknQueryDialog.h>         // CAknQueryDialog
#include <StringLoader.h>           // For loading resource strings
#include <stringresourcereader.h>   // CStringResourceReader
#include <sysutil.h>                // For FFSSpaceBelowCriticalLevelL(..)
#include <uri16.h>                  // For url handling.

#include <avkon.rsg>                // Avkon ids
#include <documenthandlerui.rsg>    // Resource ids

#include "DocDefaultHandler.h"      // Class decration
#include "DocSaver.h"               // Saver util
#include "DocConstants.h"           // Documenthandler constants
#include "DocResourceFile.h"        // CDocResourceFile

#include <AiwGenericParam.h>        // Generic parameters

#ifdef RD_MULTIPLE_DRIVE
#include <driveinfo.h>      //DriveInfo
#include <coemain.h>
#endif

#include "pathinfo.h"               // PathInfo
#include <featmgr.h>                // FeatureManager

#ifdef RD_CONTENTNOTIFICATION
#include <contentnotification.hrh>
#include <contentcreatedevent.h>
#include <contentnotification.h>
#endif

#ifdef ENABLE_DRM
#include <caf/caf.h>
#include <caf/cafplatform.h>
#include <Oma2Agent.h>
#include <DcfEntry.h>               // CDcfEntry 
#include <DcfRep.h>                 // CDcfRep
#endif 

#ifdef __KEEP_DRM_CONTENT_ON_PHONE
#include <oem/distributablechecker.h>
#endif

#include <f32file.h>

using namespace ContentAccess;
_LIT( KFSName, "Fat" );

// ================= LOCAL FUNCTIONS ========================
LOCAL_C inline TBool NeedsToReplaceDcf2Extension( TDes& aFileName )
    {
    TParsePtrC ptr( aFileName );
    if ( ptr.ExtPresent() )
        {
        TPtrC ext( ptr.Ext() );
        if( !KOma2DcfExtensionAudio().CompareF( ext ) ||
            !KOma2DcfExtensionVideo().CompareF( ext ) ||
            !KOma2DcfExtension().CompareF( ext ) )
            {
            // no need to replace extension.
            return EFalse;
            }
        }
    return ETrue;
    }

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CDocDefaultHandler::CDocDefaultHandler(    
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher,
    TDocServiceMode aServiceMode ) : 
        iApaLs( aDocDispatcher->ApaLs() ),
        iDataType( aDataType ),
        iDocDispatcher( aDocDispatcher ),
        iFileManager( NULL ),
        iSavedAsTemp( EFalse ),
        iServiceMode( aServiceMode ),
        iStatus( KErrNone ),
        iUid( aUid ),
        iOpenService( NULL ),
        iMMCSaveAllowed ( ETrue )
    {
    }
    
// Destructor  
//
CDocDefaultHandler::~CDocDefaultHandler()
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::~CDocDefaultHandler"));
    #endif      
      
    iFs.Close();        // Close sessions
    
    if ( iOpenService )
    {
        delete iOpenService;
    }                            

    delete iFileManager; // Delete members  
    delete iAiwParams;
    delete iOutAiwParams;
    delete iMimeExtensions;
    delete iExtensions;
    delete iIdle;
    }

// ---------------------------------------------------------
// Two-phased constructor. 
// ---------------------------------------------------------
//
CDocDefaultHandler* CDocDefaultHandler::NewL(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher,
    TDocServiceMode aServiceMode )
    {
    CDocDefaultHandler * self = NewLC( aDataType, aUid, 
                                       aDocDispatcher, aServiceMode );
    CleanupStack::Pop();
    return self;
    }
    
// ---------------------------------------------------------
// Two-phased constructor. Leaves the contructed instance in to the 
// clean up stack.
// ---------------------------------------------------------
//
CDocDefaultHandler* CDocDefaultHandler::NewLC(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher,
    TDocServiceMode aServiceMode )
    {
    CDocDefaultHandler* self = 
        new ( ELeave ) CDocDefaultHandler( aDataType, aUid, 
                                           aDocDispatcher, aServiceMode );
    CleanupStack::PushL( self );
    self->BaseConstructL();
    return self;
    }

// ---------------------------------------------------------
// Epoc contructor
// ---------------------------------------------------------
//  
void CDocDefaultHandler::BaseConstructL()
    {       
    User::LeaveIfError( iFs.Connect() ); // Connect to servers                      
    iFileManager = CFileMan::NewL( iFs );// Construct a filemanager   
    PopulateAppInfo();    
    }

// ---------------------------------------------------------
// CDocDefaultHandler::SaveTempFileL()
// Save the content to the correct directory. 
// This method is used from CDocumentHandler::SaveTempFileL() 
// and CDocumentHandler::SaveL()
// ---------------------------------------------------------
//
TInt CDocDefaultHandler::SaveTempFileL( 
    const TDesC8& aContent, 
    const TUint aAttr,
    TDes& aFileName)
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::SaveTempFileL(aContent, aAttr, aFileName) Called"));
    #endif 

    TInt error = KErrNone;              // Error code

    if ( aContent.Size() == 0 )         // Check if there is anything to save.
        {
        return SetAndReturnStatus( KNullContent );  
        }

    error = SaveChecksL(aContent);
    
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::SaveTempFileL: error=%d after filename checks."), error);
    #endif 
    if ( error == KErrNone )
        {              
        #ifdef _DEBUG        
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::SaveTempFileL: Trying to save the file..."));
        #endif 
        iFs.MkDirAll( iDestFile );
        
        RFile tempfile;
        User::LeaveIfError( tempfile.Replace( iFs, iDestFile, EFileShareAny | EFileWrite) );   
        
        HBufC* waitNoteText = HBufC::NewLC( KDocWaitNoteMaxLen );
        TPtr waitNoteTextPtr = waitNoteText->Des();  
        WaitNoteTextL( waitNoteTextPtr );              
        
        CDocAsyncSaver* asyncSaver = CDocAsyncSaver::NewLC();
        AddResourcesL();
        asyncSaver->WriteToFileL(
            aContent, 
            tempfile, 
            waitNoteTextPtr );
        RemoveResources();
        User::LeaveIfError( asyncSaver->Status().Int() );
        CleanupStack::PopAndDestroy( 2 ); // asyncSaver, waitNoteTextPtr

        User::LeaveIfError( tempfile.SetAtt( aAttr, 0 ) );
        tempfile.Close();
        
        // Put filename to aFileName
        aFileName.Copy(iDestFile);

        #ifdef _DEBUG        
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::SaveTempFileL: File %S saved and closed!"), &iDestFile);
        #endif 
        }

    return SetAndReturnStatus( error );

    }

// ---------------------------------------------------------
// CDocDefaultHandler::SaveChecksL()
// This method is called from SaveTempFileL.
// Check disk space for file and generate filename.
// ---------------------------------------------------------
//
TInt CDocDefaultHandler::SaveChecksL(const TDesC8& aContent)
    {
    TInt error = KErrNone;   
    if (GenerateFileNameL( iUid, iDestFile, iDataType, aContent.Length() ) == KErrCancel)
        {
        return KUserCancel;
        }
        
    CheckDiskspaceL( aContent.Size() ); // Leave if not enough space to save.
    TBool done = EFalse;                // Try saving until done    
    do
        {
        TBool valid  = iFs.IsValidName( iDestFile );
        TBool exists = BaflUtils::FileExists( iFs, iDestFile );

        #ifdef _DEBUG        
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::SaveChecksL: Filename valid=%d"), valid);
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::SaveChecksL: Filename exists=%d"), exists);
        #endif 

        // If filename allready exists, generate new name without asking user 
        if ( exists || !valid )
            {
            GenerateTempFileNameL( iDestFile ,MaxNameLen() );
            }
        else
            {
            if ( error == KErrNone )
                {
                done = ETrue;
                }
            else
                {
                User::Leave( SetAndReturnStatus( error ) );
                }
            } // else
        }
    while ( !done ); 
    
    // If file is saved to temp place, DocumentHandler is responsible of deleting this file.
    if ( iSavedAsTemp ) 
        {
        iDocDispatcher->SetTempFile(iDestFile);
        }

    return error;
    }

// ---------------------------------------------------------    
// CDocDefaultHandler::CopyChecksAndQueriesL()   
// This method is called from CopyOrMoveL and CopyHandleL. 
// Check disk space for file, generate filename and
// and show save as query to user.
// ---------------------------------------------------------    
//
TInt CDocDefaultHandler::CopyChecksAndQueriesL(TInt aDataSize)
    {
    TInt error = KErrNone;      // Error code
    
    #ifdef _DEBUG      
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CopyChecksAndQueriesL: Enter, aDataSize = %d"), aDataSize);
    #endif
    
    if (GenerateFileNameL( iUid, iDestFile, iDataType, aDataSize) == KErrCancel)
        {
        return KUserCancel;
        }
    CheckDiskspaceL( aDataSize ); // Leave if not enough space to save.
    
    // Make destination directories
    error = iFs.MkDirAll( iDestFile );
    if ( error != KErrAlreadyExists && error != KErrNone )
        {
        User::Leave( error );   // Something unexpected happend
        }
    TBool done = EFalse;        // Try until done    
    do 
        {
        TBool valid  = iFs.IsValidName( iDestFile );
        TBool exists = BaflUtils::FileExists( iFs, iDestFile );

        #ifdef _DEBUG      
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CopyChecksAndQueriesL: Filename = %S"), &iDestFile);
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CopyChecksAndQueriesL: Filename valid=%d"), valid);
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CopyChecksAndQueriesL: Filename exists=%d"), exists);
        #endif 

        // If filename allready exists, generate new name without asking 
        // user in case of SilentMove
        if ( (DocOperation() == EDocSilentMove) &&
             (exists || !valid) )
            {
            GenerateTempFileNameL( iDestFile ,MaxNameLen() );
            }
        else if ( !valid || (exists && !iSavedAsTemp) )
            {
            switch ( SaveAsQueryL( iDestFile ) )
                {
                case EDocFileCancelWrite:
                    done = ETrue;  
                    iDestFile.Zero();
                    error = KUserCancel;
                    HandleServerAppExit(0);
                    break;
                case EDocFileOverWrite:
                    done = ETrue;
                    error = KErrNone;
                    break;
                case EDocFileRenameNew:  
                    CheckFileNameExtensionL( iDestFile, iDataType );
                    break;
                default:
                    User::Leave( SetAndReturnStatus( KErrUnknown ) );
                } // switch
            } // if
        else  // if
            {
             done = ETrue;
             error = KErrNone;
            }
        } while ( !done );// while
    
    // If file is saved to temp place, DocumentHandler is responsible of deleting this file.
    if ( iSavedAsTemp ) 
        {
        iDocDispatcher->SetTempFile(iDestFile);
        }
        
    #ifdef _DEBUG      
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CopyChecksAndQueriesL: Finished, error = %d"), error);
    #endif
        
    return error;
    }

// ---------------------------------------------------------    
// CDocDefaultHandler::CopyOrMoveL()    
// Copy/Move file to the correct directory. DocOperation() 
// tells what we do (copy/move/silentmove)
// --------------------------------------------------------- 
//   
TInt CDocDefaultHandler::CopyOrMoveL( const TUint aAttr )
    {
    TInt error = KErrNone;      // Error code
    TEntry fileEntry;           // File entry
    
    IsMMCSaveAllowedL(iSourceFile);
    
    User::LeaveIfError( iFs.Entry( iSourceFile, fileEntry ) );

    error = CopyChecksAndQueriesL(fileEntry.iSize);

    if ( error == KErrNone )
        {             
        HBufC* waitNoteText = HBufC::NewLC( KDocWaitNoteMaxLen );
        TPtr waitNoteTextPtr = waitNoteText->Des();  
      
        CDocAsyncSaver* asyncSaver = CDocAsyncSaver::NewLC();
		if (DocOperation() == EDocSilentMove)    
            {
            asyncSaver->MoveFileL(
                iFileManager,
                iSourceFile, 
                iDestFile, 
                ETrue,                 
                waitNoteTextPtr,
                ETrue );
            }
		else 
			{
			WaitNoteTextL( waitNoteTextPtr );                
			// This function is called either from MoveL or CopyL or SilentMoveL
			if (DocOperation() == EDocMove)
    			{
           	 	AddResourcesL();
           	 	asyncSaver->MoveFileL(
           		   iFileManager,
           	 	   iSourceFile, 
       			   iDestFile, 
       			   ETrue,                
   		    	   waitNoteTextPtr,
          	 	   EFalse );
           	 	RemoveResources();
    			}
   		 	else
   		 		{
   		 		AddResourcesL();
            	asyncSaver->CopyFileL(
       		 		iFileManager,
       		 		iSourceFile, 
       		 		iDestFile, 
           			ETrue,                 
           	 		waitNoteTextPtr );
           		 RemoveResources();
           		 }
			}
    
        error = asyncSaver->Status().Int();   
        User::LeaveIfError( error );
        User::LeaveIfError( iFileManager->Attribs( iDestFile, aAttr, 0, TTime( 0 ), 0 ) );
        if(asyncSaver->ShowDialog() && IsConfNoteAllowed())
            {
            HBufC* confNoteText = HBufC::NewLC( KDocConfNoteMaxLen );
            TPtr confNoteTextPtr = confNoteText->Des();  
            ConfirmationNoteTextL( confNoteTextPtr );  
            CDocSaver::ConfNoteL( confNoteTextPtr, ETrue );
            CleanupStack::PopAndDestroy( 1 ); // confNoteTextPtr
            }
        
        CleanupStack::PopAndDestroy( 2 ); // asyncSaver, waitNoteTextPtr
          
        // Notify MediaGallery that its content may have been changed
        TRAP_IGNORE(UpdateMediaGalleryIfNeededL());
    
        // Notify DCFRepository about new file
        // DcfRepository leaves if file is not-DRM file, so this call needs to be TRAPPED
        TRAP_IGNORE(UpdateDCFRepositoryL());
        }

    return SetAndReturnStatus( error );
    }
    
// ---------------------------------------------------------    
// CDocDefaultHandler::CopyHandleL()    
// Copy file to the correct directory. 
// --------------------------------------------------------- 
//   
TInt CDocDefaultHandler::CopyHandleL( const RFile& aSourceFile, const TUint aAttr )
    {
    TInt error = KErrNone;      // Error code    
    TInt fileSize;
    
    IsMMCSaveAllowedL(aSourceFile);
    
    User::LeaveIfError( aSourceFile.Size(fileSize) );

    error = CopyChecksAndQueriesL(fileSize);

    if ( error == KErrNone )
        {
        HBufC* waitNoteText = HBufC::NewLC( KDocWaitNoteMaxLen );
        TPtr waitNoteTextPtr = waitNoteText->Des();  
        WaitNoteTextL( waitNoteTextPtr );              

        CDocAsyncSaver* asyncSaver = CDocAsyncSaver::NewLC();

        AddResourcesL();
        asyncSaver->CopyFileL(
            iFileManager, 
            aSourceFile, 
            iDestFile, 
            ETrue, 
            waitNoteTextPtr );
        RemoveResources();

        error = asyncSaver->Status().Int();   
        User::LeaveIfError( error );
        User::LeaveIfError( iFileManager->Attribs( iDestFile, aAttr, 0, TTime( 0 ), 0 ) );       
        if(asyncSaver->ShowDialog() && IsConfNoteAllowed())
            {
            HBufC* confNoteText = HBufC::NewLC( KDocConfNoteMaxLen );
            TPtr confNoteTextPtr = confNoteText->Des();  
            ConfirmationNoteTextL( confNoteTextPtr );
            CDocSaver::ConfNoteL( confNoteTextPtr, ETrue );
            CleanupStack::PopAndDestroy( 1 ); // confNoteTextPtr
            }
        
        CleanupStack::PopAndDestroy( 2 ); // asyncSaver, waitNoteTextPtr
        
        // Notify MediaGallery that its content may have been changed
        TRAP_IGNORE(UpdateMediaGalleryIfNeededL());
    
        // Notify DCFRepository about new file
        // DcfRepository leaves if file is not-DRM file, so this call needs to be TRAPPED
        TRAP_IGNORE(UpdateDCFRepositoryL());
        }

    return SetAndReturnStatus( error );
    }

// ---------------------------------------------------------
// CDocDefaultHandler::SetSrcFileName()
// Check the name and sets iSourceFile if ok.
// ---------------------------------------------------------
//
TInt CDocDefaultHandler::SetSrcFileName( const TDesC& aFileName )
    {
    __ASSERT_DEBUG( 
        aFileName.Length() <= KMaxFileName,
        User::Panic( _L( "DocDefaultHandler" ), KErrBadName ) );

    if ( !iFs.IsValidName( aFileName ) )
        return SetAndReturnStatus( KErrBadName );
        
    iSourceFile = aFileName;
    return SetAndReturnStatus( KErrNone );
    }

// ---------------------------------------------------------
// CDocDefaultHandler::SetDestName()
// Check the name and set iDestFile.
// ---------------------------------------------------------
//    
TInt CDocDefaultHandler::SetDestName( const TDesC &aFilename )
    {
    TParse parse;

    parse.Set( aFilename, NULL, NULL );
    // drop possible drive letter and path.
    iDestFile.Copy( parse.NameAndExt() );        

    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::SetDestName : iDestFile=%S"), &iDestFile);
    #endif 

    return SetAndReturnStatus( KErrNone );
    }

// ---------------------------------------------------------
// CDocDefaultHandler::SetRootPath()
// Set root path of File which should be used.
// ---------------------------------------------------------
//    
TInt CDocDefaultHandler::SetRootPath( const TDesC& aRootPath )
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::SetRootPath : aRootPath=%S"), &aRootPath);
    #endif  
   
    TChar rootChar = aRootPath[0];
    TDriveList driveList; 
    TBool invalidRootPath = ETrue;

    if( iFs.DriveList( driveList ) == KErrNone )
        {
        for ( TInt i = 0; i < driveList.Length(); i++ )
            {
            TDriveInfo info;  
            if ( iFs.Drive( info, i ) == KErrNone &&
                 info.iType != EMediaNotPresent )
                {
                TChar driveChar;
                RFs::DriveToChar( i, driveChar );
                if ( driveChar == rootChar)
                    {
                	invalidRootPath = EFalse;
                	break;
                    }  
                }
            }
        }
      
    if( !invalidRootPath )
        {
    	iRootPath.Copy( aRootPath ); 
    	return SetAndReturnStatus( KErrNone );
    	}
    else
        {
    	return KNotInitialized; 
    	}
    }

// ---------------------------------------------------------
// CDocDefaultHandler::AddToParamListL()
// Add parameters (gives as parameter) to iAiwParams
// ---------------------------------------------------------
//    
void CDocDefaultHandler::AddToParamListL(const CAiwGenericParamList& aParams)
    {
    // Clear previous parameters.
    if (!iAiwParams)
        {
        iAiwParams = CAiwGenericParamList::NewL();
        }
    iAiwParams->AppendL( aParams ); 
    }

// ---------------------------------------------------------
// CDocDefaultHandler::OutputParamsL()
// Is this method needed?
// ---------------------------------------------------------
//    
const CAiwGenericParamList* CDocDefaultHandler::OutputParamsL()
    { 
/* TODO: How to get outputparams, or is these even needed?    
    if (iStore && iDictionary)
        {       
        delete iOutAiwParams;
        iOutAiwParams = NULL;
        iOutAiwParams = CAiwGenericParamList::NewL();

        RStoreReadStream stream;
        TStreamId id = iDictionary->At(KUidEmbedOutputStream);

        stream.OpenLC(*iStore, id);
        iOutAiwParams->InternalizeL(stream);
        CleanupStack::PopAndDestroy();  // stream
        }
*/
    return iOutAiwParams;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::SetDataType()
// Set the data type (iDataType)
// ---------------------------------------------------------
//    
void CDocDefaultHandler::SetDataType( const TDataType& aDataType )
    {
    iDataType = aDataType;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::OpenFileEmbeddedL()
// Calls Avkon Open File Service with file handle which should
// be opened. Also UID of application which should be launched 
// and iAiwParams is given as parameter. 
// ---------------------------------------------------------
//        
TInt CDocDefaultHandler::OpenFileEmbeddedL(RFile& aFileHandle )
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::OpenFileEmbeddedL(aFileHandle) Called"));
    #endif 

    if ( iOpenService )
        {
        delete iOpenService;
        iOpenService = NULL;
        }
    
    iOpenService = CAknOpenFileService::NewL(iUid, aFileHandle, this, iAiwParams);

    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::OpenFileEmbeddedL: Returns")) ;
    #endif 
    return SetAndReturnStatus( KErrNone );  // If we're still here, everything is ok.
    } 
    
// ---------------------------------------------------------
// CDocDefaultHandler::OpenFileL( )
// Calls RApaLsSession::StartDocument with file handle which 
// should be launched on standalone. 
// ---------------------------------------------------------
//        
TInt CDocDefaultHandler::OpenFileL(RFile& aFileHandle )
    {
    TThreadId id;

    User::LeaveIfError( iApaLs->StartDocument( aFileHandle, iDataType, id ) );

    // If client try to open embedded, but handler application supports only 
    // stand-alone open, then we need to notify exit instantly to avoid problems.
    if (DocOperation() == EDocOpenFileEmb)
        {
        if ( !iIdle )
            {
            iIdle = CIdle::NewL( CActive::EPriorityIdle );
            }

        if ( !iIdle->IsActive() )
            {
            iIdle->Start( TCallBack( IdleNotifyServerAppExit, this ) );
            }
        }
    
    return SetAndReturnStatus( KErrNone );  // If we're still here, everything is ok.
    }

// ---------------------------------------------------------
// CDocDefaultHandler::IdleNotifyServerAppExit( )
// Used for notifying server app exit with CIdle when
// OpenFileEmbedded operation has actually opened stand-alone.
// ---------------------------------------------------------
//
TInt CDocDefaultHandler::IdleNotifyServerAppExit( TAny* aParam )
    {
    static_cast<CDocDefaultHandler*>( aParam )->HandleServerAppExit(0);
    return EFalse;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::HandleServerAppExit()
// Delegates the exit signal to the listener registered for
// DocumentHandler. Tries to delete temporary file. If it
// fail we'll try again in the destructor.
// ---------------------------------------------------------
//    
void CDocDefaultHandler::HandleServerAppExit( TInt aReason )
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::HandleServerAppExit : Exit notified."));
    #endif 

    if ( iExitNotified )
        return;
    
    if ( iDocDispatcher->ServerAppExitObserver() )
        {
         #ifdef _DEBUG        
         RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::HandleServerAppExit : Exit notification forwarded."));
        #endif 
        iDocDispatcher->ServerAppExitObserver()->HandleServerAppExit( aReason );
        }
        
    // We should base call in case of EAknCmdExit (to close client application)
    if (aReason == EAknCmdExit)
        {
        MAknServerAppExitObserver::HandleServerAppExit(aReason);
        }
        
    iExitNotified = ETrue;   
    SetAndReturnStatus( KErrNone );
    } 
// ---------------------------------------------------------
// CDocDefaultHandler::CanBeSavedToMmcL()
// Check if there is possibility to save data to MMC
// ---------------------------------------------------------
//    
TBool CDocDefaultHandler::CanBeSavedToMmcL()
    {       
    TBool retval = ETrue;
    TResourceReader reader;
    CDesCArrayFlat *exArr;

    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CanBeSavedToMmcL : Enter "));
    #endif 

    // Check if MMC feature is supported.
    if (!FeatureManager::FeatureSupported( KFeatureIdMmc ) )
        {
        return EFalse;
        }

    // Check if there is MMC card inserted & ok.
    if( !IsMMCLocked() ) // Request when unlocked.
        {            
        TDriveUnit unit(PathInfo::MemoryCardRootPath());
        TInt drive( unit );
        TVolumeInfo volumeInfo;
        TInt error(iFs.Volume(volumeInfo, drive));
        if ( error != KErrNone )
            {
            return EFalse;
            }
        }
        
    // It is not allowed to saving DRM protected file to MMC if this
    // feature flag is defined.
    #ifdef __KEEP_DRM_CONTENT_ON_PHONE
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CanBeSavedToMmcL : (KEEP_DRM) Let's check if MMC save allowed."));
    #endif 
    if (!iMMCSaveAllowed)
        {
        #ifdef _DEBUG        
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CanBeSavedToMmcL : (KEEP_DRM) iMMCSaveAllowed = EFalse"));
        #endif 
        return EFalse;
        }
    #endif

    // Check if this MIME type is listed as an exception which is never saved to MMC
    // card.
    CreateDocResourceReaderLC(reader, R_DOCUMENT_HANDLER_EXCEPTION_TYPES_LIST);
    exArr = reader.ReadDesCArrayL();    
    if (exArr)
        {
        TInt posTmp;
        if (exArr->Find(iDataType.Des(), posTmp) == 0)
            {
            retval = EFalse;
            }
        delete exArr;   
        }
    CleanupStack::PopAndDestroy(); // reader

    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CanBeSavedToMmcL : Finished and returns %d"), retval);
    #endif 
    return retval;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::Status()
// Get the iStatus
// ---------------------------------------------------------
//        
TInt CDocDefaultHandler::Status() const
    {
    return iStatus;
    }
    
// ---------------------------------------------------------
// CDocDefaultHandler::GetPath()
// Return the path where the content was saved/copied
// ---------------------------------------------------------
//        
void CDocDefaultHandler::GetPath( TDes& aPath ) const
    {
    aPath.Copy( iDestFile );
    }

// ---------------------------------------------------------
// CDocDefaultHandler::CanOpen()
// Is the handler capable of opening the mime type
// ---------------------------------------------------------
//         
TBool CDocDefaultHandler::CanOpen() const 
    {
    return ( iServiceMode == EDocOpenOnly || iServiceMode == EDocOpenAndSave );
    }
    
// ---------------------------------------------------------
// CDocDefaultHandler::CanSave()
// Is the handler capable of saving the mime type
// ---------------------------------------------------------
//        
TBool CDocDefaultHandler::CanSave() const
    {
    return ( iServiceMode == EDocSaveOnly || iServiceMode == EDocOpenAndSave );
    }

// ---------------------------------------------------------
// CDocDefaultHandler::IsViewerOperation
// Is the operation viewing (ETrue) or saving (EFalse) operation
// ---------------------------------------------------------
// 
TBool CDocDefaultHandler::IsViewerOperation( TDocOperation aOperation )
    {
    switch ( aOperation )
        {
        case EDocOpenFile:
        case EDocOpenFileEmb:
            return ETrue;
        case EDocCopy:  
        case EDocMove:
        case EDocSilentMove:
        case EDocSave:
        case EDocSaveAs:
        case EDocSaveTemp:
            return EFalse;
        default:
            break;
        }
    return EFalse;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::IsConfNoteAllowed()
// Are we allowed to show confirmation note. In case of 
// SilentMove and viewer operation we are not allowed to
// show this note.
// ---------------------------------------------------------
// 
TBool CDocDefaultHandler::IsConfNoteAllowed()
    {
    if (DocOperation() == EDocSilentMove || DocOperation() == EDocSaveTemp)
        {
        return EFalse;
        }
    else 
        {
        return ( !IsViewerOperation( DocOperation() ) );
        }
    }

// ---------------------------------------------------------
// CDocDefaultHandler::HideFileExtension()
// Should we hide file extension. This should be overriden
// in derived handlers if needed.
// ---------------------------------------------------------
// 
TBool CDocDefaultHandler::HideFileExtension()
    {
    return EFalse;
    }
#ifdef RD_MULTIPLE_DRIVE
// ---------------------------------------------------------
// CDocDefaultHandler::CanOnlyBeSavedToPhoneMemory()
// check to see if the content can only be saved to Phone memory
// ---------------------------------------------------------
//
TBool CDocDefaultHandler::CanOnlyBeSavedToPhoneMemoryL()
	{
	TBool retval = EFalse;
	CDesCArrayFlat *exArr;
	TResourceReader reader;
	// It is not allowed to saving DRM protected file to MMC if this
    // feature flag is defined.
    #ifdef __KEEP_DRM_CONTENT_ON_PHONE
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CanBeSavedToMmcL : (KEEP_DRM) Let's check if MMC save allowed."));
    #endif 
    if (!iMMCSaveAllowed)
        {
        #ifdef _DEBUG        
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CanBeSavedToMmcL : (KEEP_DRM) iMMCSaveAllowed = EFalse"));
        #endif 
        return ETrue;
        }
    #endif

    // Check if this MIME type is listed as an exception which is never saved to MMC
    // card.
    CreateDocResourceReaderLC(reader, R_DOCUMENT_HANDLER_EXCEPTION_TYPES_LIST);
    exArr = reader.ReadDesCArrayL();    
    if (exArr)
        {
        TInt posTmp;
        if (exArr->Find(iDataType.Des(), posTmp) == 0)
            {
            retval = ETrue;
            }
        delete exArr;   
        }
    CleanupStack::PopAndDestroy(); // reader
    return retval;
	}
#endif

#ifdef RD_MULTIPLE_DRIVE 
// ---------------------------------------------------------
// CDocDefaultHandler::GetSystemDrivesCount()
// This should not be called when RD_MULTIPLE_DRIVE flag is diabled
// ---------------------------------------------------------
// 
TInt CDocDefaultHandler::GetAvailableDrivesCountL()
	{
	TDriveList driveList;
	TInt driveCount;
	User::LeaveIfError(
			DriveInfo::GetUserVisibleDrives(
				iFs,
	            driveList,
	            driveCount ) );
	
	TInt driveListLen(driveList.Length());
	TDriveNumber driveNumber;
	driveCount=0;
	TInt defaultPhoneMem( KErrNotFound );
    DriveInfo::GetDefaultDrive( DriveInfo::EDefaultPhoneMemory, defaultPhoneMem );

	for( TInt i( 0 ); i < driveListLen; ++i )
		{
	    if ( driveList[ i ] ) // Non zero items are valid drives
	    	{
	    	driveNumber=TDriveNumber(i);
	    	if( defaultPhoneMem == driveNumber)
	    		driveCount++;
	    	else if(IsDriveAvailableL(driveNumber))
	    		driveCount++;
	       	}
	    }
	return driveCount;
	}
#endif

#ifdef RD_MULTIPLE_DRIVE 
// ---------------------------------------------------------
// CDocDefaultHandler::IsDriveAvailable( const TDriveNumber & aDriveNumber)
// check drive availability ie is it available for user read/write operations
// This should not be called when RD_MULTIPLE_DRIVE flag is diabled
// ---------------------------------------------------------
// 
TBool CDocDefaultHandler::IsDriveAvailableL(const TInt & aDriveNumber)
	{

	 TInt error;
	 TUint status=0;
	 TDriveInfo driveInfo;
	 TVolumeInfo volumeInfo;
	 error = DriveInfo::GetDriveStatus( iFs, aDriveNumber, status );
	 if( error )
		 {
	     return EFalse;
	     }
	 TFullName fsName;
	 error = iFs.FileSystemName( fsName, aDriveNumber );
	 if(error)
		 {
		 return EFalse;
		 }
	 // if not mounted, try to mount it.
	 if( fsName.Length() == 0 )
		 {
		 error = iFs.MountFileSystem( KFSName,aDriveNumber );
		 switch( error )
		 	{
	        case KErrNone:
	        case KErrLocked:
	        	{
	        	break;
	        	}
	        default:
		        {
		        return EFalse;
		        }
		    }
	     }
	 error = iFs.Drive( driveInfo, aDriveNumber );
    if( error && ( error != KErrLocked ) )
		 {
	     return EFalse;
	     }
	 error = iFs.Volume( volumeInfo, aDriveNumber );
    if( error && ( error != KErrLocked  ) ) // if memory card locked, don't return false
		 {
	     return EFalse;
		 }
	 if( driveInfo.iDriveAtt & KDriveAttRemote )
		 {
		 /*TChar driveLetter;
		 iFs.DriveToChar( aDriveNumber, driveLetter );
		 //This statement migth cause leave.. to be solve
         CRsfwMountMan* mountMgr = CRsfwMountMan::NewL( 0, NULL );
         CleanupStack::PushL( mountMgr );
		 TRsfwMountInfo mountInfo;
		 error = mountMgr->GetMountInfo( driveLetter, mountInfo );
		 CleanupStack::PopAndDestroy( mountMgr );
		 if( error )
			 {
		 	 return EFalse;
			 }*/
		 /* Always return EFlase for Remote drives*/
		 return EFalse;
		 }
	 return ETrue;
	}
#endif
// ---------------------------------------------------------
// CDocDefaultHandler::GetDataDirL( 
// Get the data directory for the mime type. Directory is
// saved finally to aPath.
// ---------------------------------------------------------
//        
TInt CDocDefaultHandler::GetDataDirL( 
    const TDataType& aDataType, 
    const TUid& /*aUid*/, 
    TDes& aPath,
    TInt aDataSize)
    {    
    TFileName path;                     // The path
    TFileName folder;
    
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::GetDataDirL : Enter "));
    #endif 
    
    if ( DocOperation() == EDocSaveTemp )
        {
        User::LeaveIfError( SetTemporaryPathL( aDataSize, path, ETrue ) );
        
        // DocumentHandler will take care deleting this file
        iSavedAsTemp = ETrue;
        }
    else if ( !IsViewerOperation( DocOperation() ) )
        {
        if (DocOperation() == EDocSilentMove)
            {
            TParsePtrC parse(iRootPath);
            // If we try to save to MMC, let's check that it is allowed.
            if( parse.Drive().CompareF( PathInfo::MemoryCardRootPath().Left(2) ) == 0 )
                {
                if ( !CanBeSavedToMmcL() )
                    {
                    #ifdef _DEBUG        
                    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::GetDataDir: Return ERROR, we are not allowed to save to MMC."));
                    #endif 
                    return KErrCancel;
                    }
                }
            path.Copy( iRootPath );
            }
        else 
            {
            path.Copy( PathInfo::PhoneMemoryRootPath() );
            }

		if ( iUid.iUid == 0 ) // Data type not supported
			{
			folder.Copy( PathInfo::OthersPath() );
            }	
		else // Data type supported
			{						
			iMediaGalleryData = GetDefaultFolderForDataTypeL( aDataType, folder );       		
        	if ( !iMediaGalleryData ) // Non-gallery files
            	{                                    	
            	if ( IsInstallerData() ) // Installable files.
                	{
                	folder.Copy( PathInfo::InstallsPath() );
                	}
            	else              		// Other supported non-gallery files.
                	{
                	folder.Copy( PathInfo::OthersPath() );                    	
               	 	}
            	}
            }
        }
    else
        {
        // do nothing
        }

    if ( DocOperation() != EDocSaveTemp )
        {
        if (( folder.Length() == 0 ) || ( path.Length() == 0 ))
            {
            User::LeaveIfError(SetTemporaryPathL(aDataSize, path, EFalse));

            // DocumentHandler will take care deleting this file
            iSavedAsTemp = ETrue;
            }        
        else
            {
            path.Append( folder );      
            }
        }
    
    TParsePtr parse( path );
    if ( parse.NamePresent() )                  // There is no '\' in the end.
        {
        path.Append( _L( "\\" ) );              // Append it. We need it!
        }

    aPath.Copy( path );
    return SetAndReturnStatus( KErrNone );
    }

// ---------------------------------------------------------
// CDocDefaultHandler::QueryRenameL()
// Ask from the user if he wants to rename aName
// ---------------------------------------------------------
//      
TBool CDocDefaultHandler::QueryRenameL( const TDesC& aName )
    {
    TParsePtrC parse( aName );

    return RunQueryDialogL( R_DOCHANDLER_RENAME_QUERY,
                            R_DOCUMENT_HANDLER_NAME_IN_USE_TEXT,
                            HideFileExtension() ? 
                            parse.Name(): 
                            parse.NameAndExt() );
    }

// ---------------------------------------------------------
// CDocDefaultHandler::QueryOverWriteL()
// Ask from the user if he wants to overwrite aName
// ---------------------------------------------------------
//      
TBool CDocDefaultHandler::QueryOverWriteL( const TDesC& aName )
    {
    TParsePtrC parse( aName );
    
    return RunQueryDialogL( R_DOCHANDLER_OVERWRITE_QUERY,
                            R_DOCUMENT_HANDLER_OVERWRITE_TEXT,
                            HideFileExtension() ? 
                            parse.Name(): 
                            parse.NameAndExt() );
    }

// ---------------------------------------------------------
// CDocDefaultHandler::QueryNewNameL()
// Ask a new name for aName from the user.
// ---------------------------------------------------------
//      
TBool CDocDefaultHandler::QueryNewNameL( TFileName& aName, const TInt aMaxLen )
    {
    TBool cancel( EFalse );
    TBool valid( EFalse );
    CApaApplication::GenerateFileName( iFs, aName );
    TParsePtr parse( aName );
    HBufC* extension = HBufC::NewLC( parse.Ext().Length() );
    extension->Des().Copy( parse.Ext() );
    TFileName name;

    do 
        {
        if ( HideFileExtension() )
            name.Copy( parse.Name() );
        else
            name.Copy( parse.NameAndExt() );
        TInt len = Min( KMaxFileName - KLengthOfFileExtension - parse.DriveAndPath().Length(), 
                        aMaxLen);
        if ( HideFileExtension() )
            {
            len -= extension->Des().Length();
            }
        if ( len <= 0 )
            User::Leave( KErrUnknown );

        if (name.Length() > len)
            {
            if ( HideFileExtension() )
                {
                name.SetLength( len );              
                }
            else
                {
                name.SetLength( len - extension->Des().Length() );
                name.Append( *extension );
                }
            }

        CAknTextQueryDialog* dlg = new( ELeave ) CAknTextQueryDialog( name );
        dlg->SetMaxLength( len );    
        if ( dlg->ExecuteLD( R_DOCHANDLER_NAME_QUERY_DIALOG ) ) 
            {          
            valid = iFs.IsValidName( name ) ;
            if ( !valid )
                {
                CAknNoteDialog* note = new (ELeave) CAknNoteDialog(CAknNoteDialog::ENoTone, CAknNoteDialog::ELongTimeout);
                HBufC* noteText = NULL;
                noteText = StringLoader::LoadLC( R_DOCUMENT_HANDLER_ILLEGAL_CHARACTERS );
                note->PrepareLC( R_DOCUMENT_HANDLER_INFO_NOTE );
                note->SetTextPluralityL(EFalse);
                note->SetTextL( *noteText );
                note->RunLD();
                CleanupStack::PopAndDestroy(noteText);
                cancel = EFalse;
                }
            else
                {
                aName.Copy( parse.DriveAndPath() );
                aName.Append( name );  
                if ( HideFileExtension() )
                    aName.Append( extension->Des() );        
                cancel = EFalse;        
                }
            }
        else
            {
            cancel = ETrue;
            }    
        }
        while ( !valid && !cancel );
    CleanupStack::PopAndDestroy(); // extension
    return !cancel;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::GenerateTempFileNameL()
// Creates a new name (based on existing name) without asking anything from user.
// ---------------------------------------------------------
//      
void CDocDefaultHandler::GenerateTempFileNameL( TFileName& aName, const TInt aMaxLen )
    {
    TBool valid( EFalse );
    CApaApplication::GenerateFileName( iFs, aName );
    TParsePtr parse( aName );
    HBufC* extension = HBufC::NewLC( parse.Ext().Length() );
    extension->Des().Copy( parse.Ext() );
    TFileName name;

    if ( HideFileExtension() )
        name.Copy( parse.Name() );
    else
        name.Copy( parse.NameAndExt() );
        
    TInt len = Min( KMaxFileName - KLengthOfFileExtension - parse.DriveAndPath().Length(), aMaxLen);
    if ( HideFileExtension() )
        {
        len -= extension->Des().Length();
        }
    if ( len <= 0 )
        User::Leave( KErrUnknown );

    if (name.Length() > len)
        {
        if ( HideFileExtension() )
            {
            name.SetLength( len );              
            }
        else
            {
            name.SetLength( len - extension->Des().Length() );
            name.Append( *extension );
            }
        }
      
    valid = iFs.IsValidName( name ) ;
        
    if ( !valid )
        {
        User::Leave( KErrUnknown );
        }
    else
        {
        aName.Copy( parse.DriveAndPath() );
        aName.Append( name );  
        if ( HideFileExtension() )
            aName.Append( extension->Des() );           
        }

    CleanupStack::PopAndDestroy(); // extension
    }

// ---------------------------------------------------------
// TCDocDefaultHandler::SaveAsQueryL()
// Run "save as" dialog chain.
// ---------------------------------------------------------
//      
TDocSaveAsResult CDocDefaultHandler::SaveAsQueryL( TFileName& aPath )
    {    
    AddResourcesL();
    TDocSaveAsResult response = EDocFileCancelWrite;   

    TParsePtr parse( aPath );
    
    if ( IsFileWritableL( aPath ) )         // If the file is writable.
        {                                   // If the user wants to overwrite.
        if ( QueryOverWriteL( parse.NameAndExt() ) )
            {
            response = EDocFileOverWrite;   // Overwrite, please.
            }
        else
            {
            response = EDocFileRenameNew;   // Rename please.
            }
        }
    else                                    // If the file is not writable.
        {                                   // Ask if the user wants to rename.
        if ( QueryRenameL( parse.NameAndExt() ) )
            {
            response = EDocFileRenameNew;   // Rename, please.
            }
        else
            {
            response = EDocFileCancelWrite; // User cancelled.
            }
        }
    if ( response == EDocFileRenameNew )    // Ask the user to rename the file.
        {
        if ( !QueryNewNameL( aPath, MaxNameLen() ) )      // Run rename dialog.
            {
            response = EDocFileCancelWrite; // User cancelled.           
            }
        }       
    RemoveResources();
    return response;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::RunQueryDialogL()
// Run CAknQueryDialog with given resources. 
// ---------------------------------------------------------
//         
TInt CDocDefaultHandler::RunQueryDialogL(
    TInt aDialogTypeResID,
    TInt aStringResID,
    const TDesC& aFileName )
    {
    TInt response;
    HBufC* promptPtr = NULL;
    promptPtr = StringLoader::LoadL( aStringResID, aFileName );
    CleanupStack::PushL( promptPtr );
    TPtrC prompt( promptPtr->Des() );
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( );
    dlg->SetPromptL(prompt);
    dlg->PrepareLC(aDialogTypeResID);    
    response = dlg->RunLD();
    CleanupStack::PopAndDestroy(); // promptPtr
    return response;
    }
    
// ---------------------------------------------------------
// CDocDefaultHandler::GenerateFileNameL()
// Try to generate a file name.
// 1. Try to find the handler app's default document name.
// 2. If failed, try to load DocHandler's document name. ("unnamed")
// 3. If still failed, use a hardcoded name
// ---------------------------------------------------------
//           
TInt CDocDefaultHandler::GenerateFileNameL( 
    const TUid& aUid, 
    TDes& aFileName, 
    const TDataType& aDataType,
    TInt aDataSize)
    {
    #ifdef _DEBUG        
    TPtrC mimetype = aDataType.Des();        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::GenerateFileNameL( %x, %S, %S ) Called"), aUid.iUid, &aFileName, &mimetype);
    #endif 

    TFileName path;
    TParsePtr parse( aFileName );

    if ( parse.NamePresent() )
        {
            aFileName.Copy( parse.NameAndExt() );
        }
    else
        {
        TFileName resFileName;        

        // Find an application's resource file
        if ( iAppInfo.iFullName.Length() > 0 )
            {                                       
            TParsePtr appParse( iAppInfo.iFullName );
            resFileName.Copy( resourceaApps );       //"\resource\apps\" 
            resFileName.Append( appParse.Name() );   //"\resource\apps\ap"
            resFileName.Append( resExt );            //"\resource\apps\ap.rsc"
            
            CStringResourceReader* reader = NULL;
            TRAPD( 
                error, 
                ( reader = CStringResourceReader::NewL( resFileName ) ) );
            if ( error == KErrNone )
                {
                CleanupStack::PushL( reader );       // This is needed, it can leave!
                aFileName = reader->ReadResourceString( EDefaultNameResourceOffset );
                CleanupStack::PopAndDestroy();       // reader
                }
            } 

        // Use the docHandler's (fall back) doc name            
        if ( aFileName == errorStr || aFileName.Length() == 0 ) 
            {                                                   
            resFileName.Copy( KDocResourceFileName );
            CStringResourceReader* reader = NULL;
            TRAPD( 
                error, 
                ( reader = CStringResourceReader::NewL( resFileName ) ) );
            if ( error == KErrNone )
                {
                __ASSERT_DEBUG (
                    reader,
                    User::Panic( _L( "DocDefaultHandler" ), KErrNoMemory ) );
                CleanupStack::PushL( reader );      // This is needed, it can leave!
                aFileName = reader->ReadResourceString( EDefaultNameResourceOffset );
                CleanupStack::PopAndDestroy();      // reader
                }
            }
        
        if ( aFileName == errorStr || aFileName.Length() == 0 )
            {
            #ifdef _DEBUG        
            User::Panic( _L( "DocumentHandler: CDocDefaultHandler::GenerateFileNameL: resource problem" ), KErrUnknown );
            #endif 
            aFileName.Copy( KDocFallBackName );
            }
        }

    CheckFileNameExtensionL( aFileName, aDataType );
    if (GetDataDirL( iDataType, aUid, path, aDataSize ) == KErrCancel)
        {
        return KErrCancel;  
        }
    aFileName.Insert( 0, path );
    
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::GenerateFileNameL exit, aFileName=\"%S\""), &aFileName);
    #endif 

    return KErrNone;
    }
    
// ---------------------------------------------------------
// CDocDefaultHandler::CheckDiskspaceL()
// Always leave if no space left on flash
// ---------------------------------------------------------
//      
void CDocDefaultHandler::CheckDiskspaceL( TInt aBytes )
    {
    // If MoveL command used, we do not need any more space because
    // Symbian API renames the file -> we can skip this check
    if (DocOperation() == EDocMove || DocOperation() == EDocSilentMove)
        {
        return;
        }

    if (iDestFile.FindF( PathInfo::PhoneMemoryRootPath() ) != KErrNotFound)
        {
        #ifdef _DEBUG        
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CheckDiskspaceL: Disk Space checked"));
        #endif 
        if ( SysUtil::FFSSpaceBelowCriticalLevelL( &iFs, aBytes ) )
            {
            #ifdef _DEBUG        
            RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CheckDiskspaceL: Leave with KErrDiskFull"));
            #endif 
            User::Leave( KErrDiskFull );
            }
        }
    }

// ---------------------------------------------------------
// CDocDefaultHandler::ReplaceExtension()
// Replace current extension at aName with extension given (eExt).
// ---------------------------------------------------------
//      
void CDocDefaultHandler::ReplaceExtension( TDes& aName, const TDesC& aExt )
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::ReplaceExtension: Enter, aName =%S, aExt=%S"),&aName, &aExt);
    #endif 
    
    TInt dotPos = aName.LocateReverse( '.' );
    if ( dotPos != KErrNotFound )
       {
       aName.Delete( dotPos, aName.Length()- dotPos );
       }
    aName.Append( aExt );
    }

// ---------------------------------------------------------
// CDocDefaultHandler::AddRecourcesL()
// Calls CDocResourceFile::AddLC()
// ---------------------------------------------------------
//      
void CDocDefaultHandler::AddResourcesL()
    {
    CDocResourceFile::AddLC( KDocResourceFileName, iFs );
    }

// ---------------------------------------------------------
// CDocDefaultHandler::RemoveRecources()
// Calls CDocResourceFile::Remove()
// ---------------------------------------------------------
//  
void CDocDefaultHandler::RemoveResources()
    {
    CDocResourceFile::Remove();
    }

// ---------------------------------------------------------
// CDocDefaultHandler::CheckFileNameExtensionL()
// We should not have to do this. But some recognizers
// don't work as expected and for example browser may suggest wrong file
// extensions (such as .asp). 
// ---------------------------------------------------------
//       
void CDocDefaultHandler::CheckFileNameExtensionL(
    TDes &aFileName,
    const TDataType& aDataType )
    {
    #ifdef _DEBUG        
    TPtrC mimetype = aDataType.Des();        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CheckFileNameExtensionL: Enter, aFileName =%S, aDataType =%S"), &aFileName, &mimetype);
    #endif 
    
    // Jad files should always have jad extension even proctected.
    if ( aDataType.Des().FindF( KDocMimeJad ) != KErrNotFound )
    	{
    	// change extension to .jad
    	TBuf<6> ext;
        ext.Copy( KDocExtJad );         
        ReplaceExtension( aFileName, ext );                    
        return;            
    	}
    	
    // If we have iSourceFile available, we check first that is file DCF file. 
    // If it is, then we will use dcf file extensions, which override all other extensions.
    if (iSourceFile.Length() > 0)
        {
        TInt ret = EFalse;
        TBuf<6> ext;

		CContent* content = NULL;
        TRAPD(err,content = CContent::NewL( iSourceFile ));

		if(err == KErrNone)
			{	
			CleanupStack::PushL(content);
			content->GetAttribute( ContentAccess::EIsProtected, ret  );
			if ( ret )
				{
				content->GetAttribute( EFileType, ret );
            
				#ifdef _DEBUG             
				RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CheckFileNameExtensionL: GetAttribute called, ret =%d"), ret);
				#endif 
    
				if ( ret == EOma1Dcf )
					{
					// change extension to .dcf
					ext.Copy( KOma1DcfExtension );         
					ReplaceExtension( aFileName, ext );            
					CleanupStack::PopAndDestroy();  // content
					return;            
					}
				else if ( ret == EOma2Dcf )
	                {
		            // change extension to .odf if not already .o4a, .o4v or .odf
			        ext.Copy( KOma2DcfExtension );
				    if ( NeedsToReplaceDcf2Extension( aFileName ) )
					    {
						ReplaceExtension( aFileName, ext );
	                    }
		            CleanupStack::PopAndDestroy();  // content
			        return;            
				    }
				}
			CleanupStack::PopAndDestroy();  // content
			}
        }

    //if mime type=oma 2 dcf check extension separately
    if ( aDataType.Des8().FindF( KOma2DcfContentType ) != KErrNotFound )
        {
        if ( NeedsToReplaceDcf2Extension( aFileName ) )
            {
            ReplaceExtension( aFileName, KOma2DcfExtension() );
            }
        }
    else
        {
        if (!iMimeExtensions)
            {
            TResourceReader reader; 

            CreateDocResourceReaderLC(reader, R_EXTENSION_GUARANTEED_MIME_TYPES);
            iMimeExtensions = reader.ReadDesCArrayL();  
            CleanupStack::PopAndDestroy();  // reader

            CreateDocResourceReaderLC(reader, R_EXTENSION_GUARANTEED_EXTENSIONS);
            iExtensions = reader.ReadDesCArrayL();  
            CleanupStack::PopAndDestroy();  // reader
            }   

        TInt position;
        TFileName mimeType;
        mimeType.Copy(aDataType.Des8());
        if (!iMimeExtensions->Find(mimeType, position))
            {
        #ifdef _DEBUG             
            RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CheckFileNameExtensionL: Founded from mapping table."));
        #endif 
            TBuf<6> ext = iExtensions->MdcaPoint( position );
            ext.Insert(0, _L("."));
            ReplaceExtension( aFileName, ext );
            }
        }
    #ifdef _DEBUG             
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::CheckFileNameExtensionL: Finished"));
    #endif          
    }

// ---------------------------------------------------------
// CDocDefaultHandler::IsFileInUse()
// Try to open file for writing. If it fails return EFalse. 
// If it succeeds close the file and return ETrue?
// ---------------------------------------------------------
//       
TBool CDocDefaultHandler::IsFileInUse( const TDesC& aFileName )
    {
    RFile file;
    TInt error;
    TBool retValue = EFalse;
    error = file.Open( iFs, aFileName, EFileWrite );
    if ( error == KErrInUse || error == KErrLocked )
        {
        retValue = ETrue;
        }
    file.Close();
    return retValue;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::IsFileWritableL()
// check if the file is read only or in use.
// ---------------------------------------------------------
//       
TBool CDocDefaultHandler::IsFileWritableL( const TDesC& aFileName )
    {
    TEntry fileEntry;    
    TInt error = iFs.Entry( aFileName, fileEntry );
    if ( error != KErrNone && error != KErrBadName )
        {
        User::Leave( error );
        }
    
    if ( fileEntry.IsReadOnly() || IsFileInUse( aFileName ) ) 
        {
        return EFalse;
        }
    else
        {
        return ETrue;
        }
    }

// ---------------------------------------------------------
// CDocDefaultHandler::SetAndReturnStatus()
// Set iStatus.
// ---------------------------------------------------------
//       
TInt CDocDefaultHandler::SetAndReturnStatus( TInt aErrorCode )
    {
    if (aErrorCode == KErrCancel)
        {
        iStatus = KErrNone;
        }
    else
        {
        iStatus = aErrorCode;
        }
    return iStatus;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::DocOperation() const
// Return iOperation.
// ---------------------------------------------------------
//       
TDocOperation CDocDefaultHandler::DocOperation() const
    {
    return iDocDispatcher->DocOperation();
    }
    
// ---------------------------------------------------------
// CDocDefaultHandler::PopulateAppInfo()
// Construct iAppInfo with iUid.
// ---------------------------------------------------------
//       
void CDocDefaultHandler::PopulateAppInfo()
    {
    PopulateAppInfo( iUid );    
    }
    
// ---------------------------------------------------------
// CDocDefaultHandler::PopulateAppInfo()
// Construct iAppInfo.
// ---------------------------------------------------------
//      
void CDocDefaultHandler::PopulateAppInfo( const TUid& aUid )
    {
    TInt error = iApaLs->GetAppInfo( iAppInfo, aUid );    
    if ( error != KErrNone )
        {
        // TODO: What happends if GetAppInfo fails?
        }
    }
    
// ---------------------------------------------------------
// CDocDefaultHandler::MaxNameLen()
// Return max lenght of file name.
// ---------------------------------------------------------
//      
TInt CDocDefaultHandler::MaxNameLen()
    {
    return KMaxFileName;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::ReverseSlashes()
// Reverses slashes at aString ('/' -> '\').
// ---------------------------------------------------------
//      
void CDocDefaultHandler::ReverseSlashes(TDes& aString)
    {
    TInt findPos = aString.Locate('/');
    while (findPos != KErrNotFound)
        {
        aString.Replace(findPos, 1, _L("\\"));
        findPos = aString.Locate('/');
        }
    }

// ---------------------------------------------------------
// CDocDefaultHandler::IsParameterAlreadyInList()
// Check if given parameter is allready on iAiwParams.
// ---------------------------------------------------------
//    
TBool CDocDefaultHandler::IsParameterAlreadyInList(TGenericParamId aId)
    {
    if ( iAiwParams )
        {
        TInt index = 0;
        iAiwParams->FindFirst(index, aId);
        if (index!=KErrNotFound)
            {
            return ETrue;
            }
        }
    return EFalse;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::WaitNoteTextL
// Resolve wait note text.
// ---------------------------------------------------------
// 
void CDocDefaultHandler::WaitNoteTextL( TPtr& aTextPtr )
    {
    AddResourcesL();
    HBufC* text;
	if(IsInstallerData())
       	{
       	text = StringLoader::LoadLC( R_DOCUMENT_HANDLER_SAVING_INSTALLS_DIRECTORY );
       	}
    else if( iUid.iUid == 0 || !iMediaGalleryData )//KWmlcHandler == iUid.iUid ) 
        {
        text = StringLoader::LoadLC( R_DOCUMENT_HANDLER_SAVING_OTHERS_DIRECTORY );
        }
    else
        {
        TApaAppCaption caption;
        ResolveCaptionName( caption );
        text = StringLoader::LoadLC( R_DOCUMENT_HANDLER_SAVING_FILE_TO, caption );
        }
    aTextPtr.Copy( text->Des() );
    CleanupStack::PopAndDestroy(); // text
    RemoveResources();
    }
    
// ---------------------------------------------------------
// CDocDefaultHandler::ConfirmationNoteTextL
// Resolve confirmation note text.
// ---------------------------------------------------------
// 
void CDocDefaultHandler::ConfirmationNoteTextL( TPtr& aTextPtr  )
    {
    AddResourcesL();
    HBufC* text;
    TBuf<100> mime16;
    mime16.Copy( iDataType.Des() );
    
	if(IsInstallerData())
    	{
    	text = StringLoader::LoadLC( R_DOCUMENT_HANDLER_SAVED_INSTALLS_DIRECTORY );
    	}
    else if( mime16.FindF(KMIMETypeSvg) != KErrNotFound 
           || iUid.iUid == 0 || !iMediaGalleryData ) // Data type not supported.
        {
        text = StringLoader::LoadLC( R_DOCUMENT_HANDLER_SAVED_OTHERS_DIRECTORY );
        }
    else
        {
        TApaAppCaption caption;
        ResolveCaptionName( caption );
        text = StringLoader::LoadLC( R_DOCUMENT_HANDLER_FILE_SAVED_TO, caption );
        }
    aTextPtr.Copy( text->Des() );
    CleanupStack::PopAndDestroy(); // text
    RemoveResources();
    }


// ---------------------------------------------------------
// CDocDefaultHandler::ResolveCaptionName
// Resolve confirmation note text.
// ---------------------------------------------------------
// 
void CDocDefaultHandler::ResolveCaptionName( TApaAppCaption& aCaption )
    {
    if ( iMediaGalleryData || IsInstallerData() )
        {
        TBuf<100> mime16;
        mime16.Copy( iDataType.Des() );
        // Get app info for media gallery app or app manager.
        TApaAppInfo appInfo;
        TUid uid;
        if( mime16.FindF( KMIMETypeImage ) != KErrNotFound )
            {    	
            uid = KPhotosUID3;
            }
        else if ( mime16.FindF(KMIMETypeVideo)!= KErrNotFound 
            || mime16.FindF(KMIMETypeVideoReal)!= KErrNotFound 
            || mime16.FindF(KMIMETypeVideoSdp)!= KErrNotFound )
            {
            uid = KVideoCenterAppUid;
            } 
        else if( mime16.FindF(KMIMETypeAudioMpeg)!= KErrNotFound 
            || mime16.FindF(KMIMETypeAudioMp4)!= KErrNotFound )
            {
            uid = KMusicPlayerAppUid;
            }
        else if(mime16.FindF(KMIMETypeAudio)!= KErrNotFound )
            {
            uid = KFileManagerUID3;
            }
        else
            {
            uid = KAppManagerUID3;
            }
        TInt error = iApaLs->GetAppInfo( appInfo, uid );
        if ( error == KErrNone )
            {
            aCaption = appInfo.iCaption;
            }
        }
    else
        {
        aCaption = iAppInfo.iCaption;
        }          
    }
// ---------------------------------------------------------
// CDocDefaultHandler::GetDefaultFolderForDataTypeL()
// Get folder for given datatype. This info is get from
// documenthandlerui.rss file.
// ---------------------------------------------------------
// 
TBool CDocDefaultHandler::GetDefaultFolderForDataTypeL(const TDataType& aDataType, TDes& result)
    {
    #ifdef _DEBUG        
    TPtrC mimetype = aDataType.Des();        
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::GetDefaultFolderForDataTypeL: Enter, aDataType =%S"), &mimetype);
    #endif 
    
    TResourceReader resReader;
    CreateDocResourceReaderLC(resReader, R_DOCHANDLER_DEFAULT_PATH_ARRAY);

    TBuf<100> mime16;
    mime16.Copy( aDataType.Des() );

    result.Zero();

    TInt count = resReader.ReadInt16();

    TBool found = EFalse;   
    for (TInt i = 0; i < count; i++)
        {
        HBufC* mimetype = resReader.ReadHBufCL();
        CleanupStack::PushL( mimetype );        
        HBufC* path = resReader.ReadHBufCL();
        CleanupStack::PushL( path );        

        if (mime16.FindF( *mimetype ) != KErrNotFound)
            {
            result.Copy( path->Des() );
            found = ETrue;
            }

        CleanupStack::PopAndDestroy( 2 );  // mimetype, path

        if (found)
            {
            break;
            }
        }

    CleanupStack::PopAndDestroy(); // resReader

    #ifdef _DEBUG             
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::GetDefaultFolderForDataTypeL: Finished, returns =%d"), found);
    #endif 

    return found;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::IsInstallerData()
// Check if application installer is handler application.
// ---------------------------------------------------------
// 
TBool CDocDefaultHandler::IsInstallerData() const
    {
    TUid uid;
    HandlerAppUid(uid);
    if (uid.iUid == KAppInstHandler)
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }  
    }

// ---------------------------------------------------------
// CDocDefaultHandler::SetTemporaryPathL()
// Set temporary path to aPath. First choice to temporary 
// place is 
// -if we prefer private folder (aPrivate = ETrue) -> d:\[process_private_directory] 
// -if not any need where to save -> d:\system\temp, 
// Second choice is to save to c:\system\temp.
// ---------------------------------------------------------
// 
TInt CDocDefaultHandler::SetTemporaryPathL(TInt aDataSize, TDes& aPath, TBool aPrivate)
    {    
    #ifdef _DEBUG           
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::SetTemporaryPathL: Enter"));
    #endif 
    
    //TDriveUnit unit(KDocDDriveRoot);
    TDriveUnit unit(EDriveD);
    TInt drive( unit );
    TVolumeInfo volumeInfo;
    TInt error(iFs.Volume(volumeInfo, drive));

    if (error == KErrNone)
        {
        if (volumeInfo.iFree >= aDataSize)
            {
            if (aPrivate)
                {
                // Get process privatepath     
                User::LeaveIfError( iFs.PrivatePath(aPath) );
                    
                // Add used memory to beginning 
                aPath.Insert(0,unit.Name());
                }
            else
                {
               	// Set temp to drive D.
                aPath.Insert(0,KDocTempPath);
                aPath.Insert(0,unit.Name());
                }      
            return KErrNone;
            }
        }  

    // Not enough space in drive D, try drive C instead
    if ( SysUtil::FFSSpaceBelowCriticalLevelL( &iFs, aDataSize ) )
        {
        return KErrDiskFull;
        }

    // Set temp to drive C
    aPath.Copy(KDocTempPath2);

    return KErrNone;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::UpdateMediaGalleryIfNeededL()
// Calls MediaGallery Update method so that media gallery
// knows update its view.
// ---------------------------------------------------------
// 
void CDocDefaultHandler::UpdateMediaGalleryIfNeededL()
    {
    if (!iSavedAsTemp)
        {  
        #ifdef _DEBUG        
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::UpdateMediaGalleryIfNeededL: aFileName=\"%S\""), &iDestFile);
        #endif 
#ifdef RD_CONTENTNOTIFICATION            
        CContentNotification* notifier = CContentNotification::NewL();
        CleanupStack::PushL( notifier );        
        CContentNotificationEvent* event = CContentCreatedEvent::NewL( iDestFile );                    
        CleanupStack::PushL( event );               
        CArrayFixFlat<CContentNotificationEvent*>* eventArray;
        eventArray = new CArrayFixFlat<CContentNotificationEvent*>(2);    	        	        
        CleanupStack::PushL( eventArray );        
        eventArray->AppendL( event );        
        User::LeaveIfError( notifier->SendNotification( eventArray->Array() ) );
        eventArray->Delete( 0 );
        CleanupStack::PopAndDestroy( 3 ); // eventArray, event, notifier.
#endif        
        }
    }

// ---------------------------------------------------------
// CDocDefaultHandler::UpdateDCFRepositoryL()
// Update saved file to DCFRepository  
// ---------------------------------------------------------
// 
void CDocDefaultHandler::UpdateDCFRepositoryL()
    {
#ifdef ENABLE_DRM
    CDcfEntry* dcf = NULL;
    dcf = CDcfEntry::NewL();    
    CleanupStack::PushL( dcf );
    
    CDcfRep* dcfRep = NULL;
    dcfRep = CDcfRep::NewL();
    CleanupStack::PushL( dcfRep );
    
    dcf->SetLocationL( iDestFile, 0 );    
    dcfRep->UpdateL( dcf );
    
    CleanupStack::PopAndDestroy(2); // dcf, dcfRep
#endif
    }


// ---------------------------------------------------------
// CDocDefaultHandler::HandlerAppUid()
// Returns handler application Uid.
// ---------------------------------------------------------
// 
void CDocDefaultHandler::HandlerAppUid(TUid& aUid) const
    {
    aUid = iUid;
    }
    
// ---------------------------------------------------------
// CDocDefaultHandler::DeleteFile()
// Utility method: Delete file given in parameter if possible.
// ---------------------------------------------------------
//       
void CDocDefaultHandler::DeleteFile(const TDesC& aFileName)
    {
    #ifdef _DEBUG  
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::DeleteFile: Trying to delete file %S "), &aFileName );
    #endif   
    
    // Delete file, don't care about possible errors
    TInt error = iFileManager->Delete( aFileName, 0 );
    
    if ( error == KErrNone ) 
        {      
        #ifdef _DEBUG        
        RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::DeleteFile: Deleting succesful!"));
        #endif      
        }
    }

// ---------------------------------------------------------
// CDocDefaultHandler::IsMMCSaveAllowedL()
// Check if we are allowed to save MMC DRM content. Result
// is saved to iMMCSaveAllowed member variable.
// ---------------------------------------------------------
//
void CDocDefaultHandler::IsMMCSaveAllowedL(const TDesC& aSourceFile)
    {
#ifndef __KEEP_DRM_CONTENT_ON_PHONE
    iMMCSaveAllowed = ETrue;
    (void)aSourceFile; // This is because of removing warning
#else
    iMMCSaveAllowed = EFalse;   // paranoia
    CDistributableChecker* distributableChecker = CDistributableChecker::NewL();
    CleanupStack::PushL( distributableChecker );
    TBool isProtected( ETrue );
    TInt err(KErrNone);

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::IsMMCSaveAllowedL : (KEEP_DRM) Filename version. Created CDistributableChecker.") );
    #endif

    err = distributableChecker->Check( aSourceFile, isProtected );

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::IsMMCSaveAllowedL : (KEEP_DRM) isProtected =%d, err =%d."), isProtected, err);
    #endif

    if ( err == KErrNone && isProtected == EFalse )
        {
        iMMCSaveAllowed = ETrue;
        }

    CleanupStack::PopAndDestroy( distributableChecker );
#endif // __KEEP_DRM_CONTENT_ON_PHONE
    }

// ---------------------------------------------------------
// CDocDefaultHandler::IsMMCSaveAllowedL()
// Check if we are allowed to save MMC DRM content. Result
// is saved to iMMCSaveAllowed member variable.
// ---------------------------------------------------------
//
void CDocDefaultHandler::IsMMCSaveAllowedL(const RFile& aSourceFile)
    {


#ifndef __KEEP_DRM_CONTENT_ON_PHONE
    iMMCSaveAllowed = ETrue;
    (void)aSourceFile; // This is because of removing warning
#else
    iMMCSaveAllowed = EFalse;   //paranoia
    CDistributableChecker* distributableChecker = CDistributableChecker::NewL();
    CleanupStack::PushL( distributableChecker );
    TBool isProtected( ETrue );
    TInt err(KErrNone);

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::IsMMCSaveAllowedL : (KEEP_DRM) Filehandle version. Created CDistributableChecker.") );
    #endif

    RFile& source = const_cast<RFile&>(aSourceFile);    // not nice, but needed to go between APIs
    err = distributableChecker->Check( source, isProtected );

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocDefaultHandler::IsMMCSaveAllowedL : (KEEP_DRM) isProtected =%d, err =%d."), isProtected, err);
    #endif

    if ( err == KErrNone && isProtected == EFalse )
        {
        iMMCSaveAllowed = ETrue;
        }

    CleanupStack::PopAndDestroy( distributableChecker );
#endif // __KEEP_DRM_CONTENT_ON_PHONE
    }

// ---------------------------------------------------------
// CDocDefaultHandler::CreateDocResourceReaderLC()
// Setup aReader (TResourceReader) for resource reading with 
// aResourceID. This method is because need to use DocumentHandler 
// services from server-side, where CCoeEnv is not available.
// ---------------------------------------------------------
//      
void CDocDefaultHandler::CreateDocResourceReaderLC(TResourceReader& aReader, TInt aResourceID)
    {  
    TFileName resourceFile(KDocResourceFileName);
    BaflUtils::NearestLanguageFile( iFs, resourceFile );
    
    RResourceFile rfile;
    rfile.OpenL( iFs, resourceFile ); 
    CleanupClosePushL(rfile);             

    HBufC8* buffer = rfile.AllocReadL( (KRIMask & aResourceID) );
    
    CleanupStack::PopAndDestroy();  // rfile
    CleanupStack::PushL(buffer);
        
    aReader.SetBuffer(buffer);
    }

// ---------------------------------------------------------
// CDocDefaultHandler::IsMMCLocked()
// Checks if Mmc card is currently locked.
// ---------------------------------------------------------
//  
TBool CDocDefaultHandler::IsMMCLocked()
    {
    TBool ret = EFalse;
   
    // Check if MMC mounted, mount if required
    TInt err = TryMountMMC();

    if( !err )
        {
        TDriveInfo driveInfo;    
        err = iFs.Drive( driveInfo, EDriveE );
        if( !err ) 
            {            
            if( driveInfo.iMediaAtt & KMediaAttLocked )
                {
                ret = ETrue;  
                }
            }
        }
        
    return ret;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::TryMountMMC()
// Mounts Mmc card.
// ---------------------------------------------------------
//      
TInt CDocDefaultHandler::TryMountMMC()
    {
    // Check if MMC mounted, mount if required

    TFullName fsname;
    
    // If can't use the drive, returns KErrNotFound
    TInt err = iFs.FileSystemName( fsname, EDriveE );

    if ( !err )
        {
        // MMC found. Checking if it is mounted
        if ( fsname.Length( ) == 0 )
            {
            // Returns KErrLocked, if card locked and password not in store
            err = iFs.MountFileSystem( KFSName, EDriveE );                        
            }
        }
    return err;
    }    
//  End of File  
