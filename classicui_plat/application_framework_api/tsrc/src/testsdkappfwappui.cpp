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
* Description:  Test application_framework_api
*
*/



// INCLUDE FILES
#include "testsdkappfwappui.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAppFWAppUiBase::CTestSDKAppFWAppUiBase
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKAppFWAppUiBase::CTestSDKAppFWAppUiBase()
    {
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CTestSDKAppFWAppUiBase::~CTestSDKAppFWAppUiBase()
    { 
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUiBase::ProtectedHandleScreenDeviceChangedL
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUiBase::ProtectedHandleScreenDeviceChangedL()
    {
    HandleScreenDeviceChangedL();
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUiBase::ProtectedHandleApplicationSpecificEventL
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUiBase::ProtectedHandleApplicationSpecificEventL( TInt aType,
    const TWsEvent& aEvent )
    {
    HandleApplicationSpecificEventL( aType, aEvent );
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUiBase::ProtectedSetFullScreenApp
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUiBase::ProtectedSetFullScreenApp( TBool aIsFullScreen )
    {
    SetFullScreenApp( aIsFullScreen );
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUiBase::ProtectedReplaceKeySoundsL
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUiBase::ProtectedReplaceKeySoundsL( TInt aUid )
    {
    ReplaceKeySoundsL( aUid );
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUiBase::ProtectedMopSupplyObject
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUiBase::ProtectedMopSupplyObject( TTypeUid aId )
    {
    MopSupplyObject( aId );
    }



// -----------------------------------------------------------------------------
// CTestSDKAppFWAppUi::CTestSDKAppFWAppUi
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKAppFWAppUi::CTestSDKAppFWAppUi()
    {
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CTestSDKAppFWAppUi::~CTestSDKAppFWAppUi()
    { 
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUi::ProtectedHandleStatusPaneSizeChange
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUi::ProtectedHandleStatusPaneSizeChange()
    {
    CAknAppUi::HandleStatusPaneSizeChange();
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUi::ProtectedHandleSystemEventL
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUi::ProtectedHandleSystemEventL( const TWsEvent& aEvent )
    {
    HandleSystemEventL( aEvent );
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUi::ProtectedReserved_MtsmPosition
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUi::ProtectedReserved_MtsmPosition()
    {
    Reserved_MtsmPosition();
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUi::ProtectedReserved_MtsmObject
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUi::ProtectedReserved_MtsmObject()
    {
    Reserved_MtsmObject();
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUi::ProtectedHandleForegroundEventL
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUi::ProtectedHandleForegroundEventL( TBool aForeground )
    {
    HandleForegroundEventL( aForeground );
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUi::ProtectedHandleForegroundEventL
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUi::ProtectedHandleWsEventL( const TWsEvent& aEvent,
    CCoeControl* aDestination )
    {
    CAknAppUi::HandleWsEventL( aEvent, aDestination );
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUi::ProtectedSetKeyBlockMode
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUi::ProtectedSetKeyBlockMode( TAknKeyBlockMode aMode )
    {
    SetKeyBlockMode( aMode );
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWAppUi::ProtectedHandleErrorL
//-----------------------------------------------------------------------------
//
void CTestSDKAppFWAppUi::ProtectedHandleErrorL( TInt aError, HBufC** aErrorDesc,
    TBool aShowNote )
    {
    HandleErrorL( aError, aErrorDesc, aShowNote );
    }

//  End of File
