/*
* Copyright (c) 1998 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikbtgrp.h>
#include <coecntrl.h>
#include <eikcmbut.h>

EXPORT_C void MEikButtonGroup::AnimateCommand(TInt aCommandId)
	{
	CEikCommandButton* button=GroupControlAsButton(aCommandId);
	if (button)
		button->Animate();
	}

void MEikButtonGroup::Release()
	{
	CCoeControl* ctrl=AsControl();
	if (ctrl)
		delete ctrl;
	}

EXPORT_C void MEikButtonGroup::Reserved_1()
	{
	}
