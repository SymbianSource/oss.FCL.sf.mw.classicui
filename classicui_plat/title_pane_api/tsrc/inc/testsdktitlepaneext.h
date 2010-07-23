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



#ifndef C_TESTSDKTITLEPANEEXT_H
#define C_TESTSDKTITLEPANEEXT_H

// FORWARD DECLARATIONS
class CAknTitlePane;

// CLASS DECLARATIONS
class CTestTitlePane : public CAknTitlePane
    {
public: // test protected functions in CAknTitlePane

    /**
     * test SizeChanged
     */
    void DoSizeChanged();

    /**
     * test PositionChanged
     */
    void DoPositionChanged();

    /**
     * test HandleResourceChange
     */
    void DoHandleResourceChange( TInt aType );

    /**
     * test CountComponentControls
     */
    TInt DoCountComponentControls();

    /**
     * test ComponentControl
     */
    CCoeControl* DoComponentControl( TInt aIndex );

    };


#endif // C_TESTSDKTITLEPANEEXT_H
