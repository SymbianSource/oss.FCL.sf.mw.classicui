/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __LAFTXLBX_H__
#define __LAFTXLBX_H__

class CFont;
class MLafEnv;

/**
 * @since App-Framework_6.1
 * @internal
 * Internal to Symbian
 */
class LafTextListBox
	{
public:
	IMPORT_C static const CFont* Font(const MLafEnv& aLafEnv);
	};


/**
 * @since App-Framework_6.1
 * @internal
 * Internal to Symbian
 */
class LafSnakingTextListBox
	{
public:
	IMPORT_C static const CFont* Font(const MLafEnv& aLafEnv);
	};

#endif
