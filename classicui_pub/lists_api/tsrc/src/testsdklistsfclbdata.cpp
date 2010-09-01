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
* Description:  
*
*/

#include "testsdklistsfclbdata.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKListsFCLBData::CTestSDKListsFCLBData()
// -----------------------------------------------------------------------------
//
CTestSDKListsFCLBData::CTestSDKListsFCLBData()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKListsFCLBData::ConstructLD()
// -----------------------------------------------------------------------------
//
void CTestSDKListsFCLBData::ConstructLD()
    {
    CFormattedCellListBoxData::ConstructLD();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsFCLBData::ConstructLD( aAnimationIID )
// -----------------------------------------------------------------------------
//
void CTestSDKListsFCLBData::ConstructLD(const TAknsItemID& aAnimationIID)
    {
    CFormattedCellListBoxData::ConstructLD( aAnimationIID );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsFCLBData::DrawFormatted()
// -----------------------------------------------------------------------------
//
void CTestSDKListsFCLBData::DrawFormatted(TListItemProperties aProperties,
                                          CWindowGc& aGc,
                                          const TDesC* aText,
                                          const TRect& aRect,
                                          TBool aHighlight,
                                          const TColors& aColors) const
    {
    CFormattedCellListBoxData::DrawFormatted( aProperties, aGc, aText, aRect,
                                              aHighlight, aColors);
    }
