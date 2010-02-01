/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon testability ECom plugin interface definition.  
*                Implementation for ECom instantiation functionality.
*
*/


#include <ecom/implementationinformation.h>

inline CAknTasPluginInterface* CAknTasPluginInterface::NewL()
    {
#ifdef _DEBUG 
    RDebug::Print( _L( "=> CAknTasPluginInterface::NewL" ) );
#endif

    TAny* ptr = REComSession::CreateImplementationL( 
        KAknTasPluginImplementationUid,
        _FOFF( CAknTasPluginInterface, iImplementation ) );

#ifdef _DEBUG
    RDebug::Print( _L( "<= CAknTasPluginInterface::NewL" ) );
#endif
    return reinterpret_cast<CAknTasPluginInterface*>( ptr );
    }

inline CAknTasPluginInterface::~CAknTasPluginInterface()
    {
    REComSession::DestroyedImplementation( iImplementation );
    }

// End of File
