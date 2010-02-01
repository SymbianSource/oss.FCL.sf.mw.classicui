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
* Description:  Implementation of DCF handler class.
*
*/


#include <e32std.h>
#include <s32mem.h>
#include <coemain.h>

#include <DRMCommon.h>
#include <DRMHelper.h>
#include <AiwGenericParam.h>
#include <AknQueryDialog.h>         // CAknQueryDialog
#include <documenthandlerui.rsg>    // Resource ids
#include <StringLoader.h>           // For loading resource strings
#include <stringresourcereader.h>   // CStringResourceReader

#include "DocDCFHandler.h"
#include "DocDefaultHandler.h"
#include "DocResourceFile.h"
#include "DocSaver.h" 

// ---------------------------------------------------------
// C++ default constructor can NOT contain any code, that
// might leave.
// ---------------------------------------------------------
//
CDocDCFHandler::CDocDCFHandler( 
    const TDataType& aDataType,
    TDocOperation aOperation,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher): 
        CDocDefaultHandler( aDataType, aUid, aDocDispatcher, EDocOpenAndSave ),
        iEntryFunc( aOperation )
    {
    }
            
// ---------------------------------------------------------
// Two-phased constructor. 
// ---------------------------------------------------------
//
CDocDCFHandler* CDocDCFHandler::NewL(
    const TDataType& aDataType,
    TDocOperation aOperation, 
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher)
    {
    CDocDCFHandler *self = new (ELeave) CDocDCFHandler( aDataType, aOperation, aUid, aDocDispatcher );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// ---------------------------------------------------------
// Epoc contructor
// ---------------------------------------------------------
//  
void CDocDCFHandler::ConstructL()
    {
    BaseConstructL();
    iDRMCommon = DRMCommon::NewL();
    }

// ---------------------------------------------------------
// Destructor  
// ---------------------------------------------------------
//
CDocDCFHandler::~CDocDCFHandler()
    {
    delete iDRMCommon;
    delete iDocHandler;
    }

// ---------------------------------------------------------
// CDocDCFHandler::SetDataTypeL()
// Set the data type (iDataType)
// ---------------------------------------------------------
//  
void CDocDCFHandler::SetDataTypeL(HBufC8* MIMEType)
    {               
    TPtr8 ptr = MIMEType->Des();
    ptr.Copy(*MIMEType);               
    iDataType = TDataType( ptr );
    #ifdef _DEBUG        
    TPtrC mimetype = iDataType.Des();  
    RDebug::Print( _L("DocumentHandler: CDocDCFHandler::SetDataTypeL: iDataType: %S "), &mimetype);
    #endif 
    }
    
// ---------------------------------------------------------
// CDocDCFHandler::GetPath()
// Return the path where the content was saved/copied
// ---------------------------------------------------------
//  
void CDocDCFHandler::GetPath( TDes& aPath ) const
    {
    if ( iDocHandler )
        {
        iDocHandler->GetPath( aPath );
        }
    else
        {
        aPath.Zero();
        }
    }

// ---------------------------------------------------------
// CDocDCFHandler::HandlerAppUid()
// Returns handler application Uid.
// ---------------------------------------------------------
// 
void CDocDCFHandler::HandlerAppUid( TUid& aUid ) const
    {
    if ( iDocHandler  )
        {
        iDocHandler->HandlerAppUid( aUid );
        }
    }

// ---------------------------------------------------------
// CDocDCFHandler::CanOpen()
// Is the handler capable of opening the mime type
// ---------------------------------------------------------
//   
TBool CDocDCFHandler::CanOpen() const
    {
    return ETrue;
    }

// ---------------------------------------------------------
// CDocDCFHandler::CanSave()
// Is the handler capable of saving the mime type
// ---------------------------------------------------------
//   
TBool CDocDCFHandler::CanSave() const
    {
    return ETrue;
    }

// ---------------------------------------------------------
// CDocDCFHandler::ConvertErrorCode()
// Converts DRM error code to more generic one
// ---------------------------------------------------------
//   
TInt CDocDCFHandler::ConvertErrorCode(TInt aDrmError)
    {
    switch (aDrmError)
        {
        case DRMCommon::EOk:
            return KErrNone;    
        case DRMCommon::EGeneralError:
            return KErrGeneral;
        case DRMCommon::EUnknownMIME:
            return KMimeNotSupported;
        case DRMCommon::EVersionNotSupported:
            return  KDRMErrInvalidVersion;
        case DRMCommon::ESessionError:
            return KDRMErrSession;
        case DRMCommon::ENoRights:
            return KDRMErrNoRights;
        case DRMCommon::ERightsDBCorrupted:
            return  KDRMErrRightsDBCorrupted;
        case DRMCommon::EUnsupported:
            return KErrNotSupported;                
        default:
            break;
        }

    // It is possible that DRM error is normal errorcode
    // those are passed without conversion.
    return aDrmError;     
    }
   
// ---------------------------------------------------------
// CDocDCFHandler::OpenFileL( )
// Calls OpenDCFFileL.
// ---------------------------------------------------------
//       
TInt CDocDCFHandler::OpenFileL(RFile& aFileHandle)
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler : CDocDCFHandler::OpenFileL called."));
    #endif   
    return OpenDCFFileL( aFileHandle );
    }
    
// ---------------------------------------------------------
// CDocDCFHandler::OpenFileEmbeddedL( )
// Calls OpenDCFFileL.
// ---------------------------------------------------------
//      
TInt CDocDCFHandler::OpenFileEmbeddedL(RFile& aFileHandle)
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler : CDocDCFHandler::OpenFileEmbeddedL called."));
    #endif       
    return OpenDCFFileL( aFileHandle );
    }

// ---------------------------------------------------------
// CDocDCFHandler::CopyOrMoveL( )
// Calls CopyDCFFileL.
// CopyL & MoveL & SilentMoveL is supported
// ---------------------------------------------------------
//  
TInt CDocDCFHandler::CopyOrMoveL( const TUint aAttr)
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler : CDocDCFHandler::CopyOrMoveL called."));
    #endif   
       
    RFile tempHandle; // This is only temporary, not used to anything
    TInt retValue = CopyDCFFileL(EFalse, tempHandle, aAttr);     
    tempHandle.Close();
    return retValue;  
    }

// ---------------------------------------------------------
// CDocDCFHandler::CopyOrMoveL( )
// Calls CopyDCFFileL.
// CopyL is supported
// ---------------------------------------------------------
//  
TInt CDocDCFHandler::CopyHandleL( const RFile& aSourceFile, const TUint aAttr )
    {
    // CopyL (with filehandle) is supported
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler : CDocDCFHandler::CopyHandleL called."));
    #endif   
    
    return CopyDCFFileL(ETrue, const_cast<RFile&>(aSourceFile), aAttr);    
    }

// ---------------------------------------------------------
// CDocDCFHandler::OpenDCFFileL( )
// Check DRM rights and create new CDocumentHandler instance
// for handling actual operation with payload MIME-type.
// ---------------------------------------------------------
//  
TInt CDocDCFHandler::OpenDCFFileL(RFile& aFileHandle)
    {
    TUint bufLength;
    DRMCommon::TContentProtection protection;
    HBufC8* MIMEType = NULL;
    HBufC8* contentURI = NULL;
    TInt error;
      
    error = iDRMCommon->GetFileInfo(aFileHandle,
        protection,
        MIMEType,
        contentURI,
        bufLength); 
    
    if (error != DRMCommon::EOk)
        {
        #ifdef _DEBUG        
        RDebug::Print( _L("DocumentHandler : CDocDCFHandler::OpenDCFFileL: GetFileInfo returned=%d"), error);
        #endif 
        return ConvertErrorCode(error);
        }
    else 
        {
        error = KErrNone;    
        }
        
    // Errorcode from iDRMCommon cannot be trusted. Check here params first.
    if (!MIMEType || !contentURI)
        {
        if (MIMEType)
            delete MIMEType;

        if (contentURI)
            delete contentURI;

        return KDRMErrInvalidVersion; // This is one possible reason
        }

    CleanupStack::PushL( MIMEType );
    CleanupStack::PushL( contentURI );
    
    if ( MIMEType->FindF( KDataTypeDCF ) != KErrNotFound )
        {
        CleanupStack::PopAndDestroy(2);  // MIMEType, contentURI
        return KBadMimeType;
        }

    SetDataTypeL( MIMEType );  
    
    CDRMRights* rightsObject = NULL;
    TInt rights = iDRMCommon->GetActiveRights(*contentURI, 0, rightsObject);
    delete rightsObject;
    CleanupStack::PopAndDestroy(2);  // MIMEType, contentURI

    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler : CDocDCFHandler::OpenDCFFileL: Rights of file are=%d"), rights);
    #endif 

    // Check if file is empty (rights must exist before we can trust bufLength)
    if (rights != DRMCommon::ENoRights  && bufLength == 0)
        {
        return KNullContent;
        }
    
    if ( !iDocHandler )
        {
        iDocHandler = CDocumentHandler::NewL( ); 
        if (iDocDispatcher->ServerAppExitObserver())
            {
            iDocHandler->SetExitObserver(iDocDispatcher->ServerAppExitObserver());
            }
        }

    if (rights == DRMCommon::ENoRights)
        {
        return KDRMErrNoRights;
        }
           
    switch ( iEntryFunc )
        {
        case EDocOpenFileEmb:
            error = iDocHandler->OpenFileEmbeddedL( aFileHandle, iDataType, *iAiwParams );              
            break;
        case EDocOpenFile:
            error = iDocHandler->OpenFileL( aFileHandle, iDataType ); 
            break;         
        default:
            User::Leave( KErrNotSupported );
        }
    
    iStatus = error;
    
    return error;
    }

// ---------------------------------------------------------
// CDocDCFHandler::CopyDCFFileL( )
// Check DRM rights and create new CDocumentHandler instance
// for handling actual operation with payload MIME-type.
// ---------------------------------------------------------
//  
TInt CDocDCFHandler::CopyDCFFileL(TBool aUseHandle, RFile& aFileHandle, const TUint aAttr)
    {
    TUint bufLength;
    DRMCommon::TContentProtection protection;
    HBufC8* MIMEType = NULL;
    HBufC8* contentURI = NULL;
    TInt error;  
      
    if (aUseHandle) // Filehandle version
        {
        error = iDRMCommon->GetFileInfo(aFileHandle,
        protection,
        MIMEType,
        contentURI,
        bufLength); 
        }
    else            // FileName version   
        {
        error = iDRMCommon->GetFileInfo(iSourceFile,
        protection,
        MIMEType,
        contentURI,
        bufLength);  
        }    

    if (error != DRMCommon::EOk)
        {
        #ifdef _DEBUG        
        RDebug::Print( _L("DocumentHandler : CDocDCFHandler::CopyDCFFileL: GetFileInfo returned=%d"), error);
        #endif 
        return ConvertErrorCode(error);
        }
    else 
        {
        error = KErrNone;    
        }

    // Errorcode from iDRMCommon cannot be trusted. Check here params first.
    if (!MIMEType || !contentURI)
        {
        if (MIMEType)
            delete MIMEType;
        if (contentURI)
            delete contentURI;
        return KDRMErrInvalidVersion; // This is one possible reason
        }

    CleanupStack::PushL( MIMEType );
    CleanupStack::PushL( contentURI );
    
    if ( MIMEType->FindF( KDataTypeDCF ) != KErrNotFound )
        {
        CleanupStack::PopAndDestroy(2);  // MIMEType, contentURI
        return KBadMimeType;
        }

    SetDataTypeL( MIMEType );  
    
    CDRMRights* rightsObject = NULL;
    TInt rights = iDRMCommon->GetActiveRights(*contentURI, 0, rightsObject);  
    delete rightsObject;
    CleanupStack::PopAndDestroy(2);  // MIMEType, contentURI
    
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler : CDocDCFHandler::CopyDCFFileL: Rights of file are=%d"), rights);
    #endif 

    // Check if file is empty (rights must exist before we can trust bufLength)
    if (rights != DRMCommon::ENoRights  && bufLength == 0)
        {
        return KNullContent;
        }

    // Check if file is with PreviewRights (preview file is not allowed to save)
    if (rights == CDRMRights::EPreviewRights && protection == DRMCommon::EForwardLocked)
        {
        return KDRMErrPreviewRights;
        }

    if ( !iDocHandler )
        {
        iDocHandler = CDocumentHandler::NewL( ); 
        if (iDocDispatcher->ServerAppExitObserver())
            {
            iDocHandler->SetExitObserver(iDocDispatcher->ServerAppExitObserver());
            }
        }
            
    switch ( iEntryFunc )
        {  
        case EDocCopy:         
            if (aUseHandle) // Filehandle version
                {
                error = iDocHandler->CopyL( aFileHandle, iDestFile, iDataType, aAttr );
                }                     
            else            // FileName version   
                {
                error = iDocHandler->CopyL( iSourceFile, iDestFile, iDataType, aAttr );
                }
            break;   
        case EDocMove:
            error = iDocHandler->MoveL( iSourceFile, iDestFile, iDataType, aAttr );
            break;         
        case EDocSilentMove:
            error = iDocHandler->SilentMoveL( iSourceFile, iDestFile, iRootPath, iDataType, aAttr );
            break;  
        default:
            User::Leave( KErrNotSupported );
        }
    
    iStatus = error;
    
    return error;  
    }

//  End of File  
