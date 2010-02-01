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

#ifndef __AKNFORMACCESSOR_H__
#define __AKNFORMACCESSOR_H__

#include <coemop.h>

class CTextView;
class CTextLayout;
class CCoeControl;

class MAknFormAccessor
	{
public:
	DECLARE_TYPE_ID(0x101F9A76)

	virtual CTextLayout* GetTextLayout() const = 0;
	virtual CTextView* GetTextView() const = 0;
	virtual CCoeControl* FormClientControl() const = 0;
	};

#endif

