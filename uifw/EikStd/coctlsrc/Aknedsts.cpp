/*
* Copyright (c) 1997-2000 Nokia Corporation and/or its subsidiary(-ies).
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



#include "aknedsts.h"
#include "eikccpu.h"
#include "eikmenub.h"
#include <AknFormAccessor.h>
#include <aknedformaccessor.h>
#include <eikedwin.pan>
#include <eikedwin.h>
#include <avkon.rsg>

//
// class CAknEdwinState
//

CAknEdwinState::~CAknEdwinState()
	{
	}

CAknEdwinState::CAknEdwinState(MEikCcpuEditor* aCcpuState) :
	iFlags(EAknEditorFlagDefault),
	iDefaultInputMode(EAknEditorTextInputMode),
	iPermittedInputModes(EAknEditorAllInputModes),
	iDefaultCase(EAknEditorTextCase),
	iPermittedCases(EAknEditorAllCaseModes),
	iLocalLanguage(TLanguage(0)), // explicitly set to language code 0
	iSpecialCharacterTableResourceId(-1), // -1 sets default SCT
	iNumericKeymap(EAknEditorAlphanumericNumberModeKeymap),
	iCcpuState(aCcpuState)
	{
	iCbaState.iLeftSoftkeyCommandId=0;
	iCbaState.iRightSoftkeyCommandId=0;
	iMiddleSoftkeyCommandId=0;
	}

EXPORT_C CAknEdwinState::CAknEdwinState() :
	iFlags(EAknEditorFlagDefault),
	iDefaultInputMode(EAknEditorTextInputMode),
	iPermittedInputModes(EAknEditorAllInputModes),
	iDefaultCase(EAknEditorTextCase),
	iPermittedCases(EAknEditorAllCaseModes),
	iLocalLanguage(TLanguage(0)), // explicitly set to language code 0
	iSpecialCharacterTableResourceId(-1), // -1 sets default SCT
	iNumericKeymap(EAknEditorAlphanumericNumberModeKeymap)
	{
	iCbaState.iLeftSoftkeyCommandId=0;
	iCbaState.iRightSoftkeyCommandId=0;
	iMiddleSoftkeyCommandId=0;
	}

EXPORT_C void CAknEdwinState::SetObserver(MAknEdStateObserver* aObserver)
	{
	iObserver = aObserver;
	}

EXPORT_C void CAknEdwinState::ReportAknEdStateEventL(MAknEdStateObserver::EAknEdwinStateEvent aEventType)
	{
	if (iObserver)
        {
		iObserver->HandleAknEdwinStateEventL(this, aEventType);
        }
	}

EXPORT_C TInt CAknEdwinState::Flags() const
	{
	return iFlags;
	}

EXPORT_C TInt CAknEdwinState::DefaultInputMode() const
	{
	return iDefaultInputMode;
	}

EXPORT_C TInt CAknEdwinState::CurrentInputMode() const
	{
	return iCurrentInputMode;
	}

EXPORT_C TInt CAknEdwinState::PermittedInputModes() const
	{
	return iPermittedInputModes;
	}

EXPORT_C TInt CAknEdwinState::DefaultCase() const
	{
	return iDefaultCase;
	}

EXPORT_C TInt CAknEdwinState::CurrentCase() const
	{
	return iCaseState.CurrentCase();
	}

EXPORT_C TInt CAknEdwinState::PermittedCases() const
	{
	return iPermittedCases;
	}

EXPORT_C TInt CAknEdwinState::DefaultLanguage() const
	{
    // T9 language codes are not anymore supported, use LocalLanguage instead
    return 0;
	}

EXPORT_C TInt CAknEdwinState::SpecialCharacterTableResourceId() const
	{
	return iSpecialCharacterTableResourceId;
	}

EXPORT_C TAknEditorNumericKeymap CAknEdwinState::NumericKeymap() const
	{
	return iNumericKeymap;
	}

EXPORT_C TCursorSelection CAknEdwinState::CurrentInlineEditSpan() const
	{
	return iCurrentInlineEditSpan;
	}

EXPORT_C CAknEdwinState::SEditorCbaState& CAknEdwinState::CbaState()
	{
	return iCbaState;
	}

EXPORT_C MEikCcpuEditor* CAknEdwinState::CcpuState() const
	{
	return iCcpuState;
	}

EXPORT_C CEikMenuBar* CAknEdwinState::MenuBar() const
	{
	return iMenu;
	}

EXPORT_C TLanguage CAknEdwinState::LocalLanguage() const
	{
	return iLocalLanguage;
	}

EXPORT_C CAknEdwinFormAccessor* CAknEdwinState::FormAccessor() const
	{
	return iFormAccessor;
	}

EXPORT_C void CAknEdwinState::SetFlags( TInt aFlags )
	{
    TBool flagsChange( iFlags != aFlags );	
    TInt oldFlags( iFlags );
	iFlags = aFlags;
	if ( flagsChange && iFormAccessor )
	    {
	    CEikEdwin* edwin( static_cast<CEikEdwin*>( 
	        iFormAccessor->FormClientControl() ) );
	    edwin->OnEditorStateFlagChange( oldFlags, aFlags );
	    }
	}

EXPORT_C void CAknEdwinState::SetDefaultInputMode(TInt aInputMode)
	{
	iDefaultInputMode=aInputMode;
	}

EXPORT_C void CAknEdwinState::SetCurrentInputMode(TInt aInputMode)
	{
	iCurrentInputMode=aInputMode;
	}

EXPORT_C void CAknEdwinState::SetPermittedInputModes(TInt aInputModes)
	{
	iPermittedInputModes=aInputModes;
	}

EXPORT_C void CAknEdwinState::SetDefaultCase(TInt aCase)
	{
	iDefaultCase=aCase;
	}

EXPORT_C void CAknEdwinState::SetCurrentCase(TInt aCase)
	{
	iCaseState.SetCurrentCase(aCase);
	iCaseState.SetFlag(TAknEditorCaseState::EFlagSupressAutoUpdateCase);
	}

EXPORT_C void CAknEdwinState::SetPermittedCases(TInt aCases)
	{
	iPermittedCases=aCases;
	}

EXPORT_C void CAknEdwinState::SetDefaultLanguage(TInt /* aLanguage */)
	{
    // T9 language codes are not anymore supported (use SetLocalLanguage instead)    
	}

EXPORT_C void CAknEdwinState::SetSpecialCharacterTableResourceId(TInt aResourceId)
	{
	iSpecialCharacterTableResourceId=aResourceId;
	}

EXPORT_C void CAknEdwinState::SetNumericKeymap(TAknEditorNumericKeymap aKeymap)
	{
	iNumericKeymap=aKeymap;
	}

EXPORT_C void CAknEdwinState::SetInlineEditSpan(TCursorSelection aCurrentInlineEditSpan)
	{
	iCurrentInlineEditSpan=aCurrentInlineEditSpan;
	}

EXPORT_C void CAknEdwinState::SetCba()
	{
	iObjectProvider->MopGetObject(iCbaState.iCurrentCba);
	iCbaState.iLeftSoftkeyCommandId=0;
	iCbaState.iRightSoftkeyCommandId=0;
	iMiddleSoftkeyCommandId=0;
	}

EXPORT_C void CAknEdwinState::SetMenu()
	{
	iObjectProvider->MopGetObject(iMenu);
	}

EXPORT_C void CAknEdwinState::SetLocalLanguage(TLanguage aLanguage)
	{
	iLocalLanguage = aLanguage;
	}

EXPORT_C void CAknEdwinState::SetFormAccessor(CAknEdwinFormAccessor* aFormAccessor)
	{
	iFormAccessor = aFormAccessor;
	}

EXPORT_C void CAknEdwinState::SetCurrentCaseWithNoInitialisation(TInt aCase)
	{
	iCaseState.SetCurrentCase(aCase);
	}

EXPORT_C void CAknEdwinState::SetCcpuState(MEikCcpuEditor* aCcpuEditor)
	{
	iCcpuState=aCcpuEditor;
	}

EXPORT_C TAknEditorCaseState& CAknEdwinState::CaseState()
	{
	return iCaseState;
	}

void CAknEdwinState::CheckLRCursorAndT9Consistency()
	{
#ifdef _DEBUG
	_LIT(KPanicCategory,"CAknEdwinState");
#endif
	__ASSERT_DEBUG(
					(!(iFlags&EAknEditorFlagNoLRNavigation)) ||
					(!(iPermittedInputModes& EAknEditorTextInputMode)),
					User::Panic(KPanicCategory,EEikPanicEdwinInvalidFlagCombination)
				);
	}

EXPORT_C MObjectProvider* CAknEdwinState::ObjectProvider() const
	{
	return iObjectProvider;
	}

EXPORT_C void CAknEdwinState::SetObjectProvider(MObjectProvider* aObjectProvider)
	{
	iObjectProvider = aObjectProvider;
	}


EXPORT_C void CAknEdwinState::SetMiddleSoftkeyCommandId(TInt aCommandId)
	{
	iMiddleSoftkeyCommandId = aCommandId;
	}


EXPORT_C TInt CAknEdwinState::MiddleSoftkeyCommandId() const
	{
	return iMiddleSoftkeyCommandId;
	}


/**
 *	TAknEditorCaseState
 *
 *	Data structure to hold the current state of all case state
 *	information currently held by the fep and applicable to an
 *	editor
 *
 */
EXPORT_C TAknEditorCaseState::TAknEditorCaseState()
	{
	SetFlag(EFlagInitialiseRequired);
	}

EXPORT_C void TAknEditorCaseState::SetCurrentCase(TUint aCase)
	{
	iCurrentCase = STATIC_CAST(TUint8, (aCase&0x000F));  // 0 fill most sig 24 bits and cast
	}

EXPORT_C void TAknEditorCaseState::SetPreviousCase(TUint aCase)
	{
	iPreviousCase = STATIC_CAST(TUint8, (aCase&0x000F));  // 0 fill most sig 24 bits and cast
	}

EXPORT_C void TAknEditorCaseState::SetPreviousCaseUsedToEnterText(TUint aCase)
	{
	iPreviousCaseUsedToEnterText = STATIC_CAST(TUint8, (aCase&0x000F));  // 0 fill most sig 24 bits and cast
	}

EXPORT_C TUint TAknEditorCaseState::CurrentCase() const
	{
	return iCurrentCase;
	}

EXPORT_C TUint TAknEditorCaseState::PreviousCase() const
	{
	return iPreviousCase;
	}

EXPORT_C TUint TAknEditorCaseState::PreviousCaseUsedToEnterText() const
	{
	return iPreviousCaseUsedToEnterText;
	}

EXPORT_C void TAknEditorCaseState::SetFlag(TCaseStateFlags aFlag)
	{
	iFlags |= aFlag;
	}

EXPORT_C void TAknEditorCaseState::ClearFlag(TCaseStateFlags aFlag)
	{
	iFlags &= ~aFlag;
	}

EXPORT_C TBool TAknEditorCaseState::IsFlagSet(TCaseStateFlags aFlag) const
	{
	return iFlags & aFlag;
	}


