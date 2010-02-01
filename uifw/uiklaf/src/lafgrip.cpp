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


#include <gdi.h>
#include <coedef.h>
#include "lafgrip.h"


void TLafGrip::Draw(CGraphicsContext& aGc, const TRect& aRect) const
// Draw the grip (centred) in the given TRect using the given Gc (presumed active)
	{
	const TBool horizontal=((iData&EOrientationMask)==EHorizontal);
	const TInt width=aRect.Width();
	const TInt height=aRect.Height();
	TInt gripLength=width;
	TInt lineLength=height;
	if (horizontal)
		{
		gripLength=height;
		lineLength=width;
		}
	TInt numOfLines=0;
	while (gripLength>=ELineWidth)
		{
		++numOfLines;
		gripLength-=(ELineWidth+ESpaceBetweenLines);
		}
	const TInt offset=(gripLength+ESpaceBetweenLines)/2;
	const TPoint posOne=((horizontal)? TPoint(0,1): TPoint(1,0));
	const TPoint negOne=((horizontal)? TPoint(0,-1): TPoint(-1,0));
	const TPoint posLine=((horizontal)? TPoint(lineLength-1,0): TPoint(0,lineLength-1));
	const TPoint negLine=((horizontal)? TPoint(-(lineLength-1),0): TPoint(0,-(lineLength-1)));
	const TPoint gripToGrip=((horizontal)? TPoint(0, ESpaceBetweenLines+ELineWidth): TPoint(ESpaceBetweenLines+ELineWidth, 0));
	TPoint ref=aRect.iTl+((horizontal)? TPoint(0,ELineWidth+offset) : TPoint(ELineWidth+offset,0));
	aGc.SetPenStyle(CGraphicsContext::ESolidPen);
	for (TInt i=0; i<numOfLines;i++)
		{
		aGc.MoveTo(ref-posOne);
		aGc.SetPenColor(KRgbWhite);
		aGc.DrawLineBy(negOne);
		aGc.DrawLineBy(posLine);
		aGc.SetPenColor(KRgbBlack);
		aGc.DrawLineBy(posOne);
		aGc.DrawLineBy(negLine);
		ref+=gripToGrip;
		}
	}
