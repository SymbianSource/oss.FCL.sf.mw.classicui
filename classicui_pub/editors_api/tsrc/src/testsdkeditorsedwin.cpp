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
* Description:  Test EIKEDWIN.h
*
*/


#include "testsdkeditorsedwin.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::ActivateGc
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::ActivateGc()
    {
    CEikEdwin::ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::DeactivateGc
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::DeactivateGc()
    {
    CEikEdwin::DeactivateGc();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::EditObserver
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::EditObserver( TInt aStartEdit,TInt aEditLength )
    {
    CEikEdwin::EditObserver( aStartEdit, aEditLength );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::TrappedDraw
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::TrappedDraw(const TRect& aRect) const
    {
    CEikEdwin::TrappedDraw( aRect );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::BaseConstructL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::BaseConstructL()
    {
    CEikEdwin::BaseConstructL();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::DrawContents
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::DrawContents()
    {
    CEikEdwin::DrawContents();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::FormatTextL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::FormatTextL()
    {
    CEikEdwin::FormatTextL();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::DeleteHighlightL
// -----------------------------------------------------------------------------
TInt CTestSDKEditorsEdwin::DeleteHighlightL( TBool& aChanged, 
                                             TBool aIsBackSpace,
                                             TBool aPromptConfirmation )
    {
    return CEikEdwin::DeleteHighlightL( aChanged, aIsBackSpace, aPromptConfirmation );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::OkToDeleteSelectionL
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsEdwin::OkToDeleteSelectionL()
    {
    return CEikEdwin::OkToDeleteSelectionL();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::DeleteL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::DeleteL( TBool& aChanged, const TCursorSelection& aSelection,
                                                     TBool aIsBackSpace,
                                                     TBool aAllowUndo )
    {
    CEikEdwin::DeleteL( aChanged, aSelection, aIsBackSpace, aAllowUndo );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::TrappedSizeChanged
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::TrappedSizeChanged()
    {
    CEikEdwin::TrappedSizeChanged();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::HandleSizeChangedL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::HandleSizeChangedL()
    {
    CEikEdwin::HandleSizeChangedL();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::CancelSelectionL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::CancelSelectionL( TEnd aEndOfSelectionToLeaveCursor )
    {
    CEikEdwin::CancelSelectionL( aEndOfSelectionToLeaveCursor );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::MoveCursorToChunkStartL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::MoveCursorToChunkStartL( TBool aSelect, 
                                                    TChunkSize aChunkSize,
                                                    TEnd aEndScanningTowards )
    {
    CEikEdwin::MoveCursorToChunkStartL( aSelect, aChunkSize, aEndScanningTowards );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::CancelInsertCharFormat
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::CancelInsertCharFormat()
    {
    CEikEdwin::CancelInsertCharFormat();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::PlaceDataOnClipboardL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::PlaceDataOnClipboardL()
    {
    CEikEdwin::PlaceDataOnClipboardL();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::ReportEdwinEventL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::ReportEdwinEventL( MEikEdwinObserver::TEdwinEvent aEventType )
    {
    CEikEdwin::ReportEdwinEventL( aEventType );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::SetLineCursorDetailsL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::SetLineCursorDetailsL()
    {
    CEikEdwin::SetLineCursorDetailsL();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::CopyDocumentContentL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::CopyDocumentContentL( CGlobalText& aInText, CGlobalText& aOutText )
    {
    CEikEdwin::CopyDocumentContentL( aInText, aOutText );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::DisplayFindTextNotFound
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::DisplayFindTextNotFound( TDes& aFindText )
    {
    CEikEdwin::DisplayFindTextNotFound( aFindText );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::HandleTextPastedL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::HandleTextPastedL(TInt aStartPos,TInt& aLength)
    {
    CEikEdwin::HandleTextPastedL( aStartPos, aLength );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::CreateCustomDrawL
// -----------------------------------------------------------------------------
CLafEdwinCustomDrawBase* CTestSDKEditorsEdwin::CreateCustomDrawL()
    {
    return CEikEdwin::CreateCustomDrawL();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::ReadAknResourceL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::ReadAknResourceL(TResourceReader& aReader)
    {
    CEikEdwin::ReadAknResourceL( aReader );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::CreateLayoutL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::CreateLayoutL(MLayDoc* aLayDoc)
    {
    CEikEdwin::CreateLayoutL( aLayDoc );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::CreateTextAndLayoutL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::CreateTextAndLayoutL( CParaFormatLayer* aParaFormatLayer,
                                                 CCharFormatLayer* aCharFormatLayer )
    {
    CEikEdwin::CreateTextAndLayoutL( aParaFormatLayer, aCharFormatLayer );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::CreateTextAndLayoutL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdwin::CheckEdwinExtensionL()
    {
    CEikEdwin::CheckEdwinExtensionL();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdwin::CreateTextAndLayoutL
// -----------------------------------------------------------------------------
TTypeUid::Ptr CTestSDKEditorsEdwin::MopSupplyObject(TTypeUid aId)
    {
    return CEikEdwin::MopSupplyObject( aId );
    }
