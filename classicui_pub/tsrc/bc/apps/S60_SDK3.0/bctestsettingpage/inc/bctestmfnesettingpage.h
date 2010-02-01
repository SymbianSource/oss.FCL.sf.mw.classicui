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









#ifndef BCTEST_MFNESETTINGPAGE_H
#define BCTEST_MFNESETTINGPAGE_H 

#include <aknmfnesettingpage.h>

 
// FORWARD DECLARATIONS
class CBCTestSettingPageCase;
 
/** 
 *
 * This class is used as the base for the date, time, duration and Ip editor
 * setting page types.  It performs all the layout.
 *
 */
class CBCTestMfneSettingPage : public CAknMfneSettingPage
{
	friend class CBCTestSettingPageCase;
public:
    /**
     * Constructor using purely Setting page resource
     *
     * @param   aResourceId     Setting page resource Id
     */
    IMPORT_C CBCTestMfneSettingPage(TInt ResourceId );
     /**
     * Constructor that allows separate setting page and editor resources
     * 
     * @param aSettingTitleText Text at top of setting pane ; Externally owned
     * @param aSettingNumber        Number at top left (if present)
     * @param aControlType          Determines the type constructed and how its
     *                              resource is read
     * @param aEditorResourceId Editor resource to use in the setting page 
     *                          (if present)
     */
    IMPORT_C CBCTestMfneSettingPage(   const TDesC* aSettingTitleText, 
                                TInt aSettingNumber, 
                                TInt aControlType,
                                TInt aEditorResourceId, 
                                TInt aSettingPageResourceId );
};


/** 
*
* This class is used for entering Dates in a "Code" setting page
*
*/
class CBCTestDateSettingPage : public CAknDateSettingPage
{
	friend class CBCTestSettingPageCase;
public:

    /**
     * Constructor using purely Setting page resource
     *
     * @param   aResourceId     Setting page resource Id
     * @param   aDateValue      Reference to a date value set to the initial 
     *                          date
     */
    IMPORT_C CBCTestDateSettingPage(
        TInt aResourceID, 
        TTime& aDateValue);

    /**
     * Constructor that allows separate setting page and editor resources
     * 
     * This constructor allows the use of setting page using only the editor 
     * resource. Other combinations are also possible
     *
     * In all cases the number (if supplied i.e. <> 0 ) is used.  
     *
     *      Editor Resource     Setting Page Resource
     *          present             present             Both are used 
     *                                                  (but text 
     *                                                  & number overridden)
     *           = 0                present             Editor resource is used
     *                                                  via SP resource 
     *                                                  (Effectively like the
     *                                                  other constructor)
     *          present             = 0                 Default Avkon SP 
     *                                                  resource if used + this
     *                                                  editor resource
     *           = 0                = 0                 uses default resource
     *                                                  for both SP and editor.
     *                                                  This is OK if:
     *   i) control type is present, 
     *  ii) a default resource exists ( OK for text, integer, date, time, 
     *      duration )
     *
     * Note: THe first argument is a TDesC* (rather than TDesC&) because the
     * other constructor cannot initialize such a member without allocation or
     * having an internal dummy buffer.
     * Note that this descriptor must be owned by the client at least until the
     * ExecuteLD().
     *
     * Rules for text and numbers: The rules are the same for both:  
     * (non-zero length) text or number other than 
     * EAknSettingPageNoOrdinalDisplayed if given in this constructor will not
     * override resource (unless that is zero length or 
     * EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number
     * given via the specific API for setting them, WILL override resource.
     * It is assumed that number from resource is very rare.  Special text is
     * somewhat more likely.
     * 
     * @param aSettingTitleText Text at top of setting pane; OWNED EXTERNALLY
     * @param aSettingNumber        Number at top left (if present)
     * @param aControlType          Determines the type constructed and how its
     *                              resource is read
     * @param aEditorResourceId Editor resource to use in the setting page 
     *                          (if present)
     * @param aSettingPageResourceId        Setting Page to use (if present)
     * @param aDateValue                reference to date
     */
    IMPORT_C CBCTestDateSettingPage(   
                                const TDesC* aSettingTitleText, 
                                TInt aSettingNumber, 
                                TInt aControlType,
                                TInt aEditorResourceId, 
                                TInt aSettingPageResourceId,    
                                TTime& aDateValue );
};

/** 
 *
 * This class is used for entering Times in a "Code" setting page
 *
 */
class CBCTestTimeSettingPage : public CAknTimeSettingPage
{
	friend class CBCTestSettingPageCase;
public:
    /**
     * Constructor using purely Setting page resource
     *
     * @param   aResourceId     Setting page resource Id
     * @param   aTimeValue      Reference to a time value for the initial time
     */
    IMPORT_C CBCTestTimeSettingPage(
        TInt aResourceID, 
        TTime& aTimeValue);

    /**
     * Constructor that allows separate setting page and editor resources
     * 
     * This constructor allows the use of setting page using only the editor 
     * resource.  Other combinations are also possible
     *
     * In all cases the number (if supplied i.e. <> 0 ) is used.  
     *
     *      Editor Resource     Setting Page Resource
     *          present             present             Both are used (but text
     *                                                  & number overridden)
     *           = 0                present             Editor resource is used
     *                                                  via SP resource 
     *                                                  (Effectively like the
     *                                                  other constructor)
     *          present              = 0                Default Avkon SP 
     *                                                  resource if used + this
     *                                                  editor resource
     *           = 0                 = 0                uses default resource
     *                                                  for both SP and editor.
     *                                                  This is OK if:
     *   i) control type is present, 
     *  ii) a default resource exists ( OK for text, integer, 
     *      date, time, duration )
     *
     * Note: THe first argument is a TDesC* (rather than TDesC&) because the
     * other constructor cannot initialize such a member without allocation or
     * having an internal dummy buffer.
     * Note that this descriptor must be owned by the client at least until the
     * ExecuteLD().
     *
     * Rules for text and numbers: The rules are the same for both:  
     * (non-zero length) text or number other than 
     * EAknSettingPageNoOrdinalDisplayed if given in this constructor will not
     * override resource (unless that is zero length or 
     * EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number
     * given via the specific API for setting them, WILL override resource.
     * It is assumed that number from resource is very rare.  Special text is
     * somewhat more likely.
     * 
     * @param aSettingTitleText Text at top of setting pane
     * @param aSettingNumber        Number at top left (if present)
     * @param aControlType          Determines the type constructed and how its
     *                              resource is read
     * @param aEditorResourceId Editor resource to use in the setting page 
     *                          (if present)
     * @param aSettingPageResourceId        Setting Page to use (if present)
     * @param aTimeValue                reference to a time
     */
    IMPORT_C CBCTestTimeSettingPage(   const TDesC* aSettingTitleText, 
                                TInt aSettingNumber, 
                                TInt aControlType,
                                TInt aEditorResourceId, 
                                TInt aSettingPageResourceId,    
                                TTime& aTimeValue );

 
};

/** 
 *
 * This class is used for entering duration in a "Code" setting page
 *
 */
class CBCTestDurationSettingPage : public CAknDurationSettingPage
{
	friend class CBCTestSettingPageCase;
public:
    /**
     * Constructor using purely Setting page resource
     *
     * @param   aResourceId     Setting page resource Id
     * @param   aDurationValue      Reference to the maintained duration value
     */
    IMPORT_C CBCTestDurationSettingPage(
        TInt                    aResourceID, 
        TTimeIntervalSeconds&   aDurationValue);
    /**
     * Constructor that allows separate setting page and editor resources
     * 
     * This constructor allows the use of setting page using only the editor 
     * resource.  Other combinations are also possible
     *
     * In all cases the number (if supplied i.e. <> 0 ) is used.  
     *
     *      Editor Resource     Setting Page Resource
     *          present             present             Both are used 
     *                                                  (but text & number 
     *                                                  overridden)
     *           = 0                    present         Editor resource is used
     *                                                  via SP resource 
     *                                                  (Effectively like the 
     *                                                  other constructor)
     *          present             = 0                 Default Avkon SP 
     *                                                  resource if used + this
     *                                                  editor resource
     *           = 0                    = 0             uses default resource 
     *                                                  for both SP and editor.
     *                                                  This is OK if:
     *   i) control type is present, 
     *  ii) a default resource exists ( OK for text, integer, 
     *      date, time, duration )
     *
     * Note: THe first argument is a TDesC* (rather than TDesC&) because the 
     * other constructor cannot initialize such a member without allocation or
     * having an internal dummy buffer.
     * Note that this descriptor must be owned by the client at least until the
     * ExecuteLD().
     *
     * Rules for text and numbers: The rules are the same for both:
     * (non-zero length) text or number other than 
     * EAknSettingPageNoOrdinalDisplayed if given in this constructor will not
     * override resource (unless that is zero length or 
     * EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number
     * given via the specific API for setting them, WILL override resource.
     * It is assumed that number from resource is very rare.  Special text is
     * somewhat more likely.
     * 
     * @param aSettingTitleText Text at top of setting pane; OWNED EXTERNALLY
     * @param aSettingNumber        Number at top left (if present)
     * @param aControlType          Determines the type constructed and how its
     *                              resource is read
     * @param aEditorResourceId Editor resource to use in the setting page 
     *                          (if present)
     * @param aSettingPageResourceId        Setting Page to use (if present)
     * @param aDurationValue                reference to a duration
     */
    IMPORT_C CBCTestDurationSettingPage(   const TDesC* aSettingTitleText, 
                                TInt aSettingNumber, 
                                TInt aControlType,
                                TInt aEditorResourceId, 
                                TInt aSettingPageResourceId,    
                                TTimeIntervalSeconds&   aDurationValue);
};


/**
*  Time offset setting page.
*
*  @lib avkon
*  @since 2.0
*/

class CBCTestTimeOffsetSettingPage : public CAknTimeOffsetSettingPage
{
	friend class CBCTestSettingPageCase;
public:
    /**
     * Constructor using purely Setting page resource
     *
     * @since 2.0
     * @param   aResourceId     Setting page resource Id
     * @param   aTimeOffsetValue        Reference to the maintained 
     *                                  offset value
     */
    IMPORT_C CBCTestTimeOffsetSettingPage(
        TInt                    aResourceID, 
        TTimeIntervalSeconds&   aTimeOffsetValue);
    /**
     * Constructor that allows separate setting page and editor resources
     * 
     * This constructor allows the use of setting page using only the editor 
     * resource. Other combinations are also possible
     *
     * In all cases the number (if supplied i.e. <> 0 ) is used.  
     *
     *      Editor Resource     Setting Page Resource
     *          present             present             Both are used 
     *                                                  (but text & number 
     *                                                  overridden)
     *           = 0                present             Editor resource is 
     *                                                  used via SP resource 
     *                                                  (Effectively like the 
     *                                                  other constructor)
     *          present             = 0                 Default Avkon SP 
     *                                                  resource if used + 
     *                                                  this editor resource
     *           = 0                = 0                 uses default resource 
     *                                                  for both SP and editor. 
     *                                                  This is OK if:
     * i) control type is present, 
     * ii) a default resource exists ( OK for text, integer, 
     *     date, time, duration )
     *
     * Note: THe first argument is a TDesC* (rather than TDesC&) because 
     * the other constructor cannot initialize such a member without allocation
     * or having an internal dummy buffer.
     * Note that this descriptor must be owned by the client at least until the
     * ExecuteLD().
     *
     * Rules for text and numbers: The rules are the same for both:  
     * (non-zero length) text or number other than 
     * EAknSettingPageNoOrdinalDisplayed if given in this constructor will not 
     * override resource (unless that is zero length or 
     * EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number 
     * given via the specific API for setting them, WILL override resource.
     * It is assumed that number from resource is very rare.  Special text is 
     * somewhat more likely.
     * 
     * @since 2.0
     * @param aSettingTitleText Text at top of setting pane; OWNED EXTERNALLY
     * @param aSettingNumber        Number at top left (if present)
     * @param aControlType          Determines the type constructed 
     *                              and how its resource is read
     * @param aEditorResourceId Editor resource to use in the setting page 
     *                                 (if present)
     * @param aSettingPageResourceId        Setting Page to use (if present)
     * @param aTimeOffsetValue              reference to time offset
     */
    IMPORT_C CBCTestTimeOffsetSettingPage( const TDesC* aSettingTitleText, 
                                TInt aSettingNumber, 
                                TInt aControlType,
                                TInt aEditorResourceId, 
                                TInt aSettingPageResourceId,    
                                TTimeIntervalSeconds&   aTimeOffsetValue);

 };
/** 
 *
 * Setting page class for entering an IP Address
 *
 */
class CBCTestIpFieldSettingPage : public CAknIpFieldSettingPage
{
	friend class CBCTestSettingPageCase;
public:
    /**
     * Constructor using purely Setting page resource
     *
     * @param   aResourceId     Setting page resource Id
     * @param   aIpAddress      Reference to the maintained IP address
     */
    IMPORT_C CBCTestIpFieldSettingPage(
        TInt                    aResourceID, 
        TInetAddr&          aIpAddress);
    /**
     * Constructor that allows separate setting page and editor resources
     * 
     * This constructor allows the use of setting page using only the editor 
     * resource.  Other combinations are also possible
     *
     * In all cases the number (if supplied i.e. <> 0 ) is used.  
     *
     *      Editor Resource     Setting Page Resource
     *          present             present             Both are used (but text
     *                                                  & number overridden)
     *           = 0                    present         Editor resource is 
     *                                                  used via SP resource 
     *                                                  (Effectively like the 
     *                                                  other constructor)
     *          present             = 0                 Default Avkon SP 
     *                                                  resource if used + this
     *                                                  editor resource
     *           = 0                    = 0             uses default resource 
     *                                                  for both SP and editor. 
     *                                                  This is OK if:
     *   i) control type is present, 
     *  ii) a default resource exists ( OK for text, integer, 
     *      date, time, duration )
     *
     * Note: THe first argument is a TDesC* (rather than TDesC&) because the 
     * other constructor cannot initialize such a member without allocation 
     * or having an internal dummy buffer.
     * Note that this descriptor must be owned by the client at least until 
     * the ExecuteLD().
     *
     * Rules for text and numbers: The rules are the same for both: 
     * (non-zero length) text or number other than 
     * EAknSettingPageNoOrdinalDisplayed if given in this constructor will not 
     * override resource (unless that is zero length or 
     * EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number 
     * given via the specific API for setting them, WILL override resource.
     * It is assumed that number from resource is very rare.  Special text is 
     * somewhat more likely.
     * 
     * @param aSettingTitleText Text at top of setting pane; OWNED EXTERNALLY
     * @param aSettingNumber        Number at top left (if present)
     * @param aControlType          Determines the type constructed and how its 
     *                              resource is read
     * @param aEditorResourceId Editor resource to use in the setting page 
     *                          (if present)
     * @param aSettingPageResourceId        Setting Page to use (if present)
     * @param aIpAddress                reference to a duration
     */
    IMPORT_C CBCTestIpFieldSettingPage(    const TDesC* aSettingTitleText, 
                                TInt aSettingNumber, 
                                TInt aControlType,
                                TInt aEditorResourceId, 
                                TInt aSettingPageResourceId,    
                                TInetAddr&  aIpAddress);
 
    };
#endif 
