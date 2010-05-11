/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*
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
