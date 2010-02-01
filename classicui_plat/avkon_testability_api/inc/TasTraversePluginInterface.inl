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
* Description:  Avkon traverse ECom plugin interface definition.  
*               Implementation for ECom instantiation functionality.
*
*/

// SYSTEm INCLUDE
#include <ecom/implementationinformation.h>

// USER INCLUDES
#include "AknTasPluginInterface.h"

// Interface's (abstract base class's) static factory method implementation.
// Asks ECOM plugin framework to instantiate appropriate concret plugin
// implementation.
inline CTasTraversePluginInterface*
CTasTraversePluginInterface::NewL(const TDesC8& aTraverseObjectName, CAknTasPluginInterface * aAknTasPluginInterface )
    {
    // This NewL uses default resolver, which just compares given
    // aTraverseObjectName and default_data string in the implementation
    // resource file.

    // Define options, how the default resolver will find appropriate
    // implementation.
    TEComResolverParams resolverParams;
    resolverParams.SetDataType(aTraverseObjectName);
    resolverParams.SetWildcardMatch(ETrue);     // Allow wildcard matching

    // Find implementation for our interface.
    // - KTasTraversePluginInterfaceUid is the UID of our custom ECOM
    //   interface. It is defined in TasTraversePluginInterface.h
    // - This call will leave, if the plugin architecture cannot find
    //   implementation.
    // - The returned pointer points to one of our interface implementation
    //   instances.
    TAny* ptr = REComSession::CreateImplementationL(
        KTasTraversePluginInterfaceUid,
        _FOFF(CTasTraversePluginInterface,iImplementation),
                // _FOFF specifies offset of iImplementation so that
                // ECOM framework can update its value.
        resolverParams);

    // The type of TAny* ptr should be CTasTraversePluginInterface.
    CTasTraversePluginInterface* traverseInterface = REINTERPRET_CAST(CTasTraversePluginInterface*, ptr);
    
    // Set the CAknTasPluginInterface pointer
    traverseInterface->iAknTasPluginInterface = aAknTasPluginInterface;
    traverseInterface->iAknTasTraverseObjectName.Set( aTraverseObjectName);
   
    
    return traverseInterface;
    }


inline CTasTraversePluginInterface::~CTasTraversePluginInterface()
    {
    REComSession::DestroyedImplementation( iImplementation );
    }


// End of File
