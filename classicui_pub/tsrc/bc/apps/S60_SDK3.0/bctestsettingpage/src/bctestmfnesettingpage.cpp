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









#include "bctestmfnesettingpage.h"

//////////////////////////////////////////////////////////////////////
//
//  MFNE SETTING PAGE - virtual class
//
//////////////////////////////////////////////////////////////////////



/**
 * Simple pass-through constructor for this interim class
 *
 */
EXPORT_C CBCTestMfneSettingPage::CBCTestMfneSettingPage( TInt aResourceId ) : CAknMfneSettingPage( aResourceId )
    {}

/**
 * Constructor that allows separate setting page and editor resources
 * 
 */
EXPORT_C CBCTestMfneSettingPage::CBCTestMfneSettingPage(  
                                const TDesC* aSettingText, 
                                TInt aSettingNumber, 
                                TInt aControlType,
                                TInt aEditorResourceId, 
                                TInt aSettingPageResourceId )
                                :   CAknMfneSettingPage( 
                                    aSettingText, 
                                    aSettingNumber, 
                                    aControlType, 
                                    aEditorResourceId, 
                                    aSettingPageResourceId) 
    {}



//////////////////////////////////////////////////////////////////////
//
//  DATE SETTING PAGE
//
//////////////////////////////////////////////////////////////////////

/**
 * Constructor using Setting page resource
 *
 *
 * @param	aResourceId		Setting page resource Id
 * @param	aDateValue		Reference to a Time value set to the initial date
 */
EXPORT_C CBCTestDateSettingPage::CBCTestDateSettingPage( TInt aResourceId, TTime& aDateValue ):
	 CAknDateSettingPage( aResourceId , aDateValue )
	{
	}

/**
 * Constructor that allows separate setting page and editor resources
 * 
 */
EXPORT_C CBCTestDateSettingPage::CBCTestDateSettingPage(	
                                const TDesC* aSettingText, 
                                TInt aSettingNumber, 
                                TInt aControlType,
                                TInt aEditorResourceId, 
                                TInt aSettingPageResourceId, 
                                TTime& aDateValue )
                                :   CAknDateSettingPage( 
                                    aSettingText, 
                                    aSettingNumber, 
                                    aControlType, 
                                    aEditorResourceId, 
                                    aSettingPageResourceId, 
                                    aDateValue)
	{
	}

//////////////////////////////////////////////////////////////////////
//
//  TIME SETTING PAGE
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * Constructor using Setting page resource
 *
 *
 * @param	aResourceId		Setting page resource Id
 * @param	aTimeValue		Reference to a Time value set to the initial date
 */
EXPORT_C CBCTestTimeSettingPage::CBCTestTimeSettingPage( TInt aResourceId, TTime& aTimeValue ):
	 CAknTimeSettingPage( aResourceId, aTimeValue )
	{
	}
/**
 * Constructor that allows separate setting page and editor resources
 * 
 */
EXPORT_C CBCTestTimeSettingPage::CBCTestTimeSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TTime& aTimeValue )
								:	CAknTimeSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId, 
									aTimeValue)
	{
	}

//////////////////////////////////////////////////////////////////////
//
//  DURATION SETTING PAGE
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/**
 * Constructor using Setting page resource
 *
 *
 * @param	aResourceId		Setting page resource Id
 * @param	aDurationValue		Reference to a Time value set to the initial date
 */
EXPORT_C CBCTestDurationSettingPage::CBCTestDurationSettingPage( TInt aResourceId, TTimeIntervalSeconds& aDurationValue ):
	 CAknDurationSettingPage( aResourceId, aDurationValue )
	{
	}
	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0				present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present				 = 0				Default Avkon SP resource if used + this editor resource
	 *			 = 0				 = 0				uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, duration )
	 *
	 *
	 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
	 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
	 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
	 * specific API for setting them, WILL override resource.
	 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
	 * 
	 * @param aSettingTitleText		Text at top of setting pane
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId		Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aDurationValue				reference to a duration
	 */

EXPORT_C CBCTestDurationSettingPage::CBCTestDurationSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TTimeIntervalSeconds& aDurationValue )
								:	CAknDurationSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId, 
									aDurationValue)
	{
	}

//////////////////////////////////////////////////////////////////////
//
//  TIME OFFSET SETTING PAGE
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/**
 * Constructor using Setting page resource
 *
 *
 * @param	aResourceId		Setting page resource Id
 * @param	aDurationValue		Reference to a Time value set to the initial date
 */
EXPORT_C CBCTestTimeOffsetSettingPage::CBCTestTimeOffsetSettingPage( TInt aResourceId, TTimeIntervalSeconds& aTimeOffsetValue ):
	 CAknTimeOffsetSettingPage( aResourceId, aTimeOffsetValue )
	{
	}
	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0				present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present				 = 0				Default Avkon SP resource if used + this editor resource
	 *			 = 0				 = 0				uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, duration )
	 *
	 *
	 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
	 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
	 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
	 * specific API for setting them, WILL override resource.
	 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
	 * 
	 * @param aSettingTitleText		Text at top of setting pane
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId		Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aDurationValue				reference to a duration
	 */

EXPORT_C CBCTestTimeOffsetSettingPage::CBCTestTimeOffsetSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TTimeIntervalSeconds& aTimeOffsetValue )
								:	CAknTimeOffsetSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId, 
									aTimeOffsetValue )
	{
	}

//////////////////////////////////////////////////////////////////////
//
//  IP ADDRESS FIELD SETTING PAGE
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * Constructor using Setting page resource
 *
 *
 * @param	aResourceId		Setting page resource Id
 * @param	aIpFieldValue		Reference to a Time value set to the initial date
 */
EXPORT_C CBCTestIpFieldSettingPage::CBCTestIpFieldSettingPage( TInt aResourceId, TInetAddr& aIpAddress )
: CAknIpFieldSettingPage( aResourceId, aIpAddress )
	{
	}
	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0				present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present				 = 0				Default Avkon SP resource if used + this editor resource
	 *			 = 0				 = 0				uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, IpField )
	 *
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
	 * @param aIpAddress				reference to a IP address
	 */

EXPORT_C CBCTestIpFieldSettingPage::CBCTestIpFieldSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TInetAddr& aIpAddress )
								:	CAknIpFieldSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId, 
									aIpAddress )
	{
	}

// End of File
