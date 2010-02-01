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
* Description:     Declares Base service API for all providers to implement in 
*                order to offer services to Application Interworking Framework.
*
*/




#ifndef AIW_SERVICE_IF_BASE_H
#define AIW_SERVICE_IF_BASE_H

// INCLUDES
#include <AiwGenericParam.h>
#include <AiwCommon.h>

// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
* This is the base service interface to access providers that offer base services.
*
* This interface needs to be implemented by all the AIW providers. Base service
* providers should inherit from this class directly. Menu service providers 
* should inherit from CAiwServiceIfMenu.
*
* @lib ServiceHandler.lib
* @since Series 60 2.6
* @see CAiwServiceIfMenu
**/
class CAiwServiceIfBase : public CBase
    {
    public:
        /** 
        * Destructor.
        */
        IMPORT_C virtual ~CAiwServiceIfBase();

        /**
        * Called by the AIW framework to initialise provider with necessary information 
        * from the Service Handler. This method is called when the consumer makes 
        * the attach operation.
        *
        * @param aFrameworkCallback Framework provided callback for provider to send 
        *                           events to framework.
        * @param aInterest List of criteria items which invoked the provider.
        */
        virtual void InitialiseL(
            MAiwNotifyCallback& aFrameworkCallback,
            const RCriteriaArray& aInterest) = 0;
        
        /**
        * Executes generic service commands included in criteria.
        *
        * @param aCmdId Command to be executed.
        * @param aInParamList Input parameters, can be an empty list.
        * @param aOutParamList Output parameters, can be an empty list.
        * @param aCmdOptions Options for the command, see KAiwOpt* in AiwCommon.hrh.
        * @param aCallback Callback for asynchronous command handling, parameter checking, etc.
        * @leave KErrArgument Callback is missing when required.
        * @leave KErrNotSupported No provider supports service.
        */
        virtual void HandleServiceCmdL(
            const TInt& aCmdId,
            const CAiwGenericParamList& aInParamList,
            CAiwGenericParamList& aOutParamList,
            TUint aCmdOptions = 0,
            const MAiwNotifyCallback* aCallback = NULL) = 0;

        // Rest of the class is for AIW's internal use and doesn't consern 
        // service providers.
        friend class CAiwServiceHandlerImpl;
        friend class CAiwBinding;
        friend class CAiwEcomMonitor;

    protected:
        IMPORT_C virtual void* ExtensionInterface(TUid aInterface);

    private:
        void SetDtorKeyId(TUid aDtorKeyId);
        TBool Match(CAiwCriteriaItem* aItem);   
        void AddCriteria(CAiwCriteriaItem* aItem);
        TUid ImplementationUid() const;
        void SetImplementationUid(TUid aUid);
        TBool HasCriteria(CAiwCriteriaItem& aItem) const;

    private:
        TUid iDtorKeyId;
        RCriteriaArray iCriterias;
        TUid iImplUid;

        // Reserved member        
        TAny* iReserved;        
    };


#endif  // AIW_SERVICE_IF_BASE_H

// End of file
