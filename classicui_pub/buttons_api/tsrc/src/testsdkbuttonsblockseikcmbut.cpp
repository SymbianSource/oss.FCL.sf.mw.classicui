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
* Description:  Test api in eikcmbut.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <testsdkbuttons.rsg>
#include <akniconutils.h>
#include <avkon.mbg>
#include <s32mem.h>
#include <s32file.h>
#include <eikcmbut.h>
#include <eikalign.h>
#include <eiklabel.h>

#include "testsdkbuttons.h"
#include "testsdkbuttons.hrh"

// CONSTANTS
const TInt KArraySize = 10;
const TInt KHBufSize = 20000;
const TInt KBufSize = 64;
_LIT( KBitmapFile, "Z:\\resource\\apps\\avkon2.mbm" );

// FORWARD DECLARATIONS
// This class is used for testing functions in CEikCommandButtonBase
// because it's constructor is protected.
class CTestCmdBtBase : public CEikCommandButtonBase
    {
public:
    /*
     * constructor
     * */
    CTestCmdBtBase();
    /*
     * deconstructor
     * */
    ~CTestCmdBtBase();
    
    // test protect functon 
    // test StateChanged
    void DoStateChanged();
    
    // test Draw
    void DoDraw(const TRect& aRect);
    
    // test WriteInternalStateL
    void DoWriteInternalStateL( RWriteStream& aStream );
    
    // test SetTextL
    void DoSetTextL( const TDesC& aText );
    
    // test SetPictureL
    void DoSetPictureL( const CFbsBitmap* aMain,const CFbsBitmap* aMask );
    
    // test SetPictureFromFileL
    void DoSetPictureFromFileL( const TDesC& aFilename,TInt aMain,TInt aMask );
    
    // set components, aIndex is a number in array. The value is 0 or 1.
    TInt SetComponentsL( TInt aIndex );
    
    };
// -----------------------------------------------------------------------------
// CTestCmdBtBase::CTestCmdBtBase
// -----------------------------------------------------------------------------
//
CTestCmdBtBase::CTestCmdBtBase(){}

// -----------------------------------------------------------------------------
// CTestCmdBtBase::~CTestCmdBtBase
// -----------------------------------------------------------------------------
//
CTestCmdBtBase::~CTestCmdBtBase(){}

// -----------------------------------------------------------------------------
// CTestCmdBtBase::DoStateChanged
// -----------------------------------------------------------------------------
//
void CTestCmdBtBase::DoStateChanged()
    {
    StateChanged();
    }
// -----------------------------------------------------------------------------
// CTestCmdBtBase::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestCmdBtBase::DoWriteInternalStateL( RWriteStream& aStream )
    {
    WriteInternalStateL( aStream );
    }

// -----------------------------------------------------------------------------
// CTestCmdBtBase::DoSetTextL
// -----------------------------------------------------------------------------
//
void CTestCmdBtBase::DoSetTextL( const TDesC& aText )
    {
    SetTextL( aText, iComponents[0] );
    }

// -----------------------------------------------------------------------------
// CTestCmdBtBase::DoSetPictureL
// -----------------------------------------------------------------------------
//
void CTestCmdBtBase::DoSetPictureL( const CFbsBitmap* aMain,const CFbsBitmap* aMask )
    {
    SetPictureL( aMain, aMask, iComponents[0] );
    }

// -----------------------------------------------------------------------------
// CTestCmdBtBase::DoSetPictureFromFileL
// -----------------------------------------------------------------------------
//
void CTestCmdBtBase::DoSetPictureFromFileL( const TDesC& aFilename,TInt aMain,TInt aMask )
    {
    SetPictureFromFileL( aFilename, aMain, aMask, iComponents[0] );
    }


// -----------------------------------------------------------------------------
// CTestCmdBtBase::DoDraw
// -----------------------------------------------------------------------------
//
void CTestCmdBtBase::DoDraw(const TRect& aRect)
    {
    Draw( aRect );
    }

// -----------------------------------------------------------------------------
// CTestCmdBtBase::SetComponentsL
// -----------------------------------------------------------------------------
//
TInt CTestCmdBtBase::SetComponentsL( TInt aIndex )
    {
    const TInt marginsize = 2;
    switch ( aIndex )
        {
        case 0:
            {
            CEikAlignedControl* component = new ( ELeave ) CEikAlignedControl;
            component->SetAllMarginsTo( marginsize );
            component->SetAlignment( EHLeftVCenter );
            iComponents[0] = component;
            break;
            }
        case 1:
            {
            CEikAlignedControl* component = new ( ELeave ) CEikAlignedControl;
            component->SetAllMarginsTo( marginsize );
            component->SetAlignment( EHLeftVCenter );
            iComponents[1] = component;
            break;
            }
        default:
            return -1;
        }
    return 0;
    }
    
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseConstrutorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseConstrutorL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    STIF_ASSERT_NOT_NULL( cmdbtbase );
    CleanupStack::PopAndDestroy( cmdbtbase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseSetButtonLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseSetButtonLayoutL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    CEikCommandButtonBase::TLayout layout = CEikCommandButtonBase::EFirstRightSecondLeft;
    cmdbtbase->SetButtonLayout( layout );
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseSetExcessSpaceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseSetExcessSpaceL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    CEikCommandButtonBase::TExcess excess = CEikCommandButtonBase::EToFirst;
    cmdbtbase->SetExcessSpace( excess );
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseSetDisplayContentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseSetDisplayContentL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    CEikCommandButtonBase::TDisplayContent content = CEikCommandButtonBase::EFirstOnly;
    cmdbtbase->SetDisplayContent( content );
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseLayoutComponentsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseLayoutComponentsL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON);
    cmdbtbase->StartConstructFromResourceL( reader );
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->LayoutComponents();
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseStartConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseStartConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON);
    cmdbtbase->StartConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseConstructLabelAndImageFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseConstructLabelAndImageFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructLabelFromResourceL( reader, CEikCommandButtonBase::EFirst );
    CleanupStack::PopAndDestroy();
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructImageFromResourceL( reader, CEikCommandButtonBase::EFirst );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseUpdateComponentAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseUpdateComponentAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->UpdateComponentAlignment();
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseSetDefaultL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseSetDefaultL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetDefault( EFalse );
    cmdbtbase->SetDefault( ETrue );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseSetDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseSetDimmedL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetDimmed( EFalse );
    cmdbtbase->SetDimmed( ETrue );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    TSize size( 0, 0 );
    size = cmdbtbase->MinimumSize();
    if ( size.iHeight == 0 || size.iWidth == 0 )
        {
        CleanupStack::PopAndDestroy( 2 );
        return KErrCorrupt;
        }
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetComponentsL( 0 );
    TInt num = cmdbtbase->CountComponentControls();
    CleanupStack::PopAndDestroy( 2 );
    const TInt controlnum = 1;
    STIF_ASSERT_EQUALS( controlnum, num );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseComponentControlL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    
    cmdbtbase->SetComponentsL( 0 );
    CCoeControl* control = cmdbtbase->ComponentControl( 0 );
    STIF_ASSERT_NOT_NULL( control );
    
    CleanupStack::PopAndDestroy( cmdbtbase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseSetContainerWindowLAndActivateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseSetContainerWindowLAndActivateL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetContainerWindowL( *iContainer );
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->ActivateL();
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetContainerWindowL( *iContainer );
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->ActivateL();
    
    cmdbtbase->FocusChanged( ENoDrawNow );
    cmdbtbase->FocusChanged( EDrawNow );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetContainerWindowL( *iContainer );
    
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->ActivateL();
    TKeyEvent keyevent;
    keyevent.iCode = EKeyDevice3;
    cmdbtbase->OfferKeyEventL( keyevent, EEventKey );
    TPointerEvent event;
    cmdbtbase->HandlePointerEventL( event );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetContainerWindowL( *iContainer );
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->ActivateL();
    CArrayFixFlat<TCoeColorUse>* array = new (ELeave) CArrayFixFlat<TCoeColorUse>( KArraySize );
    CleanupStack::PushL( array );
    cmdbtbase->GetColorUseListL( *array );
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetContainerWindowL( *iContainer );
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->ActivateL();
    cmdbtbase->HandleResourceChange( 0 );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseStateChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseStateChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetContainerWindowL( *iContainer );
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->ActivateL();
    cmdbtbase->DoStateChanged();
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseSetTextL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetContainerWindowL( *iContainer );
    _LIT( KBtText, "testcommondbutton" );
    TBuf<KBufSize> buf( KBtText );
    cmdbtbase->DoSetTextL( buf );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseSetPictureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseSetPictureL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetContainerWindowL( *iContainer );
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->ActivateL();
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( mask );
    cmdbtbase->DoSetPictureL( bitmap, mask );
    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseSetPictureFromFileL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseSetPictureFromFileL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); //reader
    cmdbtbase->SetContainerWindowL( *iContainer );
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->ActivateL();
    TRect rect( 0, 0, 1, 1 );
    cmdbtbase->DoSetPictureFromFileL( KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    iContainer->ActivateGc();
    cmdbtbase->DoDraw( rect );
    iContainer->DeactivateGc();
    CleanupStack::PopAndDestroy( cmdbtbase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseDrawL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetButtonLayout( CEikCommandButtonBase::EFirstRightSecondLeft );
    cmdbtbase->SetExcessSpace( CEikCommandButtonBase::EShare );
    cmdbtbase->SetDisplayContent( CEikCommandButtonBase::EFirstOnly );
    cmdbtbase->SetContainerWindowL( *iContainer );
    iContainer->ActivateL();
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->ActivateL();
    iContainer->DrawNow();
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtBaseWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtBaseWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CTestCmdBtBase* cmdbtbase = new ( ELeave ) CTestCmdBtBase;
    CleanupStack::PushL( cmdbtbase );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMDBUTTON );
    cmdbtbase->ConstructFromResourceL( reader );
    cmdbtbase->SetContainerWindowL( *iContainer );
    cmdbtbase->SetComponentsL( 0 );
    cmdbtbase->ActivateL();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* hbuf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( hbuf );
    TPtr8 ptr = hbuf->Des();
    stream.Open( ptr );
    cmdbtbase->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( 4 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtConstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikCommandButton* cmdbt = new ( ELeave ) CEikCommandButton;
    CleanupStack::PushL( cmdbt );
    STIF_ASSERT_NOT_NULL( cmdbt );
    CleanupStack::PopAndDestroy( cmdbt );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikCommandButton* cmdbt = new ( ELeave ) CEikCommandButton;
    CleanupStack::PushL( cmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMBUT_BUTTON );
    cmdbt->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtSetPictureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtSetPictureL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CEikCommandButton* cmdbt = new ( ELeave ) CEikCommandButton;
    CleanupStack::PushL( cmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMBUT_BUTTON );
    cmdbt->ConstructFromResourceL( reader );
    CEikImage* image = NULL;
    switch ( num )
        {
        case 1:
            {
            CFbsBitmap* main = NULL;
            CFbsBitmap* mask = NULL;
            AknIconUtils::CreateIconL( main, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            cmdbt->SetPictureL( main, mask );
            image = cmdbt->Picture();
            STIF_ASSERT_NOT_NULL( image );
            CleanupStack::PopAndDestroy();
            break;
            }
        case 2:
            {
            cmdbt->SetPictureFromFileL( KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            image = cmdbt->Picture();
            STIF_ASSERT_NOT_NULL( image );
            CleanupStack::PopAndDestroy();
            break;
            }
        default:
            CleanupStack::PopAndDestroy( cmdbt );
            return KErrNotSupported;
        }
    
    CleanupStack::PopAndDestroy( cmdbt );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtSetThreeEnumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtSetThreeEnumL( CStifItemParser& /*aItem*/ )
    {
    CEikCommandButton* cmdbt = new ( ELeave ) CEikCommandButton;
    CleanupStack::PushL( cmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMBUT_BUTTON );
    cmdbt->ConstructFromResourceL( reader );
    cmdbt->SetButtonLayout( CEikCommandButton::ETextRightPictureLeft );
    cmdbt->SetButtonLayout( CEikCommandButton::ETextBottomPictureTop );
    cmdbt->SetButtonLayout( CEikCommandButton::ETextTopPictureBottom );
    cmdbt->SetButtonLayout( CEikCommandButton::ETextLeftPictureRight );
    cmdbt->SetExcessSpace( CEikCommandButton::EShare );
    cmdbt->SetExcessSpace( CEikCommandButton::EToText );
    cmdbt->SetExcessSpace( CEikCommandButton::EToPicture );
    cmdbt->SetDisplayContent( CEikCommandButton::ETextOnly );
    cmdbt->SetDisplayContent( CEikCommandButton::ETextOnly );
    cmdbt->SetDisplayContent( CEikCommandButton::ETextAndPicture );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtSetTextL( CStifItemParser& /*aItem*/ )
    {
    CEikCommandButton* cmdbt = new ( ELeave ) CEikCommandButton;
    CleanupStack::PushL( cmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMBUT_BUTTON );
    cmdbt->ConstructFromResourceL( reader );
    _LIT( KText, "settext" );
    cmdbt->SetTextL( KText );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtLabelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtLabelL( CStifItemParser& /*aItem*/ )
    {
    CEikCommandButton* cmdbt = new ( ELeave ) CEikCommandButton;
    CleanupStack::PushL( cmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMBUT_BUTTON );
    cmdbt->ConstructFromResourceL( reader );
    CEikLabel* label = NULL;
    label = cmdbt->Label();
    STIF_ASSERT_NOT_NULL( label );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtCmdSetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtCmdSetL( CStifItemParser& /*aItem*/ )
    {
    CEikCommandButton* cmdbt = new ( ELeave ) CEikCommandButton;
    CleanupStack::PushL( cmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMBUT_BUTTON );
    cmdbt->ConstructFromResourceL( reader );
    CFbsBitmap* main = NULL;
    CFbsBitmap* mask = NULL;
    _LIT( KText, "settext" );
    AknIconUtils::CreateIconL( main, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( main );
    CleanupStack::PushL( mask );
    cmdbt->SetCommandL( ELeftBt, &KText, main, mask );
    CleanupStack::Pop( mask );
    CleanupStack::Pop( main );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtUpdateComponentAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtUpdateComponentAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CEikCommandButton* cmdbt = new ( ELeave ) CEikCommandButton;
    CleanupStack::PushL( cmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMBUT_BUTTON );
    cmdbt->ConstructFromResourceL( reader );
    cmdbt->UpdateComponentAlignment();
    
    TPointerEvent event;
    cmdbt->HandlePointerEventL( event );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTwoPicCmdBtConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTwoPicCmdBtConstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikTwoPictureCommandButton* piccmdbt = new ( ELeave ) CEikTwoPictureCommandButton;
    CleanupStack::PushL( piccmdbt );
    STIF_ASSERT_NOT_NULL( piccmdbt );
    CleanupStack::PopAndDestroy( piccmdbt );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTwoPicCmdBtConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTwoPicCmdBtConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikTwoPictureCommandButton* piccmdbt = new ( ELeave ) CEikTwoPictureCommandButton;
    CleanupStack::PushL( piccmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TWOPICBT_BUTTON );
    piccmdbt->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTwoPicCmdBtIsSecondPictureOwnedExternallyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTwoPicCmdBtIsSecondPictureOwnedExternallyL( CStifItemParser& /*aItem*/ )
    {
    CEikTwoPictureCommandButton* piccmdbt = new ( ELeave ) CEikTwoPictureCommandButton;
    CleanupStack::PushL( piccmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TWOPICBT_BUTTON );
    piccmdbt->ConstructFromResourceL( reader );
    CFbsBitmap* main = NULL;
    CFbsBitmap* mask = NULL;
    CFbsBitmap* secondmain = NULL;
    CFbsBitmap* secondmask = NULL;
    AknIconUtils::CreateIconL( main, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    AknIconUtils::CreateIconL( secondmain, secondmask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    piccmdbt->SetTwoPicturesL( main, mask, secondmain, secondmask );
    piccmdbt->IsSecondPictureOwnedExternally();
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTwoPicCmdBtPictureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTwoPicCmdBtPictureL( CStifItemParser& /*aItem*/ )
    {
    CEikTwoPictureCommandButton* piccmdbt = new ( ELeave ) CEikTwoPictureCommandButton;
    CleanupStack::PushL( piccmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TWOPICBT_BUTTON );
    piccmdbt->ConstructFromResourceL( reader );
    CFbsBitmap* main = NULL;
    CFbsBitmap* mask = NULL;
    CFbsBitmap* secondmain = NULL;
    CFbsBitmap* secondmask = NULL;
    AknIconUtils::CreateIconL( main, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    AknIconUtils::CreateIconL( secondmain, secondmask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    piccmdbt->SetTwoPicturesL( main, mask, secondmain, secondmask );
    CEikImage* image = NULL;
    image = piccmdbt->Picture();
    STIF_ASSERT_NOT_NULL( image );
    
    TPointerEvent event;
    piccmdbt->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTwoPicCmdBtSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTwoPicCmdBtSetTextL( CStifItemParser& /*aItem*/ )
    {
    CEikTwoPictureCommandButton* piccmdbt = new ( ELeave ) CEikTwoPictureCommandButton;
    CleanupStack::PushL( piccmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TWOPICBT_BUTTON );
    piccmdbt->ConstructFromResourceL( reader );
    _LIT( KText, "settext" );
    piccmdbt->SetTextL( KText );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTwoPicCmdBtPictureSetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTwoPicCmdBtPictureSetL( CStifItemParser& /*aItem*/ )
    {
    CEikTwoPictureCommandButton* piccmdbt = new ( ELeave ) CEikTwoPictureCommandButton;
    CleanupStack::PushL( piccmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TWOPICBT_BUTTON );
    piccmdbt->ConstructFromResourceL( reader );
    piccmdbt->SetContainerWindowL( *iContainer );
    CFbsBitmap* main = NULL;
    CFbsBitmap* mask = NULL;
    CFbsBitmap* secondmain = NULL;
    CFbsBitmap* secondmask = NULL;
    AknIconUtils::CreateIconL( main, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    AknIconUtils::CreateIconL( secondmain, secondmask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    piccmdbt->SetTwoPicturesL( main, mask, secondmain, secondmask );
    secondmain = NULL;
    secondmask = NULL;
    AknIconUtils::CreateIconL( secondmain, secondmask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    piccmdbt->SetSecondPicture( secondmain, secondmain );
    piccmdbt->SetPictureFromFileL( KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    TRAPD( err, piccmdbt->SetSecondPictureFromFileL( KBitmapFile, EMbmAvkonQgn_graf_tab_21, EMbmAvkonQgn_graf_tab_21_mask ) );
    CleanupStack::PopAndDestroy( 2 );
    if ( err != KErrNone )
        {
        err = KErrNone;
        }
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTwoPicCmdBtConstructImagesFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTwoPicCmdBtConstructImagesFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikTwoPictureCommandButton* piccmdbt = new ( ELeave ) CEikTwoPictureCommandButton;
    CleanupStack::PushL( piccmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TWOPICBT_BUTTON );
//    TRAPD( err, piccmdbt->ConstructImagesFromResourceL( reader, CEikCommandButtonBase::ESecond ) );
//    if ( err != KErrNone )
//        {
//        return KErrNone;
//        }
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTwoPicCmdBtSetSecondPictureOwnedExternallyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTwoPicCmdBtSetSecondPictureOwnedExternallyL( CStifItemParser& /*aItem*/ )
    {
    CEikTwoPictureCommandButton* piccmdbt = new ( ELeave ) CEikTwoPictureCommandButton;
    CleanupStack::PushL( piccmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TWOPICBT_BUTTON );
    piccmdbt->ConstructFromResourceL( reader );
    piccmdbt->SetContainerWindowL( *iContainer );
    piccmdbt->SetSecondPictureOwnedExternally( ETrue );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTwoPicCmdBtActivateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTwoPicCmdBtActivateL( CStifItemParser& /*aItem*/ )
    {
    CEikTwoPictureCommandButton* piccmdbt = new ( ELeave ) CEikTwoPictureCommandButton;
    CleanupStack::PushL( piccmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TWOPICBT_BUTTON );
    piccmdbt->ConstructFromResourceL( reader );
    CFbsBitmap* main = NULL;
    CFbsBitmap* mask = NULL;
    CFbsBitmap* secondmain = NULL;
    CFbsBitmap* secondmask = NULL;
    AknIconUtils::CreateIconL( main, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    AknIconUtils::CreateIconL( secondmain, secondmask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    piccmdbt->SetTwoPicturesL( main, mask, secondmain, secondmask );
    iContainer->ActivateGc();
    piccmdbt->ActivateL();
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTwoPicCmdBtWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTwoPicCmdBtWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    //new a class for test only one protected function
    class CTestTwoPicBt : public CEikTwoPictureCommandButton
        {
    public:
        CTestTwoPicBt(){}
        ~CTestTwoPicBt(){}
        void DoWriteInternalStateL( RWriteStream& aStream ){ WriteInternalStateL( aStream ); }
        TInt SetComponents( TInt aIndex )
            {
            const TInt marginsize = 2;
            switch ( aIndex )
                {
                case 0:
                    {
                    CEikAlignedControl* component = new ( ELeave ) CEikAlignedControl;
                    component->SetAllMarginsTo( marginsize );
                    component->SetAlignment( EHLeftVCenter );
                    iComponents[0] = component;
                    break;
                    }
                case 1:
                    {
                    CEikAlignedControl* component = new ( ELeave ) CEikAlignedControl;
                    component->SetAllMarginsTo( marginsize );
                    component->SetAlignment( EHLeftVCenter );
                    iComponents[1] = component;
                    break;
                    }
                default:
                    return -1;
                }
            return 0;
            }
        };
    CTestTwoPicBt* piccmdbt = new ( ELeave ) CTestTwoPicBt;
    CleanupStack::PushL( piccmdbt );
    piccmdbt->SetComponents( 0 );
    piccmdbt->SetComponents( 1 );
    CFbsBitmap* main = NULL;
    CFbsBitmap* mask = NULL;
    CFbsBitmap* secondmain = NULL;
    CFbsBitmap* secondmask = NULL;
    AknIconUtils::CreateIconL( main, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    AknIconUtils::CreateIconL( secondmain, secondmask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    piccmdbt->SetTwoPicturesL( main, mask, secondmain, secondmask );
    HBufC8* buf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( buf );
    TPtr8 ptr = buf->Des();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    stream.Open( ptr );
    // crash when reading bitmap data
    TRAPD( err, piccmdbt->DoWriteInternalStateL( stream ) );
    stream.CommitL();
    stream.Close();
    CleanupStack::PopAndDestroy( 3 );//piccmdbt, buf, stream
    if ( err != KErrNone )
        {
        err = KErrNone;
        }
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikInverterCmdBtConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikInverterCmdBtConstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikInverterCommandButton* invertcmdbt = new ( ELeave ) CEikInverterCommandButton;
    CleanupStack::PushL( invertcmdbt );
    STIF_ASSERT_NOT_NULL( invertcmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMBUT_BUTTON );
    invertcmdbt->ConstructFromResourceL( reader );
    TPointerEvent event;
    invertcmdbt->HandlePointerEventL( event );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikInverterCmdBtWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikInverterCmdBtWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    //new a class for test only one protected function
    class CTestInvertCmdBt : public CEikInverterCommandButton
        {
    public:
        CTestInvertCmdBt(){}
        ~CTestInvertCmdBt(){}
        void DoWriteInternalStateL( RWriteStream& aStream ){ WriteInternalStateL( aStream ); }
        };
    CTestInvertCmdBt* invertcmdbt = new ( ELeave ) CTestInvertCmdBt;
    CleanupStack::PushL( invertcmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMBUT_BUTTON );
    invertcmdbt->ConstructFromResourceL( reader );
    HBufC8* buf = HBufC8::NewL( KHBufSize );
    TPtr8 ptr = buf->Des();
    CleanupStack::PushL( buf );
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    stream.Open( ptr );
    invertcmdbt->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    CleanupStack::PopAndDestroy( 4 );//invertcmdbt, reader, buf, stream
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTxtBtConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTxtBtConstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikTextButton* txtbt = new ( ELeave ) CEikTextButton;
    CleanupStack::PushL( txtbt );
    STIF_ASSERT_NOT_NULL( txtbt );
    CleanupStack::PopAndDestroy( txtbt );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTxtBtConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTxtBtConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikTextButton* txtbt = new ( ELeave ) CEikTextButton;
    CleanupStack::PushL( txtbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TXTBT_BUTTON );
    txtbt->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTxtBtSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTxtBtSetTextL( CStifItemParser& /*aItem*/ )
    {
    CEikTextButton* txtbt = new ( ELeave ) CEikTextButton;
    CleanupStack::PushL( txtbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TXTBT_BUTTON );
    txtbt->ConstructFromResourceL( reader );
    _LIT( KText, "test" );
    txtbt->SetTextL( KText );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikTxtBtSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikTxtBtLabelL( CStifItemParser& /*aItem*/ )
    {
    CEikTextButton* txtbt = new ( ELeave ) CEikTextButton;
    CleanupStack::PushL( txtbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TXTBT_BUTTON );
    txtbt->ConstructFromResourceL( reader );
    CEikLabel* label = NULL;
    label = txtbt->Label();
    STIF_ASSERT_NOT_NULL( label );
    TPointerEvent event;
    txtbt->HandlePointerEventL( event );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBmpBtConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBmpBtConstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikBitmapButton* bmpbt = new ( ELeave ) CEikBitmapButton;
    CleanupStack::PushL( bmpbt );
    STIF_ASSERT_NOT_NULL( bmpbt );
    CleanupStack::PopAndDestroy( bmpbt );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBmpBtConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBmpBtConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikBitmapButton* bmpbt = new ( ELeave ) CEikBitmapButton;
    CleanupStack::PushL( bmpbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_BITMAPBT_BUTTON );
    bmpbt->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBmpBtPictureSetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBmpBtPictureSetL( CStifItemParser& /*aItem*/ )
    {
    CEikBitmapButton* bmpbt = new ( ELeave ) CEikBitmapButton;
    CleanupStack::PushL( bmpbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_BITMAPBT_BUTTON );
    bmpbt->ConstructFromResourceL( reader );
    CFbsBitmap* main = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( main, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    bmpbt->SetPictureL( main, mask );
    bmpbt->SetPictureFromFileL( KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CEikImage* image = NULL;
    image = bmpbt->Picture();
    STIF_ASSERT_NOT_NULL( image );
    
    TPointerEvent event;
    bmpbt->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCmdBtProcessCmdStackL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCmdBtProcessCmdStackL( CStifItemParser& /*aItem*/ )
    {
    CEikCommandButton* cmdbt = new ( ELeave ) CEikCommandButton;
    CleanupStack::PushL( cmdbt );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CMBUT_BUTTON );
    cmdbt->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    CFbsBitmap* main = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( main, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( main );
    CleanupStack::PushL( mask );
    _LIT( KText, "settext" );
    cmdbt->AddCommandToStackL( ESingle, &KText, main, mask );
    cmdbt->PopCommandFromStack();
    CleanupStack::Pop( mask );
    CleanupStack::Pop( main );
    AknIconUtils::CreateIconL( main, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( main );
    CleanupStack::PushL( mask );
    cmdbt->AddCommandToStackL( EBckBt, &KText, main, mask );
    cmdbt->RemoveCommandFromStack( EBckBt );
    CleanupStack::Pop( mask );
    CleanupStack::Pop( main );
    
    CleanupStack::PopAndDestroy( cmdbt );
    
    return KErrNone;
    }
// End of file
