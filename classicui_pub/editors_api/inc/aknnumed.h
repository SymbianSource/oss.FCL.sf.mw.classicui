/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Intermediate class for defining data shared between numeric 
*                edwins  
*
*/

#if !defined(__AKNNUMED_H_)
#define __AKNNUMED_H_

//  INCLUDES
#include <eikedwin.h>


// CLASS DECLARATION

/**
* Intermediate class for defining data shared between numeric edwins
*
* @since Series 60 0.9
*/
class CAknNumericEdwin : public CEikEdwin
	{
public:
	/**
    * Destructor.
    */
	IMPORT_C virtual ~CAknNumericEdwin();
	
	/** 
    * 
    * Indicates a validiton status for values read from the control.
    * 
    */
	enum TValidationStatus
		{
		EValueValid = KErrNone,/**< Read value is valid. */
		EValueTooSmall,   /**< Read value is smaller than the minimum value. */
		EValueTooLarge,   /**< Read value is larger than the maximum value. */
		EValueNotParsed,  /**< Read value can not be parsed. */
		EEmpty            /**< The control is empty. */
		};

    // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected:
	/**
    * Maps a key event so that any numeric character is mapped to the correct 
    * digit type that this editor is using.
    * @since Series 60 2.0
    * @param aKeyEvent The key event to modify.
    * @param aType The type to modify.
    * @param aDigitType The digit type to map all numeric characters to.
    */
	IMPORT_C void MapKeyEvent(
		TKeyEvent& aKeyEvent,
		TEventCode& /*aType*/, 
		TDigitType aDigitType) const;


private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: // from CEikEdwin
		IMPORT_C virtual void Reserved_3();
private:		
		TInt iSpare; // Needs at least some data
	};


#endif
