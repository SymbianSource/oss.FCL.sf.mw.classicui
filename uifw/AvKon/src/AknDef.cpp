/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation to get the view ID of the
*                currently active idle view.
*
*/


// INCLUDE FILES
#include "AknDef.h"
#include <vwsdef.h> // TVwsViewId

const TUid KPhoneUid = { 0x100058B3 };
const TUid KPhoneViewUid = { 0x10282D81 };

// -----------------------------------------------------------------------------
// AknDef::GetPhoneIdleViewId()
//
// Constructs and returns the view id either from publish subscribe or from a 
// hardcoded value. This method replaces a constant definition in akndef.h.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt AknDef::GetPhoneIdleViewId(TVwsViewId& aViewId)
    {
    aViewId.iAppUid = KPhoneUid;
    aViewId.iViewUid = KPhoneViewUid;
    return KErrNone;
    }

//  End of File  
