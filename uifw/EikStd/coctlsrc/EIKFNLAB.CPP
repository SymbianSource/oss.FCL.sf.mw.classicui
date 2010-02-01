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


#include <apparc.h>
#include <barsread.h>
#include <eikfnlab.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikdoc.h>
#include <eikapp.h>
#include <eiklabel.h>
#include <eikfutil.h>
#include "LAFFNLAB.H"

const TInt KLabelMargins=2;

EXPORT_C CEikFileNameLabel::CEikFileNameLabel()
	{
	LafFileNameLabel::GetDefaultBorder(iBorder);
	SetNonFocusing();
	}

EXPORT_C CEikFileNameLabel::~CEikFileNameLabel()
	{
	delete iLabel;
	}

EXPORT_C void CEikFileNameLabel::ConstructL()
	{
	iLabel=new(ELeave) CEikLabel;
	iLabel->iAlignment.SetHAlignment(EHCenter);
	iLabel->iAlignment.SetVAlignment(EVCenter);
	iLabel->iMargin.iLeft=iLabel->iMargin.iRight=iLabel->iMargin.iTop=iLabel->iMargin.iBottom=KLabelMargins;
	iLabel->SetFont(iEikonEnv->LegendFont());
	iLabel->SetTextL(TPtrC());
	}

EXPORT_C void CEikFileNameLabel::ConstructFromResourceL(TResourceReader& /*aReader*/)
	{
	ConstructL();
	}

EXPORT_C void CEikFileNameLabel::UpdateL()
	{
	TFileName fileName=iEikonEnv->EikAppUi()->Document()->Process()->MainDocFileName();
	if (fileName.Length()==0)
		fileName=iEikonEnv->EikAppUi()->Application()->AppCaption();
	User::LeaveIfError(EikFileUtils::Parse(fileName));
	TParsePtrC parse(fileName);
	if (parse.NamePresent())
		fileName=parse.NameAndExt();
	else
		fileName=TPtrC();
	TextUtils::ClipToFit(fileName,*(iLabel->Font()),iLabel->Size().iWidth,TChar(0));
	iLabel->SetTextL(fileName);
	}

EXPORT_C void CEikFileNameLabel::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	if (aPointerEvent.iType==TPointerEvent::EButton1Down && iLabel->Rect().Contains(aPointerEvent.iPosition))
		iEikonEnv->DisplayTaskList();
	}

EXPORT_C void* CEikFileNameLabel::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C TSize CEikFileNameLabel::MinimumSize()
	{
	TSize size=iLabel->MinimumSize();
	size+=iBorder.SizeDelta();
	return size;
	}

EXPORT_C void CEikFileNameLabel::SizeChanged()
	{
	TSize size=iSize-iBorder.SizeDelta();
	TPoint pos=iPosition;
	const TMargins margins=iBorder.Margins();
	pos.iX+=margins.iLeft;
	pos.iY+=margins.iTop;
	iLabel->SetExtent(pos,size);
	}

EXPORT_C TInt CEikFileNameLabel::CountComponentControls() const
	{
	return 1;
	}

EXPORT_C CCoeControl* CEikFileNameLabel::ComponentControl(TInt aIndex) const
	{
	if (aIndex==0)
		return iLabel;
	return NULL;
	}


EXPORT_C void CEikFileNameLabel::Draw(const TRect& /*aRect*/) const
	{
	TRect rect=Rect();
	CGraphicsContext& gc=SystemGc();

	TGulBorder::TColors borderColors;
	LafFileNameLabel::GetBorderColors(borderColors, iEikonEnv->LafEnv(), *this);	
	iBorder.Draw(gc, rect, borderColors);

	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikFileNameLabel::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
	{
	CEikBorderedControl::GetColorUseListL(aColorUseList);
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikFileNameLabel::HandleResourceChange(TInt aType)
	{
	CEikBorderedControl::HandleResourceChange(aType);
	}
