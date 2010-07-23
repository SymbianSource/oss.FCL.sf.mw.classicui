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
* Description:  Test api in eikcba.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <testsdkbuttons.rsg>
#include <aknsconstants.h>
#include <avkon.hrh>
#include <avkon.rsg>

#include "testsdkbuttons.hrh"
#include "testsdkbuttons.h"

// CONSTANTS
const TInt KArraySize = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCbaOfferCommandListL
// -----------------------------------------------------------------------------
//

TInt CTestSDKButtons::TestCEikCbaOfferCommandListL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                                    CEikButtonGroupContainer::ECba,
                                                                                    CEikButtonGroupContainer::EHorizontal,
                                                                                    iContainer,
                                                                                    R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    CEikCba *eikcba = static_cast<CEikCba*>( btgroupcontainer->ButtonGroup() );
    RArray<TInt> cmdlist( KArraySize );
    cmdlist.AppendL( EBckBt );
    cmdlist.AppendL( ESingle );
    cmdlist.AppendL( EEnhance );
    TInt err = KErrNone;
    TRAP( err, eikcba->OfferCommandListL( R_ENHANCED_BUTTON ) );// leave directly
    TRAP( err, eikcba->OfferCommandListL( cmdlist ) );// leave directly
    CleanupStack::PopAndDestroy( btgroupcontainer );
    if ( err != KErrNone )
        {
        return KErrNone;
        }
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCbaSetButtonGroupFlagsL
// -----------------------------------------------------------------------------
//

TInt CTestSDKButtons::TestCEikCbaSetButtonGroupFlagsL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                                    CEikButtonGroupContainer::ECba,
                                                                                    CEikButtonGroupContainer::EHorizontal,
                                                                                    iContainer,
                                                                                    R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    CEikCba *eikcba = static_cast<CEikCba*>( btgroupcontainer->ButtonGroup() );
    eikcba->SetButtonGroupFlags( 0 );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCbaIsCommandInGroupL
// -----------------------------------------------------------------------------
//

TInt CTestSDKButtons::TestCEikCbaIsCommandInGroupL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                                    CEikButtonGroupContainer::ECba,
                                                                                    CEikButtonGroupContainer::EHorizontal,
                                                                                    iContainer,
                                                                                    R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    
    CEikCba *eikcba = static_cast<CEikCba*>( btgroupcontainer->ButtonGroup() );
    STIF_ASSERT_FALSE( eikcba->IsCommandInGroup( EBckBt ) );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCbaReplaceCommandL
// -----------------------------------------------------------------------------
//

TInt CTestSDKButtons::TestCEikCbaReplaceCommandL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                                    CEikButtonGroupContainer::ECba,
                                                                                    CEikButtonGroupContainer::EHorizontal,
                                                                                    iContainer,
                                                                                    R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    
    CEikCba *eikcba = static_cast<CEikCba*>( btgroupcontainer->ButtonGroup() );
    eikcba->ReplaceCommand( ELeftBt, R_ENHANCED_BUTTON );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCbaEnableItemSpecificSoftkey
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikCbaEnableItemSpecificSoftkey( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
        CEikButtonGroupContainer::ECba,
        CEikButtonGroupContainer::EHorizontal,
        iContainer,
        R_AVKON_SOFTKEYS_OK_CANCEL );
    CleanupStack::PushL( btgroupcontainer );
    
    CEikCba *eikcba = static_cast<CEikCba*>( btgroupcontainer->ButtonGroup() );
    eikcba->EnableItemSpecificSoftkey( EFalse );
    eikcba->EnableItemSpecificSoftkey( ETrue );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCbaSetSkinBackgroundIdL
// -----------------------------------------------------------------------------
//

TInt CTestSDKButtons::TestCEikCbaSetSkinBackgroundIdL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                                    CEikButtonGroupContainer::ECba,
                                                                                    CEikButtonGroupContainer::EHorizontal,
                                                                                    iContainer,
                                                                                    R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    
    CEikCba *eikcba = static_cast<CEikCba*>( btgroupcontainer->ButtonGroup() );
    eikcba->SetSkinBackgroundId( KAknsIIDQsnBgAreaControlIdle );
    TPointerEvent event;
    eikcba->HandlePointerEventL( event );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikCbaIsEmptyL
// -----------------------------------------------------------------------------
//

TInt CTestSDKButtons::TestCEikCbaIsEmptyL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                                    CEikButtonGroupContainer::ECba,
                                                                                    CEikButtonGroupContainer::EHorizontal,
                                                                                    iContainer,
                                                                                    R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    
    CEikCba *eikcba = static_cast<CEikCba*>( btgroupcontainer->ButtonGroup() );
    eikcba->IsEmpty();
    CleanupStack::PopAndDestroy( btgroupcontainer );
    return KErrNone;
    }


// End of file
