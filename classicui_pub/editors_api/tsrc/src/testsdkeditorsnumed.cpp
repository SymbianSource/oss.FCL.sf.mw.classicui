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
* Description:  Test AknNumed.h
*
*/


#include "testsdkeditorsnumed.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditorsNumed::TestNSNSIHandleResourceChangeL
// -----------------------------------------------------------------------------
void CTestSDKEditorsNumed::MapKeyEvent( TKeyEvent& aKeyEvent, TEventCode& aType, 
                                        TDigitType aDigitType) const
    {
    CAknNumericEdwin::MapKeyEvent( aKeyEvent, aType, aDigitType );
    
    }
