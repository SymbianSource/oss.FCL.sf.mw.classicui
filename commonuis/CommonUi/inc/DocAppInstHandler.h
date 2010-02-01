/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  header file for application installer handler.  
*
*/

#ifndef APPINSTHANDLER_H
#define APPINSTHANDLER_H

//  INCLUDES
#include "DocDefaultHandler.h"
#include <SWInstApi.h>

// FORWARD DECLARATIONS
class CDocAppInstLauncher;

/**
* Handler for application intaller packages 
*/
NONSHARABLE_CLASS(CDocAppInstHandler) : public CDocDefaultHandler
    {
    public:        // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CDocAppInstHandler* NewL(
            const TDataType& aDataType,
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher,
            TDocServiceMode aServiceMode );

        /**
        * Destructor.
        */
        virtual ~CDocAppInstHandler();


    protected:        // New functions

    
        /**
        * Open installable file. 
        * 
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        */
        TInt OpenFileEmbeddedL(RFile &aFileHandle);
        
        /**
        * Open installable file. 
        * 
        * @return           KErrNone if success. If fail, a fail reason 
        *                   constant declared in CDocumentHandler.h
        */
        TInt OpenFileL(RFile &aFileHandle);
        
        /**
        * Creates parameter store (iParamPckg) for given parameter list.
        * 
        * @param aParams a parameter list to be passed.
        */
        void AddToParamListL(const CAiwGenericParamList& aParams);

    
    private:
    
        /**
        * C++ default constructor.
        */
        CDocAppInstHandler(
            const TDataType& aDataType,
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher,
            TDocServiceMode aServiceMode ); 
        
        /**
        * C++ copy constructor
        */
        CDocAppInstHandler( const CDocAppInstHandler& );

        /**
        * Prohibit the assignment operation
        */
        CDocAppInstHandler operator=( const CDocAppInstHandler& )  const;
        
        /*
        * Helper class which launches installer asyncronously
        */
        CDocAppInstLauncher* iLauncher;     
        
        /*
        * If ETrue, we call Installer with parameters
        */
        TBool iCallWithParams;         
        
        /*
        * Parameters for Application installer
        */ 
        SwiUI::TInstallReqPckg* iParamPckg;

        /*
        * Heap buffer the URL
        * Owned
        */
        HBufC*  iHeapURL;

        /*
        * Heap buffer the iParamPckg + 4 byte + URL(iHeapURL)
        * Owned
        */
        HBufC8* iParamDescriptor;

        /*
        * indicate if we can use the iParamDescriptor
        */
        TBool   iUseDescriptor;

    };

#endif      // APPINSTHANDLER_H

// End of File
