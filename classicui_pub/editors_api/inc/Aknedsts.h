/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Data structures to store current state of case
*  		    	 modes.
*
*/


// INCLUDES 
#if !defined(__EIKEDSTS_H__)
#define __EIKEDSTS_H__

#if !defined(__FEPBASE_H__)
#include <fepbase.h>
#endif

#if !defined(__AKNEDSTSOBS_H__)
#include <aknedstsobs.h>
#endif

#if !defined(__UIKON_HRH__)
#include <uikon.hrh>
#endif

#include <eikon.hrh>

#include <frmtlay.h>

// CLASS DECLARATION

/**
*  Data structure to store current state of case modes.
*  
*  Data structure to hold the current state of all case state
*  information currently held by the fep and applicable to an
*  editor.
*
*  @since Series 60 0.9
*/
class TAknEditorCaseState
	{
public:
	/**
	* Flags that indicate states of the case.
	*/
	enum TCaseStateFlags
		{
		/** Has text been entered with current case. */
		EFlagTextEnteredInCurrentCase	=0x00000001,    
		
		/** Initialisation is required. */
		EFlagInitialiseRequired			=0x00000002,    
		
		/** Supress case's automatic update. */
		EFlagSupressAutoUpdateCase		=0x00000004     
		
		};
public:
	        
    /**
    * C++ default constructor.
    */
	IMPORT_C TAknEditorCaseState();
	        
    /**
    * Sets current case.
    * @param aCase A new case.
    */
	IMPORT_C void SetCurrentCase(TUint aCase);
	        
    /**
    * Sets previous case.
    * @param aCase a Previously used case.
    */
	IMPORT_C void SetPreviousCase(TUint aCase);
	        
    /**
    * Sets previous case used to enter text.
    * @param aCase Previously used case to enter text.
    */
	IMPORT_C void SetPreviousCaseUsedToEnterText(TUint aCase);
	
		        
    /**
    * Gets current case.
    * @return The current case.
    */
	IMPORT_C TUint CurrentCase() const;
		        
    /**
    * Gets previous case.
    * @return The previous case.
    */
	IMPORT_C TUint PreviousCase() const;
		        
    /**
    * Gets previous case used to enter text.
    * @return The previous case used to enter text.
    */
	IMPORT_C TUint PreviousCaseUsedToEnterText() const;

	// flags
	        
    /**
    * Sets a flag.
    * @param aFlag a Flag to be set.
    */
	IMPORT_C void SetFlag(TCaseStateFlags aFlag);
	        
    /**
    * Clear the given flag. 
    * @param aFlag a Flag to be cleared.
    */
	IMPORT_C void ClearFlag(TCaseStateFlags aFlag);
	        
    /**
    * Tells whether the given flag is set or not.
    * @param aFlag The flag to check.
    * @return @c ETrue if flag is set, @c EFalse if not.
    */
	IMPORT_C TBool IsFlagSet(TCaseStateFlags aFlag) const;

private:
	TUint8 iCurrentCase;
	TUint8 iPreviousCase;
	TUint8 iPreviousCaseUsedToEnterText;
	TUint8 iFlags;

    TInt iSpare;
	};


// FORWARD DECLERATIONS
class MEikCcpuEditor;
class CEikButtonGroupContainer;
class CEikMenuBar;
class MObjectProvider;
class CAknEdwinFormAccessor;

// CLASS DECLARATION

/**
* Stores the (FEP) states of editor controls.
* @since Series 60 0.9
*/
class CAknEdwinState : public MCoeFepAwareTextEditor_Extension1::CState
	{
public:
    /**
    * Control's button array and softkey command id's.
    */
	struct SEditorCbaState
		{
		/** A wrapper around the different button arrays used in both pen,
		 and no-pen devices. */
		CEikButtonGroupContainer* iCurrentCba;
		/** Left softkey command id. */
		TInt iLeftSoftkeyCommandId;
		/** Right softkey command id. */
		TInt iRightSoftkeyCommandId;
		};
public:
    /** 
    * Destructor
    */
	virtual ~CAknEdwinState();
	
	/**
	* C++ constructor.
	* @param aCcpuState Pointer to a control that implements @c MEikCcpuEditor
	* interface.
	* 
	*/
	CAknEdwinState(MEikCcpuEditor* aCcpuState);
	
	/**
	* C++ default constructor.
	*/
	IMPORT_C CAknEdwinState();
	
public:
    /**
    * Sets an observer for this control.
    * @param aObserver Pointer to an observer.
    */
	IMPORT_C void SetObserver(MAknEdStateObserver* aObserver);

    /**
    * From @c MAknEdStateObserver. Sends an state event to control's observer.
    * @param aEventType Event type.
    */
	IMPORT_C void ReportAknEdStateEventL(
		MAknEdStateObserver::EAknEdwinStateEvent aEventType);

public:
	// Accessors
	
    /**
    * Returns control's flags.
    * @return Flags.
    */
	IMPORT_C TInt Flags() const;

    /**
    * Get default input mode for the editor. The input mode is used when 
    * the editor is focused first time. 
    * @return Initial input mode to be used in the editor.
    */
	IMPORT_C TInt DefaultInputMode() const;

    /**
    * Get current input mode for the editor.
    * @return Current input mode used in the editor.
    */
	IMPORT_C TInt CurrentInputMode() const;

    /**
    * Get permitted input modes for the editor.
    * @return Input modes that are allowed in the editor.
    */
	IMPORT_C TInt PermittedInputModes() const;

    /**
    * Get default case for the editor. The case is used when the editor
    * is focused first time. 
    * @return Default character case.
    */
	IMPORT_C TInt DefaultCase() const;

    /**
    * Get current character case for the editor.
    * @return Current character case.
    */
	IMPORT_C TInt CurrentCase() const;

    /**
    * Get permitted cases for the editor.
    * @return Case modes that are permitted in the editor.
    */
	IMPORT_C TInt PermittedCases() const;

    /**
    * T9 language codes are not anymore supported, use @c LocalLanguage() 
    * instead.
    * @return 0
    */
	IMPORT_C TInt DefaultLanguage() const;

    /**
    * Get editor specific special character table resource ID. 
    * @return Special character table dialog resource ID.
    */
	IMPORT_C TInt SpecialCharacterTableResourceId() const;

    /**
    * Get number mode key mapping for '*' and '#' keys. The key mapping is used
    * in editors when numeric input mode is used. Key mapping characters
    * for '*' key are shown on special character table if also text input modes
    * are allowed in the editor but the current input mode is numeric mode.
    * @return Key mapping used in an editor with number input mode.
    */
	IMPORT_C TAknEditorNumericKeymap NumericKeymap() const;

    /**
    * Get the cursor or cursor selection within a document.
    * @return The cursor or cursor selection within a document.
    */
	IMPORT_C TCursorSelection CurrentInlineEditSpan() const;

    /**
    * Get control's CBA state.
    * @return Reference to @c SEditorCbaState struct.
    */
	IMPORT_C SEditorCbaState& CbaState();

    /**
    * Get the control's menu bar.
    * @return A pointer to the control's menu bar.
    */
	IMPORT_C CEikMenuBar* MenuBar() const;

    /**
    * Get an interface that provides ccpu (cut, copy, paste and undo) 
    * functionalities.
    * @return A pointer to a ccpu interface for this control.
    */
	IMPORT_C MEikCcpuEditor* CcpuState() const;

    /**
    * Get control's object provider.
    * @return A pointer to control's object provider.
    */
	IMPORT_C MObjectProvider* ObjectProvider() const;

    /**
    * Get the control's input language.
    * @return Language identity.
    */
	IMPORT_C TLanguage LocalLanguage() const;

    /**
    * Accessor for control's form.
    * @since Series 60 2.0
    * @return A pointer to to the form accessor of this control.
    */
	IMPORT_C CAknEdwinFormAccessor* FormAccessor() const;


	// Setters

    /**
    * Set initial editor flags for the editor.
    * @param aFlags Avkon editor flags for the editor.
    */
	IMPORT_C void SetFlags(TInt aFlags);

    /**
    * Set default input mode for the editor. The input mode is used when 
    * the editor is focused first time. 
    * @c EAknEditorTextInputMode is used if the initial input mode is not set 
    * from EDWIN resource DEFAULT_INPUT_MODE or with this API.
    * @param aInputMode Initial input mode to be used in the editor.
    */
	IMPORT_C void SetDefaultInputMode(TInt aInputMode);

    /**
    * Updates editor input mode. FEP is automatically notified of the
    * new input mode in editor state and FEP takes new input mode to use 
    * immediatelly. Current inline editing is reset.
    * This method should not be used for setting initial input mode for the 
    * editor. Use @c SetDefaultInputMode() method instead for setting initial
    * input mode.
    * @param aInputMode New input mode for the editor.
    */
	IMPORT_C void SetCurrentInputMode(TInt aInputMode);

    /**
    * Set permitted input modes for the editor. 
    * All input modes are allowed ( @c EAknEditorAllInputModes ) if the value 
    * is not set from EDWIN resource ALLOWED_INPUT_MODES or with this API.
    * @param aInputModes Input modes that are allowed in the editor.
    */
	IMPORT_C void SetPermittedInputModes(TInt aInputModes);

    /**
    * Set default case for the editor. The case is used when the editor
    * is focused first time. Available case flags from @c uikon.hrh
    * are @c EAknEditorUpperCase, @c EAknEditorLowerCase and 
    * @EAknEditorTextCase. @c EAknEditorTextCase is used if the initial case is
    * not set from EDWIN resource DEFAULT_CASE or with this API.
    * @param aCase Initial case to be used in the editor.
    */
	IMPORT_C void SetDefaultCase(TInt aCase);

    /**
    * Updates editor case. FEP is automatically notified of the
    * case change in editor state and FEP takes new case to use immediately.
    * Available case flags from @c uikon.hrh are @c EAknEditorUpperCase, 
    * @c EAknEditorLowerCase and @c EAknEditorTextCase.
    * This method should not be used to set initial case for the editor.
    * Use @c SetDefaultCase() method instead for setting the initial case.
    * @param aCase New case for the editor.
    */
	IMPORT_C void SetCurrentCase(TInt aCase);

    /**
    * Set permitted cases for the editor.
    * Possible flags from @c uikon.hrh are @c EAknEditorAllCaseModes, 
    * @c EAknEditorUpperCase,@c EAknEditorLowerCase and @c EAknEditorTextCase.
    * @c EAknEditorAllCaseModes is used if the value is not set from EDWIN
    * resource ALLOWED_CASE_MODES or with this API.
    * @param aCases Case modes that are available in the editor.
    */
	IMPORT_C void SetPermittedCases(TInt aCases);

    /**
    * T9 language codes are not anymore supported. Use @c SetLocalLanguage() 
    * instead.
    */
	IMPORT_C void SetDefaultLanguage(TInt aLanguage);

    /**
    * Set editor specific special character table. 
    * @param aResourceId Special character table dialog resource ID.
    */
	IMPORT_C void SetSpecialCharacterTableResourceId(TInt aResourceId);

    /**
    * Set number mode key mapping for '*' and '#' keys. The key mapping is used
    * in editors when numeric input mode is used. Key mapping characters
    * for '*' key are shown on special character table if also the text input modes
    * are allowed in the editor but the current input mode is numeric mode.
    * @c EAknEditorStandardNumberModeKeymap is used in editors that allow only 
    * numeric input if the mapping is not set from EDWIN resource NUMERIC_KEYMAP
    * or with this API. @c EAknEditorAlphanumericNumberModeKeymap is used as 
    * default if the editor allows also text input mode.
    * @param aKeymap Key mapping used in an editor with number input mode.
    */
	IMPORT_C void SetNumericKeymap(TAknEditorNumericKeymap aKeymap);

    /**
    * Set the cursor or cursor selection within a document.
    * @param aCurrentInlineEditSpan New cursor or cursor selection within a 
    * document.
    */
	IMPORT_C void SetInlineEditSpan(TCursorSelection aCurrentInlineEditSpan);

    /**
    * Gets the control's button array from object provider and sets the softkey
    * command id's to 0.
    */
	IMPORT_C void SetCba();

    /**
    * Sets the menu bar from the object provider.
    */
	IMPORT_C void SetMenu();

    /**
    * Set the object provider for the control.
    * @param aObjectProvider A pointer to a class that implements an object 
    * provider.
    */
	IMPORT_C void SetObjectProvider(MObjectProvider* aObjectProvider);

    /**
    * Set new local input language for the editor. Global input language
    * changes have not effect for the input language but the user can still
    * change the input language from the edit menu.
    * @param aLanguage Editor local input language.
    */
	IMPORT_C void SetLocalLanguage(TLanguage aLanguage);

    /**
    * Set form accessor for this control.
    * @since Series 60 2.0
    * @param aFormAccessor Pointer to a form accessor.
    */
	IMPORT_C void SetFormAccessor(CAknEdwinFormAccessor* aFormAccessor);

	// non exported setters

    /**
    * Set a control that implements ccpu (cut, copy, paste and undo) interface.
    * @param aCcpuEditor Pointer to a control that implements @c MEikCcpuEditor
    * interface.
    */
	IMPORT_C void SetCcpuState(MEikCcpuEditor* aCcpuEditor);
	
    /**
    * Set middle sofkey command id.
    * @since S60 V3.2
    * @param aId New middle softkey command id.
    */
	IMPORT_C void SetMiddleSoftkeyCommandId(TInt aCommandId);

    /**
    * Return middle sofkey command id.
    * @since S60 V3.2
    * @return Current middle softkey command id.
    */
	IMPORT_C TInt MiddleSoftkeyCommandId() const;

private:
	IMPORT_C void SetCurrentCaseWithNoInitialisation(TInt aCase);
	IMPORT_C TAknEditorCaseState& CaseState();

private:
	void CheckLRCursorAndT9Consistency();

private:
	friend class CT9FepControl;  // dependency to be removed?
	friend class CT9FepCaseManager;  // dependency to be removed?
	friend class CAknFepCaseManager;  // dependency to be removed?
	friend class CAknFepManager;  // dependency to be removed?

private:
	TInt iFlags;
	TInt iDefaultInputMode;
	TInt iCurrentInputMode;
	TInt iPermittedInputModes;
	
	TInt iDefaultCase;
	TAknEditorCaseState iCaseState;
	TInt iPermittedCases;

	TLanguage iLocalLanguage;
	TInt iSpecialCharacterTableResourceId;
	TAknEditorNumericKeymap iNumericKeymap;
	TCursorSelection iCurrentInlineEditSpan;

	SEditorCbaState iCbaState;
	CEikMenuBar* iMenu;

	// to hold c/c/p/u info about an editor
	MEikCcpuEditor* iCcpuState;
	MObjectProvider* iObjectProvider;

	MAknEdStateObserver* iObserver;
	CAknEdwinFormAccessor* iFormAccessor;
	
	TInt iMiddleSoftkeyCommandId;

    TInt iSpare[3];
	};


#endif





