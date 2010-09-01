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
* Description:  test AknPopupFieldText.h 
*
*/



// [INCLUDE FILES]

#include <aknpopupfieldtext.h>
#include <barsread.h>
#include <coeaui.h>
#include <testsdkpopups.rsg>

#include "testsdkpopups.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFTCAknPopupFieldTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFTCAknPopupFieldTextL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupFieldText* fieldText = new (ELeave) CAknPopupFieldText;
    CleanupStack::PushL( fieldText );
    STIF_ASSERT_NOT_NULL( fieldText );
    
    CleanupStack::PopAndDestroy( fieldText );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFTDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFTDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupFieldText* fieldText = new (ELeave) CAknPopupFieldText;
    CleanupStack::PushL( fieldText );
    STIF_ASSERT_NOT_NULL( fieldText );
    
    CleanupStack::Pop( fieldText );
    delete fieldText;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFTCurrentValueTextLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFTCurrentValueTextLC( CStifItemParser& /*aItem*/ )
    {
    CAknPopupFieldText* fieldText = new (ELeave) CAknPopupFieldText;
    CleanupStack::PushL( fieldText );
    STIF_ASSERT_NOT_NULL( fieldText );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_POPUP_FIELD_TEXT );
    fieldText->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    HBufC* text = fieldText->CurrentValueTextLC();
    STIF_ASSERT_NOT_NULL( text );
    
    CleanupStack::PopAndDestroy( text );
    CleanupStack::PopAndDestroy( fieldText );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFTCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFTCurrentValueIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupFieldText* fieldText = new (ELeave) CAknPopupFieldText;
    CleanupStack::PushL( fieldText );
    STIF_ASSERT_NOT_NULL( fieldText );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_POPUP_FIELD_TEXT );
    fieldText->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const TInt index = 1;
    fieldText->SetCurrentValueIndex( index );
    TInt indexGet = fieldText->CurrentValueIndex();
    STIF_ASSERT_EQUALS( indexGet, index );
    
    CleanupStack::PopAndDestroy( fieldText );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFTSetCurrentValueIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFTSetCurrentValueIndexL( CStifItemParser& aItem )
    {
    return TestCPFTCurrentValueIndexL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFTMdcArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFTMdcArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupFieldText* fieldText = new (ELeave) CAknPopupFieldText;
    CleanupStack::PushL( fieldText );
    STIF_ASSERT_NOT_NULL( fieldText );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_POPUP_FIELD_TEXT );
    fieldText->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const TInt count = 2;
    const MDesCArray* array = fieldText->MdcArray();
    STIF_ASSERT_NOT_NULL( array );
    TInt countGet = array->MdcaCount();
    STIF_ASSERT_EQUALS( count, countGet );
    
    CleanupStack::PopAndDestroy( fieldText );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFTSetAutoAppendL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFTSetAutoAppendL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupFieldText* fieldText = new (ELeave) CAknPopupFieldText;
    CleanupStack::PushL( fieldText );
    STIF_ASSERT_NOT_NULL( fieldText );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_POPUP_FIELD_TEXT );
    fieldText->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    fieldText->SetAutoAppend( EFalse );
    fieldText->SetAutoAppend( ETrue );
    
    CleanupStack::PopAndDestroy( fieldText );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFTConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFTConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupFieldText* fieldText = new (ELeave) CAknPopupFieldText;
    CleanupStack::PushL( fieldText );
    STIF_ASSERT_NOT_NULL( fieldText );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_POPUP_FIELD_TEXT );
    fieldText->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( fieldText );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPFTHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPFTHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupFieldText* fieldText = new (ELeave) CAknPopupFieldText;
    CleanupStack::PushL( fieldText );
    STIF_ASSERT_NOT_NULL( fieldText );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_POPUP_FIELD_TEXT );
    fieldText->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    fieldText->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( fieldText );
    
    return KErrNone;
    
    }
