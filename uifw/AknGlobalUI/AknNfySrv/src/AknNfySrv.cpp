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
* Description:  AknNfySrv server and session implementation.
*
*/

#include <AknNotifierWrapperDefs.h>
#include <AknNotifierControllerPlugin.h>
#include "AknNfySrv.h"

const TUid KDllUid = {0x10000079};

    
class CAknNotifierEntry: public CBase
    {
public:   
    CAknNotifierEntry():iNotifier(0),iLibraryName(0){}
    ~CAknNotifierEntry(){if (iNotifier) iNotifier->Release();}
    MEikSrvNotifierBase2* iNotifier;
    HBufC* iLibraryName; // Not owned
    };
    
class CAknNotifLibraryEntry: public CBase
    {
public:   
    CAknNotifLibraryEntry(HBufC* aName):iReferenceCount(1), iLibraryName(aName){}
    ~CAknNotifLibraryEntry()
        {
        delete iLibraryName;
        iLibrary.Close();
        }
    TInt Load()
        {
        return iLibrary.Load( 
            *iLibraryName,
            _L("z:\\sys\\bin\\"),
            TUidType(KDllUid, KUidNotifierPlugInV2, KNullUid));
        }
    TInt iReferenceCount;
    HBufC* iLibraryName;
    RLibrary iLibrary;
    TInt iNestingLevel;
    };   
    
// local functions
TBool CheckUnusedLibraries(TAny* aThis)
    {
    CAknNfySrv* me = (CAknNfySrv*)aThis;
    TBool foundPending(EFalse); 
    for (TInt ii = me->iLibraryArray.Count()-1; ii >= 0; ii-- )
        {
        if (me->iLibraryArray[ii]->iReferenceCount == 0)
            {
            if (me->iLibraryArray[ii]->iNestingLevel >= CActiveScheduler::Current()->StackDepth())
                {
                me->DoUnload(me->iLibraryArray[ii]->iLibraryName->Des());
                }
            else
                {
                foundPending = ETrue;
                }   
            }
        }
    return foundPending; 
    }

void  CAknNfySrvSession::HandleMessageL(const RMessage2& aMessage)
    {
    TInt command = aMessage.Function();
    
    if ( command == EStartNotifier || command == EStartNotifierAndGetResponse 
        || command == EAknNfySrvLoadLibrary)
        {
        TInt libNameLength = aMessage.GetDesLength(3);
        if (libNameLength > 0)
            {
            HBufC* libName = HBufC::NewLC(libNameLength);
            TPtr ptr = libName->Des();
            aMessage.ReadL(3, ptr); 
            CleanupStack::Pop(); // ownership to server
            iServer->LoadLibraryL(libName);
            }
        }
        
    // Check pending removals before passing execution to plugin (as it may create new nesting 
    // levels).
    iServer->CheckPendingRemovalsL();
    
    if (command == EAknNfySrvLoadLibrary)
        {
        aMessage.Complete(KErrNone);
        }
    else
        {
        CAknNotifierServerAppService::HandleMessageL(aMessage);    
        }
    }

void CAknNfySrv::CheckPendingRemovalsL()
    {
    if (!iLibraryRemover)
        {
        iLibraryRemover = CIdle::NewL(CActive::EPriorityIdle); // there is no hurry
        }
    else if (iLibraryRemover->IsActive())
        {
        if (CheckUnusedLibraries((TAny*) this))
            {
            iLibraryRemover->Cancel();
            }
        }
    }

void CAknNfySrv::CancelNotifier(TUid aNotifierUid)
    {
    MEikSrvNotifierBase2* impl = FindImplementation(aNotifierUid);  
    if (impl)
        {
        // Just in case notifier likes to null the information on cancel.
        TUid uid = impl->Info().iUid; 
        
        impl->Cancel();    
        UnloadLibrary(uid);
        }
    }
    
void CAknNfySrv::StartNotifierAndGetResponseL(TUid aNotifierUid, TDesC8& aBuffer, 
    const RMessagePtr2& aMsg, TInt aReplySlot)
    {
    MEikSrvNotifierBase2* impl = FindImplementation(aNotifierUid);  
    if (!impl)
        {
        UnloadLibrary(aNotifierUid);
        }
    User::LeaveIfNull(impl);    
    impl->StartL(aBuffer, aReplySlot, aMsg);
    }
    
void CAknNfySrv::StartNotifierL(TUid aNotifierUid, const TDesC8& aBuffer, TDes8& aResponse)
    {
    MEikSrvNotifierBase2* impl = FindImplementation(aNotifierUid);  
    if (!impl)
        {
        UnloadLibrary(aNotifierUid);
        }
        
    User::LeaveIfNull(impl);    
    aResponse.Copy(impl->StartL(aBuffer));
    }
        
CApaAppServiceBase* CAknNfySrv::CreateServiceL(TUid aServiceType) const
    {
    if ( aServiceType == KAknNotifierServiceUid )
        {
        return new (ELeave) CAknNfySrvSession(this);
        }
    else 
        {
        return CAknNotifierAppServer::CreateServiceL(aServiceType); 
        }   
    }

void CAknNfySrv::LoadLibraryL(HBufC* aLibName) 
    {
    CleanupStack::PushL(aLibName);
    if (!CheckReferenceCount(aLibName->Des(), ETrue))
        {
        CAknNotifLibraryEntry* newLib = new (ELeave) CAknNotifLibraryEntry(aLibName);
        newLib->iNestingLevel = CActiveScheduler::Current()->StackDepth();
        CleanupStack::Pop(); // aLibName
        CleanupStack::PushL(newLib);
        User::LeaveIfError(newLib->Load());
        AddNotifiersFromLibL(newLib);
        iLibraryArray.AppendL(newLib);
        CleanupStack::Pop(); // newLib
        }
    else
        {
        CleanupStack::PopAndDestroy(); // aLibName
        }
    }

LOCAL_C void DeleteTempMArray(TAny* aPtr)
    {
    CArrayPtr<MEikSrvNotifierBase2>* const array = 
        reinterpret_cast<CArrayPtr<MEikSrvNotifierBase2>*>(aPtr);
        
    for (TInt i = array->Count()-1; i >= 0; i--)
        {
        array->At(i)->Release(); // effectively delete 
        }

    delete array;
    }   
    
// To make polymorphic binding bit more readable.
typedef CArrayPtr<MEikSrvNotifierBase2>* (*CreateEikSrvNotifierBase)();     

void CAknNfySrv::AddNotifiersFromLibL(CAknNotifLibraryEntry* aNewLib)
    {
    CreateEikSrvNotifierBase libEntry =
        (CreateEikSrvNotifierBase)(aNewLib->iLibrary.Lookup(1)); // fetch fptr   
        
    CArrayPtr<MEikSrvNotifierBase2>* array = 
        reinterpret_cast<CArrayPtr<MEikSrvNotifierBase2>*>((libEntry)()); // and execute it
        
    User::LeaveIfNull(array);       
    CleanupStack::PushL(TCleanupItem(DeleteTempMArray,array));
    const TInt count = array->Count();
    for (TInt j = count-1; j >= 0 ; j--)
        {
        CAknNotifierEntry* newEntry = new (ELeave) CAknNotifierEntry();
        newEntry->iNotifier = array->At(j);
        newEntry->iLibraryName = aNewLib->iLibraryName;
        CleanupStack::PushL(newEntry);
        newEntry->iNotifier->RegisterL();
        
        User::LeaveIfError(iNotifierArray.Append(newEntry));
        
        CleanupStack::Pop(newEntry);
        
        array->At(j)=0;
        array->Delete(j);
        }
            
    CleanupStack::PopAndDestroy(array);     
    }

CAknNotifierEntry* CAknNfySrv::FindEntry(TUid aUid) const
    {
    for (TInt i = 0; i < iNotifierArray.Count(); i++)
        {
        if (iNotifierArray[i]->iNotifier->Info().iUid == aUid)
            {
            return iNotifierArray[i];   
            }
        }
    return 0;
    }

MEikSrvNotifierBase2* CAknNfySrv::FindImplementation(TUid aUid) const
    {
    CAknNotifierEntry* entry = FindEntry(aUid);
    if (entry)
        {
        return entry->iNotifier;
        }
        
    return 0;
    }

TBool CAknNfySrv::CheckReferenceCount(const TDesC& aLibName, TBool aIncrease)
    {
    TBool ret = EFalse;
    for (TInt i = iLibraryArray.Count()-1; i >= 0; i--)
        {
        if (iLibraryArray[i]->iLibraryName->CompareF(aLibName) == 0)
            {
            if (aIncrease)
                {
                iLibraryArray[i]->iReferenceCount++;
                // modify nesting level only if it decreases
                if (iLibraryArray[i]->iNestingLevel > CActiveScheduler::Current()->StackDepth())
                    {
                    iLibraryArray[i]->iNestingLevel = CActiveScheduler::Current()->StackDepth();
                    }
                ret = ETrue; 
                }
            else
                {
                if (--iLibraryArray[i]->iReferenceCount == 0)
                    {
                    if (iLibraryArray[i]->iNestingLevel == CActiveScheduler::Current()->StackDepth())
                        {
                        // Return true if this was last reference and nesting level is same as 
                        // when created.
                        ret = ETrue; 
                        }
                    else
                        {                            
                        if (!iLibraryRemover->IsActive())
                            {
                            iLibraryRemover->Start(TCallBack(CheckUnusedLibraries, this));
                            }
                        }
                    }
                }    
            break;               
            }
        }
#ifdef _DEBUG
    RDebug::Print(_L("CAknNfySrv::CheckReferenceCount(%S, %d), ret %d"), &aLibName, aIncrease, ret);    
#endif
    return ret;
    }

void CAknNfySrv::UnloadLibrary(TUid aNotifierUid)
    {
    __ASSERT_ALWAYS(iLibraryArray.Count(), User::Invariant());
    
    // default to last added name
    TPtrC libName = iLibraryArray[iLibraryArray.Count()-1]->iLibraryName->Des(); 

    CAknNotifierEntry* entry = FindEntry(aNotifierUid);
    if (entry)
        {
        libName.Set(entry->iLibraryName->Des());
        }
    
    // RPointerArray could probably provide something better than linear search,
    // anyway the amount of notifiers should be considerably small so applying KISS paradigm here.
    if (CheckReferenceCount(libName, EFalse))
        {
        DoUnload(libName);
        } 
    }

void CAknNfySrv::DoUnload(const TDesC& aLibName)
    {
    for (TInt i = iNotifierArray.Count()-1; i >= 0; i--)
        {
        // Release notifiers from lib (reverse order to handle possible dependencies).
        if (iNotifierArray[i]->iLibraryName->CompareF(aLibName) == 0)
            {
            delete iNotifierArray[i];
            iNotifierArray.Remove(i);
#ifdef _DEBUG
            RDebug::Print(_L("Deleted notifier from library %S"), &aLibName);    
#endif
            }
        }
            
    for (TInt i = iLibraryArray.Count()-1; i >= 0; i--)
        {
        if (iLibraryArray[i]->iLibraryName->CompareF(aLibName) == 0)
            {
            delete iLibraryArray[i];
            iLibraryArray.Remove(i);
#ifdef _DEBUG
            RDebug::Print(_L("Deleted library"));    
#endif
            break;
            }
        }        
        
    User::Heap().Compress();
#ifdef _DEBUG
    RDebug::Print(_L("Heap compressed"));    
#endif
    }


CAknNfySrv::~CAknNfySrv()
    {
    delete iLibraryRemover;
    for (TInt i = iNotifierArray.Count()-1; i >= 0; i--)
        {
        delete iNotifierArray[i];
        }
    iNotifierArray.Close();             
    for (TInt i = iLibraryArray.Count()-1; i >= 0; i--)
        {
        delete iLibraryArray[i];
        }
    iLibraryArray.Close();
    }

void CAknNfySrv::HandleClientExit(CAknNfySrvSession* /*aSession*/)
    {
    }

void CAknNfySrv::UnbalanceReferenceCount(TUid aUid, TBool aAddCount)
    {
    CAknNotifierEntry* entry = CAknNfySrv::FindEntry(aUid);
    if (entry)
        {
        CheckReferenceCount(*entry->iLibraryName, aAddCount);
        if (!aAddCount)
            {
            // In order to free memory, we may need to allocate memory.
            TRAP_IGNORE(CheckPendingRemovalsL()); 
            }
        }
    }
    
// future proofing    
void CAknNfySrv::NotifierExtension(TUid /*aExtensionUid*/, TAny*& /*aGenParam*/)
    {    
    }
    
// End of file
