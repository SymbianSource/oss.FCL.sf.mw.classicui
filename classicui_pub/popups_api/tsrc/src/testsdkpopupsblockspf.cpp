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
* Description:  test AknPopupFader.h 
*
*/



// [INCLUDE FILES]

#include <aknform.h> 
#include <testsdkpopups.rsg>

#include "testsdkpopups.h"
#include "testsdkpopupspf.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestMFCCountFadedComponentsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestMFCCountFadedComponentsL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKPopupsPF* fadedComponent = new (ELeave) CTestSDKPopupsPF;
    CleanupStack::PushL( fadedComponent );
    STIF_ASSERT_NOT_NULL( fadedComponent );
    
    TInt count = fadedComponent->CountFadedComponents();
    STIF_ASSERT_EQUALS( 0, count );
    
    CleanupStack::PopAndDestroy( fadedComponent );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestMFCFadedComponentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestMFCFadedComponentL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKPopupsPF* fadedComponent = new (ELeave) CTestSDKPopupsPF;
    CleanupStack::PushL( fadedComponent );
    STIF_ASSERT_NOT_NULL( fadedComponent );
    
    CCoeControl* control = fadedComponent->FadedComponent( 0 );
    STIF_ASSERT_NULL( control );
    
    CleanupStack::PopAndDestroy( fadedComponent );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestTPFFadeBehindPopupL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestTPFFadeBehindPopupL( CStifItemParser& /*aItem*/ )
    {
    CAknForm* form = new( ELeave ) CAknForm();
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    CleanupStack::Pop( form );
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    
    TAknPopupFader fader;
    fader.FadeBehindPopup( form, NULL, ETrue );
    
    CleanupStack::PopAndDestroy( form );
    return KErrNone;
    
    }
