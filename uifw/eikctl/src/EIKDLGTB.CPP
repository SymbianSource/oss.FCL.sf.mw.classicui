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


#include <barsread.h>
#include <coemain.h>
#include <coeccntx.h>
#include "eikdlgtb.h"
#include <eikcmobs.h>
#include <eikfctry.h>
#include <eikpanic.h>
#include <gulcolor.h>
#include <eikenv.h>

EXPORT_C CEikDialogToolBar::~CEikDialogToolBar()
	{
	delete iBrushAndPenContext;
	}	

EXPORT_C CEikDialogToolBar::CEikDialogToolBar()
	{
	__DECLARE_NAME(_S("CEikDialogToolBar"));
	}

EXPORT_C void CEikDialogToolBar::BaseConstructL()
	{
	__ASSERT_DEBUG(Observer(),Panic(EEikPanicDialogToolBarNoObserver));
	CEikControlGroup::ConstructL(CEikControlGroup::EFromTopLeft,CEikControlGroup::ELayHorizontally);
	RWindow& window=Window();
	window.SetBackgroundColor(iEikonEnv->ControlColor(EColorDialogBackground,*this));
	window.SetPointerGrab(ETrue);
	window.SetShadowDisabled(ETrue);
	EnableDragEvents();
	iBrushAndPenContext=CCoeBrushAndPenContext::NewL();
	iBrushAndPenContext->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iBrushAndPenContext->SetBrushColor(iEikonEnv->ControlColor(EColorDialogBackground,*this));
	iBrushAndPenContext->SetPenColor(iEikonEnv->ControlColor(EColorDialogText,*this));
	SetControlContext(iBrushAndPenContext);
	}

EXPORT_C void CEikDialogToolBar::ConstructFromResourceL(TResourceReader& aReader)
	{
	BaseConstructL();
	const TInt width=aReader.ReadInt16();
	if (width)
		SetLengthInPixels(width);
	const TInt count=aReader.ReadInt16();
	for (TInt ii=0;ii<count;++ii)
		{
		const TInt ctrlType=aReader.ReadInt16();
		CCoeControl* ctrl=EikControlFactory::CreateByTypeL(ctrlType).iControl;
//		if (!ctrl)
//			ctrl=iCommandObserver->CreateCustomCommandControlL(ctrlType);
		__ASSERT_DEBUG(ctrl, Panic(EEikPanicToolBarNullControl));
		ctrl->SetContainerWindowL(*this);
		ctrl->SetNonFocusing();
		CleanupStack::PushL(ctrl);
		const TInt id=aReader.ReadInt16();
		const TInt length=aReader.ReadInt16();
		TEikGroupControl groupCtrl(ctrl,id,aReader.ReadInt16(),length);
		AddControlL(groupCtrl); //ownership now taken by array
		CleanupStack::Pop();
		ctrl->ConstructFromResourceL(aReader);
		}
	}

EXPORT_C TKeyResponse CEikDialogToolBar::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	const TInt count=iControlArray->Count();
	for (TInt ii=0;ii<count;ii++)
		{
		if ((*iControlArray)[ii].iControl->OfferKeyEventL(aKeyEvent,aType)==EKeyWasConsumed)
			return EKeyWasConsumed;
		}
	return EKeyWasNotConsumed;
	}

EXPORT_C void CEikDialogToolBar::AddControlL(TEikGroupControl& aGroupControl)
	{
	CEikControlGroup::AddControlL(aGroupControl);
	aGroupControl.iControl->SetObserver(this);
	}

void CEikDialogToolBar::HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)
	{
	if (aEventType==MCoeControlObserver::EEventStateChanged)
		{
		iStateChangeControl=aControl;
		ReportEventL(aEventType);
		}
	}

EXPORT_C CCoeControl* CEikDialogToolBar::StateChangeControl() const
	{
	return iStateChangeControl;
	}

EXPORT_C TInt CEikDialogToolBar::StateChangeControlId() const
	{
	if (!iStateChangeControl)
		return KErrNotFound;
	return ControlId(iStateChangeControl);
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikDialogToolBar::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
	{
	CEikControlGroup::GetColorUseListL(aColorUseList);

	TInt commonAttributes = TCoeColorUse::ESurrounds|TCoeColorUse::EActive|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorToolbarText);
	colorUse.SetUse(TCoeColorUse::EFore|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorToolbarBackground);
	colorUse.SetUse(TCoeColorUse::EBack|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikDialogToolBar::HandleResourceChange(TInt aType)
	{
	CEikControlGroup::HandleResourceChange(aType);

	if(aType==KEikColorResourceChange)
		{
		iBrushAndPenContext->SetBrushColor(iEikonEnv->ControlColor(EColorToolbarBackground,*this));
		iBrushAndPenContext->SetPenColor(iEikonEnv->ControlColor(EColorToolbarText,*this));
		Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorToolbarBackground,*this));
		}
	}
