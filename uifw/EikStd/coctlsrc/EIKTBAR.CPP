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
#include <eiktbar.h>
#include <eikbutb.h>
#include <eikcmobs.h>
#include <eikfctry.h>
#include <eikpanic.h>
#include <uikon.hrh>
#include <eikenv.h>
#include <eikapp.h>
#include <eikappui.h>
#include <eikdoc.h>
#include <eikcmbut.h>
#include <gulcolor.h>
#include "LAFTBAR.H"


EXPORT_C CEikToolBar::~CEikToolBar()
	{
	delete iBrushAndPenContext;
	delete iControlTypes;
	}	

EXPORT_C CEikToolBar::CEikToolBar()
	{
	__DECLARE_NAME(_S("CEikToolBar"));
	LafToolBar::GetDefaultBorder(iBorder);
	}

void CEikToolBar::BaseConstructL()
	{
	CreateWindowL();
	Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorToolbarBackground,*this));
	RDrawableWindow* window=DrawableWindow();
	window->SetPointerGrab(ETrue);
	window->SetShadowDisabled(ETrue);
	EnableDragEvents();
	iBrushAndPenContext=CCoeBrushAndPenContext::NewL();
	iBrushAndPenContext->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iBrushAndPenContext->SetBrushColor(iEikonEnv->ControlColor(EColorToolbarBackground,*this));
	iBrushAndPenContext->SetPenColor(iEikonEnv->ControlColor(EColorToolbarText,*this));
	SetControlContext(iBrushAndPenContext);
	}

EXPORT_C void CEikToolBar::ConstructFromResourceL(TResourceReader& aReader)
	{
	if (!iControlTypes)
		iControlTypes=new(ELeave) CArrayFixFlat<TInt>(4);
	const TInt length=aReader.ReadInt16();
	const TInt breadth=aReader.ReadInt16();
	const TInt lines=aReader.ReadInt8();
	iToolBarFlags=aReader.ReadInt32();
	if (iToolBarFlags&EEikToolBarHorizontal)
		CEikControlGroup::ConstructL(CEikControlGroup::EFromTopLeft,CEikControlGroup::ELayHorizontally);
	else
		CEikControlGroup::ConstructL(CEikControlGroup::EFromTopRight,CEikControlGroup::ELayVertically);
	if (length)
		SetLengthInPixels(length);
	if (breadth)
		SetBreadthInPixels(breadth);
	SetNumberOfLines(lines,iToolBarFlags&EEikToolBarDistributeControlsEvenlyBetweenLines);
	if (iToolBarFlags&EEikToolBarAllControlsSameSize)
		SetControlsAllSameSize();

	const TInt count=aReader.ReadInt16();
	for (TInt ii=0;ii<count;++ii)
		{
		const TInt ctrlType=aReader.ReadInt16();
		CCoeControl* ctrl=EikControlFactory::CreateByTypeL(ctrlType).iControl;
		if (!ctrl)
			ctrl=iCommandObserver->CreateCustomCommandControlL(ctrlType);
		__ASSERT_DEBUG(ctrl, Panic(EEikPanicToolBarNullControl));
		ctrl->SetNonFocusing();
		CleanupStack::PushL(ctrl);
		const TInt id=aReader.ReadInt16();
		const TInt flags=aReader.ReadInt16();
		TEikGroupControl groupCtrl(ctrl,id,aReader.ReadInt16(),flags);
		AddControlL(groupCtrl); // ownership now taken by array
		CleanupStack::Pop(); // ctrl
		AddControlTypeL(ctrlType);
		ctrl->ConstructFromResourceL(aReader);
		}

	aReader.ReadInt32(); // extension link
	}

EXPORT_C void CEikToolBar::SetDimmed(TBool aDimmed)
	{
	const TInt count=iControlArray->Count();
	for (TInt ii=0;ii<count;ii++)
		(*iControlArray)[ii].iControl->SetDimmed(aDimmed);
	}

EXPORT_C void CEikToolBar::ReduceRect(TRect& aBoundingRect) const
	{
	if (!IsVisible())
		return;
	if (iToolBarFlags&EEikToolBarHorizontal)
		aBoundingRect.iTl.iY+=iSize.iHeight;
	else
		aBoundingRect.iBr.iX-=iSize.iWidth;
	}

EXPORT_C void CEikToolBar::SetBoundingRect(const TRect& aRect)
	{
	TSize size=aRect.Size();
	SetLengthInPixels(iToolBarFlags&EEikToolBarHorizontal? size.iWidth: size.iHeight);
	TSize thisSize=MinimumSize();
	TPoint thisPos=aRect.iTl;
	if (iToolBarFlags&EEikToolBarHorizontal)
		iSize.iHeight=thisSize.iHeight;
	else
		{
		thisPos.iX=aRect.iBr.iX-thisSize.iWidth;
		iSize.iWidth=thisSize.iWidth;
		}
	CCoeControl::SetExtent(thisPos,iSize);
	}

EXPORT_C void CEikToolBar::StaticConstructL(MEikCommandObserver* aCommandObserver,TInt aResourceId)
	{
	BaseConstructL();
	iCommandObserver=aCommandObserver;
	if (aResourceId)
		{
		TResourceReader reader;
		iCoeEnv->CreateResourceReaderLC(reader,aResourceId);
		ConstructFromResourceL(reader);
		CleanupStack::PopAndDestroy();
		}
	}

EXPORT_C void CEikToolBar::ConstructL(MEikCommandObserver* aCommandObserver,TInt aResourceId,const TRect& aBoundingRect)
	{
	if (!iControlTypes)
		iControlTypes=new(ELeave) CArrayFixFlat<TInt>(4);
	StaticConstructL(aCommandObserver,aResourceId);
	SetBoundingRect(aBoundingRect);
	if (!(iToolBarFlags&EEikToolBarDelayActivation))
		ActivateL();
	}

EXPORT_C void CEikToolBar::SetCommandObserver(MEikCommandObserver* aCommandObserver)
	{
	iCommandObserver=aCommandObserver;
	}

EXPORT_C void CEikToolBar::HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent)
	{
	__ASSERT_DEBUG(iCommandObserver, Panic(EEikPanicToolBarHasNoObserver));
	if (aEvent==EEventStateChanged)
		{
		TInt aCommand=ControlId(aControl);
		iCommandObserver->ProcessCommandL(aCommand);
		}
	}

EXPORT_C void CEikToolBar::AddControlL(CCoeControl* aControl,TInt aId)
	{
	CEikControlGroup::AddControlL(aControl,aId);
	aControl->SetObserver(this);
	}

EXPORT_C void CEikToolBar::AddControlL(TEikGroupControl& aGroupControl)
	{
	CEikControlGroup::AddControlL(aGroupControl);
	aGroupControl.iControl->SetObserver(this);
	}

EXPORT_C void CEikToolBar::CoordinateButtons(TInt aId,TInt aCount,TEikButtonCoordinator* aCoordinator)
	{
	TInt index=IndexById(aId);
	while (aCount--)
		((CEikButtonBase*)Control(index++))->SetCoordinator(aCoordinator);
	}

EXPORT_C TBool CEikToolBar::DelayActivation() const
	{
	return (iToolBarFlags&EEikToolBarDelayActivation);
	}

EXPORT_C void CEikToolBar::SetButtonStateOn(TInt aId,TBool aState)
	{
	CEikButtonBase* button=(CEikButtonBase*)ControlById(aId);
	CEikButtonBase::TState bState=aState? CEikButtonBase::ESet: CEikButtonBase::EClear;
	if (button->State()==bState)
		return;
	button->SetState(bState);
	button->DrawDeferred();
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
EXPORT_C void CEikToolBar::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikToolBar::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KLitEikTBarCtlStart, "<CEikToolBar>");
	_LIT(KLitEikTBarCtlEnd, "<\\CEikToolBar>");
	_LIT(KLitEikTBarFlgs,"<iToolBarFlags>");
	_LIT(KLitEikTBarFlgsEnd,"<\\iToolBarFlags>");
	_LIT(KLitEikTBarCntxt,"<iBrushAndPenContext>");
	_LIT(KLitEikTBarCntxtEnd,"<\\iBrushAndPenContext>");
	_LIT(KLitEikTBarCtlTypes,"<iControlTypes>");
	_LIT(KLitEikTBarCtlTypesEnd,"<\\iControlTypes>");

	aWriteStream << KLitEikTBarCtlStart;
	aWriteStream << KLitEikTBarFlgs;
	aWriteStream.WriteInt32L(iToolBarFlags);
	aWriteStream << KLitEikTBarFlgsEnd;
	aWriteStream << KLitEikTBarCntxt;
	aWriteStream.WriteInt32L(iBrushAndPenContext->BrushStyle());
	aWriteStream << iBrushAndPenContext->BrushColor();
	if(&(iBrushAndPenContext->BrushBitmap()))
		aWriteStream << iBrushAndPenContext->BrushBitmap();
	aWriteStream << iBrushAndPenContext->PenColor();
	aWriteStream << KLitEikTBarCntxtEnd;
	aWriteStream << KLitEikTBarCtlTypes;
	const TInt count=iControlTypes->Count();
	for(TInt ii=0;ii<count;ii++)
		{
		aWriteStream.WriteInt32L((*iControlTypes)[ii]);
		}
	aWriteStream << KLitEikTBarCtlTypesEnd;
	CEikControlGroup::WriteInternalStateL(aWriteStream);
	aWriteStream << KLitEikTBarCtlEnd;
	}
#endif

EXPORT_C void CEikToolBar::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikControlGroup::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikToolBar::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikToolBar::Reserved_2()
	{}

TInt CEikToolBar::ControlCount() const
	{
	return iControlArray->Count();
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikToolBar::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
	{
	CEikControlGroup::GetColorUseListL(aColorUseList);
	LafToolBar::GetColorUseListL(aColorUseList);
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikToolBar::HandleResourceChange(TInt aType)
	{
	CEikControlGroup::HandleResourceChange(aType);

	if(aType==KEikMessageColorSchemeChange)
		{
		iBrushAndPenContext->SetBrushStyle(CGraphicsContext::ESolidBrush);
		iBrushAndPenContext->SetBrushColor(iEikonEnv->ControlColor(EColorToolbarBackground,*this));
		iBrushAndPenContext->SetPenColor(iEikonEnv->ControlColor(EColorToolbarText,*this));
		Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorToolbarBackground,*this));
		}
	}

void CEikToolBar::AddControlTypeL(TInt aType)
	{
	iControlTypes->AppendL(aType);
	}

void CEikToolBar::RemoveControlType(TInt aIndex)
	{
	iControlTypes->Delete(aIndex);
	}

TBool CEikToolBar::ControlIsButton(TInt aIndex) const
	{
	if (ControlCount()!=iControlTypes->Count())
		return EFalse;
	const TInt type=(*iControlTypes)[aIndex];
	switch (type)
		{
	case EEikCtCommandButton:
	case EEikCtLabeledButton:
	case EEikCtTextButton:
	case EEikCtMenuButton:
	case EEikCtBitmapButton:
		return ETrue;
	default:
		break;
		}
	return EFalse;
	}

void CEikToolBar::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)
	{
	ButtonByIndex(aPosition)->SetCommandL(aCommandId,aText,aBitmap,aMask);
	SetCurrentId(aPosition,aCommandId);
	}

void CEikToolBar::SetCommandL(TInt /*aPosition*/,TInt /*aResourceId*/)
	{

	}

void CEikToolBar::SetCommandSetL(TInt /*aResourceId*/)
	{

	}

void CEikToolBar::AddCommandL(TInt /*aPosition*/,TInt /*aCommandId*/,const TDesC* /*aText*/,const CFbsBitmap* /*aBitmap*/,const CFbsBitmap* /*aMask*/)
	{
	User::Leave(KErrNotSupported);
	}

void CEikToolBar::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)
	{
	ButtonByIndex(aPosition)->AddCommandToStackL(CurrentId(aPosition),aText,aBitmap,aMask);
	SetCurrentId(aPosition,aCommandId);
	}

void CEikToolBar::AddCommandToStackL(TInt /*aPosition*/,TInt /*aResourceId*/)
	{

	}

void CEikToolBar::AddCommandSetToStackL(TInt /*aResourceId*/)
	{

	}

void CEikToolBar::SetDefaultCommand(TInt /*aCommandId*/)
	{
	}

TSize CEikToolBar::CalcMinimumSizeL(TInt /*aResourceId*/)
	{
	return MinimumSize();
	}

void CEikToolBar::SetMSKCommandObserver(MEikCommandObserver* /*aCommandObserver*/)
    {
    }

void CEikToolBar::DimCommandByPosition(TInt /*aPosition*/,TBool /*aDimmed*/)
    {
    }
    
TBool CEikToolBar::IsCommandDimmedByPosition(TInt /*aPosition*/) const
    {
    return EFalse;
    }
    
void CEikToolBar::MakeCommandVisibleByPosition(TInt /*aPosition*/,TBool /*aVisible*/)
    {
    }

TBool CEikToolBar::IsCommandVisibleByPosition(TInt /*aPosition*/) const
    {
    return EFalse;
    }

void CEikToolBar::AnimateCommandByPosition(TInt /*aPosition*/)
    {
    }

void CEikToolBar::RemoveCommandFromStack(TInt aPosition,TInt aCommandId)
	{
	if (aCommandId==CurrentId(aPosition))
		{
		SetCurrentId(aPosition,ButtonByIndex(aPosition)->PopCommandFromStack());
		}
	else
		{
		ButtonByIndex(aPosition)->RemoveCommandFromStack(aCommandId);
		}
	}

TInt CEikToolBar::CurrentId(TInt aPosition) const
	{
	return CONST_CAST(CEikToolBar*,this)->GroupControlByIndex(IndexFromPosition(aPosition)).iId;
	}

void CEikToolBar::SetCurrentId(TInt aPosition,TInt aId)
	{
	GroupControlByIndex(IndexFromPosition(aPosition)).iId=aId;
	}

TInt CEikToolBar::IndexFromPosition(TInt aPos) const
	{
	const TInt count=iControlArray->Count();
	for (TInt ii=0;ii<count;ii++)
		{
		if (ControlIsButton(ii))
			{
			if (aPos==0)
				return ii;
			else
				--aPos;
			}
		}
	return KErrNotFound;
	}

TEikGroupControl& CEikToolBar::GroupControlByIndex(TInt aIndex) const
	{
	return (*(ControlArray()))[aIndex];
	}

CEikCommandButton* CEikToolBar::ButtonByIndex(TInt aIndex) const
	{
	const TInt index=IndexFromPosition(aIndex);
	if (index==KErrNotFound)
		return NULL;
	return STATIC_CAST(CEikCommandButton*,Control(index));
	}

TInt CEikToolBar::CommandPos(TInt aCommandId) const
	{ // !!! does this need a sensible implementation?
	const TInt ctrlIndex=IndexById(aCommandId);
	TInt pos=KErrNotFound;
	if (ctrlIndex!=KErrNotFound)
		{
		for (TInt ii=0;ii<=ctrlIndex;ii++)
			if (ControlIsButton(ii))
				++pos;
		}
	return pos;
	}

void CEikToolBar::DimCommand(TInt aCommandId,TBool aDimmed)
	{
	// !!! may want an overload that allows drawing as whole toolbar redraws will flicker
	CCoeControl* ctrl=ControlById(aCommandId);
	// __ASSERT_ALWAYS(ctrl,Panic(........
	ctrl->SetDimmed(aDimmed);
	}

TBool CEikToolBar::IsCommandDimmed(TInt aCommandId) const
	{
	CCoeControl* ctrl=ControlById(aCommandId);
	// __ASSERT_ALWAYS(ctrl,Panic(........
	return ctrl->IsDimmed();
	}

CCoeControl* CEikToolBar::AsControl()
	{
	return this;
	}

const CCoeControl* CEikToolBar::AsControl() const
	{
	return this;
	}

void CEikToolBar::MakeCommandVisible(TInt aCommandId,TBool aVisible)
	{
	CCoeControl* ctrl=ControlById(aCommandId);
	// __ASSERT_ALWAYS(ctrl,Panic(........
	ctrl->MakeVisible(aVisible);
	}

TBool CEikToolBar::IsCommandVisible(TInt aCommandId) const
	{
	CCoeControl* ctrl=ControlById(aCommandId);
	// __ASSERT_ALWAYS(ctrl,Panic(........
	return ctrl->IsVisible();
	}

CCoeControl* CEikToolBar::GroupControlById(TInt aCommandId) const
	{
	return ControlById(aCommandId);
	}

CEikCommandButton* CEikToolBar::GroupControlAsButton(TInt aCommandId) const
	{
	CEikCommandButton* ret=NULL;
	const TInt index=IndexById(aCommandId);
	if (index!=KErrNotFound && ControlIsButton(index))
		ret=STATIC_CAST(CEikCommandButton*,ControlById(aCommandId));
	return ret;
	}

TInt CEikToolBar::CommandId(TInt aCommandPos) const
	{
	return CurrentId(aCommandPos);
	}

TInt CEikToolBar::ButtonCount() const
	{
	TInt numButtons=0;
	const TInt ctrlCount=iControlArray->Count();
	for (TInt ii=0;ii<ctrlCount;ii++)
		{
		if (ControlIsButton(ii))
			++numButtons;
		}
	return numButtons;
	}

TUint CEikToolBar::ButtonGroupFlags() const
	{
	if (DelayActivation())
		return CEikButtonGroupContainer::EDelayActivation;
	return 0;
	}
