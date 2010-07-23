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
* Description:  Test AknLocationEd.h
*
*/



// [INCLUDE FILES]

#include <aknlocationed.h>
#include <lbsposition.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <aknquerycontrol.h>
#include <testsdkeditors.rsg>

#include "testsdkeditorslocationed.h"
#include "testsdkeditors.h"
#include "testsdkeditorscontrol.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestLECAknLocationEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestLECAknLocationEditorL( CStifItemParser& /*aItem*/ )
    {
    CAknLocationEditor* locationEditor = new (ELeave) CAknLocationEditor;
    CleanupStack::PushL( locationEditor );
    STIF_ASSERT_NOT_NULL( locationEditor );
    
    CleanupStack::PopAndDestroy( locationEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestLEDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestLEDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknLocationEditor* locationEditor = new (ELeave) CAknLocationEditor;
    CleanupStack::PushL( locationEditor );
    STIF_ASSERT_NOT_NULL( locationEditor );
    
    CleanupStack::Pop( locationEditor );
    delete locationEditor;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestLENewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestLENewL( CStifItemParser& /*aItem*/ )
    {
    TCoordinate coord( 0.0, 0.0 );
    TLocality loc( coord, 0.1 );
    TPosition position( loc, TTime(0) );
    
    CAknLocationEditor* locationEditor = CAknLocationEditor::NewL( position, CAknLocationEditor::ELongitudeOnly );
    CleanupStack::PushL( locationEditor );
    STIF_ASSERT_NOT_NULL( locationEditor );
    
    CleanupStack::PopAndDestroy( locationEditor );

    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestLEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestLEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknLocationEditor* locationEditor = new (ELeave) CAknLocationEditor;
    CleanupStack::PushL( locationEditor );
    STIF_ASSERT_NOT_NULL( locationEditor );
    locationEditor->SetContainerWindowL( *control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDITORSLE );
    locationEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( locationEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestLEDisplayableLocationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestLEDisplayableLocationL( CStifItemParser& /*aItem*/ )
    {
    CAknLocationEditor* locationEditor = new (ELeave) CAknLocationEditor;
    CleanupStack::PushL( locationEditor );
    STIF_ASSERT_NOT_NULL( locationEditor );
    
    TCoordinate coord( 0.0, 0.0 );
    TLocality loc( coord, 0.1 );
    TPosition position( loc, TTime(0) );
    
    HBufC* buf = CAknLocationEditor::DisplayableLocationL( position, CAknLocationEditor::ELatitudeOnly );
    CleanupStack::PushL( buf );
    STIF_ASSERT_NOT_NULL( buf );
    CleanupStack::PopAndDestroy( buf );
    
    CleanupStack::PopAndDestroy( locationEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestLEPrepareForFocusLossL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestLEPrepareForFocusLossL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknLocationEditor* locationEditor = new (ELeave) CAknLocationEditor;
    CleanupStack::PushL( locationEditor );
    STIF_ASSERT_NOT_NULL( locationEditor );
    locationEditor->SetContainerWindowL( *control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDITORSLE );
    locationEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    locationEditor->PrepareForFocusLossL();
    
    CleanupStack::PopAndDestroy( locationEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestLESetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestLESetL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknLocationEditor* locationEditor = new (ELeave) CAknLocationEditor;
    CleanupStack::PushL( locationEditor );
    STIF_ASSERT_NOT_NULL( locationEditor );
    
    TCoordinate coord( 0.0, 0.0 );
    TLocality loc( coord, 0.1 );
    TPosition position( loc, TTime(0) );
    
    locationEditor->SetContainerWindowL( *control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDITORSLE );
    locationEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    locationEditor->Set( position );
    TPosition positionGet;
    locationEditor->Get( positionGet );
    STIF_ASSERT_TRUE( position.Time() == positionGet.Time() )
    
    CleanupStack::PopAndDestroy( locationEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestLEGetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestLEGetL( CStifItemParser& aItem )
    {
    return TestLESetL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestLEOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestLEOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CAknLocationEditor* locationEditor = new (ELeave) CAknLocationEditor;
    CleanupStack::PushL( locationEditor );
    STIF_ASSERT_NOT_NULL( locationEditor );
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasConsumed == locationEditor->OfferKeyEventL( keyEvent, EEventKey ) );
    
    CleanupStack::PopAndDestroy( locationEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestLECAknLocationEditor_ExtensionInterfaceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestLECAknLocationEditor_ExtensionInterfaceL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsLocationEd* locationEditor = new (ELeave) CTestSDKEditorsLocationEd;
    CleanupStack::PushL( locationEditor );
    STIF_ASSERT_NOT_NULL( locationEditor );
    
    STIF_ASSERT_TRUE( NULL == locationEditor->CAknLocationEditor_ExtensionInterface( TUid::Null() ) );
    
    CleanupStack::PopAndDestroy( locationEditor );
    
    return KErrNone;
    
    }
