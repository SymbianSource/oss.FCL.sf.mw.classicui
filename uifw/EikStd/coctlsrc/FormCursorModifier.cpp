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
#include <eikedwin.h>
#include <tagma.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <tagmalayoutandsource.h>
#endif


#include <frmtlay.h>
#include <frmtview.h>
#include <txtrich.h>

#include "FormCursorModifier.h"
#include "FromCursorModifierUtils.h"

CFormCursorModifier* CFormCursorModifier::NewL(CTextView* aTextView, CTextLayout* aTextLayout)
	{
	CFormCursorModifier* self = new (ELeave) CFormCursorModifier(aTextView, aTextLayout);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

CFormCursorModifier::~CFormCursorModifier()
	{
	}

void CFormCursorModifier::HandleFormCursorModifierEventL(TFormCursorModifierEvent aEvent, TInt aData1, TAny* aData2)
	{
	switch (aEvent)
		{
		case EEventNull:
			break;
		case EEventInitialiseEditor:
			if (iTextLayout)
				{
				if (iTextLayout->DocumentLength() == 0 && aData2) // Added aData2 check. It is NULL when whole text is selected and cut operation is made.
					InitialiseCursorPositionL(static_cast<CEikEdwin*>(aData2));
				}
			break;
		case EEventInlineEditUpdate:
			break;
		case EEventInsertion:
			break;
		case EEventDeletion:
			if (iTextLayout)
				{
				if (iTextLayout->DocumentLength() == 0)
					InitialiseCursorPositionL(static_cast<CEikEdwin*>(aData2));
				else
					NormaliseCursorPositionFollowingDeleteL();
				}
			break;
		case EEventNavigation:
			if (iTextLayout && aData1 == 0) // aData1 is selection length
				NormaliseCursorPositionFollowingNavigationL();
			break;
		case EEventInputDirectionIsLeftToRight:
			SetDirectionality(ELeftToRight);
			break;			
		case EEventInputDirectionIsRightToLeft:
			SetDirectionality(ERightToLeft);
			break;
		default:
			// as yet undefined enumerations should be handled gracefully
			// here - this must not panic
			break;
		}
	}

void CFormCursorModifier::SetTextView(CTextView* aTextView)
	{
	iTextView = aTextView;
	}
	
void CFormCursorModifier::SetTextLayout(CTextLayout* aTextLayout)
	{
	iTextLayout = aTextLayout;
	}

CFormCursorModifier::CFormCursorModifier(CTextView* aTextView, CTextLayout* aTextLayout) :
	iTextView(aTextView),
	iTextLayout(aTextLayout),
	iDirectionality(ELeftToRight)
	{
	}

void CFormCursorModifier::ConstructL()
	{
	}

void CFormCursorModifier::NormaliseCursorPositionFollowingDeleteL()
	{
	TFormCursorModifierUtils cursorModifierUtils(*iTextView, *iTextLayout);
	TTmDocPosSpec pos = cursorModifierUtils.DocPos();

	CTmTextLayout::TTmChunkDescription leftChunk;
	CTmTextLayout::TTmChunkDescription rightChunk;
	iTextLayout->TagmaTextLayout().FindAdjacentChunks(pos, leftChunk, rightChunk);

	TBool isRTLPara = cursorModifierUtils.IsRightToLeftParagraph(pos);
	if (isRTLPara && !rightChunk.iRightToLeft || !isRTLPara && leftChunk.iRightToLeft)
		cursorModifierUtils.ToggleVisualDocPosL();	
	}

void CFormCursorModifier::NormaliseCursorPositionFollowingNavigationL()
	{
	TFormCursorModifierUtils cursorModifierUtils(*iTextView, *iTextLayout);

	if (cursorModifierUtils.VisualCursorBetweenOpposingChunks())
		{
		TTmDocPosSpec pos = cursorModifierUtils.DocPos();
		CTmTextLayout::TTmChunkDescription leftChunk;
		CTmTextLayout::TTmChunkDescription rightChunk;
		iTextLayout->TagmaTextLayout().FindAdjacentChunks(pos, leftChunk, rightChunk);

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
			if (iDirectionality == ERightToLeft)
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
			else // direction is LTR
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
		cursorModifierUtils.SetDocPosL(pos);
		}
	}

void CFormCursorModifier::InitialiseCursorPositionL(CEikEdwin* aEdwin)
	{
	CRichText* rT = static_cast<CRichText*>(aEdwin->Text());
	CParaFormat* paraF = CParaFormat::NewLC();
	paraF->iLanguage = (iDirectionality == ELeftToRight) ? ELangEnglish : ELangArabic;
	TParaFormatMask langMask;
	langMask.SetAttrib(EAttParaLanguage);
	rT->ApplyParaFormatL(paraF, langMask, 0, 1);
	if (iTextView)
		iTextView->HandleRangeFormatChangeL(TCursorSelection(0, iTextLayout->DocumentLength()), ETrue);

	CleanupStack::PopAndDestroy(); // paraF
	}


void CFormCursorModifier::SetDirectionality(TDirectionality aDirectionality)
	{
	iDirectionality = aDirectionality;
	}
