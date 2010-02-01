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
* Description:  smiley utility class
*
*/

#ifndef C_SMILEYCUSTOMWRAP_H
#define C_SMILEYCUSTOMWRAP_H

#include <e32base.h>
#include <eiklay.h>

NONSHARABLE_CLASS( CSmileyCustomWrap ): public CBase, public MFormCustomWrap
	{	
public:
	CSmileyCustomWrap();
    ~CSmileyCustomWrap();
	
public: 
// From MFormCustomWrap
    TUint LineBreakClass( TUint aCode, TUint& aRangeStart, 
        TUint& aRangeEnd ) const;
    
    TBool LineBreakPossible( TUint aPrevClass, TUint aNextClass,
        TBool aHaveSpaces ) const;
    
private: //data
    TBool iPrevCodeIsSmiley;
    TBool iPlaceHolder;
    TAvkonEditorCustomWrap iAvkonCustomWrap;
	};

#endif C_SMILEYCUSTOMWRAP_H
