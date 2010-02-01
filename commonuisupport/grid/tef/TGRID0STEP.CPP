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
// Tests APIs related to CGridImg,CGridLay and MGridTable classes
// for tables with FIXED row boundaries\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include <e32keys.h>
#include <f32file.h>
#include <s32file.h>

#include "TGrid0Step.h"


//! Color combination for Black background.\n
#define KRgbForeground			TRgb(0,0,0)			// Black
//! Color combination for White background.\n
#define KRgbBackground			TRgb(255,255,255)	// White
//! Color comination for Gray grid lines.\n
#define KRgbLines				TRgb(170,170,170)	// Light Gray
//! Color combination for Label separators.\n
#define KRgbLabelSeparators		TRgb(0,0,0)


/**
  Constructor for the Grid App Ui class \n
*/
CTestGridAppUi::CTestGridAppUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
{}
/**
  Destructor for the Grid App Ui class\n
  Destroys all the member objects like \n
  Grid Window, Grid Image,Grid Lay, Grid Table etc \n
*/
CTestGridAppUi::~CTestGridAppUi()
	{
	RemoveFromStack(iGridWin);
	delete iGridWin;
    delete iGridImg;
    delete iGridLay;
	delete iSheetCellImg;
	delete iSheetLabelImg;
	delete iGridTable;
	delete iZoomFactor;
	delete iDialog;
	}


/**
  
  Handles the following Key Events\n
  1. Ctrl+ e - Exits the application\n
  2. Ctrl+ t - Sets the Title Lines\n
  3. Ctrl+ r - Sets the cursor position to the cell at the top of the window\n
  4. Ctrl+ z - Sets the zoom factor \n 
  5. Ctrl+ p - 
  6. Ctrl+ i - Inserts columns \n
  7. Ctrl+ d - Deletes columns \n
  8. Ctrl+ c - Changes the grid colour settings\n
  9. Shift+t - Makes the cell containing cursor visible \n
  10.Shift+z - Sets the zoom factor\n
  11.Shift+r - Makes the query dialog visible\n
  12.Shift+Esc - Defocuses the query dialog if it is already visible\n
  13.Shift+c - Resizes the columns \n
  14.Shift+r - Resize the rows \n
 
  @return Response to the key event indicating whether the event is successfully handled or not.\n
  
*/
TKeyResponse CTestGridAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	if (aType==EEventKey)
        {
        if ((aKeyEvent.iModifiers&EAllStdModifiers)==EModifierCtrl)
		    {
		    switch (aKeyEvent.iCode)
			    {
			    case CTRL('e'):
				    SaveL();
				    iCoeEnv->Flush();
				    CBaActiveScheduler::Exit();
				    break;
			    case CTRL('t'):
					{
					CGridLay* gridLay=iGridWin->GridLay();
					gridLay->SetTitleLinesL(EFalse);
					iGridWin->ExposeCellL(iGridWin->CursorPos());
				    gridLay->SetTitleLinesL(ETrue);
					}
				    break;
			    case CTRL('r'):
				    iGridWin->GridLay()->SetGridToDefault();
				    iGridWin->DrawNow();
				    iGridWin->SetCursorPosL(iGridWin->GridLay()->VisibleRange().iFrom);
				    break;
                case CTRL('z'):
		            {
		            TInt zoomFactor=iZoomFactor->ZoomFactor();
		            zoomFactor=(zoomFactor<(TZoomFactor::EZoomOneToOne*4))
			            ? zoomFactor*2 : TZoomFactor::EZoomOneToOne/4;
		            SetZoomFactorL(zoomFactor);
				    break;
		            }
				case CTRL('p'):
					iGridWin->GridLay()->SetPageSizeInTwipsL
						(TSize(EPageWidthInTwips,EPageHeightInTwips));
					iGridWin->GridLay()->PaginateL();
					iGridWin->DrawNow();
				    break;
				case CTRL('i'):
				case CTRL('d'):
					{
					const CGridCellRegion* selected=iGridImg->Selected();
					TInt count=selected->Count();
					TInt noOfCols;
					TInt startCol;
					if (count)
						{
						TRangeRef range=(*selected)[count-1];	//last range
						noOfCols=range.iTo.iCol-range.iFrom.iCol+1;
						startCol=range.iFrom.iCol;
						}
					else
						{
						noOfCols=1;
						startCol=iGridWin->CursorPos().iCol;
						}
					if (aKeyEvent.iCode==CTRL('d'))
						noOfCols=-noOfCols;	// Delete 
					iGridLay->InsertDeleteColumns(startCol,noOfCols);
					iGridWin->DrawNow();
					}
					break;
				case CTRL('c'):
					{
					iUndoColors = ~iUndoColors;
					ChangeColors(iUndoColors);
					iGridWin->DrawNow();
					}
					break;
                default:
				    break;
			    }
		    }
        else if ((aKeyEvent.iModifiers&EAllStdModifiers)==EModifierShift)
            {
            switch (User::LowerCase(aKeyEvent.iCode))
                {
				case 't':
					iGridWin->GridLay()->SetTitleLinesL(EFalse);
					iGridWin->ExposeCellL(iGridWin->CursorPos());
				    break;
                case 'z':
		            {
		            TInt zoomFactor=iZoomFactor->ZoomFactor();
		            zoomFactor=(zoomFactor>(TZoomFactor::EZoomOneToOne/4))
			            ? zoomFactor/2 : TZoomFactor::EZoomOneToOne*4;
		            SetZoomFactorL(zoomFactor);
		            break;
		            }
				case 'r':
					{
					iDialog->MakeVisible(ETrue);
					iDialog->SetFocus(ETrue, EDrawNow);	
					break;
					}
                default:
                    break;
                } // switch
            }
        else if (iDialog->IsVisible())
			{
			switch(User::LowerCase(aKeyEvent.iCode))
				{
				case EKeyEscape:
					iDialog->MakeVisible(EFalse);
					break;
				case 'c': //C or c
					{
					iGridImg->StartLabelResize(ETrue,iGridWin->CursorPos().iCol);
					iGridWin->SetResizeMode(CGridWin::EResizeColumn);
					break;
					}
				case 'r':  //R or r
					{
					iGridImg->StartLabelResize(EFalse,iGridWin->CursorPos().iRow);
					iGridWin->SetResizeMode(CGridWin::EResizeRow);
					break;
					}
				default:
					break;
					}
			}
        }
	return EKeyWasConsumed;
	}
/**
  Second Phase constructor for the TestGridAppUi class.\n
  Gets the current zoom factor.\n
  Sets the grid cell settings like font and zoom factor.\n 
  Constructs a GridTable which is an interface providing row and column info.\n
  Initializes a GridLay object passing the gridtable and null gridimage. \n
  The GridLay object is used to Handle the layout of a grid,
  and controls how columns, rows and selections appear.\n
  Initializes a GridImage object with gridcell settings.\n
  A Grid Image object is used to draw cell contents.\n
  A Grid Window is formed containing using GridTable,GridLay and GridImage objects.\n
  The GridWindow offers handlers to pointer and key events.\n
  Sets the current cursor position and activates the Grid Window.\n
*/
void CTestGridAppUi::ConstructL()
    {
	//iCoeEnv->WsSession().SetAutoFlush(ETrue);
	
	iUndoColors = EFalse;
    CTestCoeAppUi::ConstructL();
	CGraphicsDevice* device=iCoeEnv->ScreenDevice();
	iZoomFactor = new(ELeave) TZoomFactor(device);
    User::Heap().Check();

	iSheetCellImg = new(ELeave) CSheetCellImg();
	TFontSpec fontSpec(_L("Swiss"),240);
	iSheetLabelImg = new(ELeave) CSheetLabelImg(fontSpec,iZoomFactor);
	iSheetLabelImg->ConstructL();
    User::Heap().Check();

	iGridLay = new(ELeave) CGridLay(iZoomFactor);
	iGridTable = new(ELeave) MGridTable;
	iGridLay->ConstructL(iGridTable,NULL,ENoRows,ENoCols);	// Test construction of gridLay with NULL gridImg
	iGridLay->SetAutoPagination(ETrue);
//	iGridLay->SetPageBreakLinesHidden(ETrue);
	iGridLay->SetGridEdgeColor(KRgbGridLabels);
//	iGridLay->SetRowPermanentlySelectedL(ETrue);
	
	TCellRef cursorPos;
	TBool isNewCursorPos=LoadL(cursorPos);	// Get Persistent data

	iGridImg = CGridImg::NewL(device,iSheetCellImg,iGridLay);	// Late construction of gridimg
	iGridImg->SetGridLabelImg(iSheetLabelImg);
	iGridLay->SetGridImgL(iGridImg);
// Copies some colours for the label
	//	Getting the grid colors
	iSheetLabelImg->SetGridColors(iGridLay->GridColors());

	iGridWin = CGridWin::NewL(NULL,iGridLay,iGridImg);	//
	AddToStackL(iGridWin);
	iGridWin->SetExtent(TPoint(EGridXPos,EGridYPos),TSize(EGridWidth,EGridHeight));
	iGridWin->ActivateL();
	iGridWin->DrawNow();
	TBool isColumn = ETrue;
	iDialog=new(ELeave) CTGridQueryDialog(isColumn);
	iDialog->ConstructL();
	iDialog->MakeVisible(EFalse);

	//
	//iGridWin->Draw(TRect(TPoint(EGridXPos,EGridYPos),TSize(EGridWidth,EGridHeight)));
	if (isNewCursorPos)
		iGridWin->SetCursorPosL(cursorPos);
	iGridWin->ActivateL();
    User::Heap().Check();
		
	AutoTestManager().StartAutoTest();

	}
/**
  Auxiliary function for T-Grid0Step-RunTestStepL.\n
  Creates a File Store and returns the pointer.\n
 
  @return Pointer to Filestore used for storing Grid data.\n
 
*/
CFileStore* CTestGridAppUi::CreateStoreLC(RFile &aFile)
	{
    CFileStore *store=CDirectFileStore::NewLC(aFile);
	TUid uid;
	uid.iUid=TUint32('G'|('R'<<8)|('D'<<16));
	store->SetTypeL(TUidType(KDirectFileStoreLayoutUid,uid));
    return(store);
	}
/**
  Auxiliary function for T-Grid0Step-RunTestStepL.\n
  Loads the GridLay settings and cursor position from dat file TGRID0.DAT.\n
 
  @return Boolean,True if the data stored in the Stream is displayed on the Grid.\n
 
*/
TBool CTestGridAppUi::LoadL(TCellRef& aCursorPos)
	{
	RFile file;
    TInt err=(file.Open(iCoeEnv->FsSession(),_L("C:\\data\\TGRID0.DAT"),
		EFileRead|EFileShareReadersOnly));
	if (err==KErrNotFound || err==KErrPathNotFound)
		return EFalse;	// Use default settings
	User::LeaveIfError(err);

    CFileStore *store=CDirectFileStore::FromLC(file);
	TStreamId root=store->Root();
    RStoreReadStream source;
    source.OpenLC(*store,root);
	source >> *iGridLay;
	source >> aCursorPos;

    CleanupStack::PopAndDestroy(2);	// stream+store
	return ETrue;
	}
/**
  Auxiliary function for T-Grid0Step-RunTestStepL.\n
  Stores the current grid settings to a Dat File.\n
  Saves the current cursor postion.\n
*/
void CTestGridAppUi::SaveL()
	{
	RFs fsSession=iCoeEnv->FsSession();
	RFile file;
	TInt err=fsSession.MkDir(_L("C:\\data\\"));
	if (err!=KErrAlreadyExists)
		User::LeaveIfError(err);
    User::LeaveIfError(file.Replace(fsSession,_L("C:\\data\\TGRID0.DAT"),EFileRead|EFileWrite));

	CFileStore *store=CreateStoreLC(file);
	RStoreWriteStream source;
	TStreamId root = source.CreateLC(*store);
	source << *iGridLay;
	source << iGridWin->CursorPos();
	store->SetRootL(root);
    CleanupStack::PopAndDestroy(2);
	}
/**
  Auxiliary function for T-Grid0Step-RunTestStepL.\n
  Sets the zoom factor depending on the argument.\n
  To Redraw the grid table again, does the following \n
  Recalculates the internal maps that map row and column numbers to heights and widths respectively.\n
  Resets the reference points.\n
  The reference points are the mainpoint and the titlepoint.\n
  Resets the row and column numbers visible at the bottom, and to the right, of the visible area of the grid.\n
*/
void CTestGridAppUi::SetZoomFactorL(TInt aZoomFactor)
	{
	iZoomFactor->SetZoomFactor(aZoomFactor);
	iSheetLabelImg->NotifyGraphicsDeviceMapChangeL();
	iGridWin->GridLay()->RecalcPixelSparseMaps();
	iGridWin->GridImg()->ResetReferencePoints();
	iGridWin->GridLay()->ResetVisibleToCell();
	iGridWin->DrawNow();
	}
/**
  Auxiliary function for T-Grid0Step-RunTestStepL.\n
  Sets the Grid colours depending on the argument.\n
  If Reset is enabled, the default colours will be enabled.\n
  Foreground to RGB value(0,0,0) , Background to RGB value(255,255,255) and Lines to (170,170,170).\n
  If Reset is not enabled, Sets the following combination
  Forground to Blue, Background to Yellow, Colour of lines to Yellow and Label separators
  to Green.\n 
*/		
void CTestGridAppUi::ChangeColors(TBool aReset)
	{
	if (aReset)
		{
		TGridColors gridColors;
		iGridLay->SetGridColors(gridColors);
		}
	else
		{
		TGridColors newGridColors(KRgbBlue, KRgbYellow, KRgbRed, KRgbGreen);
		iGridLay->SetGridColors(newGridColors);
		}
	iUndoColors = aReset;

	}
/**
   @SYMTestCaseID UIF-Grid0Step-RunTestStepL
  
   @SYMPREQ 
  
   @SYMTestCaseDesc
    Tests different functionalities of Grid Window
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
  
   @SYMTestActions \n
   The following tests are performed \n
   1. Setting a grid as default.\n
   2. Simulating right arrow key event.\n
   3. Simulating down arrow key event.\n
   4. Setting zoom in factor. \n
   5. Setting zoom out factor.\n
   6. Set/Undo Background Color. \n
   7. Making a dialog visible. \n
   8. Resize current row and column. \n
   9. Insertion and Deletion of Columns.\n
  
   @SYMTestExpectedResults All the test cases should execute successfully and the generated key events
   are handled without any error.\n
  
 */
void CTestGridAppUi::RunTestStepL(TInt aNumStep)
	{
	TKeyEvent theKeyEvent;
	TEventCode theType=EEventKey;
	
	Mem::FillZ(&theKeyEvent, sizeof(TKeyEvent));
	//only for debug

	User::After(TTimeIntervalMicroSeconds32(1000000));


	switch(aNumStep)
		{
		case 1: //Set grid to default state
		SetTestStepID(_L("UIF-Grid0Step-RunTestStepL"));
		theKeyEvent.iCode = CTRL('r');
		theKeyEvent.iModifiers=EModifierCtrl;
		INFO_PRINTF1(_L("Set grid to default"));
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 2: case 3: case 4: //Move cursor to left
		theKeyEvent.iCode = EKeyRightArrow;
		theKeyEvent.iModifiers=0;
		INFO_PRINTF1(_L("Move cursor to left"));
		iGridWin->OfferKeyEventL(theKeyEvent,theType);
		break;
		case 5: case 6: 
		theKeyEvent.iCode = EKeyDownArrow;
		theKeyEvent.iModifiers=0;//EModifierCtrl;
		INFO_PRINTF1(_L("Move cursor to down"));
		iGridWin->OfferKeyEventL(theKeyEvent,theType);
		break;
		case 7: case 8: 
		theKeyEvent.iCode = CTRL('z'); //Set zoom in factor
		theKeyEvent.iModifiers=EModifierCtrl;
		INFO_PRINTF1(_L("Set zoom in factor"));
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 9: case 10: 
		theKeyEvent.iCode = 'z'; //Set zoom out factor
		theKeyEvent.iModifiers=EModifierShift;
		INFO_PRINTF1(_L("Set zoom out factor"));
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 11: case 12: case 13:
		theKeyEvent.iCode = CTRL('c'); //Set/undo color background
		theKeyEvent.iModifiers=EModifierCtrl;
		INFO_PRINTF1(_L("Set/undo color background"));
		HandleKeyEventL(theKeyEvent,theType);
		break;
		
		case 14:
		theKeyEvent.iCode = 'r'; //Make dialog visible 
		theKeyEvent.iModifiers=EModifierShift;
		INFO_PRINTF1(_L("Make dialog visible "));
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 15:
		theKeyEvent.iCode = 'r';//Resize the current row
		theKeyEvent.iModifiers=0;
		INFO_PRINTF1(_L("Resize the current row"));
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 16:case 17:case 18: //Resize the current row
		INFO_PRINTF1(_L("Resize the current row"));
		theKeyEvent.iCode = EKeyDownArrow;
		theKeyEvent.iModifiers=0;
		iGridWin->OfferKeyEventL(theKeyEvent,theType);
		break;
		case 19: //Finish resize
		theKeyEvent.iCode = EKeyEnter; 
		theKeyEvent.iModifiers=0;
		INFO_PRINTF1(_L("Finish resize"));
		iGridWin->OfferKeyEventL(theKeyEvent,theType);
		break;
		case 20:// Resize the current column
		theKeyEvent.iCode = 'c';
		theKeyEvent.iModifiers=0;
		INFO_PRINTF1(_L("Resize the current column"));
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 21:case 22:case 23: // Resize the current column
		INFO_PRINTF1(_L("Resize the current column"));
		theKeyEvent.iCode = EKeyRightArrow;
		theKeyEvent.iModifiers=0;
		iGridWin->OfferKeyEventL(theKeyEvent,theType);
		break;
		case 24: //Finish resize
		theKeyEvent.iCode = EKeyEnter;
		theKeyEvent.iModifiers=0;
		INFO_PRINTF1(_L("Finish resize"));
		iGridWin->OfferKeyEventL(theKeyEvent,theType);
		break;
		case 25: //Close dialog
		theKeyEvent.iCode = EKeyEscape;
		theKeyEvent.iModifiers=0;
		INFO_PRINTF1(_L("Close dialog"));
		iDialog->OfferKeyEventL(theKeyEvent,theType);
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 26: //Insert column
		theKeyEvent.iCode = CTRL('i');
		theKeyEvent.iModifiers=EModifierCtrl;
		INFO_PRINTF1(_L("Insert column"));
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 27: //Move to right and delete column
		theKeyEvent.iCode = EKeyRightArrow;
		theKeyEvent.iModifiers=0;
		INFO_PRINTF1(_L("Move to right and delete column"));
		iGridWin->OfferKeyEventL(theKeyEvent,theType);
		theKeyEvent.iCode = CTRL('d');
		theKeyEvent.iModifiers=EModifierCtrl;

		HandleKeyEventL(theKeyEvent,theType);
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
		case 28: //exit
		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;		

		}
	}
	

/**
  Constructs the CTGrid0 Test application.\n
  Initializes the AppUi object.\n
  Sets the AppUi object as the default AppUi for the application.\n
 
*/
void CTGrid0Step::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTestGridAppUi* appUi= new (ELeave) CTestGridAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}


CTGrid0Step::~CTGrid0Step()
/**
  Destructor
 */
	{
	}

CTGrid0Step::CTGrid0Step()
/**
  Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTGrid0Step);
	}
/**
  Entry Function for the TGrid0 Test Step.\n
  Initializes a control environment for the application.\n
  Starts the application.\n
*/
TVerdict CTGrid0Step::doTestStepL()
	{

	INFO_PRINTF1(_L("Test Started"));
	PreallocateHALBuffer();

	__UHEAP_MARK;

	CCoeEnv* coe=new(ELeave) CCoeEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}

	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("test finished"));
	return TestStepResult();
	}

