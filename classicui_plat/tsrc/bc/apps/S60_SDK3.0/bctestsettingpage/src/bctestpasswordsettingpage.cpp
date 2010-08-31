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










#include "bctestpasswordsettingpage.h"


//////////////////////////////////////////////////////////////////////
//
//  PASSWORD SETTING PAGE BASE CLASS
//
// This class holds the main data model for the password setting pages.
// It also does the drawing and other functions.
//
//////////////////////////////////////////////////////////////////////

/**
 *
 * Constructor from setting page resource id: Pass through to base class
 *
 */
EXPORT_C CBCTestPasswordSettingPage::CBCTestPasswordSettingPage(
    TInt aResourceId,
    TDes& aNewPassword,
    const TDesC& aOldPassword )
        :   CAknPasswordSettingPage( aResourceId,
            aNewPassword, aOldPassword )
    {

    }


EXPORT_C CBCTestPasswordSettingPage::CBCTestPasswordSettingPage(
                                const TDesC* aSettingText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId,
                                TDes& aNewPassword,
                                const TDesC& aOldPassword )
                                :   CAknPasswordSettingPage(
                                    aSettingText,
                                    aSettingNumber,
                                    aControlType,
                                    aEditorResourceId,
                                    aSettingPageResourceId,
                                    aNewPassword,
                                    aOldPassword)
    {
    }

/**
 * Acts upon changes in the hosted control's state.
 *
 * @param   aControl    The control changing its state (not used)
 * @param   aEventType  The type of control event
 */
EXPORT_C void CBCTestPasswordSettingPage::HandleControlEventL(CCoeControl* aControl,
                 MCoeControlObserver::TCoeEvent aEventType)
    {
    CAknPasswordSettingPage::HandleControlEventL( aControl, aEventType );
    }

/**
 *
 * Access routine for the confirmation resource structure
 *
 */
EXPORT_C TInt CBCTestPasswordSettingPage::BCOldPasswordConfirmationResourceId() const
    {
    return OldPasswordConfirmationResourceId();
    }
/**
 *
 * Access routine for the confirmation resource structure
 *
 */
EXPORT_C TInt CBCTestPasswordSettingPage::BCNewPasswordConfirmationResourceId() const
    {
    return NewPasswordConfirmationResourceId();
    }

/**
 * Access method for the new password
 *
 */
EXPORT_C TDes& CBCTestPasswordSettingPage::BCNewPassword() const
    {
    return NewPassword();
    }

/**
 * Access method for the old password
 *
 */
EXPORT_C const TDesC& CBCTestPasswordSettingPage::BCOldPassword() const
    {
    return OldPassword();
    }

/**
 *
 * This routine is called when the a change is detected in the editor.
 * The text is copied out to the referenced descriptor using a utility routine.
 *
 */
EXPORT_C void CBCTestPasswordSettingPage::UpdateSettingL()
    {
    CAknPasswordSettingPage::UpdateSettingL();
    }


/**
 * Checks if it OK to exit. This implementation performs a new password confirmation if the resource is defined
 * If there is no confirmation resource defined, then we exit.
 * If there is, then a confirmation query is put up.  Upon exit, if the match is OK, then we exit
 *
 * Returns ETrue if the dialog is ready to exit. Returns ETrue by default.
 */
EXPORT_C TBool CBCTestPasswordSettingPage::OkToExitL(TBool aAccept )
    {
    return CAknPasswordSettingPage::OkToExitL( aAccept );
    }


/**
 *
 * The value is copied out and the call back called if there is an observer
 *
 */
EXPORT_C void CBCTestPasswordSettingPage::AcceptSettingL()
    {
    CAknPasswordSettingPage::AcceptSettingL();
    }

/**
 * Reads in the resource structure associated with a password confirmation (old or new)
 *
 */
EXPORT_C void CBCTestPasswordSettingPage::BCReadConfirmationResourceL( TInt aResourceId, SAknConfirmationResource& resources )
    {
    ReadConfirmationResourceL( aResourceId, resources );
    }
    

/**
* Implementation of CAknSettingPage framework method
*
* Method called after full construction and activation of the setting page
*/
EXPORT_C void CBCTestPasswordSettingPage::PostDisplayInitL()
    {
    CAknPasswordSettingPage::PostDisplayInitL();
    }

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
EXPORT_C TBool CBCTestPasswordSettingPage::PostDisplayCheckL()
    {
    return CAknPasswordSettingPage::PostDisplayCheckL();
    }

/**
 * Base implementation of this framework method. Just call the generic Do.. routine
 * This implementation does not use "tries" but this may be a useful piece of information
 */
EXPORT_C TBool CBCTestPasswordSettingPage::ExecuteOldPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId )
    {
    return CAknPasswordSettingPage::ExecuteOldPasswordConfirmationL( aPassword, aPasswordConfirmationResourceId );
    }

/**
 * Base implementation of this framework method. Just call the generic Do.. routine
 *
 */
EXPORT_C TBool CBCTestPasswordSettingPage::ExecuteNewPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId )
    {
    return CAknPasswordSettingPage::ExecuteNewPasswordConfirmationL( aPassword, aPasswordConfirmationResourceId );
    }

/**
 *  Default implementation of a password confirmation procedure
 *
 */
EXPORT_C TBool CBCTestPasswordSettingPage::BCDoPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId, TAknPasswordMatchingMode aMatchMode, TInt& aTries )
    {
    return DoPasswordConfirmationL( aPassword, aPasswordConfirmationResourceId, aMatchMode, aTries );
    }

EXPORT_C TInt CBCTestPasswordSettingPage::ComparePasswords( const TDesC& aRefPassword, const TDesC& aCandidatePassword, enum CAknPasswordSettingPage::TAknPasswordMatchingMode aMode) const
    {
    return CAknPasswordSettingPage::ComparePasswords( aRefPassword, aCandidatePassword, aMode );
    }

EXPORT_C void CBCTestPasswordSettingPage::SizeChanged()
    {
    CAknPasswordSettingPage::SizeChanged();
    }
    
void CBCTestPasswordSettingPage::UpdateTextL()
    {
    
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CBCTestPasswordSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {}
#else
EXPORT_C void CBCTestPasswordSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CAknPasswordSettingPage::WriteInternalStateL(aWriteStream);
    }
#endif


//////////////////////////////////////////////////////////////////////
//
//  ALPHA PASSWORD SETTING PAGE
//
//////////////////////////////////////////////////////////////////////

/**
 *
 * Constructor from setting page resource id + referenced passwords.
 *
 */
EXPORT_C CBCTestAlphaPasswordSettingPage::CBCTestAlphaPasswordSettingPage(
    TInt aResourceId,
    TDes& aNewPassword,
    const TDesC& aOldPassword ):
    CAknAlphaPasswordSettingPage( aResourceId, aNewPassword, aOldPassword )
    {
    }

EXPORT_C CBCTestAlphaPasswordSettingPage::CBCTestAlphaPasswordSettingPage(
                                const TDesC* aSettingText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId,
                                TDes& aNewPassword,
                                const TDesC& aOldPassword )
                                :   CAknAlphaPasswordSettingPage(
                                    aSettingText,
                                    aSettingNumber,
                                    aControlType,
                                    aEditorResourceId,
                                    aSettingPageResourceId,
                                    aNewPassword,
                                    aOldPassword )
    {
    }

/**
 * Destructor
 *
 */
EXPORT_C CBCTestAlphaPasswordSettingPage::~CBCTestAlphaPasswordSettingPage()
    {
    }



/**
 * Soak up function to do the safe copying of the editor to the referenced value
 *
 */
EXPORT_C void CBCTestAlphaPasswordSettingPage::UpdateTextL()
    {
    CAknAlphaPasswordSettingPage::UpdateTextL();
    }

/**
 * Compares the given passwords.
 * Supports folding matching.
 */
EXPORT_C TInt CBCTestAlphaPasswordSettingPage::ComparePasswords( const TDesC& aRefPassword, const TDesC& aCandidatePassword, enum CAknPasswordSettingPage::TAknPasswordMatchingMode aMode) const
    {
    return CAknAlphaPasswordSettingPage::ComparePasswords( aRefPassword, aCandidatePassword, aMode );
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CBCTestAlphaPasswordSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {}
#else
EXPORT_C void CBCTestAlphaPasswordSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CAknAlphaPasswordSettingPage::WriteInternalStateL(aWriteStream);
    }
#endif

//////////////////////////////////////////////////////////////////////
//
//  NUMERIC PASSWORD SETTING PAGE
//
//////////////////////////////////////////////////////////////////////



/**
 *
 * Constructor from setting page resource id + referenced passwords.
 *
 */
EXPORT_C CBCTestNumericPasswordSettingPage::CBCTestNumericPasswordSettingPage(
    TInt aResourceId,
    TDes& aNewPassword,
    const TDesC& aOldPassword ):
    CAknNumericPasswordSettingPage(aResourceId, aNewPassword, aOldPassword)
    {
    }


EXPORT_C CBCTestNumericPasswordSettingPage::CBCTestNumericPasswordSettingPage(
                                const TDesC* aSettingText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId,
                                TDes& aNewPassword,
                                const TDesC& aOldPassword )
                                :   CAknNumericPasswordSettingPage(
                                    aSettingText,
                                    aSettingNumber,
                                    aControlType,
                                    aEditorResourceId,
                                    aSettingPageResourceId,
                                    aNewPassword,
                                    aOldPassword )
    {
    }

/**
 * Destructor
 *
 */
EXPORT_C CBCTestNumericPasswordSettingPage::~CBCTestNumericPasswordSettingPage()
    {
    }

/**
 * Soak up function to do the safe copying of the editor to the referenced value
 *
 */
EXPORT_C void CBCTestNumericPasswordSettingPage::UpdateTextL()
    {
    CAknNumericPasswordSettingPage::UpdateTextL();
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CBCTestNumericPasswordSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {}
#else
EXPORT_C void CBCTestNumericPasswordSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CAknNumericPasswordSettingPage::WriteInternalStateL(aWriteStream);
    }
#endif


// End of File
