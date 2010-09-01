/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test EIKINFO.H 
*
*/


//  INCLUDES
#include "testsdknotesprogressinfo.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKNotesProgressInfo::NewLC
// -----------------------------------------------------------------------------
CTestSDKNotesProgressInfo* CTestSDKNotesProgressInfo::NewLC( const SInfo& aProgInfo )
    {
    CTestSDKNotesProgressInfo* self =new (ELeave) CTestSDKNotesProgressInfo( aProgInfo );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesProgressInfo::~CTestSDKNotesProgressInfo
// -----------------------------------------------------------------------------
CTestSDKNotesProgressInfo::~CTestSDKNotesProgressInfo()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesProgressInfo::EvaluateText
// -----------------------------------------------------------------------------
const TDesC* CTestSDKNotesProgressInfo::EvaluateText( TDes& aTextBuf ) const
    {
    return CEikProgressInfo::EvaluateText( aTextBuf );
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesProgressInfo::ConstructL
// -----------------------------------------------------------------------------
void CTestSDKNotesProgressInfo::ConstructL()
    {
    CEikProgressInfo::ConstructL();
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesProgressInfo::CTestSDKNotesControl
// -----------------------------------------------------------------------------
CTestSDKNotesProgressInfo::CTestSDKNotesProgressInfo( const SInfo& aProgInfo ):CEikProgressInfo( aProgInfo )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesProgressInfo::WriteInternalStateL
// -----------------------------------------------------------------------------
void CTestSDKNotesProgressInfo::WriteInternalStateL( RWriteStream& aWriteStream ) const
    {
    CEikProgressInfo::WriteInternalStateL( aWriteStream );
    }
