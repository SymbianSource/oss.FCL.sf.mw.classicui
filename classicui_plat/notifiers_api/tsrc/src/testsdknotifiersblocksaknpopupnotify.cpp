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
* Description:  Test AknPopupNotify.h
*
*/

/*
 * Include files
 */
#include <aknpopupnotify.h>

#include "testsdknotifiers.hrh"
#include "testsdknotifiers.h"

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPopNotifyNewLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPopNotifyNewLL( CStifItemParser& /*aItem*/ )
{
    CAknPopupNotify* popupnotify = CAknPopupNotify::NewL();
    CleanupStack::PushL( popupnotify );
    STIF_ASSERT_NOT_NULL( popupnotify );
    CleanupStack::PopAndDestroy( popupnotify );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPopNotifyNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPopNotifyNewLCL( CStifItemParser& /*aItem*/ )
{
    CAknPopupNotify* popupnotify = CAknPopupNotify::NewLC();
    STIF_ASSERT_NOT_NULL( popupnotify );
    CleanupStack::PopAndDestroy( popupnotify );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPopNotifyDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPopNotifyDestructorL( CStifItemParser& /*aItem*/ )
{
    CAknPopupNotify* popupnotify = CAknPopupNotify::NewL();
    CleanupStack::PushL( popupnotify );
    STIF_ASSERT_NOT_NULL( popupnotify );
    CleanupStack::PopAndDestroy( popupnotify );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotifiers::TestNotifiersPopNotifyPopupMessageLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::TestNotifiersPopNotifyPopupMessageLL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupNotify* popupnotify = CAknPopupNotify::NewL();
    CleanupStack::PushL( popupnotify );
    
    TBuf<KBufSize> buf( KTestString );
    popupnotify->PopupMessageL( buf );
    
    CleanupStack::PopAndDestroy( popupnotify );
    return KErrNone;
    }

//End file
