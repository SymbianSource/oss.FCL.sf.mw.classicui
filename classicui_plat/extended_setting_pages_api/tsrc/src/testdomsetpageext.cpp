/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test akntransparentcamerasettingpage.h
*
*/



#include <akntransparentcamerasettingpage.h>

#include "testdomsetpageext.h"


// ============================== MEMBER FUNCTIONS =============================

// -----------------------------------------------------------------------------
// default constructor
// -----------------------------------------------------------------------------
//
CAknTransparentCameraSettingPageExt::
        CAknTransparentCameraSettingPageExt( TInt aResourceID, 
        TInt& aCurrentSelectionIndex, 
        const MDesCArray* aItemArray ) :
        CAknTransparentCameraSettingPage
        ( 
        aResourceID, 
        aCurrentSelectionIndex,
        aItemArray )
        {
        }

// -----------------------------------------------------------------------------
// CAknTransparentCameraSettingPageExt::DoUpdateSettingL
// -----------------------------------------------------------------------------
//
void CAknTransparentCameraSettingPageExt::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CAknTransparentCameraSettingPageExt::DoDynamicInitL
// -----------------------------------------------------------------------------
//
void CAknTransparentCameraSettingPageExt::DoDynamicInitL()
    {
    DynamicInitL();
    }

// -----------------------------------------------------------------------------
// CAknTransparentCameraSettingPageExt::DoSelectCurrentItemL
// -----------------------------------------------------------------------------
//
void CAknTransparentCameraSettingPageExt::DoSelectCurrentItemL()
    {
    SelectCurrentItemL();
    }

// -----------------------------------------------------------------------------
// CAknTransparentCameraSettingPageExt::DoHandleControlEventL
// -----------------------------------------------------------------------------
//
void CAknTransparentCameraSettingPageExt::DoHandleControlEventL( 
        CCoeControl* aControl, TCoeEvent aEventType )
    {
    HandleControlEventL( aControl, aEventType );
    }

// -----------------------------------------------------------------------------
// CAknTransparentCameraSettingPageExt::DoProcessCommandL
// -----------------------------------------------------------------------------
//
void CAknTransparentCameraSettingPageExt::DoProcessCommandL( TInt aCommandId )
    {
    ProcessCommandL( aCommandId );
    }

// -----------------------------------------------------------------------------
// CAknTransparentCameraSettingPageExt::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CAknTransparentCameraSettingPageExt::DoWriteInternalStateL(
        RWriteStream& aWriteStream ) const
    {
    WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CAknTransparentCameraSettingPageExt::DoSizeChanged
// -----------------------------------------------------------------------------
//
void CAknTransparentCameraSettingPageExt::DoSizeChanged()
    {
    SizeChanged();
    }

// -----------------------------------------------------------------------------
// CAknTransparentCameraSettingPageExt::DoDraw
// -----------------------------------------------------------------------------
//
void CAknTransparentCameraSettingPageExt::DoDraw( const TRect& aRect ) const
    {
    Draw( aRect );
    }

