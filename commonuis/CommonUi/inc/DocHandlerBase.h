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
* Description:  Header file for base class for content handlers.  
*
*/


#if !defined(HANDLERBASE_H)
#define HANDLERBASE_H

// FORWARD DECLARATIONS
class CAiwGenericParamList;

/**
* Virtual interface class for content handlers. All handlers have to be
* derived from this class. There are no implemented functions or member data.
* The implementor can also extend the CDocDefaultHandler class, which
* is a implementation of the standard epoc-style.
*
* This interface allows different kinds of content storages to be used. The
* implementor can use e.g. DirectFileStorage or any other method of saving
* the content.
*
* If the concrete handler is capable of handling several data types, it
* maybe necessary to deliver the data type also. The data type of a
* content can be delivered to the concrete handler by the construction
* time.
*/
class CDocHandlerBase : public CBase
    {
    public:

        /**
        * Open an application standalone. 
        *        
        * @param aFileHandle Filehandle of file which should be opened.
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        *
        * @since Series60 3.0
        */
        virtual TInt OpenFileL(RFile& aFileHandle) = 0;
        
        /**
        * Open an application embedded. 
        *
        * @param aFileHandle Filehandle of file which should be opened.
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        *
        * @since Series60 3.0
        */
        virtual TInt OpenFileEmbeddedL(RFile& aFileHandle) = 0;

        /**
        * Save the content to process private path for temporarily. Use
        * the access attribute given if appropriate.
        *
        * @param aContent Content buffer
        * @param aAttr  Access attribute defined in  
        *               \epoc32\include\f32file.h.
        * @param aFileName Filename of saved file
        *
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        * @since 3.0
        */
        virtual TInt SaveTempFileL( const TDesC8& aContent, const TUint aAttr,
            TDes& aFileName ) = 0;

        /**
        * Copy or move (based on DocOperation) content from a file set by the
        * SetSrcFileName(const TDesC &aName) -function to the application
        * spesific place. Use the access attribute given if appropriate. Possible
        * operations are EDocCopy, EDocMove and EDocSilentMove
        *
        * @param aAttr Access attribute defined in  
        *              \epoc32\include\f32file.
        *
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        */
        virtual TInt CopyOrMoveL( const TUint aAttr ) = 0;
        
        /**
        * Copy a filehandle to the application spesific directory. Use the 
        * access attribute given if appropriate.
        *
        * @param        aAttr File attributes.
        * @param        aSourceFile File handle to copied
        *
        * @return       KErrNone if success. If fail, a fail reason
        *               constant declared in CDocumentHandler.h
        */
        virtual TInt CopyHandleL( const RFile& aSourceFile, const TUint aAttr ) = 0;

        /**
        * Set the destination of the content.
        *
        * If you want to save or copy the content with a different name
        * than the original, you have to set the destination name with
        * this function. The name can be a file name or any other
        * textual name depending on the storage type used.
        *
        * @param aName Name of the destination
        *
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        */
        virtual TInt SetDestName( const TDesC& aName ) = 0;

        /**
        * Set the source file where the content must be fetched.
        *
        * @param aFileName File name
        *
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        */
        virtual TInt SetSrcFileName( const TDesC& aFileName ) = 0;

        /**
        * Set the root path of the memory where the file should be moved.
        * This method is used only in case of SilentMoveL. 
        *
        * @param aRootPath Root path of memory
        *
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        * @since 3.0
        */
        virtual TInt SetRootPath( const TDesC& aRootPath ) = 0;

        /**
        * Get the path where the content were saved. If the storage
        * is not a file based the path can be also any other
        * textual presentation of an object.
        *
        * This function is called e.g. when opening a buffer. The buffer
        * is saved first. After saving we have to know where we saved it
        * in order to be able to open it.
        *
        * @param aPath Path to the object
        *
        */
        virtual void GetPath( TDes& aPath ) const = 0;

        /**
        * Get the Uid of handler application. 
        *
        * @param aUid Uid of the handler application. In case of Media files
        * this is MediaGallery's Uid.
        *
        * @since 2.8
        */
        virtual void HandlerAppUid( TUid& aUid ) const = 0;

        /**
        * Access a status code of the handler.
        *
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        */
        virtual TInt Status() const = 0;

        /**
        * Is the handler capable of opening the content
        * @param aDataType  Data type for content to be launched
        *
        * @return           ETrue if yes, else EFalse 
        */
        virtual TBool CanOpen() const = 0;

        /**
        * Is the handler capable of saving the content
        * @param aDataType  Data type for content to be saved
        *
        * @return           ETrue if yes, else EFalse 
        */
        virtual TBool CanSave() const = 0;
     
        /**
        * Utility method for deleting temporary file
        * CDocumentHandler will use this method for deleting temporary file
        *
        * @since Series60 3.0
        * @param aFileName a file to be deleted
        */
        virtual void DeleteFile(const TDesC& aFileName) = 0;
     
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
        virtual void CheckFileNameExtensionL(
            TDes& aFileName,
            const TDataType& aDatatype ) = 0;
     
        /**
        * Creates parameter store for given parameter list.
        * These parameters will be passed to embedded application.
        *
        * @since Series60 3.0
        * @param aParams a parameter list to be passed.
        */
        virtual void AddToParamListL(const CAiwGenericParamList& aParams) = 0;      

        /**
        * Return a list of possible output parameters set by embedded application.
        *
        * @since Series60 3.0
        * @param aParams a list of output parameters.
        */
        virtual const CAiwGenericParamList* OutputParamsL() = 0;
    };

#endif // !defined(HANDLERBASE_H)

// End of File
