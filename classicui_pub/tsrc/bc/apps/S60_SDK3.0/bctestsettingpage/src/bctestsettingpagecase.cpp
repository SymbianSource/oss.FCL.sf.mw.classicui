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









#include <w32std.h>
#include <coecntrl.h>
#include <coemain.h>
#include <eikmenup.h> 
#include <akniconarray.h>
#include <AknDesCArrayDecorator.h>
#include <in_sock.h>
#include <S32MEM.h>
#include <akndialog.h> 

#include "bctestsettingpagecase.h"
#include "bctestsettingpagecontainer.h"
#include "bctestsettingpage.hrh"
#include "bctestchecksettingpage.h"
#include "bctestpasswordsettingpage.h"
#include "bctesttextsettingpage.h"
#include "bctestslidersettingpage.h"
#include "bctestvolumesettingpage.h"
#include "bctestradiobuttonsettingpage.h"
#include "bctestsettingitemlist.h"
#include "bctestmfnesettingpage.h"
#include "bctestbasesettingpage.h"
#include <bctestsettingpage.rsg>

const TInt KAknBCTestSetPageCheckBoxSetPageNumber(1);
_LIT(KOldPassword, "TESTOLD");
_LIT( KTimeFormat, "%:0%J%:1%T%:2%S%:3%+B" );
_LIT(KTitle, "Title");

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestSettingPageCase* CBCTestSettingPageCase::NewL(
    CBCTestSettingPageContainer* aContainer )
    {
    CBCTestSettingPageCase* self = new( ELeave ) CBCTestSettingPageCase(
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestSettingPageCase::CBCTestSettingPageCase(
    CBCTestSettingPageContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSettingPageCase::~CBCTestSettingPageCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageCase::BuildScriptL()
    {
    // Add script as your need.
    //For TestCheckBoxSettingPage
    //AddTestL( LeftCBA, KeyOK, KeyOK, RightCBA, TEND );
    //For TestPasswordSettingPage
    AddTestL( LeftCBA, KeyOK, WAIT(2), RightCBA, WAIT(2), RightCBA, WAIT(2), RightCBA, WAIT(2), RightCBA, 
    WAIT(2), RightCBA, WAIT(2), RightCBA, WAIT(2), RightCBA, WAIT(2), LeftCBA, WAIT(2), RightCBA, WAIT(2), 
    RightCBA, WAIT(2), RightCBA, WAIT(2), RightCBA, WAIT(2), RightCBA, WAIT(2), RightCBA, 
    WAIT(2), RightCBA, WAIT(2), RightCBA, WAIT(2), RightCBA, WAIT(2), RightCBA, RightCBA, RightCBA, RightCBA,RightCBA, TEND );
    
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            TestAllL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageCase::PrepareCaseL( TInt aCmd )
    {
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control
            // instead of this.
            iControl = new( ELeave ) CCoeControl();
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageCase::TestCheckBoxSettingPage
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageCase::TestCheckBoxSettingPageL()
    {
    // Test some API here
    TBuf<20> temp;
	_LIT(KItem1, "Item1");
    temp.Append( KItem1 );
    CSelectableItem* item = new( ELeave ) CSelectableItem( temp, EFalse );
    CleanupStack::PushL( item );
	_LIT( KCheckBoxLog1, "CSelectableItem instance created" );
    AssertNotNullL( item, KCheckBoxLog1 );
    item->ConstructL();
	_LIT( KCheckBoxLog2, "CSelectableItem instance construct" );
    AssertTrueL( ETrue, KCheckBoxLog2 );
    item->SetSelectionStatus( ETrue );
	_LIT( KCheckBoxLog3, "Set item status to ETrue" );
    AssertTrueL( ETrue, KCheckBoxLog3 );
	_LIT( KCheckBoxLog4, "The selection status should be true" );
    AssertTrueL( item->SelectionStatus(), KCheckBoxLog4 );
	_LIT( KCheckBoxLog5, "Compare the item text" );
    AssertTrueL( ( item->ItemText().CompareC( KItem1 ) == 0 ), KCheckBoxLog5 );
   
    CSelectionItemList* itemList = new( ELeave ) CSelectionItemList( 1 );
    CleanupStack::PushL( itemList );
	_LIT( KCheckBoxLog6, "CSelectableItemList instance created" );
    AssertNotNullL( itemList, KCheckBoxLog6 );
    itemList->AppendL( item );
	_LIT( KCheckBoxLog7, "The count should be 1" );
    AssertIntL( 1, itemList->MdcaCount(), KCheckBoxLog7 );
    _LIT( KCheckBoxLog8, "The item text should be Item1" );
    AssertTrueL( ( itemList->MdcaPoint( 0 ).CompareC( KItem1 ) == 0 ), KCheckBoxLog8 );
    CBCTestCheckSettingPage* checkSettingPage = new( ELeave ) 
    CBCTestCheckSettingPage( R_BCTESTSETPAGE_CHECKBOX_SETTING_PAGE, itemList );
    CleanupStack::PushL( checkSettingPage );
    _LIT( KCheckBoxLog9, "CBCTestCheckSettingPage instance created" );
    AssertNotNullL( checkSettingPage, KCheckBoxLog9 );
    checkSettingPage->ConstructL();
    _LIT( KCheckBoxLog10, "CSelectableItem ConstructL called" );
    AssertTrueL( ETrue, KCheckBoxLog10 );
    _LIT( KCheckBoxLog11, "Get Listbox Control!" );
    AssertNotNullL( checkSettingPage->ListBoxControl(), KCheckBoxLog11 );
    checkSettingPage->SetSelectionItemArrayL( itemList );
    _LIT( KCheckBoxLog12, "Set itemlist" );
    AssertTrueL( ETrue, KCheckBoxLog12 );
    checkSettingPage->BCUpdateSettingL();
    _LIT( KCheckBoxLog13, "UpdateSettingL called" );
    AssertTrueL( ETrue, KCheckBoxLog13 );
    
    checkSettingPage->BCDynamicInitL();
    _LIT( KCheckBoxLog14, "DynamicInitL called" );
    AssertTrueL( ETrue, KCheckBoxLog14 );
    checkSettingPage->BCSelectCurrentItemL();
    _LIT( KCheckBoxLog15, "SelectCurrentItemL called" );
    AssertTrueL( ETrue, KCheckBoxLog15 );
    
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    checkSettingPage->HandlePointerEventL( pointEvent );
    _LIT( KCheckBoxLog16, "HandlePointerEventL called" );
    AssertTrueL( ETrue, KCheckBoxLog16 );
    
    CBufFlat* buf = CBufFlat::NewL( 200 );
    RBufWriteStream stream;
    stream.Open( *buf );
    checkSettingPage->BCWriteInternalStateL( stream );
	_LIT( KCheckBoxLog17, "WriteInternalStateL called" );
    AssertTrueL( ETrue, KCheckBoxLog17 ); 
    stream.Close();
    delete buf;
    
    CleanupStack::Pop( checkSettingPage );
    checkSettingPage->ExecuteLD( CAknSettingPage::EUpdateWhenChanged );
    _LIT( KCheckBoxLog18, "Function called" );
    AssertTrueL( ETrue, KCheckBoxLog18 ); 
    AssertTrueL( ETrue, KCheckBoxLog18 );
    AssertTrueL( ETrue, KCheckBoxLog18 ); 
	AssertTrueL( ETrue, KCheckBoxLog18 );
	AssertTrueL( ETrue, KCheckBoxLog18 );
	AssertTrueL( ETrue, KCheckBoxLog18 );
	AssertTrueL( ETrue, KCheckBoxLog18 );
    
    TBuf<20> titleText;
	_LIT( KCheckBoxLog19, "Six Args" );
    titleText.Append( KCheckBoxLog19 );
    CBCTestCheckSettingPage* settingPage = new (ELeave) 
            CBCTestCheckSettingPage(
	&titleText, 
	KAknBCTestSetPageCheckBoxSetPageNumber, 
	EAknSetListBox, 
	R_BCTESTSETPAGE_CHECKBOX_SETTING_PAGE, 
	0,
	itemList);
	_LIT( KCheckBoxLog20, "CBCTestCheckSettingPage instance created using six args" );
	AssertNotNullL( settingPage, KCheckBoxLog20 );
           
    delete settingPage;
    CleanupStack::PopAndDestroy( 2 );
    }
    
// ---------------------------------------------------------------------------
// CBCTestSettingPageCase::TestPasswordSettingPage
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageCase::TestPasswordSettingPageL()
    {
    TBuf<10> temp;
	_LIT(KPASSWORDLOG1, "TEST" );
    temp.Append( KPASSWORDLOG1 );
    CBCTestPasswordSettingPage* pwdSettingPage = new (ELeave)
     CBCTestPasswordSettingPage( R_BCTEST_PASSWORD_SETTING_PAGE, temp, 
      KOldPassword );

    CleanupStack::PushL( pwdSettingPage );
    _LIT(KPASSWORDLOG2, "CBCTestPasswordSettingPage instance created" );
    AssertNotNullL( pwdSettingPage, KPASSWORDLOG2 );
    
    pwdSettingPage->UpdateSettingL();
	_LIT(KPASSWORDLOG3, "UpdateSettingL called" );
    AssertTrueL( ETrue, KPASSWORDLOG3  );
    pwdSettingPage->AcceptSettingL();
    _LIT(KPASSWORDLOG4, "AcceptSettingL called" );
    AssertTrueL( ETrue, KPASSWORDLOG4 ); 
    pwdSettingPage->PostDisplayInitL();
    _LIT(KPASSWORDLOG5, "Function called" );
    AssertTrueL( ETrue, KPASSWORDLOG5 );
    AssertTrueL( pwdSettingPage->PostDisplayCheckL(), KPASSWORDLOG5 ); 

    AssertTrueL( ( EFalse == pwdSettingPage->ExecuteOldPasswordConfirmationL(
       KOldPassword, R_AKNATSETPAGE_ALPHA_PASSWORD_OLD_CONFIRMATION ) ), 
       KPASSWORDLOG5 );
    AssertTrueL( ( EFalse == pwdSettingPage->ExecuteOldPasswordConfirmationL(
       temp, R_AKNATSETPAGE_NUMERIC_PASSWORD_NEW_CONFIRMATION ) ), 
       KPASSWORDLOG5 ); 
       
    AssertTrueL( ( ( pwdSettingPage->BCNewPassword() ).CompareC( KPASSWORDLOG1 ) == 0  ), 
      KPASSWORDLOG5 );
    AssertTrueL( ( ( pwdSettingPage->BCOldPassword() ).CompareC( KOldPassword ) == 0  ), 
      KPASSWORDLOG5 );
      
    pwdSettingPage->SetOldPasswordConfirmationResourceId(
         R_AKNATSETPAGE_ALPHA_PASSWORD_OLD_CONFIRMATION );
    AssertTrueL( ETrue, KPASSWORDLOG5 );   
    pwdSettingPage->SetNewPasswordConfirmationResourceId(
         R_AKNATSETPAGE_NUMERIC_PASSWORD_NEW_CONFIRMATION );
    AssertTrueL( ETrue, KPASSWORDLOG5 ); 
    pwdSettingPage->SetMatchingMode( CAknPasswordSettingPage::ECaseInsensitive ) ;
    AssertTrueL( ETrue, KPASSWORDLOG5 ); 
    AssertTrueL( ( CAknPasswordSettingPage::ECaseInsensitive
        == pwdSettingPage->MatchingMode() ), 
        KPASSWORDLOG5 );
    pwdSettingPage->SetMaxPasswordLength( 50 );
    AssertTrueL( ETrue, KPASSWORDLOG5 ); 
    AssertIntL( 50, pwdSettingPage->MaxPasswordLength(), 
        KPASSWORDLOG5 ); 
    _LIT(KPASSWORDLOG6, "NewPasswordConfirmationResourceId called" );       
    AssertIntL( R_AKNATSETPAGE_NUMERIC_PASSWORD_NEW_CONFIRMATION,
      pwdSettingPage->BCNewPasswordConfirmationResourceId(), 
      KPASSWORDLOG6 );
    _LIT(KPASSWORDLOG7, "OldPasswordConfirmationResourceId called" );       
    AssertIntL( R_AKNATSETPAGE_ALPHA_PASSWORD_OLD_CONFIRMATION,
      pwdSettingPage->BCOldPasswordConfirmationResourceId(), 
      KPASSWORDLOG7 );

    TBuf<15> candidatePwd;
    candidatePwd.Append( KOldPassword );  
    AssertIntL( 0, pwdSettingPage->ComparePasswords( KOldPassword , candidatePwd, 
        CAknPasswordSettingPage::ECaseInsensitive ), 
        KPASSWORDLOG5 );

    SAknConfirmationResource confirmationResource;    
    pwdSettingPage->BCReadConfirmationResourceL( R_AKNATSETPAGE_NUMERIC_PASSWORD_NEW_CONFIRMATION, 
        confirmationResource );
    AssertTrueL( ETrue, KPASSWORDLOG5 ); 

    TInt tries = 1;
    AssertTrueL( ( EFalse == pwdSettingPage->BCDoPasswordConfirmationL( KOldPassword,  
        R_AKNATSETPAGE_ALPHA_PASSWORD_OLD_CONFIRMATION, 
        CAknPasswordSettingPage::ECaseInsensitive, 
        tries ) ), 
        KPASSWORDLOG5 );
    
    CleanupStack::Pop( pwdSettingPage );
    pwdSettingPage->ExecuteLD();
    pwdSettingPage = NULL;
    AssertTrueL( ETrue, KPASSWORDLOG5 );
    AssertTrueL( ETrue, KPASSWORDLOG5 );
    AssertTrueL( ETrue, KPASSWORDLOG5 );

    TBuf<20> titleText;
    _LIT(KPASSWORDLOG8, "Six Args" );
    titleText.Append( KPASSWORDLOG8 );    
    pwdSettingPage = new (ELeave)
    CBCTestPasswordSettingPage( &titleText, KAknBCTestSetPageCheckBoxSetPageNumber,
      EAknCtNumericSecretEditor, R_AKNATSETPAGE_NUMERIC_PASSWORD, 
      R_BCTEST_PASSWORD_SETTING_PAGE, temp, KOldPassword );
    _LIT(KPASSWORDLOG9, "CBCTestPasswordSettingPage's six arg constructor called" );
    AssertTrueL( ETrue, KPASSWORDLOG9 );

    CleanupStack::PushL( pwdSettingPage );
    pwdSettingPage->HandleControlEventL( NULL, MCoeControlObserver::EEventRequestCancel );
    _LIT( KPASSWORDLOG10, "CBCTestPasswordSettingPage HandleControlEventL called" );
    AssertTrueL( ETrue, KPASSWORDLOG10 );
    CleanupStack::PopAndDestroy();

    //For AlphaPasswordSettingPage
    CBCTestAlphaPasswordSettingPage* alphaPwdSettingPage = new CBCTestAlphaPasswordSettingPage(
        R_BCTEST_PASSWORD_SETTING_PAGE, temp, KOldPassword);
    _LIT( KPASSWORDLOG11, "Constructor called" );
    AssertNotNullL( alphaPwdSettingPage, KPASSWORDLOG11 );

    CleanupStack::PushL( alphaPwdSettingPage );
    alphaPwdSettingPage->ConstructL();
    AssertTrueL( ETrue, KPASSWORDLOG5 );
    AssertNotNullL( alphaPwdSettingPage->AlphaPasswordEditor(), KPASSWORDLOG5 );
    alphaPwdSettingPage->UpdateTextL();
    AssertTrueL( ETrue, KPASSWORDLOG5 );
    AssertIntL( 0, alphaPwdSettingPage->ComparePasswords( KOldPassword , candidatePwd, 
        CAknPasswordSettingPage::ECaseInsensitive ), 
        KPASSWORDLOG5 );
        
    CBufFlat* buf = CBufFlat::NewL( 200 );
    RBufWriteStream stream;
    stream.Open( *buf );
    alphaPwdSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KPASSWORDLOG5 ); 
    AssertTrueL( ETrue, KPASSWORDLOG5 ); 
    stream.Close();
    delete buf;
    
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    alphaPwdSettingPage->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KPASSWORDLOG5 );

    CleanupStack::PopAndDestroy();
    alphaPwdSettingPage = NULL;
    AssertTrueL( ETrue, KPASSWORDLOG5 );

    alphaPwdSettingPage = new (ELeave)
        CBCTestAlphaPasswordSettingPage( &titleText, KAknBCTestSetPageCheckBoxSetPageNumber,
        EAknCtNumericSecretEditor, R_AKNATSETPAGE_NUMERIC_PASSWORD, 
        R_BCTEST_PASSWORD_SETTING_PAGE, temp, KOldPassword );
    _LIT( KPASSWORDLOG12, "Constructor with six args called" );
    AssertNotNullL( alphaPwdSettingPage, KPASSWORDLOG12 );
    CleanupStack::PushL( alphaPwdSettingPage );    
    CleanupStack::PopAndDestroy();

    //For CAknNumericPasswordSettingPage
    CBCTestNumericPasswordSettingPage* numericPwdSettingPage = new CBCTestNumericPasswordSettingPage(
        R_BCTEST_PASSWORD_SETTING_PAGE, temp, KOldPassword);
    _LIT( KPASSWORDLOG13, "CBCTestNumericPasswordSettingPage Constructor called" );
    AssertNotNullL( numericPwdSettingPage, KPASSWORDLOG13 );

    CleanupStack::PushL( numericPwdSettingPage );
    numericPwdSettingPage->ConstructL();
   _LIT( KPASSWORDLOG14, "CBCTestNumericPasswordSettingPage ConstructL called" );
    AssertTrueL( ETrue, KPASSWORDLOG14 );
    AssertNotNullL( numericPwdSettingPage->NumericPasswordEditor(), KPASSWORDLOG5 );
    numericPwdSettingPage->UpdateTextL();
    AssertTrueL( ETrue, KPASSWORDLOG5 );
        
    buf = CBufFlat::NewL( 200 );
    stream.Open( *buf );
    numericPwdSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KPASSWORDLOG5 ); 
    stream.Close();
    delete buf;
    
    numericPwdSettingPage->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KPASSWORDLOG5 );

    CleanupStack::PopAndDestroy();
    numericPwdSettingPage = NULL;
    AssertTrueL( ETrue, KPASSWORDLOG5 );

    numericPwdSettingPage = new (ELeave)
        CBCTestNumericPasswordSettingPage( &titleText, KAknBCTestSetPageCheckBoxSetPageNumber,
        EAknCtNumericSecretEditor, R_AKNATSETPAGE_NUMERIC_PASSWORD, 
        R_BCTEST_PASSWORD_SETTING_PAGE, temp, KOldPassword );
    AssertNotNullL( numericPwdSettingPage, KPASSWORDLOG5 );
    CleanupStack::PushL( numericPwdSettingPage );    
    CleanupStack::PopAndDestroy();   

    }
        
// ---------------------------------------------------------------------------
// CBCTestSettingPageCase::TestTextSettingPage
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageCase::TestTextSettingPageL()
    {
    TBuf<10> temp;
	_LIT( KTEXSETTINGPAGELOG1, "TEST" );
    temp.Append( KTEXSETTINGPAGELOG1 );
    //For CAknEdwinSettingPage
    CBCTestEdwinSettingPage* edwinSettingPage = new (ELeave) CBCTestEdwinSettingPage(
        R_AKNATSETPAGE_TEXT_SETTING_PAGE );
    CleanupStack::PushL( edwinSettingPage );
    edwinSettingPage->ConstructL();
	_LIT( KTEXSETTINGPAGELOG2, "CBCTestEdwinSettingPage construct called" );
    AssertNotNullL( edwinSettingPage, KTEXSETTINGPAGELOG2 );
	_LIT( KTEXSETTINGPAGELOG3, "TextControl called" );
    AssertNotNullL( edwinSettingPage->TextControl(), KTEXSETTINGPAGELOG3 );
    
    CleanupStack::PopAndDestroy( edwinSettingPage );
    edwinSettingPage = NULL;
    edwinSettingPage = new (ELeave) CBCTestEdwinSettingPage( 
                                &temp,
                                KAknBCTestSetPageCheckBoxSetPageNumber,
                                EEikCtEdwin,
                                R_AKNATSETPAGE_EDWIN,
                                R_AKNATSETPAGE_TEXT_SETTING_PAGE );
	_LIT( KTEXSETTINGPAGELOG4, "CBCTestEdwinSettingPage construct with args called" );
    AssertNotNullL( edwinSettingPage, KTEXSETTINGPAGELOG4 );
        
    delete edwinSettingPage;

    //For CAknTextSettingPage
    CBCTestTextSettingPage* textSettingPage = new ( ELeave ) CBCTestTextSettingPage(
        R_AKNATSETPAGE_TEXT_SETTING_PAGE, temp );
	_LIT( KTEXSETTINGPAGELOG5, "CBCTestTextSettingPage constructor called" );
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG5 );

    CleanupStack::PushL( textSettingPage );

    textSettingPage->ConstructL();
	_LIT( KTEXSETTINGPAGELOG6, "Function called" );
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    textSettingPage->DynamicInitL();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    textSettingPage->UpdateSettingL();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    textSettingPage->AcceptSettingL();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    textSettingPage->RestoreOriginalSettingL();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    textSettingPage->CheckAndSetDataValidity();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    textSettingPage->UpdateTextL();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    textSettingPage->UpdateCbaL();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );    
    textSettingPage->SizeChanged(); 
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    
    CBufFlat* buf = CBufFlat::NewL( 200 );
    RBufWriteStream stream;
    stream.Open( *buf );
    textSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 ); 
    stream.Close();
    delete buf;
    
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    textSettingPage->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 ); 
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 ); 
    
    CleanupStack::PopAndDestroy();

    textSettingPage = new (ELeave) CBCTestTextSettingPage( 
                                &temp,
                                KAknBCTestSetPageCheckBoxSetPageNumber,
                                EEikCtEdwin,
                                R_AKNATSETPAGE_EDWIN,
                                R_AKNATSETPAGE_TEXT_SETTING_PAGE, temp );
    _LIT( KTEXSETTINGPAGELOG7, "CBCTestTextSettingPage construct with args called" );
    AssertNotNullL( textSettingPage, KTEXSETTINGPAGELOG7 );
    delete textSettingPage; 
    _LIT( KTEXSETTINGPAGELOG8, "CBCTestTextSettingPage destructor called" );
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG8 );


    //For CAknIntegerSettingPage
    TInt test = 10;
    CBCTestIntegerSettingPage* integerSettingPage = new (ELeave) 
        CBCTestIntegerSettingPage( R_AKNATSETPAGE_TEXT_SETTING_PAGE, test );
    _LIT( KTEXSETTINGPAGELOG9, "CBCTestIntegerSettingPage constructor called" );
    AssertNotNullL( integerSettingPage, KTEXSETTINGPAGELOG9 );
    CleanupStack::PushL( integerSettingPage );

    integerSettingPage->ConstructL();
    _LIT( KTEXSETTINGPAGELOG10, "ConstructL called" );
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG10 );
    _LIT( KTEXSETTINGPAGELOG11, "CBCTestIntegerSettingPage IntegerEditorControl called" );
    AssertNotNullL( integerSettingPage->IntegerEditorControl(), KTEXSETTINGPAGELOG11 ); 

    integerSettingPage->DynamicInitL();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    integerSettingPage->UpdateSettingL();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    integerSettingPage->RestoreOriginalSettingL();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    integerSettingPage->CheckAndSetDataValidity();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    integerSettingPage->UpdateCbaL();
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );    
    integerSettingPage->SizeChanged(); 
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    
    buf = CBufFlat::NewL( 200 );
    stream.Open( *buf );
    integerSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 ); 
    stream.Close();
    delete buf;
    
    integerSettingPage->HandleControlEventL( integerSettingPage->IntegerEditorControl(),
    	 MCoeControlObserver::EEventRequestFocus ); 
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );
    
    integerSettingPage->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 );     
     	    
    CleanupStack::PopAndDestroy();

    integerSettingPage = new (ELeave) CBCTestIntegerSettingPage( 
                                &temp,
                                KAknBCTestSetPageCheckBoxSetPageNumber,
                                EEikCtEdwin,
                                R_AKNATSETPAGE_EDWIN,
                                R_AKNATSETPAGE_TEXT_SETTING_PAGE, test );
    AssertNotNullL( integerSettingPage, KTEXSETTINGPAGELOG6 );
 
    delete integerSettingPage; 
    AssertTrueL( ETrue, KTEXSETTINGPAGELOG6 ); 

    }
 
// ---------------------------------------------------------------------------
// CBCTestSettingPageCase::TestSliderSettingPage
// ---------------------------------------------------------------------------
//   
void CBCTestSettingPageCase::TestSliderSettingPageL()
    {
    TInt value = 10;
    TBuf<10> temp;
	_LIT( KSLIDERSETTINGPAGELOG1, "Slider" );
    temp.Append( KSLIDERSETTINGPAGELOG1 );
    CBCTestSliderSettingPage* sliderSettingPage = new (ELeave) 
        CBCTestSliderSettingPage( R_AKNATSETPAGE_SLIDER_SETTING_PAGE, value );
	_LIT( KSLIDERSETTINGPAGELOG2, "CBCTestSliderSettingPage constructor called" );
    AssertNotNullL( sliderSettingPage, KSLIDERSETTINGPAGELOG2 );
    CleanupStack::PushL( sliderSettingPage );
    sliderSettingPage->ConstructL();
    _LIT( KSLIDERSETTINGPAGELOG3, "ConstructL called" );
    AssertTrueL( ETrue, KSLIDERSETTINGPAGELOG3 );
    _LIT( KSLIDERSETTINGPAGELOG4, "CBCTestSliderSettingPage constructor called" );
    AssertNotNullL( sliderSettingPage->SliderControl(), KSLIDERSETTINGPAGELOG4 );
    sliderSettingPage->UpdateSettingL();
    _LIT( KSLIDERSETTINGPAGELOG5, "CBCTestSliderSettingPage UpdateSettingL called" );
    AssertTrueL( ETrue, KSLIDERSETTINGPAGELOG5 );
    sliderSettingPage->AcceptSettingL();
    _LIT( KSLIDERSETTINGPAGELOG6, "Function called" );
    AssertTrueL( ETrue, KSLIDERSETTINGPAGELOG6 ); 
    sliderSettingPage->RestoreOriginalSettingL();
    AssertTrueL( ETrue, KSLIDERSETTINGPAGELOG6 );
    sliderSettingPage->SizeChanged();
    AssertTrueL( ETrue, KSLIDERSETTINGPAGELOG6 );
        
    CBufFlat* buf = CBufFlat::NewL( 200 );
    RBufWriteStream stream;
    stream.Open( *buf );
    sliderSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KSLIDERSETTINGPAGELOG6 ); 
    stream.Close();
    delete buf;
    
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    sliderSettingPage->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KSLIDERSETTINGPAGELOG6 ); 
  
    CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KSLIDERSETTINGPAGELOG6 );

    sliderSettingPage = new (ELeave) 
        CBCTestSliderSettingPage( &temp, 
    							  KAknBCTestSetPageCheckBoxSetPageNumber, 
    							  EAknCtSlider,
    							  R_AKNATSETPAGE_SLIDER, 
    							  R_AKNATSETPAGE_SLIDER_SETTING_PAGE,
    							  value );
        
    AssertNotNullL( sliderSettingPage, KSLIDERSETTINGPAGELOG6 );
    sliderSettingPage->ExecuteLD();
    AssertTrueL( ETrue, KSLIDERSETTINGPAGELOG6 );
    }


void CBCTestSettingPageCase::TestVolumeSettingPageL()
    {
	_LIT( KVOLUMESETTINGPAGELOG1, "Volume" );
    TInt volumevalue = 3;
    TBuf<10> temp;
    temp.Append( KVOLUMESETTINGPAGELOG1 );
    CBCTestVolumeSettingPage* volumeSettingPage = new (ELeave) 
        CBCTestVolumeSettingPage( R_AKNATSETPAGE_VOLUME_SETTING_PAGE, volumevalue );
	_LIT( KVOLUMESETTINGPAGELOG2, "CBCTestVolumeSettingPage constructor called" );
    AssertNotNullL( volumeSettingPage, KVOLUMESETTINGPAGELOG2 );
    CleanupStack::PushL( volumeSettingPage );
    volumeSettingPage->ConstructL();
	_LIT( KVOLUMESETTINGPAGELOG3, "ConstructL called" );
    AssertTrueL( ETrue, KVOLUMESETTINGPAGELOG3 );
	_LIT( KVOLUMESETTINGPAGELOG4, "CBCTestVolumeSettingPage constructor called" );
    AssertNotNullL( volumeSettingPage->VolumeControl(), KVOLUMESETTINGPAGELOG4 ); 
    
    CBufFlat* buf = CBufFlat::NewL( 200 );
    RBufWriteStream stream;
    stream.Open( *buf );
    volumeSettingPage->WriteInternalStateL( stream );
	_LIT( KVOLUMESETTINGPAGELOG5, "CBCTestSliderSettingPage WriteInternalStateL called" );
    AssertTrueL( ETrue, KVOLUMESETTINGPAGELOG5 ); 
    stream.Close();
    delete buf;

    volumeSettingPage->UpdateSettingL();
	_LIT( KVOLUMESETTINGPAGELOG6, "Function called" );
    AssertTrueL( ETrue, KVOLUMESETTINGPAGELOG6 );
    volumeSettingPage->AcceptSettingL();
    AssertTrueL( ETrue, KVOLUMESETTINGPAGELOG6 );
    volumeSettingPage->RestoreOriginalSettingL();
    AssertTrueL( ETrue, KVOLUMESETTINGPAGELOG6 );
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    volumeSettingPage->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KVOLUMESETTINGPAGELOG6 );     
    CleanupStack::PopAndDestroy();

    volumeSettingPage = new (ELeave) 
        CBCTestVolumeSettingPage( &temp, 
    					KAknBCTestSetPageCheckBoxSetPageNumber, 
    					EAknCtVolumeControl,
    					R_AKNATSETPAGE_VOLUME, 
    					R_AKNATSETPAGE_VOLUME_SETTING_PAGE,
    					volumevalue );
    AssertNotNullL( volumeSettingPage, KVOLUMESETTINGPAGELOG6 );
    volumeSettingPage->ExecuteLD();
    AssertTrueL( ETrue, KVOLUMESETTINGPAGELOG6 );
    AssertTrueL( ETrue, KVOLUMESETTINGPAGELOG6 );
    }
   
void CBCTestSettingPageCase::TestRadioButtonSettingPageL()
    {
    TBuf<10> title;
	_LIT( KRADIOBUTTONSETTINGPAGELOG1, "Radio" );
    title.Append( KRADIOBUTTONSETTINGPAGELOG1 );
    CDesCArrayFlat* array = CCoeEnv::Static()->ReadDesCArrayResourceL(
        R_AKNATSETPAGE_LIST_ITEM_ARRAY );
    CleanupStack::PushL( array );
    TInt currentItem(0);
    
    CBCTestRadioButtonSettingPage* radioButtonSettingPage = new (ELeave) 
        CBCTestRadioButtonSettingPage( R_AKNATSETPAGE_RADIOBTN_SETPAGE, 
        currentItem, array );
	_LIT( KRADIOBUTTONSETTINGPAGELOG2, "CBCTestVolumeSettingPage constructor called" );
    AssertNotNullL( radioButtonSettingPage, KRADIOBUTTONSETTINGPAGELOG2 );
    CleanupStack::PushL( radioButtonSettingPage );
    radioButtonSettingPage->ConstructL();
	_LIT( KRADIOBUTTONSETTINGPAGELOG3, "ConstructL called!" );
    AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG3 );
	_LIT( KRADIOBUTTONSETTINGPAGELOG4, "Radiobuttonsettingpage ListBoxControl called" );
    AssertNotNullL( radioButtonSettingPage->ListBoxControl(), KRADIOBUTTONSETTINGPAGELOG4 );
    radioButtonSettingPage->SetItemArrayAndSelectionL(
        array, currentItem );
	_LIT( KRADIOBUTTONSETTINGPAGELOG5, "SetItemArrayAndSelectionL called!" );
    AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG5 );
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    radioButtonSettingPage->HandlePointerEventL( pointEvent );
	_LIT( KRADIOBUTTONSETTINGPAGELOG6, "Radiobuttonsettingpage HandlePointerEventL called" );
    AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG6 );     
 
	_LIT( KRADIOBUTTONSETTINGPAGELOG7, "Function called" );
    radioButtonSettingPage->HandleResourceChange( KAknsMessageSkinChange );
    AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG7 );
    radioButtonSettingPage->HandleListBoxEventL( radioButtonSettingPage->ListBoxControl(),
    	MEikListBoxObserver::EEventEnterKeyPressed );
    AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG7 );
            	
	radioButtonSettingPage->UpdateSettingL();
    AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG7 );
    radioButtonSettingPage->DynamicInitL();
    AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG7 );
    radioButtonSettingPage->SelectCurrentItemL();
	AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG7 );
	radioButtonSettingPage->UpdateCbaL();
    AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG7 );

    CBufFlat* buf = CBufFlat::NewL( 200 );
    RBufWriteStream stream;
    stream.Open( *buf );
    radioButtonSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG7 ); 
    stream.Close();
    delete buf;
    
    CleanupStack::Pop( radioButtonSettingPage );
    radioButtonSettingPage->ExecuteLD(); 
    AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG7 );
    AssertTrueL( ETrue, KRADIOBUTTONSETTINGPAGELOG7 );        
  
    
    CleanupStack::PopAndDestroy();
    
    radioButtonSettingPage = new CBCTestRadioButtonSettingPage( &title,
                                KAknBCTestSetPageCheckBoxSetPageNumber,
                                EAknSetListBox,
                                R_AKNATSETPAGE_RADIOBTN_SETPAGE_LISTBOX,
                                R_AKNATSETPAGE_RADIOBTN_SETPAGE,
                                currentItem,
                                array );
	_LIT( KRADIOBUTTONSETTINGPAGELOG8, "CBCTestVolumeSettingPage with args constructor called" );
    AssertNotNullL( radioButtonSettingPage, KRADIOBUTTONSETTINGPAGELOG8 );
  
    delete radioButtonSettingPage;
	
    }
    
void CBCTestSettingPageCase::TestSettingItemListL()
    {
    TBuf<10> settingTitle;
	_LIT( KSETTINGITEMLISTLOG1, "Setting" );
    settingTitle.Append( KSETTINGITEMLISTLOG1 );
    TInt identifier = 1000;

    CBCTestSettingItem* settingItem = new (ELeave) CBCTestSettingItem( R_AKNATSETPAGE_TEXT_SETTING_PAGE );
	_LIT( KSETTINGITEMLISTLOG2, "CBCTestSettingItem constructor called!" );
    AssertNotNullL( settingItem, KSETTINGITEMLISTLOG2 );
    CleanupStack::PushL( settingItem );
   
    settingItem->StoreL();
	_LIT( KSETTINGITEMLISTLOG3, "CBCTestSettingItem StoreL called" );
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG3 );
    settingItem->EditItemL( ETrue );
	_LIT( KSETTINGITEMLISTLOG4, "CBCTestSettingItem EditItemL called" );
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG4 );
   
    settingItem->IsHidden();
	_LIT( KSETTINGITEMLISTLOG5, "CBCTestSettingItem IsHidden called" );
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG5 );    
    settingItem->IsNumberedStyle();
	_LIT( KSETTINGITEMLISTLOG6, "Function called" );
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );    
    settingItem->SetHidden( ETrue );
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );    
    settingItem->ListBoxText();
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->Identifier();
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->HasIcon();
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );    
    settingItem->SetEmptyItemTextL( settingTitle );
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->SetCompulsoryIndTextL( settingTitle );
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->VisibleIndex();
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->SetSettingPageFlags( EFalse );
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );    
    settingItem->SettingPageFlags();
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->CreateBitmapL();
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );   
    settingItem->SetSettingPage( NULL );
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->SettingPage();    
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->EmptyItemText();
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->SettingPageResourceId();
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->SettingEditorResourceId();
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->AssociatedResourceId();
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    settingItem->SetIconMask( NULL );
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );
    CleanupStack::PopAndDestroy(); 
    AssertTrueL( ETrue, KSETTINGITEMLISTLOG6 );

    
    //For CAknTextSettingItem
    CBCTestTextSettingItem* textSettingItem = new (ELeave) CBCTestTextSettingItem(
        identifier, settingTitle );
	_LIT( KTEXTSETTINGITEMLOG1, "CBCTestTextSettingItem constructor called!" );
    AssertNotNullL( textSettingItem, KTEXTSETTINGITEMLOG1 );
    CleanupStack::PushL( textSettingItem );
    CArrayPtr<CGulIcon>* iconArray = new (ELeave) CAknIconArray(3);
    textSettingItem->ConstructL( EFalse, 50, settingTitle, iconArray, 
        R_AKNATSETPAGE_TEXT_SETTING_PAGE, EEikCtEdwin );
    _LIT( KTEXTSETTINGITEMLOG2, "CBCTestSettingItem ConstructL called" );
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG2 );
    _LIT( KTEXTSETTINGITEMLOG3, "CBCTestSettingItem CompleteConstructL called" );
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG3 );
    _LIT( KTEXTSETTINGITEMLOG4, "CBCTestSettingItem LoadL called" );
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG4 );
    _LIT( KTEXTSETTINGITEMLOG5, "CBCTestSettingItem CreateBitmapL called");
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG5 );
    _LIT( KTEXTSETTINGITEMLOG6, "CBCTestSettingItem UpdateListBoxTextL called" );
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG6 );
    _LIT( KTEXTSETTINGITEMLOG7, "CBCTestSettingItem UpdateBitmapL called" );
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG7 );    
    _LIT( KTEXTSETTINGITEMLOG8, "Function called" );   
    textSettingItem->StoreL();
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG8 );
    textSettingItem->LoadL();
    
    textSettingItem->SettingName();
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG8 ); 
    textSettingItem->SettingNumber();
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG8 );
    settingItem->SettingTextL();
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG8 ); 
   
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG8 );
    textSettingItem->SettingTextL();
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG8 );
    textSettingItem->EditItemL( ETrue );
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG8 );
    textSettingItem->InternalTextPtr();
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG8 );
    textSettingItem->SetExternalText( settingTitle );
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG8 );
    textSettingItem->ExternalText();
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG8 );
 
    CleanupStack::PopAndDestroy( textSettingItem );
    delete iconArray;
    AssertTrueL( ETrue, KTEXTSETTINGITEMLOG8 );
    
    //For CAknIntegerSettingItem
    TInt value = 10;
    CBCTestIntegerSettingItem* integerSettingItem = new (ELeave) 
        CBCTestIntegerSettingItem( identifier, value );
	_LIT( KINTEGERSETTINGITEMLOG1, "CBCTestIntegerSettingItem constructor called!" );
    AssertNotNullL( integerSettingItem, KINTEGERSETTINGITEMLOG1 );
    CleanupStack::PushL( integerSettingItem );
    iconArray = new (ELeave) CAknIconArray(3);
    integerSettingItem->ConstructL( EFalse, 50, settingTitle, iconArray, 
        R_AKNATSETPAGE_TEXT_SETTING_PAGE, EEikCtEdwin );
	_LIT( KINTEGERSETTINGITEMLOG2, "CBCTestIntegerSettingItem CompleteConstructionL called" );
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG2 );
    
    integerSettingItem->StoreL();
	_LIT( KINTEGERSETTINGITEMLOG3, "Function called" );
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );
    integerSettingItem->LoadL();
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );
    integerSettingItem->SettingTextL();
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );
    integerSettingItem->EditItemL( ETrue );
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );
    
    CAknSettingPage* dlg = new( ELeave )CAknIntegerSettingPage(        
        &settingTitle, 
        integerSettingItem->SettingNumber(), 
        EEikCtEdwin,
        integerSettingItem->SettingEditorResourceId(), 
        integerSettingItem->SettingPageResourceId(), 
        integerSettingItem->InternalValueRef(), 
        integerSettingItem->SettingPageFlags() ); // Flags
    integerSettingItem->SetSettingPage( dlg );
    integerSettingItem->SetUpStandardSettingPageL();
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );
    integerSettingItem->HandleSettingPageEventL(integerSettingItem->SettingPage(),
    	MAknSettingPageObserver::EEventSettingCancelled );   
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 ); 
    delete dlg;
    integerSettingItem->SetSettingPage( NULL );
    
    integerSettingItem->InternalValueRef();
    AssertTrueL( ETrue, 
        KINTEGERSETTINGITEMLOG3 ); 
    integerSettingItem->ExternalValueRef(); 
    AssertTrueL( ETrue, 
        KINTEGERSETTINGITEMLOG3 );
    integerSettingItem->SetExternalValue( value );
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );
    CleanupStack::Pop( integerSettingItem );
    delete integerSettingItem;
    delete iconArray;
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );   

    //For  CAknIntegerEdwinSettingItem
    CAknIntegerEdwinSettingItem* integerEdSettingItem = new (ELeave) 
        CAknIntegerEdwinSettingItem( identifier, value );
    AssertNotNullL( integerEdSettingItem, KINTEGERSETTINGITEMLOG3 );
    CleanupStack::PushL( integerEdSettingItem );
    iconArray = new (ELeave) CAknIconArray(3);
    integerEdSettingItem->ConstructL( EFalse, 50, settingTitle, iconArray, 
        R_AKNATSETPAGE_TEXT_SETTING_PAGE, EEikCtEdwin );  
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );
   
    integerEdSettingItem->StoreL();
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );
    integerEdSettingItem->LoadL();
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );

    integerEdSettingItem->EditItemL( EFalse );
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );

    CleanupStack::Pop( integerEdSettingItem );
    delete integerEdSettingItem;
    delete iconArray;
    AssertTrueL( ETrue, KINTEGERSETTINGITEMLOG3 );        

    
    //For CAknPasswordSettingItem
    TBuf<10> temp;
	_LIT( KPASSWORDSETTINGITEMLOG1, "1234" );
    temp.Append( KPASSWORDSETTINGITEMLOG1 );
    CBCTestPasswordSettingItem* pwdSettingItem = new (ELeave) 
        CBCTestPasswordSettingItem( identifier, CAknPasswordSettingItem::ENumeric, temp );
	_LIT( KPASSWORDSETTINGITEMLOG2, "CAknPasswordSettingItem constructor called!" );
    AssertNotNullL( pwdSettingItem, KPASSWORDSETTINGITEMLOG2 );
    CleanupStack::PushL( pwdSettingItem );
    iconArray = new (ELeave) CAknIconArray(3);
    pwdSettingItem->ConstructL( EFalse, 50, settingTitle, iconArray, 
        R_BCTEST_PASSWORD_SETTING_PAGE, EEikCtEdwin );
	_LIT( KPASSWORDSETTINGITEMLOG3, "Function called!" );
    AssertTrueL( ETrue, KPASSWORDSETTINGITEMLOG3 );
    pwdSettingItem->SettingTextL();
    AssertTrueL( ETrue, KPASSWORDSETTINGITEMLOG3 );
    pwdSettingItem->EditItemL( EFalse );
    AssertTrueL( ETrue, KPASSWORDSETTINGITEMLOG3 );
    CleanupStack::Pop( pwdSettingItem );
    delete pwdSettingItem;
    AssertTrueL( ETrue, KPASSWORDSETTINGITEMLOG3 );
    delete iconArray;
    
    //For CAknVolumeSettingItem
    TInt volume = 2;
    CBCTestVolumeSettingItem* volumeSettingItem = new (ELeave) 
       CBCTestVolumeSettingItem( identifier, volume );
	_LIT( KVOLUMESETTINGITEMLOG1, "CAknVolumeSettingItem constructor called!" );
    AssertNotNullL( volumeSettingItem, KVOLUMESETTINGITEMLOG1 );
    CleanupStack::PushL( volumeSettingItem );
    iconArray = new (ELeave) CAknIconArray(3);
    volumeSettingItem->ConstructL( EFalse, 50, settingTitle, iconArray, 
        R_AKNATSETPAGE_VOLUME_SETTING_PAGE, EAknCtVolumeControl );
	_LIT( KVOLUMESETTINGITEMLOG2, "Function called" );
    AssertTrueL( ETrue, KVOLUMESETTINGITEMLOG2 );       
    AssertTrueL( ETrue, KVOLUMESETTINGITEMLOG2 );
    volumeSettingItem->StoreL();     
    AssertTrueL( ETrue, KVOLUMESETTINGITEMLOG2 );
    volumeSettingItem->LoadL();
    AssertTrueL( ETrue, KVOLUMESETTINGITEMLOG2 );
    volumeSettingItem->SettingTextL();
    AssertTrueL( ETrue, KVOLUMESETTINGITEMLOG2 );
    volumeSettingItem->EditItemL( EFalse );
    AssertTrueL( ETrue,KVOLUMESETTINGITEMLOG2 ); 
    volumeSettingItem->InternalVolumeValue();
    AssertTrueL( ETrue, KVOLUMESETTINGITEMLOG2 );       
    
    CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KVOLUMESETTINGITEMLOG2 ); 
    delete iconArray;
    
    //For CAknSliderSettingItem
    TInt slideValue = 3;
    CBCTestSliderSettingItem* sliderSettingItem = new (ELeave) 
        CBCTestSliderSettingItem( identifier, slideValue );
	_LIT( KSLIDERSETTINGITEMLOG1, "CAknSliderSettingItem constructor called!" );
    AssertNotNullL( sliderSettingItem, KSLIDERSETTINGITEMLOG1 );
    CleanupStack::PushL( sliderSettingItem ); 
    iconArray = new (ELeave) CAknIconArray(3);
    sliderSettingItem->ConstructL( EFalse, 50, settingTitle, iconArray, 
        R_AKNATSETPAGE_SLIDER_SETTING_PAGE, EAknCtSlider ); 
	_LIT( KSLIDERSETTINGITEMLOG2, "Function called!" );
    AssertTrueL( ETrue, KSLIDERSETTINGITEMLOG2 );
    
    sliderSettingItem->StoreL();     
    AssertTrueL( ETrue, KSLIDERSETTINGITEMLOG2 );
    sliderSettingItem->LoadL();
    AssertTrueL( ETrue, KSLIDERSETTINGITEMLOG2 );
    sliderSettingItem->SettingTextL();
    AssertTrueL( ETrue, KSLIDERSETTINGITEMLOG2 );
    sliderSettingItem->EditItemL( EFalse );
    AssertTrueL( ETrue, KSLIDERSETTINGITEMLOG2 ); 
    sliderSettingItem->InternalSliderValue();
    AssertTrueL( ETrue, KSLIDERSETTINGITEMLOG2 );
    sliderSettingItem->CreateAndExecuteSettingPageL();
    AssertTrueL( ETrue, KSLIDERSETTINGITEMLOG2 ); 
    AssertTrueL( ETrue, KSLIDERSETTINGITEMLOG2 );
    CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KSLIDERSETTINGITEMLOG2 );
    delete iconArray;
    
    //For CAknTimeOrDateSettingItem
    TTime time;
    time.HomeTime();
    CAknTimeOrDateSettingItem* timeDateItem = new (ELeave) CAknTimeOrDateSettingItem
        ( identifier, CAknTimeOrDateSettingItem::ETime, time );
	_LIT( KTIMEORDATESETTINGITEMLOG1, "CAknTimeOrDateSettingItem constructor called!" );
    AssertNotNullL( timeDateItem, KTIMEORDATESETTINGITEMLOG1 );
    CleanupStack::PushL( timeDateItem );
    iconArray = new (ELeave) CAknIconArray(3);
    timeDateItem->ConstructL( EFalse, 50, settingTitle, iconArray, 
        R_AKNATSETPAGE_TIME_SETTING_PAGE, EEikCtTimeEditor );
	_LIT( KTIMEORDATESETTINGITEMLOG2, "Function called!" );
    AssertTrueL( ETrue, KTIMEORDATESETTINGITEMLOG2 ); 
    timeDateItem->StoreL();
    AssertTrueL( ETrue, KTIMEORDATESETTINGITEMLOG2 );          
    timeDateItem->LoadL();
    AssertTrueL( ETrue, KTIMEORDATESETTINGITEMLOG2 ); 
    timeDateItem->SettingTextL();
    AssertTrueL( ETrue, KTIMEORDATESETTINGITEMLOG2 ); 
    timeDateItem->EditItemL( EFalse );
    AssertTrueL( ETrue, KTIMEORDATESETTINGITEMLOG2 ); 
    timeDateItem->SetTimeFormatStringL( KTimeFormat );
    AssertTrueL( ETrue, KTIMEORDATESETTINGITEMLOG2 ); 
    timeDateItem->TimeFormatString();
    AssertTrueL( ETrue, KTIMEORDATESETTINGITEMLOG2 ); 
    CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KTIMEORDATESETTINGITEMLOG2 );     
    delete iconArray;
    
    //For CAknTimeOffsetSettingItem
    TTimeIntervalSeconds seconds(60);

    CAknTimeOffsetSettingItem* timeOffsetItem = new (ELeave)
        CAknTimeOffsetSettingItem( identifier, seconds );
	_LIT( KTIMEOFFSETSETTINGITEMLOG1, "CAknTimeOffsetSettingItem constructor called!" );
    AssertNotNullL( timeOffsetItem, KTIMEOFFSETSETTINGITEMLOG1 );
    CleanupStack::PushL( timeOffsetItem );
    iconArray = new (ELeave) CAknIconArray(3);
    timeOffsetItem->ConstructL( EFalse, 50, settingTitle, iconArray, 
        R_AKNATSETPAGE_DURATION_SETTING_PAGE, EEikCtDurationEditor );
	_LIT( KTIMEOFFSETSETTINGITEMLOG2, "Function called!" );
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGITEMLOG2 );
    timeOffsetItem->StoreL();
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGITEMLOG2 );
    timeOffsetItem->LoadL();
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGITEMLOG2 ); 
    timeOffsetItem->SettingTextL();
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGITEMLOG2 ); 
    timeOffsetItem->SetTimeFormatStringL( KTimeFormat );
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGITEMLOG2 ); 
    timeOffsetItem->TimeFormatString();
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGITEMLOG2 ); 
    
//    timeOffsetItem->EditItemL( ETrue );
//    AssertTrueL( ETrue, _L( "CAknTimeOffsetSettingItem EditItemL called" ) ); 
    CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGITEMLOG2 );     
    delete iconArray;
  
    //For CAknIpFieldSettingItem
    TInetAddr ipAddr(10);
    CAknIpFieldSettingItem* ipFieldItem = new (ELeave) CAknIpFieldSettingItem (
        identifier, ipAddr );
	_LIT( KIPFIELDSETTINGITEMLOG1, "CAknIpFieldSettingItem constructor called!" );
    AssertNotNullL( ipFieldItem, KIPFIELDSETTINGITEMLOG1 );
    CleanupStack::PushL( ipFieldItem );
    iconArray = new (ELeave) CAknIconArray(3);
    ipFieldItem->ConstructL( EFalse, 50, settingTitle, iconArray, 
        R_AKNATSETPAGE_IPADDRESS_SETTING_PAGE, EAknCtIpFieldEditor );
    _LIT( KIPFIELDSETTINGITEMLOG2, "Function called!" );
    AssertTrueL( ETrue, KIPFIELDSETTINGITEMLOG2 ); 
    ipFieldItem->StoreL();
    AssertTrueL( ETrue, KIPFIELDSETTINGITEMLOG2 );
    ipFieldItem->LoadL();
    AssertTrueL( ETrue, KIPFIELDSETTINGITEMLOG2 ); 
    ipFieldItem->SettingTextL();
    AssertTrueL( ETrue, KIPFIELDSETTINGITEMLOG2 ); 
    ipFieldItem->EditItemL( EFalse );
    AssertTrueL( ETrue, KIPFIELDSETTINGITEMLOG2 );        
    CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KIPFIELDSETTINGITEMLOG2 );     
    delete iconArray;
    
    //For CAknEnumeratedItemBase
    TInt enumValue = 10;
    TInt enumPtr = 11;
    CAknEnumeratedItemBase* enumItemBase = new (ELeave) CAknEnumeratedItemBase(
        enumValue, &enumPtr );
	_LIT( KENUMERATEDITEMBASELOG1, "CAknEnumeratedItemBase constructor called!" );
    AssertNotNullL( enumItemBase, KENUMERATEDITEMBASELOG1 );
	_LIT( KENUMERATEDITEMBASELOG2, "Function called!" );
    enumItemBase->EnumerationValue();
    AssertTrueL( ETrue, KENUMERATEDITEMBASELOG2 );
    enumItemBase->SetEnumerationValue( enumValue );
    AssertTrueL( ETrue, KENUMERATEDITEMBASELOG2 );
    enumItemBase->Value();
    AssertTrueL( ETrue, KENUMERATEDITEMBASELOG2 );
    enumItemBase->SetValue( &enumPtr );
    AssertTrueL( ETrue, KENUMERATEDITEMBASELOG2 );
    delete enumItemBase;
    AssertTrueL( ETrue, KENUMERATEDITEMBASELOG2 );
     
    
    //For CAknEnumeratedTextSettingItem
    CBCTestEnumeratedTextSettingItem* enumTextItem = new (ELeave) 
        CBCTestEnumeratedTextSettingItem( R_AKNATSETPAGE_ENUMTEXT_SETTING_PAGE );
	_LIT( KENUMERATEDTEXTSETTINGITEMLOG1, "CAknEnumeratedTextSettingItem CompleteConstructionL called" );
    AssertTrueL( ETrue, KENUMERATEDTEXTSETTINGITEMLOG1 );
    _LIT( KENUMERATEDTEXTSETTINGITEMLOG2, "Function called" );
    AssertNotNullL( enumTextItem, KENUMERATEDTEXTSETTINGITEMLOG2 );
    CleanupStack::PushL( enumTextItem );
         
    enumTextItem->EnumeratedTextArray();
    AssertTrueL( ETrue, KENUMERATEDTEXTSETTINGITEMLOG2 );
    enumTextItem->PoppedUpTextArray();         
    AssertTrueL( ETrue, KENUMERATEDTEXTSETTINGITEMLOG2 );
    CArrayPtr<CAknEnumeratedText>* enumeratedTextArray = 
    	new (ELeave) CArrayPtrFlat<CAknEnumeratedText>(1);
    CArrayPtr<HBufC>* poppedUpTextArray = new (ELeave) CArrayPtrFlat<HBufC>(1);
    enumTextItem->SetEnumeratedTextArrays( enumeratedTextArray, poppedUpTextArray );
	AssertTrueL( ETrue, KENUMERATEDTEXTSETTINGITEMLOG2 );
    enumTextItem->HandleTextArrayUpdateL();
	AssertTrueL( ETrue, KENUMERATEDTEXTSETTINGITEMLOG2 );
	enumTextItem->NumberOfItems();    
	AssertTrueL( ETrue, KENUMERATEDTEXTSETTINGITEMLOG2 );
	enumTextItem->IndexFromValue( 0 );
	AssertTrueL( ETrue, KENUMERATEDTEXTSETTINGITEMLOG2 );
	enumTextItem->SetSettingPageTextL();
	AssertTrueL( ETrue, KENUMERATEDTEXTSETTINGITEMLOG2 );
	enumTextItem->SettingPageTextArray();
    AssertTrueL( ETrue, KENUMERATEDTEXTSETTINGITEMLOG2 );
	CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KENUMERATEDTEXTSETTINGITEMLOG2 );

    //For CAknEnumeratedTextPopupSettingItem
    
    TInt popItemValue = 2;
	CBCTestEnumeratedTextPopupSettingItem* enumTextPopupitem = new (ELeave)
	    CBCTestEnumeratedTextPopupSettingItem( R_AKNATSETPAGE_POPUP_SETTING_PAGE, popItemValue );
	_LIT( KENUMERATEDTEXTPOPUPSETTINGITEMLOG1, "CAknEnumeratedTextPopupSettingItem constructor called!" );
    AssertNotNullL( enumTextPopupitem, KENUMERATEDTEXTPOPUPSETTINGITEMLOG1 );
 	_LIT( KENUMERATEDTEXTPOPUPSETTINGITEMLOG2, "Function called!" ); 
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );
    CleanupStack::PushL( enumTextPopupitem );

    enumeratedTextArray = new (ELeave) CArrayPtrFlat<CAknEnumeratedText>(10);
    poppedUpTextArray = new (ELeave) CArrayPtrFlat<HBufC>(10);
    enumTextPopupitem->SetEnumeratedTextArrays( enumeratedTextArray, poppedUpTextArray );
	AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );
	enumTextPopupitem->LoadL();
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );
    enumTextPopupitem->StoreL();
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );
//    enumTextPopupitem->EditItemL( EFalse );
//    AssertTrueL( ETrue, _L( "CAknEnumeratedTextPopupSettingItem EditItemL called" ) );
    enumTextPopupitem->EnumeratedTextArray();
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );
    enumTextPopupitem->PoppedUpTextArray();
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );
//    enumTextPopupitem->CreateAndExecuteSettingPageL();
//    AssertTrueL( ETrue, _L( "CAknEnumeratedTextPopupSettingItem CreateSettingPageL called" ) );
//    AssertTrueL( ETrue, _L( "CAknEnumeratedTextPopupSettingItem CreateAndExecuteSettingPageL called" ) );
    enumTextPopupitem->SetExternalValue( 0 );
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );
    enumTextPopupitem->SetInternalValue( 0 );
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );
    
    enumTextPopupitem->SetSelectedIndex( 0 );
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );
    
//    enumTextPopupitem->SettingTextL();
//    AssertTrueL( ETrue, _L( "CAknEnumeratedTextPopupSettingItem SettingTextL called" ) );
    enumTextPopupitem->IndexFromValue( 2 );
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );      	
    enumTextPopupitem->ExternalValue();
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );
    enumTextPopupitem->InternalValue();
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 ); 
    enumTextPopupitem->QueryValue();
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );     	
	CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KENUMERATEDTEXTPOPUPSETTINGITEMLOG2 );

    //For CAknBinaryPopupSettingItem
  
    TBool binaryValue = EFalse;
    CBCTestBinaryPopupSettingItem* binaryItem = new (ELeave) CBCTestBinaryPopupSettingItem
        ( R_AKNATSETPAGE_POPUP_SETTING_PAGE, binaryValue );
	_LIT( KBINARYPOPUPSETTINGITEMLOG1, "CAknBinaryPopupSettingItem constructor called!" );
    AssertNotNullL( binaryItem,  KBINARYPOPUPSETTINGITEMLOG1 );
    CleanupStack::PushL( binaryItem );

/*  iconArray = new (ELeave) CAknIconArray(3);
    binaryItem->ConstructL( EFalse, 50, settingTitle, iconArray, 
    	R_AKNATSETPAGE_POPUP_SETTING_PAGE, EAknCtPopupSettingList );
    AssertTrueL( ETrue, _L( "CAknBinaryPopupSettingItem CompleteConstructionL called" ) );
*/
    binaryItem->StoreL();
	_LIT( KBINARYPOPUPSETTINGITEMLOG2, "CAknBinaryPopupSettingItem StoreL called" );
    AssertTrueL( ETrue, KBINARYPOPUPSETTINGITEMLOG2 );
//    binaryItem->LoadL();
//    AssertTrueL( ETrue, _L( "CAknBinaryPopupSettingItem LoadL called" ) );   
//    binaryItem->EditItemL( EFalse );
//    AssertTrueL( ETrue, _L( "CAknBinaryPopupSettingItem EditItemL called" ) );
    CleanupStack::PopAndDestroy();
//    delete iconArray;
       
    //For CAknBigSettingItemBase
    CBCTestBigSettingItemBase* bigItemBase = new (ELeave) CBCTestBigSettingItemBase( identifier );
	_LIT( KBIGSETTINGITEMLOG1, "CAknBigSettingItemBase constructor called!" );
    AssertNotNullL( bigItemBase, KBIGSETTINGITEMLOG1 );
    CleanupStack::PushL( bigItemBase );
    iconArray = new (ELeave) CAknIconArray(3);
    bigItemBase->ConstructL( EFalse, 50, settingTitle, iconArray, 
        R_AKNATSETPAGE_TEXT_SETTING_PAGE, EEikCtEdwin ); 
    bigItemBase->SettingTextL();
	_LIT( KBIGSETTINGITEMLOG2, "CAknBigSettingItemBase SettingTextL called" );
    AssertTrueL( ETrue, KBIGSETTINGITEMLOG2 ); 
    CleanupStack::PopAndDestroy();
    delete iconArray;
    
    //For CAknSettingItemArray

    CBCTestSettingItemArray* itemArray = new (ELeave) CBCTestSettingItemArray(
    	1, EFalse, 0 );
	_LIT( KSETTINGITEMARRAYLOG1, "CAknSettingItemArray constructor called!" );
    AssertNotNullL( itemArray, KBIGSETTINGITEMLOG1 );
        
    CleanupStack::PushL( itemArray );
    itemArray->MdcaCount();
    AssertTrueL( ETrue, KSETTINGITEMARRAYLOG1 );
    itemArray->RecalculateVisibleIndicesL();
    AssertTrueL( ETrue, KSETTINGITEMARRAYLOG1 );
    itemArray->SetInitialOrdinal( 0 );
    AssertTrueL( ETrue, KSETTINGITEMARRAYLOG1 );
    itemArray->SetFlags( 0 );
    AssertTrueL( ETrue, KSETTINGITEMARRAYLOG1 );
    itemArray->SetVisibleCount( 1 );
    AssertTrueL( ETrue, KSETTINGITEMARRAYLOG1 );
    itemArray->VisibleCount();
    AssertTrueL( ETrue, KSETTINGITEMARRAYLOG1 );
    itemArray->ItemIndexFromVisibleIndex( 1 );
    AssertTrueL( ETrue, KSETTINGITEMARRAYLOG1 );
//    itemArray->MdcaPoint(  );
//    AssertTrueL( ETrue, _L( "CBCTestSettingItemArray MdcaPoint called" ) );  
	CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KSETTINGITEMARRAYLOG1 );
    
    //For CAknSettingItemList
    CBCTestSettingItemList* itemList = new (ELeave)CBCTestSettingItemList();
	_LIT( KSETTINGITEMLISTITEMLOG1, "CAknSettingItemList constructor called!" );
    AssertNotNullL( itemList, KSETTINGITEMLISTITEMLOG1 );
    CleanupStack::PushL( itemList );
    itemList->ConstructFromResourceL( R_AKNATSETPAGE_SETTING_LIST_SETTING_INTEGER );
	_LIT( KSETTINGITEMLISTITEMLOG2, "Function called!" );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->CountComponentControls();	
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->ComponentControl(0);
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    TKeyEvent keyEvent;
    keyEvent.iCode = 0;
    itemList->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->FocusChanged( EDrawNow );	
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->HandleResourceChange( KAknsMessageSkinChange );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->HandleListBoxEventL( itemList->ListBox(),  MEikListBoxObserver::EEventEnterKeyPressed );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->EditItemL( 0, EFalse );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->LoadSettingsL();
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->StoreSettingsL();
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->SetIncludeHiddenInOrdinal( EFalse );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->IsNumberedStyle();
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->ListBox();
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->SettingItemArray();
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    itemList->HandleChangeInItemArrayOrVisibilityL();
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    itemList->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );      
	CAknSettingItem* tempitem = itemList->CreateSettingItemL( 1 );
    AssertTrueL( ETrue, KSETTINGITEMLISTITEMLOG2 );
    delete tempitem;      	     	    
    CleanupStack::PopAndDestroy( itemList );
 
    }
    
void CBCTestSettingPageCase::TestSettingPageL()
	{
	//For AknSettingPage
	TBuf<10> text;
	_LIT( KSETTINGPAGELOG1, "Test" );
	text.Append( KSETTINGPAGELOG1 );
	CBCTestBaseSettingPage* settingPage = new (ELeave) CBCTestBaseSettingPage(
		R_AKNATSETPAGE_TEXT_SETTING_PAGE );
	_LIT( KSETTINGPAGELOG2, "AknSettingPage constructor called" );
	AssertTrueL( ETrue, KSETTINGPAGELOG2 );
	CleanupStack::PushL( settingPage );
	settingPage->ConstructL();
	_LIT( KSETTINGPAGELOG3, "Function called" );
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	settingPage->EditorControl();
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	settingPage->SettingId();
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	settingPage->SetSettingId( R_AKNATSETPAGE_TEXT_SETTING_PAGE );
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	settingPage->SetSettingNumberL( 1 );
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	settingPage->SetSettingTextL( text );
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	settingPage->SetSettingPageObserver( NULL );
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );	
	settingPage->SettingNumber();
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	settingPage->IsNumbered();
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	settingPage->SetNumbered( EFalse );
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    TInt controlType;
	TInt editorResourceId;
	CAknSettingPage::GetEditorResourceInfoL( R_AKNATSETPAGE_TEXT_SETTING_PAGE, 
		controlType, editorResourceId );
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );	
    
    settingPage->SizeChanged();
    AssertTrueL( ETrue,KSETTINGPAGELOG3 );
    settingPage->FocusChanged( EDrawNow );
    AssertTrueL( ETrue, KSETTINGPAGELOG3 ); 
    settingPage->HandleControlEventL( NULL, MCoeControlObserver::EEventRequestCancel );
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );    
    settingPage->DynamicInitL();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->UpdateSettingL();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 ); 
    settingPage->AcceptSettingL();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->RestoreOriginalSettingL();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 ); 
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->SetFocusToEditor(); //Only Panic in this function
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->SelectCurrentItemL();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->DismissL( EFalse );
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->MenuShowing();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );    
    settingPage->Waiting();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->Cba();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->DefaultCbaResourceId();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    TKeyEvent keyEvent;
    keyEvent.iCode = 0;
    settingPage->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    	
    settingPage->StandardSettingPageLayout();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->IsBaseConstructed();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->SettingPageResourceId();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->ResetFlags();  
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->DataValidity();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->SetDataValidity( EFalse );
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->CheckAndSetDataValidity();
    AssertTrueL( ETrue, KSETTINGPAGELOG3 );

    CBufFlat* buf = CBufFlat::NewL( 200 );
    RBufWriteStream stream;
    stream.Open( *buf );
    settingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KSETTINGPAGELOG3 ); 
    stream.Close();
    delete buf;      
	settingPage->InvalidDataCbaResourceId();
	AssertTrueL( ETrue, KSETTINGPAGELOG3 ); 
	settingPage->MopSupplyObject( 1 );
	AssertTrueL( ETrue, KSETTINGPAGELOG3 ); 
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    settingPage->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KSETTINGPAGELOG3 ); 
	settingPage->ComponentControl( 0 );
	AssertTrueL( ETrue, KSETTINGPAGELOG3 ); 
	settingPage->CountComponentControls();
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
    settingPage->HandleResourceChange( KAknsMessageSkinChange );
    AssertTrueL( ETrue, KSETTINGPAGELOG3 ); 
	CleanupStack::Pop();
	delete settingPage;
	AssertTrueL( ETrue, KSETTINGPAGELOG3 );
	
	settingPage = new (ELeave) CBCTestBaseSettingPage(
		R_AKNATSETPAGE_TEXT_SETTING_PAGE );
	settingPage->ExecuteLD();
	
	AssertTrueL( ETrue, _L("DisplayMenuL() function invoked") );
	AssertTrueL( ETrue, _L("PostDisplayCheckL() function invoked") );
	

	}
    
void CBCTestSettingPageCase::TestAllL()
    {
    TestCheckBoxSettingPageL();
    TestPasswordSettingPageL();
    TestTextSettingPageL();
    TestSliderSettingPageL();
    TestVolumeSettingPageL();
    TestRadioButtonSettingPageL();
    TestSettingItemListL();
    TestMFneSettingPageL();
    TestSettingPageL();
    TestDescArrayL();
    }

void CBCTestSettingPageCase::TestMFneSettingPageL()
	{
	//For CAknMfneSettingPage
	CBCTestMfneSettingPage* mfneSettingPage = new (ELeave) CBCTestMfneSettingPage(
		R_BCTEST_PASSWORD_SETTING_PAGE );
	_LIT( KMFNESETTINGPAGELOG1, "CAknMfneSettingPage constructor called" );
    AssertTrueL( ETrue, KMFNESETTINGPAGELOG1 );
    CleanupStack::PushL( mfneSettingPage );
    mfneSettingPage->ConstructL();
	_LIT( KMFNESETTINGPAGELOG2, "Function called" );
    AssertTrueL( ETrue, KMFNESETTINGPAGELOG2 );
    AssertTrueL( ETrue, KMFNESETTINGPAGELOG2 );
    	
    mfneSettingPage->Mfne();
    AssertTrueL( ETrue, KMFNESETTINGPAGELOG2 );

    CleanupStack::PopAndDestroy();
    
    mfneSettingPage = new (ELeave) CBCTestMfneSettingPage(&KTitle, 1, 
    	EEikCtSecretEd, R_BCTEST_SETPAGE_PASSWORD,
    	R_BCTEST_PASSWORD_SETTING_PAGE );
	delete mfneSettingPage;
    AssertTrueL( ETrue, KMFNESETTINGPAGELOG2 );
    
    //For CBCTestDateSettingPage
    TTime time;
    time.HomeTime();
    CBCTestDateSettingPage* dateSettingPage = new (ELeave)CBCTestDateSettingPage(
    	R_AKNATSETPAGE_DATE_SETTING_PAGE, time );
	_LIT( KDATESETTINGPAGELOG1, "CBCTestDateSettingPage constructor called" );
    AssertTrueL( ETrue, KDATESETTINGPAGELOG1 );
    CleanupStack::PushL( dateSettingPage );
    dateSettingPage->ConstructL();
	_LIT( KDATESETTINGPAGELOG2, "Function called" );
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );
    dateSettingPage->DateEditor();   
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );
        	
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    dateSettingPage->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );  
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );
    dateSettingPage->UpdateSettingL();
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 ); 
    dateSettingPage->AcceptSettingL();   
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );
    dateSettingPage->RestoreOriginalSettingL();	
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );
        	
    CBufFlat* buf = CBufFlat::NewL( 200 );
    RBufWriteStream stream;
    stream.Open( *buf );
    dateSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 ); 
    stream.Close();
    delete buf;  
    
    dateSettingPage->CheckAndSetDataValidity();
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );
    dateSettingPage->CountComponentControls();
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );
    dateSettingPage->ComponentControl( 0 );
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );
    dateSettingPage->HandleControlEventL( NULL, MCoeControlObserver::EEventRequestCancel );
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );
    
    CleanupStack::PopAndDestroy( dateSettingPage );
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );
        	
    dateSettingPage = new (ELeave)CBCTestDateSettingPage(
    	&KTitle, 1, EEikCtDateEditor, R_AKNATSETPAGE_DATE, 
    	R_AKNATSETPAGE_DATE_SETTING_PAGE, time );
    AssertTrueL( ETrue, KDATESETTINGPAGELOG2 );
    delete dateSettingPage;
    	
     //For CBCTestTimeSettingPage
    time.HomeTime();
    CBCTestTimeSettingPage* timeSettingPage = new (ELeave)CBCTestTimeSettingPage(
    	R_AKNATSETPAGE_TIME_SETTING_PAGE, time );
	_LIT( KTIMESETTINGPAGELOG1, "CBCTestTimeSettingPage constructor called" );
    AssertTrueL( ETrue, KTIMESETTINGPAGELOG1 );
    CleanupStack::PushL( timeSettingPage );
    timeSettingPage->ConstructL();
	_LIT( KTIMESETTINGPAGELOG2, "Function called" );
    AssertTrueL( ETrue, KTIMESETTINGPAGELOG2 );
    timeSettingPage->TimeEditor();   
    AssertTrueL( ETrue, KTIMESETTINGPAGELOG2 );
    timeSettingPage->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KTIMESETTINGPAGELOG2 );   
    timeSettingPage->UpdateSettingL();
    AssertTrueL( ETrue, KTIMESETTINGPAGELOG2 );
    timeSettingPage->AcceptSettingL();   
    AssertTrueL( ETrue, KTIMESETTINGPAGELOG2 );
    timeSettingPage->RestoreOriginalSettingL();	
    AssertTrueL( ETrue, KTIMESETTINGPAGELOG2 );
    
    buf = CBufFlat::NewL( 200 );
    stream.Open( *buf );
    timeSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KTIMESETTINGPAGELOG2 ); 
    stream.Close();
    delete buf; 
      
    CleanupStack::PopAndDestroy( timeSettingPage );
    AssertTrueL( ETrue, KTIMESETTINGPAGELOG2 );
    timeSettingPage = new (ELeave) CBCTestTimeSettingPage( &KTitle, 
                                1, 
                                EEikCtTimeEditor,
                                R_AKNATSETPAGE_TIME_EDITOR, 
                                R_AKNATSETPAGE_TIME_SETTING_PAGE,    
                                time );	
    AssertTrueL( ETrue, KTIMESETTINGPAGELOG2 );
    CleanupStack::PushL( timeSettingPage );
    timeSettingPage->ConstructL();
    CleanupStack::Pop( timeSettingPage );
    timeSettingPage->ExecuteLD();
    AssertTrueL( ETrue, KTIMESETTINGPAGELOG2 );
    
    //For duration setting page
    TTimeIntervalSeconds tempsecond( 60 );
    CBCTestDurationSettingPage* durationSettingPage = new (ELeave)
    	CBCTestDurationSettingPage( R_AKNATSETPAGE_DURATION_SETTING_PAGE, tempsecond );
	_LIT( KDURATIONSETTINGPAGELOG1, "Duration settingPage constructor called" );
    AssertTrueL( ETrue, KDURATIONSETTINGPAGELOG1 );
    CleanupStack::PushL( durationSettingPage );
    durationSettingPage->ConstructL();
    _LIT( KDURATIONSETTINGPAGELOG2, "Function called" );
    AssertTrueL( ETrue, KDURATIONSETTINGPAGELOG2 );
           
    durationSettingPage->DurationEditor();
    AssertTrueL( ETrue, KDURATIONSETTINGPAGELOG2 );
    durationSettingPage->UpdateSettingL();
    AssertTrueL( ETrue, KDURATIONSETTINGPAGELOG2 );
    durationSettingPage->AcceptSettingL();
    AssertTrueL( ETrue, KDURATIONSETTINGPAGELOG2 );
    durationSettingPage->RestoreOriginalSettingL();
    AssertTrueL( ETrue, KDURATIONSETTINGPAGELOG2 );
    
    buf = CBufFlat::NewL( 200 );
    stream.Open( *buf );
    durationSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KDURATIONSETTINGPAGELOG2 ); 
    stream.Close();
    delete buf; 

    CleanupStack::PopAndDestroy();
    durationSettingPage = new (ELeave) CBCTestDurationSettingPage( &KTitle, 
                                1, 
                                EEikCtDurationEditor,
                                R_AKNATSETPAGE_DURATION_EDITOR, 
                                R_AKNATSETPAGE_DURATION_SETTING_PAGE,    
                                tempsecond );
    AssertTrueL( ETrue, KDURATIONSETTINGPAGELOG2 );
    delete durationSettingPage;
    
    
    //For Time offset settingpage
    tempsecond = 10;
    CBCTestTimeOffsetSettingPage* timeoffsetSettingPage = new (ELeave) 
    	CBCTestTimeOffsetSettingPage( R_AKNATSETPAGE_TIME_SETTING_PAGE, tempsecond );
	_LIT( KTIMEOFFSETSETTINGPAGELOG1, "TimeOffset settingPage constructor called" );
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGPAGELOG1 );
    CleanupStack::PushL( timeoffsetSettingPage );
	_LIT( KTIMEOFFSETSETTINGPAGELOG2, "Function called" );
//  timeoffsetSettingPage->BaseConstructL();
//    AssertTrueL( ETrue, _L( "TimeOffset settingPage ConstructL called" ) );
    timeoffsetSettingPage->TimeOffsetEditor();
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGPAGELOG2 );
//  IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
//  timeoffsetSettingPage->UpdateSettingL();
//  AssertTrueL( ETrue, _L( "TimeOffset settingPage UpdateSettingL called" ) );
//  timeoffsetSettingPage->AcceptSettingL();
//  AssertTrueL( ETrue, _L( "TimeOffset settingPage AcceptSettingL called" ) );
    timeoffsetSettingPage->RestoreOriginalSettingL();
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGPAGELOG2 );
  
//  IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;
    
    CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGPAGELOG2 );
    timeoffsetSettingPage = new (ELeave)CBCTestTimeOffsetSettingPage(
								&KTitle, 
                                1, 
                                EEikCtDurationEditor,
                                R_AKNATSETPAGE_DURATION_EDITOR, 
                                R_AKNATSETPAGE_DURATION_SETTING_PAGE,    
                                tempsecond );
    AssertTrueL( ETrue, KTIMEOFFSETSETTINGPAGELOG2 );
    delete timeoffsetSettingPage;
    
    //For IPField settingpage
    TInetAddr ipAddr(10);
    CBCTestIpFieldSettingPage* ipFieldSettingPage = new (ELeave) CBCTestIpFieldSettingPage(
    	R_AKNATSETPAGE_IPADDRESS_SETTING_PAGE, ipAddr );
	_LIT( KIPFIELDSETTINGPAGELOG1, "IPField settingpage constructor called" );
    AssertTrueL( ETrue, KIPFIELDSETTINGPAGELOG1 );
    _LIT( KIPFIELDSETTINGPAGELOG2, "Function called" );
    CleanupStack::PushL( ipFieldSettingPage );
    ipFieldSettingPage->ConstructL();
    AssertTrueL( ETrue, KIPFIELDSETTINGPAGELOG2 );
    ipFieldSettingPage->IpFieldEditor();
    AssertTrueL( ETrue, KIPFIELDSETTINGPAGELOG2 );
    
    ipFieldSettingPage->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KIPFIELDSETTINGPAGELOG2 ); 
        
    ipFieldSettingPage->UpdateSettingL();
    AssertTrueL( ETrue, KIPFIELDSETTINGPAGELOG2 );
    ipFieldSettingPage->AcceptSettingL();
    AssertTrueL( ETrue, KIPFIELDSETTINGPAGELOG2 );
    ipFieldSettingPage->RestoreOriginalSettingL();
    AssertTrueL( ETrue, KIPFIELDSETTINGPAGELOG2 );

    buf = CBufFlat::NewL( 200 );
    stream.Open( *buf );
    ipFieldSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KIPFIELDSETTINGPAGELOG2 ); 
    stream.Close();
    delete buf; 
	CleanupStack::PopAndDestroy();
	AssertTrueL( ETrue, KIPFIELDSETTINGPAGELOG2 );
	ipFieldSettingPage = new (ELeave) CBCTestIpFieldSettingPage( 
								&KTitle, 
                                1, 
                                EAknCtIpFieldEditor,
                                R_AKNATSETPAGE_IPADDRESS_EDITOR, 
                                R_AKNATSETPAGE_IPADDRESS_SETTING_PAGE,    
                                ipAddr );
    AssertTrueL( ETrue, KIPFIELDSETTINGPAGELOG2 );
    delete ipFieldSettingPage;
 
	}
	
void CBCTestSettingPageCase::TestDescArrayL()
	{
	TBuf<10> title;
	_LIT( KDESCARRAYLOG1, "test" );
	title.Append( KDESCARRAYLOG1 );
	TAknDesCArrayDecorator descArray;
	CBCTestSettingItemArray* itemArray = new (ELeave) CBCTestSettingItemArray(
    	1, EFalse, 0 );
	_LIT( KDESCARRAYLOG2, "Function called" );
	AssertTrueL( ETrue, KDESCARRAYLOG2 );
	descArray.SetArray( itemArray );
	AssertTrueL( ETrue, KDESCARRAYLOG2 );
	descArray.MdcaCount();
	AssertTrueL( ETrue, KDESCARRAYLOG2 );
	descArray.SetActive( ETrue );
	AssertTrueL( ETrue, KDESCARRAYLOG2 );
	descArray.SetDecorationText( title );
	AssertTrueL( ETrue, KDESCARRAYLOG2 );
	TInt index = 0;
	descArray.DecoratedIndex( index );
	AssertTrueL( ETrue, KDESCARRAYLOG2 );
	descArray.MdcaPoint( itemArray->MdcaCount() );
	AssertTrueL( ETrue, KDESCARRAYLOG2 );
	
	delete itemArray;

	}


    


