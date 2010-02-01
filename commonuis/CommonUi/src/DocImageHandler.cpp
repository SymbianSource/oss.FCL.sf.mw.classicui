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
* Description:  Implements image handler class for document handler.
*
*/


#include "DocImageHandler.h"
#include "DocSaver.h"                   // CDocAsyncSaver

// CONSTANTS
static const TInt KPhotoAlbumMaxNameLength(40);

// ---------------------------------------------------------    
// Constructor
// ---------------------------------------------------------
CDocImageHandler::CDocImageHandler(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher) : 
    CDocDefaultHandler( aDataType, aUid, aDocDispatcher, EDocOpenAndSave )
    {
    }

// ---------------------------------------------------------
// void CDocImageHandler::ConstructL(..)
// Epoc constructor. In addition to defaultHandlers
// tasks constructs a CPAlbImageUtil object.
// ---------------------------------------------------------
void CDocImageHandler::ConstructL()
    {
    BaseConstructL();
    }

// ---------------------------------------------------------
// CDocImageHandler::~CDocImageHandler()
// Destructor
// ---------------------------------------------------------
CDocImageHandler::~CDocImageHandler()
    {
    }

// ---------------------------------------------------------
// CDocImageHandler* CDocImageHandler::NewL(..)
// Returns a contructed CDocImageHandler object
// ---------------------------------------------------------
CDocImageHandler* CDocImageHandler::NewL(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher)
    {
    CDocImageHandler* self = CDocImageHandler::NewLC( aDataType, 
                                                      aUid, aDocDispatcher );
    CleanupStack::Pop();    // self
    return self;
    }

// ---------------------------------------------------------
// CDocImageHandler* CDocImageHandler::NewLC(..)
// Returns a contructed CDocImageHandler object. Leaves
// the object in the cleanup stack.
// ---------------------------------------------------------
CDocImageHandler* CDocImageHandler::NewLC(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher)
    {
    CDocImageHandler * self = 
        new( ELeave ) CDocImageHandler( aDataType, aUid,
                                        aDocDispatcher );
    CleanupStack::PushL( self );
    self->ConstructL( );
    return self;
    }

// ---------------------------------------------------------
// CDocImageHandler::PopulateAppInfo()
// Construct iAppInfo with KImageViewerUID .
// ---------------------------------------------------------
//  
void CDocImageHandler::PopulateAppInfo()
    {
    CDocDefaultHandler::PopulateAppInfo( KImageViewerUID );
    }

// ---------------------------------------------------------
// CDocDefaultHandler::MaxNameLen()
// Return max lenght of file name, in case of images it is
// different than normal file max length.
// ---------------------------------------------------------
//  
TInt CDocImageHandler::MaxNameLen()
    {
    return KPhotoAlbumMaxNameLength;
    }

// ---------------------------------------------------------
// CDocDefaultHandler::HideFileExtension()
// Should we hide file extension (in case of images, we 
// should hide).
// ---------------------------------------------------------
// 
TBool CDocImageHandler::HideFileExtension()
    {
    return ETrue;
    }



//  End of File
