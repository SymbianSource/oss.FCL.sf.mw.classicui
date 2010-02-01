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
* Description:  test special_character_table_api
*
*/


#include "testdomcharmap.h"
#include "testdomspecialchartab.h"

 
// ================================ MEMBER FUNCTIONS ================================

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestDomCharMap::CTestDomCharMap()
    {

    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestDomCharMap::~CTestDomCharMap()
    {
    
    }

// ---------------------------------------------------------------------------
// From class CAknCharMap.
// ---------------------------------------------------------------------------
//
 void CTestDomCharMap::DoSizeChanged()
    {
    CAknCharMap::SizeChanged();
    }
    
// ---------------------------------------------------------------------------
// funtion of HandleResourceChangeFrom class CAknCharMap.
// ---------------------------------------------------------------------------
//
 void CTestDomCharMap::DoHandleResourceChange( TInt aType )
    {
    CAknCharMap::HandleResourceChange( aType );
    }

// ---------------------------------------------------------------------------
// funtion of CountComponentControls From class CAknCharMap.
// ---------------------------------------------------------------------------
//    
 TInt CTestDomCharMap::DoCountComponentControls() const
    {
    return CAknCharMap::CountComponentControls();
    }
    
// ---------------------------------------------------------------------------
// funtion of ComponentControl From class CAknCharMap.
// ---------------------------------------------------------------------------
//
 CCoeControl* CTestDomCharMap::DoComponentControl(TInt aIndex) const
    {   
    return CAknCharMap::ComponentControl( aIndex );
    }

// ---------------------------------------------------------------------------
// HandleScrollEventL From class CAknCharMap.
// ---------------------------------------------------------------------------
//      
void CTestDomCharMap::HandleScrollEventL( CEikScrollBar* /*aScrollBar*/, 
    TEikScrollEvent /*aEventType*/)
    {
    
    }    

// ---------------------------------------------------------------------------
// Reserved_2 From class CCoeContrl.
// ---------------------------------------------------------------------------
//     
void CTestDomCharMap::Reserved_2()
    {
    
    }

// ---------------------------------------------------------------------------
// Draw From class CCoeContrl.
//  
// ---------------------------------------------------------------------------
//       
void CTestDomCharMap::Draw(const TRect& /*aRect*/) const
    {
    
    }

// ---------------------------------------------------------------------------
// DrawPictographArea From class MAknPictographDrawerCallBack.
// ---------------------------------------------------------------------------
//   
void CTestDomCharMap::DrawPictographArea()
    {
    
    }


//End of File


