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
* Description:  test aknscbut.h, eiksbfrm.h, eikscbut.h and eikscrlb.h
*
*/


#ifndef C_TESTSDKSCROLLERCONTROL_H
#define C_TESTSDKSCROLLERCONTROL_H

#include <coecntrl.h>
#include <eiksbobs.h>

class CEikScrollBarFrame;

/**
 *  CTestScrollerControl is used to add setting page control in its window
 */
class CTestScrollerControl : public CCoeControl, public MEikScrollBarObserver
    {
public: //constructor and destructor
    
    /**
     * Two-phased constructor.
     */
    static CTestScrollerControl* NewL();
    
    /**
     * Destructor.
     */
    ~CTestScrollerControl();

private: // constructor
    
    /**
     * Constructor.
     */
    CTestScrollerControl();
    
    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();
    
private: // from CCoeControl class
    
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

public: // Functions from MEikScrollBarObserver class

    /**
     * Callback method for scroll bar events
     *
     * Scroll bar observer should implement this method to get scroll bar events.
     *
     * @since S60 0.9
     * @param aScrollBar A pointer to scrollbar which created the event
     * @param aEventType The event occured on the scroll bar
     */
    virtual void HandleScrollEventL( CEikScrollBar* aScrollBar,
            TEikScrollEvent aEventType );

    };


#endif // C_TESTSDKSCROLLERCONTROL_H
