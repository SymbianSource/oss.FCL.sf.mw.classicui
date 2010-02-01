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
* Description:     Declares service API for providers offering menu services for 
*                consumers.
*
*/




#ifndef AIW_SERVICE_IF_MENU_H
#define AIW_SERVICE_IF_MENU_H

// INCLUDES
#include <AiwServiceIfBase.h>

// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CAiwMenuPane;

// CLASS DECLARATION

/**
* This is the menu service interface to access providers that offer menu services.
*
* Menu service providers should inherit this class. Providers offering 
* only base services should inherit CAiwServiceIfBase instead.
*
* @lib ServiceHandler.lib
* @since Series 60 2.6
* @see CAiwServiceIfBase
**/
class CAiwServiceIfMenu: public CAiwServiceIfBase
    {
    public:
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CAiwServiceIfMenu();

        /**
        * Provider should implement this method to initialise a menu pane by adding 
        * provider specific menu items. The AIW framework gives the parameters to be 
        * used in the addition process.
        *
        * @param aMenuPane Menu pane handle.
        * @param aIndex The position of the item where to add menu items.
        * @param aCascadeId ID of cascade menu item.
        * @param aInParamList Input parameter list for provider's parameter checking.
        */
        virtual void InitializeMenuPaneL(
            CAiwMenuPane& aMenuPane,
            TInt aIndex,
            TInt aCascadeId,
            const CAiwGenericParamList& aInParamList) = 0;

        /**
        * Provider should implement this method to handle a menu command. Called by the 
        * Service Handler when a consumer calls ExecuteMenuCmdL().
        *
        * @param aMenuCmdId Original provider specific ommand ID for the menu command.
        *                   Defined in the provider's menu item resource.
        * @param aInParamList Input parameters, can be an empty list.
        * @param aOutParamList Output parameters, can be an empty list.
        * @param aCmdOptions Options for the command, see KAiwCmdOpt* in AiwCommon.hrh.
        * @param aCallback Callback if asynchronous command handling is wanted by consumer.
        *                  The provider may or may not support this. A provider should 
        *                  leave with KErrNotSupported, if not.
        * @leave KErrNotSupported Callback is not supported.
        */
        virtual void HandleMenuCmdL(
            TInt aMenuCmdId,
            const CAiwGenericParamList& aInParamList,
            CAiwGenericParamList& aOutParamList,
            TUint aCmdOptions = 0,
            const MAiwNotifyCallback* aCallback = NULL) = 0;

        /**
        * Returns current AIW menu pane for this menu service provider.
        *
        * @return Pointer to the current AIW menu pane object. 
        */
        IMPORT_C const CAiwMenuPane* MenuPane() const;
        
    protected:
        IMPORT_C virtual void* ExtensionInterface(TUid aInterface);        
        
    private:
        // Rest of the class is for AIW's internal use and doesn't consern 
        // service providers.    
        friend class CAiwServiceHandlerImpl;

        void InitializeMenuPaneHookL(
            CAiwMenuPane* aMenuPane,
            TInt aIndex,
            TInt aCascadeId,
            const CAiwGenericParamList& aInParamList);

        void HandleMenuCmdHookL(
            CAiwMenuPane* aMenuPane,
            TInt aMenuCmdId,
            const CAiwGenericParamList& aInParamList,
            CAiwGenericParamList& aOutParamList,
            TUint aCmdOptions = 0,
            const MAiwNotifyCallback* aCallback = NULL);
        
    private:
        CAiwMenuPane* iMenuPane; // Not owned.
        
        // Reserved member        
        TAny* iSpare;         
    };


#endif // AIW_SERVICE_IF_MENU_H

// End of file
