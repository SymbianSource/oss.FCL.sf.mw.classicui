/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Defines interface for application skinning framework's ECOM
*                plugin.
*
*/


#ifndef C_PSLNFWPLUGININTERFACENOBASEVIEW_H
#ifndef C_PSLNFWPLUGININTERFACE_H

#define C_PSLNFWPLUGININTERFACENOBASEVIEW_H

#include <gulicon.h>
#include <AknsUtils.h>
#include <AknViewAppUi.h>
#include <data_caging_path_literals.hrh>

// Constants used in ECOM implementation
const TUid KPslnFWPluginInterfaceUid    = { 0x102750A9 };

/**
* Interface class for Psln plugin. All Psln plugins that inherit CBase from 
* other means will implement this class. This is alternative to 
* PslnFwPluginInterface. The only difference is that there is no CBase-inheritance
* in this class. 
* 
* Note that classes implementing this interface NEED to inherit
* CAknView by some other means. 
*
* Also note that class cannot implement both this and PslnFwPluginInterface (as
* defined in the PslnPluginInterface.h).
*
* For details how to implement a Psln ECOM view, 
* see header file PslnFwPluginInterface.h.
*
* @lib PslnFramework.lib
* @since S60 v3.1
*/
class CPslnFWPluginInterface: public CBase
    {
public:

    /**
    * Specifies the location of the plugin in the Personalization application.
    * By default the plugins are appended to the end of the main view.
    */
    enum TPslnFWLocationType
        {
        // Personalization application decides plugins location (recommended)
        EPslnFWNotSpecified = 0,
        // Location is specified in aIndex parameter. Note that if the location 
        // is already taken by some other plugin (or static view), then plugin
        // view is appended to the end, just like it had EPslnFWNotSpecified set.
        EPslnFWSpecified
        };

    /**
    * Creates new Psln plugin having the given UID.
    * Uses Leave code KErrNotFound if implementation is not found.
    *
    * @param aImplementationUid Implementation UID of the plugin to be
    *        created.
    * @param aAppUi Pointer to the Psln application UI that can be used to
    *               switch to another view.
    */
    static CPslnFWPluginInterface* NewL(
        const TUid aImplementationUid,
        CAknViewAppUi* aAppUi );

    /**
    * Destructor
    */
    inline ~CPslnFWPluginInterface();

    /**
    * Method for getting caption of this plugin. This should be the
    * localized name of the plugin view to be shown in main view.
    *
    * @param aCaption pointer to Caption variable
    */
    virtual void GetCaptionL( TDes& aCaption ) const = 0;

    /**
    * Method for getting tab text for this plugin. This should be the
    * localized name of the plugin view to be shown in tab group.
    *
    * @param aCaption pointer to Caption variable
    */
    virtual void GetTabTextL( TDes& aCaption ) const = 0;

    /**
    * Creates a new icon. This icon is shown in Personalization app's main view. 
    * Ownership of the created icon is transferred to the caller.
    *
    * @return Pointer of the icon. 
    * NOTE: Ownership of this icon is transferred to the caller.
    */
    virtual CGulIcon* CreateIconL() = 0;

    /**
    * Method for getting the plugin view's location within Psln application.
    * Do not override, unless plugin view should be in certain location.
    * By default the plugins are appended to the end of the main view.
    * @param aType type of location: specified / not specified
    * @param aIndex proposed location of plugin.
    */
    virtual inline void GetLocationTypeAndIndex( 
        TPslnFWLocationType& aType, 
        TInt& aIndex ) const;

    /**
    * Reserved for future use/plugin's custom functionality. This can be
    * overwritten if plugin needs to have custom functionality which cannot
    * be fulfilled otherwise.
    */
    virtual inline TAny* CustomOperationL( TAny* aParam1, TAny* aParam2 );

protected: // data

    /**
    * Pointer to application UI. This is protected, so that classes 
    * implementing the interface inherit pointer to AppUi.
    * Not own.
    */
    CAknViewAppUi* iAppUi;


private: // data

    /**
     * ECOM plugin instance UID.
     */
     TUid iDtor_ID_Key;

    };

#include "PslnFWPluginInterface.inl"

#endif // C_PSLNFWPLUGININTERFACE_H
#endif // C_PSLNFWPLUGININTERFACENOBASEVIEW_H

//End of file
