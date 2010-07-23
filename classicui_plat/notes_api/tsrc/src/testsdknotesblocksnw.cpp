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
* Description:  Test AknNoteWrappers.h
*
*/


#include <aknnotewrappers.h>
#include <testsdknotes.rsg>

#include "testsdknotesresourcenotedialog.h"
#include "testsdknotes.h"
#include "testsdknotescontrol.h"

const TInt KLength = 10;
const TInt KPoint1 = 10;
const TInt KPoint2 = 30;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWCAknNoteWrapperL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWCAknNoteWrapperL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteWrapper* noteWrapper = new (ELeave) CAknNoteWrapper;
    CleanupStack::PushL( noteWrapper );
    STIF_ASSERT_NOT_NULL( noteWrapper );
    
    CleanupStack::PopAndDestroy( noteWrapper );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWCAknNoteWrapperPointerL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWCAknNoteWrapperPointerL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteWrapper* wrapper = new (ELeave) CAknNoteWrapper;
    CleanupStack::PushL( wrapper );
    STIF_ASSERT_NOT_NULL( wrapper );
    
    CAknNoteWrapper* noteWrapper = new (ELeave) CAknNoteWrapper( &wrapper );
    CleanupStack::PushL( noteWrapper );
    STIF_ASSERT_NOT_NULL( noteWrapper );
    
    CleanupStack::Pop( noteWrapper );
    CleanupStack::PopAndDestroy( wrapper );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWExecuteLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWExecuteLD( CStifItemParser& /*aItem*/ )
    {
    CAknNoteWrapper* noteWrapper = new (ELeave) CAknNoteWrapper;
    CleanupStack::PushL( noteWrapper );
    STIF_ASSERT_NOT_NULL( noteWrapper );
    CleanupStack::Pop( noteWrapper );
    
    noteWrapper->ExecuteLD( R_TESTSDK_NOTEWRAPPER );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWExecutePromptLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWExecutePromptLD( CStifItemParser& /*aItem*/ )
    {
    CAknNoteWrapper* noteWrapper = new (ELeave) CAknNoteWrapper;
    CleanupStack::PushL( noteWrapper );
    STIF_ASSERT_NOT_NULL( noteWrapper );
    CleanupStack::Pop( noteWrapper );
    
    _LIT( KPrompt, "Wrapper" );
    TBuf<KLength> prompt( KPrompt );
    noteWrapper->ExecuteLD( R_TESTSDK_NOTEWRAPPERNOTEXT, prompt );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteWrapper* noteWrapper = new (ELeave) CAknNoteWrapper;
    CleanupStack::PushL( noteWrapper );
    STIF_ASSERT_NOT_NULL( noteWrapper );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPoint1, KPoint2 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    noteWrapper->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( noteWrapper );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWHandleDialogPageEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWHandleDialogPageEventL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteWrapper* noteWrapper = new (ELeave) CAknNoteWrapper;
    CleanupStack::PushL( noteWrapper );
    STIF_ASSERT_NOT_NULL( noteWrapper );
    
    CleanupStack::Pop( noteWrapper );
    CTestNotesControl* control = CTestNotesControl::NewL();
    CleanupStack::PushL( control );
    
    noteWrapper->SetContainerWindowL( *control );
    noteWrapper->HandleDialogPageEventL( MEikDialogPageObserver::EDialogPageTapped );
    
    CleanupStack::PopAndDestroy( control );
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNRNDExecuteLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNRNDExecuteLD( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesResourceNoteDialog* noteDialog = new (ELeave) CTestSDKNotesResourceNoteDialog( R_TESTSDK_NOTEWRAPPER );
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNRNDExecutePromptLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNRNDExecutePromptLD( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesResourceNoteDialog* noteDialog = new (ELeave) CTestSDKNotesResourceNoteDialog( R_TESTSDK_NOTEWRAPPERNOTEXT );
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    _LIT( KPrompt, "Wrapper" );
    TBuf<KLength> prompt( KPrompt );
    noteDialog->ExecuteLD( prompt );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNRNDHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNRNDHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesResourceNoteDialog* noteDialog = new (ELeave) CTestSDKNotesResourceNoteDialog( R_TESTSDK_NOTEWRAPPERNOTEXT );
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPoint1, KPoint2 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    noteDialog->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNRNDCAknResourceNoteDialogL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNRNDCAknResourceNoteDialogL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesResourceNoteDialog* noteDialog = new (ELeave) CTestSDKNotesResourceNoteDialog( R_TESTSDK_NOTEWRAPPER );
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNRNDCAknResourceNoteDialogPointerL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNRNDCAknResourceNoteDialogPointerL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteWrapper* dialog = new (ELeave) CAknNoteWrapper;
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    CTestSDKNotesResourceNoteDialog* noteDialog = new (ELeave) CTestSDKNotesResourceNoteDialog( R_TESTSDK_NOTEWRAPPER, &dialog );
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    CleanupStack::Pop( noteDialog );
    CleanupStack::PopAndDestroy( dialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNCNCAknConfirmationNoteL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNCNCAknConfirmationNoteL( CStifItemParser& /*aItem*/ )
    {
    CAknConfirmationNote* confirmationNote = new (ELeave) CAknConfirmationNote;
    CleanupStack::PushL( confirmationNote );
    STIF_ASSERT_NOT_NULL( confirmationNote );
    CleanupStack::Pop( confirmationNote );
    
    confirmationNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNCNCAknConfirmationNoteParameterL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNCNCAknConfirmationNoteParameterL( CStifItemParser& /*aItem*/ )
    {
    CAknConfirmationNote* confirmationNote = new (ELeave) CAknConfirmationNote( ETrue );
    CleanupStack::PushL( confirmationNote );
    STIF_ASSERT_NOT_NULL( confirmationNote );
    CleanupStack::Pop( confirmationNote );
    
    confirmationNote->ExecuteLD();
    
    confirmationNote = new (ELeave) CAknConfirmationNote( EFalse );
    CleanupStack::PushL( confirmationNote );
    STIF_ASSERT_NOT_NULL( confirmationNote );
    CleanupStack::Pop( confirmationNote );
    
    confirmationNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNCNCAknConfirmationNotePointerL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNCNCAknConfirmationNotePointerL( CStifItemParser& /*aItem*/ )
    {
    CAknConfirmationNote* note = new (ELeave) CAknConfirmationNote;
    CleanupStack::PushL( note );
    STIF_ASSERT_NOT_NULL( note );
    
    CAknConfirmationNote* confirmationNote = new (ELeave) CAknConfirmationNote( &note );
    CleanupStack::Pop( note );
    CleanupStack::PushL( confirmationNote );
    STIF_ASSERT_NOT_NULL( confirmationNote );
    CleanupStack::Pop( confirmationNote );
    
    confirmationNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNCNHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNCNHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknConfirmationNote* note = new (ELeave) CAknConfirmationNote;
    CleanupStack::PushL( note );
    STIF_ASSERT_NOT_NULL( note );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPoint1, KPoint2 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    note->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( note );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNINCAknInformationNoteL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNINCAknInformationNoteL( CStifItemParser& /*aItem*/ )
    {
    CAknInformationNote* informationNote = new (ELeave) CAknInformationNote;
    CleanupStack::PushL( informationNote );
    STIF_ASSERT_NOT_NULL( informationNote );
    CleanupStack::Pop( informationNote );
    
    informationNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNINCAknInformationNoteParameterL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNINCAknInformationNoteParameterL( CStifItemParser& /*aItem*/ )
    {
    CAknInformationNote* informationNote = new (ELeave) CAknInformationNote( ETrue );
    CleanupStack::PushL( informationNote );
    STIF_ASSERT_NOT_NULL( informationNote );
    CleanupStack::Pop( informationNote );
    
    informationNote->ExecuteLD();
    
    informationNote = new (ELeave) CAknInformationNote( EFalse );
    CleanupStack::PushL( informationNote );
    STIF_ASSERT_NOT_NULL( informationNote );
    CleanupStack::Pop( informationNote );
    
    informationNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNINCAknInformationNotePointerL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNINCAknInformationNotePointerL( CStifItemParser& /*aItem*/ )
    {
    CAknInformationNote* note = new (ELeave) CAknInformationNote;
    CleanupStack::PushL( note );
    STIF_ASSERT_NOT_NULL( note );
    
    CAknInformationNote* informationNote = new (ELeave) CAknInformationNote( &note );
    CleanupStack::Pop( note );
    CleanupStack::PushL( informationNote );
    STIF_ASSERT_NOT_NULL( informationNote );
    CleanupStack::Pop( informationNote );
    
    informationNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNINHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNINHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknInformationNote* note = new (ELeave) CAknInformationNote;
    CleanupStack::PushL( note );
    STIF_ASSERT_NOT_NULL( note );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPoint1, KPoint2 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    note->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( note );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNENCAknErrorNoteL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNENCAknErrorNoteL( CStifItemParser& /*aItem*/ )
    {
    CAknErrorNote* errorNote = new (ELeave) CAknErrorNote;
    CleanupStack::PushL( errorNote );
    STIF_ASSERT_NOT_NULL( errorNote );
    CleanupStack::Pop( errorNote );
    
    errorNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNENCAknErrorNoteParameterL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNENCAknErrorNoteParameterL( CStifItemParser& /*aItem*/ )
    {
    CAknErrorNote* errorNote = new (ELeave) CAknErrorNote( ETrue );
    CleanupStack::PushL( errorNote );
    STIF_ASSERT_NOT_NULL( errorNote );
    CleanupStack::Pop( errorNote );
    
    errorNote->ExecuteLD();
    
    errorNote = new (ELeave) CAknErrorNote( EFalse );
    CleanupStack::PushL( errorNote );
    STIF_ASSERT_NOT_NULL( errorNote );
    CleanupStack::Pop( errorNote );
    
    errorNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNENCAknErrorNotePointerL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNENCAknErrorNotePointerL( CStifItemParser& /*aItem*/ )
    {
    CAknErrorNote* note = new (ELeave) CAknErrorNote;
    CleanupStack::PushL( note );
    STIF_ASSERT_NOT_NULL( note );
    
    CAknErrorNote* errorNote = new (ELeave) CAknErrorNote( &note );
    CleanupStack::Pop( note );
    CleanupStack::PushL( errorNote );
    STIF_ASSERT_NOT_NULL( errorNote );
    CleanupStack::Pop( errorNote );
    
    errorNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNENHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNENHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknErrorNote* note = new (ELeave) CAknErrorNote;
    CleanupStack::PushL( note );
    STIF_ASSERT_NOT_NULL( note );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPoint1, KPoint2 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    note->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( note );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWNCAknWarningNoteL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWNCAknWarningNoteL( CStifItemParser& /*aItem*/ )
    {
    CAknWarningNote* warningNote = new (ELeave) CAknWarningNote;
    CleanupStack::PushL( warningNote );
    STIF_ASSERT_NOT_NULL( warningNote );
    CleanupStack::Pop( warningNote );
    
    warningNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWNCAknWarningNoteParameterL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWNCAknWarningNoteParameterL( CStifItemParser& /*aItem*/ )
    {
    CAknWarningNote* warningNote = new (ELeave) CAknWarningNote( ETrue );
    CleanupStack::PushL( warningNote );
    STIF_ASSERT_NOT_NULL( warningNote );
    CleanupStack::Pop( warningNote );
    
    warningNote->ExecuteLD();
    
    warningNote = new (ELeave) CAknWarningNote( EFalse );
    CleanupStack::PushL( warningNote );
    STIF_ASSERT_NOT_NULL( warningNote );
    CleanupStack::Pop( warningNote );
    
    warningNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWNCAknWarningNotePointerL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWNCAknWarningNotePointerL( CStifItemParser& /*aItem*/ )
    {
    CAknWarningNote* note = new (ELeave) CAknWarningNote;
    CleanupStack::PushL( note );
    STIF_ASSERT_NOT_NULL( note );
    
    CAknWarningNote* warningNote = new (ELeave) CAknWarningNote( &note );
    CleanupStack::Pop( note );
    CleanupStack::PushL( warningNote );
    STIF_ASSERT_NOT_NULL( warningNote );
    CleanupStack::Pop( warningNote );
    
    warningNote->ExecuteLD();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNWNHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNWNHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknWarningNote* note = new (ELeave) CAknWarningNote;
    CleanupStack::PushL( note );
    STIF_ASSERT_NOT_NULL( note );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton2Up;
    
    note->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( note );
    
    return KErrNone;
    
    }

