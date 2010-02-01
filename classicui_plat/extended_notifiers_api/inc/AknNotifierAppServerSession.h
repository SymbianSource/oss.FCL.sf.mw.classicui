/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Notifier server app session declaration.
*
*/

#ifndef __AKNNOTIFIERPSERVERAPPSESSION_H__
#define __AKNNOTIFIERPSERVERAPPSESSION_H__

#include <AknServerApp.h>

class CAknNotifierAppServer;

class CAknNotifierServerAppService : public CAknAppServiceBase
    {
public: 
    IMPORT_C CAknNotifierServerAppService(const CAknNotifierAppServer& aAppServer);         
    IMPORT_C ~CAknNotifierServerAppService();

public: // from CAknAppServiceBase    
    IMPORT_C void ServiceL(const RMessage2& aMessage);
    
public: // New methods      
    /**
     * ServiceL calls this method to decide whether the message will be served or not.
     * Default implementation just checks that client is Symbian Notifier server thread, other 
     * clients are not served.
     * @since 3.0 
     * @param aMessage Message from client.
     * @return Boolean, is a client allowed to access our services.
     */       
    IMPORT_C virtual TBool AllowClientL(const RMessage2& aMessage);

    /**
     * Actual message handling, this method commands server to do notifier operations based on
     * received message. ServiceL calls this method if client has passed AllowClientL checking.
     * 
     * @since 3.0 
     * @param aMessage Message from client.
     */       
    IMPORT_C virtual void HandleMessageL(const RMessage2& aMessage);
    
private:        
    void ResolveBuffersL(const RMessage2& aMessage);
    void WriteReplyL(const RMessage2& aMessage);
        
private:    
    CAknNotifierAppServer& iOwner; 
    HBufC8* iInputBuf;
    HBufC8* iReplyBuf;      
    };

#endif // __AKNNOTIFIERPSERVERAPPSESSION_H__

// End of file
