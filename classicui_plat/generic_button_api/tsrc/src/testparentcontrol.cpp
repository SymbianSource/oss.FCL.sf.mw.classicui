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
* Description:  Test AknButton.h
 *
*/


/*
 *  [INCLUDE FILES]
 */

#include <eikenv.h>
#include <aknappui.h> 
#include <avkon.mbg>
#include <testsdkgenericbutton.rsg>

#include "testsdkgenericbuttoninclude.h"
#include "testbuttonstate.h"
#include "testparentcontrol.h"
#include "animatorcallback.h"
#include "testbutton.h"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestParentControl::NewL
// -----------------------------------------------------------------------------
//
CTestParentControl* CTestParentControl::NewL()
    {
    CTestParentControl* self = new (ELeave) CTestParentControl;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::~CTestParentControl
// -----------------------------------------------------------------------------
//
CTestParentControl::~CTestParentControl()
    {

    }

// -----------------------------------------------------------------------------
// CTestParentControl::CTestParentControl
// -----------------------------------------------------------------------------
//
CTestParentControl::CTestParentControl(){};

// -----------------------------------------------------------------------------
// CTestParentControl::ConstructL
// -----------------------------------------------------------------------------
//
void CTestParentControl::ConstructL()
    {
    CreateWindowL();
    //add controls
    SetRect(CEikonEnv::Static()->EikAppUi()->ClientRect());
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestParentControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestParentControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/ )
    {
    return EKeyWasConsumed;

    }

// -----------------------------------------------------------------------------
// CTestParentControl::HandlePointerEventL
// -----------------------------------------------------------------------------
//
void CTestParentControl::HandlePointerEventL(const TPointerEvent& /*aPointerEvent*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestParentControl::Draw
// -----------------------------------------------------------------------------
//
void CTestParentControl::Draw(const TRect& /*aRect*/ ) const
    {
    }

// -----------------------------------------------------------------------------
// CTestParentControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestParentControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestParentControl::ComponentControl(TInt aIndex) const
    {
    switch(aIndex)
        {
        default:
            return NULL;
        }
    }

// -----------------------------------------------------------------------------
// CTestParentControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestParentControl::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonActivateL
// -----------------------------------------------------------------------------
//
TInt CTestParentControl::TestAknButtonActivateL()
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    button->ConstructFromResourceL( R_BUTTON );
    button->SetContainerWindowL( *this );
    button->SetRect( Rect() );
    TInt err( KErrNone );
    TRAP( err, button->ActivateL() );
    DrawNow();
    CleanupStack::PopAndDestroy( button );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonSetMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestParentControl::TestAknButtonSetMarginsL()
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    button->ConstructFromResourceL( R_BUTTON );
    TSize size = button->MinimumSize();
    TInt err( KFlagZero );
    if( TSize( KFlagZero, KFlagZero ) == size )
        {
        button->SetContainerWindowL( *this );
        button->SetRect( Rect() );
        const TMargins8 margins( KFlagOne, KFlagOne, KFlagOne, KFlagOne );
        button->SetMargins( margins );
        size = button->MinimumSize();
        if( !( TSize( KFlagTwo, KFlagTwo ) == size ) )
            {
            err = KFlagOne;
            return err;
            }
        }
    else{
        err = KFlagOne;
        return err;
        }
    CleanupStack::PopAndDestroy( button );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestParentControl::TestAknButtonSizeChangedL()
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    button->SetButtonFlags( KAknButtonNoFrame );
    
    const TDesC text( KNullDesC );
    const TDesC helptext( KSimpleText );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    button->DoConstructLMoreComplexL( file, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, text, helptext, KFlagOne );
    button->SetContainerWindowL( *this );
    button->SetRect( Rect() );
    button->DoSizeChanged();
    TSize size = button->MinimumSize();
    TInt err = KFlagZero;
    if( TSize( KFlagZero, KFlagZero ) == size )
        {
        button->SetButtonFlags( KAknButtonTextLeft );
        button->DoSizeChanged();
        size = button->MinimumSize();
        if( TSize( KFlagZero, KFlagZero ) == size )
            {
            err = KFlagOne;
            return err;
            }
        }
    else
        {
        err = KFlagOne;
        return err;
        }
    CleanupStack::PopAndDestroy( button );
    
    CTestButton* buttontwo = CTestButton::NewL();
    CleanupStack::PushL( buttontwo );
    buttontwo->ConstructFromResourceL( R_BUTTON );
    buttontwo->SetContainerWindowL( *this );
    buttontwo->SetRect( Rect() );
    buttontwo->DoSizeChanged();
    size = buttontwo->MinimumSize();
    if( TSize( KFlagZero, KFlagZero ) == size )
        {
        buttontwo->SetButtonFlags( KAknButtonTextLeft );
        buttontwo->DoSizeChanged();
        size = buttontwo->MinimumSize();
        if( TSize( KFlagZero, KFlagZero ) == size )
            {
            err = KFlagOne;
            return err;
            }
        }
    else
        {
        err = KFlagOne;
        return err;
        }
    CleanupStack::PopAndDestroy( buttontwo );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonPrepareForFocusLossLL
// -----------------------------------------------------------------------------
//
TInt CTestParentControl::TestAknButtonPrepareForFocusLossLL()
    {
    CAknButton* button = CAknButton::NewL();
    CleanupStack::PushL( button );
    button->ConstructFromResourceL( R_BUTTON );
    
    button->SetContainerWindowL( *this );
    button->SetRect( Rect() );
    button->PrepareForFocusGainL();
    button->SetFocus( ETrue );
    TInt err;
    TRAP( err, button->PrepareForFocusLossL() );
    CleanupStack::PopAndDestroy( button );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TInt CTestParentControl::TestAknButtonShowHelpLL()
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    button->ConstructFromResourceL( R_BUTTON );
    button->SetContainerWindowL( *this );
    button->SetRect( Rect() );
    
    TInt err( KErrNone );
    TRAP( err, button->DoShowHelpL() );
    if( err != KErrNone )
        {
        err = KFlagOne;
        return err;
        }
    button->DoHideHelp();
    
    button->SetDimmed( ETrue );
    const TDesC dimmedhelptext( KSimpleText );
    button->SetDimmedHelpTextL( dimmedhelptext );
    TRAP( err, button->DoShowHelpL() );
    if( err != KErrNone )
        {
        err = KFlagOne;
        return err;
        }
    button->DoHideHelp();
    CleanupStack::PopAndDestroy( button );
    
    return err;
    }

//End file


