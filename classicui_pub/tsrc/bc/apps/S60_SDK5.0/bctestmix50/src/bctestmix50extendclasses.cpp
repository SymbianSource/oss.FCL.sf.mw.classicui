/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include "bctestmix50extendclasses.h"


// ---------------------------------------------------------------------------
// CBCTestCAknPopupList::NewL()
//
// ---------------------------------------------------------------------------
//
CBCTestCAknPopupList* CBCTestCAknPopupList::NewL( CEikListBox* aListBox )
    {
    CAknPopupList* self = CAknPopupList::NewL( aListBox
                                              , R_AVKON_SOFTKEYS_OK_CANCEL );
    CBCTestCAknPopupList* rSelf =
     static_cast< CBCTestCAknPopupList* > ( self );
    return rSelf;
    }


// ---------------------------------------------------------------------------
// TBCTestCommandObserver::ProcessCommandL()
//
// ---------------------------------------------------------------------------
//
void TBCTestCommandObserver::ProcessCommandL( TInt /*aCommandId*/ )
    {
    }


// ---------------------------------------------------------------------------
// TBCTestPointerObserver::PointerEvent()
//
// ---------------------------------------------------------------------------
//
bool TBCTestPointerObserver::PointerEvent( CEikCaptionedControl* /*aControl*/,
    const TPointerEvent& /*aPointerEvent*/ )
    {
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CBCTestCAknSettingPage::CBCTestCAknSettingPage
//
// ---------------------------------------------------------------------------
//
CBCTestCAknSettingPage::CBCTestCAknSettingPage( TInt aResourceId )
    : CAknSettingPage( aResourceId )
    {
    }


// ---------------------------------------------------------------------------
// CBCTestCAknSettingPage::CBCTestCAknSettingPage
//
// ---------------------------------------------------------------------------
//
CBCTestCAknSettingPage::CBCTestCAknSettingPage(
                                         const TDesC* aSettingText,
                                         TInt aSettingNumber,
                                         TInt aControlType,
                                         TInt aEditorResourceId,
                                         TInt aSettingPageResourceId )
    : CAknSettingPage( aSettingText,
                       aSettingNumber,
                       aControlType,
                       aEditorResourceId,
                       aSettingPageResourceId )
    {
    }


// ---------------------------------------------------------------------------
// TBCTestSelectionObserver::SelectionModeChanged()
//
// ---------------------------------------------------------------------------
//
void TBCTestSelectionObserver::SelectionModeChanged( CEikListBox* /*aListBox*/,
     TBool /*aSelectionModeEnabled*/ )
     {
     }


// ---------------------------------------------------------------------------
// TBCTestCcpuEditor::CcpuIsFocused()
//
// ---------------------------------------------------------------------------
//
TBool TBCTestCcpuEditor::CcpuIsFocused() const
    {
    return EFalse;
    }


// ---------------------------------------------------------------------------
// TBCTestCcpuEditor::CcpuCanCut()
//
// ---------------------------------------------------------------------------
//
TBool TBCTestCcpuEditor::CcpuCanCut() const
    {
    return EFalse;
    }


// ---------------------------------------------------------------------------
// TBCTestCcpuEditor::CcpuCutL()
//
// ---------------------------------------------------------------------------
//
void TBCTestCcpuEditor::CcpuCutL()
    {
    }


// ---------------------------------------------------------------------------
// TBCTestCcpuEditor::CcpuCanCopy()
//
// ---------------------------------------------------------------------------
//
TBool TBCTestCcpuEditor::CcpuCanCopy() const
    {
    return EFalse;
    }


// ---------------------------------------------------------------------------
// TBCTestCcpuEditor::CcpuCopyL()
//
// ---------------------------------------------------------------------------
//
void TBCTestCcpuEditor::CcpuCopyL()
    {
    }


// ---------------------------------------------------------------------------
// TBCTestCcpuEditor::CcpuCanPaste()
//
// ---------------------------------------------------------------------------
//
TBool TBCTestCcpuEditor::CcpuCanPaste() const
    {
    return EFalse;
    };


// ---------------------------------------------------------------------------
// TBCTestCcpuEditor::CcpuPasteL()
//
// ---------------------------------------------------------------------------
//
void TBCTestCcpuEditor::CcpuPasteL()
    {
    }


// ---------------------------------------------------------------------------
// TBCTestCcpuEditor::CcpuCanUndo()
//
// ---------------------------------------------------------------------------
//
TBool TBCTestCcpuEditor::CcpuCanUndo() const
    {
    return EFalse;
    }


// ---------------------------------------------------------------------------
// TBCTestCcpuEditor::CcpuUndoL()
//
// ---------------------------------------------------------------------------
//
void TBCTestCcpuEditor::CcpuUndoL()
    {
    }


// ---------------------------------------------------------------------------
// TBCTestCcpuEditor::CcpuUndoL()
//
// ---------------------------------------------------------------------------
//
CBCTestCAknGrid::CBCTestCAknGrid()
    : CAknGrid()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestCAknLocationEditor::CAknLocationEditor_ExtensionInterface()
//
// ---------------------------------------------------------------------------
//
void* CBCTestCAknLocationEditor::CAknLocationEditor_ExtensionInterface( 
    TUid aInterface )
    {
    return CAknLocationEditor::CAknLocationEditor_ExtensionInterface( aInterface );
    }
