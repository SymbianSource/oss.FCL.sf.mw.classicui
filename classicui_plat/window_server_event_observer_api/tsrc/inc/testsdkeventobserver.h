/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test AknWsEventObserver.h
*
*/

#include <eikmobs.h>
#include <coecntrl.h>
#include <e32std.h>
#include <aknwseventobserver.h>

#ifndef C_TESTSDKEVENTOBSERVER_H
#define C_TESTSDKEVENTOBSERVER_H

class CTestSDKEventObserver : public CCoeControl,
                              public MAknWsEventObserver
    {
public:
    /**
     * Two-phased constructor.
     */
    static CTestSDKEventObserver* NewL();
    
    /**
     * Destructor.
     */
    ~CTestSDKEventObserver();
    
private:
    
    /**
     * Constructor.
     */
    CTestSDKEventObserver();
    
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
    *  from MAknWsEventObserver
    */
    void  HandleWsEventL ( const TWsEvent &aEvent, CCoeControl *aDestination );

    };


#endif /*C_TESTSDKEVENTOBSERVER_H*/
