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


#ifndef C_TESTSDKDIALOGSCONTROL_H
#define C_TESTSDKDIALOGSCONTROL_H

//  INCLUDES
#include <eikdialg.h>
#include <eikcapc.h> 
#include <aknmediatorobserver.h>
#include <fldbase.h>
#include <eikmfne.h> 

class CTestSDKDialogsControl : public CEikDialog, 
                               public MAknDialogMediatorObserver, 
                               public MTextFieldFactory
    {
public:// Constructors and destructor
    
    /**
    * C++ default constructor.
    */
    CTestSDKDialogsControl();
    
    /**
    * Destructor.
    */
    ~CTestSDKDialogsControl();

    /**
    *  CTestSDKDialogsSetInitialCurrentLine test function for testing the 
    * Test SetInitialCurrentLine function
    */
    void CTestSDKDialogsSetInitialCurrentLine();
    
    /**
    *  CTestSDKDialogsSetInitialCurrentLine test function for testing the 
    * Test CurrentLine function
    */
    CEikCaptionedControl* CTestSDKDialogsCurrentLine();
    
    /**
    *  MediatorCommandL test function for testing the 
    * Test MediatorCommandL function
    */
    TAknDialogMediatorObserverCommand MediatorCommandL( TUid aDomain,
        TUid aCategory, 
        TInt aCommandId,
        const TDesC8& aData );
    
    /**
    *  NotifyMediatorExit test function for testing the 
    * Test NotifyMediatorExit function
    */
    void NotifyMediatorExit();
    
    /**
    *  CTestSDKSetMediatorObserver test function for testing the 
    * Test SetMediatorObserver function
    */
    void CTestSDKSetMediatorObserver();
    
    /**
    *  NewFieldL test function for testing the 
    * Test NewFieldL function
    */
    CTextField* NewFieldL( TUid aFieldType );
    
    /**
    *  PrepareForFocusTransitionL test function for testing the 
    * Test PrepareForFocusTransitionL function
    */
    void PrepareForFocusTransitionL();
    
    /**
    *  IdOfFocusControl test function for testing the 
    * Test IdOfFocusControl function
    */
    TInt IdOfFocusControl();
    
    /**
    *  PageChangedL test function for testing the 
    * Test PageChangedL function
    */
    void PageChangedL( TInt aPageId );
    
    /**
    *  LineChangedL test function for testing the 
    * Test LineChangedL function
    */
    void LineChangedL( TInt aControlId );
    
    /**
    *  PrepareContext test function for testing the 
    * Test PrepareContext function
    */
    void PrepareContext() const;
    
    /**
    *  WriteInternalStateL test function for testing the 
    * Test WriteInternalStateL function
    */
    void WriteInternalStateL( RWriteStream& aWriteStream ) const;
    
    /**
    *  CountComponentControls test function for testing the 
    * Test CountComponentControls function
    */
    TInt CountComponentControls() const;
    
    /**
    *  ComponentControl test function for testing the 
    * Test ComponentControl function
    */
    CCoeControl* ComponentControl( TInt aIndex ) const;
    
    /**
    *  GetNumberOfLinesOnPage test function for testing the 
    * Test GetNumberOfLinesOnPage function
    */
    TInt GetNumberOfLinesOnPage( TInt aPageIndex ) const;
    
    /**
    *  GetNumberOfPages test function for testing the 
    * Test GetNumberOfPages function
    */
    TInt GetNumberOfPages() const;
    
    /**
    *  GetLineByLineAndPageIndex test function for testing the 
    * Test GetLineByLineAndPageIndex function
    */
    CEikCaptionedControl* GetLineByLineAndPageIndex( TInt aLineIndex, TInt aPageIndex ) const;
    
    /**
    *  HandleControlEventL test function for testing the 
    * Test HandleControlEventL function
    */
    void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );
    
    /**
    *  TryExitL test function for testing the 
    * Test TryExitL function
    */
    void TryExitL(TInt aButtonId);
    
    /**
    *  AdjustAllIdsOnPage test function for testing the 
    * Test AdjustAllIdsOnPage function
    */
    void AdjustAllIdsOnPage( TInt aPageId, TInt aControlIdDelta );
    
    /**
    *  ConstructSleepingDialogL test function for testing the 
    * Test ConstructSleepingDialogL function
    */
    void ConstructSleepingDialogL( TInt aResourceId );
    
    /**
    *  ConstructSleepingAlertDialogL test function for testing the 
    * Test ConstructSleepingAlertDialogL function
    */
    void ConstructSleepingAlertDialogL( TInt aResourceId );
    
    /**
    *  RouseSleepingDialog test function for testing the 
    * Test RouseSleepingDialog function
    */
    TInt RouseSleepingDialog();
    
    /**
    *  ExitSleepingDialog test function for testing the 
    * Test ExitSleepingDialog function
    */
    void ExitSleepingDialog();
    
    /**
    *  IdOfFocusControl test function for testing the 
    * Test IdOfFocusControl function
    */
    TInt IdOfFocusControl() const;
    
    /**
    *  FindLineIndex test function for testing the 
    * Test FindLineIndex function
    */
    TInt FindLineIndex( const CCoeControl& aControl ) const;
    
    /**
    *  Line test function for testing the 
    * Test Line function
    */
    CEikCaptionedControl* Line( TInt aControlId ) const;
    
    /**
    *  CurrentLine test function for testing the 
    * Test CurrentLine function
    */
    CEikCaptionedControl* CurrentLine() const;
    
    /**
    *  RotateFocusByL test function for testing the 
    * Test RotateFocusByL function
    */
    TBool RotateFocusByL( TInt aDelta );
    
    /**
    *  ActivePageIndex test function for testing the 
    * Test ActivePageIndex function
    */
    TInt ActivePageIndex() const;
    
    /**
    *  ResetLineMinimumSizes test function for testing the 
    * Test ResetLineMinimumSizes function
    */
    void ResetLineMinimumSizes();
    
    /**
    *  SwapButtonGroupContainer test function for testing the 
    * Test SwapButtonGroupContainer function
    */
    CEikButtonGroupContainer* SwapButtonGroupContainer( CEikButtonGroupContainer* aContainer );
    
    /**
    *  ButtonCommandObserver test function for testing the 
    * Test ButtonCommandObserver function
    */
    MEikCommandObserver* ButtonCommandObserver() const;
    
    /**
    *  ActivateGc test function for testing the 
    * Test ActivateGc function
    */
    void ActivateGc() const;
    
    /**
    *  DeactivateGc test function for testing the 
    * Test DeactivateGc function
    */
    void DeactivateGc() const;
    
    /**
    *  OkToExitL test function for testing the 
    * Test OkToExitL function
    */
    TBool OkToExitL( TInt aButtonId );
    
    /**
    *  PreLayoutDynInitL test function for testing the 
    * Test PreLayoutDynInitL function
    */
    void PreLayoutDynInitL();
    
    /**
    *  PostLayoutDynInitL test function for testing the 
    * Test PostLayoutDynInitL function
    */
    void PostLayoutDynInitL();
    
    /**
    *  SetInitialCurrentLine test function for testing the 
    * Test SetInitialCurrentLine function
    */
    void SetInitialCurrentLine();
    
    /**
    *  HandleControlStateChangeL test function for testing the 
    * Test HandleControlStateChangeL function
    */
    void HandleControlStateChangeL( TInt aControlId );
    
    /**
    *  HandleInteractionRefused test function for testing the 
    * Test HandleInteractionRefused function
    */
    void HandleInteractionRefused( TInt aControlId );
    
    /**
    *  SetSizeAndPosition test function for testing the 
    * Test SetSizeAndPosition function
    */
    void SetSizeAndPosition( const TSize& aSize );
    
    /**
    *  MappedCommandId test function for testing the 
    * Test MappedCommandId function
    */
    TInt BorderStyle();
    
    /**
    *  MappedCommandId test function for testing the 
    * Test MappedCommandId function
    */
    
    TInt MappedCommandId( TInt aButtonId );
    
    /**
    *  FormFlagsFromActivePage test function for testing the 
    * Test FormFlagsFromActivePage function
    */
    TInt FormFlagsFromActivePage();
    
    /**
    *  GetFirstLineOnFirstPageOrNull test function for testing the 
    * Test GetFirstLineOnFirstPageOrNull function
    */
    CEikCaptionedControl* GetFirstLineOnFirstPageOrNull();
    
    /**
    *  ControlsOnPage test function for testing the 
    * Test ControlsOnPage function
    */
    void ControlsOnPage( RArray<CEikCaptionedControl*>& aControls, TInt aPageId ) const;
    
    /**
    *  MopSupplyObject test function for testing the 
    * Test MopSupplyObject function
    */
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
    
    /**
    *  SetLabelL test function for testing the 
    * Test SetLabelL function
    */
    void SetLabelL( TInt aControlId, const TDesC& aDes );
    
    /**
    *  GetLabelText test function for testing the 
    * Test GetLabelText function
    */
    void GetLabelText( TDes& aDes,TInt aControlId ) const;
    
    /**
    *  SetLabelL test function for testing the  
    * Test SetLabelL function
    */
    void SetLabelL( TInt aControlId, TInt aResourceId );
    
    /**
    *  SetLabelReserveLengthL test function for testing the  
    * Test SetLabelReserveLengthL function
    */
    void SetLabelReserveLengthL( TInt aControlId, TInt aLength );
    
    /**
    *  SetEdwinTextL test function for testing the  
    * Test SetEdwinTextL function
    */
    void SetEdwinTextL( TInt aControlId, const TDesC* aDes );
    
    /**
    *  GetEdwinText test function for testing the  
    * Test GetEdwinText function
    */
    void GetEdwinText( TDes& aDes, TInt aControlId ) const;
    
    /**
    *  ResetSecretEditor test function for testing the  
    * Test ResetSecretEditor function
    */
    void ResetSecretEditor( TInt aControlId );
    
    /**
    *  SetTextEditorTextL test function for testing the  
    * Test SetTextEditorTextL function
    */
    void SetTextEditorTextL( TInt aControlId, const CGlobalText* aGlobalText );
    
    /**
    *  GetTextEditorText test function for testing the  
    * Test GetTextEditorText function
    */
    void GetTextEditorText( CGlobalText*& aGlobalText, TInt aControlId );
    
    /**
    *  GetSecretEditorText test function for testing the  
    * Test GetSecretEditorText function
    */
    void GetSecretEditorText( TDes& aDes, TInt aControlId ) const;
    
    /**
    *  SetFloatingPointEditorValueL test function for testing the 
    * Test SetFloatingPointEditorValueL function
    */
    void SetFloatingPointEditorValueL( TInt aControlId, const TReal* aValue );
    
    /**
    *  FloatingPointEditorValue test function for testing the  
    * Test FloatingPointEditorValue function
    */
    TReal FloatingPointEditorValue( TInt aControlId ) const;
    
    /**
    *  SetFixedPointEditorValueL test function for testing the  
    * Test SetFixedPointEditorValueL function
    */
    void SetFixedPointEditorValueL( TInt aControlId, TInt aValue );
    
    /**
    *  FixedPointEditorValue test function for testing the 
    * Test FixedPointEditorValue function
    */
    TInt FixedPointEditorValue( TInt aControlId ) const;
    
    /**
    *  SetFixedPointEditorDecimal test function for testing the  
    * Test SetFixedPointEditorDecimal function
    */
    void SetFixedPointEditorDecimal( TInt aControlId, TInt aDecimal );
    
    /**
    *  FixedPointEditorDecimal test function for testing the 
    * Test FixedPointEditorDecimal function
    */
    TInt FixedPointEditorDecimal( TInt aControlId ) const;
    
    /**
    *  SetNumberEditorMinAndMax test function for testing the  
    * Test SetNumberEditorMinAndMax function
    */
    void SetNumberEditorMinAndMax( TInt aControlId, TInt aMinimumValue, TInt aMaximumValue );
    
    /**
    *  SetNumberEditorValue test function for testing the  
    * Test SetNumberEditorValue function
    */
    void SetNumberEditorValue( TInt aControlId, TInt aNumber );
    
    /**
    *  SetFloatEditorMinAndMax test function for testing the  
    * Test SetFloatEditorMinAndMax function
    */
    void SetFloatEditorMinAndMax( TInt aControlId, TInt aMin, TInt aMax );
    
    /**
    *  NumberEditorValue test function for testing the  
    * Test NumberEditorValue function
    */
    TInt NumberEditorValue( TInt aControlId ) const;
    
    /**
    *  FloatEditorValue test function for testing the  
    * Test FloatEditorValue function
    */
    TReal FloatEditorValue( TInt aControlId ) const;
    
    /**
    *  SetFloatEditorValueL test function for testing the  
    * Test SetFloatEditorValueL function
    */
    void SetFloatEditorValueL( TInt aControlId, TReal aFloat );
    
    /**
    *  SetRangeEditorMinAndMax test function for testing the  
    * Test SetRangeEditorMinAndMax function
    */
    void SetRangeEditorMinAndMax( TInt aControlId, TInt aMinimumValue, TInt aMaximumValue );
    
    /**
    *  RangeEditorValue test function for testing the  
    * Test RangeEditorValue function
    */
    SEikRange RangeEditorValue( TInt aControlId ) const;
    
    /**
    *  SetRangeEditorValue test function for testing the  
    * Test SetRangeEditorValue function
    */
    void SetRangeEditorValue( TInt aControlId, const SEikRange& aRange );
    
    /**
    *  SetTTimeEditorMinAndMax test function for testing the  
    * Test SetTTimeEditorMinAndMax function
    */
    void SetTTimeEditorMinAndMax( TInt aControlId, 
                                  const TTime& aMinimumTime, 
                                  const TTime& aMaximumTime );
    
    /**
    *  TTimeEditorValue test function for testing the  
    * Test TTimeEditorValue function
    */
    TTime TTimeEditorValue( TInt aControlId ) const;
    
    /**
    *  SetTTimeEditorValue test function for testing the  
    * Test SetTTimeEditorValue function
    */
    void SetTTimeEditorValue( TInt aControlId, const TTime& aTime );
    
    /**
    *  SetDurationEditorMinAndMax test function for testing the  
    * Test SetDurationEditorMinAndMax function
    */
    void SetDurationEditorMinAndMax( TInt aControlId, 
                                     const TTimeIntervalSeconds& aMinimumDuration, 
                                     const TTimeIntervalSeconds& aMaximumDuration );
    
    /**
    *  SetDurationEditorValue test function for testing the  
    * Test SetDurationEditorValue function
    */
    void SetDurationEditorValue( TInt aControlId, const TTimeIntervalSeconds& aDuration );
    
    /**
    *  DurationEditorValue test function for testing the 
    * Test DurationEditorValue function
    */
    TTimeIntervalSeconds DurationEditorValue( TInt aControlId ) const;
    
    /**
    *  SetTimeOffsetEditorMinAndMax test function for testing the 
    * Test SetTimeOffsetEditorMinAndMax function
    */
    void SetTimeOffsetEditorMinAndMax( TInt aControlId, 
                                       const TTimeIntervalSeconds& aMinimumTimeOffset, 
                                       const TTimeIntervalSeconds& aMaximumTimeOffset );
    
    /**
    *  TimeOffsetEditorValue test function for testing the  
    * Test TimeOffsetEditorValue function
    */
    TTimeIntervalSeconds TimeOffsetEditorValue( TInt aControlId ) const;
    
    /**
    *  SetTimeOffsetEditorValue test function for testing the 
    * Test SetTimeOffsetEditorValue function
    */
    void SetTimeOffsetEditorValue( TInt aControlId, const TTimeIntervalSeconds& aTimeOffset );
    
    /**
    *  SetListBoxCurrentItem test function for testing the 
    * Test SetListBoxCurrentItem function
    */
    void SetListBoxCurrentItem( TInt aControlId, TInt aItem );
    
    /**
    *  ListBoxCurrentItem test function for testing the 
    * Test ListBoxCurrentItem function
    */
    TInt ListBoxCurrentItem( TInt aControlId ) const;
    
    /**
    *  SetFileNameL test function for testing the  
    * Test SetFileNameL function
    */
    void SetFileNameL( TInt aControlId, const TDesC* aFileName );
    
    /**
    *  GetFileName test function for testing the  
    * Test GetFileName function
    */
    void GetFileName( TFileName* aFileName, TInt aControlId ) const;
    
    /**
    *  UpdatePageL test function for testing the 
    * Test UpdatePageL function
    */
    void UpdatePageL( TBool aRedraw );
    
    /**
    *  GetAutoValuesFromPage test function for testing the  
    * Test GetAutoValuesFromPage function
    */
    void GetAutoValuesFromPage( CEikCapCArray* aLines );
    };


class CMyDateTimeField : public CTextField
    {
public:
    // from CTextField
    void InternalizeL(RReadStream& aStream)
        {
        }
    TInt Value( TPtr& aValueText )
        {
        if (aValueText.Length() == 0 )
            {
            return 0;
            }
        else
            {
            return aValueText.Length();
            }
        }
    TUid Type() const
        {
        return KDateTimeFieldUid;
        }
    };


#endif /*C_TESTSDKDIALOGSCONTROL_H*/
