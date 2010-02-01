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


#include <eikmover.h>
#include <barsread.h>
#include <eikenv.h>

#include <gulcolor.h>

const TInt KEikMoverMargin=3; 
const TInt KEikMoverTextPadding=10;
const TInt KEikMoverMinLineLength=10;

enum TEikMoverFlags
	{
	EEikMoverActive		=0x01,
	EEikMoverPressed	=0x02
	};

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikMover::GetColorUseListL(CArrayFix<TCoeColorUse>& /*aColorUseList*/) const
	{
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikMover::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	}

EXPORT_C CEikMover::~CEikMover()
    {
    delete(iText);
    }

EXPORT_C CEikMover::CEikMover()
	{
	__DECLARE_NAME(_S("CEikMover"));
	SetNonFocusing();
	iFont=iEikonEnv->NormalFont();
	iTitleLeftMargin = KEikMoverMargin;
	}

EXPORT_C void CEikMover::SetContainerWindowL(const CCoeControl& aContainer)
	{
	CCoeControl::SetContainerWindowL(aContainer);
	iParentControl=&((CCoeControl&)aContainer);
	}

EXPORT_C void CEikMover::SetTitleLeftMargin(TInt aLeftMargin)
	{
	iTitleLeftMargin = aLeftMargin;
	}

EXPORT_C void CEikMover::SetText(HBufC* aText)
    {
	if (iText!=aText)
		delete iText;
    iText=aText;
    }

EXPORT_C void CEikMover::SetTextL(const TDesC& aText)
    {
    HBufC* tmp=aText.AllocL();
    delete(iText);
    iText=tmp;
    }

EXPORT_C void CEikMover::ConstructFromResourceL(TResourceReader& aReader)
    {
    iText=aReader.ReadHBufCL();
    }

EXPORT_C void CEikMover::SetActive(TBool aActive)
	{
	if (aActive)
		iMoverFlags|=EEikMoverActive;
	else
		iMoverFlags&=(~(EEikMoverActive|EEikMoverPressed));
	}

EXPORT_C TBool CEikMover::Active() const
	{
	return iMoverFlags&EEikMoverActive;
	}

EXPORT_C void CEikMover::SetFont(const CFont* aFont)
	{
	// if pointer is null use the title font
	iFont=(aFont)? aFont : iEikonEnv->NormalFont();
	}

EXPORT_C TSize CEikMover::MinimumSize()
    {
	TSize size;
    size.iWidth=2*KEikMoverMargin+2*KEikMoverTextPadding+2*KEikMoverMinLineLength;
	if (iText)
    	size.iWidth+=iFont->TextWidthInPixels(*iText);
    size.iHeight=iFont->HeightInPixels()+2*KEikMoverMargin;
	return size;
    }

EXPORT_C void CEikMover::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc=SystemGc();
    TRect rect=Rect();
    const TRgb bgColor=iEikonEnv->ControlColor((iMoverFlags&EEikMoverPressed? 
                                                EColorDialogTitlePressed : EColorDialogTitle),*this);
    const TRgb textColor=iEikonEnv->ControlColor((iMoverFlags&EEikMoverPressed?
                                                  EColorDialogTitleTextPressed : EColorDialogTitleText),*this);
    gc.SetBrushColor(bgColor);
    gc.Clear(rect);
    gc.SetPenColor(KRgbGray);
    gc.DrawLine(TPoint(rect.iTl.iX,rect.iBr.iY-1),TPoint(rect.iBr.iX,rect.iBr.iY-1));
    
    // TInt textWidth=iText? iFont->TextWidthInPixels(*iText): 0;
    TRect textRect=rect;
    textRect.iTl.iX += iTitleLeftMargin;
    //textRect.Shrink((Size().iWidth-(textWidth+2*KEikMoverMargin))/2,0);
    // draw the text
    gc.SetPenColor(textColor);
    gc.SetBrushStyle(CGraphicsContext::ENullBrush);
    gc.UseFont(iFont);
    const TInt ascent=iFont->AscentInPixels();
    const TInt fontHeight=iFont->HeightInPixels();
    const TInt offset=(textRect.Height()+1)/2+(ascent-((fontHeight+1)/2));
    gc.DrawText(iText? TPtrC(*iText): TPtrC(),textRect,offset,CGraphicsContext::ELeft);
    gc.DiscardFont();
    }

EXPORT_C void* CEikMover::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }   

EXPORT_C void CEikMover::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
	if (!Active())
		return;
    TBool recordPos=ETrue;
    TPoint pos=aPointerEvent.iParentPosition; // !! should be relative to screen not to parent (see below...)
    TPointerEvent::TType type=aPointerEvent.iType;
    if (type==TPointerEvent::EButton1Down)
		{
		iMoverFlags|=EEikMoverPressed;
		DrawNow();
		}
    else
        {
        TRect screenRect(TPoint(0,0),iEikonEnv->ScreenDevice()->SizeInPixels());
        screenRect.Shrink(2,2);
        if (!screenRect.Contains(pos)) // !! this assumes parent window is screen (see above...)
            recordPos=EFalse;
        else
            {
            TPoint offset=pos-iPointerDownPos;
            if (offset.iX || offset.iY)
                {
                TPoint origin=Window().Position();
				if (iParentControl)
					iParentControl->SetPosition(origin+offset);
                }
            }
        if (type==TPointerEvent::EButton1Up)
			{
			iMoverFlags&=(~EEikMoverPressed);
			DrawNow();
			}
        }
    if (recordPos)
        iPointerDownPos=pos;
    }

//
// Reserved functions from CCoeControl
//

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikMover::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikMover::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CCoeControl::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CEikMover::Reserved_2()
	{
	}


