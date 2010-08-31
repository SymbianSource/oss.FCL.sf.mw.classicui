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
* Description:  test EIKCTLIB.H
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <f32file.h>
#include <eikctlib.h>

#include "testsdkinitialization.h"

// ============================ MEMBER FUNCTIONS ===============================
// =========================== CLASS CEikCoCtlLibrary===========================
// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestCLResourceFile
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestCLResourceFile( CStifItemParser& /*aItem*/ )
    {
    TFileName fileName = CEikCtlLibrary::ResourceFile();
    _LIT(KFileName,"z:\\resource\\eikctl.rsc");
    STIF_ASSERT_TRUE( 0 == fileName.Compare( KFileName ) );
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestCLControlFactory
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestCLControlFactory( CStifItemParser& /*aItem*/ )
    {
    TCreateByTypeFunction function = CEikCtlLibrary::ControlFactory();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestCLInitializeL 
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestCLInitializeL( CStifItemParser& /*aItem*/ )
    {
    CEikCtlLibrary::InitializeL();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKInitialization::TestCLButtonGroupFactory
// -----------------------------------------------------------------------------
TInt CTestSDKInitialization::TestCLButtonGroupFactory( CStifItemParser& /*aItem*/ )
    {
    TCreateButtonGroupByTypeFunction function = CEikCtlLibrary::ButtonGroupFactory();
    
    return KErrNone;
    
    }
