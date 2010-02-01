/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*
*/

// AKNDLGSHUT.CPP
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

//
// AknDialogShutter
//

#include "AknDlgShut.h"
#include <eikenv.h>
#include <eikappui.h>

class CKludgeScheduler : public CBaActiveScheduler
	{
public:
	inline TInt PublicLevel() const { return Level(); }
	};

TInt AknDialogShutter::StartLevel()
	{
	return ((CKludgeScheduler*)CActiveScheduler::Current())->PublicLevel();
	}

EXPORT_C void AknDialogShutter::ShutDialogsL(CEikonEnv& aEikEnv)
	{
	CEikAppUi* appUi=aEikEnv.EikAppUi();

	for (TInt attempt=0; attempt<50; attempt++)		// maximum of 50 attempts to close dialogs
		{
		TInt startLevel=StartLevel();

		if (appUi->IsDisplayingMenuOrDialog())
			{
			TKeyEvent key;
			key.iCode=EKeyEscape;
			key.iModifiers=0;
            key.iRepeats = 0;
            key.iScanCode = EStdKeyNull;
			aEikEnv.SimulateKeyEventL(key, EEventKey);
			}
		else
			{
			break;							// stop if there are no more dialogs
			}

		if (StartLevel() > startLevel)
			break;							// stop if a confirmation dialog has popped up
		}
	}

