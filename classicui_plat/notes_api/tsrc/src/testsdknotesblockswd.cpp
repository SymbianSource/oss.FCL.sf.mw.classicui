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
* Description:  Test AknWaitDialog.h
*
*/


#include <aknwaitdialog.h>
#include <barsread.h>
#include <coeaui.h>
#include <testsdknotes.rsg>

#include "testsdknotes.h"

const TInt KPoint1 = 10;
const TInt KPoint2 = 20;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWDCAknWaitDialogL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWDCAknWaitDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    CAknWaitDialog* waitDialog = new (ELeave) CAknWaitDialog( &dialog );
    CleanupStack::PushL( waitDialog );
    STIF_ASSERT_NOT_NULL( waitDialog );
    
    CleanupStack::Pop( waitDialog );
    CleanupStack::PopAndDestroy( dialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWDCAknWaitDialogBoolL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWDCAknWaitDialogBoolL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    CAknWaitDialog* waitDialog = new (ELeave) CAknWaitDialog( &dialog, EFalse );
    CleanupStack::PushL( waitDialog );
    STIF_ASSERT_NOT_NULL( waitDialog );
    CleanupStack::Pop( waitDialog );
    
    waitDialog = new (ELeave) CAknWaitDialog( &dialog, ETrue );
    CleanupStack::PushL( waitDialog );
    STIF_ASSERT_NOT_NULL( waitDialog );
    CleanupStack::Pop( waitDialog );
    
    CleanupStack::PopAndDestroy( dialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWDHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWDHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    CAknWaitDialog* waitDialog = new (ELeave) CAknWaitDialog( &dialog, EFalse );
    CleanupStack::PushL( waitDialog );
    STIF_ASSERT_NOT_NULL( waitDialog );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPoint1, KPoint2 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    waitDialog->HandlePointerEventL( event );
    
    CleanupStack::Pop( waitDialog );
    CleanupStack::PopAndDestroy( dialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWDGetProgressInfoL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWDGetProgressInfoL( CStifItemParser& /*aItem*/ )
    {
    // This function will call panic directly, so no need to test it temporary
    return KErrNone;
    
    }

