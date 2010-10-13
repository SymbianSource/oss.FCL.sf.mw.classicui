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
* Description:  smiely engine class
*
*/

#include "smileymanager.h"
#include "smileycustomwrap.h"

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CSmileyCustomWrap::CSmileyCustomWrap
// ---------------------------------------------------------------------------
//
CSmileyCustomWrap::CSmileyCustomWrap()
    {
    }

// ---------------------------------------------------------------------------
// CSmileyCustomWrap::CSmileyCustomWrap
// ---------------------------------------------------------------------------
//
CSmileyCustomWrap::~CSmileyCustomWrap()
    {    
    }

// ---------------------------------------------------------------------------
// CSmileyCustomWrap::LineBreakClass
// ---------------------------------------------------------------------------
//
TUint CSmileyCustomWrap::LineBreakClass( TUint aCode, TUint& aRangeStart, 
    TUint& aRangeEnd) const
    {
    TUint breakClass( iAvkonCustomWrap.LineBreakClass( aCode, aRangeStart, 
        aRangeEnd ) );
    CSmileyCustomWrap* customWrap( const_cast<CSmileyCustomWrap*>( this ) );
    if ( CSmileyManager::IsSmileyCode( aCode ) )
        {
        breakClass = MTmCustom::EOpLineBreakClass;
        customWrap->iPrevCodeIsSmiley = !iPlaceHolder;
        customWrap->iPlaceHolder = EFalse;
        }
    else if ( ( iPrevCodeIsSmiley || iPlaceHolder ) && aCode == CSmileyManager::KCompensateChar )
        {
        breakClass = MTmCustom::EClLineBreakClass;
        customWrap->iPrevCodeIsSmiley = EFalse;
        } 
    else if ( aCode == CSmileyManager::KPlaceHolder )        
        { 
        breakClass = MTmCustom::EB2LineBreakClass;
        customWrap->iPlaceHolder = ETrue;
        }
    return breakClass;
    }

TBool CSmileyCustomWrap::LineBreakPossible( TUint aPrevClass, TUint aNextClass,
    TBool aHaveSpaces ) const
    {
    return iAvkonCustomWrap.LineBreakPossible( aPrevClass, aNextClass, aHaveSpaces );
    }
