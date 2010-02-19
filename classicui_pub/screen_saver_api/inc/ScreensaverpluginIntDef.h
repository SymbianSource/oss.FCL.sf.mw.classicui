/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Defines screensaver plugin Ecom interface.
*
*/

#ifndef SCREEN_SAVER_PLUGIN_INT_DEF_H
#define SCREEN_SAVER_PLUGIN_INT_DEF_H

//  INCLUDES
#include <e32base.h>
#include <ecom/implementationinformation.h>
#include <screensaverplugin.h>

// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
* This base class for screensaver ECom plugin implemenation. Every plugin module
* must inherit and implement this class. 
*/
class CScreensaverPluginInterfaceDefinition: public CBase,
                                             public MScreensaverPlugin
    {
    public:         
        /*
        * Function which instantiates an object of this type
        */
        inline static CScreensaverPluginInterfaceDefinition* NewL(TUid aImplementationUid);

        /*
        * Function which lists the currently available screensaver implementations
        *
        * * @param aImplInfoArray A reference to a client-owned array, which on return
        *                         is filled with interface implementation data.
        *                         Any existing data in the array is destroyed.
        */
        inline static void ListImplementationsL(RImplInfoPtrArray& aImplInfoArray);

		/**
		*  Virtual desctructor.
		*/
		inline virtual ~CScreensaverPluginInterfaceDefinition();

    private:
        /**
        *  Required attribute for the framework
        *  (An identifier used during destruction)
        */
        TUid iDtor_ID_Key;
    };

#include "ScreensaverpluginIntDef.inl"

#endif   // SCREEN_SAVER_PLUGIN_INT_DEF_H
// End of file.
