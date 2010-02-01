/*
* Copyright (c) 1998-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#include "LAFBTGPC.H"
#include <uikon.hrh>
#include <eikon.hrh>

#include <lafpublc.hrh>

EXPORT_C TInt LafButtonGroupContainer::ButtonType(TInt aUse)
	{
	switch (aUse)
		{
	case SLafButtonGroupContainer::EView:
		return EEikBgToolBar;
	case SLafButtonGroupContainer::EDialog:
		return EEikBgButtonPanel;
	case SLafButtonGroupContainer::EToolbar:
		return EEikBgToolBar;
	case SLafButtonGroupContainer::ECba:
		return EEikBgCba;
	case SLafButtonGroupContainer::EDialogButtons:
		return EEikBgButtonPanel;
	default:
		return EEikBgToolBar;
		}
	}

EXPORT_C TInt LafButtonGroupContainer::Location(TInt aUse)
	{
	SLafButtonGroupContainer::TLocation location;
	switch (aUse)
		{
	case SLafButtonGroupContainer::EView:
		location=SLafButtonGroupContainer::EExternal;
		break;
	case SLafButtonGroupContainer::EDialog:
		location=SLafButtonGroupContainer::EInternal;
		break;
	case SLafButtonGroupContainer::EToolbar:
		location=SLafButtonGroupContainer::EExternal;
		break;
	case SLafButtonGroupContainer::ECba:
		location=SLafButtonGroupContainer::EExternal;
		break;
	case SLafButtonGroupContainer::EDialogButtons:
		location=SLafButtonGroupContainer::EInternal;
		break;
	default:
		location=SLafButtonGroupContainer::EExternal;
		break;
		}
	return location;
	}
