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
* Description:  Test aknipfed.h
*
*/



// [INCLUDE FILES]

#include <aknipfed.h>
#include <in_sock.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <testsdkeditors.rsg>

#include "testsdkeditors.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIPFECAknIpFieldEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIPFECAknIpFieldEditorL( CStifItemParser& /*aItem*/ )
    {
    CAknIpFieldEditor* ipEditor = new (ELeave) CAknIpFieldEditor;
    CleanupStack::PushL( ipEditor );
    STIF_ASSERT_NOT_NULL( ipEditor );
    
    CleanupStack::PopAndDestroy( ipEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIPFEPNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIPFEPNewL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr lowAdr;
    lowAdr.SetAddress( KInetAddrNone );
    TInetAddr highAdr;
    highAdr.SetAddress( KInetAddrAll );
    TInetAddr initialAdr;
    initialAdr.SetAddress( KInetAddrLoop );
    
    CAknIpFieldEditor* ipEditor = CAknIpFieldEditor::NewL( lowAdr, highAdr, initialAdr );
    CleanupStack::PushL( ipEditor );
    STIF_ASSERT_NOT_NULL( ipEditor );
    
    CleanupStack::PopAndDestroy( ipEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIPFENewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIPFENewL( CStifItemParser& /*aItem*/ )
    {
    CAknIpFieldEditor* ipEditor = CAknIpFieldEditor::NewL();
    CleanupStack::PushL( ipEditor );
    STIF_ASSERT_NOT_NULL( ipEditor );
    
    CleanupStack::PopAndDestroy( ipEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIPFESetAddressL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIPFESetAddressL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr lowAdr;
    lowAdr.SetAddress( KInetAddrNone );
    TInetAddr highAdr;
    highAdr.SetAddress( KInetAddrAll );
    TInetAddr initialAdr;
    initialAdr.SetAddress( KInetAddrLoop );
    
    CAknIpFieldEditor* ipEditor = CAknIpFieldEditor::NewL( lowAdr, highAdr, initialAdr );
    CleanupStack::PushL( ipEditor );
    STIF_ASSERT_NOT_NULL( ipEditor );
    
    ipEditor->SetAddress( initialAdr );
    
    CleanupStack::PopAndDestroy( ipEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIPFEAddressL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIPFEAddressL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr lowAdr;
    lowAdr.SetAddress( KInetAddrNone );
    TInetAddr highAdr;
    highAdr.SetAddress( KInetAddrAll );
    TInetAddr initialAdr;
    initialAdr.SetAddress( KInetAddrLoop );
    
    CAknIpFieldEditor* ipEditor = CAknIpFieldEditor::NewL( lowAdr, highAdr, initialAdr );
    CleanupStack::PushL( ipEditor );
    STIF_ASSERT_NOT_NULL( ipEditor );
    
    ipEditor->SetAddress( initialAdr );
    STIF_ASSERT_TRUE( initialAdr == ipEditor->Address() );
    
    CleanupStack::PopAndDestroy( ipEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIPFESetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIPFESetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr lowAdr;
    lowAdr.SetAddress( KInetAddrNone );
    TInetAddr highAdr;
    highAdr.SetAddress( KInetAddrAll );
    TInetAddr initialAdr;
    initialAdr.SetAddress( KInetAddrLoop );
    
    CAknIpFieldEditor* ipEditor = CAknIpFieldEditor::NewL( lowAdr, highAdr, initialAdr );
    CleanupStack::PushL( ipEditor );
    STIF_ASSERT_NOT_NULL( ipEditor );
    
    ipEditor->SetMinimumAndMaximum( lowAdr, highAdr );
    
    TInetAddr lowGet;
    TInetAddr highGet;
    ipEditor->GetMinimumAndMaximum( lowGet, highGet );
    
    STIF_ASSERT_TRUE( lowAdr == lowGet );
    STIF_ASSERT_TRUE( highAdr == highGet );
    
    CleanupStack::PopAndDestroy( ipEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIPFEGetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIPFEGetMinimumAndMaximumL( CStifItemParser& aItem )
    {
    return TestIPFESetMinimumAndMaximumL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIPFEReadIPAddressL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIPFEReadIPAddressL( CStifItemParser& /*aItem*/ )
    {
    CAknIpFieldEditor* ipEditor = CAknIpFieldEditor::NewL();
    CleanupStack::PushL( ipEditor );
    STIF_ASSERT_NOT_NULL( ipEditor );
    
    TInetAddr lowAdr;
    lowAdr.SetAddress( KInetAddrNone );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_IPREADEDITOR );
    TInetAddr ipRead = ipEditor->ReadIPAddress( reader );
    CleanupStack::PopAndDestroy();
    STIF_ASSERT_TRUE( lowAdr == ipRead );
    
    CleanupStack::PopAndDestroy( ipEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIPFEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIPFEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CAknIpFieldEditor* ipEditor = CAknIpFieldEditor::NewL();
    CleanupStack::PushL( ipEditor );
    STIF_ASSERT_NOT_NULL( ipEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_IPEDITOR );
    ipEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( ipEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIPFEOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIPFEOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CAknIpFieldEditor* ipEditor = CAknIpFieldEditor::NewL();
    CleanupStack::PushL( ipEditor );
    STIF_ASSERT_NOT_NULL( ipEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_IPEDITOR );
    ipEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasConsumed == ipEditor->OfferKeyEventL( keyEvent, EEventKey ) );
    
    CleanupStack::PopAndDestroy( ipEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIPFEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIPFEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknIpFieldEditor* ipEditor = CAknIpFieldEditor::NewL();
    CleanupStack::PushL( ipEditor );
    STIF_ASSERT_NOT_NULL( ipEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_IPEDITOR );
    ipEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Up;
    ipEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( ipEditor );
    
    return KErrNone;
    
    }
