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
* Description:  Inline methods for the Psln slide set settings dialog interface.
*
*/


// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
inline CPslnSlidesetDialogInterface::~CPslnSlidesetDialogInterface()
    {
    REComSession::DestroyedImplementation( iDtor_ID_Key );
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
inline CPslnSlidesetDialogInterface* CPslnSlidesetDialogInterface::NewL( 
    TUid aImplementationUid ) 
    {
    TAny* ptr;
    TInt32 keyOffset = _FOFF( CPslnSlidesetDialogInterface, iDtor_ID_Key );
    ptr = REComSession::CreateImplementationL(
        aImplementationUid,
        keyOffset );

    return reinterpret_cast<CPslnSlidesetDialogInterface*>(ptr);
    }

// -----------------------------------------------------------------------------
// Reserved for future use.
// -----------------------------------------------------------------------------
//
inline TAny* CPslnSlidesetDialogInterface::CustomOperationL(
    TAny* /*aParam1*/, 
    TAny* /*aParam2*/ )
    {
    return NULL;
    }

//  End of File  

