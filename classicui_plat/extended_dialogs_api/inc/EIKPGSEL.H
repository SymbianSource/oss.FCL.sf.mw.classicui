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


#if !defined(__EIKPGSEL_H__)
#define __EIKPGSEL_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

class CEikLabel;
class CEikCapCArray;
class CEikCaptionedControl;
class CEikDialogPage;
class CEikActivePageSelector;

/**
 * @deprecated
 */
class CEikPageSelector : public CCoeControl
	{
public: // new functions
	IMPORT_C CEikPageSelector();
	IMPORT_C ~CEikPageSelector();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void AddPageL(const TDesC& aText,TInt aControlId,TInt aLinesResourceId);
	IMPORT_C void AddPageL(CEikLabel* aLabel,TInt aControlId,TInt aLinesResourceId);
	IMPORT_C TInt CurrentPage() const;
	IMPORT_C TInt CurrentPageControlId() const;
	IMPORT_C TInt PageSelectorWidth(TInt aPageIndex);
	IMPORT_C CEikCapCArray* StartConstructPageL(TInt aPageIndex,CCoeControl*& aContainer,TInt& aResourceId);
	IMPORT_C CEikCapCArray* InfoFromPageId(TInt aPageId,CCoeControl*& aContainer) const;
	IMPORT_C void SetInitialCurrentPageIndexL(TInt aCurrentPage);
	IMPORT_C TSize MinimumPageSize() const;
	IMPORT_C void SetPagesRectL(const TRect& aRect);
	IMPORT_C CEikCapCArray* SwapPageDetails(TInt& aCurrentLine);
	IMPORT_C void ChangePageL(CEikCapCArray* aArray,TInt aCurrentLine);
	IMPORT_C TBool GetNextPage(TInt aPageIndex,CEikCapCArray*& aPage) const;
	IMPORT_C void SetPageDimmed(TInt aPageId,TBool aDimmed);
	IMPORT_C TInt IdOfUnavailableSelectedPage() const;
public: // from CCoeControl
	IMPORT_C TSize MinimumSize();
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
private:   // from CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void SizeChanged();
	void FocusChanged(TDrawNow aDrawNow);
	void Draw(const TRect& aRect) const;
	void ActivateL();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: // new functions
	void ChangeCurrentPageL(TInt aCurrentPage);
	void EmphasizeCurrentPageL(TBool aEmphasis);
private:
	struct SEikPage
		{
		CEikLabel* iLabel;
		TInt iControlId;
		TInt iPageResourceId;
		CEikDialogPage* iPage;
		CEikCapCArray* iLines;
		TInt iCurrentLine;
		};


	CArrayFixFlat<SEikPage>* iPages;
	TInt iCurrentPage;
	TInt* iPreviousPageCurrentLine;
	CEikActivePageSelector* iActiveSelector;
	TInt iIdOfUnavailableSelectedPage;
	};


/**
 * @deprecated
 */
class CEikActivePageSelector : public CCoeControl
	{
public: // new functions
	CEikActivePageSelector();
	~CEikActivePageSelector();
	void ConstructL(CCoeControl* aContainer);
	void SetTextL(const CEikLabel* aLabel);
	inline CEikLabel* Label() const {return iLabel;}
public:	// from CCoeControl
	void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	void HandleResourceChange(TInt aType);			// not available before Release 005u
private: // from CCoeControl
	void Draw(const TRect& aRect) const;
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
private:
    enum { EMaxTextLength = 20 };
	CEikLabel* iLabel;
	};



#endif
