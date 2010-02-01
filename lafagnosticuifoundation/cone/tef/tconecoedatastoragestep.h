// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @internalComponent - Internal Symbian test code 
*/

#if !defined(__TCONECOEDATASTORAGESTEP_H__)
#define __TCONECOEDATASTORAGESTEP_H__

#include "TConeTestServer.h"
#include <test/testexecutestepbase.h>
#include "appfwk_tmsteststep.h"

class CTConeCoeDataStorageStep : public CTmsTestStep
	{
public:
	CTConeCoeDataStorageStep();
	~CTConeCoeDataStorageStep();
	virtual TVerdict doTestStepL();
	void TestPopulateColorArrayOOML();
	
private:
	void DoOomTestsAfterCorruptingColorListL();
	void SetSystemColorSchemeL(const TDesC8& aBuffer);	
	};

_LIT(KTConeCoeDataStorageStep,"TConeCoeDataStorage");

#endif
