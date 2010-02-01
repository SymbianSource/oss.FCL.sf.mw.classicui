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
* Description:  test the asynchronous methods of RAknUiServer.
*
*/


#include <pathinfo.h>
 
#include "bctestdomuiserverunlockmedia.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomUiServerUnlockMedia * CBCTestDomUiServerUnlockMedia ::NewLC()
    {
    CBCTestDomUiServerUnlockMedia * self = 
        new( ELeave ) CBCTestDomUiServerUnlockMedia() ;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomUiServerUnlockMedia ::~CBCTestDomUiServerUnlockMedia ()
    {
    Cancel();
    iAknCapServerClient.Close();    
    }
    
// ---------------------------------------------------------------------------
// UnlockCardLD()
// ---------------------------------------------------------------------------
//
void CBCTestDomUiServerUnlockMedia::UnlockCardLD(TBool aStore)
    {
    CleanupStack::Pop(); //this
    iStore = aStore;

    TPath mmcRootPath = PathInfo::MemoryCardRootPath();
    TDriveUnit unit( mmcRootPath );
    TDriveNumber defaultMMCDrive = TDriveNumber( TInt( unit ) );

    StartL( defaultMMCDrive );  
    }  
        
// ---------------------------------------------------------------------------
// From class CActive.
// ---------------------------------------------------------------------------
//
void CBCTestDomUiServerUnlockMedia::DoCancel()
    {   
    iAknCapServerClient.CancelUnlockMedia();    
    }

// ---------------------------------------------------------------------------
// From class CActive.
//  
// ---------------------------------------------------------------------------
//
void CBCTestDomUiServerUnlockMedia::RunL()
    {
    delete this;
    }
    
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomUiServerUnlockMedia::CBCTestDomUiServerUnlockMedia ()
    : CActive(CActive::EPriorityStandard)
    {

    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomUiServerUnlockMedia ::ConstructL()
    {
    CActiveScheduler::Add( this );
    }

// ---------------------------------------------------------------------------
// CAknMemoryCardDialog::StartL
// ---------------------------------------------------------------------------
//
void CBCTestDomUiServerUnlockMedia::StartL( TDriveNumber& aDrive )
    {
    if ( !IsActive() )
        {
        iAknCapServerClient.EnableTaskList( EFalse );         
        iAknCapServerClient.UnlockMedia( aDrive, iStore, iStatus );
        SetActive();
        }       
    }





