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
* Description:  Test api in eikmnbut.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <testsdkbuttons.rsg>
#include <s32mem.h>

#include "testsdkbuttons.h"

// FORWARD DECLARATIONS
// Observer class for test function
class CTestMenuObserver : public CBase, public MEikMenuObserver
    {
    // from MEikMenuObserver, no need
    void SetEmphasis(CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/){}
    // from MEikMenuObserver, no need
    void ProcessCommandL(TInt /*aCommandId*/){}
    };
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestMenuBtConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestMenuBtConstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikMenuButton* menubutton = new ( ELeave ) CEikMenuButton;
    CleanupStack::PushL( menubutton );
    STIF_ASSERT_NOT_NULL( menubutton );
    CleanupStack::PopAndDestroy( menubutton );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestMenuBtConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestMenuBtConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikMenuButton* menubutton = new ( ELeave ) CEikMenuButton;
    CleanupStack::PushL( menubutton );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_MENU_BUTTON );
    menubutton->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestMenuBtLaunchPopupMenuL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestMenuBtLaunchPopupMenuL( CStifItemParser& /*aItem*/ )
    {
    CTestMenuObserver* ob = new ( ELeave ) CTestMenuObserver;
    CleanupStack::PushL( ob );
    CEikMenuButton* menubutton = new ( ELeave ) CEikMenuButton;
    CleanupStack::PushL( menubutton );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_MENU_BUTTON );
    menubutton->ConstructFromResourceL( reader );
    menubutton->SetContainerWindowL( *iContainer );
    iContainer->SetComponentControlL( menubutton );
    TPointerEvent event;
    menubutton->HandlePointerEventL( event );
//    menubutton->LaunchPopupMenuL( ob );
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestMenuBtSetMenuPaneIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestMenuBtSetMenuPaneIdL( CStifItemParser& /*aItem*/ )
    {
    TInt menupaneid = 0;
    CEikMenuButton* menubutton = new ( ELeave ) CEikMenuButton;
    CleanupStack::PushL( menubutton );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_MENU_BUTTON );
    menubutton->ConstructFromResourceL( reader );
    
    menubutton->SetMenuPaneId( menupaneid );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestMenuBtAnimateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestMenuBtAnimateL( CStifItemParser& /*aItem*/ )
    {
    CEikMenuButton* menubutton = new ( ELeave ) CEikMenuButton;
    CleanupStack::PushL( menubutton );
    menubutton->Animate();
    CleanupStack::PopAndDestroy( menubutton );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestMenuBtWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestMenuBtWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    class CTestEikMenuButton : public CEikMenuButton
        {
    public:
        /*Constructor*/
        CTestEikMenuButton(){}
        /*Deconstructor*/
        ~CTestEikMenuButton(){}
        void DoWriteInternalStateL( RWriteStream aStream )
            {
            WriteInternalStateL( aStream );
            }
        };
    CTestEikMenuButton* menubutton = new ( ELeave ) CTestEikMenuButton;
    CleanupStack::PushL( menubutton );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_MENU_BUTTON );
    menubutton->ConstructFromResourceL( reader );
    const TInt KHBufSize = 4096;
    HBufC8* buf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( buf );
    TPtr8 ptr = buf->Des();
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    stream.Open( ptr );
    menubutton->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    CleanupStack::PopAndDestroy( 4 );// menubutton, reader, buf, stream
    
    return KErrNone;
    }

// End of file
