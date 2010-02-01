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
*	Implementation of CAknPasswordSettingPage, (pure virtual) and its descendants,
*	CAknAlphaPasswordSettingPage and CAknNumericPasswordSettingPage
*   
*
*/

//////////////////////////////////////////////////////////////////////
//
// AknPasswordSettingPage.cpp
//
//////////////////////////////////////////////////////////////////////

#include "aknpasswordsettingpage.h"
#include "aknsettingpage.h"
#include "aknnotedialog.h"

//For TResourceReader
#include <barsread.h>

#include <coemain.h>
#include <coecntrl.h>
#include <coecobs.h>

//For CEikEnv
#include <eikenv.h>

// For queries
#include <AknQueryDialog.h>

//For the different layout definitions
#include <avkon.hrh>                                             
#include <aknlayoutscalable_avkon.cdl.h>


#include <AknTasHook.h>

//////////////////////////////////////////////////////////////////////
//
//  PASSWORD SETTING PAGE BASE CLASS
//
// This class holds the main data model for the password setting pages.
// It also does the drawing and other functions.
//
//////////////////////////////////////////////////////////////////////

/**
 *
 * Constructor from setting page resource id: Pass through to base class 
 *
 */
EXPORT_C CAknPasswordSettingPage::CAknPasswordSettingPage(
	TInt aResourceId, 
	TDes& aNewPassword, 
	const TDesC& aOldPassword )
		:	CAknSettingPage( aResourceId), 
			iNewPassword(aNewPassword),
			iOldPassword(aOldPassword)
	{
	SetMatchingMode( ECaseSensitive );
	AKNTASHOOK_ADD( this, "CAknPasswordSettingPage" );
	}


EXPORT_C CAknPasswordSettingPage::CAknPasswordSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TDes& aNewPassword, 
								const TDesC& aOldPassword )
								:	CAknSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId) , 
									iNewPassword( aNewPassword ),
									iOldPassword( aOldPassword )
	{
	SetMatchingMode( ECaseSensitive );
	AKNTASHOOK_ADD( this, "CAknPasswordSettingPage" );
	}

/**
 * Acts upon changes in the hosted control's state. 
 *
 * @param	aControl	The control changing its state (not used)
 * @param	aEventType	The type of control event 
 */
EXPORT_C void CAknPasswordSettingPage::HandleControlEventL(CCoeControl* /*aControl*/,
				 MCoeControlObserver::TCoeEvent aEventType)
	{
	// This event is used as it is called at least every time an edit is made to 
	// the editor
	if ( aEventType == EEventStateChanged && iUpdateMode == EUpdateWhenChanged)
		{
		UpdateSettingL();
		}
	}

/**
 *
 * Routine to set up the resources for old password confirmation. 
 *
 */
EXPORT_C void CAknPasswordSettingPage::SetOldPasswordConfirmationResourceId( TInt aConfirmationResourceId )
	{
	iOldPasswordConfirmationResourceId = aConfirmationResourceId;
	}
/**
 *
 * Routine to set up the resources for new password confirmation. 
 *
 */
EXPORT_C void CAknPasswordSettingPage::SetNewPasswordConfirmationResourceId( TInt aConfirmationResourceId )
	{
	iNewPasswordConfirmationResourceId = aConfirmationResourceId;
	}

/**
 *
 * Access routine for the confirmation resource structure 
 *
 */
EXPORT_C TInt CAknPasswordSettingPage::OldPasswordConfirmationResourceId() const
	{
	return iOldPasswordConfirmationResourceId;
	}
/**
 *
 * Access routine for the confirmation resource structure 
 *
 */
EXPORT_C TInt CAknPasswordSettingPage::NewPasswordConfirmationResourceId() const
	{
	return iNewPasswordConfirmationResourceId;
	}

/**
 * Sets the mode for the matching that will be performed
 *
 */
EXPORT_C void CAknPasswordSettingPage::SetMatchingMode( TAknPasswordMatchingMode aMode )
	{
	iMatchingMode = aMode;
	}
/**
 * Access method for the matching mode
 *
 */
EXPORT_C CAknPasswordSettingPage::TAknPasswordMatchingMode CAknPasswordSettingPage::MatchingMode()
	{
	return iMatchingMode;
	}

/**
 * Sets the maximum number of characters that will be allowed to enter or to match
 *
 */
EXPORT_C void CAknPasswordSettingPage::SetMaxPasswordLength( TInt aMaxLength )
	{
	iMaxPasswordLength = aMaxLength;
	}
/**
 * Access method for the maximum password length
 *
 *
 */
EXPORT_C TInt CAknPasswordSettingPage::MaxPasswordLength() const
	{
	return iMaxPasswordLength;
	}

/**
 * Access method for the new password
 *
 */
EXPORT_C TDes& CAknPasswordSettingPage::NewPassword() const
	{
	return iNewPassword;
	}

/**
 * Access method for the old password
 *
 */
EXPORT_C const TDesC& CAknPasswordSettingPage::OldPassword() const
	{
	return iOldPassword;
	}

/**
 *
 * This routine is called when the a change is detected in the editor.
 * The text is copied out to the referenced descriptor using a utility routine.
 *
 */
EXPORT_C void CAknPasswordSettingPage::UpdateSettingL()
	{
	UpdateTextL();

	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);	

	}


/**
 * Checks if it OK to exit. This implementation performs a new password confirmation if the resource is defined
 * If there is no confirmation resource defined, then we exit.
 * If there is, then a confirmation query is put up.  Upon exit, if the match is OK, then we exit 
 * 
 * Returns ETrue if the dialog is ready to exit. Returns ETrue by default.
 */
EXPORT_C TBool CAknPasswordSettingPage::OkToExitL(TBool aAccept )
    {
	 if ( aAccept )
		{
		return ExecuteNewPasswordConfirmationL( NewPassword(), NewPasswordConfirmationResourceId() ) ;
		// SetFocusToEditor();   // Should the focus be changed somewhere else?
		}
	 else
	    return(ETrue); 
    }


/**
 *
 * The value is copied out and the call back called if there is an observer
 *
 */
EXPORT_C void CAknPasswordSettingPage::AcceptSettingL()
	{
	UpdateTextL();
	}

/**
 * Reads in the resource structure associated with a password confirmation (old or new)
 *
 */
EXPORT_C void CAknPasswordSettingPage::ReadConfirmationResourceL( TInt aResourceId, SAknConfirmationResource& resources )
	{
	TResourceReader reader;
	iCoeEnv->CreateResourceReaderLC( reader,aResourceId );

	resources.iEntryQueryResourceId = reader.ReadInt32();
	resources.iSuccessNoteResourceId = reader.ReadInt32();
	resources.iFailureNoteResourceId = reader.ReadInt32();

	CleanupStack::PopAndDestroy(); //reader	

	}

/**
 * Activity to run after the setting page is displayed
 *
 */
 
EXPORT_C void CAknPasswordSettingPage::PostDisplayInitL()
	 {}

EXPORT_C TBool CAknPasswordSettingPage::PostDisplayCheckL()
	{
	return ExecuteOldPasswordConfirmationL( OldPassword(), OldPasswordConfirmationResourceId() ) ;
	}

/**
 * Base implementation of this framework method. Just call the generic Do.. routine
 * This implementation does not use "tries" but this may be a useful piece of information
 */
EXPORT_C TBool CAknPasswordSettingPage::ExecuteOldPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId )
	{
	// This check is done internally to allow completely different derivation of the resources
	if ( aPasswordConfirmationResourceId )
		{
		TInt tries;
		return DoPasswordConfirmationL(aPassword, aPasswordConfirmationResourceId, MatchingMode(), tries);
		}
	else
		return ETrue; // because no check has been defined
	}

/**
 * Base implementation of this framework method. Just call the generic Do.. routine
 *
 */
EXPORT_C TBool CAknPasswordSettingPage::ExecuteNewPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId )
	{
	// This check is done internally to allow completely different derivation of the resources
	if ( aPasswordConfirmationResourceId )
		{
		TInt tries;
		return DoPasswordConfirmationL(aPassword, aPasswordConfirmationResourceId, MatchingMode(), tries );
		}
	else
		return ETrue; // No check defined
	}

/**
 *  Default implementation of a password confirmation procedure
 *
 */
EXPORT_C TBool CAknPasswordSettingPage::DoPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId, TAknPasswordMatchingMode aMatchMode, TInt& aTries )
	{
	TBool retVal = EFalse;

	// zero the number of tries
	aTries = 0;

	// 
	// Read the resource for the dialogs
	//
	SAknConfirmationResource confResources;
	ReadConfirmationResourceL( aPasswordConfirmationResourceId, confResources );

	if (confResources.iEntryQueryResourceId )
		{
		// Put up a query note for the password entry
		// Produce candidate text descriptor
		HBufC* aEnteredTextBuf = HBufC::NewLC( MaxPasswordLength() );
		TPtr aEnteredTextPtr = aEnteredTextBuf->Des();

		CAknTextQueryDialog* dlgQuery = CAknTextQueryDialog::NewL(aEnteredTextPtr, CAknQueryDialog::ENoTone);

		if ( dlgQuery->ExecuteLD( confResources.iEntryQueryResourceId ) )
			{
			// Increment the tries
			aTries++;

			if ( ComparePasswords( aPassword, aEnteredTextPtr, aMatchMode ) == 0 )
				{
				// put up success note if specified
				if ( confResources.iSuccessNoteResourceId )
					{
					CAknNoteDialog* dlgSuccessNote = new (ELeave) CAknNoteDialog(CAknNoteDialog::ENoTone,CAknNoteDialog::ELongTimeout);
					dlgSuccessNote->PrepareLC(confResources.iSuccessNoteResourceId);
					dlgSuccessNote->RunLD();
					}
				// nothing otherwise
				retVal = ETrue;
				}
			else
				{
				// failure note
				if ( confResources.iFailureNoteResourceId )
					{
					CAknNoteDialog* dlgFailureNote = new (ELeave) CAknNoteDialog(CAknNoteDialog::ENoTone,CAknNoteDialog::ELongTimeout);
					dlgFailureNote->PrepareLC(confResources.iFailureNoteResourceId);
					dlgFailureNote->RunLD();
					}
				// nothing otherwise
				retVal = EFalse;
		
				}
			}
		CleanupStack::PopAndDestroy(); //  aEnteredTextBuf 

		}

	return (retVal);
	}

EXPORT_C TInt CAknPasswordSettingPage::ComparePasswords( const TDesC& aRefPassword, const TDesC& aCandidatePassword, enum CAknPasswordSettingPage::TAknPasswordMatchingMode /*aMode*/) const
	{
	// This comparison needs changing for mode. 
	return aRefPassword.Compare( aCandidatePassword );
	}

EXPORT_C void CAknPasswordSettingPage::SizeChanged()
	{
	StandardSettingPageLayout();  // Must be part of any re-implementation
	
    iSecretEditorLayoutRect.LayoutRect( 
            CAknSettingPage::SettingItemContentRect( EFalse ),
            AknLayoutScalable_Avkon::setting_code_pane_copy1() );

    TRect editorRect = iSecretEditorLayoutRect.Rect();

	iHorizontalShadow.LayoutRect(editorRect, 
		AKN_LAYOUT_WINDOW_Code_time_and_date_entry_pane_elements_Line_1);
	iVerticalShadow.LayoutRect(editorRect, 
		AKN_LAYOUT_WINDOW_Code_time_and_date_entry_pane_elements_Line_2);
	iOutlineFrame.LayoutRect(editorRect, 
		AKN_LAYOUT_WINDOW_Code_time_and_date_entry_pane_elements_Line_3);

    AknLayoutUtils::LayoutSecretEditor( ( CEikSecretEditor * )EditorControl(), 
    editorRect, AknLayoutScalable_Avkon::setting_code_pane_t1_copy1() );

	TRAP_IGNORE(((CEikSecretEditor*)EditorControl())->SetSkinTextColorL(EAknsCIQsnTextColorsCG26));

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(
        editorRect,
        AknLayoutScalable_Avkon::input_focus_pane_cp2_copy1() );
    TRect editorFrameRect( layoutRect.Rect() );
    
    layoutRect.LayoutRect(
        editorFrameRect,
        AknLayoutScalable_Avkon::set_opt_bg_pane_g1_copy1() );
    
    SetEditedItemFrameRects( editorFrameRect, layoutRect.Rect() );
    
    layoutRect.LayoutRect(
        editorRect,
        AknLayoutScalable_Avkon::indicator_popup_pane_cp6() );
    SetEditorIndicatorRect( layoutRect.Rect() );
	}

/**
 * All password setting pages containing edwins will have the same draw code
 *
 */
EXPORT_C void CAknPasswordSettingPage::Draw(const TRect& aRect) const
	{
	BaseDraw( aRect );
	// Suppress this legacy frame drawing if skins is performing it
	if ( !IsSkinsHandlingEditorFrameDrawing() )
		{
		CWindowGc& gc=SystemGc(); 
		iSecretEditorLayoutRect.DrawRect( gc );
		iHorizontalShadow.DrawRect( gc );
		iVerticalShadow.DrawRect( gc );
		iOutlineFrame.DrawOutLineRect( gc );
		}
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknPasswordSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknPasswordSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknPasswordSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknPasswordSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknPasswordSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknPasswordSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknPasswordSettingPage::CAknSettingPage_Reserved_2()
	{
	}
//////////////////////////////////////////////////////////////////////
//
//  ALPHA PASSWORD SETTING PAGE
//
//////////////////////////////////////////////////////////////////////

/**
 *
 * Constructor from setting page resource id + referenced passwords.
 *
 */
EXPORT_C CAknAlphaPasswordSettingPage::CAknAlphaPasswordSettingPage( 
	TInt aResourceId, 
	TDes& aNewPassword, 
	const TDesC& aOldPassword ):
	CAknPasswordSettingPage(aResourceId, aNewPassword, aOldPassword)
	{
	SetMaxPasswordLength( KDefaultAlphaPasswordLength );
	AKNTASHOOK_ADD( this, "CAknAlphaPasswordSettingPage" );
	}

EXPORT_C CAknAlphaPasswordSettingPage::CAknAlphaPasswordSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TDes& aNewPassword, 
								const TDesC& aOldPassword )
								:	CAknPasswordSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId,
									aNewPassword, 
									aOldPassword )
	{
	SetMaxPasswordLength( KDefaultAlphaPasswordLength );
	AKNTASHOOK_ADD( this, "CAknAlphaPasswordSettingPage" );
	}

/**
 * Destructor
 *
 */
EXPORT_C CAknAlphaPasswordSettingPage::~CAknAlphaPasswordSettingPage()
	{
	AKNTASHOOK_REMOVE();
	}


/** 
 *
 * The 2nd stage construction. Stored internal resource is used to perform the
 * construction.
 * Secret editor is reset to zero length.
 *
 */
EXPORT_C void CAknAlphaPasswordSettingPage::ConstructL()
	{
	BaseConstructL();
	AlphaPasswordEditor()->SetBorder( TGulBorder::ENone );
	AlphaPasswordEditor()->Reset();
	// Construct an appropriate control context for the contained editor areas.
	// Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrInput, KAknsIIDQsnFrInputCenter );
	}

/**
 * Soak up function to do the safe copying of the editor to the referenced value
 *
 */
EXPORT_C void CAknAlphaPasswordSettingPage::UpdateTextL()
	{
	AlphaPasswordEditor()->GetText( NewPassword() );
	}

/**
 * Compares the given passwords.
 * Supports folding matching.
 */
EXPORT_C TInt CAknAlphaPasswordSettingPage::ComparePasswords( const TDesC& aRefPassword, const TDesC& aCandidatePassword, enum CAknPasswordSettingPage::TAknPasswordMatchingMode aMode) const
	{
	TBool retVal(EFalse);

    if ( aMode == ECaseSensitive )
        retVal = aRefPassword.Compare( aCandidatePassword );
    else
        retVal = aRefPassword.CompareF( aCandidatePassword );
        
    return retVal;
	}

/** 
 *
 * Type-specific access to the alpha password editor control
 *
 */
EXPORT_C CEikSecretEditor* CAknAlphaPasswordSettingPage::AlphaPasswordEditor()
	{
	return STATIC_CAST( CEikSecretEditor*, EditorControl());
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknAlphaPasswordSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknAlphaPasswordSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknPasswordSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknAlphaPasswordSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknPasswordSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknAlphaPasswordSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknAlphaPasswordSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknAlphaPasswordSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknAlphaPasswordSettingPage::CAknSettingPage_Reserved_2()
	{
	}

//////////////////////////////////////////////////////////////////////
//
//  NUMERIC PASSWORD SETTING PAGE
//
//////////////////////////////////////////////////////////////////////



/**
 *
 * Constructor from setting page resource id + referenced passwords.
 *
 */
EXPORT_C CAknNumericPasswordSettingPage::CAknNumericPasswordSettingPage( 
	TInt aResourceId, 
	TDes& aNewPassword, 
	const TDesC& aOldPassword ):
	CAknPasswordSettingPage(aResourceId, aNewPassword, aOldPassword)
	{
	SetMaxPasswordLength( KDefaultNumericPasswordLength );
	AKNTASHOOK_ADD( this, "CAknNumericPasswordSettingPage" );
	}


EXPORT_C CAknNumericPasswordSettingPage::CAknNumericPasswordSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TDes& aNewPassword, 
								const TDesC& aOldPassword )
								:	CAknPasswordSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId,
									aNewPassword, 
									aOldPassword )
	{
	SetMaxPasswordLength( KDefaultNumericPasswordLength );
	AKNTASHOOK_ADD( this, "CAknNumericPasswordSettingPage" );
	}

/**
 * Destructor
 *
 */
EXPORT_C CAknNumericPasswordSettingPage::~CAknNumericPasswordSettingPage()
	{
	AKNTASHOOK_REMOVE();
	}


/** 
 *
 * The 2nd stage construction. Stored internal resource is used to perform the
 * construction.
 * Secret editor is reset to zero length.
 *
 */
EXPORT_C void CAknNumericPasswordSettingPage::ConstructL()
	{
	BaseConstructL();
	NumericPasswordEditor()->SetBorder( TGulBorder::ENone );
	NumericPasswordEditor()->Reset();
	// Construct an appropriate control context for the contained editor areas.
	// Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrInput, KAknsIIDQsnFrInputCenter );
	}

/**
 * Soak up function to do the safe copying of the editor to the referenced value
 *
 */
EXPORT_C void CAknNumericPasswordSettingPage::UpdateTextL()
	{
	NumericPasswordEditor()->GetText( NewPassword() );
	}
/** 
 *
 * Type-specific access to the alpha password editor control
 *
 */
EXPORT_C CAknNumericSecretEditor* CAknNumericPasswordSettingPage::NumericPasswordEditor()
	{
	return STATIC_CAST( CAknNumericSecretEditor*, EditorControl());
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknNumericPasswordSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknNumericPasswordSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknPasswordSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknNumericPasswordSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknPasswordSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknNumericPasswordSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }
    
/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknNumericPasswordSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknNumericPasswordSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknNumericPasswordSettingPage::CAknSettingPage_Reserved_2()
	{
	}

// End of File
