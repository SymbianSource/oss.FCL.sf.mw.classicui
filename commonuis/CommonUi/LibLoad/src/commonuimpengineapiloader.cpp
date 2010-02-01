/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


#include <streaminglinkmodel.h>
#include "commonuimpengineapiloader.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CCommonUiMPEngineApiLoader::CCommonUiMPEngineApiLoader()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CCommonUiMPEngineApiLoader::ConstructL()
    {
    iMPlayerModel = CStreamingLinkModel::NewL();
    }

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CCommonUiMPEngineApiLoader* CCommonUiMPEngineApiLoader::NewL()
    {
    CCommonUiMPEngineApiLoader* self = 
        new( ELeave ) CCommonUiMPEngineApiLoader();

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CCommonUiMPEngineApiLoader::~CCommonUiMPEngineApiLoader()
    {
    delete iMPlayerModel;
    }
 
// ---------------------------------------------------------------------------
// Sets tone for all profiles.
// ---------------------------------------------------------------------------
//
TInt CCommonUiMPEngineApiLoader::CreateNewLinkFileL( 
    const TDesC& aFileName, 
    MDesCArray* aLinkArray, 
    TBool aOverWrite )
    {
    return iMPlayerModel->CreateNewLinkFileL( 
        aFileName, 
        aLinkArray, 
        aOverWrite );
    }

//----------------------------------------------------------------------------
// Launcher gate function
//----------------------------------------------------------------------------
EXPORT_C TAny* GateFunction()
    {
    CCommonUiMPEngineApiLoader* launcher = NULL;
    TRAPD( err, launcher = CCommonUiMPEngineApiLoader::NewL() );
    if( err != KErrNone )
        {
        return NULL;
        }

    return launcher;
    }

//  End of File  
