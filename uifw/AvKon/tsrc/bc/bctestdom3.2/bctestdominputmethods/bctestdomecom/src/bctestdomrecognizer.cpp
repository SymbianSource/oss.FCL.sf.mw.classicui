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


#include "bctestdomrecognizer.h"

CBCTestDomHwrRecognizer* CBCTestDomHwrRecognizer::NewL()
    {
    CBCTestDomHwrRecognizer* self = new (ELeave) CBCTestDomHwrRecognizer;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    
    }
    
CBCTestDomHwrRecognizer::~CBCTestDomHwrRecognizer()
    {
    
    }

CBCTestDomHwrRecognizer::CBCTestDomHwrRecognizer()
    {
    
    }

void CBCTestDomHwrRecognizer::ConstructL()
    {
      
    }
    
