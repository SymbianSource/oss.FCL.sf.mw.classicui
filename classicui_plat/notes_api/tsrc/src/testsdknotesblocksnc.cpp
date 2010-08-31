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
* Description:  Test AknNoteControl.h
*
*/


#include <aknnotecontrol.h>
#include <aknnotedialog.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <testsdknotes.rsg>

#include "testsdknotesnotecontrol.h"
#include "testsdknotes.h"
#include "testsdknotes.hrh"

const TInt KLength = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCCAknNoteControlL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCCAknNoteControlL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteControl* noteControl = new (ELeave) CAknNoteControl;
    CleanupStack::PushL( noteControl );
    STIF_ASSERT_NOT_NULL( noteControl );
    
    CleanupStack::PopAndDestroy( noteControl );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCDeconstructorL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteControl* noteControl = new (ELeave) CAknNoteControl;
    CleanupStack::PushL( noteControl );
    STIF_ASSERT_NOT_NULL( noteControl );
    
    CleanupStack::Pop( noteControl );
    delete noteControl;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCSetImageL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCSetImageL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    CEikImage* image = new (ELeave) CEikImage;
    CleanupStack::PushL( image );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_ANDIMAGE );
    image->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    noteControl->SetImageL( image );
    
    CleanupStack::Pop( image );
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCSetAnimationL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCSetAnimationL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    noteControl->SetAnimationL( R_TESTSDK_ANIMATIONDATA );
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCSetIconL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCSetIconL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    CEikImage* image = new (ELeave) CEikImage;
    CleanupStack::PushL( image );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_ANDIMAGE );
    image->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    noteControl->SetIconL( image );
    
    CleanupStack::Pop( image );
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCSetFinalProgressValueL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCSetFinalProgressValueL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLPROGRESS );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    noteControl->CreateProgressBarL();
    CEikProgressInfo* progressInfo = noteControl->GetProgressInfo();
    STIF_ASSERT_NOT_NULL( progressInfo );
    
    const TInt progressValue = 10;
    noteControl->SetFinalProgressValue( progressValue );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCIncrementBarsAndDrawL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCIncrementBarsAndDrawL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLPROGRESS );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    noteControl->CreateProgressBarL();
    CEikProgressInfo* progressInfo = noteControl->GetProgressInfo();
    STIF_ASSERT_NOT_NULL( progressInfo );
    
    const TInt progressValue = 10;
    noteControl->SetFinalProgressValue( progressValue );
    const TInt increment = 2;
    noteControl->IncrementBarsAndDraw( increment );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCCreateProgressBarL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCCreateProgressBarL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLPROGRESS );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    noteControl->CreateProgressBarL();
    CEikProgressInfo* progressInfo = noteControl->GetProgressInfo();
    STIF_ASSERT_NOT_NULL( progressInfo );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCGetProgressInfoL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCGetProgressInfoL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLPROGRESS );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    noteControl->CreateProgressBarL();
    CEikProgressInfo* progressInfo = noteControl->GetProgressInfo();
    STIF_ASSERT_NOT_NULL( progressInfo );
    
    const TInt progressValue = 10;
    noteControl->SetFinalProgressValue( progressValue );
    const TInt increment = 2;
    noteControl->IncrementBarsAndDraw( increment );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCStartAnimationL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCStartAnimationL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    noteControl->SetAnimationL( R_TESTSDK_ANIMATIONDATA );
    noteControl->StartAnimationL();
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCCancelAnimationL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCCancelAnimationL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    noteControl->SetAnimationL( R_TESTSDK_ANIMATIONDATA );
    noteControl->StartAnimationL();
    noteControl->CancelAnimation();
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCResetTextL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCResetTextL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    _LIT( KText, "resettext" );
    TBuf<KLength> text( KText );
    noteControl->SetTextPluralityL( EFalse );
    noteControl->SetTextL( text );
    noteControl->ResetText();
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCSetTextL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCSetTextL( CStifItemParser& aItem )
    {
    return TestNNCResetTextL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCSetTextLineNumL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCSetTextLineNumL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    _LIT( KText, "resettext" );
    TBuf<KLength> text( KText );
    noteControl->SetTextPluralityL( EFalse );
    noteControl->SetTextL( text, 1 );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCSetTextNumberL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCSetTextNumberL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    _LIT( KText, "resettext" );
    TBuf<KLength> text( KText );
    noteControl->SetTextPluralityL( EFalse );
    noteControl->SetTextL( text );
    noteControl->SetTextNumberL( 1 );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCSetTextPluralityL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCSetTextPluralityL( CStifItemParser& aItem )
    {
    return TestNNCResetTextL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCNumberOfLinesL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCNumberOfLinesL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    TInt num = noteControl->NumberOfLines();
    STIF_ASSERT_EQUALS( 0, num );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCLayoutL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCLayoutL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    noteControl->Layout();
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCNoteHeightL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCNoteHeightL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    TInt height = noteControl->NoteHeight();
    STIF_ASSERT_NOT_EQUALS( 0, height );
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCNoteWidthL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCNoteWidthL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    TInt height = noteControl->NoteWidth();
    STIF_ASSERT_NOT_EQUALS( 0, height );
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    noteControl->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCSetDynamicTextL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCSetDynamicTextL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    _LIT( KText, "dynamic" );
    TBuf<KLength> text( KText );
    noteControl->SetDynamicTextL( text );
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCUpdateAndFormatLabelsL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCUpdateAndFormatLabelsL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    _LIT( KLabel, "dynamic" );
    TBuf<KLength> label( KLabel );
    noteControl->UpdateAndFormatLabelsL( label );
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCUpdateLabelsLeaveL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCUpdateLabelsLeaveL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    _LIT( KLabel, "dynamic" );
    TBuf<KLength> label( KLabel );
    noteControl->UpdateLabelsL( label );
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCUpdateLabelsL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCUpdateLabelsL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    _LIT( KLabel, "dynamic" );
    TBuf<KLength> label( KLabel );
    noteControl->UpdateLabels( label );
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCSetLabelReserveLengthL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCSetLabelReserveLengthL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    noteControl->SetLabelReserveLengthL();
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCMopSupplyObjectL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CTestSDKNotesNoteControl* noteControl = static_cast<CTestSDKNotesNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    TTypeUid::Ptr ptr = TTypeUid::Null();
    ptr = noteControl->MopSupplyObject( CEikDialog::ETypeId );
    CTestSDKNotesNoteControl* point = static_cast<CTestSDKNotesNoteControl*> ( ptr.Pointer() );
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNNCSetBgRectL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNNCSetBgRectL( CStifItemParser& /*aItem*/ )
    {
    CAknNoteDialog* noteDialog = new (ELeave) CAknNoteDialog();
    CleanupStack::PushL( noteDialog );
    STIF_ASSERT_NOT_NULL( noteDialog );
    CleanupStack::Pop( noteDialog );
    
    noteDialog->PrepareLC( R_TESTSDK_NOTECONTROLIMAGE );
    CAknNoteControl* noteControl = static_cast<CAknNoteControl*> ( noteDialog->Control( ETestSDKNoteControl ) ); 
    STIF_ASSERT_NOT_NULL( noteControl );
    
    TPoint apoint( KLength, KLength );
    const TInt KCorner = 100;
    TPoint bpoint( KCorner, KCorner );
    TRect rect( apoint, bpoint );
    noteControl->SetBgRect( rect, apoint );
    noteControl->Layout();
    
    CleanupStack::PopAndDestroy( noteDialog );
    
    return KErrNone;
    
    }
