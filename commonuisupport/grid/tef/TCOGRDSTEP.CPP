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
// for tables with INDEFINITE row boundaries\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/


#include <f32file.h>
#include <s32file.h>

#include "TCoGridStep.h"


/**
  Constructor
*/
CTestCoeGridAppUi::CTestCoeGridAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}

/**
  Destructor
*/
CTestCoeGridAppUi::~CTestCoeGridAppUi()
	{
	RemoveFromStack(iGridWin);
	delete iGridWin;
    delete iGridImg;
    delete iGridLay;
	delete iTestCellImg;
	delete iTestLabelImg;
	delete iGridTable;
	delete iZoomFactor;
	}
/**
  Auxiliary Function for T-CoGridStep-RunTestStepL.\n
  Handles the following Key Events\n
  1. Ctrl+ e - Exits the application\n
  2. Ctrl+ t - Toggles the Title Lines\n
  3. Ctrl+ r - Resets the grid to its default layout and sets the cursor position to the cell at the top of the window\n
  4. Ctrl+ m - Sets the zoom factor \n 
  5. Ctrl+ p - Paginates the Grid \n
  6. Ctrl+ i - Inserts columns \n
  7. Ctrl+ d - Deletes columns \n
  8. Ctrl+ c - Changes the grid colour settings\n
  9. Shift+m - Sets the zoom factor\n
 
  @return TKeyResponse indicating whether the key event has been handled or not.\n
 
*/
TKeyResponse CTestCoeGridAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
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
				    iGridWin->GridLay()->ToggleTitleLinesL();
				    break;
			    case CTRL('r'):
				    iGridWin->GridLay()->SetGridToDefault();
					iUndoColors=EFalse;
					iUndoColors =~iUndoColors;
					ChangeColors(iUndoColors);
				    iGridWin->DrawNow();
				    iGridWin->SetCursorPosL(iGridWin->GridLay()->VisibleRange().iFrom);
				    break;
                case CTRL('m'):
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
				case CTRL('c'):
					{
					iUndoColors = ~iUndoColors;
					ChangeColors(iUndoColors);
					iGridWin->DrawNow();
					}
					break;
				case CTRL('i'):
				case CTRL('d'):
					{
					TInt noOfCols=(aKeyEvent.iCode==CTRL('i')) ? 1 : -1;
					iGridLay->InsertDeleteColumns(iGridLay->VisibleRange().iFrom.iCol,
						noOfCols,CGridLay::EAdjustGridRange);
					iGridWin->DrawNow();
					}
					break;
				case CTRL('z'):
					{
					iGridTable->iZeroRows=!iGridTable->iZeroRows;
					iGridImg->ResetReferencePoints();
					iGridLay->ResetVisibleToCell();
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
                case 'm':
		            {
		            TInt zoomFactor=iZoomFactor->ZoomFactor();
		            zoomFactor=(zoomFactor>(TZoomFactor::EZoomOneToOne/4))
			            ? zoomFactor/2 : TZoomFactor::EZoomOneToOne*4;
		            SetZoomFactorL(zoomFactor);
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
  Second Phase constructor for the CTestCoeGridAppUi class.\n
  Gets the current zoom factor.\n
  Sets the grid cell settings like font and zoom factor.\n 
  Constructs a GridTable. It is an interface providing row and column info.\n
  Initializes a GridLay passing the gridtable and null gridimage. \n
  The GridLay object is used to handle the layout of a grid,
  and controls how columns, rows and selections appear.\n
  Initializes a GridImage with gridcell settings which is used to draw cell contents.\n
  A Grid Window is formed containing using GridTable,GridLay and GridImage objects.\n
  The GridWindow offers handlers to pointer and key events.\n
  Sets the current cursor position and activates the Grid Window.\n
*/
void CTestCoeGridAppUi::ConstructL()
    {
    CTestCoeAppUi::ConstructL();

	iUndoColors = EFalse;
	CGraphicsDevice* device=iCoeEnv->ScreenDevice();
	//iCoeEnv->WsSession().SetAutoFlush(ETrue);
	iZoomFactor = new(ELeave) TZoomFactor(device);
    User::Heap().Check();

	const CFont* font = iCoeEnv->NormalFont();
	iTestCellImg = new(ELeave) CTestCellImg(font);

	TFontSpec fontSpec(_L("Swiss"),240);
	iTestLabelImg = new(ELeave) CTestLabelImg(fontSpec,iZoomFactor);
	iTestLabelImg->ConstructL();
    User::Heap().Check();

	iGridLay = new(ELeave) CGridLay(iZoomFactor);
	iGridImg = CGridImg::NewL(device,iTestCellImg,iGridLay);
	iGridImg->SetGridLabelImg(iTestLabelImg);
	iGridTable = new(ELeave) CTestGridTable();
	iGridLay->ConstructL(iGridTable,iGridImg,ENoCols);

	iGridWin = CGridWin::NewL(NULL,iGridLay,iGridImg);
	AddToStackL(iGridWin);

	//
	iGridWin->SetRect((TRect(10,10,630,230)));
	iGridWin->ActivateL();
	iGridWin->DrawNow();
	//
	iGridLay->SetMinRowHeightInPixels(15);	// If ENoRows is not used, a minRowHeight is recommended
	iGridLay->SetColumnBursting(ETrue);
	iGridLay->SetRowPermanentlySelectedL(ETrue);
	iGridLay->SetColumnSelectionDisabled(ETrue);
	iGridLay->SetCursorVisible(EFalse);
	iGridLay->SetHighlightVisible(EFalse);
    iGridLay->SetGridLabelSeparators(EFalse);
	iGridLay->SetAutoClearGridCells(EFalse);

	LoadL();	// Get Persistent data
    User::Heap().Check();
	iGridWin->ActivateL();
    User::Heap().Check();
	
	AutoTestManager().StartAutoTest();

	}
/**
  Auxiliary function for T-CoGridStep-RunTestStepL.\n
  Creates a File Store and returns the pointer.\n
 
  @return FileStore pointer used for storing persistant data.\n 
 
*/
CFileStore* CTestCoeGridAppUi::CreateStoreLC(RFile &aFile)
	{
    CFileStore *store=CDirectFileStore::NewLC(aFile);
	TUid uid;
	uid.iUid=TUint32('G'|('R'<<8)|('D'<<16));
	store->SetTypeL(TUidType(KDirectFileStoreLayoutUid,uid));
    return(store);
	}
/**
  Auxiliary function for T-CoGridStep-RunTestStepL.\n
  Loads the GridLay settings and cursor position from dat file TGRID0.DAT.\n
*/
void CTestCoeGridAppUi::LoadL()
	{
	RFile file;
    TInt err=(file.Open(iCoeEnv->FsSession(),_L("C:\\data\\TCOGRD.DAT"),
		EFileRead|EFileShareReadersOnly));
	if (err==KErrNotFound || err==KErrPathNotFound)
		return;	// Use default settings
	User::LeaveIfError(err);

    CFileStore *store=CDirectFileStore::FromLC(file);
	TStreamId root=store->Root();
    RStoreReadStream source;
    source.OpenLC(*store,root);
	source >> *(iGridWin->GridLay());
	TCellRef cursorPos;
	source >> cursorPos;
//	TInt visibleFromCol=iGridWin->GridLay()->VisibleRange().iFrom.iCol;
//	iGridWin->SetCursorPosL(TCellRef(cursorPos.iRow,visibleFromCol));

	iGridWin->SetCursorPosL(iGridWin->GridLay()->VisibleRange().iFrom);

    CleanupStack::PopAndDestroy(2);	// stream+store
	}
/**
  Auxiliary function for T-CoGridStep-RunTestStepL.\n
  Stores the current grid settings to a Dat File.\n
  Saves the current cursor postion.\n
*/
void CTestCoeGridAppUi::SaveL()
	{
	RFs fsSession=iCoeEnv->FsSession();
	RFile file;
	TInt err=fsSession.MkDir(_L("C:\\data\\"));
	if (err!=KErrAlreadyExists)
		User::LeaveIfError(err);
    User::LeaveIfError(file.Replace(fsSession,_L("C:\\data\\TCOGRD.DAT"),EFileRead|EFileWrite));

    CFileStore *store=CreateStoreLC(file);
	RStoreWriteStream source;
	TStreamId root = source.CreateLC(*store);
	source << *(iGridWin->GridLay());
	source << iGridWin->CursorPos();
	store->SetRootL(root);
    CleanupStack::PopAndDestroy(2);
	}
/**
  Auxiliary function for T-CoGridStep-RunTestStepL.\n
  Sets the zoom factor depending on the argument.\n
  To Redraw the grid table again, the procedure followed is as follows\n
  Recalculates the internal maps that map row and column numbers to heights and widths respectively.\n
  Resets the reference points.\n
  The reference points are the mainpoint and the titlepoint.\n
  Resets the row and column numbers visible at the bottom, and to the right, of the visible area of the grid.\n
*/
void CTestCoeGridAppUi::SetZoomFactorL(TInt aZoomFactor)
	{
	iZoomFactor->SetZoomFactor(aZoomFactor);
	TEST(aZoomFactor == iZoomFactor->ZoomFactor());
	iTestLabelImg->NotifyGraphicsDeviceMapChangeL();
	iGridWin->GridLay()->RecalcPixelSparseMaps();
	iGridWin->GridImg()->ResetReferencePoints();
	iGridWin->GridLay()->ResetVisibleToCell();
	iGridWin->DrawNow();
	}

/**
  Auxiliary function for T-CoGridStep-RunTestStepL.\n
  Sets the Grid colours depending on the argument.\n
  If Reset is enabled, the default colours will be enabled.\n
  Foreground to RGB value(0,0,0) , Background to RGB value(255,255,255) and Lines to (170,170,170).\n
  If Reset is not enabled, Sets the following combination\n
  Forground to Blue, Background to Yellow, Colour of lines to Yellow and Label separators
  to Green.\n 
*/	
void CTestCoeGridAppUi::ChangeColors(TBool aReset)
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
   @SYMTestCaseID UIF-CoGridStep-RunTestStepL
  
   @SYMPREQ 
  
   @SYMTestCaseDesc
   Tests different functionalities of Grid Window
 
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
  
   @SYMTestActions \n
   The following tests are performed \n
   1. Setting grid with its default settings.\n
   2. Simulating right arrow key event.\n
   3. Simulating down arrow key event.\n
   4. Change Color Settings. \n
   5. Setting zoom in factor. \n
   6. Setting zoom out factor.\n
   7. Toggle Title Lines. \n
   8. Scroll Right.\n
   9. Scroll Left.\n
   7. Paginate the Grid. \n
   
  
   @SYMTestExpectedResults  The test pass if the events are handled without exceptions / panic / crashes\n
  
 */
void CTestCoeGridAppUi::RunTestStepL(TInt aNumStep)
	{
	TKeyEvent theKeyEvent;
	Mem::FillZ(&theKeyEvent, sizeof(TKeyEvent));
	TEventCode theType=EEventKey;
	

	User::After(TTimeIntervalMicroSeconds32(1000000));
	
	switch(aNumStep)
		{
		case 1:
		SetTestStepID(_L("UIF-CoGridStep-RunTestStepL"));
		theKeyEvent.iModifiers = EModifierCtrl;
		theKeyEvent.iCode=CTRL('r');
		INFO_PRINTF1(_L("Set grid to default"));
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 2: case 3: case 4:
		INFO_PRINTF1(_L("Move cursor right"));
		theKeyEvent.iCode = EKeyRightArrow;
		iGridWin->OfferKeyEventL(theKeyEvent,theType);
		break;
		case 5: case 6: 
		INFO_PRINTF1(_L("Move cursor down"));
		theKeyEvent.iCode = EKeyDownArrow;
		iGridWin->OfferKeyEventL(theKeyEvent,theType);
		break;
		case 7: case 8: 
		INFO_PRINTF1(_L("Change color"));
		theKeyEvent.iModifiers=EModifierCtrl;
		theKeyEvent.iCode = CTRL('c');
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 9: case 10:
		INFO_PRINTF1(_L("Zoom in"));
		theKeyEvent.iModifiers=EModifierCtrl;
		theKeyEvent.iCode = CTRL('m');
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 11: case 12:
		INFO_PRINTF1(_L("Zoom out"));
		theKeyEvent.iModifiers=EModifierShift;
		theKeyEvent.iCode = 'm';
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 13: 
		INFO_PRINTF1(_L("Toggle title lines"));
		theKeyEvent.iModifiers=EModifierCtrl;
		theKeyEvent.iCode = CTRL('t');
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 14: 
		INFO_PRINTF1(_L("Scroll right"));
		theKeyEvent.iModifiers=EModifierCtrl;
		theKeyEvent.iCode = EKeyRightArrow;
		iGridWin->OfferKeyEventL(theKeyEvent,theType);
		break;
		case 15: 
		INFO_PRINTF1(_L("Scroll left"));
		theKeyEvent.iModifiers=EModifierCtrl;
		theKeyEvent.iCode = EKeyLeftArrow;
		iGridWin->OfferKeyEventL(theKeyEvent,theType);
		break;
		case 16: 
		INFO_PRINTF1(_L("Toggle title lines"));
		theKeyEvent.iModifiers=EModifierCtrl;
		theKeyEvent.iCode = CTRL('t');
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 17: 
		INFO_PRINTF1(_L("Paginate"));
		theKeyEvent.iModifiers=EModifierCtrl;
		theKeyEvent.iCode = CTRL('p');
		HandleKeyEventL(theKeyEvent,theType);
		break;
		case 18: 
		INFO_PRINTF1(_L("Set grid to default"));
		theKeyEvent.iModifiers=EModifierCtrl;
		theKeyEvent.iCode = CTRL('r');
		HandleKeyEventL(theKeyEvent,theType);
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
		case 19: 
		    SaveL();
		    iCoeEnv->Flush();
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;

		}
	}

/**
  Constructs the CTCoGrid Test application.\n
  Initializes the AppUi object.\n
  Sets the AppUi object as the default AppUi for the application.\n
 
*/
void CTCoGridStep::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTestCoeGridAppUi* appUi=new(ELeave) CTestCoeGridAppUi(this);
	appUi->ConstructL();
	aCoe->SetAppUi(appUi);
	}


CTCoGridStep::~CTCoGridStep()
/**
   Destructor
 */
	{
	}

CTCoGridStep::CTCoGridStep()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTCoGridStep);
	}
/**
  Entry Function for the CTCoGrid Test Step.\n
  Initializes a control environment for the application.\n
  Starts the application.\n
 
  @return  : Test execution results indicating whether the test step has passed or failed.\n
  
*/
TVerdict CTCoGridStep::doTestStepL()
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

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}

