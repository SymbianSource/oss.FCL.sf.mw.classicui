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
* Description:  Test EikCcpu.h
*
*/



// [INCLUDE FILES]

#include <eikccpu.h>
#include <eikedwin.h>
#include <eikmenup.h>
#include <avkon.rsg>

#include "testsdkeditors.h"
#include "testsdkeditorsedstateobserver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestCCAknCcpuSupportL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestCCAknCcpuSupportL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin ;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CAknCcpuSupport* ccpu = new (ELeave) CAknCcpuSupport( edwin );
    CleanupStack::PushL( ccpu );
    STIF_ASSERT_NOT_NULL( ccpu );
    
    CleanupStack::PopAndDestroy( ccpu );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestCDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestCDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin ;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CAknCcpuSupport* ccpu = new (ELeave) CAknCcpuSupport( edwin );
    CleanupStack::PushL( ccpu );
    STIF_ASSERT_NOT_NULL( ccpu );
    
    CleanupStack::Pop( ccpu );
    delete ccpu;
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestCConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestCConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin ;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CAknCcpuSupport* ccpu = new (ELeave) CAknCcpuSupport( edwin );
    CleanupStack::PushL( ccpu );
    STIF_ASSERT_NOT_NULL( ccpu );
    
    ccpu->ConstructL();
    
    CleanupStack::PopAndDestroy( ccpu );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestCHandleSelectionChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestCHandleSelectionChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin ;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CAknCcpuSupport* ccpu = new (ELeave) CAknCcpuSupport( edwin );
    CleanupStack::PushL( ccpu );
    STIF_ASSERT_NOT_NULL( ccpu );
    
    ccpu->ConstructL();
    ccpu->HandleSelectionChangeL();
    
    CleanupStack::PopAndDestroy( ccpu );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestCHandleFocusChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestCHandleFocusChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin ;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CAknCcpuSupport* ccpu = new (ELeave) CAknCcpuSupport( edwin );
    CleanupStack::PushL( ccpu );
    STIF_ASSERT_NOT_NULL( ccpu );
    
    ccpu->ConstructL();
    ccpu->HandleFocusChangeL();
    
    CleanupStack::PopAndDestroy( ccpu );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestCOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestCOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin ;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CAknCcpuSupport* ccpu = new (ELeave) CAknCcpuSupport( edwin );
    CleanupStack::PushL( ccpu );
    STIF_ASSERT_NOT_NULL( ccpu );
    
    ccpu->ConstructL();
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasNotConsumed == ccpu->OfferKeyEventL( keyEvent, EEventKey ) );
    
    CleanupStack::PopAndDestroy( ccpu );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestCHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestCHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin ;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CAknCcpuSupport* ccpu = new (ELeave) CAknCcpuSupport( edwin );
    CleanupStack::PushL( ccpu );
    STIF_ASSERT_NOT_NULL( ccpu );
    
    ccpu->ConstructL();
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Up;
    ccpu->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( ccpu );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestCDynInitMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestCDynInitMenuPaneL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin ;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CAknCcpuSupport* ccpu = new (ELeave) CAknCcpuSupport( edwin );
    CleanupStack::PushL( ccpu );
    STIF_ASSERT_NOT_NULL( ccpu );
    
    ccpu->ConstructL();
    
    CTestSDKEditorsEdStateObserver* observer = CTestSDKEditorsEdStateObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    CEikMenuPane* menupane = new (ELeave) CEikMenuPane( observer );
    CleanupStack::PushL( menupane );
    STIF_ASSERT_NOT_NULL( menupane );
    ccpu->DynInitMenuPaneL( R_AVKON_MENUPANE_EMPTY, menupane );
    
    CleanupStack::PopAndDestroy( menupane );
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( ccpu );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestCProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestCProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin ;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    edwin->EnableCcpuSupportL( ETrue );
    
    CAknCcpuSupport* ccpu = new (ELeave) CAknCcpuSupport( edwin );
    CleanupStack::PushL( ccpu );
    STIF_ASSERT_NOT_NULL( ccpu );
    
    ccpu->ConstructL();

    ccpu->ProcessCommandL( EEikCmdEditRedo );
    
    CleanupStack::PopAndDestroy( ccpu );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }
