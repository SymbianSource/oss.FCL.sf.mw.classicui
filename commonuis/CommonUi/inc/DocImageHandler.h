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
* Description:  Defines image handler class for document handler.
*
*/


#ifndef CDOCIMAGEHANDLER_H
#define CDOCIMAGEHANDLER_H

//  INCLUDES
#include "DocDefaultHandler.h"  

// FORWARD DECLARATIONS

// CONSTANS

// CLASS DECLARATION

/**
*  Handler for image types.
*  Extends the default handler only by save and copy function. 
*/
NONSHARABLE_CLASS(CDocImageHandler) : public CDocDefaultHandler
    {

    public:        // Constructors and destructor

        /**
        * Two-phased constructor. 
        *
        * @param aDataType      Data type
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        *
        * @return               Constructed CDImageHandler
        */
        static CDocImageHandler* NewL(
            const TDataType& aDataType,
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher );

        /**
        * Two-phased constructor. 
        *
        * @param aDataType      Data type
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        *
        * @return               Constructed CImageHandler
        */
        static CDocImageHandler* NewLC(
            const TDataType& aDataType, 
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher );

        /**
        * Destructor
        */
        ~CDocImageHandler();

    public:       // New functions

    public:       // Functions from base classes

        /*
        * Always hide the file name extension as the UI specification
        * says. 
        *
        * @return ETrue
        */
        TBool HideFileExtension();

    private:          // New functions

        /**
        * Epoc constructor
        */
        void ConstructL();
        
        /**
        * Constructor
        * @param aDataType      Data type
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        */
        CDocImageHandler(
            const TDataType& aDataType,
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher );

        /**
        * C++ copy constructor

        */
        CDocImageHandler( const CDocImageHandler& );

        /**
        * Prohibit the assignment operation
        */
        CDocImageHandler operator=( const CDocImageHandler& )  const;

    protected:
        
        /**
        * Populate appInfo with ImageViewer's information.
        */
        void PopulateAppInfo();

        /**
        * The maximum length of image names in MediaGallery's
        * folder. The lenght is hardcoded as there was not
        * any suitable place to retrieve it on runtime.
        *
        * @return 40
        */
        TInt MaxNameLen();

    private:          // Data

    };

#endif      // CDOCIMAGEHANDLER_H

// End of File
