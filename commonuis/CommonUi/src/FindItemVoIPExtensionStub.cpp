/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Stub Implementation of CFindItemVoIPExtension
*
*
*/

#include "FindItemVoIPExtension.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
#ifndef RD_VOIP_REL_2_2
CFindItemVoIPExtension::CFindItemVoIPExtension():
    iVoIPSupported( EFalse ),
    iPreferredTelephonyVoIP( EFalse )
    {
    }
#else // RD_VOIP_REL_2_2
CFindItemVoIPExtension::CFindItemVoIPExtension()
    {
    }
#endif // !RD_VOIP_REL_2_2

// Two-phased constructor.
//
CFindItemVoIPExtension* CFindItemVoIPExtension::NewL()
    {
    CFindItemVoIPExtension *self =
        new ( ELeave ) CFindItemVoIPExtension();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// ConstructL
//
void CFindItemVoIPExtension::ConstructL()
    {
    }

// Destructor
//
CFindItemVoIPExtension::~CFindItemVoIPExtension()
    {
    }

#ifndef RD_VOIP_REL_2_2
// ----------------------------------------------------
//  CFindItemVoIPExtension::HandleNotifyInt
// ----------------------------------------------------
//
void CFindItemVoIPExtension::HandleNotifyInt(
    const TUint32 /*aID*/,
    const TInt    /*aNewValue*/ )
    {
    //NO OPERATION
    }

// ----------------------------------------------------
//  CFindItemVoIPExtension::HandleNotifyError
// ----------------------------------------------------
//
void CFindItemVoIPExtension::HandleNotifyError(
    const TUint32 /*aID*/,
    const TInt    /*aError*/,
  CCenRepNotifyHandler* /*aHandler*/ )
    {
    //NO OPERATION
    }
#endif // !RD_VOIP_REL_2_2

// ----------------------------------------------------
// CFindItemVoIPExtension::VoIPProfilesExistL
// ----------------------------------------------------
//
TBool CFindItemVoIPExtension::VoIPProfilesExistL() const
    {
    return EFalse;
    }

// ----------------------------------------------------
// CFindItemVoIPExtension::VoIPProfilesExistL
// ----------------------------------------------------
//
TBool CFindItemVoIPExtension::IsPreferredTelephonyVoIP()
    {
    return EFalse;
    }

// ----------------------------------------------------
// CFindItemVoIPExtension::IsVoIPSupported
//
// ----------------------------------------------------
TBool CFindItemVoIPExtension::IsVoIPSupported()
    {
    return EFalse;
    }
//  End of File

