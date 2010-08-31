/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

// AknForm.cpp
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//


#include <AknForm.h>
#include <AknQueryDialog.h>
#include <eikdialg.h>
#include <eikmenub.h>
#include <eikenv.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif
#include <eikappui.h>
#include <eiklabel.h>
#include <eikedwin.h>
#include <barsread.h>

#include <avkon.hrh>
#include <avkon.rsg>
#include <aknnotedialog.h>
#include <eikcapc.h>
#include "aknenv.h"
#include <eikedwin.h>

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <gfxtranseffect/gfxtranseffect.h>
#endif

/**
 * Local Panic Function and Panic Codes  (Shared by AknDialog & AknForm)
 */
enum TPanicCodes
	{
	EGeneralFormPanic,
	ENoMenuBar,
	EMenuCommandUnknown
	};

void Panic(TPanicCodes aPanic)
	{
	_LIT(kForm, "AVKON-FORM");
	User::Panic(kForm, aPanic);
	}

/**
 * Constructor 
 */
EXPORT_C CAknForm::CAknForm() 
	{
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Deregister( this );
#endif
    iWsBufferRequestID = iAvkonEnv->RequestWsBuffer( 16000 ); 
	}

/**
 * Creates a default Form menu using default form menu resource.
 * (note that the parameter, a new menu bar resource, is saved for later.
 */
EXPORT_C void CAknForm::ConstructL(TInt aMenuBarId)
	{
	iMenuBarId = aMenuBarId;
	CAknDialog::ConstructL(R_AVKON_FORM_MENUBAR);
	}

/**
 *
 */
EXPORT_C CAknForm::~CAknForm() 
	{
    // cancels large WS client buffer required by form
    iAvkonEnv->CancelWsBufferRequest( iWsBufferRequestID );
	}

/**
 * This function intialises the items on the menu.  It's used to disable and enable menu items and may be
 * over riden to add new ones.
 * In addition it adds menu items which have been provided in the ContsructL in the form of a Menu Bar resource.
 * Instead of using the Menu Bar directly it extracts the menu panes and adds them to it's own menu pane.
 * It must be called in the DynInitMenuPaneL() function of any derived class before anything else!!
 *
 */
EXPORT_C void CAknForm::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane) 
	{
	if (aResourceId == R_AVKON_FORM_MENUPANE)
		{
		if (iMenuBarId)
			{
					
			TResourceReader reader;
			iCoeEnv->CreateResourceReaderLC(reader, iMenuBarId);

			TInt count = reader.ReadInt16();  // Number of menu panes
			while (count--)
				{
				TInt menuPaneResourceId = reader.ReadInt32();
				reader.ReadTPtrC(); // read and ignore the rest...
				reader.ReadInt32();
				reader.ReadTPtrC();
				reader.ReadInt16();
				reader.ReadInt16();
				reader.ReadInt32(); 
				aMenuPane->AddMenuItemsL(menuPaneResourceId, 0, ETrue); // at the top, with a separator
				}
			CleanupStack::PopAndDestroy(); // Resource Reader
			}

		TBool editOptionDimmed = IsEditable();
		aMenuPane->SetItemDimmed(EAknFormCmdEdit, editOptionDimmed);
		aMenuPane->SetItemDimmed(EAknFormCmdSave, !editOptionDimmed);
		aMenuPane->SetItemDimmed(EAknFormCmdLabel, !editOptionDimmed);
		aMenuPane->SetItemDimmed(EAknFormCmdAdd, !editOptionDimmed);
		aMenuPane->SetItemDimmed(EAknFormCmdDelete, !editOptionDimmed);
		}
	}

/**
 *From MEikCommandObserver (act on the menu selection if menu is showing - pass on to client if not processed here)
 */
EXPORT_C void CAknForm::ProcessCommandL(TInt aCommandId)
	{
	CAknDialog::ProcessCommandL(aCommandId);

	switch (aCommandId)
		{
		case EAknFormCmdEdit : // Change into edit state
			if (!IsEditable())
				SetEditableL(ETrue);
			break;
		case EAknFormCmdAdd : // Add Field to Form (display dialog)
			AddItemL();
			break;
		case EAknFormCmdSave : // Save form data (must be implemented by Child) and revert to View Mode
			if (SaveFormDataL()) 
				{
				SetChangesPending( EFalse );
				TBool hasEditModeOnly = FormFlagsFromActivePage()&EEikFormEditModeOnly;
				if (!hasEditModeOnly)
				SetEditableL(EFalse);
				}
			break;
		case EAknFormCmdLabel : // Edit selected label (display dialog)
			EditCurrentLabelL();
			break;
		case EAknFormCmdDelete : // Delete selected item (control)
			DeleteCurrentItemL();
			break;
		default :
			// Default action is to do nothing.
			// Mustn't panic as this function might be called by a child which has already
			// acted upon an action which it has added to the menu.
			break;
		}
	}


/**
 *		From CEikDialog (thence  MEikDialogPageObserver)
 *		If deleting then this routine must not do anything (the default tries to access the control
 *		which has just been deleted!)
 */
EXPORT_C void CAknForm::PrepareForFocusTransitionL()
	{
	if (!Deleting())
		CAknDialog::PrepareForFocusTransitionL();
	}



/**
 *
 * From CEikDialog - Use this to pop up the options menu or close the dialog.
 * Will call SaveFormDataL() before closing if data has been edited.
 * Will NOT permit exit if attempt to save data fails.
 */
EXPORT_C  TBool CAknForm::OkToExitL(TInt aButtonId) 
	{
	TBool hasEditModeOnly = FormFlagsFromActivePage()&EEikFormEditModeOnly;

	if (iMenuBar)
		HideMenu();

	if (aButtonId == EAknSoftkeyOptions)
		{
		DisplayMenuL();
		return EFalse;
		}
	else if ( aButtonId  == EAknSoftkeyBack)
		{
		if (IsEditable())
			{
			TBool mayExitEditMode = ETrue;
			if (UnsavedEdit())
				{
				if ( QuerySaveChangesL() )
					{
					// User has chosen to save. Attempt to save.  Implementation of this
					// may in some situations return EFalse.  This will prevent leaving edit 
					// mode
					mayExitEditMode = SaveFormDataL(); 
					if ( mayExitEditMode )
						SetChangesPending( EFalse );
					}
				else // introduced to allow users to re-set data when a save is undesired.
					DoNotSaveFormDataL();
				}
			if (hasEditModeOnly)
				{
				if ( !mayExitEditMode )
					return EFalse; // stay in Form because save failed  
				}
			else
				{
				if ( mayExitEditMode )
					SetEditableL(EFalse); // go out of edit mode of Form 
				return EFalse; // remain in form ( but in view mode if save was OK).
			}

			} // end of if (IsEditable())

		return ETrue;
		}
    else if (aButtonId == EAknSoftkeyChange)
        {
    	if (ControlOrNull(IdOfFocusControl()))
    	    {
    	    // we need to inform popup field about MSK event
            TKeyEvent event = { EKeyOK, EKeyOK, EModifierPureKeycode, 0 };
        	Line(IdOfFocusControl())->OfferKeyEventL(event, EEventKey );
    	    }
        }
	return EFalse;
	}

EXPORT_C void CAknForm::HandleResourceChange(TInt aType)
	{
	CEikDialog::HandleResourceChange(aType);
	}



/**
 * This routine should be re-implemented by the client to save the contents of the form.
 * The re-implementation can call this function to display the 'Saved' dialog.
 * (CAknForm::SaveFormDataL())
 *
 * This should return ETrue unless there was a problem saving that the user can circumvent
 * If it is a serious system problem, then a Leave should be generated
 *
 * Note that the changes pending flag is not cleared here ( but you could if you want to ); 
 * it is the responsibility of the caller to clear iff return is ETrue.
 */
EXPORT_C  TBool CAknForm::SaveFormDataL()
	{
	return (ETrue);
	}

/**
 * This routine may be overridden.  Default displays 'Save Changes Dialog Yes/No'
 * Returns ETrue if Changes are requested to be saved and then are successfully saved
 * 
 * Re-implementation may put data validation here (as an alternative to over-riding
 * OkToExit - which is a more complicated method )
 *
 * Note that this routine does not perform the changes itself. 
 */
EXPORT_C TBool CAknForm::QuerySaveChangesL()
	{
	CAknQueryDialog* saveChangesDialog = CAknQueryDialog::NewL();
	TInt option = saveChangesDialog->ExecuteLD(R_AVKON_FORM_DEFAULT_SAVE_CHANGES_DIALOG);
	return ( option );
	}

EXPORT_C void CAknForm::SetChangesPending(TBool aChangesPending)
	{
	SetFormFlag( EUnsavedEdit, aChangesPending );
	}


/**
 * This routine may be overridden.  Default displays old label as caption and editor for new one
 * Uses customised dialog 
 */
EXPORT_C void CAknForm::EditCurrentLabelL() 
	{
	const TInt KFurtherTextIrrelevant=30;
	if (!ControlOrNull(IdOfFocusControl()))
		return;
	TPtrC originalLabel = Line(IdOfFocusControl())->GetFullCaptionText();
	TBuf<KFurtherTextIrrelevant> buf= originalLabel.Left(KFurtherTextIrrelevant);
	TResourceReader reader ;
	iCoeEnv->CreateResourceReaderLC( reader, R_AVKON_TEXT_EDIT_LABEL_QUERY_TEXT ) ;
	HBufC* editLabelQueryPrompt = reader.ReadHBufCL();
	CleanupStack::PushL(editLabelQueryPrompt);
	CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL(buf);
	dlg->PrepareLC(R_AVKON_DEFAULT_EDIT_LABEL_QUERY);
	dlg->SetPromptL(*editLabelQueryPrompt);
	TInt queryOk = dlg->RunLD();
	CleanupStack::PopAndDestroy(); // editLabelQueryPrompt
	CleanupStack::PopAndDestroy(); // reader
  	if(queryOk == EAknSoftkeyOk)
		{	
		SetFormFlag( EUnsavedEdit, ETrue );
		TRAP_IGNORE(Line(IdOfFocusControl())->SetCaptionL(buf));
		}
	DrawNow();
	}

/**
 * This routine may be overridden.  Default displays delete item? Yes/No
 * Deletes Item on return from Dialog before returning
 */
EXPORT_C void CAknForm::DeleteCurrentItemL() 
	{
	CAknQueryDialog* deleteItemDialog = CAknQueryDialog::NewL();
	TInt option = deleteItemDialog->ExecuteLD(R_AVKON_FORM_DEFAULT_DELETE_ITEM_DIALOG);
	if (option == EAknSoftkeyYes)
		{
		SetFormFlag( EDeleting, ETrue );

		TInt LineForDeletion = IdOfFocusControl();

		if (LineForDeletion)
			{
			DeleteLine(LineForDeletion);
			SetFormFlag( EUnsavedEdit, ETrue );
			}
		DrawNow();
		SetFormFlag( EDeleting, EFalse );
		}
	}

/**
 * This routine may be overridden.  Default displays Add Item
 * Uses customised dialog
 */
EXPORT_C void CAknForm::AddItemL() 
	{	
	}


/**
 * 
 */
EXPORT_C TBool CAknForm::UnsavedEdit() const
	{
	return (iFlags & EUnsavedEdit);
	}

EXPORT_C TBool CAknForm::Deleting() const
	{
	return (iFlags & EDeleting);
	}


EXPORT_C void CAknForm::PostLayoutDynInitL()
	{
	if (FormFlagsFromActivePage()&EEikFormEditModeOnly)
		SetEditableL(ETrue);
	else 
		SetEditableL(EFalse);
	}

/*
Overridden, so that the form can tell if a line's state has changed.
This is used to decide when to save changes.
*/

EXPORT_C void CAknForm::HandleControlStateChangeL(TInt aControlId)
	{
	SetChangesPending(ETrue);
	CAknDialog::HandleControlStateChangeL(aControlId);
	}

/*
This is added, so that anyone adding lines either in PreLayoutDynInit or SetInitialCurrentLine
should have the lines in a consistent state.
*/
EXPORT_C void CAknForm::SetInitialCurrentLine()
	{
	// call SetEditableL again to put controls in consistent state.
	
	TRAP_IGNORE(SetEditableL(IsEditable()));  // re-run the seteditable to ensure any added lines are in consistent state.
	// ignore e.  
	CAknDialog::SetInitialCurrentLine();
	}

EXPORT_C void CAknForm::SetFormFlag(enum CAknForm::TFlags aFlagPattern, TBool aSetTheFlag )
	{
	if ( aSetTheFlag )
		iFlags |= aFlagPattern;
	else
		iFlags &= (~aFlagPattern);
	}

EXPORT_C void CAknForm::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknDialog::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknForm::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }


EXPORT_C void CAknForm::DoNotSaveFormDataL() 
	{
	
	}; 

EXPORT_C void CAknForm::CEikDialog_Reserved_1() 
	{
	
	}

EXPORT_C void CAknForm::CEikDialog_Reserved_2() 
	{
	
	}

EXPORT_C void CAknForm::CAknDialog_Reserved() 
	{
	
	}

EXPORT_C void CAknForm::CAknForm_Reserved() 
	{
	
	}

void CAknForm::DoLayout()
	{
	Layout();
	}
