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
* Description:  Test AknNoteDialog.h
*
*/


#include <aknnotedialog.h>
#include <eikimage.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <akndef.h>
#include <aknsconstants.h>
#include <testsdknotes.rsg>
#include <aknnotecontrol.h>

#include "testsdknotesnotedialog.h"
#include "testsdknotes.hrh"
#include "testsdknotes.h"

const TInt KLength = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDCAknNoteDialogL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDCAknNoteDialogL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    STIF_ASSERT_TRUE( noteDialog->iTimeoutInMicroseconds == CAknNoteDialog::ENoTimeout );
    STIF_ASSERT_TRUE( noteDialog->iTone == CAknNoteDialog::ENoTone );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDCAknNoteDialogToneL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDCAknNoteDialogToneL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog( CAknNoteDialog::EConfirmationTone, CAknNoteDialog::EShortTimeout );
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDCAknNoteDialogPointerL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDCAknNoteDialogPointerL( CStifItemParser& /*aItem*/ )
    {
    CEikDialog** dialog = new (ELeave) CEikDialog*;
    CleanupStack::PushL( dialog );
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog( dialog );
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    CleanupStack::Pop( noteDialog );
    CleanupStack::PopAndDestroy( dialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDDeconstructorL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog( CAknNoteDialog::EConfirmationTone, CAknNoteDialog::EShortTimeout );
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    CleanupStack::Pop( noteDialog );
    delete noteDialog;
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetTimeoutL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetTimeoutL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    noteDialog->SetTimeout( CAknNoteDialog::EShortTimeout );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetToneL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetToneL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    noteDialog->SetTone( CAknNoteDialog::EConfirmationTone );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetTextWrappingL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetTextWrappingL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    noteDialog->SetTextWrapping( EFalse );
    noteDialog->SetTextWrapping( ETrue );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetTextProcessingL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetTextProcessingL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    noteDialog->SetTextProcessing( EFalse );
    noteDialog->SetTextProcessing( ETrue );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetImageL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetImageL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    CEikImage* image = new (ELeave) CEikImage;
    CleanupStack::PushL( image );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_ANDIMAGE );
    image->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    noteDialog->SetImageL( image );
    
    CleanupStack::Pop( image );
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetIconL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetIconL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    CEikImage* image = new (ELeave) CEikImage;
    CleanupStack::PushL( image );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_ANDIMAGE );
    image->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    noteDialog->SetIconL( image );
    
    CleanupStack::Pop( image );
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetTextNumberL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetTextNumberL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    const TInt number = 100;
    noteDialog->SetTextNumberL( number );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetTextPluralityL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetTextPluralityL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    noteDialog->SetTextPluralityL( EFalse );
    noteDialog->SetTextPluralityL( ETrue );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetTextL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetTextL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    _LIT( KLabel, "label" );
    TBuf<KLength> label( KLabel );
    noteDialog->SetTextL( label );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDOfferKeyEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasConsumed == noteDialog->OfferKeyEventL( keyEvent, EEventKey ) );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDHandleResourceChangeL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    noteDialog->HandleResourceChange( KAknsMessageSkinChange );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDLayoutAndDrawL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDLayoutAndDrawL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    noteDialog->LayoutAndDraw();
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDRunLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDRunLD( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog( CAknNoteDialog::EConfirmationTone, CAknNoteDialog::EShortTimeout );
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    TInt flag = noteDialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDExitSleepingDialogL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDExitSleepingDialogL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog( CAknNoteDialog::EConfirmationTone, CAknNoteDialog::EShortTimeout );
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    CleanupStack::Pop( noteDialog );
    noteDialog->ExitSleepingDialog();
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetSizeAndPositionL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetSizeAndPositionL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    TSize size( KLength, KLength );
    noteDialog->SetSizeAndPosition( size );
    
    TInt flag = noteDialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDPreLayoutDynInitL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    noteDialog->PreLayoutDynInitL();
    noteDialog->Layout();
    
    TInt flag = noteDialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDPostLayoutDynInitL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    noteDialog->PostLayoutDynInitL();
    noteDialog->Layout();
    
    TInt flag = noteDialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDPlayToneL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDPlayToneL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->SetTone( CAknNoteDialog::EConfirmationTone );
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    noteDialog->PlayTone();
    noteDialog->Layout();
    
    TInt flag = noteDialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDReportUserActivityL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDReportUserActivityL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    noteDialog->ReportUserActivity();
    
    TInt flag = noteDialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDStaticDeleteL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDStaticDeleteL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    CleanupStack::Pop( noteDialog );
    TInt flag = noteDialog->StaticDeleteL( noteDialog );
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDControlAttributesL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDControlAttributesL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    CAknNoteAttributes* attributes = noteDialog->ControlAttributes();
    STIF_ASSERT_NOT_NULL( attributes );
    
    TInt flag = noteDialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDTransferControlAttributesL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDTransferControlAttributesL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    noteDialog->TransferControlAttributes();
    
    TInt flag = noteDialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSoundSystemL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSoundSystemL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    CAknKeySoundSystem* soundSystem = noteDialog->SoundSystem();
    STIF_ASSERT_NOT_NULL( soundSystem );
    
    TInt flag = noteDialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDNoteControlL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDNoteControlL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog;
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    CAknNoteControl* noteControl = noteDialog->NoteControl();
    STIF_ASSERT_NOT_NULL( noteControl );
    
    TInt flag = noteDialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDExecuteDlgTimeOutLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDExecuteDlgTimeOutLD( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    TInt flag = noteDialog->ExecuteDlgLD( CAknNoteDialog::EShortTimeout, CAknNoteDialog::EConfirmationTone, R_TESTSDK_IMAGENOTE );
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDExecuteDlgToneLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDExecuteDlgToneLD( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    TInt flag = noteDialog->ExecuteDlgLD( CAknNoteDialog::EConfirmationTone, R_TESTSDK_IMAGENOTE );
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDExecuteDlgLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDExecuteDlgLD( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    TInt flag = noteDialog->ExecuteDlgLD( R_TESTSDK_IMAGENOTE );
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDRunDlgTimeOuntLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDRunDlgTimeOuntLD( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    TInt flag = noteDialog->RunDlgLD( CAknNoteDialog::EShortTimeout, CAknNoteDialog::EConfirmationTone );
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDRunDlgToneLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDRunDlgToneLD( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    TInt flag = noteDialog->RunDlgLD( CAknNoteDialog::EConfirmationTone );
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDRunDlgLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDRunDlgLD( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    TInt flag = noteDialog->RunDlgLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDRunDlgIdLD
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDRunDlgIdLD( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    TInt flag = noteDialog->RunDlgLD( ETESTSDKNOTESIMAGE );
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetCurrentLabelL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetCurrentLabelL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    _LIT( KTitle, "Title" );
    TBuf<KLength> title( KTitle );
    noteDialog->SetCurrentLabelL( ETESTSDKNOTESIMAGE, title );
    TInt flag = noteDialog->RunLD();
    STIF_ASSERT_EQUALS( 0, flag );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDSetNoMemoryAllocationL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDSetNoMemoryAllocationL( CStifItemParser& /*aItem*/ )
    {
    
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_IMAGENOTE );
    noteDialog->SetNoMemoryAllocation();
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNDHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNDHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    
    CTestSDKNotesNoteDialog* noteDialog = new (ELeave) CTestSDKNotesNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton2Up;
    
    noteDialog->HandlePointerEventL( event );
    
    CleanupStack::Pop( noteDialog );
    
    noteDialog->ExecuteDlgLD( R_TESTSDK_IMAGENOTE );
    
    return KErrNone;
    
    }

//The End
