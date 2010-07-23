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
* Description:  Test EIKMFNE.h
*
*/


#include "testsdkeditorsmfne.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditorsMFNE::CTestSDKEditorsMFNE
// -----------------------------------------------------------------------------
CTestSDKEditorsMFNE::CTestSDKEditorsMFNE():CEikMfneField()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsMFNE::~CTestSDKEditorsMFNE
// -----------------------------------------------------------------------------
CTestSDKEditorsMFNE::~CTestSDKEditorsMFNE()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsMFNE::Text
// -----------------------------------------------------------------------------
const TDesC& CTestSDKEditorsMFNE::Text() const
    {
    return KNullDesC16;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsMFNE::MaximumWidthInPixels
// -----------------------------------------------------------------------------
TInt CTestSDKEditorsMFNE::MaximumWidthInPixels( const CFont& /*aFont*/, 
                                                TBool /*aShrinkToMinimumSize*/ )
    {
    return 1;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsMFNE::InputCapabilities
// -----------------------------------------------------------------------------
TCoeInputCapabilities CTestSDKEditorsMFNE::InputCapabilities() const
    {
    TCoeInputCapabilities capa;
    return capa;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsMFNE::HandleLeftOrRightArrow
// -----------------------------------------------------------------------------
void CTestSDKEditorsMFNE::HandleLeftOrRightArrow( TChar aKey, 
                                                  TBool& aDataAltered, 
                                                  TInt& aHighlightIncrement )
    {
    CEikMfneField::HandleLeftOrRightArrow( aKey, aDataAltered, aHighlightIncrement );
    }
