/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef C_PSLNFWPLUGININTERFACE_H
#ifndef C_PSLNFWPLUGININTERFACENOBASEVIEW_H
#define C_PSLNFWPLUGININTERFACE_H

#include <aknview.h>
#include <gulicon.h>
#include <AknsUtils.h>
#include <aknViewAppUi.h>
#include <data_caging_path_literals.hrh>

// Constants used in ECOM implementation
const TUid KPslnFWPluginInterfaceUid    = { 0x102750A9 };

/**
* Interface class for Psln plugin. All Psln plugins will implement this class.
*
* The main functionality Psln framework will use from CAknView is:
* -DoActivate()
* -DoDeactivate()
* -Id()
* functions.
*
* Id() function must return the value of the plugin implementation UID. This
* means that the main view of the plugin will have the same UID as the plugin
* implementation. This will prevent multiple plugins from having same view
* UIDs as their main view. If plugin has more views, it is plugin's
* responsibility to ensure that the UIDs of the other views are unique.
*
* This class is mutually exclusive with CPslnFWPluginInterface as defined in the
* PslnPluginInterfaceNoBaseView.h.
*
* @lib PslnFramework.lib
* @since S60 v3.1
*/
class CPslnFWPluginInterface: public CAknView
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

#include "pslnfwplugininterface.inl"


#endif // C_PSLNFWPLUGININTERFACENOBASEVIEW_H
#endif // C_PSLNFWPLUGININTERFACE_H

//End of file
