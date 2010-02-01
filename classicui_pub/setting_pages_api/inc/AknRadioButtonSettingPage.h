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
*	  Support for Radio Button setting page 
*
*/


#ifndef __AKNRADIOBUTTONSETTINGPAGE_H__
#define __AKNRADIOBUTTONSETTINGPAGE_H__ 

// For coecontrol
#include <coecntrl.h>
#include <eikdef.h>

#include <AknListBoxSettingPage.h>

class CAknRadioButtonSettingPageExtension;

/** 
*  This class sets out a radio button listbox within a setting page.
*  
*/
class CAknRadioButtonSettingPage : public CAknListBoxSettingPage
{
public:
	IMPORT_C CAknRadioButtonSettingPage(
		TInt aResourceID, 
		TInt& aCurrentSelectionIndex, 
		const MDesCArray* aItemArray );
 /**
 * Constructor that allows separate setting page and editor resources
 *
 * In all cases the number (if supplied i.e. <> 0 ) is used.  
 *
 *		Editor Resource 	Setting Page Resource
 *			present 			present 			Both are used (but text & number overridden)
 *			 = 0				present 			Editor resource is used via SP resource
 *			present 			= 0 				Default Avkon SP resource if used
 *			 = 0				= 0 				Not permitted 
 *
 * Note: The first argument is a TDesC* (rather than TDesC&) because the other constructor
 * cannot initialize such a member without allocation or having an internal dummy buffer.
 * Note that the setting title provided here must be owned by the client.
 *
 * Rules for text and numbers: The rules are the same for both: (non-zero length) text or number other 
 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed). Note, however, that text or number given via the 
 * specific API for setting them, WILL override resource.
 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
 * 
 * @param aSettingTitleText Text at top of setting pane; EXTERNALLY OWNED
 * @param aSettingNumber		Number at top left (if present)
 * @param aControlType			Determines the type constructed and how its resource is read
 * @param aEditorResourceId Editor resource to use in the setting page (if present)
 * @param aSettingPageResourceId		Setting Page to use (if present)
 * @param aCurrentSelectionIndex	The currently selected index
 * @param aItemArray			List of option texts and their selection states
 */
	IMPORT_C CAknRadioButtonSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,
								TInt& aCurrentSelectionIndex, 
								const MDesCArray* aItemArray );

	/** 
	* 2nd stage contruction for this type.  Calls CAknSettingPage::BaseConstuctL() where the object is constructed
	* from resource.
	*/
	IMPORT_C virtual void ConstructL();

	/** 
	* Type specific access to the hosted "editor"
	*
	* @return	pointer to contained listbox
	*/
	IMPORT_C CAknSetStyleListBox* ListBoxControl() const; 

	/** 
	* From MEikListBoxObserver
	* @param	listbox generating the event
	* @param	type of listbox event
	*/
	IMPORT_C virtual void HandleListBoxEventL(CEikListBox* aListBox,
				 MEikListBoxObserver::TListBoxEvent aEventType);

	/**
	* Method to update the item array after a change in content and to re-select 
	* the "pushed in" index
	* @param CDesCArrayFlat*	aItemArray	The new item array; array of texts
	* @param TInt					aPushed		A valid 0-based index.  -1 is also legal
	* indicating nothing is pushed
	*/
	IMPORT_C void SetItemArrayAndSelectionL( const MDesCArray* aItemArray, TInt aPushed );

    /**
    * From CCoeControl 
    * Handles Radiobuttonlist's PointerEvent 
    *    
    * @param aPointerEvent PointerEvent to be handled
    */     
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    IMPORT_C void HandleResourceChange(TInt aType);

protected:
/**
* C++ destructor
*/
	IMPORT_C virtual ~CAknRadioButtonSettingPage();

/**
* Called when the external setting is to be updated
*/
	IMPORT_C virtual void UpdateSettingL();

/**
* Called immediately prior to activation, but after all construction
*/
	IMPORT_C void DynamicInitL();

/**
 * This method overrides the default implementation in order to do the special 
 * processing of selecting an item
 *
 */
	IMPORT_C virtual void SelectCurrentItemL();

private:
	/**
	* Method to move the selection to position aPushed
	*
	*/
	void SetRadioButtonSelectionL( TInt aPushed );

	/**
	* Internal method to re-generate the internal, "decorated" text array used in the
	* real listbox. 
	*/
	void GenerateInternalArrayAndGiveToListBoxL();

    void InitialiseRadioButtonBitmapsL();

//
// CoeControl Framework and reserved methods
//
protected:

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @param	aWriteSteam		A connected write stream
 */	
	IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;

private: 
/**
 *	Reserved method derived from CCoeControl
 */
	IMPORT_C virtual void Reserved_2();

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

/**
 * New reserved methods for CAknSettingPage hierarchy
 */ 
private: 
	IMPORT_C virtual void CAknSettingPage_Reserved_1();
	IMPORT_C virtual void CAknSettingPage_Reserved_2();

private:
/**
 * New reserved method from CAknListBoxSettingPage 
 *
 */
	IMPORT_C virtual void CAknListBoxSettingPage_Reserved_1();


private:
	// Back up copy of the selection index
	TInt iOldSelectionIndex;
	
	// Extension, replaces CDesCArrayFlat* iInternalItemArray
	CAknRadioButtonSettingPageExtension* iExtension;

	// The objects pointed to or referenced by these are not owned
	TInt& iCurrentSelectionIndex; 
	const MDesCArray* iItemArray; 

};

#endif 
