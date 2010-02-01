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
#include <eiklbbut.h>
#include <eikcmbut.h>
#include <eikmnbut.h>
#include <eiklabel.h>
#include <eikenv.h>
#include <eikpanic.h>
#include <uikon.hrh>
#include "laflbbut.h"

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikLabeledButton::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikLabeledButton::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KEikLitLbButCtlSt,"<CEikLabeledButton>");
	_LIT(KEikLitLbButCtlEnd,"<\\CEikLabeledButton>");
	_LIT(KEikLitLbButCtlHkey, "<iHotKeyCode>");
	_LIT(KEikLitLbButCtlHkeyEnd, "<\\iHotKeyCode>");
	_LIT(KEikLitLbButCtlFlags, "<iLButFlags>");
	_LIT(KEikLitLbButCtlFlagsEnd, "<\\iLButFlags>");

	aWriteStream << KEikLitLbButCtlSt;
	aWriteStream << KEikLitLbButCtlHkey;
	aWriteStream.WriteInt32L(iHotKeyCode);
	aWriteStream << KEikLitLbButCtlHkeyEnd;
	aWriteStream << KEikLitLbButCtlFlags;
	aWriteStream.WriteInt32L(iLButFlags);
	aWriteStream << KEikLitLbButCtlFlagsEnd;
	CCoeControl::WriteInternalStateL(aWriteStream);
	aWriteStream << KEikLitLbButCtlEnd;
	}
#endif

EXPORT_C CEikLabeledButton::CEikLabeledButton()
	{
	SetComponentsToInheritVisibility(ETrue);
	}

EXPORT_C CEikLabeledButton::~CEikLabeledButton()
	{
	delete iButton;
	delete iLabel;
	}

EXPORT_C void CEikLabeledButton::ConstructL(CEikCommandButtonBase* aButton,TInt aHotKeyCode,TInt aFlags)
	{
	__ASSERT_DEBUG(aButton,Panic(EEikPanicNullPointer));
	iButton=aButton;
	iButton->SetObserver(this);
	iHotKeyCode=aHotKeyCode;
	iLButFlags=aFlags;
	CreateLabelL();
	if(iLButFlags&EEikLabeledButtonIsDefault)
		iButton->SetDefault(ETrue);
	}

EXPORT_C void CEikLabeledButton::ConstructFromResourceL(TResourceReader& aReader)
	{
	const TInt type=aReader.ReadInt16();
	switch (type)
		{
	case EEikCtCommandButton:
		iButton=new(ELeave) CEikCommandButton;
		break;
	case EEikCtMenuButton:
		iButton=new(ELeave) CEikMenuButton;
		break;
	case EEikCtTextButton:
		iButton=new(ELeave) CEikTextButton;
		break;
	case EEikCtBitmapButton:
		iButton=new(ELeave) CEikBitmapButton;
		break;
	default:
		Panic(EEikPanicLabeledButtonInvalidButtonType);
		}
	iButton->SetContainerWindowL(*this);
	iButton->ConstructFromResourceL(aReader);
	iButton->SetObserver(this);
	iHotKeyCode=aReader.ReadInt32();
	iLButFlags=aReader.ReadInt8();
	CreateLabelL();
	if(iLButFlags&EEikLabeledButtonIsDefault)
		iButton->SetDefault(ETrue);
	}

EXPORT_C CEikCommandButtonBase* CEikLabeledButton::Button() const
	{
	return iButton;
	}

EXPORT_C CEikLabel* CEikLabeledButton::Label() const
	{
	return iLabel;
	}

EXPORT_C TInt CEikLabeledButton::HotKeyCode() const
	{
	return iHotKeyCode;
	}

EXPORT_C TBool CEikLabeledButton::ShowsHotKey() const
	{
	return (LafLabeledButton::ShowHotKey() ? iLButFlags&EShowHotKey: EFalse);
	}

EXPORT_C TBool CEikLabeledButton::PlainHotKey() const
	{
	return iLButFlags&EPlainHotKey;
	}

EXPORT_C TKeyResponse CEikLabeledButton::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	if (!IsDimmed() && aType==EEventKey)
		{
		TBool consumed=EFalse;
		if ((aKeyEvent.iModifiers & EAllStdModifiers) == EModifierCtrl)
			consumed=(aKeyEvent.iCode==(TUint)iHotKeyCode && !(aKeyEvent.iModifiers&EModifierPureKeycode));
		else
			{
			switch (iHotKeyCode)
				{
			case EEikBidCancel:
				consumed=(aKeyEvent.iCode==EKeyEscape);
				break;
			case EEikBidOk:
				consumed=(aKeyEvent.iCode==EKeyEnter);
				break;
// AKNLAF start
			case EEikBidSelect:
				consumed=(aKeyEvent.iCode==EKeyEnter);
				break;
// AKNLAF end
			case EEikBidTab:
				consumed=(aKeyEvent.iCode==EKeyTab);
				break;
			case EEikBidDelete:
				consumed=(aKeyEvent.iCode==EKeyBackspace);
				break;
			case EEikBidSpace:
				consumed=(aKeyEvent.iCode==EKeySpace);
				break;
			default:
				{
				consumed=(iLButFlags&EPlainHotKey && TCharF(aKeyEvent.iCode)==TCharF((TUint)iHotKeyCode));
				break;
				}
				}
			}
		if (consumed)
			{
			iButton->Animate();
			ReportEventL(MCoeControlObserver::EEventStateChanged);
			return EKeyWasConsumed;
			}
		}
	return EKeyWasNotConsumed;
	}

EXPORT_C TSize CEikLabeledButton::MinimumSize()
	{
	TSize size=iButton->MinimumSize();
	//size.iHeight=Max(KMinButtonHeight,size.iHeight);
	size.iHeight=Max(LafLabeledButton::MinimumButtonHeight(),size.iHeight);
	const TSize labelSize=(ShowsHotKey()? iLabel->MinimumSize()+TSize(LafLabeledButton::HorizontalLabelMargin(),LafLabeledButton::VerticalLabelMargin()) : TSize());
	size.iWidth=Max(size.iWidth,labelSize.iWidth);
	size.iHeight+=labelSize.iHeight;
	return size;
	}

EXPORT_C void CEikLabeledButton::SetContainerWindowL(const CCoeControl& aContainer)
	{
	CCoeControl::SetContainerWindowL(aContainer);
	if (iButton)
		iButton->SetContainerWindowL(aContainer);
	if (iLabel)
		iLabel->SetContainerWindowL(aContainer);
	CopyControlContextFrom(&aContainer);
	}

EXPORT_C void CEikLabeledButton::SetDimmed(TBool aDimmed)
	{
	CCoeControl::SetDimmed(aDimmed);
	if (iButton)
		iButton->SetDimmed(aDimmed);
	if (iLabel)
		iLabel->SetDimmed(aDimmed);
	}

EXPORT_C TCoeInputCapabilities CEikLabeledButton::InputCapabilities() const
	{
	return TCoeInputCapabilities(LafLabeledButton::InputCapabilities());
	}

EXPORT_C void CEikLabeledButton::Animate()
	{
	if (iButton)
		iButton->Animate();
	}

EXPORT_C void CEikLabeledButton::UpdateHotKey(TInt aKeyCode,TFlags aFlags)
	{
	iHotKeyCode=aKeyCode;
	iLButFlags=aFlags;
	TRAPD(err,UpdateHotKeyL());
	if (err)
		{
		TPtrC text(KNullDesC);
		__ASSERT_DEBUG_NO_LEAVE(iLabel->SetTextL(text)); // won't leave as we've already called SetBufferReserveLength during construction
		}
	}

TInt CEikLabeledButton::CountComponentControls() const
	{
	return 2;
	}

CCoeControl* CEikLabeledButton::ComponentControl(TInt aIndex) const
	{
	if (aIndex==0)
		return iButton;
	else if (aIndex==1)
		return iLabel;
	return NULL;
	}

void CEikLabeledButton::SizeChanged()
	{
	//const TSize butSize(iSize.iWidth,Max(KMinButtonHeight,iButton->MinimumSize().iHeight));
	const TSize butSize(iSize.iWidth,Max(LafLabeledButton::MinimumButtonHeight(),iButton->MinimumSize().iHeight));
	iButton->SetExtent(iPosition,butSize);
	iLabel->SetExtent(TPoint(iPosition.iX,iPosition.iY+butSize.iHeight),
						TSize(iSize.iWidth,iSize.iHeight-butSize.iHeight));
	}

void CEikLabeledButton::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent aEventType)
	{
	ReportEventL(aEventType);
	}

void CEikLabeledButton::CreateLabelL()
	{
	iLabel=new(ELeave) CEikLabel;
	iLabel->SetContainerWindowL(*this);
	iLabel->CopyControlContextFrom(this);
	iLabel->SetBufferReserveLengthL(LafLabeledButton::MaxLabelTextLengthInChars());
	UpdateHotKeyL();
	iLabel->SetFont(iEikonEnv->AnnotationFont());
	iLabel->SetAlignment(LafLabeledButton::LabelAlignment());
	}

void CEikLabeledButton::UpdateHotKeyL()
	{
	TPtrC text;
	if (iHotKeyCode<=EEikBidCancel && iHotKeyCode>=EEikBidSpace)
		{
		if (ShowsHotKey())
			text.Set(iEikonEnv->KeyPressLabel(EEikBidCancel-iHotKeyCode));
		}
	else
		{
		if (/*iHotKeyCode && */ShowsHotKey())
			{
			if (PlainHotKey())
				{
				TBuf<1> buf;
				buf.Append(TChar(iHotKeyCode));
				text.Set(buf);
				}
			else
				{
				TBuf<10> defaultText = iEikonEnv->KeyPressLabel((EEikBidCancel)-(EEikBidSpace)+1);
				const TInt len=defaultText.Length();
				defaultText[len-1]=(TInt8)iHotKeyCode;
				text.Set(defaultText);
				}
			}
		if (!PlainHotKey())
			{
			if (iHotKeyCode>='A' && iHotKeyCode<='Z')
				iHotKeyCode-='A'-1;
			else
				iHotKeyCode-='a'-1;
			}
		}
	iLabel->SetTextL(text);
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikLabeledButton::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
	{
	CCoeControl::GetColorUseListL(aColorUseList);	
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikLabeledButton::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	}

EXPORT_C void CEikLabeledButton::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikLabeledButton::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

void CEikLabeledButton::Reserved_2()
	{}
