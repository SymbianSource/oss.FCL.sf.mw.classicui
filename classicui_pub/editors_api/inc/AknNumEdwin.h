/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Numeric Editor derived from Uikon's CEikEdwin
*                These specializations of CEikEdwin maintain a numeric content, 
*                access methods and validation.
*
*/



#if !defined(__AKNNUMEDWIN_H__)
#define __AKNNUMEDWIN_H__

// INCLUDES
#include <eikedwin.h>
#include <aknnumed.h> // CAknNumericEdwin

// CONSTANTS
_LIT( KAknIntegerFormat, "%d" );

// CLASS DECLARATION

/**
*  The CAknIntegerEdwin class implements an editor for an integer values.
*
*  The editor has an associated resource struct @c AVKON_INTEGER_EDWIN and 
*  control factory identifier @c EAknCtIntegerEdwin.
*
*  @since Series 60 0.9
*/
class CAknIntegerEdwin : public CAknNumericEdwin
	{
public:
	/**
    * Two-phased constructor.
    * @param aMin The minimum allowable value.
    * @param aMax The maximum allowable value.
    * @param aMaxChars  The maximum allowable number of the digits.
    * @return Pointer to a fully constructed editor object.
    */
	IMPORT_C static CAknIntegerEdwin* NewL(TInt aMin, 
	                                       TInt aMax, 
	                                       TInt aMaxChars);
	
	/**
    * Constructs controls from a resource file.
    * Function reads needed values from a @c AVKON_INTEGER_EDWIN resource. 
    * Essential for Dialog/Form construction.
    * @param aReader The resource reader with which to access the control's
    * resource values.
    */
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	
	/**
    * 2nd phase constructor.
    * @param aMin The minimum allowable value.
    * @param aMax The maximum allowable value.
    * @param aMaxChars  The maximum allowable number of the digits.
    */
	IMPORT_C void ConstructL( TInt aMin, TInt aMax, TInt aMaxChars );

	// New methods
	
    /**
    * Sets the current value of the editor.
    * The control is not redrawn. 
    * @param aValue Current value of the editor.
    */
	IMPORT_C void SetValueL(TInt aValue);
	
	/**
    * Sets the value that is returned when the editor field is left empty or
    * is not valid.
    * @param aUnsetValue The default value to be returned.
    */
	IMPORT_C void SetUnsetValue( TInt aUnsetValue);
	
    /**
    * Gets the current value of the editor.
    * Validity of the value is checked, if the editor is empty, the unset value
    * is used. The value is put into aValue parameter even if it is not valid.
    * @param aValue Reference to the integer used to store the value got from
    * the editor field.
    * @return Indicates the validation status.
    */
	IMPORT_C TValidationStatus GetTextAsInteger( TInt& aValue );
	
	/**
    * Sets the minimum allowable value of the editor.
    * @param aMinimumValue The minimum value.
    */
	IMPORT_C void SetMinimumIntegerValue( TInt aMinimumValue );
	
	/**
    * Sets the maximum allowable value of the editor.
    * @param aMaximumValue The maximum value.
    */
	IMPORT_C void SetMaximumIntegerValue( TInt aMaximumValue );

	
	/**
    * From @c CCoeControl. Prepares for focus loss.
    * Called by the framework just before focus is removed from the control.
    */
	IMPORT_C void PrepareForFocusLossL();
	
	/**
    * From @c CCoeControl. Handles a change to the control's resources.
    * @since Series 60 2.0
    * @param aType a message UID value.
    */
	IMPORT_C void HandleResourceChange(TInt aType);
	
	/**
    * From @c CCoeControl. Handles key events.
    * Called by framework when a key event occurs.
    * @since Series 60 2.0
    * @param aKeyEvent The key event that occured.
	* @param aType The type of key event that occured.
    * @return @c EKeyWasConsumed if the event was processed,
    * @c EKeyWasNotConsumed if the event was not processed.
    */
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
	                                     TEventCode aType);

    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	

    /**
    * Checks if the number of the editor is within the min and max boundaries.
    * If not, the method set the number to closest legal value and highlights the 
    * number text in the editor.
    */
    IMPORT_C TBool CheckNumber();    

private:
	void CommonConstructL(TInt aMin, 
	                      TInt aMax, 
	                      TInt aMaxChars, 
	                      TInt aFlags, 
	                      TInt aUnset);
	
	void RefreshFromLocale();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private: // from CEikEdwin
    IMPORT_C void Reserved_3();

private:
	TInt iMinimumValue;
	TInt iMaximumValue;
	TInt iUnsetValue;
	TAny* iUnsetText;
	TDigitType iDigitType;
	TInt iSpare_Integer_2;
	};

#endif
