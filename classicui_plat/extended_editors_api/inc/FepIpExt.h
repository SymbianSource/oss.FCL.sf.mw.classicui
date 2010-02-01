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

 
#if !defined(__FEPIPEXT_H__)
#define __FEPIPEXT_H__

//
//	class MCoeFepSpecificExtensions
//
class TCoeInputCapabilities::MCoeFepSpecificExtensions
	{
public:
	virtual TBool IsValidCharacter(TInt aChar) = 0;
private:
	virtual void MCoeFepSpecificExtensions_Reserved_1() = 0;
	virtual void MCoeFepSpecificExtensions_Reserved_2() = 0;
	};



#endif





