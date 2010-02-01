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
* Description:  Control to fill sides of compatibility mode window
*
*/


#ifndef __AKNCOMPASIDE_H__
#define __AKNCOMPASIDE_H__

#include <coecntrl.h>

class CAknsBasicBackgroundControlContext;

/**
 * Compatibility mode side control
 *
 * @lib compamode.lib
 * @since S60 v5.0
 */
NONSHARABLE_CLASS(CAknCompaSide) : public CCoeControl
    {
public: // types
    enum TSide
        {
        ELeftSide,
        ERightSide,
        ENumSides
        };

public: // constructors and destructor

    static CAknCompaSide* NewL();

    ~CAknCompaSide();
    
    void SetBackground(TPoint aOrigin);

private: // from CCoeControl

    void Draw(const TRect& aRect) const;

private: // new functions

    void ConstructL();

private: // data
    
    // Background context
    CAknsBasicBackgroundControlContext* iBgContext;
    };

#endif // __AKNCOMPASIDE_H__
