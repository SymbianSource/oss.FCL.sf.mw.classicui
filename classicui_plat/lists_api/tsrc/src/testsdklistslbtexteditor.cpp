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
* Description:  Test eiklbed.H
*
*/

#include "testsdklistslbtexteditor.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKListsLBTextEditor::CTestSDKListsLBTextEditor
// -----------------------------------------------------------------------------
//
CTestSDKListsLBTextEditor::CTestSDKListsLBTextEditor(MListBoxModel* aModel) : CEikListBoxTextEditor( aModel )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKListsLBTextEditor::CTestSDKListsLBTextEditor
// -----------------------------------------------------------------------------
//
void CTestSDKListsLBTextEditor::Release()
    {
    CEikListBoxTextEditor::Release();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsLBTextEditor::CTestSDKListsLBTextEditor
// -----------------------------------------------------------------------------
//
MListBoxModel* CTestSDKListsLBTextEditor::ListBoxModel()
    {
    return CEikListBoxTextEditor::ListBoxModel();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsLBTextEditor::CTestSDKListsLBTextEditor
// -----------------------------------------------------------------------------
//
TInt CTestSDKListsLBTextEditor::ItemIndex() const
    {
    return CEikListBoxTextEditor::ItemIndex();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsLBTextEditor::CTestSDKListsLBTextEditor
// -----------------------------------------------------------------------------
//
void CTestSDKListsLBTextEditor::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CEikListBoxTextEditor::WriteInternalStateL( aWriteStream );
    }
