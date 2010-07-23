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


#ifndef C_TESTSDKTITLEPANECONTROL_H
#define C_TESTSDKTITLEPANECONTROL_H

#include <coecntrl.h>
#include <akntitlepaneobserver.h>

/**
 *  CTestTitlePaneControl is used to add setting page control in its window
 */
class CTestTitlePaneControl : public CCoeControl,
                              public MAknTitlePaneObserver
    {
public:
    /**
     * Two-phased constructor.
     */
    static CTestTitlePaneControl* NewL();
    
    /**
     * Destructor.
     */
    ~CTestTitlePaneControl();

public: // Functions from MAknTitlePaneObserver classes

    /**
    * HandleTitlePaneEventL is used in observers to handle title pane events.
    *
    * @param aEventID TAknTitlePaneEvents type title pane event
    */
    virtual void HandleTitlePaneEventL( TInt aEventID );

private:
    
    /**
     * Constructor.
     */
    CTestTitlePaneControl();
    
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

#endif // C_TESTSDKTITLEPANECONTROL_H
