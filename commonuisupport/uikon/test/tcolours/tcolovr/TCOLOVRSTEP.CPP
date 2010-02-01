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
// Tests color overriding for a few controls - namely
// 1) Labels
// 2) Listboxes
// 3) Dialogs
// 4) Command buttons
// 5) Scrollbars
// The colors are first overriden using the logical color names 
// for the colors that the controls employ.
// Choose 'Override fore and back' from the menu
// to override the foreground and background colors using the color
// use list that the controls publish. 
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include <barsread.h>
#include <s32file.h>
#include <gdi.h>
#include <gulutil.h>

#include <techview/eikon.hrh>
#include <techview/eikon.rsg>
#include <ecom/ecom.h>

#include <spaneinit.rsg>
#include "TCOLOVRStep.h"
#include "TCOLOVRSTEP.HRH"
#include <tcolovrstep.rsg>


// constants and definitions
#define KRgbLilac TRgb(206,207,255)

_LIT(KTCOLOVRResourceFilePath,"z:\\system\\test\\colours\\tcolovr\\tcolovrstep.rsc");

enum TTestAppUiPanic
	{
	EBadCommandPanic,
	};

LOCAL_D void Panic(TTestAppUiPanic aPanic)
	{
	User::Panic(_L("TCOLOVR"), aPanic);
	}


//
//  TColorUtils  //
//

/**
	 Provides some colour utility functions.
*/
class TColorUtils
    {
public:
	static void SetForegroundColorL(CCoeControl& aControl, TRgb aRgb);
	static void SetBackgroundColorL(CCoeControl& aControl, TRgb aRgb);
	static void ResetEnvColorsL(CCoeControl& aControl);
	};

/**
   This method overrides foreground colours. If there are any contents then
   these colours are not overridden, otherwise all colours are overridden.
   It doesnot override highlight colours.   
 */
void TColorUtils::SetForegroundColorL(CCoeControl& aControl, TRgb aRgb)
	{
	CArrayFixFlat<TCoeColorUse>* useList=new(ELeave) CArrayFixFlat<TCoeColorUse>(1);
	CleanupStack::PushL(useList);	
	aControl.GetColorUseListL(*useList);

	const TInt count = useList->Count();
	
	//
	// Count number of content colors
	//
	TInt numContentColors = 0;
	TInt ii=0;
	for(ii=0;ii<count;ii++)
		{
		TCoeColorUse colorUse = (*useList)[ii];
		if (colorUse.IsForeground() && (colorUse.IsContents()))
			{
			numContentColors++;
			}
		}


	// Override colors
    // Do not override highlight colors
	// If there are any contents colors only override these
	// Otherwise override all colors

	TInt numGrays=0;
	TInt numColors=0;
	TDisplayMode displayMode=CEikonEnv::Static()->WsSession().GetDefModeMaxNumColors(numColors, numGrays);
	const TRgb dimmedColor( ColorUtils::RgbLighterColor(aRgb, displayMode) );
	for(ii=0;ii<count;ii++)
		{
		TCoeColorUse colorUse = (*useList)[ii];
		if (colorUse.IsForeground() && !(colorUse.IsHighlights()) &&
				( (numContentColors && colorUse.IsContents()) || (!numContentColors && !colorUse.IsContents()) ) )
			{
			if (colorUse.IsDimmed())
				{
				aControl.OverrideColorL(colorUse.LogicalColor(),dimmedColor);
				}
			else
				{
				aControl.OverrideColorL(colorUse.LogicalColor(),aRgb);
				}
			}
		}

	CleanupStack::PopAndDestroy();	// useList

	aControl.HandleResourceChange(KEikColorResourceChange);
	}

/**
   This method overrides background colours. If there are any contents then
   these colours are not overridden, otherwise all colours are overridden. It 
   doesnot override highlight colours. Dimmed colours are a darker shade
   of new background colour.   
 */
void TColorUtils::SetBackgroundColorL(CCoeControl& aControl, TRgb aRgb)
	{
	CArrayFixFlat<TCoeColorUse>* useList=new(ELeave) CArrayFixFlat<TCoeColorUse>(1);
	CleanupStack::PushL(useList);	
	aControl.GetColorUseListL(*useList);

	const TInt count = useList->Count();

	//
	// Count number of content colours
	//
	TInt numContentColors = 0;
	TInt ii=0;
	for(ii=0;ii<count;ii++)
		{
		TCoeColorUse colorUse = (*useList)[ii];
		if (colorUse.IsForeground() && (colorUse.IsContents()))
			{
			numContentColors++;
			}
		}

	
	// Override  colors
	// Do not override highlight colors
	// If there are any contents colors only override these
	// Otherwise override all colors
	// Dimmed colours are made darker shade of new background color

	TInt numGrays=0;
	TInt numColors=0;
	TDisplayMode displayMode=CEikonEnv::Static()->WsSession().GetDefModeMaxNumColors(numColors, numGrays);
	const TRgb dimmedColor( ColorUtils::RgbMidDarkerColor(aRgb, displayMode) );
	for(ii=0;ii<count;ii++)
		{
		TCoeColorUse colorUse = (*useList)[ii];
		if (colorUse.IsBackground() && !(colorUse.IsHighlights()) &&
				( (numContentColors && colorUse.IsContents()) || (!numContentColors && !colorUse.IsContents()) ) )
			{
			if (colorUse.IsDimmed())
				{
				aControl.OverrideColorL(colorUse.LogicalColor(),dimmedColor);
				}
			else
				{
				aControl.OverrideColorL(colorUse.LogicalColor(),aRgb);
				}
			}
		}

	CleanupStack::PopAndDestroy();	// useList

	aControl.HandleResourceChange(KEikColorResourceChange);
	}

/**
   The method restores the system colour setting for a specified control. The
   method invokes CCoeControl::OverrideColorL() to change the colour mapping
   used in this control.
 */
void TColorUtils::ResetEnvColorsL(CCoeControl& aControl)
	{
	CArrayFixFlat<TCoeColorUse>* useList=new(ELeave) CArrayFixFlat<TCoeColorUse>(1);
	CleanupStack::PushL(useList);	
	aControl.GetColorUseListL(*useList);
	
	CEikonEnv* env=CEikonEnv::Static();

	const TInt count = useList->Count();
	for(TInt ii=0;ii<count;ii++)
		{
		TInt logicalColor=STATIC_CAST(TLogicalColor,(*useList)[ii].LogicalColor());
		aControl.OverrideColorL(STATIC_CAST(TLogicalColor,logicalColor),env->Color(STATIC_CAST(TLogicalColor,logicalColor)));
		}

	CleanupStack::PopAndDestroy();	// useList

	aControl.HandleResourceChange(KEikColorResourceChange);
	}


//
//  CStandaloneLabel  //
//

CStandaloneLabel::CStandaloneLabel()
	{
	}

/**
   This method is an override from CCoeControl. The method is used to colour the
   label control with the system background & foreground colour.   
 */
void CStandaloneLabel::Draw(const TRect& aRect) const 
	{
	CWindowGc& gc = SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(iEikonEnv->ControlColor(EColorWindowBackground,*this));
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(iEikonEnv->ControlColor(EColorWindowText,*this));
	gc.DrawRect(Rect());

	CEikLabel::Draw(aRect);
	}

/**
   This method is an override from CCoeControl. It gets the list of logical
   colours used to draw the control defines how each colour is to be used by the
   label control.    
 */	
void CStandaloneLabel::GetColorUseListL (CArrayFix<TCoeColorUse>& aColorUseList) const
	{
	CEikLabel::GetColorUseListL(aColorUseList);

	TInt commonAttributes = TCoeColorUse::ESurrounds|TCoeColorUse::EActive|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorWindowText);
	colorUse.SetUse(TCoeColorUse::EFore|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorWindowBackground);
	colorUse.SetUse(TCoeColorUse::EBack|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}



//
//  CColorOverrideControl  //
//

CColorOverrideControl::CColorOverrideControl() : iPtr(_L("Edwin"))
	{
	}
/**
   This method is overriden from CCoeControl.It returns the number of
   controls on the compound colour scheme control.
 */
TInt CColorOverrideControl::CountComponentControls() const
    {
    return(15);
    }

/**
   This method is overriden from CCOeControl.It returns the specified
   component of compound custom colour scheme control.
 */
CCoeControl* CColorOverrideControl::ComponentControl(TInt aIndex) const
    {			 
	switch (aIndex)
		{
		case 0:
		default:
		return iOverrideLabel;
		
		case 1:
		return iListBox;

		case 2:
		return iButton;

		case 3:
		return iScrollBar;
		
		case 4:
		return iEdwin;

		case 5:
		return iChoiceList;

		case 6:
		return iCaptionedCheckBox;

		case 7:
		return(iOpBut[0]);

		case 8:
		return(iOpBut[1]);

		case 9:
		return(iOpBut[2]);

		case 10:
		return iNumberEditor;

		case 11:
		return iComboBox;

		case 12:
		return iSecretEditor;

		case 13:
		return iProgressInfo;

		case 14:
		return iClock;
		}
    }

const TInt KXStart = 10;
const TInt KYStart = 10;
const TInt KXSpacing = 5;
const TInt KYSpacing = 2;
const TInt KControlWidth = 180;
const TInt KLbxHeight = 50;

const TInt KLongEnoughToCauseComponentsToBeCreated=200;

/**
   This method creates custom colour scheme control. The custom colour scheme
   control consists of (1) Label Control (2) Text Button (3) Edwin control
   (4) List box (5) Choice List control (6) Scroll Bar (7) Captioned Control
   (8) Integer Editor control (9) Combo Box (10) Progress Bar (11) Secret
   Editor (12) Menu Bar and (13) Clock Control.
 */
void CColorOverrideControl::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    Window().SetShadowDisabled(ETrue);
    SetRect(aRect);

	iBrushAndPenContext=CCoeBrushAndPenContext::NewL();
	iBrushAndPenContext->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iBrushAndPenContext->SetBrushColor(iEikonEnv->ControlColor(EColorToolbarBackground,*this));
	iBrushAndPenContext->SetPenColor(iEikonEnv->ControlColor(EColorToolbarText,*this));

	TInt yPos = KYStart;
	TInt xPos = KXStart;

	TInt halfWidth = (KControlWidth-KXSpacing)/2;

	iOverrideLabel = new(ELeave) CStandaloneLabel;
	iOverrideLabel->SetContainerWindowL(*this);
	iOverrideLabel->SetTextL(_L("Label"));
	iOverrideLabel->SetControlContext(iOverrideLabel);
	TSize size=iOverrideLabel->MinimumSize();
	size.iWidth=halfWidth;
	iOverrideLabel->SetRect(TRect(TPoint(xPos,yPos),size));

	iButton = new(ELeave) CEikTextButton;
	iButton->SetContainerWindowL(*this);
	iButton->SetTextL(_L("Button text"),CEikCommandButtonBase::EFirst);
	size=iButton->MinimumSize();
	size.iWidth=halfWidth;
	iButton->SetRect(TRect(TPoint(xPos+halfWidth+KXSpacing,yPos),size));

	yPos+=size.iHeight+KYSpacing;

	iEdwin=new(ELeave) CEikEdwin;
	iEdwin->SetContainerWindowL(*this);
	iEdwin->ConstructL(EEikEdwinNoWrap|EEikEdwinInclusiveSizeFixed,150,0,3);
	iEdwin->SetTextL(&iPtr);
	size=iEdwin->MinimumSize();
	size.iWidth=KControlWidth;
	iEdwin->SetRect(TRect(TPoint(xPos,yPos),size));
	iEdwin->CreatePreAllocatedScrollBarFrameL()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOn,CEikScrollBarFrame::EOn);
	iEdwin->ForceScrollBarUpdateL();

	yPos+=size.iHeight+KYSpacing;

	iListBox = new(ELeave) CEikTextListBox;
	iListBox->SetContainerWindowL(*this);
	TResourceReader resourceReader;
	iCoeEnv->CreateResourceReaderLC(resourceReader, R_TCOLOVR_LBX);
	iListBox->ConstructFromResourceL(resourceReader);
	CleanupStack::PopAndDestroy(); // resourceReader
	CEikScrollBarFrame* sbFrame=iListBox->CreateScrollBarFrameL();
	sbFrame->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EOn);
	size.iHeight=KLbxHeight;
	size.iWidth=KControlWidth;
	iListBox->SetRect(TRect(TPoint(xPos,yPos),size));

	iListBox->SetFocus(ETrue);

	yPos+=KLbxHeight+KYSpacing;

	iChoiceList = new(ELeave) CEikChoiceList;
	iChoiceList->SetContainerWindowL(*this);
	iChoiceList->SetArrayL(R_TCOLOVR_CHOICES);
	size=iChoiceList->MinimumSize();
	size.iWidth=halfWidth;
	iChoiceList->SetRect(TRect(TPoint(xPos,yPos),size));

	iScrollBar = new(ELeave) CEikScrollBar;
	iScrollBar->ConstructL(NULL,this,CEikScrollBar::EHorizontal,KLongEnoughToCauseComponentsToBeCreated,CEikScrollBar::EButtonsEitherSideOfShaft); 
	size=iScrollBar->MinimumSize();
	size.iWidth=halfWidth;
	iScrollBar->SetLengthL(halfWidth);
	iScrollBar->SetRect(TRect(TPoint(xPos+halfWidth+KXSpacing,yPos),size));

	yPos+=size.iHeight+KYSpacing;
	
	iCaptionedCheckBox=new(ELeave) CEikCaptionedControl;
	CEikLabel* label=new(ELeave) CEikLabel;
	label->SetContainerWindowL(*this);
	iCaptionedCheckBox->iCaption=label;
	_LIT(KCaption,"Caption");
	label->SetTextL(KCaption);
	CEikCheckBox* checkBox=new(ELeave) CEikCheckBox;
	checkBox->SetContainerWindowL(*this);
	iCaptionedCheckBox->iControl=checkBox;
	iCaptionedCheckBox->SetContainerWindowL(*this);	
	size=iCaptionedCheckBox->MinimumSize();
	iCaptionedCheckBox->SetRect(TRect(TPoint(xPos,yPos),size));

	iBCoord=new(ELeave) TEikButtonCoordinator;
    for (TInt ii=0; ii<3; ii++)
        {
		CEikOptionButton* tmp=new(ELeave) CEikOptionButton;
        iOpBut[ii]=tmp;
		tmp->ConstructL();
        tmp->SetContainerWindowL(*this);
		tmp->SetCoordinator(iBCoord);
		tmp->SetState(ii==0? CEikButtonBase::ESet: CEikButtonBase::EClear);
		size=tmp->MinimumSize();
		tmp->SetRect(TRect(TPoint(xPos+KControlWidth-(ii+1)*size.iWidth,yPos),size));
        }
	
	yPos+=size.iHeight+KYSpacing;

	iNumberEditor=new(ELeave) CEikNumberEditor();
	iNumberEditor->SetContainerWindowL(*this);
	iNumberEditor->ConstructL(0,100,50); 
	size=iNumberEditor->MinimumSize();
	size.iWidth=halfWidth;
	iNumberEditor->SetRect(TRect(TPoint(xPos,yPos),size));

	iComboBox=new(ELeave) CEikComboBox();
	iComboBox->ConstructL(*this,10,10,5);
	CDesCArray* itemArray=new(ELeave) CDesCArrayFlat(5);
	itemArray->AppendL(_L("Combo Item"));
	itemArray->AppendL(_L("Combo Item"));
	itemArray->AppendL(_L("Combo Item"));
	itemArray->AppendL(_L("Combo Item"));
	iComboBox->SetArray(itemArray);
	size=iComboBox->MinimumSize();
	size.iWidth=halfWidth;
	iComboBox->SetRect(TRect(TPoint(xPos+halfWidth+KXSpacing,yPos),size));
    

	yPos = KYStart;
	xPos = KXStart + 3*KControlWidth/2;

	iSecretEditor = new(ELeave) CEikSecretEditor();
	iSecretEditor->SetContainerWindowL(*this);
	size=iSecretEditor->MinimumSize();
	size.iWidth=halfWidth;
	iSecretEditor->SetRect(TRect(TPoint(xPos,yPos),size));


	CEikProgressInfo::SInfo info;
	info.iSplitsInBlock=0;
	info.iFinalValue=100;
	info.iWidth=halfWidth;
	info.iHeight=20;

	iProgressInfo = new(ELeave) CEikProgressInfo(info);
	iProgressInfo->SetContainerWindowL(*this);
	iProgressInfo->SetFinalValue(100);
	iProgressInfo->SetAndDraw(20);
	size=iProgressInfo->MinimumSize();
	size.iWidth=halfWidth;
	iProgressInfo->SetRect(TRect(TPoint(xPos+halfWidth+KXSpacing,yPos),size));

	yPos+=size.iHeight+KYSpacing;

	iMenuBar = new(ELeave) CEikMenuBar();
	iMenuBar->ConstructL(this);
	iMenuBar->SetMenuTitleResourceId(R_TCOLOVR_MENUS);
	iMenuBar->TryDisplayMenuBarL();
	size=iMenuBar->MinimumSize();
	size.iWidth=KControlWidth;
	iMenuBarRect=TRect(TPoint(xPos,yPos),size);
	iMenuBar->SetRect(iMenuBarRect);

	yPos+=size.iHeight+3*KYSpacing;
	
	iClock = new(ELeave) CEikClock();
	iClock->SetContainerWindowL(*this);
	iClock->SetControlContext(iBrushAndPenContext);
	iCoeEnv->CreateResourceReaderLC(resourceReader, R_TCOLOVR_CLOCK);
	iClock->ConstructFromResourceL(resourceReader);
	CleanupStack::PopAndDestroy(); // resourceReader
	size=iClock->MinimumSize();
	size.iWidth=KControlWidth;
	iClock->SetRect(TRect(TPoint(xPos,yPos),size));

	yPos+=size.iHeight+3*KYSpacing;

	iConsole = new(ELeave) CEikConsoleControl();
	size.iHeight=20;
	size.iWidth=KControlWidth;
	iConsole->ConstructL(TPoint(xPos,yPos),size,0,EEikConsWinInPixels);

	yPos+=size.iHeight+3*KYSpacing;

	iMenu = new(ELeave) CEikMenuPane(this); 
	iMenu->ConstructL(NULL);
	RestoreMenuL(iMenu,R_TCOLOVR_MENU,MEikMenuObserver::EMenuPane);
	size=iMenu->MinimumSize();
	size.iWidth=KControlWidth;
	iMenu->SetRect(TRect(TPoint(xPos,yPos),size));	
	iMenu->StartDisplayingMenuPane(NULL,TPoint(xPos,yPos),NULL,0);

	ActivateL();
    }

/**
   @SYMTestCaseID UIF-tcolovrstep-ToggleFloatingMenuL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test making the Menu Bar visible / invisible.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method checks whether the menu bar is visible or not and
   makes the menu bar invisible or visible correspondingly.
  
   @SYMTestExpectedResults If the menu bar is visible then it should be made invisible and vice versa.
 */
void CColorOverrideControl::ToggleFloatingMenuL()
	{
	if(iMenuBar->IsVisible())
		iMenuBar->StopDisplayingMenuBar();
	else
		{
		iMenuBar->TryDisplayMenuBarL();
		iMenuBar->SetRect(iMenuBarRect);
		}
	}

/**
   @SYMTestCaseID UIF-tcolovrstep-Dim
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test making contols on the colour scheme control dimmed.
 
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method checks whether each control on the colour scheme
   control is dimmed. It then makes each control dim if it is not already dimmed
   by calling CCoeControl::SetDimmed().
  
   @SYMTestExpectedResults The controls should be dimmed if it is not already dimmed.
 */
void CColorOverrideControl::Dim()
	{
	const TInt count=CountComponentControls();
	for(TInt i=0;i<count;i++)
		{
		CCoeControl* ctl=ComponentControl(i);
		ctl->SetDimmed(!ctl->IsDimmed());
		}
	}

/**
   @SYMTestCaseID UIF-tcolovrstep-SetSystemColorsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test restoring a control's colour setting.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests restoring the system colour setting for the
   custom colour scheme control. To perform this, handle for each of the
   controls on the colour scheme control is obtained and
   CCoeControl::OverrideColorL() method is called to change the colour
   mapping used in this control.
  
   @SYMTestExpectedResults The method should restore the system colour setting
   for the custom colour scheme control.
 */
void CColorOverrideControl::SetSystemColorsL()
	{
	const TInt count=CountComponentControls();
	for(TInt i=0;i<count;i++)
		{
		CCoeControl* ctl=ComponentControl(i);
		TColorUtils::ResetEnvColorsL(*ctl);
		}
	TColorUtils::ResetEnvColorsL(*iMenuBar);
	iMenuBar->StopDisplayingMenuBar();
	iMenuBar->TryDisplayMenuBarL();
	iMenuBar->SetRect(iMenuBarRect);
	TColorUtils::ResetEnvColorsL(*iMenu);
	iMenu->DrawNow();
	}

/**
   The method is an override from MEikMenuObserver. It is called by the Uikon
   framework to handle the emphasising or de-emphasising of a menu window. 
 */
void CColorOverrideControl::SetEmphasis(CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/)
	{
	}

/**
   The method is an override from MEikMenuObserver. It processes user commands.
 */
void CColorOverrideControl::ProcessCommandL(TInt /*aCommandId*/)
	{
	}

const TInt KWidth = 7;
const TInt KHeight = 7;

/**
   The method draws the list of colour used to draw a given control.
 */
void CColorOverrideControl::DrawColorBlocks(CCoeControl& aControl, TInt aXPos, TInt aYPos, CWindowGc& aGc ) const
	{
	TRAPD(err,
		CArrayFixFlat<TCoeColorUse>* useList=new(ELeave) CArrayFixFlat<TCoeColorUse>(1);
		CleanupStack::PushL(useList);	
		aControl.GetColorUseListL(*useList);

		const TInt xInc = KWidth-1;

		TInt count = useList->Count();
		for(TInt ii=0;ii<count;ii++)
			{
			TRect rect(TPoint(aXPos,aYPos),TSize(KWidth,KHeight));
			aGc.SetBrushColor(iEikonEnv->ControlColor(STATIC_CAST(TLogicalColor,(*useList)[ii].LogicalColor()),aControl));
			aGc.DrawRect(rect);
			aXPos+=xInc;
			}
	/*
		aXPos = KXStart+2*(KControlWidth+KXSpacing);

		for(ii=0;ii<count;ii++)
			{
			TRect rect(TPoint(aXPos,aYPos),TSize(KWidth,KHeight));
			aGc.SetBrushColor(iEikonEnv->Color(STATIC_CAST(TLogicalColor,(*useList)[ii].LogicalColor())));
			aGc.DrawRect(rect);
			aXPos+=xInc;
			}
	*/
		CleanupStack::PopAndDestroy();	// useList
		);
		__ASSERT_ALWAYS(!err,User::Panic(_L("DrawColorBlocks"),err));
	}

/**
   This method is an override from CCoeControl. The method is used to draw the
   list of colours used to draw each control in the colour scheme control.
 */
void CColorOverrideControl::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(iEikonEnv->ControlColor(EColorWindowBackground,*this));
	gc.DrawRect(Rect());

	TInt blockXStart = KXStart+KControlWidth+KXSpacing;

	DrawColorBlocks(*iOverrideLabel, blockXStart, iOverrideLabel->Rect().iTl.iY, gc);	
	DrawColorBlocks(*iButton, blockXStart, iButton->Rect().iTl.iY + KHeight + 2, gc);
	DrawColorBlocks(*iEdwin, blockXStart, iEdwin->Rect().iTl.iY, gc);
	DrawColorBlocks(*iListBox, blockXStart, iListBox->Rect().iTl.iY, gc);
	DrawColorBlocks(*iChoiceList, blockXStart, iChoiceList->Rect().iTl.iY, gc);
	DrawColorBlocks(*iScrollBar, blockXStart, iScrollBar->Position().iY + KHeight + 2, gc);
	DrawColorBlocks(*iCaptionedCheckBox, blockXStart, iCaptionedCheckBox->Rect().iTl.iY, gc);
	DrawColorBlocks(*iOpBut[0], blockXStart, iOpBut[0]->Rect().iTl.iY + KHeight + 2, gc);
	DrawColorBlocks(*iNumberEditor, blockXStart, iNumberEditor->Rect().iTl.iY, gc);
	DrawColorBlocks(*iComboBox, blockXStart, iComboBox->Rect().iTl.iY + KHeight + 2, gc);

	blockXStart = KXStart+5*KControlWidth/2+2*KXSpacing;

	DrawColorBlocks(*iSecretEditor, blockXStart, iSecretEditor->Position().iY, gc);
	DrawColorBlocks(*iProgressInfo, blockXStart, iProgressInfo->Position().iY + KHeight + 2, gc);
	DrawColorBlocks(*iMenuBar, blockXStart, iMenuBar->Position().iY, gc);
	DrawColorBlocks(*iClock, blockXStart, iClock->Position().iY, gc);
	DrawColorBlocks(*iConsole, blockXStart, iConsole->Position().iY, gc);
	DrawColorBlocks(*iMenu, blockXStart, iMenu->Position().iY, gc);
	}

/**
   The method calls TColorUtils::SetForegroundColorL() to override the system
   foreground colour for the control specified.
 */
void CColorOverrideControl::SetForegroundColorL(CCoeControl& aControl, TRgb aRgb)
	{
	TColorUtils::SetForegroundColorL(aControl,aRgb);
	}

/**
   The method calls TColorUtils::SetBackgroundColorL() to override the system
   background colour for the control specified.   
 */
void CColorOverrideControl::SetBackgroundColorL(CCoeControl& aControl, TRgb aRgb)
	{
	TColorUtils::SetBackgroundColorL(aControl,aRgb);
	}

/**
   @SYMTestCaseID UIF-tcolovrstep-UserOverrideForeAndBackColorsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test overriding system foreground & background colour of the
   colour scheme control.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions This method tests overriding of foreground & background colour
   of controls on the colour scheme control. 
  
   @SYMTestExpectedResults The method should override the foreground & background
   colour of controls on the custom colour scheme control.
   
 */
void CColorOverrideControl::UserOverrideForeAndBackColorsL(TRgb aForeColor, TRgb aBackColor)
	{
	const TInt count=CountComponentControls();
	for(TInt i=0;i<count;i++)
		{
		CCoeControl* ctl=ComponentControl(i);
		SetForegroundColorL(*ctl,aForeColor);
		SetBackgroundColorL(*ctl,aBackColor);
		}
	
	SetForegroundColorL(*iMenuBar,aForeColor);
	SetBackgroundColorL(*iMenuBar,aBackColor);
	iMenuBar->StopDisplayingMenuBar();
	iMenuBar->TryDisplayMenuBarL();
	iMenuBar->SetRect(iMenuBarRect);
	SetForegroundColorL(*iMenu,aForeColor);
	SetBackgroundColorL(*iMenu,aBackColor);
	iMenu->DrawNow();
	}

/**
   This method is an override from CCoeControl. It is used to process key
   events.
 */
TKeyResponse CColorOverrideControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
	{
	return EKeyWasNotConsumed;
	}

CColorOverrideControl::~CColorOverrideControl()
	{
	delete iOverrideLabel;
	delete iListBox;
	delete iButton;
	delete iScrollBar;
	delete iEdwin;
	delete iChoiceList;
	delete iCaptionedCheckBox;
	for (TInt ii=0; ii<3; ii++)
        delete(iOpBut[ii]);
	delete iBCoord;
	delete iNumberEditor;
	delete iComboBox;
	delete iMenuBar;
	delete iSecretEditor;
	delete iProgressInfo;
	delete iClock;
	delete iConsole;
	delete iBrushAndPenContext;
	delete iMenu;
	}


//
//  CColorOverrideDlg  // 
//

/**
	A dialog control for testing overriding of colour.
*/
class CColorOverrideDlg : public CEikDialog
    {
public:
    CColorOverrideDlg();
	~CColorOverrideDlg() {};
private: // from CEikDialog
    TBool OkToExitL(TInt aKeycode);
	void PreLayoutDynInitL();
    };

CColorOverrideDlg::CColorOverrideDlg() 
	{
	} 

/**
   This method is an override from CEikDialog. It is used to perform
   pre-layout dialog initialisation. 
 */
void CColorOverrideDlg::PreLayoutDynInitL()
	{
	TColorUtils::SetForegroundColorL(*this,KRgbWhite);
	TColorUtils::SetBackgroundColorL(*this,KRgbDarkMagenta);
	HandleResourceChange(KEikColorResourceChange);
	}

/**
   This method is an override from CEikDialog. It handles a dialog
   button press for the specified button 
 */
TBool CColorOverrideDlg::OkToExitL(TInt /*aControlId*/)
    {
	return(ETrue);
    }


//
// class CColorOverrideAppUi  //
//

CColorOverrideAppUi::CColorOverrideAppUi(CTmsTestStep* aStep) :
	CTestAppUi(aStep,KTCOLOVRResourceFilePath, R_TCOLOVR_HOTKEYS, R_TCOLOVR_MENUBAR, R_TCOLOVR_TOOLBAR)
	{
	}

/**
   This method sets the status pane layout as specified by the application and
   creates tool bar & custom colour scheme control. It also initiates the
   tests.
 */
void CColorOverrideAppUi::ConstructL()
    {
    CTestAppUi::ConstructL();
	INFO_PRINTF1(_L("Building Status Pane"));
	if( iEikonEnv->AppUiFactory()->StatusPane() )
		{
		iEikonEnv->AppUiFactory()->StatusPane()->SwitchLayoutL(R_STATUS_PANE_LAYOUT_SHELL);
		iEikonEnv->AppUiFactory()->StatusPane()->ApplyCurrentSettingsL();
		}
	INFO_PRINTF1(_L("Building Tool Bar"));
	iToolBar=CEikButtonGroupContainer::NewL(CEikButtonGroupContainer::EToolbar,  CEikButtonGroupContainer::EVertical, this, R_TCOLOVR_TOOLBAR);
	const TRect boundingRect=ClientRect(); // make toolband stretch to the screen width by default
	iToolBar->SetBoundingRect(boundingRect);
	iToolBar->MakeVisible(ETrue);
	AddToStackL(iToolBar);

	INFO_PRINTF1(_L("Building Colour Scheme\n"));
	iColorSchemeControl=new(ELeave) CColorOverrideControl;
    iColorSchemeControl->ConstructL(ClientRect());
	AddToStackL(iColorSchemeControl);
	
 	AutoTestManager().StartAutoTest();
    }


CColorOverrideAppUi::~CColorOverrideAppUi()
    {
	RemoveFromStack(iColorSchemeControl);
	delete iColorSchemeControl;
	RemoveFromStack(iToolBar);
	delete iToolBar;
    }

/**
   The method is an override from CTestAppUi. The method initiates all tests
   by calling CColorOverrideAppUi::HandleCommandL().
 */
void CColorOverrideAppUi::RunTestStepL(TInt aNumStep)
 	{
	User::After(500000);
 	switch(aNumStep)
 		{
 	case 1:
		{
		INFO_PRINTF1(_L("Test Case 1:"));
 		INFO_PRINTF1(_L("Toggle Status Pane Off"));
 		TRAPD(ret,HandleCommandL(EAppCmdToggleSpane));
 		TEST(ret==KErrNone);
 		INFO_PRINTF2(_L("Test case finished with return value = '%d'.\n"), ret);
		}
		break;
	case 2:
		{
		INFO_PRINTF1(_L("Test Case 2:"));
 		INFO_PRINTF1(_L("Toggle Status Pane Off"));
 		TRAPD(ret, HandleCommandL(EAppCmdToggleSpane));
 		TEST(ret==KErrNone);
 		INFO_PRINTF2(_L("Test case finished with return value = '%d'.\n"), ret);
		}
		break;
	case 3:
		{
		INFO_PRINTF1(_L("Test Case 3:"));
		INFO_PRINTF1(_L("Toggle Dialog display On"));
 		TRAPD(ret, HandleCommandL(EAppCmdShowAutoDlg));
 		TEST(ret==KErrNone);
		User::After(5000000);
		//Simulate key entry and flush the buffer to send event to windows server session.
		TKeyEvent event;
		//Set up key event "enter" to simulate key enter to replace clicking "ok" on dialog.
		event.iCode=event.iScanCode=EKeyEnter;
		event.iModifiers= 0;
		event.iRepeats=0;
		RWsSession& ws=CEikonEnv::Static()->WsSession();
		ws.SimulateKeyEvent(event);
		ws.Flush();
 		INFO_PRINTF2(_L("Test case finished with return value = '%d'.\n"), ret);
		}
		break;
	case 4:
		{
		INFO_PRINTF1(_L("Test Case 4:"));
 		INFO_PRINTF1(_L("Toggle Floating Menu Off"));
 		SetTestStepID(_L("UIF-tcolovrstep-ToggleFloatingMenuL"));
 		TRAPD(ret, HandleCommandL(EAppCmdToggleFloatingMenu));
 		TEST(ret==KErrNone);
 		INFO_PRINTF2(_L("Test case finished with return value = '%d'.\n"), ret);
 		RecordTestResultL();
		}
		break;
	case 5:
		{
		INFO_PRINTF1(_L("Test Case 5:"));
 		INFO_PRINTF1(_L("Toggle Floating Menu On"));
 		SetTestStepID(_L("UIF-tcolovrstep-ToggleFloatingMenuL"));
 		TRAPD(ret, HandleCommandL(EAppCmdToggleFloatingMenu));
 		TEST(ret==KErrNone);
 		INFO_PRINTF2(_L("Test case finished with return value = '%d'.\n"), ret);
		RecordTestResultL();
		}
		break;
	case 6:
		{
		INFO_PRINTF1(_L("Test Case 6:"));
 		INFO_PRINTF1(_L("Override foreground and background colours to light on dark"));
 		SetTestStepID(_L("UIF-tcolovrstep-UserOverrideForeAndBackColorsL"));
 		TRAPD(ret, HandleCommandL(EAppCmdOverrideForeAndBackToLightOnDark));
 		TEST(ret==KErrNone);
 		INFO_PRINTF2(_L("Test case finished with return value = '%d'.\n"), ret);
 		User::After(5000000);
 		RecordTestResultL();
		}
		break;
	case 7:
		{
		INFO_PRINTF1(_L("Test Case 7:"));
 		INFO_PRINTF1(_L("Override foreground and background colours to dark on light"));
 		SetTestStepID(_L("UIF-tcolovrstep-UserOverrideForeAndBackColorsL"));
 		TRAPD(ret, HandleCommandL(EAppCmdOverrideForeAndBackToLightOnDark));
 		TEST(ret==KErrNone);
 		INFO_PRINTF2(_L("Test case finished with return value = '%d'.\n"), ret);
 		User::After(5000000);
 		RecordTestResultL();
		}
		break;
	case 8:
		{
		INFO_PRINTF1(_L("Test Case 8:"));
 		INFO_PRINTF1(_L("Dim the text"));
 		SetTestStepID(_L("UIF-tcolovrstep-Dim"));
 		TRAPD(ret, HandleCommandL(EAppCmdDim));
 		TEST(ret==KErrNone);
 		INFO_PRINTF2(_L("Test case finished with return value = '%d'.\n"), ret);
 		RecordTestResultL();
		}
		break;
	case 9:
		{
		INFO_PRINTF1(_L("Test Case 9:"));
 		INFO_PRINTF1(_L("Override f/g and b/g to light on dark"));
 		SetTestStepID(_L("UIF-tcolovrstep-UserOverrideForeAndBackColorsL"));
 		TRAPD(ret, HandleCommandL(EAppCmdOverrideForeAndBackToLightOnDark));
 		TEST(ret==KErrNone);
 		INFO_PRINTF2(_L("Test case finished with return value = '%d'.\n"), ret);
 		User::After(5000000);
 		RecordTestResultL();
		}
		break;
	case 10:
		{
		INFO_PRINTF1(_L("Test Case 10:"));
 		INFO_PRINTF1(_L("Override f/g and b/g to dark on light with dimmed text"));
 		SetTestStepID(_L("UIF-tcolovrstep-Dim"));
 		TRAPD(ret1, HandleCommandL(EAppCmdDim));
 		TEST(ret1==KErrNone);
 		RecordTestResultL();
		SetTestStepID(_L("UIF-tcolovrstep-UserOverrideForeAndBackColorsL"));
 		TRAPD(ret2, HandleCommandL(EAppCmdOverrideForeAndBackToLightOnDark));
 		TEST(ret2==KErrNone);
 		INFO_PRINTF3(_L("Test case finished with return values = '%d' and '%d'.\n"), ret1, ret2);
 		User::After(5000000);
 		RecordTestResultL();
		}
		break;
	case 11:
		{
		INFO_PRINTF1(_L("Test Case 11:"));
 		INFO_PRINTF1(_L("Select System Colours"));
 		SetTestStepID(_L("UIF-tcolovrstep-SetSystemColorsL"));
 		TRAPD(ret, HandleCommandL(EAppCmdSystemColors));
 		TEST(ret==KErrNone);
 		INFO_PRINTF2(_L("Test case finished with return value = '%d'.\n"), ret);
 		RecordTestResultL();
 		CloseTMSGraphicsStep();
		}
		break;
	case 12:
		{
 		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		}
		break;	
	default:
 		break;
 		}
 	}


/**
   This method is called by CColorOverrideAppUi::RunTestStepL() to initiate the tests.
 */
void CColorOverrideAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
    case EEikCmdExit:
        Exit();
        break;
	case EAppCmdToggleSpane:
		if( iEikonEnv->AppUiFactory()->StatusPane() )
		{
			iEikonEnv->AppUiFactory()->StatusPane()->MakeVisible( !iEikonEnv->AppUiFactory()->StatusPane()->IsVisible() );
			iColorSchemeControl->SetRect( ClientRect() );
			iColorSchemeControl->DrawNow();
		}
		break;
	case EAppCmdShowDlg:
		{
		CEikDialog* dialog=new(ELeave) CColorOverrideDlg();	
		dialog->ExecuteLD(R_TCOLOVR_DIALOG);
		}
		break;
	case EAppCmdShowAutoDlg:
		{
		//destroyed when goes out of scope by base class
		CEikDialog* dialog=new(ELeave) CColorOverrideDlg();	
		dialog->ExecuteLD(R_TCOLOVR_AUTO_DIALOG);
		}
		break;
	case EAppCmdSystemColors:
		iColorSchemeControl->SetSystemColorsL();
		iColorSchemeControl->DrawNow();
		break;
	case EAppCmdOverrideForeAndBackToLightOnDark:
		iColorSchemeControl->UserOverrideForeAndBackColorsL(KRgbWhite,KRgbDarkMagenta);
		iColorSchemeControl->DrawNow();
		
		TColorUtils::SetForegroundColorL(*iToolBar,KRgbWhite);
		TColorUtils::SetBackgroundColorL(*iToolBar,KRgbDarkMagenta);
		iToolBar->HandleResourceChange(KEikColorResourceChange);
		iToolBar->DrawNow();
		break;
	case EAppCmdOverrideForeAndBackToDarkOnLight:
		iColorSchemeControl->UserOverrideForeAndBackColorsL(KRgbBlack,KRgbLilac);
		iColorSchemeControl->DrawNow();
		
		TColorUtils::SetForegroundColorL(*iToolBar,KRgbWhite);
		TColorUtils::SetBackgroundColorL(*iToolBar,KRgbDarkMagenta);
		iToolBar->HandleResourceChange(KEikColorResourceChange);
		iToolBar->DrawNow();
		break;
	case EAppCmdToggleFloatingMenu:
		iColorSchemeControl->ToggleFloatingMenuL();
		break;
	case EAppCmdDim:
		iColorSchemeControl->Dim();
		iColorSchemeControl->DrawNow();
		break;
	default:
		Panic(EBadCommandPanic);

        }
    }

/**
   The method creates & sets the application's user interface object.
 */
void CTColOvrStep::ConstructAppL(CEikonEnv* aEikEnv)
	{
	aEikEnv->ConstructL();
 	CColorOverrideAppUi* appUi=new(ELeave) CColorOverrideAppUi(this);
 	appUi->ConstructL();
	CleanupStack::PushL(appUi);
 	aEikEnv->SetAppUi(appUi);
	CleanupStack::Pop();
	// goes out of scope when function leaves and private members are destroyed. App Architecture handles CEikAppUI destruction
	}


TVerdict CTColOvrStep::doTestStepPreambleL()
	{
	SetTestStepResult(EPass);
	return TestStepResult();
	}

CTColOvrStep::~CTColOvrStep()
	{
	}

CTColOvrStep::CTColOvrStep()
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTColOvrStep);
	}

/**
   The method creates & sets the test step's user interface object and launches the test step.
   
 */
TVerdict CTColOvrStep::doTestStepL()
	{
	CloseAllPanicWindowsL(); //this function call is added, because tcolovr test is sensitive to windows left open by tests that have run previously
	INFO_PRINTF1(_L("Test Started"));

	PreallocateHALBuffer();

     __UHEAP_MARK;
 
 	CEikonEnv* eikEnv=new CEikonEnv;
 	TEST(eikEnv!=NULL);
 	if (eikEnv==NULL)
		{
		INFO_PRINTF1(_L("Failed to create Eikon Environment due to lack of Memory"));
 		return TestStepResult();
		}
		
 	TRAPD(err,ConstructAppL(eikEnv));
	TEST(err==KErrNone);
 	if (err!=KErrNone)
		{
		INFO_PRINTF1(_L("Failed to construct Eikon Environment"));
 		delete eikEnv;
		}
 	else
 		eikEnv->ExecuteD();

	 
	REComSession::FinalClose();	
 	__UHEAP_MARKEND;
 
	INFO_PRINTF1(_L("Test Finished!"));
	return TestStepResult();
    }



