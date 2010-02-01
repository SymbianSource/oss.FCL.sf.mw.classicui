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
 
#include "altview.h" 
#include "altmodel.h"
#include "altglobal.h"
#include "applaunchtest.hrh"
#include <techview/eikclbd.h>
#include <coemain.h>
#include <eikenv.h>
#include <techview/eiktxlbm.h>
#include <applaunchtest.rsg>


//const TInt KFOScreenMode = 0;	// actual mode (ie. size) definition is in wsini.ini
const TInt KFCScreenMode = 1;	// actual mode (ie. size) definition is in wsini.ini
const TInt KIgnoreScreenMode = -1; // actual definition in /mw/appsupport/appfw/apparchitecture/aplist/aplapplist.h

CAltView* CAltView::NewL(TRect& aRect, CAppLauncherModel* aModel)
	{
	CAltView* self=new(ELeave) CAltView;
	CleanupStack::PushL(self);
	self->ConstructL(aRect,aModel);
	CleanupStack::Pop(); //self
	return self;
	}

CAltView::CAltView()
	{
	}

CAltView::~CAltView()
	{
	delete iFilterChoice;
	delete iFilterLabel;
	delete iAppList;
	delete iStatusPane;
	}

TVwsViewId CAltView::ViewId() const
	{
	return TVwsViewId(KUidAltApp,KUidAltView);
	}

void CAltView::ConstructL(TRect& aRect, CAppLauncherModel* aModel)
	{
    CreateWindowL();
	iStatusPane = CEikStatusPane::NewL(*iEikonEnv, &iEikonEnv->RootWin(), R_ALT_STATUS_PANE);
	TRect rect(aRect);
	iStatusPane->ReduceRect(rect);
	SetRect(rect);
	iModel=aModel;
	iModel->SetAppListObserver(this);
	iFilterChoice=new(ELeave)CEikCheckBox;
	iFilterChoice->SetContainerWindowL(*this);
	iFilterChoice->SetExtent(TPoint(50,10),iFilterChoice->MinimumSize());
//	iFilterChoice->SetText(_L("Flip Open"));
	iFilterChoice->ActivateL();
	iFilterChoice->SetObserver(this);
	iFilterLabel=new(ELeave)CEikLabel;
	iFilterLabel->SetContainerWindowL(*this);
	iFilterLabel->SetTextL(_L("Flip Closed"));
	iFilterLabel->SetExtent(TPoint(60+iFilterChoice->MinimumSize().iWidth,10),iFilterLabel->MinimumSize());
	iFilterLabel->ActivateL();
	iAppList = new (ELeave) CEikColumnListBox;

	// Now create the listbox by constructL
	iAppList->ConstructL(this,  CEikListBox::EStateChanged);
	iAppList->SetBorder(TGulBorder::ENone );
	iAppList->CreateScrollBarFrameL();
	iAppList->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
    CColumnListBoxData* columnData=iAppList->ItemDrawer()->ColumnData();
	
	//App name
	columnData->SetColumnAlignmentL( 0 ,CGraphicsContext::ELeft);
    columnData->SetColumnWidthPixelL(0, Size().iWidth/2);
	
	//Hidden
	columnData->SetColumnAlignmentL( 1 ,CGraphicsContext::ELeft);
    columnData->SetColumnWidthPixelL(1, Size().iWidth/8);

	//Embeddable
	columnData->SetColumnAlignmentL( 2 ,CGraphicsContext::ELeft);
    columnData->SetColumnWidthPixelL(2, Size().iWidth/8);

	//Flip Open
	columnData->SetColumnAlignmentL( 3 ,CGraphicsContext::ELeft);
    columnData->SetColumnWidthPixelL(3, Size().iWidth/8);

	//Flip Closed
	columnData->SetColumnAlignmentL( 4 ,CGraphicsContext::ELeft);
    columnData->SetColumnWidthPixelL(4, Size().iWidth/8);

	// Full width of the window, height is totalt window  height minus the BaseMtmCtrlStart
	iAppList->SetExtent(TPoint(0, KTopControlHeight),TSize(Size().iWidth,Size().iHeight-KTopControlHeight));
	iAppList->ActivateL();

	BuildAppListL();
	ActivateL(); //Activate the view
	}

void CAltView::BuildAppListL()
	{
	// Get hold of the listbox models internal list so we
	// can add some items to it:
	CTextListBoxModel* listBoxModel = iAppList->Model();
	MDesCArray* itemArray = listBoxModel->ItemTextArray();
	((CDesCArray*)itemArray)->Reset();
	TBuf<KMaxAppBufSize>	app = TPtrC();
	TInt numOfApps=iModel->NumberOfApplications();
	TUid currentAppUid;

	for (TInt currentApp=0; currentApp < numOfApps; currentApp++)
		{
		currentAppUid=iModel->ApplicationUid(currentApp);
		// 1, Build the string as it will be shown in 
		//    the list box (differs between e.g. e-mail and SMS)
		BuildVisibleStringL( app ,currentAppUid);

		// 2, Put the complete App header in the list.
		((CDesCArray*)itemArray)->AppendL( app );

		app = TPtrC(); // Empty string
		}

	// Update listbox to view all items
	iAppList->HandleItemRemovalL();
	iAppList->DrawNow();
	}

void CAltView::BuildVisibleStringL(TBuf<KMaxAppBufSize>& appString, TUid& aUid )
	{
	// Build the message string to display
	// 1, Set the different icons depending on if the mail
	//    is read or not (first column)
	// .....
	//    and if it is read or not
	// Unfortunatelyl, the EMbmQmappEmailunread16 etc. correspond to the
	// location in the .mbm file rather than the index in the array used by
	// the listbox. To get the correct index we have to find the place where
	// the bitmaps are in the file (= EMbmQmappEmpty)
	const TInt KMaxStringSize	= 256;
	// Constants, move?
	_LIT(KSingleTab, "\t");
	_LIT(KHidden,"H");
	_LIT(KNotHidden,"NH");
	_LIT(KEmbeddable,"E");
	_LIT(KNotEmbeddable,"NE");
	_LIT(KEmbeddableOnly,"EO");
	_LIT(KFlipOpen,"FO");
	_LIT(KNotFlipOpen,"NFO");
	_LIT(KFlipClosed,"FC");
	_LIT(KNotFlipClosed,"NFC");
	_LIT(KOops,"X");

	TBuf<KMaxStringSize> longString;
	CFont* font = CONST_CAST(CFont*,iEikonEnv->NormalFont());

	// Add app name
	TApaAppInfo appInfo;
	iModel->LsSession().GetAppInfo(appInfo,aUid);
	longString.Copy(appInfo.iCaption);
	TextUtils::ClipToFit( longString, *font,Size().iWidth/2 );
	appString += longString;

	appString += KSingleTab;
	// Add hidden	

	TApaAppCapabilityBuf capability;

	iModel->LsSession().GetAppCapability(capability,aUid);

	if(capability().iAppIsHidden)
		{
		appString+=KHidden;
		}
	else
		{
		appString+=KNotHidden;
		}

	appString+=KSingleTab;

	// Embeddable
	switch(capability().iEmbeddability)
		{
	case TApaAppCapability::ENotEmbeddable:
		appString+=KNotEmbeddable;
		break;
	case TApaAppCapability::EEmbeddable:
		appString+=KEmbeddable;
		break;
	case TApaAppCapability::EEmbeddableOnly:
		appString+=KEmbeddableOnly;
		break;
	default:
		appString+=KOops;
		break;
		}

	appString += KSingleTab;

	CApaAppViewArray* appViews=new(ELeave) CApaAppViewArray(4);
	TInt err=iModel->LsSession().GetAppViews(*appViews, aUid);
	if(err!=KErrNone)
		{
		delete appViews;
		return;
		}
	TBool result=EFalse;
	TInt viewCount=appViews->Count();
	if(viewCount>0)
		{
		for(TInt ii=0;ii<viewCount;ii++)
			{
			if((*appViews)[ii].iScreenMode==0)
				{
				result=ETrue;
				break;
				}
			}
		}
	else
		{
		// An app with no views is Flip Open mode by default
		result=ETrue;
		}
	if(result)
		{
		appString+=KFlipOpen;
		}
	else
		{
		appString+=KNotFlipOpen;
		}
	appString+=KSingleTab;
	result=EFalse;
	if(viewCount>0)
		{
		for(TInt ii=0;ii<viewCount;ii++)
			{
			if((*appViews)[ii].iScreenMode==KFCScreenMode)
				{
				result=ETrue;
				break;
				}
			}
		}
	if(result)
		{
		appString+=KFlipClosed;
		}
	else
		{
		appString+=KNotFlipClosed;
		}
	delete appViews;
	}

CCoeControl* CAltView::ComponentControl(TInt aIndex) const
	{
/*	switch (aIndex)
		{
//	case 0:
//		return iLabel;
//		break;
	case 0:
		return iFilterChoice;
		break;
	case 1:
		return iAppList;
		break;
	case 2:
		return iFilterLabel;
		break;
	case 3:
		return iStatusPane->ContainerControlL(TUid::Uid(EAltSpanePaneUid1));
	default:
		return NULL;
		break;
		}*/
		
		if (aIndex == 0)
		{
		return iFilterChoice;
		}
		else if  (aIndex == 1)
		{
		return iAppList;
		}
		else if  (aIndex == 2)
		{
		return iFilterLabel;
		}
		else if  (aIndex == 3)
		{
		return iStatusPane->ContainerControlL(TUid::Uid(EAltSpanePaneUid1));
		}
		else
		{
		return NULL;
		}
	}

TInt CAltView::CountComponentControls() const
	{
	return 4;
	}

void CAltView::Draw( const TRect& /*aRect*/ ) const
	{
	// Clear the background of the View
	CWindowGc& gc = SystemGc();

	gc.SetPenStyle( CGraphicsContext::ESolidPen );
	gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
	gc.SetBrushColor( iEikonEnv->ControlColor(EColorWindowBackground,*this) );
	gc.SetPenColor( iEikonEnv->ControlColor(EColorWindowBackground,*this));
	gc.DrawRect(Rect());
	gc.DrawLine(TPoint(0,0),TPoint(200,200));
	}

void CAltView::ViewActivatedL(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,const TDesC8& /*aCustomMessage*/)
	{
	TPixelsAndRotation sizeAndRotation;
	ControlEnv()->ScreenDevice()->GetDefaultScreenSizeAndRotation(sizeAndRotation);
	ControlEnv()->ScreenDevice()->SetScreenSizeAndRotation(sizeAndRotation);

	SetFocus(ETrue,ENoDrawNow);
	MakeVisible(ETrue);

	DrawNow();
	}

void CAltView::ViewDeactivated()
	{
	}

void CAltView::AppListChangedL()
	{
	BuildAppListL();
	DrawNow();
	}

void CAltView::HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)
	{
	if(aControl==iFilterChoice && aEventType==EEventStateChanged)
		{
		switch(iFilterChoice->State())
			{
		case CEikButtonBase::ESet:
			iModel->SetScreenModeL(1);
			break;
		case CEikButtonBase::EClear:
			iModel->SetScreenModeL(KIgnoreScreenMode);
			break;
		default:
			break;
			}
		}
	}
