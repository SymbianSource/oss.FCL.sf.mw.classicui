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
* Description:  test aknstyluspopupmenu.h
*
*/


#ifndef C_TESTSDKMENUOBSERVER_H
#define C_TESTSDKMENUOBSERVER_H

#include <eikmobs.h>
#include <coecntrl.h>
#include <e32std.h>

class CTestSDKMenuObserver : public CCoeControl,
                             public MEikMenuObserver
    {
public:// Constructors and destructor
    
public:
    /**
     * Two-phased constructor.
     */
    static CTestSDKMenuObserver* NewL();
    
    /**
     * Destructor.
     */
    ~CTestSDKMenuObserver();
    
private:
    
    /**
     * Constructor.
     */
    CTestSDKMenuObserver();
    
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
    
    /**
    * from MEikMenuObserver
    */
    void SetEmphasis( CCoeControl *aMenuControl, TBool aEmphasis );
    
    /**
    * from MEikMenuObserver
    */
    void ProcessCommandL( TInt aCommandId );
    
    };

#endif /*C_TESTSDKMENUOBSERVER_H*/
