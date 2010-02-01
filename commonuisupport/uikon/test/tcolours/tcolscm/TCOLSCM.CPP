// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Acts as a very simple run-time colour scheme changer application.
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/

#include <s32file.h>
#include <gdi.h>
#include <gulutil.h>

#include <eikenv.h>
#include <techview/eikdialg.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikdebug.h>
#include <techview/eikchlst.h>
#include <eikrutil.h>
#include <eikpanic.h>
#include <eiksvdef.h>
#include <ecom/ecom.h>

#include <techview/eikon.hrh>
#include <techview/eikon.rsg>
#include <eikspane.h>
#include <spaneinit.rsg>

#include "TCOLSCM.HRH"
#include <tcolscm.rsg>

#include "Tcolscm.h"


// globals 
_LIT(KTColscmResourceFilePath, "z:\\system\\test\\colours\\tcolscm\\tcolscm.rsc");
const TUid KUidTColscm={651};

GLDEF_C void Panic(TEikPanic aPanic)
	{
	User::Panic(_L("TCOLSCM"), aPanic);
	}


//!***************************** CColorSchemeDlg. 
/**
 Dialog for the colour scheme control.
*/

CColorSchemeDlg::CColorSchemeDlg(TInt& aChoice)
	: iChoice(aChoice) 
	{
	}

/**
   This method is an override from CEikDialog. It is used to perform pre-layout dialog initialisation. 
 */
void CColorSchemeDlg::PreLayoutDynInitL()
	{
	}

/**
   This method is an override from CEikDialog. It handles a dialog button press for OK button.  
 */
TBool CColorSchemeDlg::OkToExitL(TInt aControlId)
    {
	if (aControlId==EEikBidOk)
		{
		iChoice=STATIC_CAST(CEikChoiceList*,Control(EAppChoiceListId))->CurrentItem();
		}
	return(ETrue);
    }



//!*****************************  CColorSchemeControl. 
/**
 The class represents colour scheme control on which tests are performed.
*/

/**
   The method creates the controls window and sets it ready to be drawn.
 */
void CColorSchemeControl::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    Window().SetShadowDisabled(ETrue);
    SetRect(aRect);
    ActivateL();

	iLogicalNames = new(ELeave) CDesCArrayFlat(5);
	InitNameArrayL();
    }

/**
   The method is called by CColorSchemeControl::ConstructL() to initialize the descriptor array,iLogicalNames.
 */
void CColorSchemeControl::InitNameArrayL()
    {
	iLogicalNames->AppendL(_L("WindowBackground"));
	iLogicalNames->AppendL(_L("WindowText"));
	iLogicalNames->AppendL(_L("ControlBackground"));
	iLogicalNames->AppendL(_L("ControlText"));
	iLogicalNames->AppendL(_L("ControlSurroundBackground"));
	iLogicalNames->AppendL(_L("ControlSurroundText"));
	iLogicalNames->AppendL(_L("ControlHighlightBackground"));
	iLogicalNames->AppendL(_L("ControlHighlightText"));
	iLogicalNames->AppendL(_L("ControlDimmedBackground"));
	iLogicalNames->AppendL(_L("ControlDimmedText"));
	iLogicalNames->AppendL(_L("ControlDimmedHighlightBackground"));
	iLogicalNames->AppendL(_L("ControlDimmedHighlightText"));
	iLogicalNames->AppendL(_L("DialogBackground"));
	iLogicalNames->AppendL(_L("DialogText"));
	iLogicalNames->AppendL(_L("DialogTitle"));
	iLogicalNames->AppendL(_L("DialogTitlePressed"));
	iLogicalNames->AppendL(_L("DialogTitleText"));
	iLogicalNames->AppendL(_L("DialogTitleTextPressed"));
	iLogicalNames->AppendL(_L("MenubarBackground"));
	iLogicalNames->AppendL(_L("MenubarText"));
	iLogicalNames->AppendL(_L("MenubarTitleBackground"));
	iLogicalNames->AppendL(_L("MenubarTitleText"));
	iLogicalNames->AppendL(_L("MenuPaneBackground"));
	iLogicalNames->AppendL(_L("MenuPaneText"));
	iLogicalNames->AppendL(_L("MenuPaneHighlight"));
	iLogicalNames->AppendL(_L("MenuPaneTextHighlight"));
	iLogicalNames->AppendL(_L("MenuPaneDimmedHighlight"));
	iLogicalNames->AppendL(_L("MenuPaneDimmedText"));
	iLogicalNames->AppendL(_L("MenuPaneDimmedTextHighlight"));
	iLogicalNames->AppendL(_L("ButtonFaceClear"));
	iLogicalNames->AppendL(_L("ButtonFaceSet"));
	iLogicalNames->AppendL(_L("ButtonFaceSetPressed"));
	iLogicalNames->AppendL(_L("ButtonFaceClearPressed"));
	iLogicalNames->AppendL(_L("ButtonText"));
	iLogicalNames->AppendL(_L("ButtonTextPressed"));
	iLogicalNames->AppendL(_L("ButtonTextDimmed"));
	iLogicalNames->AppendL(_L("MsgWinForeground"));
	iLogicalNames->AppendL(_L("MsgWinBackground"));
	iLogicalNames->AppendL(_L("ScrollBarBorder"));
	iLogicalNames->AppendL(_L("ScrollBarShaft"));
	iLogicalNames->AppendL(_L("ScrollBarShaftDimmed"));
	iLogicalNames->AppendL(_L("ScrollBarShaftPressed"));
	iLogicalNames->AppendL(_L("ScrollBarNoShaftOrThumb"));
	iLogicalNames->AppendL(_L("ScrollButtonIcon"));
	iLogicalNames->AppendL(_L("ScrollButtonIconPressed"));
	iLogicalNames->AppendL(_L("ScrollButtonIconDimmed"));
	iLogicalNames->AppendL(_L("ScrollButtonThumbBackground"));
	iLogicalNames->AppendL(_L("ScrollButtonThumbBackgroundPressed"));
	iLogicalNames->AppendL(_L("ScrollThumbDimmed"));
	iLogicalNames->AppendL(_L("ScrollThumbEdge"));
	iLogicalNames->AppendL(_L("ToolbarBackground"));
	iLogicalNames->AppendL(_L("ToolbarText"));
	iLogicalNames->AppendL(_L("StatuspaneBackground"));
	iLogicalNames->AppendL(_L("StatuspaneText"));
	iLogicalNames->AppendL(_L("LabelText"));
	iLogicalNames->AppendL(_L("LabelTextEmphasis"));	
	iLogicalNames->AppendL(_L("LabelDimmedText"));
	iLogicalNames->AppendL(_L("LabelHighlightPartialEmphasis"));
	iLogicalNames->AppendL(_L("LabelHighlightFullEmphasis"));
	}

const TInt KXStart = 10;
const TInt KYStart = 10;
const TInt KYTextStart = 20;
const TInt KWidth = 10;
const TInt KHeight = 18;
const TInt KXSpacing = 5;
const TInt KYSpacing = 5;
const TInt KXTextWidth = 80;


/**
   The method is an override from CCoeControl. The method gets the physical
   (TRgb) colour which corresponds to the logical colour specified from the
   application's colour list and sets it as controls background colour.
 */
void CColorSchemeControl::Draw(const TRect& /*aRect*/) const
	{
	// Tests whether custom color arrays in the list have been merged correctly
	ASSERT(iEikonEnv->ColorList().Color(KUidTColscm, EExtraSystemBackground)==KRgbRed);
	ASSERT(iEikonEnv->ColorList().Color(KUidTColscm, EExtraSystemText)==KRgbGreen);
	//

	CWindowGc& gc = SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(iEikonEnv->ControlColor(EColorWindowBackground,*this));
	gc.SetPenColor(KRgbBlack);
	gc.DrawRect(Rect());

	gc.UseFont(iEikonEnv->AnnotationFont());

	TInt yPos = KYStart;
	TInt xPos = KXStart;

	TInt yTextPos = KYTextStart;
	
	const TInt yInc = KHeight+KYSpacing;
	const TInt xInc = KWidth+KXSpacing;

	TInt count = 0;
	for(TInt jj=0;jj<6;jj++)
		{
		for(TInt ii=0;ii<10;ii++)
			{
			if(count>EEikColorLabelHighlightFullEmphasis) break;
					
			TRect rect(TPoint(xPos,yPos),TSize(KWidth,KHeight));
			gc.SetBrushColor(iEikonEnv->ControlColor(STATIC_CAST(TLogicalColor,count),*this));
			gc.DrawRect(rect);
				
			xPos+=xInc;
			TRAPD(err,
				HBufC* text=HBufC::NewLC(1024);
				TPtr textPointer=text->Des();
				textPointer.Format((*iLogicalNames)[count]);
				TextUtils::ClipToFit(textPointer, *(iEikonEnv->AnnotationFont()), KXTextWidth);
				gc.DrawText(textPointer,TPoint(xPos,yTextPos));
				CleanupStack::PopAndDestroy(); // text
				);
 		
		   	__ASSERT_ALWAYS(!err,User::Panic(_L("tcolscm"),err));
			yTextPos+=yInc;
			yPos+=yInc;
			xPos-=xInc;

			count++;
			}
		xPos+=xInc+KXTextWidth+KXSpacing;
		yTextPos=KYTextStart;
		yPos=KYStart;
		}
	}

/**
   The method is an override from CCoeControl. The method handles key events of the control.
 */
TKeyResponse CColorSchemeControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
	{
	return EKeyWasNotConsumed;
	}

CColorSchemeControl::~CColorSchemeControl()
	{
	delete iLogicalNames;
	}


//!*****************************  CBlankerWin. 
/**
 Empty Control
*/

/**
   The method is an override from CCoeControl. The method draws an empty control.
 */
void CBlankerWin::Draw(const TRect& /*aRect*/) const
	{
	}

/**
   The method creates an empty control and sets its extend to fit the entire screen.  
 */	
void CBlankerWin::ConstructL()
    {
    CreateWindowL();
    SetExtentToWholeScreen();
    ActivateL();
    DrawNow();
    iCoeEnv->Flush(300000);
    }



//!*****************************  A CTColorSchemeAppUi test class. 
/**
 The class performs tests to change colour scheme.
*/
CTColorSchemeAppUi::CTColorSchemeAppUi(CTmsTestStep* aStep) :
	CTestAppUi(aStep,KTColscmResourceFilePath)
	{
	}


/**
   The method initiates the creation of a control that acts as a runtime
   colour scheme changer and sets active object with lowest priority for
   running test in auto mode. It also initializes a colour array by reading
   a list of available colours from a resource definition.  
 */
void CTColorSchemeAppUi::ConstructL()
    {
	CTestAppUi::ConstructL();

	ReadCustomColorResourceL();

	iColorSchemeControl=new(ELeave) CColorSchemeControl();
    iColorSchemeControl->ConstructL(ClientRect());
	AddToStackL(iColorSchemeControl);

	AutoTestManager().StartAutoTest();
    }


CTColorSchemeAppUi::~CTColorSchemeAppUi()
    {
	RemoveFromStack(iColorSchemeControl);
	delete iColorSchemeControl;
    }


/**
   The method is an override from CTestAppUi. The method initiates all tests
   which refresh background with different colors by calling CTColorSchemeAppUi::HandleCommandL().
 */
void CTColorSchemeAppUi::RunTestStepL(TInt aNextStep)
	{
	switch(aNextStep)
		{
	case 1:
		SetTestStepID(_L("UIF-TCOLSCM-HandleCommandL"));
		INFO_PRINTF1(_L("Draw color background DEFAULT"));
		HandleCommandL(EAppCmdShowDlg);
		iChoice++;
		break;
	case 2:
		INFO_PRINTF1(_L("Draw color background GRAY"));
		HandleCommandL(EAppCmdShowDlg);
		iChoice++;
		break;
	case 3:
		INFO_PRINTF1(_L("Draw color background LILAC"));
		HandleCommandL(EAppCmdShowDlg);
		iChoice++;
		break;
	case 4:
		INFO_PRINTF1(_L("Draw color background MARAM_GRASS"));
		HandleCommandL(EAppCmdShowDlg);
		iChoice++;
		break;
	case 5:
		INFO_PRINTF1(_L("Draw color background SKY_BLUE"));
		HandleCommandL(EAppCmdShowDlg);
		iChoice++;
		break;
	case 6:
		INFO_PRINTF1(_L("Draw color background BEACH_SAND"));
		HandleCommandL(EAppCmdShowDlg);
		iChoice++;
		break;
	case 7:
		INFO_PRINTF1(_L("Draw color background BLUE_SLATE"));
		HandleCommandL(EAppCmdShowDlg);
		iChoice++;
		break;
	case 8:
		INFO_PRINTF1(_L("Draw color background SKY_BLUE"));
		HandleCommandL(EAppCmdShowDlg);
		iChoice++;
		break;
	case 9:
		INFO_PRINTF1(_L("Draw color background CUSTOM COLOR 1"));
		HandleCommandL(EAppCmdShowDlg);
		iChoice++;
		break;
	case 10:
		INFO_PRINTF1(_L("Draw color background CUSTOM COLOR 2"));
		HandleCommandL(EAppCmdShowDlg);
		iChoice++;
		break;
	case 11:
		HandleCommandL(EAppCmdToggleSpane);
		iChoice = 0;
		INFO_PRINTF1(_L("End of Test."));
		RecordTestResultL();
		CloseTMSGraphicsStep();
		CTestAppUi::AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;
	default:
		break;
		}
	}

/**
   The method creates a colour array by calling EikResourceUtils::CreateColorArrayLC()
   to read a list of available colours from a resource definition. The method
   sets a mapping in application colour list between logical colours which
   specify the colour scheme and physical colours by calling CEikonEnv::SetColor().
   The method then updates the system color list with application colour list
   by calling ColorUtils::UpdateSystemColorListL().
 */
void CTColorSchemeAppUi::StorePrefsL()
	{	
	CColorArray* colorArray=EikResourceUtils::CreateColorArrayLC(iResId,iEikonEnv);
	for (TInt ii=EColorWindowBackground;ii<=EEikColorLabelHighlightFullEmphasis;ii++)
		{
		iEikonEnv->SetColor(((TLogicalColor)ii),colorArray->Color(ii));
		}
	ColorUtils::UpdateSystemColorListL(iEikonEnv->FsSession(),iEikonEnv->ColorList());
	CleanupStack::PopAndDestroy(colorArray);
	}


/**
   @SYMTestCaseID UIF-TCOLSCM-HandleCommandL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests refreshing the background color of the control.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method performs the following:\n
   1) Test changing background color of the control
   2) Toggle between making the Status Pane visible and invisible.
  
   @SYMTestExpectedResults Each of the tests should display the sprite as
   expected for the values assigned to parameters of methods covered by the
   test.\n
 */
void CTColorSchemeAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
    case EEikCmdExit:
        Exit();
        break;
	case EAppCmdToggleSpane:
		ToggleStatusPane();
		break;
	case EAppCmdShowDlg:
		HandleColorChangesL();
		break;
        }
    }


/**
  The method changes the background of the control.The method calls
  StorePrefsL() to set the application colour list as the system colour list
  and accesses the windows server to change the background colour. In order
  to change the colour a windows server event to change colour scheme is
  created and the event is send to all windows group of all applications.
*/
void CTColorSchemeAppUi::HandleColorChangesL()
    {
	switch(iChoice)
		{
	case 0:
		iResId=R_COLOR_SCHEME_ER5;
		break;
	case 1:
		iResId=R_COLOR_SCHEME_GRAY;
		break;
	case 2:
		iResId=R_COLOR_SCHEME_LILAC;
		break;
	case 3:
		iResId=R_COLOR_SCHEME_MARAM_GRASS;
		break;
	case 4:
		iResId=R_COLOR_SCHEME_SKY_BLUE;
		break;
	case 5:
		iResId=R_COLOR_SCHEME_BEACH_SAND;
		break;
	case 6:
		iResId=R_COLOR_SCHEME_BLUE_SLATE;
		break;
	case 7:
		iResId=R_COLOR_SCHEME_SKY_BLUE;
		break;
		}

	StorePrefsL();

	iEikonEnv->WsSession().SetAutoFlush(ETrue);

	CArrayFixFlat<TInt> *windowList = new(ELeave) CArrayFixFlat<TInt>(5);
	CleanupStack::PushL(windowList);
	iEikonEnv->WsSession().WindowGroupList(windowList);

	TInt count=windowList->Count();
	for(int ii=0;ii<count;ii++)
		{
		TWsEvent event;
		event.SetType(KUidValueEikColorSchemeChangeEvent);
		TInt winId=(*windowList)[ii];
		iEikonEnv->WsSession().SendEventToWindowGroup(winId,event);
		}
	
	CleanupStack::PopAndDestroy(windowList);

	iEikonEnv->WsSession().SetAutoFlush(EFalse);
	
	CBlankerWin* win=new(ELeave) CBlankerWin;
	CleanupStack::PushL(win);
	win->ConstructL();
	CleanupStack::PopAndDestroy(win);
	}


/**
   The method initializes a colour array by calling
   EikResourceUtils::CreateColorArrayLC() to read a list of available
   colours from a resource definition. The color array thus created is added
   to application's colour list by calling CColorList::AddColorArrayL().
 */
void CTColorSchemeAppUi::ReadCustomColorResourceL()
	{
	CColorArray* colors=EikResourceUtils::CreateColorArrayLC(R_CUSTOM_EXTRA_COLORS,iEikonEnv);
	iEikonEnv->ColorList().AddColorArrayL(KUidTColscm,colors); // takes ownership
	CleanupStack::Pop(colors);
	}


/**
   The method alternatively makes the status pane appear, disappear and refreshes the screen.   
 */
void CTColorSchemeAppUi::ToggleStatusPane()
	{
	if( iEikonEnv->AppUiFactory()->StatusPane() )
		{
		iEikonEnv->AppUiFactory()->StatusPane()->MakeVisible( !iEikonEnv->AppUiFactory()->StatusPane()->IsVisible() );
		iColorSchemeControl->SetRect( ClientRect() );
		iColorSchemeControl->DrawNow();
		}
	}



//!*****************************  A CTestColscmStep test class. 
/**
 The class creates & sets the application's user interface object.
*/

CTestColscmStep::CTestColscmStep()
	{
	SetTestStepName(KTestColscmStep);
	}


CTestColscmStep::~CTestColscmStep()
	{
	}


/**
   The method creates & sets the application's user interface object. 
 */
void CTestColscmStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();
	CTestAppUi* appUi= new (ELeave) CTColorSchemeAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }

TVerdict CTestColscmStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Colscm step started...."));

	PreallocateHALBuffer();
	__UHEAP_MARK;

	CEikonEnv* coe=new(ELeave) CEikonEnv;
	TRAPD(err,ConstructAppL(coe));
	TEST(err==KErrNone);
	if (!err)
		{
		coe->ExecuteD();
		}

	REComSession::FinalClose();	
	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("...Test Colscm step finished!!!"));
	return TestStepResult();
	}

