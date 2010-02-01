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




#include "AiwBinding.h"


CAiwBinding* CAiwBinding::NewL()
    {
    return new (ELeave) CAiwBinding();
    }



CAiwBinding* CAiwBinding::NewLC()
    {
    CAiwBinding* bind = new (ELeave) CAiwBinding();
    CleanupStack::PushL(bind);
    return bind;
    }


void CAiwBinding::AddProviderL(CAiwServiceIfBase* aProvider, TBool aIsDefault)
    {
    if (aIsDefault)
        {
        // Default provider will be the first item in array.
        User::LeaveIfError(iProviders.Insert(aProvider, 0));
        }
    else
        {
        User::LeaveIfError(iProviders.Append(aProvider));
        }
    }



TInt CAiwBinding::HasCriteriaItem(CAiwCriteriaItem& aItem) const
    {
    const TInt count = iInterest.Count();
    for (TInt i = 0; i < count; i++)
        {
        if ((*iInterest[i]) == aItem)
            {
            return i;
            }
        }

    return KErrNotFound;
    }


TBool CAiwBinding::HasProvider(CAiwServiceIfBase* aProvider) const
    {
    for (TInt i = 0; i < iProviders.Count(); i++)
        {
        if (iProviders[i] == aProvider)
            {
            return ETrue;
            }
        }

    return EFalse;
    }


void CAiwBinding::RemoveCriteria(TInt aIndex)
    {
    iInterest.Remove( aIndex ); 
    }


TBool CAiwBinding::RemoveProvider(TInt aImplUid)
    {
    for (TInt i = 0; i < iProviders.Count(); i++)
        {
        if (iProviders[i]->ImplementationUid().iUid == aImplUid)
            {
            iProviders.Remove( i );
            return ETrue;
            }
        }

    return EFalse;
    }

    
TBool CAiwBinding::HasServiceCmd(TInt aServiceCmd) const    
    {
    for (TInt i = 0; i < iInterest.Count(); i++)
        {
        if(iInterest[i]->ServiceCmd() == aServiceCmd)
            {
            return ETrue;
            }
        }
    return EFalse;
    }

// End of file
