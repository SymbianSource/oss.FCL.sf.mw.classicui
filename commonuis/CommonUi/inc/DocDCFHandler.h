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
* Description:  Definition of DCF handler class.
*
*/


#ifndef DOCDCFHANDLER_H
#define DOCDCFHANDLER_H

#include <apmstd.h>          
#include <apacln.h>             // MapaEmbeddedDocObserver
#include "DocumentHandler.h"
#include "DocDefaultHandler.h"

// CONSTANTS

// FORWARD DECLARATIONS
class DRMCommon;
class CBufStore;
class CStreamDictionary;

NONSHARABLE_CLASS(CDocDCFHandler) : public CDocDefaultHandler
    {
    public:

        /**
        * Two-phased constructor. 
        *
        * @param aDataType      Data type
        * @param aOperation     Operation
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        *
        * @return Constructed CDocDcfHandler
        */
         static CDocDCFHandler* NewL(
            const TDataType& aDataType,
            TDocOperation aOperation,
            const TUid& aUid, 
            CDocumentHandler* aDocDispatcher);
                 
        /**
        * EPOC constructor. (Base construction for subclasses.)
        */     
        void ConstructL();
        
        /**
        * Destructor.
        */
        ~CDocDCFHandler();
 
        /**
        * Open an application standalone. 
        *
        * @param aFileHandle File to open 
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        * @since Series60 3.0
        */
        TInt OpenFileL(RFile& aFileHandle);
        
        /**
        * Open an application embedded. 
        *
        * @param aFileHandle File to open 
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        * @since Series60 3.0
        */
        TInt OpenFileEmbeddedL(RFile& aFileHandle);

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
        TInt CopyOrMoveL( const TUint aAttr );

        /**
        * Copy a file to the correct directory. 
        *
        * @param        aAttr File attributes.
        * @param        aSourceFile File handle to copied
        *
        * @return       KErrNone if success. If fail, a fail reason
        *               constant declared in CDocumentHandler.h
        */
        TInt CopyHandleL( const RFile& aSourceFile, const TUint aAttr );

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
        void GetPath( TDes& aPath ) const;

        /**
        * Get the Uid of handler application. 
        *
        * @param aUid Uid of the handler application. In case of Media files
        * this is MediaGallery's Uid.
        */
        void HandlerAppUid( TUid& aUid ) const;

        /**
        * Is the handler capable of opening the content
        * @param aDataType  Data type for content to be launched
        *
        * @return           ETrue if yes, else EFalse 
        */
        TBool CanOpen() const;

        /**
        * Is the handler capable of saving the content
        * @param aDataType  Data type for content to be saved
        *
        * @return           ETrue if yes, else EFalse 
        */
        TBool CanSave() const;

    private:
    
        /**
        * C++ constructor.
        *
        * @param aDataType      A mime type for the content
        * @param aOperation     Operation
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        */
        CDocDCFHandler(  
            const TDataType& aDataType,
            TDocOperation aOperation,
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher);
        
        /**
        * Handles DCF file opening.
        *
        * @param aFileHandle File which needs opening.
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        * @since Series60 3.0
        */
        TInt OpenDCFFileL( RFile& aFileHandle );
        
        /**
        * Handles DCF file copying.
        *
        * @param aUseHandle Do we operate with filehandle
        * @param aFileHandle File which needs copying/moving
        * @param aAttr      Attributes of file 
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        * @since Series60 3.0
        */
        TInt CopyDCFFileL( TBool aUseHandle, 
                           RFile& aFileHandle, 
                           const TUint aAttr);
        
        /**
        * Set the data type of the content. 
        *
        * @param aMIMEType  A data type in descriptor.
        */  
        void SetDataTypeL( HBufC8* MIMEType );

        /**
        * Convert DRM error code to DocumentHandler error code.
        *
        * @param aDrmError  DRM error
        * @return           General error code 
        */ 
        TInt ConvertErrorCode(TInt aDrmError);

    private:
        DRMCommon* iDRMCommon;
        TDocOperation iEntryFunc;
        CDocumentHandler* iDocHandler;
    };

#endif      // DOCDCFHANDLER_H
            
// End of File
