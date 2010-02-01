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
* Description:  Test AknInputBlock.h
*
*/


/*
 *  [INCLUDE FILES]
 */
#include "activeexample.h"

// -----------------------------------------------------------------------------
// CActiveExample::CActiveExample()
// -----------------------------------------------------------------------------
//
CActiveExample::CActiveExample(): CActive(EPriorityStandard)
{
    iFlag = EFalse;
}

// -----------------------------------------------------------------------------
// CActiveExample::~CActiveExample
// -----------------------------------------------------------------------------
//
CActiveExample::~CActiveExample()
{
    Cancel(); // Cancel any request, if outstanding
    // Delete instance variables if any
    iTimer.Close();
}

// -----------------------------------------------------------------------------
// CActiveExample::DoCancel
// -----------------------------------------------------------------------------
//
void CActiveExample::DoCancel()
    {
    iTimer.Cancel();
    iFlag = ETrue;
    }

// -----------------------------------------------------------------------------
// CActiveExample::ConstructL
// -----------------------------------------------------------------------------
//
void CActiveExample::ConstructL()
    {
    User::LeaveIfError(iTimer.CreateLocal());   // Initialize timer
    CActiveScheduler::Add(this);                // Add to scheduler
    }

// -----------------------------------------------------------------------------
// CActiveExample::NewL
// -----------------------------------------------------------------------------
//
CActiveExample* CActiveExample::NewL()
    {
    CActiveExample* self=CActiveExample::NewLC();
    CleanupStack::Pop( self ); // self;
    return self;
    }

// -----------------------------------------------------------------------------
// CActiveExample::NewLC
// -----------------------------------------------------------------------------
//
CActiveExample* CActiveExample::NewLC()
    {
    CActiveExample* self = new (ELeave)CActiveExample();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CActiveExample::StartL
// -----------------------------------------------------------------------------
//
void CActiveExample::Start(TTimeIntervalMicroSeconds32 aDelay)
    {
    Cancel();                       // Cancel any request, just to be sure
    iState = EUninitialized;
    iTimer.After(iStatus, aDelay);  // Set for later
    SetActive();                    // Tell scheduler a request is active
    }

// -----------------------------------------------------------------------------
// CActiveExample::RunL
// -----------------------------------------------------------------------------
//
void CActiveExample::RunL()
    {
    }

// -----------------------------------------------------------------------------
// CActiveExample::Getflag
// -----------------------------------------------------------------------------
//
TBool CActiveExample::Getflag()
    {
    return iFlag;
    }

// -----------------------------------------------------------------------------
// CActiveExample::Setfalg
// -----------------------------------------------------------------------------
//
void CActiveExample::Setfalg( TBool aFlag )
    {
    iFlag = aFlag;
    }
