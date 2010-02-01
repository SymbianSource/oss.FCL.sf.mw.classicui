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
* Description:  Header file for game data handler.  
*
*/


#ifndef CDOCGAMEHANDLER_H
#define CDOCGAMEHANDLER_H

//  INCLUDES

#include "DocDefaultHandler.h"

const TInt32      KMaxGameEngineDataID( 1000 );
const TInt      KGameEngineUID( 0x101F5EDA );

_LIT( KGDCount, "GDCount");

/**
*  Game data handler for Nokia games.
*  Never launch any applications, just save the file/buffer
*  to game specific directory under c:\data\games\. 
*/
NONSHARABLE_CLASS(CDocGameHandler) :public CDocDefaultHandler
    {
    public:  // Constructors and destructor
        
        /**
        * C++ default constructor.
        */
        CDocGameHandler(
            const TDataType& aDataType,
            const TUid& aUid,
            CDocumentHandler* aDocDispatcher,
            TDocServiceMode aServiceMode );

        /**
        * Two-phased constructor.
        */
        static CDocGameHandler* NewL(
                const TDataType& aDataType,
                const TUid& aUid,
                CDocumentHandler* aDocDispatcher,
                TDocServiceMode aServiceMode );

        /**
        * Destructor.
        */
        virtual ~CDocGameHandler();
       
    public: // New functions
    public: // Functions from base classes

        TInt CopyOrMoveL( const TUint aAttr );
        
        TInt CopyHandleL( const RFile& aSourceFile, const TUint aAttr );

        void PopulateAppInfo();

        void ParseGameInfoFromFileL( const RFile& aFile );
        void ParseGameInfoFromFileL( const TDesC& aFilename );
        void ParseGameInfoFromBufL( const TDesC8& aBuffer );
        TInt CheckGameDataTypeL( TInt32 aGameId );
        
    protected:  // New functions

    protected:  // Functions from base classes
        
        /**
        * Get the data directory for the mime type. 
        *
        * @param aDataType Data type 
        * @param aUid      App Uid
        * @param aPath     absolute path to return
        *
        * @return KErrNone if success. If fail an error code.
        */
        TInt GetDataDirL( 
            const TDataType& aDataType, 
            const TUid& aUid, 
            TDes& aPath,
            TInt aDataSize);

        /**
        * Never a viewer operations, because we don't launch
        * games at all.
        * @return EFalse
        */ 
       TBool IsViewerOperation( TDocOperation aOperation );

       TInt NotifyGameEngine( const TUid& aUid );

    private:

        /**
        * By default EPOC constructor is private.
        */
        void ConstructL();

        // By default, prohibit copy constructor
        CDocGameHandler( const CDocGameHandler& );

        // Prohibit assigment operator
        CDocGameHandler& operator= ( const CDocGameHandler& );

    public:     // Data
    
    protected:  // Data
        TInt32  iGameId;        

    private:    // Data

    public:     // Friend classes

    protected:  // Friend classes

    private:    // Friend classes
    
    };

#endif      // CDOCGAMEHANDLER_H
            
// End of File
