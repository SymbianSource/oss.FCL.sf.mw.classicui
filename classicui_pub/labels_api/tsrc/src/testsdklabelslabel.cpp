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
* Description:  Test EIKLABEL.H
*
*/



#include <barsread.h>
#include <coeaui.h>
#include <testsdklabels.rsg>

#include "testsdklabelslabel.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKLabelsLabel::TestLabelDeconstructorL
// -----------------------------------------------------------------------------
CTestSDKLabelsLabel* CTestSDKLabelsLabel::NewLC()
    {
    CTestSDKLabelsLabel* self = new (ELeave) CTestSDKLabelsLabel;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKLabelsLabel::~CTestSDKLabelsLabel
// -----------------------------------------------------------------------------
CTestSDKLabelsLabel::~CTestSDKLabelsLabel()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabelsLabel::WriteInternalStateL
// -----------------------------------------------------------------------------
void CTestSDKLabelsLabel::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CEikLabel::WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestSDKLabelsLabel::ConstructL
// -----------------------------------------------------------------------------
void CTestSDKLabelsLabel::ConstructL()
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    CEikLabel::ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    }

// -----------------------------------------------------------------------------
// CTestSDKLabelsLabel::CTestSDKLabelsLabel
// -----------------------------------------------------------------------------
CTestSDKLabelsLabel::CTestSDKLabelsLabel():CEikLabel()
    {
    
    }
