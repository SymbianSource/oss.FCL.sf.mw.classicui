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
* Description:  Implementation of app installer handler.
*
*/


// INCLUDE FILES
#include "DocAppInstHandler.h"
#include "DocAppInstLauncher.h"
#include <charconv.h>
#include <utf.h>


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CDocAppInstHandler::CDocAppInstHandler(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher,
    TDocServiceMode aServiceMode ) : 
        CDocDefaultHandler( aDataType, aUid, aDocDispatcher, aServiceMode ),
        iCallWithParams( EFalse ),
        iHeapURL( NULL ),
        iParamDescriptor( NULL ),
        iUseDescriptor( EFalse )
    {
    } 

// Two-phased constructor.
//
CDocAppInstHandler* CDocAppInstHandler::NewL(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher,
    TDocServiceMode aServiceMode )
    {
    CDocAppInstHandler *self = 
        new ( ELeave ) CDocAppInstHandler( aDataType,  
                                           aUid, aDocDispatcher, 
                                           aServiceMode ); 
    CleanupStack::PushL( self );
    self->BaseConstructL();
    CleanupStack::Pop();
    return self;
    }
        
// Destructor
//
CDocAppInstHandler::~CDocAppInstHandler()
    {
    if ( iLauncher )
        {
        iLauncher->Cancel();
        }
    delete iLauncher;  
    delete iParamPckg;  
    delete iHeapURL; //URL
    delete iParamDescriptor; //Params+URL
    }
    

// ---------------------------------------------------------
// CDocAppInstHandler::AddToParamListL()
// Add parameters (gives as parameter) to installer spesific parameter list
// ---------------------------------------------------------
//    
void CDocAppInstHandler::AddToParamListL(const CAiwGenericParamList& aParams)
    {
    TInt index = 0;
    const TAiwGenericParam* param = NULL;
    SwiUI::TInstallReq params; 
    
    iCallWithParams = EFalse;
    iUseDescriptor = EFalse;
       
    // Installer wants some parameters from Browser. Convert parameters 
    // (if there are any) from aParams to installer used format.
    if ( aParams.Count() ) 
        {
        //TInstallReq.iCharsetId
        param = aParams.FindFirst(index, EGenericParamCharSet, EVariantTypeDesC);
        if (index >= 0 && param)
            {
            TPtrC charset;
            param->Value().Get(charset);
            
            HBufC8* charset8 = CnvUtfConverter::ConvertFromUnicodeToUtf8L( charset );
            
            CCnvCharacterSetConverter* conv = CCnvCharacterSetConverter::NewLC();            
            params.iCharsetId = conv->ConvertStandardNameOfCharacterSetToIdentifierL( *charset8, iFs );
            CleanupStack::PopAndDestroy();   // conv
            
            delete charset8;
            iCallWithParams = ETrue;
            }
        //TInstallReq.iIAP;	
        index = 0;
        param = aParams.FindFirst(index, EGenericParamAccessPoint, EVariantTypeTInt32);
        if (index >= 0 && param)
            {
            TInt32 accesspoint;
            param->Value().Get(accesspoint);
            params.iIAP = accesspoint;
            iCallWithParams = ETrue;
            }	
        //TInstallReq.iSourceURL;
        index = 0;	
        param = aParams.FindFirst(index, EGenericParamURL, EVariantTypeDesC);
        if (index >= 0 && param)
            {
            TPtrC sourceURL;
            param->Value().Get(sourceURL);      	
            // params.iSourceURL = sourceURL; // removed because TSW JROL-7B8K6H
            iCallWithParams = ETrue;
            // Alloc URL from heap.
            iHeapURL = sourceURL.AllocL();
            iUseDescriptor = ETrue;
            }	
        //TInstallReq.iMIME;
        if ( iCallWithParams )
            {
            params.iMIME = iDataType.Des8();
            }	

        // Ok we have all params + url in the descriptor.
        if ( iUseDescriptor )
            {
            // Set params to pckg buffer.
            SwiUI::TInstallReqPckg regPckg( params );
            // Alloc heap buffer: 800bytes + 4bytes + size of URL
            iParamDescriptor = HBufC8::NewL(
                sizeof( regPckg ) +
                sizeof( TInt32 ) +
                iHeapURL->Size() );

            TPtr8 iParamDesPtr = iParamDescriptor->Des();
            // Copy parameters to 8-bit descriptor
            RDesWriteStream stream( iParamDesPtr );
            CleanupClosePushL( stream );
            stream.WriteL( regPckg );
            // Note length must be set always. Even if it is zero.
            stream.WriteInt32L( iHeapURL->Length() );
            stream.WriteL( *iHeapURL );
            CleanupStack::PopAndDestroy( &stream );
            }
        }
    iParamPckg = new ( ELeave ) SwiUI::TInstallReqPckg (params);
    }

// ---------------------------------------------------------
// CDocAppInstHandler::OpenFileEmbeddedL(RFile& aFileHandle)
// 
// ---------------------------------------------------------
//        
TInt CDocAppInstHandler::OpenFileEmbeddedL(RFile& aFileHandle)
    {
    // Installer won't be embedded -> Forward to stand-alone version
    return OpenFileL(aFileHandle);
    }

// ---------------------------------------------------------
// CDocAppInstHandler::OpenFileEmbeddedL(RFile& aFileHandle)
// 
// ---------------------------------------------------------
//        
TInt CDocAppInstHandler::OpenFileL(RFile& aFileHandle)
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocAppInstHandler::OpenFileL Called"));
    #endif 
    
    iLauncher = CDocAppInstLauncher::NewL();  
    iLauncher->SetExitObserver( this );  
    
    if ( iCallWithParams )
        {
        if ( iUseDescriptor )
            {
            iLauncher->InstallL( aFileHandle, *iParamDescriptor );
            }
        else
            {
            iLauncher->InstallL( aFileHandle, *iParamPckg );
            }
        }
    else
        {
        iLauncher->InstallL( aFileHandle ); 
        } 
         
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocAppInstHandler::OpenFileL Returns.")) ;
    #endif 
    return SetAndReturnStatus( KErrNone );  // If we're still here, everything is ok.
    }

//  End of File
