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
* Description:  Control to clear screen
*
*/


#ifndef __AKNCOMPACLEARER_H__
#define __AKNCOMPACLEARER_H__

#include <coecntrl.h>

class CAknsBasicBackgroundControlContext;

/**
 * Screen clearer UI control. Clear the whole screen (incl. status and
 * control panes) with skin background.
 *
 * @lib compamode.lib
 * @since S60 v5.0
 */
NONSHARABLE_CLASS(CAknCompaClearer) : public CCoeControl
    {
public: // constructors and destructor

    static CAknCompaClearer* NewLC();

    ~CAknCompaClearer();

private: // from CCoeControl

    void Draw(const TRect& aRect) const;

private: // new functions

    void ConstructL();

private: // data

    // Background context
    CAknsBasicBackgroundControlContext* iBgContext;
    };

#endif // __AKNCOMPACLEARER_H__
