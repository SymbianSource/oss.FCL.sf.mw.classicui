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
* Description:  test functions for testing eiksoftkeypostingtransparency.h
*
*/



// [INCLUDE FILES]
#include <eikbtgpc.h>
#include <eikbtgpc.h>
#include <avkon.rsg>

#include "testdomextbuttons.h"
#include "testaknview.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtButtons::TestEikSoftkeyPostTransMakeTransparentL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtButtons::TestEikSoftkeyPostTransMakeTransparentL( CStifItemParser& /*aItem*/ ) 
    {
    // Print to UI
    _LIT( KTestDomExtButtons, "TestDomExtButtons" );
    _LIT( KTestEikSoftkeyPostTransMakeTransparentL, "TestEikSoftkeyPostTransMakeTransparentL" );
    TestModuleIf().Printf( 0, KTestDomExtButtons, KTestEikSoftkeyPostTransMakeTransparentL );
    // Print to log file
    iLog->Log( KTestEikSoftkeyPostTransMakeTransparentL );
    
    CTestAknView* observer = new ( ELeave ) CTestAknView();
    CleanupStack::PushL( observer );
    observer->BaseConstructL();
    
    CEikButtonGroupContainer* container =
            CEikButtonGroupContainer::NewL( CEikButtonGroupContainer::ECba,
                    CEikButtonGroupContainer::EHorizontal, observer,
                    R_AVKON_SOFTKEYS_SELECT_CANCEL__SELECT );
    
    EikSoftkeyPostingTransparency::MakeTransparent( *container, ETrue );
    
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    }


//  [End of File]
