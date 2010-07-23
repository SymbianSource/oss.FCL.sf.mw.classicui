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
* Description:  Test api in eikbgfty.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eikcolib.h>

#include "testsdkbuttons.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupFactoryCbaTCreationDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupFactoryCbaTCreationDataL( CStifItemParser& /*aItem*/ )
    {
    EikButtonGroupFactory::TCreationData* data = new ( ELeave ) 
                                                    EikButtonGroupFactory::TCreationData
                                                    (
                                                    CEikButtonGroupContainer::ECba,
                                                    iContainer,
                                                    0,
                                                    &( CCoeEnv::Static()->RootWin() ),
                                                    0,
                                                    CEikButtonGroupContainer::EHorizontal );
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    CleanupStack::PopAndDestroy( data );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupFactoryArrayAddAndRemoveFuncL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupFactoryArrayAddAndRemoveFuncL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupFactoryArray::AppendFactoryFunctionL( CEikCoCtlLibrary::ButtonGroupFactory() );
    CEikButtonGroupFactoryArray::RemoveFactoryFunction( CEikCoCtlLibrary::ButtonGroupFactory() );
    return KErrNone;
    }

// End of file
