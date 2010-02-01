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
* Description:  Control to clear screen
*
*/


#include <AknUtils.h>
#include <AknsSkinInstance.h>
#include <AknsDrawUtils.h>
#include <AknsBasicBackgroundControlContext.h>

#include "akncompaclearer.h"

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaClearer* CAknCompaClearer::NewLC()
{
    CAknCompaClearer* self = new (ELeave) CAknCompaClearer();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaClearer::~CAknCompaClearer()
    {
    delete iBgContext;
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaClearer::Draw(const TRect& /*aRect*/) const
    {
    AknsDrawUtils::Background(AknsUtils::SkinInstance(), iBgContext,
        this, SystemGc(), AknLayout::screen().Rect());
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaClearer::ConstructL()
    {
    CreateWindowL();

    TRect rect = AknLayout::screen().Rect();
    SetRect(rect);

    iBgContext = CAknsBasicBackgroundControlContext::NewL(
        KAknsIIDQsnBgScreen, rect, EFalse); 

    ActivateL();
    DrawNow();
    iCoeEnv->WsSession().Flush();
    }
