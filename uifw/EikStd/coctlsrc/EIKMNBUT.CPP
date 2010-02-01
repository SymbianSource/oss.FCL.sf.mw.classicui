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


#include <eikmnbut.h>
#include <eikmenup.h>
#include <barsread.h>
#include <coeaui.h>
#include <eikenv.h>
#include <eikappui.h>
#include "lafmnbut.h"				    

#include <AknTasHook.h> // for testability hooks
EXPORT_C CEikMenuButton::CEikMenuButton()
    {
	if (LafMenuButton::IsReportingOnButtonDown())
		SetReportOnPointerDown();
	AKNTASHOOK_ADD( this, "CEikMenuButton" );
    }

EXPORT_C CEikMenuButton::~CEikMenuButton()
    {
    AKNTASHOOK_REMOVE();
	if (iMenuPopup)
		{
		iEikonEnv->EikAppUi()->RemoveFromStack(iMenuPopup);
		delete iMenuPopup;
		}
	}

EXPORT_C void CEikMenuButton::SetMenuPaneId(TInt aMenuPaneId)
    {								   
	iMenuPaneId=aMenuPaneId;
    }

EXPORT_C void CEikMenuButton::ConstructFromResourceL(TResourceReader& aReader)
	{
	iMenuPaneId=aReader.ReadInt32();
	CEikCommandButton::ConstructFromResourceL(aReader);
	}

EXPORT_C void CEikMenuButton::Animate()
	{
	iButFlags|=0x10; // same as KButtonPressedMask - avoid magic number !!!
	StateChanged();
	DrawNow();
	iCoeEnv->WsSession().Flush();
	}

EXPORT_C void CEikMenuButton::ProcessCommandL(TInt aCommandId)
	{
	if (iMenuPopup)
	    ClosePopupMenu();
	iMenuObserver->ProcessCommandL(aCommandId);
	}

EXPORT_C void CEikMenuButton::LaunchPopupMenuL(MEikMenuObserver* aObserver)
    {
	iMenuObserver=aObserver;
    iMenuPopup=new(ELeave) CEikMenuPane(this);
	TRAPD(err,DoLaunchPopupMenuL());
	if (err)
		{
		ClosePopupMenu();
		User::Leave(err);
		}
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikMenuButton::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikMenuButton::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KLitEikMenuButCtlStart, "<CEikMenuButton>");
	_LIT(KLitEikMenuButCtlEnd, "<\\CEikMenuButton>");
	_LIT(KLitEikMenuButPnId,"<iMenuPaneId>");
	_LIT(KLitEikMenuButPnIdEnd,"<\\iMenuPaneId>");
	
	aWriteStream << KLitEikMenuButCtlStart;
	aWriteStream << KLitEikMenuButPnId;
	aWriteStream.WriteInt32L(iMenuPaneId);
	aWriteStream << KLitEikMenuButPnIdEnd;
	CEikCommandButton::WriteInternalStateL(aWriteStream);
	aWriteStream << KLitEikMenuButCtlEnd;
	}
#endif

void CEikMenuButton::DoLaunchPopupMenuL()
	{
	iMenuPopup->ConstructL(NULL);
	iMenuObserver->RestoreMenuL(iMenuPopup,iMenuPaneId,MEikMenuObserver::EMenuPane);
	iMenuPopup->SetPointerCapture(ETrue);
	iEikonEnv->EikAppUi()->AddToStackL(iMenuPopup,ECoeStackPriorityDialog);
	TPoint pos(0,0);
	TRect screenRect(PositionRelativeToScreen(),Size());
	LafMenuButton::GetMenuPosition(pos, screenRect, iMenuPopup->CalculateSizeAndPosition().Size(), iEikonEnv->ScreenDevice()->SizeInPixels());
	iMenuPopup->StartDisplayingMenuPane(NULL,pos,NULL,0/*,EPopupTargetTopRight*/);
	if (iCoeEnv->LastEvent().Type()==EEventPointer)
		{
		SetIgnoreNextPointerUp();
		iMenuPopup->ClaimPointerGrab();
		}
	iMenuPopup->SetLaunchingButton(this);
	}

EXPORT_C void CEikMenuButton::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikCommandButton::HandlePointerEventL(aPointerEvent); 
    }	

EXPORT_C void* CEikMenuButton::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

void CEikMenuButton::ClosePopupMenu()
	{
	if (!iMenuPopup)
		return;
	iEikonEnv->EikAppUi()->RemoveFromStack(iMenuPopup);
	delete iMenuPopup;
	iMenuPopup=NULL;
	}

EXPORT_C void CEikMenuButton::SetEmphasis(CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/)
	{ // !! what should go here
	}

