/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#include <w32std.h>
#include <coecntrl.h>
#include <CAknMemorySelectionSettingItemMultiDrive.h>
#include <caknmemoryselectiondialogmultidrive.h>

#include "BCTestMultiDrivercase.h"
#include "BCTestMultiDrivercontainer.h"
#include "BCTestMultiDriver.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CMultiDriverCase* CMultiDriverCase::NewL( 
    CMultiDriverContainer* aContainer )
    {
    CMultiDriverCase* self = new( ELeave ) CMultiDriverCase( 
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
CMultiDriverCase::CMultiDriverCase( 
    CMultiDriverContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CMultiDriverCase::~CMultiDriverCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CMultiDriverCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CMultiDriverCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CMultiDriverCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, LeftCBA, TEND );  
    AddTestL( LeftCBA, Down, LeftCBA, TEND );  
    }
    
// ---------------------------------------------------------------------------
// CMultiDriverCase::RunL
// ---------------------------------------------------------------------------
//
void CMultiDriverCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }

    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestFunctionL();
            break;
        case EBCTestCmdOutline2:
            TestFunction2L();
            break;    
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CMultiDriverCase::TestFunctionL
// ---------------------------------------------------------------------------
//    
void CMultiDriverCase::TestFunctionL()
    {
    // Test some API here
    _LIT( MultiDrive, "CAknMemorySelectionSettingItemMultiDrive" );
    _LIT( MultiDrive1, "CompleteConstructionL" );
	_LIT( MultiDrive3, "StoreL" );
	_LIT( MultiDrive4, "SettingTextL" );
	_LIT( MultiDrive5, "LoadL" );
	_LIT( MultiDriveRlease, "MultiDriveRlease" );
	
    TInt aId = 1;
    TDriveNumber aSelDr = EDriveC;
    
    CAknMemorySelectionSettingItemMultiDrive *MemSelSetMulDriver = 
        new ( ELeave ) CAknMemorySelectionSettingItemMultiDrive( aId, aSelDr ); 
    		   
    AssertNotNullL( MemSelSetMulDriver, MultiDrive );
    
    MemSelSetMulDriver->CompleteConstructionL();
    AssertTrueL( ETrue, MultiDrive1 );
   
    CleanupStack::PushL( MemSelSetMulDriver ); 
    
    MemSelSetMulDriver->SettingTextL();
    AssertTrueL( ETrue, MultiDrive4 );    
     MemSelSetMulDriver->LoadL(); 
     AssertTrueL( ETrue, MultiDrive5 );           
         
     MemSelSetMulDriver->StoreL();    
     AssertTrueL( ETrue, MultiDrive3 );
     
     
     CleanupStack::PopAndDestroy( MemSelSetMulDriver );
     AssertTrueL( ETrue, MultiDriveRlease );
    }
    
void CMultiDriverCase::TestFunction2L()
    {
    // Test some API here
    _LIT( MultiDrive5, "CAknMemorySelectionDialogMultiDrive::NewL()1" );
	_LIT( MultiDrive6, "CAknMemorySelectionDialogMultiDrive::NewL()2" );
	_LIT( MultiDrive7, "SetTitleL" );
	_LIT( MultiDrive8, "SetLeftSoftkeyL" );
    _LIT( MultiDrive9, "SetRightSoftkeyL" );
    _LIT( MultiDrive10, "GetItem" );
	_LIT( MultiDrive11, "ExecuteL1" );
	_LIT( MultiDrive12, "ExecuteL2" );
	_LIT( MultiDrive13, "RunDlgLD1" );
    _LIT( MultiDrive14, "RunDlgLD2" );
	_LIT( MultiDrive15, "RunDlgLD3" );
	_LIT( MultiDrive16, "AddDrivePathsL" );
	_LIT( MultiDrive17, "FindIndexByDrive" );

    TInt includedMedias = 5; 
    TDriveNumber aSelDr = EDriveC;
    TCommonDialogType aDialogDr = ECFDDialogTypeNormal;    
     
    CAknMemorySelectionDialogMultiDrive *MemSelDialogMulDriver =
        CAknMemorySelectionDialogMultiDrive::NewL( aDialogDr, EFalse );
    AssertNotNullL( MemSelDialogMulDriver, MultiDrive5 );
    CleanupStack::PushL( MemSelDialogMulDriver );           

    CleanupStack::PopAndDestroy( MemSelDialogMulDriver );
    
    MemSelDialogMulDriver = CAknMemorySelectionDialogMultiDrive::NewL( 
        aDialogDr, 0, EFalse, includedMedias );
    AssertNotNullL( MemSelDialogMulDriver, MultiDrive6 );
    CleanupStack::PushL( MemSelDialogMulDriver );           
   
    _LIT( tTxt, "MulDriver title" );
    TBuf<16> aDefaultFolder( _L("c:\\") );
    TBuf<16> aRootPath( _L("d:\\") );
    TBuf<16> rText;
    
    MemSelDialogMulDriver->SetTitleL( tTxt );
    AssertTrueL( ETrue, MultiDrive7 );
    
    MemSelDialogMulDriver->SetLeftSoftkeyL( tTxt );
    AssertTrueL( ETrue, MultiDrive8 );
    
    MemSelDialogMulDriver->SetRightSoftkeyL( tTxt );
    AssertTrueL( ETrue, MultiDrive9 );
    
    MemSelDialogMulDriver->GetItem( 1, rText );
    AssertTrueL( ETrue, MultiDrive10 );
    
    MemSelDialogMulDriver->ExecuteL( aSelDr );
    AssertTrueL( ETrue, MultiDrive11);
    
    MemSelDialogMulDriver->ExecuteL( aSelDr, &rText, &aDefaultFolder );
    AssertTrueL( ETrue, MultiDrive12 );
        
    MemSelDialogMulDriver->RunDlgLD( aSelDr );
    AssertTrueL( ETrue, MultiDrive13 );
    
    MemSelDialogMulDriver->RunDlgLD( aSelDr, aDefaultFolder );
    AssertTrueL( ETrue, MultiDrive14 );
    
    MemSelDialogMulDriver->RunDlgLD( aSelDr, 0 );
    AssertTrueL( ETrue, MultiDrive15 );
    
    MemSelDialogMulDriver->AddDrivePathsL( aRootPath, aDefaultFolder );
    AssertTrueL( ETrue, MultiDrive16 );
    
    MemSelDialogMulDriver->FindIndexByDrive( aSelDr );
    AssertTrueL( ETrue, MultiDrive17 );
        
    CleanupStack::PopAndDestroy( MemSelDialogMulDriver );  
    }
    