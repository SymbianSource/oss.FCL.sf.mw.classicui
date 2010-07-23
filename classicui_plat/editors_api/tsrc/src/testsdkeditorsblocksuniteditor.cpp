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
* Description:  Test aknuniteditor.h
*
*/



// [INCLUDE FILES]

#include <aknuniteditor.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <testsdkeditors.rsg>

#include "testsdkeditors.h"
#include "testsdkeditorscontrol.h"

const TReal KMinValue = 0.0;
const TReal KMaxValue = 100.0;
const TInt KFractionalDigit = 2;
const TInt KLength = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUENewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUENewL( CStifItemParser& /*aItem*/ )
    {
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    CleanupStack::PopAndDestroy( unitEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUENewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUENewLC( CStifItemParser& /*aItem*/ )
    {
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewLC();
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    CleanupStack::PopAndDestroy( unitEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUEConstructL( CStifItemParser& /*aItem*/ )
    {
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    unitEditor->ConstructL( KMinValue, KMaxValue, KMaxValue, KFractionalDigit, EAknUnitEditorCustomUnit );
    
    CleanupStack::PopAndDestroy( unitEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_UEEDITOR );
    unitEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( unitEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUESetValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUESetValueL( CStifItemParser& /*aItem*/ )
    {
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_UEEDITOR );
    unitEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    unitEditor->SetValue( KMaxValue );
    STIF_ASSERT_TRUE( KMaxValue == unitEditor->Value() );
    
    CleanupStack::PopAndDestroy( unitEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUEValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUEValueL( CStifItemParser& aItem )
    {
    return TestUESetValueL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUESupportsUnitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUESupportsUnitL( CStifItemParser& /*aItem*/ )
    {
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_UEEDITOR );
    unitEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    STIF_ASSERT_TRUE( unitEditor->SupportsUnit( EAknUnitEditorMeter ) );
    
    CleanupStack::PopAndDestroy( unitEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUESetUnitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUESetUnitL( CStifItemParser& /*aItem*/ )
    {
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_UEEDITOR );
    unitEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KText, "ue" );
    TBuf<KLength> text( KText );
    unitEditor->SetUnitL( text );
    TBuf<KLength> textGet;
    STIF_ASSERT_TRUE( 0 == unitEditor->GetUnit( textGet ) );
    STIF_ASSERT_TRUE( 0 == text.Compare( textGet ) );
    
    CleanupStack::PopAndDestroy( unitEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUESetUnitUL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUESetUnitUL( CStifItemParser& /*aItem*/ )
    {
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_UEEDITOR );
    unitEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    unitEditor->SetUnitL( EAknUnitEditorMeter );
    STIF_ASSERT_TRUE( EAknUnitEditorMeter == unitEditor->Unit() );
    
    CleanupStack::PopAndDestroy( unitEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUEGetUnitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUEGetUnitL( CStifItemParser& aItem )
    {
    return TestUESetUnitL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUEUnitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUEUnitL( CStifItemParser& aItem )
    {
    return TestUESetUnitUL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUESetMaxFractionalDigitsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUESetMaxFractionalDigitsL( CStifItemParser& /*aItem*/ )
    {
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_UEEDITOR );
    unitEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const TInt KMax = 5;
    unitEditor->SetMaxFractionalDigits( KMax );
    STIF_ASSERT_TRUE( KMax == unitEditor->MaxFractionalDigits() );
    
    CleanupStack::PopAndDestroy( unitEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUEMaxFractionalDigitsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUEMaxFractionalDigitsL( CStifItemParser& aItem )
    {
    return TestUESetMaxFractionalDigitsL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUESetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUESetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_UEEDITOR );
    unitEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    unitEditor->SetMinimumAndMaximum( KMinValue, KMaxValue );
    TReal minValueGet;
    TReal maxValueGet;
    unitEditor->GetMinimumAndMaximum( minValueGet, maxValueGet );
    STIF_ASSERT_TRUE( KMinValue == minValueGet );
    STIF_ASSERT_TRUE( KMaxValue == maxValueGet );
    
    CleanupStack::PopAndDestroy( unitEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUEGetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUEGetMinimumAndMaximumL( CStifItemParser& aItem )
    {
    return TestUESetMinimumAndMaximumL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUESetFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUESetFlagsL( CStifItemParser& /*aItem*/ )
    {
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_UEEDITOR );
    unitEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    unitEditor->SetFlags( EAknUnitEditorAllowUninitialized );
    TUint flag = unitEditor->Flags();
    STIF_ASSERT_TRUE( EAknUnitEditorAllowUninitialized == flag );
    
    CleanupStack::PopAndDestroy( unitEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUEFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUEFlagsL( CStifItemParser& aItem )
    {
    return TestUESetFlagsL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestUEPrepareForFocusLossL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestUEPrepareForFocusLossL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknUnitEditor* unitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( unitEditor );
    STIF_ASSERT_NOT_NULL( unitEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_UEEDITOR );
    unitEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    unitEditor->SetContainerWindowL( *control );
    
    _LIT( KText, "ue" );
    TBuf<KLength> text( KText );
    unitEditor->SetUnitL( text );
    unitEditor->PrepareForFocusLossL();
    
    CleanupStack::PopAndDestroy( unitEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }
