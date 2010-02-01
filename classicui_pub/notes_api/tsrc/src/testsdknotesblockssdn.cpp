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
* Description:  Test AknStaticNoteDialog.h
*
*/


#include <aknstaticnoteDialog.h>
#include <barsread.h>
#include <coeaui.h>
#include <akncontrol.h>
#include <aknsconstants.h>
#include <testsdknotes.rsg>

#include "testsdknotesstaticnotedialog.h"
#include "testsdknotes.h"

const TInt KPoint1 = 10;
const TInt KPoint2 = 20;
// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNSNSIHandleResourceChangeL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNSNSIHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesStaticNoteDialog* noteDialog = new (ELeave) CTestSDKNotesStaticNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_STATICNOTE );
    noteDialog->PostLayoutDynInitL();
    CAknStaticNoteStackIndicator* indicator = noteDialog->Indicator();
    
    indicator->HandleResourceChange( KAknsMessageSkinChange );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNSNSIHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNSNSIHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesStaticNoteDialog* noteDialog = new (ELeave) CTestSDKNotesStaticNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_STATICNOTE );
    noteDialog->PostLayoutDynInitL();
    CAknStaticNoteStackIndicator* indicator = noteDialog->Indicator();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPoint1, KPoint2 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    indicator->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNSNDCAknStaticNoteDialogL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNSNDCAknStaticNoteDialogL( CStifItemParser& /*aItem*/ )
    {
    CAknStaticNoteDialog* noteDialog = new (ELeave) CAknStaticNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNSNDCAknStaticNoteDialogPointerL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNSNDCAknStaticNoteDialogPointerL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog* dialog = new (ELeave) CEikDialog;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    CAknStaticNoteDialog* noteDialog = new (ELeave) CAknStaticNoteDialog( &dialog );
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    CleanupStack::Pop( noteDialog );
    CleanupStack::PopAndDestroy( dialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNSNDDeconstructorL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNSNDDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknStaticNoteDialog* noteDialog = new (ELeave) CAknStaticNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    CleanupStack::Pop( noteDialog );
    delete noteDialog;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNSNDSetNumberOfBordersL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNSNDSetNumberOfBordersL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesStaticNoteDialog* noteDialog = new (ELeave) CTestSDKNotesStaticNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    const TInt number = 5;
    noteDialog->SetNumberOfBorders( number );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNSNDHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNSNDHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesStaticNoteDialog* noteDialog = new (ELeave) CTestSDKNotesStaticNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton2Up;
    
    noteDialog->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNSNDPostLayoutDynInitL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNSNDPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesStaticNoteDialog* noteDialog = new (ELeave) CTestSDKNotesStaticNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_STATICNOTE );
    noteDialog->PostLayoutDynInitL();
    noteDialog->Layout();
    noteDialog->RunLD();
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNSNDOfferKeyEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNSNDOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesStaticNoteDialog* noteDialog = new (ELeave) CTestSDKNotesStaticNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    noteDialog->ExecuteLD( R_TESTSDK_STATICNOTE );
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasConsumed == noteDialog->OfferKeyEventL( keyEvent, EEventKey ) );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }
