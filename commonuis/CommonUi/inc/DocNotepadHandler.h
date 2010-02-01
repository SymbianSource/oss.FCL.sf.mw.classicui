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
* Description:  Header file for text data handler.  
*
*/


#ifndef CDOCNOTEPADHANDLER_H
#define CDOCNOTEPADHANDLER_H

//  INCLUDES
#include "DocDefaultHandler.h"

// CLASS DECLARATION
class CCommonUiNpdApiLoader;

/**
* Handler for text files. 
* Uses the Notepad's api for saving. Uses TextViewer for opening text content.
*/
NONSHARABLE_CLASS(CDocNotepadHandler) : public CDocDefaultHandler
    {
    public:        // Constructors and destructor

        /**
        * Two-phased constructor. 
        * @param aDataType      Data type
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        * @return               Constructed CNotepadHandler
        */
        static CDocNotepadHandler* NewL( const TDataType& aDataType,
                                         const TUid& aUid,
                                         CDocumentHandler* aDocDispatcher );

        /**
        * Two-phased constructor. Leaves the contructed instance in to the 
        * clean up stack.
        * @param aDataType      Data type
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        * @return               Constructed CNotepadHandler
        */
        static CDocNotepadHandler* NewLC( const TDataType&
                                          aDataType, 
                                          const TUid& aUid,
                                          CDocumentHandler* aDocDispatcher );
        /**
        * Destructor
        */
        ~CDocNotepadHandler();

        private:
        
        /**
        * Epoc constructor
        */
        void ConstructL();

        /**
        * Constructor
        * @param aDataType      Data type
        * @param aUid           UID of the handler app
        * @param aDocDispatcher Pointer to DocumentHandler instance
        * @param aServiceMode   EDocOpenAndSave (Can handle both operations.)
        */
        CDocNotepadHandler( const TDataType&
                            aDataType, 
                            const TUid& aUid,
                            CDocumentHandler* aDocDispatcher,
                            TDocServiceMode aServiceMode = EDocOpenAndSave );
        /**
        * Load Notepad Api.
        */
		void LoadNpdApiL();
		

    public:       // Functions from base classes
        /**
        * Copy/move a file to the correct directory.
        * @param        aAttr File attributes.
        * @return       KErrNone if success, a status code if failed.
        */
        TInt CopyOrMoveL( const TUint );
        
        /**
        * Copy a file to the correct directory.
        * @param        a filehandle of source file
        * @param        aAttr File attributes.
        * @return       KErrNone if success, a status code if failed.
        */
        TInt CopyHandleL( const RFile& aSourceFile, const TUint aAttr );
        
    private:
    
    	/*
        * Has the Npd Api DLL already been loaded.
        */
        TBool iNpdDllLoaded;

        /*
        * A handle to a dynamically loadable DLL.
        */
        RLibrary iNpdDll;

        /*
        * Loads Npd Api DLL dynamically to memory.
        * Allows use of the DLL through this pointer, but only for
        * methods implemented within.
        * Own.
        */
        CCommonUiNpdApiLoader* iNpdApi;

    };

#endif      // CDOCNOTEPADHANDLER_H

// End of File
