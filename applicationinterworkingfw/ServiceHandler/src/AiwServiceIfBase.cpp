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
* Description:    
*
*/




#include <ecom/ecom.h>
#include "AiwServiceIfBase.h"
#include "AiwCommon.h"


EXPORT_C CAiwServiceIfBase::~CAiwServiceIfBase()
    {
    if (iDtorKeyId.iUid)
        {
        REComSession::DestroyedImplementation(iDtorKeyId);
        }
    iCriterias.Close();
    }


void CAiwServiceIfBase::SetDtorKeyId(TUid aDtorKeyId)
    {
    iDtorKeyId = aDtorKeyId;
    }


TBool CAiwServiceIfBase::Match(CAiwCriteriaItem* aItem)
    {
    for (TInt i = 0; i < iCriterias.Count(); i++)
        {   
        if ((iCriterias[i]->ServiceClass() == aItem->ServiceClass()) &&
            (iCriterias[i]->ServiceCmd() == aItem->ServiceCmd()) &&
            (iCriterias[i]->ContentType() == aItem->ContentType()) &&
            (iCriterias[i]->Options() == aItem->Options()) &&
            (iCriterias[i]->DefaultProvider() == aItem->DefaultProvider()))
            {
            return ETrue;
            }
        }

    return EFalse;
    }


void CAiwServiceIfBase::AddCriteria(CAiwCriteriaItem* aItem)
    {
    iCriterias.Append(aItem);
    }



TUid CAiwServiceIfBase::ImplementationUid() const
    {
    return iImplUid;
    }



void CAiwServiceIfBase::SetImplementationUid(TUid aUid)
    {
    iImplUid = aUid;
    }



TBool CAiwServiceIfBase::HasCriteria(CAiwCriteriaItem& aItem) const
    {
    TInt i;

    for (i = 0; i < iCriterias.Count(); i++)
        {
        if (aItem == *(iCriterias[i]))
            {
            return ETrue;
            }
        }

    return EFalse;
    }


EXPORT_C void* CAiwServiceIfBase::ExtensionInterface(TUid /*aInterface*/)
    {
    return NULL;
    }

// Enf of file
