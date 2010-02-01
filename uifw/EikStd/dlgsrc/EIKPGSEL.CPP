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

 
#include <eikpgsel.h>
#include <eiklabel.h>
#include <barsread.h>
#include <coedef.h>
#include <coemain.h>
#include <coedef.h>
#include <eikcapca.h>
#include <eikcapc.h>
#include <eikdpage.h>
#include <gulbordr.h>
#include <gulcolor.h>
#include <eikpanic.h>
#include <eikenv.h>

#include <akntashook.h> // for testability hooks
#define KPageSelectorOverlap (-1) // negative overlap is a gap

const TInt KPageSelectorLeftOffset = 8;
const TInt KActivePageSelectorExtraHeight = 2;
const TInt KTopGap = 3; // gap between the dialog title and the top of the ActivePageSelector
const TInt KActivePageSelectorHMargin = 7;
const TInt KPageSelectorHMargin = 5;
const TInt KPageSelectorVMargin = 5;
const TInt KMaxPageSelectorTitleLength = 30;

EXPORT_C void CEikPageSelector::GetColorUseListL(CArrayFix<TCoeColorUse>& /*aColorUseList*/) const
	{
	}

EXPORT_C void CEikPageSelector::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	}

EXPORT_C CEikPageSelector::CEikPageSelector()
	{
	__DECLARE_NAME(_S("CEikPageSelector"));
	iCurrentPage=-1;
	AKNTASHOOK_ADD( this, "CEikPageSelector" );
	}

EXPORT_C CEikPageSelector::~CEikPageSelector()
	{
	AKNTASHOOK_REMOVE();
	if (iPages!=NULL)
		{
		const TInt count=iPages->Count();
		for (TInt ii=0;ii<count;++ii)
			{
			SEikPage& page=(*iPages)[ii];
			delete(page.iLabel);
			delete(page.iLines);
			delete(page.iPage);
			}
		delete iPages;
		}
	delete iActiveSelector;
	}

EXPORT_C void CEikPageSelector::ConstructFromResourceL(TResourceReader& aReader)
	{
	iActiveSelector = new(ELeave) CEikActivePageSelector;
	iActiveSelector->ConstructL(this);
	const TInt pageCount = aReader.ReadInt16();
	iPages = new(ELeave) CArrayFixFlat<SEikPage>(pageCount);
	for (TInt ii=0;ii<pageCount;++ii)
		{
		const TPtrC text = aReader.ReadTPtrC();
		const TInt controlId = aReader.ReadInt16();
		const TInt linesResourceId = aReader.ReadInt32();
		AddPageL(text,controlId,linesResourceId);
		}
	}

EXPORT_C void CEikPageSelector::AddPageL(CEikLabel* aLabel,TInt aControlId,TInt aPageResourceId)
	{
	SEikPage page;
	page.iLabel = aLabel;
	page.iControlId = aControlId;
	page.iPageResourceId = aPageResourceId;
	page.iLabel->SetAlignment(EHCenterVCenter);
	page.iLines = NULL;
	page.iPage = NULL;
	page.iCurrentLine = -1;
	iPages->AppendL(page);
	page.iLabel->SetContainerWindowL(*this);
	}

EXPORT_C void CEikPageSelector::AddPageL(const TDesC& aText,TInt aControlId,TInt aLinesResourceId)
	{
	CEikLabel* label = new(ELeave) CEikLabel;
	CleanupStack::PushL(label);
	label->SetTextL(aText);
	AddPageL(label,aControlId,aLinesResourceId);
	CleanupStack::Pop();
	}

EXPORT_C TSize CEikPageSelector::MinimumSize()
	{
    if (iSize.iWidth)
        return(iSize);
	const TInt count = iPages->Count();
	for (TInt ii=0; ii<count; ++ii)
		{
		CEikLabel* pageLabel = (*iPages)[ii].iLabel;
		TSize minSize = pageLabel->MinimumSize();
		iSize.iWidth += minSize.iWidth + 2*KPageSelectorHMargin;
		if (iSize.iHeight < minSize.iHeight)
			iSize.iHeight = minSize.iHeight;
		}
	TGulBorder border(TGulBorder::EThickDeepRaisedWithOutline);
	TMargins margins = border.Margins();
	iSize.iWidth += (margins.iLeft + (count-1));
	iSize.iHeight += 2*KPageSelectorVMargin+KTopGap;
	return iSize;
	}

TInt CEikPageSelector::CountComponentControls() const
	{
	return (iPages->Count());
	}

CCoeControl* CEikPageSelector::ComponentControl(TInt aIndex) const
	{
	return ((*iPages)[aIndex].iLabel);
	}

void CEikPageSelector::SizeChanged()
	{
	TRect rect = Rect();
	// all pages have the same height which is *always* <=minHeight
	TSize labelSize(0,rect.Size().iHeight-2*KPageSelectorVMargin-KTopGap);
	rect.iTl.iY += KPageSelectorVMargin+KActivePageSelectorExtraHeight+KTopGap;
	rect.iTl.iX += KPageSelectorLeftOffset;
	const TInt count = iPages->Count();
	for (TInt ii=0;ii<count;++ii)
		{
		CEikLabel* pageLabel = (*iPages)[ii].iLabel;
		labelSize.iWidth = pageLabel->MinimumSize().iWidth;
		pageLabel->SetExtent(rect.iTl,labelSize);
		rect.iTl.iX += labelSize.iWidth+2*KPageSelectorHMargin - KPageSelectorOverlap;
		}
	}

EXPORT_C TInt CEikPageSelector::CurrentPage() const 
	{
	return iCurrentPage;
	}

EXPORT_C TInt CEikPageSelector::CurrentPageControlId() const
	{
	SEikPage& page = (*iPages)[iCurrentPage];
	return page.iControlId;
	}

EXPORT_C TInt CEikPageSelector::PageSelectorWidth(TInt aPageIndex)
	{
	return ((*iPages)[aPageIndex].iLabel->MinimumSize().iWidth + 2*KPageSelectorHMargin);
	}

void CEikPageSelector::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	TRect rect;
	TGulBorder border(TGulBorder::EShallowRaised);
	const TInt count = iPages->Count();
	for (TInt ii=0;ii<count;++ii)
		{
		if (ii!=iCurrentPage)
			{// current page selector is drawn by the ActivePageSelector
			rect = (*iPages)[ii].iLabel->Rect();
			rect.Grow(KPageSelectorHMargin,KPageSelectorVMargin);
#if (KPageSelectorOverlap>0)
				TRect clipRect = rect;
				clipRect.iTl.iX+=KPageSelectorOverlap+1;
				gc.SetClippingRect(clipRect);
				border.Draw(gc,rect);
				gc.CancelClippingRect();
#else
				border.Draw(gc,rect);
#endif
			}
		}
	}

EXPORT_C TInt CEikPageSelector::IdOfUnavailableSelectedPage() const
	{
	return(iIdOfUnavailableSelectedPage);
	}

EXPORT_C void* CEikPageSelector::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }   

EXPORT_C void CEikPageSelector::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	TInt selected = iCurrentPage;
    if (aPointerEvent.iType!=TPointerEvent::EButton1Down)
		return;
	const TInt count = iPages->Count();
	for (TInt ii=0; ii<count; ++ii)
		{
		CEikLabel* label = (*iPages)[ii].iLabel;
		TRect rect = label->Rect();
		rect.Grow(KPageSelectorHMargin,KPageSelectorVMargin);
		if (rect.Contains(aPointerEvent.iPosition))
			{
			if (label->IsDimmed())
				{
				iIdOfUnavailableSelectedPage = (*iPages)[ii].iPageResourceId;
				ReportEventL(MCoeControlObserver::EEventInteractionRefused);
				return;
				}
			selected = ii;
			iIdOfUnavailableSelectedPage = -1;
			SetFocus(ETrue, ENoDrawNow);
			break;
			}
		}
	if (selected != iCurrentPage)
		ChangeCurrentPageL(selected);
	}

EXPORT_C void CEikPageSelector::SetInitialCurrentPageIndexL(TInt aCurrentPage)
	{
	iCurrentPage=aCurrentPage;
	EmphasizeCurrentPageL(ETrue);
	}

void CEikPageSelector::EmphasizeCurrentPageL(TBool aEmphasis)
	{
	if (aEmphasis)
		(*iPages)[iCurrentPage].iPage->DrawableWindow()->SetOrdinalPosition(0);
	ActivateGc();
	SEikPage& page = (*iPages)[iCurrentPage];
	TRect rect=page.iLabel->Rect();
	rect.Grow(KActivePageSelectorHMargin,KPageSelectorVMargin);
	if (aEmphasis)
		{
		iActiveSelector->MakeVisible(EFalse);
		rect.iTl.iY-=KActivePageSelectorExtraHeight;
		TGulBorder border(TGulBorder::EShallowRaised);
		TMargins margins = border.Margins();
		rect.iBr.iY-=margins.iBottom-1;// -1 so line between selector and page overwritten
		iActiveSelector->SetRect(rect); // won't actually Leave
		page.iLabel->SetFont(iEikonEnv->NormalFont());
		iActiveSelector->SetTextL(page.iLabel);
		iActiveSelector->MakeVisible(ETrue);
		}
	DeactivateGc();
	page.iPage->MakeVisible(aEmphasis);
	}

void CEikPageSelector::FocusChanged(TDrawNow /*aDrawNow*/)
	{
	if (iCurrentPage < 0)
		return;
	if (IsFocused())
		{
		if (iActiveSelector)
			{
			iActiveSelector->Label()->SetEmphasis(CEikLabel::EFullEmphasis);
			iActiveSelector->Label()->DrawNow();
			}
		}
	else
		{
		if (iActiveSelector)
			{
			iActiveSelector->Label()->SetEmphasis(CEikLabel::ENoEmphasis);
			iActiveSelector->Label()->DrawNow();
			}
		}
	}

void CEikPageSelector::ChangeCurrentPageL(TInt aCurrentPage)
	{
	if (iCurrentPage == aCurrentPage)
		return;
	ReportEventL(MCoeControlObserver::EEventPrepareFocusTransition);
	iPreviousPageCurrentLine=&(*iPages)[iCurrentPage].iCurrentLine;
	TInt oldCurrentPage = iCurrentPage;
	iCurrentPage = aCurrentPage;
	EmphasizeCurrentPageL(ETrue);
	iCurrentPage = oldCurrentPage;
	EmphasizeCurrentPageL(EFalse);
	iCurrentPage = aCurrentPage;
	ReportEventL(MCoeControlObserver::EEventStateChanged);
	}

EXPORT_C void CEikPageSelector::ChangePageL(CEikCapCArray* aArray,TInt aCurrentLine)
	{
	TInt newSelectedPage=0;
	FOREVER
		{
		if ((*iPages)[newSelectedPage].iLines==aArray)
			break;
		newSelectedPage++;
		}
	TInt oldCurrentPage = iCurrentPage;
	iCurrentPage = newSelectedPage;
	EmphasizeCurrentPageL(ETrue);
	iCurrentPage = oldCurrentPage;
	(*iPages)[iCurrentPage].iCurrentLine=aCurrentLine;
	EmphasizeCurrentPageL(EFalse);
	iCurrentPage = newSelectedPage;
	}

EXPORT_C CEikCapCArray* CEikPageSelector::SwapPageDetails(TInt& aCurrentLine)
	{
	if (iPreviousPageCurrentLine)
		{
		*iPreviousPageCurrentLine=aCurrentLine;
		iPreviousPageCurrentLine=NULL;
		}
	SEikPage& page=(*iPages)[iCurrentPage];
	aCurrentLine=page.iCurrentLine;
	return(page.iLines);
	}

EXPORT_C TKeyResponse CEikPageSelector::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
/* TP: Commented because dialog has already this implemented
    if (aType!=EEventKey)
        return(EKeyWasConsumed);
*/
	TInt code = aKeyEvent.iCode;
	const TBool switchToNextPage = (code == EKeyRightArrow) || (code==EKeyTab && 
							(aKeyEvent.iModifiers&EModifierCtrl) && (aKeyEvent.iModifiers&EModifierPureKeycode));
	const TBool switchToPrevPage = (code == EKeyLeftArrow) || (code==EKeyTab && 
							(aKeyEvent.iModifiers&EModifierCtrl) && (aKeyEvent.iModifiers&EModifierShift) && 
							(aKeyEvent.iModifiers&EModifierPureKeycode));
	if (switchToNextPage || switchToPrevPage)
		{
		TInt max=iPages->Count()-1;
		TInt count=max;
		TInt selectedPage=iCurrentPage;
		if (count > 0)
			{
UpdateSelectedPageIndex:
			if (switchToPrevPage)
				--selectedPage;
			else
				++selectedPage;
    		if (selectedPage<0)
        		selectedPage=max;
    		else if (selectedPage>max)
        		selectedPage=0;
			if ((*iPages)[selectedPage].iLabel->IsDimmed())
				goto UpdateSelectedPageIndex;
			if (selectedPage!=iCurrentPage)
				ChangeCurrentPageL(selectedPage);
			return (EKeyWasConsumed);
			}
		return(EKeyWasNotConsumed);
		}
	else
		return(EKeyWasNotConsumed);
	}

EXPORT_C TCoeInputCapabilities CEikPageSelector::InputCapabilities() const
	{
	return TCoeInputCapabilities(TCoeInputCapabilities::ENavigation);
	}

EXPORT_C TBool CEikPageSelector::GetNextPage(TInt aPageIndex,CEikCapCArray*& aPage) const
	{
	const TInt count=iPages->Count();
	if (aPageIndex>=count)
		return(EFalse);
	aPage=(*iPages)[aPageIndex].iLines;
	return(ETrue);
	}

EXPORT_C CEikCapCArray* CEikPageSelector::StartConstructPageL(TInt aPageIndex,CCoeControl*& aContainer,TInt& aResourceId)
	{
	const TInt count=iPages->Count();
	if (aPageIndex>=count)
		return(NULL);
	SEikPage& page=(*iPages)[aPageIndex];
	aResourceId=page.iPageResourceId;
	if (!page.iLines)
	    page.iLines=new(ELeave) CEikCapCArray(1); // granularity
	if (!page.iPage)
		{
		page.iPage=new(ELeave) CEikDialogPage;
		page.iPage->ConstructL(aContainer,page.iLines);
		if (aPageIndex)
			page.iPage->MakeVisible(EFalse);
		}
	aContainer=page.iPage;
	return(page.iLines);
	}

EXPORT_C void CEikPageSelector::SetPageDimmed(TInt aPageId,TBool aDimmed)
	{
	const TInt count=iPages->Count();
	TInt ii=0;
	FOREVER
		{
		if (ii==count)
			Panic(EEikPanicNoSuchDialogPage);
		SEikPage& page=(*iPages)[ii++];
		if (page.iControlId!=aPageId)
			continue;
		CEikLabel* label=page.iLabel;
		label->SetDimmed(aDimmed);
		label->DrawNow();
		break;
		}
	}

EXPORT_C CEikCapCArray* CEikPageSelector::InfoFromPageId(TInt aPageId,CCoeControl*& aContainer) const
	{
	const TInt count=iPages->Count();
	TInt ii=0;
	CEikCapCArray* lines=NULL;
	FOREVER
		{
		if (ii==count)
			Panic(EEikPanicNoSuchDialogPage);
		SEikPage& page=(*iPages)[ii++];
		if (page.iControlId!=aPageId)
			continue;
		lines=page.iLines;
		aContainer=page.iPage;
		break;
		}
	return(lines);
	}

void CEikPageSelector::ActivateL()
	{
	CCoeControl::ActivateL();
	const TInt count=iPages->Count();
	for (TInt ii=0;ii<count;++ii)
		{
		CEikDialogPage* page=(*iPages)[ii].iPage;
		if (page)
			page->ActivateL();
		}
	SetInitialCurrentPageIndexL(0); // !! put this here for now
	}

EXPORT_C TSize CEikPageSelector::MinimumPageSize() const
	{
	TSize size;
	const TInt count=iPages->Count();
	for (TInt ii=0;ii<count;++ii)
		{
		SEikPage& page=(*iPages)[ii];
		TSize thisSize=page.iPage->MinimumSize();
		if (size.iWidth<thisSize.iWidth)
			size.iWidth=thisSize.iWidth;
		if (size.iHeight<thisSize.iHeight)
			size.iHeight=thisSize.iHeight;
		}
	return(size);
	}

EXPORT_C void CEikPageSelector::SetPagesRectL(const TRect& aRect)
	{
	const TInt count=iPages->Count();
	for (TInt ii=0;ii<count;++ii)
		(*iPages)[ii].iPage->SetRect(aRect);
	}

//
// CEikActivePageSelector
//

CEikActivePageSelector::CEikActivePageSelector()
	{
	__DECLARE_NAME(_S("CEikActivePageSelector"));
	}

CEikActivePageSelector::~CEikActivePageSelector()
	{
	delete iLabel;
	}

void CEikActivePageSelector::ConstructL(CCoeControl* aContainer)
	{
	CreateWindowL(aContainer);
	CopyControlContextFrom(aContainer);
	EnableDragEvents();
	iLabel = new(ELeave) CEikLabel;
	iLabel->SetBufferReserveLengthL(EMaxTextLength);
	iLabel->SetAlignment(EHCenterVCenter);
	iLabel->SetBufferReserveLengthL(KMaxPageSelectorTitleLength);
	iLabel->SetContainerWindowL(*this);
	ActivateL();
	Window().SetOrdinalPosition(0);
	}

void CEikActivePageSelector::SetTextL(const CEikLabel* aLabel)
	{ // none of following calls will actually Leave
	TRect rect = Rect();

	TGulBorder border(TGulBorder::EDeepRaisedWithOutline);
	TMargins margins = border.Margins();
	// Do not adjust iBr.iY, that way the label will clear the line between
	// the ActivePageSelector and the dialog page.
	rect.iTl.iX += margins.iLeft;
	rect.iTl.iY += margins.iTop;
	rect.iBr.iX -= margins.iRight;
	iLabel->SetTextL(*(aLabel->Text()));
	iLabel->SetRect(rect);
	iLabel->ActivateL();
	Window().SetOrdinalPosition(0);
	}

void CEikActivePageSelector::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	TRect rect=Rect();
	TGulBorder border(TGulBorder::EDeepRaisedWithOutline);
	TMargins margins = border.Margins();
	rect.iBr.iY+=margins.iBottom;// so bottom of border not drawn
	border.Draw(gc,rect);
	}

TInt CEikActivePageSelector::CountComponentControls() const
	{
	return(1);
	}

CCoeControl* CEikActivePageSelector::ComponentControl(TInt /*aIndex*/) const
	{
	return(iLabel);
	}

void CEikActivePageSelector::GetColorUseListL(CArrayFix<TCoeColorUse>& /*aColorUseList*/) const
	{
	}

void CEikActivePageSelector::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	}
