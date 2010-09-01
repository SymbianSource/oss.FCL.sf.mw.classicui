/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares main application class.
*
*/









#ifndef C_BCTESTCHECKSETTINGPAGE_H
#define C_BCTESTCHECKSETTINGPAGE_H

// INCLUDES
#include <akncheckboxsettingpage.h>

class CBCTestSettingPageCase;


// CLASS DECLARATION

/**
* CBCTestCheckSettingPageApp application class.
* Derived class from CAknCheckBoxSettingPage
*/
class CBCTestCheckSettingPage : public CAknCheckBoxSettingPage
    {
    
friend class CBCTestSettingPageCase;

public:
	IMPORT_C CBCTestCheckSettingPage(TInt aResourceID, CSelectionItemList* aItemArray );
	
 /**
 * Constructor that allows separate setting page and editor resources
 *
 * In all cases the number (if supplied i.e. <> 0 ) is used.  
 *
 *		Editor Resource		Setting Page Resource
 *			present				present				Both are used (but text & number overridden)
 *			 = 0				present				Editor resource is used via SP resource
 *			present				= 0					Default Avkon SP resource if used (to no effect?)
 *			 = 0				= 0					Not permitted
 *
 * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
 * cannot initialize such a member without allocation or having an internal dummy buffer.
 *
 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
 * specific API for setting them, WILL override resource.
 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
 * 
 * @param aSettingTitleText	Text at top of setting pane
 *	@param aSettingNumber		Number at top left (if present)
 * @param aControlType			Determines the type constructed and how its resource is read
 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
 * @param aSettingPageResourceId		Setting Page to use (if present)
 * @param aItemArray			List of option texts and their selection states
 */
	IMPORT_C CBCTestCheckSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,
								CSelectionItemList* aItemArray );

	/**
	* Destructor
	*/ 
	IMPORT_C virtual ~CBCTestCheckSettingPage();

	/**
	* Called when the setting is updated
	*
	*/
	IMPORT_C virtual void BCUpdateSettingL();

	/**
	* Called when the setting page is about to be displayed
	*
	*/
	IMPORT_C void BCDynamicInitL();

	// From MEikCommandObserver
	IMPORT_C virtual void ProcessCommandL(TInt aCommandId);
	/*
	* This method is called upon Select command id.  It should change the setting but not exit in
	* this case.
	*/
	IMPORT_C virtual void BCSelectCurrentItemL();

    /**
     * Writes the internal state of the control and its components to aStream.
     * Does nothing in release mode.
     * Designed to be overidden and base called by subclasses.
     *
     * @param	aWriteSteam		A connected write stream
     */	
	IMPORT_C virtual void BCWriteInternalStateL(RWriteStream& aWriteStream) const;

    };

#endif

// End of File
