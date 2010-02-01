// Copyright (c) 2000-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __EIKBHELP_H__
#define __EIKBHELP_H__

#include <coemain.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikmischelp.h>
#endif

/** Provides the static functions that control bubble help.

Bubble help is a feature that enables short help messages to be displayed 
for controls in transient windows which pop up close to the control bodies. 

@publishedAll 
@released */
class EikBubbleHelp
	{
public:
	IMPORT_C static void Trigger(const TDesC& aDes,const TRect& aRect,TInt aHandle=-1);
	IMPORT_C static void Cancel();
	IMPORT_C static void CancelTrigger();
	IMPORT_C static TBool IsDisplaying(TInt aHandle);
	};

#endif
