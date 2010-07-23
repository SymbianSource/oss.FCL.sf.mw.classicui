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
* Description:  Test AknServerApp.h 
*
*/


// INCLUDE FILES
#include "testsdkappservicebase.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKAppServiceBase::ServiceUid
// -----------------------------------------------------------------------------
void  CTestSDKAppServiceBase::CreateL()
    {
    CAknAppServiceBase::CreateL();
    }

// -----------------------------------------------------------------------------
// CTestSDKAppServiceBase::ServiceUid
// -----------------------------------------------------------------------------
void CTestSDKAppServiceBase::ServiceL( const RMessage2& aMessage )
    {
    CAknAppServiceBase::ServiceL( aMessage );
    }

// -----------------------------------------------------------------------------
// CTestSDKAppServiceBase::ServiceUid
// -----------------------------------------------------------------------------
void CTestSDKAppServiceBase::ServiceError( const RMessage2& aMessage,TInt aError )
    {
    CAknAppServiceBase::ServiceError( aMessage, aError );
    }
