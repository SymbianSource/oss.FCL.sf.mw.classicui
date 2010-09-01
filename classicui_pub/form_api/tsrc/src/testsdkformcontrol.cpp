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
* Description:  test AknForm.h
*
*/

// INCLUDE FILES
#include "testsdkformcontrol.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKFormControl::CTestSDKFormControl
// -----------------------------------------------------------------------------
CTestSDKFormControl::CTestSDKFormControl():CAknForm()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::~CTestSDKFormControl
// -----------------------------------------------------------------------------
CTestSDKFormControl::~CTestSDKFormControl()
    {
    
    }
    
// -----------------------------------------------------------------------------
// CTestSDKFormControl::OkToExitL
// -----------------------------------------------------------------------------
TBool CTestSDKFormControl::OkToExitL( TInt aButtonId )
    {
    return CAknForm::OkToExitL( aButtonId );
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::PrepareForFocusTransitionL
// -----------------------------------------------------------------------------
void CTestSDKFormControl::PrepareForFocusTransitionL()
    {
    CAknForm::PrepareForFocusTransitionL();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::Deleting
// -----------------------------------------------------------------------------
TBool CTestSDKFormControl::Deleting() const
    {
    return CAknForm::Deleting();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::SaveFormDataL
// -----------------------------------------------------------------------------
TBool CTestSDKFormControl::SaveFormDataL()
    {
    return CAknForm::SaveFormDataL();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::DoNotSaveFormDataL
// -----------------------------------------------------------------------------
void CTestSDKFormControl::DoNotSaveFormDataL()
    {
    CAknForm::DoNotSaveFormDataL();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::QuerySaveChangesL
// -----------------------------------------------------------------------------
TBool CTestSDKFormControl::QuerySaveChangesL()
    {
    return CAknForm::QuerySaveChangesL();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::EditCurrentLabelL
// -----------------------------------------------------------------------------
void CTestSDKFormControl::EditCurrentLabelL()
    {
    CAknForm::EditCurrentLabelL();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::DeleteCurrentItemL
// -----------------------------------------------------------------------------
void CTestSDKFormControl::DeleteCurrentItemL()
    {
    CAknForm::DeleteCurrentItemL();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::SetInitialCurrentLine
// -----------------------------------------------------------------------------
void CTestSDKFormControl::SetInitialCurrentLine()
    {
    CAknForm::SetInitialCurrentLine();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::CurrentLine
// -----------------------------------------------------------------------------
CEikCaptionedControl* CTestSDKFormControl::CurrentLine()
    {
    return CAknForm::CurrentLine();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::AddItemL
// -----------------------------------------------------------------------------
void CTestSDKFormControl::AddItemL()
    {
    CAknForm::AddItemL();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::SetChangesPending
// -----------------------------------------------------------------------------
void CTestSDKFormControl::SetChangesPending( TBool aChangesPending )
    {
    CAknForm::SetChangesPending( aChangesPending );
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::SetChangesPending
// -----------------------------------------------------------------------------
void CTestSDKFormControl::PostLayoutDynInitL()
    {
    CAknForm::PostLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::SetChangesPending
// -----------------------------------------------------------------------------
void CTestSDKFormControl::HandleControlStateChangeL( TInt aControlId )
    {
    CAknForm::HandleControlStateChangeL( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::SetChangesPending
// -----------------------------------------------------------------------------
TBool CTestSDKFormControl::UnsavedEdit() const
    {
    return CAknForm::UnsavedEdit();
    }

// -----------------------------------------------------------------------------
// CTestSDKFormControl::SetChangesPending
// -----------------------------------------------------------------------------
void CTestSDKFormControl::SetFormFlag()
    {
    CAknForm::SetFormFlag( CAknForm::EDeleting, ETrue );
    }
