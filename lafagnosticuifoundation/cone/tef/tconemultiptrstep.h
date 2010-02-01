// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef TCONEMULTIPTRSTEP_H_
#define TCONEMULTIPTRSTEP_H_

#include <coemain.h>
#include <coecntrl.h>
#include <coeaui.h>
#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"
#include "tmultiptrtestcontrol.h"
#include "tconemultiptrtestappui.h"
#include "tconemultiptrconst.h"


// TConeMultiPtr Test Step Name.\n
_LIT(KTConeMultiPtrStep,"TConeMultiPtr");


class CTConeMultiPtrStep : public CTmsTestStep
	{
public:
	CTConeMultiPtrStep();
	~CTConeMultiPtrStep();
	virtual TVerdict doTestStepL();
	TVerdict doTestStepPreambleL();
	TVerdict doTestStepPostambleL();
	
	void ConstructConeMultiPtrAppL(CCoeEnv* aCoe);
	
public:
	TTimeIntervalMicroSeconds32 iDoubleClickMaxInterval;
	TInt iDoubleClickMaxDistance;
	};


#endif /*TCONEMULTIPTRSTEP_H_*/
