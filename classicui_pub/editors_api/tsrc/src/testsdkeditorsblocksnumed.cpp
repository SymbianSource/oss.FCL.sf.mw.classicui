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
* Description:  Test AknNumed.h
*
*/



// [INCLUDE FILES]

#include <aknnumed.h>
#include <e32const.h>

#include "testsdkeditors.h"
#include "testsdkeditorsnumed.h"
#include "testsdkeditorscontrol.h"

const TInt KLength = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestNEDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestNEDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknNumericEdwin* numEdwin = new (ELeave) CAknNumericEdwin;
    CleanupStack::PushL( numEdwin );
    STIF_ASSERT_NOT_NULL( numEdwin );
    
    CleanupStack::Pop( numEdwin );
    delete numEdwin;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestNEMapKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestNEMapKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsNumed* numEdwin = new (ELeave) CTestSDKEditorsNumed;
    CleanupStack::PushL( numEdwin );
    STIF_ASSERT_NOT_NULL( numEdwin );
    
    TKeyEvent keyEvent;
    TEventCode eventCode = EEventKey;
    numEdwin->MapKeyEvent( keyEvent, eventCode, EDigitTypeAllTypes );
    
    CleanupStack::PopAndDestroy( numEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestNEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestNEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsNumed* numEdwin = new (ELeave) CTestSDKEditorsNumed;
    CleanupStack::PushL( numEdwin );
    STIF_ASSERT_NOT_NULL( numEdwin );
    
    numEdwin->ConstructL( EEikEdwinAutoSelection, KLength, KLength, KLength );
    numEdwin->SetContainerWindowL( *control );
    numEdwin->CreateTextViewL();

    TKeyEvent keyEvent;
    TEventCode eventCode = EEventKey;
    numEdwin->MapKeyEvent( keyEvent, eventCode, EDigitTypeAllTypes );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    numEdwin->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( numEdwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }
