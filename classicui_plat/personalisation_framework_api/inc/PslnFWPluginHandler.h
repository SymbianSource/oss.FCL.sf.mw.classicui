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
* Description:  Loads plugins into plugin array.
*
*/


#ifndef C_PSLNFWPLUGINHANDLER_H
#define C_PSLNFWPLUGINHANDLER_H

#include <e32base.h>

#include "pslnfwplugininterface.h"

class CAknViewAppUi;

/**
 *  Loads all found ECOM plugins into plugin array.
 *
 *  @lib PslnFramework.lib
 *  @since S60 3.1
 */
NONSHARABLE_CLASS( CPslnFWPluginHandler ) : public CBase
    {

public:

    /**
    * Creates plugin handler. 
    * @param aAppUi pointer to application UI owning the plugin views.
    * @param aPluginArray array into which client expects to get the ECOM views.
    * @return new instance of CPslnFWPluginHandler.
    */
    IMPORT_C static CPslnFWPluginHandler* NewL( 
        CAknViewAppUi* aAppUi,
        CArrayPtrFlat<CPslnFWPluginInterface>* aPluginArray );
    
    /**
    * Destructor.
    */
    IMPORT_C ~CPslnFWPluginHandler();

    /**
    * Loads all applicable plugins.
    * @param aPluginArray array into which the plugins should be loaded.
    */
    IMPORT_C void LoadPluginsL( 
        CArrayPtrFlat<CPslnFWPluginInterface>* aPluginArray );

    /**
    * Loads single plugin.
    * @param aPluginId UID of plugin to load.
    * @return plugin interface, or NULL if the plugin is not found.
    */
    IMPORT_C CPslnFWPluginInterface* LoadPluginL( const TUid aPluginId );

    /**
    * Creates plugin handler with no array for plugins.
    * @param aAppUi pointer to application UI owning the plugin views.
    * @return new instance of CPslnFWPluginHandler.
    */
    IMPORT_C static CPslnFWPluginHandler* NewL( CAknViewAppUi* aAppUi );

private:

    /* Default constructor. */
    CPslnFWPluginHandler( 
        CAknViewAppUi* aAppUi, 
        CArrayPtrFlat<CPslnFWPluginInterface>* aPluginArray );

    /**
    * Starts loading next plugin.
    */
    void LoadNextPlugin();
    
    /**
    * Creates the plugin interface and appends it to the plugin array.
    */
    void AppendPluginL( const TUid& aImplUid );

    /**
    * Checks that the plugin location is valid. 
    * Invalid locations are those claimed by static views in Psln main view.
    */
    TBool IsInvalidLocation( const TInt& aLoc ) const;

private: // data

    /**
    * Pointer application UI. 
    * Not own.
    */
    CAknViewAppUi* iAppUi;
           
    /**
    * Personalisation application specific skinning plugins found. 
    * Not own.
    */
    CArrayPtrFlat<CPslnFWPluginInterface>* iPluginArray;

    /**
    * Pluginloader goes through this array and loads the plugins into 
    * iPluginArray if they fulfill the criterias.
    */
    RImplInfoPtrArray iImplInfoArray;
    
    /**
    * Used as an iterator to maintain location in iImplInfoArray.
    */
    TInt iImplInfoArrayIterator;

    };

#endif // C_PSLNFWPLUGINHANDLER_H

// End of File
