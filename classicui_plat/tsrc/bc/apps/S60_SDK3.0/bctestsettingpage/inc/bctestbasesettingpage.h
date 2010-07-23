/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#ifndef BCTEST_BASE_SETTINGPAGE_H
#define BCTEST_BASE_SETTINGPAGE_H 

#include <aknsettingpage.h>

class CBCTestSettingPageCase;

class CBCTestBaseSettingPage : public CAknSettingPage
	{

	friend class CBCTestSettingPageCase;
public:

/**
 * Simple contructor for using a single setting page resource which itself gives all 
 * the setup
 */
	IMPORT_C CBCTestBaseSettingPage( TInt aSettingPageResourceId );
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
 *
 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
 * specific API for setting them, WILL override resource.
 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
 * 
 * @param aSettingTitleText		Text at top of setting pane (not copied; must be owned externally until ExecuteLD is called)
 * @param aSettingNumber		Number at top left (if present)
 * @param aControlType			Determines the type constructed and how its resource is read
 * @param aEditorResourceId Editor resource to use in the setting page (if present)
 * @param aSettingPageResourceId		Setting Page to use (if present)
 */
	IMPORT_C CBCTestBaseSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId = 0 );
/**
* C++ destructor
*/
	IMPORT_C virtual ~CBCTestBaseSettingPage();
	
	IMPORT_C virtual void SetFocusToEditor();
	IMPORT_C TBool PostDisplayCheckL();

};

#endif 
