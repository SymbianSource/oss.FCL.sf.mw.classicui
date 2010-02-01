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
* Description:  Test api in eikbutb.h
*
*/



// [INCLUDE FILES]
#include <stifparser.h>
#include <s32mem.h>

#include "testsdkbuttons.h"

// CONSTANTS
const TInt KArraySize = 10;
const TInt KHbufSize = 2000;
// FORWARD DECLARATIONS
/*
 * ==============================================================================
 * Test protect functions of CTestButtonBase
 * ==============================================================================
 * */
class CTestButtonBase : public CEikButtonBase
    {
public:
    // NewL function
    static CTestButtonBase* NewL();
    
    // Deconstructor
    ~CTestButtonBase();
public:

    /**
     * Test protected function DrawState of CEikButtonBase
     */
    TInt DoDrawState();

    /**
     * Test protected function SetAllowTristate of CEikButtonBase
     */
    TInt DoSetAllowTristate();

    /**
     * Test protected function CopyDrawStateTo of CEikButtonBase
     */
    TInt DoCopyDrawStateTo(CEikButtonBase* aTargetButton);
    
private:
    /**
     * 2nd constuctor
     */
    void ConstructL();
    /**
     * Constructor
     */
    CTestButtonBase();
    
private:
    // Data
    
    };
// -----------------------------------------------------------------------------
// CTestButtonBase::CTestButtonBase
// -----------------------------------------------------------------------------
//
CTestButtonBase::CTestButtonBase(){}

// -----------------------------------------------------------------------------
// CTestButtonBase::~CTestButtonBase
// -----------------------------------------------------------------------------
//
CTestButtonBase::~CTestButtonBase(){}

// -----------------------------------------------------------------------------
// CTestButtonBase::CTestButtonBase
// -----------------------------------------------------------------------------
//
CTestButtonBase* CTestButtonBase::NewL()
    {
    CTestButtonBase* self = new ( ELeave ) CTestButtonBase;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestButtonBase::ConstructL
// -----------------------------------------------------------------------------
//
void CTestButtonBase::ConstructL()
    {
    // Nothing to do
    }

// -----------------------------------------------------------------------------
// CTestButtonBase::DoDrawState
// -----------------------------------------------------------------------------
//
TInt CTestButtonBase::DoDrawState()
    {
    CEikButtonBase::SetReportOnPointerDown();
    CEikButtonBase::SetIgnoreNextPointerUp();
    SetReportOnPointerDown();
    IsPressed();
    DrawState();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestButtonBase::DoSetAllowTristate
// -----------------------------------------------------------------------------
//
TInt CTestButtonBase::DoSetAllowTristate()
    {
    SetAllowTristate();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestButtonBase::DoCopyDrawStateTo
// -----------------------------------------------------------------------------
//
TInt CTestButtonBase::DoCopyDrawStateTo( CEikButtonBase* aTargetButton )
    {
    CopyDrawStateTo( aTargetButton );
    if ( this->State() != aTargetButton->State() )
        return KErrGeneral;
    return KErrNone;
    }

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseConstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonBase* btbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( btbase );
    STIF_ASSERT_NOT_NULL( btbase );
    CleanupStack::PopAndDestroy( btbase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseSetAndGetStateL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonBase* btbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( btbase );
    btbase->SetState( CEikButtonBase::ESet );
    CEikButtonBase::TState state = CEikButtonBase::EClear;
    state = btbase->State();
    if ( state != CEikButtonBase::ESet )
        {
        return KErrGeneral;
        }
        
    CleanupStack::PopAndDestroy( btbase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseAnimateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseAnimateL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonBase* btbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( btbase );
    btbase->Animate();
    
    CleanupStack::PopAndDestroy( btbase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseSetCoordinatorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseSetCoordinatorL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonBase* btbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( btbase );
    CEikButtonBase* cobtbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( cobtbase );
    TEikButtonCoordinator coordinator;
    coordinator.SetChosenButton( cobtbase );
    btbase->SetCoordinator( &coordinator );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseSetBehaviorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseSetBehaviorL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonBase* btbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( btbase );
    btbase->SetBehavior( EEikButtonStaysSet );
    
    CleanupStack::PopAndDestroy( btbase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonBase* btbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( btbase );
    
    CArrayFixFlat<TCoeColorUse>* array = new ( ELeave ) CArrayFixFlat<TCoeColorUse>( KArraySize );
    CleanupStack::PushL( array );
    btbase->GetColorUseListL( *array );
    STIF_ASSERT_EQUALS( 0, array->Count() );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonBase* btbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( btbase );
    btbase->HandleResourceChange( 0 );
    
    CleanupStack::PopAndDestroy( btbase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonBase* btbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( btbase );
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* buf = HBufC8::NewL( KHbufSize );
    CleanupStack::PushL( buf );
    TPtr8 ptr = buf->Des();
    stream.Open( ptr );
    btbase->WriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    CleanupStack::PopAndDestroy( 3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseDrawStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseDrawStateL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonBase* abtbase = CTestButtonBase::NewL();
    CleanupStack::PushL( abtbase );
    TInt err = abtbase->DoDrawState();
    CleanupStack::PopAndDestroy( abtbase );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseSetAllowTristateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseSetAllowTristateL( CStifItemParser& /*aItem*/ )
    {
    CTestButtonBase* abtbase = CTestButtonBase::NewL();
    CleanupStack::PushL( abtbase );
    TInt err = abtbase->DoSetAllowTristate();
    CleanupStack::PopAndDestroy( abtbase );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseCopyDrawStateToL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseCopyDrawStateToL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonBase* btbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( btbase );
    btbase->SetState( CEikButtonBase::ESet );
    CTestButtonBase* abtbase = CTestButtonBase::NewL();
    CleanupStack::PushL( abtbase );
    TInt err = abtbase->DoCopyDrawStateTo( btbase );
    CleanupStack::PopAndDestroy( 2 );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonBase* btbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( btbase );
    TKeyEvent keyevent;
    keyevent.iCode = EKeyDevice3;
    btbase->OfferKeyEventL( keyevent, EEventKey );
    CleanupStack::PopAndDestroy( btbase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtBaseInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtBaseInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonBase* btbase = new ( ELeave ) CEikButtonBase;
    CleanupStack::PushL( btbase );
    TCoeInputCapabilities ability = btbase->InputCapabilities();
    CleanupStack::PopAndDestroy( btbase );
    
    return KErrNone;
    }

// End of file
