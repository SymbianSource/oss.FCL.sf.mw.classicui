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
* Description:  Test aknmultilinequerycontrol.h
*
*/

//INCLUDE
#include <aknmultilinequerycontrol.h>
#include <aknquerydialog.h>
#include <testsdkqueries.rsg>
#include <barsread.h>

#include "testsdkqueries.h"
#include "testsdkaknquerydialogprotected.h"

const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMlqcConstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknMultilineQueryControl* mQC = new( ELeave ) CAknMultilineQueryControl;
    CleanupStack::PushL( mQC );
    STIF_ASSERT_NOT_NULL( mQC );
    CleanupStack::PopAndDestroy( mQC );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMlqcDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknMultilineQueryControl* mQC = new( ELeave ) CAknMultilineQueryControl;
    CleanupStack::PushL( mQC );
    CleanupStack::PopAndDestroy( mQC );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMlqcSetNbrOfPromptLinesL( CStifItemParser& /*aItem*/ )
    {
    CAknMultilineQueryControl* mQC = new( ELeave ) CAknMultilineQueryControl;
    CleanupStack::PushL( mQC );
    mQC->SetNbrOfPromptLines( KOne, KTwo );
    CleanupStack::PopAndDestroy( mQC );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMlqcIsFirstL( CStifItemParser& /*aItem*/ )
    {
    CAknMultilineQueryControl* mQC = new( ELeave ) CAknMultilineQueryControl;
    CleanupStack::PushL( mQC );
    TBool firstLine = mQC->IsFirst();
    STIF_ASSERT_TRUE( firstLine );
    CleanupStack::PopAndDestroy( mQC );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMlqcIsSecondL( CStifItemParser& /*aItem*/ )
    {
    CAknMultilineQueryControl* mQC = new( ELeave ) CAknMultilineQueryControl;
    CleanupStack::PushL( mQC );
    TBool second = mQC->IsSecond();
    STIF_ASSERT_FALSE( second );
    CleanupStack::PopAndDestroy( mQC );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMlqcControlByLayoutOrNullL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( CAknQueryDialog::ENoTone );
    dlg->PrepareLC( R_QUERY_DIALOG );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    
    CAknMultilineQueryControl* mQC = static_cast<CAknMultilineQueryControl*>( testDlg->QueryControl() );

    CCoeControl* control = mQC->ControlByLayoutOrNull( EMultiDataSecondPhoneEd );
    STIF_ASSERT_NULL( control );

    control = mQC->ControlByLayoutOrNull( EMultiDataSecondSecEd );
    STIF_ASSERT_NULL( control );
    
    control = mQC->ControlByLayoutOrNull( EMultiDataSecondDateEd );
    STIF_ASSERT_NULL( control );
    
    control = mQC->ControlByLayoutOrNull( EMultiDataSecondTimeEd );
    STIF_ASSERT_NULL( control );
    
    control = mQC->ControlByLayoutOrNull( EMultiDataSecondDurEd );
    STIF_ASSERT_NULL( control );
    
    control = mQC->ControlByLayoutOrNull( EMultiDataSecondNumEd );
    STIF_ASSERT_NULL( control );
    
    control = mQC->ControlByLayoutOrNull( EMultiDataSecondPinEd );
    STIF_ASSERT_NULL( control );
    
    control = mQC->ControlByLayoutOrNull( EMultiDataSecondLocationEd );
    STIF_ASSERT_NULL( control );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMlqcMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknMultilineQueryControl* mQC = new( ELeave ) CAknMultilineQueryControl;
    CleanupStack::PushL( mQC );
    
    TSize returnSize = mQC->MinimumSize();
    TSize compareSize( KZero, KZero );
    STIF_ASSERT_NOT_EQUALS( compareSize, returnSize );
    
    CleanupStack::PopAndDestroy( mQC );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMlqcHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    
    CAknMultilineQueryControl* mQc = new(ELeave) CAknMultilineQueryControl();
    CleanupStack::PushL( mQc );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_QUERY_DIALOG );
    mQc->ConstructFromResourceL( reader );
   
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    mQc->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( mQc );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMlqcHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( CAknQueryDialog::ENoTone );
    dlg->PrepareLC( R_QUERY_DIALOG );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    
    CAknMultilineQueryControl* mQC = static_cast<CAknMultilineQueryControl*>( testDlg->QueryControl() );
    
    mQC->HandleResourceChange( KAknsMessageSkinChange );
    mQC->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtMlqcConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtMlqcConstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknExtMultilineQueryControl* extMqc = new( ELeave ) CAknExtMultilineQueryControl;
    CleanupStack::PushL( extMqc );
    STIF_ASSERT_NOT_NULL( extMqc );
    CleanupStack::PopAndDestroy( extMqc );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtMlqcDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtMlqcDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknExtMultilineQueryControl* extMqc = new( ELeave ) CAknExtMultilineQueryControl;
    CleanupStack::PushL( extMqc );
    CleanupStack::PopAndDestroy( extMqc );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtMlqcSetNbrOfPromptLinesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtMlqcSetNbrOfPromptLinesL( CStifItemParser& /*aItem*/ )
    {
    CAknExtMultilineQueryControl* extMqc = new( ELeave ) CAknExtMultilineQueryControl;
    CleanupStack::PushL( extMqc );
    extMqc->SetNbrOfPromptLines( KOne, KTwo );
    CleanupStack::PopAndDestroy( extMqc );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtMlqcIsFirstL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtMlqcIsFirstL( CStifItemParser& /*aItem*/ )
    {
    CAknExtMultilineQueryControl* extMqc = new( ELeave ) CAknExtMultilineQueryControl;
    CleanupStack::PushL( extMqc );
    TBool firstLine = extMqc->IsFirst();
    STIF_ASSERT_TRUE( firstLine );
    CleanupStack::PopAndDestroy( extMqc );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtMlqcIsSecondL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtMlqcIsSecondL( CStifItemParser& /*aItem*/ )
    {
    CAknExtMultilineQueryControl* extMqc = new( ELeave ) CAknExtMultilineQueryControl;
    CleanupStack::PushL( extMqc );
    TBool second = extMqc->IsSecond();
    STIF_ASSERT_FALSE( second );
    CleanupStack::PopAndDestroy( extMqc );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtMlqcControlByLayoutOrNullL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtMlqcControlByLayoutOrNullL( CStifItemParser& /*aItem*/ )
    {
    CAknExtMultilineQueryControl* extMqc = new( ELeave ) CAknExtMultilineQueryControl;
    CleanupStack::PushL( extMqc );
    
    CCoeControl* control = extMqc->ControlByLayoutOrNull( EMultiDataFirstIpEd );
    STIF_ASSERT_NULL( control );
    
    control = extMqc->ControlByLayoutOrNull( EMultiDataSecondIpEd );
    STIF_ASSERT_NULL( control );
    
    CleanupStack::PopAndDestroy( extMqc );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtMlqcMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtMlqcMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknExtMultilineQueryControl* extMqc = new( ELeave ) CAknExtMultilineQueryControl;
    CleanupStack::PushL( extMqc );
    
    TSize returnSize = extMqc->MinimumSize();
    TSize compareSize( KZero, KZero );
    STIF_ASSERT_NOT_EQUALS( compareSize, returnSize );
    
    CleanupStack::PopAndDestroy( extMqc );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtMlqcHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtMlqcHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    
    CAknExtMultilineQueryControl* extMqc = new(ELeave) CAknExtMultilineQueryControl();
    CleanupStack::PushL( extMqc );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_QUERY_DIALOG );
    extMqc->ConstructFromResourceL( reader );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    extMqc->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( extMqc );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestExtMlqcHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestExtMlqcHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( CAknQueryDialog::ENoTone );
    dlg->PrepareLC( R_QUERY_DIALOG );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    
    CAknExtMultilineQueryControl* extMqc = static_cast<CAknExtMultilineQueryControl*>( testDlg->QueryControl() );
    
    extMqc->HandleResourceChange( KAknsMessageSkinChange );
    extMqc->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

//End file



