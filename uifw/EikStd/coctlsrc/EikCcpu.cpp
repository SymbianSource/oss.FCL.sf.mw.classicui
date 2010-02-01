/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefmacros.h>
#endif
#include "eikccpu.h"
#include <eikedwin.h>
#include <eikbtgpc.h>
#include <aknenv.h>
#include <avkon.rsg>
#include <avkon.hrh>
#include <eikappui.h>

const TInt ELeftSoftkeyIndex = 0;
const TInt ERightSoftkeyIndex = 2;
const TInt ENullCommandId = -1;


//
// CAknCcpuSupport
//

enum TAknCcpuSupportFlags
	{
	EFocused
	};

EXPORT_C CAknCcpuSupport::CAknCcpuSupport(MEikCcpuEditor* aEditor)
: iEditor(aEditor)
	{
	}

EXPORT_C CAknCcpuSupport::~CAknCcpuSupport()
	{
	if (iMenu)
		iMenu->RemoveEditMenuObserver(this);
	delete iCba;
	iEikonEnv->EikAppUi()->RemoveFromStack(this);
	}

EXPORT_C void CAknCcpuSupport::ConstructL()
	{
	iEikonEnv->EikAppUi()->AddToStackL(this, ECoeStackPriorityFep-1, ECoeStackFlagRefusesFocus);
	HandleFocusChangeL();
	}

EXPORT_C void CAknCcpuSupport::HandleSelectionChangeL()
	{
	if (iCba)
		UpdateCBALabelsL();
	}

EXPORT_C void CAknCcpuSupport::HandleFocusChangeL()
	{
	TBool focused = iEditor->CcpuIsFocused();
	if (COMPARE_BOOLS(focused, iFlags[EFocused]))
		return;

	iFlags.Assign(EFocused, focused);

	if (focused)
		{
		MopGetObject(iMenu);

		if (iMenu)
			iMenu->SetEditMenuObserver(this);
		}
	else
		{
		if (iMenu)
			{
			iMenu->RemoveEditMenuObserver(this);
			iMenu = NULL;
			}
		}

	if (iCba && !focused)
		{
		// something has caused loss of focus while shift is pressed - drop everything.
		delete iCba;
		iCba = NULL;
		}
	}

EXPORT_C TKeyResponse CAknCcpuSupport::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	if (!iFlags[EFocused])
		return EKeyWasNotConsumed;

	if (aKeyEvent.iCode == EKeyF21)		// FEP generates F21 on long shift press
		{
		if (aType == EEventKey)
			{
			delete iCba;
			iCba = NULL;
			iCba = CEikButtonGroupContainer::NewL(CEikButtonGroupContainer::ECba, CEikButtonGroupContainer::EHorizontal, this, R_AVKON_SOFTKEYS_EMPTY);
			iCba->SetBoundingRect(iEikonEnv->EikAppUi()->ApplicationRect());
			UpdateCBALabelsL();
			}
		return EKeyWasConsumed;
		}  
    else if (aType == EEventKey &&
             aKeyEvent.iCode == EKeyF18 &&
             (aKeyEvent.iModifiers & EModifierCtrl))			
        {
        // FEP requests Ccpu actions with CTRL + F18         
        // Requested action is encoded in iScanCode.
        ProcessCommandL(aKeyEvent.iScanCode);
       	return EKeyWasConsumed;
        }					
	else if ((aKeyEvent.iScanCode == EStdKeyLeftShift || aKeyEvent.iScanCode == EStdKeyRightShift) && aType == EEventKeyUp)
		{
		delete iCba;
		iCba = NULL;
		}
	
	return EKeyWasNotConsumed;
	}

EXPORT_C void CAknCcpuSupport::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
	{
	if (aResourceId == R_AVKON_EDIT_MODE_MENU || 
		aResourceId == R_AVKON_EDIT_TEXT_MENU)
		{
		aMenuPane->SetItemDimmed(EEikCmdEditCut,!iEditor->CcpuCanCut());
		aMenuPane->SetItemDimmed(EEikCmdEditCopy,!iEditor->CcpuCanCopy());
		aMenuPane->SetItemDimmed(EEikCmdEditPaste,!iEditor->CcpuCanPaste());
		}
	}

EXPORT_C void CAknCcpuSupport::ProcessCommandL(TInt aCommandId)
	{
	switch (aCommandId)
		{
		case EEikCmdEditCut:
			iEditor->CcpuCutL();
			break;
		case EEikCmdEditCopy:
			iEditor->CcpuCopyL();
			break;
		case EEikCmdEditPaste:
			iEditor->CcpuPasteL();
			break;
		case EEikCmdEditUndo:
			iEditor->CcpuUndoL();
			break;
		default:
			break;
		}
	}

void CAknCcpuSupport::UpdateCBALabelsL()
	{
	TBool change = EFalse;

	if (iEditor->CcpuCanCopy())
		change = UpdateCBALabelL(ELeftSoftkeyIndex, EEikCmdEditCopy, R_TEXT_SOFTKEY_COPY) || change;
	else
		change = UpdateCBALabelL(ELeftSoftkeyIndex, ENullCommandId, R_TEXT_SOFTKEY_EMPTY) || change;

	if (iEditor->CcpuCanPaste())
		change = UpdateCBALabelL(ERightSoftkeyIndex, EEikCmdEditPaste, R_TEXT_SOFTKEY_PASTE) || change;
	else
		change = UpdateCBALabelL(ERightSoftkeyIndex, ENullCommandId, R_TEXT_SOFTKEY_EMPTY) || change;

	if (change)
		iCba->DrawNow();
	}

TBool CAknCcpuSupport::UpdateCBALabelL(TInt aPosition, TInt aCommandId, TInt aTextResId)
	{
	if (iCba->ButtonGroup()->CommandId(aPosition) != aCommandId)
		{
		HBufC* buf = iEikonEnv->AllocReadResourceLC(aTextResId);
		iCba->SetCommandL(aPosition, aCommandId, *buf);
		CleanupStack::PopAndDestroy(buf);
		return ETrue;
		}
	return EFalse;
	}

void CAknCcpuSupport::SetEmphasis(CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/)
	{
	}

EXPORT_C void CAknCcpuSupport::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknCcpuSupport::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }


