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



#ifndef C_TESTSDKAPPSERVICE_H
#define C_TESTSDKAPPSERVICE_H

class RTestSDKAppService : public RAknAppServiceBase
    {
public:
    
    /**
    *  from class RAknAppServiceBase
    */
    TUid ServiceUid() const;
    
    /**
    * Destructor.
    */
    ~RTestSDKAppService();
    };

#endif /*C_TESTSDKAPPSERVICE_H*/
