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
* Description:    test functions for testing aiwpocparameters.h
*
*/






// INCLUDE FILES
#include <aiwpocparameters.h>

#include "testdomextaiwcriteria.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwPPDTAiwPocParameterDataL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwPPDTAiwPocParameterDataL( CStifItemParser& /*aItem*/ )
    {
    TAiwPocParameterData* pocparadata = new ( ELeave ) TAiwPocParameterData();
    CleanupStack::PushL( pocparadata );
    
    STIF_ASSERT_NOT_NULL( pocparadata );
    
    CleanupStack::PopAndDestroy( pocparadata );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwPPDVersion
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwPPDVersion( CStifItemParser& /*aItem*/ )
    {
    TAiwPocParameterData pocparadata;
    
    pocparadata.Version();
    
    return KErrNone;
    }



// End of file

