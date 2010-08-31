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
* Description:  Notifier server app session implementation.
*
*/

#include <e32notif.h>
#include <eiksrvs.h>

#include "AknNotiferAppServerApplication.h" 
#include "AknNotifierAppServer.h" 
#include "AknNotifierAppServerSession.h"
#include "AknNotifierControllerUtilities.h"

const TInt KINPUTSLOT = 1; 
const TInt KREPLYSLOT = 2; 
const TInt KEikonServerSecureId = 0x10003A4A;

LOCAL_C void SetEikonServerFree(TAny* aPtr)
    {
    *(TBool*)aPtr = 0; // points to boolean
    }
  
EXPORT_C CAknNotifierServerAppService::CAknNotifierServerAppService(
    const CAknNotifierAppServer& aAppServer) 
:iOwner(const_cast<CAknNotifierAppServer&>(aAppServer))
    {
    }

EXPORT_C CAknNotifierServerAppService::~CAknNotifierServerAppService()
    {       
    delete iInputBuf;
    delete iReplyBuf;       
    }
   
EXPORT_C void CAknNotifierServerAppService::HandleMessageL(const RMessage2& aMessage)
    {    
    CAknNotifierAppServerAppUi* appUi = (CAknNotifierAppServerAppUi*)CEikonEnv::Static()->AppUi();
    
    if (appUi && aMessage.SecureId().iId == KEikonServerSecureId)
        {
        appUi->EikSrvBlocked() = ETrue;
        CleanupStack::PushL(TCleanupItem(SetEikonServerFree, &(appUi->EikSrvBlocked()) ));     
        }
    
    if (aMessage.Function() == KDoNotifierControllerCommand)
        {
        if (appUi && appUi->NotifierControllerUtility())
            {
            appUi->NotifierControllerUtility()->DoNotifierContollerCommandL(
                (CAknNotifierControllerUtility::TNotifierControllerCommand)aMessage.Int0());
            
            CleanupStack::PopAndDestroy(); // Free eikon server 
            }
    
        aMessage.Complete(KErrNone);    
        return;
        }
            
    /* Disable showing notifiers. CR #541 */

    /* switch ( aMessage.Function() ) */
    /*     { */
    /*     case EStartNotifier: */
    /*          { */
    /*          ResolveBuffersL(aMessage); */
    /*          TPtr8 ptr = iReplyBuf->Des(); */
    /*          iOwner.StartNotifierL(TUid::Uid(aMessage.Int0()),*iInputBuf, ptr); */
    /*          WriteReplyL(aMessage); */
    /*          break;    */
    /*          } */
    /*     case EUpdateNotifier: */
    /*          { */
    /*          ResolveBuffersL(aMessage); */
    /*          TPtr8 ptr2 = iReplyBuf->Des(); */
    /*          iOwner.UpdateNotifierL(TUid::Uid(aMessage.Int0()),*iInputBuf, ptr2); */
    /*          WriteReplyL(aMessage); */
    /*          break; */
    /*          } */
    /*     case ECancelNotifier: */
    /*          { */
    /*          iOwner.CancelNotifier(TUid::Uid(aMessage.Int0()));                  */
    /*          aMessage.Complete(KErrNone); */
    /*          break; */
    /*          } */
    /*     case EStartNotifierAndGetResponse: */
    /*          { */
    /*          if (appUi && appUi->EikSrvBlocked()) */
    /*              { */
    /*              CleanupStack::PopAndDestroy(); // Free eikon server  */
    /*              } */
                    
    /*          ResolveBuffersL(aMessage); */
             
    /*          iOwner.StartNotifierAndGetResponseL( */
    /*              TUid::Uid(aMessage.Int0()),  */
    /*              *iInputBuf,  */
    /*              aMessage,  */
    /*              KREPLYSLOT);  */
                
    /*          break; */
    /*          } */
    /*     case EUpdateNotifierAndGetResponse: */
    /*          { */
    /*          if (appUi && appUi->EikSrvBlocked()) */
    /*              { */
    /*              CleanupStack::PopAndDestroy(); // Free eikon server  */
    /*              } */
                    
    /*          ResolveBuffersL(aMessage); */
             
    /*          iOwner.UpdateNotifierAndGetResponseL( */
    /*             TUid::Uid(aMessage.Int0()),  */
    /*             *iInputBuf,  */
    /*             aMessage,  */
    /*             KREPLYSLOT);  */
                
    /*          break; */
    /*          } */
    /*     default: */
    /*         { */
    /*         CAknAppServiceBase::ServiceL(aMessage);            */
    /*         } */
    /*     } */        
    
    aMessage.Complete(KErrNone);    

    if (appUi && appUi->EikSrvBlocked())
        {
        CleanupStack::PopAndDestroy(); // Free eikon server 
        }    
    }
    
EXPORT_C TBool CAknNotifierServerAppService::AllowClientL(const RMessage2& aMessage)
    { 
    // By default, we don't serve other process than notifier server.
    return (aMessage.SecureId().iId == KEikonServerSecureId);
    }

                   
EXPORT_C void CAknNotifierServerAppService::ServiceL(const RMessage2& aMessage)
    {
    if (!AllowClientL(aMessage)) 
        {  
        aMessage.Complete(KErrAccessDenied);
        }
    else 
        {
        HandleMessageL(aMessage);   
        }   
    }

    
void CAknNotifierServerAppService::ResolveBuffersL(const RMessage2& aMessage)
    {
    delete iInputBuf;
    iInputBuf = 0;
    
    delete iReplyBuf;
    iReplyBuf = 0;
    
    iInputBuf = HBufC8::NewL(aMessage.GetDesLengthL(KINPUTSLOT));
    
    TPtr8 ptr = iInputBuf->Des();
    aMessage.Read(KINPUTSLOT,ptr);
    
    if (aMessage.Function() == EStartNotifier || aMessage.Function() == EUpdateNotifier)
        {
        iReplyBuf = HBufC8::NewL(aMessage.GetDesMaxLengthL(KREPLYSLOT));   
        }
    }


void CAknNotifierServerAppService::WriteReplyL(const RMessage2& aMessage)
    {
    aMessage.WriteL(KREPLYSLOT, *iReplyBuf);
    aMessage.Complete(KErrNone);
    }

// End of file
