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

			  
#include <e32base.h>
#include <e32keys.h>

#include <bamatch.h>
#include <badesca.h>
#include <barsread.h>

#include <eiktxlbx.h>
#include <eiklbv.h>
#include <eiklbi.h>
#include <eiktxlbm.h>
#include <eikenv.h>
#include <eikpanic.h>
#include <w32std.h> 
#include "laflbx.h"
#include "laftxlbx.h"
#include "akntrace.h"

EXPORT_C CEikTextListBox::CEikTextListBox()
    {
    }

EXPORT_C CEikTextListBox::~CEikTextListBox()
    {
    }

EXPORT_C void CEikTextListBox::CreateItemDrawerL()
	{
	_AKNTRACE_FUNC_ENTER;
	const CFont* font=LafTextListBox::Font(iEikonEnv->LafEnv());
	iItemDrawer = new(ELeave) CTextListItemDrawer((CTextListBoxModel*)iModel,font);
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CEikTextListBox::ConstructFromResourceL(TResourceReader& aReader)
    {
    _AKNTRACE_FUNC_ENTER;
	RestoreCommonListBoxPropertiesL(aReader);
	iRequiredCellCharWidth = aReader.ReadInt16();

    TInt array_id = aReader.ReadInt32();
    if (array_id)
		{
		CDesCArray* desArray = iCoeEnv->ReadDesCArrayResourceL(array_id);
		CleanupStack::PushL(desArray);
		iModel = new(ELeave) CTextListBoxModel;
		((CTextListBoxModel*)iModel)->ConstructL(desArray);
		CleanupStack::Pop();
		}
	else
		{
		iModel = new(ELeave) CTextListBoxModel;
		((CTextListBoxModel*)iModel)->ConstructL();
		}
	CreateItemDrawerL();
	((CTextListItemDrawer*)iItemDrawer)->SetCellWidthInChars(iRequiredCellCharWidth);
	CreateViewL();
	UpdateViewColors();
	UpdateItemDrawerColors();
	_AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikTextListBox::ConstructL(const CCoeControl* aParent, TInt aFlags)
	{
	_AKNTRACE_FUNC_ENTER;
	iModel = new(ELeave) CTextListBoxModel;
	((CTextListBoxModel*)iModel)->ConstructL();
	CreateItemDrawerL();
	CEikListBox::ConstructL(aParent,aFlags);
	_AKNTRACE_FUNC_EXIT;
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
EXPORT_C void CEikTextListBox::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikTextListBox::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KLitEikTxLbxCtlStart, "<CEikTextListBox>");
	_LIT(KLitEikTxLbxCtlEnd, "<\\CEikTextListBox>");
	_LIT(KLitEikTxLbxReqWdth,"<iRequiredCellCharWidth>");
	_LIT(KLitEikTxLbxReqWdthEnd,"<\\iRequiredCellCharWidth>");

	aWriteStream << KLitEikTxLbxCtlStart;
	aWriteStream << KLitEikTxLbxReqWdth;
	aWriteStream.WriteInt32L(iRequiredCellCharWidth);
	aWriteStream << KLitEikTxLbxReqWdthEnd;
	CEikListBox::WriteInternalStateL(aWriteStream);
	aWriteStream << KLitEikTxLbxCtlEnd;
	}
#endif

EXPORT_C CTextListBoxModel* CEikTextListBox::Model() const
	{
	return (CTextListBoxModel*) iModel;
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikTextListBox::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
	{
	CEikListBox::GetColorUseListL(aColorUseList);
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikTextListBox::HandleResourceChange(TInt aType)
	{
	CEikListBox::HandleResourceChange(aType);
	}

EXPORT_C void CEikTextListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikListBox::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikTextListBox::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikTextListBox::CEikListBox_Reserved()
	{}

//
// class CEikSnakingTextListBox
//

EXPORT_C CEikSnakingTextListBox::CEikSnakingTextListBox()
    {
    }

EXPORT_C CEikSnakingTextListBox::~CEikSnakingTextListBox()
    {
    }

EXPORT_C void CEikSnakingTextListBox::ConstructL(const CCoeControl* aParent, TInt aFlags)
	{
	_AKNTRACE_FUNC_ENTER;
	iModel = new(ELeave) CTextListBoxModel;
	((CTextListBoxModel*)iModel)->ConstructL();
	const CFont* font=LafSnakingTextListBox::Font(iEikonEnv->LafEnv());
	iItemDrawer = new(ELeave) CTextListItemDrawer((CTextListBoxModel*)iModel, font);
	CEikListBox::ConstructL(aParent, aFlags);
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C CTextListBoxModel* CEikSnakingTextListBox::Model() const
	{
	return (CTextListBoxModel*) iModel;
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikSnakingTextListBox::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
	{
	CEikSnakingListBox::GetColorUseListL(aColorUseList);
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikSnakingTextListBox::HandleResourceChange(TInt aType)
	{
	CEikSnakingListBox::HandleResourceChange(aType);
	}

EXPORT_C void CEikSnakingTextListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikSnakingListBox::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikSnakingTextListBox::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }
