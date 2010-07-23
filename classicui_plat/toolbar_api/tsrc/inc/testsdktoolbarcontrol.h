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
* Description:  test AknToolbar.h,akntoolbarextension.h and AknToolbarObserver.h
*
*/


#ifndef C_TESTSDKTOOLBARCONTROL_H
#define C_TESTSDKTOOLBARCONTROL_H

#include <coecntrl.h>
#include <akntoolbar.h>
#include <akntoolbarobserver.h>

/**
 *  CTestToolbarControl is used to add setting page control in its window
 */
class CTestToolbarControl : public CCoeControl,
                            public MAknToolbarObserver
    {
public: //constructor and destructor
    
    
    /**
     * Constructor.
     */
    CTestToolbarControl();
    
    /**
     * Two-phased constructor.
     */
    static CTestToolbarControl* NewL();
    
    /**
     * Destructor.
     */
    ~CTestToolbarControl();

public: // from MAknToolbarObserver class
    
    /**
    * Handles toolbar events for a certain toolbar item.
    * @param aCommand The command ID of some toolbar item.
    */
    virtual void OfferToolbarEventL( TInt aCommand );
    
    /**
     * Should be used to set the properties of some toolbar components 
     * before it is drawn.
     * @param aResourceId The resource ID for particular toolbar
     * @param aToolbar The toolbar object pointer
     */
    void DoDynInitToolbarL( TInt aResourceId, CAknToolbar* aToolbar );
    
    /**
     * from MAknToolbarObserver
     */
    TInt DoMAknToolbarObserver_Reserved_1();

    /**
     * from MAknToolbarObserver
     */
    TInt DoMAknToolbarObserver_Reserved_2();
   
private: // constructor
    
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

class CTestToolBar : public CAknToolbar
    {
    friend class CTestSDKToolbar;
    };

#endif // C_TESTSDKTOOLBARCONTROL_H
