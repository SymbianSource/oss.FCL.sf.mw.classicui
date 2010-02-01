/*
* Copyright (c) 1999 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __EIKDPSEL_H__
#define __EIKDPSEL_H__

#include <gulbordr.h>
#include <coeccntx.h>
#include <coecobs.h>
#include <coecntrl.h>
#include <AknTabObserver.h>


//
// Forward declarations.
//

class CEikDialogPageContainer;
class CEikCaptionedControl;
class MEikDialogPageObserver;


class CAknTabGroup ;
class MAknNavigationContainerInterface ;
class CAknNavigationControlContainer;
class MAknNavigationDecoratorInterface ;
class CAknNavigationDecorator;
class CEikTabPreStore ;

// This Class manages tool tips for the dialog.
// Tips are displayed in the NaviPane if there is nothing else there.
// Tips are only displayed for single page dialogs containing forms.
NONSHARABLE_CLASS(CEikDlgToolTipMgr) : public CBase
	{
	public:
		CEikDlgToolTipMgr(CEikonEnv* aEikonEnv) ;
		~CEikDlgToolTipMgr() ;

		void DisplayTipL( const TDesC* aTipText ) ;
		void HideTip() ;
		void EnableTips( TBool aShowTips ) ;

	private:
		MAknNavigationContainerInterface* iNaviContainer ;
		MAknNavigationDecoratorInterface* iToolTip ;

		TBool iShowTips ;
		TBool iIsTipShowing ;

	};



/**
 * The CEikDialogPageSelector class manages a dialog's pages and tabs.
 *
 * @internal
 * @since ER5U
 */
NONSHARABLE_CLASS(CEikDialogPageSelector) : public CCoeControl,public MCoeControlContext,public MCoeControlObserver, public MAknTabObserver
	{
public:
	~CEikDialogPageSelector();
	static CEikDialogPageSelector* NewL(const CCoeControl& aParent,CEikDialog* aDialog);
	static CEikDialogPageSelector* NewLC(const CCoeControl& aParent,CEikDialog* aDialog);
	static CEikDialogPageSelector* NewL(const CCoeControl& aParent,TResourceReader& aReader,CEikDialog* aDialog);
	static CEikDialogPageSelector* NewLC(const CCoeControl& aParent,TResourceReader& aReader,CEikDialog* aDialog);
	TSize PreferredSize(const TSize& aMaxSize) const;
	void SetActivePageByIdL(TInt aPageId);
	void SetActivePageByIndexL(TInt aPageIndex);
	void ActivateFirstPageL();
	void SetInitialFocus();
	void AddPageL(TResourceReader& aReader);
	void AddPageL(TInt aPageId,const TDesC& aTabText);
	void AddPageL(TInt aPageId,const TDesC& aTabText,TResourceReader& aReader);
	CEikCaptionedControl* Line(TInt aControlId) const;
	CEikCaptionedControl* LineOrNull(TInt aControlId) const;
	CEikCaptionedControl* CurrentLine() const;
	void SetPageDensePacked(TInt aPageId,TBool aDensePacked);
	void SetAllPagesDensePacked(TBool aDensePacked);
	void SetPageDimmed(TInt aPageId,TBool aDimmed,TDrawNow aDrawNow);
	TInt LineId(const CCoeControl& aControl) const;
	void DeleteLine(TInt aLineId,TBool aRedraw);
	void InsertLineL(TInt aPosition,TInt aPageId,TInt aResourceId);
	void AdjustAllIds(TInt aPageId,TInt aControlIdDelta);
	CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aControlId,TInt aControlType,TAny* aReturnValue);
	CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aPageId,TInt aControlId,TInt aControlType,TAny* aReturnValue);
	void FocusLineL(TInt aLineId);
	TInt FocusedLineId() const;
	void GetAutoValues();
	TInt ActivePageId() const;
	TInt ActivePageIndex() const;
	void ResetLineMinimumSizes();
	TInt FindLineIndex(const CCoeControl& aControl) const;
	TBool RotateFocusByL(TInt aDelta);
	TKeyResponse OfferHotKeysKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	TBool TakesEnterKey();
	void SetEditableL( TBool aEditable) ; // This should only be used for form resource
	TInt NumPages() const ;
	CEikDialogPageContainer* PageContainer();


public: // from CCoeControl
	virtual TSize MinimumSize();
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
public: // from MCoeControlContext
	virtual void PrepareContext(CWindowGc& aGc) const;
public: // from MCoeControlObserver
	virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
public: 
	void SetDialg(CEikDialog* aDialg);
	CEikDialog* Dialg() const;
public: 
	TBool IsForm() const;
protected:
	void RegisterPageSelectorWithPageContainer();

protected: // from CCoeControl
	virtual void SizeChanged();
	virtual TInt CountComponentControls() const;
	virtual CCoeControl* ComponentControl(TInt aIndex) const;
	virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	virtual void Draw(const TRect& aRect) const;
	void DrawBorder(const TRect& aRect) const;
	void DrawBackground(const TRect& aRect) const;
	virtual void Reserved_2();
private:
	CEikDialogPageSelector();
	void ConstructL(MEikDialogPageObserver* aPageObserver);
	void ConstructFromResourceL(TResourceReader& aReader,MEikDialogPageObserver* aPageObserver);
	void PrepareForFocusTransitionL();
	void HandleRequestFocusL(CCoeControl* aControl);
	void HandleTabStateChangedL(CAknTabGroup* aTabContainer);
	void PassOnEventL(CCoeControl* aControl,MCoeControlObserver::TCoeEvent aEvent);

	void AddFormToPageL( TInt aPageId,TResourceReader& aReader ) ;

    void CreatePreStoredTabL();
    void CreateTabContainerL();
	void DestroyTabContainer() ;

public: 
    // From MAknTabObserver
    void TabChangedL(TInt aIndex); 

private:
	CEikDialogPageContainer* iPageContainer;

	CAknTabGroup* iTabContainer ;
	CAknNavigationDecorator* iNaviDecorator ;
	CAknNavigationControlContainer* iNaviContainer ;
	TBool iEditable ;
	TBool iTabsVisible ;
	TBool iIsForm ;
	TGulBorder iBorder;
	CEikDialog* iDialg;
	CEikTabPreStore* iTabPreStore;
	TBool iFirstTabContainsText;
	};


#endif

