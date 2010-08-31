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
* Description:  test functions for testing CAknPointerEventSuppressor class
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdktouchuiutil.h"

// CONSTANTS
const TInt KIntervalTime = 1000000;
const TInt KSizelen = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknPointerSuppressorNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknPointerSuppressorNewL( CStifItemParser& /*aItem*/ )
    {
    CAknPointerEventSuppressor* pointersuppressor = CAknPointerEventSuppressor::NewL();
    CleanupStack::PushL( pointersuppressor );
    STIF_ASSERT_NOT_NULL( pointersuppressor );
    CleanupStack::PopAndDestroy( pointersuppressor );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknPointerSuppressorSuppressPointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknPointerSuppressorSuppressPointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknPointerEventSuppressor* pointersuppressor = CAknPointerEventSuppressor::NewL();
    CleanupStack::PushL( pointersuppressor );
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    pointersuppressor->SuppressPointerEvent( event );
    CleanupStack::PopAndDestroy( pointersuppressor );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknPointerSuppressorSetMaxTapDurationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknPointerSuppressorSetMaxTapDurationL( CStifItemParser& /*aItem*/ )
    {
    CAknPointerEventSuppressor* pointersuppressor = CAknPointerEventSuppressor::NewL();
    CleanupStack::PushL( pointersuppressor );
    pointersuppressor->SetMaxTapDuration( KIntervalTime );
    CleanupStack::PopAndDestroy( pointersuppressor );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknPointerSuppressorSetMaxTapMoveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknPointerSuppressorSetMaxTapMoveL( CStifItemParser& /*aItem*/ )
    {
    CAknPointerEventSuppressor* pointersuppressor = CAknPointerEventSuppressor::NewL();
    CleanupStack::PushL( pointersuppressor );
    TSize size( KSizelen, KSizelen);
    pointersuppressor->SetMaxTapMove( size );
    CleanupStack::PopAndDestroy( pointersuppressor );
    
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::TestCAknPointerSuppressorSetMinInterDragIntervalL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::TestCAknPointerSuppressorSetMinInterDragIntervalL( CStifItemParser& /*aItem*/ )
    {
    CAknPointerEventSuppressor* pointersuppressor = CAknPointerEventSuppressor::NewL();
    CleanupStack::PushL( pointersuppressor );
    pointersuppressor->SetMinInterDragInterval( KIntervalTime );
    CleanupStack::PopAndDestroy( pointersuppressor );
    
    return KErrNone;
    }

// End fo file

