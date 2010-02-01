// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#if (!defined __TGlay_STEP_H__)
#define __TGlay_STEP_H__
#include "TGridTestServer.h"
#include "grdstd.h"
#include "appfwk_tmsteststep.h"
//! A CTestStep derived class 
/*!
	Incorporates the grid layout tests.\n
*/
class CTGlayStep : public CTmsTestStep
	{
public:
	CTGlayStep();
	~CTGlayStep();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void Test1L();
	void Test2L();
private:
	void ConstructGridLayLC(CGridLay*& aGridLay);
	};

_LIT(KTGlayStep,"TGlay");
#endif

