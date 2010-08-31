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
* Description:  Test EIKDIALG.H
*
*/

//  INCLUDES
#include <eikedwin.h> 
#include <flddef.h>
#include <s32std.h>
#include <e32base.h>

#include "testsdkdialogscontrol.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::CTestSDKDialogsControl 
// -----------------------------------------------------------------------------
CTestSDKDialogsControl::CTestSDKDialogsControl() : CEikDialog()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::~CTestSDKDialogsControl 
// -----------------------------------------------------------------------------
CTestSDKDialogsControl::~CTestSDKDialogsControl()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::CTestSDKDialogsSetInitialCurrentLine 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::CTestSDKDialogsSetInitialCurrentLine()
    {
    SetInitialCurrentLine();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::CTestSDKDialogsCurrentLine 
// -----------------------------------------------------------------------------
CEikCaptionedControl* CTestSDKDialogsControl::CTestSDKDialogsCurrentLine()
    {
    return CurrentLine();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::MediatorCommandL 
// -----------------------------------------------------------------------------
TAknDialogMediatorObserverCommand CTestSDKDialogsControl::MediatorCommandL( TUid /*aDomain*/,
    TUid /*aCategory*/, 
    TInt /*aCommandId*/,
    const TDesC8& /*aData*/ )
    {
    return EAcceptDialog;
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::NotifyMediatorExit 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::NotifyMediatorExit()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::CTestSDKSetMediatorObserver 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::CTestSDKSetMediatorObserver()
    {
    SetMediatorObserver( this );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::NewFieldL 
// -----------------------------------------------------------------------------
CTextField* CTestSDKDialogsControl::NewFieldL( TUid aFieldType )
    {
    CTextField* field = NULL; 
    if ( aFieldType == KDateTimeFieldUid )
        {
        field = ( CTextField* ) new (ELeave) CMyDateTimeField();
        }
    return field;

    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::PrepareForFocusTransitionL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::PrepareForFocusTransitionL()
    {
    CEikDialog::PrepareForFocusTransitionL();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::IdOfFocusControl 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::IdOfFocusControl()
    {
    return CEikDialog::IdOfFocusControl();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::PageChangedL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::PageChangedL( TInt aPageId )
    {
    CEikDialog::PageChangedL( aPageId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::LineChangedL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::LineChangedL( TInt aControlId )
    {
    CEikDialog::LineChangedL( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::PrepareContext 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::PrepareContext() const
    {
    CWindowGc& gc = SystemGc();
    CEikDialog::PrepareContext( gc );
    gc.Reset();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::WriteInternalStateL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::WriteInternalStateL( RWriteStream& aWriteStream ) const
    {
    CEikDialog::WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::CountComponentControls 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::CountComponentControls() const
    {
    return CEikDialog::CountComponentControls();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::ComponentControl 
// -----------------------------------------------------------------------------
CCoeControl* CTestSDKDialogsControl::ComponentControl( TInt aIndex ) const
    {
    return CEikDialog::ComponentControl( aIndex );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::GetNumberOfLinesOnPage 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::GetNumberOfLinesOnPage( TInt aPageIndex ) const
    {
    return CEikDialog::GetNumberOfLinesOnPage( aPageIndex );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::GetNumberOfPages 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::GetNumberOfPages() const
    {
    return CEikDialog::GetNumberOfPages();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::GetLineByLineAndPageIndex 
// -----------------------------------------------------------------------------
CEikCaptionedControl* CTestSDKDialogsControl::GetLineByLineAndPageIndex( TInt aLineIndex, 
        TInt aPageIndex ) const
    {
    return CEikDialog::GetLineByLineAndPageIndex( aLineIndex, aPageIndex );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::HandleControlEventL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType )
    {
    CEikDialog::HandleControlEventL( aControl, aEventType );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::TryExitL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::TryExitL( TInt aButtonId )
    {
    CEikDialog::TryExitL( aButtonId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::AdjustAllIdsOnPage 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::AdjustAllIdsOnPage( TInt aPageId, TInt aControlIdDelta )
    {
    CEikDialog::AdjustAllIdsOnPage( aPageId, aControlIdDelta );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::ConstructSleepingDialogL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::ConstructSleepingDialogL( TInt aResourceId )
    {
    CEikDialog::ConstructSleepingDialogL( aResourceId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::ConstructSleepingAlertDialogL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::ConstructSleepingAlertDialogL( TInt aResourceId )
    {
    CEikDialog::ConstructSleepingAlertDialogL( aResourceId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::RouseSleepingDialog 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::RouseSleepingDialog()
    {
    return CEikDialog::RouseSleepingDialog();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::ExitSleepingDialog 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::ExitSleepingDialog()
    {
    CEikDialog::ExitSleepingDialog();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::IdOfFocusControl 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::IdOfFocusControl() const
    {
    return CEikDialog::IdOfFocusControl();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::FindLineIndex 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::FindLineIndex( const CCoeControl& aControl ) const
    {
    return CEikDialog::FindLineIndex( aControl );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::Line 
// -----------------------------------------------------------------------------
CEikCaptionedControl* CTestSDKDialogsControl::Line( TInt aControlId ) const
    {
    return CEikDialog::Line( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::CurrentLine 
// -----------------------------------------------------------------------------
CEikCaptionedControl* CTestSDKDialogsControl::CurrentLine() const
    {
    return CEikDialog::CurrentLine();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::RotateFocusByL 
// -----------------------------------------------------------------------------
TBool CTestSDKDialogsControl::RotateFocusByL( TInt aDelta )
    {
    return CEikDialog::RotateFocusByL( aDelta );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::ActivePageIndex 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::ActivePageIndex() const
    {
    return CEikDialog::ActivePageIndex();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::ResetLineMinimumSizes 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::ResetLineMinimumSizes()
    {
    CEikDialog::ResetLineMinimumSizes();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SwapButtonGroupContainer 
// -----------------------------------------------------------------------------
CEikButtonGroupContainer* CTestSDKDialogsControl::SwapButtonGroupContainer( 
        CEikButtonGroupContainer* aContainer )
    {
    return CEikDialog::SwapButtonGroupContainer( aContainer );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::ButtonCommandObserver 
// -----------------------------------------------------------------------------
MEikCommandObserver* CTestSDKDialogsControl::ButtonCommandObserver() const
    {
    return CEikDialog::ButtonCommandObserver();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::ActivateGc 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::ActivateGc() const
    {
    CEikDialog::ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::DeactivateGc 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::DeactivateGc() const
    {
    CEikDialog::DeactivateGc();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::OkToExitL 
// -----------------------------------------------------------------------------
TBool CTestSDKDialogsControl::OkToExitL( TInt aButtonId )
    {
    return CEikDialog::OkToExitL( aButtonId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::PreLayoutDynInitL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::PreLayoutDynInitL()
    {
    CEikDialog::PreLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::PostLayoutDynInitL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::PostLayoutDynInitL()
    {
    CEikDialog::PostLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetInitialCurrentLine 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetInitialCurrentLine()
    {
    CEikDialog::SetInitialCurrentLine();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::HandleControlStateChangeL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::HandleControlStateChangeL( TInt aControlId )
    {
    CEikDialog::HandleControlStateChangeL( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::HandleInteractionRefused 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::HandleInteractionRefused( TInt aControlId )
    {
    CEikDialog::HandleInteractionRefused( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetSizeAndPosition 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetSizeAndPosition( const TSize& aSize )
    {
    CEikDialog::SetSizeAndPosition( aSize );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::BorderStyle 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::BorderStyle()
    {
    return CEikDialog::BorderStyle();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::MappedCommandId 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::MappedCommandId( TInt aButtonId )
    {
    return CEikDialog::MappedCommandId( aButtonId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::FormFlagsFromActivePage 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::FormFlagsFromActivePage()
    {
    return CEikDialog::FormFlagsFromActivePage();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::GetFirstLineOnFirstPageOrNull 
// -----------------------------------------------------------------------------
CEikCaptionedControl* CTestSDKDialogsControl::GetFirstLineOnFirstPageOrNull()
    {
    return CEikDialog::GetFirstLineOnFirstPageOrNull();
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::ControlsOnPage 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::ControlsOnPage( 
        RArray<CEikCaptionedControl*>& aControls, TInt aPageId ) const
    {
    CEikDialog::ControlsOnPage( aControls, aPageId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::MopSupplyObject 
// -----------------------------------------------------------------------------
TTypeUid::Ptr CTestSDKDialogsControl::MopSupplyObject( TTypeUid aId )
    {
    return CEikDialog::MopSupplyObject( aId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetLabelL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetLabelL( TInt aControlId, const TDesC& aDes )
    {
    CEikDialog::SetLabelL( aControlId, aDes );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::GetLabelText 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::GetLabelText( TDes& aDes,TInt aControlId ) const
    {
    CEikDialog::GetLabelText( aDes, aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetLabelL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetLabelL(TInt aControlId, TInt aResourceId)
    {
    CEikDialog::SetLabelL( aControlId, aResourceId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetLabelReserveLengthL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetLabelReserveLengthL( TInt aControlId, TInt aLength )
    {
    CEikDialog::SetLabelReserveLengthL( aControlId, aLength );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetEdwinTextL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetEdwinTextL( TInt aControlId, const TDesC* aDes )
    {
    CEikDialog::SetEdwinTextL( aControlId, aDes );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::GetEdwinText 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::GetEdwinText( TDes& aDes,TInt aControlId ) const
    {
    CEikDialog::GetEdwinText( aDes, aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::ResetSecretEditor 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::ResetSecretEditor(TInt aControlId)
    {
    CEikDialog::ResetSecretEditor( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetTextEditorTextL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetTextEditorTextL( TInt aControlId, const CGlobalText* aGlobalText )
    {
    CEikDialog::SetTextEditorTextL( aControlId, aGlobalText );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::GetTextEditorText 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::GetTextEditorText(CGlobalText*& aGlobalText,TInt aControlId)
    {
    CEikDialog::GetTextEditorText( aGlobalText, aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::GetSecretEditorText 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::GetSecretEditorText(TDes& aDes,TInt aControlId) const
    {
    CEikDialog::GetSecretEditorText( aDes, aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetFloatingPointEditorValueL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetFloatingPointEditorValueL( TInt aControlId, const TReal* aValue )
    {
    CEikDialog::SetFloatingPointEditorValueL( aControlId, aValue );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::FloatingPointEditorValue 
// -----------------------------------------------------------------------------
TReal CTestSDKDialogsControl::FloatingPointEditorValue(TInt aControlId) const
    {
    return CEikDialog::FloatingPointEditorValue( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetFixedPointEditorValueL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetFixedPointEditorValueL( TInt aControlId, TInt aValue )
    {
    CEikDialog::SetFixedPointEditorValueL( aControlId, aValue );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::FixedPointEditorValue 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::FixedPointEditorValue( TInt aControlId ) const
    {
    return CEikDialog::FixedPointEditorValue( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetFixedPointEditorDecimal 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetFixedPointEditorDecimal( TInt aControlId, TInt aDecimal )
    {
    CEikDialog::SetFixedPointEditorDecimal( aControlId, aDecimal );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::FixedPointEditorDecimal 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::FixedPointEditorDecimal( TInt aControlId ) const
    {
    return CEikDialog::FixedPointEditorDecimal( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetNumberEditorMinAndMax 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetNumberEditorMinAndMax( TInt aControlId, 
        TInt aMinimumValue, TInt aMaximumValue )
    {
    CEikDialog::SetNumberEditorMinAndMax( aControlId, aMinimumValue, aMaximumValue );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetNumberEditorValue 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetNumberEditorValue(TInt aControlId, TInt aNumber)
    {
    CEikDialog::SetNumberEditorValue( aControlId, aNumber );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetFloatEditorMinAndMax 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetFloatEditorMinAndMax(TInt aControlId,TInt aMin,TInt aMax)
    {
    CEikDialog::SetFloatEditorMinAndMax( aControlId, aMin ,aMax );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::NumberEditorValue 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::NumberEditorValue( TInt aControlId ) const
    {
    return CEikDialog::NumberEditorValue( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::FloatEditorValue 
// -----------------------------------------------------------------------------
TReal CTestSDKDialogsControl::FloatEditorValue(TInt aControlId) const
    {
    return CEikDialog::FloatEditorValue( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetFloatEditorValueL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetFloatEditorValueL( TInt aControlId, TReal aFloat )
    {
    CEikDialog::SetFloatEditorValueL( aControlId, aFloat );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetRangeEditorMinAndMax 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetRangeEditorMinAndMax( TInt aControlId, 
        TInt aMinimumValue, TInt aMaximumValue )
    {
    CEikDialog::SetRangeEditorMinAndMax( aControlId, aMinimumValue, aMaximumValue );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::RangeEditorValue 
// -----------------------------------------------------------------------------
SEikRange CTestSDKDialogsControl::RangeEditorValue( TInt aControlId ) const
    {
    return CEikDialog::RangeEditorValue( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetRangeEditorValue 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetRangeEditorValue( TInt aControlId, const SEikRange& aRange )
    {
    CEikDialog::SetRangeEditorValue(  aControlId, aRange );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetTTimeEditorMinAndMax 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetTTimeEditorMinAndMax( TInt aControlId, 
        const TTime& aMinimumTime, const TTime& aMaximumTime )
    {
    CEikDialog::SetTTimeEditorMinAndMax( aControlId, aMinimumTime, aMaximumTime );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::TTimeEditorValue 
// -----------------------------------------------------------------------------
TTime CTestSDKDialogsControl::TTimeEditorValue( TInt aControlId ) const
    {
    return CEikDialog::TTimeEditorValue( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetTTimeEditorValue 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetTTimeEditorValue( TInt aControlId, const TTime& aTime )
    {
    CEikDialog::SetTTimeEditorValue( aControlId, aTime );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetDurationEditorMinAndMax 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetDurationEditorMinAndMax( TInt aControlId, 
        const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration )
    {
    CEikDialog::SetDurationEditorMinAndMax( aControlId, aMinimumDuration, aMaximumDuration );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetDurationEditorValue 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetDurationEditorValue( TInt aControlId, 
        const TTimeIntervalSeconds& aDuration )
    {
    CEikDialog::SetDurationEditorValue( aControlId, aDuration );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::DurationEditorValue 
// -----------------------------------------------------------------------------
TTimeIntervalSeconds CTestSDKDialogsControl::DurationEditorValue( TInt aControlId ) const
    {
    return CEikDialog::DurationEditorValue( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetTimeOffsetEditorMinAndMax 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetTimeOffsetEditorMinAndMax( TInt aControlId, 
        const TTimeIntervalSeconds& aMinimumTimeOffset, 
        const TTimeIntervalSeconds& aMaximumTimeOffset )
    {
    CEikDialog::SetTimeOffsetEditorMinAndMax( aControlId, aMinimumTimeOffset, aMaximumTimeOffset );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::TimeOffsetEditorValue 
// -----------------------------------------------------------------------------
TTimeIntervalSeconds CTestSDKDialogsControl::TimeOffsetEditorValue( TInt aControlId ) const
    {
    return CEikDialog::TimeOffsetEditorValue( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetTimeOffsetEditorValue 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetTimeOffsetEditorValue(TInt aControlId, 
        const TTimeIntervalSeconds& aTimeOffset)
    {
    CEikDialog::SetTimeOffsetEditorValue( aControlId, aTimeOffset );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetListBoxCurrentItem 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetListBoxCurrentItem( TInt aControlId, TInt aItem )
    {
    CEikDialog::SetListBoxCurrentItem( aControlId, aItem );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::ListBoxCurrentItem 
// -----------------------------------------------------------------------------
TInt CTestSDKDialogsControl::ListBoxCurrentItem( TInt aControlId ) const
    {
    return CEikDialog::ListBoxCurrentItem( aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::SetFileNameL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::SetFileNameL( TInt aControlId, const TDesC* aFileName )
    {
    CEikDialog::SetFileNameL( aControlId, aFileName );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::GetFileName 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::GetFileName( TFileName* aFileName, TInt aControlId ) const
    {
    CEikDialog::GetFileName( aFileName, aControlId );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::UpdatePageL 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::UpdatePageL( TBool aRedraw )
    {
    CEikDialog::UpdatePageL( aRedraw );
    }

// -----------------------------------------------------------------------------
// CTestSDKDialogsControl::GetAutoValuesFromPage 
// -----------------------------------------------------------------------------
void CTestSDKDialogsControl::GetAutoValuesFromPage( CEikCapCArray* aLines )
    {
    CEikDialog::GetAutoValuesFromPage( aLines );
    }
