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
* Description:  Test EIKBTGRP.H
*
*/


#ifndef C_TESTSDKUIKONCCOBSERVER_H
#define C_TESTSDKUIKONCCOBSERVER_H

//  INCLUDES
#include "testsdkuikoncc.h"
/**
*  class TestSdkUikonccObserver for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CTestSdkUikonccObserver:public CBase, public MEikMenuObserver
{
public:
    /**
    * C++ default constructor.
    */
    CTestSdkUikonccObserver();
    /**
     * Destructor.
    */
    virtual ~CTestSdkUikonccObserver();
public:
    /**
    * SetEmphasis
    * @since S60 5.0
    * @return Symbian OS error code.
    */
    void SetEmphasis(CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/){}
    /**
     * ProcessCommandL
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    void ProcessCommandL(TInt /*aCommandId*/){}

};

#endif /*C_TESTSDKUIKONCCOBSERVER_H*/

//  End of File
