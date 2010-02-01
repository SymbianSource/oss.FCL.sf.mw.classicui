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
#include <eikspace.h>
#include <eikon.hrh>


EXPORT_C CEikSpacer::CEikSpacer()
	: iColor(KRgbWhite), iClear(EFalse)
    {}

EXPORT_C CEikSpacer::CEikSpacer(TInt aWidth,TInt aHeight,TRgb aColor)
    {
	iSize.iWidth=aWidth;
	iSize.iHeight=aHeight;
	iColor=aColor;
	}

EXPORT_C CEikSpacer::~CEikSpacer()
    {
    }

void CEikSpacer::ConstructFromResourceL(TResourceReader& aReader)
    {
    iSize.iWidth=aReader.ReadInt16();
    iSize.iHeight=aReader.ReadInt16();
	const TInt color=aReader.ReadInt32();
	switch (color)
		{
	case EEikSpacerWhite:
		iColor=KRgbWhite;
		break;
	case EEikSpacerDitheredGray:
		iColor=KRgbDitheredLightGray;
		break;
	case EEikSpacerGray:
		iColor=KRgbGray;
		break;
	case EEikSpacerDarkGray:
		iColor=KRgbDarkGray;
		break;
	case EEikSpacerBlack:
		iColor=KRgbBlack;
		break;
	case EEikSpacerClear:
		iClear=ETrue;
		break;
		}
    }

void CEikSpacer::Draw(const TRect& aRect) const
	{
	CWindowGc& gc=SystemGc();
	gc.SetPenStyle(CGraphicsContext::ENullPen);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	if (!iClear)
		gc.SetBrushColor(iColor);
	gc.DrawRect(aRect);
	}

EXPORT_C void CEikSpacer::SetWidth(TInt aWidth)
	{
    iSize.iWidth=aWidth;
	}

EXPORT_C void CEikSpacer::SetHeight(TInt aHeight)
	{
    iSize.iHeight=aHeight;
	}

EXPORT_C void CEikSpacer::SetColor(TRgb aColor)
	{
	iColor=aColor;
	}

EXPORT_C void CEikSpacer::SetClear(TBool aClear)
	{
	iClear=aClear;
	}
	
EXPORT_C void CEikSpacer::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikSpacer::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }	
