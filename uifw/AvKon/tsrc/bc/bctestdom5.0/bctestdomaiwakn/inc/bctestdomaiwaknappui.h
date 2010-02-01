/*
* ============================================================================
*  Name        : bctestdomaiwaknappui.h
*  Part of     : BCTest / bctestdomaiwakn       
*  Description : declaration of appui.
*  Version     : %version: 3 % << Don't touch! Updated by Synergy at check-out.
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

#ifndef C_CBCTESTDOMAIWAKNAPPUI_H
#define C_CBCTESTDOMAIWAKNAPPUI_H

#include <aknviewappui.h>

class CBCTestDomAiwAknView;
class CBCTestDomAknAnimatedView;
class CBCTestUtil;


/**
 *  Application UI class
 *  
 *
 *  @code
 *   
 *  @endcode
 *
 *  @lib bctestutil.lib
 *  @since S60 v5.0
 */ 
class CBCTestDomAiwAknAppUi : public CAknViewAppUi
    {
public:  

    /**
     * constructor
     */      
    CBCTestDomAiwAknAppUi();

    /**
     * symbian 2nd constructor
     */
     void ConstructL();

    /**
     * destructor
     */
     virtual ~CBCTestDomAiwAknAppUi();

private:

// from base class CEikAppUi
    /**
     * From CEikAppUi.
     * HandleCommandL()
     *
     * @since S60 v5.0
     * @param aCommand  Command Id.
     */
    void HandleCommandL( TInt aCommand );

private: // data
      
    /**
     * pointor to the view.
     * own
     */
     CBCTestDomAiwAknView*  iView;

    /**
     * iAnimView, The Animated view .
     * own.
     */
     CBCTestDomAknAnimatedView* iAnimView;

	/**
     * pointor to the BC Test framework utility.
     * own
     */
     CBCTestUtil*  iTestUtil;
    };

#endif // C_CBCTESTDOMAIWAKNAPPUI_H

// End of File
