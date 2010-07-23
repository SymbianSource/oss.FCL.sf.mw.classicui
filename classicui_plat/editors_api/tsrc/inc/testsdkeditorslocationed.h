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
* Description:  Test AknLocationEd.H
*
*/

#ifndef C_TESTSDKEDITORSLOCATIONED_H
#define C_TESTSDKEDITORSLOCATIONED_H

//  INCLUDES
#include <aknlocationed.h>

    /**
    *  CTestSDKEditorsLocationEd test class for CAknLocationEditor protected API.
    */
class CTestSDKEditorsLocationEd : public CAknLocationEditor
    {
public:
    
    /**
    *  CAknLocationEditor_ExtensionInterface test function for testing the 
    * Test CAknLocationEditor_ExtensionInterface function
    */
    void* CAknLocationEditor_ExtensionInterface( TUid aInterface );

    };

#endif /*C_TESTSDKEDITORSLOCATIONED_H*/
