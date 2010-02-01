/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test genericparamconsumer.h
*
*/



#include <genericparamconsumer.h>

#include "testdomgenparamext.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// default constructor
// -----------------------------------------------------------------------------
//
CAiwGenericParamConsumerExt::CAiwGenericParamConsumerExt(
        CEikApplication& aApp ) : CAiwGenericParamConsumer( aApp )
    {
    }

// -----------------------------------------------------------------------------
// CAiwGenericParamConsumerExt::CreateAppUiL
// -----------------------------------------------------------------------------
//
CEikAppUi* CAiwGenericParamConsumerExt::CreateAppUiL()
    {
    return NULL;
    }

// -----------------------------------------------------------------------------
// CAiwGenericParamConsumerExt::DoGetInputParameters
// -----------------------------------------------------------------------------
//
const CAiwGenericParamList* CAiwGenericParamConsumerExt::DoGetInputParameters() const
    {
    return GetInputParameters();
    }

// -----------------------------------------------------------------------------
// CAiwGenericParamConsumerExt::DoSetOutputParamsL
// -----------------------------------------------------------------------------
//
void CAiwGenericParamConsumerExt::DoSetOutputParamsL(
        const CAiwGenericParamList* aList )
    {
    SetOutputParamsL( aList );
    }

