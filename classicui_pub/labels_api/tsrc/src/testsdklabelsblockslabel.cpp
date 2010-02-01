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
* Description:  Test EIKLABEL.H
*
*/



// [INCLUDE FILES]

#include <eikfnlab.h>
#include <eiklabel.h>
#include <avkon.hrh>
#include <gdi.h>
#include <barsread.h>
#include <coeaui.h>
#include <aknsconstants.h>
#include <eikappui.h>
#include <eikenv.h>
#include <aknpictographinterface.h> 
#include <s32mem.h>
#include <testsdklabels.rsg>

#include "testsdklabelslabel.h"
#include "testsdklabelssubaknpictographcallback.h"
#include "testsdklabels.h"

const TInt KTextLength = 20;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    CleanupStack::Pop( label );
    delete label;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelCEikLabelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelCEikLabelL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    STIF_ASSERT_EQUALS( label->Font(), CCoeEnv::Static()->NormalFont() );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelSetLabelAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelSetLabelAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->SetLabelAlignment( ELayoutAlignCenter );
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelSetBrushStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelSetBrushStyleL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->SetBrushStyle( CWindowGc::ESolidBrush );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelSetBrushStyleFromContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelSetBrushStyleFromContextL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->SetBrushStyleFromContext();
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TSize minsize = label->MinimumSize();
    TPoint point( minsize.AsPoint() );
    
    STIF_ASSERT_NOT_EQUALS( 0, point.iX );
    STIF_ASSERT_NOT_EQUALS( 0, point.iY );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KText, "TestSDKLabels" );
    TBuf<KTextLength> text;
    text = *( label->Text() );
    STIF_ASSERT_EQUALS( 0, text.Compare( KText ) );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CArrayFix<TCoeColorUse>* colorUseList = new (ELeave) CArrayFixFlat<TCoeColorUse> ( 1 );
    CleanupStack::PushL( colorUseList );
    label->GetColorUseListL( *colorUseList );
    STIF_ASSERT_NOT_NULL( colorUseList );
    
    CleanupStack::PopAndDestroy( colorUseList );
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->HandleResourceChange( KAknsMessageSkinChange );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelDrawL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->DrawNow();
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelSetTextL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KText, "Labels" );
    STIF_ASSERT_NOT_LEAVES( label->SetTextL( KText ) );
    TBuf<KTextLength> text;
    text = *( label->Text() );
    STIF_ASSERT_EQUALS( 0, text.Compare( KText ) );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelTextL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const TInt KLength = 20;
    label->CropText();
    _LIT( KText, "TestSDKLabels" );
    TBuf<KLength> text;
    text = *( label->Text() );
    STIF_ASSERT_EQUALS( 0, text.Compare( KText ) );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelCropTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelCropTextL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const TInt KLength = 20;
    label->CropText();
    _LIT( KText, "TestSDKLabels" );
    TBuf<KLength> text;
    text = *( label->Text() );
    STIF_ASSERT_EQUALS( 0, text.Compare( KText ) );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelSetBufferReserveLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelSetBufferReserveLengthL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const TInt KLength = 20;
    label->SetBufferReserveLengthL( KLength );
    TBuf<KLength> text;
    text = *( label->Text() );
    TInt length = text.MaxLength();
    STIF_ASSERT_EQUALS( length, KLength );
    
    _LIT( KText, "TestSDKLabels" );
    STIF_ASSERT_EQUALS( 0, text.Compare( KText ) );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelSetFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelSetFontL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const CFont* font = CEikonEnv::Static()->LegendFont();
    label->SetFont( font );
    
    const CFont* fontGet = label->Font();
    STIF_ASSERT_TRUE( font == fontGet );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelFontL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const CFont* font = CEikonEnv::Static()->LegendFont();
    label->SetFont( font );
    
    const CFont* fontGet = label->Font();
    STIF_ASSERT_TRUE( font == fontGet );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelSetEmphasisL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelSetEmphasisL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->SetEmphasis( CEikLabel::TTextEmphasis( 0 ));
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelSetPixelGapBetweenLinesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelSetPixelGapBetweenLinesL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->SetPixelGapBetweenLines( 2 );
    TInt pixelGap = label->PixelGapBetweenLines();
    STIF_ASSERT_EQUALS( 2, pixelGap );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelPixelGapBetweenLinesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelPixelGapBetweenLinesL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TInt pixelGap = label->PixelGapBetweenLines();
    label->SetPixelGapBetweenLines( pixelGap );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelIsUnderlinedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelIsUnderlinedL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->SetUnderlining( ETrue );
    TBool underline = label->IsUnderlined();
    STIF_ASSERT_TRUE( underline );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelSetUnderliningL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelSetUnderliningL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->SetUnderlining( ETrue );
    TBool underline = label->IsUnderlined();
    STIF_ASSERT_TRUE( underline );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelIsStrikethroughL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelIsStrikethroughL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->SetStrikethrough( ETrue );
    TBool strikethrough = label->IsStrikethrough();
    STIF_ASSERT_TRUE( strikethrough );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelSetStrikethroughL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelSetStrikethroughL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->SetStrikethrough( ETrue );
    TBool strikethrough = label->IsStrikethrough();
    STIF_ASSERT_TRUE( strikethrough );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelCalcMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelCalcMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KText, "CalcMinimumSize" );
    TPtrC text( KText );
    TSize size = label->CalcMinimumSize( text );
    TPoint point( size.AsPoint() );
    
    STIF_ASSERT_NOT_EQUALS( 0, point.iX );
    STIF_ASSERT_NOT_EQUALS( 0, point.iY );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelNumberOfLinesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelNumberOfLinesL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TUint8 numberOfLinea = label->NumberOfLines();
    STIF_ASSERT_FALSE( 0 == numberOfLinea );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelBufferReserveLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelBufferReserveLengthL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const TInt KLength = 20;
    label->SetBufferReserveLengthL( KLength );
    TInt reserveLength = label->BufferReserveLength();
    STIF_ASSERT_EQUALS( KLength, reserveLength);
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelUseLogicalToVisualConversionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelUseLogicalToVisualConversionL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->UseLogicalToVisualConversion( EFalse );
    TBool visualConversion= label->LogicalToVisualConversionUsed();
    STIF_ASSERT_FALSE( visualConversion );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelLogicalToVisualConversionUsedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelLogicalToVisualConversionUsedL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TBool visualConversion = label->LogicalToVisualConversionUsed();
    STIF_ASSERT_TRUE( visualConversion );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelEnablePictographsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelEnablePictographsL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CTestSDKLabelsSubAknPictographCallBack *subCallBack = CTestSDKLabelsSubAknPictographCallBack::NewLC();
    CAknPictographInterface* interface = subCallBack->Interface();
    
    label->EnablePictographsL( *interface );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelDisablePictographsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelDisablePictographsL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    label->DisablePictographs();
    
    CTestSDKLabelsSubAknPictographCallBack *subCallBack = CTestSDKLabelsSubAknPictographCallBack::NewLC();
    CAknPictographInterface* interface = subCallBack->Interface();
    label->EnablePictographsL( *interface );
    
    label->DisablePictographs();
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikLabel* label = new (ELeave) CEikLabel;
    CleanupStack::PushL( label );
    
    STIF_ASSERT_NOT_NULL( label );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_LABELS );
    label->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    STIF_ASSERT_NOT_LEAVES( label->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLabelWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLabelWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKLabelsLabel* label = CTestSDKLabelsLabel::NewLC();
    STIF_ASSERT_NOT_NULL( label );
    
    const TInt KLength = 200;
    CBufFlat* buf = CBufFlat::NewL( KLength );
    CleanupStack::PushL( buf );
    RBufWriteStream writeStream;
    CleanupClosePushL( writeStream );
    writeStream.Open( *buf );
    
    STIF_ASSERT_NOT_LEAVES( label->WriteInternalStateL( writeStream ) );
    STIF_ASSERT_NOT_NULL( buf );
    STIF_ASSERT_NOT_NULL( &writeStream );
    
    CleanupStack::PopAndDestroy( &writeStream );
    CleanupStack::PopAndDestroy( buf );
    CleanupStack::PopAndDestroy( label );
    
    return KErrNone;
    
    }

//  [End of File]
