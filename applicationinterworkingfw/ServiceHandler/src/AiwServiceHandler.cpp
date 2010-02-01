/*
* Copyright (c) 2003-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Implements API for consumer application to access Application
*                Interworking Framework. 
*
*/




#include <eikenv.h>
#include <aiwservicehandler.rsg>
#include "AiwMenuBinding.h"
#include "AiwServiceHandler.h"
#include "AiwServiceHandlerImpl.h"
#include "AiwMenu.h"
#include "AiwUids.hrh"
#include "AiwCommon.hrh"
#include "AiwTlsData.h"

//
// AiwServiceHandler
//

EXPORT_C CAiwServiceHandler* CAiwServiceHandler::NewL()
    {
    CAiwServiceHandler* handler = new (ELeave) CAiwServiceHandler();
    CleanupStack::PushL( handler );
    handler->ConstructL();
    CleanupStack::Pop(); // handler
    return handler;
    }


EXPORT_C CAiwServiceHandler* CAiwServiceHandler::NewLC()
    {
    CAiwServiceHandler* handler = new (ELeave) CAiwServiceHandler();
    CleanupStack::PushL( handler );
    handler->ConstructL();
    return handler;     
    }


CAiwServiceHandler::CAiwServiceHandler()
    {
    // Nothing to do here.
    }


void CAiwServiceHandler::ConstructL()
    {
    iImpl = CAiwServiceHandlerImpl::NewL();
    }


EXPORT_C CAiwServiceHandler::~CAiwServiceHandler()
    {
    delete iImpl;
    }


EXPORT_C void CAiwServiceHandler::Reset()
    {
    iImpl->Reset();
    }


EXPORT_C TInt CAiwServiceHandler::NbrOfProviders(const CAiwCriteriaItem* aCriteria)
    {
    return iImpl->NbrOfProviders(aCriteria);
    }


EXPORT_C void CAiwServiceHandler::AttachL(TInt aInterestResourceId)
    {
    iImpl->AttachL(aInterestResourceId);
    }


EXPORT_C void CAiwServiceHandler::AttachL(const RCriteriaArray& aInterest)
    {
    iImpl->AttachL(aInterest);
    }


EXPORT_C void CAiwServiceHandler::GetInterest(RCriteriaArray& aInterest)
    {
    iImpl->GetInterest(aInterest);
    }
    
    
EXPORT_C void CAiwServiceHandler::DetachL(const RCriteriaArray& aInterest)
    {
    iImpl->DetachL(aInterest);
    }


EXPORT_C void CAiwServiceHandler::DetachL(TInt aInterestResourceId)
    {
    iImpl->DetachL(aInterestResourceId);
    }


EXPORT_C const CAiwCriteriaItem* CAiwServiceHandler::GetCriteria(TInt aId)
    {
    return iImpl->GetCriteria(aId);
    }


EXPORT_C void CAiwServiceHandler::InitializeMenuPaneL(
    CEikMenuPane& aMenuPane,
    TInt aMenuResourceId,
    TInt aBaseMenuCmdId,
    const CAiwGenericParamList& aInParamList)
    {
    iImpl->InitializeMenuPaneL(aMenuPane, 
        aMenuResourceId, 
        aBaseMenuCmdId, 
        aInParamList);   
    }

    
EXPORT_C void CAiwServiceHandler::InitializeMenuPaneL(
    CEikMenuPane& aMenuPane,
    TInt aMenuResourceId,
    TInt aBaseMenuCmdId,
    const CAiwGenericParamList& aInParamList,
    TBool aUseSubmenuTextsIfAvailable)
    {
    iImpl->InitializeMenuPaneL(aMenuPane, 
        aMenuResourceId, 
        aBaseMenuCmdId, 
        aInParamList, 
        aUseSubmenuTextsIfAvailable);
    }    


EXPORT_C void CAiwServiceHandler::InitializeMenuPaneL(
    CEikMenuPane& aMenuPane,
    TInt aMenuResourceId,
    TInt aBaseMenuCmdId,
    const CAiwGenericParamList& aInParamList,
    TBool aUseSubmenuTextsIfAvailable,
    TBool aSetAsItemSpecific )
    {
    iImpl->InitializeMenuPaneL(aMenuPane, 
        aMenuResourceId, 
        aBaseMenuCmdId, 
        aInParamList, 
        aUseSubmenuTextsIfAvailable,
        aSetAsItemSpecific);
    }    

    
EXPORT_C TInt CAiwServiceHandler::ServiceCmdByMenuCmd(TInt aMenuCmdId) const
    {
    return iImpl->ServiceCmdByMenuCmd(aMenuCmdId);
    }


EXPORT_C void CAiwServiceHandler::ExecuteMenuCmdL(
    TInt aMenuCmdId,
    const CAiwGenericParamList& aInParamList,
    CAiwGenericParamList& aOutParamList,
    TUint aCmdOptions,
    MAiwNotifyCallback* aCallback)
    {
    iImpl->ExecuteMenuCmdL(aMenuCmdId, aInParamList, aOutParamList, aCmdOptions, aCallback);
    }


EXPORT_C void CAiwServiceHandler::AttachMenuL(TInt aMenuResourceId, TInt aInterestResourceId)
    {
    iImpl->AttachMenuL(aMenuResourceId, aInterestResourceId);
    }


EXPORT_C void CAiwServiceHandler::AttachMenuL(TInt aMenuResourceId, TResourceReader& aReader)
    {
    iImpl->AttachMenuL(aMenuResourceId, aReader);
    }


EXPORT_C void CAiwServiceHandler::AttachMenuL(TInt aMenuResourceId, const RCriteriaArray& aInterest)
    {
    iImpl->AttachMenuL(aMenuResourceId, aInterest);
    }    


EXPORT_C void CAiwServiceHandler::DetachMenu(TInt aMenuResourceId, TInt aInterestResourceId)
    {
    iImpl->DetachMenu(aMenuResourceId, aInterestResourceId);
    }


EXPORT_C TBool CAiwServiceHandler::IsSubMenuEmpty(TInt aSubMenuId)
    {
    return iImpl->IsSubMenuEmpty(aSubMenuId);
    }


EXPORT_C void CAiwServiceHandler::ExecuteServiceCmdL(
    const TInt& aCmdId,
    const CAiwGenericParamList& aInParamList,
    CAiwGenericParamList& aOutParamList,
    TUint aCmdOptions,
    MAiwNotifyCallback* aCallback)
    {
    iImpl->ExecuteServiceCmdL(aCmdId, aInParamList, aOutParamList, aCmdOptions, aCallback);
    }


EXPORT_C CAiwGenericParamList& CAiwServiceHandler::InParamListL()
    {
    return iImpl->InParamListL();
    }


EXPORT_C CAiwGenericParamList& CAiwServiceHandler::OutParamListL()
    {
    return iImpl->OutParamListL();
    }


EXPORT_C TBool CAiwServiceHandler::IsAiwMenu(TInt aMenuResourceId)
    {
    return iImpl->IsAiwMenu(aMenuResourceId);
    }


EXPORT_C TBool CAiwServiceHandler::HandleSubmenuL(CEikMenuPane& aPane)
    {
    return iImpl->HandleSubmenuL(aPane);
    }


EXPORT_C void CAiwServiceHandler::ReportMenuLaunch()
    {
    CAiwTlsData* data = CAiwTlsData::Instance();
    if(data)
        {
        data->ReportMenuLaunch();
        }
    }

// End of file
