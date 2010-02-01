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
* Description:     Criteria binding base class declaration.
*
*/





#ifndef _AIW_BINDING_H
#define _AIW_BINDING_H

#include "AiwCommon.h" 
#include "AiwServiceIfBase.h"

class CAiwBinding : public CBase
    {
    public:
        static CAiwBinding* NewL();
        static CAiwBinding* NewLC();

        inline virtual ~CAiwBinding();
        inline RPointerArray<CAiwCriteriaItem>& Interest(); 
        inline void AddCriteriaL(CAiwCriteriaItem* aItem);
        inline CAiwServiceIfBase* BaseProvider(TInt aIndex);
        inline TInt NumberOfProviders() const;
        void AddProviderL(CAiwServiceIfBase* aProvider, TBool aIsDefault);
        TBool RemoveProvider(TInt aImplUid);
        TInt HasCriteriaItem(CAiwCriteriaItem& aItem) const;
        void RemoveCriteria(TInt aIndex);
        TBool HasProvider(CAiwServiceIfBase* aProvider) const;
        TBool HasServiceCmd(TInt aServiceCmd) const;
    protected:
        inline CAiwBinding();
    
    private:
    
    protected:
        RPointerArray<CAiwCriteriaItem> iInterest;
        RPointerArray<CAiwServiceIfBase> iProviders;
    };


#include "AiwBinding.inl"

#endif

// End of file
