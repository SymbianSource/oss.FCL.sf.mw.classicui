/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Inline functions for CPslnFWPluginInteface.
*
*/


// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
inline CPslnFWPluginInterface::~CPslnFWPluginInterface()
    {
    REComSession::DestroyedImplementation( iDtor_ID_Key );
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
inline CPslnFWPluginInterface* CPslnFWPluginInterface::NewL( 
    TUid aImplementationUid, 
    CAknViewAppUi* aAppUi ) 
    {
    TAny* ptr;
    TInt32 keyOffset = _FOFF( CPslnFWPluginInterface, iDtor_ID_Key );
    ptr = REComSession::CreateImplementationL(
        aImplementationUid,
        keyOffset,
        aAppUi );
    
    CPslnFWPluginInterface* plugin = 
        reinterpret_cast <CPslnFWPluginInterface*> (ptr);
    plugin->iAppUi = aAppUi;
    return plugin;
    }    
    
// -----------------------------------------------------------------------------
// CPslnFWPluginInterface::CustomOperationL()
// -----------------------------------------------------------------------------
//
inline TAny* CPslnFWPluginInterface::CustomOperationL(
    TAny* /*aParam1*/, 
    TAny* /*aParam2*/ )
    {
    return NULL;   
    }
    
// -----------------------------------------------------------------------------
// CPslnFWPluginInterface::GetLocationTypeAndIndex()
// -----------------------------------------------------------------------------
//
inline void CPslnFWPluginInterface::GetLocationTypeAndIndex( 
            TPslnFWLocationType& aType, 
            TInt& aIndex ) const
    {
    aType = EPslnFWNotSpecified;
    aIndex = KErrNotFound;
    }

//  End of File  
