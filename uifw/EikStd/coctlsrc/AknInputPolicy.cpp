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
#include <aknenv.h>
#include <aknsettingcache.h>
#include <eikedwin.h>
#include <txtrich.h>
#include "akncursormanager.h"
#include "akninputpolicy.h"

CAknInputPolicyManager* CAknInputPolicyManager::NewL(CEikEdwin* aEdwin)
	{
	CAknInputPolicyManager* self = new (ELeave) CAknInputPolicyManager(aEdwin);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

CAknInputPolicyManager::~CAknInputPolicyManager()
	{
	}

void CAknInputPolicyManager::HandleInputPolicyManagerEventL(TEventType aEvent, TInt /*aData1*/, TAny* /*aData2*/)
	{
	switch (aEvent)
		{
		case ECMEventNull:
			break;
		case ECMEventInitialise:
			if (iEdwin->TextLength() == 0)
				SetCursorUsingLanguageL();
			break;
		case ECMEventInlineEditUpdate:
			break;
		case ECMEventInsertion:
			break;
		case ECMEventDeletion:
			if (iEdwin->TextLength() == 0)
				SetCursorUsingLanguageL();
			else
				NormaliseCursorPositionFollowingDeleteL();
			break;
		case ECMEventNavigation:
			NormaliseCursorPositionFollowingNavigationL();
			break;
		default:
			break;
		}
	}

CAknInputPolicyManager::CAknInputPolicyManager(CEikEdwin* aEdwin) :
	iEdwin(aEdwin)
	{
	}

void CAknInputPolicyManager::ConstructL()
	{
	}


void CAknInputPolicyManager::NormaliseCursorPositionFollowingDeleteL()
	{
	CAknCursorManager* cursorManager = CAknCursorManager::NewL(iEdwin->EditorState());
	CleanupStack::PushL(cursorManager);

	TTmDocPosSpec pos = cursorManager->DocPos();
	CTmTextLayout::TTmChunkDescription leftChunk;
	CTmTextLayout::TTmChunkDescription rightChunk;
	iEdwin->TextLayout()->TagmaTextLayout().FindAdjacentChunks(pos, leftChunk, rightChunk);

	TBool isRTLPara = cursorManager->IsRightToLeftParagraph(pos);
	if (!isRTLPara && leftChunk.iRightToLeft ||
		isRTLPara && !rightChunk.iRightToLeft)
		cursorManager->ToggleVisualDocPosL();
	
	CleanupStack::PopAndDestroy(); // cursorManager
	}

void CAknInputPolicyManager::NormaliseCursorPositionFollowingNavigationL()
	{
	CAknCursorManager* cursorManager = CAknCursorManager::NewL(iEdwin->EditorState());
	CleanupStack::PushL(cursorManager);

	if (cursorManager->VisualCursorBetweenOpposingChunks())
		{
		TTmDocPosSpec pos = cursorManager->DocPos();
		CTmTextLayout::TTmChunkDescription leftChunk;
		CTmTextLayout::TTmChunkDescription rightChunk;
		iEdwin->TextLayout()->TagmaTextLayout().FindAdjacentChunks(pos, leftChunk, rightChunk);

		CAknSettingCache& cache = CAknEnv::Static()->SettingCache();
		TLanguage currentLanguage = cache.InputLanguage();

		if (leftChunk.iStart == -1)
			{ // left end of a line
			if (rightChunk.iRightToLeft)
				{ // set doc pos trailing at the end of the right chunk
				pos.iType = TTmDocPosSpec::ETrailing;
				pos.iPos = rightChunk.iEnd;
				}
			else // rightChunk is LTR
				{ // set doc pos leading at start of right chunk
				pos.iType = TTmDocPosSpec::ELeading;
				pos.iPos = rightChunk.iStart;
				}
			}
		else if (rightChunk.iStart == -1)
			{ // right end of a line
			if (leftChunk.iRightToLeft)
				{ // set doc pos leading at start of left chunk
				pos.iType = TTmDocPosSpec::ELeading;
				pos.iPos = leftChunk.iStart;
				}
			else // leftChunk is LTR
				{ // set doc pos trailing at the end of the left chunk
				pos.iType = TTmDocPosSpec::ETrailing;
				pos.iPos = leftChunk.iEnd;
				}
			}

		else // middle of a line
			{
			currentLanguage &= KAknLanguageMask;
			if (currentLanguage == ELangArabic || currentLanguage == ELangHebrew)
				{
				if (rightChunk.iRightToLeft)
					{ // set doc pos trailing at the end of the right chunk
					pos.iType = TTmDocPosSpec::ETrailing;
					pos.iPos = rightChunk.iEnd;
					}
				else // rightChunk is LTR
					{ // set doc pos leading at start of left chunk
					pos.iType = TTmDocPosSpec::ELeading;
					pos.iPos = leftChunk.iStart;
					}
				}
			else // language is LTR
				{
				if (rightChunk.iRightToLeft)
					{ // set doc pos trailing at the end of left chunk
					pos.iType = TTmDocPosSpec::ETrailing;
					pos.iPos = leftChunk.iEnd;
					}
				else // rightChunk is LTR
					{ // set doc pos leading at the start of right chunk
					pos.iType = TTmDocPosSpec::ELeading;
					pos.iPos = rightChunk.iStart;
					}
				}
			}
		// set the doc position...
		cursorManager->SetDocPosL(pos);
		}
	CleanupStack::PopAndDestroy(); // cursorManager
	}

void CAknInputPolicyManager::SetCursorUsingLanguageL()
	{
	CAknSettingCache& cache = CAknEnv::Static()->SettingCache();
	TLanguage currentLanguage = cache.InputLanguage();

	CRichText* rT = static_cast<CRichText*>(iEdwin->Text());
	CParaFormat* paraF = CParaFormat::NewLC();
	paraF->iLanguage = currentLanguage;
	TParaFormatMask langMask;
	langMask.SetAttrib(EAttParaLanguage);
	rT->ApplyParaFormatL(paraF, langMask, iEdwin->CursorPos(), 1);
	iEdwin->TextView()->HandleRangeFormatChangeL(TCursorSelection(0, iEdwin->TextLength()), ETrue);

	CleanupStack::PopAndDestroy(); // paraF
	}
