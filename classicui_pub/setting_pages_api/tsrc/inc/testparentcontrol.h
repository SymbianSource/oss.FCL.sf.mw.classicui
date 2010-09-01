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
* Description:  Test setting_pages_api
*
*/

#ifndef C_CTESTAARENTCONTROL_H
#define C_CTESTAARENTCONTROL_H

//  INCLUDES
#include <coecntrl.h>
#include <e32std.h>
#include <testclassassert.h>
#include <stifitemparser.h>

/**
 *  CTestParentControl is used to add button control in its window
 */
class CTestParentControl : public CCoeControl
    {
public:
    /**
     * Two-phased constructor.
     */
    static CTestParentControl* NewL();
    
    /**
     * Destructor.
     */
    ~CTestParentControl();
    /*
     * This function will active gc
     */
    void DoActivateGc();
    /*
     * This function will deactive gc
     */
    void DoDeactivateGc();
private:
    
    /**
     * Constructor.
     */
    CTestParentControl();
    
    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();
    
    /**
     * Receive key events.
     */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
        TEventCode aType);
    
    /**
     * Handle point events.
     */
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
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

#endif /*C_CTESTAARENTCONTROL_H*/

//End file


