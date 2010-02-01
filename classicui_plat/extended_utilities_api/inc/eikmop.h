/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef EIKMOP_H
#define EIKMOP_H

#include <coemop.h>
#include <eikmenub.h>
#include <eikcba.h>
#include <eikbtgpc.h>

inline TTypeUid::Ptr SupplyMopObject(TTypeUid aId, CEikButtonGroupContainer* aCba=0, CEikMenuBar* aMenu=0)
	{
	if (aCba)
		{
		if (aId.iUid == CEikCba::ETypeId)
			{
			if (aCba->ButtonGroupType() == CEikButtonGroupContainer::ECba)
				return aId.MakePtr(static_cast<CEikCba*>(aCba->ButtonGroup()));
			else
				return TTypeUid::Null();
			}
		else if (aId.iUid == CEikButtonGroupContainer::ETypeId)
			{
			return aId.MakePtr(aCba);
			}
		}

	if (aMenu)
		{
		if (aId.iUid == CEikMenuBar::ETypeId)
			{
			return aId.MakePtr(aMenu);
			}
		}

	return TTypeUid::Null();
	}

#endif
