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
* Description:  misc_controls_api
*
*/

//  INCLUDES
#include "testsdkcapcsubprotectedclass.h"
// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSubCaptionedControl::Draw
// -----------------------------------------------------------------------------
//
void CTestSubCaptionedControl::Draw(const TRect& /*aRect*/) const
    {

    }
// -----------------------------------------------------------------------------
// CTestSubCaptionedControl::WriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestSubCaptionedControl::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {

    }
// -----------------------------------------------------------------------------
// CTestSubCaptionedControl::MopSupplyObject
// -----------------------------------------------------------------------------
//
TTypeUid::Ptr CTestSubCaptionedControl::MopSupplyObject(TTypeUid aId)
    {
    return ( CEikCaptionedControl::MopSupplyObject( aId ) );
    }
// -----------------------------------------------------------------------------
// CTestSubCaptionedControl::PointerEvent
// -----------------------------------------------------------------------------
//
bool CTestSubCaptionedControl::PointerEvent(CEikCaptionedControl */*aControl*/, const TPointerEvent& /*aPointerEvent*/)
    {
    return ETrue;
    }
