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
* Description:  Defines midlet handler class for document handler.
*
*/


#ifndef CDOCMIDLETHANDLER_H
#define CDOCMIDLETHANDLER_H

//  INCLUDES
#include "DocDefaultHandler.h"  

// FORWARD DECLARATIONS

// CONSTANS

// CLASS DECLARATION

/**
* This class is Java Midlet handler for midlets which do support 
* CDMA Sprint extensions to Application Management System (AMS). 
*
*/
NONSHARABLE_CLASS(CDocMidletHandler) : public CDocDefaultHandler
    {

    public:        // Constructors and destructor

        /**
        * Two-phased constructor. 
        *
        * @param aDataType      Data type
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        *
        * @return               Constructed CDocMidletHandler
        */
        static CDocMidletHandler* NewL(
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
        * @return               Constructed CMidletHandler
        */
        static CDocMidletHandler* NewLC(
            const TDataType& aDataType, 
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher );

        /**
        * Destructor
        */
        ~CDocMidletHandler();

    public:       // New functions

        /**
        * Method for checking if given UID belongs to a Java Midlet.
        *
        * @param aUid           UID of some app
        *
        * @return               ETrue if given UID belongs to a midlet, 
        *                       otherwise EFalse.
        */
        static TBool IsMidlet(const TUid& aUid);

    public:       // Functions from base classes

        /**
        * From CDefaultHandler OpenFileEmbedded(). Calls OpenFile()
        * because midlet is not embeddable.
        * @return An error code
        */
        TInt OpenFileEmbeddedL();

        /**
        * From CDefaultHandler OpenFile(). 
        * Launches midlet normally and passes required parameter(s).
        * @return An error code
        */
        TInt OpenFileL();

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
        CDocMidletHandler(
            const TDataType& aDataType,
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher );

        /**
        * C++ copy constructor

        */
        CDocMidletHandler( const CDocMidletHandler& );

        /**
        * Prohibit the assignment operation
        */
        CDocMidletHandler operator=( const CDocMidletHandler& )  const;

    protected:
        
    private:          // Data

    };

#endif      // CDOCMIDLETHANDLER_H

// End of File
