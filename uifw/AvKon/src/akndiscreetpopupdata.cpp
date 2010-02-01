/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Global discreet popup data class.
*
*/

#include "akndiscreetpopupdata.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// TAknDiscreetPopupCancelRequestData::SetStatusHandle
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupCancelRequestData::SetStatusHandle( 
        const TUint& aHandle )
    {
    iStatusHandle = aHandle;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupLaunchData::SetAppUid
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupLaunchData::SetAppUid( const TUid& aAppUid )
    {
    iAppUid = aAppUid;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupLaunchData::SetViewUid
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupLaunchData::SetViewUid( const TUid& aViewUid )
    {
    iViewUid = aViewUid;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupLaunchData::SetAction
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupLaunchData::SetAction( const TBool& aAction )
    {
    iAction = aAction;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupLaunchData::SetPopupId
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupLaunchData::SetPopupId( const TInt& aPopupId )
    {
    iPopupId = aPopupId;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::SetTitleText
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupParamData::SetTitleText( const TDesC& aTitleText )
    {
    iTitleText = aTitleText;
    }

// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::SetBodyText
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupParamData::SetBodyText(  const TDesC& aBodyText )
    {
    iBodyText = aBodyText;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::SetSkinId
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupParamData::SetSkinId( const TAknsItemID& aSkinId )
    {
    iSkinId = aSkinId;
    }

// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::SetBitmapFile
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupParamData::SetBitmapFile( const TDesC& aBitmapFile )
    {
    iBitmapFile = aBitmapFile;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::SetBitmapId
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupParamData::SetBitmapId( const TInt& aBitmapId )
    {
    iBitmapId = aBitmapId;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::SetMaskId
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupParamData::SetMaskId( const TInt& aMaskId )
    {
    iMaskId = aMaskId;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::SetFlags
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupParamData::SetFlags( const TInt& aFlags )
    {
    iFlags = aFlags;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupResourceData::SetResourceFile
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupResourceData::SetResourceFile( const TDesC& aResourceFile )
    {
    iResourceFile = aResourceFile;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupResourceData::SetResourceId
// ---------------------------------------------------------------------------
//
void TAknDiscreetPopupResourceData::SetResourceId( const TInt& aResourceId )
    {
    iResourceId = aResourceId;
    }

