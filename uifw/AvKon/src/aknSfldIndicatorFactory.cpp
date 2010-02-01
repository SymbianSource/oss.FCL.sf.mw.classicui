/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*  Implementation of search field indicatorfactory.
*  Returns new search field indicator if apac variant.
*
*/


// INCLUDES
#include "aknSfldIndicatorFactory.h"
#include "aknsfldIndicator.h"
#include <featmgr.h>

// -----------------------------------------------------------------------------
// AknSearchFieldIndicatorFactory::CreateIndicatorL()
// -----------------------------------------------------------------------------

CAknSearchFieldIndicator* AknSearchFieldIndicatorFactory::CreateIndicatorL()
    {
    if (FeatureManager::FeatureSupported(KFeatureIdAvkonApac))
        {
        return CAknSearchFieldIndicator::NewL();
        }
    else 
        {
        return NULL;
        }
    }

// End of File
