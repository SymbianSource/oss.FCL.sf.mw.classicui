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
* Description:  test api in eikbcctrl.h
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <s32mem.h>

#include "testsdkbasecontrols.h"

// CONSTANTS
const TInt KAdjacentNum = 10;
const TInt KHbufSize = 10000;
const TInt KPointerCoordinate = 40;

// Class for testing protected function of CEikBorderedControl
class CTestEikBorderedControl : public CEikBorderedControl
    {
public:
    // Test protected function Draw of CEikBorderedControl
    void DoDraw(const TRect& aRect){ Draw( aRect ); }
    
    // Test protected function WriteInternalStateL of CEikBorderedControl
    void DoWriteInternalStateL(RWriteStream& aWriteStream){ WriteInternalStateL( aWriteStream ); }
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikBorderedControlContructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikBorderedControlContructorL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    switch ( num )
        {
        case ECaseOne:
            {
            CEikBorderedControl* control = new ( ELeave ) CEikBorderedControl;
            CleanupStack::PushL( control );
            STIF_ASSERT_NOT_NULL( control );
            CleanupStack::PopAndDestroy( control );
            break;
            }
        case ECaseTwo:
            {
            TGulBorder border( TGulBorder::ESingleBlack );
            CEikBorderedControl* controlwithpara = new ( ELeave ) CEikBorderedControl( border );
            CleanupStack::PushL( controlwithpara );
            STIF_ASSERT_NOT_NULL( controlwithpara );
            CleanupStack::PopAndDestroy( controlwithpara );
            break;
            }
        default:
            return KErrNotSupported;
        }
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikBorderedControlHasBorderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikBorderedControlHasBorderL( CStifItemParser& /*aItem*/ )
    {
    
    CEikBorderedControl* control = new ( ELeave ) CEikBorderedControl;
    CleanupStack::PushL( control );
    TBool result = control->HasBorder();
    STIF_ASSERT_FALSE( result );
    CleanupStack::PopAndDestroy( control );
    
    TGulBorder border( TGulBorder::ESingleBlack );
    control = new ( ELeave ) CEikBorderedControl( border );
    CleanupStack::PushL( control );
    result = control->HasBorder();
    STIF_ASSERT_TRUE( result );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikBorderedControlSetAdjacentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikBorderedControlSetAdjacentL( CStifItemParser& /*aItem*/ )
    {
    CEikBorderedControl* control = new ( ELeave ) CEikBorderedControl;
    CleanupStack::PushL( control );
    control->SetAdjacent( KAdjacentNum );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikBorderedControlGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikBorderedControlGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CEikBorderedControl* control = new ( ELeave ) CEikBorderedControl;
    CleanupStack::PushL( control );
    CArrayFix<TCoeColorUse>* array = NULL;
    control->GetColorUseListL( *array );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikBorderedControlHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikBorderedControlHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikBorderedControl* control = new ( ELeave ) CEikBorderedControl;
    CleanupStack::PushL( control );
    TInt type = 0;
    control->HandleResourceChange( type );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikBorderedControlHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikBorderedControlHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikBorderedControl* control = new ( ELeave ) CEikBorderedControl;
    CleanupStack::PushL( control );
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPointerCoordinate, KPointerCoordinate );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    control->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikBorderedControlSetBorderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikBorderedControlSetBorderL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        return err;
    TGulBorder border( TGulBorder::ESingleBlack );
    CEikBorderedControl* control = new ( ELeave ) CEikBorderedControl( border );
    CleanupStack::PushL( control );
    switch ( num )
        {
        case ECaseOne:
            {
            control->SetBorder( TGulBorder::ESingleGray );
            break;
            }
        case ECaseTwo:
            {
            TInt bordertype = 1;
            control->SetBorder( bordertype );
            break;
            }
        default:
            CleanupStack::PopAndDestroy( control );
            return KErrNotSupported;
        }
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikBorderedControlBorderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikBorderedControlBorderL( CStifItemParser& /*aItem*/ )
    {
    TGulBorder border( TGulBorder::ESingleBlack );
    CEikBorderedControl* control = new ( ELeave ) CEikBorderedControl( border );
    CleanupStack::PushL( control );
    TGulBorder result = control->Border();
    STIF_ASSERT_EQUALS( border.Type() , result.Type() );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikBorderedControlBorderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikBorderedControlDrawL( CStifItemParser& /*aItem*/ )
    {
    CTestEikBorderedControl* control = new ( ELeave ) CTestEikBorderedControl;
    CleanupStack::PushL( control );
    TRect rect( 0, 0, 0, 0 );
    control->DoDraw( rect );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKBaseControls::TestCEikBorderedControlBorderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKBaseControls::TestCEikBorderedControlWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CTestEikBorderedControl* control = new ( ELeave ) CTestEikBorderedControl;
    CleanupStack::PushL( control );
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* buf = HBufC8::NewL( KHbufSize );
    CleanupStack::PushL( buf );
    TPtr8 ptr = buf->Des();
    stream.Open( ptr );
    control->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

//End of file

