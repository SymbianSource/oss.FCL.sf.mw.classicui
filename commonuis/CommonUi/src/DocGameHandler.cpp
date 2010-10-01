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
* Description:  Implementation of game data handler.
*
*/


// INCLUDE FILES
#include <s32mem.h>
#include <s32file.h>
#include "DocGameHandler.h"
#include "pathinfo.h"

// EXTERNAL DATA STRUCTURES

// EXTERNAL FUNCTION PROTOTYPES  

// CONSTANTS

// MACROS

// LOCAL CONSTANTS AND MACROS

// MODULE DATA STRUCTURES

// LOCAL FUNCTION PROTOTYPES

// ==================== LOCAL FUNCTIONS ====================

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CDocGameHandler::CDocGameHandler(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher,
    TDocServiceMode aServiceMode ): 
        CDocDefaultHandler( aDataType, aUid, 
                            aDocDispatcher, aServiceMode )
    {
    }



// EPOC default constructor can leave.
void CDocGameHandler::ConstructL()
    {
    BaseConstructL();
    iGameId = KGameEngineUID;
    }

// Two-phased constructor.
CDocGameHandler* CDocGameHandler::NewL(    
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher,
    TDocServiceMode aServiceMode )
    {
    CDocGameHandler* self = new (ELeave) CDocGameHandler( aDataType, 
                                           aUid, aDocDispatcher, 
                                           aServiceMode );
       
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }
    
// Destructor
CDocGameHandler::~CDocGameHandler()
    {
    
    } 

void CDocGameHandler::ParseGameInfoFromFileL( const TDesC& aFilename )
    {
    RFile file;
    User::LeaveIfError( file.Open( iFs, aFilename, EFileRead ) );
    CleanupClosePushL( file );
    RFileReadStream reader( file );    
    iGameId = reader.ReadInt32L();
    reader.ReadInt8L();             // Data Type
    reader.ReadInt32L();            // Data Length
    TInt size = reader.ReadInt8L();// Size of Name String
    if ( size > 0 )
        {
        reader.ReadL( iDestFile, size );// Name String
        }
    reader.Close();
    CleanupStack::PopAndDestroy( &file );
    }
    
// TODO: Does this method work, how to test this?    
void CDocGameHandler::ParseGameInfoFromFileL( const RFile& aFile )
    {
    RFileReadStream reader( const_cast<RFile&>(aFile) );    
    iGameId = reader.ReadInt32L();
    reader.ReadInt8L();             // Data Type
    reader.ReadInt32L();            // Data Length
    TInt size = reader.ReadInt8L();// Size of Name String
    if ( size > 0 )
        {
        reader.ReadL( iDestFile, size );// Name String
        }
    reader.Close();
    }    

void CDocGameHandler::ParseGameInfoFromBufL( const TDesC8& aBuffer )
    {   
    RDesReadStream reader( aBuffer );
    iGameId = reader.ReadInt32L();  // GameId
    reader.ReadInt8L();             // Data Type
    reader.ReadInt32L();            // Data Length
    TInt size = reader.ReadInt8L(); // Size of Name String
    if ( size > 0 )
        {
        reader.ReadL( iDestFile, size );// Name String
        }
    reader.Close();  
    }

//
// Changes iUid to "real". Changes iDataType to "real" value.
//
TInt CDocGameHandler::CheckGameDataTypeL( TInt32 aGameId )
    {
    TInt error = KErrNone;
    if ( aGameId > KMaxGameEngineDataID )
        {
        TBuf8<256> completedType = iDataType.Des8();                
        completedType.Append( _L("-") );
        completedType.AppendNumFixedWidth( aGameId, EHex, 8 );      
        iDataType = TDataType( completedType );
        }
    error = iApaLs->AppForDataType( iDataType, iUid );
    if ( error != KErrNone )
        {
        User::Leave( error );
        }

    if ( iUid.iUid == 0)
        {
        iUid.iUid = KGameEngineUID;
        }

    PopulateAppInfo();
    if ( iAppInfo.iFullName.Length() == 0 )
        {
        User::Leave( KMimeNotSupported );
        }
    return error;
    }

  
void CDocGameHandler::PopulateAppInfo()
    {    
    CDocDefaultHandler::PopulateAppInfo( iUid );    
    }

// ---------------------------------------------------------
// CDocDefaultHandler::GetDataDirL( 
//    const TDataType& aDataType, 
//    const TUid& aUid, 
//    TDes& aPath 
//    TDes& aDataSize)
// Get the data directory for the mime type
// ---------------------------------------------------------
//        
TInt CDocGameHandler::GetDataDirL( 
    const TDataType& aDataType, 
    const TUid& aUid, 
    TDes& aPath,
    TInt aDataSize)
    {    
    if ( iUid.iUid != 0 )
        {
        if (CDocDefaultHandler::GetDataDirL( aDataType, aUid, aPath, aDataSize ) == KErrCancel)
            {
            return KErrCancel;
            }
        }
  
    if ( iSavedAsTemp )
        User::Leave( KMimeNotSupported );

    if ( iUid.iUid != KGameEngineUID )
        {
        aPath.Insert( 0,  PathInfo::GamesPath() );
        }
    TParsePtr parse( aPath );
    if ( parse.NamePresent() )                  // There is no '\' in the end.
        {
        aPath.Append( _L( "\\" ) );              // Append it. We need it!
        }

    return SetAndReturnStatus( KErrNone );
    }

TInt CDocGameHandler::CopyOrMoveL( const TUint aAttr )
    {
    ParseGameInfoFromFileL( iSourceFile );
    User::LeaveIfError( CheckGameDataTypeL( iGameId ) );
    TInt error = CDocDefaultHandler::CopyOrMoveL( aAttr );
    if ( iUid.iUid == KGameEngineUID )
        {
        NotifyGameEngine( iUid );
        }
    HandleServerAppExit(0);
    return SetAndReturnStatus( error );
    }
    
TInt CDocGameHandler::CopyHandleL( const RFile& aSourceFile, const TUint aAttr  )
    {
    ParseGameInfoFromFileL( aSourceFile );
    User::LeaveIfError( CheckGameDataTypeL( iGameId ) );
    TInt error = CDocDefaultHandler::CopyHandleL( aSourceFile, aAttr );
    if ( iUid.iUid == KGameEngineUID )
        {
        NotifyGameEngine( iUid );
        }
    HandleServerAppExit(0);
    return SetAndReturnStatus( error );
    }    

TBool CDocGameHandler::IsViewerOperation( TDocOperation /*aOperation*/ )
    {
    return EFalse;
    }

    
TInt CDocGameHandler::NotifyGameEngine( const TUid& /*aUid*/ )
    {

    // TODO: Is there needed some notify?
    return 0;
    }
    
//  End of File  
