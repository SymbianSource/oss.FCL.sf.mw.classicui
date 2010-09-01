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
* Description:  Test Aknnumseced.h
*
*/



// [INCLUDE FILES]

#include <aknnumseced.h>

#include "testsdkeditors.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestNSECAknNumericSecretEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestNSECAknNumericSecretEditorL( CStifItemParser& /*aItem*/ )
    {
    CAknNumericSecretEditor* secretEditor = new (ELeave) CAknNumericSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestNSEInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestNSEInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    CAknNumericSecretEditor* secretEditor = new (ELeave) CAknNumericSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TCoeInputCapabilities capa = secretEditor->InputCapabilities();
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestNSEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestNSEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknNumericSecretEditor* secretEditor = new (ELeave) CAknNumericSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Up;
    secretEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestNSEAppendCharacterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestNSEAppendCharacterL( CStifItemParser& /*aItem*/ )
    {
//Deconstructor is not import or virtual
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestNSECreateFepStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestNSECreateFepStateL( CStifItemParser& /*aItem*/ )
    {
//Deconstructor is not import or virtual
    
    return KErrNone;
    
    }
