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
*               Implementation for ECom instantiation functionality.
*
*/

#include <ecom/implementationinformation.h>

inline CTasFixturePluginInterface* CTasFixturePluginInterface::NewL( 
        TUid aImplementationUid )
    {
#ifdef _DEBUG 
    RDebug::Print( _L( "=> CTasFixturePluginInterface::NewL" ) );
#endif

    TAny* ptr = REComSession::CreateImplementationL( 
            aImplementationUid,
            _FOFF( CTasFixturePluginInterface, iImplementation ) );

#ifdef _DEBUG
    RDebug::Print( _L( "<= CTasFixturePluginInterface::NewL" ) );
#endif
    return reinterpret_cast<CTasFixturePluginInterface*>( ptr );
    }

inline CTasFixturePluginInterface::~CTasFixturePluginInterface()
    {
    REComSession::DestroyedImplementation( iImplementation );
    }

// End of File
