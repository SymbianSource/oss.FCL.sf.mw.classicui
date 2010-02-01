/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/


#include "EIKCDLIB.H"
#include <eikinfo.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <eikenv.h>
#else
#include <eikenv.h>
#include <uikon/eikenvinterface.h>
#endif
#include <eikalert.h>
#include <eikhfdlg.h>
#include "EIKCDFTY.H"
//#include <eikbprev.h>
//#include <eikchmap.h>
#include <eikpanic.h>

// Static DLL functions
GLDEF_C void Panic(TEikPanic aPanic)
    {
    _LIT(KPanicCat,"EIKCDLG");
    User::Panic(KPanicCat,aPanic);
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// CEikCDlgLibrary
//
///////////////////////////////////////////////////////////////////////////////////////
CEikCDlgLibrary::CEikCDlgLibrary()
    {
    }


///////////////////////////////////////////////////////////////////////////////////////
//
// InitializeL
//
///////////////////////////////////////////////////////////////////////////////////////
EXPORT_C void CEikCDlgLibrary::InitializeL()
    {
    CEikonEnv* eikEnv = CEikonEnv::Static();
    // Inform the EikEnv of this library's presence
    // to allow creation of Info and query dialogs
    eikEnv->SetRequestQueryDialogFunc(RequestQueryDialogL);
    eikEnv->SetRequestInfoDialogFunc(RequestInfoDialogL);
    // Create the Alert win - owned by EikEnv
    CEikAlertNotifier* aAlertWin = new(ELeave) CEikAlertNotifier;
    eikEnv->SetAlertWin(aAlertWin);
    // Create the Debug keys - owned by Cone
    CEikDebugKeys* aDebugKeys=new(ELeave) CEikDebugKeys;
    eikEnv->SetDebugKeys(aDebugKeys);
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// ResourceFile
//
///////////////////////////////////////////////////////////////////////////////////////
EXPORT_C TFileName CEikCDlgLibrary::ResourceFile()
    {
    _LIT(KResFileName,"z:\\resource\\eikcdlg.rsc");
    return KResFileName();
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// ControlFactory
//
///////////////////////////////////////////////////////////////////////////////////////
EXPORT_C TCreateByTypeFunction  CEikCDlgLibrary::ControlFactory()
    {
    return CreateByTypeL;
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// RequestQueryDialogL
//
///////////////////////////////////////////////////////////////////////////////////////
EXPORT_C void CEikCDlgLibrary::RequestQueryDialogL()
    {
    CEikInfoDialog *queryDialog= new(ELeave) CEikInfoDialog(CEikInfoDialog::EIgnoreEnter);
    CEikonEnv::Static()->SetQueryDialog(queryDialog);
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// RequestInfoDialogL
//
///////////////////////////////////////////////////////////////////////////////////////
EXPORT_C void CEikCDlgLibrary::RequestInfoDialogL()
    {
    CEikInfoDialog *infoDialog= new(ELeave) CEikInfoDialog();
    CEikonEnv::Static()->SetInfoDialog(infoDialog);
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// CreateByTypeL
//
///////////////////////////////////////////////////////////////////////////////////////
SEikControlInfo CEikCDlgLibrary::CreateByTypeL(TInt /*aControlType*/)
    {
    SEikControlInfo controlInfo;
    controlInfo.iControl = NULL;
    controlInfo.iTrailerTextId = 0;
    controlInfo.iFlags = 0;
    return controlInfo;
    }

///////////////////////////////////////////////////////////////////////////////////////
// END OF FILE
///////////////////////////////////////////////////////////////////////////////////////
