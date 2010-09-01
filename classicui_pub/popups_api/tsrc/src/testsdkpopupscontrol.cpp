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
* Description:  test aknPopupHeadingPane.h 
*
*/


//  INCLUDES
#include <coecobs.h>
#include <aknpopupheadingpane.h>
#include <barsread.h>
#include <coemain.h>
#include <testsdkpopups.rsg>

#include "testsdkpopupscontrol.h"
// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKPopupsControl::CTestSDKPopupsControl
// -----------------------------------------------------------------------------
CTestSDKPopupsControl::CTestSDKPopupsControl():CCoeControl()
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsControl::~CTestSDKPopupsControl
// -----------------------------------------------------------------------------
CTestSDKPopupsControl::~CTestSDKPopupsControl()
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsControl::ConstructL
// -----------------------------------------------------------------------------
void CTestSDKPopupsControl::ConstructL()
    {
    CreateWindowL();
    ActivateL();
    }
