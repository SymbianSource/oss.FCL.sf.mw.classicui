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
* Description:  misc_controls_api
*
*/

#ifndef C_TESTSDKGROUPPROTECTEDCLASS_H
#define C_TESTSDKGROUPPROTECTEDCLASS_H
//  INCLUDES

#include <eikctgrp.h>
#include "testsdkmisccontrols.h"
/**
*  CTestSDKDialogs test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CTestSDKMiscControls;
class CTestControlGroup : public CEikControlGroup
    {
    friend class CTestSDKMiscControls;
public:
    // Constructors
    CTestControlGroup();
    
    };
#endif /*C_TESTSDKGROUPPROTECTEDCLASS_H*/
