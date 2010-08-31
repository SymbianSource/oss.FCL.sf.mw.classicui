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
* Description:  Test AknClearer.h & eikspace.h
*
*/

#include "testsdkscscreenclearerbase.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSCScreenClearerBase::CTestSDKSCScreenClearerBase
// -----------------------------------------------------------------------------
//
CTestSDKSCScreenClearerBase::CTestSDKSCScreenClearerBase()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKSCScreenClearerBase::~CTestSDKSCScreenClearerBase
// -----------------------------------------------------------------------------
//
CTestSDKSCScreenClearerBase::~CTestSDKSCScreenClearerBase()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKSCScreenClearerBase::ConstructL
// -----------------------------------------------------------------------------
//
void CTestSDKSCScreenClearerBase::ConstructL(RWindowGroup& aParent, TInt aOrdinalPos, TBool aBlankAppStatusPane)
    {
    CAknScreenClearerBase::ConstructL( aParent, aOrdinalPos, aBlankAppStatusPane );
    }
