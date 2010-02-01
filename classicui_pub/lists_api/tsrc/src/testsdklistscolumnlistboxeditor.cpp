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
* Description:  
*
*/

#include "testsdklistscolumnlistboxeditor.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKListsColumnListBoxEditor::CTestSDKListsColumnListBoxEditor()
// -----------------------------------------------------------------------------
//
CTestSDKListsColumnListBoxEditor::CTestSDKListsColumnListBoxEditor( MListBoxModel* aModel ) 
            : CEikColumnListBoxEditor( aModel )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKListsColumnListBoxEditor::~CTestSDKListsColumnListBoxEditor()
// -----------------------------------------------------------------------------
//
CTestSDKListsColumnListBoxEditor::~CTestSDKListsColumnListBoxEditor()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKListsColumnListBoxEditor::Column()
// -----------------------------------------------------------------------------
//
TInt CTestSDKListsColumnListBoxEditor::Column() const
    {
    return CEikColumnListBoxEditor::Column();
    }
