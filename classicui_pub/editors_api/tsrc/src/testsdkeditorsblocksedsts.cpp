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
* Description:  Test Aknsedsts.H
*
*/



// [INCLUDE FILES]

#include <aknedsts.h>
#include <eikedwin.h> 

#include "testsdkeditors.h"
#include "testsdkeditorsedstateobserver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECSTAknEditorCaseStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECSTAknEditorCaseStateL( CStifItemParser& /*aItem*/ )
    {
    TAknEditorCaseState caseState;
    STIF_ASSERT_NOT_NULL( &caseState );
    
    caseState.SetCurrentCase( 0 );
    STIF_ASSERT_TRUE( 0 == caseState.CurrentCase() );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECSSetCurrentCaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECSSetCurrentCaseL( CStifItemParser& aItem )
    {
    return TestECSTAknEditorCaseStateL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECSSetPreviousCaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECSSetPreviousCaseL( CStifItemParser& /*aItem*/ )
    {
    TAknEditorCaseState caseState;
    STIF_ASSERT_NOT_NULL( &caseState );
    
    caseState.SetPreviousCase( 0 );
    STIF_ASSERT_TRUE( 0 == caseState.PreviousCase() );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECSSetPreviousCaseUsedToEnterTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECSSetPreviousCaseUsedToEnterTextL( CStifItemParser& /*aItem*/ )
    {
    TAknEditorCaseState caseState;
    STIF_ASSERT_NOT_NULL( &caseState );
    
    caseState.SetPreviousCaseUsedToEnterText( 0 );
    STIF_ASSERT_TRUE( 0 == caseState.PreviousCaseUsedToEnterText() );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECSCurrentCaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECSCurrentCaseL( CStifItemParser& aItem )
    {
    return TestECSTAknEditorCaseStateL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECSPreviousCaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECSPreviousCaseL( CStifItemParser& aItem )
    {
    return TestECSSetPreviousCaseL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECSPreviousCaseUsedToEnterTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECSPreviousCaseUsedToEnterTextL( CStifItemParser& aItem )
    {
    return TestECSSetPreviousCaseUsedToEnterTextL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECSSetFlagL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECSSetFlagL( CStifItemParser& /*aItem*/ )
    {
    TAknEditorCaseState caseState;
    STIF_ASSERT_NOT_NULL( &caseState );
    
    caseState.SetFlag( TAknEditorCaseState::EFlagTextEnteredInCurrentCase );
    STIF_ASSERT_TRUE( caseState.IsFlagSet( TAknEditorCaseState::EFlagTextEnteredInCurrentCase ) );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECSClearFlagL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECSClearFlagL( CStifItemParser& /*aItem*/ )
    {
    TAknEditorCaseState caseState;
    STIF_ASSERT_NOT_NULL( &caseState );
    
    caseState.SetFlag( TAknEditorCaseState::EFlagTextEnteredInCurrentCase );
    caseState.ClearFlag( TAknEditorCaseState::EFlagTextEnteredInCurrentCase );
    STIF_ASSERT_FALSE( caseState.IsFlagSet( TAknEditorCaseState::EFlagTextEnteredInCurrentCase ) );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECSIsFlagSetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECSIsFlagSetL( CStifItemParser& aItem )
    {
    return TestECSSetFlagL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESCAknEdwinStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESCAknEdwinStateL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetObserverL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    CTestSDKEditorsEdStateObserver* observer = CTestSDKEditorsEdStateObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    edwinState->SetObserver( observer );
    
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESReportAknEdStateEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESReportAknEdStateEventL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    CTestSDKEditorsEdStateObserver* observer = CTestSDKEditorsEdStateObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    edwinState->SetObserver( observer );
    edwinState->ReportAknEdStateEventL( MAknEdStateObserver::EAknActivatePenInputRequest );
    
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESFlagsL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetFlags( EAknEditorFlagDefault );
    STIF_ASSERT_TRUE( EAknEditorFlagDefault == edwinState->Flags() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESDefaultInputModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESDefaultInputModeL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetDefaultInputMode( EAknEditorTextInputMode );
    STIF_ASSERT_TRUE( EAknEditorTextInputMode == edwinState->DefaultInputMode() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESCurrentInputModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESCurrentInputModeL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetCurrentInputMode( EAknEditorTextInputMode );
    STIF_ASSERT_TRUE( EAknEditorTextInputMode == edwinState->CurrentInputMode() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESPermittedInputModesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESPermittedInputModesL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetPermittedInputModes( EAknEditorTextInputMode );
    STIF_ASSERT_TRUE( EAknEditorTextInputMode == edwinState->PermittedInputModes() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESDefaultCaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESDefaultCaseL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetDefaultCase( EAknEditorUpperCase );
    STIF_ASSERT_TRUE( EAknEditorUpperCase == edwinState->DefaultCase() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESCurrentCaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESCurrentCaseL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetCurrentCase( EAknEditorUpperCase );
    STIF_ASSERT_TRUE( EAknEditorUpperCase == edwinState->CurrentCase() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESPermittedCasesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESPermittedCasesL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetPermittedCases( EAknEditorUpperCase );
    STIF_ASSERT_TRUE( EAknEditorUpperCase == edwinState->PermittedCases() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESDefaultLanguageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESDefaultLanguageL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetDefaultLanguage( ELangEnglish );
    STIF_ASSERT_TRUE( 0 == edwinState->DefaultLanguage() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSpecialCharacterTableResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSpecialCharacterTableResourceIdL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetSpecialCharacterTableResourceId( 0 );
    STIF_ASSERT_TRUE( 0 == edwinState->SpecialCharacterTableResourceId() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESNumericKeymapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESNumericKeymapL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetCurrentInputMode( EAknEditorNumericInputMode );
    edwinState->SetNumericKeymap( EAknEditorStandardNumberModeKeymap );
    STIF_ASSERT_TRUE( EAknEditorStandardNumberModeKeymap == edwinState->NumericKeymap() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESCurrentInlineEditSpanL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESCurrentInlineEditSpanL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    TCursorSelection crusorSelection;
    edwinState->SetInlineEditSpan( crusorSelection );
    STIF_ASSERT_TRUE( crusorSelection.LowerPos() == edwinState->CurrentInlineEditSpan().LowerPos() );
    STIF_ASSERT_TRUE( crusorSelection.HigherPos() == edwinState->CurrentInlineEditSpan().HigherPos() );
    STIF_ASSERT_TRUE( crusorSelection.Length() == edwinState->CurrentInlineEditSpan().Length() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESCbaStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESCbaStateL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    CAknEdwinState::SEditorCbaState cbaState = edwinState->CbaState();
    STIF_ASSERT_EQUALS( 0, cbaState.iLeftSoftkeyCommandId );
    STIF_ASSERT_EQUALS( 0, cbaState.iRightSoftkeyCommandId );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESMenuBarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESMenuBarL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    CEikMenuBar* menuBar = edwinState->MenuBar();
    STIF_ASSERT_NULL( menuBar );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESCcpuStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESCcpuStateL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    edwinState->SetCcpuState( edwin );
    MEikCcpuEditor* ccpu = edwinState->CcpuState();
    STIF_ASSERT_NOT_NULL( ccpu );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESObjectProviderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESObjectProviderL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    CTestSDKEditorsEdStateObserver* provider = CTestSDKEditorsEdStateObserver::NewL();
    CleanupStack::PushL( provider );
    STIF_ASSERT_NOT_NULL( provider );
    
    edwinState->SetObjectProvider( provider );
    STIF_ASSERT_NOT_NULL( edwinState->ObjectProvider() );
    STIF_ASSERT_TRUE( provider == edwinState->ObjectProvider() );
    
    CleanupStack::PopAndDestroy( provider );
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESLocalLanguageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESLocalLanguageL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetLocalLanguage( ELangEnglish );
    STIF_ASSERT_TRUE( ELangEnglish == edwinState->LocalLanguage() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESFormAccessorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESFormAccessorL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    CAknEdwinFormAccessor* aormAccessor = NULL;
    edwinState->SetFormAccessor( aormAccessor );
    STIF_ASSERT_TRUE( NULL == edwinState->FormAccessor() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetFlagsL( CStifItemParser& aItem )
    {
    return TestESFlagsL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetDefaultInputModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetDefaultInputModeL( CStifItemParser& aItem )
    {
    return TestESDefaultInputModeL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetCurrentInputModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetCurrentInputModeL( CStifItemParser& aItem )
    {
    return TestESCurrentInputModeL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetPermittedInputModesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetPermittedInputModesL( CStifItemParser& aItem )
    {
    return TestESPermittedInputModesL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetDefaultCaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetDefaultCaseL( CStifItemParser& aItem )
    {
    return TestESDefaultCaseL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetCurrentCaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetCurrentCaseL( CStifItemParser& aItem )
    {
    return TestESCurrentCaseL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetPermittedCasesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetPermittedCasesL( CStifItemParser& aItem )
    {
    return TestESPermittedCasesL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetDefaultLanguageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetDefaultLanguageL( CStifItemParser& aItem )
    {
    return TestESDefaultLanguageL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetSpecialCharacterTableResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetSpecialCharacterTableResourceIdL( CStifItemParser& aItem )
    {
    return TestESSpecialCharacterTableResourceIdL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetNumericKeymapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetNumericKeymapL( CStifItemParser& aItem )
    {
    return TestESNumericKeymapL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetInlineEditSpanL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetInlineEditSpanL( CStifItemParser& aItem )
    {
    return TestESCurrentInlineEditSpanL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetCbaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetCbaL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    CTestSDKEditorsEdStateObserver* provider = CTestSDKEditorsEdStateObserver::NewL();
    CleanupStack::PushL( provider );
    STIF_ASSERT_NOT_NULL( provider );
    
    edwinState->SetObjectProvider( static_cast<MObjectProvider*>(provider) );
    
    edwinState->SetCba();
    CAknEdwinState::SEditorCbaState cbaState = edwinState->CbaState();
    STIF_ASSERT_EQUALS( 0, cbaState.iLeftSoftkeyCommandId );
    STIF_ASSERT_EQUALS( 0, cbaState.iRightSoftkeyCommandId );
    
    CleanupStack::PopAndDestroy( provider );
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetMenuL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetMenuL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    CTestSDKEditorsEdStateObserver* provider = CTestSDKEditorsEdStateObserver::NewL();
    CleanupStack::PushL( provider );
    STIF_ASSERT_NOT_NULL( provider );
    
    edwinState->SetObjectProvider( static_cast<MObjectProvider*>(provider) );

    edwinState->SetMenu();
    
    CleanupStack::PopAndDestroy( provider );
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetObjectProviderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetObjectProviderL( CStifItemParser& aItem )
    {
    return TestESObjectProviderL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetLocalLanguageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetLocalLanguageL( CStifItemParser& aItem )
    {
    return TestESLocalLanguageL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetFormAccessorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetFormAccessorL( CStifItemParser& aItem )
    {
    return TestESFormAccessorL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetCcpuStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetCcpuStateL( CStifItemParser& aItem )
    {
    return TestESCcpuStateL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESSetMiddleSoftkeyCommandIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESSetMiddleSoftkeyCommandIdL( CStifItemParser& /*aItem*/ )
    {
    CAknEdwinState* edwinState = new (ELeave) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    STIF_ASSERT_NOT_NULL( edwinState );
    
    edwinState->SetMiddleSoftkeyCommandId( 0 );
    STIF_ASSERT_TRUE( 0 == edwinState->MiddleSoftkeyCommandId() );
    
    CleanupStack::PopAndDestroy( edwinState );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESMiddleSoftkeyCommandIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESMiddleSoftkeyCommandIdL( CStifItemParser& aItem )
    {
    return TestESSetMiddleSoftkeyCommandIdL( aItem );
    
    }
