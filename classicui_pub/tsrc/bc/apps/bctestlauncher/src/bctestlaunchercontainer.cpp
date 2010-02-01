/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implementation of application container class.
*
*/









#include <coemain.h>
#include <barsread.h>
#include <aknappui.h>
#include <eikprogi.h>
#include <aknenv.h>
#include <avkon.hrh>
#include <akntitle.h>
#include <aknquerydialog.h>
#include <bctestlauncher.rsg>
#include <stringloader.h> // StringLoader
#include <f32file.h>  // link against efsrv.lib
#include <s32file.h>
#include <eikenv.h>
#include <aknnotewrappers.h>

#include "bctestlauncherdefs.h"
#include "bctestlaunchercontainer.h"

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CBCTestLauncherContainer::CBCTestLauncherContainer()
// C++ default constructor can NOT contain any code, that
// might leave.
// ---------------------------------------------------------------------------
//
CBCTestLauncherContainer::CBCTestLauncherContainer()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherContainer::ConstructL
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CBCTestLauncherContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();

    Window().SetShadowDisabled( EFalse );

    CEikStatusPane *sp = 
        ( ( CAknAppUi* )iEikonEnv->EikAppUi() )->StatusPane();
    iTitlePane = ( CAknTitlePane * )sp->ControlL( 
        TUid::Uid( EEikStatusPaneUidTitle ) );
   	iCba = CEikButtonGroupContainer::Current();

    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherContainer::~CBCTestLauncherContainer
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestLauncherContainer::~CBCTestLauncherContainer()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherContainer::CountComponentControls() const
// amount of component controls
// ---------------------------------------------------------------------------
//
TInt CBCTestLauncherContainer::CountComponentControls() const
    {
    return 0; // return nbr of controls inside this container
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherContainer::ComponentControl( TInt aIndex ) const
// Returns ptr to component controls
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestLauncherContainer::ComponentControl( 
    TInt /*aIndex*/ ) const
    {
    return NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherContainer::Draw( const TRect& aRect ) const
// Draw function
// ---------------------------------------------------------------------------
//
void CBCTestLauncherContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbWhite );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    gc.Clear();
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherContainer::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------------------------
//
void CBCTestLauncherContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/ )
    {
    }
// ---------------------------------------------------------------------------
// CBCTestLauncherContainer::ClearScreen()
// Clears the screen.
// ---------------------------------------------------------------------------
//    
void CBCTestLauncherContainer::ClearScreen()
	{
	CEikStatusPaneBase* sp = 
	    ( ( CAknAppUi* )iEikonEnv->EikAppUi() )->StatusPane();
	sp->MakeVisible( EFalse );
	iCba->MakeVisible( EFalse );
	DrawNow();
	}
	
// ---------------------------------------------------------------------------
// CBCTestLauncherContainer::RestoreScreen()
// Makes status pane and cba labels visible which ClearScreen() hides.
// ---------------------------------------------------------------------------
//	
void CBCTestLauncherContainer::RestoreScreen()
	{
	CEikStatusPaneBase *sp = 
	    ( ( CAknAppUi* )iEikonEnv->EikAppUi() )->StatusPane();
	sp->MakeVisible( ETrue );
	iCba->MakeVisible( ETrue );
	DrawNow();
	}

// -----------------------------------------------------------------------------
// CBCTestLauncherContainer::SetSdkVersion
// Set the SDK version.
// -----------------------------------------------------------------------------
//	
 void CBCTestLauncherContainer::SetSdkVersion()
	{
	TBuf<8> sdkVer;
	CAknTextQueryDialog* verQuery = CAknTextQueryDialog::NewL( sdkVer );
	CleanupStack::PushL(verQuery);
	verQuery->SetMaxLength( 2 );
	//EAknEditorSecretAlphaInputMode EAknEditorNumericInputMode
	verQuery->SetDefaultInputMode( EAknEditorNumericInputMode );
	HBufC* prompt;
	// Pushes prompt onto the Cleanup Stack.
	prompt = StringLoader::LoadLC(R_BCTESTLAUNCHER_QUERY_CAPTION);	
	verQuery->SetPromptL(*prompt);
	CleanupStack::PopAndDestroy(prompt);
	CleanupStack::Pop(verQuery);
	if (verQuery->ExecuteLD(R_AVKON_DIALOG_QUERY_VALUE_NUMBER))
		{
		// write sdk version into file
	    RFs fs;
	    User::LeaveIfError( fs.Connect() );
	    CleanupClosePushL( fs );
		RFileWriteStream writeStream;
        writeStream.Replace( fs, KSdkVerFile, EFileWrite );
	    CleanupClosePushL( writeStream );
	    //writeStream.WriteL( sdkVer );
	    TInt verNum;
	    TLex lex(sdkVer);
	    lex.Val(verNum);
	    
	    TBuf<120> buf;
	    if ( verNum<MinVersionValue || verNum >MaxVersionValue )
	    {
	    verNum = 0;
	    CAknInformationNote* tInfoNote = new( ELeave ) CAknInformationNote();
        buf.Format( _L( "The value should between %d and %d" ), 
            MinVersionValue, MaxVersionValue );
        tInfoNote->ExecuteLD( buf );	
	    }
	    
	    writeStream.WriteInt32L(verNum);
	    writeStream.CommitL ();
	    CleanupStack::PopAndDestroy( 2 );
	    fs.Close();     	

		}
	}
		
