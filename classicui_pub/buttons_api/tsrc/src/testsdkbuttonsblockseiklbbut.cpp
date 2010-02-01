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
* Description:  Test api in eiklbbut.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <testsdkbuttons.rsg>
#include <w32std.h>
#include <coedef.h>
#include <s32file.h>
#include <s32mem.h>
#include <coecobs.h>

#include "testsdkbuttons.h"


// CONSTANTS
const TInt KArraySize = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtConstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    STIF_ASSERT_NOT_NULL( labelbutton );
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtConstructL( CStifItemParser& /*aItem*/ )
    {
    TInt hotKeyCode = 1;
    TInt flags = 1;
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    CEikCommandButton* commandbutton = new( ELeave )CEikCommandButton();
    CleanupStack::PushL( commandbutton );
    labelbutton->ConstructL( commandbutton, hotKeyCode, flags );
    CleanupStack::Pop( commandbutton );
    CleanupStack::PopAndDestroy( labelbutton );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LABELBUTTON );
    labelbutton->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtButtonoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtButtonoL( CStifItemParser& /*aItem*/ )
    {
    TInt hotKeyCode = 1;
    TInt flags = 1;
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    CEikCommandButton* commandbutton = new( ELeave )CEikCommandButton();
    CleanupStack::PushL( commandbutton );
    labelbutton->ConstructL( commandbutton, hotKeyCode, flags );
    CleanupStack::Pop( commandbutton );
    
    CEikCommandButtonBase* temp = NULL;
    temp = labelbutton->Button();
    STIF_ASSERT_NOT_NULL( temp );
    
    CleanupStack::PopAndDestroy( labelbutton );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtLabelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtLabelL( CStifItemParser& /*aItem*/ )
    {
    TInt hotKeyCode = 1;
    TInt flags = 1;
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    CEikCommandButton* commandButton = new( ELeave )CEikCommandButton();
    CleanupStack::PushL( commandButton );
    labelbutton->ConstructL( commandButton, hotKeyCode, flags );
    CleanupStack::Pop( commandButton );
    
    CEikLabel* temp = NULL;
    temp = labelbutton->Label();
    STIF_ASSERT_NOT_NULL( temp );
    
    CleanupStack::PopAndDestroy( labelbutton );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtHotKeyFunctionsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtHotKeyFunctionsL( CStifItemParser& /*aItem*/ )
    {
    TInt hotKeyCode = 97;
    TInt flags = 1;
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    CEikCommandButton* commandButton = new( ELeave )CEikCommandButton();
    CleanupStack::PushL( commandButton );
    labelbutton->ConstructL( commandButton, hotKeyCode, flags );
    CleanupStack::Pop( commandButton );
    labelbutton->HotKeyCode();
    labelbutton->ShowsHotKey();
    labelbutton->PlainHotKey();
    
    hotKeyCode++;
    labelbutton->UpdateHotKey( hotKeyCode, CEikLabeledButton::EPlainHotKey );
    STIF_ASSERT_EQUALS( hotKeyCode, labelbutton->HotKeyCode() );
    STIF_ASSERT_FALSE( labelbutton->ShowsHotKey() );
    STIF_ASSERT_TRUE( labelbutton->PlainHotKey() );
    
    
    CleanupStack::PopAndDestroy( labelbutton );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtAnimateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtAnimateL( CStifItemParser& /*aItem*/ )
    {
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LABELBUTTON );
    labelbutton->ConstructFromResourceL( reader );
    
    labelbutton->Animate();
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtOfferKeyEvnetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtOfferKeyEvnetL( CStifItemParser& /*aItem*/ )
    {
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    labelbutton->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LABELBUTTON );
    labelbutton->ConstructFromResourceL( reader );
    TKeyEvent keyevent = { EKeyEnter, EStdKeyEnter, 0, 0  };
    TEventCode type = EEventKey;
    TKeyResponse result = labelbutton->OfferKeyEventL( keyevent, type );
    STIF_ASSERT_EQUALS( EKeyWasNotConsumed, result );
    
    TPointerEvent event;
    labelbutton->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtSetContainerWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtSetContainerWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    labelbutton->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LABELBUTTON );
    labelbutton->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtMiniSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtMiniSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    labelbutton->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LABELBUTTON );
    labelbutton->ConstructFromResourceL( reader );
    TSize size( 0, 0 );
    size = labelbutton->MinimumSize();
    STIF_ASSERT_NOT_EQUALS( 0, size.iWidth );
    STIF_ASSERT_NOT_EQUALS( 0, size.iHeight );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtSetdimL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtSetdimL( CStifItemParser& /*aItem*/ )
    {
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    labelbutton->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LABELBUTTON );
    labelbutton->ConstructFromResourceL( reader );
    labelbutton->SetDimmed( EFalse );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    labelbutton->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LABELBUTTON );
    labelbutton->ConstructFromResourceL( reader );
    TInt type = 0;
    labelbutton->HandleResourceChange( type );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    labelbutton->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LABELBUTTON );
    labelbutton->ConstructFromResourceL( reader );
    labelbutton->InputCapabilities();
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CEikLabeledButton* labelbutton = new ( ELeave ) CEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    labelbutton->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LABELBUTTON );
    labelbutton->ConstructFromResourceL( reader );
    CArrayFixFlat<TCoeColorUse>* array = new (ELeave) CArrayFixFlat<TCoeColorUse>( KArraySize );
    CleanupStack::PushL( array );
    labelbutton->GetColorUseListL( *array );
    STIF_ASSERT_EQUALS( 0, array->Count() );
    
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKButtons::TestLabelBtWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestLabelBtWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    class CTestEikLabeledButton : public MCoeControlObserver, public CEikLabeledButton
        {
    public:
        /*Constructor*/
        CTestEikLabeledButton(){}
        /*Deconstructor*/
        ~CTestEikLabeledButton(){}
        void DoWriteInternalStateL( RWriteStream aStream )
            {
            WriteInternalStateL( aStream );
            }
    public:
        /**
        * From CCoeControl
        * Returns the number of component controls
        *  @return  Number of component controls
        */
        TInt CountComponentControls() const{ return 0; }
        
        /**
        * From CCoeControl
        * Return a pointer to the component control at the give index.
        *  @return  Pointer to the conponent control.No ownership is transferred
        */
        CCoeControl* ComponentControl(TInt /*aIndex*/) const{ return NULL; }
        /**
        * From CCoeControl
        */
        void SizeChanged(){}
        /**
        * From CCoeControl
        */
        void Reserved_2(){}
        /**
        * from MCoeControlObserver
        */
        void HandleControlEventL(CCoeControl* /*aControl*/,
            TCoeEvent /*aEventType*/){}
        };
    
    CTestEikLabeledButton* labelbutton = new ( ELeave ) CTestEikLabeledButton;
    CleanupStack::PushL( labelbutton );
    labelbutton->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_LABELBUTTON );
    labelbutton->ConstructFromResourceL( reader );
    const TInt KHBufSize = 4096;
    HBufC8* buf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( buf );
    TPtr8 ptr = buf->Des();
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    stream.Open( ptr );
    labelbutton->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( 4 );// labelbutton, reader, buf, stream
    
    return KErrNone;
    
    }

// End of file

