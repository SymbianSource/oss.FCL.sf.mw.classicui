/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test protected for CEikColumnListBox
*
*/

#ifndef C_TESTSDKLISTSCOLUMNLISTBOX_H
#define C_TESTSDKLISTSCOLUMNLISTBOX_H

#include <eikclb.h>

class CTestSDKListsColumnListBox : public CEikColumnListBox
{
public:
    /**
     * C++ default constructor.
     */
	CTestSDKListsColumnListBox();
    /**
     * C++ default destructor.
     */
	virtual ~CTestSDKListsColumnListBox();
	
	//from CEikColumnListBox
    /**
     * This member is internal and not intended for use.
     */
    virtual void CreateItemDrawerL();

    /**
     * Creates a new @c CTextListBoxModel 
     */
    virtual void CreateModelL();
};

#endif /*C_TESTSDKLISTSCOLUMNLISTBOX_H*/
