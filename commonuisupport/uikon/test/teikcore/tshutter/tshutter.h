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
// Tests Memory leak in CEikShutter.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/
#if (!defined __TSHUTTER_H__)
#define __TSHUTTER_H__


#include <test/testexecutestepbase.h>
#include "appfwk_tmsteststep.h"

//! A CTShutter test step class
/**
Tests Memory leak in CEikShutter.
*/
class CTShutter : public CTmsTestStep
	{
public:
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
private:
	void TestShutterL();
	void setupCleanup();
private:
	CTrapCleanup* iTrapCleanup;
	};

_LIT(KTShutter,"TShutter");
#endif

