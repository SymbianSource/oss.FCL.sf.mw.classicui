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
* Description:  declaration of appui.
*
*/


#ifndef C_BCTESTDOMAPOPUPAPPUI_H
#define C_BCTESTDOMAPOPUPAPPUI_H

#include <aknviewappui.h>

class CBCDomainTestPopupView;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCDomainTestPopupAppUi : public CAknViewAppUi
    {
public: 
// Constructors and destructor

    /**
    * constructor
    */
    CBCDomainTestPopupAppUi();
 
    /**
     * symbian 2nd constructor
     */
    void ConstructL();

    /**
     * destructor
     */
    virtual ~CBCDomainTestPopupAppUi();

private:

    /**
     * From CEikAppUi
     */
    void HandleCommandL( TInt aCommand );

 private:
  // data
        
    /**
     * pointor to the view.
     * own
     */
    CBCDomainTestPopupView*  iView;
    
    /**
     * pointor to the BC Test framework utility.
     * own
     */
    CBCTestUtil*  iTestUtil;
    
    };

#endif // C_BCTESTDOMAPOPUPAPPUI_H

// End of File
