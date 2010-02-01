// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

/**
 @file 
 @internalComponent - Internal Symbian test code 
*/


#include <barsread.h>
#include <s32file.h>
#include <gdi.h>
#include <gulutil.h>
#include <gulicon.h>
#include <apgaplst.h>
#include <apgicnfl.h>
#include <apgcli.h>
#include <vwsdef.h>

#include <eikenv.h>
#include <techview/eikdialg.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikpanic.h>
#include <techview/eikhlbx.h>
#include <techview/eikhlbm.h>
#include <techview/eikhlbi.h>
#include <techview/eiktxlbx.h>
#include <techview/eiktxlbm.h>
#include <techview/eikon.hrh>
#include <techview/eikon.rsg>
#include <eikon.mbg>
#include <eikstart.h>

#include "tview4.hrh"
#include "tview4.rsg"


/** Tests reading of views on system at runtime. Installed apps are shown in hierarchical list.
    Expanding the list item for an app reveals its views. Toolbar allows link to the view to be
    followed.
*/

//
// global functions
//

GLDEF_C void Panic(TEikPanic aPanic)
	{
	User::Panic(_L("TVIEW4"), aPanic);
	}

//
// class COwnedFilesDialog
//

class COwnedFilesDialog : public CEikDialog
	{
public:
	COwnedFilesDialog(TUid aAppUid);
private: // framework
	void PreLayoutDynInitL();
private:
	TUid iAppUid;
	};

COwnedFilesDialog::COwnedFilesDialog(TUid aAppUid)
	: iAppUid(aAppUid) 
	{
	}

void COwnedFilesDialog::PreLayoutDynInitL()
	{
	CEikTextListBox* listBox = static_cast<CEikTextListBox*>(Control(EAppDlgOwnedFilesId));
	CEikScrollBarFrame* sbFrame = listBox->CreateScrollBarFrameL();
	sbFrame->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
	
	RApaLsSession ls;
	CleanupClosePushL(ls);
	User::LeaveIfError(ls.Connect());
	User::LeaveIfError(ls.GetAllApps());

	CDesCArray* ownedFileArray=new(ELeave) CDesCArraySeg(2);
	User::LeaveIfError(ls.GetAppOwnedFiles(*ownedFileArray,iAppUid));
	
	CleanupStack::PopAndDestroy();	// ls
	
	listBox->Model()->SetItemTextArray(ownedFileArray);
	}

//
// class CAppAndViewListItem
//

class CAppAndViewListItem : public CHierListItem
	{
public:
	CAppAndViewListItem(TInt16 aFlags);
	~CAppAndViewListItem();
	void SetIcon(CGulIcon* aIcon);
	CGulIcon* Icon() const;
	void SetAppUid(TUid aUid);
	TUid AppUid() const;
	void SetViewUid(TUid aUid);
	TUid ViewUid() const;
private:
	CGulIcon* iIcon;
	TUid iAppUid;
	TUid iViewUid;
	};

CAppAndViewListItem::CAppAndViewListItem(TInt16 aFlags)
	: CHierListItem(aFlags),
	iAppUid(KNullUid), iViewUid(KNullUid)
	{
	}

CAppAndViewListItem::~CAppAndViewListItem()
	{
	delete iIcon;
	}

void CAppAndViewListItem::SetIcon(CGulIcon* aIcon)
	{
	iIcon=aIcon;
	}

CGulIcon* CAppAndViewListItem::Icon() const
	{
	return iIcon;
	}

void CAppAndViewListItem::SetAppUid(TUid aUid)
	{
	iAppUid=aUid;
	}

TUid CAppAndViewListItem::AppUid() const
	{
	return iAppUid;
	}

void CAppAndViewListItem::SetViewUid(TUid aUid)
	{
	iViewUid=aUid;
	}

TUid CAppAndViewListItem::ViewUid() const
	{
	return iViewUid;
	}


//
// class CAppAndViewListBoxModel
//

class CAppAndViewListBoxModel : public CHierarchicalListBoxModel
	{
public:
	CAppAndViewListBoxModel();
	~CAppAndViewListBoxModel();
	void CreateListL();
	void ExpandItemL(TInt aNodeToBeExpanded);
	void UpdateL();
	CAppAndViewListItem* AppAndViewItem(TInt aIndex) const;
	TInt ItemIconHeight() const;
private:
	TInt iItemIconHeight;
	};

CAppAndViewListBoxModel::CAppAndViewListBoxModel()
	{
	}

TInt CAppAndViewListBoxModel::ItemIconHeight() const
	{
	return iItemIconHeight;
	}

CAppAndViewListItem* CAppAndViewListBoxModel::AppAndViewItem(TInt aIndex) const
	{
	return STATIC_CAST(CAppAndViewListItem*,Item(aIndex));
	}

void CAppAndViewListBoxModel::CreateListL()
	{
	RApaLsSession ls;
	CleanupClosePushL(ls);
	User::LeaveIfError(ls.Connect());

	if (!iHierListArray)
		iHierListArray=new(ELeave) CArrayFixSeg<CHierListItem*>(5);
	else
		RemoveAllItems();

	User::LeaveIfError(ls.GetAllApps());
	TApaAppInfo info;
	TInt ret=ls.GetNextApp(info);
	TInt itemIndex=-1;

	CApaMaskedBitmap* appBitmap=CApaMaskedBitmap::NewLC();
	CAppAndViewListItem* item=NULL;
	CGulIcon* icon=NULL;

	while (ret==KErrNone)
		{
		item=new(ELeave) CAppAndViewListItem((TInt16)0);
		CleanupStack::PushL(item);

		ls.GetAppIcon(info.iUid,0,*appBitmap);
		icon=CEikonEnv::Static()->CreateIconFromMaskedBitmapL(*appBitmap);
		item->SetIcon(icon);
		item->SetTextL(info.iCaption);
		item->SetAppUid(info.iUid);
		AddItemL(item,-1,itemIndex++);
		iItemIconHeight=Max(iItemIconHeight,icon->Bitmap()->SizeInPixels().iHeight);
		CleanupStack::Pop();	// item
	
		ret=ls.GetNextApp(info);
		}

	if (ret!=RApaLsSession::ENoMoreAppsInList && ret!=RApaLsSession::EAppListInvalid)
		User::Leave(ret);

	CleanupStack::PopAndDestroy(2); // appBitmap, ls
	}

void CAppAndViewListBoxModel::ExpandItemL(TInt aItemToBeExpanded)
	{
	const TInt index=aItemToBeExpanded;
	CAppAndViewListItem* itemToBeExpanded=AppAndViewItem(index);
	if (itemToBeExpanded->IsExpanded())
		return;
	if (itemToBeExpanded->Level()!=0)
		return;

	RApaLsSession ls;
	CleanupClosePushL(ls);
	User::LeaveIfError(ls.Connect());
	User::LeaveIfError(ls.GetAllApps());

	CApaAppViewArray* appViews=new(ELeave) CApaAppViewArray(5);
	CleanupStack::PushL(appViews);
	TUid appUid(itemToBeExpanded->AppUid());
	ls.GetAppViews(*appViews, appUid);
	TInt newItemIndex=index;

	CApaMaskedBitmap* viewBitmap=CApaMaskedBitmap::NewLC();
	CGulIcon* icon=NULL;

	const TInt count=appViews->Count();
	for (TInt ii=0; ii<count; ii++)
		{
		CAppAndViewListItem* newItem=new(ELeave) CAppAndViewListItem((TInt16)0);
		CleanupStack::PushL(newItem);
		const TApaAppViewInfo& viewInfo=(*appViews)[ii];
		newItem->SetTextL(viewInfo.iViewCaption);
		newItem->SetViewUid(viewInfo.iUid);
		newItem->SetAppUid(appUid);

		ls.GetAppViewIcon(itemToBeExpanded->AppUid(),viewInfo.iUid,TSize(24,24),*viewBitmap);
		icon=CEikonEnv::Static()->CreateIconFromMaskedBitmapL(*viewBitmap);
		newItem->SetIcon(icon);

		AddItemL(newItem,index,newItemIndex++);
		CleanupStack::Pop();	// newItem
		}
	
	itemToBeExpanded->SetExpanded();
	CleanupStack::PopAndDestroy(3);	// ls, appViews, viewBitmap
	}

void CAppAndViewListBoxModel::UpdateL()
	{
	// Update not implemented - requires scanning for application installation which is not needed for this test
	}

CAppAndViewListBoxModel::~CAppAndViewListBoxModel()
	{	
	}



//
// class CAppAndViewListItemDrawer
// 

class CAppAndViewListItemDrawer : public CHierarchicalListItemDrawer
	{
public:
	CAppAndViewListItemDrawer(CAppAndViewListBoxModel* aModel,const CFont* aFont,
											CArrayPtr<CGulIcon>* aIconArray);
private: // from CHierarchicalListItemDrawer
	CGulIcon* ItemIcon(TInt aItemIndex) const;
	};

CAppAndViewListItemDrawer::CAppAndViewListItemDrawer(CAppAndViewListBoxModel* aModel,
																  const CFont* aFont,
																  CArrayPtr<CGulIcon>* aIconArray)
	: CHierarchicalListItemDrawer(aModel,aFont,aIconArray)
	{}

CGulIcon* CAppAndViewListItemDrawer::ItemIcon(TInt aItemIndex) const
	{
	return STATIC_CAST(CAppAndViewListBoxModel*,iModel)->AppAndViewItem(aItemIndex)->Icon();
	}


//
// class CAppAndViewListBox
//


class CAppAndViewListBox : public CEikHierarchicalListBox, public MHierarchicalListExpansionObserver
	{
public:
    CAppAndViewListBox();
    ~CAppAndViewListBox();
	void ConstructL(const CCoeControl* aParent,TInt aFlags);
	void CreateListL();
	void UpdateL();
	CAppAndViewListBoxModel* AppAndViewModel() const;
public: // from MHierExpansionObserver
	void UpdateHierarchyL(TInt aItemIndex);
private:
	void BaseConstructL();
	};


CAppAndViewListBox::CAppAndViewListBox()
    {
    }

CAppAndViewListBox::~CAppAndViewListBox()
    {
    }

void CAppAndViewListBox::ConstructL(const CCoeControl* aParent,TInt aFlags)
	{
	aFlags&=~EIncrementalMatching; // don't want incremental matching
	iListBoxFlags=aFlags;
	BaseConstructL();
	AppAndViewModel()->ConstructL();
	CEikListBox::ConstructL(aParent,aFlags);
	AppAndViewModel()->SetExpansionObserver(this);
	}

void CAppAndViewListBox::BaseConstructL()
	{
	iModel=new(ELeave) CAppAndViewListBoxModel();
	iItemDrawer=new(ELeave) CAppAndViewListItemDrawer((CAppAndViewListBoxModel*)iModel,iEikonEnv->NormalFont(),NULL);
	}

void CAppAndViewListBox::UpdateL()
	{
	AppAndViewModel()->UpdateL();
	View()->CalcBottomItemIndex();
	if (AppAndViewModel()->NumberOfItems()>0)
		SetCurrentItemIndex(0);
	UpdateScrollBarsL();
	}

void CAppAndViewListBox::UpdateHierarchyL(TInt aItemIndex)
	{
	if (View()->ItemIsVisible(aItemIndex))
		{
		View()->CalcDataWidth();
		View()->CalcBottomItemIndex();
		DrawNow();
		}
	UpdateScrollBarsL();
	}

CAppAndViewListBoxModel* CAppAndViewListBox::AppAndViewModel() const
	{
	return (CAppAndViewListBoxModel*)iModel;
	}           

void CAppAndViewListBox::CreateListL()
	{
	Reset();
	CAppAndViewListBoxModel* model=AppAndViewModel();
	model->CreateListL();
	SetItemHeightL(Max(ItemHeight(),model->ItemIconHeight()+2));
	iView->CalcBottomItemIndex();
	}


//
//	CInstalledViewListContainer
//

class CInstalledViewListContainer : public CCoeControl
    {
public:
	CInstalledViewListContainer();
    void ConstructL(const TRect& aRect);
	~CInstalledViewListContainer();
	void ListOwnedFilesL();
private: // from CCoeControl
	void Draw(const TRect& aRect) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
private:
	CAppAndViewListBox* iAppAndViewListBox;
    };

CInstalledViewListContainer::~CInstalledViewListContainer()
	{
	delete iAppAndViewListBox;
	}

CInstalledViewListContainer::CInstalledViewListContainer()
	{}

TInt CInstalledViewListContainer::CountComponentControls() const
    {
    return 1;
    }

CCoeControl* CInstalledViewListContainer::ComponentControl(TInt /*aIndex*/) const
    {			 
	return iAppAndViewListBox;
    }

const TInt KXStart = 20;
const TInt KYStart = 10;
//const TInt KXSpacing = 5;
//const TInt KYSpacing = 10;
//const TInt KControlWidth = 180;

void CInstalledViewListContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    Window().SetShadowDisabled(ETrue);
	Window().SetPointerGrab(ETrue);
    SetRect(aRect);

	TInt yPos = KYStart;
	TInt xPos = KXStart;

	iAppAndViewListBox = new(ELeave) CAppAndViewListBox;
	iAppAndViewListBox->ConstructL(this,0);
	iAppAndViewListBox->CreateScrollBarFrameL();
	iAppAndViewListBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
	iAppAndViewListBox->SetExtent(TPoint(xPos, yPos), TSize(Size().iWidth-(2*xPos), Size().iHeight-(2*yPos)));
	iAppAndViewListBox->CreateListL();
	iAppAndViewListBox->HandleItemAdditionL();
	iAppAndViewListBox->SetFocus(ETrue);

	ActivateL();
    }

void CInstalledViewListContainer::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(iEikonEnv->ControlColor(EColorControlSurroundBackground,*this));
	gc.DrawRect(Rect());
	}

TKeyResponse CInstalledViewListContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	return iAppAndViewListBox->OfferKeyEventL(aKeyEvent, aType);
	}

void CInstalledViewListContainer::ListOwnedFilesL()
	{

	CAppAndViewListItem* item=iAppAndViewListBox->AppAndViewModel()->AppAndViewItem(iAppAndViewListBox->CurrentItemIndex());
	CEikDialog* dialog = new(ELeave) COwnedFilesDialog(item->AppUid());
	dialog->ExecuteLD(R_TVIEW4_OWNED_FILE_DLG);
	}


//
// class CTestAppUi
//

class CTestAppUi : public CEikAppUi
    {
public:
	CTestAppUi();
    void ConstructL();
    ~CTestAppUi();
private: // framework
    void HandleCommandL(TInt aCommand);
private:
	CInstalledViewListContainer* iListContainer;
    };


CTestAppUi::~CTestAppUi()
    {
	RemoveFromStack(iListContainer);
	delete iListContainer;
    }

CTestAppUi::CTestAppUi()
    {
	delete iListContainer;
    }

void CTestAppUi::ConstructL()
    {
    BaseConstructL();

	iListContainer=new(ELeave) CInstalledViewListContainer;
    iListContainer->ConstructL(ClientRect());
	AddToStackL(iListContainer);
    }

void CTestAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
	case EAppCmdListOwnedFiles:
		iListContainer->ListOwnedFilesL();
		break;
    case EEikCmdExit:
        Exit();
        break;
	default:
		break;
        }
    }


//
// CTestDocument
//

class CTestDocument : public CEikDocument
	{
public:
	CTestDocument(CEikApplication& aApp): CEikDocument(aApp) { }
private: // from CApaDocument
	CEikAppUi* CreateAppUiL();
	};

CEikAppUi* CTestDocument::CreateAppUiL()
	{
    return(new(ELeave) CTestAppUi);
	}

//
// CTestApplication
//

class CTestApplication : public CEikApplication
	{
private: // from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
private:
	CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }
	};

const TUid KUidTestApp={0x10207F70};

TUid CTestApplication::AppDllUid() const
	{
	return(KUidTestApp);
	}

CApaDocument* CTestApplication::CreateDocumentL()
	{
	return(new(ELeave) CTestDocument(*this));
	}

//
// EXPORTed functions
//


	LOCAL_C CApaApplication* NewApplication()
		{
		return new CTestApplication;
		}

	GLDEF_C TInt E32Main()
		{
		return EikStart::RunApplication(NewApplication);
		}



