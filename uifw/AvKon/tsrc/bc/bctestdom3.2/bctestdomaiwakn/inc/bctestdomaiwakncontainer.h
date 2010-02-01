/*
* ============================================================================
*  Name        : bctestdomaiwakncontainer.h
*  Part of     : BCTest / bctestdomaiwakn       
*  Description : declaration of container.
*  Version     : %version: 2 % << Don't touch! Updated by Synergy at check-out.
*
*  Copyright © 2007.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.2
*/

#ifndef C_CBCTESTDOMAIWAKNCONTAINER_H
#define C_CBCTESTDOMAIWAKNCONTAINER_H

#include <coecntrl.h>

class CAknAppStyleGrid;
/**
 *  container class
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib  
 *  @since S60 v5.0
 */ 
class CBCTestDomAiwAknContainer: public CCoeControl
    {
public:  
    
    /**
     * C++ default constructor
     */
    CBCTestDomAiwAknContainer();
    
    /**
     * Destructor
     */
    virtual ~CBCTestDomAiwAknContainer();
    
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
    void SetControl( CCoeControl* aControl ); 
    
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
    
    CAknAppStyleGrid* iAppStyleGrid;
    };    

#endif // C_CBCTESTDOMAIWAKNCONTAINER_H