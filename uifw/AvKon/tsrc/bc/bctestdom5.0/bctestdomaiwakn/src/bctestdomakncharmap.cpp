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
* Description:  for indirectly testing APIs in akncharmap.h
*
*/


#include "bctestdomakncharmap.h"

 
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomCAknCharMap::CBCTestDomCAknCharMap()
    {

    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestDomCAknCharMap::~CBCTestDomCAknCharMap()
    {
    
    }

// ---------------------------------------------------------------------------
// From class CAknCharMap.
//  
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestDomCAknCharMap::SizeChanged()
    {
    CAknCharMap::SizeChanged();
    }
    
// ---------------------------------------------------------------------------
// From class CAknCharMap.
//  
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestDomCAknCharMap::HandleResourceChange( TInt aType )
    {
    CAknCharMap::HandleResourceChange( aType );
    }

// ---------------------------------------------------------------------------
// From class CAknCharMap.
//  
// ---------------------------------------------------------------------------
//    
EXPORT_C TInt CBCTestDomCAknCharMap::CountComponentControls() const
    {
    return CAknCharMap::CountComponentControls();
    }
    
// ---------------------------------------------------------------------------
// From class CAknCharMap.
//  
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CBCTestDomCAknCharMap::
    ComponentControl(TInt aIndex) const
	{	
	return CAknCharMap::ComponentControl( aIndex );    
    }

// ---------------------------------------------------------------------------
// From class CAknCharMap.
//  
// ---------------------------------------------------------------------------
//      
void CBCTestDomCAknCharMap::HandleScrollEventL( CEikScrollBar* /*aScrollBar*/, 
    TEikScrollEvent /*aEventType*/)
    {
    
    }    

// ---------------------------------------------------------------------------
// From class CCoeContrl.
//  
// ---------------------------------------------------------------------------
//     
void CBCTestDomCAknCharMap::Reserved_2()
    {
    
    }

// ---------------------------------------------------------------------------
// From class CCoeContrl.
//  
// ---------------------------------------------------------------------------
//       
void CBCTestDomCAknCharMap::Draw(const TRect& /*aRect*/) const
    {
    
    }

// ---------------------------------------------------------------------------
// From class MAknPictographDrawerCallBack.
//  
// ---------------------------------------------------------------------------
//   
void CBCTestDomCAknCharMap::DrawPictographArea()
    {
    
    }




