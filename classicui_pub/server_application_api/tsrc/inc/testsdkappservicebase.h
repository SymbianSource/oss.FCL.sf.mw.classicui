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

#include <aknserverapp.h>

#ifndef C_TESTSDKAPPSERVICEBASE_H
#define C_TESTSDKAPPSERVICEBASE_H

class CTestSDKAppServiceBase : public CAknAppServiceBase,
                               public MAknServerAppExitObserver
    {
public:
    
    /**
    *  CreateL test function for testing the 
    * Test CreateL function
    */
    void CreateL();
    
    /**
    *  ServiceL test function for testing the 
    * Test ServiceL function
    */
    void ServiceL( const RMessage2& aMessage );
    
    /**
    *  ServiceError test function for testing the 
    * Test ServiceError function
    */
    void ServiceError( const RMessage2& aMessage,TInt aError );
    };

#endif /*C_TESTSDKAPPSERVICEBASE_H*/
