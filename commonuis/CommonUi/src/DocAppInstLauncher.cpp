/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This module contains the implementation of CDocAppInstLauncher 
*
*/


// INCLUDE FILES
#include <f32file.h>
#include "DocAppInstLauncher.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CDocAppInstLauncher::CDocAppInstLauncher
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CDocAppInstLauncher::CDocAppInstLauncher() 
    : CActive( CActive::EPriorityStandard )
    {
    }

// -----------------------------------------------------------------------------
// CDocAppInstLauncher::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDocAppInstLauncher::ConstructL()
    {
    CActiveScheduler::Add( this );    
    }

// -----------------------------------------------------------------------------
// CDocAppInstLauncher::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDocAppInstLauncher* CDocAppInstLauncher::NewL()
    {
    CDocAppInstLauncher* self = new( ELeave ) CDocAppInstLauncher();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;    
    }
    
// Destructor
CDocAppInstLauncher::~CDocAppInstLauncher()
    {    
    Cancel();        
    }

// -----------------------------------------------------------------------------
// CDocAppInstLauncher::InstallL
// Handle install request.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//    
void CDocAppInstLauncher::InstallL( RFile& aFile )
    {
    iCalledWithParams = EFalse;    
    User::LeaveIfError( iLauncher.Connect() );
    iLauncher.Install( iStatus, aFile );
    SetActive();    
    }
    
// -----------------------------------------------------------------------------
// CDocAppInstLauncher::InstallL
// Handle install request.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//    
void CDocAppInstLauncher::InstallL( RFile& aFile, const TDesC8& aOptions )
    {
    iCalledWithParams = ETrue;    
    User::LeaveIfError( iLauncher.Connect() );
    iLauncher.Install( iStatus, aFile, aOptions );
    SetActive();    
    }    

// -----------------------------------------------------------------------------
// CDocAppInstLauncher::SetExitObserver
// Set exit observer
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//    
void CDocAppInstLauncher::SetExitObserver( MAknServerAppExitObserver* aObserver )
    {
    __ASSERT_DEBUG ( 
        aObserver, 
        User::Panic ( _L ( "DocumentHandler" ), KErrUnknown ) );
    iExitObserver = aObserver;
    }

// -----------------------------------------------------------------------------
// CDocAppInstLauncher::RunL
// Called by framework when request is finished.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//    
void CDocAppInstLauncher::RunL()
    {
    // Close the installer
    iLauncher.Close();    

	// We have to inform launcher application that installer has exited.
    if ( iExitObserver )
        {
        #ifdef _DEBUG        
         RDebug::Print( _L("DocumentHandler: CDocAppInstLauncher::RunL : Exit notification forwarded."));
        #endif 
        iExitObserver->HandleServerAppExit( 0 );
        }
    }

// -----------------------------------------------------------------------------
// CDocAppInstLauncher::DoCancelL
// Called by framework when request is cancelled.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
// 
void CDocAppInstLauncher::DoCancel()
    {
    if ( iCalledWithParams )
        {
         iLauncher.CancelAsyncRequest( SwiUI::ERequestInstallParamsHandle );
        }
    else
        {
        iLauncher.CancelAsyncRequest( SwiUI::ERequestInstallHandle );
        }
    iLauncher.Close();    
    }


//  End of File  
