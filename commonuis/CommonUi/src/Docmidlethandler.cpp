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
* Description:  Implements Midlet handler class for document handler.
*
*/


#include <apgtask.h>
#include <eikenv.h>
#include <eikappui.h>
#include <vwsdef.h>
#include <e32math.h>
#include <EikProc.h>                // CEikProcess
#include <EikDoc.h>                 // CEikDocument
#include <EikEnv.h>                 // CEikEnv
#include <UriUtils.h>
#include <f32file.h>
#include <s32file.h>
#include <AiwGenericParam.h>

#include "DocMidletHandler.h"
#include "DocSaver.h"                   // CDocAsyncSaver

// The UID for Java MIDlets
const TInt KUidJavaMidpAppValue = 0x100096C5;

// ---------------------------------------------------------    
// Constructor
// ---------------------------------------------------------
CDocMidletHandler::CDocMidletHandler(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher) : 
    CDocDefaultHandler( aDataType, aUid, aDocDispatcher, EDocOpenAndSave )
    {
    }

// ---------------------------------------------------------
// void CDocMidletHandler::ConstructL(..)
// Epoc constructor. 
// ---------------------------------------------------------
void CDocMidletHandler::ConstructL()
    {
    BaseConstructL();
    }

// ---------------------------------------------------------
// CDocMidletHandler::~CDocMidletHandler()
// Destructor
// ---------------------------------------------------------
CDocMidletHandler::~CDocMidletHandler()
    {
    }

// ---------------------------------------------------------
// CDocMidletHandler* CDocMidletHandler::NewL(..)
// Returns a contructed CDocMidletHandler object
// ---------------------------------------------------------
CDocMidletHandler* CDocMidletHandler::NewL(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher)
    {
    CDocMidletHandler* self = CDocMidletHandler::NewLC( aDataType,  
                                                      aUid, aDocDispatcher );
    CleanupStack::Pop();    // self
    return self;
    }

// ---------------------------------------------------------
// CDocMidletHandler* CDocMidletHandler::NewLC(..)
// Returns a contructed CDocMidletHandler object. Leaves
// the object in the cleanup stack.
// ---------------------------------------------------------
CDocMidletHandler* CDocMidletHandler::NewLC(
    const TDataType& aDataType,
    const TUid& aUid,
    CDocumentHandler* aDocDispatcher)
    {
    CDocMidletHandler * self = 
        new( ELeave ) CDocMidletHandler( aDataType, aUid,
                                        aDocDispatcher );
    CleanupStack::PushL( self );
    self->ConstructL( );
    return self;
    }

TInt CDocMidletHandler::OpenFileEmbeddedL(RFile& aFileHandle)
    {
    // Midlets cannot be launched as embedded, so just call OpenFileL()
    // here for now.
    return OpenFileL(aFileHandle);
    }

TInt CDocMidletHandler::OpenFileL(RFile& /*aFileHandle*/)
    {
// TODO: This type of application launching is not supported on release 3.0
// Do we need still support midlets?
    return KErrNotSupported;
    }


TBool CDocMidletHandler::IsMidlet(const TUid& aUid)
    {
    // Find out if given UID belongs to a Java Midlet        
    TBool isMidlet = EFalse;

    RApaLsSession   appArcSession;
    TInt error = appArcSession.Connect();
    if (error == KErrNone)
        {
        TApaAppInfo aInfo;
        appArcSession.GetAppInfo(aInfo, aUid);
        #ifdef _DEBUG        
        RDebug::Print(_L("DocumentHandler: CDocMidletHandler::IsMidlet: Checking possible Midlet app = "));
        RDebug::Print(aInfo.iFullName);
        #endif
    
        RFs fs;
        TInt connectError = fs.Connect();
        if (connectError == KErrNone)
            {
            TEntry entry;
            TInt readError = fs.Entry(aInfo.iFullName,entry); // Check if file exists, and get uid
            if (readError == KErrNone)
                {
                TUid uid = TUid::Uid(KUidJavaMidpAppValue);
                if (entry.iType[1] == uid)
                    {
                    isMidlet = ETrue;
                    #ifdef _DEBUG        
                    RDebug::Print(_L("DocumentHandler: CDocMidletHandler::IsMidlet: App is a Midlet app !"));
                    #endif
                    }
                }
            fs.Close();
            }
        else
            {
            #ifdef _DEBUG        
            RDebug::Print(_L("DocumentHandler: CDocMidletHandler::IsMidlet: connect fs error: %d"), connectError);
            #endif
            }
        
        appArcSession.Close(); 
        }

    return isMidlet;    
    }

//  End of File  
