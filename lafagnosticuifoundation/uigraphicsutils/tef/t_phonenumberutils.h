// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code 
*/

#if (!defined __T_PHONENUMBERUTILS_H__)
#define __T_PHONENUMBERUTILS_H__

#include "appfwk_test_AppUi.h"
#include <tulphonenumberutils.h>

const TInt KMaxTestBufferSize = 128;
const TInt KPhoneNoUtilsMaxNumbers = 48; // see hard coded value in ... tulphonenumberutils.cpp

_LIT(KT_PhoneNumberUtilsStep,"t_phonenumberutils");

//PPN == EPlainPhoneNumber
//CCN == EContactCardNumber
//PCN == EPhoneClientNumber
//SMS == ESMSNumber
	
class CT_PhoneNumberUtilsStep : public CTmsTestStep
	{
public:
	CT_PhoneNumberUtilsStep();
	~CT_PhoneNumberUtilsStep();
	virtual TVerdict doTestStepL();
	void RunTestCases();

private:
    void ParsePhoneNumberForPPN();
    void ParsePhoneNumberForCCN();
	void ParsePhoneNumberForSMSNumber();
	void ParsePhoneNumberForPCN();
	};

#endif
