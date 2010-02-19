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


#include "eikkwin.h"

EXPORT_C CEikKeyWindow::CEikKeyWindow()
	{
	__DECLARE_NAME(_S("CEikKeyWindow"));
	}

EXPORT_C CEikKeyWindow::~CEikKeyWindow()
	{
	if (DrawableWindow())
		Window().RemoveAllKeyRects();
	}

EXPORT_C void CEikKeyWindow::ConstructL(const TPoint& aPoint,const TSize& aSize,TInt aDeadSpaceAtStart, TInt aDeadSpaceAtEnd,TInt aScanCode,TInt aNumOfButtons,TType aType,RWindowGroup* aParent)
	{
    CreateWindowL(aParent);
	SetExtent(aPoint,aSize);
	TSize unit=aSize;
	TPoint tl;
	// dead space adjustments
	TInt* pBreadth=(aType==EHorizontal)? &(unit.iHeight) : &(unit.iWidth);
	(*pBreadth)-=(aDeadSpaceAtStart+aDeadSpaceAtEnd);
	TInt* pAdjust=(aType==EHorizontal)? &(tl.iY) : &(tl.iX);
	(*pAdjust)+=aDeadSpaceAtStart;
	//
	TInt* pMove=(&tl.iX);
	TInt* pLength=(&unit.iWidth);
	if (aType==EVertical)
		{
		pMove=(&tl.iY);
		pLength=(&unit.iHeight);
		}
	TInt length=(*pLength);
	TInt remainder=length%aNumOfButtons;
	length/=aNumOfButtons;
	*pLength=length;
	for (TInt ii=0; ii<aNumOfButtons; ii++)
		{
		User::LeaveIfError(Window().AddKeyRect(TRect(tl,unit),aScanCode++,ETrue));
		*pMove+=length;
		if (remainder)
			{
			(*pMove)++;
			remainder--;
			}
		}
	Window().SetShadowDisabled(ETrue);
	Window().Activate();
	}

EXPORT_C void CEikKeyWindow::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikKeyWindow::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }
