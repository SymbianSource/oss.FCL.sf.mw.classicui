/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <w32std.h>
#include "laflbi.h"
#include "laflbx.h"
#include "lafpublc.h"
#include "LAFSTD.H"

const TInt KLafListItemDrawerDefaultMarkColumnWidth = 10;
const TInt KLafListItemDrawerDefaultPostMarkColumnSpace = 2;

EXPORT_C LafListItemDrawer::TLidColors::TLidColors(TRgb aTextColor,
												TRgb aBackColor,
												TRgb aHighlightedTextColor,
												TRgb aHighlightedBackColor,
												TRgb aDimmedTextColor,
												TRgb aDimmedBackColor,
												TRgb aMarkColor)
	:iTextColor(aTextColor), iBackColor(aBackColor),iHighlightedTextColor(aHighlightedTextColor)
	,iHighlightedBackColor(aHighlightedBackColor),iDimmedTextColor(aDimmedTextColor)
	,iDimmedBackColor(aDimmedBackColor), iMarkColor(aMarkColor)
	{}
						

EXPORT_C void LafListItemDrawer::DrawFrame(CWindowGc& aGc,const TRect& aRect,TInt aFlags,const TLidColors& aColors)
	{ // static
	if(!(aFlags&SLafListBox::EEmphasized))
		{
		if(aFlags&SLafListBox::ECurrent)
			{
			aGc.SetPenStyle(CGraphicsContext::ESolidPen);
			aGc.SetPenColor(aColors.iTextColor);
			aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
			aGc.DrawRect(aRect);
			}
		}
	}

/**
 * Returns a constant value according to aConstantType.
 * @internal
 */
EXPORT_C TInt LafListItemDrawer::Constant(TConstantType aConstant)
	{//static
	TInt retValue = 0;
	switch (aConstant)
		{
	case EDefaultMarkColumnWidth:
		retValue = KLafListItemDrawerDefaultMarkColumnWidth;
		break;
	case EDefaultPostMarkColumnSpace:
		retValue = KLafListItemDrawerDefaultPostMarkColumnSpace;
		break;
	default:
		__ASSERT_DEBUG(EFalse, Panic(ELafPanicConstantNotKnown));
		break;
		}
	return retValue;
	}

EXPORT_C void LafTextListItemDrawer::DrawNormalText(const TDesC& aDes,const CFont& /*aFont*/,CWindowGc& aGc,
										 const TRect& aItemTextRect,const TInt aBaseLineOffset,
										 const CGraphicsContext::TTextAlign aAlign)
	{//static
	aGc.DrawText(aDes,aItemTextRect,aBaseLineOffset,aAlign,LafListBox::InnerGutter());
	}

EXPORT_C TInt LafTextListItemDrawer::PrepareItemAttribute(TInt /*aFlags*/,TBool aItemIsCurrent,
												TBool aItemIsSelected,TBool aViewIsEmphasized)
	{//static
	TInt attribute=0;
	if(aItemIsCurrent)
		attribute|=SLafListBox::ECurrent;
	if(aViewIsEmphasized)
		attribute|=SLafListBox::EEmphasized;
	if(aItemIsSelected)
		attribute|=SLafListBox::ESelected;
	return attribute;
	}
