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


//Include files
#include "testaknpasswordsettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::CTestPasswordSettingPage
// -----------------------------------------------------------------------------
//
CTestPasswordSettingPage::CTestPasswordSettingPage( TInt aResourceID, 
        TDes& aNewPassword, 
        const TDesC& aOldPassword ):CAknPasswordSettingPage( aResourceID, aNewPassword, 
        aOldPassword )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::CTestPasswordSettingPage
// -----------------------------------------------------------------------------
//
CTestPasswordSettingPage::CTestPasswordSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,    
    TDes& aNewPassword, 
    const TDesC& aOldPassword ):CAknPasswordSettingPage( aSettingTitleText, aSettingNumber,
                                   aControlType, aEditorResourceId, aSettingPageResourceId, 
                                   aNewPassword, aOldPassword )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::~CTestPasswordSettingPage
// -----------------------------------------------------------------------------
//
CTestPasswordSettingPage::~CTestPasswordSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::UpdateTextL
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::UpdateTextL()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::GetOldPasswordConfirmationResourceId
// -----------------------------------------------------------------------------
//
TInt CTestPasswordSettingPage::GetOldPasswordConfirmationResourceId()
    {
    return OldPasswordConfirmationResourceId();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::GetNewPasswordConfirmationResourceId
// -----------------------------------------------------------------------------
//
TInt CTestPasswordSettingPage::GetNewPasswordConfirmationResourceId()
    {
    return NewPasswordConfirmationResourceId();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoAcceptSettingL
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::DoAcceptSettingL()
    {
    AcceptSettingL();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::SetUpdateMode
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::SetUpdateMode( TInt aMode )
    {
    iUpdateMode = aMode;
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoHandleControlEventL
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::DoHandleControlEventL( CCoeControl* aControl, 
    MCoeControlObserver::TCoeEvent aEventType )
    {    
    HandleControlEventL( aControl, aEventType );
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoPostDisplayInitL
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::DoPostDisplayInitL()
    {
    PostDisplayInitL();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::GetPostDisplayCheckL
// -----------------------------------------------------------------------------
//
TBool CTestPasswordSettingPage::GetPostDisplayCheckL()
    {
    return PostDisplayCheckL();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoOkToExitL
// -----------------------------------------------------------------------------
//
TBool CTestPasswordSettingPage::DoOkToExitL( TBool aAccept )
    {
    return OkToExitL( aAccept);
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoSizeChanged
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::DoSizeChanged()
    {
    SizeChanged();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoDraw
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::DoDraw(const TRect& aRect) const
    {
    Draw( aRect );
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoExecuteOldPasswordConfirmationL
// -----------------------------------------------------------------------------
//
TBool CTestPasswordSettingPage::DoExecuteOldPasswordConfirmationL(const TDesC& aPassword, 
    TInt aPasswordConfirmationResourceId )
    {
    return ExecuteOldPasswordConfirmationL( aPassword, aPasswordConfirmationResourceId );
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoExecuteNewPasswordConfirmationL
// -----------------------------------------------------------------------------
//
TBool CTestPasswordSettingPage::DoExecuteNewPasswordConfirmationL(const TDesC& aPassword, 
    TInt aPasswordConfirmationResourceId )
    {
    return ExecuteNewPasswordConfirmationL( aPassword, aPasswordConfirmationResourceId );
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoComparePasswords
// -----------------------------------------------------------------------------
//
TInt CTestPasswordSettingPage::DoComparePasswords( const TDesC& aRefPassword, 
    const TDesC& aCandidatePassword, CAknPasswordSettingPage::TAknPasswordMatchingMode aMode ) const
    {
    return ComparePasswords( aRefPassword, aCandidatePassword, aMode );
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoOldPasswordConfirmationResourceId
// -----------------------------------------------------------------------------
//
TInt CTestPasswordSettingPage::DoOldPasswordConfirmationResourceId() const
    {
    return OldPasswordConfirmationResourceId();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoNewPasswordConfirmationResourceId
// -----------------------------------------------------------------------------
//
TInt CTestPasswordSettingPage::DoNewPasswordConfirmationResourceId() const
    {
    return NewPasswordConfirmationResourceId();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoReadConfirmationResourceL
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::DoReadConfirmationResourceL( TInt aPasswordResourceId, 
    SAknConfirmationResource& aResourceGroup )
    {
    ReadConfirmationResourceL( aPasswordResourceId, aResourceGroup );
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoDoPasswordConfirmationL
// -----------------------------------------------------------------------------
//
TBool CTestPasswordSettingPage::DoDoPasswordConfirmationL(const TDesC& aPassword, 
    TInt aPasswordConfirmationResourceId, TAknPasswordMatchingMode aMatchMode, TInt& aTries )
    {
    return DoPasswordConfirmationL( aPassword, aPasswordConfirmationResourceId,
        aMatchMode, aTries );
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoNewPassword
// -----------------------------------------------------------------------------
//
TDes& CTestPasswordSettingPage::DoNewPassword() const
    {
    return NewPassword();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoOldPassword
// -----------------------------------------------------------------------------
//
const TDesC& CTestPasswordSettingPage::DoOldPassword() const
    {
    return OldPassword();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::DoActivateGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingPage::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingPage::DoDeactivateGc()
    {
    DeactivateGc();
    }

// -----------------------------------------------------------------------------
// CTestAlphaPasswordSettingPage::CTestAlphaPasswordSettingPage
// -----------------------------------------------------------------------------
//
CTestAlphaPasswordSettingPage::CTestAlphaPasswordSettingPage( TInt aResourceID, 
        TDes& aNewPassword, 
        const TDesC& aOldPassword):CAknAlphaPasswordSettingPage( aResourceID, 
            aNewPassword,
            aOldPassword )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestAlphaPasswordSettingPage::CTestAlphaPasswordSettingPage
// -----------------------------------------------------------------------------
//
CTestAlphaPasswordSettingPage::CTestAlphaPasswordSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,
    TDes& aNewPassword, 
    const TDesC& aOldPassword ):CAknAlphaPasswordSettingPage( aSettingTitleText, 
        aSettingNumber,
        aControlType,
        aEditorResourceId,
        aSettingPageResourceId,
        aNewPassword,
        aOldPassword )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestAlphaPasswordSettingPage::~CTestAlphaPasswordSettingPage
// -----------------------------------------------------------------------------
//
CTestAlphaPasswordSettingPage::~CTestAlphaPasswordSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestAlphaPasswordSettingPage::DoUpdateTextL
// -----------------------------------------------------------------------------
//
void CTestAlphaPasswordSettingPage::DoUpdateTextL()
    {
    UpdateTextL();
    }

// -----------------------------------------------------------------------------
// CTestAlphaPasswordSettingPage::DoComparePasswords
// -----------------------------------------------------------------------------
//
TInt CTestAlphaPasswordSettingPage::DoComparePasswords( const TDesC& aRefPassword, 
    const TDesC& aCandidatePassword, CAknPasswordSettingPage::TAknPasswordMatchingMode aMode ) const
    {
    return ComparePasswords( aRefPassword, aCandidatePassword, 
        aMode );
    }

// -----------------------------------------------------------------------------
// CTestAlphaPasswordSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestAlphaPasswordSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestNumbericPasswordSettingPage::CTestNumbericPasswordSettingPage
// -----------------------------------------------------------------------------
//
CTestNumbericPasswordSettingPage::CTestNumbericPasswordSettingPage( TInt aResourceID, 
        TDes& aNewPassword, 
        const TDesC& aOldPassword ):CAknNumericPasswordSettingPage( aResourceID,
            aNewPassword,
            aOldPassword )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestNumbericPasswordSettingPage::CTestNumbericPasswordSettingPage
// -----------------------------------------------------------------------------
//
CTestNumbericPasswordSettingPage::CTestNumbericPasswordSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,    
    TDes& aNewPassword, 
    const TDesC& aOldPassword ):CAknNumericPasswordSettingPage( aSettingTitleText,
        aSettingNumber, 
        aControlType,
        aEditorResourceId, 
        aSettingPageResourceId, 
        aNewPassword,
        aOldPassword )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestNumbericPasswordSettingPage::~CTestNumbericPasswordSettingPage
// -----------------------------------------------------------------------------
//
CTestNumbericPasswordSettingPage::~CTestNumbericPasswordSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestNumbericPasswordSettingPage::DoUpdateTextL
// -----------------------------------------------------------------------------
//
void CTestNumbericPasswordSettingPage::DoUpdateTextL()
    {
    UpdateTextL();
    }

// -----------------------------------------------------------------------------
// CTestNumbericPasswordSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestNumbericPasswordSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

//End file


