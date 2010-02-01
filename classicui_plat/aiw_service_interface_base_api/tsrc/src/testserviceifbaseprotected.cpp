/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:    Test aiwserviceifbase.h
*
*/



/*
 * Include files
 */
#include "testserviceifbaseprotected.h"

// -----------------------------------------------------------------------------
// CServiceIfBase::CServiceIfBase
// -----------------------------------------------------------------------------
//
CTestServiceIfBaseProtected::CTestServiceIfBaseProtected()
{
}

// -----------------------------------------------------------------------------
// CServiceIfBase::~CServiceIfBase
// -----------------------------------------------------------------------------
//
CTestServiceIfBaseProtected::~CTestServiceIfBaseProtected()
{
}

// -----------------------------------------------------------------------------
// CServiceIfBase::InitialiseL
// -----------------------------------------------------------------------------
//
void CTestServiceIfBaseProtected::InitialiseL(
        MAiwNotifyCallback& /*aFrameworkCallback*/,
        const RCriteriaArray& /*aInterest*/)
    {
    
    }

// -----------------------------------------------------------------------------
// CServiceIfBase::HandleServiceCmdL
// -----------------------------------------------------------------------------
//
void CTestServiceIfBaseProtected::HandleServiceCmdL(
    const TInt& /*aCmdId*/,
    const CAiwGenericParamList& /*aInParamList*/,
    CAiwGenericParamList& /*aOutParamList*/,
    TUint /*aCmdOptions*/,
    const MAiwNotifyCallback* /*aCallback*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CServiceIfBase::ExtensionInterface
// -----------------------------------------------------------------------------
//
void* CTestServiceIfBaseProtected::ExtensionInterface(TUid /*aInterface*/)
    {
    return NULL;
    }
