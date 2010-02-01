/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of CDocumentHandler class.
*
*/


// INCLUDE FILES

#include "DocumentHandler.h"        // Class Declaration
#include "DocConstants.h"

// All special handlers and the default handler
#include "DocDefaultHandler.h"
#include "DocImageHandler.h"
#include "DocGameHandler.h"
#include "DocAppInstHandler.h"
//#include "DocMidletHandler.h"

#ifdef ENABLE_DRM
#include "DocDCFHandler.h"
#include <Oma2Agent.h>
#endif // ENABLE_DRM

#include <AiwGenericParam.h>

#include <featmgr.h>

#include <centralrepository.h>
#include <CommonUiInternalCRKeys.h>

#define LEAVEONERROR( error ) if( error != KUserCancel && error != KErrNone )\
                                   User::Leave( error )

const TInt KDocMaxCenRepBufLen = 1024;
const TInt KDocPDMaxMimeLen = 64;
const TInt KDocPDMaxUids = 24;
const TInt KDocPDMaxUidLen = 12;
const TInt KDocMaxDigitsInHexString = 8; // 32 bits.

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
// @since Series60 3.0
//
CDocumentHandler::CDocumentHandler()
    {
    }

// Two-phased constructor.
// @since Series60 3.0
EXPORT_C CDocumentHandler* CDocumentHandler::NewL( )
    {
    CDocumentHandler* self = NewLC( );
    CleanupStack::Pop();
    return self;
    }

// Two-phased constructor.
// @since Series60 3.0
EXPORT_C CDocumentHandler* CDocumentHandler::NewLC( )
    {
    CDocumentHandler* self = new( ELeave ) CDocumentHandler ( );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// EPOC default constructor can leave.
void CDocumentHandler::ConstructL()
    {
    iApaLs = new ( ELeave ) RApaLsSession;
    User::LeaveIfError(iApaLs->Connect());

    FeatureManager::InitializeLibL();

    iTempFileName.Zero();
    }

// Two-phased constructor.
EXPORT_C CDocumentHandler* CDocumentHandler::NewL( CEikProcess* /*aProcess*/ )
    {
    CDocumentHandler* self = NewLC( );
    CleanupStack::Pop();
    return self;
    }

// Two-phased constructor.
EXPORT_C CDocumentHandler* CDocumentHandler::NewLC( CEikProcess* /*aProcess*/ )
    {
    CDocumentHandler* self = new( ELeave ) CDocumentHandler (  );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// Destructor
EXPORT_C CDocumentHandler::~CDocumentHandler()
    {
    FeatureManager::UnInitializeLib();

    if ( iApaLs )
        {
        iApaLs->Close();
        delete iApaLs;
        }

    CloseSharableFS();

    // If we have temp file, we use iHandler services to delete this file
    if ( iTempFileName.Length() != 0 && iHandler )
        {
        iHandler->DeleteFile(iTempFileName);
        }

    delete iHandler;

    if ( iInParams )
        {
        delete iInParams;
        }

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler instance destructed succesfully!"));
    #endif
    }


// ---------------------------------------------------------
// RApaLsSession* CDocumentHandler::ApaLs()
// Returns Application list server object
// ---------------------------------------------------------
RApaLsSession* CDocumentHandler::ApaLs()
    {
    return iApaLs;
    }

// ---------------------------------------------------------
// CDocumentHandler::DocOperation()
// Returns CDocumentHandler::iOperation.
// ---------------------------------------------------------
TDocOperation CDocumentHandler::DocOperation() const
    {
    return iOperation;
    }

// ---------------------------------------------------------
// MApaEmbeddedDocObserver* CDocumentHandler::ExitObserver()
// Returns ExitObserver
// @since Series60 3.0
// ---------------------------------------------------------
MAknServerAppExitObserver* CDocumentHandler::ServerAppExitObserver() const
    {
    return iServerAppExitObserver;
    }

// ---------------------------------------------------------
// CDocumentHandler::SaveL
// Save content to the correct directory based on aDataType
// with a generated filename and attributes.
//
// This functions calls other SaveL version.
//
// Returns: KErrNone:           Everything went ok
//          KUserCancel:      The user cancelled the operation
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::SaveL(
    const TDesC8& aContent,     // Content buffer
    TDataType& aDataType,       // Mime type of the content
    const TUint aAttr )         // Save with these attributes
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::SaveL(aContent, aDataType, aAttr) Called"));
    TPtrC mimetype = aDataType.Des();
    RDebug::Print( _L("DocumentHandler: Parameters are: aDataType: %S "), &mimetype);
    #endif

    TFileName nullFileName;

    return SaveL(aContent, aDataType, nullFileName, aAttr);
    }

// ---------------------------------------------------------
// CDocumentHandler::SaveL
// Save content to the correct directory based on aDataType
// with aFileName and attributes.
//
// We first save wile with SaveTempFileL command.
// After that we use MoveL command.
//
// Returns: KErrNone:           Everything went ok
//          KUserCancel:      The user cancelled the operation
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::SaveL(
    const TDesC8& aContent,     // Content buffer
    TDataType& aDataType,       // Mime type of the content
    const TDesC& aName,         // Save with this name
    const TUint aAttr )         // Save with these attributes
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::SaveL(aContent, aDataType, aFileName, aAttr) Called"));
    TPtrC mimetype = aDataType.Des();
    RDebug::Print( _L("DocumentHandler: Parameters are: aDataType: %S -- aFileName: %S  "), &mimetype, &aName);
    #endif

    TUid uid = { 0 };
    TInt error;

    if (aDataType.Des8().FindF( KDummyMimeType ) != KErrNotFound)
        {
        return KErrNone;
        }

    TFileName tempFileName;

    iOperation = EDocSaveTemp; // First save temp file

    // Use Default Handler for saving whatever mimetype actually is
    delete iHandler;            // delete the old handler
    iHandler = NULL;
    iHandler = CDocDefaultHandler::NewL( aDataType,
                                             uid, this, EDocSaveOnly );

    error = iHandler->SetDestName( aName );     // Save with this file name

    // Close if existing sharable RFs and create new for sharing purposes.
    if ( error == KErrNone )
        {
        CloseSharableFS();
        User::LeaveIfError(iSharableFS.Connect());
        iSharableFS.ShareProtected();
        }

    if ( error == KErrNone )
        {
        error = iHandler->SaveTempFileL( aContent, KEntryAttNormal, tempFileName);
        }

    iOperation = EDocMove; // Move temp file to correct folder

    if ( error == KErrNone )
        {
        RecognizeAndCheckFileL( tempFileName, aDataType, uid );

        TRAP( error, FindHandlerL( aDataType, uid ) ); // allow unsupported.
        if ( error == KMimeNotSupported )
            {
            iHandler = CDocDefaultHandler::NewL( aDataType, uid, this, EDocSaveOnly );
            error = KErrNone;
            }
        else
            {
            User::LeaveIfError( error );
            }
        }

    if ( !iHandler->CanSave() )
        {
        User::Leave( KErrNotSupported );
        }

    if ( error == KErrNone )
        {
        error = iHandler->SetSrcFileName( tempFileName );
        }

    if ( error == KErrNone )
        {
        error = iHandler->SetDestName( aName );
        }

    // We use CopyOrMoveL-function, iOperation is checked there
    if ( error == KErrNone )
        {
        error = iHandler->CopyOrMoveL( aAttr );
        }

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::SaveL: finished with error=%d."), error);
    #endif

    LEAVEONERROR( error );

// Because DCF files are not tried to be recognized we return empty
// type here. Normally the return value has the type which was used
// when handler was selected.
#ifdef ENABLE_DRM
#ifdef __DRM_OMA2
    if ( aDataType.Des8().FindF( KOma1DcfContentType ) != KErrNotFound ||
         aDataType.Des8().FindF( KOma2DcfContentType ) != KErrNotFound )
#else // __DRM_OMA2
    if ( aDataType.Des8().FindF( KOma1DcfContentType ) != KErrNotFound )
#endif // __DRM_OMA2
        {
        TDataType emptyDataType;
        aDataType = emptyDataType;
        }
#endif // ENABLE_DRM

    return error;
    }

// ---------------------------------------------------------
// CDocumentHandler::CopyL
// Copy file to the correct directory based on it's mime type.
//
// Returns: KErrNone:           Everything went ok
//          KUserCancel:      The user cancelled the operation
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::CopyL(
    const TDesC& aFileNameOld,  // copy data from this file
    const TDesC& aFileNameNew,  // using this filename
    TDataType& aDataType,       // Mime type of data
    const TUint aAttr )         // use these attributes
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::CopyL(aFileNameOld, aFileNameNew, aDataType, aAttr) Called"));
    TPtrC mimetype = aDataType.Des();
    RDebug::Print( _L("DocumentHandler: Parameters are: aDataType: %S -- aFileNameOld: %S -- aFileNameNew: %S"), &mimetype, &aFileNameOld, &aFileNameNew);
    #endif

    TInt error = KErrNone;
    TUid uid = { 0 };

    if (aDataType.Des8().FindF( KDummyMimeType ) != KErrNotFound)
        {
        return KErrNone;
        }

    iOperation = EDocCopy;

    RecognizeAndCheckFileL( aFileNameOld, aDataType, uid );

    TRAP( error, FindHandlerL( aDataType, uid ) ); // allow unsupported.
    if ( error == KMimeNotSupported )
        {
        iHandler = CDocDefaultHandler::NewL( aDataType, uid, this, EDocSaveOnly );
        error = KErrNone;
        }
    else
        {
        User::LeaveIfError( error );
        }

    if ( !iHandler->CanSave() )
        {
        User::Leave( KErrNotSupported );
        }

    error = iHandler->SetSrcFileName( aFileNameOld );
    if ( error == KErrNone )
        {
        // If aFileNameNew is not set, use source file name
        if (aFileNameNew.Length() != 0)
            {
            error = iHandler->SetDestName( aFileNameNew );
            }
        else
            {
            error = iHandler->SetDestName( aFileNameOld );
            }
        }

    // We use CopyOrMoveL-function, iOperation is checked there
    if ( error == KErrNone )
        {
        error = iHandler->CopyOrMoveL( aAttr );
        }

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::CopyL: finished with error=%d."), error);
    #endif

    LEAVEONERROR( error );

    return error;
    }


// ---------------------------------------------------------
// CDocumentHandler::CopyL
// Copy file to the correct directory based on it's mime type.
//
// Returns: KErrNone:           Everything went ok
//          KUserCancel:      The user cancelled the operation
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::CopyL(
    const RFile& aFileOld,      // copy data from this file
    const TDesC& aFileNameNew,  // using this filename
    TDataType& aDataType,       // Mime type of data
    const TUint aAttr )         // use these attributes
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::CopyL(aFileOld, aFileNameNew, aDataType, aAttr) Called"));
    TPtrC mimetype = aDataType.Des();
    TFileName fileNameOld;
    aFileOld.FullName(fileNameOld);
    RDebug::Print( _L("DocumentHandler: Parameters are: aDataType: %S -- aFileOld (name): %S -- aFileNameNew: %S"), &mimetype, &fileNameOld, &aFileNameNew);
    #endif

    TInt error = KErrNone;
    TUid uid = { 0 };

    if (aDataType.Des8().FindF( KDummyMimeType ) != KErrNotFound)
        {
        return KErrNone;
        }

    iOperation = EDocCopy;

    RecognizeAndCheckFileL( const_cast<RFile&>(aFileOld), aDataType, uid );

    TRAP( error, FindHandlerL( aDataType, uid ) ); // allow unsupported.
    if ( error == KMimeNotSupported )
        {
        iHandler = CDocDefaultHandler::NewL( aDataType, uid, this, EDocSaveOnly );
        error = KErrNone;
        }
    else
        {
        User::LeaveIfError( error );
        }

    if ( !iHandler->CanSave() )
        {
        User::Leave( KErrNotSupported );
        }
	
	TFileName filenameold;
    aFileOld.FullName( filenameold );
    iHandler->SetSrcFileName( filenameold );

    // If aFileNameNew is not set, use source file name
    if (aFileNameNew.Length() != 0)
        {
        error = iHandler->SetDestName( aFileNameNew );
        }
    else
        {
        aFileOld.Name( filenameold );
        error = iHandler->SetDestName( filenameold );
        }

    // Let's do actual copying using CopyHandleL method
    if ( error == KErrNone )
        {
        error = iHandler->CopyHandleL( aFileOld, aAttr );
        }

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::CopyL: finished with error=%d."), error);
    #endif

    LEAVEONERROR( error );

    return error;
    }

// ---------------------------------------------------------
// CDocumentHandler::MoveL
// Move file to the correct directory based on it's mime type.
//
// Returns: KErrNone:           Everything went ok
//          KUserCancel:      The user cancelled the operation
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::MoveL(
    const TDesC& aFileNameOld,  // Move this file ...
    const TDesC& aFileNameNew,  // ...to this filename
    TDataType& aDataType,       // Mime type of data
    const TUint aAttr )         // use these attributes to new file
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::MoveL(aFileNameOld, aFileNameNew, aDataType, aAttr) Called"));
    TPtrC mimetype = aDataType.Des();
    RDebug::Print( _L("DocumentHandler: Parameters are: aDataType: %S -- aFileNameOld: %S -- aFileNameNew: %S"), &mimetype, &aFileNameOld, &aFileNameNew);
    #endif

    TInt error = KErrNone;
    TUid uid = { 0 };

    if (aDataType.Des8().FindF( KDummyMimeType ) != KErrNotFound)
        {
        return KErrNone;
        }

    iOperation = EDocMove;

    RecognizeAndCheckFileL( aFileNameOld, aDataType, uid );

    TRAP( error, FindHandlerL( aDataType, uid ) ); // allow unsupported.
    if ( error == KMimeNotSupported )
        {
        iHandler = CDocDefaultHandler::NewL( aDataType, uid, this, EDocSaveOnly );
        error = KErrNone;
        }
    else
        {
        User::LeaveIfError( error );
        }

    if ( !iHandler->CanSave() )
        {
        User::Leave( KErrNotSupported );
        }

    error = iHandler->SetSrcFileName( aFileNameOld );
    if ( error == KErrNone )
        {
        error = iHandler->SetDestName( aFileNameNew );
        }

    // We use CopyOrMoveL-function, iOperation is checked there
    if ( error == KErrNone )
        {
        error = iHandler->CopyOrMoveL( aAttr );
        }

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::MoveL: finished with error=%d."), error);
    #endif

    LEAVEONERROR( error );

    return error;
    }

// ---------------------------------------------------------
// CDocumentHandler::SilentMoveL
// Move file to the correct directory based on it's mime type.
// Not any user interaction.
//
// Returns: KErrNone:           Everything went ok
//          KUserCancel:      The user cancelled the operation
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::SilentMoveL(
    const TDesC& aFileNameOld,
    const TDesC& aNameNew,
    const TDesC& aRootPath,
    TDataType& aDataType,
    const TUint aAttr )
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::SilentMoveL(aFileNameOld, aFileNameNew, aDataType, aAttr) Called"));
    TPtrC mimetype = aDataType.Des();
    RDebug::Print( _L("DocumentHandler: Parameters are: aDataType: %S -- aFileNameOld: %S -- aFileNameNew: %S"), &mimetype, &aFileNameOld, &aNameNew);
    #endif

    TInt error = KErrNone;
    TUid uid = { 0 };

    if (aDataType.Des8().FindF( KDummyMimeType ) != KErrNotFound)
        {
        return KErrNone;
        }

    iOperation = EDocSilentMove;

    RecognizeAndCheckFileL( aFileNameOld, aDataType, uid );

    TRAP( error, FindHandlerL( aDataType, uid ) ); // allow unsupported.
    if ( error == KMimeNotSupported )
        {
        iHandler = CDocDefaultHandler::NewL( aDataType, uid, this, EDocSaveOnly );
        error = KErrNone; 
        }
    else
        {
        User::LeaveIfError( error );
        }

    if ( !iHandler->CanSave() )
        {
        User::Leave( KErrNotSupported );
        }

    error = iHandler->SetRootPath( aRootPath );

    if ( error == KErrNone )
        {
        error = iHandler->SetSrcFileName( aFileNameOld );
        }
    if ( error == KErrNone )
        {
        error = iHandler->SetDestName( aNameNew );
        }

    // We use CopyOrMoveL-function, iOperation is checked there
    if ( error == KErrNone )
        {
        error = iHandler->CopyOrMoveL( aAttr );
        }

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::SilentMoveL: finished with error=%d."), error);
    #endif

    LEAVEONERROR( error );

    return error;
    }

// ---------------------------------------------------------
// CDocumentHandler::OpenFileL
//
// Open a file with a given data type standalone.
// Calls other version of OpenFileL.
//
// Returns: KErrNone:           Everything went ok
//          KUserCancel:      The user cancelled the operation
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::OpenFileL(
    const TDesC& aFileName,     // Read data from here
    TDataType& aDataType )      // mime type of the data
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::OpenFileL(aFileName, aDataType) Called"));
    TPtrC mimetype = aDataType.Des();
    RDebug::Print( _L("DocumentHandler: Parameters are: aDataType: %S -- aFileName: %S  "), &mimetype, &aFileName);
    #endif

    RFile fileHandle;
    OpenTempFileL(aFileName, fileHandle);
    TInt error = OpenFileL(fileHandle, aDataType);
    fileHandle.Close();
    return error;
    }

// ---------------------------------------------------------
// CDocumentHandler::OpenFileL
//
// Open a file with a given data type standalone. First
// check that the content is supported and get the handler
// application's UID. Based on that UID find the correct
// handler for the content. File data is not copied over.
//
// Returns: KErrNone:           Everything went ok
//          KUserCancel:      The user cancelled the operation
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::OpenFileL(
          RFile& aSharableFile,
          TDataType& aDataType)
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::OpenFileL(aSharableFile, aDataType) Called"));
    TPtrC mimetype = aDataType.Des();
    TFileName filename;
    aSharableFile.FullName(filename);
    RDebug::Print( _L("DocumentHandler: Parameters are: aDataType: %S -- fullname of filehandle: %S  "), &mimetype, &filename);
    #endif

    TUid uid = { 0 };
    TInt error;

    if (aDataType.Des8().FindF( KDummyMimeType ) != KErrNotFound)
        {
        return KErrNone;
        }

    iOperation = EDocOpenFile;

    RecognizeAndCheckFileL( aSharableFile, aDataType, uid );

    FindHandlerL( aDataType, uid );

    if ( !iHandler->CanOpen() )
        {
        User::Leave( KErrNotSupported );
        }

    error = iHandler->OpenFileL(aSharableFile);            // Do open file

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::OpenFileL: finished with error=%d."), error);
    #endif

    LEAVEONERROR( error );

    return error;
    }

// ---------------------------------------------------------
// CDocumentHandler::OpenFileEmbeddedL
// Open a file with a given data type embedded.
// Calls other version of OpenFileEmbeddedL.
//
// Returns: KErrNone:           Everything went ok
//          KUserCancel:      The user cancelled the operation
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::OpenFileEmbeddedL(
    const TDesC& aFileName,     // Read data from here
    TDataType& aDataType )      // mime type of the data
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::OpenFileEmbeddedL(aFileName, aDataType) Called"));
    TPtrC mimetype = aDataType.Des();
    RDebug::Print( _L("DocumentHandler: Parameters are: aDataType: %S -- aFileName: %S  "), &mimetype, &aFileName);
    #endif

    RFile fileHandle;
    OpenTempFileL(aFileName, fileHandle);
    TInt error = OpenFileEmbeddedL(fileHandle, aDataType, InParamListL());
    fileHandle.Close();
    return error;
    }

// ---------------------------------------------------------
// CDocumentHandler::OpenFileEmbeddedL
// Calls other version of OpenFileEmbeddedL.
//
// Returns: KErrNone:           Everything went ok
//          KUserCancel:      The user cancelled the operation
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::OpenFileEmbeddedL(
          RFile& aSharableFile,
          TDataType& aDataType)
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::OpenFileEmbeddedL(aSharableFile, aDataType) Called"));
    #endif

    return OpenFileEmbeddedL(aSharableFile, aDataType, InParamListL());
    }

// ---------------------------------------------------------
// CDocumentHandler::OpenFileEmbeddedL
// Open a file with a given data type embedded. First
// check that the content is supported and get the handler
// application's UID. Based on that UID find the correct
// handler for the content. File data is not copied over.
//
// Returns: KErrNone:           Everything went ok
//          KUserCancel:      The user cancelled the operation
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::OpenFileEmbeddedL(
          RFile& aSharableFile,
          TDataType& aDataType,
          const CAiwGenericParamList& aParamList)
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::OpenFileEmbeddedL(aSharableFile, aDataType, aParamList) Called"));
    TPtrC mimetype = aDataType.Des();
    TFileName filename;
    aSharableFile.FullName(filename);
    RDebug::Print( _L("DocumentHandler: Parameters are: aDataType: %S -- fullname of filehandle: %S  "), &mimetype, &filename);
    #endif

    TUid uid = { 0 };
    TInt error;

    if (aDataType.Des8().FindF( KDummyMimeType ) != KErrNotFound)
        {
        return KErrNone;
        }

    iOperation = EDocOpenFileEmb;

    error = RecognizeAndCheckFileL( aSharableFile, aDataType, uid );

    if ( error != KErrNone )
        {
        User::Leave( KErrNotSupported );
        }

    FindHandlerL( aDataType, uid );

    if ( !iHandler->CanOpen() )
        {
        User::Leave( KErrNotSupported );
        }

    iHandler->AddToParamListL( aParamList );


     // Default to true.
    TBool supportsEmbeddability = ETrue;

    // Check from AppArc whether the handler app. supports embeddability.
    TUid handlerUid;
    iHandler->HandlerAppUid( handlerUid );

    TApaAppCapability caps;
    TPckg<TApaAppCapability> pack( caps );
    TInt err = iApaLs->GetAppCapability( pack, handlerUid );

    if ( err == KErrNone && caps.iEmbeddability == TApaAppCapability::ENotEmbeddable )
        {
        supportsEmbeddability = EFalse;
        }

    if ( supportsEmbeddability )
        {
        error = iHandler->OpenFileEmbeddedL(aSharableFile); // Open embedded
        }
    else
        {
        error = iHandler->OpenFileL(aSharableFile); // Open stand-alone
        }

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::OpenFileEmbeddedL: finished with error=%d."), error);
    #endif

    LEAVEONERROR( error );

    return error;
    }

// ---------------------------------------------------------
// CDocumentHandler::CanHandleL
// Check if there is a handler application for aDataType.
//
// Returns: ETrue:  The system is capable of handling aDataType
//          EFalse: The system is not capable of handling aDataType
// ---------------------------------------------------------
//
EXPORT_C TBool CDocumentHandler::CanHandleL( const TDataType& aDataType )
    {
    TUid appUid;
    TInt error;
    TBool response = EFalse;

    #ifdef _DEBUG
    TPtrC mimetype = aDataType.Des();
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::CanHandleL called with aDataType: %S "), &mimetype );
    #endif

    error = iApaLs->AppForDataType( aDataType, appUid );
    if ( error == KErrNone )
        {
        TRAP( error, FindHandlerL( aDataType, appUid ) ); // allow unsupported.
        if ( error == KMimeNotSupported )
            {
            iHandler = CDocDefaultHandler::NewL( aDataType, appUid, this, EDocSaveOnly );
            error = KErrNone;
            }
        else
            {
            User::LeaveIfError( error );
            }

        if ( iHandler )
            {
            response = ( iHandler->CanOpen() ||
                         iHandler->CanSave() );
            }
        }
    return response;
    }

// ---------------------------------------------------------
// CDocumentHandler::CanOpenL
// Check if there is a handler application for aDataType and
// open is possible.
//
// Returns: ETrue:  The system is capable of handling aDataType
//          EFalse: The system is not capable of handling aDataType
// ---------------------------------------------------------
//
EXPORT_C TBool CDocumentHandler::CanOpenL( const TDataType& aDataType )
    {
    TUid appUid;
    TInt error;
    TBool response = EFalse;

    #ifdef _DEBUG
    TPtrC mimetype = aDataType.Des();
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::CanOpenL called with aDataType: %S "), &mimetype );
    #endif

    error = iApaLs->AppForDataType( aDataType, appUid );
    if ( error == KErrNone )
        {
        FindHandlerL( aDataType, appUid ); // do not allow unsupported
        if ( iHandler )
            {
            response = iHandler->CanOpen();
            }
        }
    return response;
    }


// ---------------------------------------------------------
// CDocumentHandler::CanSaveL
// Check if there is a handler application for aDataType and
// saving is possible.
//
// Returns: ETrue:  The system is capable of handling aDataType
//          EFalse: The system is not capable of handling aDataType
// ---------------------------------------------------------
//
EXPORT_C TBool CDocumentHandler::CanSaveL( const TDataType& aDataType )
    {
    TUid appUid;
    TInt error;
    TBool response = EFalse;

    #ifdef _DEBUG
    TPtrC mimetype = aDataType.Des();
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::CanSaveL called with aDataType: %S "), &mimetype );
    #endif

    error = iApaLs->AppForDataType( aDataType, appUid );
    if ( error == KErrNone )
        {
        TRAP( error, FindHandlerL( aDataType, appUid ) ); // allow unsupported.
        if ( error == KMimeNotSupported )
            {
            iHandler = CDocDefaultHandler::NewL( aDataType, appUid, this, EDocSaveOnly );
            error = KErrNone;
            }
        else
            {
            User::LeaveIfError( error );
            }

        if ( iHandler )
            {
            response = iHandler->CanSave();
            }
        }
    return response;
    }


// ---------------------------------------------------------
// CDocumentHandler::CheckFileNameExtension
// Add correct file extension to aFileName with aDatatype.
// Calls CDocDefaultHandler::CheckFileNameExtensionL()
// ---------------------------------------------------------
//
EXPORT_C void CDocumentHandler::CheckFileNameExtension( TDes& aFileName, const TDataType& aDatatype )
    {
    #ifdef _DEBUG
    TPtrC mimetype = aDatatype.Des();
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::CheckFileNameExtension called with: aFileName: %S -- aDataType: %S "), &aFileName, &mimetype );
    #endif

    TUid appUid;
    TInt error;

    // Try to find uid
    error = iApaLs->AppForDataType( aDatatype, appUid );
    if ( error == KErrNone )
        {
        // Try to find handler.
        TRAPD(err, FindHandlerL(aDatatype, appUid));

        if (err == KErrNone && iHandler)
            {
            // Check finally extension
            TRAP_IGNORE( iHandler->CheckFileNameExtensionL( aFileName, aDatatype ) );
            }
        }

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::CheckFileNameExtension finished : aFileName: %S"), &aFileName );
    #endif
    }

// ---------------------------------------------------------
// CDocumentHandler::SetExitObserver(..)
// Delegate exit signals to aObserver too.
// ---------------------------------------------------------
//
EXPORT_C void CDocumentHandler::SetExitObserver(
    MAknServerAppExitObserver* aObserver )
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::SetExitObserver called.") );
    #endif

    __ASSERT_DEBUG (
        aObserver,
        User::Panic ( _L ( "DocumentHandler" ), KErrUnknown ) );
    iServerAppExitObserver = aObserver;
    }

// ---------------------------------------------------------
// CDocumentHandler::FindHandlerByUidL(..)
// Try to find a handler for aUid.
// ---------------------------------------------------------
//
void CDocumentHandler::FindHandlerByUidL( const TUid& aUid, const TDataType& aDataType )
    {
    switch ( aUid.iUid )
        {
        case KTextHandler:        // Notepad viewer
            iHandler = CDocDefaultHandler::NewL(
                           aDataType, 
                           aUid, this, EDocOpenAndSave );
            break;
        case KCertSaveAppHandler: // Cert save app
            iHandler = CDocDefaultHandler::NewL(
                           aDataType,
                           aUid, this, EDocOpenOnly );
            break;
        case KLandmarkHandler: // Landmark UI app
            iHandler = CDocDefaultHandler::NewL(
                           aDataType,
                           aUid, this, EDocOpenOnly );
            break;
        case KImageViewerHandler: // Image Viewer
            iHandler = CDocImageHandler::NewL(
                           aDataType, aUid, this);
            break;
        case KAppInstHandler:   // Application Installer
            iHandler = CDocAppInstHandler::NewL(
                           aDataType,
                           aUid, this, EDocOpenAndSave );
            break;
        case KWmlcHandler: // Browser
            iHandler = CDocDefaultHandler::NewL(
                           aDataType,
                           aUid, this, EDocOpenAndSave );
            break;
        default:
/*          TODO: Do we need midlet handler anymore?
            if (FeatureManager::FeatureSupported( KFeatureIdCdmaExtendedAms ) )
                {
                // Check if given UID belongs to a Java Midlet
                if ( CDocMidletHandler::IsMidlet( aUid ) )
                    {
                    iHandler = CDocMidletHandler::NewL(
                        aDataType,
                        aUid, this);
                    }
                }
*/
            break; // We will use default handler
        }
    }

// ---------------------------------------------------------
// void CDocumentHandler::FindHandlerByMimeTypeL(..)
// Try to find a handler for aDataType
// ---------------------------------------------------------
//
void CDocumentHandler::FindHandlerByMimeTypeL( const TUid& aUid, const TDataType& aDataType )
    {
    // All games are handler by the game handler
    if ( aDataType.Des8().FindF( KGameMimeType ) != KErrNotFound )
        {
        iHandler = CDocGameHandler::NewL(
                           aDataType, aUid, this, EDocSaveOnly );
        return;
        }

    if (( aDataType.Des8().FindF( KDocMimeCard ) != KErrNotFound) ||
        ( aDataType.Des8().FindF( KDocMimeCalendar) != KErrNotFound) ||
        ( aDataType.Des8().FindF( KDocMimeCalendar2) != KErrNotFound))
        {
        //
        // vCal and vCard types are handled as 'read only' types
        // (must be saved from application, not through doc handler).
        //
        iHandler = CDocDefaultHandler::NewL(
                           aDataType,
                           aUid, this, EDocOpenOnly );
        return;
        }
    #ifdef ENABLE_DRM
    #ifdef __DRM_OMA2
    if ( aDataType.Des8().FindF( KOma1DcfContentType ) != KErrNotFound ||
         aDataType.Des8().FindF( KOma2DcfContentType ) != KErrNotFound )
    #else // __DRM_OMA2
    if ( aDataType.Des8().FindF( KOma1DcfContentType ) != KErrNotFound )
    #endif // __DRM_OMA2
        {
        iHandler = CDocDCFHandler::NewL( aDataType, iOperation, aUid, this );
        return;
        }
    #endif // ENABLE_DRM

    }

// ---------------------------------------------------------
// CDocumentHandler::FindHandlerL
// Based on app uid and mime type decide which handler
// implementation to use.
//
//
// Returns: KErrNone:           The handler was constructed ok
// ---------------------------------------------------------
//
TInt CDocumentHandler::FindHandlerL(
    const TDataType& aDataType,
    const TUid& aUid)
    {
    delete iHandler;            // delete the old handler
    iHandler = NULL;

    // First check by the application uid
    FindHandlerByUidL( aUid, aDataType );

    // Then check by the mime type
    if ( !iHandler )
        {
        FindHandlerByMimeTypeL( aUid, aDataType );
        }

    // Default handler if everything else has failed
    if ( !iHandler )
        {
        TApaAppInfo info;
        if ( iApaLs->GetAppInfo( info, aUid ) == KErrNone ) // Check the uid is real.
            {
            iHandler = CDocDefaultHandler::NewL( aDataType,
                                             aUid, this, EDocOpenAndSave );
            }
        else
            {
            User::Leave( KMimeNotSupported );
            }
        }
        
    return KErrNone;
    }


// ---------------------------------------------------------
// Get the whole path including filename where the content was saved.
// If the content was not saved in a file, return the id
// representing the object.
// returns: KErrNone:           Ok
//          KNotInitialized     Handler is no initialized
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::GetPath( TDes& aPath )
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::GetPath called.") );
    #endif

    __ASSERT_DEBUG (
        iHandler,
        User::Panic ( _L( "DocumentHandler" ), KNotInitialized ) );

    if ( !iHandler )
        {
        aPath.Zero();
        return KNotInitialized;
        }
    iHandler->GetPath( aPath );

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::GetPath returns aPath: %S "), &aPath);
    #endif

    return iHandler->Status();
    }

// ---------------------------------------------------------
// Get the Uid of handler application.
// returns: KErrNone:           Ok
//          KNotInitialized     Handler is no initialized
// ---------------------------------------------------------
//
EXPORT_C TInt CDocumentHandler::HandlerAppUid( TUid& aUid )
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::HandlerAppUid called.") );
    #endif

    __ASSERT_DEBUG (
        iHandler,
        User::Panic ( _L( "DocumentHandler" ), KNotInitialized ) );

    if ( !iHandler )
        {
        return KNotInitialized;
        }
    iHandler->HandlerAppUid( aUid );

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::HandlerAppUid returns uid: %x "), aUid.iUid);
    #endif

    return iHandler->Status();
    }

// ---------------------------------------------------------
// CDocumentHandler::ListSupportedMimeTypesL
// Lists all supported MIME-types using RDebug::Print
// ---------------------------------------------------------
//
void CDocumentHandler::ListSupportedMimeTypesL()
    {
    #ifdef _DEBUG
    RDebug::Print( _L( "DocumentHandler: All supported mime types:" ) );
    RDebug::Print( _L( "**********************" ) );
    CDataTypeArray *dataTypes = new( ELeave ) CDataTypeArray( 20 );
    CleanupStack::PushL( dataTypes );
    iApaLs->GetSupportedDataTypesL( *dataTypes );
    for ( TInt i = dataTypes->Count() - 1; i; i-- )
        {
        TBuf < KMaxDataTypeLength > buf;
        buf.Copy( dataTypes->At( i ).Des8() );
        RDebug::Print( buf );
        TUid uid;
        iApaLs->AppForDataType( dataTypes->At( i ), uid );
        TApaAppInfo appInfo;
        iApaLs->GetAppInfo( appInfo, uid );
        RDebug::Print( _L(" -handler app uid - %x, caption - %S"), uid.iUid, &appInfo.iCaption);

        }
    RDebug::Print( _L( "**********************" ) );
    CleanupStack::PopAndDestroy();
    #endif
    }

// ---------------------------------------------------------
// CDocumentHandler::RecognizeAndCheckFile
// Recognizes the file and makes other checks.
// This filehandle version is called from OpenFile*L methods
// ---------------------------------------------------------
//
TInt CDocumentHandler::RecognizeAndCheckFileL(
    RFile& aFileHandle,
    TDataType& aDataType,
    TUid& aUid )
    {
    #ifdef ENABLE_DRM
    if ( aDataType.Des8().FindF( KOma1DcfContentType ) != KErrNotFound ||
         aDataType.Des8().FindF( KOma2DcfContentType ) != KErrNotFound )
        {
        return KErrNone;
        }
    #endif

    #ifdef _DEBUG
    ListSupportedMimeTypesL(); // Let's list all supported mime-types
    #endif

    TDataType recognizedData;
    TDataType emptyType;

    // TODO: Do we need some security checks for file?
    TInt error = KErrNone;

    // Caller gave data type, try it first.
    if ( aDataType != emptyType )
        {
        error = iApaLs->AppForDataType( aDataType, aUid );
        if ( error == KErrNone )
            {
            #ifdef _DEBUG
            RDebug::Print( _L("DocumentHandler: CDocumentHandler::RecognizeAndCheckFileL: Use data type from caller:") );
            RDebug::Print( aDataType.Des() );
            #endif
            return KErrNone;
            }
        }

    // Let's ask from RApaLsSession what datatype file is
    // This will give us both uid of an application and the data type.
    error = iApaLs->AppForDocument( aFileHandle, aUid, recognizedData );
    if ( error == KErrNone )
        {
#ifdef _DEBUG
        RDebug::Print( _L( "DocumentHandler: CDocumentHandler::RecognizeAndCheckFileL: Recognized mime type:" ) );
        RDebug::Print( recognizedData.Des() );
#endif
        if ( recognizedData != emptyType )
            {
            aDataType = recognizedData;
            return KErrNone;
            }
        }

    return KErrNotFound;
    }

// ---------------------------------------------------------
// CDocumentHandler::RecognizeAndCheckFile
// Recognizes the file and makes other checks.
// This filename version is called from Copy/Move methods
// ---------------------------------------------------------
//
TInt CDocumentHandler::RecognizeAndCheckFileL(
    const TDesC& aFileName,
    TDataType& aDataType,
    TUid& aUid )
    {
    #ifdef ENABLE_DRM
    if ( aDataType.Des8().FindF( KOma1DcfContentType ) != KErrNotFound ||
         aDataType.Des8().FindF( KOma2DcfContentType ) != KErrNotFound )
        {
        return KErrNone;
        }
    #endif

    TDataType recognizedData;
    TDataType emptyType;

    #ifdef _DEBUG
    ListSupportedMimeTypesL(); // Let's list all supported mime-types
    #endif

    // If the file is an executable, we are not allowed to continue
    // for security reasons.
    TBool executable;
    User::LeaveIfError( iApaLs->IsProgram( aFileName, executable ) );
    if ( executable )               // Warn the caller about the content.
        {
        User::Leave( KExecNotAllowed );
        }

    TInt error = KErrNone;

    // Caller gave data type, try it first.
    if ( aDataType != emptyType )
        {
        error = iApaLs->AppForDataType( aDataType, aUid );
        if ( error == KErrNone )
            {
            #ifdef _DEBUG
            RDebug::Print( _L("DocumentHandler: CDocumentHandler::RecognizeAndCheckFileL: Use data type from caller:") );
            RDebug::Print( aDataType.Des() );
            #endif
            // Success, we're done.
            return KErrNone;
            }
        }

    // Let's ask from RApaLsSession what datatype file is
    // This will give us both uid of an application and the data type.
    error = iApaLs->AppForDocument( aFileName, aUid, recognizedData );
    if ( error == KErrNone )
        {
        #ifdef _DEBUG
        RDebug::Print( _L( "DocumentHandler: CDocumentHandler::RecognizeAndCheckFileL: Recognized mime type:" ) );
        RDebug::Print( recognizedData.Des() );
        #endif
        if ( recognizedData != emptyType )
            {
            aDataType = recognizedData;
            return KErrNone;
            }
        }

    return KErrNotFound;
    }

// ---------------------------------------------------------
// CDocumentHandler::OpenTempFileL()
// Opens a new sharable filehandle from existing file.
// ---------------------------------------------------------
//
EXPORT_C void CDocumentHandler::OpenTempFileL(
          const TDesC& aFileName,
          RFile &aSharableFile)
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::OpenTempFileL() Called"));
    RDebug::Print( _L("DocumentHandler: Parameters are: aFileName: %S  "), &aFileName);
    #endif

    TInt error = KErrNone;

    // Cannot do anything if filename is not valid.
    if (aFileName.Length() == 0)
        {
        error=KNotInitialized;
        }

    // Close if existing sharable RFs and create new for sharing purposes.
    if ( error == KErrNone )
        {
        CloseSharableFS();
        User::LeaveIfError(iSharableFS.Connect());
        User::LeaveIfError(iSharableFS.ShareProtected());
        TInt err = aSharableFile.Open(iSharableFS,aFileName,EFileShareReadersOnly);
        if (err == KErrInUse)
            {
            User::LeaveIfError(aSharableFile.Open(iSharableFS,aFileName,EFileShareReadersOrWriters));
            }
        else if ( err != KErrNone )
            {
            error = err; // Otherwise possible KErrNotReady caused by hotswap leads to crash later
            }
        }
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::OpenTempFileL: finished with error=%d."), error);
    #endif

    LEAVEONERROR( error );
    }

// ---------------------------------------------------------
// CDocumentHandler::SaveTempFileL()
// Saves content (aContent) to file and opens that sharable file
// ---------------------------------------------------------
//
EXPORT_C void CDocumentHandler::SaveTempFileL(
          const TDesC8& aContent,
          TDataType& aDataType,
          const TDesC& aFileName,
          RFile &aSharableFile)
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::SaveTempFileL() Called"));
    TPtrC mimetype = aDataType.Des();
    RDebug::Print( _L("DocumentHandler: Parameters are: aDataType: %S -- aFileName: %S  "), &mimetype, &aFileName);
    #endif

    TUid uid = { 0 };
    TInt error;
    TFileName createdFileName;

    iOperation = EDocSaveTemp;

    // Use Default Handler for saving whatever mimetype actually is
    delete iHandler;            // delete the old handler
    iHandler = NULL;
    iHandler = CDocDefaultHandler::NewL( aDataType,
                                             uid, this, EDocSaveOnly );

    error = iHandler->SetDestName( aFileName );     // Save with this file name

    // Close if existing sharable RFs and create new for sharing purposes.
    if ( error == KErrNone )
        {
        CloseSharableFS();
        User::LeaveIfError(iSharableFS.Connect());
        iSharableFS.ShareProtected();
        }

    if ( error == KErrNone )
        {
        error = iHandler->SaveTempFileL( aContent, KEntryAttNormal, createdFileName ); // Do save the content
        }

    if ( error == KErrNone )
        {
        OpenTempFileL(createdFileName, aSharableFile);
        }

    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::SaveTempFileL: finished with error=%d."), error);
    #endif

    LEAVEONERROR( error );
    }

// ---------------------------------------------------------
// CDocumentHandler::InParamListL()
// Returns empty instance of CAiwGenericParamList
// ---------------------------------------------------------
//
EXPORT_C CAiwGenericParamList& CDocumentHandler::InParamListL()
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::InParamListL() Called"));
    #endif

    if (!iInParams)
        {
        iInParams = CAiwGenericParamList::NewL();
        }
    iInParams->Reset();
    return *iInParams;
    }

// ---------------------------------------------------------
// CDocumentHandler::OutParamList()
// Returns list of possible output parameters
// ---------------------------------------------------------
//
EXPORT_C const CAiwGenericParamList* CDocumentHandler::OutParamList()
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::OutParamListL() Called"));
    #endif

    const CAiwGenericParamList* result = NULL;

    if (!iHandler)
        {
        return NULL;
        }

    TRAPD(err, result = iHandler->OutputParamsL());
    if (err != KErrNone)
        {
        return NULL;
        }

    return result;
    }

// ---------------------------------------------------------
// CDocumentHandler::CloseSharableFS
// Close iSharableFs
// ---------------------------------------------------------
//
void CDocumentHandler::CloseSharableFS()
    {
    if (iSharableFS.Handle() != NULL)
        {
        iSharableFS.Close();
        }
    }

// ---------------------------------------------------------
// CDocumentHandler::SetTempFile
// Set temp file, which will be deleted in destructor.
// ---------------------------------------------------------
//
void CDocumentHandler::SetTempFile(const TDesC& aTempFile)
    {
    #ifdef _DEBUG
    RDebug::Print( _L("DocumentHandler: CDocumentHandler::SetTempFile called with %S  "), &aTempFile);
    #endif

    // If there allready is stored tempfile, delete it first
    if ( iTempFileName.Length() > 0 && iHandler )
        {
        iHandler->DeleteFile(iTempFileName);
        }

    // Set new tempfile to member variable
    if ( aTempFile.Length() > 0 )
        {
        iTempFileName = aTempFile;
        }
    }

// ---------------------------------------------------------
// CDocumentHandler::CanHandleProgressivelyL()
// Returns ETrue if progressive downloading is supported by
// some application for the requested data type. The Uid of
// the application for the given data type is also returned.
//
// ---------------------------------------------------------
//
EXPORT_C TBool CDocumentHandler::CanHandleProgressivelyL(
    const TDataType& aDataType,
    TUid& aUid )
    {
    aUid.iUid = 0; // By default

    HBufC* buffer16 = HBufC::NewLC( KDocMaxCenRepBufLen );

    // Get Uid list.
    //
    TInt err = KErrNone;
    RArray<TInt32> uidList;
    TRAP( err, GetProgressiveDownloadAppUidsL( uidList ) )
    CleanupClosePushL( uidList );
    User::LeaveIfError( err ); // KErrNotFound.

    // Check mimetypes.
    //
    CRepository* variation = CRepository::NewL( KCRUidCommonUi );
    CleanupStack::PushL( variation );

    TPtr allMimePtr( buffer16->Des() );
    allMimePtr.Zero();

    HBufC8* oneMime = HBufC8::NewLC( KDocPDMaxMimeLen );
    TPtr8 oneMimePtr( oneMime->Des() );
    TUint uidCount = uidList.Count();

    for ( TInt i = 0; i < Min( uidCount, KDocPDMaxUids ); i++ )
        {
        err = variation->Get( KCuiMimeTypeSet1 + i, allMimePtr );
        TInt start = 0; // leftmost pos.
        TInt len = 0;
        do
            {
            len = allMimePtr.Mid( start ).Locate( ';' );
            if ( len == KErrNotFound )
                {
                len = allMimePtr.Mid( start ).Length();
                }
            if ( len > KDocPDMaxMimeLen ) // resize buffer length
                {
                CleanupStack::PopAndDestroy( oneMime );
                oneMime = HBufC8::NewLC( len );
                oneMimePtr.Set( oneMime->Des() );
                }
            oneMimePtr.Copy( allMimePtr.Mid( start, len ) );
            oneMimePtr.Trim();

            if ( !aDataType.Des8().CompareF( oneMimePtr ) ||
                aDataType.Des8().MatchF( oneMimePtr ) != KErrNotFound )
                {
                aUid.iUid = uidList[ i ];
                CleanupStack::PopAndDestroy( 4 ); // buffer16, uidList, variation
                                                  // oneMime
                return ETrue;
                }

            oneMimePtr.Zero();
            if ( len > KDocPDMaxMimeLen ) // return normal length
                {
                CleanupStack::PopAndDestroy( oneMime );
                oneMime = HBufC8::NewLC( KDocPDMaxMimeLen );
                oneMimePtr = oneMime->Des();
                }
            start += len + 1;
            }
        while ( start < allMimePtr.Length() );
        }

    CleanupStack::PopAndDestroy( 4 ); // buffer16, uidList, variation, oneMime

    return EFalse; // not found.
    }

// ---------------------------------------------------------
// CDocumentHandler::GetProgressiveDownloadAppUidsL
// Returns
//
// ---------------------------------------------------------
//
EXPORT_C void CDocumentHandler::GetProgressiveDownloadAppUidsL(
    RArray<TInt32>& aUidList )
    {
    // 16-bit buffer for CenRep.
    HBufC* buffer16 = HBufC::NewLC( KDocMaxCenRepBufLen );

    // Read data to the buffer.
    TInt err = KErrNone;
    CRepository* variation = CRepository::NewL( KCRUidCommonUi );
    CleanupStack::PushL( variation );
    TPtr allUidPtr( buffer16->Des() );

    err = variation->Get( KCuiProgDownloadUids, allUidPtr );
    if( err != KErrNone )
        {
        User::LeaveIfError( KErrNotFound ); // Error: CenRep access failed.
        }
    CleanupStack::PopAndDestroy( 1 ); // variation

    HBufC* oneUid = HBufC::NewLC( KDocPDMaxUidLen );
    TPtr oneUidPtr( oneUid->Des() );

    TInt start = 0;
    TInt len = 0;
    do
        {
        len = allUidPtr.Mid( start ).Locate( ';' );
        if ( len == KErrNotFound )
            {
            len = allUidPtr.Mid( start ).Length();
            }
        if ( len > KDocPDMaxUidLen ) // resize buffer length
            {
            CleanupStack::PopAndDestroy( oneUid );
            oneUid = HBufC::NewLC( len );
            oneUidPtr.Set( oneUid->Des() );
            }
        oneUidPtr.Copy( allUidPtr.Mid( start, len ) );
        oneUidPtr.Trim();

        TInt32 uid = 0;
        if ( ConvertHexStringToInt32( oneUidPtr, uid ) != KErrNone )
            {
            User::LeaveIfError( KErrNotFound ); // Error: conversion failed.
            }
        aUidList.AppendL( uid );

        oneUidPtr.Zero();
        if ( len > KDocPDMaxUidLen ) // return normal length
            {
            CleanupStack::PopAndDestroy( oneUid );
            oneUid = HBufC::NewLC( KDocPDMaxUidLen );
            oneUidPtr = oneUid->Des();
            }
        start += len + 1;
        }
    while ( start < allUidPtr.Length() );

    CleanupStack::PopAndDestroy( 2 ); // buffer16, oneUid
    }

// ---------------------------------------------------------
// CDocumentHandler::ConvertHexStringToInt32
// Returns TInt32 for a valid hex string, otherwise KErrArgument.
//
// ---------------------------------------------------------
//
TInt CDocumentHandler::ConvertHexStringToInt32(
    const TDesC& aHexString,
    TInt32& aInt32 )
    {
    aInt32 = 0;

    TInt pos = aHexString.LocateF( 'x' );
    if ( pos == KErrNotFound )
        {
        pos = 0;
        }
    else
        {
        pos++;
        }

    if( ( aHexString.Length() - pos ) > KDocMaxDigitsInHexString )
        {
        return KErrArgument; // Error: value too big.
        }
    TPtrC aHexStringPtr( aHexString.Mid( pos ) );

    TInt64 value64;
    if ( TLex( aHexStringPtr ).Val( value64, EHex ) != KErrNone )
        {
        return KErrArgument; // Error: conversion failed.
        }
    aInt32 = value64;

    return KErrNone;
    }

// End of File
