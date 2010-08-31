/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test aknpasswordsettingpage.h
*
*/

#ifndef C_STIFPASSWORDSETTINGPAGE_H
#define C_STIFPASSWORDSETTINGPAGE_H

//Include files
#include <aknpasswordsettingpage.h>
#include <eikmobs.h>

/*
 * This class inherit from the CAknPasswordSettingPage class for 
 * testing the CAknPasswordSettingPage's protected function
 */
class CTestPasswordSettingPage:public CAknPasswordSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestPasswordSettingPage( TInt aResourceID, 
        TDes& aNewPassword, 
        const TDesC& aOldPassword );
    /*
     * Constructor
     */
    CTestPasswordSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,    
        TDes& aNewPassword, 
        const TDesC& aOldPassword );
    /*
     * Destructor
     */
    ~CTestPasswordSettingPage();
    /*
     * This fuction is wrote for testing UpdateTextL() function
     */
    void UpdateTextL();
    /*
     * This fuction is wrote for getting the old password confirmation 
     * resourceId
     */
    TInt GetOldPasswordConfirmationResourceId();
    /*
     * This fuction is wrote for getting the new password confirmation 
     * resourceId
     */
    TInt GetNewPasswordConfirmationResourceId();
    /*
     * This fuction is wrote for testing UpdateSettingL() function
     */
    void DoUpdateSettingL();
    /*
     * This fuction is wrote for testing AcceptSettingL() function
     */
    void DoAcceptSettingL();
    /*
     * This fuction is wrote for changing iUpdateMode's value
     */
    void SetUpdateMode( TInt aMode );
    /*
     * This fuction is wrote for testing HandleControlEventL() function
     */
    void DoHandleControlEventL( CCoeControl* aControl, 
        MCoeControlObserver::TCoeEvent aEventType );
    /*
     * This fuction is wrote for testing PostDisplayInitL() function
     */
    void DoPostDisplayInitL();
    /*
     * This fuction is wrote for getting DisplayCheckL()'s state
     */
    TBool GetPostDisplayCheckL();
    /*
     * This fuction is wrote for testing OkToExitL() function
     */
    TBool DoOkToExitL( TBool aAccept );
    /*
     * This fuction is wrote for testing SizeChanged() function
     */
    void DoSizeChanged();
    /*
     * This fuction is wrote for testing Draw() function
     */
    void DoDraw(const TRect& aRect) const;
    /*
     * This fuction is wrote for testing ExecuteOldPasswordConfirmationL() 
     * function
     */
    TBool DoExecuteOldPasswordConfirmationL(const TDesC& aPassword, 
        TInt aPasswordConfirmationResourceId );
    /*
     * This fuction is wrote for testing ExecuteNewPasswordConfirmationL() 
     * function
     */
    TBool DoExecuteNewPasswordConfirmationL(const TDesC& aPassword, 
        TInt aPasswordConfirmationResourceId );
    /*
     * This fuction is wrote for testing ComparePasswords() function
     */
    TInt DoComparePasswords( const TDesC& aRefPassword, 
        const TDesC& aCandidatePassword, TAknPasswordMatchingMode ) const;
    /*
     * This fuction is wrote for testing NewPasswordConfirmationResourceId() 
     * function
     */
    TInt DoNewPasswordConfirmationResourceId() const;
    /*
     * This fuction is wrote for testing OldPasswordConfirmationResourceId() 
     * function
     */
    TInt DoOldPasswordConfirmationResourceId() const;
    /*
     * This fuction is wrote for testing ReadConfirmationResourceL() 
     * function
     */
    void DoReadConfirmationResourceL( TInt aPasswordResourceId, 
        SAknConfirmationResource& aResourceGroup );
    /*
     * This fuction is wrote for testing DoPasswordConfirmationL() function
     */
    TBool DoDoPasswordConfirmationL(const TDesC& aPassword, 
        TInt aPasswordConfirmationResourceId, TAknPasswordMatchingMode aMatchMode, 
        TInt& aTries );
    /*
     * This fuction is wrote for testing NewPassword() function
     */
    TDes& DoNewPassword() const;
    /*
     * This fuction is wrote for testing OldPassword() function
     */
    const TDesC& DoOldPassword() const;
    /*
     * This fuction is wrote for testing WriteInternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;
    
    /*
     * This fuction is wrote for testing BaseConstructL() function
     */
    void DoActivateGc();
    /*
     * This fuction is wrote for testing BaseConstructL() function
     */
    void DoDeactivateGc();
    };

/*
 * This class inherit from the CAknAlphaPasswordSettingPage class for 
 * testing the CAknAlphaPasswordSettingPage's protected function
 */
class CTestAlphaPasswordSettingPage:public CAknAlphaPasswordSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestAlphaPasswordSettingPage( TInt aResourceID, 
        TDes& aNewPassword, 
        const TDesC& aOldPassword);
    /*
     * Constructor
     */
    CTestAlphaPasswordSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,    
        TDes& aNewPassword, 
        const TDesC& aOldPassword );
    /*
     * Destructor
     */
    ~CTestAlphaPasswordSettingPage();
    /*
     * This fuction is wrote for testing UpdateTextL() function
     */
    void DoUpdateTextL();
    /*
     * This fuction is wrote for testing ComparePasswords() function
     */
    TInt DoComparePasswords( const TDesC& aRefPassword, 
        const TDesC& aCandidatePassword, TAknPasswordMatchingMode ) const;
    /*
     * This fuction is wrote for testing WriteInternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;
    };

/*
 * This class inherit from the CAknNumericPasswordSettingPage class for 
 * testing the CAknNumericPasswordSettingPage's protected function
 */
class CTestNumbericPasswordSettingPage:public CAknNumericPasswordSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestNumbericPasswordSettingPage( TInt aResourceID, 
        TDes& aNewPassword, 
        const TDesC& aOldPassword );
    /*
     * Constructor
     */
    CTestNumbericPasswordSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,    
        TDes& aNewPassword, 
        const TDesC& aOldPassword );
    /*
     * Destructor
     */
    ~CTestNumbericPasswordSettingPage();
    /*
     * This fuction is wrote for testing UpdateTextL() function
     */
    void DoUpdateTextL();
    /*
     * This fuction is wrote for testing WriteInternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;
    };

#endif/*C_STIFPASSWORDSETTINGPAGE_H*/

//End file


