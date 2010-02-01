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
* Description:  test special_character_table_api
*
*/


#ifndef C_TESTDOMCONTAINER_H
#define C_TESTDOMCONTAINER_H

//  INCLUDES
#include <coecntrl.h>

class CAknAppStyleGrid;
/**
 *  container class
 *  @code
 *  @endcode
 *  @lib  
 *  @since S60 v5.0
 */ 
class CTestDomContainer: public CCoeControl
    {
public:  
    
    /**
     * C++ default constructor
     */
    CTestDomContainer();
    
    /**
     * Destructor
     */
    virtual ~CTestDomContainer();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL( const TRect& aRect );
    
    /**
     * Set component control, and container will own the control
     *
     * @since S60 v5.0
     * @param aControl pointer to a control.
     */      
    void SetControlL( CCoeControl* aControl ); 
    
    /**
     * Delete control
     *
     * @since S60 v5.0
     */     
    void ResetControl();

// from base class CCoeControl

    /**
     * From CCoeControl.
     * Return count of component controls
     *
     * @since S60 v5.0
     * @param aIndex, a index to specify a component control
     * @return  count of component controls.
     */      
    TInt CountComponentControls() const;

    /**
     * From CCoeControl.
     * Return pointer to component control specified by index
     *
     * @since S60 v5.0
     * @param aIndex, a index to specify a component control
     * @return  pointer to component control specified by index.
     */     
    CCoeControl* ComponentControl( TInt aIndex ) const;

private:  

// from base class CCoeControl    

    /**
     * From CCoeControl.
     * Fills the window's rectangle.
     *
     * @since S60 v5.0
     * @param aRect Region of the control to be (re)drawn.
     */    
    void Draw( const TRect& aRect ) const;  
    
private: // data
    
    /**
     * Pointer to component control.
     * own
     */
    CCoeControl* iControl;  
    /**
     * Pointer to component control.
     * own
     */
    CAknAppStyleGrid* iAppStyleGrid;
    
    };    


#endif // C_CTESTDOMCONTAINER_H

// End of File


