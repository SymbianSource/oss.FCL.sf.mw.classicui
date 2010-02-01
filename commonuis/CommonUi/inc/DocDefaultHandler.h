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
* Description:  Concrete implementation of the default (Epoc way) document handling.
*                Called and constructed by CDocumentHandler.
*
*/


#if !defined DEFAULTHANDLER_H
#define DEFAULTHANDLER_H

// INCLUDE FILES

#include <apgcli.h>             // RApaLsSession
#include <s32mem.h>             // For TStreamId

#include "DocumentHandler.h"    // Common Constants etc.
#include "DocHandlerBase.h"     // Base class
#include "DocConstants.h"       // Constants of DocumentHandler

#include <AiwGenericParam.hrh>	// Generic parameters
#include <AknServerApp.h>       // MAknServerAppExitObserver
#include <AknOpenFileService.h> // CAknOpenFileService

#include "AiwCommon.h"          // CAiwGenericParamList


// CONSTANTS

// FORWARD DECLARATIONS
class CDirectFileStore;
class CEikDocument;
class CIdle;

//  CLASS DECLARATION
/**
* Default (Epoc-style) implementation of CHandlerBase class.
* Constructed and called from CDocumentHandler.
*/
NONSHARABLE_CLASS(CDocDefaultHandler) :
            public CDocHandlerBase,       
            public MAknServerAppExitObserver
    {

    public:           // Constructors and destructor

        /**
        * Two-phased constructor. Leaves the contructed instance in to the
        * clean up stack.
        *
        * @param aDataType      Data type
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        * @param aServiceMode   Are we able to Save, Open or do both
        *
        * @return Constructed CDefaultHandler
        */
        static CDocDefaultHandler* NewLC(
            const TDataType& aDataType,
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher,
            TDocServiceMode aServiceMode );

        /**
        * Two-phased constructor.
        *
        * @param aDataType      Data type
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        * @param aServiceMode   Are we able to Save, Open or do both
        *
        * @return Constructed CDefaultHandler
        */
        static CDocDefaultHandler* NewL(
            const TDataType& aDataType,
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher,
            TDocServiceMode aServiceMode );

        /**
        * Destructor.
        */
        virtual ~CDocDefaultHandler();

    protected:

        /**
        * C++ constructor.
        *
        * @param aDataType      A mime type for the content
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        * @param aServiceMode   Are we able to Save, Open or do both
        */
        CDocDefaultHandler(
            const TDataType& aDataType,
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher,
            TDocServiceMode aServiceMode );

        /**
        * EPOC constructor. (Base construction for subclasses.)
        */
        void BaseConstructL();

    private:

        /**
        * C++ copy constructor
        */
        CDocDefaultHandler( const CDocDefaultHandler& );

    public:           // Functions from CHandlerBase

        /**
        * Get Status code
        *
        * @return       A Status code for the latest operation.
        */
        TInt Status() const;

        /*
        * Get a path where the content was saved.
        *
        * @param aPath  Return full file name with a path. If the content
        *               was not saved into a file, returns some string
        *               representing the object.
        *
        */
        void GetPath( TDes& aPath ) const;

        /**
        * Get the Uid of handler application. 
        *
        * @param aUid Uid of the handler application. In case of 
        *             media files this is MediaGallery's Uid.
        */
        void HandlerAppUid( TUid& aUid ) const;

        /**
        * By default the saving is possible with the default handler.
        *
        * @return       Always ETrue
        */
        TBool CanSave() const;

        /**
        * By default the launching is possible with the default handler.
        *
        * @return       Always ETrue
        */
        TBool CanOpen() const;

        /**
        * Copy/Move a file to the correct directory. Correct operation
        * is decided based on DocOperation(). Possible operations are
        * EDocCopy, EDocMove and EDocSilentMove.
        *
        * @param        aAttr File attributes.
        *
        * @return       KErrNone if success. If fail, a fail reason
        *               constant declared in CDocumentHandler.h
        */
        virtual TInt CopyOrMoveL( const TUint aAttr );
        
        /**
        * Copy a file to the correct directory. 
        *
        * @param        aAttr File attributes.
        * @param        aSourceFile File handle to copied
        *
        * @return       KErrNone if success. If fail, a fail reason
        *               constant declared in CDocumentHandler.h
        */
        virtual TInt CopyHandleL( const RFile& aSourceFile, const TUint aAttr );

        /**
        * Save aContent to the correct directory.
        *
        * @param aContent A content buffer
        * @param aAttr    File attributes defined in
        *                 \epoc32\include\f32file.h
        * @param aFileName Filename of saved file
        *
        * @return       KErrNone if success. If fail, a fail reason
        *               constant declared in CDocumentHandler.h
        */
        TInt SaveTempFileL( 
            const TDesC8& aContent, 
            const TUint aAttr,
            TDes& aFileName );

        /**
        * Open a file standalone
        *
        * @param aFileHandle File to open 
        * @return       KErrNone if success. If fail, a fail reason
        *               constant declared in CDocumentHandler.h
        */
        virtual TInt OpenFileL(RFile& aFileHandle);

        /**
        * Open a file embedded
        *
        * @param aFileHandle File to open  
        * @return       KErrNone if success. If fail, a fail reason
        *               constant declared in CDocumentHandler.h
        */
        virtual TInt OpenFileEmbeddedL(RFile& aFileHandle);

        /**
        * Set source file name.
        *
        * @param aFileName A source file name with full path
        *
        * @return       KErrNone if success. If fail, a fail reason
        *               constant declared in CDocumentHandler.h
        */
        TInt SetSrcFileName( const TDesC& aFileName );

        /**
        * Set destination file name.
        *
        * @param aFileName A destination file name without path
        *
        * @return       KErrNone if success. If fail, a fail reason
        *               constant declared in CDocumentHandler.h
        */
        TInt SetDestName( const TDesC& aFileName );

        /**
        * Set the root path of the memory where the file should be moved.
        * This method is used only in case of SilentMoveL. 
        *
        * @param aRootPath Root path of memory
        *
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        */
        TInt SetRootPath( const TDesC& aRootPath );

        /**
        * Creates parameter store for given parameter list.
        * These parameters will be passed to embedded application.
        *
        * @param aParams a parameter list to be passed.
        */
        virtual void AddToParamListL(const CAiwGenericParamList& aParams);

        /**
        * Returns list of output parameters.
        *
        * @param aParams a parameter list to be passed.
        */
        const CAiwGenericParamList* OutputParamsL();
        
        /**
        * Utility method for deleting temporary file
        * CDocumentHandler will use this method for deleting temporary file
        *
        * @param aFileName a file to be deleted
        */
        void DeleteFile(const TDesC& aFileName);
        
        /**
        * Append a correct file name extension for some content. 
        * This is needed, because we want quarantee that file extension
        * is correct with mime-type. Some content types cannot be recognized
        * based on the data it self. (No header information etc.)
        *
        * See related contents and extensions from documenthandlerui.rss:
        * r_extension_guaranteed_mime_types and r_extension_guaranteed_extensions
        *
        * @param aFileName  Append extension to this filename.
        * @param aDataType  The content type of the file.
        */
        void CheckFileNameExtensionL(
            TDes& aFileName,
            const TDataType& aDatatype );


    protected:        // New functions

        /**
        * Set the data type of the content. 
        *
        * @param aDataType A data type.
        */
        void SetDataType( const TDataType& aDataType );

        /**
        * Get the data directory. Leaves on errors.
        *
        * @param aDataType A data type
        * @param aUid      An application uid
        * @param aPath     A path to the data directory. Either main doc dir or
        *                  a mime type specific directory.
        * @param aDataSize Size of data
        * @return          Error code
        */
        virtual TInt GetDataDirL(
            const TDataType& aDataType,
            const TUid& aUid,
            TDes& aPath,
            TInt aDataSize);

        /**
        * Check disk space for file, generate filename and
        * and show save as query to user before copying the file.
        * CopyOrMoveL and CopyHandleL uses this function.
        *
        * @param aDataSize Size of data in bytes
        * @return          Error code
        */
        virtual TInt CopyChecksAndQueriesL(TInt aDataSize);

        /**
        * Check disk space for file and generate filename.
        * SaveTempFileL uses this function.
        *
        * @param aContent  Data to save
        *
        * @return          Error code
        */
        virtual TInt SaveChecksL(const TDesC8& aContent);

        /**
        * Query user to overwrite or rename an existing file.
        *
        * @param aPath     A absolute path to the file. Will be
        *                  modified to an unique name.
        *                  E.g. from data.dat to data(01).dat etc.
        * @return          EDocFileCancelWrite - User canceled
        *                  EDocFileOverWrite   - Overwrite
        *                  EDocFileRenameNew   - New name for content
        */
        TDocSaveAsResult SaveAsQueryL( TFileName& aPath );

        /**
        * Launch a CAknQueryDialog dialog.
        *
        * @param aDialogTypeResID   Resource ID for the dialog.
        * @param aStringResId       String resource ID for the prompt.
        * @param aFileName          The resource file name.
        *
        * @return                   Error value
        */
        TInt RunQueryDialogL(
            TInt aDialogTypeResID,
            TInt aStringResID,
            const TDesC& aFileName );

        /**
        * Generate a file name for a nameless buffer. First try to load
        * default document file name from handler application's resources.
        * If that fail read a general name from the docHadler's resources.
        *
        * @param aUid       An UID for handler application.
        * @param aFileName  The generated file name will be in here
        * @param aDataType  A data type
        * @param aDataSize  Size of data
        * @return           Error code
        */
        virtual TInt GenerateFileNameL(
            const TUid& aUid,
            TDes& aFileName,
            const TDataType& aDataType,
            TInt aDataSize);

        /**
        * Leave if the flash disk space would be under critical level.
        *
        * @param bytes      Number of bytes to be writen.
        */
        void CheckDiskspaceL( TInt bytes );

        /**
        * Check if the file is in use.
        *
        * @param aFileName  File name
        *
        * @return           ETrue if the file is locked or in use, else EFalse.
        */
        TBool IsFileInUse( const TDesC& aFileName );

        /**
        * Check if the file is writable.
        *
        * @param aFileName  File name
        *
        * @return           ETrue if the file is writable
        *                   and not in use, else EFalse.
        */
        TBool IsFileWritableL( const TDesC& aFileName );

        /**
        * Run query dialog for asking user if
        * he wants to rename the file.
        *
        * @param aName      File name
        *
        * @return           ETrue if yes, else EFalse.
        */
        TBool QueryRenameL( const TDesC& aName );

        /**
        * Run query dialog for asking user if
        * he wants to overwrite the old file.
        *
        * @param aName      File name
        *
        * @return           ETrue if yes, else EFalse.
        */
        TBool QueryOverWriteL( const TDesC& aName );

        /**
        * Run query dialog for asking the new name for a file
        *
        * @param aName      Old file name
        * @param aMaxLen    Max name length
        *
        * @return           ETrue if user pressed ok, EFalse if cancel
        */
        TBool QueryNewNameL( TFileName& aName, const TInt aMaxLen );

        /**
        * Creates a new name (based on existing name) without asking 
        * anything from user.
        */
        void GenerateTempFileNameL( TFileName& aName, const TInt aMaxLen );

        /**
        * Get the operation
        */
        TDocOperation DocOperation() const;

        /**
        * Set and return a SetAndReturnStatus code for the latest operation.
        *
        * @param aErrorCode Any error code defined in global Epoc headers of
        *        DocumentHandler specific error code.
        * @return The same error code
        */
        TInt SetAndReturnStatus( const TInt aErrorCode );

        /**
        * Construct a correct application information data. I.e. Construct
        * iAppInfo member variable. Special handlers should override this
        * function if the handler application is not the same as the viewer
        * application. E.g. Mediagallery vs. ImageViewer.
        * This function is called from BaseConstructL().
        */
        virtual void PopulateAppInfo();

        /**
        * Construct a correct application information data defined by aUid.
        * @param
        */
        void PopulateAppInfo( const TUid& aUid );

        /**
        * Maximum length for the file name and extension.
        *
        * @return Length
        */
        virtual TInt MaxNameLen();

        /**
        * Is the operation for viewing. 
        *
        * @param aOperation One of the API operations.
        *
        * @return ETrue if yes, otherwise EFalse.
        */
        virtual TBool IsViewerOperation( TDocOperation aOperation );

        /**
        * Is the confirmation note allowed.
        *
        * @return ETrue if yes, otherwise EFalse.
        */
        virtual TBool IsConfNoteAllowed();

        /**
        * Should the naming dialog hide the file name extension.
        *
        * @return Allways EFalse
        */
        virtual TBool HideFileExtension();

        /**
        * Replace the filename extension with aExt. If there
        * is no previous extension just append aExt.
        *
        * @param aName The file name in descriptor.
        * @param aExt  The extension
        */
        void ReplaceExtension( TDes& aName, const TDesC& aExt );

        /**
        * Add the Document Handler's resources to resource pool.
        * @see RemoveResources
        */
        void AddResourcesL();

        /**
        * Remove the Document Handler's resources from resource pool.
        * @see AddResourcesL
        */
        void RemoveResources();

        /**
        * Queries if given parameter type is already in input param list.
        *
        * @return ETrue if given parameter type is already in list.
        */
        TBool IsParameterAlreadyInList(TGenericParamId aId);
        
        /**
        * Finds out wheter this data type can be stored
        * to MMC. This information can be found from
        * resource file by Uid value.
        */
        TBool CanBeSavedToMmcL();

        /**
        * Internal helper function needed for parsing filenames from urls.
        */
        void ReverseSlashes(TDes& aString);

        /**
        * Get folder for given datatype. Default folder for default datatypes
        * are defined at documenthandlerui.rss.
        */
        TBool GetDefaultFolderForDataTypeL(const TDataType& aDataType, TDes& result);

        /**
        * Notifies mediagallery that its content may have been changed.
        */
        void UpdateMediaGalleryIfNeededL();
        
        /**
        * Notifies DCF Repository about new file
        */
        void UpdateDCFRepositoryL();
        
        /**
        * Forwards server application exit to registered listeners.
        */   
        void HandleServerAppExit(TInt aReason);

        /**
        * Returns ETrue if data is for installer.
        */
        TBool IsInstallerData() const;
        
        /**
        * Initialize aReader with aResourceID. Does not need access to CCoeEnv.
        */
        void CreateDocResourceReaderLC(TResourceReader& aReader, TInt aResourceID);

    private:

        /**
        * Prohibit the assignment operator
        */
        CDocDefaultHandler operator=( const CDocDefaultHandler& );

        /**
        * Set temporary path to aPath.
        */
        TInt SetTemporaryPathL(TInt aDataSize, TDes& aPath, TBool aPrivate);
        
        /**
        * Check if it is allowed to save content to MMC. Save result
        * to iMMCSaveAllowed member variable.
        */
        void IsMMCSaveAllowedL(const TDesC& aSourceFile);
        
        /**
        * Check if MMC card is locked        
        */
        TBool IsMMCLocked();
        
        /**
        * Mount MMC drive.        
        */
        TInt TryMountMMC();
        
        /**
        * Check if it is allowed to save content to MMC. Save result
        * to iMMCSaveAllowed member variable.
        */
        void IsMMCSaveAllowedL(const RFile& aSourceFile);
        
        /**
        * Used for notifying server app exit with CIdle when
        * OpenFileEmbedded operation has actually opened stand-alone.
        */
        static TInt IdleNotifyServerAppExit( TAny* aParam );
        
        /**
        * Finds correct text for Save confirmation note.
        *
        * @param aText result of the query will be stored here.
        */
        void ConfirmationNoteTextL( TPtr& aText );
        
        /**
        * Finds correct text for Save wait note.
        *
        * @param aText result of the query will be stored here.
        */        
        void WaitNoteTextL( TPtr& aText );
        
        /**
        * Resolve correct caption text for notes.
        *
        * @param aCaption result will be stored here.
        */  
        void ResolveCaptionName( TApaAppCaption& aCaption );
#ifdef RD_MULTIPLE_DRIVE 
         /**
         * check to see if the content can only be saved to Phone memory
         *
         * @param 
         */        
        TBool CanOnlyBeSavedToPhoneMemoryL();  
        /**
         * gets the number of system drives available in phone including phone memory
         * This should not be called when RD_MULTIPLE_DRIVE flag is diabled
         * @param 
         */       
        TInt GetAvailableDrivesCountL();
        /**
         * check drive availability ie is it available for user read/write operations
         * This should not be called when RD_MULTIPLE_DRIVE flag is diabled
         * @param 
         */  
        TBool IsDriveAvailableL(const TInt & aDriveNumber);
#endif
    protected:

        /*
        * Application list server session client
        */
        RApaLsSession* iApaLs;

        /**
        * Data type of the content
        */
        TDataType iDataType;

        /**
        * Destination filename
        */
        TFileName iDestFile;

        /**
        * DocumentHandler (Dispatcher object)
        */
        CDocumentHandler* iDocDispatcher;

        /**
        * FileManager
        */
        CFileMan* iFileManager;

        /**
        * FileServer
        */
        RFs iFs;

        /**
        * Is the content saved to temp dir. Remember to delete temp files!
        */
        TBool iSavedAsTemp;

        /**
        * Flag for service mode.
        */
        TDocServiceMode iServiceMode;

        /**
        * Source filename
        */
        TFileName iSourceFile;

        /**
        * Request status for the latest operation.
        */
        TInt iStatus;

        /**
        * Handler applications UID
        */
        TUid iUid;

        /**
        * Application information
        */
        TApaAppInfo iAppInfo;

        /**
        * Is the exit already notified.
        */
        TBool iExitNotified;

        /**
        * Generic param list for parameter passing
        */
        CAiwGenericParamList* iAiwParams;

        /**
        * Generic param list for parameter passing
        */
        CAiwGenericParamList* iOutAiwParams;

        /**
        * Handle to open file service framework.
        */
        CAknOpenFileService* iOpenService; 

        /**
        * List of mime types whose extension will be overriden when saved.
        */
        CDesCArrayFlat* iMimeExtensions;

        /**
        * List of extensions mapping to iMimeExtensions list.
        */
        CDesCArrayFlat* iExtensions;

        /**
        * Is data media gallery data.
        */
        TBool iMediaGalleryData;

        /**
        * Root path of memory. This variable is used only in case of SilentMoveL.
        */
        TBuf<32> iRootPath;
        
        /**
        * Is save to MMC allowed for DRM encrypted content.
        */
        TBool iMMCSaveAllowed;

        /**
        * Used for notifying server app exit with CIdle when
        * OpenFileEmbedded operation has actually opened stand-alone.
        */
        CIdle* iIdle;        
    };

#endif // !defined DEFAULTHANDLER_

// End of File
