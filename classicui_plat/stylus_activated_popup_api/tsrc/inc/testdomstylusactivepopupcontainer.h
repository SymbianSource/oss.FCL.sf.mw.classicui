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
* Description:  container with window for test
*
*/


#ifndef C_TESTDOMSTYLUSACTIVEPOPUPCONTAINER_H
#define C_TESTDOMSTYLUSACTIVEPOPUPCONTAINER_H

// INCLUDE FILES
#include <coecntrl.h>

/*
 * container class with window for testing
 */
class CTestStyleActivePopUpContainer : public CCoeControl
    {
public:
    /*
     * Static NewL function to build this object
     * */
    static CTestStyleActivePopUpContainer* NewL( TRect& aRect );
    /*
     * Deconstructor
     * */
    ~CTestStyleActivePopUpContainer();
    
    /*
     * Set control in this container that has window
     * */
    void SetComponentControlL( CCoeControl* aControl );
    
    /*
     * Return the control'rect
     * */
    TRect ControlRect();
    
    /*
     * Active Gc
     * */
    void ActiveControlGc();
    
    /*
     * Deactive Gc
     * */
    void DeActiveControlGc();
private:
    /*
     * Constructor
     * */
    CTestStyleActivePopUpContainer();
    /*
     * Two-phrase construct
     * */
    void ConstructL( TRect& aRect );
    
    /*
     * for components
     * */
    TInt CountComponentControls() const;
    
    /*
     * for components
     * */
    CCoeControl *ComponentControl( TInt aIndex ) const;
    
    /*
     * Draw control
     * */
    void Draw(const TRect& aRect) const;

    
private:
    // Not own
    CCoeControl* iControl;
    /*
     * The rect of control
     * Own
     * */
    TRect iRect;
    };

#endif /*C_TESTDOMSTYLUSACTIVEPOPUPCONTAINER_H*/

// End of file


