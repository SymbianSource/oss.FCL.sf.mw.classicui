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
* Description:         container
*
*/









#ifndef BCTEST_RADIOBUTTONSETTINGPAGE_H
#define BCTEST_RADIOBUTTONSETTINGPAGE_H

#include <aknradiobuttonsettingpage.h>

class CBCTestSettingPageCase;

/**
*  This class sets out a radio button listbox within a setting page.
*
*/
class CBCTestRadioButtonSettingPage : public CAknRadioButtonSettingPage
{

friend class CBCTestSettingPageCase;

public:
    IMPORT_C CBCTestRadioButtonSettingPage(
        TInt aResourceID,
        TInt& aCurrentSelectionIndex,
        const MDesCArray* aItemArray );
 /**
 * Constructor that allows separate setting page and editor resources
 *
 * In all cases the number (if supplied i.e. <> 0 ) is used.
 *
 *      Editor Resource     Setting Page Resource
 *          present             present             Both are used (but text & number overridden)
 *           = 0                present             Editor resource is used via SP resource
 *          present             = 0                 Default Avkon SP resource if used
 *           = 0                = 0                 Not permitted
 *
 * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
 * cannot initialize such a member without allocation or having an internal dummy buffer.
 * Note that the setting title provided here must be owned by the client.
 *
 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other
 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource
 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the
 * specific API for setting them, WILL override resource.
 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
 *
 * @param aSettingTitleText Text at top of setting pane; EXTERNALLY OWNED
 * @param aSettingNumber        Number at top left (if present)
 * @param aControlType          Determines the type constructed and how its resource is read
 * @param aEditorResourceId Editor resource to use in the setting page (if present)
 * @param aSettingPageResourceId        Setting Page to use (if present)
 * @param aCurrentSelectionIndex    THe currently selected index
 * @param aItemArray            List of option texts and their selection states
 */
    IMPORT_C CBCTestRadioButtonSettingPage(    const TDesC* aSettingTitleText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId,
                                TInt& aCurrentSelectionIndex,
                                const MDesCArray* aItemArray );

/**
* C++ destructor
*/
    IMPORT_C virtual ~CBCTestRadioButtonSettingPage();

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

//
// CoeControl Framework and reserved methods
//

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @param   aWriteSteam     A connected write stream
 */
    IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;

};

#endif
