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

#include <e32std.h>
#include <w32std.h>
#include "laflbd.h"

EXPORT_C void LafListBoxData::DrawSearchText(const TRect& aItemTextRect,
							CWindowGc& aGc,const CFont& aItemFont,const CFont& aBoldFont,
							const TDesC& aItemText,const TInt aStrPos,const TInt aStrLen,
							const TInt aBaseLineOffset,const CGraphicsContext::TTextAlign aAlign)
	{//static
	const TPtrC textHead = TPtrC(aItemText.Left(aStrPos));
	const TPtrC searchStr= TPtrC(aItemText.Mid(aStrPos,aStrLen));
	const TPtrC textTail = TPtrC(aItemText.Right(aItemText.Length()-aStrPos-aStrLen));

	const TInt headLen = aItemFont.TextWidthInPixels(textHead);
	const TInt strLen  = aBoldFont.TextWidthInPixels(searchStr);
	const TInt tailLen = aItemFont.TextWidthInPixels(textTail);

	// adjust text alignment by drawing empty rect before text if necessary
	TRect rect = aItemTextRect;
	const TInt textLen = headLen + strLen + tailLen;
	TInt emptyLen = rect.Width() - textLen;
	if ((aAlign==CGraphicsContext::ELeft) || (emptyLen<=0))
		emptyLen = 0;
	else
		{
		if (aAlign==CGraphicsContext::ECenter) emptyLen = (emptyLen>>1);
		}

	// draw item head up to search string
	rect.iBr.iX = rect.iTl.iX + emptyLen + headLen;
	aGc.DrawText( textHead, rect, aBaseLineOffset, CGraphicsContext::ERight );

	// draw item tail after the search string
	rect.iTl.iX = rect.iBr.iX + strLen;
	rect.iBr.iX = aItemTextRect.iBr.iX;
	aGc.DrawText( textTail, rect, aBaseLineOffset );

    // change font and set undelining on
	aGc.UseFont(&aBoldFont);
    aGc.SetUnderlineStyle(EUnderlineOn);

	// draw the search string part of the item with different font
	rect.iBr.iX = rect.iTl.iX;
	rect.iTl.iX = rect.iBr.iX - strLen;
	aGc.DrawText( searchStr, rect, aBaseLineOffset );
	}

