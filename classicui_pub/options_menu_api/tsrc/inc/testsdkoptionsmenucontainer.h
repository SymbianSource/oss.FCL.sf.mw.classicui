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
* Description:  test options_menu_api
 *
*/


#ifndef C_TESTSDKOPTIONSMENUCONTAINER_H
#define C_TESTSDKOPTIONSMENUCONTAINER_H

//  INCLUDES
#include <coecntrl.h>
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>


/**
 *  Ctestsdkoptionsmenu test class for STIF Test Framework TestScripter.
 *  @since S60 5.0
 */
class CTestSDKOptionsMenuContainer: public CCoeControl 
    {
public: // constructor and destructor
    /**
     * New a CTestSDKOptionsMenuContainer object
     */
    static CTestSDKOptionsMenuContainer* NewL( const TRect& aRect );
    
    /**
     * Destructor
     */
    virtual ~CTestSDKOptionsMenuContainer();
    
    
public: // new functions
    
    /**
    * Set component control, and container will own the control
    * @param aControl pointer to a control.
    */
    void SetControlL( CCoeControl* aControl ); 
    
    /**
     * Delete control
     */
    void ResetControl();
    
    /*
     * From CCoeControl
     */
    void ActivateGc();
    
    /*
     * From CCoeControl
     */
    void DeactivateGc();

private:
    /**
     * Return count of component controls
     */
    TInt CountComponentControls() const;
    
    /**
     * Return pointer to component control specified by index
     * @param aIndex, a index to specify a component control
     */
    CCoeControl* ComponentControl( TInt aIndex ) const;
    
    /**
     * C++ default constructor
     */
    CTestSDKOptionsMenuContainer();
    /**
     * Symbian 2nd constructor
     */
    void ConstructL( const TRect& aRect );
    
    /**
    * From CCoeControl, Draw.
    * Fills the window's rectangle.
    * @param aRect Region of the control to be (re)drawn.
    */
    void Draw( const TRect& aRect ) const;
    
private: // data
    
    /**
     * Pointer to component control.
     * Not own
     */
    CCoeControl* iControl;
    
    };

#endif // C_TESTSDKOPTIONSMENUCONTAINER_H

// End of File
