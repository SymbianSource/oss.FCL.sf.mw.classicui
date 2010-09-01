/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/



#include <eiklbbut.h>
#include <eikcmbut.h>

#include "bctestmix50patchmisc.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestCommandButtonBase* CBCTestCommandButtonBase::NewL( )
    {
    CBCTestCommandButtonBase* self = 
    	new( ELeave ) CBCTestCommandButtonBase( );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestCommandButtonBase::CBCTestCommandButtonBase()
    {
    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestCommandButtonBase::~CBCTestCommandButtonBase()
    {  
    }

// --------------------------------------------------------------------------
// CBCTestCommandButtonBase::Draw
// ---------------------------------------------------------------------------
//
void CBCTestCommandButtonBase::Draw( const TRect& aRect ) const
    {
    CEikCommandButtonBase::Draw( aRect );
    }

// --------------------------------------------------------------------------
// CBCTestCommandButtonBase::WriteInternalStateL
// --------------------------------------------------------------------------
//
void CBCTestCommandButtonBase::WriteInternalStateL(
        RWriteStream& aWriteStream ) const
    {
    CEikButtonBase::WriteInternalStateL( aWriteStream );
    }

// ---------------------------------------------------------------------------
// CBCTestVolumeSettingPage::CBCTestVolumeSettingPage
// ---------------------------------------------------------------------------
//
CBCTestVolumeSettingPage::CBCTestVolumeSettingPage(TInt aResourceID, TInt& aVolume) :
       CAknVolumeSettingPage( aResourceID, aVolume)
    {
    
    }

// ---------------------------------------------------------------------------
// CBCTestIntegerSettingPage::CBCTestIntegerSettingPage
// ---------------------------------------------------------------------------
//
CBCTestIntegerSettingPage::CBCTestIntegerSettingPage( TInt aResourceId, TInt& aValue, TInt aFlags ):
     CAknIntegerSettingPage( aResourceId, aValue, aFlags )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestTextSettingPage::CBCTestTextSettingPage
// ---------------------------------------------------------------------------
//
CBCTestTextSettingPage::CBCTestTextSettingPage( TInt aResourceId, TDes& aText, TInt aFlags ):
     CAknTextSettingPage( aResourceId, aText, aFlags )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestSliderSettingPage::CBCTestSliderSettingPage
// ---------------------------------------------------------------------------
//
CBCTestSliderSettingPage::CBCTestSliderSettingPage( TInt aResourceId, TInt& aSliderValue ):
     CAknSliderSettingPage( aResourceId, aSliderValue )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPatchAknSettingPage::CBCTestPatchAknSettingPage
// ---------------------------------------------------------------------------
//
CBCTestPatchAknSettingPage::CBCTestPatchAknSettingPage( TInt aResourceId )
    : CAknSettingPage( aResourceId )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestRadioButtonSettingPage::CBCTestRadioButtonSettingPage
// ---------------------------------------------------------------------------
//
CBCTestRadioButtonSettingPage::CBCTestRadioButtonSettingPage( TInt aResourceId,
    TInt& aCurrentSelectionItem, const MDesCArray* aItemArray):
    CAknRadioButtonSettingPage( aResourceId, aCurrentSelectionItem, aItemArray )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestNumericPasswordSettingPage::CBCTestNumericPasswordSettingPage
// ---------------------------------------------------------------------------
//
CBCTestNumericPasswordSettingPage::CBCTestNumericPasswordSettingPage(
    TInt aResourceId,
    TDes& aNewPassword,
    const TDesC& aOldPassword ):
    CAknNumericPasswordSettingPage(aResourceId, aNewPassword, aOldPassword)
    {
    }
    
// ---------------------------------------------------------------------------
// CBCTestAlphaPasswordSettingPage::CBCTestAlphaPasswordSettingPage
// ---------------------------------------------------------------------------
//
CBCTestAlphaPasswordSettingPage::CBCTestAlphaPasswordSettingPage(
    TInt aResourceID,
    TDes& aNewPassword,
    const TDesC& aOldPassword ):
    CAknAlphaPasswordSettingPage( aResourceID, aNewPassword, aOldPassword )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPasswordSettingPage::CBCTestPasswordSettingPage
// ---------------------------------------------------------------------------
//
CBCTestPasswordSettingPage::CBCTestPasswordSettingPage(
    TInt aResourceId,
    TDes& aNewPassword,
    const TDesC& aOldPassword ) :   
    CAknPasswordSettingPage( aResourceId, aNewPassword, aOldPassword )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestIpFieldSettingPage::CBCTestIpFieldSettingPage
// ---------------------------------------------------------------------------
//
CBCTestIpFieldSettingPage::CBCTestIpFieldSettingPage( 
        TInt aResourceId, 
        TInetAddr& aIpAddress )
    : CAknIpFieldSettingPage( aResourceId, aIpAddress )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestTimeOffsetSettingPage::CBCTestTimeOffsetSettingPage
// ---------------------------------------------------------------------------
//
CBCTestTimeOffsetSettingPage::CBCTestTimeOffsetSettingPage( TInt aResourceId, 
        TTimeIntervalSeconds& aTimeOffsetValue ):
     CAknTimeOffsetSettingPage( aResourceId, aTimeOffsetValue )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestCheckBoxSettingPage::CBCTestCheckBoxSettingPage
// ---------------------------------------------------------------------------
//
CBCTestCheckBoxSettingPage::CBCTestCheckBoxSettingPage( TInt aResourceId, 
    CSelectionItemList* aItemArray ) : 
    CAknCheckBoxSettingPage( aResourceId, aItemArray )
    {    
    }

// ---------------------------------------------------------------------------
// CBCTestAppServiceBase::HandleServerAppExit(TInt aReason)
// ---------------------------------------------------------------------------
//
void CBCTestAppServiceBase::HandleServerAppExit( TInt aReason )
	{
	MAknServerAppExitObserver::HandleServerAppExit( aReason );
	}

// ----------------------------------------------------------------------------
// CAknAppServiceDrv::CreateL()
// ----------------------------------------------------------------------------
//
void CBCTestAppServiceBase::CreateL()
	{
	CAknAppServiceBase::CreateL();
	}

// ----------------------------------------------------------------------------
// CAknAppServiceDrv::ServiceL(const RMessage2& aMessage)
// ----------------------------------------------------------------------------
//
void CBCTestAppServiceBase::ServiceL( const RMessage2& aMessage )
	{
	CAknAppServiceBase::ServiceL( aMessage );
	}

// ----------------------------------------------------------------------------
// CAknAppServiceDrv::ServiceError(const RMessage2& aMessage,TInt aError)
// ----------------------------------------------------------------------------
//
void CBCTestAppServiceBase::ServiceError( 
        const RMessage2& aMessage,TInt aError )
	{
	CAknAppServiceBase::ServiceError( aMessage,aError );
	}
