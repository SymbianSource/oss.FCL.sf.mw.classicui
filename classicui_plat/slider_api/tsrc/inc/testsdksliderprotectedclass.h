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
* Description:  slider_api
*
*/

#ifndef C_TESTSDKSLIDERPROTECTEDCLASS_H
#define C_TESTSDKSLIDERPROTECTEDCLASS_H

//  INCLUDES
#include <aknslider.h>
#include "testsdkslider.h"
/**
*  CTestSDKSlider test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CTestSDKSlider;
class CTestAknSlider : public CAknSlider
    {
    friend class CTestSDKSlider;
public:
    // Constructors
     CTestAknSlider();
    // Functions from base classes
     /**
      * MinimumSize test method.
      * @since S60 5.0
      * @param aItem Script line containing parameters.
      * @return Symbian OS error code.
      */
     TSize MinimumSize();
     /**
      * OfferKeyEventL test method.
      * @since S60 5.0
      * @param aItem Script line containing parameters.
      * @return Symbian OS error code.
      */
     TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                      TEventCode aType );
     /**
      * Draw test method.
      * @since S60 5.0
      * @param aItem Script line containing parameters.
      * @return Symbian OS error code.
      */
     void Draw( const TRect& aRect ) const;
     /**
      * Draw test SizeChanged.
      * @since S60 5.0
      * @param aItem Script line containing parameters.
      * @return Symbian OS error code.
      */
     void SizeChanged(); 

    };

#endif //C_TESTSDKSLIDERPROTECTEDCLASS_H

