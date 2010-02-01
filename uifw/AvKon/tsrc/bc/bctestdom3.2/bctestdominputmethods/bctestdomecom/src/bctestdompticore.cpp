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
* Description:  DomInputMethods test app
*
*/


#include "bctestdompticore.h"

CBCTestDomPtiCore* CBCTestDomPtiCore::NewL()
    {
    CBCTestDomPtiCore* self = new (ELeave) CBCTestDomPtiCore();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    
    }

void CBCTestDomPtiCore::InitializeL(CPtiEngine* /*aOwner*/,
                                    TDes* /*aTextBuffer*/,
                                    CArrayPtrFlat<CPtiCoreLanguage>* /*aLanguageList*/,
                                    TBool /*aUseDefautUserDictionary*/)
{
    
}
    
CBCTestDomPtiCore::~CBCTestDomPtiCore()
    {
    
    }

CBCTestDomPtiCore::CBCTestDomPtiCore()
    {
    
    }

void CBCTestDomPtiCore::ConstructL()
    {
      
    }

