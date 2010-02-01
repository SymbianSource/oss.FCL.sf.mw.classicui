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


#include <eikbctrl.h>

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikBorderedControl::GetColorUseListL(CArrayFix<TCoeColorUse>& /*aColorUseList*/) const
	{
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikBorderedControl::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	}

EXPORT_C CEikBorderedControl::CEikBorderedControl()
	{}

EXPORT_C CEikBorderedControl::CEikBorderedControl(const TGulBorder& aBorder)
	: iBorder(aBorder)
	{}

EXPORT_C TBool CEikBorderedControl::HasBorder() const
	{
	return iBorder.HasBorder();
	}

EXPORT_C void CEikBorderedControl::SetAdjacent(TInt aAdjacent)
	{
	iBorder.SetAdjacent(aAdjacent);
	}

/**
 * Overloaded method which sets the border type to aBorderType for a value from the enum TGulBorder::TBorderType.
 */
EXPORT_C void CEikBorderedControl::SetBorder(TGulBorder::TBorderType aBorderType)
	{
	iBorder=TGulBorder(aBorderType);
	}

/**
  *	Sets the border type to aBorderType. Any one of the values from the enums TGulBorder::TBorderType
  * or TGulBorder::TLogicalType specifies a valid border type. Custom border types can be created by selecting 
  * <ul>
  * <li> one value from each of the enums TGulBorder::T3DStyle and TGulBorder::TConstructionStyle,
  * <li> at most one value from the enums TGulBorder::TOutlineStyle and TGulBorder::TInlineStyle,
  * <li> at least one value from the enums TGulBorder::TThickness and TGulBorder::TRounding
  * </ul>
  * and ORing these values together.
  *
  * @since Uikon1.2
  */
EXPORT_C void CEikBorderedControl::SetBorder(TInt aBorderType)
	{
	iBorder=TGulBorder(aBorderType);
	}

EXPORT_C TGulBorder CEikBorderedControl::Border() const
	{
	return iBorder;
	}

EXPORT_C void CEikBorderedControl::Draw(const TRect& /*aRect*/) const
	{
	TRect rect=Rect();
	CGraphicsContext& gc=SystemGc();
	iBorder.Draw(gc,rect);
	if (IsBlank())
		{
		TRect innerRect=iBorder.InnerRect(rect);
		gc.SetPenStyle(CGraphicsContext::ENullPen);
		gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    	gc.DrawRect(innerRect);
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
EXPORT_C void CEikBorderedControl::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikBorderedControl::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KEikLitBrdrCtlSt,"<CEikBorderedControl>");
	_LIT(KEikLitBrdrCtlEnd,"<\\CEikBorderedControl>");
	_LIT(KEikLitBrdrCtlBorder,"<iBorder>");
	_LIT(KEikLitBrdrCtlBorderEnd,"<\\iBorder>");

	aWriteStream << KEikLitBrdrCtlSt;
	aWriteStream << KEikLitBrdrCtlBorder;
	aWriteStream.WriteInt32L(iBorder.Type());
	aWriteStream << KEikLitBrdrCtlBorderEnd;
	CCoeControl::WriteInternalStateL(aWriteStream);
	aWriteStream << KEikLitBrdrCtlEnd;
	}
#endif

EXPORT_C void CEikBorderedControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikBorderedControl::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }
