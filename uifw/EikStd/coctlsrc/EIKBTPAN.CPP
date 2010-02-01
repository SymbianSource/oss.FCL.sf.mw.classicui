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

 
#include <eikbtpan.h>
#include <eiklbbut.h>
#include <eikcmbut.h>
#include <eiklabel.h>
#include <barsread.h>
#include <coedef.h>
#include <eiklabel.h>
#include <eikcmobs.h>
#include <uikon.hrh>
#include <eikcoctl.rsg>
#include <coemain.h>
#include <eikenv.h>
#include "lafbtpan.h"
#include "laflbbut.h"
#include <eiklbbut.h>
#include <uiklaf/private/lafenv.h>

// const TInt KButtonArrayGranularity=2;

const TInt KVerticalSpaceForNonLabeledButtons=6;
const TInt KEikButtonLabelTopMargin=2;
const TInt KEikButtonLabelBottomMargin=1;
// const TInt KStdMinButtonWidth=50;

#define VERTICAL_BUTTONS_AT_BOTTOM

static TBool AnyButtonHasHotKey(const CEikControlGroup* aGroup, const TInt count)
	{
	TBool hasHotkey=EFalse;
		for(TInt ii=0;ii<count && !hasHotkey;ii++)
			{
			if(static_cast<CEikLabeledButton*>(aGroup->Control(ii))->ShowsHotKey())
			hasHotkey=ETrue;
			}
	return hasHotkey;
	}

EXPORT_C CEikButtonPanel::~CEikButtonPanel()
	{
	if (iControlGroups)
		{
		iControlGroups->ResetAndDestroy();
		delete iControlGroups;
		}
	}

EXPORT_C CEikButtonPanel::CEikButtonPanel()
	: iMinButWidth(LafButtonPanel::MinButtonWidth())
	{
	__DECLARE_NAME(_S("CEikButtonPanel"));
	SetNonFocusing();
	}

void CEikButtonPanel::AppendNewLineL()
	{//private
	CEikControlGroup* controlGroup=new(ELeave) CEikControlGroup();
	CleanupStack::PushL(controlGroup);
	if(LafButtonPanel::ButtonsAllSameSize())
		controlGroup->SetControlsAllSameSize();
	controlGroup->SetControlSpacing(LafButtonPanel::HorGapBetweenButtons(),LafButtonPanel::VerGapBetweenButtons());
	controlGroup->SetContainerWindowL(*this);
	controlGroup->ConstructL(
		static_cast<CEikControlGroup::TStartCorner>(LafButtonPanel::DefaultStartCorner()),
		static_cast<CEikControlGroup::TOrientation>(LafButtonPanel::DefaultOrientation()));
	iControlGroups->AppendL(controlGroup);
	CleanupStack::Pop(); // controlGroup
	iCount++;
	iMinSize=TSize(0,0);
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
EXPORT_C void CEikButtonPanel::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikButtonPanel::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KEikLitBtpanCtlSt,"<CEikButtonPanel>");
	_LIT(KEikLitBtpanCtlEnd,"<\\CEikButtonPanel>");
	_LIT(KEikLitBtpanCtlMinSize, "<iMinSize>");
	_LIT(KEikLitBtpanCtlMinSizeEnd, "<\\iMinSize>");
	_LIT(KEikLitBtpanCtlButWidth, "<iButWidth>");
	_LIT(KEikLitBtpanCtlButWidthEnd, "<\\iButWidth>");
	_LIT(KEikLitBtpanCtlMinButWidth, "<iMinButWidth>");
	_LIT(KEikLitBtpanCtlMinButWidthEnd, "<\\iMinButWidth>");
	_LIT(KEikLitBtpanCtlCount, "<iCount>");
	_LIT(KEikLitBtpanCtlCountEnd, "<\\iCount>");
	_LIT(KEikLitBtpanCtlObs, "<iCommandObserver>");
	_LIT(KEikLitBtpanCtlObsEnd, "<\\iCommandObserver>");

	aWriteStream << KEikLitBtpanCtlSt;
	aWriteStream << KEikLitBtpanCtlMinSize;
	aWriteStream.WriteInt32L(iMinSize.iWidth);
	aWriteStream.WriteInt32L(iMinSize.iHeight);
	aWriteStream << KEikLitBtpanCtlMinSizeEnd;
	aWriteStream << KEikLitBtpanCtlButWidth;
	aWriteStream.WriteInt32L(iButWidth);
	aWriteStream << KEikLitBtpanCtlButWidthEnd;
	aWriteStream << KEikLitBtpanCtlMinButWidth;
	aWriteStream.WriteInt32L(iMinButWidth);
	aWriteStream << KEikLitBtpanCtlMinButWidthEnd;
	aWriteStream << KEikLitBtpanCtlCount;
	aWriteStream.WriteInt32L(iCount);
	aWriteStream << KEikLitBtpanCtlCountEnd;
	aWriteStream << KEikLitBtpanCtlObs;
	aWriteStream.WriteInt32L((TInt)iCommandObserver);
	aWriteStream << KEikLitBtpanCtlObsEnd;
	CCoeControl::WriteInternalStateL(aWriteStream);
	aWriteStream << KEikLitBtpanCtlEnd;
	}
#endif

EXPORT_C void CEikButtonPanel::ConstructL()
	{
	iControlGroups=new(ELeave) CArrayPtrFlat<CEikControlGroup>(1);
	AppendNewLineL();
	}

EXPORT_C void CEikButtonPanel::SetHorizontal()
	{
	for(TInt ii=0;ii<iCount;ii++)
		(*iControlGroups)[ii]->SetControlLayout(CEikControlGroup::EFromTopLeft, CEikControlGroup::ELayHorizontally);
	}

EXPORT_C TInt CEikButtonPanel::ButtonId(CCoeControl* aControl) const
	{
	TInt id=0;
	for(TInt ii=0;ii<iCount;ii++)
		{
		id=(*iControlGroups)[ii]->ControlId(aControl);
		if((*iControlGroups)[ii]->ControlById(id)==aControl)
			break;
		}
	return id; 
	// KErrNotFound is a valid Id, but also used by CEikControlGroup to signify not found!
	}

EXPORT_C CEikCommandButtonBase* CEikButtonPanel::ButtonById(TInt aButtonId) const
	{
	CEikLabeledButton* button=LabeledButtonById(aButtonId);
	return (button ? button->Button() : NULL);
	}

EXPORT_C CEikLabeledButton* CEikButtonPanel::LabeledButtonById(TInt aButtonId) const
	{
	CEikLabeledButton* button=NULL;
	for(TInt ii=0;ii<iCount && !button;ii++)
		{
		button=static_cast<CEikLabeledButton*>((*iControlGroups)[ii]->ControlById(aButtonId));
		}
	return button;
	}

EXPORT_C void CEikButtonPanel::AddButtonL(CEikLabeledButton* aButton,TInt aId)
	{
	AddButtonL(aButton,aId,iCount-1);//last row by default
	}

/**
 * Takes ownership of aButton, with asociated id, aId and adds it to the row of buttons aRow.
 * Creates aRow if it does not already exist. Should not be used for vertical button layout.
 * Leaves in out of memory conditions. 
 *
 * @ since Uikon1.2
 */
EXPORT_C void CEikButtonPanel::AddButtonL(CEikLabeledButton* aButton,TInt aId,TInt aRow)
	{
	CleanupStack::PushL(aButton);
	aButton->SetNonFocusing();
	aButton->SetContainerWindowL(*this);
	aButton->CopyControlContextFrom(this);
	aButton->SetObserver(this);
	for(;aRow>iCount;AppendNewLineL())
		;// no body
	(*iControlGroups)[aRow-1]->AddControlL(aButton,aId);
	CleanupStack::Pop(); // aButton
	ResetMinimumSize();
	}

EXPORT_C void CEikButtonPanel::ActivateL()
	{
	CCoeControl::ActivateL();
	}

EXPORT_C void CEikButtonPanel::ConstructFromResourceL(TResourceReader& aReader)
	{
	ConstructL();
	aReader.ReadUint32(); // read past flags - they're only used in CBAs currently
	const TInt count=aReader.ReadInt16();
	for (TInt ii=0;ii<count;++ii)
		{
		const TInt id=aReader.ReadInt16();
		CEikLabeledButton* button=new(ELeave) CEikLabeledButton;
		CleanupStack::PushL(button);
		button->CopyControlContextFrom(this);
		button->ConstructFromResourceL(aReader);
		TInt lineNumber=aReader.ReadInt8();
		if (button->ShowsHotKey())
			{
			CEikLabel* label=button->Label();
			label->CopyControlContextFrom(this);
			label->iMargin.iTop=KEikButtonLabelTopMargin;
			label->iMargin.iBottom=KEikButtonLabelBottomMargin;
			}
		CleanupStack::Pop(); // AddButtonL takes ownership
		AddButtonL(button,id,lineNumber);
		}
	}

EXPORT_C void CEikButtonPanel::ResetMinimumSize()
	{
	iMinSize=TSize(0,0);
	}

EXPORT_C void CEikButtonPanel::SetMinButtonWidth(TInt aWidth)
	{
	iMinButWidth=aWidth;
	}

EXPORT_C void CEikButtonPanel::SetCommandObserver(MEikCommandObserver* aCommandObserver)
	{
	iCommandObserver=aCommandObserver;
	}

void CEikButtonPanel::UpdateHotKeyL(TInt aCommandId,CEikLabeledButton::TFlags aFlags,TInt aKeyCode)
	{
	CEikLabeledButton* button=LabeledButtonById(aCommandId);
	if (!button)
		User::Leave(KErrNotFound);
	button->UpdateHotKey(aKeyCode,aFlags);
	}

EXPORT_C TInt CEikButtonPanel::CountComponentControls() const
	{
	return iCount;
	}

EXPORT_C CCoeControl* CEikButtonPanel::ComponentControl(TInt aIndex) const
	{
	return (*iControlGroups)[aIndex];
	}

EXPORT_C void CEikButtonPanel::SizeChanged()
	{
	if(!iMinSize.iWidth)
		SetButtonWidths();
	TInt excess=iSize.iWidth-iMinSize.iWidth;
	TMargins8 margins = LafButtonPanel::Margins();
	TInt gapBetweenButtons=LafButtonPanel::HorGapBetweenButtons();
	if(excess<0)
		AdjustMarginsToFit(margins.iLeft, margins.iRight, gapBetweenButtons);
	TRect groupRect=Rect();
	groupRect.iTl.iX+=margins.iLeft;
	groupRect.iBr.iX-=margins.iRight;
	groupRect.iTl.iY+=margins.iTop;
	
	#if defined VERTICAL_BUTTONS_AT_BOTTOM
	groupRect.iTl.iY+=(iSize.iHeight-iMinSize.iHeight);
	#endif
	
	TRect individualRect(groupRect.iTl,TSize(0,0));
	TInt translateBy=0;
	TInt horizontal=0;
	TInt vertical=0;
	CEikControlGroup* group;
	TSize groupMinSize;
	for(TInt ii=0 ; ii<iCount ;ii++)
		{
		group=(*iControlGroups)[ii];
		group->ControlSpacing(horizontal,vertical);
		group->SetControlSpacing(gapBetweenButtons,vertical);
		groupMinSize=group->MinimumSize();
		individualRect=TRect(individualRect.iTl,TSize(groupRect.Width(),groupMinSize.iHeight));
		TRect shiftedRect=individualRect;
		excess=groupRect.Width()-groupMinSize.iWidth;
		if (excess>0)
			{
			TInt shiftLeft=0;
			TInt shiftRight=0;
			LafButtonPanel::TranslateForExcessSpace(excess, shiftLeft, shiftRight);
			shiftedRect.iTl.iX+=shiftLeft;
			shiftedRect.iBr.iX+=shiftRight;
			}
		group->SetRect(shiftedRect);
		translateBy=group->Size().iHeight+LafButtonPanel::InterRowMargin();
		if(LafLabeledButton::ShowHotKey()
			&& group->Orientation()==CEikControlGroup::ELayHorizontally
			&& !(AnyButtonHasHotKey(group,group->ControlArray()->Count())))
			{
			translateBy+=KVerticalSpaceForNonLabeledButtons;
			}
		individualRect.iTl.iY+=translateBy;
		}
	}

void CEikButtonPanel::AdjustMarginsToFit(TInt8& aLeftBorder,TInt8& aRightBorder, TInt& aGapBetweenButtons)
	{
	// let the laf dictate the shrinking policy
	CEikControlGroup* group;
	TFixedArray<LafButtonPanel::TDimensions,KLafButPanMaxLinesOfDlgButtons> array;
	for(TInt ii=0; ii<iCount && ii<KLafButPanMaxLinesOfDlgButtons;ii++)
		{
		group=(*iControlGroups)[ii];
		array[ii].iNumButtons=group->ControlArray()->Count();
		array[ii].iExcess=iSize.iWidth-group->MinimumSize().iWidth;
		}
	LafButtonPanel::ReduceMarginsToFit(array, aLeftBorder, aRightBorder, aGapBetweenButtons);
	}

void CEikButtonPanel::SetButtonWidths()
	{
	if((*iControlGroups)[0]->Orientation()==CEikControlGroup::ELayHorizontally)
		{
		CArrayFix<TEikGroupControl>* array=NULL;
		TInt components;
		TInt width=0;
		if(iMinButWidth!=KLafButPanNoMinButWidth)
			width=iMinButWidth;
		if(LafButtonPanel::ButtonsAllSameSize())
			{
			TInt thisWidth;
			for(TInt ll=0; ll<iCount ; ll++)
				{
				array=(*iControlGroups)[ll]->ControlArray();
				components=array->Count();
				for(TInt mm=0; mm<components;mm++)
					{
					thisWidth=(*array)[mm].iControl->MinimumSize().iWidth;
					if(thisWidth>iButWidth)
						iButWidth=thisWidth;
					}
				}
			if(width<iButWidth)
				width=iButWidth;
			}
		if(width)
			{	
			for(TInt jj=0; jj<iCount ; jj++)
				{
				array=(*iControlGroups)[jj]->ControlArray();
				components=array->Count();
				for(TInt kk=0; kk<components;kk++)
					{
					TEikGroupControl& grpControl=(*array)[kk];
					grpControl.SetLength(Max(width,grpControl.iControl->MinimumSize().iWidth));
					}
				}
			}
		}
	}

EXPORT_C TSize CEikButtonPanel::MinimumSize()
	{
	if (!iMinSize.iWidth)
		{
		SetButtonWidths();
		TMargins8 margins = LafButtonPanel::Margins();
		iMinSize.iHeight=margins.iTop+margins.iBottom;
		iMinSize.iWidth=0;
		iMinSize.iHeight+=(iCount-1)*LafButtonPanel::InterRowMargin();
		CEikControlGroup* group=NULL;
		TSize groupMinSize;
		for(TInt jj=0; jj<iCount; jj++)
			{
			group=(*iControlGroups)[jj];
			TInt count=group->ControlArray()->Count();
			if(LafLabeledButton::ShowHotKey())
				{
				CEikControlGroup::TOrientation orientation=group->Orientation();
				if(orientation==CEikControlGroup::ELayVertically && !LafButtonPanel::ButtonsAllSameSize())
					{
					for(TInt ii=0;ii<count;ii++)
						{
						if(!static_cast<CEikLabeledButton*>(group->Control(ii))->ShowsHotKey())
							iMinSize.iHeight+=KVerticalSpaceForNonLabeledButtons;
						}
					}
				else if(orientation==CEikControlGroup::ELayVertically && LafButtonPanel::ButtonsAllSameSize())
					{
					if(!AnyButtonHasHotKey(group,count))
						{
						group->SetControlSpacing(LafButtonPanel::HorGapBetweenButtons(),LafButtonPanel::VerGapBetweenButtons()+KVerticalSpaceForNonLabeledButtons);
						iMinSize.iHeight+=KVerticalSpaceForNonLabeledButtons; // for bottom
						}
					}
				else if(orientation==CEikControlGroup::ELayHorizontally)
					{
					if(!AnyButtonHasHotKey(group,count))
						iMinSize.iHeight+=KVerticalSpaceForNonLabeledButtons;
					}
				}
			groupMinSize=group->MinimumSize();
			iMinSize.iHeight+=groupMinSize.iHeight;
			iMinSize.iWidth=Max(iMinSize.iWidth,groupMinSize.iWidth);
			}
		iMinSize.iWidth+=(margins.iLeft + margins.iRight);
		}
	return(iMinSize);
	}

EXPORT_C void CEikButtonPanel::HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)
	{
	if (aEventType==EEventStateChanged)
		iCommandObserver->ProcessCommandL(ButtonId(aControl));
	}

EXPORT_C CEikCommandButtonBase* CEikButtonPanel::ButtonForKey(TInt aChar,TInt& aButtonId) const
	{
	const TCharF foldedChar(aChar);
	const TUint foldedCharCode=TUint(foldedChar);
	TInt count=0;
	CEikControlGroup* group=NULL;
	CEikCommandButtonBase* match=NULL;
	for(TInt jj=0;jj<iCount && !match;jj++)
		{
		group=(*iControlGroups)[jj];
		count=group->ControlArray()->Count();
		for (TInt ii=0;ii<count && !match ;++ii)
			{
			CEikLabeledButton* button=static_cast<CEikLabeledButton*>(group->Control(ii));
			if ((foldedChar==TCharF(button->HotKeyCode()))
				||((button->Button()->IsDefault())&&(LafEnv::IsDefaultKey(foldedCharCode))))
				{
				aButtonId=group->ControlId(group->Control(ii));
				if (button->IsVisible())
					match=button->Button();
				}
			}
		}
	return match;
	}

EXPORT_C void CEikButtonPanel::MakeButtonVisible(TInt aButtonId,TBool aVisible)
	{
	TInt count=0;
	CEikControlGroup* group=NULL;
	for(TInt jj=0;jj<iCount;jj++)
		{
		group=(*iControlGroups)[jj];
		count=group->ControlArray()->Count();
		for (TInt ii=0;ii<count;++ii)
			{
			CEikLabeledButton* button=static_cast<CEikLabeledButton*>(group->Control(ii));
			if (group->ControlId(group->Control(ii))==aButtonId)
				{
				button->MakeVisible(aVisible);
				return;
				}
			}
		}
	}


void CEikButtonPanel::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)
	{
	TInt groupIndex=0;
	CEikLabeledButton* lBut=LabeledButtonByPosition(aPosition,groupIndex);
	CEikCommandButtonBase* button=static_cast<CEikCommandButtonBase*>(lBut->Button());
	static_cast<CEikCommandButton*>(button)->SetCommandL(aCommandId, aText, aBitmap, aMask);
	TInt ignore=0;
	(*((*iControlGroups)[groupIndex])->ControlArray())[RelativePosition(aPosition,ignore)].iId=aCommandId;
	}

void CEikButtonPanel::SetCommandL(TInt aPosition,TInt aResourceId)
	{
	TResourceReader reader;
	iEikonEnv->CreateResourceReaderLC(reader,aResourceId);
	const TInt id=reader.ReadInt16(); // id
	const TInt type=reader.ReadInt16(); // buttontype
	if (type==EEikCtCommandButton)
		{
		CEikCommandButton* button=new(ELeave) CEikCommandButton;
		CleanupStack::PushL(button);
		button->ConstructFromResourceL(reader);
		/*TInt hotKeyCode=*/reader.ReadInt32();
		/*TInt lButFlags=*/reader.ReadInt8();
		SetCommandL(aPosition, id, button->Label()->Text(), NULL, NULL); 
		CleanupStack::PopAndDestroy();
		}
	CleanupStack::PopAndDestroy();
	}

void CEikButtonPanel::SetCommandSetL(TInt aResourceId)
	{
	TResourceReader reader;
	iEikonEnv->CreateResourceReaderLC(reader,aResourceId);
	const TInt count=reader.ReadInt16();
	TInt ii;
	for (ii=0 ; ii<count; ii++)
		{
		const TInt id=reader.ReadInt16(); // id
		const TInt type=reader.ReadInt16(); // buttontype
	
		if (type==EEikCtCommandButton)
			{
			CEikCommandButton* button=new(ELeave) CEikCommandButton;
			CleanupStack::PushL(button);
			button->ConstructFromResourceL(reader);
			/*TInt hotKeyCode=*/reader.ReadInt32();
			/*TInt lButFlags=*/reader.ReadInt8();
			SetCommandL(ii, id, button->Label()->Text(), NULL, NULL); 
			CleanupStack::PopAndDestroy();
			DimCommand(id,EFalse);
			}
		}
	CleanupStack::PopAndDestroy();
	}

void CEikButtonPanel::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)
	{
	// !!! todo - cleanup support for bitmaps
//	if (IsReadyToDraw())
//		User::Leave(KErrGeneral);
	TInt groupIndex=0;
	TInt posInGroup=RelativePosition(aPosition,groupIndex);
	CEikControlGroup* group=(*iControlGroups)[groupIndex];
	const TInt count=group->ControlArray()->Count();
	if (aPosition>count)
		User::Leave(KErrOverflow);
	CEikCommandButton* button=new(ELeave) CEikCommandButton;
	CleanupStack::PushL(button);
	if (aText)
		button->SetTextL(*aText);
	if (aBitmap)
		button->SetPictureL(aBitmap,aMask);
	CEikLabeledButton* lBut=new(ELeave) CEikLabeledButton;
	CleanupStack::PushL(lBut);
	lBut->ConstructL(button,0,0);
	CleanupStack::Pop(); // button
	lBut->SetContainerWindowL(*this);
	lBut->SetObserver(this);
	if (aPosition<count)
		{
		TEikGroupControl grpControl=TEikGroupControl(lBut,aCommandId,0,0);
		group->InsertControlL(grpControl,posInGroup);
		}
	else
		group->AddControlL(lBut,aCommandId);
	CleanupStack::Pop(); // lBut
	}


void CEikButtonPanel::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)
	{
	CEikCommandButton* lBut=static_cast<CEikCommandButton*>(LabeledButtonByPosition(aPosition)->Button());
	TInt groupIndex=0; 
	TInt relativePos=RelativePosition(aPosition,groupIndex);
	CEikControlGroup* group=(*iControlGroups)[groupIndex];
	lBut->AddCommandToStackL(group->ControlId(group->Control(relativePos)),aText,aBitmap,aMask);
	(*group->ControlArray())[relativePos].iId=aCommandId;
	}

void CEikButtonPanel::AddCommandToStackL(TInt /*aPosition*/,TInt /*aResourceId*/)
	{
	}

void CEikButtonPanel::AddCommandSetToStackL(TInt /*aResourceId*/)
	{
	}

void CEikButtonPanel::SetDefaultCommand(TInt /*aCommandId*/)
	{
	}

TSize CEikButtonPanel::CalcMinimumSizeL(TInt /*aResourceId*/)
	{
	return MinimumSize();
	}

void CEikButtonPanel::RemoveCommandFromStack(TInt aPosition,TInt aCommandId)
	{
	TInt groupIndex=0;
	CEikCommandButton* lBut=static_cast<CEikCommandButton*>(LabeledButtonByPosition(aPosition,groupIndex)->Button());
	CEikControlGroup* group=(*iControlGroups)[groupIndex];
	if (aCommandId==group->ControlId(group->Control(aPosition)))
		{
		(*group->ControlArray())[aPosition].iId=lBut->PopCommandFromStack();
		}
	else
		{
		lBut->RemoveCommandFromStack(aCommandId);
		}
	}

TInt CEikButtonPanel::CommandPos(TInt aCommandId) const
	{
	TBool found=EFalse;
	TInt indexOfOwningGroup=0;
	CEikControlGroup* group=NULL;
	TInt pos=0;
	for(;(indexOfOwningGroup<iCount) && (!found); indexOfOwningGroup++)
		{
		group=(*iControlGroups)[indexOfOwningGroup];
		if(group->IndexById(aCommandId)==KErrNotFound)
			pos+=group->ControlArray()->Count();
		else
			{
			pos+=group->IndexById(aCommandId);
			found=ETrue;
			}
		}
	return (found? pos : KErrNotFound);
	}

void CEikButtonPanel::DimCommand(TInt aCommandId,TBool aDimmed)
	{
	LabeledButtonById(aCommandId)->SetDimmed(aDimmed);
	LabeledButtonById(aCommandId)->DrawNow();
	}

TBool CEikButtonPanel::IsCommandDimmed(TInt aCommandId) const
	{
	return LabeledButtonById(aCommandId)->IsDimmed();
	}

void CEikButtonPanel::MakeCommandVisible(TInt aCommandId,TBool aVisible)
	{
	MakeButtonVisible(aCommandId,aVisible);
	}

TBool CEikButtonPanel::IsCommandVisible(TInt aCommandId) const
	{
	return LabeledButtonById(aCommandId)->IsVisible();
	}

CCoeControl* CEikButtonPanel::AsControl()
	{
	return this;
	}

const CCoeControl* CEikButtonPanel::AsControl() const
	{
	return this;
	}

void CEikButtonPanel::SetBoundingRect(const TRect& /*aBoundingRect*/)
	{
	}

void CEikButtonPanel::ReduceRect(TRect& /*aBoundingRect*/) const
	{
	}

void CEikButtonPanel::SetMSKCommandObserver(MEikCommandObserver* /*aCommandObserver*/)
    {
    }

void CEikButtonPanel::DimCommandByPosition(TInt /*aPosition*/,TBool /*aDimmed*/)
    {
    }
    
TBool CEikButtonPanel::IsCommandDimmedByPosition(TInt /*aPosition*/) const
    {
    return EFalse;
    }
    
void CEikButtonPanel::MakeCommandVisibleByPosition(TInt /*aPosition*/,TBool /*aVisible*/)
    {
    }

TBool CEikButtonPanel::IsCommandVisibleByPosition(TInt /*aPosition*/) const
    {
    return EFalse;
    }

void CEikButtonPanel::AnimateCommandByPosition(TInt /*aPosition*/)
    {
    }

CCoeControl* CEikButtonPanel::GroupControlById(TInt aCommandId) const
	{
	return LabeledButtonById(aCommandId); // assume callers only care about the button part
	}

CEikCommandButton* CEikButtonPanel::GroupControlAsButton(TInt aCommandId) const
	{
	CEikCommandButton* ret=NULL;
	CEikCommandButtonBase* but=ButtonById(aCommandId);
	if (but)
		ret=STATIC_CAST(CEikCommandButton*,but);
	return ret;
	}

TInt CEikButtonPanel::CommandId(TInt aCommandPos) const
	{
	TInt indexOfOwningGroup;
	CEikLabeledButton* button=LabeledButtonByPosition(aCommandPos,indexOfOwningGroup);
	return (*iControlGroups)[indexOfOwningGroup]->ControlId(button);
	}

CEikLabeledButton* CEikButtonPanel::LabeledButtonByPosition(TInt aPosition)	const
	{
	TInt ignore;
	return LabeledButtonByPosition(aPosition,ignore);
	}

CEikLabeledButton* CEikButtonPanel::LabeledButtonByPosition(TInt aPosition, TInt& aGroupIndex) const
	{
	TInt pos=RelativePosition(aPosition, aGroupIndex);
	return static_cast<CEikLabeledButton*>((*iControlGroups)[aGroupIndex]->Control(pos));
	}

TInt CEikButtonPanel::RelativePosition(TInt aCommandPos, TInt& aGroupIndex) const
	{
	TInt trialPos=aCommandPos;
	aGroupIndex=0;
	CEikControlGroup* group=NULL;
	for(;(aGroupIndex<iCount) && (trialPos>=0); aGroupIndex++)
		{
		aCommandPos=trialPos;
		group=(*iControlGroups)[aGroupIndex];
		trialPos-=group->ControlArray()->Count();
		}
	aGroupIndex--;
	return aCommandPos;
	}

TInt CEikButtonPanel::ButtonCount() const
	{
	TInt buttonCount=0;
	CEikControlGroup* group=NULL;
	for(TInt jj=0; jj<iCount;jj++)
		{
		group=(*iControlGroups)[jj];
		buttonCount+=group->ControlArray()->Count();
		}
	return buttonCount;
	}

TUint CEikButtonPanel::ButtonGroupFlags() const
	{
	return 0;
	}

TBool CEikButtonPanel::ButtonsConsumedKeyL(TInt aCode)
	{
	TInt buttonId;
	CEikCommandButtonBase* button=ButtonForKey(aCode,buttonId);
	
	if (!button)
		return(EFalse);
	
	if (button->IsDimmed())
		{
		ReportEventL(MCoeControlObserver::EEventInteractionRefused);
		return(EFalse);
		}
	
	if (!button->IsVisible())
		return(EFalse);
	
	button->Animate();
	iCommandObserver->ProcessCommandL(buttonId);
    
	return(ETrue);
	}

EXPORT_C TKeyResponse CEikButtonPanel::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
    if (aType!=EEventKey)
        return(EKeyWasConsumed);

	TInt code=aKeyEvent.iCode;
	TInt foldedCode=TCharF(code);
	
	return ButtonsConsumedKeyL(foldedCode) ? EKeyWasConsumed : EKeyWasNotConsumed;
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikButtonPanel::GetColorUseListL(CArrayFix<TCoeColorUse>& /*aColorUseList*/) const
	{
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikButtonPanel::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	}

EXPORT_C void CEikButtonPanel::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikButtonPanel::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikButtonPanel::Reserved_2()
	{}
