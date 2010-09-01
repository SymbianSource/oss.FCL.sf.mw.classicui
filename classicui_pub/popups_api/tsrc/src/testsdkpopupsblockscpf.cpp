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
* Description:  test AknPopupField.h 
*
*/



// [INCLUDE FILES]

#include <aknpopupfield.h> 
#include <barsread.h>
#include <coemain.h>
#include <aknqueryvaluetext.h> 
#include <eikenv.h>
#include <aknlists.h>
#include <aknform.h>
#include <testsdkpopups.rsg>

#include "testsdkpopups.hrh"
#include "testsdkpopups.h"
#include "testsdkpopupspf.h"
#include "testsdkpopupscpf.h"

const TInt KLength = 20;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFCAknPopupFieldL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFCAknPopupFieldL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    CleanupStack::Pop( field );
    delete field;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFConstructL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    
    _LIT( KEmptyText, "EmptyText" );
    TBuf<KLength> emptyText( KEmptyText );
    field->SetEmptyTextL( emptyText );
    
    _LIT( KInvalidText, "InvalidText" );
    TBuf<KLength> invalidText( KInvalidText );
    field->SetInvalidTextL( invalidText );
    
    field->ConstructL();
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSetAllowsUserDefinedEntryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSetAllowsUserDefinedEntryL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    field->SetAllowsUserDefinedEntry( EFalse );
    field->SetAllowsUserDefinedEntry( ETrue );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFActivateSelectionListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFActivateSelectionListL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    field->SetEmptyListNoteL( R_TESTSDK_LISTNOTE );
    field->ActivateSelectionListL();
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSetQueryValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSetQueryValueL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KArrayContent, "test" );
    CAknQueryValueText* queryValue = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValue );
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( array );
    CDesC16ArrayFlat* temp = new (ELeave) CDesC16ArrayFlat(1);
    CleanupStack::PushL( temp );
    temp->AppendL( KArrayContent );
    array->SetArray( *temp );
    queryValue->SetArrayL( array );
    field->SetQueryValueL( queryValue );
    
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( queryValue );
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSetFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSetFontL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const CFont* font = CEikonEnv::Static()->LegendFont();
    field->SetFont( font );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSetShowIndicatorsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSetShowIndicatorsL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    field->SetShowIndicatorsL( EFalse );
    field->SetShowIndicatorsL( ETrue );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFNumLinesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFNumLinesL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TInt num = field->NumLines();
    STIF_ASSERT_EQUALS( 1, num );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSetPopupFieldObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSetPopupFieldObserverL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKPopupsPF* observer = new (ELeave) CTestSDKPopupsPF;
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    field->SetPopupFieldObserver( observer );
    
    CleanupStack::PopAndDestroy( field );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSetEmptyListNoteL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSetEmptyListNoteL( CStifItemParser& aItem )
    {
    return TestCPFActivateSelectionListL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSetEmptyTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSetEmptyTextL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KEmptyText, "EmptyText" );
    TBuf<KLength> emptyText( KEmptyText );
    field->SetEmptyTextL( emptyText );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSetOtherTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSetOtherTextL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KOtherText, "OtherText" );
    TBuf<KLength> otherText( KOtherText );
    field->SetOtherTextL( otherText );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSetInvalidTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSetInvalidTextL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KInvalidText, "InvalidText" );
    TBuf<KLength> invalidText( KInvalidText );
    field->SetInvalidTextL( invalidText );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyDevice1;
    STIF_ASSERT_TRUE( EKeyWasNotConsumed == field->OfferKeyEventL( keyEvent, EEventKey ) );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TSize size = field->MinimumSize();
    TPoint point = size.AsPoint();
    STIF_ASSERT_EQUALS( 0, point.iX );
    STIF_ASSERT_NOT_EQUALS( 0, point.iY );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    field->HandleResourceChange( KEikMessageCaptionedControlEditableStateChange );
    field->HandleResourceChange( KEikMessageCaptionedControlEditableStateChangeWideWithGraphic );
    field->HandleResourceChange( KEikMessageCaptionedControlEditableStateChangeWideWithoutGraphic );
    field->HandleResourceChange( KEikMessageCaptionedControlNotEditableStateChange );
    field->HandleResourceChange( KEikMessageCaptionedControlNotEditableStateChangeWideWithGraphic );
    field->HandleResourceChange( KEikMessageCaptionedControlNotEditableStateChangeWideWithoutGraphic );
    field->HandleResourceChange( KEikMessageCaptionedControlEditableStateChange );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    field->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSetMaxNumberOfLinesPermittedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSetMaxNumberOfLinesPermittedL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const TInt maxnum = 5;
    field->SetMaxNumberOfLinesPermitted( maxnum );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSetFormFieldRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSetFormFieldRectL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupField* field = new (ELeave) CAknPopupField;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TRect rect( KLength, KLength, KLength, KLength );
    field->SetFormFieldRect( rect );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFHandleControlEventL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* formatListBox = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( formatListBox );
    STIF_ASSERT_NOT_NULL( formatListBox );
    
    CTestSDKPopupsCPF* field = new (ELeave) CTestSDKPopupsCPF;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    field->HandleControlEventL( formatListBox, MCoeControlObserver::EEventRequestExit );
    field->HandleControlEventL( formatListBox, MCoeControlObserver::EEventRequestFocus );
    field->HandleControlEventL( formatListBox, MCoeControlObserver::EEventPrepareFocusTransition );
    
    CleanupStack::PopAndDestroy( field );
    CleanupStack::PopAndDestroy( formatListBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    CAknForm* form = new( ELeave ) CAknForm();
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    CleanupStack::Pop( form );
    form->PrepareLC( R_TESTSDK_POPUPSFIELDFORM );
    
    CTestSDKPopupsCPF* field = static_cast<CTestSDKPopupsCPF*>( form->ControlOrNull( ETestSDKField1 ) );
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    _LIT( KArrayContent, "test" );
    _LIT( KArrayContent1, "test1" );
    CAknQueryValueText* queryValue = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValue );
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( array );
    CDesC16ArrayFlat* temp = new (ELeave) CDesC16ArrayFlat(1);
    CleanupStack::PushL( temp );
    temp->AppendL( KArrayContent );
    temp->AppendL( KArrayContent1 );
    array->SetArray( *temp );
    queryValue->SetArrayL( array );
    field->SetQueryValueL( queryValue );
    
    field->ActivateSelectionListL();
    
    field->ProcessCommandL( EAknSoftkeyOk );
    
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( queryValue );
    CleanupStack::Pop( field );
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFHandleListBoxEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFHandleListBoxEventL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* formatListBox = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( formatListBox );
    STIF_ASSERT_NOT_NULL( formatListBox );
    
    CAknForm* form = new( ELeave ) CAknForm();
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    CleanupStack::Pop( form );
    form->PrepareLC( R_TESTSDK_POPUPSFIELDFORM );
    
    CTestSDKPopupsCPF* field = static_cast<CTestSDKPopupsCPF*>( form->ControlOrNull( ETestSDKField1 ) );
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    _LIT( KArrayContent, "test" );
    _LIT( KArrayContent1, "test1" );
    CAknQueryValueText* queryValue = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValue );
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( array );
    CDesC16ArrayFlat* temp = new (ELeave) CDesC16ArrayFlat(1);
    CleanupStack::PushL( temp );
    temp->AppendL( KArrayContent );
    temp->AppendL( KArrayContent1 );
    array->SetArray( *temp );
    queryValue->SetArrayL( array );
    field->SetQueryValueL( queryValue );
    
    field->ActivateSelectionListL();
    field->HandleListBoxEventL( formatListBox, MEikListBoxObserver::EEventEnterKeyPressed );
    
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( queryValue );
    CleanupStack::Pop( field );
    CleanupStack::PopAndDestroy( form );
    CleanupStack::PopAndDestroy( formatListBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKPopupsCPF* field = new (ELeave) CTestSDKPopupsCPF;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TInt count = field->CountComponentControls();
    STIF_ASSERT_EQUALS( 1, count );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFComponentControlL( CStifItemParser& /*aItem*/ )
    {
    CAknForm* form = new( ELeave ) CAknForm();
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    CleanupStack::Pop( form );
    form->PrepareLC( R_TESTSDK_POPUPSFIELDFORM );
    
    CTestSDKPopupsCPF* field = static_cast<CTestSDKPopupsCPF*>( form->ControlOrNull( ETestSDKField1 ) );
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    _LIT( KArrayContent, "test" );
    _LIT( KArrayContent1, "test1" );
    CAknQueryValueText* queryValue = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValue );
    CAknQueryValueTextArray* array = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( array );
    CDesC16ArrayFlat* temp = new (ELeave) CDesC16ArrayFlat(1);
    CleanupStack::PushL( temp );
    temp->AppendL( KArrayContent );
    temp->AppendL( KArrayContent1 );
    array->SetArray( *temp );
    queryValue->SetArrayL( array );
    field->SetQueryValueL( queryValue );
    
    field->ActivateSelectionListL();
    
    CEikLabel* label = static_cast<CEikLabel*> ( field->ComponentControl( 1 ) );
    STIF_ASSERT_NOT_NULL( label );
    
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( queryValue );
    CleanupStack::Pop( field );
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    
    CTestSDKPopupsCPF* field = new (ELeave) CTestSDKPopupsCPF;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TRect rect( KLength, KLength, KLength, KLength );
    field->SetFormFieldRect( rect );
    field->SizeChanged();
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    
    CTestSDKPopupsCPF* field = new (ELeave) CTestSDKPopupsCPF;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    field->FocusChanged( EDrawNow );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFDrawL( CStifItemParser& /*aItem*/ )
    {
    
    CTestSDKPopupsCPF* field = new (ELeave) CTestSDKPopupsCPF;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_TESTSDK_POPUPSFIELD );
    field->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TRect rect( KLength, KLength, KLength, KLength );
    field->Draw( rect );
    
    CleanupStack::PopAndDestroy( field );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    CAknForm* form = new( ELeave ) CAknForm();
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    CleanupStack::Pop( form );
    form->PrepareLC( R_TESTSDK_POPUPSFIELDFORM );
    
    CTestSDKPopupsCPF* field = static_cast<CTestSDKPopupsCPF*>( form->ControlOrNull( ETestSDKField1 ) );
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    TTypeUid::Ptr ptr = TTypeUid::Null();
    ptr = field->MopSupplyObject( CAknPopupList::ETypeId );
    CTestSDKPopupsCPF* point = static_cast<CTestSDKPopupsCPF*> ( ptr.Pointer() );
    STIF_ASSERT_NULL( point );
    
    CleanupStack::Pop( field );
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }
