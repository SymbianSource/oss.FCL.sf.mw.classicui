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
* Description:  text aknmarqueecontrol.h
*
*/



#ifndef C_TESTDOMTEXTSCROLLERCONTAINER_H
#define C_TESTDOMTEXTSCROLLERCONTAINER_H


#include <coecntrl.h>

/**
 *  CTestTextScrollerContainer is used to add setting page control in its window
 */
class CTestTextScrollerContainer : public CCoeControl
    {
public:    //constructor and destructor

    /**
     * Constructor.
     */
    CTestTextScrollerContainer();

    /**
     * Two-phased constructor.
     */
    static CTestTextScrollerContainer* NewL();

    /**
     * Destructor.
     */
    ~CTestTextScrollerContainer();

private:    // constructor

    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();

private:    // from CCoeControl class

    /**
     * Receive key events.
     */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

    /**
     * Draw control.
     */
    void Draw(const TRect& aRect) const;

    /**
     * Return number of controls in its window.
     */
    TInt CountComponentControls() const;

    /**
     * Controls in its window.
     */
    CCoeControl* ComponentControl(TInt aIndex) const;

    /**
     * Resize screen.
     */
    void SizeChanged();

public:

    /**
     * ActivateGc
     */
    void DoActivateGc();

    /**
     * DeactivateGc
     */
    void DoDeactivateGc();

    };

#endif // C_TESTDOMTEXTSCROLLERCONTAINER_H
