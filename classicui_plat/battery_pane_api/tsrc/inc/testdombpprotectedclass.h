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
* Description:  battery_pane_api
*
*/

#ifndef C_TESTDOMBPPROTECTEDCLASS_H
#define C_TESTDOMBPPROTECTEDCLASS_H

//  INCLUDES
#include <aknbattery.h>
#include "testdombatterypane.h"
    /**
     *  CTestSDKSlider test class for STIF Test Framework TestScripter.
     *  @since S60 5.0
     */
class CTestDOMBatteryPane;

class CTestBatteryPane : public CAknBatteryPane
    {
    friend class CTestDOMBatteryPane;    
public:
    /**
    * Constructor test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    CTestBatteryPane();
    /**
    * HandlePointerEventL test method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    };
#endif /*C_TESTDOMBPPROTECTEDCLASS_H*/
