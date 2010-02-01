// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

 
#include "altappui.h" 
#include "altmodel.h"
#include "altview.h"
#include "applaunchtest.hrh"

CAltAppUi::CAltAppUi()
	{
	}

void CAltAppUi::ConstructL()
	{
	BaseConstructL();
	iModel=CAppLauncherModel::NewL();
	TRect rect=ClientRect();
	iView=CAltView::NewL(rect,iModel);
	RegisterViewAndAddStackL(*iView);
	AddToViewStackL(*iView,iView);
	iView->MakeVisible(ETrue);
	SetDefaultViewL(*iView);
	}

CAltAppUi::~CAltAppUi()
	{
	if(iView != NULL)
		{
		RemoveFromViewStack(*iView,iView);
		DeregisterViewAndRemoveStack(*iView);
		delete iView;
		}
	delete iModel;
	}

void CAltAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
	case EAltCmdWriteInternalState:
			{
			iEikonEnv->WriteInternalStateOfStackedControlsL();
			}
			break;
		// Handle requests to exit the application
	case EEikCmdExit:
			{
			Exit();
			}
		break;
	default:
		break;
		}
	}
