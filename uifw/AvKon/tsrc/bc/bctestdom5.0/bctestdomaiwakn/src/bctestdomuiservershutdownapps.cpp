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
* Description:  test the asynchronous method RAknUiServer::ShutdownApps().
*
*/


#include <AknSgcc.h>
#include "bctestdomuiservershutdownapps.h"

 
// ======== MEMBER FUNCTIONS ========


// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomUiServerShutdownApps * CBCTestDomUiServerShutdownApps ::NewLC()
    {
    CBCTestDomUiServerShutdownApps * self = 
        new( ELeave ) CBCTestDomUiServerShutdownApps;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomUiServerShutdownApps ::~CBCTestDomUiServerShutdownApps ()
    {
    Cancel();    
    }

// ---------------------------------------------------------------------------
// UnlockCardLD()
// ---------------------------------------------------------------------------
//
void CBCTestDomUiServerShutdownApps::ShutdownAppsLD(
    const TUid aRequesterUID, 
    const TInt aTimeoutInMicroseconds )
    {
    CleanupStack::Pop(); //this
    
    if ( iAknCapServerClient && iAknCapServerClient->Handle() )
        {
        StartL( aRequesterUID,aTimeoutInMicroseconds );
        }  
    else
        {
        delete this;
        }
    }
        
// ---------------------------------------------------------------------------
// From class CActive.
// ---------------------------------------------------------------------------
//
void CBCTestDomUiServerShutdownApps::DoCancel()
    {   
    if ( iAknCapServerClient && iAknCapServerClient->Handle() )
        {
        iAknCapServerClient->CancelShutdownApps();        
        }    
    }

// ---------------------------------------------------------------------------
// From class CActive.
//  
// ---------------------------------------------------------------------------
//
void CBCTestDomUiServerShutdownApps::RunL()
    {
    delete this;
    }
   
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomUiServerShutdownApps ::CBCTestDomUiServerShutdownApps ()
    : CActive(CActive::EPriorityStandard)
    {

    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomUiServerShutdownApps ::ConstructL()
    {
    iAknCapServerClient = CAknSgcClient::AknSrv();
    CActiveScheduler::Add( this );    
    }

// ---------------------------------------------------------------------------
// CAknMemoryCardDialog::StartL
// ---------------------------------------------------------------------------
//
void CBCTestDomUiServerShutdownApps::StartL( 
    const TUid aRequesterUID, 
    const TInt aTimeoutInMicroseconds )
    {    
    if ( !IsActive() )
        {        
        
        iAknCapServerClient->ShutdownApps( 
            aRequesterUID, 
            aTimeoutInMicroseconds,
            iStatus );
            
        SetActive();
        }       
    }
    

