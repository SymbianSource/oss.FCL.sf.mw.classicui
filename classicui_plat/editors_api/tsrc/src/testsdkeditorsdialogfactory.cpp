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
* Description:  Test EIKGTED.H
*
*/


//  INCLUDES
#include <gdi.h>

#include "testsdkeditorsdialogfactory.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// TTestSDKEditorsDialogFactory::CTestSDKEditorsDialogFactory
// -----------------------------------------------------------------------------
CTestSDKEditorsDialogFactory::CTestSDKEditorsDialogFactory()
    {
    
    }

// -----------------------------------------------------------------------------
// TTestSDKEditorsDialogFactory::~CTestSDKEditorsDialogFactory
// -----------------------------------------------------------------------------
CTestSDKEditorsDialogFactory::~CTestSDKEditorsDialogFactory()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunPaginateDlgLD
// -----------------------------------------------------------------------------
 TBool CTestSDKEditorsDialogFactory::RunPaginateDlgLD( CEikGlobalTextEditor* /*aEditor*/,
                                                       CPrintSetup* /*aPrintSetup*/,
                                                       CArrayFix<TInt>* /*aCharsPerPage*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::NewDefaultPrintSetupL
// -----------------------------------------------------------------------------
 CPrintSetup* CTestSDKEditorsDialogFactory::NewDefaultPrintSetupL()
    {
    return NULL;
    }
 
// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunCharMapDlgLD( CCoeControl* /*aControl*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunFontDlgLD( TCharFormat& /*aFormat*/,
                                    TCharFormatMask& /*aAttribChangedMask*/,
                                    TCharFormatMask& /*aUndeterminedMask*/,
                                    TDesC& /*aTextSelection*/,
                                    TInt /*aFonts*/,
                                    CGraphicsDevice* /*aGraphicsDevice*/, 
                                    TInt /*aFontControlFlags*/,
                                    const TRgb /*aBackGroundColor*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunInsertObjectDlgLD( 
                                    CEikEmbeddableAppList* /*aList*/,
                                    TInt& /*aChoice*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunObjectInfoDlgLD( const TDesC& /*aCaption*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunFormatObjectDlgLD( CApaDoor& /*aDoor*/,
                                    CApaDocument& /*aDoc*/,
                                    const TSize& /*aDefaultIconSize*/ )
    {
    return ETrue;
    }


// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunEdwinFindDlgLD( SEdwinFindModel* /*aModel*/,
                                                       CDesCArray* /* aFindList*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunEdwinReplaceDlgLD( SEdwinFindModel* /* aModel*/,
                                                          CDesCArray* /*aFindList*/,
                                                          CDesCArray* /*aReplaceList*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunEdwinReplaceOptionDlgLD( 
                                    CEikGlobalTextEditor* /*aEdwin*/,
                                    SEdwinFindModel* /*aModel*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunAlignDlgLD( CParaFormat* /*aFormat*/, 
                                    TParaFormatMask& /*aAttribChangedMask*/, 
                                    TParaFormatMask& /*aUndeterminedMask*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunSpaceDlgLD( CParaFormat* /*aFormat*/, 
                                    TParaFormatMask& /*aAttribChangedMask*/, 
                                    TParaFormatMask& /*aUndeterminedMask*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunBorderDlgLD( CParaFormat* /*aFormat*/, 
                                    TParaFormatMask& /*aAttribChangedMask*/, 
                                    TParaFormatMask& /*aUndeterminedMask*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunTabsDlgLD( CParaFormat* /*aFormat*/, 
                                    TParaFormatMask& /*aAttribChangedMask*/, 
                                    TParaFormatMask& /*aUndeterminedMask*/,
                                    const TInt /*aPageWidth*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunCharMapDlgLD
// -----------------------------------------------------------------------------
TBool CTestSDKEditorsDialogFactory::RunIndentDlgLD( CParaFormat* /*aFormat*/, 
                                    TParaFormatMask& /*aAttribChangedMask*/, 
                                    TParaFormatMask& /*aUndeterminedMask*/,
                                    const TInt /*aPageWidth*/ )
    {
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsDialogFactory::RunEdwinFindAndReplaceDlgLD
// -----------------------------------------------------------------------------
void CTestSDKEditorsDialogFactory::RunEdwinFindAndReplaceDlgLD( 
                                   MEikFindAndReplaceDlgObserver& /*aObserver*/,
                                   SEdwinFindModel& /*aModel*/, 
                                   TBool /*aFindOnly*/, 
                                   TRect /*aEdwinRect*/ )
    {
    
    }
