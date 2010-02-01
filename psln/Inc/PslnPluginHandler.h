/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Handles application specific ECOM plugins.
*
*/



#ifndef C_PSLNPLUGINHANDLER_H
#define C_PSLNPLUGINHANDLER_H

#include <e32base.h>

class CPslnFWPluginInterface;
class CPslnFWPluginHandler;
class CPslnUi;

/**
*  Handles application specific ECOM plugins.
*  Owns the plugins in Psln Application.
*
*  @since S60 v3.1
*/
class CPslnPluginHandler : public CBase
    {
    public:
        
        /**
        * Two-phased constructor.
        * @param aPslnUi pointer to UI class.
        * @return new instance of CPslnPluginHandler.
        */
        static CPslnPluginHandler* NewL( CPslnUi* aPslnUi );
        
        /**
        * Destructor.
        */
        virtual ~CPslnPluginHandler();
        
        /**
        * Gets array of loaded plugins.
        * Plugin array ownership is not transferred.
        * @return array of AknView ECOM plugins.
        */
        CArrayPtrFlat<CPslnFWPluginInterface>* GetPluginArray() const;
        
        /**
        * Retrieves a plugin that matches Uid.
        * Plugin ownership is not transferred.
        * @param aUid plugin to retrieve.
        * @return pointer to the matching plugin interface.
        */
        CPslnFWPluginInterface* GetPlugin( const TUid& aUid );

    private:

        /**
        * C++ constructor.
        */
        CPslnPluginHandler( CPslnUi* aPslnUi );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private:    // Data

        /**
        * Array of loaded plugins.
        * Own.
        */
        CArrayPtrFlat<CPslnFWPluginInterface>* iPluginArray;

        /**
        * Reference to Ui. 
        * Not own. Owned by Main view.
        */
        CPslnUi* iPslnUi;

    };

#endif      // C_PSLNPLUGINHANDLER_H
            
// End of File
