/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon fixture ECom plugin interface definition.
*
*/

#ifndef __TASFIXTUREPLUGININTERFACE_H__
#define __TASFIXTUREPLUGININTERFACE_H__

// INCLUDES
#include <e32base.h>
#include <ecom/ecom.h>
#include <e32hashtab.h>

// CONSTANTS
const static TUid KTasFixturePluginInterfaceUid = { 0x20026F7D };

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
*  Avkon fixture ECom plugin interface definition class.
*  It provides ECom interface instantiation and destruction as well as the 
*  interface for services it provides. The concrete implementations are 
*  defined in inherited classes.
*/
class CTasFixturePluginInterface : public CBase
    {
    public:
        
        /**
         * @brief Two-phased constructor. 
         *
         * Creates an instance of a CTasFixturePluginInterface implementation.
         * ECom framework is used in finding and creating the suitable 
         * implementation. 
         *
         * @return A new instance of a CTasFixturePluginInterface implementation
         */ 
        static CTasFixturePluginInterface* NewL( TUid aImplementationUid );
    
        /**
         * @brief Destructor.
         */
        virtual ~CTasFixturePluginInterface();
        
        /**
         * @brief Execute an action on the fixture plugin.
         *
         * Interface to execute an action with given parameters on the fixture
         * plugin. An object can be given through a void pointer. Response is 
         * send back to the caller.
         * 
         * Abstract function, must be implemented in derived classes.
         *
         * @return KErrNone if the action was successfully executed, one of
         *         the Symbian OS error codes if not.
         * @param aObject An object to be used in execution
         * @param aAction Identification of the desired action 
         * @param aParams Parameters as key - value pairs
         * @param aResponse A response to be send back to the caller
         */
        virtual TInt Execute( 
                    TAny* aObject, 
                    TDesC8& aAction, 
                    RHashMap<RBuf8, RBuf8>& aParams, 
                    RBuf8& aResponse ) = 0;
        
    private: // Data
        
        /// Current instance identifier
        TUid iImplementation;
        
    };

#include <TasFixturePluginInterface.inl>

#endif // __TASFIXTUREPLUGININTERFACE_H__

// End of File
