/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*
*/

#ifndef C_CBCTESTDOMAIWSERVICEIFMENU_H
#define C_CBCTESTDOMAIWSERVICEIFMENU_H


#include <aiwserviceifmenu.h> 
 

/**
 *  test CAiwServiceIfMenu and CAiwServiceIfBase.
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib   
 *  @since S60 v5.0
 */ 
class CBCTestDomAiwServiceIfMenu : public CAiwServiceIfMenu
    {


public:

    IMPORT_C static CBCTestDomAiwServiceIfMenu* NewL();

    IMPORT_C static CBCTestDomAiwServiceIfMenu* NewLC();

    /**
     * Destructor.
     */
    IMPORT_C virtual ~CBCTestDomAiwServiceIfMenu();

    /**
     * test ExtensionInterface
     *  
     * @since S60 v5.0       
     */
    void TestFuncExtensionInterface() ;

// from base class CAiwServiceIfBase  
    /**
     * From CAiwServiceIfBase.      
     * Called by the AIW framework to initialise provider with necessary
     * information from the Service Handler. This method is called when 
     * the consumer makes the attach operation.
     *
     * @since S60 v5.0       
     * @param aFrameworkCallback Framework provided callback for provider 
     *                  to send events to framework.
     * @param aInterest List of criteria items which invoked the provider.
     */
     virtual void InitialiseL(
         MAiwNotifyCallback& aFrameworkCallback,
         const RCriteriaArray& aInterest) ;
     
    /**
     * From CAiwServiceIfBase.      
     * Executes generic service commands included in criteria.
     *
     * @since S60 v5.0       
     * @param aCmdId Command to be executed.
     * @param aInParamList Input parameters, can be an empty list.
     * @param aOutParamList Output parameters, can be an empty list.
     * @param aCmdOptions Options for the command, see KAiwOpt* in 
     *        AiwCommon.hrh.
     * @param aCallback Callback for asynchronous command handling, 
     *        parameter checking, etc.
     * @leave KErrArgument Callback is missing when required.
     * @leave KErrNotSupported No provider supports service.
     */
     virtual void HandleServiceCmdL(
         const TInt& aCmdId,
         const CAiwGenericParamList& aInParamList,
         CAiwGenericParamList& aOutParamList,
         TUint aCmdOptions = 0,
         const MAiwNotifyCallback* aCallback = NULL) ;
    
// from base class CAiwServiceIfMenu    
     
    /**
     * From CAiwServiceIfMenu.    
     * Provider should implement this method to initialise a menu pane by 
     * adding provider specific menu items. The AIW framework gives the 
     * parameters to beused in the addition process.
     *
     * @since S60 v5.0     
     * @param aMenuPane Menu pane handle.
     * @param aIndex The position of the item where to add menu items.
     * @param aCascadeId ID of cascade menu item.
     * @param aInParamList Input parameter list for provider's parameter
     *         checking.
     */
     virtual void InitializeMenuPaneL(
         CAiwMenuPane& aMenuPane,
         TInt aIndex,
         TInt aCascadeId,
         const CAiwGenericParamList& aInParamList);

    /**
     * From CAiwServiceIfMenu.    
     * Provider should implement this method to handle a menu command. 
     * Called by the Service Handler when a consumer calls ExecuteMenuCmdL().
     *
     * @since S60 v5.0     
     * @param aMenuCmdId Original provider specific ommand ID for the menu
     *              command.Defined in the provider's menu item resource.
     * @param aInParamList Input parameters, can be an empty list.
     * @param aOutParamList Output parameters, can be an empty list.
     * @param aCmdOptions Options for the command, see KAiwCmdOpt* in
     *         AiwCommon.hrh.
     * @param aCallback Callback if asynchronous command handling is wanted by
     *             consumer.The provider may or may not support this. A 
     *             provider should leave with KErrNotSupported, if not.
     * @leave KErrNotSupported Callback is not supported.
     */
     virtual void HandleMenuCmdL(
         TInt aMenuCmdId,
         const CAiwGenericParamList& aInParamList,
         CAiwGenericParamList& aOutParamList,
         TUint aCmdOptions = 0,
         const MAiwNotifyCallback* aCallback = NULL); 
        

private:

    CBCTestDomAiwServiceIfMenu();

    void ConstructL();

    };

#endif // C_CBCTESTDOMAIWSERVICEIFMENU_H
