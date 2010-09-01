/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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


#include <akncontext.h>
#include "testsdkcpcontextpane.h"

//==============================CTestSDKCPContextPane========================
//
// ---------------------------------------------------------------------------
// CTestSDKCPContextPane::CTestSDKCPContextPane()
// ---------------------------------------------------------------------------
//
CTestSDKCPContextPane::CTestSDKCPContextPane()
    {
    }

// ---------------------------------------------------------------------------
// CTestSDKCPContextPane::~CTestSDKCPContextPane()
// ---------------------------------------------------------------------------
//
CTestSDKCPContextPane::~CTestSDKCPContextPane()
    {
    }

// ---------------------------------------------------------------------------
// CTestSDKCPContextPane::SizeChanged()
// ---------------------------------------------------------------------------
//
void CTestSDKCPContextPane::SizeChanged()
    {
    CAknContextPane::SizeChanged();
    }

// ---------------------------------------------------------------------------
// CTestSDKCPContextPane::HandleResourceChange()
// ---------------------------------------------------------------------------
//
void CTestSDKCPContextPane::HandleResourceChange(TInt aType)
    {
    CAknContextPane::HandleResourceChange( aType );
    }

// ---------------------------------------------------------------------------
// CTestSDKCPContextPane::CountComponentControls()
// ---------------------------------------------------------------------------
//
TInt CTestSDKCPContextPane::CountComponentControls() const
    {
    return CAknContextPane::CountComponentControls();
    }

// ---------------------------------------------------------------------------
// CTestSDKCPContextPane::ComponentControl()
// ---------------------------------------------------------------------------
//
CCoeControl* CTestSDKCPContextPane::ComponentControl(TInt aIndex) const
    {
    return CAknContextPane::ComponentControl( aIndex );
    }

// ---------------------------------------------------------------------------
// CTestSDKCPContextPane::MopSupplyObject()
// ---------------------------------------------------------------------------
//
TTypeUid::Ptr CTestSDKCPContextPane::MopSupplyObject(TTypeUid aId)
    {
    if(aId.iUid == CAknContextPane::ETypeId)
        {
        return aId.MakePtr(this);
        }

    return CCoeControl::MopSupplyObject(aId);
    }
