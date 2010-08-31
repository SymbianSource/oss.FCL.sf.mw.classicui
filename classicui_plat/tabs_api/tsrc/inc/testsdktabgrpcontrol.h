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
* Description:  test akntabgrp.h
*
*/


#ifndef C_TESTSDKTABGRPCONTROL_H
#define C_TESTSDKTABGRPCONTROL_H

//  INCLUDES
#include <akntabobserver.h> 
#include <coecntrl.h>

/**
 *  CTestTabsControl is used to add setting page control in its window
 */
class CTestTabsControl : public CCoeControl, public MAknTabObserver
    {
public:
    /**
     * Two-phased constructor.
     */
    static CTestTabsControl* NewL();
    
    /**
     * Destructor.
     */
    ~CTestTabsControl();

    /**
     * from MAknTabObserver.
     */
    void TabChangedL ( TInt aIndex );
    
private:
    
    /**
     * Constructor.
     */
    CTestTabsControl();
    
    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();
    
    /**
     * Receive key events.
     */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    
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

    };

#endif // C_TESTSDKTABGRPCONTROL_H
