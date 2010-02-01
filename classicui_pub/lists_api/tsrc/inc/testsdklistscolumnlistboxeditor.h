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
* Description:  test protected for CEikColumnListBoxEditor
*
*/

#ifndef C_TESTSDKLISTSCOLUMNLISTBOXEDITOR_H
#define C_TESTSDKLISTSCOLUMNLISTBOXEDITOR_H

#include <eikclb.h>

class CTestSDKListsColumnListBoxEditor : public CEikColumnListBoxEditor
{
public:
    /**
     * C++ default constructor.
     */
	CTestSDKListsColumnListBoxEditor( MListBoxModel* aModel );
    /**
     * C++ default destructor.
     */
	virtual ~CTestSDKListsColumnListBoxEditor();
	
	// for protected
	TInt Column() const;
};

#endif /*C_TESTSDKLISTSCOLUMNLISTBOXEDITOR_H*/
