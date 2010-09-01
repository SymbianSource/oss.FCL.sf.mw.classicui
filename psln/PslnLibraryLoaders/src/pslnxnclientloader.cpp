/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  XnClient.DLL wrapper.
*
*/


#include <XnClient.h>

#include "PslnXNClientLoader.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnXNClientLoader::CPslnXNClientLoader()
    {
    }

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CPslnXNClientLoader* CPslnXNClientLoader::NewL()
    { 
    CPslnXNClientLoader* self = 
        new( ELeave ) CPslnXNClientLoader();

    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CPslnXNClientLoader::~CPslnXNClientLoader()
    {
    delete iXknClient;
    }

//----------------------------------------------------------------------------   
// Launcher gate function
//----------------------------------------------------------------------------
TXnServiceCompletedMessage CPslnXNClientLoader::GetListHeaders( 
    const CXnODT& aSearchMask, CArrayPtrFlat<CXnODT>& aHeaderList )
    {
    return iXknClient->XnGetListHeaders( aSearchMask, aHeaderList );
    }

//----------------------------------------------------------------------------   
// Launcher gate function
//----------------------------------------------------------------------------
TXnServiceCompletedMessage CPslnXNClientLoader::SetActiveTheme( 
    const CXnODT& aSetMask, CXnODT& aHeader )
    {
    return iXknClient->XnSetActiveTheme( aSetMask, aHeader );
    }

//----------------------------------------------------------------------------   
// Launcher gate function
//----------------------------------------------------------------------------
void CPslnXNClientLoader::GetNextHeader()
    {
    iXknClient->XnGetNextHeader();
    }

//----------------------------------------------------------------------------   
// Launcher gate function
//----------------------------------------------------------------------------
TXnServiceCompletedMessage CPslnXNClientLoader::CancelGetListHeaders()
    {
    return iXknClient->XnCancelGetListHeaders();
    }

//----------------------------------------------------------------------------   
// Create client.
//----------------------------------------------------------------------------
void CPslnXNClientLoader::CreateClientL( 
        MXnThemeManagementServiceObserver& aObserver )
    {
    iXknClient = CXnClient::NewL( aObserver );
    }

//----------------------------------------------------------------------------
// Launcher gate function
//----------------------------------------------------------------------------
EXPORT_C TAny* GateFunction()
    {
    CPslnXNClientLoader* launcher = NULL;
    TRAPD( err, launcher = CPslnXNClientLoader::NewL() );
    if( err != KErrNone )
        {
        return NULL;
        }

    return launcher;
    }

//  End of File  
