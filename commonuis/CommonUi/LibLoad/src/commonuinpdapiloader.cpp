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


#include "commonuinpdapiloader.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CCommonUiNpdApiLoader::CCommonUiNpdApiLoader()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CCommonUiNpdApiLoader::ConstructL()
    {
    }

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CCommonUiNpdApiLoader* CCommonUiNpdApiLoader::NewL()
    {
    CCommonUiNpdApiLoader* self = 
        new( ELeave ) CCommonUiNpdApiLoader();

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CCommonUiNpdApiLoader::~CCommonUiNpdApiLoader()
    {
    }
 
// ---------------------------------------------------------------------------
// Sets tone for all profiles.
// ---------------------------------------------------------------------------
//
void CCommonUiNpdApiLoader::SaveFileAsMemoL( const TDesC& /*aFileName*/ )
    {
    }

// ---------------------------------------------------------------------------
// Sets tone for all profiles.
// ---------------------------------------------------------------------------
//
void CCommonUiNpdApiLoader::SaveFileAsMemoL( const RFile& /*aFileHandle*/ )
    {
    }

//----------------------------------------------------------------------------
// Launcher gate function
//----------------------------------------------------------------------------
EXPORT_C TAny* GateFunction()
    {
    CCommonUiNpdApiLoader* launcher = NULL;
    TRAPD( err, launcher = CCommonUiNpdApiLoader::NewL() );
    if( err != KErrNone )
        {
        return NULL;
        }
    
    return launcher;
    }

//  End of File  
