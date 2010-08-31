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
* Description:  Test AknNumed.H
*
*/

#ifndef C_TESTSDKEDITORSNUMED_H
#define C_TESTSDKEDITORSNUMED_H

//  INCLUDES
#include <aknnumed.h>

    /**
    *  CTestSDKEditorsNumed test class for CAknNumericEdwin protected API.
    */
class CTestSDKEditorsNumed : public CAknNumericEdwin
    {
public:
    
    /**
    *  MapKeyEvent test function for testing the 
    * Test MapKeyEvent function
    */
    void MapKeyEvent( TKeyEvent& aKeyEvent, TEventCode& aType, TDigitType aDigitType) const;

    };
#endif /*C_TESTSDKEDITORSNUMED_H*/
