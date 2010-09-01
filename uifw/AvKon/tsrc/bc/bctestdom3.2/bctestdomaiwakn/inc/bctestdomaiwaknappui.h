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
