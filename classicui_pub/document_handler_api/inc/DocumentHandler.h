/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Definition of CDocumentHandler class.
*                The purpose of the Documenthandler is to offer to applications
*                - wrapper for application embedding
*                - temporary file utility to support data caging for platform security 
*             
*
*/


#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

//  INCLUDES
#include <e32base.h>
#include <f32file.h>

// CONSTANTS

// App UIDs for handlers. Handlers are identified by the handler application's
// UID. E.g. The handler for WMLC (binary format of Wireless Markup Language)
// is responsible for launching the WMLBrowser. The data type
// application/wap.vnd.wmlc is therefore mapped to the browser's UID,
// 0x10008D39.

const TInt KTextHandler         = 0x1000599d;   // Notepad viever
const TInt KWmlcHandler         = 0x10008D39;   // WML Browser
const TInt KJamHandler          = 0x100009C1;   // JAM
const TInt KAppInstHandler      = 0x101F875A;   // Installer 
const TInt KBioViewerAppHandler = 0x0FC99F01;   // BVA
const TInt KImageViewerHandler  = 0x101f4d90;   // Image viever
const TInt KCertSaveAppHandler  = 0x100059D2;   // Cert response handler app
const TInt KCODHandler          = 0x10008d4a;   // COD handler
const TInt KDDhandler           = 0x10008d3f;   // DD Handler

// A global external mime type for all nokia games.
_LIT8(KGameMimeType, "application/x-NokiaGameData");
_LIT8(KDataTypeODM,"application/vnd.oma.drm.message"); // Not supported by DocumentHandler
_LIT8(KDataTypeDCF,"application/vnd.oma.drm.content"); // Deprecated, do not use from here
                                                     
// Fail reasons
const TInt KBadMimeType         = -12002;        // Mime type conflict etc.
const TInt KMimeNotSupported    = -12003;        // No handler found
const TInt KNullContent         = -12005;        // Empty content
const TInt KDataDirNotFound     = -12006;        // Deprecated - not used
const TInt KExecNotAllowed      = -12007;        // Executables not allowed
const TInt KNoHostProcess       = -12008;        // Deprecated - not used
const TInt KNotInitialized      = -12009;        // Not initialized
const TInt KUserCancel          = -12010;        // User cancelled operation
const TInt KDRMErrSession           = -12011;   // DRM session error.
const TInt KDRMErrNoRights          = -12012;   // Invalid DRM rights.
const TInt KDRMErrRightsDBCorrupted = -12013;   // DRM rights db corrupted.
const TInt KDRMErrInvalidVersion    = -12014;   // Invalid DRM version.
const TInt KDRMErrPreviewRights     = -12015;   // Preview DRM rights.


// DATA TYPES

// API operations to inform special handlers of the entry function.
enum TDocOperation
    {
    EDocCopy,               // CopyL( aFileNameOld, aNameNew, aDataType, aAttr)
    EDocSave,               // SaveL( aContent, aDataType, aAttr )
    EDocSaveAs,             // SaveL( aContent, aDataType,aFileName, aAttr )
    EDocOpenFile,           // OpenFileL( aFileName, aDataType )
    EDocOpenFileEmb,        // OpenFileEmbeddedL( aFileName, aDataType) 
    EDocMove,               // MoveL( aFileNameOld, aNameNew, aDataType, aAttr)
    EDocSilentMove,         // SilentMoveL( aFileNameOld, aNameNew, aRootPaht, aDataType, aAttr)
    EDocSaveTemp,           // SaveTempFileL( aContent, aDataType, aFileName, aSharableFile)
    };

// FORWARD DECLARATIONS
class CDocHandlerBase;                       // Base class for handlers
class CEikProcess;                           // The host process
class MAknServerAppExitObserver;             // Viewer app exit observer 
class TDataType;                             // Mime type handling
class RApaLsSession;                         // App list server session
class CAiwGenericParamList;                  // Generic parameter list 

// CLASS DECLARATION

/**
* Utility class for opening and saving any supported content.
* This class declares an interface for the DocumentHandler, a
* common component in Series60.
*
* The CDocumentHandler class will not itself implement any content
* handling routines. It's responsible for finding out which application
* can handle given data type and constructing a correct handler implementation
* for that application. If the given data type is supported by the system
* but no specific handler is found, the CDocDefaltHandler is then constructed.
* The default handler is an implementation of the CDoCDocHandlerBase class with
* standard "Epoc-style" content handling.
*
* The handler application can be lauched standalone or embedded. The
* Embedded launching is preferred way in Series60.
* Standalone launching means that the application will run in
* it's own process. Embedded launching means that the UI of an
* application, which is responsible for handling given data type,
* is embedded into the parent application. There will be only
* parent applications icon shown in the fast swap window when an
* application is embedded.
*
* Link your application against CommonUI.lib.
*
* <b>An example: </b> 
*<pre> 
* #include <DocumentHandler.h>
*
* <i>// Define DocHandler</i>
* CDocumentHandler* iDocHandler;
* 
* <i>// Construct DocHandler</i>
* void ConstructL()
*    {
*    iDocHandler = CDocumentHandler::NewL();
*
*    <i>// I want to be notified when exit happends. Because I
*    // pass "this" pointer, I have to derive from
*    // MAknServerAppExitObserver class.</i>
*    iDocHandler->SetExitObserver(this)     
*    }
*
* <i>// delete DocHandler</i>
* void ~Myapp()
*    {
*    delete iDocHandler;
*    }
*
*
* <i>// and use like this</i>
*
* void OpenAttachmentL( RFile& aFile,           <i>// A file to be open</i>
*                       TDataType& aDataType )  <i>// DataType can be empty</i>
*   {
*   TInt error = KErrNone;
*   TFileName path;
*
*   <i>
*   // Leaves on system wide errors like disk full, out of memory etc.</i>
*   error = iDocHandler->OpenFileEmbeddedL( aFile, aDataType );
*   // The status code can be either KErrNone or KUserCancel
*
*    }
* </pre>
*
*/
NONSHARABLE_CLASS(CDocumentHandler) : public CBase
    {
    public:        // Constructors and destructor

        /**
        * Two-phased constructor. Leaves on failure.
        *
        * @param aProcess   The host process, which will be
        *                   used for embedded launching.
        *
        * @return           The constructed CDocumentHandler
        * @deprecated in Series60 3.0, instead use NewL without CEikProcess parameter
        */
        IMPORT_C static CDocumentHandler* NewL( CEikProcess* aProcess );

        /**
        * Two-phased constructor. Leaves on failure.
        *
        * @param aProcess   The host process, which will be
        *                   used for embedded launching.
        *
        * @return           The constructed CDocumentHandler
        * @deprecated in Series60 3.0, instead use NewL without CEikProcess parameter
        */
        IMPORT_C static CDocumentHandler* NewLC( CEikProcess* aProcess );

        /**
        * Two-phased constructor. Leaves on failure.
        *
        *
        * @return           The constructed CDocumentHandler
        * @since Series 60 3.0
        */
        IMPORT_C static CDocumentHandler* NewL( );

        /**
        * Two-phased constructor. Leaves on failure.
        *
        *
        * @return           The constructed CDocumentHandler
        * @since Series 60 3.0
        */
        IMPORT_C static CDocumentHandler* NewLC( );

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CDocumentHandler();

    private:        // Constructors and destructor

        /**
        * C++ default constructor.
        */
        CDocumentHandler( );

        /**
        * C++ copy constructor
        */
        CDocumentHandler( const CDocumentHandler& );

        /**
        * By default EPOC constructor is private.
        */
        void ConstructL();

    public:       // New functions, data caging
        
      /**
       * Utility method for opening filehandle from existing file for OpenFileL 
       * calls. The created file handle is meant to be shared across process 
       * boundaries.
       * 
       * This function can leave in some system wide error situation.
       * E.g. out of memory, not enough space in filesystem etc. These
       * errors are usually trapped by the application framework.
       *
       * NOTE! Caller is responsible of closing opened file handle. 
       *
       * @param aFileName  Name (including directory information) for file. 
       *                   This file should exist allready, otherwise this 
       *                   function leaves with KErrNotFound. 
       * @param aSharableFile Returned file handle that can be shared.
       * @since Series 60 3.0
       */
      IMPORT_C void OpenTempFileL(
          const TDesC& aFileName,
          RFile &aSharableFile);

      /**
       * Utility method for save aContent with aDataType temporarily
       * for OpenFileL calls. The created file handle is meant to be shared 
       * across process boundaries.
       *
       * This temporary file will be saved to process private temp directory.
       * Temporary directory will be created if not existing yet. 
       *
       * This function can leave in some system wide error situation.
       * E.g. out of memory, not enough space in filesystem etc. These
       * errors are usually trapped by the application framework.
       *
       * NOTE! Caller is responsible of closing opened file handle!
       * Created temporary file will be deleted in destructor of 
       * DocumentHandler, but caller can delete it self as well.
       *
       * @param aContent   A content data buffer. Narrow descriptor that
       *                   can contain any kind of data.
       * @param aDataType  A data type for the content of the file. If empty
       *                   the DocumentHandler tries to recognize the content.
       * @param aFileName  Use this name for saving. The name must not 
       *                   contain any directory information.
       * @param aSharableFile Returned file handle that can be shared.
       * @since Series 60 3.0
       */
      IMPORT_C void SaveTempFileL(
          const TDesC8& aContent,
          TDataType& aDataType,
          const TDesC& aFileName,
          RFile &aSharableFile);

    public:       // New functions, parameter handling
      
      /**
       * Returns an empty instance of CAiwGenericParamList class. It can be
       * used for example as an input parameter list for API methods.
       * This is just a convinience method and doesn't have
       * to be used. If consumer wants to create input list by itself
       * it is ok. If this method is used, service handler takes care
       * of deleting returned generic parameter list.
       *
       * @return  An empty instance of CAiwGenericParameter list.
       * @since Series 60 3.0
       */
      IMPORT_C CAiwGenericParamList& InParamListL();

      /**
       * Returns a list of possible output parameters handler application
       * may have set after executing the service. The caller is responsible 
       * for deleting the parameter instance if not null.
       *
       * @return   List of output parameters, NULL if nothing set.
       * @deprecated
       */          
      IMPORT_C const CAiwGenericParamList* OutParamList();

    public:       // New functions, open file with filehandle
      
       /**
        * Launches an application in standalone capable of handling
        * data in aSharableFile (using aDatatype if available). 
        * Doesn't save data from the file. In case of DRM protected 
        * files with restricted rights, there will be query asking
        * if user want open file. 
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. See 
        * also possible error codes from documenthandler.h header file.
        * 
        * @param aSharableFile  A sharable file handle to be passed to
        *                       the launched application
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation. 
        * @since Series 60 3.0
        */
      IMPORT_C TInt OpenFileL(
          RFile& aSharableFile,
          TDataType& aDataType);      
         
       /**
        * Launches an application in embedded (if possible) capable of 
        * handling data in aSharableFile (using aDatatype if available). 
        * Doesn't save data from the file. In case of DRM protected
        * files with restricted rights, there will be query asking
        * if user want open file. 
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. See 
        * also possible error codes from documenthandler.h header file.
        *
        * @param aSharableFile  A sharable file handle to be passed to
        *                       the launched application. 
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @param aParamList Parameter list to be passed to handler application.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation. 
        * @since Series 60 3.0
        */
      IMPORT_C TInt OpenFileEmbeddedL(
          RFile& aSharableFile,
          TDataType& aDataType,
          const CAiwGenericParamList& aParamList);
          
        /**
        * Launches an application in embedded (if possible) capable of 
        * handling data in aSharableFile (using aDatatype if available). 
        * Doesn't save data from the file. In case of DRM protected
        * files with restricted rights, there will be query asking
        * if user want open file. 
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. See 
        * also possible error codes from documenthandler.h header file.
        *
        * @param aSharableFile  A sharable file handle to be passed to
        *                       the launched application. 
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation. 
        * @since Series 60 3.0
        */
      IMPORT_C TInt OpenFileEmbeddedL(
          RFile& aSharableFile,
          TDataType& aDataType);
     
    public:       // open file with filename

        /**
        * Launches an application standalone capable of handling
        * data in aFilename, with aDataType. Doesn't copy data
        * from the file.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. See 
        * also possible error codes from documenthandler.h header file.
        *
        * @param aFileName  Name of the file. Directory path included.
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt OpenFileL(
            const TDesC& aFileName,
            TDataType& aDataType );

        /**
        * Launches an application embedded capable of handling data in
        * aFilename with aDataType. Doesn't copy data from the file.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. See 
        * also possible error codes from documenthandler.h header file.
        *
        * @param aFileName  Name of the file. Directory path included.
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt OpenFileEmbeddedL(
            const TDesC& aFileName,
            TDataType& aDataType );

    public:       // data saving

        /**
        * Save aContent with aDataType using aAttr to a correct directory.
        * Generates a new name for saving. The storage is usually a filesystem, 
        * but can be anything from application spesific data structures to 
        * a database.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. See 
        * also possible error codes from documenthandler.h header file.
        *
        * @param aContent   A content data buffer. Narrow descriptor that
        *                   can contain any kind of data.
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @param aAttr      Use these file attributes for saving. Your can 
        *                   find these attributes from 
        *                   \epoc32\include\f32file.h header file. 
        *                   If the storage is not a filesystem these 
        *                   attributes are ignored.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt SaveL(
            const TDesC8& aContent,
            TDataType& aDataType,
            const TUint aAttr );

        /**
        * Save aBuffer with aDataType using aAttr to a correct storage with a
        * supplied name. The storage is usually a filesystem, but can be 
        * anything from application spesific data structures to a database.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. See 
        * also possible error codes from documenthandler.h header file.
        *
        * @param aContent   A content data buffer. Narrow descriptor that
        *                   can contain any kind of data.
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @param aName      Use this name for saving. The name must not 
        *                   contain any directory information.
        * @param aAttr      Use these file attributes for saving. Your can 
        *                   find these attributes from 
        *                   \epoc32\include\f32file.h header file. 
        *                   If the storage is not a filesystem these 
        *                   attributes are ignored.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt SaveL(
            const TDesC8& aContent,
            TDataType& aDataType,
            const TDesC& aName,
            const TUint aAttr );

        /**
        * Copy a file named aFileNameOld to the correct storage using
        * name aNameNew and aFileAttr. If aNameNew is empty, use
        * the old name.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. See 
        * also possible error codes from documenthandler.h header file.
        *
        * @param aFileNameOld   Name of the file being copied.
        * @param aNameNew       Name of the new file. If null, use the 
        *                       old name.
        * @param aDataType      A data type for the file. If empty the 
        *                       DocumentHandler tries to recognize type.
        * @param aAttr          Use these file attributes for saving. 
        *                       ReadOnly, ReadWrite.
        * @return               KErrNone if success. KUserCancel if the user 
        *                       cancelled the operation.
        */
        IMPORT_C TInt CopyL(
            const TDesC& aFileNameOld,
            const TDesC& aNameNew,
            TDataType& aDataType,
            const TUint aAttr );
            
        /**
        * Copy a file with handle aFileOld to the correct storage using
        * name aNameNew and aFileAttr. If aNameNew is empty, use
        * the old name.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. See 
        * also possible error codes from documenthandler.h header file.
        *
        * @param aFileOld       Handle of the file being copied.
        * @param aNameNew       Name of the new file. If null, use the 
        *                       old name.
        * @param aDataType      A data type for the file. If empty the 
        *                       DocumentHandler tries to recognize type.
        * @param aAttr          Use these file attributes for saving. 
        *                       ReadOnly, ReadWrite.
        * @return               KErrNone if success. KUserCancel if the user 
        *                       cancelled the operation.
        */
        IMPORT_C TInt CopyL(
            const RFile& aFileOld,
            const TDesC& aNameNew,
            TDataType& aDataType,
            const TUint aAttr );

        /**
        * Move a file named aFileNameOld to the correct storage using
        * name aNameNew and aFileAttr. Note that file in the old location 
        * (aFileNameOld) will be removed during this operation.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. See 
        * also possible error codes from documenthandler.h header file.
        *
        * @param aFileNameOld   Name of the file being copied.
        * @param aNameNew       Name of the new file. If null, use the 
        *                       default name for this mime-type. 
        * @param aDataType      A data type for the file. If empty the 
        *                       DocumentHandler tries to recognize type.
        * @param aAttr          Use these file attributes for saving. 
        *                       ReadOnly, ReadWrite.
        * @return               KErrNone if success. KUserCancel if the user 
        *                       cancelled the operation.
        * @since Series60 2.8
        */
        IMPORT_C TInt MoveL(
            const TDesC& aFileNameOld,
            const TDesC& aNameNew,
            TDataType& aDataType,
            const TUint aAttr );

        /**
        * Move a file named aFileNameOld to the correct storage using
        * name aNameNew and aFileAttr. This method operates silently, so 
        * nothing will be asked from user. Caller should give root path of 
        * the selected memory. Unique file name will be created automatically 
        * without user interaction. Note that file in the old location 
        * (aFileNameOld) will be removed during this operation. 
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. See 
        * also possible error codes from documenthandler.h header file.
        * 
        * @param aFileNameOld   Name of the file being copied.
        * @param aNameNew       Name of the new file. If null, use the 
        *                       default name for this mime-type. 
        * @param aRootPath      Root path of the selected memory where file 
        *                       should be moved.
        * @param aDataType      A data type for the file. If empty the 
        *                       DocumentHandler tries to recognize type.
        * @param aAttr          Use these file attributes for saving. 
        *                       ReadOnly, ReadWrite.
        * @return               KErrNone if success. 
        * @since Series60 3.0
        */
        IMPORT_C TInt SilentMoveL(
            const TDesC& aFileNameOld,
            const TDesC& aNameNew,
            const TDesC& aRootPath,
            TDataType& aDataType,
            const TUint aAttr );


    public:       // query functions

        /**
        * Is the aDataType supported by the system.
        *
        * @param    aDataType Data type for content.
        *
        * @return   True if there is an application capable of handling
        *           aDataType. False if no application can handle
        *           this mime type.
        */
        IMPORT_C TBool CanHandleL( const TDataType& aDataType );

        /**
        * Is opening of aDataType supported by the system.
        *
        * @param    aDataType Data type for content.
        *
        * @return   True if there is an application capable of handling
        *           aDataType. False if no application can handle
        *           this mime type.
        */
        IMPORT_C TBool CanOpenL( const TDataType& aDataType );

        /**
        * Is saving aDataType supported by the system.
        *
        * @param    aDataType Data type for content.
        *
        * @return   True if there is an application capable of handling
        *           aDataType. False if no application can handle
        *           this mime type.
        */
        IMPORT_C TBool CanSaveL( const TDataType& aDataType );

        /**
        * Get the whole path including filename where the content was saved.
        * If the content was not saved to a file, this function returns
        * a name that represents the saved object.  
        * 
        * It may not be possible to open the object with the returned 
        * value, if it's not a real file in the filesystem. This situation
        * may happen when e.g. the handler application stores it's contents in
        * some weird data structure.
        *
        * @param    aPath The path of the saved content.
        *
        * @return   KErrNone if the path was found. KNotInitialised if the  
        *           handler is not initialised.        
        */
        IMPORT_C TInt GetPath( TDes& aPath );   
        
        /**
        * Get the uid of handler application. In case of media files uid is 
        * Media Gallery's uid. This method should be called only succesfully 
        * completed DocumentHandler operations. 
        *
        * @param    aUid Uid of the handler application for the content. 
        *
        * @return   KErrNone if the uid was found. KNotInitialised if the 
        *           handler is not initialised.        
        * @since Series 60 2.8
        */
        IMPORT_C TInt HandlerAppUid( TUid& aUid );   
        
        /**
        * Set an observer for embedded application exit events. 
        * DocumentHandler will delegate embedding applications exit 
        * events to aObserver if it's not NULL:
        * 
        * @param    aObserver Exit observer
        * @since Series 60 3.0
        */
        IMPORT_C void SetExitObserver( MAknServerAppExitObserver* aObserver );
        
        /**
        * Utility method for appending a correct file name extension for some 
        * content. This method should be called if wanted quarantee that file 
        * extension of aFileName is correct with aDataType. 
        *
        * This method uses internal mapping table to find correct file 
        * extension to aFileName. Mapping table contains mainly extensions
        * and datatypes, which cannot be recognized based on the data it self 
        * (No header information etc.). 
        *
        * This method replaces existing extension with correct one at aFileName 
        * if needed. If aDatatype is not found from mapping table or aDatatype
        * is not supported by any application, aFileName will remain unchanged.
        *
        * @param aFileName  Append extension to this filename. 
        * @param aDataType  The content type of the file.
        * @since Series 60 3.0
        */
        IMPORT_C void CheckFileNameExtension(
            TDes& aFileName,
            const TDataType& aDatatype );
        
        /**
        * Get the RApaLsSession.
        *
        * @return Pointer to RApaLsSession
        */
        RApaLsSession* ApaLs();

        /**
        * Get the exit observer.    
        *
        * @return Pointer to exit observer
        * @since Series 60 3.0
        */
        MAknServerAppExitObserver* ServerAppExitObserver() const;

        /**
        * Get the operation code of the api entry function.
        */
        TDocOperation DocOperation() const;
        
        /** 
        * Close sharable FileSession. 
        */
        void CloseSharableFS();
        
        /**
        * Set temporary file, which will be deleted in destructor.
        */
        void SetTempFile( const TDesC& aTempFile);
        
        /**
        * Utility method to find out if there are any applications that 
        * support progressive downloading for a given data type. 
        *        
        * The decision is based on configuration made in central repository.
        *
        * @param aDataType  The content type of the file.
        * @param aUid  An Uid of the applications for the given data type.
        * @return ETrue if progressive download was supported for the given
        *   data type. Otherwise EFalse.
        * @since Series 60 3.1
        */
        IMPORT_C TBool CanHandleProgressivelyL( 
            const TDataType& aDataType, 
            TUid& aUid );
        
        /**
        * Utility method to provide a list of applications that support 
        * progressive downloading. 
        *
        * The list of applications uids is configured central repository.
        *
        * @param aUidList A list of app Uids
        * @since Series 60 3.2
        */            
        IMPORT_C void GetProgressiveDownloadAppUidsL( RArray<TInt32>& aUidList );            
            
    private:        // New functions

        /**
        * Construct a handler for a given data type. A previous handler will 
        * be destroyed and the new one is constructed.
        *
        * The desicion of which handler implementation to use is
        * based on Apparc's AppForDataType query. If the app uid is
        * found for aDataType and there is a hardcoded handler for it,
        * the right handler will be constucted. If the app uid is not found
        * try to match a data type for some handler. The default handler is
        * constructed if no handler entry is found.
        *
        * @param    aUid UID of the handler application.
        * @return   Error code
        */
        TInt FindHandlerL(
            const TDataType& aDataType,
            const TUid& aUid);

        /**
        * Try to find a handler for aUid. Constructs iHandler if found.
        *
        * @param aDataType A data type to pass to a handler
        * @param aUid An uid to search a handler for
        */
        void FindHandlerByUidL( 
            const TUid& aUid, 
            const TDataType& aDataType);

        /**
        * Try to find a handler for aDataType. Constructs iHandler if found.
        *
        * @param aUid      An Uid for handler application.
        * @param aDataType A data type to search a handler for.
        */
        void FindHandlerByMimeTypeL( 
            const TUid& aUid, 
            const TDataType& aDataType);
                                
        /**
        * Makes all the nesessary security checks and maps aDataType to 
        * an UID of the handler application. If system is not able to handle 
        * the content type, or file is DRM protectedfile, aDataType and aUid  
        * will left empty.
        *
        * @param aFileName  Filename
        * @param aDataType  Data type for the file
        * @param aUid       An application UID will be returned if a handler 
        *                   was found.
        * @return           KErrNone if success, error code if failure.
        */
        TInt RecognizeAndCheckFileL(
            const TDesC& aFileName,
            TDataType& aDataType,
            TUid& aUid );     
            
        /**
        * Makes all the nesessary security checks and maps aDataType to 
        * an UID of the handler application. If system is not able to handle 
        * the content type, or file is DRM protectedfile, aDataType and aUid  
        * will left empty.
        *
        * @param aFileHandle Filehandle
        * @param aDataType  Data type for the file
        * @param aUid       An application UID will be returned if a handler 
        *                   was found.
        * @return           KErrNone if success, error code if failure.
        */
        TInt RecognizeAndCheckFileL(
            RFile& aFileHandle,
            TDataType& aDataType,
            TUid& aUid );     

        /**
        * This method lists all supported mime-types of system using 
        * RDebug::Print. On UREL mode this method do nothing.
        */
        void ListSupportedMimeTypesL();
		
        /**
        * Prohibit the assignment operation
        */
        CDocumentHandler operator=( const CDocumentHandler& )  const;
        
        /**
        * Convert a hex string to 32-bit integer.
        */        
        TInt ConvertHexStringToInt32( 
            const TDesC& aHexString, 
            TInt32& aInt );               

    private:          // Data

        /**
        * The entry operation. Handlers can query about the entry function
        * when they need to implement some special behaviour.
        */
        TDocOperation iOperation;

        /**
        * A handler providing operations. 
        */
        CDocHandlerBase* iHandler;

        /**
        * A ApaLs session client.
        */
        RApaLsSession* iApaLs;
        
        /**
        * Notify embedded app's exit event to this observer.
        */
        MAknServerAppExitObserver* iServerAppExitObserver;
        
        /**
        * Holds sharable Fileserver session
        */
        RFs iSharableFS;

        /**
        * Parameter list created using InParamListL function
        */
        CAiwGenericParamList* iInParams;
        
        /**
        * Filename of temporary saved file. This file will be deleted 
        * in destructor of documenthandler
        */
        TFileName iTempFileName;     
        
    };

#endif              // DOCUMENTHANDLER_H

// End of File
