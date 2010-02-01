/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Avkon SliderAndIcons test app
*
*/









// INCLUDE FILES
#include "BCTestSliderAndIconsApp.h"
#include "BCTestSliderAndIconsDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestSliderAndIconsApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestSliderAndIconsApp::AppDllUid() const
    {
    return KUidBCTestSliderAndIcons;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestSliderAndIconsApp::CreateDocumentL()
// Creates CBCTestSliderAndIconsDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestSliderAndIconsApp::CreateDocumentL()
    {
    return CBCTestSliderAndIconsDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestSliderAndIconsApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestSliderAndIconsApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
