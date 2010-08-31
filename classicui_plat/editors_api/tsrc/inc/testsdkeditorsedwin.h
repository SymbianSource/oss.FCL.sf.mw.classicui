/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test EIKEDWIN.H
*
*/

#ifndef C_TESTSDKEDITORSEDWIN_H
#define C_TESTSDKEDITORSEDWIN_H

//  INCLUDES
#include <eikedwin.h>

    /**
    *  CTestSDKEditorsEdwin test class for CEikEdwin protected API.
    */
class CTestSDKEditorsEdwin : public CEikEdwin
    {
public:
    
    /**
    *  ActivateGc test function for testing the 
    * Test ActivateGc function
    */
    void ActivateGc();

    /**
    *  DeactivateGc test function for testing the 
    * Test DeactivateGc function
    */
    void DeactivateGc();
    
    /**
    *  DeactivateGc test function for testing the 
    * Test DeactivateGc function
    */
    void EditObserver( TInt aStartEdit,TInt aEditLength );
    
    /**
    *  TrappedDraw test function for testing the 
    * Test TrappedDraw function
    */
    void TrappedDraw(const TRect& aRect) const;
    
    /**
    *  DrawContents test function for testing the 
    * Test DrawContents function
    */
    void DrawContents();
    
    /**
    *  BaseConstructL test function for testing the 
    * Test BaseConstructL function
    */
    void BaseConstructL();
    
    /**
    *  FormatTextL test function for testing the 
    * Test FormatTextL function
    */
    void FormatTextL();
    
    /**
    *  DeleteHighlightL test function for testing the 
    * Test DeleteHighlightL function
    */
    TInt DeleteHighlightL(TBool& aChanged, 
                          TBool aIsBackSpace=EFalse,
                          TBool aPromptConfirmation=ETrue);
    
    /**
    *  OkToDeleteSelectionL test function for testing the 
    * Test OkToDeleteSelectionL function
    */
    TBool OkToDeleteSelectionL();
    
    /**
    *  OkToDeleteSelectionL test function for testing the 
    * Test OkToDeleteSelectionL function
    */
    void DeleteL( TBool& aChanged, const TCursorSelection& aSelection,
                                   TBool aIsBackSpace=EFalse,
                                   TBool aAllowUndo=ETrue );
    
    /**
    *  TrappedSizeChanged test function for testing the 
    * Test TrappedSizeChanged function
    */
    void TrappedSizeChanged();
    
    /**
    *  HandleSizeChangedL test function for testing the 
    * Test HandleSizeChangedL function
    */
    void HandleSizeChangedL();
    
    /**
    *  CancelSelectionL test function for testing the 
    * Test CancelSelectionL function
    */
    void CancelSelectionL(TEnd aEndOfSelectionToLeaveCursor = CEikEdwin::EStart);
    
    /**
    *  MoveCursorToChunkStartL test function for testing the 
    * Test MoveCursorToChunkStartL function
    */
    void MoveCursorToChunkStartL( TBool aSelect, 
                                  TChunkSize aChunkSize = CEikEdwin::EChunkWord,
                                  TEnd aEndScanningTowards = CEikEdwin::EEnd );
    
    /**
    *  CancelInsertCharFormat test function for testing the 
    * Test CancelInsertCharFormat function
    */
    void CancelInsertCharFormat();
    
    /**
    *  PlaceDataOnClipboardL test function for testing the 
    * Test PlaceDataOnClipboardL function
    */
    void PlaceDataOnClipboardL();
    
    /**
    *  ReportEdwinEventL test function for testing the 
    * Test ReportEdwinEventL function
    */
    void ReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType);
    
    /**
    *  SetLineCursorDetailsL test function for testing the 
    * Test SetLineCursorDetailsL function
    */
    void SetLineCursorDetailsL();
    
    /**
    *  CopyDocumentContentL test function for testing the 
    * Test CopyDocumentContentL function
    */
    void CopyDocumentContentL( CGlobalText& aInText, CGlobalText& aOutText );
    
    /**
    *  DisplayFindTextNotFound test function for testing the 
    * Test DisplayFindTextNotFound function
    */
    void DisplayFindTextNotFound( TDes& aFindText );
    
    /**
    *  HandleTextPastedL test function for testing the 
    * Test HandleTextPastedL function
    */
    void HandleTextPastedL(TInt aStartPos,TInt& aLength);
    
    /**
    *  CreateCustomDrawL test function for testing the 
    * Test CreateCustomDrawL function
    */
    CLafEdwinCustomDrawBase* CreateCustomDrawL();
    
    /**
    *  ReadAknResourceL test function for testing the 
    * Test ReadAknResourceL function
    */
    void ReadAknResourceL(TResourceReader& aReader);
    
    /**
    *  CreateLayoutL test function for testing the 
    * Test CreateLayoutL function
    */
    void CreateLayoutL(MLayDoc* aLayDoc);
    
    /**
    *  CreateTextAndLayoutL test function for testing the 
    * Test CreateTextAndLayoutL function
    */
    void CreateTextAndLayoutL( CParaFormatLayer* aParaFormatLayer,
                               CCharFormatLayer* aCharFormatLayer );
    
    /**
    *  CheckEdwinExtensionL test function for testing the 
    * Test CheckEdwinExtensionL function
    */
    void CheckEdwinExtensionL();
    
    /**
    *  MopSupplyObject test function for testing the 
    * Test MopSupplyObject function
    */
    TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
    };

#endif /*C_TESTSDKEDITORSEDWIN_H*/
