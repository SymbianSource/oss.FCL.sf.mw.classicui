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
* Description:     Inline methods for PoC AIW related classes
*
*/





// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// TAiwPocParameterData::TAiwPocParameterData
// -----------------------------------------------------------------------------
TAiwPocParameterData::TAiwPocParameterData()
:   iVersion( 1 ),
    iConsumerAppUid( KNullUid ),
    iConsumerWindowGroup( 0 ),
    iPreferredMenu( KAiwPoCMenuDataBased ),
    iCommandId( 0 ),
    iLogId( 0 ),
    iLogOperation( EPoCNoOpTypeId )
    {
    }

// -----------------------------------------------------------------------------
// TAiwPocParameterData::Version
// -----------------------------------------------------------------------------
inline TInt TAiwPocParameterData::Version() const
    {
    return iVersion;
    }

// End of File
