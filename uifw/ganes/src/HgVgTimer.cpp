/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

// INCLUDE FILES

#include "HgVgTimer.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CHgVgTimer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHgVgTimer* CHgVgTimer::NewL()
    {
    CHgVgTimer* self = new ( ELeave ) CHgVgTimer();
    CleanupStack::PushL (self );
    self->ConstructL( );
    CleanupStack::Pop ( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgTimer::CHgVgTimer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgVgTimer::CHgVgTimer() : CTimer(CActive::EPriorityStandard)
    {
    CActiveScheduler::Add( this );
    }
        
// -----------------------------------------------------------------------------
// CHgVgTimer::~CHgVgTimer()
// Destructor.
// -----------------------------------------------------------------------------
//
CHgVgTimer::~CHgVgTimer ( )
    {
    Cancel();
    }

// -----------------------------------------------------------------------------
// CHgVgTimer::Start()
// -----------------------------------------------------------------------------
//
void CHgVgTimer::Start( TTimeIntervalMicroSeconds32 aDelay,
                                 TTimeIntervalMicroSeconds32 aInterval,
                                 TCallBack aCallBack)
    {
    iInterval = aInterval.Int();
    iCallBack = aCallBack;
    HighRes( aDelay );
    }

// -----------------------------------------------------------------------------
// CHgVgTimer::RunL()
// -----------------------------------------------------------------------------
//
void CHgVgTimer::RunL()
    {
    HighRes(iInterval);
    iCallBack.CallBack(); 
    }

// End of File
