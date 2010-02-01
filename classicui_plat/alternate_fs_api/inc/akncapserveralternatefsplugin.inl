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
* Description:  
*
*/

// -----------------------------------------------------------------------------
// CAknCapAppServerAlternateFs::NewL
// -----------------------------------------------------------------------------
//
inline CAknCapAppServerAlternateFs* 
    CAknCapAppServerAlternateFs::NewL( const TUid& aImplementationUid )
    {
    CAknCapAppServerAlternateFs* self =
        static_cast<CAknCapAppServerAlternateFs*>(
            REComSession::CreateImplementationL(
            aImplementationUid,
            _FOFF( CAknCapAppServerAlternateFs, iDtorKey ) ) );
    self->iImplUid = aImplementationUid;
    return self;
    }

// -----------------------------------------------------------------------------
// CAknCapAppServerAlternateFs::~CAknCapAppServerAlternateFs
// -----------------------------------------------------------------------------
//
inline CAknCapAppServerAlternateFs::~CAknCapAppServerAlternateFs()
    {
    REComSession::DestroyedImplementation( iDtorKey );
    }
    
// -----------------------------------------------------------------------------
// CAknCapAppServerAlternateFs::ImplementationUid
// -----------------------------------------------------------------------------
//
inline TUid CAknCapAppServerAlternateFs::ImplementationUid() const
    {
    return iImplUid;
    }

// End of file
