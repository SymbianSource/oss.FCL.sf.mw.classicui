/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Starts subscribing PubSub key.
*
*/



// INCLUDE FILES
#include    "PslnPropertySubscriber.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// 
// NOTE that callback method is NOT allowed to leave.
// -----------------------------------------------------------------------------
//
CPslnPropertySubscriber::CPslnPropertySubscriber(
    TCallBack aCallBack, RProperty& aProperty )
    : CActive( CActive::EPriorityStandard ), iCallBack( aCallBack ), 
    iProperty( aProperty )
    {
    CActiveScheduler::Add( this );
    }
    
// Destructor
CPslnPropertySubscriber::~CPslnPropertySubscriber()
    {
    Cancel();    
    }

// -----------------------------------------------------------------------------
// CPslnPropertySubscriber::Subscribe
// -----------------------------------------------------------------------------
//
void CPslnPropertySubscriber::Subscribe()
    {
    if ( !IsActive() )
        {
        iProperty.Subscribe( iStatus );
        SetActive();
        }
    }

// -----------------------------------------------------------------------------
// CPslnPropertySubscriber::RunL
// -----------------------------------------------------------------------------
//
void CPslnPropertySubscriber::RunL()
    {
    if ( iStatus.Int() == KErrNone )
        {
        Subscribe();
        iCallBack.CallBack();
        }
    }

// -----------------------------------------------------------------------------
// CPslnPropertySubscriber::DoCancel
// -----------------------------------------------------------------------------
//
void CPslnPropertySubscriber::DoCancel()
    {
    iProperty.Cancel();
    }

//  End of File  
