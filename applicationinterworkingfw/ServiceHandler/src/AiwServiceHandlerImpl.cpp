/*
* Copyright (c) 2003-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Implements API for consumer application to access Application
*                Interworking Framework. 
*
*/




#include <eikenv.h>
#include <aiwservicehandler.rsg>
#include <eikon.hrh>
#include "AiwMenuBinding.h"
#include "AiwServiceHandlerImpl.h"
#include "AiwMenu.h"
#include "AiwUids.hrh"
#include "AiwCommon.hrh"
#include "AiwMenuSlot.hrh"
#include "AiwEcomMonitor.h"
#include "AiwTlsData.h"
#include "data_caging_path_literals.hrh"

// CONSTANTS
// Max number of empty menu resource slots.
const TInt KMaxMenuResources = 16;

// This value tells how many times consumer can call InitializeMenuPaneL() without 
// closing the Options-menu.
const TInt KMaxPaneIds = KMaxMenuResources;

// The range reserved for individual menu pane.
const TInt KIndividualMenuPaneIdRange = 10000;

// The whole range that is reserved to all menu panes. Currently value is 170 000.
const TInt KMenuPaneCommandRange = (KMaxMenuResources + 1) * KIndividualMenuPaneIdRange; 

_LIT(KAiwResourceFile, "AiwServiceHandler.rSC");
_LIT(KAiwZDrive, "z:");

const TInt KMaxMenuTitleSize = 100;

// Command id space reserved for single placeholder.
const TInt KPlaceholderCmdIdRange = 200;

void Cleanup(TAny* aAny);
void InterestCleanup(TAny* aAny);
void IntArrayCleanup(TAny* aAny);
void FilteredCleanup(TAny* aAny);


//
// AiwServiceHandler
//

CAiwServiceHandlerImpl* CAiwServiceHandlerImpl::NewL()
    {
    CAiwServiceHandlerImpl* handler = new (ELeave) CAiwServiceHandlerImpl();
    CleanupStack::PushL( handler );
    handler->ConstructL();
    CleanupStack::Pop(); // handler
    return handler;
    }



CAiwServiceHandlerImpl::CAiwServiceHandlerImpl()
    {
    // Nothing to do here.
    }



void CAiwServiceHandlerImpl::ConstructL()
    {
    TFileName resFile;

    TCallBack callBack(SynchronizeCallBack, this);
    iEcomMonitor = CAiwEcomMonitor::NewL(callBack);

    resFile.Copy(KAiwZDrive);
    resFile.Append(KDC_RESOURCE_FILES_DIR);
    resFile.Append(KAiwResourceFile);

    iCoeEnv = CCoeEnv::Static();
    
    // A Service Handler instance can be created also when CCoeEnv is not 
    // available (e.g. from server applications). In this case, the methods 
    // needing CCoeEnv/CEikonEnv will leave with KErrNotSupported.
    if(iCoeEnv)
        {
        iResourceOffset = iCoeEnv->AddResourceFileL(resFile);
        }

    // CAiwTlsData has a reference count so each OpenL call
    // must have a matching Close call (done in destructor).
    // OpenL is called only here, the TLS data object can be
    // referenced by calling CAiwTlsData::Instance().
    CAiwTlsData* data = CAiwTlsData::OpenL();
    iTlsDataOpened = ETrue;

    // CEikMenuPane informs all menu launch observers
    // when an options menu is launched.
    data->AddMenuLaunchObserverL( this );
    }



CAiwServiceHandlerImpl::~CAiwServiceHandlerImpl()
    {
    if (iResourceOffset && iCoeEnv)
        {
        iCoeEnv->DeleteResourceFile(iResourceOffset);
        }
    Reset();

    delete iEcomMonitor;

    if ( iTlsDataOpened )
        {
        CAiwTlsData* data = CAiwTlsData::Instance();
        data->RemoveMenuLaunchObserver( this );
        CAiwTlsData::Close();
        }
    }



void CAiwServiceHandlerImpl::Reset()
    {
    iInterestList.ResetAndDestroy();
    iMenuBindings.ResetAndDestroy();
    iBaseBindings.ResetAndDestroy();
    iProviders.ResetAndDestroy();

    iLastInitialized.Reset();

    iMenuPanes.ResetAndDestroy();

    delete iInParams;
    iInParams = NULL;
    delete iOutParams;
    iOutParams = NULL;
    }



void CAiwServiceHandlerImpl::ListProvidersForCriteriaL(RArray<TInt>& aResult, 
    CAiwCriteriaItem& aItem)
    {
    TInt i;

    for (i = 0; i < iProviders.Count(); i++)
        {   
        if (iProviders[i]->HasCriteria(aItem))
            {
            User::LeaveIfError(aResult.Append(iProviders[i]->ImplementationUid().iUid));
            }
        }
    }



TInt CAiwServiceHandlerImpl::NbrOfProviders(const CAiwCriteriaItem* aCriteria)
    {
    if(!aCriteria)
        {
        return 0;
        }
    
    TInt i, j;

    for (i = 0; i < iBaseBindings.Count(); i++)
        {
        for (j = 0; j < iBaseBindings[i]->Interest().Count(); j++)
            {
            if ((*iBaseBindings[i]->Interest()[j]) == (*aCriteria))
                {
                return iBaseBindings[i]->NumberOfProviders();
                }
            }
        }

    for (i = 0; i < iMenuBindings.Count(); i++)
        {
        for (j = 0; j < iMenuBindings[i]->Interest().Count(); j++)
            {
            if ((*iMenuBindings[i]->Interest()[j]) == (*aCriteria))
                {
                return iMenuBindings[i]->NumberOfProviders();
                }
            }       
        }

    return 0;
    }



void CAiwServiceHandlerImpl::AttachL(TInt aInterestResourceId)
    {
    // CCoeEnv/CEikonEnv needs to be accessible.
    if(!iCoeEnv)
        {
        User::Leave(KErrNotSupported);
        }
    
    RCriteriaArray interest, filtered;

    CleanupStack::PushL( TCleanupItem( InterestCleanup, &interest ) );
    CleanupStack::PushL( TCleanupItem( FilteredCleanup, &filtered ) );

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, aInterestResourceId);
    ReadInterestListL(reader, interest);
    CleanupStack::PopAndDestroy(); // reader

    FilterInterestListL(interest, filtered);
    
    DoAttachL(filtered);

    filtered.Reset();

    CleanupStack::Pop(); // filtered
    CleanupStack::Pop(); // interest
    }



void CAiwServiceHandlerImpl::AttachL(const RCriteriaArray& aInterest)
    {
    RCriteriaArray interest, filtered;
    
    CleanupStack::PushL( TCleanupItem( InterestCleanup, &interest ) );
    CleanupStack::PushL( TCleanupItem( FilteredCleanup, &filtered ) );
        
    for(TInt i = 0; i < aInterest.Count(); i++)
        {
        CAiwCriteriaItem* item = CAiwCriteriaItem::NewLC();
        
        item->SetId(               aInterest[i]->Id()                    );
        item->SetServiceCmd(       aInterest[i]->ServiceCmd()            );
        item->SetContentTypeL(     aInterest[i]->ContentType()           );
        item->SetServiceClass(     aInterest[i]->ServiceClass()          );
        item->SetOptions(          aInterest[i]->Options()               );
        item->SetDefaultProvider( (aInterest[i]->DefaultProvider()).iUid );
        item->SetMaxProviders(     aInterest[i]->MaxProviders()          );       
        
        User::LeaveIfError(interest.Append(item));
        CleanupStack::Pop(item); 
        }
        
    FilterInterestListL(interest, filtered);        

    DoAttachL(filtered);

    filtered.Reset();

    CleanupStack::Pop(); // filtered
    CleanupStack::Pop(); // interest
    }



void CAiwServiceHandlerImpl::DoAttachL(const RCriteriaArray& aInterest)
    {
    CAiwBinding* bind;
    for (TInt i = 0; i < aInterest.Count(); i++)
        {
        bind = CAiwBinding::NewLC();
        
        if (ResolveProvidersL(bind, aInterest[i]))
            {
            User::LeaveIfError(iBaseBindings.Append( bind ));
            CleanupStack::Pop(); // bind
            bind->AddCriteriaL(aInterest[i]);

            // Initialise providers.
            for (TInt k = 0; k < bind->NumberOfProviders(); k++)
                {
                // Trap the initialisation. If not done, a leaving provider
                // could prevent the initialisation of other providers.
                TRAPD(err, bind->BaseProvider(k)->InitialiseL(*this, bind->Interest()));
                if(err)
                    {
#ifdef _DEBUG                    
                    RDebug::Print(_L("AIW PROVIDER ERROR: CAiwServiceIfBase::InitialiseL() failed, leave code:%d"), err);
#endif                    
                    }
                }
            }
        else
            {
            CleanupStack::PopAndDestroy(); // bind
            }
        }
    }


void CAiwServiceHandlerImpl::GetInterest(RCriteriaArray& aInterest)
    {
    for (TInt i = 0; i < iInterestList.Count(); i++)
        {
        if (aInterest.Append(iInterestList[i]) != KErrNone)
            {
            return;
            }
        }
    }
    
    

void CAiwServiceHandlerImpl::DetachL(const RCriteriaArray& aInterest)
    {
    // First, remove relevant criteria items from relevat base bindings.
    for (TInt i = 0; i < aInterest.Count(); i++)
        {
        for (TInt j = 0; j < iBaseBindings.Count(); j++)
            {
            TInt index = iBaseBindings[j]->HasCriteriaItem(*aInterest[i]);
            if (index != KErrNotFound)
                {
                iBaseBindings[j]->RemoveCriteria(index);
                }                           
            }
        }

    // Second pass removes empty bindings.
    for (TInt i = 0; i < iBaseBindings.Count(); i++)
        {
        if (iBaseBindings[i]->Interest().Count() == 0)
            {
            delete iBaseBindings[i];
            iBaseBindings.Remove(i);
            i--;
            }
        }

    // Then check if there were left obselete criteria items and remove them.   
    RemoveObsoleteCriteriaItems();
    
    // Finally check if there were left obselete providers and remove them.
    RemoveObsoleteProviders();        
    }



void CAiwServiceHandlerImpl::DetachL(TInt aInterestResourceId)
    { 
    // CCoeEnv/CEikonEnv needs to be accessible.
    if(!iCoeEnv)
        {
        User::Leave(KErrNotSupported);
        }
    
    RCriteriaArray interest;

    CleanupStack::PushL( TCleanupItem( InterestCleanup, &interest ) );

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, aInterestResourceId);
    ReadInterestListL(reader, interest);
    CleanupStack::PopAndDestroy(); // reader

    DetachL( interest );

    interest.ResetAndDestroy();
    CleanupStack::Pop(); // interest
    }


const CAiwCriteriaItem* CAiwServiceHandlerImpl::GetCriteria(TInt aId)
    {
    for (TInt i = 0; i < iInterestList.Count(); i++)
        {
        if (iInterestList[i]->Id() == aId)
            {
            return iInterestList[i];
            }
        }

    return NULL;  
    }
    
TInt CAiwServiceHandlerImpl::NumAlreadyInitializedPaneIdsL() const
    {
    TInt ret = 0;
    TInt paneIds[KMaxPaneIds] = {0};
    TBool found = EFalse;
    
    for (TInt i = 0; i < iLastInitialized.Count(); i++)
        {
        found = EFalse;
        
        for (TInt j = 0; j < ret; j++)
            {
            if (iLastInitialized[i]->MenuResourceId() == paneIds[j])
                {
                found = ETrue;
                break;              
                }
            }
                
        if (!found) 
            {
            // Create new item.
            if (ret >= KMaxPaneIds)
                {
#ifdef _DEBUG
                RDebug::Print(_L("ERROR: OVERFLOW in CAiwServiceHandlerImpl::NumAlreadyInitializedPaneIdsL()"));
#endif
                User::Leave(KErrOverflow);
                }
            paneIds[ret] = iLastInitialized[i]->MenuResourceId();
            ret++;
            }                       
        }
    return ret;         
    }    

void CAiwServiceHandlerImpl::InitializeMenuPaneL(
    CEikMenuPane& aMenuPane,
    TInt aMenuResourceId, 
    TInt aBaseMenuCmdId,
    const CAiwGenericParamList& aInParamList)
    {
    InitializeMenuPaneL(aMenuPane, aMenuResourceId, aBaseMenuCmdId, 
        aInParamList, EFalse, EFalse);    
    }        
        
void CAiwServiceHandlerImpl::InitializeMenuPaneL(
    CEikMenuPane& aMenuPane,
    TInt aMenuResourceId, 
    TInt aBaseMenuCmdId,
    const CAiwGenericParamList& aInParamList,
    TBool aUseSubmenuTextsIfAvailable)
    {
    InitializeMenuPaneL(aMenuPane, aMenuResourceId, aBaseMenuCmdId, aInParamList, aUseSubmenuTextsIfAvailable, EFalse);
    }


void CAiwServiceHandlerImpl::InitializeMenuPaneL(
    CEikMenuPane& aMenuPane,
    TInt aMenuResourceId, 
    TInt aBaseMenuCmdId,
    const CAiwGenericParamList& aInParamList,
    TBool aUseSubmenuTextsIfAvailable,
    TBool aSetAsItemSpecific)
    {        
    // CCoeEnv/CEikonEnv needs to be accessible.
    if(!iCoeEnv)
        {
        User::Leave(KErrNotSupported);
        }
    
    if (!iMenuBindings.Count())
        {
        // Either no menu is attached to interest or menu was attached but
        // it didn't contain any placeholders for criteria items. So
        // nothing to do, get out.
        return;
        }

    TInt index;
    TInt slotcmd;
    TBuf <KMaxMenuTitleSize> subTitle;
    TBool titleLocked;
    TInt paneOffset = NumAlreadyInitializedPaneIdsL() * KIndividualMenuPaneIdRange;

    iSubmenuCmd = aBaseMenuCmdId + KMenuPaneCommandRange;
    slotcmd = SlotItemCmd(aMenuPane);
    if (slotcmd >= 0)
        {
        // aMenuPane is aiw submenu. At this point it is empty and we must
        // copy provider menu items to it.
        CAiwMenuPane* aiwPane = MenuPaneForSlotCmd(slotcmd);
        if (aiwPane)
            {
            CopyMenuItemsL(aiwPane, aMenuPane, 0, ETrue, aSetAsItemSpecific);
            aMenuPane.DeleteMenuItem(slotcmd);
            iSubmenu = aiwPane;
            }
        }
    else
        {
        iSubmenu = NULL;
        
        const TInt bindcount = iMenuBindings.Count();
        for (TInt i = 0; i < bindcount; i++)
            {
            if  ((iMenuBindings[i]->MenuId() == aMenuResourceId) &&
                (aMenuPane.MenuItemExists(iMenuBindings[i]->MenuCmd(), index)))
                {
                CAiwMenuPane* aiwPane = iMenuBindings[i]->MenuPane();
                TInt menuResourceId = -1;
                if(aiwPane)
                    {
                    // An AIW menu pane already exists (this means that a normal
                    // non-AIW submenu with AIW items has been opened more than once). 
                    // In this case we use the existing resource slot id.
                    menuResourceId = aiwPane->ResourceSlotId();
                    paneOffset = aiwPane->PaneOffset();
                    DeleteAiwMenuPane(aiwPane);
                    aiwPane = NULL;
                    }
                aiwPane = CreateEmptyAiwMenuPaneL(aBaseMenuCmdId, menuResourceId);
                CleanupStack::PushL(aiwPane);
                aiwPane->SetPaneOffset(paneOffset);
                paneOffset += KPlaceholderCmdIdRange;
                iMenuBindings[i]->SetMenuPane(aiwPane);     

                // Clean previous service commands from list.
                CAiwGenericParamList& list = const_cast<CAiwGenericParamList&>(aInParamList);
                while (list.Remove(EGenericParamServiceCommand)) 
                    {
                    // Intentionally left empty.    
                    }

                // Add service commands for current placeholder.
                const TInt icount = iMenuBindings[i]->Interest().Count();
                for (TInt k = 0; k < icount; k++)
                    {
                    list.AppendL(TAiwGenericParam(EGenericParamServiceCommand,
                        TAiwVariant(iMenuBindings[i]->Interest()[k]->ServiceCmd())));
                    }

                // Loop from last entry to first entry always inserting to same index.
                // Default provider is the first item in list, so if there is a default
                // provider defined, it will be the first one to appear in menus.               
                for (TInt j = iMenuBindings[i]->NumberOfProviders() - 1; j >= 0; j--)
                    {
                    aiwPane->SetInitializingOwner(iMenuBindings[i]->MenuProvider(j));
                    iMenuBindings[i]->MenuProvider(j)->InitializeMenuPaneHookL(aiwPane,
                        0, 0, aInParamList);
                    }

                GetSubmenuTitle(aiwPane->MenuPane(), subTitle);
            
                TAiwPlaceholderType phtype = PlaceholderType(aMenuPane, 
                    iMenuBindings[i]->MenuCmd(), titleLocked);

                if ((phtype == EAiwPlaceholderCascade) ||
                    (phtype == EAiwPlaceholderIntelligentCascade))
                    {
                    if (aiwPane->MenuPane().NumberOfItemsInPane() == 1)
                        {
                        // Remove placeholder item.
                        aMenuPane.DeleteMenuItem(iMenuBindings[i]->MenuCmd());
                        CleanupStack::PopAndDestroy(); // aiwPane
                        continue;
                        }
                    else if ((aiwPane->MenuPane().NumberOfItemsInPane() == 2) &&
                        (phtype == EAiwPlaceholderIntelligentCascade))
                        {
                        UnCascadeL(aMenuPane, iMenuBindings[i]->MenuCmd(), *aiwPane, aSetAsItemSpecific);
                        User::LeaveIfError(iLastInitialized.Append(aiwPane));
                        }
                    else
                        {
                        if (titleLocked)
                            {
                            subTitle.Zero();
                            }
                        ConvertPlaceholderL(aMenuPane, iMenuBindings[i]->MenuCmd(), *aiwPane, 
                            subTitle, aSetAsItemSpecific);
                        }       
                    }
                else
                    {
                    // Remove placeholder item.
                    aMenuPane.DeleteMenuItem(iMenuBindings[i]->MenuCmd());
        
                    // Copy menu items to actual menu pane
                    CopyMenuItemsL(aiwPane, aMenuPane, index, aUseSubmenuTextsIfAvailable, aSetAsItemSpecific);
                    
                    User::LeaveIfError(iLastInitialized.Append(aiwPane));
                    }
                aiwPane->SetMenuResourceId(aMenuResourceId);
                User::LeaveIfError(iMenuPanes.Append(aiwPane));
                CleanupStack::Pop(); // aiwPane
                }
            }
        }
    }


TInt CAiwServiceHandlerImpl::ServiceCmdByMenuCmd(TInt aMenuCmdId) const
    {
    for (TInt i = 0; i < iMenuBindings.Count(); i++)
        {
        if ((IsInLastInitialized(iMenuBindings[i]->MenuPane())) &&
            (iMenuBindings[i]->MenuPane()->IsCmdInRange(KPlaceholderCmdIdRange, aMenuCmdId)))
            {
            return iMenuBindings[i]->MenuPane()->ServiceCmdId(aMenuCmdId); 
            }
        }

    return 0;   
    }



void CAiwServiceHandlerImpl::ExecuteMenuCmdL(
    TInt aMenuCmdId,
    const CAiwGenericParamList& aInParamList,
    CAiwGenericParamList& aOutParamList,
    TUint aCmdOptions,
    MAiwNotifyCallback* aCallback)
    {
    // CCoeEnv/CEikonEnv needs to be accessible.
    if(!iCoeEnv)
        {
        User::Leave(KErrNotSupported);
        }
    
    if (!iMenuBindings.Count())
        {
        return;
        }   

    // Handle real menu providers.
    for (TInt i = 0; i < iMenuBindings.Count(); i++)
        {
        CAiwMenuPane* menuPane = iMenuBindings[i]->MenuPane();

        if (IsInLastInitialized(menuPane))
            {
            for (TInt j = 0; j < iMenuBindings[i]->NumberOfProviders(); j++)
                {
                if ((menuPane->IsCmdInRange(KPlaceholderCmdIdRange, aMenuCmdId)) && 
                    (menuPane->CommandOwner(aMenuCmdId) == iMenuBindings[i]->MenuProvider(j)))
                    {
                    iMenuBindings[i]->MenuProvider(j)->HandleMenuCmdHookL(
                        menuPane, 
                        aMenuCmdId, 
                        aInParamList, 
                        aOutParamList, 
                        aCmdOptions, 
                        aCallback); 
                    return;
                    }
                }
            }
        }
    }



void CAiwServiceHandlerImpl::AttachMenuL(TInt aMenuResourceId, TInt aInterestResourceId)
    {
    // CCoeEnv/CEikonEnv needs to be accessible.
    if(!iCoeEnv)
        {
        User::Leave(KErrNotSupported);
        }
    
    RCriteriaArray interest, filtered;
    TResourceReader reader;

    CleanupStack::PushL( TCleanupItem( InterestCleanup, &interest ) );
    CleanupStack::PushL( TCleanupItem( FilteredCleanup, &filtered ) );
    iCoeEnv->CreateResourceReaderLC(reader, aInterestResourceId);
    ReadInterestListL(reader, interest);
    CleanupStack::PopAndDestroy(); // reader
    FilterInterestListL(interest, filtered);

    iCoeEnv->CreateResourceReaderLC(reader, aMenuResourceId);
    DoAttachMenuL(reader, aMenuResourceId, filtered);
    filtered.Reset();
    CleanupStack::PopAndDestroy(); // reader
    CleanupStack::Pop(); // filtered
    CleanupStack::Pop(); // interest
    }



void CAiwServiceHandlerImpl::AttachMenuL(TInt aMenuResourceId, TResourceReader& aReader)
    {
    // CCoeEnv/CEikonEnv needs to be accessible.
    if(!iCoeEnv)
        {
        User::Leave(KErrNotSupported);
        }
    
    RCriteriaArray interest, filtered;
    TResourceReader reader;

    CleanupStack::PushL( TCleanupItem( InterestCleanup, &interest ) );
    CleanupStack::PushL( TCleanupItem( FilteredCleanup, &filtered ) );
    ReadInterestListL(aReader, interest);
    FilterInterestListL(interest, filtered);

    iCoeEnv->CreateResourceReaderLC(reader, aMenuResourceId);
    DoAttachMenuL(reader, aMenuResourceId, filtered);
    filtered.Reset();
    CleanupStack::PopAndDestroy(); // reader
    CleanupStack::Pop(); // filtered
    CleanupStack::Pop(); // interest
    }


void CAiwServiceHandlerImpl::AttachMenuL(TInt aMenuResourceId, const RCriteriaArray& aInterest)
    {
    // CCoeEnv/CEikonEnv needs to be accessible.
    if(!iCoeEnv)
        {
        User::Leave(KErrNotSupported);
        }    
    
    RCriteriaArray interest, filtered;
    TResourceReader reader;
    
    CleanupStack::PushL( TCleanupItem( InterestCleanup, &interest ) );
    CleanupStack::PushL( TCleanupItem( FilteredCleanup, &filtered ) );
        
    for(TInt i = 0; i < aInterest.Count(); i++)
        {
        CAiwCriteriaItem* item = CAiwCriteriaItem::NewLC();
        
        item->SetId(               aInterest[i]->Id()                    );
        item->SetServiceCmd(       aInterest[i]->ServiceCmd()            );
        item->SetContentTypeL(     aInterest[i]->ContentType()           );
        item->SetServiceClass(     aInterest[i]->ServiceClass()          );
        item->SetOptions(          aInterest[i]->Options()               );
        item->SetDefaultProvider( (aInterest[i]->DefaultProvider()).iUid );
        item->SetMaxProviders(     aInterest[i]->MaxProviders()          );       
        
        User::LeaveIfError(interest.Append(item));
        CleanupStack::Pop(item); 
        }
        
    FilterInterestListL(interest, filtered);        

    iCoeEnv->CreateResourceReaderLC(reader, aMenuResourceId);
    DoAttachMenuL(reader, aMenuResourceId, filtered);
    filtered.Reset();
    CleanupStack::PopAndDestroy(); // reader
    CleanupStack::Pop(); // filtered
    CleanupStack::Pop(); // interest    
    }   


void CAiwServiceHandlerImpl::DoAttachMenuL(TResourceReader& aReader, TInt aMenuId, 
    RCriteriaArray& aInterest)
    {
    TInt menuCmd;
    TInt count = aReader.ReadInt16();
    TBool bound;

    for (TInt i = 0; i < count; i++)
        {
        menuCmd = aReader.ReadInt32();
        CAiwMenuBinding* bind = NULL;
        bound = EFalse;

        for (TInt j = 0; j < aInterest.Count(); j++)
            {           
            if (aInterest[j]->Id() == menuCmd)
                {                       
                if (!bind)
                    {
                    bind = AlreadyBound(aMenuId, menuCmd, i);
                    if (!bind)
                        {
                        bind = CAiwMenuBinding::NewLC(i, aMenuId);
                        bind->SetMenuCmd( menuCmd );
                        }
                    else
                        {
                        bound = ETrue;
                        }
                    }
                
                if (bind->HasCriteriaItem(*(aInterest[j])) == KErrNotFound)
                    {
                    ResolveProvidersL(bind, aInterest[j]);
                    bind->AddCriteriaL(aInterest[j]);
                    }
                }
            }

        // Initialise providers.
        if (bind)
            {
            for (TInt k = 0; k < bind->NumberOfProviders(); k++)
                {
                TRAPD(err, bind->MenuProvider(k)->InitialiseL(*this, bind->Interest()));
                if(err)
                    {
#ifdef _DEBUG
                    RDebug::Print(_L("AIW PROVIDER ERROR: CAiwServiceIfMenu::InitialiseL() failed, leave code:%d"), err);
#endif                     
                    // The provider failed to initialise.
                    // Remove the failed provider from this menu binding.
                    CAiwServiceIfMenu* provider = bind->MenuProvider(k);
                    TInt implUid = provider->ImplementationUid().iUid;
                    bind->RemoveProvider(implUid);
                    
                    // Remove the failed provider also from other menu bindings.
                    for (TInt m = 0; m < iMenuBindings.Count(); m++)
                        {
                        iMenuBindings[m]->RemoveProvider(implUid);
                        }

                    // Then remove provider from the owner list and delete it.
                    for (TInt m = 0; m < iProviders.Count(); m++)
                        {
                        if (iProviders[m]->ImplementationUid().iUid == implUid)
                            {
                            delete iProviders[m];
                            iProviders.Remove(m);
                            m--;
                            }
                        }                    
                    }
                }
            if (!bound)
                {
                User::LeaveIfError(iMenuBindings.Append( bind ));
                CleanupStack::Pop();  // bind                       
                }
            }
        SkipMenuFields(aReader);  // Jump to next menu item
        }
    }


void CAiwServiceHandlerImpl::ReadInterestL(RCriteriaArray& aInterest, TInt aInterestResourceId)
    {
    CleanupStack::PushL( TCleanupItem( InterestCleanup, &aInterest ) );
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, aInterestResourceId);
    ReadInterestListL(reader, aInterest);
    CleanupStack::PopAndDestroy(); // reader
    CleanupStack::Pop(&aInterest);
    }


void CAiwServiceHandlerImpl::DetachMenu(TInt aMenuResourceId, TInt aInterestResourceId)
    {
    // If interest resource id is null, then detach all items in the given menu.
    if (!aInterestResourceId)
        {
        DoDetachMenu(aMenuResourceId);        
        }
    else
        {
        // CCoeEnv/CEikonEnv needs to be accessible.
        if(!iCoeEnv)
            {
            // We cannot leave because this is a non-leaving method.
            return; 
            }    

        RCriteriaArray interest;
        TRAPD(err, ReadInterestL(interest, aInterestResourceId));
        if (err)
            {
            return;
            }
        
        DoDetachMenu(aMenuResourceId, interest);
        
        interest.ResetAndDestroy();
        }
    }
        

void CAiwServiceHandlerImpl::DoDetachMenu(TInt aMenuResourceId)
    {
    // First, delete the relevant menu bindings.
    for (TInt i = 0; i < iMenuBindings.Count(); i++)
        {
        if (iMenuBindings[i]->MenuId() == aMenuResourceId)
            {
            delete iMenuBindings[i];
            iMenuBindings.Remove(i);
            i--;
            }
        }

    // Then check if there were left obselete criteria items and remove them.   
    RemoveObsoleteCriteriaItems();
    
    // Finally check if there were left obselete providers and remove them.
    RemoveObsoleteProviders();  
    }

    
void CAiwServiceHandlerImpl::DoDetachMenu(TInt aMenuResourceId, RCriteriaArray& aInterest)
    {
    // First, remove relevant criteria items from relevant menu bindings.
    for (TInt i = 0; i < iMenuBindings.Count(); i++)
        {
        if (iMenuBindings[i]->MenuId() == aMenuResourceId) 
            {
            for (TInt j = 0; j < aInterest.Count(); j++)
                {
                TInt index = iMenuBindings[i]->HasCriteriaItem(*aInterest[j]);
                if (index != KErrNotFound)
                    {
                    iMenuBindings[i]->RemoveCriteria(index);
                    }
                }
            }
        }

    // Second pass removes empty bindings.
    for (TInt i = 0; i < iMenuBindings.Count(); i++)
        {
        if (iMenuBindings[i]->Interest().Count() == 0)
            {
            delete iMenuBindings[i];
            iMenuBindings.Remove(i);
            i--;
            }
        }
    
    // Then check if there were left obselete criteria items and remove them.   
    RemoveObsoleteCriteriaItems();
    
    // Finally check if there were left obselete providers and remove them.
    RemoveObsoleteProviders();        
    }    
    
    
void CAiwServiceHandlerImpl::RemoveObsoleteCriteriaItems()
    {
    for (TInt i = 0; i < iInterestList.Count(); i++)
        {
        CAiwCriteriaItem* criteria = iInterestList[i];
        TBool found = EFalse;
        
        // Loop through base bindings.
        for (TInt j = 0; j < iBaseBindings.Count(); j++)
            {
            if (iBaseBindings[j]->HasCriteriaItem(*criteria) != KErrNotFound)
                {
                found = ETrue;
                break;
                }
            }

        // If still not found, loop through menu bindings.        
        if (!found)
            {
            for (TInt j = 0; j < iMenuBindings.Count(); j++)
                {
                if (iMenuBindings[j]->HasCriteriaItem(*criteria) != KErrNotFound)
                    {
                    found = ETrue;
                    break;
                    }
                }            
            }
            
        // Criteria item can be deleted if it was not found.            
        if (!found)
            {
            delete iInterestList[i];
            iInterestList.Remove(i);
            i--;
            }
        }    
    }
    
    
void CAiwServiceHandlerImpl::RemoveObsoleteProviders()
    {
    for (TInt i = 0; i < iProviders.Count(); i++)
        {
        CAiwServiceIfBase* provider = iProviders[i];
        TBool found = EFalse;
        
        // Loop through base bindings.
        for (TInt j = 0; j < iBaseBindings.Count(); j++)
            {
            if (iBaseBindings[j]->HasProvider(provider))
                {
                found = ETrue;
                break;
                }
            }

        // If still not found, loop through menu bindings.        
        if (!found)
            {
            for (TInt j = 0; j < iMenuBindings.Count(); j++)
                {
                if (iMenuBindings[j]->HasProvider(provider))
                    {
                    found = ETrue;
                    break;
                    }
                }            
            }
            
        // Criteria item can be deleted if it was not found.            
        if (!found)
            {
            delete iProviders[i];
            iProviders.Remove(i);
            i--;
            }
        }    
    }


TBool CAiwServiceHandlerImpl::IsSubMenuEmpty(TInt aSubMenuId)
    {
    for (TInt i = 0; i < iMenuBindings.Count(); i++)
        {
        if (iMenuBindings[i]->MenuId() == aSubMenuId)
            {
            if (iMenuBindings[i]->NumberOfProviders() > 0)
                {
                return EFalse;
                }

            return ETrue;
            }
        }

    return EFalse;
    }




CAiwMenuBinding* CAiwServiceHandlerImpl::AlreadyBound(TInt aMenuId, TInt aMenuCmd, 
    TInt aMenuItemIndex) const
    {
    for (TInt i = 0; i < iMenuBindings.Count(); i++)
        {
        if ((iMenuBindings[i]->MenuId() == aMenuId) &&
            (iMenuBindings[i]->MenuCmd() == aMenuCmd) &&
            (iMenuBindings[i]->MenuItemIndex() == aMenuItemIndex))
            {
            return iMenuBindings[i];
            }
        }

    return NULL;
    }


void CAiwServiceHandlerImpl::ExecuteServiceCmdL(
    const TInt& aCmdId,
    const CAiwGenericParamList& aInParamList,
    CAiwGenericParamList& aOutParamList,
    TUint aCmdOptions,
    MAiwNotifyCallback* aCallback)
    {
    for (TInt i = 0; i < iBaseBindings.Count(); i++)
        {
        if(iBaseBindings[i]->HasServiceCmd(aCmdId))
            {
            for (TInt j = 0; j < iBaseBindings[i]->NumberOfProviders(); j++)
                {
                iBaseBindings[i]->BaseProvider(j)->HandleServiceCmdL(
                    aCmdId,
                    aInParamList, 
                    aOutParamList, 
                    aCmdOptions, 
                    aCallback);
                }
            }
        }
    }



void CAiwServiceHandlerImpl::ReadInterestListL(TResourceReader& aReader, 
    RPointerArray<CAiwCriteriaItem>& aResult)  
    {
    const TInt count = aReader.ReadInt16();
    for (TInt ii = 0; ii < count; ++ii)
        {
        CAiwCriteriaItem* item = CAiwCriteriaItem::NewLC();
        item->ReadFromResoureL( aReader );
        User::LeaveIfError(aResult.Append(item));
        CleanupStack::Pop(); // item
        }
    }


TInt CAiwServiceHandlerImpl::ResolveProvidersL(CAiwBinding* aBinding, CAiwCriteriaItem* aItem)
    {
    RImplInfoPtrArray infoArray;
    TInt result = 0;

    CleanupStack::PushL( TCleanupItem( Cleanup, &infoArray ) );

    iEcomMonitor->ListImplemetationsL(infoArray, aItem);

    FilterInfoArray(infoArray, aItem);

    // First resolve for providers already in memory.
    TInt i;
    for (i = 0; i < iProviders.Count(); i++)
        {
        if (iProviders[i]->Match(aItem))
            {
            aBinding->AddProviderL((CAiwServiceIfBase*)iProviders[i], 
                iProviders[i]->ImplementationUid() == aItem->DefaultProvider());          
            result++;
            }     
        }

    // If cached providers were found, then it means that all the matching
    // providers must be already in memory. No need to query from ECom framework.
    if (!result)
        {
        for (i = 0; i < infoArray.Count(); i++)
            {
            if ((aItem->Options() & AIW_OPTIONS_ROM_ONLY) && (infoArray[i]->RomBased() == EFalse))
                {
                continue;
                }
    
    		CAiwServiceIfBase* iface = NULL;
    		TRAP_IGNORE( iface = iEcomMonitor->CreateImplementationL(
                infoArray[i]->ImplementationUid()) );
 			       
            if (iface)
                {
                if (!IsCached(iface))
                    {
                    CleanupStack::PushL(iface);
                    result++;
                    iface->AddCriteria(aItem);
                    User::LeaveIfError(iProviders.Append( iface ));
                    CleanupStack::Pop(iface);
                    
                    aBinding->AddProviderL(iface, 
                        infoArray[i]->ImplementationUid() == aItem->DefaultProvider());
                    }                           
                else    
                    {
                    delete iface;
                    iface = NULL;                
                    }
                }
            }
        }

    CleanupStack::PopAndDestroy(); // infoArray     

    return result;
    }



void CAiwServiceHandlerImpl::FilterInfoArray(RImplInfoPtrArray& aArray, CAiwCriteriaItem* aItem)
    {
    if (aItem->MaxProviders() <= 0)
        {
        aArray.ResetAndDestroy();
        }
    else
        {
        while (aArray.Count() > aItem->MaxProviders())
            {
            // Skip default provider.
            if (aArray[0]->ImplementationUid() == aItem->DefaultProvider())
                {
                delete aArray[1];
                aArray.Remove(1);               
                }
            else
                {
                delete aArray[0];
                aArray.Remove(0);               
                }
            }
        }
    }



TBool CAiwServiceHandlerImpl::IsCached(CAiwServiceIfBase* /*aProvider*/)
    {
    return EFalse;
    }


CAiwGenericParamList& CAiwServiceHandlerImpl::InParamListL()
    {
    if (!iInParams)
        {
        iInParams = CAiwGenericParamList::NewL();
        }
    iInParams->Reset();
    return *iInParams;
    }



CAiwGenericParamList& CAiwServiceHandlerImpl::OutParamListL()
    {
    if (!iOutParams)
        {
        iOutParams = CAiwGenericParamList::NewL();
        }
    iOutParams->Reset();
    return *iOutParams;
    }



TBool CAiwServiceHandlerImpl::IsInLastInitialized(CAiwMenuPane* aiwPane) const
    {
    if (aiwPane)
        {
        if (iSubmenu == aiwPane)
            {
            return ETrue;       
            }

        for (TInt i = 0; i < iLastInitialized.Count(); i++)
            {
            if (iLastInitialized[i] == aiwPane)
                {
                return ETrue;
                }
            }
        }

    return EFalse;
    }


TInt CAiwServiceHandlerImpl::HandleNotifyL(
    TInt /*aCmdId*/,
    TInt /*aEventId*/,
    CAiwGenericParamList& /*aEventParamList*/,
    const CAiwGenericParamList& /*aInParamList*/)
    {
    return KErrNone;    
    }


// CEikMenuPane::ConstructFromresourceL is defined as 'protected' so
// we have to use a wrapper class for accessing it.
class CAiwMenuResource : public CEikMenuPane
    {
    public:
        CAiwMenuResource() : CEikMenuPane(NULL) {}
        CAiwMenuResource(MEikMenuObserver* aObserver) : CEikMenuPane(aObserver) {}

        void CreateL(TResourceReader& aReader)
            {
            ConstructFromResourceL(aReader);
            }
    };


CAiwMenuPane* CAiwServiceHandlerImpl::CreateEmptyAiwMenuPaneL(TInt aBaseMenuCmdId, 
    TInt aResourceId)
    {
    CAiwMenuPane* result = NULL;
    TResourceReader reader; 
    
    TInt id;
    if(aResourceId >= 0)
        {
        // Use existing id.
        id = aResourceId;
        }
    else
        {
        // Create new id.
        id = ResourceIdForNextFreeSlot();
        if (id < 0)
            {
            User::Leave(KErrOverflow);
            }
        }
    iCoeEnv->CreateResourceReaderLC(reader, id);
    
    CAiwMenuResource* pane = new (ELeave) CAiwMenuResource(this);
    CleanupStack::PushL(pane);
    pane->ConstructL(NULL);
    pane->CreateL(reader);

    result = new (ELeave) CAiwMenuPane(*pane, aBaseMenuCmdId);
    
    CleanupStack::Pop(pane);
    CleanupStack::PopAndDestroy(); // reader
    
    result->SetResourceSlotId( id );
    
    return result;
    }


void CAiwServiceHandlerImpl::DeleteAiwMenuPane(CAiwMenuPane* aAiwPane)
    {
    delete aAiwPane->iMenuPane;
    aAiwPane->iMenuPane = NULL;

    // Reset iIdMap and extraText.
    for(TInt i = 0; i < aAiwPane->iIdMap.Count(); i++)
        {
        aAiwPane->iIdMap[i].extraText.Close();
        }
    aAiwPane->iIdMap.Reset();
    
    // Remove the aiw menu pane from iMenuPanes array.
    for(TInt i = 0; i < iMenuPanes.Count(); i++)
        {
        if(iMenuPanes[i] == aAiwPane)
            {
            iMenuPanes.Remove(i);
            break;                            
            }
        }
    
    // Remove the aiw menu pane from iMenuLastInitialized array.
    for(TInt i = 0; i < iLastInitialized.Count(); i++)
        {
        if(iLastInitialized[i] == aAiwPane)
            {
            iLastInitialized.Remove(i);
            break;                            
            }
        }                        
    
    delete aAiwPane;
    aAiwPane = NULL;    
    }

const TInt resourceSlotIds[KMaxMenuResources] =
    {
    R_AIW_EMPTY_MENU_0,
    R_AIW_EMPTY_MENU_1,
    R_AIW_EMPTY_MENU_2,
    R_AIW_EMPTY_MENU_3,
    R_AIW_EMPTY_MENU_4,
    R_AIW_EMPTY_MENU_5,
    R_AIW_EMPTY_MENU_6,
    R_AIW_EMPTY_MENU_7,
    R_AIW_EMPTY_MENU_8,
    R_AIW_EMPTY_MENU_9,
    R_AIW_EMPTY_MENU_10,
    R_AIW_EMPTY_MENU_11,
    R_AIW_EMPTY_MENU_12,
    R_AIW_EMPTY_MENU_13,
    R_AIW_EMPTY_MENU_14,
    R_AIW_EMPTY_MENU_15
    };


TInt CAiwServiceHandlerImpl::ResourceIdForNextFreeSlot()
    {
    if (iNextFreeSlot < KMaxMenuResources)
        {
        return resourceSlotIds[iNextFreeSlot++];
        }

    return -1;
    }


void CAiwServiceHandlerImpl::SetEmphasis(CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/)
    {
    }


void CAiwServiceHandlerImpl::ProcessCommandL(TInt /*aCommandId*/) 
    {
    }


void Cleanup( TAny* aAny )
    {
    RImplInfoPtrArray* implArray = 
        reinterpret_cast< RImplInfoPtrArray*> ( aAny );
    implArray->ResetAndDestroy();
    implArray->Close();
    }


void InterestCleanup( TAny* aAny )
    {
    RPointerArray<CAiwCriteriaItem>* interestArray = 
        reinterpret_cast<RPointerArray<CAiwCriteriaItem>*> ( aAny );

    interestArray->ResetAndDestroy();   
    }

void FilteredCleanup( TAny* aAny )
    {
    RPointerArray<CAiwCriteriaItem>* filteredArray = 
        reinterpret_cast<RPointerArray<CAiwCriteriaItem>*> ( aAny );

    filteredArray->Reset();   
    }


void IntArrayCleanup(TAny* aAny)
    {
    RArray<TInt>* intArray = 
        reinterpret_cast<RArray<TInt>*> ( aAny );

    intArray->Close();
    }


void CAiwServiceHandlerImpl::CopyMenuItemsL(CAiwMenuPane* aSource, CEikMenuPane& aDest, 
    TInt aStartIndex, TBool aIsSubmenu, TBool aSetAsItemSpecific)
    {
    TInt cmdId;
    TInt inPos = aStartIndex;

    for (TInt i = 0; i < aSource->MenuPane().NumberOfItemsInPane(); i++)
        {
        cmdId = aSource->FindCmdId(i);
        if (cmdId >= 0)
            {
            CEikMenuPaneItem::SData itemData = aSource->MenuPane().ItemData(cmdId);
            
            // The menu item might include alternative texts for a main menu level 
            // and for submenu. Use submenu string if it is intended so.       
            if(aIsSubmenu)
                {
                const TDesC& extraText = aSource->ExtraText(cmdId);
                if(extraText.Length())
                    {
                    itemData.iText.Zero();
                    itemData.iText.Append(extraText);
                    }                 
                }

            if ( aSetAsItemSpecific )
                {
                itemData.iFlags |= EEikMenuItemSpecific;
                }
            
            aDest.InsertMenuItemL(itemData, inPos++);
            }   
        }   
    }



TInt CAiwServiceHandlerImpl::SlotItemCmd(CEikMenuPane& aPane)
    {
    TInt index;

    for (TInt i = 0; i < KMaxMenuResources; i++)
        {
        if (aPane.MenuItemExists(EAiwMenuSlotBase + i, index))
            {
            return EAiwMenuSlotBase + i;
            }
        }

    return -1;
    }



CAiwMenuPane* CAiwServiceHandlerImpl::MenuPaneForSlotCmd(TInt aCmdId)
    {
    TInt index = aCmdId - EAiwMenuSlotBase; 

    if (index < KMaxMenuResources)
        {
        TInt resId = resourceSlotIds[index];
        for (TInt i = 0; i < iMenuPanes.Count(); i++)
            {
            if (iMenuPanes[i]->ResourceSlotId() == resId)
                {
                return iMenuPanes[i];
                }
            }
        }

    return NULL;
    }



CAiwServiceHandlerImpl::TAiwPlaceholderType CAiwServiceHandlerImpl::PlaceholderType(
    CEikMenuPane& aPane, TInt aCmd, TBool& aTitleLocked)
    {
    CEikMenuPaneItem::SData& itemData = aPane.ItemData(aCmd);

    aTitleLocked = EFalse;

    if ((itemData.iCascadeId & AIW_CASCADE_ID) == AIW_CASCADE_ID)
        {
        if (itemData.iCascadeId & AIW_LOCK_SUBMENU_TITLE)
            {
            aTitleLocked = ETrue;
            }
        return EAiwPlaceholderCascade;
        }
    else if ((itemData.iCascadeId & AIW_INTELLIGENT_CASCADE_ID) == AIW_INTELLIGENT_CASCADE_ID)
        {
        if (itemData.iCascadeId & AIW_LOCK_SUBMENU_TITLE)
            {
            aTitleLocked = ETrue;
            }
        return EAiwPlaceholderIntelligentCascade;
        }

    return EAiwPlaceholderNormal;
    }


void CAiwServiceHandlerImpl::ConvertPlaceholderL(CEikMenuPane& aPane, TInt aCmd, 
    CAiwMenuPane& aAiwPane, const TDesC& aTitle, TBool aSetAsItemSpecific)
    {
    CEikMenuPaneItem::SData itemData = aPane.ItemData(aCmd);
    TInt index;

    // Remenber index.
    aPane.MenuItemExists(aCmd, index);

    // Remove placeholder item.
    aPane.DeleteMenuItem(aCmd);

    // Replace aiw cascade id with actual menu resource id.
    itemData.iCascadeId = aAiwPane.iResourceSlotId;

    if (aTitle.Length())
        {
        itemData.iText.Copy(aTitle);
        }

    // Set unused dynamic cmd id.   
    itemData.iCommandId = iSubmenuCmd++;

    if ( aSetAsItemSpecific )
        {
        itemData.iFlags |= EEikMenuItemSpecific;
        }

    // Insert cascade item.
    aPane.InsertMenuItemL(itemData, index);
    }


void CAiwServiceHandlerImpl::UnCascadeL(CEikMenuPane& aPane, TInt aCmd,
    CAiwMenuPane& aAiwPane, TBool aSetAsItemSpecific)
    {
    CEikMenuPaneItem::SData itemData = aAiwPane.MenuPane().ItemData(aAiwPane.FindCmdId(0));
    TInt index;

    // Remenber index.
    aPane.MenuItemExists(aCmd, index);

    // Remove placeholder item.
    aPane.DeleteMenuItem(aCmd);

    // Uncascade 
    itemData.iCascadeId = 0;

    if ( aSetAsItemSpecific )
        {
        itemData.iFlags |= EEikMenuItemSpecific;
        }

    // Insert cascade item.
    aPane.InsertMenuItemL(itemData, index);     
    }



void CAiwServiceHandlerImpl::SkipMenuFields(TResourceReader& aReader)
    {
    aReader.ReadInt32(); // Skip cascade id
    aReader.ReadInt32(); // Skip flags
    aReader.ReadTPtrC(); // Skip text
    aReader.ReadTPtrC(); // Skip extra text
    aReader.ReadTPtrC(); // Skip bmpfile.
    aReader.ReadInt16(); // Skip bmpid.
    aReader.ReadInt16(); // Skip bmpmask. 
    aReader.ReadInt32(); // Skip extension.   
    }


TBool CAiwServiceHandlerImpl::IsAiwMenu(TInt aMenuResourceId)
    {
    TInt i;

    // First check if this is aiw submenu id
    for (i = 0; i < KMaxMenuResources; i++)
        {
        if (aMenuResourceId == resourceSlotIds[i])
            {
            return ETrue;
            }
        }

    // Then check if this menu is among attached menus.
    for (i = 0; i < iMenuBindings.Count(); i++)
        {
        if (iMenuBindings[i]->MenuId() == aMenuResourceId)
            {
            return ETrue;
            }
        }

    return EFalse;
    }



TBool CAiwServiceHandlerImpl::HandleSubmenuL(CEikMenuPane& aPane)
    {
    TInt slotcmd = SlotItemCmd(aPane);
    if (slotcmd >= 0)
        {
        // aPane is aiw submenu. At this point it is empty and we must
        // copy provider menu items to it.
        CAiwMenuPane* aiwPane = MenuPaneForSlotCmd(slotcmd);
        if (aiwPane)
            {
            CopyMenuItemsL(aiwPane, aPane, 0, ETrue, EFalse);
            aPane.DeleteMenuItem(slotcmd);
            iSubmenu = aiwPane;     
            return ETrue;
            }
        }

    return EFalse;
    }



TBool CAiwServiceHandlerImpl::GetSubmenuTitle(CEikMenuPane& aPane, TDes& aResult)
    {
    TInt index;
    
    aResult.Zero();
    while (aPane.MenuItemExists(AIW_SUBMENU_TITLE, index))
        {
        CEikMenuPaneItem::SData& itemData = aPane.ItemData(AIW_SUBMENU_TITLE);
        if (aResult.Length() == 0)
            {
            aResult.Copy(itemData.iText);
            }
        aPane.DeleteMenuItem(AIW_SUBMENU_TITLE);
        return ETrue;
        }

    return EFalse;
    }



CAiwCriteriaItem* CAiwServiceHandlerImpl::ConvertCriteriaItemPointerL(CAiwCriteriaItem* aCandidate)
    {
    for (TInt i = 0; i < iInterestList.Count(); i++)
        {
        if ((*iInterestList[i]) == (*aCandidate))
            {
            // Already in list, aCandidate is not needed.
            delete aCandidate;
            return iInterestList[i];
            }
        }

    CleanupStack::PushL(aCandidate);
    User::LeaveIfError(iInterestList.Append(aCandidate));
    CleanupStack::Pop(); // aCandidate

    return aCandidate;
    }



void CAiwServiceHandlerImpl::FilterInterestListL(RPointerArray<CAiwCriteriaItem>& aOriginal,
    RPointerArray<CAiwCriteriaItem>& aFiltered)
    {
    CAiwCriteriaItem* item;

    while (aOriginal.Count() > 0)
        {
        item = aOriginal[0];
        aOriginal.Remove(0);
        item = ConvertCriteriaItemPointerL(item);
        User::LeaveIfError(aFiltered.Append(item));
        }
    aOriginal.Reset();
    }



void CAiwServiceHandlerImpl::RemoveProvider(TInt aImplUid)
    {
    TInt i;

    // First go through bindings and remove all the 
    // references to given provider.
    for (i = 0; i < iBaseBindings.Count(); i++)
        {
        iBaseBindings[i]->RemoveProvider(aImplUid);
        }

    for (i = 0; i < iMenuBindings.Count(); i++)
        {
        iMenuBindings[i]->RemoveProvider(aImplUid);
        }
    
    // Then remove provider from the owner list and delete it.
    for (i = 0; i < iProviders.Count(); i++)
        {
        if (iProviders[i]->ImplementationUid().iUid == aImplUid)
            {
            delete iProviders[i];
            iProviders.Remove(i);
            i--;
            }
        }
    }


void CAiwServiceHandlerImpl::AddProviderL(TUid aImplUid, CAiwCriteriaItem* aItem)
    {
    TInt i;
    CAiwServiceIfBase* iface = iEcomMonitor->CreateImplementationL(aImplUid);
    
    if (iface)
        {
        CleanupStack::PushL(iface);
        iface->AddCriteria(aItem);
        User::LeaveIfError(iProviders.Append( iface ));
        CleanupStack::Pop(iface);

        for (i = 0; i < iBaseBindings.Count(); i++)
            {
            if (iBaseBindings[i]->HasCriteriaItem(*aItem) != KErrNotFound)
                {
                iBaseBindings[i]->AddProviderL(iface, aImplUid == aItem->DefaultProvider());
                iface->InitialiseL(*this, iBaseBindings[i]->Interest());
                }               
            }

        for (i = 0; i < iMenuBindings.Count(); i++)
            {
            if (iMenuBindings[i]->HasCriteriaItem(*aItem) != KErrNotFound)
                {
                iMenuBindings[i]->AddProviderL(iface, aImplUid == aItem->DefaultProvider());
                iface->InitialiseL(*this, iMenuBindings[i]->Interest());
                }               
            }
        }
    }



TInt CAiwServiceHandlerImpl::SynchronizeCallBack(TAny* aImpl)
    {
    CAiwServiceHandlerImpl* impl = reinterpret_cast<CAiwServiceHandlerImpl*>(aImpl);
    TRAPD(err, impl->SynchronizeDbL());
    return err;
    }



void CAiwServiceHandlerImpl::SynchronizeDbL()
    {
    TInt i;
    RArray<TInt> providers;
    RImplInfoPtrArray infoArray;

    CleanupStack::PushL( TCleanupItem( IntArrayCleanup, &providers ) );
    CleanupStack::PushL( TCleanupItem( Cleanup, &infoArray ) );

    for (i = 0; i < iInterestList.Count(); i++)
        {
        if (iInterestList[i]->RomOnly())  // Rom-only criterias can be skipped.
            {
            continue;
            }

        providers.Reset();
        infoArray.ResetAndDestroy();
        ListProvidersForCriteriaL(providers, *(iInterestList[i]));
        iEcomMonitor->ListImplemetationsL(infoArray, iInterestList[i]);
        HandleRemovedProviders(providers, infoArray);          
        HandleNewProvidersL(providers, infoArray, iInterestList[i]);        
        }

    CleanupStack::PopAndDestroy(2); // providers, infoArray
    }


void CAiwServiceHandlerImpl::HandleRemovedProviders(RArray<TInt>& aInMemory, 
    RImplInfoPtrArray& aInSystem)
    {
    TInt i, j;

    for (i = 0; i < aInMemory.Count(); i++)
        {
        for (j = 0; j < aInSystem.Count(); j++)
            {
            if (aInSystem[j]->ImplementationUid().iUid == aInMemory[i])
                {
                break;
                }
            }
        if (j >= aInSystem.Count())  // Was removed from system.
            {
            RemoveProvider(aInMemory[i]);
            }
        }
    }


void CAiwServiceHandlerImpl::HandleNewProvidersL(RArray<TInt>& aInMemory, 
    RImplInfoPtrArray& aInSystem, CAiwCriteriaItem* aItem)
    {
    TInt i;

    for (i = 0; i < aInSystem.Count(); i++)
        {
        if (aInMemory.Find(aInSystem[i]->ImplementationUid().iUid) == KErrNotFound)
            {
            AddProviderL(aInSystem[i]->ImplementationUid(), aItem);
            }       
        }
    }
    
void CAiwServiceHandlerImpl::MenuLaunched()
    {  
    ClearMenuPaneArray();
    iNextFreeSlot = 0;
    iLastInitialized.Reset();

    // Reset the iMenuPane pointers from iMenuBindings.
    for(TInt i = 0; i < iMenuBindings.Count(); i++)
        {
        iMenuBindings[i]->SetMenuPane(NULL);
        }
    }

// End of file
