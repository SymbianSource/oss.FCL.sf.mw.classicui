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
* Description:  test EIKCOLIB.H
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <f32file.h>
#include <eikcolib.h>
#include <akntitle.h>

#include "testsdkinitialization.h"

// ============================ MEMBER FUNCTIONS ===============================
// =========================== CLASS CEikCoCtlLibrary===========================
// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestCCLResourceFile
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestCCLResourceFile( CStifItemParser& /*aItem*/ )
    {
    TFileName fileName = CEikCoCtlLibrary::ResourceFile();
    _LIT(KFileName,"z:\\resource\\eikcoctl.rsc");
    STIF_ASSERT_TRUE( 0 == fileName.Compare( KFileName ) );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestCCLControlFactory
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestCCLControlFactory( CStifItemParser& /*aItem*/ )
    {
    TCreateByTypeFunction function = CEikCoCtlLibrary::ControlFactory();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestCCLButtonGroupFactory
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestCCLButtonGroupFactory( CStifItemParser& /*aItem*/ )
    {
    TCreateButtonGroupByTypeFunction function = CEikCoCtlLibrary::ButtonGroupFactory();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestAUFCEikAppUiFactoryL 
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestAUFCEikAppUiFactoryL( CStifItemParser& /*aItem*/ )
    {
    CEikAppUiFactory* factory = new (ELeave) CEikAppUiFactory;
    CleanupStack::PushL( factory );
    STIF_ASSERT_NOT_NULL( factory );
    
    CleanupStack::PopAndDestroy( factory );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestAUFTouchPaneL 
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestAUFTouchPaneL( CStifItemParser& /*aItem*/ )
    {
    CEikAppUiFactory* factory = new (ELeave) CEikAppUiFactory;
    CleanupStack::PushL( factory );
    STIF_ASSERT_NOT_NULL( factory );
    
    CAknTouchPane* pane = factory->TouchPane();
    STIF_ASSERT_NULL( pane );
    
    CleanupStack::PopAndDestroy( factory );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestAUFPopupToolbarL 
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestAUFPopupToolbarL( CStifItemParser& /*aItem*/ )
    {
    CEikAppUiFactory* factory = new (ELeave) CEikAppUiFactory;
    CleanupStack::PushL( factory );
    STIF_ASSERT_NOT_NULL( factory );
    
    CAknToolbar* toolBar = factory->PopupToolbar();
    STIF_ASSERT_NULL( toolBar );
    
    CleanupStack::PopAndDestroy( factory );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestAUFCurrentPopupToolbarL 
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestAUFCurrentPopupToolbarL( CStifItemParser& /*aItem*/ )
    {
    CEikAppUiFactory* factory = new (ELeave) CEikAppUiFactory;
    CleanupStack::PushL( factory );
    STIF_ASSERT_NOT_NULL( factory );
    
    CAknToolbar* toolBar = factory->CurrentPopupToolbar();
    STIF_ASSERT_NULL( toolBar );
    
    CleanupStack::PopAndDestroy( factory );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestAUFSetViewPopupToolbarL 
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestAUFSetViewPopupToolbarL( CStifItemParser& /*aItem*/ )
    {
    CEikAppUiFactory* factory = new (ELeave) CEikAppUiFactory;
    CleanupStack::PushL( factory );
    STIF_ASSERT_NOT_NULL( factory );
    
    CAknToolbar* toolBar = factory->CurrentFixedToolbar();
    
    factory->SetViewPopupToolbar( toolBar );

    CleanupStack::PopAndDestroy( factory );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestAUFCurrentFixedToolbarL 
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestAUFCurrentFixedToolbarL( CStifItemParser& /*aItem*/ )
    {
    CEikAppUiFactory* factory = new (ELeave) CEikAppUiFactory;
    CleanupStack::PushL( factory );
    STIF_ASSERT_NOT_NULL( factory );
    
    CAknToolbar* toolBar = factory->CurrentFixedToolbar();
    STIF_ASSERT_NULL( toolBar );
    
    CleanupStack::PopAndDestroy( factory );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestAUFSetViewFixedToolbarL 
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestAUFSetViewFixedToolbarL( CStifItemParser& /*aItem*/ )
    {
    CEikAppUiFactory* factory = new (ELeave) CEikAppUiFactory;
    CleanupStack::PushL( factory );
    STIF_ASSERT_NOT_NULL( factory );
    
    CAknToolbar* toolBar = factory->CurrentFixedToolbar();
    
    factory->SetViewFixedToolbar( toolBar );

    CleanupStack::PopAndDestroy( factory );
    
    return KErrNone;
    
    }
