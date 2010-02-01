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

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// TAknDiscreetPopupData::TAknDiscreetPopupData
// ---------------------------------------------------------------------------
//
TAknDiscreetPopupData::TAknDiscreetPopupData()
    : iType( EAknPopupTypeUndefined )
    {
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupData::Type
// ---------------------------------------------------------------------------
//
const TInt TAknDiscreetPopupData::Type()
    {
    return iType;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupCancelRequestData::TAknDiscreetPopupCancelRequestData
// ---------------------------------------------------------------------------
//
TAknDiscreetPopupCancelRequestData::TAknDiscreetPopupCancelRequestData()
    {
    iType = EAknPopupTypeCancelRequest;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupCancelRequestData::StatusHandle
// ---------------------------------------------------------------------------
//
const TUint& TAknDiscreetPopupCancelRequestData::StatusHandle()
    {
    return iStatusHandle;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupLaunchData::AppUid
// ---------------------------------------------------------------------------
//
const TUid& TAknDiscreetPopupLaunchData::AppUid()
    {
    return iAppUid;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupLaunchData::ViewUid
// ---------------------------------------------------------------------------
//
const TUid& TAknDiscreetPopupLaunchData::ViewUid()
    {
    return iViewUid;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupLaunchData::Action
// ---------------------------------------------------------------------------
//
const TBool& TAknDiscreetPopupLaunchData::Action()
    {
    return iAction;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupLaunchData::PopupId
// ---------------------------------------------------------------------------
//
const TInt TAknDiscreetPopupLaunchData::PopupId()
    {
    return iPopupId;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::TAknDiscreetPopupParamData
// ---------------------------------------------------------------------------
//
TAknDiscreetPopupParamData::TAknDiscreetPopupParamData()
    {
    iType = EAknPopupTypeParam;
    }

// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::TitleText
// ---------------------------------------------------------------------------
//
const TDesC& TAknDiscreetPopupParamData::TitleText()
    {
    return iTitleText;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::BodyText
// ---------------------------------------------------------------------------
//
const TDesC& TAknDiscreetPopupParamData::BodyText()
    {
    return iBodyText;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::SkinId
// ---------------------------------------------------------------------------
//
const TAknsItemID& TAknDiscreetPopupParamData::SkinId()
    {
    return iSkinId;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::BitmapFile
// ---------------------------------------------------------------------------
//
const TDesC& TAknDiscreetPopupParamData::BitmapFile()
    {
    return iBitmapFile;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::BitmapId
// ---------------------------------------------------------------------------
//
const TInt TAknDiscreetPopupParamData::BitmapId()
    {
    return iBitmapId;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::MaskId
// ---------------------------------------------------------------------------
//
const TInt TAknDiscreetPopupParamData::MaskId()
    {
    return iMaskId;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupParamData::Flags
// ---------------------------------------------------------------------------
//
const TInt TAknDiscreetPopupParamData::Flags()
    {
    return iFlags;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupResourceData::TAknDiscreetPopupResourceData
// ---------------------------------------------------------------------------
//
TAknDiscreetPopupResourceData::TAknDiscreetPopupResourceData()
    {
    iType = EAknPopupTypeResource;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupResourceData::ResourceFile
// ---------------------------------------------------------------------------
//
const TDesC& TAknDiscreetPopupResourceData::ResourceFile()
    {
    return iResourceFile;
    }


// ---------------------------------------------------------------------------
// TAknDiscreetPopupResourceData::ResourceId
// ---------------------------------------------------------------------------
//
const TInt TAknDiscreetPopupResourceData::ResourceId()
    {
    return iResourceId;
    }

// ---------------------------------------------------------------------------
// TAknDiscreetPopupRectData::TAknDiscreetPopupRectData
// ---------------------------------------------------------------------------
//
TAknDiscreetPopupRectData::TAknDiscreetPopupRectData(const TRect& aRect) 
    {
    iType = EAknPopupTypeQueryInUseRect;
    iRect = aRect;
    }

// ---------------------------------------------------------------------------
// TAknDiscreetPopupResourceData::Rect
// ---------------------------------------------------------------------------
//
const TRect TAknDiscreetPopupRectData::Rect()
    {
    return iRect;
    }
