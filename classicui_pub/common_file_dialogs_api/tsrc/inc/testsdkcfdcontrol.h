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
* Description:  Test CAknMemorySelectionSettingPage.h
 *
*/


#ifndef C_TESTSDKCFDCONTROL_H
#define C_TESTSDKCFDCONTROL_H

//  INCLUDES
#include <coecntrl.h>
#include <e32std.h>
#include <testclassassert.h>
#include <stifitemparser.h>
#include <caknmemoryselectionsettingpage.h>
#include <maknmemoryselectionobserver.h>

/**
 *  CTestControl is used to add setting page control in its window
 */
class CTestControl : public CCoeControl, public MAknMemorySelectionObserver
    {
public:
    /**
     * Two-phased constructor.
     */
    static CTestControl* NewL();
    
    /**
     * Destructor.
     */
    ~CTestControl();
    
    /**
     * Public function to test setting page RunDL function.
     */
    TInt TestSettingPageRunLDL( CStifItemParser& aItem );
    
    /**
     * from MAknMemorySelectionObserver.
     */
    TBool OkToExitL( CAknMemorySelectionDialog::TMemory aMemory );
    
private:
    
    /**
     * Constructor.
     */
    CTestControl();
    
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
    
private:
    //data
    CAknMemorySelectionSettingPage* iSettingPage;
    };

#endif /*C_TESTSDKCFDCONTROL_H*/
