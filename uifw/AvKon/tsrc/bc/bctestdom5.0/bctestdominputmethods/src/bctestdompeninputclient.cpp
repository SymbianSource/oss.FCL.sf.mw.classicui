/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for peninput client
*
*/


// INCLUDE FILES

#include "peninputclient.h"
#include "bctestdompeninputclient.h"

// ---------------------------------------------------------------------------
// CMPenUiA::CMPenUiA
// ---------------------------------------------------------------------------
//   
CMPenUiA::CMPenUiA()
    {
    }

// ---------------------------------------------------------------------------
// CMPenUiA::OnPeninputUiDeactivated
// ---------------------------------------------------------------------------
//   
void CMPenUiA::OnPeninputUiDeactivated()
    {
    }

// ---------------------------------------------------------------------------
// CMPenUiA::OnPeninputUiActivated
// ---------------------------------------------------------------------------
//   
void CMPenUiA::OnPeninputUiActivated()
    {
    }
    
// ---------------------------------------------------------------------------
// CPenUiNotificationHandler::NewL
// ---------------------------------------------------------------------------
//   
CPenUiNotificationHandler* CPenUiNotificationHandler::NewL(
                                            MPenUiActivationHandler* aHandler,
                                            RPeninputServer* aClient )
    {
    CPenUiNotificationHandler* self = new ( ELeave ) 
                                    CPenUiNotificationHandler( aHandler, aClient );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// CPenUiNotificationHandler::CPenUiNotificationHandler
// ---------------------------------------------------------------------------
//   
CPenUiNotificationHandler::CPenUiNotificationHandler(
                    MPenUiActivationHandler* aHandler,RPeninputServer* aClient)
                    : iHandler( aHandler ), iClient( aClient )
    {    
    }

// ---------------------------------------------------------------------------
// CPenUiNotificationHandler::ConstructL
// ---------------------------------------------------------------------------
//   
void CPenUiNotificationHandler::ConstructL()
    {
    }
    
    
// ---------------------------------------------------------------------------
// CPenUiNotificationHandler::HandleServerEventL
// ---------------------------------------------------------------------------
//   
TBool CPenUiNotificationHandler::HandleServerEventL( TInt /*aEventId*/ )
    {
    return ETrue;
    }

// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::NewL
// ---------------------------------------------------------------------------
//   
CBCTestDomHwrRecognizer* CBCTestDomHwrRecognizer::NewL( TInt aImpId )
    {
    CBCTestDomHwrRecognizer* self = 
                static_cast< CBCTestDomHwrRecognizer* >( CHwrRecognizer::NewL( aImpId ) );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::IsSupportUdm
// ---------------------------------------------------------------------------
//   
TBool CBCTestDomHwrRecognizer::IsSupportUdm()
    {
    return CHwrRecognizer::IsSupportUdm();
    }

// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::LoadUdmL
// ---------------------------------------------------------------------------
//   
void CBCTestDomHwrRecognizer::LoadUdmL( TUdmType aType )   
    {
    CHwrRecognizer::LoadUdmL( aType );
    }

// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::UnLoadUdmL
// ---------------------------------------------------------------------------
//   
void CBCTestDomHwrRecognizer::UnLoadUdmL( TUdmType aType )
    {
    CHwrRecognizer::UnLoadUdmL( aType );
    }

// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::GetModelIndexListL
// ---------------------------------------------------------------------------
//   
void CBCTestDomHwrRecognizer::GetModelIndexListL( TUdmType aType, 
                             RArray<TInt>& aList, 
                             const THwrUdmRange& aRange )
    {
    CHwrRecognizer::GetModelIndexListL( aType, aList, aRange );
    }

// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::GetSymbolModelL
// ---------------------------------------------------------------------------
//   
void CBCTestDomHwrRecognizer::GetSymbolModelL( TUdmType aType, 
                                            TInt aIndex, 
                                            TPtrC& aSymbolName,
                                            RArray<TPoint>& aModel, 
                                            TInt& aHelpLine, TInt& aBaseLine )
    {
    CHwrRecognizer::GetSymbolModelL( aType, 
                                     aIndex,  
                                     aSymbolName,
                                     aModel,
                                     aHelpLine, 
                                     aBaseLine );
    }
// End of File
