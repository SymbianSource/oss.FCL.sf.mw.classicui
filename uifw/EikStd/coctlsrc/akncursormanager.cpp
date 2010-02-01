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
#include <aknedsts.h>
#include <aknedformaccessor.h>
#include <coecntrl.h>
#include <coemop.h>
#include <frmtlay.h>
#include <frmtview.h>
#include <tagma.h>

#include "akncursormanager.h"

CAknCursorManager* CAknCursorManager::NewL(CAknEdwinState* aEdwinState)
	{
	CAknCursorManager* self = new (ELeave) CAknCursorManager(aEdwinState);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

CAknCursorManager::~CAknCursorManager()
	{
	}


TTmDocPosSpec CAknCursorManager::DocPos() const
	{
	TTmDocPosSpec docPos = TTmDocPosSpec();
	if (TextView())
		{
		TTmDocPos rawDocPos;
		TextView()->GetCursorPos(rawDocPos);
		docPos.iPos = rawDocPos.iPos;
		TTmDocPosSpec::TType docPosType = rawDocPos.iLeadingEdge ? TTmDocPosSpec::ELeading : TTmDocPosSpec::ETrailing;
		docPos.iType = docPosType;
		}
	return docPos;
	}

void CAknCursorManager::SetDocPosL(const TTmDocPosSpec& aDocPos)
	{
	if (TextView())
		TextView()->SetDocPosL(aDocPos);
	}

TBool CAknCursorManager::IsRightToLeftParagraph(TTmDocPosSpec aPos)
	{
	TTmPosInfo2 posInfo;
	TTmLineInfo lineInfo;
	TextLayout()->TagmaTextLayout().FindDocPos(aPos, posInfo, lineInfo);
	return lineInfo.iFlags & TTmLineInfo::EParRightToLeft;
	}

TBool CAknCursorManager::VisualCursorBetweenOpposingChunks()
	{
	TTmDocPosSpec pos = DocPos();
	CTmTextLayout::TTmChunkDescription leftChunk;
	CTmTextLayout::TTmChunkDescription rightChunk;
	TextLayout()->TagmaTextLayout().FindAdjacentChunks(pos, leftChunk, rightChunk);
	
	if (leftChunk.iRightToLeft != rightChunk.iRightToLeft)
		return ETrue;
	return EFalse;
	}


void CAknCursorManager::ToggleVisualDocPosL()
	{
	TTmDocPosSpec pos = DocPos();
	pos.iType = (pos.iType == TTmDocPosSpec::ETrailing) ? TTmDocPosSpec::ELeading : TTmDocPosSpec::ETrailing;
	TextView()->SetDocPosL(pos);
	}


void CAknCursorManager::ToggleLogicalDocPosL()
	{
	TTmDocPosSpec pos = DocPos();
	CTmTextLayout::TTmChunkDescription leftChunk;
	CTmTextLayout::TTmChunkDescription rightChunk;
	TextLayout()->TagmaTextLayout().FindAdjacentChunks(pos, leftChunk, rightChunk);

	TBool MoveToLeftChunk = EFalse;
	TBool MoveToRightChunk = EFalse;

	if ((!leftChunk.iRightToLeft && pos.iPos == leftChunk.iEnd) ||
		(leftChunk.iRightToLeft && pos.iPos == leftChunk.iStart))
		MoveToRightChunk = ETrue;

	else if ((!rightChunk.iRightToLeft && pos.iPos == rightChunk.iStart) ||
			 (rightChunk.iRightToLeft && pos.iPos == rightChunk.iEnd))
		MoveToLeftChunk = ETrue;

	TBool toggleLeadingTrailing = EFalse;
	if (leftChunk.iRightToLeft == rightChunk.iRightToLeft)
		toggleLeadingTrailing = ETrue;

	if (MoveToLeftChunk)
		{
		if (toggleLeadingTrailing)
			pos.iType = (pos.iType == TTmDocPosSpec::ETrailing) ? TTmDocPosSpec::ELeading : TTmDocPosSpec::ETrailing;
		if (!leftChunk.iRightToLeft) // LTR
			pos.iPos = leftChunk.iEnd;
		else //RTL
			pos.iPos = leftChunk.iStart;
		}
	else if (MoveToRightChunk)
		{
		if (toggleLeadingTrailing)
			pos.iType = (pos.iType == TTmDocPosSpec::ETrailing) ? TTmDocPosSpec::ELeading : TTmDocPosSpec::ETrailing;
		if (!rightChunk.iRightToLeft) // LTR
			pos.iPos = rightChunk.iStart;
		else //RTL
			pos.iPos = rightChunk.iEnd;
		}
	TextView()->SetDocPosL(pos);
	}


CAknCursorManager::CAknCursorManager(CAknEdwinState* aEdwinState) :
	iEdwinState(aEdwinState)
	{
	}

void CAknCursorManager::ConstructL()
	{
	}

CAknEdwinFormAccessor* CAknCursorManager::FormAccessor() const
	{
	return iEdwinState->FormAccessor();
	}

CTextLayout* CAknCursorManager::TextLayout() const
	{
	CAknEdwinFormAccessor* formAccessor = FormAccessor();
	if (formAccessor)
		return formAccessor->GetTextLayout();
	return NULL;
	}

CTextView* CAknCursorManager::TextView() const
	{
	CAknEdwinFormAccessor* formAccessor = FormAccessor();
	if (formAccessor)
		return formAccessor->GetTextView();
	return NULL;
	}

