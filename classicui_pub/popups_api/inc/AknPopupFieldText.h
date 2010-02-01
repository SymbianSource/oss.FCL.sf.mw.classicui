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
*     Represents a text combo box type control, used to implement the
*     Series 60 text pop-up field.
*     This control can be constructed directly from resource.
*
*
*/


#if !defined(__AKNPOPUPFIELDTEXT_H__)
#define __AKNPOPUPFIELDTEXT_H__

#include "AknPopupField.h"
#include "AknQueryValueText.h"

/**
 * Represents a text combo box type control which is used to implement
 * the Series 60 text pop-up field. This control can be constructed directly
 * from a resource. 
 */
class CAknPopupFieldText : public CAknPopupField
	{
public: 

    /**
     * C++ default constructor.
     */
	IMPORT_C CAknPopupFieldText();

    /**
     * Destructor.
     */
	IMPORT_C ~CAknPopupFieldText();

    /**
     * Gets the current value  text stored in the @c CaknQueryValueText member.
     *
     * @return Pointer to the current value text. 
     */
	IMPORT_C HBufC* CurrentValueTextLC();

    /**
     * Gets the current value index from the @c CAknQueryValueText member.
     *
     * @return The current value index.
     */
	IMPORT_C TInt CurrentValueIndex() const;

    /**
     * Sets the current value index to the @c CAknQueryValueText member.
     *
     * @param aIndex The current value index.
     */
	IMPORT_C void SetCurrentValueIndex(const TInt aIndex);

    /**
     * Gets the @c MdcArray from the @c CAknQueryValueText member. This array 
     * contains the selection array of the popup field.
     *
     * @return Selection array of the popup field.
     */
	IMPORT_C const MDesCArray* MdcArray() const;

    /**
     * Sets or clears @c EAutoAppendBitIndexCalls flag from @c CAknQueryValue.
     *
     * @param aAppend If @c ETrue, the flag is set.
     */
	IMPORT_C void SetAutoAppend(TBool aAppend);

public: // from CCoeControl

    /**
     * From @c CCoeControl.
     * 
     * Constructs the control from a resource file.
     *
     * @param aReader Resource reader.
     */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private: // Methods from CAknPopupField that were public

    /**
     * 2nd phase constructor.
     */
	void ConstructL();

	/**
	* This method should not be used. 
	* It is here to hide it from users, this will panic if you use it.
	*/
	void SetQueryValueL(MAknQueryValue* aValue);

private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private: // personal
	void CommonConstructL(TInt aTextArrayResourceId, TInt aInitialIndex);

private:
	// the following members are owned
	CDesCArray* iArray;	// the array of text items
	CAknQueryValueTextArray* iTextArray;	
	CAknQueryValueText* iTextValue;
    TInt iSpare[2];
	};

#endif // __AKNPOPUPFIELDTEXT_H__
