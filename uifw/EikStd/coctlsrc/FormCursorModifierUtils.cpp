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
#include <frmtlay.h>
#include <frmtview.h>
#include <tagma.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <tagmalayoutandsource.h>
#endif

#include "FromCursorModifierUtils.h"

TFormCursorModifierUtils::~TFormCursorModifierUtils()
	{
	}

TFormCursorModifierUtils::TFormCursorModifierUtils(CTextView& aTextView, CTextLayout& aTextLayout) :
	iTextView(aTextView),
	iTextLayout(aTextLayout)
	{
	}

TTmDocPosSpec TFormCursorModifierUtils::DocPos() const
	{
	TTmDocPosSpec docPos = TTmDocPosSpec();
	TTmDocPos rawDocPos;
	iTextView.GetCursorPos(rawDocPos);
	docPos.iPos = rawDocPos.iPos;
	TTmDocPosSpec::TType docPosType = rawDocPos.iLeadingEdge ? TTmDocPosSpec::ELeading : TTmDocPosSpec::ETrailing;
	docPos.iType = docPosType;
	return docPos;
	}

void TFormCursorModifierUtils::SetDocPosL(const TTmDocPosSpec& aDocPos)
	{
	iTextView.SetDocPosL(aDocPos);
	}

TBool TFormCursorModifierUtils::IsRightToLeftParagraph(TTmDocPosSpec aPos)
	{
	TTmPosInfo2 posInfo;
	TTmLineInfo lineInfo;
	iTextLayout.TagmaTextLayout().FindDocPos(aPos, posInfo, lineInfo);
	return lineInfo.iFlags & TTmLineInfo::EParRightToLeft;
	}

TBool TFormCursorModifierUtils::VisualCursorBetweenOpposingChunks()
	{
	TTmDocPosSpec pos = DocPos();
	CTmTextLayout::TTmChunkDescription leftChunk;
	CTmTextLayout::TTmChunkDescription rightChunk;
	iTextLayout.TagmaTextLayout().FindAdjacentChunks(pos, leftChunk, rightChunk);
	
	if (leftChunk.iRightToLeft != rightChunk.iRightToLeft)
		return ETrue;
	return EFalse;
	}


void TFormCursorModifierUtils::ToggleVisualDocPosL()
	{
	TTmDocPosSpec pos = DocPos();
	pos.iType = (pos.iType == TTmDocPosSpec::ETrailing) ? TTmDocPosSpec::ELeading : TTmDocPosSpec::ETrailing;
	SetDocPosL(pos);
	}


void TFormCursorModifierUtils::ToggleLogicalDocPosL()
	{
	TTmDocPosSpec pos = DocPos();
	CTmTextLayout::TTmChunkDescription leftChunk;
	CTmTextLayout::TTmChunkDescription rightChunk;
	iTextLayout.TagmaTextLayout().FindAdjacentChunks(pos, leftChunk, rightChunk);

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
	SetDocPosL(pos);
	}


