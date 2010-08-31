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
* Description:  Test aknnotecontrol.h
*
*/

#ifndef C_TESTSDKNOTESNOTECONTROL_H
#define C_TESTSDKNOTESNOTECONTROL_H

//  INCLUDES
#include <aknnotecontrol.h>

#include "testsdknotes.h"
    /**
    *  CTestSDKNotesNoteControl test class for CAknNoteDialog protected API.
    */
class CTestSDKNotesNoteControl : public CAknNoteControl
    {
public:// Constructors and destructor
    
    /**
    * C++ default constructor.
    */
    CTestSDKNotesNoteControl();

    /**
    *  MopSupplyObject test function for testing the 
    * Test MopSupplyObject function
    */
    TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

    /**
    *  ConstructFromResourceL test function for testing the 
    * Test ConstructFromResourceL function
    */
    void ConstructFromResourceL(TResourceReader& aRes);

    /**
    *  Draw test function for testing the 
    * Test Draw function
    */
    void Draw(const TRect& aRect) const;

    /**
    *  SizeChanged test function for testing the 
    * Test SizeChanged function
    */
    void SizeChanged();

    /**
    *  DoLayout test function for testing the 
    * Test DoLayout function
    */
    TSize MinimumSize();

    /**
    *  CountComponentControls test function for testing the 
    * Test CountComponentControls function
    */
    TInt CountComponentControls() const;

    /**
    *  ComponentControl test function for testing the 
    * Test ComponentControl function
    */
    CCoeControl* ComponentControl(TInt anIndex) const;
    };
#endif /*C_TESTSDKNOTESNOTECONTROL_H*/
