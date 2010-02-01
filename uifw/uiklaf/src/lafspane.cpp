/*
* Copyright (c) 1997-2000 Nokia Corporation and/or its subsidiary(-ies).
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


#include <uiklaf/private/lafspane.h>

EXPORT_C TBool LafStatusPaneContainer::AllowFading()
	{ // static
	return ETrue;
	}

EXPORT_C CEikStatusPaneBackground* LafStatusPaneContainer::CreateStatusPaneBackgroundL()
    {
    return NULL;
    }
