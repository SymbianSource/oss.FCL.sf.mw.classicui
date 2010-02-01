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


#include <eikcmbut.h>
#include <barsread.h>
#include <gulbordr.h>
#include <eikenv.h>
#include <eiklabel.h>
#include <eikimage.h>
#include <eikpanic.h>
#include <LAFCMBUT.H>

#include "gulcolor.h"
#include <AknIconUtils.h>

const TInt KLayoutMask				=0x0007;
const TInt KLayoutAndFontMask		=0x000f;
const TInt KExcessMask				=0x00f0;
const TInt KDisplayContentMask		=0x0f00;

//
// class CEikCommandStack
//

NONSHARABLE_CLASS(CEikCommandStack) : public CBase
	{
public:
	class TStackableCommand
		{
	public:
		TStackableCommand();
		TStackableCommand(TInt aCommandId,HBufC* aText,CFbsBitmap* aBitmap,CFbsBitmap* aMask);
	public:
		void SetBitmapOwner(TBool aOwner);
		void SetDimmed(TBool aDimmed);
		void SetVisible(TBool aVisible);
		inline TBool IsBitmapOwner() const;
		inline TBool IsDimmed() const;
		inline TBool IsVisible() const;
	public:
		TInt iCommandId;
		HBufC* iText;
		CFbsBitmap* iBitmap;
		CFbsBitmap* iMask;
	private:
		enum TFlags
			{
			EBitmapOwner	=0x04,
			EDimmed			=0x08,
			EInvisible		=0x10,
			};
	private:
		TInt iFlags;
		};
public:
	static CEikCommandStack* NewL();
	~CEikCommandStack();
public:
	void AddL(TInt aCommandId,const TDesC* aText,CFbsBitmap* aBitmap,CFbsBitmap* aMask);
	TBool Remove(TInt aCommandId);
	TStackableCommand Pop();
	TInt Level() const;
	TStackableCommand& StackableCommand(TInt aCommandId) const;
	TStackableCommand& StackableCommandByPos(TInt aPos) const;
private:
	TInt Find(TInt aCommandId) const;
	void Delete(TInt aIndex);
private:
	CArrayFix<TStackableCommand>* iCommands;
	};

CEikCommandStack::TStackableCommand::TStackableCommand()
	: iCommandId(0), iText(NULL), iBitmap(NULL), iMask(NULL), iFlags(0)
	{}

CEikCommandStack::TStackableCommand::TStackableCommand(TInt aCommandId,HBufC* aText,
													   CFbsBitmap* aBitmap,CFbsBitmap* aMask)
	: iCommandId(aCommandId), iText(aText), iBitmap(aBitmap), iMask(aMask), iFlags(0)
	{}

void CEikCommandStack::TStackableCommand::SetBitmapOwner(TBool aOwner)
	{
	if (aOwner)
		iFlags|=EBitmapOwner;
	else
		iFlags&=~EBitmapOwner;
	}

void CEikCommandStack::TStackableCommand::SetDimmed(TBool aDimmed)
	{
	if (aDimmed)
		iFlags|=EDimmed;
	else
		iFlags&=~EDimmed;
	}

void CEikCommandStack::TStackableCommand::SetVisible(TBool aVisible)
	{
	if (!aVisible)
		iFlags|=EInvisible;
	else
		iFlags&=~EInvisible;
	}

inline TBool CEikCommandStack::TStackableCommand::IsBitmapOwner() const
	{return iFlags&EBitmapOwner;}
inline TBool CEikCommandStack::TStackableCommand::IsDimmed() const
	{return iFlags&EDimmed;}
inline TBool CEikCommandStack::TStackableCommand::IsVisible() const
	{return !(iFlags&EInvisible);}


CEikCommandStack* CEikCommandStack::NewL()
	{ // static
	CEikCommandStack* self=new(ELeave) CEikCommandStack;
	return self;
	}

CEikCommandStack::~CEikCommandStack()
	{
	if (iCommands)
		{
		for (TInt ii=iCommands->Count()-1;ii>=0;ii--)
			{
			Delete(ii);
			}
		}
	}

void CEikCommandStack::AddL(TInt aCommandId,const TDesC* aText,CFbsBitmap* aBitmap,CFbsBitmap* aMask)
	{
	CArrayFix<TStackableCommand>* commands=NULL;
	if (iCommands)
		{
		commands=iCommands;
		}
	else
		{
		commands=new(ELeave) CArrayFixFlat<TStackableCommand>(1);
		CleanupStack::PushL(commands);
		}
	HBufC* text=NULL;
	if (aText)
		text=aText->AllocLC();
	TStackableCommand cmd(aCommandId,text,aBitmap,aMask);
	commands->AppendL(cmd);
	if (aText)
		CleanupStack::Pop(); // text
	if (!iCommands)
		{
		iCommands=commands;
		CleanupStack::Pop(); // commands
		}
	}

TBool CEikCommandStack::Remove(TInt aCommandId)
	{
	TBool removed=EFalse;
	if (iCommands)
		{
		const TInt index=Find(aCommandId);
		if (index!=KErrNotFound)
			{
			Delete(index);
			removed=ETrue;
			}
		}
	return removed;
	}

TInt CEikCommandStack::Level() const
	{
	return (iCommands? iCommands->Count() : 0);
	}

CEikCommandStack::TStackableCommand& CEikCommandStack::StackableCommand(TInt aCommandId) const
	{
	// __ASSERT_ALWAYS(iCommands,..........
	// search backwards through the array in case there are two commands with the same id
	TInt loop=iCommands->Count();
	TInt index=KErrNotFound;
	while (--loop>=0)
		{
		if ((*iCommands)[loop].iCommandId==aCommandId)
			{
			index=loop;
			break;
			}
		}
	// __ASSERT_ALWAYS(index!=KErrNotFound...
	return (*iCommands)[index];
	}

CEikCommandStack::TStackableCommand& CEikCommandStack::StackableCommandByPos(TInt aPos) const
	{
	// __ASSERT_ALWAYS(iCommands,..........
	// __ASSERT_ALWAYS(aPos>=0 && aPos<iCommands->Count(),...
	return (*iCommands)[aPos];
	}

TInt CEikCommandStack::Find(TInt aCommandId) const
	{
	// __ASSERT_DEBUG(iCommands...
	const TInt count=iCommands->Count();
	for (TInt ii=0;ii<count;ii++)
		{
		TInt command=(*iCommands)[ii].iCommandId;
		if (command==aCommandId)
			return ii;
		}
	return KErrNotFound;
	}

CEikCommandStack::TStackableCommand CEikCommandStack::Pop()
	// Relinquishes ownership of text and bitmap resources.
	{
	ASSERT(iCommands);
	ASSERT(iCommands->Count());

	TInt top=iCommands->Count()-1;
	TStackableCommand poppedCommand=(*iCommands)[top];
	iCommands->Delete(top);
	if (iCommands->Count()==0)
		{
		delete iCommands;
		iCommands=NULL;
		}

	return poppedCommand;
	}

void CEikCommandStack::Delete(TInt aIndex)
	{
	ASSERT(iCommands);
	
	TStackableCommand cmd=(*iCommands)[aIndex];
	delete cmd.iText;
	if (cmd.IsBitmapOwner())
		{
		delete cmd.iBitmap;
		delete cmd.iMask;
		}
	iCommands->Delete(aIndex);
	if (iCommands->Count()==0)
		{
		delete iCommands;
		iCommands=NULL;
		}
	}

//
// class CEikCommandButtonBase
//

EXPORT_C CEikCommandButtonBase::~CEikCommandButtonBase()
	{
	delete iComponents[0];
	delete iComponents[1];
	delete iCommandStack;
	}

EXPORT_C CEikCommandButtonBase::CEikCommandButtonBase()
	{
	__DECLARE_NAME(_S("CEikCommandButton"));
	LafCommandButtonBase::GetDefaultBorder(iBorder);
    iContext = this;
	SetBehavior(EEikButtonStaysClear);
	SetDisplayContent(EBoth); // default if button contains both
	SetExcessSpace(EShare); // default if button contains both
	SetButtonLayout(EFirstRightSecondLeft); // default if button contains both
	SetNonFocusing();
	}

EXPORT_C void CEikCommandButtonBase::SetTextL(const TDesC& aText,CEikAlignedControl*& aComponent)
	{
	if (aComponent==NULL)
		{
		CEikLabel* label=new(ELeave) CEikLabel;
		CleanupStack::PushL(label);
		label->SetContainerWindowL(*this);
		CleanupStack::Pop(); // label
		label->SetFont(iCmdFlags&EDenseFont? iEikonEnv->DenseFont() : iEikonEnv->LegendFont());
		label->SetAllMarginsTo(LafCommandButtonBase::LabelMargin());
		aComponent=label;
		}
	STATIC_CAST(CEikLabel*,aComponent)->SetTextL(aText);
	}


EXPORT_C void CEikCommandButtonBase::SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask,CEikAlignedControl*& aComponent)
	{
	if (aMain)
		{
		CEikImage* image=new(ELeave) CEikImage;
		CleanupStack::PushL(image);
		image->SetContainerWindowL(*this);
		image->SetPicture(aMain,aMask);
		SetImageAttributes(image);
		if (IsReadyToDraw())
			image->ActivateL(); // won't leave
		if (aComponent)
			{
			const TRect rect(aComponent->Rect());
			if (rect.Width())
				image->SetRect(rect);
			delete aComponent;
			}
		CleanupStack::Pop(); // image
		aComponent=image;
		}
	else if (aComponent)
		{
		delete aComponent;
		aComponent=NULL;
		SetNewComponentExtentL();
		}
	}

EXPORT_C void CEikCommandButtonBase::SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask,CEikAlignedControl*& aComponent)
	{
	CEikImage* image=new(ELeave) CEikImage;
	CleanupStack::PushL(image);
	image->SetContainerWindowL(*this);
	image->CreatePictureFromFileL(aFilename,aMain,aMask);
	SetImageAttributes(image);
	if (IsReadyToDraw())
		image->ActivateL(); // won't leave
	if (aComponent)
		{
		const TRect rect(aComponent->Rect());
		if (rect.Width())
			image->SetRect(rect); // won't leave
		delete aComponent;
		}
	CleanupStack::Pop(); // image
	aComponent=image;
	}

EXPORT_C void CEikCommandButtonBase::StartConstructFromResourceL(TResourceReader& aReader)
	{
	if (!iCommandStack)
		{
		iCommandStack=CEikCommandStack::NewL();
		}

	aReader.ReadInt8();
	const TInt behavior=aReader.ReadInt16();
	SetBehavior(STATIC_CAST(TButtonBehavior,behavior));
	if(behavior==EEikButtonStaysClear)
		{
		SetState(EClear);
		}
	else if(behavior==EEikButtonStaysSet)
		{
		SetState(ESet);
		}
	const TInt layout=aReader.ReadInt16();
	SetButtonLayout(STATIC_CAST(TLayout,(layout&KLayoutAndFontMask)));
	SetExcessSpace(STATIC_CAST(TExcess,(layout&KExcessMask)));
	aReader.ReadTPtrC();  // bubble help text 
	aReader.ReadInt32(); // extension link
	}

EXPORT_C void CEikCommandButtonBase::ConstructLabelFromResourceL(TResourceReader& aReader,TWhichComponent aWhich)
	{
	if (!iCommandStack)
		{
		iCommandStack=CEikCommandStack::NewL();
		}

	TPtrC text=aReader.ReadTPtrC();
	if (text.Length())
		{
		SetTextL(text,((CEikAlignedControl*&)(aWhich==EFirst? iComponents[0] : iComponents[1])));
		CEikLabel* label=STATIC_CAST(CEikLabel*,(aWhich==EFirst? iComponents[0] : iComponents[1]));
		label->SetAllMarginsTo(LafCommandButtonBase::LabelMargin());
		label->SetContainerWindowL(*this);
		}
	}

EXPORT_C void CEikCommandButtonBase::ConstructImageFromResourceL(TResourceReader& aReader,TWhichComponent aWhich)
	{
	if (!iCommandStack)
		{
		iCommandStack=CEikCommandStack::NewL();
		}

	TPtrC bitmapFile=aReader.ReadTPtrC();

	const TInt bitmapId=aReader.ReadInt16();
	const TInt bitmapMask=aReader.ReadInt16();

	if (bitmapId!=-1)
		SetPictureFromFileL(bitmapFile,bitmapId,bitmapMask,(aWhich==EFirst? iComponents[0] : iComponents[1]));
	}

TInt CEikCommandButtonBase::ButFlags() const	
	{
	return iCmdFlags;
	}

EXPORT_C void CEikCommandButtonBase::SetDefault(TBool aDefaultButton)
	{
	iDefault = aDefaultButton;
	}

TBool CEikCommandButtonBase::IsDefault() const
	{
	return iDefault;
	}


EXPORT_C TSize CEikCommandButtonBase::MinimumSize()
	{
	TSize size;
	const TSize comp1Size=(iComponents[0] ? iComponents[0]->MinimumSize() : size);
	const TSize comp2Size=(iComponents[1] ? iComponents[1]->MinimumSize() : size);
	size=TSize(iMargins.iLeft + iMargins.iRight,iMargins.iTop + iMargins.iBottom);
    size+=iBorder.SizeDelta();
	if (iComponents[1]==NULL || ((iCmdFlags&KDisplayContentMask)==EFirstOnly))
		size+=comp1Size;
	else if (iComponents[0]==NULL || ((iCmdFlags&KDisplayContentMask)==ESecondOnly))
		size+=comp2Size;
	else if (LayoutIsVertical())
		{
		size.iHeight+=comp1Size.iHeight+comp2Size.iHeight+LafCommandButtonBase::IntraComponentMargin();
		size.iWidth+=Max(comp1Size.iWidth,comp2Size.iWidth);
		}
	else
		{
		size.iWidth+=comp1Size.iWidth+comp2Size.iWidth+LafCommandButtonBase::IntraComponentMargin();
		size.iHeight+=Max(comp1Size.iHeight,comp2Size.iHeight);
		}
	return size;
	}

EXPORT_C void CEikCommandButtonBase::SetDimmed(TBool aDimmed)
	{
	CCoeControl::SetDimmed(aDimmed);
	if (iComponents[0])
		iComponents[0]->SetDimmed(aDimmed);
	if (iComponents[1])
		iComponents[1]->SetDimmed(aDimmed);
	}

EXPORT_C void CEikCommandButtonBase::SetContainerWindowL(const CCoeControl& aContainer)
	{
	CCoeControl::SetContainerWindowL(aContainer);
	if (iComponents[0])
		iComponents[0]->SetContainerWindowL(aContainer);
	if (iComponents[1])
		iComponents[1]->SetContainerWindowL(aContainer);
	}

CEikCommandStack* CEikCommandButtonBase::CommandStack() const
	{
	return iCommandStack;
	}


EXPORT_C void CEikCommandButtonBase::ActivateL()
	{
	iContext=this;
	if (iComponents[0])
		iComponents[0]->CopyControlContextFrom(this);
	if (iComponents[1])
		iComponents[1]->CopyControlContextFrom(this);
	LafCommandButtonBase::GetBorder(iBorder, DrawState(), iButFlags,*this,IsDefault());
	UpdateComponentAlignment();
	CCoeControl::ActivateL();
	}

EXPORT_C void CEikCommandButtonBase::UpdateComponentAlignment()
	{
	const TInt layout=iCmdFlags&KLayoutAndFontMask;
	if (layout==EFirstBottomSecondTop || layout==EFirstTopSecondBottom)
		{
		if (iComponents[0])
			iComponents[0]->SetAlignment(EHCenterVCenter);
		if (iComponents[1])
			iComponents[1]->SetAlignment(EHCenterVCenter);
		}
	else
		{
		if (iComponents[0])
			{
			if (iComponents[1])
				{
				iComponents[0]->SetAlignment(layout==EFirstLeftSecondRight? EHLeftVCenter : EHRightVCenter);
				iComponents[1]->SetAlignment(layout==EFirstLeftSecondRight? EHRightVCenter : EHLeftVCenter);
				}
			else
				iComponents[0]->SetAlignment(EHCenterVCenter);
			}
		else
			iComponents[1]->SetAlignment(EHCenterVCenter);
		}
	}

EXPORT_C void CEikCommandButtonBase::SetButtonLayout(TLayout aLayout)
	{
    iCmdFlags &= (~KLayoutAndFontMask);
	iCmdFlags |= aLayout;
	}

EXPORT_C void CEikCommandButtonBase::SetExcessSpace(TExcess aExcess)
	{
	iCmdFlags&=~KExcessMask;
	iCmdFlags|=aExcess;
	}

EXPORT_C void CEikCommandButtonBase::SetDisplayContent(TDisplayContent aContent)
	{
	iCmdFlags &= (~KDisplayContentMask);
	iCmdFlags |= aContent;
	}

EXPORT_C TInt CEikCommandButtonBase::CountComponentControls() const
	{
	__ASSERT_DEBUG((iComponents[0]||iComponents[1]),Panic(EEikPanicButtonHasNoComponent));
	if (iComponents[0] && iComponents[1] && ((iCmdFlags&KDisplayContentMask)==EBoth))
		return 2;
	return 1;
	}

EXPORT_C CCoeControl* CEikCommandButtonBase::ComponentControl(TInt aIndex) const
	{
	__ASSERT_DEBUG((iComponents[0]||iComponents[1]),Panic(EEikPanicButtonHasNoComponent));
	if (iComponents[1]==NULL || ((iCmdFlags&KDisplayContentMask)==EFirstOnly))
		return iComponents[0];
	if (iComponents[0]==NULL || ((iCmdFlags&KDisplayContentMask)==ESecondOnly))
		return iComponents[1];
	if (aIndex==0)
		return iComponents[0];
	return iComponents[1];
	}

EXPORT_C void CEikCommandButtonBase::SizeChanged()
	{
	__ASSERT_DEBUG((iComponents[0]||iComponents[1]),Panic(EEikPanicButtonHasNoComponent));
    TRect innerRect=iBorder.InnerRect(Rect());
	innerRect.SetRect(innerRect.iTl.iX+iMargins.iLeft,innerRect.iTl.iY+iMargins.iTop,
						innerRect.iBr.iX-iMargins.iRight,innerRect.iBr.iY-iMargins.iBottom);
	innerRect.Move(iDrawOffset,iDrawOffset);
	if (iComponents[1]==NULL || ((iCmdFlags&KDisplayContentMask)==EFirstOnly))
		iComponents[0]->SetRect(innerRect);
	else if (iComponents[0]==NULL || ((iCmdFlags&KDisplayContentMask)==ESecondOnly))
		iComponents[1]->SetRect(innerRect);
	else
		SetComponentExtents(innerRect);
	}

EXPORT_C void CEikCommandButtonBase::LayoutComponents()
	{
	SizeChanged();
	}

EXPORT_C void CEikCommandButtonBase::StateChanged()
	{
	TInt drawState = DrawState();
	if (iBorder.HasBorder())
		LafCommandButtonBase::GetBorder(iBorder, drawState, iButFlags,*this,IsDefault());
	const TInt offset=LafCommandButtonBase::ComponentOffset(drawState, iButFlags);

	if (offset==iDrawOffset)
		return;

	const TInt deltaOffset = offset-iDrawOffset;
	const TPoint delta(deltaOffset,deltaOffset);
	
	if (iComponents[0])
		iComponents[0]->SetPosition(iComponents[0]->Position()+delta);
	
	if (iComponents[1])
		iComponents[1]->SetPosition(iComponents[1]->Position()+delta);
	
	iDrawOffset=offset;
	}

/**
 * Prepares the basic graphic contents according to the the type of command
 * button, e.g. pen and brush colors.
 *
 * @since ER5U 
 */
EXPORT_C void CEikCommandButtonBase::PrepareContext(CWindowGc& aGc) const
	{
	LafCommandButtonBase::PrepareContext(aGc,DrawState(),iEikonEnv->LafEnv(),*this);
	}

EXPORT_C void CEikCommandButtonBase::Draw(const TRect& /*aRect*/) const
	{
	LafCommandButtonBase::Draw(iEikonEnv->LafEnv(),*this,SystemGc(),
								iBorder,iDrawOffset,DrawState(),
								iMargins,IsDefault());
    }


EXPORT_C TKeyResponse CEikCommandButtonBase::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	if(aKeyEvent.iCode==EKeyEnter && aType==EEventKey)
		{
		Animate();
		return EKeyWasConsumed;
		}
	else
		return EKeyWasNotConsumed;
	}

EXPORT_C void CEikCommandButtonBase::FocusChanged(TDrawNow aDrawNow)
	{
	if(aDrawNow && !IsNonFocusing())
		DrawNow();
	}

void CEikCommandButtonBase::SetComponentExtents(const TRect& aRect)
	{
	TInt8 margin = (TInt8)(LafCommandButtonBase::IntraComponentMargin()>>1);
	TSize comp1Size=iComponents[0]->MinimumSize();
	TSize comp2Size=iComponents[1]->MinimumSize();

	const TInt excess=(LayoutIsVertical()? 
								aRect.Size().iHeight-(comp1Size+comp2Size).iHeight - LafCommandButtonBase::IntraComponentMargin():
								aRect.Size().iWidth-(comp1Size+comp2Size).iWidth - LafCommandButtonBase::IntraComponentMargin());
	switch (iCmdFlags&KExcessMask)
		{
	case EToFirst:
		if (LayoutIsVertical())
			comp1Size.iHeight+=excess;
		else
			comp1Size.iWidth+=excess;
		break;
	case EToSecond:
		if (LayoutIsVertical())
			comp2Size.iHeight+=excess;
		else
			comp2Size.iWidth+=excess;
		break;
	case EShare:
		if (LayoutIsVertical())
			{
			comp2Size.iHeight+=excess>>1;
			comp1Size.iHeight+=excess-(excess>>1);
			}
		else
			{
			comp2Size.iWidth+=excess>>1;
			comp1Size.iWidth+=excess-(excess>>1);
			}
		break;
		}
	if (LayoutIsVertical())
		{
		comp2Size.iHeight+=margin;
		comp1Size.iHeight+=margin;
		}
	else
		{
		comp2Size.iWidth+=margin;
		comp1Size.iWidth+=margin;
		}
	TRect comp1Rect=aRect;
	TRect comp2Rect=aRect;
    switch (iCmdFlags&KLayoutMask)
        {
    case EFirstTopSecondBottom:
		comp2Rect.iTl.iY+=comp1Size.iHeight;
		comp1Rect.iBr.iY=comp2Rect.iTl.iY;
		iComponents[0]->iMargin.iBottom=margin;
		iComponents[1]->iMargin.iTop=margin;
        break;
    case EFirstBottomSecondTop:
		comp1Rect.iTl.iY+=comp2Size.iHeight;
		comp2Rect.iBr.iY=comp1Rect.iTl.iY;
		iComponents[0]->iMargin.iTop=margin;
		iComponents[1]->iMargin.iBottom=margin;
        break;
    case EFirstLeftSecondRight:
		comp2Rect.iTl.iX+=comp1Size.iWidth;
		comp1Rect.iBr.iX=comp2Rect.iTl.iX;
		iComponents[0]->iMargin.iRight=margin;
		iComponents[1]->iMargin.iLeft=margin;
        break;
    case EFirstRightSecondLeft:
		comp1Rect.iTl.iX+=comp2Size.iWidth;
		comp2Rect.iBr.iX=comp1Rect.iTl.iX;
		iComponents[0]->iMargin.iLeft=margin;
		iComponents[1]->iMargin.iRight=margin;
        break;
		}
	iComponents[0]->SetRect(comp1Rect); // won't leave
	iComponents[1]->SetRect(comp2Rect); // won't leave
	}

void CEikCommandButtonBase::SetImageAttributes(CEikImage* aImage)
	{
//	aImage->SetAlignment(EHCenterVCenter);
	aImage->SetAllMarginsTo(LafCommandButtonBase::ImageMargin());
	}

void CEikCommandButtonBase::SetNewComponentExtentL()
// only ever called when the image changes
	{
    TRect innerRect=iBorder.InnerRect(Rect());
	innerRect.SetRect(innerRect.iTl.iX+iMargins.iLeft,innerRect.iTl.iY+iMargins.iTop,
					innerRect.iBr.iX-iMargins.iRight,innerRect.iBr.iY-iMargins.iBottom);
	innerRect.Move(iDrawOffset,iDrawOffset);
	if (!iComponents[1] || (iCmdFlags&KDisplayContentMask==EFirstOnly))
		iComponents[0]->SetRect(innerRect);
	else if (!iComponents[0] || (iCmdFlags&KDisplayContentMask==ESecondOnly))
		iComponents[1]->SetRect(innerRect);
	else
		SetComponentExtents(innerRect);
	}

TBool CEikCommandButtonBase::LayoutIsVertical() const
	{ // !! change back to TLayout values to simplify this routine again
	TInt layout=iCmdFlags&KLayoutMask;
	return (layout==EFirstBottomSecondTop || layout==EFirstTopSecondBottom);
	}

inline TInt CEikCommandButtonBase::Behavior() const
	{return iButFlags&(EEikButtonStaysClear|EEikButtonStaysSet|EEikButtonLatches|EEikButtonReportsOnPointerDown);}

inline void CEikCommandButtonBase::CheckCreateCommandStackL()
	{
	if (!iCommandStack)
		{
		iCommandStack=CEikCommandStack::NewL();
		}
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikCommandButtonBase::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
	{
	CEikButtonBase::GetColorUseListL(aColorUseList);
	LafCommandButtonBase::GetColorUseListL(aColorUseList);
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikCommandButtonBase::HandleResourceChange(TInt aType)
	{
	CEikButtonBase::HandleResourceChange(aType);
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
EXPORT_C void CEikCommandButtonBase::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikCommandButtonBase::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KLitEikCmdButBsCtlStart, "<CEikCommandButtonBase>");
	_LIT(KLitEikCmdButBsCtlEnd, "<\\CEikCommandButtonBase>");
	_LIT(KLitEikCmdButBsMrg,"<iMargins>");
	_LIT(KLitEikCmdButBsMrgEnd,"<\\iMargins>");
    _LIT(KLitEikCmdButBsCmdFls,"<iCmdFlags>");
	_LIT(KLitEikCmdButBsCmdFlsEnd,"<\\iCmdFlags>");
	_LIT(KLitEikCmdButBsDrwOff,"<iDrawOffset>");
	_LIT(KLitEikCmdButBsDrwOffEnd,"<\\iDrawOffset>");
	_LIT(KLitEikCmdButBsCmdStck,"<iCommandStack>");
	_LIT(KLitEikCmdButBsCmdStckEnd,"<\\iCommandStack>");
	_LIT(KLitEikCmdButBsDef,"<iDefault>");
	_LIT(KLitEikCmdButBsDefEnd,"<\\iDefault>");

	aWriteStream << KLitEikCmdButBsCtlStart;
	aWriteStream << KLitEikCmdButBsMrg;
	aWriteStream.WriteInt8L(iMargins.iLeft);
	aWriteStream.WriteInt8L(iMargins.iRight);
	aWriteStream.WriteInt8L(iMargins.iTop);
	aWriteStream.WriteInt8L(iMargins.iBottom);
	aWriteStream << KLitEikCmdButBsMrgEnd;
    aWriteStream << KLitEikCmdButBsCmdFls;
	aWriteStream.WriteInt32L(iCmdFlags);
	aWriteStream << KLitEikCmdButBsCmdFlsEnd;
	aWriteStream << KLitEikCmdButBsDrwOff;
	aWriteStream.WriteInt32L(iDrawOffset);
	aWriteStream << KLitEikCmdButBsDrwOffEnd;
	aWriteStream << KLitEikCmdButBsCmdStck;
	const TInt top=(iCommandStack ? iCommandStack->Level() : 0);
	for(TInt level=0; level<top ; level++)
		{
		const CEikCommandStack::TStackableCommand& cmd=iCommandStack->StackableCommandByPos(level);
		aWriteStream.WriteInt32L(cmd.iCommandId);
		if(cmd.iText)
			aWriteStream << cmd.iText;
		if(cmd.iBitmap)
			aWriteStream << cmd.iBitmap;
		if(cmd.iMask)
			aWriteStream << cmd.iBitmap;
		}
	aWriteStream << KLitEikCmdButBsCmdStckEnd;
	aWriteStream << KLitEikCmdButBsDef;
	aWriteStream.WriteInt32L(iDefault);
	aWriteStream << KLitEikCmdButBsDefEnd;
	CEikButtonBase::WriteInternalStateL(aWriteStream);
	aWriteStream << KLitEikCmdButBsCtlEnd;	
	}
#endif

EXPORT_C void CEikCommandButtonBase::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikButtonBase::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikCommandButtonBase::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikCommandButtonBase::Reserved_2()
	{}
EXPORT_C void CEikCommandButtonBase::Reserved_3()
	{}
EXPORT_C void CEikCommandButtonBase::Reserved_4()
	{}

//
// class CEikCommandButton
//


EXPORT_C CEikCommandButton::CEikCommandButton()
	{
	iMargins = LafCommandButton::Margins();
	}

EXPORT_C CEikCommandButton::~CEikCommandButton()
	{}

EXPORT_C void CEikCommandButton::SetTextL(const TDesC& aText)
	{
	CEikCommandButtonBase::SetTextL(aText,iComponents[0]);
	}

EXPORT_C void CEikCommandButton::SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask)
	{
	CEikCommandButtonBase::SetPictureL(aMain,aMask,iComponents[1]);
	}

EXPORT_C void CEikCommandButton::SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask)
	{
	CEikCommandButtonBase::SetPictureFromFileL(aFilename,aMain,aMask,iComponents[1]);
	}

EXPORT_C CEikLabel* CEikCommandButton::Label() const
	{
	return STATIC_CAST(CEikLabel*,iComponents[0]);
	}

EXPORT_C CEikImage* CEikCommandButton::Picture() const
	{
	return STATIC_CAST(CEikImage*,iComponents[1]);
	}

EXPORT_C void CEikCommandButton::SetButtonLayout(TLayout aLayout)
	{
	CEikCommandButtonBase::SetButtonLayout(((CEikCommandButtonBase::TLayout)aLayout));
	}

EXPORT_C void CEikCommandButton::SetExcessSpace(TExcess aExcess)
	{
	CEikCommandButtonBase::SetExcessSpace(((CEikCommandButtonBase::TExcess)aExcess));
	}

EXPORT_C void CEikCommandButton::SetDisplayContent(TDisplayContent aContent)
	{
	CEikCommandButtonBase::SetDisplayContent(((CEikCommandButtonBase::TDisplayContent)aContent));
	}

EXPORT_C void CEikCommandButton::ConstructFromResourceL(TResourceReader& aReader)
	{
	StartConstructFromResourceL(aReader);
	ConstructLabelFromResourceL(aReader,EFirst);
	ConstructImageFromResourceL(aReader,ESecond);
	if (!(iComponents[0] || iComponents[1]))
		{
		SetTextL(KNullDesC);
		CEikLabel* label=static_cast<CEikLabel*>(iComponents[0]);
		label->SetAllMarginsTo(LafCommandButtonBase::LabelMargin());
		label->SetContainerWindowL(*this);
		}
	}

EXPORT_C void CEikCommandButton::UpdateComponentAlignment()
	{
	const TInt layout=iCmdFlags&KLayoutAndFontMask;
	if (layout==EFirstBottomSecondTop || layout==EFirstTopSecondBottom)
		{
		if (iComponents[0])
			iComponents[0]->SetAlignment(EHCenterVCenter);
		if (iComponents[1])
			iComponents[1]->SetAlignment(EHCenterVCenter);
		}
	else
		{
		if (iComponents[0])
			{
			if (iComponents[1])
				{
				iComponents[0]->SetAlignment(EHLeftVCenter); // always align text on the left
				iComponents[1]->SetAlignment(layout==EFirstLeftSecondRight? EHRightVCenter : EHLeftVCenter);
				}
			else
				iComponents[0]->SetAlignment(EHCenterVCenter);
			}
		else
			iComponents[1]->SetAlignment(EHCenterVCenter);
		}
	}

/**
 * Sets aText as the text in the command button.  Sets aBitmap and aMask as the bitmap and mask of the command button.
 *
 * @since App-Framework_6.1
 */
EXPORT_C void CEikCommandButton::SetCommandL(TInt /*aCommandId*/,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)
	{
	// !!! no rollback
	if (aText && Label()->BufferReserveLength())
		UpdateLabelReserveLengthL(aText);
	SetTextL(*aText);
	SetPictureL(aBitmap,aMask);
	}

void CEikCommandButton::UpdateLabelReserveLengthL(const TDesC* aText)
	{
	TInt length=(aText? aText->Length() : 0);
	CEikLabel* label=Label();
	length=Max(length,label->Text()->Length());
	if (length>label->BufferReserveLength())
		label->SetBufferReserveLengthL(length);
	}
	
EXPORT_C void CEikCommandButton::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikCommandButtonBase::HandlePointerEventL(aPointerEvent); 
    }	

EXPORT_C void* CEikCommandButton::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

struct SLabelCleanup
	{
	CEikLabel* iLabel;
	TDesC* iText;
	};
LOCAL_C void CleanupLabel(TAny* aPtr)
	{
	SLabelCleanup& temp=*(SLabelCleanup*)aPtr;
	temp.iLabel->SetTextL(*(temp.iText)); // won't leave as SetBufferReserveLengthL has been called
	}

struct SStackCleanup
	{
	CEikCommandStack* iStack;
	TInt iCommandId;
	};
LOCAL_C void CleanupCommandStack(TAny* aPtr)
	{
	SStackCleanup& temp=*(SStackCleanup*)aPtr;
	temp.iStack->Remove(temp.iCommandId);
	}

/**
 * Sets the command button to respond to aCommandId.  Sets aText as the text in the command button.
 * Sets aBitmap and aMask as the bitmap and mask of the command button.  The previous command can be
 * restored on the command button by a subsequent call to PopCommandFromStack(). 
 *
 * @since App-Framework_6.1
 */
EXPORT_C void CEikCommandButton::AddCommandToStackL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)
	{
	//if (Extension()==NULL)
	//	InitExtensionL();
	CEikImage* image=Picture();
	CFbsBitmap* bitmap=(image? CONST_CAST(CFbsBitmap*,image->Bitmap()) : NULL);
	CFbsBitmap* mask=(image? CONST_CAST(CFbsBitmap*,image->Mask()) : NULL);
	CheckCreateCommandStackL();
	CEikCommandStack* stack=CommandStack();
	stack->AddL(aCommandId,Label()->Text(),bitmap,mask);
	SStackCleanup stackCleanup;
	stackCleanup.iStack=stack;
	stackCleanup.iCommandId=aCommandId;
	CleanupStack::PushL(TCleanupItem(CleanupCommandStack,&stackCleanup));
	CEikLabel* label=Label();
	SLabelCleanup labelCleanup;
	labelCleanup.iLabel=label;
	labelCleanup.iText=stack->StackableCommand(aCommandId).iText;
	UpdateLabelReserveLengthL(aText);
	TPtrC text;
	if (aText)
		text.Set(*aText);
	SetTextL(text); // won't leave as SetBufferReserveLengthL has been called
	CleanupStack::PushL(TCleanupItem(CleanupLabel,&labelCleanup));
	if (image)
		image->SetPictureOwnedExternally(ETrue);
	SetPictureL(aBitmap,aMask); // !!! may delete a CEikImage => rollback impossible
	if (aBitmap)
		Picture()->SetPictureOwnedExternally(EFalse);
	CleanupStack::Pop(2); // imageCleanup, stackCleanup
	CEikCommandStack::TStackableCommand& cmd=stack->StackableCommand(aCommandId);
	cmd.SetBitmapOwner(ETrue);
	cmd.SetDimmed(IsDimmed());
	cmd.SetVisible(IsVisible());
	SetDimmed(EFalse);
	MakeVisible(ETrue);
	}

/**
 * Removes the command which has aCommandId from the stack of commmands.
 *
 * @since App-Framework_6.1
 */
EXPORT_C TBool CEikCommandButton::RemoveCommandFromStack(TInt aCommandId)
	{
	// __ASSERT_DEBUG(Extension()==NULL,.....
	CEikCommandStack* stack=CommandStack();
	return stack->Remove(aCommandId);
	}

/**
 * Pops the current command from the stack, if there is one.  Restores the command button to
 * respond to the previous commandId before the last push to the stack.  The text, bitmap and mask
 * are also restored to the previous values (before the last push was made).
 *
 * @since App-Framework_6.1
 */
EXPORT_C TInt CEikCommandButton::PopCommandFromStack()
	{
	CEikCommandStack* stack=CommandStack();
	__ASSERT_DEBUG(stack,Panic(EEikPanicCommandStackIsNull));
	CEikCommandStack::TStackableCommand cmd=stack->Pop();

	TPtrC text;
	if (cmd.iText)
		{
		text.Set(*(cmd.iText));
		}
	SetTextL(text); // won't leave as SetBufferReserveLengthL has been called
	delete cmd.iText;
	TRAP_IGNORE(SetPictureL(cmd.iBitmap,cmd.iMask));
	SetDimmed(cmd.IsDimmed());
	MakeVisible(cmd.IsVisible());

	return cmd.iCommandId;
	}


//
// class CEikTwoPictureCommandButton
//

const TInt KPictureOwnedExternally	=0x10;


EXPORT_C CEikTwoPictureCommandButton::CEikTwoPictureCommandButton()
	{
	LafTwoPictureCommandButton::GetDefaultBorder(iBorder);
	iMargins = LafTwoPictureCommandButton::Margins();
	}

EXPORT_C CEikTwoPictureCommandButton::~CEikTwoPictureCommandButton()
	{
	if(IsSecondPictureOwnedExternally())
		return;
    if (iSecondBitmap != iSecondMaskBitmap)
    	delete CONST_CAST(CFbsBitmap*,iSecondBitmap);
	delete CONST_CAST(CFbsBitmap*,iSecondMaskBitmap);
	}

/**
 * Sets the text for the button label to aText.
 */
EXPORT_C void CEikTwoPictureCommandButton::SetTextL(const TDesC& aText)
	{
	CEikCommandButtonBase::SetTextL(aText,iComponents[0]);
	}

/**
 * Sets both the pictures for the command button. The first picture is created from the image bitmap aMain
 * and the mask bitmap aMask. The optional second picture is created from the image bitmap aSecondMain and mask
 * bitmap aSecondMask.
 */
EXPORT_C void CEikTwoPictureCommandButton::SetTwoPicturesL(const CFbsBitmap* aMain,const CFbsBitmap* aMask,const CFbsBitmap* aSecondMain,const CFbsBitmap* aSecondMask)
	{
	CEikCommandButtonBase::SetPictureL(aMain,aMask,iComponents[1]);
	SetSecondPicture(aSecondMain,aSecondMask);
	}

/**
 * Sets the first picture for the button by loading the image bitmap identified by aMain and the mask bitmap
 * identified by aMask from the bitmap file named aFilename.
 */
EXPORT_C void CEikTwoPictureCommandButton::SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask)
	{
	CEikCommandButtonBase::SetPictureFromFileL(aFilename,aMain,aMask,iComponents[1]);
	}

/**
 * Sets the second picture for the button by loading the image bitmap identified by aMain and the mask bitmap
 * identified by aMask from the bitmap file named aFilename.
 */
EXPORT_C void CEikTwoPictureCommandButton::SetSecondPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask)
	{
	CFbsBitmap* secondBitmap = iEikonEnv->CreateBitmapL(aFilename, aMain);
	//CFbsBitmap* secondBitmap = AknIconUtils::CreateIconL( aFilename, aMain );
	CFbsBitmap* secondMask = NULL;
	if(aMask!=-1)
		secondMask = iEikonEnv->CreateBitmapL(aFilename, aMask);
		//secondMask = AknIconUtils::CreateIconL( aFileName, aMask );
	SetSecondPicture(secondBitmap, secondMask);
	}

/**
 * Returns a pointer to the image control component of the button which displays the button pictures.
 */
EXPORT_C CEikImage* CEikTwoPictureCommandButton::Picture() const
	{
	return STATIC_CAST(CEikImage*,iComponents[1]);
	}

/**
 * Sets the second picture for the button using aSecondMain as the image bitmap and aSecondMask as the mask bitmap.
 * Takes ownership of the bitmaps unless the second picture has been set to be owned externally.
 */
EXPORT_C void CEikTwoPictureCommandButton::SetSecondPicture(const CFbsBitmap* aSecondMain,const CFbsBitmap* aSecondMask)
	{
	if (!IsSecondPictureOwnedExternally())
		{
		if (iSecondBitmap!=iSecondMaskBitmap)
    		delete const_cast<CFbsBitmap*>(iSecondBitmap);
		delete const_cast<CFbsBitmap*>(iSecondMaskBitmap);
		}
	iSecondBitmap=aSecondMain;
	iSecondMaskBitmap=aSecondMask;
	}

void CEikTwoPictureCommandButton::SwapPictures(CEikImage* aImage)
	{
	if(iSecondBitmap)	// only swap if the second bitmap exists
		{
		const CFbsBitmap* tempBitmap = aImage->Bitmap();
		const CFbsBitmap* tempMaskBitmap = aImage->Mask();
		TBool oldImageOwnership = aImage->IsPictureOwnedExternally();

		aImage->SetPictureOwnedExternally(ETrue);
		aImage->SetPicture(iSecondBitmap,iSecondMaskBitmap);
		aImage->SetPictureOwnedExternally(IsSecondPictureOwnedExternally());

		SetSecondPictureOwnedExternally(oldImageOwnership);
		iSecondBitmap=tempBitmap;
		iSecondMaskBitmap=tempMaskBitmap;

		SetImageAttributes(aImage);
		if (IsReadyToDraw())
			{
			TRAP_IGNORE(aImage->ActivateL());
			}
		}
	}

EXPORT_C void CEikTwoPictureCommandButton::ConstructFromResourceL(TResourceReader& aReader)
	{
	StartConstructFromResourceL(aReader);
	ConstructLabelFromResourceL(aReader,EFirst);
	ConstructImagesFromResourceL(aReader,ESecond);
	}

EXPORT_C void CEikTwoPictureCommandButton::ConstructImagesFromResourceL(TResourceReader& aReader,TWhichComponent /*aWhich*/)
	{
	CheckCreateCommandStackL();
	TPtrC bitmapFile=aReader.ReadTPtrC();

	const TInt bitmapId=aReader.ReadInt16();
	const TInt bitmapMask=aReader.ReadInt16();
	if (bitmapId!=-1)
		SetPictureFromFileL(bitmapFile,bitmapId,bitmapMask);

	const TInt bitmapSecondId=aReader.ReadInt16();
	const TInt bitmapSecondMask=aReader.ReadInt16();
	if (bitmapSecondId!=-1)
		SetSecondPictureFromFileL(bitmapFile,bitmapSecondId,bitmapSecondMask);
	}

EXPORT_C void CEikTwoPictureCommandButton::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc=SystemGc();
	PrepareContext(gc);
	CEikCommandButtonBase::Draw(Rect());
    }

EXPORT_C void CEikTwoPictureCommandButton::StateChanged()
	{
	CEikImage* component = STATIC_CAST(CEikImage*, iComponents[1]);
	if (component == NULL)
		return;
	TInt state = DrawState();
	if ( (Behavior() == EEikButtonLatches) )
		{
		switch (state)
			{
		case EDrawClearPressed:
		case EDrawSetPressed:
			SwapPictures(component);
			break;
		default:
			break;
			}
		}
	else
		{
		switch (state)
			{
		case EDrawClearPressed:
		case EDrawClear:
			SwapPictures(component);
			break;
		default:
			break;
			}
		}
	if( iBorder.HasBorder() )
		CEikCommandButtonBase::StateChanged();
    }
    
EXPORT_C void CEikTwoPictureCommandButton::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikCommandButtonBase::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void* CEikTwoPictureCommandButton::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikTwoPictureCommandButton::PrepareContext(CWindowGc& aGc) const
	{
	if (iBorder.HasBorder())
		LafCommandButtonBase::PrepareContext(aGc,DrawState(),iEikonEnv->LafEnv(),*this);
	else
		aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	}

/**
 * Sets the bitmaps used for the second button picture to be owned externally if aOwnership is ETrue.
 */
EXPORT_C void CEikTwoPictureCommandButton::SetSecondPictureOwnedExternally(TBool aOwnership)
	{
	if (aOwnership)
		iPictureFlags|=KPictureOwnedExternally;
	else
		iPictureFlags&=~KPictureOwnedExternally;
	}

/**
 * Returns ETrue if the bitmaps for the second button picture are owned externally.
 */
EXPORT_C TBool CEikTwoPictureCommandButton::IsSecondPictureOwnedExternally()
	{
    if (iPictureFlags&KPictureOwnedExternally)
		return ETrue;
	else
		return EFalse;
	}

EXPORT_C void CEikTwoPictureCommandButton::ActivateL()
	{
	__ASSERT_DEBUG(iSecondBitmap, Panic(EEikPanicButtonHasNoComponent));
	if (iBorder.HasBorder())
		CEikCommandButtonBase::ActivateL();
	else
		{
		if (iComponents[0])
			iComponents[0]->CopyControlContextFrom(this);
		if (iComponents[1])
			iComponents[1]->CopyControlContextFrom(this);
		UpdateComponentAlignment();
		CCoeControl::ActivateL();
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
EXPORT_C void CEikTwoPictureCommandButton::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikTwoPictureCommandButton::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KLitEikTwPcCmdButCtlStart, "<CEikTwoPictureCommandButton>");
	_LIT(KLitEikTwPcCmdButCtlEnd, "<\\CEikTwoPictureCommandButton>");
	_LIT(KLitEikTwPcCmdButScndBmp,"<iSecondBitmap>");
	_LIT(KLitEikTwPcCmdButScndBmpEnd,"<\\iSecondBitmap>");
	_LIT(KLitEikTwPcCmdButScndMsk,"<iSecondMaskBitmap>");
	_LIT(KLitEikTwPcCmdButScndMskEnd,"<\\iSecondMaskBitmap>");
	_LIT(KLitEikTwPcCmdButPcFlgs,"<iPictureFlags>");
	_LIT(KLitEikTwPcCmdButPcFlgsEnd,"<\\iPictureFlags>");
	
	aWriteStream << KLitEikTwPcCmdButCtlStart;
	aWriteStream << KLitEikTwPcCmdButScndBmp;
	aWriteStream << *iSecondBitmap;
	aWriteStream << KLitEikTwPcCmdButScndBmpEnd;
	aWriteStream << KLitEikTwPcCmdButScndMsk;
	aWriteStream << *iSecondMaskBitmap;
	aWriteStream << KLitEikTwPcCmdButScndMskEnd;
	aWriteStream << KLitEikTwPcCmdButPcFlgs;
	aWriteStream.WriteInt32L(iPictureFlags);
	aWriteStream << KLitEikTwPcCmdButPcFlgsEnd;
	CEikCommandButtonBase::WriteInternalStateL(aWriteStream);
	aWriteStream << KLitEikTwPcCmdButCtlEnd;
	}
#endif

//
// class CEikInverterCommandButton
//

#define KBaseColor		KRgbDarkGray
#define KInverterColor	KRgbBlack


EXPORT_C CEikInverterCommandButton::CEikInverterCommandButton()
	{
	iMargins = LafInverterCommandButton::Margins();
	}

EXPORT_C CEikInverterCommandButton::~CEikInverterCommandButton()
	{}

EXPORT_C void CEikInverterCommandButton::PrepareContext(CWindowGc& aGc) const
	{
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	TRgb penColor;
	TRgb brushColor;
	switch (DrawState())
		{
	case EDrawSet:
		penColor = KBaseColor;
		brushColor= KInverterColor;
		break;
	case EDrawClearPressed:
		penColor= KBaseColor;
		brushColor= KInverterColor;
		break;
	case EDrawClear:
		penColor= KInverterColor;
		brushColor=KBaseColor;
		break;
	case EDrawSetPressed:
		penColor= KInverterColor;
		brushColor= KBaseColor;
		break;
	default:
		break;
		}
	aGc.SetPenColor(penColor);
	aGc.SetBrushColor(brushColor);
	}
	
EXPORT_C void CEikInverterCommandButton::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikCommandButton::HandlePointerEventL(aPointerEvent); 
    }	

EXPORT_C void* CEikInverterCommandButton::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikInverterCommandButton::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KLitEikInvCmdButCtlStart, "<CEikTwoPictureCommandButton>");
	_LIT(KLitEikInvCmdButCtlEnd, "<\\CEikTwoPictureCommandButton>");
	_LIT(KLitEikInvCmdButFlg,"<iFlag>");
	_LIT(KLitEikInvCmdButFlgEnd,"<\\iFlag>");
	aWriteStream << KLitEikInvCmdButCtlStart;
	aWriteStream << KLitEikInvCmdButFlg;
	aWriteStream.WriteInt32L(iFlag);
	aWriteStream << KLitEikInvCmdButFlgEnd;
	CEikCommandButton::WriteInternalStateL(aWriteStream);
	aWriteStream << KLitEikInvCmdButCtlEnd;
	}

//
// class CEikTextButton
//

EXPORT_C CEikTextButton::CEikTextButton()
	{
	iMargins = LafTextButton::Margins();
	}

EXPORT_C CEikTextButton::~CEikTextButton()
	{}

EXPORT_C void CEikTextButton::SetTextL(const TDesC& aText,TWhichComponent aWhich)
	{
	CEikCommandButtonBase::SetTextL(aText,(aWhich==EFirst? iComponents[0] : iComponents[1]));
	}

EXPORT_C CEikLabel* CEikTextButton::Label(TWhichComponent aWhich) const
	{
	return STATIC_CAST(CEikLabel*,(aWhich==EFirst? iComponents[0] : iComponents[1]));
	}

EXPORT_C void CEikTextButton::ConstructFromResourceL(TResourceReader& aReader)
	{
	StartConstructFromResourceL(aReader);
	ConstructLabelFromResourceL(aReader,EFirst);
	ConstructLabelFromResourceL(aReader,ESecond);
	}

EXPORT_C void CEikTextButton::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikCommandButtonBase::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikTextButton::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

//
// class CEikBitmapButton
//

EXPORT_C CEikBitmapButton::CEikBitmapButton()
	{
	iMargins = LafBitmapButton::Margins();
	}

EXPORT_C CEikBitmapButton::~CEikBitmapButton()
	{}

EXPORT_C void CEikBitmapButton::SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask,TWhichComponent aWhich)
	{
	CEikCommandButtonBase::SetPictureL(aMain,aMask,(aWhich==EFirst? iComponents[0] : iComponents[1]));
	}

EXPORT_C void CEikBitmapButton::SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask,TWhichComponent aWhich)
	{
	CEikCommandButtonBase::SetPictureFromFileL(aFilename,aMain,aMask,(aWhich==EFirst? iComponents[0] : iComponents[1]));
	}

EXPORT_C CEikImage* CEikBitmapButton::Picture(TWhichComponent aWhich) const
	{
	return STATIC_CAST(CEikImage*,(aWhich==EFirst? iComponents[0] : iComponents[1]));
	}

EXPORT_C void CEikBitmapButton::ConstructFromResourceL(TResourceReader& aReader)
	{
	StartConstructFromResourceL(aReader);
	ConstructImageFromResourceL(aReader,EFirst);
	ConstructImageFromResourceL(aReader,ESecond);
	}

EXPORT_C void CEikBitmapButton::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikCommandButtonBase::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikBitmapButton::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }
