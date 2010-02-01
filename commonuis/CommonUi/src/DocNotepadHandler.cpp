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
* Description:  Implementation of text data handler.
*
*/


// INCLUDE FILES

#include "DocNotepadHandler.h"
#include "DocSaver.h"

#include "CommonUiNpdApiLoader.h"

// CONSTANTS
// Path and filename of wrapper dll.
_LIT( KCommonUiNpdApiLoaderName, "z:\\sys\\bin\\commonuinpdapiloader.dll" );
// Entry point for dynamically loaded dlls.
const TInt KNpdApiDllEntryPoint = 1;

// TYPE DEFINITIONS
typedef TAny* (*NpdApiL)();

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Two-phased constructor. 
// -----------------------------------------------------------------------------
//
CDocNotepadHandler* CDocNotepadHandler::NewL(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher )
    {
    CDocNotepadHandler *self = 
        CDocNotepadHandler::NewLC( aDataType, 
                                   aUid, aDocDispatcher );
    CleanupStack::Pop();
    return self;
    }
    
// -----------------------------------------------------------------------------
// Two-phased constructor. Leaves the contructed instance in to the 
// clean up stack.
// -----------------------------------------------------------------------------
CDocNotepadHandler* CDocNotepadHandler::NewLC(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher )
    {
    CDocNotepadHandler *self = 
        new( ELeave ) CDocNotepadHandler( aDataType, aUid, 
                                          aDocDispatcher, EDocOpenAndSave );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// Epoc constructor    
// -----------------------------------------------------------------------------
void CDocNotepadHandler::ConstructL()
    {
    BaseConstructL();    
    }

// -----------------------------------------------------------------------------    
// Destructor
// -----------------------------------------------------------------------------
CDocNotepadHandler::~CDocNotepadHandler()
    {
    delete iNpdApi;
    if( iNpdDllLoaded )
        {
        iNpdDll.Close();
        }
    }

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
CDocNotepadHandler::CDocNotepadHandler(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher,
    TDocServiceMode aServiceMode ) : 
    CDocDefaultHandler( aDataType, aUid, aDocDispatcher, aServiceMode )
    {
    }


// -----------------------------------------------------------------------------
// TInt CDocNotepadHandler::CopyOrMoveL(..)
// Copy the text file content to Notepad's storage.
// -----------------------------------------------------------------------------    
TInt CDocNotepadHandler::CopyOrMoveL( const TUint )
    {
    TInt error = KErrNone;
   	if( !iNpdDllLoaded )
        {
        LoadNpdApiL();
        }    
    iNpdApi->SaveFileAsMemoL( iSourceFile );
    
    // If this was MoveL-function, then we have to delete source file
    if (DocOperation() == EDocMove || DocOperation() == EDocSilentMove)
        { 
        error = iFileManager->Delete(iSourceFile, ETrue);        
        }

    // skip note if silentmove
    if (DocOperation() != EDocSilentMove)
        {
        AddResourcesL();
        HBufC* text;        
        text = StringLoader::LoadLC( 
            R_DOCUMENT_HANDLER_FILE_SAVED_TO, 
            this->iAppInfo.iCaption );                
        CDocSaver::ConfNoteL( text->Des(), ETrue );
        CleanupStack::PopAndDestroy(); // text
        RemoveResources();
        }

    HandleServerAppExit(0);
    return SetAndReturnStatus( error );
    }
    
// -----------------------------------------------------------------------------
// TInt CDocNotepadHandler::CopyHandleL(..)
// Copy the text file content to Notepad's storage.
// -----------------------------------------------------------------------------
TInt CDocNotepadHandler::CopyHandleL( const RFile& aSourceFile, const TUint )
    {
    TInt error = KErrNone;
	if( !iNpdDllLoaded )
        {
        LoadNpdApiL();
        }
    iNpdApi->SaveFileAsMemoL( aSourceFile );
            
    AddResourcesL();
    HBufC* text;        
    text = StringLoader::LoadLC( 
        R_DOCUMENT_HANDLER_FILE_SAVED_TO, 
        this->iAppInfo.iCaption );                                
    CDocSaver::ConfNoteL( text->Des(), ETrue );
    CleanupStack::PopAndDestroy(); // text
    RemoveResources();
    
    HandleServerAppExit(0);
    return SetAndReturnStatus( error );
    }    

// -----------------------------------------------------------------------------
// TInt CDocNotepadHandler::LoadNpdApiL
// Load Notepad Api.
// -----------------------------------------------------------------------------
void CDocNotepadHandler::LoadNpdApiL()
	{	
	// Memo saving dll loading.
    if( !iNpdDllLoaded )
        {        
        if( iNpdDll.Load( KCommonUiNpdApiLoaderName ) == KErrNone )
            {         
            iNpdDllLoaded = ETrue;
            // Request the entry function
            NpdApiL npdApi = (NpdApiL) iNpdDll.Lookup( KNpdApiDllEntryPoint );
            if( npdApi )
                {                
                // Create the class
                iNpdApi = (CCommonUiNpdApiLoader*) (*npdApi)();
                }
            }
        }
    // The wrapper failed to load.
    if ( !iNpdApi )
        {
        User::Leave( KErrNotFound );
        }    
	}

//  End of File
