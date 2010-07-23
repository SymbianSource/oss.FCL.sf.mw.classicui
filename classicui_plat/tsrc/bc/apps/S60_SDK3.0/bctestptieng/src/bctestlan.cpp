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
#include <eikenv.h>
#include <ptilanguage.h>
#include <ptidefs.h>

#include "BCTestLan.h"
#include "BCTestPtiEngcontainer.h"
#include "BCTestPtiEng.hrh"
#include "bctestqwertymap.h"
#include "bctestkeymap.h"
#include "streamlogger.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestLanguage* CBCTestLanguage::NewL()
    {
    CBCTestLanguage* self = new( ELeave ) CBCTestLanguage();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestLanguage::CBCTestLanguage():iLan(NULL)
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestLanguage::~CBCTestLanguage()
    {
    Teardown();
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestLanguage::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestLanguage::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestLanguage::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, 
        REP(Down, 1),
        KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestLanguage::RunL
// ---------------------------------------------------------------------------
//
void CBCTestLanguage::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdPtiLanguage)
        {
        return;
        }
    
    TestFunctionL();
    }

// ---------------------------------------------------------------------------
// CBCTestLanguage::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestLanguage::TestFunctionL()
    {
    SetupL();
    TestL12nL();
    TestSetKeyMap();
	TestOthers();
    }
    

void CBCTestLanguage::SetupL()
    {
    iLan = CPtiCoreLanguage::NewL();
    AssertNotNullL(iLan, _L("created by NewL"));
    }

void CBCTestLanguage::Teardown()
    {
    delete iLan;
	iLan = NULL;
    }

void CBCTestLanguage::TestSetKeyMap()
    {
    iLan->SetKeyMappings(CBCTestKeymap::CreateKeyMapL());
    iLan->SetQwertyKeyMappings(CBCTestQwertyMap::CreateKeyMapL());
    AssertNotNullL(iLan->GetKeymappings(), _L("Key mapping set and got."));
    AssertNotNullL(iLan->GetQwertyKeymappings(), _L("Qwerty key mapping set and got."));

    //clear them all
    iLan->ClearMultitapping();
    iLan->ClearQwerty();
    AssertTrueL(NULL == iLan->GetKeymappings(), _L("Key mapping cleared."));
    AssertTrueL(NULL == iLan->GetQwertyKeymappings(), _L("Qwerty key mapping cleared."));
    }

void CBCTestLanguage::TestL12nL()
    {
    //short name
    _LIT(KShortL12nName, "en");
    iLan->SetLocalizedName(KShortL12nName);
    AssertTrueL(iLan->LocalizedNameDes() == KShortL12nName, _L("short i12n name en set and got"));

    //long name
    _LIT(KLongL12nName, "English, use in both western Eroup and north America");
    iLan->SetLocalizedName(KLongL12nName);
    TBuf<KMaxLanguageNameLength> cutName;
    const TDesC& ref = KLongL12nName;
    cutName.Copy(ref.Left(KMaxLanguageNameLength));
    AssertTrueL(iLan->LocalizedNameDes() == cutName, _L("long i12n name set and cut"));

    //lan code
    TInt oldCode = iLan->LanguageCode();
    iLan->SetLanguageCode(31);      // chinese
    iLan->SetLanguageCode(31);      // set same code again
    AssertIntL(iLan->LanguageCode(), 31, _L("set lan code to 31"));
    iLan->SetLanguageCode(1);       // set another code
    AssertIntL(iLan->LanguageCode(), 1, _L("set lan code to 1"));
    iLan->SetLanguageCode(oldCode); // reset
    }

void CBCTestLanguage::TestOthers()
	{
	RArray<TInt> inputModes;
    iLan->GetAvailableInputModesL(inputModes);
    AssertTrueL(ETrue, _L("available input modes are got into RArray"));
    inputModes.Close();

	CArrayFixFlat<TInt>* modes = new (ELeave) CArrayFixFlat<TInt>(10);
    CleanupStack::PushL(modes);
    iLan->GetAvailableInputModesL(modes);
    AssertTrueL(ETrue, _L("available input modes are got into CArrayFix"));
    CleanupStack::PopAndDestroy(); // modes

	iLan->RemoveCore(NULL);
	AssertTrueL(ETrue, _L("NULL core removed"));
	}
//end of file
