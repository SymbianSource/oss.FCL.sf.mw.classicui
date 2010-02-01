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
// lafcommn.cpp
//
//


#include <gdi.h>
#include <gulutil.h>
#include "lafmain.h"
#include "lafcommn.h"


void LafCommonUtils::GetRgbDerivedBorderColors(TGulBorder::TColors& aBorderColors,
		TLogicalColor aLogicalBackgroundColor, const MLafEnv& aEnv, const CCoeControl& aBorderedControl)
	{ //static
	TDisplayMode mode=aEnv.DefaultDisplayMode();
	ColorUtils::GetRgbDerivedBorderColors( aBorderColors,
		aEnv.ControlColor(aLogicalBackgroundColor,aBorderedControl), mode );
	}
