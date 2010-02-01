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
* Description:  Notifier app server implementation.
*
*/

#include <AknNotifierWrapperDefs.h>
#include "AknNotifierAppServer.h"
#include "AknNotifierAppServerSession.h"
#include "AknNotiferAppServerApplication.h"
 
typedef CArrayPtr<MEikSrvNotifierBase2>* (*CreateEikSrvNotifierBase)();  

class CNotifierNames: public CBase
    {    
public:
    ~CNotifierNames()
        {
        for (TInt i = 0; i < iNotifierNames.Count(); i++)   
            {
            delete (iNotifierNames[i]);
            }
    
        iNotifierNames.Close();
        }
        
    MNotifLibraryOwningServer* iFinder; 
    RPointerArray<HBufC> iNotifierNames;    
    };

    
EXPORT_C CAknNotifierAppServer::CAknNotifierAppServer()   
    {   
    }
        
EXPORT_C CAknNotifierAppServer::~CAknNotifierAppServer()
    {
    TInt i;

    delete iNotifierNames;

    for (i = 0; i < iNotifierArray.Count(); i++)    
        {
        iNotifierArray[i]->Release();
        }
    
    iNotifierArray.Close();     
    
    for (i = 0; i < iLibraries.Count(); i++)
        {
        iLibraries[i].Close();  
        }
        
    iLibraries.Close(); 
    }

 
EXPORT_C void CAknNotifierAppServer::StartNotifierL(TUid aNotifierUid, const TDesC8& aBuffer,
    TDes8& aResponse)
    {
    MEikSrvNotifierBase2* impl = FindImplementation(aNotifierUid);  
    User::LeaveIfNull(impl);    
    aResponse.Copy(impl->StartL(aBuffer));
    }
    
    
EXPORT_C void CAknNotifierAppServer::CancelNotifier(TUid aNotifierUid)
    {
    MEikSrvNotifierBase2* impl = FindImplementation(aNotifierUid);  
    if (impl)
        {
        impl->Cancel();    
        }
    }
    
    
EXPORT_C void CAknNotifierAppServer::StartNotifierAndGetResponseL(TUid aNotifierUid, 
    TDesC8& aBuffer, const RMessagePtr2& aMsg, TInt aReplySlot)
    {
    MEikSrvNotifierBase2* impl = FindImplementation(aNotifierUid);  
    User::LeaveIfNull(impl);    
    impl->StartL(aBuffer,aReplySlot,aMsg);
    }
    
    
EXPORT_C void CAknNotifierAppServer::UpdateNotifierL(TUid aNotifierUid, const TDesC8& aBuffer,
    TDes8& aResponse)
    {
    MEikSrvNotifierBase2* impl = FindImplementation(aNotifierUid);  
    User::LeaveIfNull(impl);    
    aResponse.Copy(impl->UpdateL(aBuffer));     
    }
    
EXPORT_C void CAknNotifierAppServer::UpdateNotifierAndGetResponseL(TUid aNotifierUid, 
    TDesC8& aBuffer, const RMessagePtr2& aMsg, TInt aReplySlot)
    {
    MEikSrvNotifierBase2* impl = FindImplementation(aNotifierUid);  
    User::LeaveIfNull(impl);    
    impl->UpdateL( aBuffer, aReplySlot, aMsg );
    }
    
LOCAL_C void DeleteTempMArray(TAny* aPtr)
    {
    CArrayPtr<MEikSrvNotifierBase2>* const array = 
        reinterpret_cast<CArrayPtr<MEikSrvNotifierBase2>*>(aPtr);
        
    for (TInt i = array->Count()-1; i >= 0 ; i--)
        {
        array->At(i)->Release(); // effectively delete 
        }

    delete array;
    }   
    
    
EXPORT_C void CAknNotifierAppServer::LoadNotifiersL()
    {
    __ASSERT_DEBUG(iNotifierNames && iNotifierNames->iNotifierNames.Count(), User::Invariant());
        
    TInt i, j;
    CArrayPtr<MEikSrvNotifierBase2>* notArray;  
        
    const TUid KDllUid = {0x10000079};
    
    for (i = 0; i < iNotifierNames->iNotifierNames.Count(); i++)
        {
        notArray = CreateImplementationsL(
            *(iNotifierNames->iNotifierNames[i]), 
            TUidType(KDllUid, KUidNotifierPlugInV2, KNullUid));
            
        User::LeaveIfNull(notArray);        
        CleanupStack::PushL(TCleanupItem(DeleteTempMArray,notArray));
        const TInt count = notArray->Count();
        for (j = count-1; j >= 0 ; j--)
            {
            notArray->At(j)->RegisterL();
            User::LeaveIfError(iNotifierArray.Append(notArray->At(j)));
            
            notArray->At(j)=0;
            notArray->Delete(j);
            }
            
        CleanupStack::PopAndDestroy(notArray); 
        }
    }


EXPORT_C void CAknNotifierAppServer::AppendNotifierLibNameL(const TDesC& aLibraryName)
    {
    if (!iNotifierNames)
        {
        iNotifierNames = new (ELeave) CNotifierNames;
        }

    HBufC* libName = aLibraryName.AllocLC();
    User::LeaveIfError(iNotifierNames->iNotifierNames.Append(libName));
    CleanupStack::Pop();
    }
                            
                                                                
MEikSrvNotifierBase2* CAknNotifierAppServer::FindImplementation(TUid aUid) const
    {
    if (iNotifierNames && iNotifierNames->iFinder)
        {
        return iNotifierNames->iFinder->FindImplementation(aUid);
        }
    for (TInt i = 0; i < iNotifierArray.Count(); i++)
        {
        if (iNotifierArray[i]->Info().iUid == aUid)
            {
            return iNotifierArray[i];   
            }
        }
    
    return NULL;    
    }
    
    
CArrayPtr<MEikSrvNotifierBase2>* CAknNotifierAppServer::CreateImplementationsL(
    const TDesC& aLibName, const TUidType& aUidType)
    {
    RLibrary lib;       
    
    CleanupClosePushL(lib);
    User::LeaveIfError(lib.Load(aLibName,_L("z:\\sys\\bin\\"),aUidType));
    CreateEikSrvNotifierBase libEntry =(CreateEikSrvNotifierBase)(lib.Lookup(1));   
    
    CArrayPtr<MEikSrvNotifierBase2>* array = 
        reinterpret_cast<CArrayPtr<MEikSrvNotifierBase2>*>((libEntry)());
        
    iLibraries.AppendL(lib);        
    CleanupStack::Pop(); // lib
    
    return array;
    }
                                                                                        
    
EXPORT_C CApaAppServiceBase* CAknNotifierAppServer::CreateServiceL(TUid aServiceType) const
    {
    if (aServiceType == KAknNotifierServiceUid)   
        {
        return new (ELeave) CAknNotifierServerAppService(*this);
        }
    else
        {
        return CAknAppServer::CreateServiceL(aServiceType); 
        }       
    }   
 
EXPORT_C void CAknNotifierAppServer::SetImplementationFinderL(MNotifLibraryOwningServer* aFinder)
    {
    if (!iNotifierNames)
        {
        iNotifierNames = new (ELeave) CNotifierNames;
        }
    iNotifierNames->iFinder = aFinder;    
    }

EXPORT_C void CAknNotifierAppServer::UnbalanceReferenceCountForNotif(TUid aUid, TBool aAddCount)
    {
    if(iNotifierNames && iNotifierNames->iFinder)
        {
        iNotifierNames->iFinder->UnbalanceReferenceCount(aUid, aAddCount); 
        }
    }

// End of file
