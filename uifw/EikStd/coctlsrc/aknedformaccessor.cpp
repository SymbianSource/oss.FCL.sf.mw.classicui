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

#include <eikedwin.h>

#include "aknedformaccessor.h"

EXPORT_C CAknEdwinFormAccessor::CAknEdwinFormAccessor(CEikEdwin* aEdwin) :
	iEdwin(aEdwin)
	{
	}

CAknEdwinFormAccessor::~CAknEdwinFormAccessor()
	{
	}

EXPORT_C void CAknEdwinFormAccessor::SetEdwin(CEikEdwin* aEdwin)
	{
	iEdwin = aEdwin;
	}

CTextLayout* CAknEdwinFormAccessor::GetTextLayout() const
	{
	if (iEdwin)
		return iEdwin->TextLayout();
	return NULL;
	}

CTextView* CAknEdwinFormAccessor::GetTextView() const
	{
	if (iEdwin)
		return iEdwin->TextView();
	return NULL;
	}

CCoeControl* CAknEdwinFormAccessor::FormClientControl() const
	{
	return static_cast<CCoeControl*>(iEdwin);
	}
