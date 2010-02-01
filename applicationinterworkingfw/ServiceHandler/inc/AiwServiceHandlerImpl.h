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
* Description:     Implementation class for CAiwServiceHandler. 
*                See also AiwServiceHandler.h.
*
*/





#ifndef AIW_SERVICE_HANDLER_IMPL_H
#define AIW_SERVICE_HANDLER_IMPL_H

// INCLUDES
#include <ecom/ecom.h>
#include <barsread.h> 
#include <AiwCommon.h>
#include "AiwTlsData.h"
#include <eikmobs.h> 

// CONSTANTS

// MACROS

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CAiwMenuBinding;
class CAiwMenuPane;
class CAiwServiceIfMenu;
class CAiwServiceIfBase;
class CAiwEcomMonitor;

// CLASS DECLARATION

/**
* Internal implementation class for CAiwServiceHandler. 
*
* Contains the actual implementation logic for Service Handler, whereas the
* CAiwServiceHandler class provides only the public API. 
*
* @see CAiwServiceHandler for API documentation.
* @since Series 60 2.6
*/
NONSHARABLE_CLASS(CAiwServiceHandlerImpl) :
    public CBase,
    public MAiwNotifyCallback,
    public MEikMenuObserver,
    public MAiwMenuLaunchObserver
    {
    public:  // Construction & destruction
        /**
        * Constructs CAiwServiceHandlerImpl instance.
        *
        * @return Pointer to the new instance.
        */
        static CAiwServiceHandlerImpl* NewL();

        /** 
        * Destructor.
        */
        virtual ~CAiwServiceHandlerImpl();
        
    public:  // Management
        /**
        * @see CAiwServiceHandler::Reset()
        */
        void Reset();

        /**
        * @see CAiwServiceHandler::NbrOfProviders() 
        */
        TInt NbrOfProviders(const CAiwCriteriaItem* aCriteria);
        
    public:  // Interest handling
        /**
        * @see CAiwServiceHandler::AttachL() 
        */
        void AttachL(TInt aInterestResourceId);

        /**
        * @see CAiwServiceHandler::AttachL() 
        */
        void AttachL(const RCriteriaArray& aInterest);

        /**
        * @see CAiwServiceHandler::GetInterest()
        */
        void GetInterest(RCriteriaArray& aInterest);

        /**
        * @see CAiwServiceHandler::DetachL()
        */
        void DetachL(const RCriteriaArray& aInterest);

        /**
        * @see CAiwServiceHandler::DetachL()
        */
        void DetachL(TInt aInterestResourceId); 
        
        /**
        * @see CAiwServiceHandler::GetCriteria()
        */
        const CAiwCriteriaItem* GetCriteria(TInt aId);

        /**
        * @see CAiwServiceHandler::InParamListL()
        */
        CAiwGenericParamList& InParamListL();

        /**
        * @see CAiwServiceHandler::OutParamListL()
        */
        CAiwGenericParamList& OutParamListL();
        
    public:  // Menu handling
        /**
        * @see CAiwServiceHandler::InitializeMenuPaneL()
        */
        void InitializeMenuPaneL(
            CEikMenuPane& aMenuPane,
            TInt aMenuResourceId,
            TInt aBaseMenuCmdId,
            const CAiwGenericParamList& aInParamList);
            
        /**
        * @see CAiwServiceHandler::InitializeMenuPaneL()
        */
        void InitializeMenuPaneL(
            CEikMenuPane& aMenuPane,
            TInt aMenuResourceId,
            TInt aBaseMenuCmdId,
            const CAiwGenericParamList& aInParamList,
            TBool aUseSubmenuTextsIfAvailable);            

        /**
        * @see CAiwServiceHandler::InitializeMenuPaneL()
        */
        void InitializeMenuPaneL(
            CEikMenuPane& aMenuPane,
            TInt aMenuResourceId,
            TInt aBaseMenuCmdId,
            const CAiwGenericParamList& aInParamList,
            TBool aUseSubmenuTextsIfAvailable,
            TBool aSetAsItemSpecific );
        
        /**
        * @see CAiwServiceHandler::ServiceCmdByMenuCmd()
        */
        TInt ServiceCmdByMenuCmd(TInt aMenuCmdId) const;

        /**
        * @see CAiwServiceHandler::ExecuteMenuCmdL()
        */
        void ExecuteMenuCmdL(
            TInt aMenuCmdId,
            const CAiwGenericParamList& aInParamList,
            CAiwGenericParamList& aOutParamList,
            TUint aCmdOptions = 0,
            MAiwNotifyCallback* aCallback= NULL);

        /**
        * @see CAiwServiceHandler::AttachMenuL()
        */
        void AttachMenuL(TInt aMenuResourceId, TInt aInterestResourceId);

        /**
        * @see CAiwServiceHandler::AttachMenuL()
        */
        void AttachMenuL(TInt aMenuResourceId, TResourceReader& aReader);
        
        /**
        * @see CAiwServiceHandler::AttachMenuL()
        */
        void AttachMenuL(TInt aMenuResourceId, const RCriteriaArray& aInterest);           
        
        /**
        * @see CAiwServiceHandler::DetachMenu()
        */
        void DetachMenu(TInt aMenuResourceId, TInt aInterestResourceId);

        /**
        * @see CAiwServiceHandler::IsSubMenuEmpty()
        */
        TBool IsSubMenuEmpty(TInt aSubMenuId);

        /**
        * @see CAiwServiceHandler::IsAiwMenu()
        */
        TBool IsAiwMenu(TInt aMenuResourceId);

        /**
        * @see CAiwServiceHandler::HandleSubmenuL()
        */
        TBool HandleSubmenuL(CEikMenuPane& aPane);

    public:  // Generic service command handling
        /**
        * @see CAiwServiceHandler::ExecuteServiceCmdL()
        */
        void ExecuteServiceCmdL(
            const TInt& aCmdId,
            const CAiwGenericParamList& aInParamList,
            CAiwGenericParamList& aOutParamList,
            TUint aCmdOptions = 0,
            MAiwNotifyCallback* aCallback = 0);

    public:  // Other new methods
        /** 
        * Called by CAiwEcomMonitor.
        *
        * @param aImpl An object representing this class.
        * @return An error code. KErrNone if successful.
        */ 
        static TInt SynchronizeCallBack(TAny* aImpl);
        
    public: // From MAiwNotifyCallback
        TInt HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CAiwGenericParamList& aEventParamList,
            const CAiwGenericParamList& aInParamList);

    public: // From MEikMenuObserver
        void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);

    public: // From MEikCommandObserver (via MEikMenuObserver)
        void ProcessCommandL(TInt aCommandId);

    private: // From MAiwMenuLaunchObserver
        void MenuLaunched();

    private:
        // Possible placeholder types.
        enum TAiwPlaceholderType
            {
            EAiwPlaceholderNormal,
            EAiwPlaceholderCascade,     
            EAiwPlaceholderIntelligentCascade
            };

    private:
        CAiwServiceHandlerImpl();
        void ConstructL();

        // Attach menu related criteria items to given menu. 
        void DoAttachMenuL(TResourceReader& aReader, TInt aMenuId, RCriteriaArray& aInterest);

        void DoAttachL(const RCriteriaArray& aInterest);
        void ReadInterestListL(TResourceReader& aReader, RPointerArray<CAiwCriteriaItem>& aResult);
        TInt ResolveProvidersL(CAiwBinding* aBinding, CAiwCriteriaItem* aItem);
        TBool IsCached(CAiwServiceIfBase* aProvider);
        
        CAiwMenuPane* CreateEmptyAiwMenuPaneL(TInt aBaseMenuCmdId, TInt aResourceId);
        void DeleteAiwMenuPane(CAiwMenuPane* aAiwPane);
        
        TInt ResourceIdForNextFreeSlot();
        void CopyMenuItemsL(CAiwMenuPane* aSource, CEikMenuPane& aDest, TInt aStartIndex, 
            TBool aIsSubmenu, TBool aSetAsItemSpecific);
        TInt SlotItemCmd(CEikMenuPane& aPane);
        CAiwMenuPane* MenuPaneForSlotCmd(TInt aCmdId);
        TAiwPlaceholderType PlaceholderType(CEikMenuPane& aPane, TInt aCmd, TBool& aTitleLocked);
        void ConvertPlaceholderL(CEikMenuPane& aPane, TInt aCmd, CAiwMenuPane& aAiwPane, 
            const TDesC& aTitle, TBool aSetAsItemSpecific);
        void UnCascadeL(CEikMenuPane& aPane, TInt aCmd, CAiwMenuPane& aAiwPane,
            TBool aSetAsItemSpecific);
        void SkipMenuFields(TResourceReader& aReader);
        TBool IsInLastInitialized(CAiwMenuPane* aiwPane) const;
        TBool GetSubmenuTitle(CEikMenuPane& aPane, TDes& aResult);
        TBool IsCriteriaAlreadyInInterest(CAiwCriteriaItem& aItem, 
            RPointerArray<CAiwCriteriaItem>& aInterest) const;
        CAiwCriteriaItem* ConvertCriteriaItemPointerL(CAiwCriteriaItem* aCandidate);
        void FilterInterestListL(RPointerArray<CAiwCriteriaItem>& aOriginal,
            RPointerArray<CAiwCriteriaItem>& aFiltered);
        void FilterInfoArray(RImplInfoPtrArray& aArray, CAiwCriteriaItem* aItem);
        CAiwMenuBinding* AlreadyBound(TInt aMenuId, TInt aMenuCmd, TInt aMenuItemIndex) const;
        void SynchronizeDbL();
        void ListProvidersForCriteriaL(RArray<TInt>& aResult, CAiwCriteriaItem& aItem);
        void HandleRemovedProviders(RArray<TInt>& aInMemory, RImplInfoPtrArray& aOnSystem);
        void HandleNewProvidersL(RArray<TInt>& aInMemory, RImplInfoPtrArray& aOnSystem, 
            CAiwCriteriaItem* aItem);
        void RemoveProvider(TInt aImplUid);
        void AddProviderL(TUid aImplUid, CAiwCriteriaItem* aItem);
        inline void ClearMenuPaneArray();
        TInt NumAlreadyInitializedPaneIdsL() const;

        // Leaving helper method. Handler cleanupstack issues and calls ReadInterestListL().
        void ReadInterestL(RCriteriaArray& aInterest, TInt aInterestResourceId);

        // Detaches all items from given menu.        
        void DoDetachMenu(TInt aMenuResourceId);

        // Detaches only those items from a given menu, which match the given interest.
        void DoDetachMenu(TInt aMenuResourceId, RCriteriaArray& aInterest);
        
        // Removes unnecessary criteria items from Service Handler.
        void RemoveObsoleteCriteriaItems();
        
        // Removes unnecessary providers from Service Handler.
        void RemoveObsoleteProviders();

    private:
        // Pointer to the control environment.
        CCoeEnv* iCoeEnv;
        
        // Owns all the attached criteria items.
        RPointerArray<CAiwCriteriaItem> iInterestList;  
        
        // Criteria -> provider bindings for base service providers.
        RPointerArray<CAiwBinding>      iBaseBindings;  
        
        // Criteria -> provider bindings for menu service providers.
        RPointerArray<CAiwMenuBinding>  iMenuBindings;  
        
        // Contains the AIW menu panes.
        RPointerArray<CAiwMenuPane>     iMenuPanes;     

        // Input parameter list which can be given to the consumer application.
        CAiwGenericParamList* iInParams;
        
        // Output parameter list which can be given to the consumer application.
        CAiwGenericParamList* iOutParams; 
        
        // Resource offset for AiwServiceHandler.rsc.
        TInt iResourceOffset;
        
        // Owns all the providers currently in memory.
        RPointerArray<CAiwServiceIfBase> iProviders;  
          
        TInt                             iNextFreeSlot;
        RPointerArray<CAiwMenuPane>      iLastInitialized;
        CAiwMenuPane*                    iSubmenu;
        TInt                             iSubmenuCmd;
        CAiwEcomMonitor*                 iEcomMonitor;
        TBool                            iTlsDataOpened;
    };


inline void CAiwServiceHandlerImpl::ClearMenuPaneArray()
    {
    iMenuPanes.ResetAndDestroy();
    }

#endif // AIW_SERVICE_HANDLER_IMPL_H

// END of File


