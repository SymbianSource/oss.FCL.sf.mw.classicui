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
// The following test case is used to test writable APIs in REikAppUiSession and to test whether
// uiktestserver process has the capability to access those APIs.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#if !defined(__TCAPABILITY1_H__)
#define __TCAPABILITY1_H__

#include "uiktestserver.h"
#include "appfwk_test_AppUi.h"

//! CTCapability1Step
/** 
  This class is used to test writable apis in REikAppUiSession
*/
class CTCapability1Step : public CTmsTestStep
	{
public:
	CTCapability1Step();
	virtual TVerdict doTestStepL();
	void ExecuteL();
private:
	~CTCapability1Step();
private:
	};

_LIT(KTCapability1Step,"TCapability1");

#endif
