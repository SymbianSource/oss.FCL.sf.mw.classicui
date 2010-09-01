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

#ifdef RD_IDLE_SEPARATION
#include <e32property.h>
#include <activeidle2domainpskeys.h>
#endif

const TInt KPhoneUid( 0x100058B3 );
const TInt KActiveIdle2Uid( 0x102750F0 );

// -----------------------------------------------------------------------------
// AknDef::GetPhoneIdleViewId()
//
// Constructs and returns the view id either from publish subscribe or from a 
// hardcoded value. This method replaces a constant definition in akndef.h.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt AknDef::GetPhoneIdleViewId(TVwsViewId& aViewId)
    {
    TInt uidValue = NULL;
    TInt retVal = KErrNone;

#ifdef RD_IDLE_SEPARATION
    retVal = RProperty::Get( KPSUidAiInformation, KActiveIdleUid, uidValue );
    if(retVal == KErrNotFound)
        {
        retVal = KErrNone;
        uidValue = KPhoneUid;
        }
#else
    uidValue = KPhoneUid;  // Was defined as KAknPhoneIdleViewId in akndef.h.
#endif // RD_IDLE_SEPARATION

    if(retVal == KErrNone)
        {
        aViewId = TVwsViewId(TUid::Uid(uidValue), TUid::Uid(uidValue));
        }
        
#ifdef RD_BOOT_CUSTOMIZABLE_AI

    // ActiveIdle2 is view-based, so this is a temporary fix
    // in order to be able to activate idle from app shell with menu-key,
    // until a proper way for view uid acquisition is made.
    
    TInt pluginRangeStart;
    TInt pluginRangeEnd;
    
    RProperty::Get( KPSUidAiInformation, KAIActivePluginRangeStart, pluginRangeStart );
    RProperty::Get( KPSUidAiInformation, KAIActivePluginRangeEnd, pluginRangeEnd );
    
    if ( uidValue >= pluginRangeStart && uidValue <= pluginRangeEnd && pluginRangeEnd )
        {
        uidValue = KActiveIdle2Uid;
        aViewId.iAppUid = TUid::Uid( uidValue );
        }
    else if ( uidValue >= pluginRangeStart ) // end UID may not be defined
        {
        uidValue = KActiveIdle2Uid;
        aViewId.iAppUid = TUid::Uid( uidValue );
        }
    
    if ( uidValue == KActiveIdle2Uid )
        {
        aViewId.iViewUid = TUid::Uid(1);
        }
        
#endif // RD_BOOT_CUSTOMIZABLE_AI

    return retVal; 
    }

//  End of File  
