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
* Description:  Test AknButton.h
 *
*/


#ifndef C_TESTAARENTCONTROL_H
#define C_TESTAARENTCONTROL_H

//  INCLUDES
#include <coecntrl.h>
#include <e32std.h>
#include <testclassassert.h>
#include <stifitemparser.h>
#include <aknbutton.h>

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
    
    /**
     * Public function to test ActivateL() function.
     */
    TInt TestAknButtonActivateL();
    /**
     * Public function to test SetMargins() function.
     */
    TInt TestAknButtonSetMarginsL();
    /**
     * Public function to test SizeChanged() function.
     */
    TInt TestAknButtonSizeChangedL();
    /**
     * Public function to test PrepareForFocusLossL() function.
     */
    TInt TestAknButtonPrepareForFocusLossLL();
    /**
     * Public function to test ShowHelpL() function.
     */
    TInt TestAknButtonShowHelpLL();
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
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    
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
    
private:
    };

#endif /*CTESTAARENTCONTROL_H_*/

//End file


