/*
* ============================================================================
*  Name        : bctestaknbattery.h
*  Part of     : BCTest / bctestdomaiwakn       
*  Description : for testing the protected methods of aknbattery.h
*  Version     : %version: 1 % << Don't touch! Updated by Synergy at check-out.
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


#ifndef C_CBCTESTDOMAKNBATTERYPANE_H
#define C_CBCTESTDOMAKNBATTERYPANE_H

#include <aknbattery.h> //for testing protected APIs in aknbattery.h 

/**
 *  test protected APIs in aknbattery.h  .
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib   
 *  @since S60 v5.0
 */   
class CBCTestDomAknBatteryPane : public CAknBatteryPane
    {

public:

    CBCTestDomAknBatteryPane();

    /**
     * Destructor.
     */
     virtual ~CBCTestDomAknBatteryPane();

 

// from base class CAknBatteryPane  
    /**
     * Handles a change to the control's resources of type aType
     * which are shared across the environment.
     *
     * @since S60 v5.0   
     * @param aType Event type.
     */
     IMPORT_C void HandleResourceChange( TInt aType );

    /**
     * From CCoeControl. 
     * Returns number of controls inside the context pane control.
     *
     * @since S60 v5.0   
     * @return Number of component controls.
     */
     IMPORT_C TInt CountComponentControls() const;

    /**
     * From CCoeControl. 
     * Returns a control determined by control id.
     *
     * @since S60 v5.0   
     * @param anIndex Index of a control to be returned.
     * @return Pointer to control
     */
     IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

private:

    /**
     * Handle PointerEvent.This is an empty function.
     *
     * @since S60 v5.0   
     * @param aPointerEvent a TPointerEvent object reference.
     */    
     
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    };

#endif // C_CBCTESTDOMAKNBATTERYPANE_H
