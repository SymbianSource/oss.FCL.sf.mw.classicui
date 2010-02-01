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
* Description:  Active engine helper class implementation for BCTestGlobalListMsgQuery.
*
*/

// INCLUDE FILES
#include "bctestactiveengine.h"

// ================= MEMBER FUNCTIONS =========================================

// ---------------------------------------------------------------------------
// CBCTestActiveEngine::CBCTestActiveEngine()
// ---------------------------------------------------------------------------
//
CBCTestActiveEngine::CBCTestActiveEngine()
: CActive( EPriorityStandard )
    {
    CActiveScheduler::Add( this );
    }

// ---------------------------------------------------------------------------
// CBCTestActiveEngine::~CBCTestActiveEngine()
// ---------------------------------------------------------------------------
//
CBCTestActiveEngine::~CBCTestActiveEngine()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestActiveEngine::GetStatus()
// ---------------------------------------------------------------------------
//
TRequestStatus* CBCTestActiveEngine::GetStatus()
    {
    return &iStatus;
    }

// ---------------------------------------------------------------------------
// CBCTestActiveEngine::RunL()
// ---------------------------------------------------------------------------
//
void CBCTestActiveEngine::RunL()
    {
    Cancel();
    }
    
// ---------------------------------------------------------------------------
// CBCTestActiveEngine::DoCancel()
// ---------------------------------------------------------------------------
//
void CBCTestActiveEngine::DoCancel()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestActiveEngine::Active()
// ---------------------------------------------------------------------------
//
TBool CBCTestActiveEngine::Active()
    {
    return IsActive();
    }

// ---------------------------------------------------------------------------
// CBCTestActiveEngine::MakeActive()
// ---------------------------------------------------------------------------
//
void CBCTestActiveEngine::MakeActive()
    {
    SetActive();
    }

// End of file
