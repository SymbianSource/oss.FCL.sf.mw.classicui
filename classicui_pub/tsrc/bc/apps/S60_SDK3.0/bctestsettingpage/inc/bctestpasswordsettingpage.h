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









#ifndef C_BCTEST_PASSWORDSETTINGPAGE_H
#define C_BCTEST_PASSWORDSETTINGPAGE_H

#include <aknpasswordsettingpage.h>

class CBCTestPasswordSettingPage : public CAknPasswordSettingPage
    {
public:
    /**
     * Simple constructor depending only on a single resource Id and the new and old password.
     * Editor resource is given via the link in the setting page resource.
     *
     * @param aSettingPageResourceId        Setting Page to use (if present)
     * @param aNewPassword
     * @param aOldPassword                  password to be checked against
     */
    IMPORT_C CBCTestPasswordSettingPage(
        TInt aResourceID,
        TDes& aNewPassword,
        const TDesC& aOldPassword);

    /**
     * Constructor that allows separate setting page and editor resources
     *
     * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
     *
     * In all cases the number (if supplied i.e. <> 0 ) is used.
     *
     *      Editor Resource     Setting Page Resource
     *          present             present             Both are used (but text & number overridden)
     *           = 0                    present             Editor resource is used via SP resource (Effectively like the other constructor)
     *          present             = 0                 Default Avkon SP resource if used + this editor resource
     *           = 0                    = 0                 uses default resource for both SP and editor. This is OK if:
     *   i) control type is present,
     *  ii) a default resource exists ( OK for text, integer, date, time, duration )
     *
     * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
     * cannot initialize such a member without allocation or having an internal dummy buffer.
     * This descriptor must be owned by the client since not copy is taken until ExecuteLD()
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
     * @param aNewPassword          Descriptor for the new password
     * @param aOldPassword          Descriptor for the old password
     */

    IMPORT_C CBCTestPasswordSettingPage( const TDesC* aSettingTitleText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId,
                                TDes& aNewPassword,
                                const TDesC& aOldPassword );


public:

    /**
    * Implementation of CAknSettingPage framework method
    * Called when the client's value is updated.  Frequency of calling depends
    * upon the flag passed to ExecuteLD()
    *
    */
    IMPORT_C virtual void UpdateSettingL();


    /**
    * Implementation of CAknSettingPage framework method
    * Perform necessary operations when the user accepts.
    * Default implementation has password checking
    */
    IMPORT_C virtual void AcceptSettingL();


    /**
    * Acts upon changes in the hosted control's state.
    *
    * @param    aControl    The control changing its state (not used)
    * @param    aEventType  The type of control event
    */
    IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType );


    /**
    * Implementation of CAknSettingPage framework method
    *
    * Method called after full construction and activation of the setting page
    */
    IMPORT_C virtual void PostDisplayInitL();

    /**
    * Implementation of CAknSettingPage framework method
    * Called after display of the setting page, but before the start of the
    * setting page "waiting".
    *
    * If overidden, would normally hold a query.
    *
    * @return   ETrue if OK to carry on; EFalse if setting it to be abandoned
    *
    */
    IMPORT_C virtual TBool PostDisplayCheckL();


    /**
    * Implementation of CAknSettingPage framework method
    *
    */
    IMPORT_C virtual TBool OkToExitL(TBool aAccept);

    /**
    * Implementation of CCoeControl framework method
    * Called when the control has its size changed
    */
    IMPORT_C virtual void SizeChanged();
    
    void UpdateTextL();

    /**
    * Framework for password handling
    * Called when the old password is to be confirmed
    * @param    aPassword   old password
    * @param    aResourceId AVKON_PASSWORD_CONFIRMATION id to use
    */
    IMPORT_C virtual TBool ExecuteOldPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId );

    /**
    * Framework for password handling
    * Called when the new password is to be confirmed
    * @param    aPassword   new password
    * @param    aResourceId AVKON_PASSWORD_CONFIRMATION id to use
    */
    IMPORT_C virtual TBool ExecuteNewPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId );

    /**
    * Framework for password handling
    * Called to compare the two passwords
    * @param    reference (old) password
    * @param    candidate password; password just entered
    */
    IMPORT_C virtual TInt ComparePasswords( const TDesC& aRefPassword, const TDesC& aCandidatePassword, TAknPasswordMatchingMode ) const;

    /**
    * Utility method
    * Access to the old password confirmation resource
    * @return   id for AVKON_PASSWORD_CONFIRMATION structure
    */
    IMPORT_C TInt BCOldPasswordConfirmationResourceId() const;

    /**
    * Utility method
    * Access to the new password confirmation resource
    * @return   id for AVKON_PASSWORD_CONFIRMATION structure
    */
    IMPORT_C TInt BCNewPasswordConfirmationResourceId() const;

    /**
    * Utility method
    * Read in the confirmation resource structure
    * @param    aPasswordResourceId     id to use
    * @param    aResourceGroup      structure to fill
    */
    IMPORT_C void BCReadConfirmationResourceL( TInt aPasswordResourceId, SAknConfirmationResource& aResourceGroup );

    /**
    * Utility method
    * Run the password confirmation
    */
    IMPORT_C TBool BCDoPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId, TAknPasswordMatchingMode aMatchMode, TInt& aTries );

    /**
    * Utility method
    * Access to new password candidate
    */

    IMPORT_C TDes& BCNewPassword() const;

    /**
    * Utility method
    * Access to old password
    */
    IMPORT_C const TDesC& BCOldPassword() const;


    /**
     * Writes the internal state of the control and its components to aStream.
     * Does nothing in release mode.
     * Designed to be overidden and base called by subclasses.
     *
     * @param   aWriteSteam     A connected write stream
     */
    IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;


};


/**
 *
 * This class is used for alphanumeric passwords
 *
 */

class CBCTestAlphaPasswordSettingPage : public CAknAlphaPasswordSettingPage
{
public:
    /**
     * Simple constructor depending only on a single resource Id and the new and old password.
     * Editor resource is given via the link in the setting page resource.
     *
     * @param aSettingPageResourceId        Setting Page to use (if present)
     * @param aNewPassword
     * @param aOldPassword                  password to be checked against
     */
    IMPORT_C CBCTestAlphaPasswordSettingPage(
        TInt aResourceID,
        TDes& aNewPassword,
        const TDesC& aOldPassword);
    /**
     * Constructor that allows separate setting page and editor resources
     *
     * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
     *
     * In all cases the number (if supplied i.e. <> 0 ) is used.
     *
     *      Editor Resource     Setting Page Resource
     *          present             present             Both are used (but text & number overridden)
     *           = 0                    present             Editor resource is used via SP resource (Effectively like the other constructor)
     *          present             = 0                 Default Avkon SP resource if used + this editor resource
     *           = 0                    = 0                 uses default resource for both SP and editor. This is OK if:
     *   i) control type is present,
     *  ii) a default resource exists ( OK for text, integer, date, time, duration )
     *
     * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
     * cannot initialize such a member without allocation or having an internal dummy buffer.
     * This descriptor must be owned by the client since not copy is taken until ExecuteLD()
     *
     * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other
     * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource
     * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the
     * specific API for setting them, WILL override resource.
     * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
     *
     * @param aSettingTitleText     Text at top of setting pane; EXTERNALLY OWNED
     * @param aSettingNumber        Number at top left (if present)
     * @param aControlType          Determines the type constructed and how its resource is read
     * @param aEditorResourceId Editor resource to use in the setting page (if present)
     * @param aSettingPageResourceId        Setting Page to use (if present)
     * @param aNewPassword          Descriptor for the new password
     * @param aOldPassword          Descriptor for the old password
     */
    IMPORT_C CBCTestAlphaPasswordSettingPage(  const TDesC* aSettingTitleText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId,
                                TDes& aNewPassword,
                                const TDesC& aOldPassword );

    /**
    * Destructor
    */
    IMPORT_C virtual ~CBCTestAlphaPasswordSettingPage();

    /**
    * From CAknPasswordSettingPage - Implemented in this class
    * Copy text from the editor to the client's descriptor
    */
    IMPORT_C virtual void UpdateTextL();

    /**
    * Framework for password handling
    * Called to compare the two passwords
    * @param    reference (old) password
    * @param    candidate password; password just entered
    */
    IMPORT_C virtual TInt ComparePasswords( const TDesC& aRefPassword, const TDesC& aCandidatePassword, TAknPasswordMatchingMode ) const;

    /**
     * Writes the internal state of the control and its components to aStream.
     * Does nothing in release mode.
     * Designed to be overidden and base called by subclasses.
     *
     * @param   aWriteSteam     A connected write stream
     */
    IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;

};


/**
 *
 * This class is used for numeric passwords.  The API uses text descriptors rather than
 * integers for the PIN numbers as this is the usage
 *
 */

#include <aknnumseced.h>

class CBCTestNumericPasswordSettingPage : public CAknNumericPasswordSettingPage
{
public:
    /**
     * Simple constructor depending only on a single resource Id and the new and old password.
     * Editor resource is given via the link in the setting page resource.
     *
     * @param aSettingPageResourceId        Setting Page to use (if present)
     * @param aNewPassword
     * @param aOldPassword                  password to be checked against
     */
    IMPORT_C CBCTestNumericPasswordSettingPage(
        TInt aResourceID,
        TDes& aNewPassword,
        const TDesC& aOldPassword);
    /**
     * Constructor that allows separate setting page and editor resources
     *
     * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
     *
     * In all cases the number (if supplied i.e. <> 0 ) is used.
     *
     *      Editor Resource     Setting Page Resource
     *          present             present             Both are used (but text & number overridden)
     *           = 0                    present             Editor resource is used via SP resource (Effectively like the other constructor)
     *          present             = 0                 Default Avkon SP resource if used + this editor resource
     *           = 0                    = 0                 uses default resource for both SP and editor. This is OK if:
     *   i) control type is present,
     *  ii) a default resource exists ( OK for text, integer, date, time, duration )
     *
     * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
     * cannot initialize such a member without allocation or having an internal dummy buffer.
     * This descriptor must be owned by the client since not copy is taken until ExecuteLD()
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
     * @param aNewPassword          Descriptor for the new password
     * @param aOldPassword          Descriptor for the old password
     */
    IMPORT_C CBCTestNumericPasswordSettingPage(    const TDesC* aSettingTitleText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId,
                                TDes& aNewPassword,
                                const TDesC& aOldPassword );

     /**
    * Destructor
    */
    IMPORT_C virtual ~CBCTestNumericPasswordSettingPage();

    /**
    * From CAknPasswordSettingPage - Implemented in this class
    * Copy text from the editor to the client's descriptor
    */
    IMPORT_C virtual void UpdateTextL();

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
