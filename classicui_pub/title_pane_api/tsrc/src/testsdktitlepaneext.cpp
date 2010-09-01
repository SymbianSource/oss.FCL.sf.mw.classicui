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
* Description:  test akntitle.h
*
*/



#include <akntitle.h>

#include "testsdktitlepaneext.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestTitlePane::DoSizeChanged
// -----------------------------------------------------------------------------
//
void CTestTitlePane::DoSizeChanged() 
    {
    SizeChanged();
    }

// -----------------------------------------------------------------------------
// CTestTitlePane::DoPositionChanged
// -----------------------------------------------------------------------------
//
void CTestTitlePane::DoPositionChanged() 
    {
    PositionChanged();
    }

// -----------------------------------------------------------------------------
// CTestTitlePane::DoHandleResourceChange
// -----------------------------------------------------------------------------
//
void CTestTitlePane::DoHandleResourceChange( TInt aType ) 
    {
    HandleResourceChange( aType );
    }

// -----------------------------------------------------------------------------
// CTestTitlePane::DoCountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestTitlePane::DoCountComponentControls() 
    {
    return CountComponentControls();
    }

// -----------------------------------------------------------------------------
// CTestTitlePane::DoComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestTitlePane::DoComponentControl( TInt aIndex ) 
    {
    CCoeControl* componentControl = NULL;
    componentControl = ComponentControl( aIndex );
    return componentControl;
    }

