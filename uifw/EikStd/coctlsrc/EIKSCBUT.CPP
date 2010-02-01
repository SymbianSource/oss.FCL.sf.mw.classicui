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


#pragma warning( disable : 4710 )	// function not expanded

#include <gulutil.h>
#include <gulcolor.h>
#include "LAFSCBUT.H"

#include <eiksfont.h>
#include <eikenv.h>
#include <eikscbut.h>

// const TInt KEikScrollButtonBorderWidth=1;
// const TInt KTypeOfScrollBarMask = 0x000f;


EXPORT_C CEikScrollButton::~CEikScrollButton()
	{
	}

EXPORT_C CEikScrollButton::CEikScrollButton(CEikScrollButton::TType /*aType*/)
	{
	}

EXPORT_C CEikScrollButton::TType CEikScrollButton::Type() const
	{
	return ENudgeUp;
	}

EXPORT_C void CEikScrollButton::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikButtonBase::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikScrollButton::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

//
// CEikArrowHeadScrollButton
//

EXPORT_C CEikArrowHeadScrollButton* CEikArrowHeadScrollButton::NewL(const CCoeControl* /*aParent*/, TType /*aType*/)
	{
	return 0;
	}

CEikArrowHeadScrollButton::CEikArrowHeadScrollButton() 
: CEikScrollButton(ENudgeUp)
	{
	}

