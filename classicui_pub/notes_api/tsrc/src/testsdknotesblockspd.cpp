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
* Description:  Test AknProgressDialog.h
*
*/


#include <aknprogressdialog.h>
#include <barsread.h>
#include <coeaui.h>
#include <testsdknotes.rsg>

#include "testsdknotesprogressdialog.h"
#include "testsdknotes.h"

const TInt KFinalValue = 200;
const TInt KIncrement = 100;
const TInt KInterval = 20;
const TInt KPoint1 = 10;
const TInt KPoint2 = 20;

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDCAknProgressDialogValueL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDCAknProgressDialogValueL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    CAknProgressDialog* progressDialog = new (ELeave) CAknProgressDialog( KFinalValue, KIncrement, KInterval, &dialog );
    CleanupStack::PushL( progressDialog );
    STIF_ASSERT_NOT_NULL( progressDialog );
    
    CleanupStack::Pop( progressDialog );
    CleanupStack::PopAndDestroy( dialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDCAknProgressDialogPointerL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDCAknProgressDialogPointerL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    CAknProgressDialog* progressDialog = new (ELeave) CAknProgressDialog( &dialog );
    CleanupStack::PushL( progressDialog );
    STIF_ASSERT_NOT_NULL( progressDialog );
    
    CleanupStack::Pop( progressDialog );
    CleanupStack::PopAndDestroy( dialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDCAknProgressDialogL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDCAknProgressDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    CAknProgressDialog* progressDialog = new (ELeave) CAknProgressDialog( &dialog, ETrue );
    CleanupStack::PushL( progressDialog );
    STIF_ASSERT_NOT_NULL( progressDialog );
    
    CleanupStack::Pop( progressDialog );
    CleanupStack::PopAndDestroy( dialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDDeconstructorL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDDeconstructorL( CStifItemParser& /*aItem*/ )
    {    
    CAknProgressDialog* progressDialog = new (ELeave) CAknProgressDialog( KFinalValue, KIncrement, KInterval, NULL );
    CleanupStack::PushL( progressDialog );
    STIF_ASSERT_NOT_NULL( progressDialog );
    
    CleanupStack::Pop( progressDialog );
    delete progressDialog;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDRunLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDRunLD( CStifItemParser& /*aItem*/ )
    {
    CAknProgressDialog* progressDialog = new (ELeave) CAknProgressDialog( KFinalValue, KIncrement, KInterval, NULL );
    CleanupStack::PushL( progressDialog );

    progressDialog->PrepareLC( R_TESTSDK_PROGRESS_NOTE );
    progressDialog->RunLD();
    
    progressDialog->ProcessFinishedL();
    CleanupStack::Pop( progressDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDGetProgressInfoL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDGetProgressInfoL( CStifItemParser& /*aItem*/ )
    {
    CAknProgressDialog* progressDialog = new (ELeave) CAknProgressDialog( KFinalValue, KIncrement, KInterval, NULL );
    CleanupStack::PushL( progressDialog );
    STIF_ASSERT_NOT_NULL( progressDialog );
    CleanupStack::Pop( progressDialog );
    
    progressDialog->PrepareLC( R_TESTSDK_PROGRESS_NOTE );
    CEikProgressInfo* progressBar = progressDialog->GetProgressInfoL();
    STIF_ASSERT_NOT_NULL( progressBar );
    
    CleanupStack::PopAndDestroy( progressDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDOfferKeyEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CAknProgressDialog* progressDialog = new (ELeave) CAknProgressDialog( KFinalValue, KIncrement, KInterval, NULL );
    CleanupStack::PushL( progressDialog );
    STIF_ASSERT_NOT_NULL( progressDialog );
    
    progressDialog->ExecuteLD( R_TESTSDK_PROGRESS_NOTE );
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasConsumed == progressDialog->OfferKeyEventL( keyEvent, EEventKeyUp ) );
    
    progressDialog->ProcessFinishedL();
    
    CleanupStack::Pop( progressDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDProcessFinishedL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDProcessFinishedL( CStifItemParser& /*aItem*/ )
    {
    CAknProgressDialog* progressDialog = new (ELeave) CAknProgressDialog( KFinalValue, KIncrement, KInterval, NULL );
    CleanupStack::PushL( progressDialog );

    progressDialog->ExecuteLD( R_TESTSDK_PROGRESS_NOTE );
    
    progressDialog->ProcessFinishedL();
    CleanupStack::Pop( progressDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDSetCallbackL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDSetCallbackL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesProgressDialog* progressDialog = new (ELeave) CTestSDKNotesProgressDialog( KFinalValue, KIncrement, KInterval, NULL );
    CleanupStack::PushL( progressDialog );

    progressDialog->ExecuteLD( R_TESTSDK_PROGRESS_NOTE );
    
    progressDialog->ProcessFinishedL();
    CleanupStack::Pop( progressDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesProgressDialog* progressDialog = new (ELeave) CTestSDKNotesProgressDialog( KFinalValue, KIncrement, KInterval, NULL );
    CleanupStack::PushL( progressDialog );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPoint1, KPoint2 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    progressDialog->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( progressDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDPreLayoutDynInitL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesProgressDialog* progressDialog = new (ELeave) CTestSDKNotesProgressDialog( KFinalValue, KIncrement, KInterval, NULL );
    CleanupStack::PushL( progressDialog );
    
    progressDialog->PrepareLC( R_TESTSDK_PROGRESS_NOTE );
    progressDialog->PreLayoutDynInitL();
    progressDialog->RunLD();
    
    progressDialog->ProcessFinishedL();
    CleanupStack::Pop( progressDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPDOkToExitL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPDOkToExitL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesProgressDialog* progressDialog = new (ELeave) CTestSDKNotesProgressDialog( KFinalValue, KIncrement, KInterval, NULL );
    CleanupStack::PushL( progressDialog );
    
    progressDialog->PrepareLC( R_TESTSDK_PROGRESS_NOTE );
    progressDialog->RunLD();
    progressDialog->OkToExitL( EAknSoftkeyDone );

    CleanupStack::PopAndDestroy( progressDialog );
    
    return KErrNone;
    
    }
