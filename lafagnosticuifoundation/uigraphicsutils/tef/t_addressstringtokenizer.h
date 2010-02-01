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

#if (!defined __T_ADDRESSSTRINGTOKENIZER_STEP_H__)
#define __T_ADDRESSSTRINGTOKENIZER_STEP_H__

#include "appfwk_test_AppUi.h"
#include <tuladdressstringtokenizer.h>

_LIT(KT_AddressStringTokenizerStep,"t_addressstringtokenizer");

class CT_AddressStringTokenizerStep : public CTmsTestStep
	{
public:
	CT_AddressStringTokenizerStep();
	~CT_AddressStringTokenizerStep();
	virtual TVerdict doTestStepL();
	void RunTestCases();
	
private:
	void SearchURLsL();
	void SearchEMailAddressesL();
	void SearchPhoneNumbersL();
	void SearchPhoneNumbersWithMin3NosL();
	void SearchPhoneNumbersWithMin8NosL();
	void SearchPhoneNumbersWithMin15NosL();
	void SearchAllL();
	void CheckPositionsL();
	void ParseURIFileL();
	void TestAddressStringTokenizers(CTulAddressStringTokenizer* aAddressStringTokenizer, TFileText& aReader, TDes& aText);
	void TestOOMForAddressStringTokenizer();
	void TestPhoneSearchSeparatorsL();
	};

#endif
