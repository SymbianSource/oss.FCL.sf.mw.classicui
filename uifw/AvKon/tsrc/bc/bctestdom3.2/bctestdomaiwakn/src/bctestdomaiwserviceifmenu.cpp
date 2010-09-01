/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test CAiwServiceIfMenu and CAiwServiceIfBase
*
*/



#include "bctestdomaiwserviceifmenu.h"


const TUid KUidInterface = { 0xA000409E }; // UID of the application.

// ======== MEMBER FUNCTIONS ========


// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestDomAiwServiceIfMenu* CBCTestDomAiwServiceIfMenu::NewL()
    {
    CBCTestDomAiwServiceIfMenu* self = CBCTestDomAiwServiceIfMenu::NewLC();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestDomAiwServiceIfMenu* CBCTestDomAiwServiceIfMenu::NewLC()
    {
    CBCTestDomAiwServiceIfMenu* self = 
        new( ELeave ) CBCTestDomAiwServiceIfMenu;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestDomAiwServiceIfMenu::~CBCTestDomAiwServiceIfMenu()
    {
    
    
    }

// ---------------------------------------------------------------------------
// TestFuncExtensionInterface.
// to test the Function ExtensionInterface().
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwServiceIfMenu::TestFuncExtensionInterface() 
    {
    CAiwServiceIfBase::ExtensionInterface( KUidInterface ); 
    
    CAiwServiceIfMenu::ExtensionInterface( KUidInterface );  
    }
     
// ---------------------------------------------------------------------------
// From class CAiwServiceIfBase.
// InitialiseL
// ---------------------------------------------------------------------------
//    
void CBCTestDomAiwServiceIfMenu::InitialiseL(
         MAiwNotifyCallback& /*aFrameworkCallback*/,
         const RCriteriaArray& /*aInterest*/) 
    {
    
    }
        
// ---------------------------------------------------------------------------
// From class CAiwServiceIfBase.
// InitializeMenuPaneL
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwServiceIfMenu::HandleServiceCmdL(
         const TInt& /*aCmdId*/,
         const CAiwGenericParamList& /*aInParamList*/,
         CAiwGenericParamList& /*aOutParamList*/,
         TUint /*aCmdOptions*/ ,
         const MAiwNotifyCallback* /*aCallback*/ ) 
    {
    
    }
           
// ---------------------------------------------------------------------------
// From class CAiwServiceIfMenu.
// InitializeMenuPaneL
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwServiceIfMenu::InitializeMenuPaneL(
         CAiwMenuPane& /*aMenuPane*/,
         TInt /*aIndex*/,
         TInt /*aCascadeId*/,
         const CAiwGenericParamList& /*aInParamList*/)
    {  

    }

// ---------------------------------------------------------------------------
// From class CAiwServiceIfMenu.
// HandleMenuCmdL
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwServiceIfMenu::HandleMenuCmdL(
         TInt /* aMenuCmdId */,
         const CAiwGenericParamList& /*aInParamList*/,
         CAiwGenericParamList& /*aOutParamList*/,
         TUint /*aCmdOptions */,
         const MAiwNotifyCallback* /*aCallback*/ )
    {
    
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAiwServiceIfMenu::CBCTestDomAiwServiceIfMenu()
    {

    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwServiceIfMenu::ConstructL()
    {

    }


