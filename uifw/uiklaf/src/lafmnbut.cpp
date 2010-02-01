/*
* Copyright (c) 2000 Nokia Corporation and/or its subsidiary(-ies).
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


#include "lafmnbut.h"

/**
 * Returns ETrue if the menu button should report on a button down event. Otherwise the button
 * should report on a button up event.
 *
 * @since App-Framework_6.1
 */
EXPORT_C TBool LafMenuButton::IsReportingOnButtonDown()
	{
	return ETrue;
	}

/**
 * Gets the position, aMenuPosition, of the popup menu launched by the button using the rectangle
 * of the button aButtonRect, the size of the menu aMenuSize and the device screen size
 * aScreenSize for reference.
 *
 * @since App-Framework_6.1
 */
EXPORT_C void LafMenuButton::GetMenuPosition(TPoint& aMenuPosition, const TRect& aButtonRect,
											 const TSize& aMenuSize, const TSize& aScreenSize)
	{
	aMenuPosition=aButtonRect.iTl;
	// try to position popup to right of button, then below, then left and lastly above
	TSize buttonSize(aButtonRect.Size());
	if (aMenuPosition.iX+buttonSize.iWidth+aMenuSize.iWidth<=aScreenSize.iWidth)
		aMenuPosition.iX+=buttonSize.iWidth;
	else if (aMenuPosition.iY+buttonSize.iHeight+aMenuSize.iHeight<=aScreenSize.iHeight)
		aMenuPosition.iY+=buttonSize.iHeight;
	else if (aMenuPosition.iX-aMenuSize.iWidth>=0)
		aMenuPosition.iX-=aMenuSize.iWidth;
	else if (aMenuPosition.iY-aMenuSize.iHeight>=0)
		aMenuPosition.iY-=aMenuSize.iHeight;
	else
		{
		aMenuPosition.iX+=buttonSize.iWidth;
		aMenuPosition.iY+=buttonSize.iHeight;
		}
	}
